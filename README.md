# Geant4-P2P-Investigation

My University of York Theoretical Physics BSc dissertation and accompanying code, investigating the optimal detector system for utilising a (p,2p) interaction when determining the proton binding energy within Carbon-12 atoms.

## Project Description

### Dissertation abstract

A particle detector was designed to make use of the quasi-free (p,2p) knockout reaction in
order to probe the observables of protons in the Carbon-12 nucleus and simulated using the
[Geant4](https://geant4.web.cern.ch/) framework. This report will be beneficial in making design choices at [$R^3B$](https://www.gsi.de/work/forschung/nustarenna/nustarenna_divisions/kernreaktionen/activities/r3b), at which a
physical detector is being developed for similar purposes. The detector system is made up of
two silicon cylindrical layers surrounded by a spherical silicon calorimeter. To investigate the
proficiency of the detector, the missing mass reconstruction was calculated using the outgoing
proton’s 4-momentum vectors. Dimensions tested are the length of the cylinders, the gap
between them and their thickness, as well as the thickness of the calorimeter. An optimal
detector for this situation would be at least 80 cm long, have a gap of 3 cm, a layer thickness
of 0.01 mm or less, and a calorimeter of 160 cm, giving a detector with an 85% efficiency. - [Link to full paper](ConnerGriceFinalDissertation.pdf)

### Program overview

The main purpose of this program is to simulate how 2 protons generated during the (p,2p) reaction move through materials. Specific particle properties are recorded in a digitised way to simulate real-world detectors. This data is then used to calculate the protons momentum, and then used to calculate the binding energy of the Carbon-12 atom the protons originated from (analogous to the missing mass).

[Exact missing mass image here]

The main program can either be viewed within a visualiser, or multiple simulations can be carried out consecutively within the terminal.

[Visualiser image here]

The simulations will result in a data file being produced, that can be converted into a histogram or scatter plots.

[Punch through plot image here]

Multiple scripts are used to automate the simulation and experimentation workflow. Through these experiments, different detector parameters can be fine tuned to get the best results. These parameters include:

- Detector length
- Detector thickness
- Space between detector cylinders
- Thickness of the calorimeter

 More information can be found [here](#usage).

This program makes use of the [Geant4](https://geant4.web.cern.ch/) framework as well as the [ROOT analytics](https://root.cern/) framework.

Geant4 is produced by CERN and makes use of [Monte Carlo simulations](https://en.wikipedia.org/wiki/Monte_Carlo_method) in order to simulate how particles would behave while traveling through different mediums. Geant4 comes with the capabilities to generate 3D geometry as well as a visualiser.

ROOT Analytics is another open-source framework created by CERN for specific use within high energy particle physics. Its primary use is for data analytics. The main feature is the tree-based file system `.root`. These are C++ objects that can be saved and can contain many columns within them.

## Installation

This whole project was done using a [virtual machine](https://indico.cern.ch/event/865808/page/19021-geant4-virtual-machine) provided by CERN, using VMWare. The machine had dependencies already compiled and working.

It seems that this virtual machine is no-longer available for download, so basic dependencies and versions are given below.

|Package|Version|Link|
---:|:---:|:---
Geant4|`10.7.2`|[Download](https://geant4.web.cern.ch/support/download)
ROOT Analytics|`6.18/04`|[Download](https://root.cern/install/)
CLHEP|`**get version**`|[Download](https://gitlab.cern.ch/CLHEP/CLHEP)

Once the dependencies are installed, the program can be built and compiled. First, clone this repository into you desired directory:

```sh
git clone https://github.com/ConnerGrice/Geant4-P2P-Investigation.git
```

Once cloned, move into the `build/` directory and build the program using:

```sh
cmake -DGeant_DIR=$G4COMP ..
```

**Note:** `$G4COMP` is a variable set by the virtual machine, the path this variable corresponds to is, `geant4.10.07.p02/lib64/Geaant-10.7.2`, which represents the directory Geant4 is built into.

Once the CMake file have been created, compile the program using:

```sh
make
```

The `p2p.exe` should now be available in your `build/` directory.

## Usage

Before running any experiments, make sure all the parameters are set to the desired values. The parameters can be found in `classes/dimensions.h`.

Dimension|Description
---|---
`LENGTH`| The length of both cylinders.
`GAP`| The gap between cylinders.
`THICKNESS`| The thickness of both cylinders.
`SEGMENTS`| The number of radial segments in each section along both cylinders.
`ROWS`| The number of sections along both cylinders.
`INNERRAD`| The radius of the inner cylinder.
`CALTHICKNESS`| The thickness of the spherical calorimeter surrounding the detector.

The program can be used in multiple different ways. Carrying out a [single run](#single-run) using the visualiser; a [single experiment](#single-experiment), which consists of 100240 runs; or [multiple experiments](#multiple-experiments), where a parameter is changed according to a specific [script](#scripts).

### Single Run

To initiate the visualiser, use:

```sh
./p2p
```

This will use the `init_vis.mac` macro, which will call the `vis.mac` macro. The `init_vis.mac` macro should be unedited, however, `vis.mac` can be used to change some effects within the visualiser. For example:

```
/vis/viewer/set/viewpointVector 0 0 0
/vis/viewer/set/lightsVector -1 0 0
```

`/vis/viewer/set/viewpointVector` can be used to change the initial position of the camera when the visualiser first loads. The 3 values after the command are the 3D coordinates of the camera. `/vis/viewer/set/lightsVector` is the position of the light source. The 3 values after this command is the 3D unit vector that corresponds to the direction the light source is pointing.

Some commands may need to specify a geometric object to target, for example:

```
/vis/geometry/set/visibility World 0 false
```

In the code above, `World` is the name of an objects in the scene. There are other objects. These objects can be found in `classes/p2pDetectorConstruction.cpp`.

Object Name|Description
---|---
`World`| The entire scene, where all other objects are generated inside of.
`Calorimeter`| The sphere surrounding the detector cylinders.
`Emission`| The small cuboid that simulates the surface that particles original from.
`Inner`| The inner, smaller detector cylinder.
`Outer`| The outer, larger detector cylinder.

More visualiser commands can be found [here](http://www.hep.ph.ic.ac.uk/~yoshiu/COMET/comet_g4HTMLdoc/_vis_.html).

Once the visualiser is running, generate a pair of particles using the command `/run/beamOn 1`. This will use the data from the first entry in the `quasi.root` file provided. Each proceeding run of the command will use the next entry in the file.  

### Single Experiment

A single experiment can be carried out using:

```sh
./p2p run.mac
```

This will make the program use the `run.mac` macro and run the program 100240 times, using all the data in the `quasi.root` file. Due to the increased number of runs, this will be done in batch mode. Batch mode means that the visualiser is not launched and everything is printed into the terminal.

The `run.mac` macro can be edited. The only commands that should be changed if needed:

```
/control/verbose 0
/run/verbose 1
/event/verbose 0
/tracking/verbose 0
```

These will change the type of data that is printed into the terminal as the program is executed.

Once all 100240 runs have been completed and the program stops, a new file containing all the experiment data will have been generated, `build/data.root`. This data can now be processed using:

```sh
root missingmass.cpp
```

This will generate a new file, `figs/missing.root`, which will contain all the missing mass calculation data. ROOT can then be exited with `.q`.

Next, by using `plotprinter.cpp`:

```sh
root plotprinter.cpp
```

A `.png` image along with a `.eps` vector image can be generated. More information on [`missingmass.cpp`](#missingmasscpp) and setting up [`plotprinter.cpp`](#plotprintercpp) can be found.

### Multiple Experiments

The program can be run like this using the one of many shell scripts provided. All of these scripts act in vary similar ways. They carry out an experiment, change some parameter, then run the experiment again.

These scripts can be run using:

```sh
./name_of_shell_script.sh
```

Once the script is finished, there should be a number of `.root` files in the corresponding directory. The next step is to use the corresponding [collection script](#collection-scripts) to assemble the individual experiments together into a single plot for analysis. These collection scripts can be run using:

```sh
root name_of_collection_script.cpp
```

The shell scripts and corresponding collection scripts are as follows:

Script|Default Process|Results Directory|Collection Script
---|---|---|---
`thickness.sh`|`THICKNESS` from 0.01mm to 1mm in 0.01mm steps|`figs/thickness/`|`thicknesscollection.cpp`
`length.sh`|`LENGTH` from 51cm to 80cm in 1cm steps|`figs/lengths/`|`lengthcollection.cpp`
`gap.sh`|`GAP` from 0.1cm to 5cm in 0.1cm steps|`figs/gaps/`|`gapcollection.cpp`
`energycomp.sh`|`CALTHICKNESS` from 80cm to 200cm in 5cm steps|`figs/energy/`| N/A

The shell scripts can be edited to change the range through which the parameters are changed. More information about this can be found [here](#experimentation-scripts). The collection scripts can also be edited in order to change the type of data that is plotted. More information can be found [here](#collection-scripts)

## Scripts

### exacmass.cpp

### missingmass.cpp

### energycomp.cpp

### plotprinter.cpp

### Experimentation scripts

### Collection scripts
