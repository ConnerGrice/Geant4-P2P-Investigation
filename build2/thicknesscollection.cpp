#include <TFile.h>
#include <TH1F.h>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>

void thicknesscollection(){
	Int_t n = 100;
	Int_t c = 0;
	Double_t meanCollection[n],stdDevCollection[n],entriesCollection[n],thickness[n];

	for (int i=1;i<=100;i++){
		std::string file = std::to_string(i);
		std::string filePath = "figs/thickness/" + file + ".root";

		TFile files(filePath.c_str());

		TH1F* data = nullptr;
		files.GetObject("missHist",data);

		thickness[c] =(Double_t)(i)/100.0;
		std::cout<<thickness[c]<<std::endl;
		meanCollection[c] = data->GetMean();
		stdDevCollection[c] = data->GetStdDev();
		entriesCollection[c] = data->GetEntries();

		c++;
		files.Close();
	}
	TCanvas* c1 = new TCanvas();
	auto dets = new TGraph(n,thickness,meanCollection);
	dets->SetTitle("");
	dets->GetXaxis()->SetTitle("Thickness of cylindrical Detectors (mm)");
	dets->GetYaxis()->SetTitle("Missing Mass (keV/c^2)");
	dets->SetMarkerStyle(7);
	dets->Draw("acp");
	dets->SaveAs("figs/collections/thickness.root");

	c1->SetRightMargin(0.09);
	c1->SetLeftMargin(0.15);
	c1->Print("figs/collections/thickness.eps");
	c1->Print("figs/collections/thickness.png");



}
