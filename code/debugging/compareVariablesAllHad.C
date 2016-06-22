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
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "/usr/users/dschaefer/root/headerfiles/WWConstants.h"
#include "/usr/users/dschaefer/root/headerfiles/AllHadronicConstants.h"

using namespace std;

namespace{
  int loadMyLibraryTriggerFunc(){
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/General.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}


 
void compareVariablesAllHad(string ModelName1, string ModelName2,string decayMode)
{
  
  string inputname1 = ModelName1+"_"+decayMode+"_genWkin.root";
  string inputname2 = ModelName2+"_"+decayMode+"_genWkin.root";
  
  TFile* histos1 = new TFile(inputname1.c_str(),"READ");
  TFile* histos2 = new TFile(inputname2.c_str(),"READ");
  
  TH1F* M1_W_pt 		= (TH1F*) histos1->Get("W_pt");
  TH1F* M1_W_eta 		= (TH1F*) histos1->Get("W_eta");
  TH1F* M1_W_pt_rec	= (TH1F*) histos1->Get("W_pt_rec");
  TH1F* M1_W_eta_rec 	= (TH1F*) histos1->Get("W_eta_rec");
  TH1F* M1_W_tau21 	= (TH1F*) histos1->Get("W_tau21");
  TH1F* M1_W_prunedmass    = (TH1F*) histos1->Get("W_prunedmass");
  
  TH1F* M2_W_pt 		= (TH1F*) histos2->Get("W_pt");
  TH1F* M2_W_eta 		= (TH1F*) histos2->Get("W_eta");
  TH1F* M2_W_pt_rec		= (TH1F*) histos2->Get("W_pt_rec");
  TH1F* M2_W_eta_rec 		= (TH1F*) histos2->Get("W_eta_rec");
  TH1F* M2_W_tau21 		= (TH1F*) histos2->Get("W_tau21");
  TH1F* M2_W_prunedmass    	= (TH1F*) histos2->Get("W_prunedmass");
  
  float norm = M1_W_pt->GetEntries();
  M1_W_pt->Scale(1/norm);
  norm = M1_W_eta->GetEntries();
  M1_W_eta->Scale(1/norm);
  norm = M1_W_eta_rec->GetEntries();
  M1_W_eta_rec->Scale(1/norm);
  norm = M1_W_pt_rec->GetEntries();
  M1_W_pt_rec->Scale(1/norm);
  norm = M1_W_tau21->GetEntries();
  M1_W_tau21->Scale(1/norm);
  norm = M1_W_prunedmass->GetEntries();
  M1_W_prunedmass->Scale(1/norm);
  
  norm = M2_W_pt->GetEntries();
  M2_W_pt->Scale(1/norm);
  norm = M2_W_eta->GetEntries();
  M2_W_eta->Scale(1/norm);
  norm = M2_W_eta_rec->GetEntries();
  M2_W_eta_rec->Scale(1/norm);
  norm = M2_W_pt_rec->GetEntries();
  M2_W_pt_rec->Scale(1/norm);
  norm = M2_W_tau21->GetEntries();
  M2_W_tau21->Scale(1/norm);
  norm = M2_W_prunedmass->GetEntries();
  M2_W_prunedmass->Scale(1/norm);
  
  
  
   TCanvas* comp = new TCanvas("comp","comp",1600,1600);
   comp->Divide(4,2);
   comp->cd(1);
   M1_W_pt->SetLineColor(kRed);
   M1_W_pt->Draw();
  // M1_W_pt->Draw("E1");
   M2_W_pt->SetLineColor(kBlue);
   M2_W_pt->Draw("same");
   comp->cd(2);
   M1_W_eta->SetLineColor(kRed);
   M1_W_eta->Draw();
   M2_W_eta->SetLineColor(kBlue);
   M2_W_eta->Draw("same");
  
   comp->cd(5);
   M1_W_pt_rec->SetLineColor(kRed);
   M1_W_pt_rec->Draw();
   M2_W_pt_rec->SetLineColor(kBlue);
   M2_W_pt_rec->Draw("same");
   comp->cd(6);
   M1_W_eta_rec->SetLineColor(kRed);
   M1_W_eta_rec->Draw();
   M2_W_eta_rec->SetLineColor(kBlue);
   M2_W_eta_rec->Draw("same");
  
  comp->cd(7);
   M1_W_tau21->SetLineColor(kRed);
   M1_W_tau21->Draw();
   M2_W_tau21->SetLineColor(kBlue);
   M2_W_tau21->Draw("same");
   comp->cd(8);
   M1_W_prunedmass->SetLineColor(kRed);
   M1_W_prunedmass->Draw();
   M2_W_prunedmass->SetLineColor(kBlue);
   M2_W_prunedmass->Draw("same");
  
  
}