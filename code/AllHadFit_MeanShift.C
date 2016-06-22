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


void AllHadFit_MeanShift(float mass)
{
  string directory = "/usr/users/dschaefer/root/results/misc/AllHadHistosForLimits/";
  
  
  vector<string> modelNames = {"Radion","Zprime","RSGrav","Wprime"};
  vector<float> width = {0.1,0.2,0.3};
  //vector<string> modelNames = {"BulkGrav"};
  //vector<float> width = {0.0};
 for(int w=0;w<width.size();w++)
 {
  for(int i=0;i<modelNames.size();i++)
  {
    std::cout << modelNames[i] << " "<< mass << " "<< width[w] <<std::endl;
    string outputFileName = directory+modelNames[i]+"_meanShift_WW_jjjj_M"+std::to_string(int(mass))+"_w0p"+std::to_string(int(10*width[w]))+".txt";
    
    RooFitResult* fit1 = AllHadFitMeanShift(modelNames[i],"HP",mass,width[w]);
    fit1->Print();
    RooArgList finalParam1 = fit1->floatParsFinal();
    RooArgSet *Set1 = new RooArgSet(finalParam1);
    Set1->writeToFile((outputFileName).c_str());  
  }
 }   
}