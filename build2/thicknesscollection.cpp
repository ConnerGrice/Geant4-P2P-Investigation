#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>

void thicknesscollection(){
	//Number of experiments
	Int_t n = 100;
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
		TF1 *gfit = new TF1("gfit","gaus");//,-1100,-1500);
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
	//Plots the wanted data
	//User can change what data is plotted
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
}
