#ifndef CLASSES_P2PPRIMARYGENERATORMESSENGER_H_
#define CLASSES_P2PPRIMARYGENERATORMESSENGER_H_

#include <G4UImessenger.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIdirectory.hh>
#include <globals.hh>

class p2pPrimaryGeneratorAction;

class p2pPrimaryGeneratorMessenger: public G4UImessenger {
public:
	p2pPrimaryGeneratorMessenger(p2pPrimaryGeneratorAction*);
	virtual ~p2pPrimaryGeneratorMessenger();
	void SetNewValue(G4UIcommand*,G4String);
private:
	p2pPrimaryGeneratorAction* Action;
	G4UIdirectory* fDir;
	G4UIcmdWithAString* fMessenger;

};

#endif /* CLASSES_P2PPRIMARYGENERATORMESSENGER_H_ */
