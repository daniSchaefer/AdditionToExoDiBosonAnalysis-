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

using namespace std;

 const char* BG_600 = "/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph.root";
 const char* BG_2000 ="/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-2000_13TeV-madgraph.root";
 const char* BG_800 ="/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-800_13TeV-madgraph.root";
 const char* BG_1000 ="/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-1000_13TeV-madgraph.root";
 const char* BG_1200 ="/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-1200_13TeV-madgraph.root";
 const char* BG_1400 ="/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-1400_13TeV-madgraph.root";
 const char* BG_1600 ="/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-1600_13TeV-madgraph.root";
 const char* BG_1800 ="/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-1800_13TeV-madgraph.root";
 const char* BG_3500 ="/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph.root";
 const char* BG_4000 ="/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-4000_13TeV-madgraph.root";
 const char* BG_4500 ="/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-4500_13TeV-madgraph.root";
 
 
namespace{
  int loadMyLibraryTriggerFunc(){
  
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/ZZtree.C+");
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

void ZEfficiency(int pdgId)
{
  TChain treeChain("tree/treeMaker");

  treeChain.Add(BG_600);
  treeChain.Add(BG_800);
  treeChain.Add(BG_1000);
  treeChain.Add(BG_1200);
  treeChain.Add(BG_1400);
  treeChain.Add(BG_1600);
  treeChain.Add(BG_1800);
  treeChain.Add(BG_2000);
     treeChain.Add(BG_3500);
  treeChain.Add(BG_4000);
  treeChain.Add(BG_4500);
  
  ZZtree* tree = new ZZtree(&treeChain);
  
  const char* output_filename;
  if(pdgId ==11)
  { output_filename = "/storage/jbod/dschaefer/EfficiencyHistos/ZKinematicsEl.root";}
  if(pdgId ==13)
  {output_filename = "/storage/jbod/dschaefer/EfficiencyHistos/ZKinematicsMu.root";}
  
  TFile ZKinematics(output_filename,"RECREATE");
  
  int nBinsX =17;
  int nBinsY =10;
  const Float_t BinsX[17]={0,80,200,250,300,400,500,600,700,800,1000,1200,1500,2000,2500,3000,4000};
  const Float_t BinsY[10]={0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};
 
  TH2F* hZ_lep_rec = new TH2F("hZ_lep_rec","Z #rightarrow l #nu_{l}",(nBinsX-1), BinsX,(nBinsY-1), BinsY);
  TH2F* hZ_lep_gen = new TH2F("hZ_lep_gen","Z #rightarrow l #nu_{l}",(nBinsX-1), BinsX,(nBinsY-1), BinsY);
  
  
  
  TH2F* hZ_had_rec = new TH2F("hZ_had_rec","Z #rightarrow q q'",(nBinsX-1), BinsX,(nBinsY-1), BinsY);
  TH2F* hZ_had_gen = new TH2F("hZ_had_gen","Z #rightarrow q q'",(nBinsX-1), BinsX,(nBinsY-1), BinsY);
  

  bool isHP =1;
  bool isLP =0;
 
  TLorentzVector Z_lep_gen;
  TLorentzVector Z_had_gen;
  vector<vector<int> > lept;
  
  int NumberOfPassedEventsLep=0;
  int NumberOfPassedEventsHad=0;
  int NumberOfPassedEventsAll=0;
  
  
  int howmany = tree->fChain->GetEntries();
  std::cout<< howmany<< " events are beeing processed "<<std::endl;
  for(int i=0;i<howmany;i++)
  {
  tree->GetEntry(i);
  if(!hasGenLepton(pdgId,tree)) continue;
  if(!hasGenHadron(tree)) continue;
  Z_had_gen = GetGeneratedZOrW(tree);
  Z_lep_gen = GetGeneratedZ(tree,0);
  if(!isLeptonicZ(Z_lep_gen)) continue;
  if(!isHadronicZ(Z_had_gen)) continue;
  if(!GravitonSelection(Z_had_gen, Z_lep_gen)) continue;
 
  
  hZ_had_gen->Fill(Z_had_gen.Pt(),Z_had_gen.Eta());
  hZ_lep_gen->Fill(Z_lep_gen.Pt(),Z_lep_gen.Eta());
  
  
 //if(!passedTrigger(pdgId,tree)) continue;
 //if(!LeptonSelection(pdgId,tree)) continue;
  
  lept = GetIndicesLeptonPairs(tree);
  if(passedTrigger(pdgId,tree) and LeptonSelection(pdgId,tree))
  {
  
 hZ_lep_rec->Fill(Z_lep_gen.Pt(),Z_lep_gen.Eta());
  NumberOfPassedEventsLep +=1;
  }
  
  if(!HadronSelection(lept,tree, isHP, isLP)) continue;
 
  hZ_had_rec->Fill(Z_had_gen.Pt(),Z_had_gen.Eta());
  NumberOfPassedEventsHad +=1;
  
  if(!passedTrigger(pdgId,tree)) continue;
  if(!LeptonSelection(pdgId,tree)) continue;
  NumberOfPassedEventsAll +=1;
       
  }
  
  std::cout << " # events that passed lepton selection crit. " << NumberOfPassedEventsLep << std::endl;
  std::cout << " # events that passed hadron selection crit. " << NumberOfPassedEventsHad <<std::endl;
  std::cout << " # events that passed all selections crit. " << NumberOfPassedEventsAll <<std::endl;
 
 
  hZ_had_gen->Write();
  hZ_had_rec->Write();
  hZ_lep_rec->Write();
  hZ_lep_gen->Write();
  
}