#include "p2pRunAction.h"

p2pRunAction::p2pRunAction() : G4UserRunAction() {
}

p2pRunAction::~p2pRunAction() {
	delete G4AnalysisManager::Instance();
}

void p2pRunAction::BeginOfRunAction(const G4Run*){
	G4AnalysisManager* manager = G4AnalysisManager::Instance();
	manager->OpenFile("data.root");

	manager->CreateNtuple("Inner","Position");
	manager->CreateNtupleIColumn("Event");
	manager->CreateNtupleDColumn("X");
	manager->CreateNtupleDColumn("Y");
	manager->CreateNtupleDColumn("Z");
	manager->FinishNtuple(0);

	manager->CreateNtuple("Outer","Position");
	manager->CreateNtupleIColumn("Event");
	manager->CreateNtupleDColumn("X");
	manager->CreateNtupleDColumn("Y");
	manager->CreateNtupleDColumn("Z");
	manager->FinishNtuple(1);
}

void p2pRunAction::EndOfRunAction(const G4Run*){


	G4AnalysisManager* manager = G4AnalysisManager::Instance();

	manager->Write();
	manager->CloseFile();

}
