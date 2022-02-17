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
	//fParticleGun->SetParticleEnergy(energy);
	//fParticleGun->SetParticlePosition(position);


	G4AnalysisReader* reader = G4AnalysisReader::Instance();
	reader->SetVerboseLevel(2);

	G4int ntupleID = reader->GetNtuple("Particles","quasi.root");

	G4cout<<"ID: "<<ntupleID<<G4endl;

	G4double x,y,z,px1,py1,pz1,px2,py2,pz2;

	reader->SetNtupleDColumn(ntupleID,"Xint",x);
	reader->SetNtupleDColumn(ntupleID,"Yint",y);
	reader->SetNtupleDColumn(ntupleID,"Zint",z);
	reader->SetNtupleDColumn(ntupleID,"P1x",px1);
	reader->SetNtupleDColumn(ntupleID,"P1y",py1);
	reader->SetNtupleDColumn(ntupleID,"P1z",pz1);
	reader->SetNtupleDColumn(ntupleID,"P2x",px2);
	reader->SetNtupleDColumn(ntupleID,"P2y",py2);
	reader->SetNtupleDColumn(ntupleID,"P2z",pz2);

	reader->GetNtupleRow();

	G4cout<<"Origin: ("<<x<<","<<y<<","<<z<<")"<<G4endl;
	G4cout<<"P1 Mom: ("<<px1<<","<<py1<<","<<pz1<<")"<<G4endl;
	G4cout<<"P2 Mom: ("<<px2<<","<<py2<<","<<pz2<<")"<<G4endl;

	fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));

	fParticleGun->SetParticleMomentum(G4ThreeVector(px1,py1,pz1));
	fParticleGun->GeneratePrimaryVertex(anEvent);

	fParticleGun->SetParticleMomentum(G4ThreeVector(px2,py2,pz2));
	fParticleGun->GeneratePrimaryVertex(anEvent);

/*
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1,1,0));
	fParticleGun->GeneratePrimaryVertex(anEvent);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(-1,1,0));
	fParticleGun->GeneratePrimaryVertex(anEvent);
*/
}

void p2pPrimaryGeneratorAction::SetGunParam1(G4String file){

	G4AnalysisReader* reader = G4AnalysisReader::Instance();
	reader->SetVerboseLevel(2);
	reader->SetFileName("quasi.root");


	G4int ID = reader->GetNtuple("tree");;
	G4cout<<"ID: "<<ID<<G4endl;

}

