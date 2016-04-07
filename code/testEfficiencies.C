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



 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}



void testEfficiencies(string ModelName, string channel)
{
    TChain tree("ntuplizer/tree");
    string dir = "/storage/a/mmozer/Res_Sig/";
    const char* filename;
    int pdgId =13;
    if(channel.find("el") != string::npos or channel.find("El")!=string::npos)
    {pdgId=11;}
    string  SfM800w0p0_1 = (getFileName(dir,ModelName,800,0.0,1));
    string  SfM1200w0p0_1 = getFileName(dir,ModelName,1200,0.0,1);
    string  SfM1400w0p0_1 = getFileName(dir,ModelName,1400,0.0,1);
    string  SfM1600w0p0_1 = getFileName(dir,ModelName,1600,0.0,1);
    string  SfM1800w0p0_1 = getFileName(dir,ModelName,1800,0.0,1);
    string  SfM2000w0p0_1 = getFileName(dir,ModelName,2000,0.0,1);
    string  SfM2500w0p0_1 = getFileName(dir,ModelName,2500,0.0,1);
    string  SfM3000w0p0_1 = getFileName(dir,ModelName,3000,0.0,1);
    string  SfM3500w0p0_1 = getFileName(dir,ModelName,3500,0.0,1);
    string  SfM4000w0p0_1 = getFileName(dir,ModelName,4000,0.0,1);
    string  SfM4500w0p0_1 = getFileName(dir,ModelName,4500,0.0,1);
    
    const char* fM800w0p0_1 =   SfM800w0p0_1.c_str();
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
    
    
    
    string  SfM800w0p1_1 =  getFileName(dir,ModelName,800,0.1,1);
    string  SfM1200w0p1_1 = getFileName(dir,ModelName,1200,0.1,1);
    string  SfM2000w0p1_1 = getFileName(dir,ModelName,2000,0.1,1);
    string  SfM3000w0p1_1 = getFileName(dir,ModelName,3000,0.1,1);
    string  SfM4000w0p1_1 = getFileName(dir,ModelName,4000,0.1,1);
    string  SfM800w0p1_2 =  getFileName(dir,ModelName,800,0.1,2);
    string  SfM1200w0p1_2 = getFileName(dir,ModelName,1200,0.1,2);
    string  SfM2000w0p1_2 = getFileName(dir,ModelName,2000,0.1,2);
    string  SfM3000w0p1_2 = getFileName(dir,ModelName,3000,0.1,2);
    string  SfM4000w0p1_2 = getFileName(dir,ModelName,4000,0.1,2);
    string  SfM800w0p1_3 =  getFileName(dir,ModelName,800,0.1,3);
    string  SfM1200w0p1_3 = getFileName(dir,ModelName,1200,0.1,3);
    string  SfM2000w0p1_3 = getFileName(dir,ModelName,2000,0.1,3);
    string  SfM3000w0p1_3 = getFileName(dir,ModelName,3000,0.1,3);
    string  SfM4000w0p1_3 = getFileName(dir,ModelName,4000,0.1,3);
    
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
    
    
    string SfM800w0p2_1 =  getFileName(dir,ModelName,800,0.2,1);
    string SfM1200w0p2_1 = getFileName(dir,ModelName,1200,0.2,1);
    string SfM2000w0p2_1 = getFileName(dir,ModelName,2000,0.2,1);
    string SfM3000w0p2_1 = getFileName(dir,ModelName,3000,0.2,1);
    string SfM4000w0p2_1 = getFileName(dir,ModelName,4000,0.2,1);
    string SfM800w0p2_2 =  getFileName(dir,ModelName,800,0.2,2);
    string SfM1200w0p2_2 = getFileName(dir,ModelName,1200,0.2,2);
    string SfM2000w0p2_2 = getFileName(dir,ModelName,2000,0.2,2);
    string SfM3000w0p2_2 = getFileName(dir,ModelName,3000,0.2,2);
    string SfM4000w0p2_2 = getFileName(dir,ModelName,4000,0.2,2);
    string SfM800w0p2_3 =  getFileName(dir,ModelName,800,0.2,3);
    string SfM1200w0p2_3 = getFileName(dir,ModelName,1200,0.2,3);
    string SfM2000w0p2_3 = getFileName(dir,ModelName,2000,0.2,3);
    string SfM3000w0p2_3 = getFileName(dir,ModelName,3000,0.2,3);
    string SfM4000w0p2_3 = getFileName(dir,ModelName,4000,0.2,3);
    
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
                                              
    string SfM800w0p3_1 =  getFileName(dir,ModelName,800,0.3,1);
    string SfM1200w0p3_1 = getFileName(dir,ModelName,1200,0.3,1);
    string SfM2000w0p3_1 = getFileName(dir,ModelName,2000,0.3,1);
    string SfM3000w0p3_1 = getFileName(dir,ModelName,3000,0.3,1);
    string SfM4000w0p3_1 = getFileName(dir,ModelName,4000,0.3,1);
    string SfM800w0p3_2 =  getFileName(dir,ModelName,800,0.3,2);
    string SfM1200w0p3_2 = getFileName(dir,ModelName,1200,0.3,2);
    string SfM2000w0p3_2 = getFileName(dir,ModelName,2000,0.3,2);
    string SfM3000w0p3_2 = getFileName(dir,ModelName,3000,0.3,2);
    string SfM4000w0p3_2 = getFileName(dir,ModelName,4000,0.3,2);
    string SfM800w0p3_3 =  getFileName(dir,ModelName,800,0.3,3);
    string SfM1200w0p3_3 = getFileName(dir,ModelName,1200,0.3,3);
    string SfM2000w0p3_3 = getFileName(dir,ModelName,2000,0.3,3);
    string SfM3000w0p3_3 = getFileName(dir,ModelName,3000,0.3,3);
    string SfM4000w0p3_3 = getFileName(dir,ModelName,4000,0.3,3);

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
   tree.Add(fM1200w0p0_1);
   tree.Add(fM1400w0p0_1);
   tree.Add(fM1600w0p0_1);
   tree.Add(fM1800w0p0_1);
   tree.Add(fM2000w0p0_1);
   tree.Add(fM2500w0p0_1);
   tree.Add(fM3000w0p0_1);
   tree.Add(fM3500w0p0_1);
   //tree.Add(fM4000w0p0_1);
   tree.Add(fM4500w0p0_1);
    if(pdgId ==11)
   {filename = "BulkGravToWKinematicsEl_testEff.root";}
   else 
   {filename = "BulkGravToWKinematicsMu_testEff.root";}
 
}

