#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "GeneralPurpose_PrimaryGenerator.hh"
#include "GeneralPurpose_RunAction.hh"
#include "GeneralPurpose_SteppingAction.hh"
#include "GeneralPurpose_EventAction.hh"
#include "GeneralPurpose_TrackingAction.hh"


class GeneralPurpose_DetectorConstruction;


class GeneralPurpose_ActionInitialization : public  G4VUserActionInitialization
{
public:
  GeneralPurpose_ActionInitialization(GeneralPurpose_DetectorConstruction *detector);
  virtual ~GeneralPurpose_ActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;


private:
  GeneralPurpose_DetectorConstruction *fDetector;
};

#endif
