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
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies2.h"
#include "/usr/users/dschaefer/root/headerfiles/passed_mu_jes.h"
#include "/usr/users/dschaefer/root/headerfiles/Op.h"
#include "/usr/users/dschaefer/root/headerfiles/EventSelection.h"
#include "/usr/users/dschaefer/root/headerfiles/GenFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/RecFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc.h"
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
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
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

void run_PrintTablesForEffTests()
{
  vector<float> masses = {800,1200,1400,1800,2000,2500,3000,3500,4500};
  string category = "HP";
  PrintReconstructionEfficiencyTable("BulkGrav",category,masses,0.0,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the efficiency tables. The test was performed on the narrow width bulk graviton sample.");
  
  
  PrintReconstructionEfficiencyTable("Wprime",category,masses,0.0,"Comparison between the exact efficiencies for W$' \\rightarrow $ W Z using the full analysis selection and the efficiencies obtained using the efficiency tables extracted from the narrow width bulk graviton sample. ");
  
  vector<float> massesRSGRAV = {800,1200,2000,3000,4000};
  PrintReconstructionEfficiencyTable("RSGrav",category,massesRSGRAV,0.1,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a RS graviton sample. The hadronic W reconstruction efficiency has been corrected by a constant factor of 1.305 to take effects of W polaristion into account.");
  
  vector<float> massesZprime = {800,1200,2000,3000,4000};
  PrintReconstructionEfficiencyTable("Zprime",category,massesZprime,0.1,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a Z$'$ sample with $\\Gamma/M_x =0.1$.");
  
  vector<float> massesWprime = {800,1200,2000,3000,4000};
  PrintReconstructionEfficiencyTable("Wprime",category,massesWprime,0.1,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a W$' \\rightarrow$ WW sample with $\\Gamma/M_x =0.3$.");
  
  vector<float> massesRadion = {800,1200,2000,3000,4000};
  PrintReconstructionEfficiencyTable("Radion",category,massesRadion,0.1,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a Radion$ \\rightarrow$ WW sample with $\\Gamma/M_x =0.3$.");
  
  
  
  //===================================================================================
  //============= Make plots to test the dependance of the efficiency on width=========
  //===================================================================================
   string model = "Zprime";
  vector<vector<double> > eff_M800_w1 =  ExtractRecoAndTestEfficiency(model,category,800,0.1);
  vector<vector<double> > eff_M800_w2 =  ExtractRecoAndTestEfficiency(model,category,800,0.2);
  vector<vector<double> > eff_M800_w3 =  ExtractRecoAndTestEfficiency(model,category,800,0.3);
  vector<vector<double> > eff_M2000_w1 = ExtractRecoAndTestEfficiency(model,category,2000,0.1);
  vector<vector<double> > eff_M2000_w2 = ExtractRecoAndTestEfficiency(model,category,2000,0.2);
  vector<vector<double> > eff_M2000_w3 = ExtractRecoAndTestEfficiency(model,category,2000,0.3);
  vector<vector<double> > eff_M1200_w1 = ExtractRecoAndTestEfficiency(model,category,1200,0.1);
  vector<vector<double> > eff_M1200_w2 = ExtractRecoAndTestEfficiency(model,category,1200,0.2);
  vector<vector<double> > eff_M1200_w3 = ExtractRecoAndTestEfficiency(model,category,1200,0.3);
  vector<vector<double> > eff_M3000_w1 = ExtractRecoAndTestEfficiency(model,category,3000,0.1);
  vector<vector<double> > eff_M3000_w2 = ExtractRecoAndTestEfficiency(model,category,3000,0.2);
  vector<vector<double> > eff_M3000_w3 = ExtractRecoAndTestEfficiency(model,category,3000,0.3);
  vector<vector<double> > eff_M4000_w1 = ExtractRecoAndTestEfficiency(model,category,4000,0.1);
  vector<vector<double> > eff_M4000_w2 = ExtractRecoAndTestEfficiency(model,category,4000,0.2);
  vector<vector<double> > eff_M4000_w3 = ExtractRecoAndTestEfficiency(model,category,4000,0.3);
  
 
  TCanvas *c1_mu = new TCanvas();
  gPad->SetLeftMargin(0.15);
 double x_mu[3] ={0.1,0.2,0.3};
 double y_mu_M4000[3] ={eff_M4000_w1[0][0],eff_M4000_w2[0][0],eff_M4000_w3[0][0]};
 double ex_mu_M4000[3] = {0,0,0};
 double ey_mu_M4000[3] = {eff_M4000_w1[0][3],eff_M4000_w2[0][3],eff_M4000_w3[0][3]};
 TGraphErrors* g_mu_M4000 = new TGraphErrors(3,x_mu,y_mu_M4000,ex_mu_M4000,ey_mu_M4000);
 g_mu_M4000->SetMarkerColor(1);
 g_mu_M4000->SetMarkerStyle(21);
 g_mu_M4000->GetXaxis()->SetTitle("#Gamma / M_{x}");
 g_mu_M4000->GetYaxis()->SetTitleOffset(1.40);
 g_mu_M4000->SetMaximum(0.25);
 g_mu_M4000->SetMinimum(0.05);
 g_mu_M4000->GetYaxis()->SetTitle("Efficiency #times Acceptance");
 g_mu_M4000->SetTitle("");
 g_mu_M4000->Draw("AP");
 
 
 double y_mu_M3000[3] ={eff_M3000_w1[0][0],eff_M3000_w2[0][0],eff_M3000_w3[0][0]};
 double ex_mu_M3000[3] = {0,0,0};
 double ey_mu_M3000[3] = {eff_M3000_w1[0][3],eff_M3000_w2[0][3],eff_M3000_w3[0][3]};
 TGraphErrors* g_mu_M3000 = new TGraphErrors(3,x_mu,y_mu_M3000,ex_mu_M3000,ey_mu_M3000);
 g_mu_M3000->SetMarkerColor(2);
 g_mu_M3000->SetMarkerStyle(22);
 g_mu_M3000->SetTitle("");
 g_mu_M3000->Draw("P");
 
 double y_mu_M800[3] ={eff_M800_w1[0][0],eff_M800_w2[0][0],eff_M800_w3[0][0]};
 double ex_mu_M800[3] = {0,0,0};
 double ey_mu_M800[3] = {eff_M800_w1[0][3],eff_M800_w2[0][3],eff_M800_w3[0][3]};
 TGraphErrors* g_mu_M800 = new TGraphErrors(3,x_mu,y_mu_M800,ex_mu_M800,ey_mu_M800);
 g_mu_M800->SetMarkerColor(3);
 g_mu_M800->SetMarkerStyle(23);
 g_mu_M800->SetTitle("");
 g_mu_M800->Draw("P");
 
 double y_mu_M1200[3] ={eff_M1200_w1[0][0],eff_M1200_w2[0][0],eff_M1200_w3[0][0]};
 double ex_mu_M1200[3] = {0,0,0};
 double ey_mu_M1200[3] = {eff_M1200_w1[0][3],eff_M1200_w2[0][3],eff_M1200_w3[0][3]};
 TGraphErrors* g_mu_M1200 = new TGraphErrors(3,x_mu,y_mu_M1200,ex_mu_M1200,ey_mu_M1200);
 g_mu_M1200->SetMarkerColor(4);
 g_mu_M1200->SetMarkerStyle(24);
 g_mu_M1200->SetTitle("");
 g_mu_M1200->Draw("P");
 
 double y_mu_M2000[3] ={eff_M2000_w1[0][0],eff_M2000_w2[0][0],eff_M2000_w3[0][0]};
 double ex_mu_M2000[3] = {0,0,0};
 double ey_mu_M2000[3] = {eff_M2000_w1[0][3],eff_M2000_w2[0][3],eff_M2000_w3[0][3]};
 TGraphErrors* g_mu_M2000 = new TGraphErrors(3,x_mu,y_mu_M2000,ex_mu_M2000,ey_mu_M2000);
 g_mu_M2000->SetMarkerColor(6);
 g_mu_M2000->SetMarkerStyle(25);
 g_mu_M2000->SetTitle("");
 g_mu_M2000->Draw("P");

  TLegend* leg = new TLegend(0.18,0.12,0.38,0.42);
  leg->SetFillColor(0);
  leg->SetHeader("W #rightarrow #mu #nu, HP");
  leg->AddEntry(g_mu_M800,"M = 800 GeV","p");
  leg->AddEntry(g_mu_M1200,"M = 1200 GeV","p");
  leg->AddEntry(g_mu_M2000,"M = 2000 GeV","p");
  leg->AddEntry(g_mu_M3000,"M = 3000 GeV","p");
  leg->AddEntry(g_mu_M4000,"M = 4000 GeV","p");
  leg->Draw();
  
  string c1_name = "/usr/users/dschaefer/root/results/Efficiency/plots/testEff/testWidthDependence_"+model+"_mu.pdf" ;
  c1_mu->SaveAs(c1_name.c_str());
  
  //================== electron channel ===============================================
  
   
  TCanvas *c1_el = new TCanvas();
  gPad->SetLeftMargin(0.15);
 double x_el[3] ={0.1,0.2,0.3};
 double y_el_M4000[3] ={eff_M4000_w1[0][1],eff_M4000_w2[0][1],eff_M4000_w3[0][1]};
 double ex_el_M4000[3] = {0,0,0};
 double ey_el_M4000[3] = {eff_M4000_w1[0][4],eff_M4000_w2[0][4],eff_M4000_w3[0][4]};
 TGraphErrors* g_el_M4000 = new TGraphErrors(3,x_el,y_el_M4000,ex_el_M4000,ey_el_M4000);
 g_el_M4000->SetMarkerColor(1);
 g_el_M4000->SetMarkerStyle(21);
 g_el_M4000->GetXaxis()->SetTitle("#Gamma / M_{x}");
 g_el_M4000->GetYaxis()->SetTitleOffset(1.40);
 g_el_M4000->SetMaximum(0.22);
 g_el_M4000->SetMinimum(0.0);
 g_el_M4000->GetYaxis()->SetTitle("Efficiency #times Acceptance");
 g_el_M4000->SetTitle("");
 g_el_M4000->Draw("AP");
 
 
 double y_el_M3000[3] ={eff_M3000_w1[0][1],eff_M3000_w2[0][1],eff_M3000_w3[0][1]};
 double ex_el_M3000[3] = {0,0,0};
 double ey_el_M3000[3] = {eff_M3000_w1[0][4],eff_M3000_w2[0][4],eff_M3000_w3[0][4]};
 TGraphErrors* g_el_M3000 = new TGraphErrors(3,x_el,y_el_M3000,ex_el_M3000,ey_el_M3000);
 g_el_M3000->SetMarkerColor(2);
 g_el_M3000->SetMarkerStyle(22);
 g_el_M3000->SetTitle("");
 g_el_M3000->Draw("P");
 
 double y_el_M800[3] ={eff_M800_w1[0][1],eff_M800_w2[0][1],eff_M800_w3[0][1]};
 double ex_el_M800[3] = {0,0,0};
 double ey_el_M800[3] = {eff_M800_w1[0][4],eff_M800_w2[0][4],eff_M800_w3[0][4]};
 TGraphErrors* g_el_M800 = new TGraphErrors(3,x_el,y_el_M800,ex_el_M800,ey_el_M800);
 g_el_M800->SetMarkerColor(3);
 g_el_M800->SetMarkerStyle(23);
 g_el_M800->SetTitle("");
 g_el_M800->Draw("P");
 
 double y_el_M1200[3] ={eff_M1200_w1[0][1],eff_M1200_w2[0][1],eff_M1200_w3[0][1]};
 double ex_el_M1200[3] = {0,0,0};
 double ey_el_M1200[3] = {eff_M1200_w1[0][4],eff_M1200_w2[0][4],eff_M1200_w3[0][4]};
 TGraphErrors* g_el_M1200 = new TGraphErrors(3,x_el,y_el_M1200,ex_el_M1200,ey_el_M1200);
 g_el_M1200->SetMarkerColor(4);
 g_el_M1200->SetMarkerStyle(24);
 g_el_M1200->SetTitle("");
 g_el_M1200->Draw("P");
 
 double y_el_M2000[3] ={eff_M2000_w1[0][1],eff_M2000_w2[0][1],eff_M2000_w3[0][1]};
 double ex_el_M2000[3] = {0,0,0};
 double ey_el_M2000[3] = {eff_M2000_w1[0][4],eff_M2000_w2[0][4],eff_M2000_w3[0][4]};
 TGraphErrors* g_el_M2000 = new TGraphErrors(3,x_el,y_el_M2000,ex_el_M2000,ey_el_M2000);
 g_el_M2000->SetMarkerColor(6);
 g_el_M2000->SetMarkerStyle(25);
 g_el_M2000->SetTitle("");
 g_el_M2000->Draw("P");

  TLegend* leg2 = new TLegend(0.18,0.12,0.38,0.42);
  leg2->SetFillColor(0);
  leg2->SetHeader("W #rightarrow e #nu, HP");
  leg2->AddEntry(g_el_M800,"M = 800 GeV","p");
  leg2->AddEntry(g_el_M1200,"M = 1200 GeV","p");
  leg2->AddEntry(g_el_M2000,"M = 2000 GeV","p");
  leg2->AddEntry(g_el_M3000,"M = 3000 GeV","p");
  leg2->AddEntry(g_el_M4000,"M = 4000 GeV","p");
  leg2->Draw();
  
  string c1_el_name = "/usr/users/dschaefer/root/results/Efficiency/plots/testEff/testWidthDependence_"+model+"_el.pdf";
  c1_el->SaveAs(c1_el_name.c_str());
  
//==============================================================================================
//==================== write .txt for efficiency uncertainty ===================================
//==============================================================================================

vector<float> mass ={800,1200,2000,3000,4000};
EfficiencyUncertaintyForDatacards(mass,"el","HP");
EfficiencyUncertaintyForDatacards(mass,"mu","HP");

EfficiencyUncertaintyForDatacards(mass,"el","HPW");
EfficiencyUncertaintyForDatacards(mass,"mu","HPW");

EfficiencyUncertaintyForDatacards(mass,"el","HPZ");
EfficiencyUncertaintyForDatacards(mass,"mu","HPZ");
  
  
}