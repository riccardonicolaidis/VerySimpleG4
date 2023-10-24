#include "GeneralPurpose_SteppingAction.hh"


GeneralPurpose_SteppingAction::GeneralPurpose_SteppingAction(GeneralPurpose_DetectorConstruction* det, GeneralPurpose_EventAction* event)
: G4UserSteppingAction(), fDetector(det), fEventAction(event)
{}

GeneralPurpose_SteppingAction::~GeneralPurpose_SteppingAction()
{}


void GeneralPurpose_SteppingAction::UserSteppingAction(const G4Step *step)
{ 
  if (!fScoringVolume) 
  {
    const GeneralPurpose_DetectorConstruction* detConstruction = static_cast<const GeneralPurpose_DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detConstruction->GetScoringVolume();
  }

  // get volume of the current step
  G4LogicalVolume* volume = step -> GetPreStepPoint() -> GetTouchableHandle() -> GetVolume() -> GetLogicalVolume();

  // check if we are in scoring volume
  if(volume == fScoringVolume)
  {
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edepStep);
  }  
}