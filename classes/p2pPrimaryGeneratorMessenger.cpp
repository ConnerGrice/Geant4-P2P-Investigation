#include "p2pPrimaryGeneratorMessenger.h"

#include "p2pPrimaryGeneratorAction.h"

p2pPrimaryGeneratorMessenger::p2pPrimaryGeneratorMessenger(p2pPrimaryGeneratorAction* gun): Action(gun) {

	fDir = new G4UIdirectory("/gunControl/");		//Directory for command
	fDir->SetGuidance("Gun control from ROOT file");//Description of command directory

	fMessenger = new G4UIcmdWithAString("/gunControl/read",this);	//Defining command keyword
	fMessenger->SetGuidance("ROOT file input to be read");	//Description of command
	fMessenger->SetParameterName("File", true,true);	//Name of parameter
	fMessenger->SetDefaultValue("quasi.root");	//Default parameter


}

p2pPrimaryGeneratorMessenger::~p2pPrimaryGeneratorMessenger() {
	delete fDir;
	delete fMessenger;
}

void p2pPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* cmd, G4String file){
	//Runs SetGunParam method in generator action
	if(cmd == fMessenger){Action->SetGunParam1(file);}
}
