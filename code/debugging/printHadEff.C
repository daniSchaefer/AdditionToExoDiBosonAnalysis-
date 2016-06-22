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
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
#include "/usr/users/dschaefer/root/headerfiles/MyClass.h"
#include "/usr/users/dschaefer/root/headerfiles/Op.h"
#include "/usr/users/dschaefer/root/headerfiles/EventSelection.h"
#include "/usr/users/dschaefer/root/headerfiles/GenFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/RecFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc2.h"
#include "/usr/users/dschaefer/root/headerfiles/passed_mu_jes.h"

using namespace std;


// note to this construct:
// is needed in this version of root in order to get the header functions right
//also the order in which these files are compiled matters!
namespace{
  int loadMyLibraryTriggerFunc(){
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/General.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/Op.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/EventSelection.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/GenFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/RecFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc2.cc+");
  gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.cc+");

 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void printHadEff()
{
  TFile *BG_M2000 = new TFile("testBulkGravM2000.root","READ");
  TFile *BG_M4000 = new TFile("testBulkGravM4000.root","READ");
  
  TFile *Ra_M2000 = new TFile("testRadionM2000.root","READ");
  TFile *Ra_M4000 = new TFile("testRadionM4000.root","READ");
  
  TH2F* reco_Vplus_BG_M2000 = (TH2F*) BG_M2000->Get("had_reco_Vplus");
  TH2F* reco_Vminus_BG_M2000 = (TH2F*) BG_M2000->Get("had_reco_Vminus");
  TH2F* gen_Vplus_BG_M2000 = (TH2F*) BG_M2000->Get("had_gen_Vplus");
  TH2F* gen_Vminus_BG_M2000 = (TH2F*) BG_M2000->Get("had_gen_Vminus");
  
  
  TH2F* reco_Vplus_BG_M4000 = (TH2F*) BG_M4000->Get("had_reco_Vplus");
  TH2F* reco_Vminus_BG_M4000 = (TH2F*) BG_M4000->Get("had_reco_Vminus");
  TH2F* gen_Vplus_BG_M4000 = (TH2F*) BG_M4000->Get("had_gen_Vplus");
  TH2F* gen_Vminus_BG_M4000 = (TH2F*) BG_M4000->Get("had_gen_Vminus");
  
   TH2F* reco_Vplus_Ra_M2000 = (TH2F*) Ra_M2000->Get("had_reco_Vplus");
  TH2F* reco_Vminus_Ra_M2000 = (TH2F*) Ra_M2000->Get("had_reco_Vminus");
  TH2F* gen_Vplus_Ra_M2000 = (TH2F*) Ra_M2000->Get("had_gen_Vplus");
  TH2F* gen_Vminus_Ra_M2000 = (TH2F*) Ra_M2000->Get("had_gen_Vminus");
  
  
  TH2F* reco_Vplus_Ra_M4000 = (TH2F*) Ra_M4000->Get("had_reco_Vplus");
  TH2F* reco_Vminus_Ra_M4000 = (TH2F*) Ra_M4000->Get("had_reco_Vminus");
  TH2F* gen_Vplus_Ra_M4000 = (TH2F*) Ra_M4000->Get("had_gen_Vplus");
  TH2F* gen_Vminus_Ra_M4000 = (TH2F*) Ra_M4000->Get("had_gen_Vminus");
  
  
  TCanvas* c1 = new TCanvas("c1","c1",800,800);
  c1->Divide(2,2);
  c1->cd(1);
  reco_Vplus_BG_M2000->Draw("COLZ");
  c1->cd(2);
  reco_Vminus_BG_M2000->Draw("COLZ");
  c1->cd(3);
  gen_Vplus_BG_M2000->Draw("COLZ");
  c1->cd(4);
  gen_Vminus_BG_M2000->Draw("COLZ");
  
  TCanvas* c2 = new TCanvas("c2","c2",800,800);
  c2->Divide(2,2);
  c2->cd(1);
  reco_Vplus_BG_M4000->Draw("COLZ");
  c2->cd(2);
  reco_Vminus_BG_M4000->Draw("COLZ");
  c2->cd(3);
  gen_Vplus_BG_M4000->Draw("COLZ");
  c2->cd(4);
  gen_Vminus_BG_M4000->Draw("COLZ");
  
    
  TCanvas* c3 = new TCanvas("c3","c3",800,800);
  c3->Divide(2,2);
  c3->cd(1);
  reco_Vplus_Ra_M2000->Draw("COLZ");
  c3->cd(2);
  reco_Vminus_Ra_M2000->Draw("COLZ");
  c3->cd(3);
  gen_Vplus_Ra_M2000->Draw("COLZ");
  c3->cd(4);
  gen_Vminus_Ra_M2000->Draw("COLZ");
  
  TCanvas* c4 = new TCanvas("c4","c4",800,800);
  c4->Divide(2,2);
  c4->cd(1);
  reco_Vplus_Ra_M4000->Draw("COLZ");
  c4->cd(2);
  reco_Vminus_Ra_M4000->Draw("COLZ");
  c4->cd(3);
  gen_Vplus_Ra_M4000->Draw("COLZ");
  c4->cd(4);
  gen_Vminus_Ra_M4000->Draw("COLZ");
  
  
  
}