if(ModelName.find("Wprime") !=string::npos)
{
  std::cout <<"Wprime"<<std::endl;
//    tree.Add(fM800w0p0_1);
//    tree.Add(fM1200w0p0_1);
//    tree.Add(fM1400w0p0_1);
//    //tree.Add(fM1600w0p0_1);
//    tree.Add(fM1800w0p0_1);
//    tree.Add(fM2000w0p0_1);
//    tree.Add(fM2500w0p0_1);
//    tree.Add(fM3000w0p0_1);
//    tree.Add(fM3500w0p0_1);
//    tree.Add(fM4000w0p0_1);
   
   tree.Add(fM800w0p2_1);
   tree.Add(fM800w0p2_2);
   tree.Add(fM800w0p3_1);
   tree.Add(fM800w0p3_2);
   tree.Add(fM800w0p3_3);
   tree.Add(fM1200w0p2_1);
   tree.Add(fM1200w0p3_1);
   tree.Add(fM1200w0p3_2);
   tree.Add(fM2000w0p1_1);
   tree.Add(fM2000w0p3_2);
   tree.Add(fM2000w0p3_1);
   tree.Add(fM3000w0p1_1);
   tree.Add(fM3000w0p2_1);
   tree.Add(fM4000w0p1_1);
   tree.Add(fM4000w0p1_2);
   tree.Add(fM4000w0p3_1);
   tree.Add(fM4000w0p3_2);
 
   
    if(pdgId ==11)
   {filename = "WprimeToWKinematicsEl_testEff.root";}
   else 
   {filename = "WprimeToWKinematicsMu_testEff.root";}
}


if(ModelName.find("Radion")!=string::npos)
{
  std::cout <<"Radion"<<std::endl;
  tree.Add(fM800w0p2_1);
   tree.Add(fM800w0p3_1);
   tree.Add(fM800w0p3_3);
   tree.Add(fM800w0p3_2);
   tree.Add(fM1200w0p3_1);
   tree.Add(fM1200w0p3_2);
   tree.Add(fM2000w0p2_1);
   tree.Add(fM2000w0p2_2);
   tree.Add(fM2000w0p3_1);
   tree.Add(fM3000w0p1_1);
   tree.Add(fM3000w0p1_2);
   tree.Add(fM3000w0p3_1);
   tree.Add(fM4000w0p3_1);
   tree.Add(fM4000w0p3_2);
  
   if(pdgId ==11)
   {filename = "RadionToWKinematicsEl_testEff.root";}
   else 
   {filename = "RadionToWKinematicsMu_testEff.root";}
}

