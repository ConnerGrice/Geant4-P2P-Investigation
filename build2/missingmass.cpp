#include <math.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <TRandom3.h>
#include "info.hh"

double momentum(double energy, const double mass){
	return sqrt((energy*energy)+(2*energy*mass));
}

void missingmass(){

	TH1F* missHist = new TH1F("missHist","Missing Mass",1000,-100,100);


	//Gets data file
	TFile input("data.root");
	TFile quasi("quasi.root");

	//Gets separate trees within data file
	TTree* inner=nullptr;
	input.GetObject("Inner",inner);
	TTree* outer=nullptr;
	input.GetObject("Outer",outer);
	TTree* particles=nullptr;
	input.GetObject("Protons", particles);

	TTree* other=nullptr;
	quasi.GetObject("Particles",other);

	//Combines inner and outer trees
	inner->AddFriend(outer);
	inner->AddFriend(particles);
	inner->AddFriend(other);

	//Reader for combined tree
	TTreeReader reader(inner);

	TTreeReaderValue<int> innID = {reader,"ID"};	//Track ID
	TTreeReaderValue<double> innX = {reader,"X"};	//Inner detector X coord
	TTreeReaderValue<double> innY = {reader,"Y"};	//Inner detector Y coord
	TTreeReaderValue<double> innZ = {reader,"Z"};	//Inner detector Z coord

	TTreeReaderValue<int> outID = {reader,"Outer.ID"};	//Track ID
	TTreeReaderValue<double> outX = {reader,"Outer.X"};//Outer detector X coord
	TTreeReaderValue<double> outY = {reader,"Outer.Y"};//Outer detector Y coord
	TTreeReaderValue<double> outZ = {reader,"Outer.Z"};//Outer detector Z coord

	TTreeReaderValue<double> E1 = {reader,"Protons.E1"};//Particle 1 energy
	TTreeReaderValue<double> E2 = {reader,"Protons.E2"};//Particle 2 energy

	TTreeReaderValue<double> fragX = {reader,"Particles.PBx"};//Fragment x Mom
	TTreeReaderValue<double> fragY = {reader,"Particles.PBy"};//Fragment y Mom
	TTreeReaderValue<double> fragZ = {reader,"Particles.PBz_lab"};//Fragment z Mom

	//Random number generator
	gRandom = new TRandom3();
	gRandom->SetSeed(0);
	TRandom3 r3;
	r3.SetSeed(0);

	const double proM = 938.272;	//Mass of a proton
	const double FWHW = 0.01/2.35;	//1% FWHW

	//Beam info (C-12)
	const double beamM = MA;	//Mass
	const double beamE = ENERGY;			//Energy
	const double beamP = momentum(beamE,beamM);			//Momentum
	TVector3 beam = TVector3(0,0,beamP);	//Momentum 3-vector
	TLorentzVector lbeam = TLorentzVector(beam,beamE);	//Momentum 4-vector

	//Target info (Proton)
	const double targetM = proM;							//Mass
	TVector3 target = TVector3(0,0,0);						//Momentum 3-Vector
	TLorentzVector ltarget = TLorentzVector(target,targetM);//Momentum 4-vector

	//Outgoing Particles
	double P1,P2,P1Rand,P2Rand;	//Particle momentum
	TVector3 disp1,disp2;		//Displacement 3-vectors
	TVector3 mom1,mom2;			//Momentum 3-vectors
	TLorentzVector lmom1,lmom2;	//Momentum 4-vectors

	//Fragment
	const double fragM = MB;	//Frag mass
	TVector3 frag;	//Frag 3-vector
	TLorentzVector lfrag;	//Frag 4-vector

	//Sums
	TLorentzVector momOut;	//Total output particle momentum (without frag)
	TLorentzVector momInit;	//Total initial momentum
	TLorentzVector momMiss;	//Missing mass 4-vector

	//Missing mass
	double missingMass;	//Missing mass value

	int c = 1;
	//Loops through inner tree
	while (reader.Next() && c <= 100240){
		/*
		std::cout<<"Reaction "<<c<<":"<<std::endl;
		std::cout<<"Inn ID: "<<*innID<<std::endl;
		std::cout<<"Out ID: "<<*outID<<std::endl;
		std::cout<<"Pro E1: "<<*E1<<std::endl;
		std::cout<<"Pro E2: "<<*E2<<std::endl;
		std::cout<<"Frag P: ("<<*fragX<<","<<*fragY<<","<<*fragZ<<")"<<std::endl;
		*/

		//Defines fragment momentum and 4-momentum
		frag = TVector3(*fragX,*fragY,*fragZ);
		lfrag = TLorentzVector(frag,sqrt(fragM*fragM*frag.Mag2()));

		//Calculates momentum for each particle
		P1 = momentum(*E1,proM);
		P2 = momentum(*E2,proM);

		//Adds random smear of values to simulate calorimeter resolution
		P1Rand = r3.Gaus(P1,P1*FWHW);
		P2Rand = r3.Gaus(P2,P2*FWHW);

		//Only uses data from the same particle track
		if(*innID == 1){
			//Gets displacement t 3-vector
			disp1.SetXYZ(*outX-*innX,*outY-*innY,*outZ-*innZ);

			//Gets momentum 3-vector
			mom1 = P1Rand*(disp1.Unit());

			//Gets momentum 4-vector
			lmom1.SetPxPyPzE(mom1.X(),mom1.Y(),mom1.Z(),*E1);
		}
		if(*innID == 2){
			//Gets displacement 3-vector
			disp2.SetXYZ(*outX-*innX,*outY-*innY,*outZ-*innZ);

			//Gets momentum 3-vector
			mom2 = P2Rand*(disp2.Unit());

			//Gets momentum 4-vector
			lmom2.SetPxPyPzE(mom2.X(),mom2.Y(),mom2.Z(),*E2);
		}
		c++;
		momOut = lmom1+lmom2;
		momInit = lbeam + ltarget;
		momMiss = momInit - momOut;

		missingMass = momMiss.M()-fragM;


		std::cout<<"Missing Mass: "<<missingMass<<" MeV/c^2"<<std::endl;

		missHist->Fill(missingMass);
	}

	TCanvas* cv = new TCanvas();

	missHist->GetXaxis()->SetTitle("Missing Mass (MeV/c^2)");
	missHist->Draw();
	//Gets total momentum 4 vector of both outgoing particles

	cv->SaveAs("missing.root");

	input.Close();
	quasi.Close();
}
