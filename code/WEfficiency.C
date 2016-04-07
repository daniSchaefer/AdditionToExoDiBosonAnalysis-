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
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C+");

 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}
//_--------------------------------------------------------------------------
//---------------------main function-----------------------------------------


void WEfficiency(int pdgId, string ModelName, string category)
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
  string channel = "el";
  if(pdgId ==13)
  {
   channel = "mu"; 
  }
  
    TChain tree("ntuplizer/tree");
   //string dir = "/storage/a/mmozer/Res_Sig/";
    string dir = "/storage/jbod/dschaefer/Res_Sig/";
   string outputDir = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/";
   string Sfilename = outputDir+ModelName+"ToWWKinematics_"+channel+"_"+category+".root";
   if(ModelName.find("Wprime")!=string::npos)
   {
    outputDir = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/";
    Sfilename = outputDir+ModelName+"ToWZKinematics_"+channel+"_"+category+".root";
   }
   
   
   const char* filename = Sfilename.c_str();

    string  SfM800w0p0_1 = (getFileName(dir ,ModelName,800,0.0,1));
    string  SfM1000w0p0_1 = getFileName(dir ,ModelName,1000,0.0,1);
    string  SfM1200w0p0_1 = getFileName(dir ,ModelName,1200,0.0,1);
    string  SfM1400w0p0_1 = getFileName(dir ,ModelName,1400,0.0,1);
    string  SfM1600w0p0_1 = getFileName(dir ,ModelName,1600,0.0,1);
    string  SfM1800w0p0_1 = getFileName(dir ,ModelName,1800,0.0,1);
    string  SfM2000w0p0_1 = getFileName(dir ,ModelName,2000,0.0,1);
    string  SfM2500w0p0_1 = getFileName(dir ,ModelName,2500,0.0,1);
    string  SfM3000w0p0_1 = getFileName(dir ,ModelName,3000,0.0,1);
    string  SfM3500w0p0_1 = getFileName(dir ,ModelName,3500,0.0,1);
    string  SfM4000w0p0_1 = getFileName(dir ,ModelName,4000,0.0,1);
    string  SfM4500w0p0_1 = getFileName(dir ,ModelName,4500,0.0,1);
    
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
    
    
    
    string  SfM800w0p1_1 = getFileName(dir ,ModelName,800,0.1,1);
    string  SfM1200w0p1_1 = getFileName(dir ,ModelName,1200,0.1,1);
    string  SfM2000w0p1_1 = getFileName(dir ,ModelName,2000,0.1,1);
    string  SfM3000w0p1_1 = getFileName(dir ,ModelName,3000,0.1,1);
    string  SfM4000w0p1_1 = getFileName(dir ,ModelName,4000,0.1,1);
    string  SfM800w0p1_2 = getFileName(dir ,ModelName,800,0.1,2);
    string  SfM1200w0p1_2 = getFileName(dir ,ModelName,1200,0.1,2);
    string  SfM2000w0p1_2 = getFileName(dir ,ModelName,2000,0.1,2);
    string  SfM3000w0p1_2 = getFileName(dir ,ModelName,3000,0.1,2);
    string  SfM4000w0p1_2 = getFileName(dir ,ModelName,4000,0.1,2);
    string  SfM800w0p1_3 = getFileName(dir ,ModelName,800,0.1,3);
    string  SfM1200w0p1_3 = getFileName(dir ,ModelName,1200,0.1,3);
    string  SfM2000w0p1_3 = getFileName(dir ,ModelName,2000,0.1,3);
    string  SfM3000w0p1_3 = getFileName(dir ,ModelName,3000,0.1,3);
    string  SfM4000w0p1_3 = getFileName(dir ,ModelName,4000,0.1,3);
    
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
    
    
    string SfM800w0p2_1 = getFileName(dir ,ModelName,800,0.2,1);
    string SfM1200w0p2_1 = getFileName(dir ,ModelName,1200,0.2,1);
    string SfM2000w0p2_1 = getFileName(dir ,ModelName,2000,0.2,1);
    string SfM3000w0p2_1 = getFileName(dir ,ModelName,3000,0.2,1);
    string SfM4000w0p2_1 = getFileName(dir ,ModelName,4000,0.2,1);
    string SfM800w0p2_2 = getFileName(dir ,ModelName,800,0.2,2);
    string SfM1200w0p2_2 = getFileName(dir ,ModelName,1200,0.2,2);
    string SfM2000w0p2_2 = getFileName(dir ,ModelName,2000,0.2,2);
    string SfM3000w0p2_2 = getFileName(dir ,ModelName,3000,0.2,2);
    string SfM4000w0p2_2 = getFileName(dir ,ModelName,4000,0.2,2);
    string SfM800w0p2_3 = getFileName(dir ,ModelName,800,0.2,3);
    string SfM1200w0p2_3 = getFileName(dir ,ModelName,1200,0.2,3);
    string SfM2000w0p2_3 = getFileName(dir ,ModelName,2000,0.2,3);
    string SfM3000w0p2_3 = getFileName(dir ,ModelName,3000,0.2,3);
    string SfM4000w0p2_3 = getFileName(dir ,ModelName,4000,0.2,3);
    
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
                                              
    string SfM800w0p3_1 =  getFileName(dir ,ModelName,800,0.3,1);
    string SfM1200w0p3_1 = getFileName(dir ,ModelName,1200,0.3,1);
    string SfM2000w0p3_1 = getFileName(dir ,ModelName,2000,0.3,1);
    string SfM3000w0p3_1 = getFileName(dir ,ModelName,3000,0.3,1);
    string SfM4000w0p3_1 = getFileName(dir ,ModelName,4000,0.3,1);
    string SfM800w0p3_2 =  getFileName(dir ,ModelName,800,0.3,2);
    string SfM1200w0p3_2 = getFileName(dir ,ModelName,1200,0.3,2);
    string SfM2000w0p3_2 = getFileName(dir ,ModelName,2000,0.3,2);
    string SfM3000w0p3_2 = getFileName(dir ,ModelName,3000,0.3,2);
    string SfM4000w0p3_2 = getFileName(dir ,ModelName,4000,0.3,2);
    string SfM800w0p3_3 =  getFileName(dir ,ModelName,800,0.3,3);
    string SfM1200w0p3_3 = getFileName(dir ,ModelName,1200,0.3,3);
    string SfM2000w0p3_3 = getFileName(dir ,ModelName,2000,0.3,3);
    string SfM3000w0p3_3 = getFileName(dir ,ModelName,3000,0.3,3);
    string SfM4000w0p3_3 = getFileName(dir ,ModelName,4000,0.3,3);

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
   
}


