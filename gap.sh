#!/bin/bash

suffix=1 
for value in $(seq 0.1 0.1 5.0);
do 
	sed -i 's/G4double gap = .*/G4double gap = '"$value"'*cm;/g' classes/p2pDetectorConstruction.cpp
	cd build2
	make
	./p2p run.mac
	root -q missingmass.cpp
	cp -v figs/missing.root figs/gaps/$suffix.root
	cd ..
	echo $suffix
	((suffix++))
done

echo ALL done
