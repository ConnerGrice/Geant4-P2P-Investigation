#include <math.h>
#include <TTree.h>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TSystem.h>

void missingmass(){
	//Gets data file
	TFile input("data.root");

	//Gets separate trees within data file
	TTree* inner=nullptr;
	input.GetObject("Inner",inner);
	TTree* outer=nullptr;
	input.GetObject("Outer",outer);

	//Combines inner and outer trees
	inner->AddFriend(outer);

	//Reader for combined tree
	TTreeReader reader(inner);

	TTreeReaderValue<int> innID = {reader,"ID"};
	TTreeReaderValue<double> innX = {reader,"X"};
	TTreeReaderValue<double> innY = {reader,"Y"};
	TTreeReaderValue<double> innZ = {reader,"Z"};
	TTreeReaderValue<double> pMag = {reader,"P"};

	TTreeReaderValue<int> outID = {reader,"Outer.ID"};
	TTreeReaderValue<double> outX = {reader, "Outer.X"};
	TTreeReaderValue<double> outY = {reader, "Outer.Y"};
	TTreeReaderValue<double> outZ = {reader, "Outer.Z"};


	const double proM=938.272;	//Mass of a proton

	TVector3 disp1,disp2;	//Displacement 3-vectors
	TVector3 mom1,mom2;	//Momentum 3-vectors
	TLorentzVector lmom1,lmom2;	//Momentum 4-vectors


	//Loops through inner tree
	while (reader.Next()){

		//Only uses data from the same particle track
		if(*innID == 1){
			//Gets displacement t 3-vector
			disp1.SetXYZ(*outX-*innX,*outY-*innY,*outZ-*innZ);
			//Gets momentum 3-vector
			mom1 = *pMag*(disp1.Unit());
			//Gets momentum 4-vector
			lmom1.SetPxPyPzE(mom1.X(),mom1.Y(),mom1.Z(),sqrt(proM*proM+mom1.Mag2()));
		}
		if(*innID == 2){
			//Gets displacement 3-vector
			disp2.SetXYZ(*outX-*innX,*outY-*innY,*outZ-*innZ);
			//Gets momentum 3-vector
			mom2 = *pMag*(disp2.Unit());
			//Gets momentum 4-vector
			lmom2.SetPxPyPzE(mom2.X(),mom2.Y(),mom2.Z(),sqrt(proM*proM+mom1.Mag2()));
		}

	}

	//Gets total momentum 4 vector of both outgoing particles
	TLorentzVector momOutSum = lmom1+lmom2;

	std::cout<<lmom1.X()<<","<<lmom1.Y()<<","<<lmom1.Z()<<","<<lmom1.E()<<std::endl;
	std::cout<<lmom2.X()<<","<<lmom2.Y()<<","<<lmom2.Z()<<","<<lmom2.E()<<std::endl;
	std::cout<<momOutSum.X()<<","<<momOutSum.Y()<<","<<momOutSum.Z()<<","<<momOutSum.E()<<std::endl;

	input.Close();
}
