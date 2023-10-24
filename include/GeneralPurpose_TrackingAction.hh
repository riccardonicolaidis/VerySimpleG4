#ifndef TRACKING_HH
#define TRACKING_HH

#include "G4UserTrackingAction.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4HadronicProcessType.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"


#include "GeneralPurpose_DetectorConstruction.hh"


class GeneralPurpose_DetectorConstruction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GeneralPurpose_TrackingAction : public G4UserTrackingAction {

  public:  
    GeneralPurpose_TrackingAction(GeneralPurpose_DetectorConstruction*);
   ~GeneralPurpose_TrackingAction();
   
    virtual void  PreUserTrackingAction(const G4Track*);   
    virtual void PostUserTrackingAction(const G4Track*);
    
  private:
    GeneralPurpose_DetectorConstruction* fDetector;
};




#endif