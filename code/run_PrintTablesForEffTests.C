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
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc2.h"
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
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc2.cc+");
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
  string decayMode = "WW_lvjj";
  PrintReconstructionEfficiencyTable("BulkGrav",category,decayMode,masses,0.0,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the efficiency tables. The test was performed on the narrow width bulk graviton sample.");
  
  
  PrintReconstructionEfficiencyTable("Wprime",category,"WZ_lvjj",masses,0.0,"Comparison between the exact efficiencies for W$' \\rightarrow $ W Z using the full analysis selection and the efficiencies obtained using the efficiency tables extracted from the narrow width bulk graviton sample. ");
  
   vector<float> massesRSGRAV = {800,1200,2000,3000,4000};
  PrintReconstructionEfficiencyTable("RSGrav",category,decayMode,massesRSGRAV,0.1,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a RS graviton sample. The hadronic W reconstruction efficiency has been corrected by a constant factor of 1.305 to take effects of W polaristion into account.");
  
  vector<float> massesZprime = {800,1200,2000,3000,4000};
  PrintReconstructionEfficiencyTable("Zprime",category,decayMode,massesZprime,0.1,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a Z$'$ sample with $\\Gamma/M_x =0.1$.");
  
  vector<float> massesWprime = {800,1200,2000,3000,4000};
  PrintReconstructionEfficiencyTable("Wprime",category,"WZ_lvjj",massesWprime,0.1,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a W$' \\rightarrow$ WW sample with $\\Gamma/M_x =0.3$.");
  
  vector<float> massesRadion = {800,1200,2000,3000,4000};
  PrintReconstructionEfficiencyTable("Radion",category,decayMode,massesRadion,0.1,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a Radion$ \\rightarrow$ WW sample with $\\Gamma/M_x =0.3$.");
  
  //all hadronic part:
  
  
  category = "HP";
  decayMode = "WW_jjjj";
  
  
  massesRSGRAV = {800,1200,2000,3000,4000};
  PrintReconstructionEfficiencyTable("RSGrav",category,decayMode,massesRSGRAV,0.3,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a RS graviton sample. The hadronic W reconstruction efficiency has been corrected by a constant factor of 1.305 to take effects of W polaristion into account.");
  
  PrintReconstructionEfficiencyTable("RSGrav",category,decayMode,massesRSGRAV,0.2,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a RS graviton sample. The hadronic W reconstruction efficiency has been corrected by a constant factor of 1.305 to take effects of W polaristion into account.");
  
  PrintReconstructionEfficiencyTable("RSGrav",category,decayMode,massesRSGRAV,0.1,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a RS graviton sample. The hadronic W reconstruction efficiency has been corrected by a constant factor of 1.305 to take effects of W polaristion into account.");
  
  //category="NP";
  massesZprime = {800,1200,2000,3000,4000};
  PrintReconstructionEfficiencyTable("Zprime",category,decayMode,massesZprime,0.3,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a Z$'$ sample with $\\Gamma/M_x =0.3$.");
  
  PrintReconstructionEfficiencyTable("Zprime",category,decayMode,massesZprime,0.2,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a Z$'$ sample with $\\Gamma/M_x =0.2$.");
  
  PrintReconstructionEfficiencyTable("Zprime",category,decayMode,massesZprime,0.1,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a Z$'$ sample with $\\Gamma/M_x =0.1$.");
  
  massesWprime = {1200,2000,3000,4000};
  PrintReconstructionEfficiencyTable("Wprime",category,"WZ_jjjj",massesWprime,0.3,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a W$' \\rightarrow$ WW sample with $\\Gamma/M_x =0.3$.");
  
  PrintReconstructionEfficiencyTable("Wprime",category,"WZ_jjjj",massesWprime,0.2,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a W$' \\rightarrow$ WW sample with $\\Gamma/M_x =0.2$.");
  
  PrintReconstructionEfficiencyTable("Wprime",category,"WZ_jjjj",massesWprime,0.1,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a W$' \\rightarrow$ WW sample with $\\Gamma/M_x =0.1$.");
  
  
  
  massesRadion = {800,1200,2000,3000,4000};
  PrintReconstructionEfficiencyTable("Radion",category,decayMode,massesRadion,0.3,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a Radion$ \\rightarrow$ WW sample with $\\Gamma/M_x =0.3$.");
  
  PrintReconstructionEfficiencyTable("Radion",category,decayMode,massesRadion,0.2,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a Radion$ \\rightarrow$ WW sample with $\\Gamma/M_x =0.2$.");
  
  PrintReconstructionEfficiencyTable("Radion",category,decayMode,massesRadion,0.1,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the narrow width bulk graviton tables on a Radion$ \\rightarrow$ WW sample with $\\Gamma/M_x =0.1$.");
  
  //category="HP";
  masses={1200,1400,1800,2000,3000,3500,4500};
  PrintReconstructionEfficiencyTable("BulkGrav",category,decayMode,masses,0.0,"Comparison between the exact efficiencies using the full analysis selection and the efficiencies obtained using the efficiency tables. The test was performed on the narrow width bulk graviton sample for the all hadronic analysis");
  
  PrintReconstructionEfficiencyTable("Radion",category,decayMode,masses,0.0,"test Narrow Radion sample");
  
  PrintReconstructionEfficiencyTable("Zprime",category,decayMode,masses,0.0,"narrow width Zprime");
  
  
  //=============================================================================================
  //============= Make plots to test the dependance of the efficiency on invariant mass =========
  //=============================================================================================
  
  string model1 = "Radion";
  string model2 = "BulkGrav";
  string model3 = "Zprime";
  decayMode = "WW_jjjj";
  category = "HP";
  
  std::map<string,double> eff_M1200_Ra = ExtractRecoAndTestEfficiency(model1,category,decayMode,1200,0.0);
  std::map<string,double> eff_M1400_Ra = ExtractRecoAndTestEfficiency(model1,category,decayMode,1400,0.0);
  std::map<string,double> eff_M1600_Ra = ExtractRecoAndTestEfficiency(model1,category,decayMode,1600,0.0);
  std::map<string,double> eff_M1800_Ra = ExtractRecoAndTestEfficiency(model1,category,decayMode,1800,0.0);
  std::map<string,double> eff_M2000_Ra = ExtractRecoAndTestEfficiency(model1,category,decayMode,2000,0.0);
  std::map<string,double> eff_M2500_Ra = ExtractRecoAndTestEfficiency(model1,category,decayMode,2500,0.0);
  std::map<string,double> eff_M3000_Ra = ExtractRecoAndTestEfficiency(model1,category,decayMode,3000,0.0);
  std::map<string,double> eff_M3500_Ra = ExtractRecoAndTestEfficiency(model1,category,decayMode,3500,0.0);
  std::map<string,double> eff_M4000_Ra = ExtractRecoAndTestEfficiency(model1,category,decayMode,4000,0.0);
  std::map<string,double> eff_M4500_Ra = ExtractRecoAndTestEfficiency(model1,category,decayMode,4500,0.0);
  
   std::map<string,double> eff_M1200_BG = ExtractRecoAndTestEfficiency(model2,category,decayMode,1200,0.0);
   std::map<string,double> eff_M1400_BG = ExtractRecoAndTestEfficiency(model2,category,decayMode,1400,0.0);
   std::map<string,double> eff_M1600_BG = ExtractRecoAndTestEfficiency(model2,category,decayMode,1600,0.0);
   std::map<string,double> eff_M1800_BG = ExtractRecoAndTestEfficiency(model2,category,decayMode,1800,0.0);
   std::map<string,double> eff_M2000_BG = ExtractRecoAndTestEfficiency(model2,category,decayMode,2000,0.0);
   std::map<string,double> eff_M2500_BG = ExtractRecoAndTestEfficiency(model2,category,decayMode,2500,0.0);
   std::map<string,double> eff_M3000_BG = ExtractRecoAndTestEfficiency(model2,category,decayMode,3000,0.0);
   std::map<string,double> eff_M3500_BG = ExtractRecoAndTestEfficiency(model2,category,decayMode,3500,0.0);
   std::map<string,double> eff_M4000_BG = ExtractRecoAndTestEfficiency(model2,category,decayMode,4000,0.0);
   std::map<string,double> eff_M4500_BG = ExtractRecoAndTestEfficiency(model2,category,decayMode,4500,0.0);
   
   
    std::map<string,double> eff_M1200_Zprime = ExtractRecoAndTestEfficiency(model3,category,decayMode,1200,0.0);
   std::map<string,double> eff_M1400_Zprime = ExtractRecoAndTestEfficiency(model3,category,decayMode,1400,0.0);
   std::map<string,double> eff_M1600_Zprime = ExtractRecoAndTestEfficiency(model3,category,decayMode,1600,0.0);
   std::map<string,double> eff_M1800_Zprime = ExtractRecoAndTestEfficiency(model3,category,decayMode,1800,0.0);
   std::map<string,double> eff_M2000_Zprime = ExtractRecoAndTestEfficiency(model3,category,decayMode,2000,0.0);
   std::map<string,double> eff_M2500_Zprime = ExtractRecoAndTestEfficiency(model3,category,decayMode,2500,0.0);
   std::map<string,double> eff_M3000_Zprime = ExtractRecoAndTestEfficiency(model3,category,decayMode,3000,0.0);
   std::map<string,double> eff_M3500_Zprime = ExtractRecoAndTestEfficiency(model3,category,decayMode,3500,0.0);
   std::map<string,double> eff_M4000_Zprime = ExtractRecoAndTestEfficiency(model3,category,decayMode,4000,0.0);
   std::map<string,double> eff_M4500_Zprime = ExtractRecoAndTestEfficiency(model3,category,decayMode,4500,0.0);
  
  
   TCanvas* c_eff_over_mass = new TCanvas("c_eff_over_mass","",400,400);
   double m[10] = {1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
   double y_eff_Ra[10] = {eff_M1200_Ra.find("had_rec")->second,eff_M1400_Ra.find("had_rec")->second,eff_M1600_Ra.find("had_rec")->second,eff_M1800_Ra.find("had_rec")->second,eff_M2000_Ra.find("had_rec")->second,eff_M2500_Ra.find("had_rec")->second,eff_M3000_Ra.find("had_rec")->second,eff_M3500_Ra.find("had_rec")->second,eff_M4000_Ra.find("had_rec")->second,eff_M4500_Ra.find("had_rec")->second};
   double y_eff_BG[10] = {eff_M1200_BG.find("had_rec")->second,eff_M1400_BG.find("had_rec")->second,eff_M1600_BG.find("had_rec")->second,eff_M1800_BG.find("had_rec")->second,eff_M2000_BG.find("had_rec")->second,eff_M2500_BG.find("had_rec")->second,eff_M3000_BG.find("had_rec")->second,eff_M3500_BG.find("had_rec")->second,eff_M4000_BG.find("had_rec")->second,eff_M4500_BG.find("had_rec")->second};
    double y_eff_Zprime[10] = {eff_M1200_Zprime.find("had_rec")->second,eff_M1400_Zprime.find("had_rec")->second,eff_M1600_Zprime.find("had_rec")->second,eff_M1800_Zprime.find("had_rec")->second,eff_M2000_Zprime.find("had_rec")->second,eff_M2500_Zprime.find("had_rec")->second,eff_M3000_Zprime.find("had_rec")->second,eff_M3500_Zprime.find("had_rec")->second,eff_M4000_Zprime.find("had_rec")->second,eff_M4500_Zprime.find("had_rec")->second};
  
   std::cout << eff_M1200_Ra.find("had_rec")->second << std::endl;
    std::cout << eff_M1200_BG.find("had_rec")->second << std::endl;
    
    std::cout << 1200<<" "<< eff_M1200_Ra.find("had_rec")->second << std::endl;
    std::cout << 1400<<" "<< eff_M1400_Ra.find("had_rec")->second << std::endl;
    std::cout << 1600<<" "<< eff_M1600_Ra.find("had_rec")->second << std::endl;
    std::cout <<1800 <<" "<< eff_M1800_Ra.find("had_rec")->second << std::endl;
    std::cout <<2000 <<" "<< eff_M2000_Ra.find("had_rec")->second << std::endl;
    std::cout <<2500 <<" "<< eff_M2500_Ra.find("had_rec")->second << std::endl;
    std::cout <<3000 <<" "<< eff_M3000_Ra.find("had_rec")->second << std::endl;
    std::cout <<3500 <<" "<< eff_M3500_Ra.find("had_rec")->second << std::endl;
    std::cout <<4000 <<" "<< eff_M4000_Ra.find("had_rec")->second << std::endl;
    std::cout <<4500 <<" "<< eff_M4500_Ra.find("had_rec")->second << std::endl;
   
     std::cout << 1200<<" "<< eff_M1200_BG.find("had_rec")->second/eff_M1200_Ra.find("had_rec")->second  << std::endl;
     std::cout << 1400<<" "<< eff_M1400_BG.find("had_rec")->second/eff_M1400_Ra.find("had_rec")->second  << std::endl;
     std::cout << 1600<<" "<< eff_M1600_BG.find("had_rec")->second/eff_M1600_Ra.find("had_rec")->second  << std::endl;
     std::cout <<1800 <<" "<< eff_M1800_BG.find("had_rec")->second/eff_M1800_Ra.find("had_rec")->second  << std::endl;
     std::cout <<2000 <<" "<< eff_M2000_BG.find("had_rec")->second/eff_M2000_Ra.find("had_rec")->second  << std::endl;
     std::cout <<2500 <<" "<< eff_M2500_BG.find("had_rec")->second/eff_M2500_Ra.find("had_rec")->second  << std::endl;
     std::cout <<3000 <<" "<< eff_M3000_BG.find("had_rec")->second/eff_M3000_Ra.find("had_rec")->second  << std::endl;
     std::cout <<3500 <<" "<< eff_M3500_BG.find("had_rec")->second/eff_M3500_Ra.find("had_rec")->second  << std::endl;
     std::cout <<4000 <<" "<< eff_M4000_BG.find("had_rec")->second/eff_M4000_Ra.find("had_rec")->second  << std::endl;
     std::cout <<4500 <<" "<< eff_M4500_BG.find("had_rec")->second/eff_M4500_Ra.find("had_rec")->second  << std::endl;
   
   TGraph* g_Ra = new TGraph(10,m,y_eff_Ra);
   TGraph* g_BG = new TGraph(10,m,y_eff_BG);
   TGraph* g_Zprime = new TGraph(10,m,y_eff_Zprime);
   
   float ymax = 0.55;
   float ymin = 0.25;
   if(category.find("HP")!= string::npos)
   {
    ymax = 0.3;
    ymin = 0.05;
   }
   
   g_Ra->SetMarkerColor(1);
   g_Ra->SetMarkerStyle(21);
   g_Ra->GetXaxis()->SetTitle("M_{x}");
   g_Ra->GetYaxis()->SetTitleOffset(1.40);
   g_Ra->SetMaximum(ymax);
   g_Ra->SetMinimum(ymin);
   g_Ra->GetYaxis()->SetTitle("Efficiency #times Acceptance, Radion");
   g_Ra->SetTitle("");
   g_Ra->Draw("AP");
   
   g_BG->SetMarkerColor(4);
   g_BG->SetMarkerStyle(22);
   g_BG->GetXaxis()->SetTitle("M_{x}");
   g_BG->GetYaxis()->SetTitleOffset(1.40);
   g_BG->SetMaximum(ymax);
   g_BG->SetMinimum(ymin);
   g_BG->GetYaxis()->SetTitle("Efficiency #times Acceptance, Bulk-graviton");
   g_BG->SetTitle("");
   g_BG->Draw("SAMEP");
   
   g_Zprime->SetMarkerColor(2);
   g_Zprime->SetMarkerStyle(23);
   g_Zprime->GetXaxis()->SetTitle("M_{x}");
   g_Zprime->GetYaxis()->SetTitleOffset(1.40);
   g_Zprime->SetMaximum(ymax);
   g_Zprime->SetMinimum(ymin);
   g_Zprime->GetYaxis()->SetTitle("Efficiency #times Acceptance, Bulk-graviton");
   g_Zprime->SetTitle("");
   g_Zprime->Draw("SAMEP");
   
   
   TLegend* L = new TLegend(0.18,0.12,0.38,0.32);
   L->SetFillColor(0);
   L->SetHeader(("WW all had,"+category).c_str());
   L->AddEntry(g_Ra,"Radion","p");
   L->AddEntry(g_BG,"Bulk graviton","p");
   L->AddEntry(g_Zprime,"Z'","p");
   L->Draw();
   c_eff_over_mass->SaveAs(("/usr/users/dschaefer/root/results/Efficiency/plots/testEff/EffDependenceOnMass_had_"+category+".pdf").c_str());
   
   
  model1 = "Zprime";
  model2 = "BulkGrav";
  decayMode = "WW_lvjj";
  category = "HP";
  
  std::map<string,double> eff_M1200_Ra_semilep = ExtractRecoAndTestEfficiency(model1,category,decayMode,1200,0.0);
  std::map<string,double> eff_M1400_Ra_semilep = ExtractRecoAndTestEfficiency(model1,category,decayMode,1400,0.0);
  std::map<string,double> eff_M1600_Ra_semilep = ExtractRecoAndTestEfficiency(model1,category,decayMode,1600,0.0);
  std::map<string,double> eff_M1800_Ra_semilep = ExtractRecoAndTestEfficiency(model1,category,decayMode,1800,0.0);
  std::map<string,double> eff_M2000_Ra_semilep = ExtractRecoAndTestEfficiency(model1,category,decayMode,2000,0.0);
  std::map<string,double> eff_M2500_Ra_semilep = ExtractRecoAndTestEfficiency(model1,category,decayMode,2500,0.0);
  std::map<string,double> eff_M3000_Ra_semilep = ExtractRecoAndTestEfficiency(model1,category,decayMode,3000,0.0);
  std::map<string,double> eff_M3500_Ra_semilep = ExtractRecoAndTestEfficiency(model1,category,decayMode,3500,0.0);
  std::map<string,double> eff_M4000_Ra_semilep = ExtractRecoAndTestEfficiency(model1,category,decayMode,4000,0.0);
  std::map<string,double> eff_M4500_Ra_semilep = ExtractRecoAndTestEfficiency(model1,category,decayMode,4500,0.0);
  
   std::map<string,double> eff_M1200_BG_semilep = ExtractRecoAndTestEfficiency(model2,category,decayMode,1200,0.0);
   std::map<string,double> eff_M1400_BG_semilep = ExtractRecoAndTestEfficiency(model2,category,decayMode,1400,0.0);
   std::map<string,double> eff_M1600_BG_semilep = ExtractRecoAndTestEfficiency(model2,category,decayMode,1600,0.0);
   std::map<string,double> eff_M1800_BG_semilep = ExtractRecoAndTestEfficiency(model2,category,decayMode,1800,0.0);
   std::map<string,double> eff_M2000_BG_semilep = ExtractRecoAndTestEfficiency(model2,category,decayMode,2000,0.0);
   std::map<string,double> eff_M2500_BG_semilep = ExtractRecoAndTestEfficiency(model2,category,decayMode,2500,0.0);
   std::map<string,double> eff_M3000_BG_semilep = ExtractRecoAndTestEfficiency(model2,category,decayMode,3000,0.0);
   std::map<string,double> eff_M3500_BG_semilep = ExtractRecoAndTestEfficiency(model2,category,decayMode,3500,0.0);
   std::map<string,double> eff_M4000_BG_semilep = ExtractRecoAndTestEfficiency(model2,category,decayMode,4000,0.0);
   std::map<string,double> eff_M4500_BG_semilep = ExtractRecoAndTestEfficiency(model2,category,decayMode,4500,0.0);
    
   TCanvas* c_eff_over_mass_slep = new TCanvas("c_eff_over_mass_slep","semileptonic case",400,400);
   double m_semilep[10] = {1200,1400,1600,1800,2000,2500,3000,3500,4000,4500};
   double y_eff_Ra_semilep[10] = {eff_M1200_Ra_semilep.find("mu_rec")->second,eff_M1400_Ra_semilep.find("mu_rec")->second,eff_M1600_Ra_semilep.find("mu_rec")->second,eff_M1800_Ra_semilep.find("mu_rec")->second,eff_M2000_Ra_semilep.find("mu_rec")->second,eff_M2500_Ra_semilep.find("mu_rec")->second,eff_M3000_Ra_semilep.find("mu_rec")->second,eff_M3500_Ra_semilep.find("mu_rec")->second,eff_M4000_Ra_semilep.find("mu_rec")->second,eff_M4500_Ra_semilep.find("mu_rec")->second};
   double y_eff_BG_semilep[10] = {eff_M1200_BG_semilep.find("mu_rec")->second,eff_M1400_BG_semilep.find("mu_rec")->second,eff_M1600_BG_semilep.find("mu_rec")->second,eff_M1800_BG_semilep.find("mu_rec")->second,eff_M2000_BG_semilep.find("mu_rec")->second,eff_M2500_BG_semilep.find("mu_rec")->second,eff_M3000_BG_semilep.find("mu_rec")->second,eff_M3500_BG_semilep.find("mu_rec")->second,eff_M4000_BG_semilep.find("mu_rec")->second,eff_M4500_BG_semilep.find("mu_rec")->second};
  
   TGraph* g_Ra_semilep = new TGraph(10,m,y_eff_Ra_semilep);
   TGraph* g_BG_semilep = new TGraph(10,m,y_eff_BG_semilep);
   
   g_Ra_semilep->SetMarkerColor(1);
   g_Ra_semilep->SetMarkerStyle(21);
   g_Ra_semilep->GetXaxis()->SetTitle("M_{x}");
   g_Ra_semilep->GetYaxis()->SetTitleOffset(1.40);
   g_Ra_semilep->SetMaximum(0.25);
   g_Ra_semilep->SetMinimum(0.15);
   g_Ra_semilep->GetYaxis()->SetTitle("Efficiency #times Acceptance, Radion");
   g_Ra_semilep->SetTitle("");
   g_Ra_semilep->Draw("AP");
   
   g_BG_semilep->SetMarkerColor(4);
   g_BG_semilep->SetMarkerStyle(22);
   g_BG_semilep->GetXaxis()->SetTitle("M_{x}");
   g_BG_semilep->GetYaxis()->SetTitleOffset(1.40);
   g_BG_semilep->SetMaximum(0.25);
   g_BG_semilep->SetMinimum(0.15);
   g_BG_semilep->GetYaxis()->SetTitle("Efficiency #times Acceptance, Bulk-graviton");
   g_BG_semilep->SetTitle("");
   g_BG_semilep->Draw("SAME");
   
   
    TLegend* l = new TLegend(0.18,0.12,0.38,0.32);
    l->SetFillColor(0);
    l->SetHeader(("WW semilep mu,"+category).c_str());
    l->AddEntry(g_Ra_semilep,"Z #prime","p");
    l->AddEntry(g_BG_semilep,"Bulk graviton","p");
    l->Draw();
    
    c_eff_over_mass_slep->SaveAs(("/usr/users/dschaefer/root/results/Efficiency/plots/testEff/EffDependenceOnMass_mu_"+category+".pdf").c_str());
   
  //===================================================================================
  //============= Make plots to test the dependance of the efficiency on width=========
  //===================================================================================
  /*
  string model = "Zprime";
   decayMode = "WW_lvjj";
  std::map<string,double> eff_M800_w1 =  ExtractRecoAndTestEfficiency(model,category,decayMode,800,0.1);
  std::map<string,double> eff_M800_w2 =  ExtractRecoAndTestEfficiency(model,category,decayMode,800,0.2);
  std::map<string,double> eff_M800_w3 =  ExtractRecoAndTestEfficiency(model,category,decayMode,800,0.3);
  std::map<string,double> eff_M2000_w1 = ExtractRecoAndTestEfficiency(model,category,decayMode,2000,0.1);
  std::map<string,double> eff_M2000_w2 = ExtractRecoAndTestEfficiency(model,category,decayMode,2000,0.2);
  std::map<string,double> eff_M2000_w3 = ExtractRecoAndTestEfficiency(model,category,decayMode,2000,0.3);
  std::map<string,double> eff_M1200_w1 = ExtractRecoAndTestEfficiency(model,category,decayMode,1200,0.1);
  std::map<string,double> eff_M1200_w2 = ExtractRecoAndTestEfficiency(model,category,decayMode,1200,0.2);
  std::map<string,double> eff_M1200_w3 = ExtractRecoAndTestEfficiency(model,category,decayMode,1200,0.3);
  std::map<string,double> eff_M3000_w1 = ExtractRecoAndTestEfficiency(model,category,decayMode,3000,0.1);
  std::map<string,double> eff_M3000_w2 = ExtractRecoAndTestEfficiency(model,category,decayMode,3000,0.2);
  std::map<string,double> eff_M3000_w3 = ExtractRecoAndTestEfficiency(model,category,decayMode,3000,0.3);
  std::map<string,double> eff_M4000_w1 = ExtractRecoAndTestEfficiency(model,category,decayMode,4000,0.1);
  std::map<string,double> eff_M4000_w2 = ExtractRecoAndTestEfficiency(model,category,decayMode,4000,0.2);
  std::map<string,double> eff_M4000_w3 = ExtractRecoAndTestEfficiency(model,category,decayMode,4000,0.3);
  
 
  TCanvas *c1_mu = new TCanvas();
  gPad->SetLeftMargin(0.15);
 double x_mu[3] ={0.1,0.2,0.3};
 double y_mu_M4000[3] ={eff_M4000_w1.find("mu_rec")->second,eff_M4000_w2.find("mu_rec")->second,eff_M4000_w3.find("mu_rec")->second};
 double ex_mu_M4000[3] = {0,0,0};
 double ey_mu_M4000[3] = {eff_M4000_w1.find("err_mu")->second,eff_M4000_w2.find("err_mu")->second,eff_M4000_w3.find("err_mu")->second};
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
 
 
 double y_mu_M3000[3] ={eff_M3000_w1.find("mu_rec")->second,eff_M3000_w2.find("mu_rec")->second,eff_M3000_w3.find("mu_rec")->second};
 double ex_mu_M3000[3] = {0,0,0};
 double ey_mu_M3000[3] = {eff_M3000_w1.find("err_mu")->second,eff_M3000_w2.find("err_mu")->second,eff_M3000_w3.find("err_mu")->second};
 TGraphErrors* g_mu_M3000 = new TGraphErrors(3,x_mu,y_mu_M3000,ex_mu_M3000,ey_mu_M3000);
 g_mu_M3000->SetMarkerColor(2);
 g_mu_M3000->SetMarkerStyle(22);
 g_mu_M3000->SetTitle("");
 g_mu_M3000->Draw("P");
 
 double y_mu_M800[3] ={eff_M800_w1.find("mu_rec")->second,eff_M800_w2.find("mu_rec")->second,eff_M800_w3.find("mu_rec")->second};
 double ex_mu_M800[3] = {0,0,0};
 double ey_mu_M800[3] = {eff_M800_w1.find("err_mu")->second,eff_M800_w2.find("err_mu")->second,eff_M800_w3.find("err_mu")->second};
 TGraphErrors* g_mu_M800 = new TGraphErrors(3,x_mu,y_mu_M800,ex_mu_M800,ey_mu_M800);
 g_mu_M800->SetMarkerColor(3);
 g_mu_M800->SetMarkerStyle(23);
 g_mu_M800->SetTitle("");
 g_mu_M800->Draw("P");
 
 double y_mu_M1200[3] ={eff_M1200_w1.find("mu_rec")->second,eff_M1200_w2.find("mu_rec")->second,eff_M1200_w3.find("mu_rec")->second};
 double ex_mu_M1200[3] = {0,0,0};
 double ey_mu_M1200[3] = {eff_M1200_w1.find("err_mu")->second,eff_M1200_w2.find("err_mu")->second,eff_M1200_w3.find("err_mu")->second};
 TGraphErrors* g_mu_M1200 = new TGraphErrors(3,x_mu,y_mu_M1200,ex_mu_M1200,ey_mu_M1200);
 g_mu_M1200->SetMarkerColor(4);
 g_mu_M1200->SetMarkerStyle(24);
 g_mu_M1200->SetTitle("");
 g_mu_M1200->Draw("P");
 
 double y_mu_M2000[3] ={eff_M2000_w1.find("mu_rec")->second,eff_M2000_w2.find("mu_rec")->second,eff_M2000_w3.find("mu_rec")->second};
 double ex_mu_M2000[3] = {0,0,0};
 double ey_mu_M2000[3] = {eff_M2000_w1.find("err_mu")->second,eff_M2000_w2.find("err_mu")->second,eff_M2000_w3.find("err_mu")->second};
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
 double y_el_M4000[3] ={eff_M4000_w1.find("el_rec")->second,eff_M4000_w2.find("el_rec")->second,eff_M4000_w3.find("el_rec")->second};
 double ex_el_M4000[3] = {0,0,0};
 double ey_el_M4000[3] = {eff_M4000_w1.find("err_el")->second,eff_M4000_w2.find("err_el")->second,eff_M4000_w3.find("err_el")->second};
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
 
 
 double y_el_M3000[3] ={eff_M3000_w1.find("el_rec")->second,eff_M3000_w2.find("el_rec")->second,eff_M3000_w3.find("el_rec")->second};
 double ex_el_M3000[3] = {0,0,0};
 double ey_el_M3000[3] = {eff_M3000_w1.find("err_el")->second,eff_M3000_w2.find("err_el")->second,eff_M3000_w3.find("err_el")->second};
 TGraphErrors* g_el_M3000 = new TGraphErrors(3,x_el,y_el_M3000,ex_el_M3000,ey_el_M3000);
 g_el_M3000->SetMarkerColor(2);
 g_el_M3000->SetMarkerStyle(22);
 g_el_M3000->SetTitle("");
 g_el_M3000->Draw("P");
 
 double y_el_M800[3] ={eff_M800_w1.find("el_rec")->second,eff_M800_w2.find("el_rec")->second,eff_M800_w3.find("el_rec")->second};
 double ex_el_M800[3] = {0,0,0};
 double ey_el_M800[3] = {eff_M800_w1.find("err_el")->second,eff_M800_w2.find("err_el")->second,eff_M800_w3.find("err_el")->second};
 TGraphErrors* g_el_M800 = new TGraphErrors(3,x_el,y_el_M800,ex_el_M800,ey_el_M800);
 g_el_M800->SetMarkerColor(3);
 g_el_M800->SetMarkerStyle(23);
 g_el_M800->SetTitle("");
 g_el_M800->Draw("P");
 
 double y_el_M1200[3] ={eff_M1200_w1.find("el_rec")->second,eff_M1200_w2.find("el_rec")->second,eff_M1200_w3.find("el_rec")->second};
 double ex_el_M1200[3] = {0,0,0};
 double ey_el_M1200[3] = {eff_M1200_w1.find("err_el")->second,eff_M1200_w2.find("err_el")->second,eff_M1200_w3.find("err_el")->second};
 TGraphErrors* g_el_M1200 = new TGraphErrors(3,x_el,y_el_M1200,ex_el_M1200,ey_el_M1200);
 g_el_M1200->SetMarkerColor(4);
 g_el_M1200->SetMarkerStyle(24);
 g_el_M1200->SetTitle("");
 g_el_M1200->Draw("P");
 
 double y_el_M2000[3] ={eff_M2000_w1.find("el_rec")->second,eff_M2000_w2.find("el_rec")->second,eff_M2000_w3.find("el_rec")->second};
 double ex_el_M2000[3] = {0,0,0};
 double ey_el_M2000[3] = {eff_M2000_w1.find("err_el")->second,eff_M2000_w2.find("err_el")->second,eff_M2000_w3.find("err_el")->second};
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
//EfficiencyUncertaintyForDatacards(mass,"el","HP","WW_lvjj");
//EfficiencyUncertaintyForDatacards(mass,"mu","HP","WW_lvjj");

// EfficiencyUncertaintyForDatacards(mass,"el","HPW","WW_lvjj");
// EfficiencyUncertaintyForDatacards(mass,"mu","HPW","WW_lvjj");
// 
// EfficiencyUncertaintyForDatacards(mass,"el","HPZ","WW_lvjj");
// EfficiencyUncertaintyForDatacards(mass,"mu","HPZ","WW_lvjj");
  
  */
}