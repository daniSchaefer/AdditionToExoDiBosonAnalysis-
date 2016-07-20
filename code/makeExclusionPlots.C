#include "TGraphAsymmErrors.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"
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
#include "/usr/users/dschaefer/root/headerfilesAllChannels/CrossSections.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/CrossSections2.h"
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
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/Op.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/EventSelection.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/GenFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/RecFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies2.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/CrossSections2.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/CrossSections.cc+");
    

 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}


FminusG* SetupRootFinding(std::string ModelName, std::string decayMode, double ktilde,TPad* pad);

void makeExclusionPlots(string ModelName, string decayMode)
{
  TStopwatch watch;
  watch.Start();
  string channel = "had";
  if(decayMode.find("lvjj")!=std::string::npos)
  {
   channel = "em"; 
  }
  
  TFile* file = new TFile(("/home/dschaefer/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/graphs_"+channel+".root").c_str(),"READ");
  string histoname = "ExclusionLimitOnEventNumber_BulkG_WW_em_HP";
  if(channel.find("had")!=std::string::npos)
  {
   histoname =  "ExclusionLimitOnEventNumber_BulkWW_had_HP";
  }
  TH2F* obsLim = dynamic_cast<TH2F*>(file->Get(histoname.c_str()));
  
  TGraph* iso0p05  = IsoKtilde(ModelName,decayMode,0.05);
  TGraph* iso0p03  = IsoKtilde(ModelName,decayMode,0.03);
  TGraph* iso0p095 = IsoKtilde(ModelName,decayMode,0.095);
  TGraph* iso0p12  = IsoKtilde(ModelName,decayMode,0.12);
  TGraph* iso0p20  = IsoKtilde(ModelName,decayMode,0.2);
  TGraph* iso0p30  = IsoKtilde(ModelName,decayMode,0.3);
  TGraph* iso0p40  = IsoKtilde(ModelName,decayMode,0.4);
  TGraph* iso0p15  = IsoKtilde(ModelName,decayMode,0.15);
  TGraph* isotest  = IsoKtilde(ModelName,decayMode,0.07);
  
  
  printWidthForKtilde(ModelName,0.15,4500,800);
  printWidthForKtilde(ModelName,0.07,4500,800);
  
  TCanvas* MyC = new TCanvas("MyC","MyC",800,600);
  MyC->SetRightMargin(0.19);
  MyC->SetLogz();
  obsLim->Draw("COLZ");
  SetGraphStyle(iso0p095,"#tilde{k} = 0.10",4000,0.22);
  SetGraphStyle(iso0p12,"#tilde{k} = 0.12",3700,0.31);
  SetGraphStyle(iso0p20,"#tilde{k} = 0.20",2280,0.31);
  SetGraphStyle(iso0p30,"#tilde{k} = 0.30",1500,0.31);
  SetGraphStyle(iso0p40,"#tilde{k} = 0.40",1000,0.31);
  SetGraphStyle(iso0p05,"#tilde{k} = 0.05",4000,0.05);
  SetGraphStyle(iso0p03,"#tilde{k} = 0.03",4000,0.011);
  SetGraphStyle(isotest,"#tilde{k} = 0.07",4000,0.11);
  SetGraphStyle(iso0p15,"#tilde{k} = 0.15",3000,0.31);
  
  iso0p095->Draw("CSame");
  iso0p12 ->Draw("CSame");
  iso0p20 ->Draw("CSame");
  iso0p30 ->Draw("CSame");
  iso0p40 ->Draw("CSame");
  iso0p05 ->Draw("CSame");
  iso0p03 ->Draw("CSame");
  iso0p15 ->Draw("Csame");
  isotest ->Draw("Csame");

  
 

  TCanvas* cm = new TCanvas("cm","cm",1600,1600);
  cm->Divide(3,3);
  TPad* p1 = dynamic_cast<TPad*>(cm->cd(1));
  TPad* p2 = dynamic_cast<TPad*>(cm->cd(2));
  TPad* p3 = dynamic_cast<TPad*>(cm->cd(3));
  TPad* p4 = dynamic_cast<TPad*>(cm->cd(4));
  TPad* p5 = dynamic_cast<TPad*>(cm->cd(5));
  TPad* p6 = dynamic_cast<TPad*>(cm->cd(6));
  TPad* p7 = dynamic_cast<TPad*>(cm->cd(7));
  
  FminusG* h_k0p095 = SetupRootFinding(ModelName,decayMode,0.095,p1);
  FminusG* h_k0p05  = SetupRootFinding(ModelName,decayMode,0.05,p2);
  FminusG* h_k0p03  = SetupRootFinding(ModelName,decayMode,0.03,p3);
  FminusG* h_k0p20  = SetupRootFinding(ModelName,decayMode,0.20,p4);
  FminusG* h_k0p12  = SetupRootFinding(ModelName,decayMode,0.12,p5);
  FminusG* h_k0p30  = SetupRootFinding(ModelName,decayMode,0.30,p6);
  //FminusG* h_k0p40  = SetupRootFinding(ModelName,decayMode,0.40,p7);
  
  
  double* roots = new double[9];
  double* kt    = new double[9];
  double* widths= new double[9];
  kt[0]    = 0.10;
  roots[0] = h_k0p095->GetRoot(2000,2100);
  widths[0] = iso0p095->Eval(roots[0]);
  kt[1]    = 0.05;
  roots[1] = h_k0p05->GetRoot(1800,1900);
  widths[1] = iso0p05->Eval(roots[1]);
  kt[2]    = 0.03;
  roots[2] = h_k0p03->GetRoot(1400,1500);
  widths[2] = iso0p03->Eval(roots[2]);
  kt[3]    = 0.12;
  roots[3] = h_k0p12->GetRoot(2100,2200);
  widths[3] = iso0p12->Eval(roots[3]);
  
  kt[4] = 0.03;
  roots[4] = h_k0p03->GetRoot(1100,1200);
  widths[4] = iso0p03->Eval(roots[4]);
  kt[5] = 0.03;
  roots[5] = h_k0p03->GetRoot(1200,1400);
  widths[5] = iso0p03->Eval(roots[5]);
  
  
  for(int i=0;i<9;i++)
  {
   std::cout <<kt[i] << " " << roots[i] << std::endl;   
  }
  
  TGraph* ExP = new TGraph(6,roots,widths);
  MyC->cd();
  ExP->SetMarkerStyle(4);
  ExP->Draw("Psame");
  
  watch.Stop();
  watch.Print();
 
}


