#include "p2pActionInitialization.h"
#include "p2pPrimaryGeneratorAction.h"
#include "p2pRunAction.h"

p2pActionInitialization::p2pActionInitialization() : G4VUserActionInitialization() {

}

p2pActionInitialization::~p2pActionInitialization() {
}

void p2pActionInitialization::Build() const{
	SetUserAction(new p2pPrimaryGeneratorAction);
	SetUserAction(new p2pRunAction);
}

