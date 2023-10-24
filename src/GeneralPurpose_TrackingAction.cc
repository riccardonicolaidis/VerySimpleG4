#include "GeneralPurpose_TrackingAction.hh"

GeneralPurpose_TrackingAction::GeneralPurpose_TrackingAction(GeneralPurpose_DetectorConstruction* det)
:G4UserTrackingAction(), fDetector(det)
{}

GeneralPurpose_TrackingAction::~GeneralPurpose_TrackingAction()
{}


void GeneralPurpose_TrackingAction::PreUserTrackingAction(const G4Track* track)
{}


void GeneralPurpose_TrackingAction::PostUserTrackingAction(const G4Track* )
{}