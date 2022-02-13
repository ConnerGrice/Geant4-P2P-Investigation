#include "p2pPrimaryGeneratorAction.h"

p2pPrimaryGeneratorAction::p2pPrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(),fParticleGun(0){
	G4int nofParticles = 1; //Number of particles
	fParticleGun = new G4ParticleGun(nofParticles);

	//fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1,1,0));

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


	G4AnalysisReader* reader = G4AnalysisReader::Instance();
	reader->SetVerboseLevel(1);
	reader->SetFileName("quasi.root");
	G4String tree = "Particles";

	G4int ID = reader->GetNtuple(tree);

	if(ID >=0){
		G4double test;
		reader->SetNtupleDColumn("X_interact",test);
		while (reader->GetNtupleRow()){
			G4cout<<"Testing reader: "<<test<<G4endl;
		}
	}
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1,1,0));
	fParticleGun->GeneratePrimaryVertex(anEvent);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1,1,0));
	fParticleGun->GeneratePrimaryVertex(anEvent);
}

void p2pPrimaryGeneratorAction::SetGunParam1(G4String file){

	G4AnalysisReader* reader = G4AnalysisReader::Instance();
	reader->SetVerboseLevel(2);
	reader->SetFileName("quasi.root");


	G4int ID = reader->GetNtuple("tree");;

	if(ID >=0){
		G4double test;
		reader->SetNtupleDColumn("X_interact",test);
		while (reader->GetNtupleRow()){
			G4cout<<test<<G4endl;
			fParticleGun->SetParticleMomentumDirection(G4ThreeVector(test,1,test));
		}
	}



}

