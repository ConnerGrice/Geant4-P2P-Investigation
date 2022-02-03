#include "p2pSteppingAction.h"

p2pSteppingAction::p2pSteppingAction(p2pEventAction* eventAction) {
	EventAction = eventAction;
}

p2pSteppingAction::~p2pSteppingAction() {

}

void p2pSteppingAction::UserSteppingAction(const G4Step* step){

	G4double edep = step->GetTotalEnergyDeposit();
	EventAction->AddEdep(edep);
}
