#include <TFile.h>
#include <TH1F.h>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>

void gapcollection(){
	Int_t n = 50;
	Int_t c = 0;
	Double_t meanCollection[n],stdDevCollection[n],entriesCollection[n],gaps[n];

	for (int i=1;i<=50;i++){
		std::string file = std::to_string(i);
		std::string filePath = "figs/gaps/" + file + ".root";

		TFile files(filePath.c_str());

		TH1F* data = nullptr;
		files.GetObject("missHist",data);

		gaps[c] =(Double_t)i/10;
		meanCollection[c] = data->GetMean();
		stdDevCollection[c] = data->GetStdDev();
		entriesCollection[c] = data->GetEntries();

		c++;
		files.Close();
	}
	TCanvas* c1 = new TCanvas();
	TGraph* dets = new TGraph(31,gaps,stdDevCollection);
	dets->SetTitle("");
	dets->GetXaxis()->SetTitle("Gap between detectors (cm) ");
	dets->GetYaxis()->SetTitle("Standard deviation of missing mass (keV/c^2)");
	dets->SetMarkerStyle(7);
	dets->Draw("acp");
	dets->SaveAs("figs/collections/gaps_std.root");

	c1->SetRightMargin(0.09);
	c1->SetLeftMargin(0.15);
	c1->Print("figs/collections/gaps_std.eps");
	c1->Print("figs/collections/gaps_std.png");



}
