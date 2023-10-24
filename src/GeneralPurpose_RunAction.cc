#include "GeneralPurpose_RunAction.hh"

// Include particles
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4GenericIon.hh"
#include "G4Alpha.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4He3.hh"
#include "G4PionPlus.hh"
#include "G4PionMinus.hh"
#include "G4PionZero.hh"
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"

GeneralPurpose_RunAction::GeneralPurpose_RunAction(GeneralPurpose_DetectorConstruction *det, GeneralPurpose_PrimaryGenerator *prim, GeneralPurpose_EventAction *event, GeneralPurpose_SteppingAction *stepping)
    : G4UserRunAction(),
      fDetector(det), fPrimary(prim), fEvent(event), fStepping(stepping)
{


    TotalFileName = "Default.root";
    fMessenger = new G4GenericMessenger(this, "/NameOfFile/", "Name of the file to save data");
    fMessenger->DeclareProperty("NameOfFile", TotalFileName, "Name of the file to save data");

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    // Ntuple particle generator
    man->CreateNtuple("Event", "Event");
    man->CreateNtupleDColumn("IncidentEnergy");                                     // 0
    man->CreateNtupleDColumn("Xgen");                                               // 1
    man->CreateNtupleDColumn("Ygen");                                               // 2
    man->CreateNtupleDColumn("Zgen");                                               // 3
    man->CreateNtupleDColumn("pDirX");                                              // 4
    man->CreateNtupleDColumn("pDirY");                                              // 5
    man->CreateNtupleDColumn("pDirZ");                                              // 6
    man->CreateNtupleIColumn("EventNumber");                                        // 7
    man->CreateNtupleDColumn("Edep");
    man->FinishNtuple(0);


    // Create an output text file

    G4String FileName = "../Output.txt";
    ofstream OutputFile;
    OutputFile.open(FileName);

    OutputFile << "PDG Encoding for particles:" << endl;

    OutputFile << "gamma = " << G4Gamma::GammaDefinition()->GetPDGEncoding() << endl;
    OutputFile << "e- = " << G4Electron::ElectronDefinition()->GetPDGEncoding() << endl;
    OutputFile << "e+ = " << G4Positron::PositronDefinition()->GetPDGEncoding() << endl;
    OutputFile << "mu- = " << G4MuonMinus::MuonMinusDefinition()->GetPDGEncoding() << endl;
    OutputFile << "mu+ = " << G4MuonPlus::MuonPlusDefinition()->GetPDGEncoding() << endl;
    OutputFile << "pi- = " << G4PionMinus::PionMinusDefinition()->GetPDGEncoding() << endl;
    OutputFile << "pi+ = " << G4PionPlus::PionPlusDefinition()->GetPDGEncoding() << endl;
    OutputFile << "pi0 = " << G4PionZero::PionZeroDefinition()->GetPDGEncoding() << endl;
    OutputFile << "proton = " << G4Proton::ProtonDefinition()->GetPDGEncoding() << endl;

    OutputFile.close();


}

GeneralPurpose_RunAction::~GeneralPurpose_RunAction()
{
}

void GeneralPurpose_RunAction::BeginOfRunAction(const G4Run *run)
{

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    TotalFileNameFinal = TotalFileName + ".root";
    man->SetVerboseLevel(6);
    man->OpenFile(TotalFileNameFinal);
}

void GeneralPurpose_RunAction::EndOfRunAction(const G4Run *)
{

    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}