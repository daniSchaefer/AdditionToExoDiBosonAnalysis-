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

TFile * histos = new TFile("results/kinematicsVarBinSizes.root","READ");
//TFile * histos = new TFile("results/kinematics.root","READ");


void get2DEffMuEl()
{

  TH2F* hMu = (TH2F*) histos->Get("hMu");
  TH2F* hMu_rec = (TH2F*) histos->Get("hMu_rec");
  TH2F* hEl = (TH2F*) histos->Get("hEl");
  TH2F* hEl_rec =(TH2F*) histos->Get("hEl_rec");
  TH2F* hW_MuonChannel=(TH2F*) histos->Get("hW_MuChannel");
  TH2F* hW_ElectronChannel=(TH2F*) histos->Get("hW_ElChannel");
  TH2F* hW_MuonChannel_rec=(TH2F*) histos->Get("hW_MuChannel_rec");
  TH2F* hW_ElectronChannel_rec=(TH2F*) histos->Get("hW_ElChannel_rec");
  style2D(hMu,"generated p_{t} [GeV]","generated |#eta|","number of events");
  style2D(hEl,"generated p_{t} [GeV]","generated |#eta|","number of events");

  style2D(hMu_rec,"generated p_{t} [GeV]","generated |#eta|","number of events");
  style2D(hEl_rec,"generated p_{t} [GeV]","generated |#eta|","number of events");


  TCanvas * c1= new TCanvas("c1","c1",800,1600);
  c1->Divide(2,4);
  c1->cd(1);
  hMu->Draw("COLZ");
  c1->cd(2);
  hMu_rec->Draw("COLZ");
  c1->cd(3);
  hEl->Draw("COLZ");
  c1->cd(4);
  hEl_rec->Draw("COLZ");
  c1->cd(5);
  hW_MuonChannel->Draw("COLZ");
  c1->cd(6);
  hW_ElectronChannel->Draw("COLZ");
  c1->cd(7);
  hW_MuonChannel_rec->Draw("COLZ");
  c1->cd(8);
  hW_ElectronChannel_rec->Draw("COLZ");

  TCanvas * c2= new TCanvas("c2","c2",400,400);
  TCanvas * c3= new TCanvas("c3","c3",400,400);
  TCanvas * c4= new TCanvas("c4","c4",400,400);
  TCanvas * c5= new TCanvas("c5","c5",400,400);
  c2->cd();
  gPad->SetRightMargin(0.15);
  c3->cd();
  gPad->SetRightMargin(0.15);
  c4->cd();
  gPad->SetRightMargin(0.15);
  c5->cd();
  gPad->SetRightMargin(0.15);
 
  TEfficiency* muEff = 0;
  TEfficiency* elEff = 0;
  TEfficiency* WmuEff = 0;
  TEfficiency* WelEff = 0;
 if(TEfficiency::CheckConsistency(*hMu_rec,*hMu))
   {
     muEff = new TEfficiency(*hMu_rec,*hMu);
     TH2* hmuEff= muEff->CreateHistogram();
     hmuEff->SetTitle("muon channel");
     style2D(hmuEff,"Generator p_{t}^{mu} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
     c2->cd();
     hmuEff->Draw("COLZ");
    
   }

if(TEfficiency::CheckConsistency(*hEl_rec,*hEl))
   {
     elEff = new TEfficiency(*hEl_rec,*hEl);
     TH2* helEff= elEff->CreateHistogram();
     helEff->SetTitle("electron channel");
     style2D(helEff,"Generator p_{t}^{el} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
     c3->cd();
     helEff->Draw("COLZ");
   }
 if(TEfficiency::CheckConsistency(*hW_MuonChannel_rec,*hW_MuonChannel))
   {
     WmuEff = new TEfficiency(*hW_MuonChannel_rec,*hW_MuonChannel);
     TH2* hWmuEff= WmuEff->CreateHistogram();
     hWmuEff->SetTitle("W #rightarrow #mu #nu_{#mu}");
     style2D(hWmuEff,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
     c4->cd();
     hWmuEff->Draw("COLZ");
    
   }

if(TEfficiency::CheckConsistency(*hW_ElectronChannel_rec,*hW_ElectronChannel))
   {
     WelEff = new TEfficiency(*hW_ElectronChannel_rec,*hW_ElectronChannel);
     TH2* hWelEff= WelEff->CreateHistogram();
     hWelEff->SetTitle("W #rightarrow e #nu_{e}");
     style2D(hWelEff,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
     c5->cd();
     hWelEff->Draw("COLZ");
   }


 c1->SaveAs("results/EtaOverPt_VarBinSize_WithVetos.pdf");
 c2->SaveAs("results/MuonEff_VarBinSize_WithVetos.pdf");
 c3->SaveAs("results/ElectronEff_VarBinSize_WithVetos.pdf");
 c4->SaveAs("results/WMuonEff_VarBinSize_WithVetos.pdf");
 c5->SaveAs("results/WElectronEff_VarBinSize_WithVetos.pdf");


}
