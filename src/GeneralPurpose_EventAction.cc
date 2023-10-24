#include "GeneralPurpose_EventAction.hh"

GeneralPurpose_EventAction::GeneralPurpose_EventAction()
{
}

GeneralPurpose_EventAction::~GeneralPurpose_EventAction()
{}



void GeneralPurpose_EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;  
}


void GeneralPurpose_EventAction::EndOfEventAction(const G4Event* event)
{

  // Retrieve the energy deposited in the sensitive detector


  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man -> FillNtupleDColumn(0, 8, fEdep);

  // Get the Event Number
  G4RunManager *runManager = G4RunManager::GetRunManager();
  G4int EventNumber = runManager->GetCurrentEvent()->GetEventID();
  man -> FillNtupleIColumn(0, 7, EventNumber);

  


  if(fEdep > 0.)
  {
    man -> AddNtupleRow(0);
  }
  

}
