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


using namespace std;

namespace{
  int loadMyLibraryTriggerFunc(){
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc");
 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

TFile * histos1 = new TFile("results/W_lepKinematicsEl.root","READ");
TFile * histos2 = new TFile("results/W_lepKinematicsMu.root","READ");

void get2DEffW_lep()
{
 TH2F* hWMu 			= (TH2F*) histos2->Get("hW");
 TH2F* hWMu_rec 		= (TH2F*) histos2->Get("hW_rec");
 TH2F* hWMu_NoVeto 		= (TH2F*) histos2->Get("hW_NoVeto");
 TH2F* hWMu_NoBVeto 		= (TH2F*) histos2->Get("hW_NoBVeto");
 TH2F* hWMu_NoLooseLeptonVeto 	= (TH2F*) histos2->Get("hW_NoLooseLeptonVeto");
 TH2F* hWMu_genWithVeto 	= (TH2F*) histos2->Get("hW_genWithVeto");
 
 TH2F* hWEl 			= (TH2F*) histos1->Get("hW");
 TH2F* hWEl_rec 		= (TH2F*) histos1->Get("hW_rec");
 TH2F* hWEl_NoVeto 		= (TH2F*) histos1->Get("hW_NoVeto");
 TH2F* hWEl_NoBVeto 		= (TH2F*) histos1->Get("hW_NoBVeto");
 TH2F* hWEl_NoLooseLeptonVeto 	= (TH2F*) histos1->Get("hW_NoLooseLeptonVeto");
 TH2F* hWEl_genWithVeto 	= (TH2F*) histos1->Get("hW_genWithVeto");

//  TCanvas* c1 = new TCanvas("c1","c1",800,1600);
//  c1->Divide(2,3);
//  c1->cd(1);
//  hWMu->Draw("COLZ");
//  c1->cd(2);
//  hWMu_NoVeto->Draw("COLZ");
//  c1->cd(3);
//  hWMu_rec->Draw("COLZ");
//  c1->cd(4);
//  hWMu_NoBVeto->Draw("COLZ");
//  c1->cd(5);
//  hWMu_NoLooseLeptonVeto->Draw("COLZ");
//  
 
 //efficiencies like in the sqrt(8) cms paper:
 //generated events kinematic cuts and vetos applied
 //reconstructed events also with all vetos and kin. cuts
 TCanvas *c3 = new TCanvas("c3","vetos on gen. and rec. events applied",800,400);
 c3->Divide(2,1);
 c3->cd(1);
 gPad->SetRightMargin(0.15);
 c3->cd(2);
 
 TEfficiency* WMuEff_wV=0;
 
 if(TEfficiency::CheckConsistency(*hWMu_rec,*hWMu_genWithVeto))
 {
   WMuEff_wV=new TEfficiency(*hWMu_rec,*hWMu_genWithVeto);
   TH2* hWMuEff_wV = WMuEff_wV->CreateHistogram();
    hWMuEff_wV->SetTitle("muon channel");
   style2D(hWMuEff_wV,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
   c3->cd(1);
   hWMuEff_wV->Draw("COLZ");
 }
 
 TEfficiency* WElEff_wV=0;
 
 if(TEfficiency::CheckConsistency(*hWEl_rec,*hWEl_genWithVeto))
 {
   WElEff_wV=new TEfficiency(*hWEl_rec,*hWEl_genWithVeto);
   TH2* hWElEff_wV = WElEff_wV->CreateHistogram();
   hWElEff_wV->SetTitle("electron channel");
   style2D(hWElEff_wV,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
   c3->cd(2);
   hWElEff_wV->Draw("COLZ");
 }
 
 //check efficiencies for the b-tagged jets veto
 TCanvas *c5 = new TCanvas("c5","vetos on gen. and rec. events applied",800,400);
 c5->Divide(2,1);
 c5->cd(1);
 gPad->SetRightMargin(0.15);
 c5->cd(2);
 
 TEfficiency* BTagEffMu=0;
 
 if(TEfficiency::CheckConsistency(*hWMu_rec,*hWMu_NoBVeto))
 {
    BTagEffMu =new TEfficiency(*hWMu_rec,*hWMu_NoBVeto);
    TH2* hBTagEffMu = BTagEffMu->CreateHistogram();
    hBTagEffMu->SetTitle("muon channel: b-tagger efficiency");
   style2D(hBTagEffMu,"Generator p_{t}^{W} [GeV]","Generator |#eta|","b-tagger efficiency");
   c5->cd(1);
   hBTagEffMu->Draw("COLZ");
 }
 
 TEfficiency* BTagEffEl=0;
 
 if(TEfficiency::CheckConsistency(*hWEl_rec,*hWEl_NoBVeto))
 {
   BTagEffEl =new TEfficiency(*hWEl_rec,*hWEl_NoBVeto);
   TH2* hBTagEffEl = BTagEffEl->CreateHistogram();
   hBTagEffEl->SetTitle("electron channel: b-tagger efficiency");
   style2D(hBTagEffEl,"Generator p_{t}^{W} [GeV]","Generator |#eta|","b-tagger efficiency");
   c5->cd(2);
   hBTagEffEl->Draw("COLZ");
 }
 
// check efficiency of the loose lepton veto
 TCanvas *c6 = new TCanvas("c6","vetos on gen. and rec. events applied",800,400);
 c6->Divide(2,1);
 c6->cd(1);
 gPad->SetRightMargin(0.15);
 c6->cd(2);
 
 TEfficiency* LVetoMu=0;
 
 if(TEfficiency::CheckConsistency(*hWMu_rec,*hWMu_NoLooseLeptonVeto))
 {
    LVetoMu =new TEfficiency(*hWMu_rec,*hWMu_NoLooseLeptonVeto);
    TH2* hLVetoMu = LVetoMu->CreateHistogram();
    hLVetoMu->SetTitle("muon channel: lepton veto efficiency");
   style2D(hLVetoMu,"Generator p_{t}^{W} [GeV]","Generator |#eta|","lepton veto efficiency");
   c6->cd(1);
   hLVetoMu->Draw("COLZ");
 }
 
 TEfficiency* LVetoEl=0;
 
 if(TEfficiency::CheckConsistency(*hWEl_rec,*hWEl_NoLooseLeptonVeto))
 {
   LVetoEl =new TEfficiency(*hWEl_rec,*hWEl_NoLooseLeptonVeto);
   TH2* hLVetoEl = LVetoEl->CreateHistogram();
   hLVetoEl->SetTitle("electron channel: lepton veto efficiency");
   style2D(hLVetoEl,"Generator p_{t}^{W} [GeV]","Generator |#eta|","lepton veto efficiency");
   c6->cd(2);
   hLVetoEl->Draw("COLZ");
 }
 
 //plot efficiencies for W-> mu 
 
//  TCanvas * c2 = new TCanvas("c2","W #rightarrow #mu #nu_{#mu} efficiencies",800,800);
//  c2->Divide(2,2);
//  c2->cd(1);
//  gPad->SetRightMargin(0.15);
//  c2->cd(2);
//  gPad->SetRightMargin(0.15);
//  c2->cd(3);
//  gPad->SetRightMargin(0.15);
//  c2->cd(4);
//  gPad->SetRightMargin(0.15);
//  TEfficiency* WMuEff = 0;
//  TEfficiency* WMuEff_NoVeto = 0;
//  TEfficiency* WMuEff_NoBVeto = 0;
//  TEfficiency* WMuEff_NoLooseLeptonVeto = 0;
 
 //overall efficiency with all vetos and cuts applied to the reconstructed events
 //and just kinematic cuts applied to the generated events
 
//  if(TEfficiency::CheckConsistency(*hWMu_rec,*hWMu))
//    {
//      WMuEff = new TEfficiency(*hWMu_rec,*hWMu);
//      TH2* hWMuEff= WMuEff->CreateHistogram();
//      hWMuEff->SetTitle("W #rightarrow #mu #nu_{#mu}, all vetos applied");
//      style2D(hWMuEff,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
//      c2->cd(1);
//      hWMuEff->Draw("COLZ");
//    }

   //efficiency for reconstruction and kinematic cuts only
//  if(TEfficiency::CheckConsistency(*hWMu_NoVeto,*hWMu))
//    {
//      WMuEff_NoVeto = new TEfficiency(*hWMu_NoVeto,*hWMu);
//      TH2* hWMuEff_NoVeto= WMuEff_NoVeto->CreateHistogram();
//      hWMuEff_NoVeto->SetTitle("W #rightarrow #mu #nu_{#mu},  without vetos ");
//      style2D(hWMuEff_NoVeto,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
//      c2->cd(2);
//      hWMuEff_NoVeto->Draw("COLZ");
//    }
   
   //efficiency for reconstruction and cuts and lepton veto
  
//    if(TEfficiency::CheckConsistency(*hWMu_NoBVeto,*hWMu))
//    {
//      WMuEff_NoBVeto = new TEfficiency(*hWMu_NoBVeto,*hWMu);
//      TH2* hWMuEff_NoBVeto= WMuEff_NoBVeto->CreateHistogram();
//      hWMuEff_NoBVeto->SetTitle("W #rightarrow #mu #nu_{#mu}, with loose lepton veto ");
//      style2D(hWMuEff_NoBVeto,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
//      c2->cd(3);
//      hWMuEff_NoBVeto->Draw("COLZ");
//    }
   
   //efficiency for reconstruction and cuts and b-tagged jet veto
//     if(TEfficiency::CheckConsistency(*hWMu_NoLooseLeptonVeto,*hWMu))
//    {
//      WMuEff_NoLooseLeptonVeto = new TEfficiency(*hWMu_NoLooseLeptonVeto,*hWMu);
//      TH2* hWMuEff_NoLooseLeptonVeto= WMuEff_NoLooseLeptonVeto->CreateHistogram();
//      hWMuEff_NoLooseLeptonVeto->SetTitle("W #rightarrow #mu #nu_{#mu},  with b-tagged AK4 jets veto ");
//      style2D(hWMuEff_NoLooseLeptonVeto,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
//      c2->cd(4);
//      hWMuEff_NoLooseLeptonVeto->Draw("COLZ");
//    }
//    
   // efficiencies for electron channel
//  TCanvas * c4 = new TCanvas("c4","W #rightarrow e #nu_{e} efficiencies",800,800);
//  c4->Divide(2,2);
//  c4->cd(1);
//  gPad->SetRightMargin(0.15);
//  c4->cd(2);
//  gPad->SetRightMargin(0.15);
//  c4->cd(3);
//  gPad->SetRightMargin(0.15);
//  c4->cd(4);
//  gPad->SetRightMargin(0.15);
//  TEfficiency* WElEff = 0;
//  TEfficiency* WElEff_NoVeto = 0;
//  TEfficiency* WElEff_NoBVeto = 0;
//  TEfficiency* WElEff_NoLooseLeptonVeto = 0;
//  
 //overall efficiency with all vetos and cuts applied to the reconstructed events
 //and just kinematic cuts applied to the generated events
 
//  if(TEfficiency::CheckConsistency(*hWEl_rec,*hWEl))
//    {
//      WElEff = new TEfficiency(*hWEl_rec,*hWEl);
//      TH2* hWElEff= WElEff->CreateHistogram();
//      hWElEff->SetTitle("W #rightarrow e #nu_{e}, all vetos applied");
//      style2D(hWElEff,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
//      c4->cd(1);
//      hWElEff->Draw("COLZ");
//    }
    //efficiency for reconstruction and kinematic cuts only

//  if(TEfficiency::CheckConsistency(*hWEl_NoVeto,*hWEl))
//    {
//      WElEff_NoVeto = new TEfficiency(*hWEl_NoVeto,*hWEl);
//      TH2* hWElEff_NoVeto= WElEff_NoVeto->CreateHistogram();
//      hWElEff_NoVeto->SetTitle("W #rightarrow e #nu_{e},  without vetos ");
//      style2D(hWElEff_NoVeto,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
//      c4->cd(2);
//      hWElEff_NoVeto->Draw("COLZ");
//    }
     //efficiency for reconstruction and cuts and lepton veto
//    if(TEfficiency::CheckConsistency(*hWEl_NoBVeto,*hWEl))
//    {
//      WElEff_NoBVeto = new TEfficiency(*hWEl_NoBVeto,*hWEl);
//      TH2* hWElEff_NoBVeto= WElEff_NoBVeto->CreateHistogram();
//      hWElEff_NoBVeto->SetTitle("W #rightarrow e #nu_{e}, with loose lepton veto ");
//      style2D(hWElEff_NoBVeto,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
//      c4->cd(3);
//      hWElEff_NoBVeto->Draw("COLZ");
//    }
    //efficiency for reconstruction and cuts and b-tagged jet veto
//    if(TEfficiency::CheckConsistency(*hWEl_NoLooseLeptonVeto,*hWEl))
//    {
//      WElEff_NoLooseLeptonVeto = new TEfficiency(*hWEl_NoLooseLeptonVeto,*hWEl);
//      TH2* hWElEff_NoLooseLeptonVeto= WElEff_NoLooseLeptonVeto->CreateHistogram();
//      hWElEff_NoLooseLeptonVeto->SetTitle("W #rightarrow e #nu_{e},  with b-tagged AK4 jets veto ");
//      style2D(hWElEff_NoLooseLeptonVeto,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
//      c4->cd(4);
//      hWElEff_NoLooseLeptonVeto->Draw("COLZ");
//    }
}