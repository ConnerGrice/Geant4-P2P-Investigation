#ifndef CLASSES_P2PSENSITIVEDETECTOR_H_
#define CLASSES_P2PSENSITIVEDETECTOR_H_

#include <G4VSensitiveDetector.hh>

#include <g4root.hh>
#include <G4RunManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4Step.hh>
#include <G4HCofThisEvent.hh>
#include <G4SDManager.hh>
#include <G4THitsCollection.hh>

#include "p2pHit.h"

class p2pSensitiveDetector: public G4VSensitiveDetector {
public:
	p2pSensitiveDetector(G4String);
	virtual ~p2pSensitiveDetector();

	virtual void Initialize(G4HCofThisEvent*);
	virtual G4bool ProcessHits(G4Step*,G4TouchableHistory*);
	virtual void EndOfEvent(G4HCofThisEvent*);

private:
	p2pHitsCollection* fHitsCollection = new p2pHitsCollection();

};

#endif /* CLASSES_P2PSENSITIVEDETECTOR_H_ */
