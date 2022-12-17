#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>

void thicknesscollection(){
	//Number of experiments
	Int_t start = 1;	//Starting parameter
	Int_t end = 100;	//Final parameter
	Int_t n = end-start;

	//Counter
	Int_t c = 0;

	//Arrays that will contain plotting data
	Double_t meanCollection[n],stdDevCollection[n],entriesCollection[n],thickness[n];

	for (int i=1;i<=100;i++){
		//Generates file path string
		std::string file = std::to_string(i);
		std::string filePath = "figs/thickness/" + file + ".root";

		//Gets file object
		TFile files(filePath.c_str());

		//Gets histogram from file
		TH1F* data = nullptr;
		files.GetObject("missHist",data);

		//Fits Gaussian to data
		TF1 *gfit = new TF1("gfit","gaus");
		data->Fit("gfit","gaus");

		//Calculates real unit
		thickness[c] =(Double_t)(i)/100.0;
		std::cout<<thickness[c]<<std::endl;

		//Fills the arrays with their data
		meanCollection[c] = gfit->GetParameter("Mean");
		stdDevCollection[c] = gfit->GetParameter("Sigma");
		entriesCollection[c] = data->GetEntries()/100240;

		c++;
		files.Close();
	}
	//Choose which data you want to plot

	//Mean missing mass
	TCanvas* c1 = new TCanvas();
	auto dets = new TGraph(n,thickness,meanCollection);
	dets->SetTitle("");
	dets->GetXaxis()->SetTitle("Thickness of layers Detectors (mm)");
	dets->GetYaxis()->SetTitle("Mean missing mass (keV/c^2)");
	dets->SetMarkerStyle(7);
	dets->Draw("acp");

	dets->SaveAs("figs/collections/thickness_mass.root");

	c1->SetRightMargin(0.09);
	c1->SetLeftMargin(0.15);
	c1->Print("figs/collections/thickness_mass.eps");
	c1->Print("figs/collections/thickness_mass.png");

/*
	//Standard deviation of missing mass
	TCanvas* c1 = new TCanvas();
	auto dets = new TGraph(n,thickness,stdDevCollection);
	dets->SetTitle("");
	dets->GetXaxis()->SetTitle("Thickness of layers Detectors (mm)");
	dets->GetYaxis()->SetTitle("Standard deviation of missing mass (keV/c^2)");
	dets->SetMarkerStyle(7);
	dets->Draw("acp");

	dets->SaveAs("figs/collections/thickness_std.root");

	c1->SetRightMargin(0.09);
	c1->SetLeftMargin(0.15);
	c1->Print("figs/collections/thickness_std.eps");
	c1->Print("figs/collections/thickness_std.png");
*/

/*
	//Detector efficiency
	TCanvas* c1 = new TCanvas();
	auto dets = new TGraph(n,thickness,entriesCollection);
	dets->SetTitle("");
	dets->GetXaxis()->SetTitle("Thickness of layers Detectors (mm)");
	dets->GetYaxis()->SetTitle("Detector efficiency");
	dets->SetMarkerStyle(7);
	dets->Draw("acp");

	dets->SaveAs("figs/collections/thickness_eff.root");

	c1->SetRightMargin(0.09);
	c1->SetLeftMargin(0.15);
	c1->Print("figs/collections/thickness_eff.eps");
	c1->Print("figs/collections/thickness_eff.png");
*/
}
