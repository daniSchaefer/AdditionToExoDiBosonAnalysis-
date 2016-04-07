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
#include "/usr/users/dschaefer/root/headerfiles/Op.h"
#include "/usr/users/dschaefer/root/headerfiles/EventSelection.h"
#include "/usr/users/dschaefer/root/headerfiles/GenFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/RecFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"

namespace{
  int loadMyLibraryTriggerFunc(){
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/General.cc+"); 
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/Op.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/EventSelection.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/GenFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/RecFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.cc+");


 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void run_makeRootFileForCheckFitCBBW(string category)
{
  const char* channel = "mu";
  //string category = "HP";
  for(int i=0;i<2;i++)
  {
    if(i==0) {channel="el";}
    else {channel = "mu";}
    
   vector<string> model_narrow = {"BulkGrav","Wprime","Zprime"};
   vector<float> mass_narrow = {800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
   for(int i=0;i<model_narrow.size();i++)
   {
      std::cout << model_narrow.at(i) << std::endl;
      for(int m=0;m<mass_narrow.size();m++)
      {
      makeRootFileForCheckFitCBBW(model_narrow.at(i),channel,category,mass_narrow.at(m),0.0);
      } 
    }
  
    vector<string> model = {"Radion","RSGrav","Wprime","Zprime"};
    vector<float> mass = {800,1200,2000,3000,4000};
    for(int m=0;m<mass.size();m++)
    {
      for(int i=0;i<model.size();i++)
      {
      makeRootFileForCheckFitCBBW(model.at(i),channel,category,mass.at(m),0.1);
      makeRootFileForCheckFitCBBW(model.at(i),channel,category,mass.at(m),0.2);
      makeRootFileForCheckFitCBBW(model.at(i),channel,category,mass.at(m),0.3);
      }
    }       
  }
  
}

