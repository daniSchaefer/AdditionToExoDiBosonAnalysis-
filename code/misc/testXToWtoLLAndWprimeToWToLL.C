#include "TROOT.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TChain.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
#include "headerfiles/StyleFunc.h"
#include "headerfilesAllChannels/WorkOnHistos.h"



using namespace std;

namespace{
  int loadMyLibraryTriggerFunc(){
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C+");
    
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}
const char* WprimeEl= "results/WPrimeKinematicsEl.root";
const char* WprimeMu = "results/WPrimeKinematicsMu.root";
const char* XEl = "results/WKinematicsEl.root";
const char* XMu = "results/WKinematicsMu.root";
TFile * histosWPEl = new TFile(WprimeEl,"READ");
TFile * histosWPMu = new TFile(WprimeMu,"READ");
TFile * histosXEl = new TFile(XEl,"READ");
TFile * histosXMu = new TFile(XMu,"READ");


void testXToWtoLLAndWprimeToWToLL()
{
   TH2F* hWPToMu_rec		= (TH2F*) histosWPMu->Get("hW_lep_rec");
   TH2F* hWPToMu_gen 		= (TH2F*) histosWPMu->Get("hW_lep_genWithVeto");
   TH2F* hWPToEl_rec		= (TH2F*) histosWPEl->Get("hW_lep_rec");
   TH2F* hWPToEl_gen 		= (TH2F*) histosWPEl->Get("hW_lep_genWithVeto");
   
   TH2F* hXToMu_rec		= (TH2F*) histosXMu->Get("hW_lep_rec");
   TH2F* hXToMu_gen 		= (TH2F*) histosXMu->Get("hW_lep_genWithVeto");
   TH2F* hXToEl_rec		= (TH2F*) histosXEl->Get("hW_lep_rec");
   TH2F* hXToEl_gen 		= (TH2F*) histosXEl->Get("hW_lep_genWithVeto");
   
   TH2* effWPMu = GetEfficiencies(hWPToMu_rec,hWPToMu_gen);
   TH2* effWPEl = GetEfficiencies(hWPToEl_rec,hWPToEl_gen);
   TH2* effXMu  = GetEfficiencies(hXToMu_rec,hXToMu_gen);
   TH2* effXEl  = GetEfficiencies(hXToEl_rec,hXToEl_gen);
   
   TH1D* proj_effWPMu = effWPMu->ProjectionX("proj_effWPMu");
   TH1D* proj_effXMu = effXMu->ProjectionX("proj_effXMu");
   TH1D* proj_effWPMu_eta = effWPMu->ProjectionY("proj_effWPMu_eta");
   TH1D* proj_effXMu_eta = effXMu->ProjectionY("proj_effXMu_eta");
   
   
   TCanvas* c1 = new TCanvas("c1","mu_pT",400,400);
   c1->cd();
   gPad->SetFillStyle(4000);
   proj_effWPMu->SetFillStyle(4000);
   proj_effXMu->SetFillStyle(4000);
   proj_effWPMu->SetLineColor(kRed);
   proj_effXMu->SetLineColor(kBlue);
   proj_effWPMu->Draw();
   proj_effXMu->Draw("SAME");
   c1->Update();
   
   TCanvas* c2 = new TCanvas("c2","mu_eta",400,400);
   c2->cd();
   gPad->SetFillStyle(4000);
   proj_effWPMu_eta->SetFillStyle(4000);
   proj_effXMu_eta->SetFillStyle(4000);
   proj_effWPMu_eta->SetLineColor(kRed);
   proj_effXMu_eta->SetLineColor(kBlue);
   proj_effWPMu_eta->Draw();
   proj_effXMu_eta->Draw("SAME");
   c1->Update();
   
}


