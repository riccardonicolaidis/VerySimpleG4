#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH


#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4GenericMessenger.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4GenericMessenger.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4GDMLParser.hh"
#include "G4GDMLWriteStructure.hh"
#include "G4GDMLEvaluator.hh"
#include "G4MaterialTable.hh"
#include <cmath>
#include "G4VisAttributes.hh"
#include "G4Ellipsoid.hh"
#include "G4AnalysisManager.hh"
#include "G4UserLimits.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"


#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>



#include "GeneralPurpose_Globals.hh"

class GeneralPurpose_DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  GeneralPurpose_DetectorConstruction();
  ~GeneralPurpose_DetectorConstruction();

  virtual G4VPhysicalVolume *Construct();


  G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

private:
  G4LogicalVolume* fScoringVolume = nullptr;

  virtual void ConstructSDandField();

  // World
  G4Box             *solidWorld;
  G4LogicalVolume   *logicWorld;
  G4VPhysicalVolume *physWorld;
  G4VisAttributes   *visWorld;
 
  void DefineMaterials();

  // Materials
  G4Material *worldMat, *SiMat, *Aluminium, *Silicon, *EJ200, *Hmat;
  G4Element *Si, *Cd, *Zn, *Te;
  
  // World
  G4double xWorld, yWorld, zWorld;


  G4double TkAluminium = 0.1 * um;
  G4double TkSilicon   = 100 * um;


  G4double xAl, yAl, zAl;
  G4double xSi, ySi, zSi;

  G4double LSi, LAl;


  G4Box *solidAl;
  G4LogicalVolume *logicAl;
  G4VPhysicalVolume *physAl;
  G4VisAttributes *visAl;

  G4Box *solidSi;
  G4LogicalVolume *logicSi;
  G4VPhysicalVolume *physSi;
  G4VisAttributes *visSi;


  G4GenericMessenger *fMessenger;

};

#endif
