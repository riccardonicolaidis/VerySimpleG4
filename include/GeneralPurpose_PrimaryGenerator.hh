#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"
#include "G4GenericMessenger.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

#include "GeneralPurpose_Globals.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class GeneralPurpose_PrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
  GeneralPurpose_PrimaryGenerator();
  ~GeneralPurpose_PrimaryGenerator();

  virtual void GeneratePrimaries(G4Event*);

private:
  G4GeneralParticleSource *fParticleSource;
  G4int ParticleNumber;
};

#endif
