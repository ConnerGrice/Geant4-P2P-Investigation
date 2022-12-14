#include <math.h>
#include <vector>
#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
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

	TH1F* missHist = new TH1F("missHist","Missing Mass",1000,-1100,-1500);

	missHist->GetXaxis()->SetTitle("Missing Mass (keV/c^2)");
	missHist->GetYaxis()->SetTitle("Frequency");


	//Gets data file
	TFile input("build/data.root");
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
	TTreeReaderValue<int> innEvent = {reader,"Event"};

	TTreeReaderValue<int> outID = {reader,"Outer.ID"};	//Track ID
	TTreeReaderValue<double> outX = {reader,"Outer.X"};//Outer detector X coord
	TTreeReaderValue<double> outY = {reader,"Outer.Y"};//Outer detector Y coord
	TTreeReaderValue<double> outZ = {reader,"Outer.Z"};//Outer detector Z coord
	TTreeReaderValue<int> outEvent = {reader,"Outer.Event"};

	TTreeReaderValue<double> E1 = {reader,"Protons.E1"};//Particle 1 energy
	TTreeReaderValue<double> E2 = {reader,"Protons.E2"};//Particle 2 energy

	TTreeReaderValue<double> fragX = {reader,"Particles.PBx"};//Fragment x Mom
	TTreeReaderValue<double> fragY = {reader,"Particles.PBy"};//Fragment y Mom
	TTreeReaderValue<double> fragZ = {reader,"Particles.PBz_lab"};//Fragment z Mom

	std::vector<std::vector<double>> data; //Contains all particle data
	std::vector<std::vector<double>> allEnergy; //Contains all energy values

	int c=0;

	//Loops over all data in collected by detector
	while (reader.Next()){
		//Data for each recorded particles (missed hits included)
		std::vector<double> part = {(double)*innID,//0
									(double)*outID,//1
									(double)*innEvent,//2
									*innX,//3
									*innY,//4
									*innZ,//5
									*outX,//6
									*outY,//7
									*outZ};//8

		data.push_back(part);

		//Tree containing energy values only contains 100240 data points
		if (c <= 100239){
			std::vector<double> energy = {*E1,*E2};
			allEnergy.push_back(energy);
		}
		c++;
	}

	//Random number generator
	gRandom = new TRandom3();
	gRandom->SetSeed(0);
	TRandom3 r3;
	r3.SetSeed(0);

	//Variables for random momentum
	const double FWHW = 0.01/2.35;	//1% FWHW
	double p,pRand;	//Particle momentum
	const double proM = 938.272;	//Mass of a proton

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

	//Total input momentum 4-vector
	TLorentzVector momIn = lbeam + ltarget;

	//Fragment
	const double fragM = MB;	//Fragment mass

	//Contains momentum for particles pairs for a single event
	std::vector<TLorentzVector> eventMom;
	//Momentum 4-vector for a particle
	TLorentzVector lmom;

	//4-vector of the missing mass
	TLorentzVector missingMom;
	//Missing mass value
	double missingMass;

	//Number of events where both particles hit both detectors
	int hitEvent = 0;
	//Total number of events
	int event = 0;

	//Loop though all particles in the dataset
	for(int i=0;i<(int)(data.size()/2);i++){
		//Checks if ANY particle missed ANY of the detectors
		if (data[2*i][0] != -1 && data[2*i][1] != -1 && data[2*i+1][0] != -1 && data[2*i+1][1] != -1){

			eventMom.clear();
			//Loops though the pair of particles for each event that has no misses
			for (int j=0;j<2;j++){

				//Displacement 3-vector of particle
				TVector3 mom = {data[2*i+j][6]-data[2*i+j][3],
								data[2*i+j][7]-data[2*i+j][4],
								data[2*i+j][8]-data[2*i+j][5]};

				//Converts displacement to momentum 4-vector
				//Checks if particle 1
				if (data[2*i+j][0]==1){
					p = momentum(allEnergy[i][0],proM);
					pRand = r3.Gaus(p,p*FWHW);
					mom = pRand*mom.Unit();
					lmom.SetPxPyPzE(mom.x(),mom.y(),mom.z(),allEnergy[i][0]);
				}
				//Checks if particle 2
				if (data[2*i+j][0]==2){
					p = momentum(allEnergy[i][1],proM);
					pRand = r3.Gaus(p,p*FWHW);
					mom = pRand*mom.Unit();
					lmom.SetPxPyPzE(mom.x(),mom.y(),mom.z(),allEnergy[i][1]);
				}
				eventMom.push_back(lmom);

			}
			//Calculates total final 4-momentum
			TLorentzVector momOut = eventMom[0] + eventMom[1];
			//Calculates missing mass 4-momentum
			missingMom = momIn - momOut;
			//Calculates missing mass
			missingMass = missingMom.M()-fragM;
			std::cout<<"Missing Mass: "<<missingMass<<std::endl;
			//Puts value into histogram
			missHist->Fill(missingMass);

			hitEvent++;
		}
		event++;
	}

	std::cout<<"Number of hit events: "<<hitEvent<<std::endl;
	std::cout<<"Number of events: "<<event<<std::endl;


	//Canvas to be drawn on
	TCanvas* cv = new TCanvas();
	missHist->Draw();
	missHist->SaveAs("figs/missing.root");
	//Saving figure
	//cv->SaveAs("figs/missing.root");
	//cv->Print("figs/missing.eps");
	//cv->Print("figs/missing.png");

	//Close files
	input.Close();
	quasi.Close();
}
