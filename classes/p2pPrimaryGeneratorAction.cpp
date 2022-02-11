#include "p2pPrimaryGeneratorAction.h"

p2pPrimaryGeneratorAction::p2pPrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(),fParticleGun(0){

	G4int nofParticles = 1; //Number of particles
	fParticleGun = new G4ParticleGun(nofParticles);

	fMessenger = new p2pPrimaryGeneratorMessenger(this);


}

p2pPrimaryGeneratorAction::~p2pPrimaryGeneratorAction() {
	delete fParticleGun;
	delete fMessenger;
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

void p2pPrimaryGeneratorAction::SetGunParam1(G4String file){
	G4AnalysisReader* reader = G4AnalysisReader::Instance();
	reader->SetVerboseLevel(1);
	reader->SetFileName(file);

	G4int ntupleID = reader->GetNtuple("X_interact");

	if (ntupleID>=0){
		G4double initX,initY,initZ;
		reader->SetNtupleDColumn("X_interact",initX);
		reader->SetNtupleDColumn("Y_interact",initY);
		reader->SetNtupleDColumn("Z_interact",initZ);
		while(reader->GetNtupleRow()){
			G4cout<<initX<<" "<<initY<<" "<<initZ<<G4endl;
		}
	}


}
