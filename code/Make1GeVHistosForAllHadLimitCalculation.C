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

 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void Make1GeVHistosForAllHadLimitCalculation(string ModelName, float mass, float width)
{
  string decayMode = "WW_jjjj";
  string VV = determineVV(decayMode);
  string input_dir = "/storage/jbod/dschaefer/Res_Sig/";
  string output_dir = "/usr/users/dschaefer/root/results/misc/AllHadHistosForLimits/";
  
  string input_file = getFileName(input_dir, ModelName,decayMode,mass,width,1);
  string output_file = output_dir+ModelName+VV+"_13TeV_"+std::to_string(int(mass))+"GeV_width0p"+std::to_string(int(width*100))+".root";
  
  
  TFile file(output_file.c_str(),"RECREATE");
  
  
  TChain tree("ntuplizer/tree");
  tree.Add(input_file.c_str());
  
  MyClass* t12 = new MyClass(&tree);
  
  int howmany = t12->fChain->GetEntries();
  
  std::cout<< "we look at  "<< howmany<<" events " << std::endl;
  
  TH1F* DijetMassHighPuriVV = new TH1F("DijetMassHighPuriVV","DijetMassHighPuriVV",7000,0,7000);
  TH1F* DijetMassLowPuriVV = new TH1F("DijetMassLowPuriVV","DijetMassLowPuriVV",7000,0,7000);
  TH1F* DijetMassHighPuriWW = new TH1F("DijetMassHighPuriWW","DijetMassHighPuriWW",7000,0,7000);
  TH1F* DijetMassLowPuriWW = new TH1F("DijetMassLowPuriWW","DijetMassLowPuriWW",7000,0,7000);
  TH1F* DijetMassHighPuriWZ = new TH1F("DijetMassHighPuriWZ","DijetMassHighPuriWZ",7000,0,7000);
  TH1F* DijetMassLowPuriWZ = new TH1F("DijetMassLowPuriWZ","DijetMassLowPuriWZ",7000,0,7000);
  TH1F* DijetMassHighPuriZZ = new TH1F("DijetMassHighPuriZZ","DijetMassHighPuriZZ",7000,0,7000);
  TH1F* DijetMassLowPuriZZ = new TH1F("DijetMassLowPuriZZ","DijetMassLowPuriZZ",7000,0,7000);
  
  TLorentzVector jet1;
  TLorentzVector jet2;
  vector<int> cand;
  for(int i=0;i<howmany;i++)
  {
    t12->fChain->GetEntry(i);
    if(!genEventSelectionInclusive(t12,"jjjj"))
      continue;
    if(!applyTriggerAllHadronic(t12))
      continue;
    if(!passedAllHadronicSelections(t12))
      continue;
    
     jet1 = reconstructV1(t12);
     jet2 = reconstructV2(t12);
    
    if(passedSubstructureSelection(t12,"WW_HP"))
      DijetMassHighPuriWW->Fill((jet1+jet2).M());
    if(passedSubstructureSelection(t12,"WW_LP"))
      DijetMassLowPuriWW->Fill((jet1+jet2).M());
    if(passedSubstructureSelection(t12,"WZ_HP"))
      DijetMassHighPuriWZ->Fill((jet1+jet2).M());
    if(passedSubstructureSelection(t12,"WZ_LP"))
      DijetMassLowPuriWZ->Fill((jet1+jet2).M());
    if(passedSubstructureSelection(t12,"ZZ_HP"))
      DijetMassHighPuriZZ->Fill((jet1+jet2).M());
    if(passedSubstructureSelection(t12,"ZZ_LP"))
      DijetMassLowPuriZZ->Fill((jet1+jet2).M());
    if(passedSubstructureSelection(t12,"VV_HP"))
      DijetMassHighPuriVV->Fill((jet1+jet2).M());
    if(passedSubstructureSelection(t12,"VV_LP"))
      DijetMassLowPuriVV->Fill((jet1+jet2).M());
  }
  
  DijetMassHighPuriVV->Sumw2();
  DijetMassHighPuriWW->Sumw2();
  DijetMassHighPuriZZ->Sumw2();
  DijetMassHighPuriWZ->Sumw2();
  
  DijetMassLowPuriVV->Sumw2();
  DijetMassLowPuriWW->Sumw2();
  DijetMassLowPuriZZ->Sumw2();
  DijetMassLowPuriWZ->Sumw2();
  
  
  DijetMassHighPuriVV->Scale(1/DijetMassHighPuriVV->GetEntries());
  DijetMassHighPuriWW->Scale(1/DijetMassHighPuriWW->GetEntries());
  DijetMassHighPuriZZ->Scale(1/DijetMassHighPuriZZ->GetEntries());
  DijetMassHighPuriWZ->Scale(1/DijetMassHighPuriWZ->GetEntries());
  
  DijetMassLowPuriVV->Scale(1/DijetMassLowPuriVV->GetEntries());
  DijetMassLowPuriWW->Scale(1/DijetMassLowPuriWW->GetEntries());
  DijetMassLowPuriZZ->Scale(1/DijetMassLowPuriZZ->GetEntries());
  DijetMassLowPuriWZ->Scale(1/DijetMassLowPuriWZ->GetEntries());
  
  
  
  DijetMassHighPuriVV->Write();
  DijetMassHighPuriWW->Write();
  DijetMassHighPuriWZ->Write();
  DijetMassHighPuriZZ->Write();
  DijetMassLowPuriVV->Write();
  DijetMassLowPuriWW->Write();
  DijetMassLowPuriWZ->Write();
  DijetMassLowPuriZZ->Write();
   
}