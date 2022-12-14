#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TGraph.h>


void plotprinter(){

	std::string file = "figs/energy/energycomp2";
	std::string plotName = "C1";

	std::string root = file + ".root";
	std::string eps = file + ".eps";
	std::string png = file + ".png";

	std::cout<<root<<std::endl;

	TFile plot(root.c_str());

	TCanvas* data = nullptr;
	plot.GetObject(plotName.c_str(),data);

	data->Draw();
	data->Print(png.c_str());
	data->Print(eps.c_str());

	plot.Close();
}
