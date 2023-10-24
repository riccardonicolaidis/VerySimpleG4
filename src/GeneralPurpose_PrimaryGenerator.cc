#include "GeneralPurpose_PrimaryGenerator.hh"


using namespace std;


GeneralPurpose_PrimaryGenerator::GeneralPurpose_PrimaryGenerator(): G4VUserPrimaryGeneratorAction(),
   fParticleSource(0)
{ 
  // PARTICLE GUN DEFINITION
  fParticleSource = new G4GeneralParticleSource();
  
  // COUNTER
  ParticleNumber = 0;
  

  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String          particleName = "geantino";
  G4ParticleDefinition *particle = particleTable -> FindParticle(particleName);
}

GeneralPurpose_PrimaryGenerator::~GeneralPurpose_PrimaryGenerator()
{
  delete fParticleSource;
}

void GeneralPurpose_PrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  G4ThreeVector positionStart;
  G4ThreeVector momentumStart;

  fParticleSource -> GeneratePrimaryVertex(anEvent);
  positionStart = fParticleSource -> GetParticlePosition();
  momentumStart = fParticleSource -> GetParticleMomentumDirection();

  man -> FillNtupleDColumn(0, fParticleSource->GetParticleEnergy());


  // FILL ALL THE DETAILS REQUIRED FOR THE ANALYSIS
  man -> FillNtupleDColumn(0, 1, positionStart.getX());
  man -> FillNtupleDColumn(0, 2, positionStart.getY());
  man -> FillNtupleDColumn(0, 3, positionStart.getZ());
  man -> FillNtupleDColumn(0, 4, momentumStart.getX());
  man -> FillNtupleDColumn(0, 5, momentumStart.getY());
  man -> FillNtupleDColumn(0, 6, momentumStart.getZ());

  if(ParticleNumber%1000 == 0)
  {
    G4cout << ParticleNumber << G4endl;
  }
    
    

  ++ParticleNumber;
  
}
