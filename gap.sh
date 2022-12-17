#!/bin/bash

suffix=1 
for value in $(seq 0.1 0.1 5.0);
do 
	sed -i 's/const G4double GAP = .*/const G4double GAP = '"$value"'*cm;/g' classes/dimensions.h
	cd build2
	make
	./p2p run.mac
	cd ..
	root -q missingmass.cpp
	cp -v figs/missing.root figs/gaps/$suffix.root
	echo $suffix
	((suffix++))
done

echo ALL done
