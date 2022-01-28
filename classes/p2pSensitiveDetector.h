#ifndef CLASSES_P2PSENSITIVEDETECTOR_H_
#define CLASSES_P2PSENSITIVEDETECTOR_H_

#include <G4VSensitiveDetector.hh>

#include <g4root.hh>
#include <G4RunManager.hh>
#include <G4SystemOfUnits.hh>

class p2pSensitiveDetector: public G4VSensitiveDetector {
public:
	p2pSensitiveDetector(G4String);
	virtual ~p2pSensitiveDetector();
private:
	virtual G4bool ProcessHits(G4Step*,G4TouchableHistory*);
};

#endif /* CLASSES_P2PSENSITIVEDETECTOR_H_ */
