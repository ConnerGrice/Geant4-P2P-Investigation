#include "p2pSensitiveDetector.h"

p2pSensitiveDetector::p2pSensitiveDetector(G4String name,G4String collection) : G4VSensitiveDetector(name),
fHitsCollection(0){

	collectionName.insert(collection);
}

p2pSensitiveDetector::~p2pSensitiveDetector() {
}

void p2pSensitiveDetector::Initialize(G4HCofThisEvent* hce){

	//G4cout<<"Detector "<<SensitiveDetectorName<<" initialised"<<G4endl;

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

	G4int numSeg = SEGMENTS;				//Number of segments
	G4double thick = THICKNESS;		//Thickness of tubes (0.5mm)
	G4double innMin = INNERRAD;			//Inner inner radius
	G4double gap = GAP;			//Gap between detectors

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

	//Gets event number
	G4int event = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	//Records the coordinates of the detector segment hit
	if (trackID == 1 || trackID == 2){
		//G4cout<<"Event: "<<event<<", Detector: "<<copyNo<<", Particle: "<<trackID<<G4endl;
		p2pHit* newHit = new p2pHit();

		newHit->SetCopy(copyNo);
		newHit->SetTrack(trackID);
		newHit->SetPos(detPos);
		newHit->SetEvent(event);
		newHit->Hit(trackID);

		fHitsCollection->insert(newHit);
	}
	return true;
}

void p2pSensitiveDetector::EndOfEvent(G4HCofThisEvent*){

	//Number of hits in this event
	G4int nHits = fHitsCollection->entries();

	//Event number
	G4int event = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	//Detector copy number
	G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);

	G4cout<<"Detector: "<<SensitiveDetectorName<<G4endl;
	G4cout<<"Event: "<<event<<G4endl;

	//Hit counter for each particle
	std::vector<G4int> tot = {0,0};

	//Empty hit container
	p2pHit* hit = new p2pHit();

	//Counting number of times each particle hit detector
	for (G4int i=0;i<nHits;i++){
		hit = (*fHitsCollection)[i];
		tot[0] += hit->Getp1(); //Particle 1
		tot[1] += hit->Getp2();	//Particle 2
	}

	G4cout<<"particle 1: "<<tot[0]<<", Particle 2: "<<tot[1]<<G4endl;

	//Empty hit containers for when particles miss detector
	p2pHit* missHit1 = new p2pHit();
	missHit1->SetEvent(event);
	missHit1->SetCopy(hcID);
	p2pHit* missHit2 = new p2pHit();
	missHit2->SetEvent(event);
	missHit2->SetCopy(hcID);
	std::vector<p2pHit*> missHit = {missHit1,missHit2};

	//Checks if either particle missed any of the detectors
	for (G4int i=0;i<2;i++){
		if (tot[i] == 0){
			//Adds missed hit container
			fHitsCollection->insert(missHit[i]);
		}
	}

	//Tracker for recording data
	G4int nump1 = 0;
	G4int nump2 = 0;

	//Particle ID
	G4int particle;

	//Number of recorded hits per event
	G4int recorded = 0;

	//UPdates number of hits after adding missed hit containers
	nHits = fHitsCollection->entries();

	//For recording data
	G4AnalysisManager* manager = G4AnalysisManager::Instance();

	//Loops through each hit in collections
	for (G4int i=0;i<nHits;i++){

		//Getting hit data individual hit
		hit = (*fHitsCollection)[i];
		particle = hit->GetTrack();
		G4ThreeVector detPos = hit->GetPos();
		G4int copyNo = hit->GetCopy();

		/*
		 * Only records the data for each particle for their initial
		 * hit to the detector (In case the particle hits the detector
		 * multiple times)
		 */

		//Checks if particle 1
		if (particle == 1){
			//Checks if particle 1 hit has already been recorded
			if (nump1 == 0){
				G4cout<<"RECORDED P1"<<G4endl;
				recorded += 1;

				//copyNo = 0 (Inner), copyNo = 1 (Outer)
				manager->FillNtupleIColumn(copyNo,0,particle);
				manager->FillNtupleDColumn(copyNo,1,detPos[0]);
				manager->FillNtupleDColumn(copyNo,2,detPos[1]);
				manager->FillNtupleDColumn(copyNo,3,detPos[2]);
				manager->FillNtupleIColumn(copyNo,4,event);
				manager->AddNtupleRow(copyNo);
			}
			nump1 += 1;
		}
		//Checks if particle 2
		if (particle == 2){
			//Checks if particle 2 has already been recorded
			if (nump2 == 0){
				G4cout<<"RECORDED P2"<<G4endl;
				recorded += 1;

				//copyNo = 0 (Inner), copyNo = 1 (Outer)
				manager->FillNtupleIColumn(copyNo,0,particle);
				manager->FillNtupleDColumn(copyNo,1,detPos[0]);
				manager->FillNtupleDColumn(copyNo,2,detPos[1]);
				manager->FillNtupleDColumn(copyNo,3,detPos[2]);
				manager->FillNtupleIColumn(copyNo,4,event);
				manager->AddNtupleRow(copyNo);
			}
			nump2 += 1;
		}
		//Checks if the particle is a missed hit
		if (particle == -1){
			G4cout<<"RECORDED MISS"<<G4endl;
			recorded += 1;

			//copyNo = 0 (Inner), copyNo = 1 (Outer)
			manager->FillNtupleIColumn(copyNo,0,particle);
			manager->FillNtupleDColumn(copyNo,1,detPos[0]);
			manager->FillNtupleDColumn(copyNo,2,detPos[1]);
			manager->FillNtupleDColumn(copyNo,3,detPos[2]);
			manager->FillNtupleIColumn(copyNo,4,event);
			manager->AddNtupleRow(copyNo);
		}
	}
	G4cout<<"RECORDED: "<<recorded<<G4endl;


}
