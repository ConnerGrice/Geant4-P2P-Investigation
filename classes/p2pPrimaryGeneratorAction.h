#ifndef CLASSES_P2PPRIMARYGENERATORACTION_H_
#define CLASSES_P2PPRIMARYGENERATORACTION_H_

#include <G4VUserPrimaryGeneratorAction.hh>

#include <G4ThreeVector.hh>
#include <G4ParticleMomentum.hh>
#include <G4ParticleGun.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>

class p2pPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction {
public:
	p2pPrimaryGeneratorAction(
						const G4String& particleName = "alpha",
						G4double energy = 300*MeV,
						G4ThreeVector position = G4ThreeVector(0,0,-25*cm),
						G4ParticleMomentum momentumDir = G4ParticleMomentum(1,2,0));

	virtual ~p2pPrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event*);

private:
	G4ParticleGun* fParticleGun;
};

#endif /* CLASSES_P2PPRIMARYGENERATORACTION_H_ */
