#ifndef CLASSES_P2PPHYSICSLIST_H_
#define CLASSES_P2PPHYSICSLIST_H_

#include <G4VUserPhysicsList.hh>

#include <G4LeptonConstructor.hh>
#include <G4MesonConstructor.hh>
#include <G4BaryonConstructor.hh>
#include <G4BosonConstructor.hh>
#include <G4ShortLivedConstructor.hh>
#include <G4IonConstructor.hh>
#include <G4VPhysicsConstructor.hh>
#include <G4EmStandardPhysics.hh>

class p2pPhysicsList: public G4VUserPhysicsList {
public:
	p2pPhysicsList();
	virtual ~p2pPhysicsList();
	virtual void ConstructParticle();
	virtual void ConstructProcess();
};

#endif /* CLASSES_P2PPHYSICSLIST_H_ */
