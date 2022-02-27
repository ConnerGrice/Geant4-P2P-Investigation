#include "p2pSensitiveDetector.h"

p2pSensitiveDetector::p2pSensitiveDetector(G4String name,G4String collection) : G4VSensitiveDetector(name),
fHitsCollection(0){

	collectionName.insert(collection);
}

p2pSensitiveDetector::~p2pSensitiveDetector() {
}

void p2pSensitiveDetector::Initialize(G4HCofThisEvent* hce){

	G4cout<<"Detector "<<SensitiveDetectorName<<" initialised"<<G4endl;

	fHitsCollection = new p2pHitsCollection(SensitiveDetectorName,collectionName[0]);

	G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
	hce->AddHitsCollection(hcID,fHitsCollection);

}

G4bool p2pSensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory*){


	//Gets position of particles hitting detector
	G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
	G4ThreeVector prePos = preStepPoint->GetPosition();

	//Gets the copy number of hit detector
	const G4VTouchable* touchable = preStepPoint->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber();

	//Track related variables
	G4Track* track = aStep->GetTrack();
	G4int trackID = track->GetTrackID();



	//Gets translation and rotation of detector segment that was hit
	G4VPhysicalVolume* physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	G4RotationMatrix* rotDetector = physVol->GetRotation();

	//Gets actual angle of segment from horizontal
	G4double theta = (rotDetector->getPsi())*2;

	G4int numSeg = 100;				//Number of segments
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
	//Gets event number
	G4int event = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	//Records the coordinates of the detector segment hit
	G4AnalysisManager* manager = G4AnalysisManager::Instance();
	if (trackID == 1 || trackID == 2){
		G4cout<<"Event: "<<event<<", Detector: "<<copyNo<<", Particle: "<<trackID<<G4endl;
		p2pHit* newHit = new p2pHit();

		newHit->SetCopy(copyNo);
		newHit->SetTrack(trackID);
		newHit->SetPos(detPos);
		newHit->SetEvent(event);
		newHit->Hit(trackID);

		//newHit->Print();
		fHitsCollection->insert(newHit);


		//copyNo = 0 (Inner), copyNo = 1 (Outer)
		manager->FillNtupleIColumn(copyNo,0,trackID);
		manager->FillNtupleDColumn(copyNo,1,detPos[0]);
		manager->FillNtupleDColumn(copyNo,2,detPos[1]);
		manager->FillNtupleDColumn(copyNo,3,detPos[2]);
		manager->FillNtupleIColumn(copyNo,4,event);
		manager->AddNtupleRow(copyNo);
	}
	return true;
}

void p2pSensitiveDetector::EndOfEvent(G4HCofThisEvent*){

	G4int nHits = fHitsCollection->entries();
	p2pHit* hit = new p2pHit();
	G4int p1Tot = 0;
	G4int p2Tot = 0;

	for (G4int i=0;i<nHits;i++){
		hit = (*fHitsCollection)[i];
		p1Tot += hit->Getp1();
		p2Tot += hit->Getp2();
		G4cout<<"HIT COLLECTION"<<G4endl;
		G4cout<<"Event: "<<hit->GetEvent()<<", Detector: "<<hit->GetCopy()<<", Particle: "<<hit->GetTrack()<<G4endl;
	}
	G4cout<<"Detector: "<<SensitiveDetectorName<<G4endl;
	G4cout<<"particle 1: "<<p1Tot<<", Particle 2: "<<p2Tot<<G4endl;
}
