#include "p2pActionInitialization.h"

p2pActionInitialization::p2pActionInitialization() : G4VUserActionInitialization() {

}

p2pActionInitialization::~p2pActionInitialization() {
}

void p2pActionInitialization::Build() const{
	SetUserAction(new p2pPrimaryGeneratorAction);

	p2pRunAction* run = new p2pRunAction();
	SetUserAction(run);

	p2pEventAction* event = new p2pEventAction(run);
	SetUserAction(event);

	p2pSteppingAction* step = new p2pSteppingAction(event);
	SetUserAction(step);
}

void p2pActionInitialization::BuildForMaster() const{

	SetUserAction(new p2pRunAction());
}

