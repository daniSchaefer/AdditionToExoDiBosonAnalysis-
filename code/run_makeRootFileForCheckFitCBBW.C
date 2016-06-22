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
#include "/usr/users/dschaefer/root/headerfiles/MyClass.h"
#include "/usr/users/dschaefer/root/headerfiles/passed_mu_jes.h"
#include "/usr/users/dschaefer/root/headerfiles/Op.h"
#include "/usr/users/dschaefer/root/headerfiles/EventSelection.h"
#include "/usr/users/dschaefer/root/headerfiles/GenFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/RecFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc2.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"

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
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.cc+");


 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

// root -b -q 'run_makeRootFileForCheckFitCBBW.C("Wprime","had","HP","WZ_jjjj",3000)'

void run_makeRootFileForCheckFitCBBW(string ModelName,string channel, string category,string decayMode,float mass, bool isNarrow=0)
{
  if(isNarrow)
  {
      makeRootFileForCheckFitCBBW(ModelName,channel,category,decayMode,mass,0.0);
  }
  else
  {
      makeRootFileForCheckFitCBBW(ModelName,channel,category,decayMode,mass,0.1);
      makeRootFileForCheckFitCBBW(ModelName,channel,category,decayMode,mass,0.2);
      makeRootFileForCheckFitCBBW(ModelName,channel,category,decayMode,mass,0.3);
  }
}

