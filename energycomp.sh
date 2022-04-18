#!/bin/bash

suffix=1 
for value in $(seq 0.01 0.1 1.0);
do 
	sed -i 's/G4double thick = .*/G4double thick = '"$value"'*mm;/g' classes/p2pDetectorConstruction.cpp
	cd build2
	make
	./p2p run.mac
	root -q energycomp.cpp
	cp -v figs/energycomp1.root figs/energy/$suffix.root
	cd ..
	echo $suffix
	echo $value
	suffix=$((suffix + 10))
done

echo ALL done
