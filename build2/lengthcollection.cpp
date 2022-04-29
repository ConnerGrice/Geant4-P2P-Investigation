#include <TFile.h>
#include <TH1F.h>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>

void lengthcollection(){
	Int_t n = 61;
	Int_t c = 0;
	Double_t meanCollection[n],stdDevCollection[n],entriesCollection[n],lengths[n];

	for (int i=20;i<=80;i++){
		std::string file = std::to_string(i);
		std::string filePath = "figs/lengths/" + file + ".root";

		TFile files(filePath.c_str());

		TH1F* data = nullptr;
		files.GetObject("missHist",data);

		lengths[c] =(Double_t)i;
		meanCollection[c] = data->GetMean();
		stdDevCollection[c] = data->GetStdDev();
		entriesCollection[c] = data->GetEntries()/100240;
		std::cout<<c<<" "<<i<<" "<<filePath<<std::endl;
		c++;
		files.Close();
	}
	TCanvas* c1 = new TCanvas();
	TGraph* dets = new TGraph(n,lengths,entriesCollection);
	dets->SetTitle("");
	dets->GetXaxis()->SetTitle("Length of cylindrical Detectors (cm)");
	dets->GetYaxis()->SetTitle("Detector efficiency");
	dets->SetMarkerStyle(7);
	dets->Draw("acp");
	dets->SaveAs("figs/collections/detections_new.root");

	c1->SetRightMargin(0.09);
	c1->SetLeftMargin(0.15);
	c1->Print("figs/collections/detections_new.eps");
	c1->Print("figs/collections/detections_new.png");



}
