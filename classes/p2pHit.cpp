#include "p2pHit.h"

p2pHit::p2pHit(){
	innFlag = 0;
	outFlag = 0;
}

p2pHit::~p2pHit() {
}

p2pHit::p2pHit(const p2pHit& right):G4VHit(){
	innFlag = right.innFlag;
	outFlag = right.outFlag;
}

void p2pHit::Print(){
	G4cout<<"Inn Flag: "<<innFlag<<G4endl;
	G4cout<<"Out Flag: "<<outFlag<<G4endl;
}

