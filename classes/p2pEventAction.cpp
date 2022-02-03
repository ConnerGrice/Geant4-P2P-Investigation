#include "p2pEventAction.h"

p2pEventAction::p2pEventAction(p2pRunAction* ) {
	Edep=0;
}

p2pEventAction::~p2pEventAction() {

}

void p2pEventAction::BeginOfEventAction(const G4Event*){
	Edep = 0;


}

void p2pEventAction::EndOfEventAction(const G4Event*){
	G4cout<<"Energy Deposition: "<<Edep<<G4endl;
}



