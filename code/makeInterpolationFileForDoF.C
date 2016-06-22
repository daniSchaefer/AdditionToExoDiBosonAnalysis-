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
#include "/home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/PDFs/HWWLVJRooPdfs.h"
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
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/HWWLVJRooPdfs.cxx+");
 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void makeInterpolationFileForDoF(string ModelName, string category,string decayMode="WW_lvjj")
{
 string VV = determineVV(decayMode);
 string mode = determineSemilepHadOrLep(decayMode);
  
 string input_directory =  "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/logfiles/";
 
 string filename = input_directory+"InterpolateHighMassCorrections_"+ModelName+"_"+category+".root";;
 if(decayMode.find("lvjj")!=string::npos)
 {
   filename = "/home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/interpolationFiles/InterpolateHighMassCorrections_"+ModelName+"_"+category+".root";
 }
   

 double mass[2]={3000,4000};
 double Dmass[2]={0,0};
 double gamma[3]={0.1,0.2,0.3};
 double D_gamma[3]={0,0,0};
 double a0_el_M3000[3];
 double D_a0_el_M3000[3];
 double a0_mu_M3000[3];
 double D_a0_mu_M3000[3];
 double a0_el_M4000[3];
 double D_a0_el_M4000[3];
 double a0_mu_M4000[3];
 double D_a0_mu_M4000[3];
 
 string wide_fit_file_name;
// string category = "HPZ";
// string ModelName = "Radion";
  RooRealVar a0("a0","a0",0);
  RooArgSet* FitParameter = new RooArgSet(a0);
 
 for(int i=0;i<3;i++)
 {
   wide_fit_file_name = input_directory+ModelName+"_Fit_M"+std::to_string(int(mass[0]))+"_width0p"+std::to_string(int(gamma[i]*10))+"_el_"+category+".txt";
   std::cout<<wide_fit_file_name <<std::endl;
  
   FitParameter->readFromFile(wide_fit_file_name.c_str(),"READ",0,kTRUE);
   std::cout << a0.getValV()<<std::endl;
   std::cout << a0.getError()<<std::endl;
   a0_el_M3000[i] = a0.getValV();
   D_a0_el_M3000[i] = a0.getError();
   
   wide_fit_file_name = input_directory+ModelName+"_Fit_M"+std::to_string(int(mass[0]))+"_width0p"+std::to_string(int(gamma[i]*10))+"_mu_"+category+".txt";
   std::cout<<wide_fit_file_name <<std::endl;
    FitParameter->readFromFile(wide_fit_file_name.c_str(),"READ",0,kTRUE);
   std::cout << a0.getValV()<<std::endl;
   std::cout << a0.getError()<<std::endl;
   a0_mu_M3000[i] = a0.getValV();
   D_a0_mu_M3000[i] = a0.getError();
   
   wide_fit_file_name = input_directory+ModelName+"_Fit_M"+std::to_string(int(mass[1]))+"_width0p"+std::to_string(int(gamma[i]*10))+"_el_"+category+".txt";
   std::cout<<wide_fit_file_name <<std::endl;
  
   FitParameter->readFromFile(wide_fit_file_name.c_str(),"READ",0,kTRUE);
   std::cout << a0.getValV()<<std::endl;
   std::cout << a0.getError()<<std::endl;
   a0_el_M4000[i] = a0.getValV();
   D_a0_el_M4000[i] = a0.getError();
   
   wide_fit_file_name = input_directory+ModelName+"_Fit_M"+std::to_string(int(mass[1]))+"_width0p"+std::to_string(int(gamma[i]*10))+"_mu_"+category+".txt";
   std::cout<<wide_fit_file_name <<std::endl;
    FitParameter->readFromFile(wide_fit_file_name.c_str(),"READ",0,kTRUE);
   std::cout << a0.getValV()<<std::endl;
   std::cout << a0.getError()<<std::endl;
   a0_mu_M4000[i] = a0.getValV();
   D_a0_mu_M4000[i] = a0.getError();
   
 }
 
 TGraphErrors* In_HighMassCorrections_mu = new TGraphErrors(3,gamma,a0_mu_M4000,D_gamma,D_a0_mu_M4000);
 TGraphErrors* In_HighMassCorrections_el = new TGraphErrors(3,gamma,a0_el_M4000,D_gamma,D_a0_el_M4000);
 In_HighMassCorrections_mu->SetTitle("a0_M4000_mu");
 In_HighMassCorrections_el->SetTitle("a0_M4000_el");
 
 TCanvas *InterpolateHighMassCorrections_mu  = new TCanvas("InterpolateHighMassCorrections_mu","mu",400,400);
 InterpolateHighMassCorrections_mu->cd();
 In_HighMassCorrections_mu->Draw("AL");
 
 TCanvas *InterpolateHighMassCorrections_el  = new TCanvas("InterpolateHighMassCorrections_el","el",400,400);
 InterpolateHighMassCorrections_el->cd();
 In_HighMassCorrections_el->Draw("AL");
 std::cout << In_HighMassCorrections_mu->Eval(0.15,0,"a") <<std::endl;
 
 TFile* f= new TFile(filename.c_str(),"RECREATE");
 In_HighMassCorrections_el->SetName("a0_over_gamma_M4000_el");
 In_HighMassCorrections_mu->SetName("a0_over_gamma_M4000_mu");
 In_HighMassCorrections_el->Write();
 In_HighMassCorrections_mu->Write();
 
 TGraphErrors* In_HighMassCorrections_mu_M3000 = new TGraphErrors(3,gamma,a0_mu_M3000,D_gamma,D_a0_mu_M3000);
 TGraphErrors* In_HighMassCorrections_el_M3000 = new TGraphErrors(3,gamma,a0_el_M3000,D_gamma,D_a0_el_M3000);
 In_HighMassCorrections_mu_M3000->SetTitle("a0_M3000_mu");
 In_HighMassCorrections_el_M3000->SetTitle("a0_M3000_el");
 
 TCanvas *InterpolateHighMassCorrections_mu_M3000  = new TCanvas("InterpolateHighMassCorrections_mu_M3000","mu",400,400);
 InterpolateHighMassCorrections_mu_M3000->cd();
 In_HighMassCorrections_mu_M3000->Draw("AL");
 
 TCanvas *InterpolateHighMassCorrections_el_M3000  = new TCanvas("InterpolateHighMassCorrections_el_M3000","el",400,400);
 InterpolateHighMassCorrections_el_M3000->cd();
 In_HighMassCorrections_el_M3000->Draw("AL");
 
 In_HighMassCorrections_el_M3000->SetName("a0_over_gamma_M3000_el");
 In_HighMassCorrections_mu_M3000->SetName("a0_over_gamma_M3000_mu");
 In_HighMassCorrections_el_M3000->Write();
 In_HighMassCorrections_mu_M3000->Write();
 
 
 
 
 double a_M_w1[2]= {a0_mu_M3000[0],a0_mu_M4000[0]};
 double D_a_M_w1[2]={D_a0_mu_M3000[0],D_a0_mu_M4000[0]};
 TGraphErrors * g_M_mu_w1 = new TGraphErrors(2,mass,a_M_w1,Dmass,D_a_M_w1);
  double a_M_w2[2]= {a0_mu_M3000[1],a0_mu_M4000[1]};
 double D_a_M_w2[2]={D_a0_mu_M3000[1],D_a0_mu_M4000[1]};
 TGraphErrors * g_M_mu_w2 = new TGraphErrors(2,mass,a_M_w2,Dmass,D_a_M_w2);
 double a_M_w3[2]= {a0_mu_M3000[2],a0_mu_M4000[2]};
 double D_a_M_w3[2]={D_a0_mu_M3000[2],D_a0_mu_M4000[2]};
 TGraphErrors * g_M_mu_w3 = new TGraphErrors(2,mass,a_M_w3,Dmass,D_a_M_w3);
 
 TCanvas* c_mass = new TCanvas("c_mass","a0 over mass: mu",400,400);
 g_M_mu_w3->Draw("AL");
 g_M_mu_w1->Draw("SAME");
 g_M_mu_w2->Draw("SAME");
 
 
 double a_M_w1_el[2]= {a0_el_M3000[0],a0_el_M4000[0]};
 double D_a_M_w1_el[2]={D_a0_el_M3000[0],D_a0_el_M4000[0]};
 TGraphErrors * g_M_el_w1 = new TGraphErrors(2,mass,a_M_w1_el,Dmass,D_a_M_w1_el);
  double a_M_w2_el[2]= {a0_el_M3000[1],a0_el_M4000[1]};
 double D_a_M_w2_el[2]={D_a0_el_M3000[1],D_a0_el_M4000[1]};
 TGraphErrors * g_M_el_w2 = new TGraphErrors(2,mass,a_M_w2_el,Dmass,D_a_M_w2_el);
 double a_M_w3_el[2]= {a0_el_M3000[2],a0_el_M4000[2]};
 double D_a_M_w3_el[2]={D_a0_el_M3000[2],D_a0_el_M4000[2]};
 TGraphErrors * g_M_el_w3 = new TGraphErrors(2,mass,a_M_w3_el,Dmass,D_a_M_w3_el);
 
 TCanvas* c_mass2 = new TCanvas("c_mass2","a0 over mass: el",400,400);
 g_M_el_w3->Draw("AL");
 g_M_el_w2->Draw("SAME");
 g_M_el_w1->Draw("SAME");
 
 g_M_mu_w1->SetName("a0_over_mass_w1_mu");
 g_M_mu_w2->SetName("a0_over_mass_w2_mu");
 g_M_mu_w3->SetName("a0_over_mass_w3_mu");
 g_M_el_w1->SetName("a0_over_mass_w1_el");
 g_M_el_w2->SetName("a0_over_mass_w2_el");
 g_M_el_w3->SetName("a0_over_mass_w3_el");
 
 
 g_M_mu_w1->Write();
 g_M_mu_w2->Write();
 g_M_mu_w3->Write();
 g_M_el_w1->Write();
 g_M_el_w2->Write();
 g_M_el_w3->Write();
  
}