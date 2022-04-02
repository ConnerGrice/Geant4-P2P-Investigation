#ifndef CLASSES_P2PDETECTORCONSTRUCTION_H_
#define CLASSES_P2PDETECTORCONSTRUCTION_H_

#include <G4VUserDetectorConstruction.hh>
#include <G4VPhysicalVolume.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4Box.hh>
#include <G4Sphere.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4ThreeVector.hh>
#include <G4Tubs.hh>
#include <G4RotationMatrix.hh>
#include <G4PVReplica.hh>
#include <G4SDManager.hh>
#include <G4GenericMessenger.hh>

#include "p2pSensitiveDetector.h"

class p2pDetectorConstruction: public G4VUserDetectorConstruction {
public:
	p2pDetectorConstruction();
	virtual ~p2pDetectorConstruction();
	virtual G4VPhysicalVolume* Construct();
	G4LogicalVolume* GetScoringVolume() const {return fScoringVolume;};
private:
	virtual void ConstructSDandField();
	void DefineMaterial();

	G4LogicalVolume* fScoringVolume;
	G4Box* solidWorld;
	G4Sphere* solidCal;
	G4Tubs* solidEmi,*solidInn,*solidOut;
	G4LogicalVolume *logicWorld,*logicCal,*logicEmi,*logicInn,*logicOut;
	G4VPhysicalVolume* physicalWorld,*physicalCal,*physicalEmi,*physicalInn,*physicalOut;
	G4Material *worldMat,*detectorMat,*emissionMat;

	G4GenericMessenger* fMessenger;

};

#endif /* CLASSES_P2PDETECTORCONSTRUCTION_H_ */
