#ifndef CLASSES_P2PRUNACTION_H_
#define CLASSES_P2PRUNACTION_H_

#include <G4UserRunAction.hh>
#include <g4root.hh>
#include <G4Threading.hh>
#include <G4RunManager.hh>
#include <G4Run.hh>

class p2pRunAction: public G4UserRunAction {
public:
	p2pRunAction();
	virtual ~p2pRunAction();

	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);

};

#endif /* CLASSES_P2PRUNACTION_H_ */
