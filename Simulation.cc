#include "GeneralPurpose_Globals.hh"


#include <iostream>
#include <string>
#include <string_view>

#include "G4Types.hh"
#include "G4GenericPhysicsList.hh"
#include "G4VModularPhysicsList.hh"

#include "G4RunManager.hh"


#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "FTFP_BERT.hh"

#include "LBE.hh"
#include "G4EmLowEPPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalParameters.hh"
#include "G4OpticalPhysics.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4PhysListFactory.hh"

#include "GeneralPurpose_DetectorConstruction.hh"
#include "GeneralPurpose_ActionInitialization.hh"      

#include "PhysicsList.hh"

using namespace std;


int main(int argc, char** argv)
{
  // Construct the default run manager
  G4UIExecutive *ui = nullptr;
  // Single Thread mode
  // auto* runManager = G4RunManagerFactory::CreateRunManager();

  G4RunManager* runManager = new G4RunManager();

  // Set mandatory initialization classes
  // Define PhysicsList
  // G4VModularPhysicsList* physicsList = new FTFP_BERT();
  // physicsList   -> ReplacePhysics(new G4EmStandardPhysics_option4());
  // physicsList   -> ReplacePhysics(new G4EmLowEPPhysics());

  // G4StepLimiterPhysics* stepLimiter = new G4StepLimiterPhysics();
  // stepLimiter -> SetApplyToAll(true);
  // physicsList -> RegisterPhysics(stepLimiter);

  
  GeneralPurpose_DetectorConstruction* det= new GeneralPurpose_DetectorConstruction;

  runManager -> SetUserInitialization(det);

  FTFP_BERT* physicsList = new FTFP_BERT();

  G4StepLimiterPhysics* stepLimiter = new G4StepLimiterPhysics();
  stepLimiter -> SetApplyToAll(true);
  physicsList -> RegisterPhysics(stepLimiter);


  
  physicsList -> SetVerboseLevel(0);
  physicsList -> ReplacePhysics(new G4EmStandardPhysics_option4());
  physicsList -> ReplacePhysics(new G4EmLowEPPhysics());
  
  runManager -> SetUserInitialization(physicsList);
  
  runManager -> SetUserInitialization(new GeneralPurpose_ActionInitialization(det));


  G4PhysListFactory *factory = new G4PhysListFactory();
  ofstream out("../physlist.out");

  vector <G4String> physlist = factory -> AvailablePhysLists();
  for (auto &i : physlist)
  {
    out << i << endl;
  }



  if( argc == 1)
  {
    ui = new G4UIExecutive(argc,argv);
  }

  G4VisManager  *visManager = new G4VisExecutive();
  visManager -> Initialize();

  G4UImanager *UImanager =  G4UImanager::GetUIpointer();
  
  runManager -> Initialize();
  

  if(ui)
  {
      UImanager -> ApplyCommand("/control/execute vis.mac");
      UImanager -> ApplyCommand("/control/execute default_generator.mac");
      ui ->SessionStart();
  }
  else 
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager -> ApplyCommand("/control/execute default_generator.mac");
    UImanager -> ApplyCommand(command + fileName);
  }


  delete visManager;
  delete runManager;

  return 0;
}
