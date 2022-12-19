# Geant4-P2P-Investigation

My University of York Theoretical Physics BSc dissertation and accompanying code, investigating the optimal detector system for utilising a (p,2p) interaction when determining the proton binding energy within Carbon-12 atoms.

## Project Description

### Dissertation abstract

A particle detector was designed to make use of the quasi-free (p,2p) knockout reaction in
order to probe the observables of protons in the Carbon-12 nucleus and simulated using the
[Geant4](https://geant4.web.cern.ch/) framework. This report will be beneficial in making design choices at [R3B](https://www.gsi.de/work/forschung/nustarenna/nustarenna_divisions/kernreaktionen/activities/r3b), at which a
physical detector is being developed for similar purposes. The detector system is made up of
two silicon cylindrical layers surrounded by a spherical silicon calorimeter. To investigate the
proficiency of the detector, the missing mass reconstruction was calculated using the outgoing
proton’s 4-momentum vectors. Dimensions tested are the length of the cylinders, the gap
between them and their thickness, as well as the thickness of the calorimeter. An optimal
detector for this situation would be at least 80 cm long, have a gap of 3 cm, a layer thickness
of 0.01 mm or less, and a calorimeter of 160 cm, giving a detector with an 85% efficiency. - [Link to full paper](ConnerGriceFinalDissertation.pdf)

### Program overview

The main purpose of this program is to simulate how 2 protons generated during the (p,2p) reaction move through materials. Specific particle properties are recorded in a digitised way to simulate real-world detectors. This data is then used to calculate the protons momentum, and then used to calculate the binding energy of the Carbon-12 atom the protons originated from (analogous to the missing mass).

**Exact missing mass image here**

The main program can either be viewed within a visualiser, or multiple simulations can be carried out consecutively within the terminal. 

![Geant4 visualiser](screenshots/detectorview.png)

The simulations will result in a data file being produced, that can be converted into a histogram or scatter plots.

**Punch through plot image here**

Multiple scripts are used to automate the simulation and experimentation workflow. Through these experiments, different detector parameters can be fine tuned to get the best results. These parameters include:

- Detector length
- Detector thickness
- Space between detector cylinders
- Thickness of the calorimeter

 More information can be found [here](#useage).

This program makes use of the [Geant4](https://geant4.web.cern.ch/) framework as well as the [ROOT analytics](https://root.cern/) framework.

**Geant4**

This framework was produced by CERN and makes use of [Monte Carlo simulations](https://en.wikipedia.org/wiki/Monte_Carlo_method) in order to simulate how particles would behave while traveling through different mediums. Geant4 comes with the capabilities to generate 3D geometry as well as a visualiser.

**ROOT Analytics**

This is another open-source framework created by CERN for specific use within high energy particle physics. Its primary use is for data analytics. The main feature is the tree-based file system `.root`. These are C++ objects that can be saved and can contain many columns within them.

## Installation

This whole project was done using a [virtual machine](https://indico.cern.ch/event/865808/page/19021-geant4-virtual-machine) provided by CERN, using VMWare. The machine had dependencies already compiled and working.

It seems that this virtual machine is no-longer available for download, so basic dependencies and versions are given below.

Package|Version|Link
---:|:---:|:---
Geant4|10.7.2|[Download](https://geant4.web.cern.ch/support/download)
ROOT Analytics|6.18/04|[Download](https://root.cern/install/)
CLHEP|**get version**|[Download](https://gitlab.cern.ch/CLHEP/CLHEP)

Once the dependencies are installed, the program can be built and compiled. First, clone this repository into you desired directory:

```console
$ git clone https://github.com/ConnerGrice/Geant4-P2P-Investigation.git
```

Once cloned, move into the `build/` directory and build the program using:

```console
$ cmake -DGeant_DIR=$G4COMP ..
```

**Note:** `$G4COMP` is a variable set by the virtual machine, the path this variable corresponds to is, `geant4.10.07.p02/lib64/Geaant-10.7.2`, which represents the directory Geant4 is built into.

Once the CMake file have been created, compile the program using:

```console
$ make
```

The `p2p.exe` should now be available in your `build/` directory.

## Usage
