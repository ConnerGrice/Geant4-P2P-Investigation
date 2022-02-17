#include "p2pRunAction.h"

p2pRunAction::p2pRunAction() : G4UserRunAction() {
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
	//manager->CreateNtupleDColumn("P");
	manager->FinishNtuple(0);

	//Data for particles entering outer detector
	manager->CreateNtuple("Outer","Position");
	manager->CreateNtupleIColumn("ID");
	manager->CreateNtupleDColumn("X");
	manager->CreateNtupleDColumn("Y");
	manager->CreateNtupleDColumn("Z");
	manager->FinishNtuple(1);

	manager->CreateNtuple("Particles","Energy");
	manager->CreateNtupleDColumn("E1");
	manager->CreateNtupleDColumn("E2");
	manager->FinishNtuple(2);


}

p2pRunAction::~p2pRunAction() {
	delete G4AnalysisManager::Instance();
}

void p2pRunAction::BeginOfRunAction(const G4Run*){
	G4AnalysisManager* manager = G4AnalysisManager::Instance();
	manager->OpenFile();


}

void p2pRunAction::EndOfRunAction(const G4Run*){


	G4AnalysisManager* manager = G4AnalysisManager::Instance();

	manager->Write();
	manager->CloseFile();

	//delete G4AnalysisManager::Instance();

}
