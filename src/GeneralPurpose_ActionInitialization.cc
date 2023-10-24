#include "GeneralPurpose_ActionInitialization.hh"

GeneralPurpose_ActionInitialization::GeneralPurpose_ActionInitialization(GeneralPurpose_DetectorConstruction *detector) 
  : G4VUserActionInitialization(),
  fDetector(detector)
{}

GeneralPurpose_ActionInitialization::~GeneralPurpose_ActionInitialization()
{}

void GeneralPurpose_ActionInitialization::BuildForMaster() const
{
  GeneralPurpose_RunAction *runAction = new GeneralPurpose_RunAction(fDetector, 0, 0, 0);
  SetUserAction(runAction);
}


void GeneralPurpose_ActionInitialization::Build() const
{
  GeneralPurpose_PrimaryGenerator *primary = new GeneralPurpose_PrimaryGenerator();
  GeneralPurpose_EventAction *eventAction = new GeneralPurpose_EventAction();
  GeneralPurpose_SteppingAction *steppingAction = new GeneralPurpose_SteppingAction(fDetector,eventAction);
  GeneralPurpose_RunAction *runAction = new GeneralPurpose_RunAction(fDetector, primary, eventAction, steppingAction);
  GeneralPurpose_TrackingAction* trackingAction = new GeneralPurpose_TrackingAction(fDetector);
  


  SetUserAction(primary);

  
  SetUserAction(eventAction);


  
  SetUserAction(runAction);



  SetUserAction(trackingAction);


  SetUserAction(steppingAction);

}
