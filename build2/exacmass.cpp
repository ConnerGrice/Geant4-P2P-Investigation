#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TH1F.h>
#include <TF1.h>
#include "info.hh"

//Calcualtes the relativistic momentum
double momentum(double energy, const double mass){
	return sqrt((energy*energy)+(2*energy*mass));
}

void exacmass(){
	//Initialise histogram
	TH1F* exacHist = new TH1F("exacHist","Exact Missing Mass",1000,-1200,-1400);
	exacHist->GetXaxis()->SetTitle("Missing Mass (keV/c^2)");
	exacHist->GetYaxis()->SetTitle("Frequency");

	//Gets file
	TFile quasi("quasi.root");

	//Gets data from file
	TTree* info = nullptr;
	quasi.GetObject("Particles",info);


	TTreeReader reader(info);

	//Initialise data variables
	//Outgoing particle 1
	TTreeReaderValue<double> P1x = {reader,"P1x"};
	TTreeReaderValue<double> P1y = {reader,"P1y"};
	TTreeReaderValue<double> P1z = {reader,"P1z"};
	TTreeReaderValue<double> E1 = {reader,"E1"};
	TLorentzVector P1;

	//Outgoing particle 2
	TTreeReaderValue<double> P2x = {reader,"P2x"};
	TTreeReaderValue<double> P2y = {reader,"P2y"};
	TTreeReaderValue<double> P2z = {reader,"P2z"};
	TTreeReaderValue<double> E2 = {reader,"E2"};
	TLorentzVector P2;

	//Outgoing fragment
	double fragM = MA;

	//Beam info (C-12)
	const double beamM = MA;							//Mass
	const double beamE = ENERGY;						//Energy
	const double beamP = momentum(beamE,beamM);			//Momentum
	TVector3 beam = TVector3(0,0,beamP);				//Momentum 3-vector
	TLorentzVector lbeam = TLorentzVector(beam,beamE);	//Momentum 4-vector

	//Target info (Proton)
	const double targetM = Ma;								//Mass
	TVector3 target = TVector3(0,0,0);						//Momentum 3-Vector
	TLorentzVector ltarget = TLorentzVector(target,targetM);//Momentum 4-vector

	//Sums
	TLorentzVector momOut;	//Total output particle momentum (without frag)
	TLorentzVector momInit;	//Total initial momentum
	TLorentzVector momMiss;	//Missing mass 4-vector
	double missing;

	//Read until all the data has been read
	while (reader.Next()){

		//Momentum 4-vectors
		P1 = TLorentzVector(*P1x,*P1y,*P1z,*E1);
		P2 = TLorentzVector(*P2x,*P2y,*P2z,*E2);

		//Calculates the momentum values
		momOut = P1 + P2;
		momInit = ltarget + lbeam;
		momMiss = momInit-momOut;

		missing = momMiss.M()-fragM;
		std::cout<<missing<<std::endl;

		//Fills histogram with data
		exacHist->Fill(missing);

	}

	//Fits Gaussian to histogram
	TF1 *gfit = new TF1("gfit","gaus");
	exacHist->Fit("gfit","gaus");

	//Draws histogram
	TCanvas* cv = new TCanvas();
	exacHist->Draw();
	exacHist->Write();

	cv->SaveAs("figs/ExactMass.root");
	cv->Print("figs/ExactMass.eps");
	cv->Print("figs/ExactMass.png");

}
