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
#include "/usr/users/dschaefer/root/headerfiles/MyClass.h"
#include "/usr/users/dschaefer/root/headerfiles/passed_mu_jes.h"
#include "/usr/users/dschaefer/root/headerfiles/Op.h"
#include "/usr/users/dschaefer/root/headerfiles/EventSelection.h"
#include "/usr/users/dschaefer/root/headerfiles/GenFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/RecFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc2.h"
using namespace std;


namespace{
  int loadMyLibraryTriggerFunc(){
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/Op.cc");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/EventSelection.cc");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/GenFunc.cc");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/RecFunc.cc");
     gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc2.cc");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C");

 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}


void narrowShapes(string channel, string category, float mass)
{
//   float mass = 800;
//   string channel = "el";
//   string category = "HPZ";
 string inputTreeName = "/home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/AnaSigTree_25ns/"+channel+"/treeEDBR_BulkG_WW_lvjj_M"+std::to_string(int(mass))+"_xww.root"; 
 string outputFileName = "/usr/users/dschaefer/root/code/debugging/hMWW_"+std::to_string(int(mass))+"_"+channel+"_"+category+".root";
 
 TChain tree("tree");
 tree.Add(inputTreeName.c_str());
 
 passed_mu_jes* t = new passed_mu_jes(&tree);
 
 bool isHP=1;
 bool isLP=0;
 bool isW =1;
 bool isZ=1;
 
 if(category.find("LP") !=string::npos)
 {
   isLP=1;
   isHP=0;
 }
 if(category.find("W") !=string::npos)
 {
   
  isZ=0; 
 }
 if(category.find("Z")!=string::npos)
 {
   isW =0;
 }
 std::cout << " HP: "<<isHP <<" LP : "<<isLP <<" W : "<<isW <<" Z : "<<isZ<<std::endl;
 TH1F* hMWW = new TH1F("hMWW","hMWW",100,400,5000);
 TFile* foutput = new TFile(outputFileName.c_str(),"RECREATE");
 
  for(int i=0;i<t->fChain->GetEntries();i++)
  {
   t->GetEntry(i);
   double tau21 = t->tau21;
   //std::cout<<tau21 <<std::endl;
   double jet_mass = t->Mjpruned;
   double Mass = t->MWW;
   if(isHP and !isLP)
   {
     if(tau21>= 0.6) continue;
   }
   if(!isHP and isLP)
   {
     if(tau21<= 0.6 and tau21>=0.75)
     {
      continue;
     }
   }
   if(isW and !isZ)
   {
    if(jet_mass >= 85 and jet_mass <=65)
    {
     continue; 
    }
   }
   if(!isW and isZ)
   {
    if(jet_mass >= 105 and jet_mass <=85)
    {
     continue; 
    }
   }
  if(isW and isZ)
   {
    if(jet_mass >= 105 and jet_mass <=65)
    {
     continue; 
    }
   }
   hMWW->Fill(Mass);
  }
  hMWW->Write();
}