#include "p2pDetectorConstruction.h"
#include "p2pSensitiveDetector.h"

#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4ThreeVector.hh>
#include <G4Tubs.hh>
#include <G4RotationMatrix.hh>

p2pDetectorConstruction::p2pDetectorConstruction() : G4VUserDetectorConstruction(),
logicInn(0),logicOut(0){

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
	G4double worldx = 200*cm;
	G4double worldy = 200*cm;
	G4double worldz = 200*cm;

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

	//Detector surfaces
	G4int numSeg = 20;				//Number of segments
	G4int numRow = 6;				//Number of rows
	G4double len = 300*cm;			//Total length of tubes
	G4double segLen = len/numRow;	//Length of each segment
	G4double gap = 10*cm;			//Space between tubes
	G4double thick = 1*cm;			//Thickness of tubes

	G4double innMin = 19*cm;
	G4double innMax = innMin + thick;
	G4double innHHight = segLen/2;
	G4double innStart = 0;
	G4double innEnd = (2*M_PI)/numSeg;

	G4Tubs* solidInn = new G4Tubs("Inner",innMin,innMax,innHHight,innStart,innEnd);
	logicInn = new G4LogicalVolume(solidInn,detectorMat,"Inner");

	G4double outMin = innMin + gap;
	G4double outMax = outMin + thick;

	G4Tubs* solidOut = new G4Tubs("Outer",outMin,outMax,innHHight,innStart,innEnd);
	logicOut = new G4LogicalVolume(solidOut,detectorMat,"Outer");

	G4ThreeVector trans;

	for(G4int j=0;j<numRow;j++){
		for(G4int i=0;i<numSeg;i++){

			G4RotationMatrix* rot = new G4RotationMatrix();

			rot->rotateZ(i*innEnd);
			trans = G4ThreeVector(0,0,segLen*(1-numRow)/2+2*j*innHHight);

			new G4PVPlacement(rot,trans,logicInn,"Inner",logicWorld,false,i+numSeg*j,checkOverlaps);
			new G4PVPlacement(rot,trans,logicOut,"Outer",logicWorld,false,10*i+numSeg*j,checkOverlaps);
		}
	}

	return physicalWorld;
}

void p2pDetectorConstruction::ConstructSDandField(){
	p2pSensitiveDetector* innDet = new p2pSensitiveDetector("InnerSens");
	p2pSensitiveDetector* outDet = new p2pSensitiveDetector("InnerSens");
	logicInn->SetSensitiveDetector(innDet);
	logicOut->SetSensitiveDetector(outDet);
}

