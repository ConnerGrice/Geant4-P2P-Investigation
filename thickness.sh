#!/bin/bash

suffix=1 
for value in $(seq 0.01 0.01 1.0);
do 
	sed -i 's/G4double thick = .*/G4double thick = '"$value"'*mm;/g' classes/p2pDetectorConstruction.cpp
	cd build2
	make
	./p2p run.mac
	root -q missingmass.cpp
	cp -v figs/missing.root figs/thickness/$suffix.root
	cd ..
	echo $suffix
	((suffix++))
done

echo ALL done
