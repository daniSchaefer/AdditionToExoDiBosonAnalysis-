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
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies2.h"
//#include "/usr/users/dschaefer/root/headerfilesZZ/ZZtree.h"

using namespace std;


// note to this construct:
// is needed in this version of root in order to get the header functions right
//also the order in which these files are compiled matters!
namespace{
  int loadMyLibraryTriggerFunc(){
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/General.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C+");
 //gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/ZZtree.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/Op.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/EventSelection.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/GenFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/RecFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc2.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies2.cc+");
  


 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void run_testEfficiencies(string ModelName, string channel, string category,string decayMode,float mass,bool isNarrow =0)
{
    
  std::cout << channel << "  " << category << std::endl;
if(isNarrow)
{
  if(decayMode.find("lvjj")!=string::npos)
  {
      vector<double> vetoEff1= makeEfficiencyTest(ModelName,channel,category,decayMode,mass,0.0);
       std::cout << mass << " & "<< vetoEff1[0]  << " & " <<  vetoEff1[1] << " & "<<std::endl;
  }
  else 
  {
    makeEfficiencyTest(ModelName,channel,category,decayMode,mass,0.0);
  }
}
else
{
  makeEfficiencyTest(ModelName,channel,category,decayMode,mass,0.1);
  makeEfficiencyTest(ModelName,channel,category,decayMode,mass,0.2);
  makeEfficiencyTest(ModelName,channel,category,decayMode,mass,0.3);
}  
 
 /* 
   std::cout << channel << "  " << category << std::endl;
if(isNarrow)
{
  if(decayMode.find("lvjj")!=string::npos)
  {
      vector<double> vetoEff1= makeEfficiencyTestVersion2HAD(ModelName,channel,category,decayMode,mass,0.0);
       std::cout << mass << " & "<< vetoEff1[0]  << " & " <<  vetoEff1[1] << " & "<<std::endl;
  }
  else 
  {
    makeEfficiencyTestVersion2HAD(ModelName,channel,category,decayMode,mass,0.0);
  }
}
else
{
  makeEfficiencyTestVersion2HAD(ModelName,channel,category,decayMode,mass,0.1);
  makeEfficiencyTestVersion2HAD(ModelName,channel,category,decayMode,mass,0.2);
  makeEfficiencyTestVersion2HAD(ModelName,channel,category,decayMode,mass,0.3);
}  
   */
}