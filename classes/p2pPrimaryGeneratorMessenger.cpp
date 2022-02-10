#include "p2pPrimaryGeneratorMessenger.h"
#include "p2pPrimaryGeneratorAction.h"

p2pPrimaryGeneratorMessenger::p2pPrimaryGeneratorMessenger(p2pPrimaryGeneratorAction* gun):generator(gun){

	dir = new G4UIdirectory("/gunControl/");

	fActioncmd = new G4UIcmdWithAString("/gunControl/readData",this);
	fActioncmd->SetGuidance("Generates particles from root file");
}

p2pPrimaryGeneratorMessenger::~p2pPrimaryGeneratorMessenger() {
	delete fActioncmd;
	delete dir;
}

void p2pPrimaryGeneratorMessenger::SetNewParam(){

	generator->SetGun(fActioncmd->GetCurrentValue());
}
