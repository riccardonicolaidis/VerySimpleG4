#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4AnalysisManager.hh"


#include "GeneralPurpose_HitClass.hh"
#include "GeneralPurpose_RunAction.hh"
#include "GeneralPurpose_Globals.hh"

class GeneralPurpose_EventAction : public G4UserEventAction
{
public:
        GeneralPurpose_EventAction();
        ~GeneralPurpose_EventAction();

        virtual void BeginOfEventAction(const G4Event*);
        virtual void EndOfEventAction(const G4Event*);
        void AddEdep(G4double edep) { fEdep += edep; }

private:

        G4double   fEdep;


        

        G4GenericMessenger *fMessenger;





};


#endif