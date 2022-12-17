#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TGraph.h>


void plotprinter(){

	//File name of canvas you want to save as an image
	std::string file = "figs/ExactMass";

	//Name of the plot
	std::string plotName = "c1_n2";

	//Output file names
	std::string root = file + ".root";
	std::string eps = file + ".eps";
	std::string png = file + ".png";

	std::cout<<root<<std::endl;

	//Gets root file
	TFile plot(root.c_str());

	//Gets plot inside file
	TCanvas* data = nullptr;
	plot.GetObject(plotName.c_str(),data);

	//Outputs canvas as images
	data->Draw();
	data->Print(png.c_str());
	data->Print(eps.c_str());

	plot.Close();
}
