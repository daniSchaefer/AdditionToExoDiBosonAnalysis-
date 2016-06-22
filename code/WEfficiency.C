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
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
#include "/usr/users/dschaefer/root/headerfiles/WWConstants.h"
#include "/usr/users/dschaefer/root/headerfiles/AllHadronicConstants.h"

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
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc2.cc+");
 //gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc++");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.cc+");
 
 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}
//_--------------------------------------------------------------------------
//---------------------main function-----------------------------------------


void WEfficiency(string channel, string ModelName, string category,string decayMode ="WW_lvjj")
{
  
  bool isHP=1;
  bool isLP=0;
  bool useWRegion=1;
  bool useZRegion=1;
  
  
  if(category.find("LP")!=string::npos)
  {
    isLP =1;
    isHP =0;
  }
  if(category.find("W") !=string::npos)
  {
    useZRegion=0;
  }
  if(category.find("Z") !=string::npos)
  {
   useWRegion=0; 
  }
  int pdgId=0;
  
  if(channel.find("el")!=string::npos)
  {
    pdgId =11;
  }
   if(channel.find("mu")!=string::npos)
  {
    pdgId =13;
  }
   if(channel.find("had")!=string::npos)
  {
    pdgId =1;
  }
  
    TChain tree("ntuplizer/tree");
   //string dir = "/storage/a/mmozer/Res_Sig/";
  // string dir = "/storage/jbod/dschaefer/Res_Sig/";
   string dir = "/storage/jbod/dschaefer/Res_Sig/finalTreesSemilep/";
   string outputDir = "/storage/jbod/dschaefer/EfficiencyHistos/";
   string VV = determineVV(decayMode);
   string mode = determineSemilepHadOrLep(decayMode);
   
   outputDir=outputDir+mode+"/To"+VV+"/";
   
   string Sfilename = outputDir+ModelName+"To"+VV+"Kinematics_"+channel+"_"+category+".root";
   
   
   const char* filename = Sfilename.c_str();

    string  SfM800w0p0_1 = (getFileName(dir ,ModelName,decayMode,800,0.0,1));
    string  SfM1000w0p0_1 = getFileName(dir ,ModelName,decayMode,1000,0.0,1);
    string  SfM1200w0p0_1 = getFileName(dir ,ModelName,decayMode,1200,0.0,1);
    string  SfM1400w0p0_1 = getFileName(dir ,ModelName,decayMode,1400,0.0,1);
    string  SfM1600w0p0_1 = getFileName(dir ,ModelName,decayMode,1600,0.0,1);
    string  SfM1800w0p0_1 = getFileName(dir ,ModelName,decayMode,1800,0.0,1);
    string  SfM2000w0p0_1 = getFileName(dir ,ModelName,decayMode,2000,0.0,1);
    string  SfM2500w0p0_1 = getFileName(dir ,ModelName,decayMode,2500,0.0,1);
    string  SfM3000w0p0_1 = getFileName(dir ,ModelName,decayMode,3000,0.0,1);
    string  SfM3500w0p0_1 = getFileName(dir ,ModelName,decayMode,3500,0.0,1);
    string  SfM4000w0p0_1 = getFileName(dir ,ModelName,decayMode,4000,0.0,1);
    string  SfM4500w0p0_1 = getFileName(dir ,ModelName,decayMode,4500,0.0,1);
    
      std::cout << SfM800w0p0_1  <<std::endl;
      std::cout << SfM1000w0p0_1 <<std::endl;
      std::cout << SfM1200w0p0_1 <<std::endl;
      std::cout << SfM1400w0p0_1 <<std::endl;
      std::cout << SfM1600w0p0_1 <<std::endl;
      std::cout << SfM1800w0p0_1 <<std::endl;
      std::cout << SfM2000w0p0_1 <<std::endl;
      std::cout << SfM2500w0p0_1 <<std::endl;
      std::cout << SfM3000w0p0_1 <<std::endl;
      std::cout << SfM3500w0p0_1 <<std::endl;
      std::cout << SfM4000w0p0_1 <<std::endl;
      std::cout << SfM4500w0p0_1 <<std::endl;
    
    const char* fM800w0p0_1 =   SfM800w0p0_1.c_str();
    const char* fM1000w0p0_1 =  SfM1000w0p0_1.c_str();
    const char* fM1200w0p0_1 =  SfM1200w0p0_1.c_str();
    const char* fM1400w0p0_1 =  SfM1400w0p0_1.c_str();
    const char* fM1600w0p0_1 =  SfM1600w0p0_1.c_str();
    const char* fM1800w0p0_1 =  SfM1800w0p0_1.c_str();
    const char* fM2000w0p0_1 =  SfM2000w0p0_1.c_str();
    const char* fM2500w0p0_1 =  SfM2500w0p0_1.c_str();
    const char* fM3000w0p0_1 =  SfM3000w0p0_1.c_str();
    const char* fM3500w0p0_1 =  SfM3500w0p0_1.c_str();
    const char* fM4000w0p0_1 =  SfM4000w0p0_1.c_str();
    const char* fM4500w0p0_1 =  SfM4500w0p0_1.c_str();
    
    
    
    string  SfM800w0p1_1 = getFileName(dir  ,ModelName,decayMode,800,0.1,1);
    string  SfM1200w0p1_1 = getFileName(dir ,ModelName,decayMode,1200,0.1,1);
    string  SfM2000w0p1_1 = getFileName(dir ,ModelName,decayMode,2000,0.1,1);
    string  SfM3000w0p1_1 = getFileName(dir ,ModelName,decayMode,3000,0.1,1);
    string  SfM4000w0p1_1 = getFileName(dir ,ModelName,decayMode,4000,0.1,1);
    string  SfM800w0p1_2 = getFileName(dir  ,ModelName,decayMode,800,0.1,2);
    string  SfM1200w0p1_2 = getFileName(dir ,ModelName,decayMode,1200,0.1,2);
    string  SfM2000w0p1_2 = getFileName(dir ,ModelName,decayMode,2000,0.1,2);
    string  SfM3000w0p1_2 = getFileName(dir ,ModelName,decayMode,3000,0.1,2);
    string  SfM4000w0p1_2 = getFileName(dir ,ModelName,decayMode,4000,0.1,2);
    string  SfM800w0p1_3 = getFileName(dir  ,ModelName,decayMode,800,0.1,3);
    string  SfM1200w0p1_3 = getFileName(dir ,ModelName,decayMode,1200,0.1,3);
    string  SfM2000w0p1_3 = getFileName(dir ,ModelName,decayMode,2000,0.1,3);
    string  SfM3000w0p1_3 = getFileName(dir ,ModelName,decayMode,3000,0.1,3);
    string  SfM4000w0p1_3 = getFileName(dir ,ModelName,decayMode,4000,0.1,3);
    
    const char* fM800w0p1_1  =   SfM800w0p1_1.c_str();
    const char* fM1200w0p1_1 =   SfM1200w0p1_1.c_str();
    const char* fM2000w0p1_1 =   SfM2000w0p1_1.c_str();
    const char* fM3000w0p1_1 =   SfM3000w0p1_1.c_str();
    const char* fM4000w0p1_1 =   SfM4000w0p1_1.c_str();
    const char* fM800w0p1_2  =   SfM800w0p1_2.c_str();
    const char* fM1200w0p1_2 =   SfM1200w0p1_2.c_str();
    const char* fM2000w0p1_2 =   SfM2000w0p1_2.c_str();
    const char* fM3000w0p1_2 =   SfM3000w0p1_2.c_str();
    const char* fM4000w0p1_2 =   SfM4000w0p1_2.c_str();
    const char* fM800w0p1_3  =   SfM800w0p1_3.c_str();
    const char* fM1200w0p1_3 =   SfM1200w0p1_3.c_str();
    const char* fM2000w0p1_3 =   SfM2000w0p1_3.c_str();
    const char* fM3000w0p1_3 =   SfM3000w0p1_3.c_str();
    const char* fM4000w0p1_3 =   SfM4000w0p1_3.c_str();
    
    
    string SfM800w0p2_1 = getFileName(dir  ,ModelName,decayMode,800,0.2,1);
    string SfM1200w0p2_1 = getFileName(dir ,ModelName,decayMode,1200,0.2,1);
    string SfM2000w0p2_1 = getFileName(dir ,ModelName,decayMode,2000,0.2,1);
    string SfM3000w0p2_1 = getFileName(dir ,ModelName,decayMode,3000,0.2,1);
    string SfM4000w0p2_1 = getFileName(dir ,ModelName,decayMode,4000,0.2,1);
    string SfM800w0p2_2 = getFileName(dir  ,ModelName,decayMode,800,0.2,2);
    string SfM1200w0p2_2 = getFileName(dir ,ModelName,decayMode,1200,0.2,2);
    string SfM2000w0p2_2 = getFileName(dir ,ModelName,decayMode,2000,0.2,2);
    string SfM3000w0p2_2 = getFileName(dir ,ModelName,decayMode,3000,0.2,2);
    string SfM4000w0p2_2 = getFileName(dir ,ModelName,decayMode,4000,0.2,2);
    string SfM800w0p2_3 = getFileName(dir  ,ModelName,decayMode,800,0.2,3);
    string SfM1200w0p2_3 = getFileName(dir ,ModelName,decayMode,1200,0.2,3);
    string SfM2000w0p2_3 = getFileName(dir ,ModelName,decayMode,2000,0.2,3);
    string SfM3000w0p2_3 = getFileName(dir ,ModelName,decayMode,3000,0.2,3);
    string SfM4000w0p2_3 = getFileName(dir ,ModelName,decayMode,4000,0.2,3);
    
    const char* fM800w0p2_1  =   SfM800w0p2_1.c_str();
    const char* fM1200w0p2_1 =   SfM1200w0p2_1.c_str();
    const char* fM2000w0p2_1 =   SfM2000w0p2_1.c_str();
    const char* fM3000w0p2_1 =   SfM3000w0p2_1.c_str();
    const char* fM4000w0p2_1 =   SfM4000w0p2_1.c_str();
    const char* fM800w0p2_2  =   SfM800w0p2_2.c_str();
    const char* fM1200w0p2_2 =   SfM1200w0p2_2.c_str();
    const char* fM2000w0p2_2 =   SfM2000w0p2_2.c_str();
    const char* fM3000w0p2_2 =   SfM3000w0p2_2.c_str();
    const char* fM4000w0p2_2 =   SfM4000w0p2_2.c_str();
    const char* fM800w0p2_3  =   SfM800w0p2_3.c_str();
    const char* fM1200w0p2_3 =   SfM1200w0p2_3.c_str();
    const char* fM2000w0p2_3 =   SfM2000w0p2_3.c_str();
    const char* fM3000w0p2_3 =   SfM3000w0p2_3.c_str();
    const char* fM4000w0p2_3 =   SfM4000w0p2_3.c_str();
                                              
    string SfM800w0p3_1 =  getFileName(dir ,ModelName,decayMode,800,0.3,1);
    string SfM1200w0p3_1 = getFileName(dir ,ModelName,decayMode,1200,0.3,1);
    string SfM2000w0p3_1 = getFileName(dir ,ModelName,decayMode,2000,0.3,1);
    string SfM3000w0p3_1 = getFileName(dir ,ModelName,decayMode,3000,0.3,1);
    string SfM4000w0p3_1 = getFileName(dir ,ModelName,decayMode,4000,0.3,1);
    string SfM800w0p3_2 =  getFileName(dir ,ModelName,decayMode,800,0.3,2);
    string SfM1200w0p3_2 = getFileName(dir ,ModelName,decayMode,1200,0.3,2);
    string SfM2000w0p3_2 = getFileName(dir ,ModelName,decayMode,2000,0.3,2);
    string SfM3000w0p3_2 = getFileName(dir ,ModelName,decayMode,3000,0.3,2);
    string SfM4000w0p3_2 = getFileName(dir ,ModelName,decayMode,4000,0.3,2);
    string SfM800w0p3_3 =  getFileName(dir ,ModelName,decayMode,800,0.3,3);
    string SfM1200w0p3_3 = getFileName(dir ,ModelName,decayMode,1200,0.3,3);
    string SfM2000w0p3_3 = getFileName(dir ,ModelName,decayMode,2000,0.3,3);
    string SfM3000w0p3_3 = getFileName(dir ,ModelName,decayMode,3000,0.3,3);
    string SfM4000w0p3_3 = getFileName(dir ,ModelName,decayMode,4000,0.3,3);

    const char* fM800w0p3_1 =  SfM800w0p3_1.c_str();
    const char* fM1200w0p3_1= SfM1200w0p3_1.c_str();
    const char* fM2000w0p3_1= SfM2000w0p3_1.c_str();
    const char* fM3000w0p3_1= SfM3000w0p3_1.c_str();
    const char* fM4000w0p3_1= SfM4000w0p3_1.c_str();
    const char* fM800w0p3_2 =  SfM800w0p3_2.c_str();
    const char* fM1200w0p3_2= SfM1200w0p3_2.c_str();
    const char* fM2000w0p3_2= SfM2000w0p3_2.c_str();
    const char* fM3000w0p3_2= SfM3000w0p3_2.c_str();
    const char* fM4000w0p3_2= SfM4000w0p3_2.c_str();
    const char* fM800w0p3_3 =  SfM800w0p3_3.c_str();
    const char* fM1200w0p3_3= SfM1200w0p3_3.c_str();
    const char* fM2000w0p3_3= SfM2000w0p3_3.c_str();
    const char* fM3000w0p3_3= SfM3000w0p3_3.c_str();
    const char* fM4000w0p3_3= SfM4000w0p3_3.c_str();
    
 if(ModelName.find("BulkG") != string::npos)
 {
   std::cout <<"BulkGrav"<<std::endl;
   std::cout <<fM800w0p0_1 <<std::endl;
   tree.Add(fM800w0p0_1);
   tree.Add(fM1000w0p0_1);
   tree.Add(fM1200w0p0_1);
   tree.Add(fM1400w0p0_1);
   tree.Add(fM1600w0p0_1);
   tree.Add(fM1800w0p0_1);
   tree.Add(fM2000w0p0_1);
   tree.Add(fM2500w0p0_1);
   tree.Add(fM3000w0p0_1);
   tree.Add(fM3500w0p0_1);
   tree.Add(fM4000w0p0_1);
   tree.Add(fM4500w0p0_1);
  
 
}

if(ModelName.find("Wprime") !=string::npos)
{
  std::cout <<"Wprime"<<std::endl;
    tree.Add(fM800w0p0_1);
  // tree.Add(fM1000w0p0_1);
   tree.Add(fM1200w0p0_1);
   tree.Add(fM1400w0p0_1);
   tree.Add(fM1600w0p0_1);
   tree.Add(fM1800w0p0_1);
   tree.Add(fM2000w0p0_1);
   tree.Add(fM2500w0p0_1);
   tree.Add(fM3000w0p0_1);
   tree.Add(fM3500w0p0_1);
   tree.Add(fM4000w0p0_1);
   tree.Add(fM4500w0p0_1);
  
tree.Add(fM800w0p1_1 );
tree.Add(fM1200w0p1_1);
tree.Add(fM2000w0p1_1);
tree.Add(fM3000w0p1_1);
tree.Add(fM4000w0p1_1);
tree.Add(fM800w0p1_2 );
tree.Add(fM1200w0p1_2);
tree.Add(fM2000w0p1_2);
tree.Add(fM3000w0p1_2);
tree.Add(fM4000w0p1_2);
tree.Add(fM800w0p1_3 );
tree.Add(fM1200w0p1_3);
tree.Add(fM2000w0p1_3);
tree.Add(fM3000w0p1_3);
tree.Add(fM4000w0p1_3);
tree.Add(fM800w0p2_1 );
tree.Add(fM1200w0p2_1);
tree.Add(fM2000w0p2_1);
tree.Add(fM3000w0p2_1);
tree.Add(fM4000w0p2_1);
tree.Add(fM800w0p2_2 );
tree.Add(fM1200w0p2_2);
tree.Add(fM2000w0p2_2);
tree.Add(fM3000w0p2_2);
tree.Add(fM4000w0p2_2);
tree.Add(fM800w0p2_3 );
tree.Add(fM1200w0p2_3);
tree.Add(fM2000w0p2_3);
tree.Add(fM3000w0p2_3);
tree.Add(fM4000w0p2_3);
tree.Add(fM800w0p3_1 );
tree.Add(fM1200w0p3_1);
tree.Add(fM2000w0p3_1);
tree.Add(fM3000w0p3_1);
tree.Add(fM4000w0p3_1);
tree.Add(fM800w0p3_2 );
tree.Add(fM1200w0p3_2);
tree.Add(fM2000w0p3_2);
tree.Add(fM3000w0p3_2);
tree.Add(fM4000w0p3_2);
tree.Add(fM800w0p3_3 );
tree.Add(fM1200w0p3_3);
tree.Add(fM2000w0p3_3);
tree.Add(fM3000w0p3_3);
tree.Add(fM4000w0p3_3);
  
}


if(ModelName.find("Radion")!=string::npos)
{
  std::cout <<"Radion"<<std::endl;
   std::cout <<fM800w0p0_1 <<std::endl;
  tree.Add(fM800w0p0_1);
  tree.Add(fM1000w0p0_1);
  tree.Add(fM1200w0p0_1);
  tree.Add(fM1400w0p0_1);
  tree.Add(fM1600w0p0_1);
  tree.Add(fM1800w0p0_1);
  tree.Add(fM2000w0p0_1);
  tree.Add(fM2500w0p0_1);
  tree.Add(fM3000w0p0_1);
  tree.Add(fM3500w0p0_1);
  tree.Add(fM4000w0p0_1);
  tree.Add(fM4500w0p0_1);
  
/*  
  tree.Add(fM800w0p1_1 );
 tree.Add(fM1200w0p1_1);*/
//   tree.Add(fM2000w0p1_1);
//   tree.Add(fM3000w0p1_1);
//   tree.Add(fM4000w0p1_1);
//   tree.Add(fM800w0p1_2 );
//   tree.Add(fM1200w0p1_2);
//   tree.Add(fM2000w0p1_2);
//   tree.Add(fM3000w0p1_2);
//   tree.Add(fM4000w0p1_2);
//   tree.Add(fM800w0p1_3 );
//   tree.Add(fM1200w0p1_3);
//   tree.Add(fM2000w0p1_3);
//   tree.Add(fM3000w0p1_3);
//   tree.Add(fM4000w0p1_3);
//   tree.Add(fM800w0p2_1 );
//   tree.Add(fM1200w0p2_1);
//   tree.Add(fM2000w0p2_1);
//   tree.Add(fM3000w0p2_1);
//   tree.Add(fM4000w0p2_1);
//   tree.Add(fM800w0p2_2 );
//   tree.Add(fM1200w0p2_2);
//   tree.Add(fM2000w0p2_2);
//   tree.Add(fM3000w0p2_2);
//   tree.Add(fM4000w0p2_2);
//   tree.Add(fM800w0p2_3 );
//   tree.Add(fM1200w0p2_3);
//   tree.Add(fM2000w0p2_3);
//   tree.Add(fM3000w0p2_3);
//   tree.Add(fM4000w0p2_3);
//   tree.Add(fM800w0p3_1 );
//   tree.Add(fM1200w0p3_1);
//   tree.Add(fM2000w0p3_1);
//   tree.Add(fM3000w0p3_1);
//   tree.Add(fM4000w0p3_1);
//   tree.Add(fM800w0p3_2 );
//   tree.Add(fM1200w0p3_2);
//   tree.Add(fM2000w0p3_2);
//   tree.Add(fM3000w0p3_2);
//   tree.Add(fM4000w0p3_2);
//   tree.Add(fM800w0p3_3 );
//   tree.Add(fM1200w0p3_3);
//   tree.Add(fM2000w0p3_3);
//   tree.Add(fM3000w0p3_3);
//   tree.Add(fM4000w0p3_3);
  
}

if(ModelName.find("RSGrav")!= string::npos)
{
  std::cout <<"RSGrav"<<std::endl;
  tree.Add(fM800w0p1_1 );
  tree.Add(fM1200w0p1_1);
  tree.Add(fM2000w0p1_1);
  tree.Add(fM3000w0p1_1);
  tree.Add(fM4000w0p1_1);
  tree.Add(fM800w0p1_2 );
  tree.Add(fM1200w0p1_2);
  tree.Add(fM2000w0p1_2);
  tree.Add(fM3000w0p1_2);
  tree.Add(fM4000w0p1_2);
  tree.Add(fM800w0p1_3 );
  tree.Add(fM1200w0p1_3);
  tree.Add(fM2000w0p1_3);
  tree.Add(fM3000w0p1_3);
  tree.Add(fM4000w0p1_3);
  tree.Add(fM800w0p2_1 );
  tree.Add(fM1200w0p2_1);
  tree.Add(fM2000w0p2_1);
  tree.Add(fM3000w0p2_1);
  tree.Add(fM4000w0p2_1);
  tree.Add(fM800w0p2_2 );
  tree.Add(fM1200w0p2_2);
  tree.Add(fM2000w0p2_2);
  tree.Add(fM3000w0p2_2);
  tree.Add(fM4000w0p2_2);
  tree.Add(fM800w0p2_3 );
  tree.Add(fM1200w0p2_3);
  tree.Add(fM2000w0p2_3);
  tree.Add(fM3000w0p2_3);
  tree.Add(fM4000w0p2_3);
  tree.Add(fM800w0p3_1 );
  tree.Add(fM1200w0p3_1);
  tree.Add(fM2000w0p3_1);
  tree.Add(fM3000w0p3_1);
  tree.Add(fM4000w0p3_1);
  tree.Add(fM800w0p3_2 );
  tree.Add(fM1200w0p3_2);
  tree.Add(fM2000w0p3_2);
  tree.Add(fM3000w0p3_2);
  tree.Add(fM4000w0p3_2);
  tree.Add(fM800w0p3_3 );
  tree.Add(fM1200w0p3_3);
  tree.Add(fM2000w0p3_3);
  tree.Add(fM3000w0p3_3);
  tree.Add(fM4000w0p3_3);
  
}
  
if(ModelName.find("Zprime")!= string::npos)
{
  std::cout <<"Zprime"<<std::endl;
   tree.Add(fM800w0p0_1);
   tree.Add(fM1000w0p0_1);
   tree.Add(fM1200w0p0_1);
   tree.Add(fM1400w0p0_1);
   tree.Add(fM1600w0p0_1);
   tree.Add(fM1800w0p0_1);
   tree.Add(fM2000w0p0_1);
   tree.Add(fM2500w0p0_1);
   tree.Add(fM3000w0p0_1);
   tree.Add(fM3500w0p0_1);
   tree.Add(fM4000w0p0_1);
   tree.Add(fM4500w0p0_1);
  /* 
   tree.Add(fM800w0p1_1 );
  tree.Add(fM1200w0p1_1);
  tree.Add(fM2000w0p1_1);
  tree.Add(fM3000w0p1_1);
  tree.Add(fM4000w0p1_1);
  tree.Add(fM800w0p1_2 );
  tree.Add(fM1200w0p1_2);
  tree.Add(fM2000w0p1_2);
  tree.Add(fM3000w0p1_2);
  tree.Add(fM4000w0p1_2);
  tree.Add(fM800w0p1_3 );
  tree.Add(fM1200w0p1_3);
  tree.Add(fM2000w0p1_3);
  tree.Add(fM3000w0p1_3);
  tree.Add(fM4000w0p1_3);
  tree.Add(fM800w0p2_1 );
  tree.Add(fM1200w0p2_1);
  tree.Add(fM2000w0p2_1);
  tree.Add(fM3000w0p2_1);
  tree.Add(fM4000w0p2_1);
  tree.Add(fM800w0p2_2 );
  tree.Add(fM1200w0p2_2);
  tree.Add(fM2000w0p2_2);
  tree.Add(fM3000w0p2_2);
  tree.Add(fM4000w0p2_2);
  tree.Add(fM800w0p2_3 );
  tree.Add(fM1200w0p2_3);
  tree.Add(fM2000w0p2_3);
  tree.Add(fM3000w0p2_3);
  tree.Add(fM4000w0p2_3);
  tree.Add(fM800w0p3_1 );
  tree.Add(fM1200w0p3_1);
  tree.Add(fM2000w0p3_1);
  tree.Add(fM3000w0p3_1);
  tree.Add(fM4000w0p3_1);
  tree.Add(fM800w0p3_2 );
  tree.Add(fM1200w0p3_2);
  tree.Add(fM2000w0p3_2);
  tree.Add(fM3000w0p3_2);
  tree.Add(fM4000w0p3_2);
  tree.Add(fM800w0p3_3 );
  tree.Add(fM1200w0p3_3);
  tree.Add(fM2000w0p3_3);
  tree.Add(fM3000w0p3_3);
  tree.Add(fM4000w0p3_3);
 
 */
}
  
  

  MyClass* t12 = new MyClass(&tree);
int howmany = t12->fChain->GetEntries();
cout<<"we look at the first " << howmany << " events."<<endl;

  
TFile Wkinematics(filename,"RECREATE");


if(decayMode.find("lvjj")!=string::npos)
{
//same for Electron decay channel
 const Float_t xbinsW[16]= BINNINGX;
 const Float_t ybinsW[10]= BINNINGY;
 

 
 TH2F* hW_lep_rec = new TH2F("hW_lep_rec","W #rightarrow l #nu_{l}, rec.",15,xbinsW,9,ybinsW);
 TH2F* hW_lep_gen = new TH2F("hW_lep_gen","W #rightarrow l #nu_{l}, gen.",15,xbinsW,9,ybinsW);
 TH2F* hW_lep_genWithVeto = new TH2F("hW_lep_genWithVeto","W #rightarrow l #nu_{l}, all vetos",15,xbinsW,9,ybinsW);
 TH2F* hW_lep_genWithBVeto = new TH2F("hW_lep_genWithBVeto","W #rightarrow l #nu_{l}, B-tagged jet veto",15,xbinsW,9,ybinsW);
 TH2F* hW_lep_genWithLooseLeptonVeto = new TH2F("hW_lep_genWithLooseLeptonVeto","W #rightarrow l #nu_{l}, loose lepton veto",15,xbinsW,9,ybinsW);
 
 TH2F* hW_had_genWithVeto = new TH2F("hW_had_genWithVeto","hadronic W decay, all vetos",15,xbinsW,9,ybinsW);
 TH2F* hW_had_genWithBVeto = new TH2F("hW_had_genWithBVeto","hadronic W decay, b-tagged jet veto",15,xbinsW,9,ybinsW);
 TH2F* hW_had_genWithLooseLeptonVeto = new TH2F("hW_had_genWithLooseLeptonVeto","hadronic W decay, loose lepton veto",15,xbinsW,9,ybinsW);
 TH2F* hW_had_gen = new TH2F("hW_had_gen","hadronic W decay",15,xbinsW,9,ybinsW);
 TH2F* hW_had_rec = new TH2F("hW_had_rec","hadronic W decay",15,xbinsW,9,ybinsW);
 
 
 //  for finer Binning (test!)
 
 TH2F* hW_lep_rec_fb = new TH2F("hW_lep_rec_fb","W #rightarrow l #nu_{l}, rec.",100,0,4000,100,0,2.5);
 TH2F* hW_lep_gen_fb = new TH2F("hW_lep_gen_fb","W #rightarrow l #nu_{l}, gen.",100,0,4000,100,0,2.5);
 TH2F* hW_lep_genWithVeto_fb = new TH2F("hW_lep_genWithVeto_fb","W #rightarrow l #nu_{l}, all vetos",100,0,4000,100,0,2.5);
 
 
 TH2F* hW_had_genWithVeto_fb = new TH2F("hW_had_genWithVeto_fb","hadronic W decay, all vetos",100,0,4000,100,0,2.5);
 TH2F* hW_had_gen_fb = new TH2F("hW_had_gen_fb","hadronic W decay, gen. sel. ony",100,0,4000,100,0,2.5);
 TH2F* hW_had_rec_fb= new TH2F("hW_had_rec_fb","hadronic W decay, rec events",100,0,4000,100,0,2.5);

 TH2F* pt1_over_pt2 = new TH2F("pt1_over_pt2","pt1_over_pt2",1000,0,4000,1000,0,4000);
 TH2F* eta1_over_eta2 = new TH2F("eta1_over_eta2","eta1_over_eta2",9,ybinsW,9,ybinsW);
 TH2F* eta1_over_pt1 = new TH2F("eta1_over_pt1","eta1_over_pt1",100,0,2.5,1000,0,4000);
 TH2F* eta1_over_pt2 = new TH2F("eta1_over_pt2","eta1_over_pt2",100,0,2.5,1000,0,4000);
 TH2F* eta2_over_pt1 = new TH2F("eta2_over_pt1","eta2_over_pt1",100,0,2.5,1000,0,4000);
 TH2F* eta2_over_pt2 = new TH2F("eta2_over_pt2","eta2_over_pt2",100,0,2.5,1000,0,4000);
 

 
 TLorentzVector W_lep;
 TLorentzVector W_had;
 TLorentzVector l;
 
 int events=0;
 int selected_events=0;
 int events_lepton=0;
 int events_after_MVV_selections=0;
 int events_after_all_selections=0;
 
 for(int i=0;i<howmany;i++)
   {
     
      t12->fChain->GetEntry(i);
    events+=1;
     if(generatedEventSelection(pdgId,t12)==0)
       continue;
     
     TLorentzVector V1 = getLVofGenParticle(24,t12);
     TLorentzVector V2 = getLVofGenParticle(pdgId,t12)+getLVofGenParticle(pdgId+1,t12);
     pt1_over_pt2->Fill(V1.Pt(),V2.Pt());
     eta1_over_eta2->Fill(V1.Eta(),V2.Eta());
     eta1_over_pt1->Fill(V1.Eta(),V1.Pt());
     eta1_over_pt2->Fill(V1.Eta(),V2.Pt());
     eta2_over_pt1->Fill(V2.Eta(),V1.Pt());
     eta2_over_pt2->Fill(V2.Eta(),V2.Pt());
     
     
 
     getGenWKinematics(hW_had_gen,0,t12);
     getGenWKinematics(hW_lep_gen,pdgId,t12);
     getGenWKinematics(hW_had_gen_fb,0,t12);
     getGenWKinematics(hW_lep_gen_fb,pdgId,t12);
     if(applyBVeto(t12)==1)
     {
       getGenWKinematics(hW_had_genWithBVeto,0,t12);
       getGenWKinematics(hW_lep_genWithBVeto,pdgId,t12);
     }
      if(applyLooseLeptonVeto(pdgId,t12)==1)
     {
       getGenWKinematics(hW_had_genWithLooseLeptonVeto,0,t12);
       getGenWKinematics(hW_lep_genWithLooseLeptonVeto,pdgId,t12);
     }
     
      if(!applyVetos(pdgId,t12)) continue;
  
     getGenWKinematics(hW_lep_genWithVeto,pdgId,t12);
     getGenWKinematics(hW_had_genWithVeto,0,t12); 
     getGenWKinematics(hW_lep_genWithVeto_fb,pdgId,t12);
     getGenWKinematics(hW_had_genWithVeto_fb,0,t12);      
    
     if(applyLeptonSelection_NoVeto(pdgId,t12)==1 and applyMET(pdgId,t12)==1 and applyTrigger(pdgId,t12)==1)
	{
	  W_lep = reconstructLeptonicW(pdgId,t12);
	  if(W_lep.Pt()<200)
	    continue;
	  getGenWKinematics(hW_lep_rec,pdgId,t12);
	  getGenWKinematics(hW_lep_rec_fb,pdgId,t12);
	  events_lepton+=1;
	  
	}
     if(applyHadronSelection(t12,isHP,isLP,useWRegion,useZRegion)==1)
	{
	  W_had = reconstructHadronicWOrZ(t12,1,1);
	  if(W_had.Pt()<200)
	    continue;
	  getGenWKinematics(hW_had_rec,0,t12);
	  getGenWKinematics(hW_had_rec_fb,0,t12);
	  selected_events+=1;
	}
	
	if(!applyLeptonSelection_NoVeto(pdgId,t12) and !applyMET(pdgId,t12) and !applyTrigger(pdgId,t12)) continue;
	if(W_lep.Pt()<200) continue;
	if(applyHadronSelection(t12,isHP,isLP,useWRegion,useZRegion)==0) continue;
	if(W_had.Pt()<200) continue;
	W_had = reconstructHadronicWOrZ(t12);
	W_lep = reconstructLeptonicW(pdgId,t12);
	l     = reconstructLepton(pdgId,t12);
	TLorentzVector n = W_lep - l;
	events_after_all_selections+=1;
	if(!recoEventSelectionMVVSystemSemilep(l,n,W_had)) continue;
	events_after_MVV_selections+=1;
  }
  
  
 std::cout << " number of all events " << events<< std::endl;
 std::cout << " number of selected events " << selected_events<< std::endl;
 std::cout<< "number of leptonic selected events " << events_lepton << std::endl;
 std::cout<< "mVV cuts efficiency "<< events_after_MVV_selections/double(events_after_all_selections) << std::endl;
 
 hW_lep_rec->Write();
 hW_lep_gen->Write();
 hW_lep_genWithVeto->Write();
 hW_lep_genWithBVeto->Write();
 hW_lep_genWithLooseLeptonVeto->Write();
 hW_had_rec->Write();
 hW_had_gen->Write();
 hW_had_genWithVeto->Write();
 hW_had_genWithBVeto->Write();
 hW_had_genWithLooseLeptonVeto->Write();
 
 hW_lep_rec_fb->Write();
 hW_lep_gen_fb->Write();
 hW_lep_genWithVeto_fb->Write();
 hW_had_rec_fb->Write();
 hW_had_gen_fb->Write();
 hW_had_genWithVeto_fb->Write();
 
 pt1_over_pt2->Write();
 eta1_over_eta2->Write();
 eta1_over_pt1->Write();
 eta1_over_pt2->Write();
 eta2_over_pt1->Write();
 eta2_over_pt2->Write();
 

}
if(decayMode.find("jjjj")!=string::npos)
{
  
  int events=0;
  int selected_events=0;
  if(category.find("W")!=string::npos or category.find("Z")!=string::npos)
  {
   std::cout << "for all hadronic channel only HP and LP as categories possible!"<<std::endl; 
  }
  
  const Float_t xbins[ALLHADNBINSX]=  ALLHADBINNINGX;
  const Float_t ybins[ALLHADNBINSY]=  ALLHADBINNINGY;
  int nbinsx = ALLHADNBINSX-1;
  int nbinsy = ALLHADNBINSY-1;
  
  const Float_t xbinsNew[ALLHADNBINSXBOTHJETS]=  ALLHADBINNINGXBOTHJETS;
  const Float_t ybinsNew[ALLHADNBINSYBOTHJETS]=  ALLHADBINNINGYBOTHJETS;
  int nbinsxNew = ALLHADNBINSXBOTHJETS-1;
  int nbinsyNew = ALLHADNBINSYBOTHJETS-1;
 
 TH2F* hhad_Wtag_rec = new TH2F("hhad_Wtag_rec","W-tagged  rec.",nbinsxNew,xbinsNew,nbinsyNew,ybinsNew);
 TH2F* hhad_Wtag_gen = new TH2F("hhad_Wtag_gen","W-tagged, gen.",nbinsxNew,xbinsNew,nbinsyNew,ybinsNew);
 TH2F* hhad_Ztag_rec = new TH2F("hhad_Ztag_rec","Z-tagged, rec",nbinsxNew,xbinsNew,nbinsyNew,ybinsNew);
 TH2F* hhad_Ztag_gen = new TH2F("hhad_Ztag_gen","Z-tagged, gen",nbinsxNew,xbinsNew,nbinsyNew,ybinsNew);
 TH2F* hhad_WZtag_rec = new TH2F("hhad_WZtag_rec","WZ-tagged, rec",nbinsxNew,xbinsNew,nbinsyNew,ybinsNew);
 TH2F* hhad_WZtag_gen = new TH2F("hhad_WZtag_gen","WZ-tagged, gen",nbinsxNew,xbinsNew,nbinsyNew,ybinsNew);
 TH2F* hhad_rec = new TH2F("hhad_rec","reco all region",nbinsxNew,xbinsNew,nbinsyNew,ybinsNew);
 TH2F* hhad_gen = new TH2F("hhad_gen","gen all region",nbinsxNew,xbinsNew,nbinsyNew,ybinsNew);
 
 
 TH2F* h_Vplus_denominator = new TH2F("h_jet1_denominator","",nbinsx,xbins,nbinsy,ybins);
 TH2F* h_Vplus_numerator = new TH2F("h_jet1_numerator","",nbinsx,xbins,nbinsy,ybins);
 TH2F* h_Vminus_denominator = new TH2F("h_jet2_denominator","",nbinsx,xbins,nbinsy,ybins);
 TH2F* h_Vminus_numerator = new TH2F("h_jet2_numerator","",nbinsx,xbins,nbinsy,ybins);
 
 TH2F* h_tau21_tau21 = new TH2F("h_tau21_tau21","Wplus tau21 over Wminus tau21 after all cuts",1000,0,1,1000,0,1);
 TH2F* h_tau21_tau21_gen = new TH2F("h_tau21_tau21_gen","Wplus tau21 over Wminus tau21 after generator cuts + 2 jets found",1000,0,1,1000,0,1);
 
 TH2F* h_mpruned1_mpruned2 = new TH2F("h_mpruned1_mpruned2","Wplus mpruned^{matched jet} over Wminus mpruned^{matched jet} after all cuts",1000,0,180,1000,0,180);
 TH2F* h_mpruned1_mpruned2_gen = new TH2F("h_mpruned1_mpruned2_gen","Wplus mpruned^{matched jet} over Wminus mpruned^{matched jet} after generator cuts + 2 jets found",1000,0,180,1000,0,180);
     
 TLorentzVector Vplus;
 TLorentzVector Vminus;
 TLorentzVector jet1;
 TLorentzVector jet2;
 vector<int> cand;
 
 events=0;
 selected_events=0;

 int selectedEv_Wtag=0;
 int selectedEv_Ztag=0;
 int selectedEv_Vtag=0;
 int veto =0;
 int veto_denom=0;
 int events_with_atLeast_one_unmatched_jet=0;
 int eventsWithVplusPTsmaller400=0;
 int eventsWithVminusPTsmaller400=0;
 int eventsWithVplusPTsmaller400_rec=0;
 int eventsWithVminusPTsmaller400_rec=0;
 
 int numberBothVmatchjet1=0;
 int numberBothVmatchjet2=0;
 int numberOfEventsWithPtSmaller400AndUnmatchedJet_Wplus=0;
 int numberOfEventsWithPtSmaller400AndUnmatchedJet_Wminus=0;
 int numberOfEventsWithPtGreater3000AndUnmatchedJet_Wplus=0;
 int numberOfEventsWithPtGreater3000AndUnmatchedJet_Wminus=0;
 int numberOfEventsWithPtGreater3000_Wminus=0;
 int numberOfEventsWithPtGreater3000_Wplus=0;
 int numberOfEventsWithJet1NotMatched=0;
 int numberOfEventsWithJet2NotMatched=0;
 int numberOfEventsWithWminusNotMatched=0;
 int numberOfEventsWithWplusNotMatched=0;
 int numberOfEventsWithBothJetsNotMatched=0;
 int numberOfEventsBothJetsMatchVplus=0;
 int numberOfEventsBothJetsMatchVminus=0;
 int denomForAcceptance=0;
 
 ofstream fplus("debugHadWplus.txt");
 ofstream fminus("debugHadWminus.txt");
 
 //howmany = 30;
 
 for(int i=0;i<howmany;i++)
 {
   t12->fChain->GetEntry(i);
   if(!genEventSelectionInclusive(t12,"jjjj"))
      continue;
   Vplus = getGenLV_V1(t12);
   Vminus = getGenLV_V2(t12);
   vector<float>* jet_pt = t12->jetAK8_pt;
   vector<float>* jet_eta = t12->jetAK8_eta;
   vector<float>* jet_phi = t12->jetAK8_phi;
   vector<float>* jet_e = t12->jetAK8_e;
   
   //std::cout << " V+ : "<<Vplus.Pt()<<std::endl;
   //std::cout << " V- : "<<Vminus.Pt() <<std::endl;
    
     
     if(Vplus.Pt()==Vminus.Pt() and Vplus.Eta()==Vminus.Eta())
     {
       std::cout << t12->EVENT_event <<std::endl;
     }
     
    denomForAcceptance+=1; 
     
     
     
   if(!applyGeneratorKinematicSelectionsAllHad(Vplus,Vminus))
     continue;
   
   if(Vplus.Pt()<400)
     {
       if(Vplus.Pt()>200 and Vplus.Eta()<2.4)
       {
	  eventsWithVplusPTsmaller400+=1;
	  
       }
     }
     if(Vminus.Pt()<400)
     {
       if(Vminus.Pt()>200 and Vminus.Eta()<2.4)
       {
      eventsWithVminusPTsmaller400+=1;
       }
     }
   
   
   
   
   events+=1;
   h_Vplus_denominator->Fill(Vplus.Pt(),TMath::Abs(Vplus.Eta()));
   h_Vminus_denominator->Fill(Vminus.Pt(),TMath::Abs(Vminus.Eta()));
   
   hhad_gen->Fill(Vplus.Pt()+Vminus.Pt(),TMath::Abs(Vplus.Eta()-Vminus.Eta()));
  
   //=========fill histos with generated events with WW, WZ or ZZ ===========================
   if(genEventVVClassification(t12)==48)
   {
    hhad_Wtag_gen->Fill(Vplus.Pt()+Vminus.Pt(),TMath::Abs(Vplus.Eta()-Vminus.Eta()));
   }
   if(genEventVVClassification(t12)==46)
   {
    hhad_Ztag_gen->Fill(Vplus.Pt()+Vminus.Pt(),TMath::Abs(Vplus.Eta()-Vminus.Eta()));
   }
   if(genEventVVClassification(t12)==47)
   {
    hhad_WZtag_gen->Fill(Vplus.Pt()+Vminus.Pt(),TMath::Abs(Vplus.Eta()-Vminus.Eta()));
   }
   //==========================================================================================
    if(!applyTriggerAllHadronic(t12))
      continue;
    int index1 = findFirstJet(t12);
    int index2 = findSecondJet(t12);
     if(index1==-99)
       continue;
     if(index2==-99)
      continue;
    jet2.SetPtEtaPhiE(jet_pt->at(index2),jet_eta->at(index2),jet_phi->at(index2),jet_e->at(index2));
    jet1.SetPtEtaPhiE(jet_pt->at(index1),jet_eta->at(index1),jet_phi->at(index1),jet_e->at(index1));
    
    float tau21_1 = t12->jetAK8_tau2->at(index1)/t12->jetAK8_tau1->at(index1);
    float tau21_2 = t12->jetAK8_tau2->at(index2)/t12->jetAK8_tau1->at(index2);
    float mjpruned1 = t12->jetAK8_pruned_massCorr->at(index1);
    float mjpruned2 = t12->jetAK8_pruned_massCorr->at(index2);
    
    
    if(applyPrunedMassCut(index1,t12) and applyPrunedMassCut(index2,t12))
    {
      if((isMatched(Vplus,jet1) or isMatched(Vplus,jet2)) and (isMatched(Vminus,jet1) or isMatched(Vminus,jet2)))
      {
	if(isMatched(Vplus,jet2))
	{
	float tmp = tau21_1;
	tau21_1 = tau21_2;
	tau21_2 = tmp;
	tmp = mjpruned2;
	mjpruned1 = mjpruned2;
	mjpruned2 = tmp;
	}
	h_tau21_tau21_gen->Fill(tau21_1,tau21_2);
	h_mpruned1_mpruned2_gen->Fill(mjpruned1,mjpruned2);
      }
    }
    //=========== found one jet that passes m_pruned and tau12 cuts?============================
    
    
    if(applyJetCuts(category,index1,t12))
    {
      if(isMatched(Vplus,jet1))
      {
	h_Vplus_numerator->Fill(Vplus.Pt(),TMath::Abs(Vplus.Eta()));
      }
      if(isMatched(Vminus,jet1))
      {
	h_Vminus_numerator->Fill(Vminus.Pt(),TMath::Abs(Vminus.Eta()));
      }
      if(!isMatched(Vminus,jet1) and !isMatched(Vplus,jet1))
      {
	std::cout << "in event "<<t12->EVENT_event << " first jet not matched " <<std::endl;
	events_with_atLeast_one_unmatched_jet+=1;
	numberOfEventsWithJet1NotMatched+=1;
      }
      if(isMatched(Vminus,jet1) and isMatched(Vplus,jet1))
      {
	numberBothVmatchjet1+=1;
      }
    }
    //===========================================================================================
    
    
    //============= find second jet that passed m_pruned and tau21 cuts? ==========================
    if(applyJetCuts(category,index2,t12))
    {
      if(isMatched(Vplus,jet2))
      {
	h_Vplus_numerator->Fill(Vplus.Pt(),TMath::Abs(Vplus.Eta()));
      }
      if(isMatched(Vminus,jet2))
      {
	h_Vminus_numerator->Fill(Vminus.Pt(),TMath::Abs(Vminus.Eta()));
      }
      if(!isMatched(Vminus,jet2) and !isMatched(Vplus,jet2))
      {
	std::cout << "in event "<<t12->EVENT_event << " second jet not matched " <<std::endl;
	numberOfEventsWithJet2NotMatched+=1;
	events_with_atLeast_one_unmatched_jet+=1;
	if(!isMatched(Vminus,jet1) and !isMatched(Vplus,jet1))
	{
	  events_with_atLeast_one_unmatched_jet-=1;
	  numberOfEventsWithBothJetsNotMatched+=1;
	}
      }
       if(isMatched(Vminus,jet2) and isMatched(Vplus,jet2))
      {
	numberBothVmatchjet2+=1;
      }
      
    }
    
    
    //=================================================================================================
    
    if(!applyPrunedMassCutAndSubjettinessHighPurity(index1,t12) or !applyPrunedMassCutAndSubjettinessHighPurity(index2,t12))
      continue;
    veto_denom+=1;
    vector<int> index = {index1,index2};
    if(!AllHadPassedDEtajj(t12,index))
      continue;
    if(!AllHadPassedMjj(t12,index))
      continue;
    veto+=1;
    
    //================================================================================================
    tau21_1 = t12->jetAK8_tau2->at(index1)/t12->jetAK8_tau1->at(index1);
    tau21_2 = t12->jetAK8_tau2->at(index2)/t12->jetAK8_tau1->at(index2);
    
    if(isMatched(Vplus,jet2))
    {
     float tmp = tau21_1;
     tau21_1 = tau21_2;
     tau21_2 = tmp;
     tmp = mjpruned2;
     mjpruned1 = mjpruned2;
     mjpruned2 = tmp;
    }
    
    
    h_tau21_tau21->Fill(tau21_1,tau21_2);
    h_mpruned1_mpruned2->Fill(mjpruned1,mjpruned2);
    
    if(!isMatched(Vplus,jet1) and !isMatched(Vplus,jet2))
    {
     numberOfEventsWithWplusNotMatched+=1; 
    }
     if(!isMatched(Vminus,jet1) and !isMatched(Vminus,jet2))
    {
     numberOfEventsWithWminusNotMatched+=1; 
    }
    
    if(isMatched(Vplus,jet1) and isMatched(Vplus,jet2))
    {
     numberOfEventsBothJetsMatchVplus+=1;
    }
    if(isMatched(Vminus,jet1) and isMatched(Vminus,jet2))
    {
     numberOfEventsBothJetsMatchVminus+=1; 
    }
    
    
    if(Vplus.Pt()<400)
    {
      printInfoEventHadronic(t12->EVENT_event,t12,fplus);
      eventsWithVplusPTsmaller400_rec+=1;
     if(!isMatched(Vplus,jet1) and !isMatched(Vplus,jet2) )
     {
      numberOfEventsWithPtSmaller400AndUnmatchedJet_Wplus+=1; 
     }
    }
     
    if(Vminus.Pt()<400)
    {
       printInfoEventHadronic(t12->EVENT_event, t12, fminus);
       eventsWithVminusPTsmaller400_rec+=1;
     if(!isMatched(Vminus,jet1) and !isMatched(Vminus,jet2) )
     {
      numberOfEventsWithPtSmaller400AndUnmatchedJet_Wminus+=1; 
     }
    }
    
    if(Vplus.Pt()>3000)
    {
     if(!isMatched(Vplus,jet1) and !isMatched(Vplus,jet2) )
     {
      numberOfEventsWithPtGreater3000AndUnmatchedJet_Wplus+=1; 
     }
     numberOfEventsWithPtGreater3000_Wplus+=1;
    }
     
    if(Vminus.Pt()>3000)
    {
     if(!isMatched(Vminus,jet1) and !isMatched(Vminus,jet2) )
     {
      numberOfEventsWithPtGreater3000AndUnmatchedJet_Wminus+=1; 
     }
     numberOfEventsWithPtGreater3000_Wminus +=1;
    }
    //============================================================================================
    
    if(!passedAllHadronicSelections(t12))
      continue;
    if(passedSubstructureSelection(t12,("WW_"+category).c_str()))
    {
      hhad_Wtag_rec->Fill(Vplus.Pt()+Vminus.Pt(),TMath::Abs(Vplus.Eta()-Vminus.Eta()));
      //hhad_Wtag_rec->Fill(Vminus.Pt(),TMath::Abs(Vminus.Eta()));
      selectedEv_Wtag+=1;
    }
    if(passedSubstructureSelection(t12,("WZ_"+category).c_str()))
    {
      hhad_WZtag_rec->Fill(Vplus.Pt()+Vminus.Pt(),TMath::Abs(Vplus.Eta()-Vminus.Eta()));
      //hhad_WZtag_rec->Fill(Vminus.Pt(),TMath::Abs(Vminus.Eta()));
    }
    if(passedSubstructureSelection(t12,("ZZ_"+category).c_str()))
    {
      hhad_Ztag_rec->Fill(Vplus.Pt()+Vminus.Pt(),TMath::Abs(Vplus.Eta()-Vminus.Eta()));
      //hhad_Ztag_rec->Fill(Vminus.Pt(),TMath::Abs(Vminus.Eta()));
      selectedEv_Ztag+=1;
    }
    if(passedSubstructureSelection(t12,("VV_"+category).c_str()))
    {
      
      hhad_rec->Fill(Vplus.Pt()+Vminus.Pt(),TMath::Abs(Vplus.Eta()-Vminus.Eta()));
      //hhad_rec->Fill(Vminus.Pt(),TMath::Abs(Vminus.Eta()));
      selectedEv_Vtag+=1;
    }
      selected_events+=1;
    
 }
 std::cout << " acceptance : " << events/double(denomForAcceptance) << std::endl;
 std::cout << " number of all events " << events<< std::endl;
 std::cout << " number of selected events " << selected_events<< std::endl;
 std::cout << " number of selected events W tag " << selectedEv_Wtag<< std::endl;
std::cout << " number of selected events  Z tag " << selectedEv_Ztag<< std::endl;
std::cout << " number of selected events V tag  " << selectedEv_Vtag<< std::endl;

std::cout << " delta eta and mass cut : " << veto << " "<<veto_denom <<" "<< veto/double(veto_denom) <<std::endl;
std::cout << "# events where jets can't be matched : " << events_with_atLeast_one_unmatched_jet <<std::endl;
 hhad_Wtag_gen->Write();
 hhad_Wtag_rec->Write();
 hhad_Ztag_gen->Write();
 hhad_Ztag_rec->Write();
 hhad_WZtag_gen->Write();
 hhad_WZtag_rec->Write();
 hhad_rec->Write();
 hhad_gen->Write();
 
 h_Vplus_denominator->Write();
 h_Vminus_denominator->Write();
 h_Vplus_numerator->Write();
 h_Vminus_numerator->Write();
 
 h_tau21_tau21->Write();
 h_tau21_tau21_gen->Write();
 h_mpruned1_mpruned2->Write();
 h_mpruned1_mpruned2_gen->Write();
 
 std::cout << "number of events with Wplus not matched " << numberOfEventsWithWplusNotMatched  <<std::endl;
 std::cout << "number of events with Wminus not matched " << numberOfEventsWithWminusNotMatched  <<std::endl;
 std::cout << "number of events with jet1 not matched " << numberOfEventsWithJet1NotMatched  <<std::endl;
 std::cout << "number of events with jet2 not matched " << numberOfEventsWithJet2NotMatched  <<std::endl;
 std::cout << "number of events with both jets not matched " << numberOfEventsWithBothJetsNotMatched  <<std::endl;
  std::cout << " number of events where both jets match Vplus " <<numberOfEventsBothJetsMatchVplus << std::endl;
    std::cout << " number of events where both jets match Vminus " <<numberOfEventsBothJetsMatchVminus << std::endl;
 std::cout <<"number of generated events with Wplus pt <400 " << eventsWithVplusPTsmaller400 <<std::endl;
 std::cout <<"number of generated events with Wminus pt < 400 " << eventsWithVminusPTsmaller400 << std::endl;
 std::cout <<"number of reconstructed events with Wplus pt <400 " << eventsWithVplusPTsmaller400_rec <<std::endl;
 std::cout <<"number of reconstructed events with Wminus pt < 400 " << eventsWithVminusPTsmaller400_rec << std::endl;
 
 std::cout << "number of events with pt greater 3000; Wplus "<< numberOfEventsWithPtGreater3000_Wplus <<std::endl;
 std::cout <<  "number of events with pt greater 3000; Wminus "<< numberOfEventsWithPtGreater3000_Wminus <<std::endl;
 std::cout << " jet 1 matches both V  " << numberBothVmatchjet1<<std::endl;
 std::cout << "jet 2 matches both V " << numberBothVmatchjet2 <<std::endl;
 std::cout << "number of events with Wplus.Pt<400 and no jet matched to Wplus : " <<numberOfEventsWithPtSmaller400AndUnmatchedJet_Wplus <<std::endl;
 std::cout <<  "number of events with Wminus.Pt<400 and no jet matched to Wminus : " << numberOfEventsWithPtSmaller400AndUnmatchedJet_Wminus<<std::endl;
  std::cout << "number of events with Wplus.Pt>3000 and no jet matched to Wplus : " <<numberOfEventsWithPtGreater3000AndUnmatchedJet_Wplus <<std::endl;
  std::cout <<  "number of events with Wminus.Pt>3000 and no jet matched to Wminus : " << numberOfEventsWithPtGreater3000AndUnmatchedJet_Wminus<<std::endl;
  
   
 
 
}
Wkinematics.Close();

}
