#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "p2pActionInitialization.h"	//Class that generates the actions by the particle gun
#include "p2pDetectorConstruction.h" //Class that generates the objects
#include "p2pPhysicsList.h"			//Class that defines the physical processes

int main(int argc,char** argv)
{
  // construct the default run manager
  auto runManager = G4RunManagerFactory::CreateRunManager();

  // set mandatory initialization classes
  runManager->SetUserInitialization(new p2pDetectorConstruction());
  runManager->SetUserInitialization(new p2pPhysicsList());
  runManager->SetUserInitialization(new p2pActionInitialization());

  // initialize G4 kernel
  runManager->Initialize();

  //Allows for the use of the visualizer
  //Initializing visualizer
  //the G4VisExecutive can take verbose options e.g "new G4VisExecutive("Quite")"
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  //get the pointer to the UI manager
  G4UImanager* UI = G4UImanager::GetUIpointer();

  //Initializes UI Executive object
  G4UIExecutive* session = nullptr;

  //fills session object if no arguments are given at command line
  if (argc == 1){ session = new G4UIExecutive(argc,argv);}

  //If session is empty, run in batch mode
  if (! session){
	  G4String command = "/control/execute ";
	  G4String macro = argv[1];
	  UI->ApplyCommand(command+macro);
  }
  //else, run init_vis macro and start the visualizer
  else{
	  UI->ApplyCommand("/control/execute init_vis.mac");
	  session->SessionStart();
	  delete session;
  }
  // job termination
  delete runManager;
  delete visManager;
  return 0;
}
