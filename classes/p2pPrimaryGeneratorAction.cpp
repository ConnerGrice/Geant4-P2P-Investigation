#include "p2pPrimaryGeneratorAction.h"

p2pPrimaryGeneratorAction::p2pPrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(),fParticleGun(0){

	G4int nofParticles = 1; //Number of particles
	fParticleGun = new G4ParticleGun(nofParticles);

}

p2pPrimaryGeneratorAction::~p2pPrimaryGeneratorAction() {
	delete fParticleGun;
}

void p2pPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
	G4double energy = 30*MeV;
	G4ThreeVector position = G4ThreeVector(0,0,0);

	//Setting the values for the particle gun
	fParticleGun->SetParticleDefinition(G4Proton::Definition());
	fParticleGun->SetParticleEnergy(energy);
	fParticleGun->SetParticlePosition(position);

	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1,1,0));
	fParticleGun->GeneratePrimaryVertex(anEvent);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1,1,0));
	fParticleGun->GeneratePrimaryVertex(anEvent);

}

