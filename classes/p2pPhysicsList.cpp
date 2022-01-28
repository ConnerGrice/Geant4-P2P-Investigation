#include "p2pPhysicsList.h"

p2pPhysicsList::p2pPhysicsList() {

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
