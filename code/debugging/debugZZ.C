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
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/GenParticle.cc+");
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

void debugZZ()
{
  TChain tree("tree/treeMaker");
  tree.Add(input_filename);
  
  ZZtree* t = new ZZtree(&tree);
  for(int loop=0;loop<100;loop++)
  {
  t->GetEntry(loop);
 
 /* Muon* particle = new Muon(t);
  printParticleInfo(particle,t);
 
 delete particle;
 vector<vector<int> > candidateList = leptonCandidates(t);
 vector<int> electronCandidates = candidateList[0];
 vector<int> muonCandidates = candidateList[1];
 
 Muon* cand1 = new Muon(t);
 Muon* cand2 = new Muon(t);
 if(muonCandidates.size()>=2)
 {
 cand1->Init(muonCandidates[0],t);
 cand2->Init(muonCandidates[1],t);
 std::cout <<" has uncharged Pair " << isUnchargedPair(cand1,cand2) << std::endl;
 }
 
 vector<int> rightPair = leptonPair(cand1,cand2,candidateList,t);
 std::cout << " lenght " << rightPair.size() << " lepton indices " << rightPair[0] <<" "<< rightPair[1] << std::endl;
 TLorentzVector Z_lep = reconstructLeptonicZ(13,rightPair,t);
 TLorentzVector Z_lep2 = reconstructLeptonicZ(13,t);
  std::cout <<" Z_lep mass : " <<Z_lep.M() << " " << Z_lep2.M() << std::endl;
 
 for(int i=0;i<muonCandidates.size();i++)
 {
   std::cout <<  muonCandidates.at(i) << "  ";
 }
 std::cout << std::endl;
 delete cand1;
 delete cand2;
 */
 GenParticle* generatedParticle = new GenParticle(t);
 std::cout<<" nGenPar "<< generatedParticle->Get_IndexMax()<< " "<< t->nGenPar <<std::endl;
 for(int i=0;i< t->nGenPar-1;i++)
 {
   generatedParticle->Init(i,t);
  std::cout << i << "  "<< generatedParticle->Get_Index();
  generatedParticle->Print();
  
 }
 delete generatedParticle;
 
 }
  
  
}



