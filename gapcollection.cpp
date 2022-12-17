#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>

void gapcollection(){
	//Number of experiments
	Int_t start = 1;	//Starting parameter
	Int_t end = 50;		//Ending parameter
	Int_t n = end - start;
	Int_t c = 0;

	//Values to be collected
	Double_t meanCollection[n],stdDevCollection[n],entriesCollection[n],gaps[n];

	//Start = first experiment parameter
	//End = last experiment parameter
	for (int i=start;i<=end;i++){
		//Generates file path string
		std::string file = std::to_string(i);
		std::string filePath = "build2/figs/gaps/" + file + ".root";

		//Gets file
		TFile files(filePath.c_str());

		//Gets histogram from file
		TH1F* data = nullptr;
		files.GetObject("missHist",data);

		//Fits Gaussian to histogram
		TF1 *gfit = new TF1("gfit","gaus");//,-1100,-1500);
		data->Fit("gfit","gaus");

		//Converts to real units
		gaps[c] =(Double_t)i/10;

		//Fills arrays with values
		meanCollection[c] = gfit->GetParameter("Mean");
		stdDevCollection[c] = gfit->GetParameter("Sigma");
		entriesCollection[c] = data->GetEntries()/100240;

		std::cout<<"Mean: "<<meanCollection[c]<<std::endl;
		std::cout<<"Sigma: "<<stdDevCollection[c]<<std::endl;

		c++;
		files.Close();
	}

	//Generates plot
	//User can choose which data to plot

	//Mean missing mass
	TCanvas* c1 = new TCanvas();
	TGraph* dets = new TGraph(n,gaps,meanCollection);
	dets->SetTitle("");
	dets->GetXaxis()->SetTitle("Gap between layers (cm)");
	dets->GetYaxis()->SetTitle("Mean missing mass (keV/c^2)");
	dets->SetMarkerStyle(7);
	dets->Draw("acp");
	dets->SaveAs("figs/collections/gaps_mass.root");

	c1->SetRightMargin(0.09);
	c1->SetLeftMargin(0.15);
	c1->Print("figs/collections/gaps_mass.eps");
	c1->Print("figs/collections/gaps_mass.png");

/*
	//Standard deviation of missing mass
	TCanvas* c1 = new TCanvas();
	TGraph* dets = new TGraph(n,gaps,stdDevCollection);
	dets->SetTitle("");
	dets->GetXaxis()->SetTitle("Gap between layers (cm)");
	dets->GetYaxis()->SetTitle("Standard deviation of missing mass (keV/c^2)");
	dets->SetMarkerStyle(7);
	dets->Draw("acp");
	dets->SaveAs("figs/collections/gaps_std.root");

	c1->SetRightMargin(0.09);
	c1->SetLeftMargin(0.15);
	c1->Print("figs/collections/gaps_std.eps");
	c1->Print("figs/collections/gaps_std.png");
*/

/*
	//Detector efficiency
	TCanvas* c1 = new TCanvas();
	TGraph* dets = new TGraph(n,gaps,entriesCollection);
	dets->SetTitle("");
	dets->GetXaxis()->SetTitle("Gap between layers (cm)");
	dets->GetYaxis()->SetTitle("Detector efficiency");
	dets->SetMarkerStyle(7);
	dets->Draw("acp");
	dets->SaveAs("figs/collections/gaps_eff.root");

	c1->SetRightMargin(0.09);
	c1->SetLeftMargin(0.15);
	c1->Print("figs/collections/gaps_eff.eps");
	c1->Print("figs/collections/gaps_eff.png");
*/



}
