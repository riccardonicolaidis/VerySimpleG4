#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4GenericMessenger.hh"
#include "G4AnalysisManager.hh"



#include "GeneralPurpose_DetectorConstruction.hh"
#include "GeneralPurpose_EventAction.hh"
#include "GeneralPurpose_Globals.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class GeneralPurpose_DetectorConstruction;
class GeneralPurpose_EventAction;

class GeneralPurpose_SteppingAction : public G4UserSteppingAction
{
public:
    GeneralPurpose_SteppingAction(GeneralPurpose_DetectorConstruction* ,GeneralPurpose_EventAction *);
    ~GeneralPurpose_SteppingAction();

    virtual void UserSteppingAction(const G4Step*);




private:
    GeneralPurpose_EventAction *fEventAction;
    GeneralPurpose_DetectorConstruction *fDetector;
    G4LogicalVolume* fScoringVolume = nullptr;
    
    

    G4GenericMessenger* fMessenger;

};

#endif