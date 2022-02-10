#ifndef CLASSES_P2PPRIMARYGENERATORMESSENGER_H_
#define CLASSES_P2PPRIMARYGENERATORMESSENGER_H_

#include <G4UImessenger.hh>
#include <G4UIcmdWithAString.hh>

#include "p2pPrimaryGeneratorAction.h"

class p2pPrimaryGeneratorMessenger: public G4UImessenger {
public:
	p2pPrimaryGeneratorMessenger(p2pPrimaryGeneratorAction* gun);
	virtual ~p2pPrimaryGeneratorMessenger();

	void SetNewParam();

private:
	p2pPrimaryGeneratorAction* generator;
	G4UIdirectory* dir;
	G4UIcmdWithAString* fActioncmd;



};

#endif /* CLASSES_P2PPRIMARYGENERATORMESSANGER_H_ */
