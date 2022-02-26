#include "p2pPrimaryGeneratorAction.h"

p2pPrimaryGeneratorAction::p2pPrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(),fParticleGun(0){
	G4int nofParticles = 1; //Number of particles
	fParticleGun = new G4ParticleGun(nofParticles);

}

p2pPrimaryGeneratorAction::~p2pPrimaryGeneratorAction() {
	delete fParticleGun;
}

void p2pPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){

	//Setting the values for the particle gun
	fParticleGun->SetParticleDefinition(G4Proton::Definition());

	//Create analysis reader to read data file
	G4AnalysisReader* reader = G4AnalysisReader::Instance();
	reader->SetVerboseLevel(1);

	//Read an individual row of the "Particles" tree in the "quasi.root" file
	G4int ntupleID = reader->GetNtuple("Particles","quasi.root");
	//G4cout<<"ID: "<<ntupleID<<G4endl;

	G4double x,y,z,px1,py1,pz1,px2,py2,pz2;

	//Pick out the wanted values in that row
	reader->SetNtupleDColumn(ntupleID,"Xint",x);
	reader->SetNtupleDColumn(ntupleID,"Yint",y);
	reader->SetNtupleDColumn(ntupleID,"Zint",z);
	reader->SetNtupleDColumn(ntupleID,"P1x",px1);
	reader->SetNtupleDColumn(ntupleID,"P1y",py1);
	reader->SetNtupleDColumn(ntupleID,"P1z",pz1);
	reader->SetNtupleDColumn(ntupleID,"P2x",px2);
	reader->SetNtupleDColumn(ntupleID,"P2y",py2);
	reader->SetNtupleDColumn(ntupleID,"P2z",pz2);

	//Get values
	reader->GetNtupleRow();

	/*
	G4cout<<"Origin: ("<<x<<","<<y<<","<<z<<")"<<G4endl;
	G4cout<<"P1 Mom: ("<<px1<<","<<py1<<","<<pz1<<")"<<G4endl;
	G4cout<<"P2 Mom: ("<<px2<<","<<py2<<","<<pz2<<")"<<G4endl;
	*/

	//Set reaction origin point
	fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));

	//Define and shoot outgoing particle 1
	fParticleGun->SetParticleMomentum(G4ThreeVector(px1,py1,pz1));
	fParticleGun->GeneratePrimaryVertex(anEvent);

	//Define and shoot outgoing particle 2
	fParticleGun->SetParticleMomentum(G4ThreeVector(px2,py2,pz2));
	fParticleGun->GeneratePrimaryVertex(anEvent);
}


