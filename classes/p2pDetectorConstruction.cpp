#include "p2pDetectorConstruction.h"

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

	//Detector surfaces
	G4int numSeg = 25;				//Number of segments
	G4int numRow = 15;				//Number of rows
	G4double len = 30*cm;			//Total length of tubes
	G4double segLen = len/numRow;	//Length of each segment
	G4double gap = 3*cm;			//Space between tubes
	G4double thick = 0.5*mm;		//Thickness of tubes

	G4double innMin = 5*cm;				//Inner radius of segment
	G4double innMax = innMin + thick;	//Outer radius of segment
	G4double innHHight = segLen/2;		//half the length of cylinder segment
	G4double innStart = 0;				//segment starting angle
	G4double innEnd = (2*M_PI)/numSeg;	//segment ending angle

	//Inner cylinder
	G4Tubs* solidInn = new G4Tubs("Inner",innMin,innMax,innHHight,innStart,innEnd);
	logicInn = new G4LogicalVolume(solidInn,detectorMat,"Inner");

	//Outer cylinder dimensions
	G4double outMin = innMin + gap;
	G4double outMax = outMin + thick;

	//Outer cylinder
	G4Tubs* solidOut = new G4Tubs("Outer",outMin,outMax,innHHight,innStart,innEnd);
	logicOut = new G4LogicalVolume(solidOut,detectorMat,"Outer");


	G4ThreeVector trans;	//Segment translation
	G4RotationMatrix* rot;	//Segment rotation

	//Loop to generate tube of cylinders in the z axis
	for(G4int j=0;j<numRow;j++){
		//Loop to generate full cylinder
		for(G4int i=0;i<numSeg;i++){

			rot = new G4RotationMatrix();

			//Moving the segment
			rot->rotateZ(i*innEnd);
			trans = G4ThreeVector(0,0,segLen*(1-numRow)/2+2*j*innHHight);

			new G4PVPlacement(rot,trans,logicInn,"Inner",logicWorld,false,0,checkOverlaps);
			new G4PVPlacement(rot,trans,logicOut,"Outer",logicWorld,false,1,checkOverlaps);
		}
	}

	return physicalWorld;
}

void p2pDetectorConstruction::ConstructSDandField(){
	logicInn->SetSensitiveDetector(new p2pSensitiveDetector("InnerSens"));
	logicOut->SetSensitiveDetector(new p2pSensitiveDetector("OuterSens"));
}

