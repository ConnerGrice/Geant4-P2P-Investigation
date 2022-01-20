#include "p2pDetectorConstruction.h"

#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4ThreeVector.hh>
#include <G4Tubs.hh>
#include <G4RotationMatrix.hh>

p2pDetectorConstruction::p2pDetectorConstruction() {

}

p2pDetectorConstruction::~p2pDetectorConstruction() {

}

G4VPhysicalVolume* p2pDetectorConstruction::Construct() {

	//Allows for the use of Nist Material list
	G4NistManager* nist = G4NistManager::Instance();

	//Defines some materials
	G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");
	G4Material* detectorMat = nist->FindOrBuildMaterial("G4_Si");

	G4bool checkOverlaps = true;

	//WOrld
	G4double worldx = 100*cm;
	G4double worldy = 100*cm;
	G4double worldz = 100*cm;

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

	//inner detector
	G4int numSeg = 4;
	G4int numRow = 4;
	G4double len = 50*cm;

	G4double innMin = 19*cm;
	G4double innMax = 20*cm;
	G4double innHHight = (len/(2*numRow))*cm;
	G4double innStart = 0;
	G4double innEnd = (2*M_PI)/numSeg;
	G4ThreeVector trans;

	G4Tubs* solidInn = new G4Tubs("Inner",innMin,innMax,innHHight,innStart,innEnd);
	G4LogicalVolume* logicInn = new G4LogicalVolume(solidInn,detectorMat,"Inner");

	for(G4int j=0;j<numRow;j++){
		for(G4int i=0;i<numSeg;i++){
			G4RotationMatrix* rot = new G4RotationMatrix();
			rot->rotateZ(i*innEnd);
			trans = G4ThreeVector(0,0,j*(len/numRow)-len);

			new G4PVPlacement(
							rot,
							trans,
							logicInn,
							"Inner",
							logicWorld,
							false,
							i*j,
							checkOverlaps);
		}
	}











	return physicalWorld;
}

