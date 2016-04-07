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
 

 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void debugHad()
{
  string filename = "/storage/jbod/dschaefer/Res_Sig/EXOVVTree_BulkGravToWW_narrow_M-1800_13TeV-madgraph_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_1.root";
   //string filename = "/storage/jbod/dschaefer/Res_Sig/BulkGravToWWToWlepWhad_narrow_M-1000/EXOVVTree_BulkGravToWWToWlepWhad_narrow_M-1000_1.root";
  
  TChain tree("ntuplizer/tree");
  tree.Add(filename.c_str());
  
  MyClass* t12 = new MyClass(&tree);
  
  int numberHad =0;
  int numberHadPreselection=0;
  int numberHadTrigger =0;
  int numberHadDetajj=0;
  int numberHadMjj=0;
  int numberHadPrunedMassCut=0;
  int howmany = t12->fChain->GetEntries();
  //int howmany = 100;
  std::cout<< "# events overall "<< howmany << std::endl;
  for(int i=0;i<howmany;i++)
  {
    t12->fChain->GetEntry(i);
   // get_pdgId("test.txt",t12);
   // if(!genEventSelectionInclusive(t12,"jjjj"))
     // continue;
    numberHad +=1;
    // if(!applyTriggerAllHadronic(t12))
      // continue;
       numberHadTrigger +=1;
       vector<int> indices = hadronicJetCandidates(t12);
      // std::cout <<indices[0] << " "<<indices[1] << std::endl;
     if(indices[0]==-99)
       continue;
      numberHadPreselection+=1;
     if(!AllHadPassedDEtajj(t12,indices))
       continue;
     numberHadDetajj+=1;
      if(!AllHadPassedMjj(t12,indices))
       continue;
     numberHadMjj+=1;
     if(!AllHadPassedPrunedMassCut(t12,indices))
       continue;
     numberHadPrunedMassCut+=1;
     
  
  }
  std::cout<< "number after generated hadronic selections "<< numberHad <<std::endl;
  std::cout << "number after Triggers applied " << numberHadTrigger <<std::endl;
  std::cout << "number after preselections " << numberHadPreselection <<std::endl;
  std::cout << "number after Delta Eta_jj " << numberHadDetajj <<std::endl;
  std::cout << "number after Mjj " << numberHadMjj <<std::endl;
  std::cout << "number after pruned Mass cut " << numberHadPrunedMassCut <<std::endl;
}