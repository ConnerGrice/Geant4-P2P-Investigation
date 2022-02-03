#include "TTree.h"
#include "TFile.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

#include <TVector3.h>

void missingmass(){
	TFile input("data_t0.root");

	TTree* inner=nullptr;
	input.GetObject("Inner",inner);

	TTree* outer=nullptr;
	input.GetObject("Outer",outer);

	//inner->AddFriend(outer);

	TTreeReader reader(inner);

	TTreeReaderValue<Double_t> innX(reader,"X");
	//TTreeReaderValue<Double_t> innY(reader,"Y");
	//TTreeReaderValue<Double_t> innZ(reader,"Z");

	//TTreeReaderValue<Double_t> outX(reader,"outer.X");
	//TTreeReaderValue<Double_t> outY(reader,"outer.Y");
	//TTreeReaderValue<Double_t> outZ(reader,"outer.Z");

	while (reader.Next()){
		std::cout<<"Inner: "<<*innX<<std::endl; //" "<<*innY<<" "<<*innZ<<std::endl;
		//std::cout<<"Outer: "<<*outX<<" "<<*outY<<" "<<*outZ<<std::endl;
	}

}
