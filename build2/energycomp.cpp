#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TGraph.h>
#include <TMultiGraph.h>

void energycomp(){

	TFile quasi("quasi.root"); //Contains exact energies
	TFile measured("data.root");//Contains measured energies

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


	Int_t n = 100240; //Number of data points
	Double_t allCalcE1[n],allCalcE2[n],allExactE1[n],allExactE2[n]; //arrays to be filled
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
	E1->SetTitle("Exact Energy vs Calorimeter Energy of Particle 1");
	E1->GetXaxis()->SetTitle("Calorimeter Energy (keV/c^2)");
	E1->GetYaxis()->SetTitle("Exact Energy (keV/c^2)");

	//Graph containing particle 2 data
	TGraph* E2 = new TGraph(n,allCalcE2,allExactE2);
	E2->SetTitle("Exact Energy vs Calorimeter Energy of Particle 2");
	E2->GetXaxis()->SetTitle("Calorimeter Energy (keV/c^2)");
	E2->GetYaxis()->SetTitle("Exact Energy (keV/c^2)");

	//Choice which particle to look at
	int choice;
	std::cout<<"Comparing particle 1 or 2: ";
	std::cin>>choice;

	//Saves and draws the graph that was chosen
	switch(choice){
	case 1:
		E1->Draw("ap");
		cv->SaveAs("figs/energycomp1.root");
		cv->Print("figs/energycomp1.eps");
		cv->Print("figs/energycomp1.png");
		break;
	case 2:
		E2->Draw("ap");
		cv->SaveAs("figs/energycomp2.root");
		cv->Print("figs/energycomp2.eps");
		cv->Print("figs/energycomp2.png");
		break;
	default:
		std::cout<<"Please input 1 or 2"<<std::endl;
		break;
	}
	quasi.Close();
	measured.Close();
}
