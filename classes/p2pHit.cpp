#include "p2pHit.h"

p2pHit::p2pHit(){
	p1 = 0;
	p2 = 0;
	fTrack = -1;
	fEvent = 0;
	fCopy = 0;
	fPos = G4ThreeVector(0,0,0);
}

p2pHit::~p2pHit() {
}

//Counts how many times each particle hit sensitive detector
void p2pHit::Hit(G4int particle){
	if (particle == 1){p1 += 1;}
	if (particle == 2){p2 += 1;}
}

void p2pHit::Print(){
	G4cout<<"Particle 1 hit: "<<p1<<G4endl;
	G4cout<<"Particle 2 hit: "<<p2<<G4endl;

}

