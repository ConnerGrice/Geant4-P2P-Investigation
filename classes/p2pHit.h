#ifndef CLASSES_P2PHIT_H_
#define CLASSES_P2PHIT_H_


#include <G4VHit.hh>
#include <G4THitsCollection.hh>
#include <G4ThreeVector.hh>

class p2pHit: public G4VHit {
public:
	p2pHit();
	virtual ~p2pHit();

	//Print data
	virtual void Print();

	//Set methods
	void Hit(G4int particle);
	void SetTrack(G4int trackID) {fTrack = trackID;};
	void SetEvent(G4int event){fEvent = event;};
	void SetPos(G4ThreeVector pos){fPos = pos;};
	void SetCopy(G4int copy){fCopy = copy;};

	//Get methods
	G4int Getp1() {return p1;};
	G4int Getp2() {return p2;};
	G4int GetTrack() {return fTrack;};
	G4int GetEvent() {return fEvent;};
	G4int GetCopy() {return fCopy;};
	G4ThreeVector GetPos() {return fPos;};
private:
	G4int p1,p2,fTrack,fEvent,fCopy;
	G4ThreeVector fPos;
};


typedef G4THitsCollection<p2pHit> p2pHitsCollection;

#endif /* CLASSES_P2PHIT_H_ */