if(ModelName.find("RSGrav")!= string::npos)
{
  std::cout <<"RSGrav"<<std::endl;

   tree.Add(fM800w0p1_1);
   tree.Add(fM800w0p1_2);
   tree.Add(fM800w0p3_1);
   tree.Add(fM1200w0p1_1);
   tree.Add(fM1200w0p2_1); 
   tree.Add(fM1200w0p2_2);
   tree.Add(fM1200w0p3_1);
   tree.Add(fM1200w0p3_2);
   tree.Add(fM2000w0p1_1);
   tree.Add(fM2000w0p2_1);
   tree.Add(fM2000w0p2_2);
   tree.Add(fM3000w0p1_1);
   tree.Add(fM3000w0p2_1);
   tree.Add(fM3000w0p3_1);
   tree.Add(fM4000w0p1_1);
   tree.Add(fM4000w0p2_1);
   if(pdgId ==11)
   {filename = "RSGravToWKinematicsEl_testEff.root";}
   else 
   {filename = "RSGravToWKinematicsMu_testEff.root";}
 
}


if(ModelName.find("Zprime")!= string::npos)
{
  std::cout <<"Zprime"<<std::endl;
 
   tree.Add(fM800w0p1_1);
   tree.Add(fM800w0p3_1);
   tree.Add(fM1200w0p2_1); 
   tree.Add(fM1200w0p2_2);
   tree.Add(fM1200w0p3_1);
   tree.Add(fM2000w0p1_1);
   tree.Add(fM2000w0p1_2);
   tree.Add(fM2000w0p2_1);
   tree.Add(fM3000w0p1_1);
   tree.Add(fM3000w0p2_1);
   tree.Add(fM3000w0p2_2);
   tree.Add(fM3000w0p3_1);
   tree.Add(fM4000w0p1_1);
   tree.Add(fM4000w0p2_1);
   tree.Add(fM4000w0p3_1);
   if(pdgId ==11)
   {filename = "ZprimeToWKinematicsEl_testEff.root";}
   else 
   {filename = "ZprimeToWKinematicsMu_testEff.root";}
 
}

MyClass* t12 = new MyClass(&tree);
int howmany = t12->fChain->GetEntries();
std::cout<<" the files have " <<howmany << " events in total" <<std::endl;

const char* BGEff ="/storage/jbod/dschaefer/EfficiencyHistos/BulkGravToWKinematicsEl.root";
if(channel.find("mu")!=string::npos)
{
 BGEff = "/storage/jbod/dschaefer/EfficiencyHistos/BulkGravToWKinematicsMu.root"; 
}
string outputDirectory = "/storage/jbod/dschaefer/testEff/";
string NameOutputFile = outputDirectory+filename;

 
 int nBinsX = 16;
 int nBinsY = 10;
 vector<double> BinsX={0,200,250,300,400,500,600,700,800,1000,1200,1500,2000,2500,3000,4000};
 vector<double> BinsY={0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};
 double scale=1;

TFile *f = new TFile(BGEff,"READ");
TH2F* hLep_rec = (TH2F*) f->Get("hW_lep_rec");
TH2F* hHad_rec = (TH2F*) f->Get("hW_had_rec");
TH2F* hLep_genWV = (TH2F*) f->Get("hW_lep_genWithVeto");
TH2F* hLep_genBV = (TH2F*) f->Get("hW_lep_genWithBVeto");
TH2F* hLep_gen  = (TH2F*) f->Get("hW_lep_gen");
TH2F* hLep_genLLV = (TH2F*) f->Get("hW_lep_genWithLooseLeptonVeto");
TH2F* hHad_gen = (TH2F*) f->Get("hW_had_genWithVeto");

TH2* hLepEff = GetEfficiencies(hLep_rec,hLep_genWV);
TH2* hHadEff = GetEfficiencies(hHad_rec,hHad_gen);
 
TH2* hBTagEff = GetEfficiencies(hLep_genBV,hLep_gen);
TH2* hLLVetoEff = GetEfficiencies(hLep_genLLV,hLep_gen);

vector<double> BV = SumOverAllFilledBins(hBTagEff,nBinsX,nBinsY);
double BVEff = BV[1]/BV[0];
vector<double> LLV = SumOverAllFilledBins(hLLVetoEff,nBinsX,nBinsY);
double LLVEff = LLV[1]/LLV[0];

vector<vector<double> > leptonEff = MakeListOfWeights(hLepEff,BinsX,BinsY);
vector<vector<double> > hadronEff = MakeListOfWeights(hHadEff,BinsX,BinsY);

if(ModelName.find("RSGrav") != string::npos)
{
  scale = 1/1.30528;
}

testEfficiency(ModelName,channel,t12,NameOutputFile,hadronEff,leptonEff,BVEff,LLVEff,scale);


}