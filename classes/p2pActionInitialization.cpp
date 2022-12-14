#include "p2pActionInitialization.h"

p2pActionInitialization::p2pActionInitialization() : G4VUserActionInitialization() {

}

p2pActionInitialization::~p2pActionInitialization() {
}

//These methods tell the program which native classes should be overridden with my user made classes
void p2pActionInitialization::Build() const{
	SetUserAction(new p2pPrimaryGeneratorAction);

	p2pRunAction* run = new p2pRunAction();
	SetUserAction(run);

	p2pEventAction* event = new p2pEventAction(run);
	SetUserAction(event);

	p2pSteppingAction* step = new p2pSteppingAction(event);
	SetUserAction(step);
}

//This is for multithreading mode
void p2pActionInitialization::BuildForMaster() const{

	SetUserAction(new p2pRunAction());
}