FminusG* SetupRootFinding(std::string ModelName, std::string decayMode, double ktilde,TPad* pad)
{
  float* EffTimesAcc = getAcceptance(decayMode,ktilde);
  TF1* xs          = getTheoryCrossSectionFitted(ModelName,ktilde);
  //float m_xs[10]  =  {800,900,1000,1500,1800,2000,2500,3000,3500,4500};
  vector<float> masses = getMassesForKtilde(decayMode,ktilde);
  
  int n = masses.size();
  float* m_EffTimesAcc = new float[n];
  for(int i=0;i<n;i++)
  {
   m_EffTimesAcc[i]  = masses.at(i);   
  }
  
  //TGraph* g_xs       = new TGraph(10,m_xs,xs);
  TGraph* g_EffTimesAcc =new TGraph(n,m_EffTimesAcc,EffTimesAcc);
  
  
   
  TGraph* N_exp = getNumberOfExpectedEvents(xs,g_EffTimesAcc,ModelName,decayMode);
  TGraph* isoKtilde = IsoKtilde(ModelName,decayMode,ktilde);
  TGraph* obsLim  = getLimitOnNexpected(decayMode,isoKtilde);
  
  TF1* f = getFitFunction(N_exp);
  float massmin =800;
  if(decayMode.find("jjjj")!=std::string::npos){massmin =1200;}
  float massmax = findMassMaxForKtilde(ModelName,decayMode,ktilde);
  
  FminusG* h = new FminusG(f,obsLim,massmin,massmax);
  std::stringstream s;
  s << std::fixed << std::setprecision(2) << ktilde;
  std::string label = "k = "+s.str();
  h->Draw(pad,label);
  
//   TCanvas* t = new TCanvas("t","t",400,400);
//   //g_EffTimesAcc->Draw();
//   t->SetLogy();
//   N_exp->SetLineColor(kGreen);
//   N_exp->SetLineWidth(3);
//   f->SetLineColor(kRed);
//   N_exp->Draw();
//   TCanvas* t2 = new TCanvas("t2","t2",400,400);
//   f->Draw();
//   std::cout << n << std::endl;
  
  return h;
}
