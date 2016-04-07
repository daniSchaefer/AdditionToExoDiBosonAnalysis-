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
#include "/usr/users/dschaefer/root/headerfilesZZ/RecParticle.h"
 #include "/usr/users/dschaefer/root/headerfilesZZ/GenParticle.h"
 #include "/usr/users/dschaefer/root/headerfilesZZ/Electron.h"
 #include "/usr/users/dschaefer/root/headerfilesZZ/Muon.h"
 #include "/usr/users/dschaefer/root/headerfilesZZ/ReconstructLeptonicZ.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/Jet.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/FatJet.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/ReconstructHadronicZ.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/DebugFuncZZ.h"

const char* input_filename = 

"/usr/users/dschaefer/root/data/crab_BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph.root";

namespace{
  int loadMyLibraryTriggerFunc(){
  
   gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/ZZtree.C+");
   gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/RecParticle.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/Electron.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/Muon.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/Jet.cc+");
   gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/FatJet.cc+");
   gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/ReconstructLeptonicZ.cc+");
   gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/ReconstructHadronicZ.cc+");
   gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/DebugFuncZZ.cc+");
   
 return 0; 
}
int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void debugZZjets()
{
  TChain tree("tree/treeMaker");
  tree.Add(input_filename);
  
  ZZtree* t = new ZZtree(&tree);
  
  for(int loop=1;loop<100;loop++)
  {
  t->GetEntry(loop);
  printAllFatJetInfo(t);
  TLorentzVector Z_had = reconstructHadronicZ(GetIndicesLeptonPairs(t),t); 
  std::cout <<" Z_had passed Kin. : " << isHadronicZ(Z_had)<< " Z_had pt : "<< Z_had.Pt() << " Z_had mass : "<< Z_had.M()<<  std::endl;
  std::cout<< " ========================================================" <<std::endl;
  //reconstructHadronicZ(GetIndicesLeptonPairs(t),t);
  //std::cout<< " Z_had pt : "<< Z_had.Pt()<<std::endl;
  
  }
  
  
}