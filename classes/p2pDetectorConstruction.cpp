#include "p2pDetectorConstruction.h"

#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4ThreeVector.hh>

p2pDetectorConstruction::p2pDetectorConstruction() {

}

p2pDetectorConstruction::~p2pDetectorConstruction() {

}

G4VPhysicalVolume* p2pDetectorConstruction::Construct() {

	//Allows for the use of Nist Material list
	G4NistManager* nist = G4NistManager::Instance();

	//Defines some materials
	G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");
	G4Material* detectorMat = nist->FindOrBuildMaterial("G4_Ag");

	G4bool checkOverlaps = true;

	//WOrld
	G4double worldx = 50*cm;
	G4double worldy = 50*cm;
	G4double worldz = 50*cm;

	G4Box* solidWorld = new G4Box("World",worldx,worldy,worldz);
	G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,worldMat,"World");
	G4VPhysicalVolume* physicalWorld = new G4PVPlacement(0,
														G4ThreeVector(0,0,0),
														logicWorld,
														"World",
														0,
														false,
														0,
														checkOverlaps);

	//Stand in object
	G4double objx = 10*cm;
	G4double objy = 20*cm;
	G4double objz = 30*cm;

	G4RotationMatrix* rot = new G4RotationMatrix();
	rot->rotateX(45*deg);

	G4Box* solidObj = new G4Box("Object",objx,objy,objz);
	G4LogicalVolume* logicObj = new G4LogicalVolume(solidObj,detectorMat,"Object");
	G4VPhysicalVolume* physicalObj = new G4PVPlacement(rot,
											G4ThreeVector(0,10*cm,0),
											logicObj,
											"Object",
											logicWorld,
											false,
											1,
											checkOverlaps);
	return physicalWorld;
}

