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
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies2.h"

using namespace std;


// note to this construct:
// is needed in this version of root in order to get the header functions right
//also the order in which these files are compiled matters!
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
  gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.cc+");
  gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies2.cc+");



 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void run_testEfficiencies(string channel, string category)
{
  //const char* channel = "mu";
  //string category = "HP";
  std::cout << channel << "  " << category << std::endl;
  vector<string> model_narrow = {"BulkGrav","Wprime","Zprime"};
  vector<float> mass_narrow = {800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
  for(int i=0;i<model_narrow.size();i++)
  {
    std::cout << model_narrow.at(i) << std::endl;
    for(int m=0;m<mass_narrow.size();m++)
    {
      vector<double> vetoEff1= makeEfficiencyTest(model_narrow.at(i),channel,category,mass_narrow.at(m),0.0);
      std::cout<<mass_narrow.at(m)<< " & " <<vetoEff1[0]  << " & " <<  vetoEff1[1] << " & "<<std::endl;
    }
  }
 

  
  
  vector<string> model = {"Radion","RSGrav","Wprime","Zprime"};
  vector<float> mass = {800,1200,2000,3000,4000};
  for(int m=0;m<mass.size();m++)
  {
  for(int i=0;i<model.size();i++)
  {
  makeEfficiencyTest(model.at(i),channel,category,mass.at(m),0.1);
  makeEfficiencyTest(model.at(i),channel,category,mass.at(m),0.2);
  makeEfficiencyTest(model.at(i),channel,category,mass.at(m),0.3);
  }
  }
   
}