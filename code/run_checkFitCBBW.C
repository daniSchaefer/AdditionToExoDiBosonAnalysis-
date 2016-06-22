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
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos2.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/HWWLVJRooPdfs.h"
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"

using namespace RooFit;

namespace{
  int loadMyLibraryTriggerFunc(){
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/General.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/HWWLVJRooPdfs.cxx+");
  gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
  gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos2.cc+");
 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

//run with: root -l
//.x run_checkFitCBBW.C("Wprime","had","HP","WZ_jjjj")
//fits the DCB to the narrow width sameple -> draws convolution width BW into Canvas with MC sample with width >0
//possible models: BulkGrav, Wprime, Zprime, Radion, RSGrav but look out: not all files for all models exist
//Ymax is the maximum for the y-Axis of the convolution plot -> must be set per hand to a value so that the plot looks good

void run_checkFitCBBW(string ModelName,string channel, string category,string decayMode,bool checkNarrow =0)
{
string VV = determineVV(decayMode);
string mode = determineSemilepHadOrLep(decayMode);
string logfileName = "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/log_GoodnessOfFit_WideSamples_"+ModelName+"_"+channel+".txt";
ofstream logfile;
logfile.open(logfileName,ios::ate);
std::cout << logfile.good() <<std::endl;
  
  
 if(checkNarrow)
{
 
//=============================================================
//========== check fit, narrow samples ========================
//=============================================================  

if(decayMode.find("jjjj")!=string::npos)
{
  int n =8;
  double mass_narrow[8]= {800,1200,1400,1600,1800,2500,3500,4500};
  for(int i=0;i<n;i++)
  {
    checkNarrowFit(mass_narrow[i],channel,ModelName,category,decayMode);	
  }
}
else
{
  double mass_narrow[12]= {800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
  for(int i=0;i<12;i++)
  {
    checkNarrowFit(mass_narrow[i],channel,ModelName,category,decayMode);	
  }
}

}  
else
{  
//=============================================================
//========== check fit for wide samples all selections applied=
//=============================================================  

double mass[5]={800,1200,2000,3000,4000};
double gamma[3]={0.1,0.2,0.3};

//Zprime
if(ModelName.find("Zprime")!=string::npos or ModelName.find("Wprime") !=string::npos)
{
 if(decayMode.find("jjjj")!=string::npos)
 {
  double yHAD[5][3]={{600,600,350},{400,300,400},{250,80,250},{300,200,150},{200,150,100}};
  for(int i=0;i<5;i++)
  {
    for(int l=0;l<3;l++)
    {
      checkFitCBBW(logfile,mass[i],gamma[l],channel,ModelName,category,decayMode,yHAD[i][l]);
    }
  }
  }
  else
  { 
  double y[5][3] ={{650,800,700},{600,700,600},{500,550,500},{700,400,300},{400,300,250}};
  for(int i=0;i<5;i++)
  {
    for(int l=0;l<3;l++)
    {
      checkFitCBBW(logfile,mass[i],gamma[l],channel,ModelName,category,decayMode,y[i][l]);
    }
  }
  }
}
//RSGrav
if(ModelName.find("RSGrav")!=string::npos)
{
  if(decayMode.find("jjjj")!=string::npos)
 {
  double yHAD[5][3]={{600,600,350},{350,250,200},{200,200,200},{200,150,100},{150,100,100}};
  for(int i=0;i<5;i++)
  {
    for(int l=0;l<3;l++)
    {
      checkFitCBBW(logfile,mass[i],gamma[l],channel,ModelName,category,decayMode,yHAD[i][l]);
    }
  }
  }
  else
  {
    double  y[5][3]={{300,200,400},{400,300,350},{300,400,300},{400,300,250},{400,300,250}};
    for(int i=0;i<5;i++)
    {
      for(int l=0;l<3;l++)
      {
	checkFitCBBW(logfile,mass[i],gamma[l],channel,ModelName,category,decayMode,y[i][l]);
      }
    }
  }
}
//Radion
if(ModelName.find("Radion")!=string::npos)
{
 if(decayMode.find("jjjj")!=string::npos)
 {
  double yHAD[5][3]={{600,600,350},{350,250,200},{200,200,200},{200,150,100},{150,100,100}};
  for(int i=0;i<5;i++)
  {
    for(int l=0;l<3;l++)
    {
      checkFitCBBW(logfile,mass[i],gamma[l],channel,ModelName,category,decayMode,yHAD[i][l]);
    }
  }
  }
  else
  {
    double y[5][3]={{600,600,350},{500,350,350},{350,500,400},{400,300,250},{400,300,250}};
    for(int i=0;i<5;i++)
    {
      for(int l=0;l<3;l++)
      {
	checkFitCBBW(logfile,mass[i],gamma[l],channel,ModelName,category,decayMode,y[i][l]);
      }
  
    }
  }
}


std::cout << logfile.good() <<std::endl;

}
//=======================================================================
//========== check fit for wide samples, matched jets no hadron sel.=====
//=======================================================================

/*
double mass[5]={800,1200,2000,3000,4000};
double gamma[3]={0.1,0.2,0.3};

//Zprime
if(ModelName.find("Zprime")!=string::npos or ModelName.find("Wprime") !=string::npos)
{
 double y[5][3] ={{650,800,700},{600,700,600},{500,550,500},{700,400,300},{400,300,250}};
 for(int i=0;i<5;i++)
{
  for(int l=0;l<3;l++)
  {
    checkFitCBBW(logfile,mass[i],gamma[l],channel,ModelName,category,y[i][l],0,0,1);
  }
  
}
}
//RSGrav
if(ModelName.find("RSGrav")!=string::npos)
{
double  y[5][3]={{300,200,400},{400,300,350},{300,400,300},{400,300,250},{400,300,250}};
for(int i=0;i<5;i++)
{
  for(int l=0;l<3;l++)
  {
    checkFitCBBW(logfile,mass[i],gamma[l],channel,ModelName,category,y[i][l],0,0,1);
  }
  
}
}
//Radion
if(ModelName.find("Radion")!=string::npos)
{
 double y[5][3]={{600,600,350},{500,350,350},{350,500,400},{400,300,250},{400,300,250}};
 for(int i=0;i<5;i++)
{
  for(int l=0;l<3;l++)
  {
    checkFitCBBW(logfile,mass[i],gamma[l],channel,ModelName,category,y[i][l],0,0,1);
  }
  
}
}*/



  
  logfile.close();
}