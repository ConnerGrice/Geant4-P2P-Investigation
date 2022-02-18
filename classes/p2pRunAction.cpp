#include "p2pRunAction.h"

p2pRunAction::p2pRunAction() : G4UserRunAction() {
	//Creates the tree at when the run action is constructed
	G4AnalysisManager* manager = G4AnalysisManager::Instance();
	manager->SetNtupleMerging(true);
	manager->SetVerboseLevel(1);

	manager->SetFileName("data.root");

	//Data for particles entering inner detector
	manager->CreateNtuple("Inner","Position");
	manager->CreateNtupleIColumn("ID");
	manager->CreateNtupleDColumn("X");
	manager->CreateNtupleDColumn("Y");
	manager->CreateNtupleDColumn("Z");
	manager->FinishNtuple(0);

	//Data for particles entering outer detector
	manager->CreateNtuple("Outer","Position");
	manager->CreateNtupleIColumn("ID");
	manager->CreateNtupleDColumn("X");
	manager->CreateNtupleDColumn("Y");
	manager->CreateNtupleDColumn("Z");
	manager->FinishNtuple(1);

	//Data for the energy deposition into the calorimeter by each outgoing proton
	manager->CreateNtuple("Protons","Energy");
	manager->CreateNtupleDColumn("E1");
	manager->CreateNtupleDColumn("E2");
	manager->FinishNtuple(2);


}

p2pRunAction::~p2pRunAction() {
	delete G4AnalysisManager::Instance();
}

void p2pRunAction::BeginOfRunAction(const G4Run*){
	G4AnalysisManager* manager = G4AnalysisManager::Instance();

	//Opens the tree for data collection at the start of each run
	manager->OpenFile();

}

void p2pRunAction::EndOfRunAction(const G4Run*){
	G4AnalysisManager* manager = G4AnalysisManager::Instance();

	//Writes then closes the tree at the end of the run
	manager->Write();
	manager->CloseFile();

}
