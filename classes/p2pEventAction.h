#ifndef CLASSES_P2PEVENTACTION_H_
#define CLASSES_P2PEVENTACTION_H_

#include <G4EventManager.hh>
#include <G4UserEventAction.hh>

#include "p2pRunAction.h"

class p2pEventAction: public G4UserEventAction {
public:
	p2pEventAction(p2pRunAction*);
	virtual ~p2pEventAction();

	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);

	void AddEdep(G4double edep){Edep += edep;};
private:
	G4double Edep;
};

#endif /* CLASSES_P2PEVENTACTION_H_ */
