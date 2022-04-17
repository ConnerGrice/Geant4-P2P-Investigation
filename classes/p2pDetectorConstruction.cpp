#include "p2pDetectorConstruction.h"

p2pDetectorConstruction::p2pDetectorConstruction() : G4VUserDetectorConstruction(),
fScoringVolume(0){

	DefineMaterial();

}

p2pDetectorConstruction::~p2pDetectorConstruction() {

}

void p2pDetectorConstruction::DefineMaterial(){
	//Allows for the use of Nist Material list
		G4NistManager* nist = G4NistManager::Instance();

		//Defines some materials
		worldMat = nist->FindOrBuildMaterial("G4_Galactic");
		detectorMat = nist->FindOrBuildMaterial("G4_Si");
		emissionMat = nist->FindOrBuildMaterial("G4_lH2");

}

G4VPhysicalVolume* p2pDetectorConstruction::Construct() {

	G4bool checkOverlaps = true;

	//World
	G4double worldx = 100*cm;
	G4double worldy = 100*cm;
	G4double worldz = 100*cm;

	solidWorld = new G4Box("World",worldx,worldy,worldz);
	logicWorld = new G4LogicalVolume(solidWorld,worldMat,"World");
	physicalWorld = new G4PVPlacement(0,G4ThreeVector(0,0,0),logicWorld,"World",0,false,0,checkOverlaps);

	//Spherical calorimeter
	G4double calMin = 20*cm;
	G4double calThick = 80*cm;
	G4double calMax = calMin+calThick;

	solidCal= new G4Sphere("Calorimeter",calMin,calMax,0,2*M_PI,0,M_PI);
	logicCal = new G4LogicalVolume(solidCal,detectorMat,"Calorimeter");
	physicalCal = new G4PVPlacement(0,G4ThreeVector(0,0,0),logicCal,"Calorimeter",logicWorld,false,3,checkOverlaps);

	fScoringVolume = logicCal;

	//Emission Surface
	G4double emiDiameter = 3*cm;
	G4double emiLength = 3*cm;

	solidEmi = new G4Tubs("Emission",0,emiDiameter,emiLength,0,2*M_PI);
	logicEmi = new G4LogicalVolume(solidEmi,emissionMat,"Emission");
	physicalEmi = new G4PVPlacement(0,G4ThreeVector(0,0,0),logicEmi,"Emission",logicWorld,false,4,checkOverlaps);



	//Detector surfaces (CHANGE IN SENSITIVE DETECTOR ASWELL!)
	G4int numSeg = 100;				//Number of segments
	G4int numRow = 100;				//Number of rows
	G4double len = 36*cm;
	G4double segLen = len/numRow;	//Length of each segment
	G4double gap = 3*cm;			//Space between tubes (3cm)
	G4double thick = 1.00*mm;

	G4double innMin = 5*cm;				//Inner radius of segment (5cm)
	G4double innMax = innMin + thick;	//Outer radius of segment
	G4double innHHight = segLen/2;		//half the length of cylinder segment
	G4double innStart = 0;				//segment starting angle
	G4double innEnd = (2*M_PI)/numSeg;	//segment ending angle

	//Inner cylinder
	solidInn = new G4Tubs("Inner",innMin,innMax,innHHight,innStart,innEnd);
	logicInn = new G4LogicalVolume(solidInn,detectorMat,"Inner");

	//Outer cylinder dimensions
	G4double outMin = innMin + gap;
	G4double outMax = outMin + thick;

	//Outer cylinder
	solidOut = new G4Tubs("Outer",outMin,outMax,innHHight,innStart,innEnd);
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

			physicalInn = new G4PVPlacement(rot,trans,logicInn,"Inner",logicWorld,false,0,checkOverlaps);
			physicalOut = new G4PVPlacement(rot,trans,logicOut,"Outer",logicWorld,false,1,checkOverlaps);
		}
	}
	return physicalWorld;
}

void p2pDetectorConstruction::ConstructSDandField(){
	//Defining which parts of the geometry will become the sensitive detectors

	//HOW I ORIGINALLY SET THE SENSITIVE DETECTORS
	//logicInn->SetSensitiveDetector(new p2pSensitiveDetector("InnerSens","InnerCollection"));
	//logicOut->SetSensitiveDetector(new p2pSensitiveDetector("OuterSens","OuterCollection"));

	//NEW WAY, USING SENSITIVE DETECTOR MANAGER
	auto innSD = new p2pSensitiveDetector("InnerSens","InnerCollection");
	G4SDManager::GetSDMpointer()->AddNewDetector(innSD);
	SetSensitiveDetector("Inner",innSD);

	auto outSD = new p2pSensitiveDetector("OuterSens","OuterCollection");
	G4SDManager::GetSDMpointer()->AddNewDetector(outSD);
	SetSensitiveDetector("Outer",outSD);


}

