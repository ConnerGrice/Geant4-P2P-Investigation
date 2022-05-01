#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>

void gapcollection(){
	Int_t n = 50-6;
	Int_t c = 0;
	Double_t meanCollection[n],stdDevCollection[n],entriesCollection[n],gaps[n];

	for (int i=7;i<=50;i++){
		std::string file = std::to_string(i);
		std::string filePath = "figs/gaps/" + file + ".root";

		TFile files(filePath.c_str());

		TH1F* data = nullptr;
		files.GetObject("missHist",data);

		TF1 *gfit = new TF1("gfit","gaus");//,-1100,-1500);
		data->Fit("gfit","gaus");

		gaps[c] =(Double_t)i/10;
		meanCollection[c] = gfit->GetParameter("Mean");
		stdDevCollection[c] = gfit->GetParameter("Sigma");
		entriesCollection[c] = data->GetEntries()/100240;

		std::cout<<"Mean: "<<meanCollection[c]<<std::endl;
		std::cout<<"Sigma: "<<stdDevCollection[c]<<std::endl;


		c++;
		files.Close();
	}
	TCanvas* c1 = new TCanvas();
	TGraph* dets = new TGraph(n,gaps,stdDevCollection);
	dets->SetTitle("");
	dets->GetXaxis()->SetTitle("Gap between layers (cm)");
	dets->GetYaxis()->SetTitle("Sigma (keV/c^2)");
	dets->SetMarkerStyle(7);
	dets->Draw("acp");
	dets->SaveAs("figs/collections/gaps_sigma_7.root");

	c1->SetRightMargin(0.09);
	c1->SetLeftMargin(0.15);
	c1->Print("figs/collections/gaps_sigma_7.eps");
	c1->Print("figs/collections/gaps_sigma_7.png");



}
