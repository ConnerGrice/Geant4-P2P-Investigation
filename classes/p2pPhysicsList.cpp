/*
 * p2pPhysicsList.cpp
 *
 *  Created on: Jan 20, 2022
 *      Author: local1
 */

#include "p2pPhysicsList.h"

#include <G4LeptonConstructor.hh>
#include <G4MesonConstructor.hh>
#include <G4BaryonConstructor.hh>
#include <G4BosonConstructor.hh>
#include <G4ShortLivedConstructor.hh>
#include <G4IonConstructor.hh>
#include <G4VPhysicsConstructor.hh>
#include <G4EmStandardPhysics.hh>

p2pPhysicsList::p2pPhysicsList() {
	// TODO Auto-generated constructor stub

}

p2pPhysicsList::~p2pPhysicsList() {

}

void p2pPhysicsList::ConstructParticle(){
	//G4Alpha::AlphaDefinition();
	// Construct all baryons
	G4BaryonConstructor bConstructor; 	//pointer to constructor
	bConstructor.ConstructParticle();	//method that constructs

	// Construct all leptons
	G4LeptonConstructor lConstructor;
	lConstructor.ConstructParticle();

	// Construct all mesons
	G4MesonConstructor mConstructor;
	mConstructor.ConstructParticle();

	// Construct all Boson
	G4BosonConstructor bsConstructor;
	bsConstructor.ConstructParticle();

	// Construct all Shortlived
	G4ShortLivedConstructor slConstructor;
	slConstructor.ConstructParticle();

	// Construct Ion
	G4IonConstructor iConstructor;
	iConstructor.ConstructParticle();
}

void p2pPhysicsList::ConstructProcess(){
	//Allows for tracking
	AddTransportation();

	//Allows for Ion scattering
	G4VPhysicsConstructor* scatter = new G4EmStandardPhysics();
	scatter->ConstructProcess();
}
