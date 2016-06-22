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
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C+");

 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

//run like this:
//root -l
//.x makeRootFileForCheckFitCBBW("Wprime","mu",3000,0.1,1)
//numberFiles is the number of files the root tree of this sample is split into
//channel must be lower case!

void makeRootFileForCheckFitCBBW(string ModelName,string channel,float mass, float width,int numberFiles)
{
  std::ostringstream s;
  s<< mass;
  std::string smass(s.str());
  std::ostringstream ss; int temp_width = width*10;
  ss<<temp_width;
  std::string swidth(ss.str());
  string sfileName="/storage/a/mmozer/Res_Sig/";
  string sfileName1="/storage/a/mmozer/Res_Sig/";
  string sfileName2="/storage/a/mmozer/Res_Sig/";
  string soutput_filename = "/usr/users/dschaefer/root/results/"+ModelName+"/"+ModelName+"_M"+smass+"_width0p"+swidth+"_mWW_"+channel+".root";
  
  if(ModelName.find("Wprime") !=string::npos)
  {
    if(width==0.0)
    {
   sfileName ="/storage/a/mmozer/Res_Sig/"+ModelName+"ToWZToWlepZhad_narrow_M-"+smass+"/EXOVVTree_"+ModelName+"ToWZToWlepZhad_narrow_M-"+smass+"_1.root";
    }
    else
    {
      sfileName ="/storage/a/mmozer/Res_Sig/"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"_1.root";
      sfileName1 ="/storage/a/mmozer/Res_Sig/"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"_2.root";
      sfileName2 ="/storage/a/mmozer/Res_Sig/"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"_3.root";
    }
  }
  if(ModelName.find("Radion") != string::npos or ModelName.find("Zprime") != string::npos or ModelName.find("RSGrav") != string::npos )
  {
    if(width==0.0)
    {
      std::cout << " no narrow width sample exists" <<std::endl;
   //sfileName ="/storage/a/mmozer/Res_Sig/"+ModelName+"ToWZToWlepZhad_narrow_M-"+smass+"/EXOVVTree_"+ModelName+"ToWZToWlepZhad_narrow_M-"+smass+"_1.root";
    }
    else
    {
      sfileName ="/storage/a/mmozer/Res_Sig/"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"_1.root";
      sfileName1 ="/storage/a/mmozer/Res_Sig/"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"_2.root";
      sfileName2 ="/storage/a/mmozer/Res_Sig/"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"_3.root";
    }
  }
  
   if(ModelName.find("BulkGrav") != string::npos)
  {
    if(width==0.0)
    {
      
   sfileName ="/storage/a/mmozer/Res_Sig/"+ModelName+"ToWWToWlepWhad_narrow_M_"+smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_narrow_M_"+smass+"_1.root";
    }
    else
    {
      std::cout << " no width sample exists" <<std::endl;
//       sfileName ="/storage/a/mmozer/Res_Sig/"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"_1.root";
//       sfileName1 ="/storage/a/mmozer/Res_Sig/"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"_2.root";
//       sfileName2 ="/storage/a/mmozer/Res_Sig/"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_width0p"+swidth+"_M-"+smass+"_3.root";
    }
  }
  const char* fileName = sfileName.c_str();
  //const char* fileName1 = sfileName1.c_str();
  const char* fileName2 = sfileName1.c_str();
  const char* fileName3 = sfileName2.c_str();
  const char* output_filename = soutput_filename.c_str();
//   const char* input_filename1 ="/storage/a/mmozer/Res_Sig/RadionToWWToWlepWhad_width0p3_M-800/EXOVVTree_RadionToWWToWlepWhad_width0p3_M-800_1.root";
//   const char* input_filename2 ="/storage/a/mmozer/Res_Sig/RadionToWWToWlepWhad_width0p3_M-800/EXOVVTree_RadionToWWToWlepWhad_width0p3_M-800_2.root";
//   const char* input_filename3 ="/storage/a/mmozer/Res_Sig/RadionToWWToWlepWhad_width0p3_M-800/EXOVVTree_RadionToWWToWlepWhad_width0p3_M-800_3.root";
  
  TFile mWWSpectrum(output_filename,"RECREATE");
  TH1F* hmWW;
  if(mass ==800)
  {
    hmWW = new TH1F("hmWW","mWW spectrum",100,mass-mass/3.,1300);
  }
  else
  {
  hmWW = new TH1F("hmWW","mWW spectrum",100,mass-mass/3.,mass+mass/3.);
  }
  TChain tree("ntuplizer/tree");
  if(numberFiles ==1)
  {
  tree.Add(fileName);
  }
  if(numberFiles==2)
  {
   tree.Add(fileName2);
   tree.Add(fileName);
  }
   if(numberFiles==3)
  {
   tree.Add(fileName2);
   tree.Add(fileName);
   tree.Add(fileName3);
  }
 
  
  MyClass* t12 = new MyClass(&tree);
  int howmany = t12->fChain->GetEntries();
  
  int pdgId= 13;
  if(channel.find("el") != string::npos)
  {pdgId =11;}
  TLorentzVector W_lep;
  TLorentzVector W_had;
  for(int i=0;i<howmany;i++)
  {
  
    t12->fChain->GetEntry(i);
    if(!generatedEventSelection(pdgId,t12))
       continue;
    if(!applyVetos(pdgId,t12))
      continue;
    if(!applyLeptonSelection_NoVeto(pdgId,t12))
      continue;
    if(!applyMET(pdgId,t12))
      continue;
    if(!applyHadronSelection(t12,1,0,1,1))
      continue;
    if(!applyTrigger(pdgId,t12))
      continue;
    W_had = reconstructHadronicWOrZ(t12,1,1);
    W_lep = reconstructLeptonicW(pdgId,t12);
    TLorentzVector l     = reconstructLepton(pdgId,t12);
    TLorentzVector n = W_lep - l;
    if(!applyBackToBackTopology(l ,W_had,W_lep,n)) continue;
    hmWW->Fill((W_had+W_lep).M());
  }
  hmWW->Write();
  mWWSpectrum.Close();
}