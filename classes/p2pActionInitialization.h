#ifndef CLASSES_P2PACTIONINITIALIZATION_H_
#define CLASSES_P2PACTIONINITIALIZATION_H_

#include <G4VUserActionInitialization.hh>

#include "p2pPrimaryGeneratorAction.h"
#include "p2pRunAction.h"
#include "p2pEventAction.h"
#include "p2pSteppingAction.h"


class p2pActionInitialization: public G4VUserActionInitialization {
public:
	p2pActionInitialization();
	virtual ~p2pActionInitialization();

	virtual void Build() const;
	virtual void BuildForMaster() const;
};

#endif /* CLASSES_P2PACTIONINITIALIZATION_H_ */
