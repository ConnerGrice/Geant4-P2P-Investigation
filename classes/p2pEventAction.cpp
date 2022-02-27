#include "p2pEventAction.h"

p2pEventAction::p2pEventAction(p2pRunAction* ) {
	Edep1=0;
	Edep2=0;
}

p2pEventAction::~p2pEventAction() {

}

void p2pEventAction::BeginOfEventAction(const G4Event*){
	Edep1 = 0;
	Edep2 = 0;
}

void p2pEventAction::EndOfEventAction(const G4Event*){
	G4cout<<"Energy Deposition 1: "<<Edep1<<G4endl;
	G4cout<<"Energy Deposition 2: "<<Edep2<<G4endl;

	//Records final energy deposition by each particle
	G4AnalysisManager* manager = G4AnalysisManager::Instance();
	manager->FillNtupleDColumn(2,0,Edep1);
	manager->FillNtupleDColumn(2,1,Edep2);
	manager->AddNtupleRow(2);
}



