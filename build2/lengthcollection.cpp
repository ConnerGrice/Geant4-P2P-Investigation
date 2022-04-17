#include <TFile.h>
#include <TH1F.h>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>

void lengthcollection(){
	Int_t n = 31;
	Int_t c = 0;
	Double_t meanCollection[n],stdDevCollection[n],entriesCollection[n],lengths[n];

	for (int i=20;i<=50;i++){
		std::string file = std::to_string(i);
		std::string filePath = "figs/lengths/" + file + ".root";

		TFile files(filePath.c_str());

		TH1F* data = nullptr;
		files.GetObject("missHist",data);

		lengths[c] =(Double_t)i;
		meanCollection[c] = data->GetMean();
		stdDevCollection[c] = data->GetStdDev();
		entriesCollection[c] = data->GetEntries();

		c++;
		files.Close();
	}
	TCanvas* c1 = new TCanvas();
	TGraph* dets = new TGraph(31,lengths,entriesCollection);
	dets->SetTitle("");
	dets->GetXaxis()->SetTitle("Length of cylindrical Detectors (cm)");
	dets->GetYaxis()->SetTitle("Reactions fully detected");
	dets->SetMarkerStyle(7);
	dets->Draw("acp");
	dets->SaveAs("figs/collections/detections.root");

	c1->SetRightMargin(0.09);
	c1->SetLeftMargin(0.15);
	c1->Print("figs/collections/detections.eps");
	c1->Print("figs/collections/detections.png");



}
