#!/bin/bash

suffix=20 
for value in $(seq 20.0 1.0 50.0);
do 
	sed -i 's/G4double len = .*/G4double len = '"$value"'*cm;/g' classes/p2pDetectorConstruction.cpp
	cd build2
	make
	./p2p run.mac
	root -q missingmass.cpp
	cp -v figs/missing.root figs/lengths/$suffix.root
	cd ..
	echo $suffix
	((suffix++))
	
done

echo ALL done