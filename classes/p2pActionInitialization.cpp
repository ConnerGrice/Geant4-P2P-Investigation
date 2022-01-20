/*
 * p2pActionInitialization.cpp
 *
 *  Created on: Jan 20, 2022
 *      Author: local1
 */

#include "p2pActionInitialization.h"
#include "p2pPrimaryGeneratorAction.h"

p2pActionInitialization::p2pActionInitialization() : G4VUserActionInitialization() {
	// TODO Auto-generated constructor stub

}

p2pActionInitialization::~p2pActionInitialization() {
	// TODO Auto-generated destructor stub
}

void p2pActionInitialization::Build() const{
	SetUserAction(new p2pPrimaryGeneratorAction);
}

