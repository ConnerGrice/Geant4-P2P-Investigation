#include "p2pSensitiveDetector.h"

p2pSensitiveDetector::p2pSensitiveDetector(G4String name) : G4VSensitiveDetector(name) {
}

p2pSensitiveDetector::~p2pSensitiveDetector() {
}

G4bool p2pSensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*){

	//Track related variables
	G4Track* track = aStep->GetTrack();
	G4int trackID = track->GetTrackID();

	//Gets position of particles hitting detector
	G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
	G4ThreeVector prePos = preStepPoint->GetPosition();


	//Gets the copy number of hit detector
	const G4VTouchable* touchable = preStepPoint->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber();


	//Gets translation and rotation of detector segment that was hit
	G4VPhysicalVolume* physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	G4RotationMatrix* rotDetector = physVol->GetRotation();

	//Gets actual angle of segment from horizontal
	G4double theta = (rotDetector->getPsi())*2;

	G4int numSeg = 31;				//Number of segments
	G4double thick = 0.5*mm;		//Thickness of tubes (0.5mm)
	G4double innMin = 5*cm;			//Inner inner radius
	G4double gap = 3*cm;			//Gap between detectors

	G4double outMin = innMin + gap;		//Outer inner radius
	G4double innRad = innMin+(thick/2);	//Inner central radius
	G4double outRad = outMin+(thick/2);	//Outer central radius

	G4ThreeVector detPos;	//Calculated detector position

	G4double delta = theta + (M_PI/(numSeg));	//Angle about z axis

	//Decides which radius to use when calculating coordinates
	switch(copyNo) {
	case 0:
		detPos = G4ThreeVector(innRad*std::cos(delta),innRad*std::sin(delta),posDetector.getZ());
		break;
	case 1:
		detPos = G4ThreeVector(outRad*std::cos(delta),outRad*std::sin(delta),posDetector.getZ());
		break;
	default:
		break;
	}

	//MAY BE USEFUL FOR DEBUGGING
	/*
	//Gets event number
	G4int event = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	G4ThreeVector mom = preStepPoint->GetMomentum();
	G4double momMag = mom.mag();

	G4ThreeVector detDir = detPos.unit();
	G4ThreeVector momCal = momMag*detDir;


	//positions in mm
	G4cout<<"Hit: 		"<<copyNo<<G4endl;
	G4cout<<"Psi: 		"<<delta<<G4endl;
	G4cout<<"Exact: 	"<<prePos<<G4endl;
	G4cout<<"Calculated:"<<detPos<<G4endl;

	G4cout<<"Track: "<<trackID <<G4endl;
	G4cout<<"Momentum: "<<momMag<<G4endl;
	G4cout<<"Direction: "<<detDir<<G4endl;
	G4cout<<"Mom Dir: "<<momCal<<G4endl;
	G4cout<<"Mom Exa: "<<mom<<G4endl;

	*/

	//Records the coordinates of the datactor segment hit
	G4AnalysisManager* manager = G4AnalysisManager::Instance();

	//copyNo = 0 (Inner), copyNo = 1 (Outer)
	manager->FillNtupleIColumn(copyNo,0,trackID);
	manager->FillNtupleDColumn(copyNo,1,detPos[0]);
	manager->FillNtupleDColumn(copyNo,2,detPos[1]);
	manager->FillNtupleDColumn(copyNo,3,detPos[2]);
	manager->AddNtupleRow(copyNo);
	return true;
}

