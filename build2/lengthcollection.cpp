#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <vector>
#include <TGraph.h>
#include <TCanvas.h>

void lengthcollection(){
	//Number of experiments
	Int_t n = 61-5;

	//Counter
	Int_t c = 0;

	//Arrays to contains experiment results (histogram parameters)
	Double_t meanCollection[n],stdDevCollection[n],entriesCollection[n],lengths[n];

	for (int i=25;i<=80;i++){
		//Generates the file path for each experiment
		std::string file = std::to_string(i);
		std::string filePath = "figs/lengths/" + file + ".root";

		//Gets the root file object
		TFile files(filePath.c_str());

		//Gets missing mass histogram
		TH1F* data = nullptr;
		files.GetObject("missHist",data);

		//Fits a Gaussian curve to the histogram
		TF1 *gfit = new TF1("gfit","gaus");
		data->Fit("gfit","gaus");

		//Gets data that will be plotted and puts it into the arrays
		lengths[c] =(Double_t)i;
		meanCollection[c] = gfit->GetParameter("Mean");
		stdDevCollection[c] = gfit->GetParameter("Sigma");
		entriesCollection[c] = data->GetEntries()/100240;
		std::cout<<c<<" "<<i<<" "<<filePath<<std::endl;
		c++;
		files.Close();
	}

	//Plots the data
	TCanvas* c1 = new TCanvas();

	//Choose which data you want to plot
	TGraph* dets = new TGraph(n,lengths,meanCollection);
	dets->SetTitle("");
	dets->GetXaxis()->SetTitle("Length of cylindrical Detectors (cm)");
	dets->GetYaxis()->SetTitle("Mean missing mass (keV/c^2)");
	dets->SetMarkerStyle(7);
	dets->Draw("acp");
	dets->SaveAs("figs/collections/length_mass.root");

	c1->SetRightMargin(0.09);
	c1->SetLeftMargin(0.15);
	c1->Print("figs/collections/length_mass.eps");
	c1->Print("figs/collections/length_mass.png");



}
