#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TString.h"
#include "TMath.h"
#include "TVector3.h"
#include "TCanvas.h"
#include "TH2D.h"

#include "./TH2DLog.h"
#include "./TH1DLog.h"

TH1* Analisi_1(TString FName)
{
    TFile *file = new TFile(FName);

    TTree *tree = (TTree*)file->Get("Event");

    TCanvas *c1 = new TCanvas("c1","c1",1000,1000);

    tree-> Draw("Edep:IncidentEnergy","","colz");

    double xmin = tree -> GetMinimum("IncidentEnergy");
    double xmax = tree -> GetMaximum("IncidentEnergy");

    double ymin = tree -> GetMinimum("Edep");
    double ymax = tree -> GetMaximum("Edep");



    TH2DLog *h2log = new TH2DLog();
    h2log -> SetName("h2");
    h2log -> SetTitle("h2");
    h2log -> SetXTitle("Incident Energy [MeV]");
    h2log -> SetYTitle("Edep [MeV]");
    h2log -> SetXAxis(xmin,xmax,600);
    h2log -> SetYAxis(ymin,ymax,600);
    h2log -> GenerateHistogram();


    TH2D *h2 = h2log -> GetHistogram();

    tree -> Draw("Edep:IncidentEnergy>>h2","","colz");

    gPad -> SetLogx();
    gPad -> SetLogy();
    gPad -> SetLogz();
    gPad -> SetGrid();



    // Generate a TH1D with same x binning as h2.
    // For each x bin take the y average and the rms

    TH1DLog *h1log = new TH1DLog();
    h1log -> SetName("h1");
    h1log -> SetTitle("h1");
    h1log -> SetXTitle("Incident Energy [MeV]");
    h1log -> SetYTitle("Edep [MeV]");
    h1log -> SetXAxis(xmin,xmax,600);
    h1log -> GenerateHistogram();

    TH1D *h1 = h1log -> GetHistogram();

    for (int i = 1; i <= h2 -> GetNbinsX(); i++)
    {
        TH1D *h1temp = h2 -> ProjectionY("h1temp",i,i);
        h1 -> SetBinContent(i,h1temp -> GetMean());
        h1 -> SetBinError(i,h1temp -> GetRMS());
    }

    h1 -> Draw("histosame");

   return (TH1*) h1 -> Clone();
}



int Analisi()
{
    TString FName1= "/home/riccardo/Documenti/GeantProjects/VerySimpleG4/build/Antiproton.root";
    TString FName2= "/home/riccardo/Documenti/GeantProjects/VerySimpleG4/build/Proton.root";

    TH1 *h1_1 = Analisi_1(FName1);
    TH1 *h1_2 = Analisi_1(FName2);

    h1_2 -> SetLineColor(kRed);


    TCanvas *c2 = new TCanvas("c2","c2",1000,1000);
    h1_1 -> Draw("histo");
    h1_2 -> Draw("histosame");

    h1_1 -> SetLineWidth(2);
    h1_2 -> SetLineWidth(2);

    TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
    leg -> AddEntry(h1_1,"Antiproton","l");
    leg -> AddEntry(h1_2,"Proton","l");

    leg -> Draw();

    gPad -> SetLogx();
    gPad -> SetLogy();
    gPad -> SetGrid();


    // Create a new Histogram which is the division of the two previous ones

    TH1D *h1_3 = (TH1D*) h1_1 -> Clone();
    h1_3 -> Divide(h1_2);

    TCanvas *c3 = new TCanvas("c3","c3",1000,1000);
    h1_3 -> Draw("histo");
    h1_3 -> Smooth(100);

    gPad -> SetLogx();
    gPad -> SetGrid();

    // Smooth the histogram



    return 0;
}