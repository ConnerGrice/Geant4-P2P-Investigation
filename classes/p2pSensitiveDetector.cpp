#include "p2pSensitiveDetector.h"

#include <g4root.hh>
#include <G4RunManager.hh>
#include <G4SystemOfUnits.hh>
p2pSensitiveDetector::p2pSensitiveDetector(G4String name) : G4VSensitiveDetector(name) {
}

p2pSensitiveDetector::~p2pSensitiveDetector() {
}

G4bool p2pSensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*){
	G4Track* track = aStep->GetTrack();
	//track->SetTrackStatus(fStopAndKill);

	G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
	G4ThreeVector prePos = preStepPoint->GetPosition();

	G4StepPoint* postStepPoint = aStep->GetPostStepPoint();
	G4ThreeVector postPos = postStepPoint->GetPosition();

	const G4VTouchable* touchable = preStepPoint->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber();

	G4VPhysicalVolume* physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	G4RotationMatrix* rotDetector = physVol->GetRotation();
	G4double thetaX = rotDetector->getDelta();	//180 clockwise and 180 anticlockwise

	G4int numSeg = 20;
	G4double theta;
	G4double sum;

	theta = thetaX+(M_PI/numSeg);

	//positions in mm
	G4cout<<"Index: "<<copyNo<<G4endl;
	G4cout<<"Detector Position: "<<posDetector<<G4endl;
	G4cout<<"delta: "<<thetaX<<G4endl;

	G4cout<<"theta:  "<<theta<<G4endl;
	G4cout<<"Particle Position: "<<prePos<<G4endl;

	return true;
}

