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
#include "/usr/users/dschaefer/root/headerfilesZZ/ZZtree.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/GenParticle.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/RecParticle.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/GenParticle.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/Electron.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/Muon.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/ReconstructLeptonicZ.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/Jet.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/FatJet.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/ReconstructHadronicZ.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/EventSelectionZZ.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/DebugFuncZZ.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"

using namespace std;

namespace{
  int loadMyLibraryTriggerFunc(){
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/ZZtree.C+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
       gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/RecParticle.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/GenParticle.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/Electron.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/Muon.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/Jet.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/FatJet.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/ReconstructLeptonicZ.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/ReconstructHadronicZ.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/EventSelectionZZ.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/DebugFuncZZ.cc+");
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

TFile * electronChannel = new TFile("/storage/jbod/dschaefer/EfficiencyHistos/ZKinematicsEl.root","READ");
TFile * muonChannel = new TFile("/storage/jbod/dschaefer/EfficiencyHistos/ZKinematicsMu.root","READ");

const char* input_filename = "/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph.root";

TFile *gendata = new TFile(input_filename,"READ");
TTree *t800 = (TTree*) gendata->Get("tree/treeMaker");

void get2DEffZ()
{

 TH2F* hZ_el_rec 	= (TH2F*) electronChannel->Get("hZ_lep_rec");
 TH2F* hZ_mu_rec	= (TH2F*) muonChannel->Get("hZ_lep_rec");
 TH2F* hZ_mu_gen	= (TH2F*) muonChannel->Get("hZ_lep_gen");
 TH2F* hZ_el_gen 	= (TH2F*) electronChannel->Get("hZ_lep_gen");
 TH2F* hZ_had_rec1	= (TH2F*) muonChannel->Get("hZ_had_rec");
 TH2F* hZ_had_gen1	= (TH2F*) muonChannel->Get("hZ_had_gen");
 TH2F* hZ_had_rec2	= (TH2F*) electronChannel->Get("hZ_had_rec");
 TH2F* hZ_had_gen2	= (TH2F*) electronChannel->Get("hZ_had_gen");

 TH2F* hZ_had_gen = new TH2F(*hZ_had_gen1);
 TH2F* hZ_had_rec = new TH2F(*hZ_had_rec1);
 
 hZ_had_gen->Add(hZ_had_gen2);
 hZ_had_rec->Add(hZ_had_rec2);
 
  int nBinsX =17;
  int nBinsY =10;
  vector<double> BinsX ={0,80,200,250,300,400,500,600,700,800,1000,1200,1500,2000,2500,3000,4000};
  vector<double> BinsY ={0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};
 
 //efficiencies like in the sqrt(8) cms paper:
 //generated events kinematic cuts and vetos applied
 //reconstructed events also with all vetos and kin. cuts
 
 
 TH2* muEff = GetEfficiencies(hZ_mu_rec, hZ_mu_gen);
 TH2* elEff = GetEfficiencies(hZ_el_rec, hZ_el_gen);
 TH2* hadEff = GetEfficiencies(hZ_had_rec, hZ_had_gen);

 TH2* hadEffmu = GetEfficiencies(hZ_had_rec1,hZ_had_gen1);
 TH2* hadEffel = GetEfficiencies(hZ_had_rec2,hZ_had_gen2);

PrintBinContents(muEff,BinsX,BinsY,"Z $\\rightarrow  \\mu \\mu $  efficiency"); 
PrintBinContents(elEff,BinsX,BinsY,"Z $\\rightarrow$ e e efficiency"); 
PrintBinContents(hadEff,BinsX,BinsY,"Z $\\rightarrow q  \\bar{q}$ efficiency");
PrintBinContents(hadEffmu,BinsX,BinsY,"Z $\\rightarrow q  \\bar{q}$ efficiency, mu channel");
PrintBinContents(hadEffel,BinsX,BinsY,"Z $\\rightarrow q  \\bar{q}$ efficiency, el channel");

vector<vector<double> > Wel = MakeListOfWeights(elEff,BinsX,BinsY);
vector<vector<double> > Wmu = MakeListOfWeights(muEff,BinsX,BinsY);
vector<vector<double> > Whad= MakeListOfWeights(hadEff,BinsX,BinsY);

vector<vector<double> > WhadMu= MakeListOfWeights(hadEffmu,BinsX,BinsY);
vector<vector<double> > WhadEl= MakeListOfWeights(hadEffel,BinsX,BinsY);

//ZZtree* tree = new ZZtree(t800);

//vector<double> testElectron 	= testSelfConsistency(11,tree,Wel,Whad,1,0);
//vector<double> testMuon 	= testSelfConsistency(13,tree,Wmu,Whad,1,0);



//std::cout << (testMuon[0]+testElectron[0])/(testMuon[1] + testElectron[1])<<std::endl; 



//==========================print stuff on canvas=============================================
const char* title = "work in progress      #sqrt{s} = 13 TeV";

TCanvas *c1 = new TCanvas("c1","Z #rightarrow #mu #mu",400,400);
const char* channelZToMuMu = "Z #rightarrow #mu #mu";
SetStyleEffPlots(muEff,c1,title,channelZToMuMu," ",2500);

 TCanvas *c2 = new TCanvas("c2","Z #rightarrow e e ",400,400);
 const char* channelZToElEl = "Z #rightarrow e e ";
 SetStyleEffPlots(elEff,c2,title, channelZToElEl," ",2500);
 
 TCanvas *c3 = new TCanvas("c3","Z #rightarrow q #bar{q}",400,400);
 const char* channelZToHad = "Z #rightarrow q #bar{q}";
 SetStyleEffPlots(hadEff,c3,title,channelZToHad," ",2500);
 
 
 TCanvas *c4 = new TCanvas("c4","Z #rightarrow q #bar{q}, only muon channel",400,400);
 c4->cd();
 gPad->SetRightMargin(0.15);
 TCanvas *c5 = new TCanvas("c5","Z #rightarrow q #bar{q}, only electron channel",400,400);
 c5->cd();
 gPad->SetRightMargin(0.15);

 c4->cd();
 hadEffmu->Draw("COLZ");
 c5->cd();
 hadEffel->Draw("COLZ");
 
 
  c1->SaveAs("/usr/users/dschaefer/root/results/Efficiency/plots/BulkGToZZ_MuEff_all.pdf");
  c2->SaveAs("/usr/users/dschaefer/root/results/Efficiency/plots/BulkGToZZ_ElEff_all.pdf");
  c3->SaveAs("/usr/users/dschaefer/root/results/Efficiency/plots/BulkGToZZ_HadEff_all.pdf");
}