if(ModelName.find("Radion")!=string::npos)
{
  std::cout <<"Radion"<<std::endl;
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

//point of this function:
//write Pt over Eta for the leptonically and hadronically decaying W boson for electrons or muons 
//make the following distinctions:
//hWMu = All generated Events with Muons in final state i.e W-> mu,nu and W-> tau,nu -> mu, nu, nu, nu
//hWMu_rec = Muon Channel with all leptonic and B tagging Cuts and Vetos applied
//hWMu_NoVeto = with no Veto on reconstructed Events
//hWMu_NoLooseLeptonVeto  = with no 2nd loose lepton veto
//hWMu_NoBVeto = with no B-tagged jet veto
  
TFile Wkinematics(filename,"RECREATE");

//same for Electron decay channel
 const Float_t xbinsW[16]={0,200,250,300,400,500,600,700,800,1000,1200,1500,2000,2500,3000,4000};
 const Float_t ybinsW[10]={0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};
 

 
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

 

 
 TLorentzVector W_lep;
 TLorentzVector W_had;
 TLorentzVector l;
 
 int events=0;
 int selected_events=0;
 int events_lepton=0;
 
 for(int i=0;i<howmany;i++)
   {
     
      t12->fChain->GetEntry(i);
    events+=1;
     if(generatedEventSelection(pdgId,t12)==0)
       continue;
     
 
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
       
  }
  
 std::cout << " number of all events " << events<< std::endl;
 std::cout << " number of selected events " << selected_events<< std::endl;
 std::cout<< "number of leptonic selected events " << events_lepton << std::endl;
 
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
 
 Wkinematics.Close();

}
