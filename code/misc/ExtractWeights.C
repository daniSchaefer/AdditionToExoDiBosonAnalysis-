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
#include "headerfilesAllChannels/WorkOnHistos.h"
#include "/usr/users/dschaefer/root/headerfiles/MyClass.h"
#include "/usr/users/dschaefer/root/headerfiles/passed_mu_jes.h"
#include "/usr/users/dschaefer/root/headerfiles/Op.h"
#include "/usr/users/dschaefer/root/headerfiles/EventSelection.h"
#include "/usr/users/dschaefer/root/headerfiles/GenFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/RecFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc.h"


namespace{
  int loadMyLibraryTriggerFunc(){
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/Op.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/EventSelection.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/GenFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/RecFunc.cc+");
  gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C+");
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}
// TFile *electronChannel = new TFile("results/WKinematicsEl.root","READ");
// TFile *muonChannel = new TFile("results/WKinematicsMu.root","READ");
// TFile *electronChannel_2TeV = new TFile("results/WKinematicsEl-2TeV.root","READ");
// TFile *muonChannel_2TeV = new TFile("results/WKinematicsMu-2TeV.root","READ");
// 
// const char* input_filename6 = "/storage/a/mmozer/Res_Sig/BulkGravToWWToWlepWhad_narrow_M_2000/EXOVVTree_BulkGravToWWToWlepWhad_narrow_M_2000_1.root";

TFile *electronChannel = new TFile("results/WPrimeKinematicsEl.root","READ");
TFile *muonChannel = new TFile("results/WPrimeKinematicsMu.root","READ");
TFile *electronChannel_2TeV = new TFile("results/WPrimeKinematicsEl-2TeV.root","READ");
TFile *muonChannel_2TeV = new TFile("results/WPrimeKinematicsMu-2TeV.root","READ");

const char* input_filename6 ="/storage/a/mmozer/Res_Sig/WprimeToWZToWlepZhad_narrow_M-2000/EXOVVTree_WprimeToWZToWlepZhad_narrow_M-2000_1.root";

TFile *gendata = new TFile(input_filename6,"READ");
TTree *tree = (TTree*) gendata->Get("ntuplizer/tree");

void ExtractWeights()
{
  //electron Channel:
  
  //lepton selection
 TH2F* hWEl_rec 		= (TH2F*) electronChannel->Get("hW_lep_rec");
 TH2F* hWEl_genWithVeto 	= (TH2F*) electronChannel->Get("hW_lep_genWithVeto");
 TH2F* hWEl_rec_2TeV		= (TH2F*) electronChannel_2TeV->Get("hW_lep_rec");
 TH2F* hWEl_2TeV		= (TH2F*) electronChannel_2TeV->Get("hW_lep_genWithVeto");
 TH2F* hWEl_2TeV_weights;
 

 //B-Veto
 TH2F* hWEl_genWithBVeto	= (TH2F*) electronChannel->Get("hW_lep_genWithBVeto");
 TH2F* hWEl_2TeV_genWithBVeto   = (TH2F*) electronChannel_2TeV->Get("hW_lep_genWithBVeto");
 
 //Loose Lepton Veto
 TH2F* hWEl_genWithLooseLeptonVeto = (TH2F*) electronChannel->Get("hW_lep_genWithLooseLeptonVeto");
 TH2F* hWEl_2TeV_genWithLooseLeptonVeto = (TH2F*) electronChannel_2TeV->Get("hW_lep_genWithLooseLeptonVeto");
 
 //muon channel
 
 //lepton selection
 TH2F* hWMu_rec 		= (TH2F*) muonChannel->Get("hW_lep_rec");
 TH2F* hWMu_genWithVeto 	= (TH2F*) muonChannel->Get("hW_lep_genWithVeto");
 TH2F* hWMu_rec_2TeV		= (TH2F*) muonChannel_2TeV->Get("hW_lep_rec");
 TH2F* hWMu_2TeV		= (TH2F*) muonChannel_2TeV->Get("hW_lep_genWithVeto");
 TH2F* hWMu_2TeV_weights;
 
 //B-Veto and hW_lep_genWithLooseLeptonVeto
 TH2F* hWMu_genWithBVeto = (TH2F*) muonChannel->Get("hW_lep_genWithBVeto");
 TH2F* hWMu_genWithLooseLeptonVeto = (TH2F*) muonChannel->Get("hW_lep_genWithLooseLeptonVeto");
 
 TH2F* hWMu_2TeV_genWithBVeto = (TH2F*) muonChannel_2TeV->Get("hW_lep_genWithBVeto");
 TH2F* hWMu_2TeV_genWithLooseLeptonVeto = (TH2F*) muonChannel_2TeV->Get("hW_lep_genWithLooseLeptonVeto");
 
 
 //hadronic W
 
 //jet selection
 TH2F* hW_had_rec		= (TH2F*) muonChannel->Get("hW_had_rec");
 TH2F* hW_had_genWithVeto	= (TH2F*) muonChannel->Get("hW_had_genWithVeto");
 TH2F* hW_had_rec_El		= (TH2F*) electronChannel->Get("hW_had_rec");
 TH2F* hW_had_gen_El 		= (TH2F*) electronChannel->Get("hW_had_genWithVeto");
 
 TH2F* hW_had_rec_2TeV		= (TH2F*) muonChannel_2TeV->Get("hW_had_rec");
 TH2F* hW_had_genWithVeto_2TeV	= (TH2F*) muonChannel_2TeV->Get("hW_had_genWithVeto");
 TH2F* hW_had_rec_El_2TeV	= (TH2F*) electronChannel_2TeV->Get("hW_had_rec");
 TH2F* hW_had_gen_El_2TeV 	= (TH2F*) electronChannel_2TeV->Get("hW_had_genWithVeto");
 TH2F* hW_had_2TeV_weights;
 
 hW_had_genWithVeto->Add(hW_had_gen_El);
 hW_had_rec->Add(hW_had_rec_El);
 hW_had_genWithVeto_2TeV->Add(hW_had_gen_El_2TeV);
 hW_had_rec_2TeV->Add(hW_had_rec_El_2TeV);
 
 
  style2D(hWEl_rec_2TeV,"Generator p_{t}^{W} [GeV]","Generator |#eta|","# events");
  
  style2D(hWMu_rec_2TeV,"Generator p_{t}^{W} [GeV]","Generator |#eta|","# events");
 
  
  
 int nBinsX = 16;
 int nBinsY = 10;
 vector<double> BinsX={0,200,250,300,400,500,600,700,800,1000,1200,1500,2000,2500,3000,4000};
 vector<double> BinsY={0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};
 
 TCanvas* canvas1 = new TCanvas("canvas1","canvas1",400,400);
 TCanvas* canvas2 = new TCanvas("canvas2","canvas2",400,400);
 TCanvas* canvas3 = new TCanvas("canvas3","canvas3",400,400);
 
 hW_had_2TeV_weights = GenerateAllTables(hW_had_rec,hW_had_genWithVeto,hW_had_genWithVeto_2TeV,hW_had_rec_2TeV,24,nBinsX,nBinsY,BinsX,BinsY,canvas3);
 
 hWEl_2TeV_weights =GenerateAllTables(hWEl_rec,hWEl_genWithVeto,hWEl_2TeV,hWEl_rec_2TeV,11,nBinsX, nBinsY, BinsX, BinsY,canvas1);
 
 hWMu_2TeV_weights = GenerateAllTables(hWMu_rec,hWMu_genWithVeto,hWMu_2TeV,hWMu_rec_2TeV,13,nBinsX,nBinsY, BinsX, BinsY,canvas2);
 
 
 TH2* test = GetEfficienciesWithError(hWEl_rec,hWEl_genWithVeto,nBinsX,nBinsY);
 
 //all tests combined
//==============================================================================
/*
 TH2F* hWcombined = new TH2F(*hW_had_2TeV_weights);
 hWcombined->Add(hWEl_2TeV_weights);
 hWcombined->Add(hWMu_2TeV_weights);
 
 TH2F* hWcombined_rec = new TH2F(*hW_had_rec_2TeV);
 hWcombined_rec->Add(hWEl_rec_2TeV);
 hWcombined_rec->Add(hWMu_rec_2TeV);
 
 
 
 vector<vector<double> > rw_had = MakeListOfWeights( GetEfficiencies(hW_had_rec,hW_had_genWithVeto) ,nBinsX,nBinsY);
 vector<vector<double> > rw_el = MakeListOfWeights(GetEfficiencies(hWEl_rec,hWEl_genWithVeto), nBinsX, nBinsY);
 vector<vector<double> > rw_mu = MakeListOfWeights(GetEfficiencies(hWMu_rec,hWMu_genWithVeto),nBinsX, nBinsY);
 
 TH2F* hWEl_2TeV_rw = new  TH2F(*hWEl_2TeV);
 TH2F* hWMu_2TeV_rw = new  TH2F(*hWMu_2TeV);
 TH2F* hW_had_2TeV_rw = new  TH2F(*hW_had_genWithVeto_2TeV);
 
 ReweightHistogram(hWEl_2TeV_rw,rw_el);
 ReweightHistogram(hWMu_2TeV_rw,rw_mu);
 ReweightHistogram(hW_had_2TeV_rw,rw_had);
 
 TH2F* hWcombined_rw = new TH2F(*hWEl_2TeV_rw);
 hWcombined_rw->Add(hW_had_2TeV_rw);
 hWcombined_rw->Add(hWMu_2TeV_rw);
 
 double result2 = GetRatio(hWcombined_rw,hWcombined_rec,nBinsX,nBinsY);

 
 if(hWcombined!=0 and hWcombined_rec!=0)
 {
    //double result = GetRatio(hWcombined,hWcombined_rec,nBinsX, nBinsY);
   vector<double> result = SumOverAllFilledBins(hWcombined, nBinsX, nBinsY);
    std::cout<< "combined ratio of electron, muon and hadron channel, all bins "<< result[1]/(3*result[0])<< "  "<< result2 << std::endl;
    std::cout<< "abs(combined ratio -1) "<< TMath::Abs(result[1]/(3*result[0])-1) <<  "   "<< TMath::Abs(result2-1) <<std::endl;
 }
 else
   std::cout << " at least hWcombined or hWcombined_rec is a zero pointer " <<std::endl; */

// PrintBinContents(hWcombined, BinsX, BinsY,"hWcombined");
// PrintBinContents(hWcombined_rec, BinsX, BinsY,"hWcombined_rec");
 
 
 //Display the histos in a Canvas
 //=============================================================================
 

 TCanvas *c2 = new TCanvas("c2","c2",800,800);
 c2->Divide(2,2);
 c2->cd(1);
  gPad->SetRightMargin(0.15);
  hWEl_2TeV->SetTitle("W #rightarrow e #nu");
 hWEl_2TeV->Draw("COLZ");
 c2->cd(2);
  gPad->SetRightMargin(0.15);
  hWEl_rec_2TeV->SetTitle("W #rightarrow e #nu");
 hWEl_rec_2TeV->Draw("COLZ");
 c2->cd(3);
  gPad->SetRightMargin(0.15);
  hWEl_2TeV_weights->GetYaxis()->SetRangeUser(0,2.5);
  hWEl_2TeV_weights->SetTitle("W #rightarrow e #nu");
  hWEl_2TeV_weights->Draw("COLZ");
 

TCanvas *c3 = new TCanvas("c3","c3",800,800);
 c3->Divide(2,2);
 c3->cd(1);
  gPad->SetRightMargin(0.15);
  hWMu_2TeV->SetTitle("W #rightarrow #mu #nu");
 hWMu_2TeV->Draw("COLZ");
 c3->cd(2);
  gPad->SetRightMargin(0.15);
   hWMu_rec_2TeV->SetTitle("W #rightarrow #mu #nu");
 hWMu_rec_2TeV->Draw("COLZ");
 c3->cd(3);
  gPad->SetRightMargin(0.15);
  hWMu_2TeV_weights->GetYaxis()->SetRangeUser(0,2.5);
   hWMu_2TeV_weights->SetTitle("W #rightarrow #mu #nu");
 hWMu_2TeV_weights->Draw("COLZ");
 
 //B Veto
 //=============================================================================
 vector<double> BVelectrons;
 vector<double> BVmuons;
 

 TH2* hBVEl = GetEfficienciesWithError(hWEl_genWithVeto,hWEl_genWithLooseLeptonVeto,nBinsX,nBinsY);
 if(hBVEl!=0)
 {
   BVelectrons= SumOverAllFilledBins(hBVEl,nBinsX,nBinsY);
   std::cout<<"electrons B-Veto Eff"<<std::endl;
  // std::cout<< BVelectrons[0]<<"  "<< BVelectrons[1]<<std::endl;
   std::cout<< BVelectrons[1]/BVelectrons[0]<<std::endl;
 }
 
 
 TH2* hBVMu = GetEfficienciesWithError(hWMu_genWithVeto,hWMu_genWithLooseLeptonVeto,nBinsX, nBinsY);
 if(hBVMu!=0)
 {
   BVmuons = SumOverAllFilledBins(hBVMu,nBinsX,nBinsY);
   std::cout<< "muons B-Veto Eff" << std::endl;
   //std::cout<< BVmuons[0]<<" "<<BVmuons[1]<<std::endl;
   std::cout<<BVmuons[1]/BVmuons[0]<<std::endl;
 }
 
 //B Veto from 2TeV sample
 double BVelectrons2TeV = GetRatio(hWEl_2TeV,hWEl_2TeV_genWithLooseLeptonVeto,nBinsX,nBinsY);
 double BVmuons2TeV = GetRatio(hWMu_2TeV,hWMu_2TeV_genWithLooseLeptonVeto,nBinsX,nBinsY);
 std::cout << "BV eff for 2TeV sample electron channel " << BVelectrons2TeV <<std::endl;
 std::cout << "BV eff for 2TeV sample  muon channel "<< BVmuons2TeV <<std::endl;
 std::cout<<" electron + muon channel combined"<<std::endl;
 std::cout << " 2TeV "<<(BVmuons2TeV + BVelectrons2TeV)/2.0 << " all "<< (BVmuons[1] + BVelectrons[1])/(BVmuons[0]+BVelectrons[0]) <<std::endl;
 
 
 
 
 // loose lepton veto
 //============================================================================
 vector<double> LLVelectrons;
 vector<double> LLVmuons;
 
 
 TH2* hLLVEl = GetEfficienciesWithError(hWEl_genWithVeto,hWEl_genWithBVeto,nBinsX,nBinsY);
 if(hLLVEl!=0)
 {
   LLVelectrons= SumOverAllFilledBins(hLLVEl,nBinsX,nBinsY);
   std::cout<<"electrons LLV Eff"<<std::endl;
  // std::cout<< LLVelectrons[0]<<"  "<< LLVelectrons[1]<<std::endl;
   std::cout<< "average over all bins of LLV efficincy in electron channel"<<LLVelectrons[1]/LLVelectrons[0]<<std::endl;
 }
 
 
 TH2* hLLVMu = GetEfficienciesWithError(hWMu_genWithVeto,hWMu_genWithBVeto,nBinsX,nBinsY);
 if(hLLVMu!=0)
 {
   LLVmuons = SumOverAllFilledBins(hLLVMu,nBinsX,nBinsY);
   std::cout<< "muons LLV Eff" << std::endl;
  // std::cout<< LLVmuons[0]<<" "<<LLVmuons[1]<<std::endl;
   std::cout<< "(average over all Bins of LLV efficincy in the muon channel) "<<LLVmuons[1]/LLVmuons[0]<<std::endl;
 }
 
 //B Veto from 2TeV sample
 double LLVelectrons2TeV = GetRatio(hWEl_2TeV,hWEl_2TeV_genWithBVeto,nBinsX,nBinsY);
 double LLVmuons2TeV = GetRatio(hWMu_2TeV,hWMu_2TeV_genWithBVeto,nBinsX,nBinsY);
 std::cout << "LLV eff for 2TeV sample electron channel " << LLVelectrons2TeV <<std::endl;
 std::cout << "LLV eff for 2TeV sample  muon channel "<< LLVmuons2TeV <<std::endl;
 std::cout<<" electron + muon channel combined"<<std::endl;
 std::cout << " 2TeV (average 2TeV electron and muon LLV efficiency)  "<<(LLVmuons2TeV + LLVelectrons2TeV)/2.0 << " all (average over electron and muon channel efficincies) "<< (LLVmuons[1] + LLVelectrons[1])/(LLVmuons[0]+LLVelectrons[0]) <<std::endl;
 
//  vector<vector<double> > test = MakeListOfWeights(GetEfficiencies(hWMu_rec,hWMu_genWithVeto),BinsX,BinsY);
//  std::cout << test[0].size()<<" "<<test[1].size()<<" "<<test[2].size() << " " << test[3].size() << " "<< test[4].size()<<std::endl;
//  
// for(int m=0;m<test[0].size();m++)
// {
//  std::cout<< test[0].at(m) << " - "<<test[1].at(m)<< " and " <<test[2].at(m) << " - "<<test[3].at(m)<<" value " << test[4].at(m)<<std::endl; 
// }
 
 vector<vector<double> > muonEff = MakeListOfWeights(GetEfficiencies(hWMu_rec,hWMu_genWithVeto),BinsX,BinsY);
 vector<vector<double> > electronEff = MakeListOfWeights(GetEfficiencies(hWEl_rec,hWEl_genWithVeto),BinsX,BinsY);
 vector<vector<double> >  hadronEff = MakeListOfWeights(GetEfficiencies(hW_had_rec,hW_had_genWithVeto),BinsX,BinsY);
 double LLVEff = (LLVmuons[1] + LLVelectrons[1])/(LLVmuons[0]+LLVelectrons[0]);
 double BVEff = (BVmuons[1] + BVelectrons[1])/(BVmuons[0]+BVelectrons[0]);
 
 
 MyClass* t12 = new MyClass(tree);
 
vector<double> testMuon = testSelfConsistency(13,t12,muonEff,hadronEff,BVEff,LLVEff);
vector<double> testElectron = testSelfConsistency(11,t12,electronEff,hadronEff,BVEff,LLVEff);

std::cout << (testMuon[0]+testElectron[0])/(testMuon[1] + testElectron[1])<<std::endl; 
 
}

