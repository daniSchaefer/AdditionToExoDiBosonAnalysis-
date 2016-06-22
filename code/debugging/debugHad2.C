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

void debugHad2()
{
  string filename = "/storage/jbod/dschaefer/Res_Sig/EXOVVTree_BulkGravToWW_narrow_M-1800_13TeV-madgraph_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_1.root";
   //string filename = "/storage/jbod/dschaefer/Res_Sig/BulkGravToWWToWlepWhad_narrow_M-1000/EXOVVTree_BulkGravToWWToWlepWhad_narrow_M-1000_1.root";
  
  TChain tree("ntuplizer/tree");
  tree.Add(filename.c_str());
  
  MyClass* t12 = new MyClass(&tree);
  
  ifstream mE("missingEvents.txt");
  vector<int> missingEvents = GetEventsFromFile(mE);
  ifstream tE("toomanyEvents.txt");
  vector<int> toomanyEvents = GetEventsFromFile(tE);
  
 ofstream debugfilemE;
 debugfilemE.open("debug_mE.txt",ios::ate);
 ofstream debugfiletE;
 debugfiletE.open("debug_tE.txt",ios::ate);
 
 int howmany = t12->fChain->GetEntries();
 
 for(int i=0;i<howmany;i++)
  {
    t12->fChain->GetEntry(i);
     for(int loop =0; loop<missingEvents.size();loop++)
    {
    printInfoEventHadronic(missingEvents.at(loop),t12,debugfilemE);
    }
     for(int loop =0; loop<toomanyEvents.size();loop++)
    {
    printInfoEventHadronic(toomanyEvents.at(loop),t12,debugfiletE);
    }
    
  }
}





























  