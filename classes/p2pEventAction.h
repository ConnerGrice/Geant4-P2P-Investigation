#ifndef CLASSES_P2PEVENTACTION_H_
#define CLASSES_P2PEVENTACTION_H_

#include <G4EventManager.hh>
#include <G4UserEventAction.hh>
#include <g4root.hh>
#include <G4ParticleGun.hh>

#include "p2pRunAction.h"

class p2pEventAction: public G4UserEventAction {
public:
	p2pEventAction(p2pRunAction*);
	virtual ~p2pEventAction();

	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);

	void AddEdep1(G4double edep){Edep1 += edep;};
	void AddEdep2(G4double edep){Edep2 += edep;};
private:
	G4double Edep1,Edep2;
};

#endif /* CLASSES_P2PEVENTACTION_H_ */
