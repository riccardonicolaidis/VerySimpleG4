#include "GeneralPurpose_DetectorConstruction.hh"
#include "G4UserLimits.hh"


using namespace std;

GeneralPurpose_DetectorConstruction::GeneralPurpose_DetectorConstruction()
{

  TkAluminium = TK_AL;
  TkSilicon = 100*um;

  fMessenger = new G4GenericMessenger(this, "/GeneralPurpose/", "Geometry parameters");
  fMessenger->DeclareProperty("TkAluminium", TkAluminium, "Thickness of the Aluminium layer");
  fMessenger->DeclareProperty("TkSilicon", TkSilicon, "Thickness of the Silicon layer");
  
  
  // Define the materials only once
  DefineMaterials();  
}

GeneralPurpose_DetectorConstruction::~GeneralPurpose_DetectorConstruction()
{}

void GeneralPurpose_DetectorConstruction::DefineMaterials()
{
  G4NistManager *nist = G4NistManager::Instance();

  

  Si    = nist -> FindOrBuildElement("Si");
  SiMat = new G4Material("Si", 2.328*g/cm3, 1);
  SiMat -> AddElement(Si,1);

  Aluminium = nist -> FindOrBuildMaterial("G4_Al");
  Silicon = nist -> FindOrBuildMaterial("G4_Si");   
  worldMat = nist -> FindOrBuildMaterial("G4_Galactic");
  Hmat = nist -> FindOrBuildMaterial("G4_H");
  // Set very high density
  // Liquid Hidrogen

  Hmat = new G4Material("Hmat", 1 , 2.016*g/mole, 70.8*kg/m3);

  EJ200 = nist -> FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  
  
  std::vector<G4double> RIndexWorld   = {1.                , 1.                 , 1.};
  std::vector<G4double> RIndexSi      = {3.88163           , 3.88163            , 3.88163};
  std::vector<G4double> Wavelength0 = { 500 * nm, 425*nm, 400*nm};
  std::vector<G4double> Energy ;

  for (int i = 0; i < Wavelength0.size(); i++)
  {
    Energy.push_back(1240*nm/Wavelength0[i]);
  }

  std::vector<G4double> ABSL        = { 380. * cm, 380. * cm , 380. * cm  };
  std::vector<G4double> ABSL_Si     = { 0.1 * um, 0.1 * um , 0.1 * um  };


  G4MaterialPropertiesTable *mptWorld   = new G4MaterialPropertiesTable();
  G4MaterialPropertiesTable *mptSi      = new G4MaterialPropertiesTable();
  

  mptWorld -> AddProperty("RINDEX", Energy, RIndexWorld, 3);
  worldMat -> SetMaterialPropertiesTable(mptWorld);

  mptSi    -> AddProperty("RINDEX", Energy, RIndexWorld, 3);
  mptSi    -> AddProperty("ABSLENGTH", Energy, ABSL_Si, 3);
  SiMat    -> SetMaterialPropertiesTable(mptSi);
}

G4VPhysicalVolume *GeneralPurpose_DetectorConstruction::Construct()
{


  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();


  // .oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo
  // .oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo
  //
  //        NUMERICAL DATA - PARAMETRIZATION
  //
  // .oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo
  // .oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo
  


  TkSilicon = 4*mm;
  double MaxStepLength = 1* um;


  // World dimensions
  xWorld = 5.*m;
  yWorld = 5.*m;
  zWorld = 5.*m;

 
  solidWorld = new G4Box("solidWorld",xWorld*0.5, yWorld*0.5, zWorld*0.5);  
  logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
  visWorld   = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  visWorld->SetVisibility(false);
  logicWorld->SetVisAttributes(visWorld);
  physWorld  = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);
  

  xAl = 0.;
  yAl = 0.;
  zAl = 2*cm;

  xSi = 0.;
  ySi = 0.;
  zSi = zAl + TkAluminium/2. + TkSilicon/2. + 0.1*mm;
  
  LAl = 20*cm;
  LSi = 20*cm;


  solidAl = new G4Box("solidAl", LAl*0.5, LAl*0.5, TkAluminium*0.5);
  logicAl = new G4LogicalVolume(solidAl, Aluminium, "logicAl");
  visAl   = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  visAl->SetVisibility(true);
  logicAl->SetVisAttributes(visAl);
  //physAl  = new G4PVPlacement(0, G4ThreeVector(xAl,yAl,zAl), logicAl, "physAl", logicWorld, false, 0, true);

  solidSi = new G4Box("solidSi", LAl*0.5, LAl*0.5, TkSilicon*0.5);
  logicSi = new G4LogicalVolume(solidSi, Hmat, "logicSi");

  G4UserLimits *MaxStep = new G4UserLimits();
  MaxStep -> SetMaxAllowedStep(MaxStepLength);
  logicSi -> SetUserLimits(MaxStep);


  visSi   = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
  visSi->SetVisibility(true);
  logicSi->SetVisAttributes(visSi);
  physSi  = new G4PVPlacement(0, G4ThreeVector(xSi,ySi,zSi), logicSi, "physSi", logicWorld, false, 0, true);


  fScoringVolume = logicSi;







  return physWorld;  
}


void GeneralPurpose_DetectorConstruction::ConstructSDandField()
{}

