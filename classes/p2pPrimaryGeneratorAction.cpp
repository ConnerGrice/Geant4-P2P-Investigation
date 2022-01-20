#include "p2pPrimaryGeneratorAction.h"

#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>

p2pPrimaryGeneratorAction::p2pPrimaryGeneratorAction(
										const G4String& particleName,
										G4double energy,
										G4ThreeVector position,
										G4ParticleMomentum momentumDir)
: G4VUserPrimaryGeneratorAction(),fParticleGun(0){

	G4int nofParticles = 1; //Number of particles
	fParticleGun = new G4ParticleGun(nofParticles);

	//Gets the definition of particles that will be used
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* particle = particleTable->FindParticle(particleName);

	//Setting the values for the particle gun
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleEnergy(energy);
	fParticleGun->SetParticlePosition(position);
	fParticleGun->SetParticleMomentumDirection(momentumDir);
}

p2pPrimaryGeneratorAction::~p2pPrimaryGeneratorAction() {
	delete fParticleGun;
}

void p2pPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
	fParticleGun->GeneratePrimaryVertex(anEvent);

}

