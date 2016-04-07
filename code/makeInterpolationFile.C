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

 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}


void makeInterpolationFile(string channel, string category, bool Overwrite =0)
{
  
 
 TFile* f_with_Eff = new TFile();
  int n= 11;
  double mass[11] = {800/*,1000*/,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
  double Dmass[11] = {0,0,0,0,0,0,0,0,0,0,0};
  double CB_mean   [n];
  double CB_Dmean  [n];
  double CB_sigma  [n];
  double CB_Dsigma [n];
  double CB_n1     [n];
  double CB_Dn1    [n];
  double CB_n2     [n];
  double CB_Dn2    [n];
  double CB_alpha1 [n];
  double CB_Dalpha1[n];
  double CB_alpha2 [n];
  double CB_Dalpha2[n];
  
  
  double Eff[n];
  double lumi[n];
  double Number[n];
  double DNumber[n];
  
  string filename = "/home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/interpolationFiles/BulkG_WW_lvjj_"+channel+"_"+category+"_my.root";
  if(Overwrite)
  {
    filename = "/home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/interpolationFiles/BulkG_WW_lvjj_"+channel+"_"+category+".root";
  }
  
  for(int i=0;i<n;i++)
  {
 
  string suffix = "M"+std::to_string(int(mass[i]))+"_"+channel+"_"+category;//+"_debug";
  
  string SfileName = "/usr/users/dschaefer/root/results/testFit/semileptonic/ToWW/logfiles/Narrow_Fit_"+suffix+".txt";
  const char* fileName = SfileName.c_str();
  //use the file with histo for efficiency test, in order to get the number of signal events for the extrapolation of Ndatacard !
   string file_with_Eff = "/storage/jbod/dschaefer/testEff/BulkGravToWKinematics_"+channel+"_"+category+"_M"+std::to_string(int(mass[i]))+"_width0p0_testEff.root";
  
  
  RooRealVar mean(("mean_CB_"+suffix).c_str(),("mean_CB_"+suffix).c_str(),0);
  RooRealVar alpha1(("alpha1_CB_"+suffix).c_str(),("alpha1_CB_"+suffix).c_str(),0);
  RooRealVar alpha2(("alpha2_CB_"+suffix).c_str(),("alpha2_CB_"+suffix).c_str(),0);
  RooRealVar  sigma(("sigma_CB_"+suffix).c_str(),("sigma_CB_"+suffix).c_str(),0);
  RooRealVar     n1(("n1_CB_"+suffix).c_str(),("n1_CB_"+suffix).c_str(),0);
  RooRealVar     n2(("n2_CB_"+suffix).c_str(),("n2_CB_"+suffix).c_str(),0);
  
  
  
  RooArgSet* FitParameters = new RooArgSet(mean,sigma,alpha1,alpha2,n1,n2);
  
  
  FitParameters->readFromFile(fileName,"READ",0,kTRUE);
  std::cout<< mean.getValV() <<std::endl;
  std::cout<<mean.getError() << std::endl;

  double m = mean.getValV();
  double Dm = mean.getError();
  double a1 =  alpha1.getValV();
  double Da1 = alpha1.getError();
  double a2 = alpha2.getValV();
  double Da2 = alpha2.getError();
  double s = sigma.getValV();
  double Ds = sigma.getError();
  double dn1 = n1.getValV();
  double Ddn1 = n1.getError();
  double dn2 = n2.getValV();
  double Ddn2 = n2.getError();
  
  
  
  std::cout<< "alpha1 " <<a1 << std::endl;
  std::cout<< "alpha2 " <<alpha2.getValV() << std::endl;

  std::cout<< "n1 " <<n1.getValV() << std::endl;
  std::cout<< "n2 " <<n2.getValV() << std::endl;
  std::cout<< "sigma " << sigma.getValV() << std::endl;
  
   CB_mean   [i] = m;
   CB_Dmean  [i] = Dm;
   CB_sigma  [i] = s;
   CB_Dsigma [i] = Ds;
   CB_n1     [i] = dn1;
   CB_Dn1    [i] = Ddn1;
   CB_n2     [i] = dn2;
   CB_Dn2    [i] = Ddn2;
   CB_alpha1 [i] = a1;
   CB_Dalpha1[i] = Da1;
   CB_alpha2 [i] = a2;
   CB_Dalpha2[i] = Da2;
  
   
   //std::cout<< f_with_hmWW->Open(file_with_hmWW.c_str(),"READ")<< std::endl;
   TFile* tmp = f_with_Eff->Open(file_with_Eff.c_str(),"READ");
   TH2F* histo = (TH2F*) tmp->Get("hW_lep_rec");
   TH2F* histo2 = (TH2F*) tmp->Get("hW_lep_gen");
   if(channel.find("el")!=string::npos)
   {
   file_with_Eff = "/storage/jbod/dschaefer/testEff/BulkGravToWKinematics_mu_"+category+"_M"+std::to_string(int(mass[i]))+"_width0p0_testEff.root";
   }
   else
   {
    file_with_Eff = "/storage/jbod/dschaefer/testEff/BulkGravToWKinematics_el_"+category+"_M"+std::to_string(int(mass[i]))+"_width0p0_testEff.root"; 
   }
   f_with_Eff->Close();
   tmp = f_with_Eff->Open(file_with_Eff.c_str(),"READ");
   TH2F* histo3 = (TH2F*) tmp->Get("hW_lep_gen");
   //std::cout << histo<< std::endl;
   
   double NS = histo->GetEntries();
   Number[i] = NS;
   DNumber[i] = TMath::Sqrt(NS);
   double NSgen2 = histo3->GetEntries();
   double NSgen1 = histo2->GetEntries();
   double NSgen =  NSgen1 + NSgen2;
   double lumi = 2.10*1000;//NumberOfEventsInFile("BulkGrav",mass[i],0.0);
   double NSgenAll = NumberOfEventsInFile("BulkGrav",mass[i],0.0);
   Eff[i] = NS/NSgenAll*lumi*0.01;
   std::cout << Eff[i] <<std::endl;
   std::cout <<" Number of events : " << NS <<std::endl;
   std::cout <<" Number of events : " << NSgen <<std::endl;
   f_with_Eff->Close("R");
  }
  
  
  TCanvas* cc = new TCanvas("cc","cc",400,400);
  gPad->SetLeftMargin(0.15);
  cc->cd();
  TGraph* g_Ndatacard = new TGraph(n,mass,Eff);
  g_Ndatacard->SetName("Ndatacard");
  g_Ndatacard->GetYaxis()->SetTitle("Ndatacard");
  g_Ndatacard->GetXaxis()->SetTitle("m_{VV} [GeV]");
  g_Ndatacard->Draw("AL");
  
  TCanvas* cc1 = new TCanvas("cc1","cc1",400,400);
  gPad->SetLeftMargin(0.15);
  cc1->cd();
  TGraphErrors* g_number = new TGraphErrors(n,mass,Number, Dmass,DNumber);
  g_number->SetName("number");
  g_number->GetYaxis()->SetTitle("number");
  g_number->GetXaxis()->SetTitle("m_{VV} [GeV]");
  g_number->Draw("AL");
  
  
  TCanvas* c1 = new TCanvas("c1","c1",400,400);
  gPad->SetLeftMargin(0.15);
  c1->cd();
  TGraphErrors* g_alpha1 = new TGraphErrors(n,mass,CB_alpha1, Dmass,CB_Dalpha1);
  g_alpha1->SetName("alpha1");
  g_alpha1->GetYaxis()->SetTitle("alpha1");
  g_alpha1->GetXaxis()->SetTitle("m_{VV} [GeV]");
  g_alpha1->Draw("AL");
  
  TCanvas* c2 = new TCanvas("c2","c2",400,400);
  gPad->SetLeftMargin(0.15);
  c2->cd();
  TGraphErrors* g_alpha2 = new TGraphErrors(n,mass,CB_alpha2, Dmass,CB_Dalpha2);
  g_alpha2->SetName("alpha2");
  g_alpha2->GetYaxis()->SetTitle("alpha2");
  g_alpha2->GetXaxis()->SetTitle("m_{VV} [GeV]");
  g_alpha2->Draw("AL");
  
  
  TCanvas* c3 = new TCanvas("c3","c3",400,400);
  gPad->SetLeftMargin(0.15);
  c3->cd();
  TGraphErrors* g_mean = new TGraphErrors(n,mass,CB_mean, Dmass,CB_Dmean);
  g_mean->SetName("mean");
  g_mean->GetYaxis()->SetTitle("mean");
  g_mean->GetXaxis()->SetTitle("m_{VV} [GeV]");
  g_mean->Draw("AL");
  
  TCanvas* c4 = new TCanvas("c4","c4",400,400);
  gPad->SetLeftMargin(0.15);
  c4->cd();
  TGraphErrors* g_n1 = new TGraphErrors(n,mass,CB_n1, Dmass,CB_Dn1);
  g_n1->SetName("n1");
  g_n1->GetYaxis()->SetTitle("n1");
  g_n1->GetXaxis()->SetTitle("m_{VV} [GeV]");
  g_n1->Draw("AL");
  
  TCanvas* c5 = new TCanvas("c5","c5",400,400);
  gPad->SetLeftMargin(0.15);
  c5->cd();
  TGraphErrors* g_n2 = new TGraphErrors(n,mass ,CB_n2, Dmass,CB_Dn2);
  g_n2->SetName("n2");
   g_n2->GetYaxis()->SetTitle("n2");
  g_n2->GetXaxis()->SetTitle("m_{VV} [GeV]");
  g_n2->Draw("AL");
  
  TCanvas* c6 = new TCanvas("c6","c6",400,400);
  gPad->SetLeftMargin(0.15);
  c6->cd();
  TGraphErrors* g_sigma = new TGraphErrors(n,mass,CB_sigma, Dmass,CB_Dsigma);
  g_sigma->SetName("sigma");
  g_sigma->GetYaxis()->SetTitle("sigma");
  g_sigma->GetXaxis()->SetTitle("m_{VV} [GeV]");
  g_sigma->Draw("AL");
  
 
  TFile* f= new TFile(filename.c_str(),"RECREATE");
  
  g_alpha1->Write();
  g_alpha2->Write();
  g_mean->Write();
  g_n1->Write();
  g_n2->Write();
  g_sigma->Write();
  g_Ndatacard->Write();
  g_number->Write();
  
  
}