#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TGraph.h>
#include <TMultiGraph.h>

void energycomp(){

	TFile quasi("quasi.root"); //Contains exact energies
	TFile measured("build/data.root");//Contains measured energies

	TTree* exact = nullptr;
	quasi.GetObject("Particles",exact);

	TTree* calculated=nullptr;
	measured.GetObject("Protons", calculated);

	exact->AddFriend(calculated);

	TTreeReader reader(exact);

	//Outgoing particle 1
	TTreeReaderValue<Double_t> exactE1 = {reader,"E1"};
	TTreeReaderValue<Double_t> exactE2 = {reader,"E2"};

	TTreeReaderValue<Double_t> calcE1 = {reader,"Protons.E1"};
	TTreeReaderValue<Double_t> calcE2 = {reader,"Protons.E2"};

	//Number of particle experiments
	Int_t n = 100240;

	//Arrays to be filled (Energy for both particles)
	Double_t allCalcE1[n],allCalcE2[n],allExactE1[n],allExactE2[n];
	Int_t c=0;	//counter

	//Gets data and puts them into arrays
	while (reader.Next()){
		allExactE1[c] = *exactE1;
		allExactE2[c] = *exactE2;
		allCalcE1[c] = *calcE1;
		allCalcE2[c] = *calcE2;
		c++;
	}

	//Canvas to be drawn on
	TCanvas* cv = new TCanvas("C1","Energy",0,1000,700,500);
	cv->SetGrid();

	//Graph containing particle 1 data
	TGraph* E1 = new TGraph(n,allCalcE1,allExactE1);
	E1->SetTitle("");
	E1->GetXaxis()->SetTitle("Calorimeter Energy (MeV)");
	E1->GetYaxis()->SetTitle("Exact Energy (MeV)");


	E1->Draw("ap");
	cv->SaveAs("figs/energycomp.root");
	E1->Print("figs/energycomp.eps");

	quasi.Close();
	measured.Close();
}
