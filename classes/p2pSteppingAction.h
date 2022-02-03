#ifndef CLASSES_P2PSTEPPINGACTION_H_
#define CLASSES_P2PSTEPPINGACTION_H_

#include <G4UserSteppingAction.hh>

#include "p2pDetectorConstruction.h"
#include "p2pEventAction.h"

class p2pSteppingAction: public G4UserSteppingAction {
public:
	p2pSteppingAction(p2pEventAction* eventAction);
	virtual ~p2pSteppingAction();

	virtual void UserSteppingAction(const G4Step* step);

private:
	p2pEventAction* EventAction;
};

#endif /* CLASSES_P2PSTEPPINGACTION_H_ */
