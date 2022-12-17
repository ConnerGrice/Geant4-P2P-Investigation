#!/bin/bash

suffix=80 
for value in $(seq 80 5 200);
do 
	sed -i 's/const G4double CALTHICKNESS = .*/const G4double CALTHICKNESS = '"$value"'*cm;/g' classes/dimensions.h
	cd build2
	make
	./p2p run.mac
	cd ..
	root -q energycomp.cpp
	cp -v figs/energycomp.root figs/energy/$suffix.root
	echo $suffix
	echo $value
	((suffix++))
done

echo ALL done
