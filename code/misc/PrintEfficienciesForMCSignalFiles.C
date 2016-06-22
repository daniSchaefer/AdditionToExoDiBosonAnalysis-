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
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"

using namespace std;

 

// note to this construct:
// is needed in this version of root in order to get the header functions right
//also the order in which these files are compiled matters!
namespace{
  int loadMyLibraryTriggerFunc(){
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/Op.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/EventSelection.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/GenFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/RecFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.cc+");
 
 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}
//_--------------------------------------------------------------------------
//---------------------main function-----------------------------------------

//approriate for ModelName:
// BulkG_WW
// WPrime_WZ
// WPrime_WV  oder WW ??
//oder BulkG_WZ ???
void PrintEfficienciesForMCSignalFiles(int pdgId,string ModelName)
{
  
    ofstream f;
    string directory = "/storage/jbod/dschaefer/";
    string file = " ";
    if(ModelName.find("BulkG") != string::npos)
    {
      file = directory+"/BulkGravToWWToWlepWhad_narrow_M/EXOVVTree_BulkGravToWWToWlepWhad_narrow_M_";
    }
    if(pdgId ==11)
    {
    f.open("results/"+ModelName+"_el.txt",ios::ate);
    }
    else
    {
      f.open("results/"+ModelName+"_mu.txt",ios::ate);
    }
     
    vector<float> masses = {800,1200,1400,1600,1800,2000,2500,3000,3500,4500};
    for(int i =0;i<masses.size();i++)
    {
     string fileName = file;
     std::ostringstream ss;
     ss << masses[i];
     std::string mass(ss.str());
   
     fileName = fileName+mass+"_1.root";
     std::cout<< fileName << std::endl;
     
     const char* fN = fileName.c_str();
     WEfficiencyGetMCEffperSample(pdgId,fN,f);
     
     
     
    }
     
    f.close();

}

