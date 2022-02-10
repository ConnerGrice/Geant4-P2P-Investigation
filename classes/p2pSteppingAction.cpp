#include "p2pSteppingAction.h"

p2pSteppingAction::p2pSteppingAction(p2pEventAction* eventAction) {
	EventAction = eventAction;
}

p2pSteppingAction::~p2pSteppingAction() {

}

void p2pSteppingAction::UserSteppingAction(const G4Step* step){
	//Gets track ID
	G4int trackID = step->GetTrack()->GetTrackID();

	//Gets the logical volume that was hit
	G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

	//Gets the whole constructor object
	const p2pDetectorConstruction* construction = static_cast<const p2pDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

	//Gets the scoring volume (calorimeter)
	G4LogicalVolume* fScoringVolume = construction->GetScoringVolume();

	//Only gets the energy deposited into the scoring volume
	if (volume != fScoringVolume) {return;}
	G4double edep = step->GetTotalEnergyDeposit();

	//Checks which particle the energy is associated with
	switch(trackID){
	case 1:
		EventAction->AddEdep1(edep);
		break;
	case 2:
		EventAction->AddEdep2(edep);
		break;
	default:
		break;
	}
}
