#!/bin/bash

suffix=51 
for value in $(seq 51.0 1.0 80.0);
do 
	sed -i 's/const G4double LENGTH = .*/const G4double LENGTH = '"$value"'*cm;/g' classes/dimensions.h
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