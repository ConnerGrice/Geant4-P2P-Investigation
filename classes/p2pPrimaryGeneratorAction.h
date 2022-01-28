#ifndef CLASSES_P2PPRIMARYGENERATORACTION_H_
#define CLASSES_P2PPRIMARYGENERATORACTION_H_

#include <G4VUserPrimaryGeneratorAction.hh>

#include <G4ThreeVector.hh>
#include <G4ParticleMomentum.hh>
#include <G4ParticleGun.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>
#include <G4Proton.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>

class p2pPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction {
public:
	p2pPrimaryGeneratorAction();

	virtual ~p2pPrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event*);

private:
	G4ParticleGun* fParticleGun;
};

#endif /* CLASSES_P2PPRIMARYGENERATORACTION_H_ */
