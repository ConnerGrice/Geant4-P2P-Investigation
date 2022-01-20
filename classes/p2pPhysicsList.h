/*
 * p2pPhysicsList.h
 *
 *  Created on: Jan 20, 2022
 *      Author: local1
 */

#ifndef CLASSES_P2PPHYSICSLIST_H_
#define CLASSES_P2PPHYSICSLIST_H_

#include <G4VUserPhysicsList.hh>

class p2pPhysicsList: public G4VUserPhysicsList {
public:
	p2pPhysicsList();
	virtual ~p2pPhysicsList();
	virtual void ConstructParticle();
	virtual void ConstructProcess();
};

#endif /* CLASSES_P2PPHYSICSLIST_H_ */
