#include "p2pSensitiveDetector.h"

p2pSensitiveDetector::p2pSensitiveDetector(G4String name) : G4VSensitiveDetector(name) {
}

p2pSensitiveDetector::~p2pSensitiveDetector() {
}

G4bool p2pSensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*){
	G4Track* track = aStep->GetTrack();
	//track->SetTrackStatus(fStopAndKill);

	G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
	G4ThreeVector prePos = preStepPoint->GetPosition();


	const G4VTouchable* touchable = preStepPoint->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber();
/*
	G4VPhysicalVolume* physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	G4RotationMatrix* rotDetector = physVol->GetRotation();
	G4double thetaX = rotDetector->getDelta();	//180 clockwise and 180 anticlockwise

	G4int numSeg = 20;
	G4double theta;

	theta = thetaX+(M_PI/numSeg);



	//positions in mm
	G4cout<<"Index: "<<copyNo<<G4endl;
	G4cout<<"Detector Position: "<<posDetector<<G4endl;
	G4cout<<"delta: "<<thetaX<<G4endl;

	G4cout<<"theta:  "<<theta<<G4endl;

*/
	G4cout<<"Particle Position: "<<prePos<<" "<<copyNo<<G4endl;

	G4int event = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	G4AnalysisManager* manager = G4AnalysisManager::Instance();

	manager->FillNtupleIColumn(copyNo,0,event);
	manager->FillNtupleDColumn(copyNo,1,prePos[0]);
	manager->FillNtupleDColumn(copyNo,2,prePos[1]);
	manager->FillNtupleDColumn(copyNo,3,prePos[2]);

	manager->AddNtupleRow(copyNo);


	return true;
}

