#include <TTree.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TH1F.h>
#include <TF1.h>
#include "info.hh"

double momentum(double energy, const double mass){
	return sqrt((energy*energy)+(2*energy*mass));
}

void exacmass(){

	TH1F* exacHist = new TH1F("exacHist","Exact Missing Mass",1000,-100,100);

	TFile quasi("quasi.root");

	TTree* info = nullptr;
	quasi.GetObject("Particles",info);

	TTreeReader reader(info);

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
	TTreeReaderValue<double> PBx = {reader,"PBx"};
	TTreeReaderValue<double> PBy = {reader,"PBy"};
	TTreeReaderValue<double> PBz = {reader,"PBz_lab"};
	TTreeReaderValue<double> EB = {reader,"EB"};
	double fragM = MA;
	TLorentzVector frag;

	//Beam info (C-12)
	const double beamM = MA;	//Mass
	const double beamE = ENERGY;			//Energy
	const double beamP = momentum(beamE,beamM);			//Momentum
	TVector3 beam = TVector3(0,0,beamP);	//Momentum 3-vector
	TLorentzVector lbeam = TLorentzVector(beam,beamE);	//Momentum 4-vector

	//Target info (Proton)
	const double targetM = Ma;							//Mass
	TVector3 target = TVector3(0,0,0);						//Momentum 3-Vector
	TLorentzVector ltarget = TLorentzVector(target,targetM);//Momentum 4-vector

	//Sums
	TLorentzVector momOut;	//Total output particle momentum (without frag)
	TLorentzVector momInit;	//Total initial momentum
	TLorentzVector momMiss;	//Missing mass 4-vector
	double missing;



	while (reader.Next()){
		P1 = TLorentzVector(*P1x,*P1y,*P1z,*E1);
		P2 = TLorentzVector(*P2x,*P2y,*P2z,*E2);
		frag =TLorentzVector(*PBx,*PBy,*PBz,*EB);

		momOut = P1 + P2;
		momInit = ltarget + lbeam;
		momMiss = momInit-momOut;

		missing = momMiss.M()-fragM;
		std::cout<<missing<<std::endl;

		exacHist->Fill(missing);

	}
	TCanvas* cv = new TCanvas();
	exacHist->Draw();

}
