#ifndef RUN_HH
#define RUN_HH


#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4GenericMessenger.hh"
#include "G4AnalysisManager.hh"

#include "GeneralPurpose_DetectorConstruction.hh"
#include "GeneralPurpose_PrimaryGenerator.hh"
#include "GeneralPurpose_EventAction.hh"
#include "GeneralPurpose_Globals.hh"
#include "GeneralPurpose_SteppingAction.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class GeneralPurpose_DetectorConstruction;
class GeneralPurpose_PrimaryGenerator;
class GeneralPurpose_EventAction;
class GeneralPurpose_SteppingAction;


class GeneralPurpose_RunAction : public G4UserRunAction
{
public:
    GeneralPurpose_RunAction(GeneralPurpose_DetectorConstruction*, GeneralPurpose_PrimaryGenerator*, GeneralPurpose_EventAction*, GeneralPurpose_SteppingAction*);
    ~GeneralPurpose_RunAction();

    virtual void BeginOfRunAction(const G4Run* );
    virtual void EndOfRunAction(const G4Run* );

private:
    GeneralPurpose_DetectorConstruction *fDetector;
    GeneralPurpose_PrimaryGenerator *fPrimary;
    GeneralPurpose_EventAction *fEvent;
    GeneralPurpose_SteppingAction *fStepping;
    G4GenericMessenger *fMessenger;
    G4String TotalFileName;
    G4String TotalFileNameFinal;

};

#endif