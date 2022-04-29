#!/bin/bash

suffix=1 
for value in $(seq 0.01 0.01 1.0);
do 
	sed -i 's/const G4double THICKNESS = .*/const G4double THICKNESS = '"$value"'*mm;/g' classes/dimensions.h
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
