#ifndef CLASSES_P2PDETECTORCONSTRUCTION_H_
#define CLASSES_P2PDETECTORCONSTRUCTION_H_

#include <G4VUserDetectorConstruction.hh>
#include <G4VPhysicalVolume.hh>

class p2pDetectorConstruction: public G4VUserDetectorConstruction {
public:
	p2pDetectorConstruction();
	virtual ~p2pDetectorConstruction();
	virtual G4VPhysicalVolume* Construct();
};

#endif /* CLASSES_P2PDETECTORCONSTRUCTION_H_ */
