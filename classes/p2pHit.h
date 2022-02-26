#ifndef CLASSES_P2PHIT_H_
#define CLASSES_P2PHIT_H_


#include <G4VHit.hh>
#include <G4THitsCollection.hh>

class p2pHit: public G4VHit {
public:
	p2pHit();
	virtual ~p2pHit();
	p2pHit(const p2pHit&);

	virtual void Print();

	void InnHit(){innFlag += 1;};
	void OutHit(){outFlag += 1;};

	G4int GetInnFlag() {return innFlag;};
	G4int GetOutFlag() {return outFlag;};

private:
	G4int innFlag,outFlag;
};


typedef G4THitsCollection<p2pHit> p2pHitsCollection;

#endif /* CLASSES_P2PHIT_H_ */
