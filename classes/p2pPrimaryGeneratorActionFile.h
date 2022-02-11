#ifndef CLASSES_P2PPRIMARYGENERATORACTIONFILE_H_
#define CLASSES_P2PPRIMARYGENERATORACTIONFILE_H_

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <g4root.hh>

class p2pPrimaryGeneratorActionFile: public G4VUserPrimaryGeneratorAction {
public:
	p2pPrimaryGeneratorActionFile(G4ParticleGun*);
	virtual ~p2pPrimaryGeneratorActionFile();
	virtual void GeneratePrimaries(G4Event*);
private:
	G4ParticleGun* fGun;
};

#endif /* CLASSES_P2PPRIMARYGENERATORACTIONFILE_H_ */
