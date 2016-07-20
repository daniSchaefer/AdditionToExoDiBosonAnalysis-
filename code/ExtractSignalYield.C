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
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/CrossSections.cc+");

 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}





void ExtractSignalYield(string ModelName, string decayMode, float natural_width, bool dependsOnKtilde=0)
{
  
  string dir = "/usr/users/dschaefer/root/results/";
  string outputfile = ModelName+"_"+decayMode+"_signalYield.root";
  //float natural_width =0.05;
  std::stringstream s;
      if(int(natural_width*100+0.5) == 10 or int(100*natural_width+0.5)==20 or int(natural_width*100+0.5)==30)
      {
	s << std::fixed << std::setprecision(1) << natural_width;
      }
      else
      {
	s << std::fixed << std::setprecision(2) << natural_width;
      }
  string swidth = s.str();
  float ktilde;
  string sktilde;
  if(dependsOnKtilde)
  {
   ktilde = natural_width;
   sktilde = swidth;
  }
  
  TGraph* limit = getObservedLimit(ModelName,decayMode,natural_width,dependsOnKtilde);
  TGraph* limitUP = getLimitUp(ModelName,decayMode,natural_width,1,dependsOnKtilde);
  TGraph* limitDOWN = getLimitDown(ModelName,decayMode,natural_width,1,dependsOnKtilde);
  TGraph* limitUP2 = getLimitUp(ModelName,decayMode,natural_width,2,dependsOnKtilde);
  TGraph* limitDOWN2 = getLimitDown(ModelName,decayMode,natural_width,2,dependsOnKtilde);
  
  
  int number;
  float* masses;
  if(decayMode.find("lvjj")!=string::npos)
  {
    masses = new float[38];
    number =38;
    float array[38] = {800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000,4100,4200,4300,4400,4500};
    masses = array;
  }
  else
  {
   number = 29;
   masses = new float[29];
   float array[29] = {1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000};
   masses = array;
  }
  TGraph* gryellow = new TGraph(2*number);
  TGraph* grgreen  = new TGraph(2*number);
  
  for(int m=0;m<number;m++)
  {
    gryellow->SetPoint(m,masses[m],limitUP->Eval(masses[m]));
    gryellow->SetPoint(number+m,masses[number-m-1],limitDOWN->Eval(masses[number-m-1]));
    grgreen->SetPoint(m,masses[m],limitUP2->Eval(masses[m]));
    grgreen->SetPoint(number+m,masses[number-m-1],limitDOWN2->Eval(masses[number-m-1]));
    
  }
  gryellow->SetFillColor(kYellow);
  grgreen->SetFillColor(kGreen);
  
  TCanvas* test = new TCanvas("test","test",400,400);
  test->SetLogy();
  limitUP->SetFillColor(kGreen+2);
  limitUP->SetLineColor(kGreen+2);
  limitUP->SetLineWidth(-1504);
  
  //limitUP->Draw("ACP");
  limitDOWN->SetFillColor(kBlue);
  limitDOWN->SetLineColor(kGreen+2);
  limitDOWN->SetLineWidth(-1504);
  //limitDOWN->Draw("CPsame");
  gryellow->Draw("AFsame");
  grgreen->Draw("Fsame");
  limit->SetLineColor(kBlue);
  limit->SetLineWidth(3);
  limit->Draw("Lsame");
  test->Update();
  
  float lumi = 2.10*1000;  //pb^-1
  if(decayMode.find("jjjj")!=string::npos){lumi = 2.6*1000;}//pb^-1
  
  
  
  
  //float *xs = getTheoryCrossSection(ModelName,0.1);
  
  //x values for which a theory prediction for production cross section exists
  float m_xs[10]  =  {800,900,1000,1500,1800,2000,2500,3000,3500,4500};
  float BR_G_to_WW[10];
  float BR_G_to_ZZ[10];
  float *acceptance;
  float *N_expected;
  //float xs = 0.01;
  float *xs = new float[10];
  
  if(dependsOnKtilde)
  {
    xs = getTheoryCrossSection(ModelName,ktilde);
  }
  else
  {
    for(int i=0;i<10;i++)
    {
    if(natural_width!=0)
    {
      ktilde = getKtilde(ModelName,m_xs[i],natural_width);
      //std::cout << m_xs[i] << " k = " << ktilde <<std::endl;
      xs[i] = getTheoryCrossSection(ModelName,m_xs[i],ktilde);
    }
    else
    {
      ktilde = getKtilde(ModelName,m_xs[i],0.02);
      //std::cout <<  m_xs[i] << " k = " << ktilde <<std::endl;
      xs[i] = getTheoryCrossSection(ModelName,m_xs[i],ktilde);
    }
    }
  }
  
 
 
 
  
  TGraph* production_xs = new TGraph(10,m_xs,xs);
  
  // TCanvas* c_xs = new TCanvas("c_xs","c_xs",400,400);
  // c_xs->SetLogy();
  // production_xs->SetMarkerColor(1);
  // production_xs->GetXaxis()->SetTitle("m_G [GeV]");
  // production_xs->GetYaxis()->SetTitle("theory production cross section");
  // production_xs->Draw("AL");
  
  
  
  if(!dependsOnKtilde)
  {
  acceptance = getAcceptance(ModelName,decayMode,m_xs,10);
  }
  else
  {
   acceptance = getAcceptance(decayMode,ktilde); 
  }
  
  N_expected = getNumberOfExpectedEvents(xs,m_xs,acceptance,ModelName,decayMode);
  

 std::cout << "production cross section : "<< std::endl;
  for(int i=0;i<10;i++)
    {
      std::cout << m_xs[i] <<  " " << xs[i]<< std::endl;
    }
  std::cout << " acceptance : "<<std::endl;
  for(int i=0;i<10;i++)
    {
      std::cout << m_xs[i] << " "<<acceptance[i]<<std::endl;
    }
  float br[10];
  std::cout << "Branching Ratios : "<<std::endl;
  for(int i=0;i<10;i++)
    {
      float BR_W_to_lv = 0.327;
      float BR_W_to_jj = 0.674;
      float BR_Z_to_jj = 0.6991;
      br[i] = getBranchingRatioToWW(ModelName,m_xs[i])*std::pow(BR_W_to_jj,2)*2 + getBranchingRatioToZZ(ModelName,m_xs[i])*std::pow(BR_Z_to_jj,2)*2;
      if(decayMode.find("lvjj")!=std::string::npos)
	{
	  br[i] = getBranchingRatioToWW(ModelName,m_xs[i])*2*BR_W_to_lv*BR_W_to_jj;
	}
      std::cout << m_xs[i] << " "<< br[i] << std::endl;
    }
  std::cout << lumi <<std::endl;
  std::cout << " N expected : "<<std::endl;
  for(int i=0;i<10;i++)
    {
      std::cout << m_xs[i] << " "<<N_expected[i] << " " <<xs[i]*lumi*br[i]*acceptance[i] << std::endl;
    }

  
  TGraph* N = new TGraph(10,m_xs,N_expected);
  //N->SetName("expected signal yield");
  grgreen->GetXaxis()->SetTitle("m_{VV} [GeV]");
  grgreen->GetYaxis()->SetTitle("number signal events");
  grgreen->GetYaxis()->SetTitleOffset(1.3);
  grgreen->SetTitle("");
  TCanvas* c_N = new TCanvas("c_N","c_N",600,400);
  gPad->SetRightMargin(0.1);
  gPad->SetLeftMargin(0.1);
  limit->SetLineColor(kBlue);
  limit->SetLineWidth(3);
  c_N->SetLogy();
  N->SetLineColor(kRed);
  N->SetLineWidth(2);
  //N->Draw("A");
  grgreen->SetMaximum(1000);
  grgreen->Draw("AF");
  gryellow->Draw("Fsame");
  limit->Draw("Csame");
  N->Draw("Lsame");
  TLegend* leg = new TLegend(0.59,0.65,0.95,0.89);
  leg->SetFillColor(kWhite);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.04);
  leg->SetBorderSize(0);
  
  string title = "Preliminary";
  string cms = "#font[62]{CMS} #font[52]{"+string(title)+"} ";
  string lumitext = "2.6 fb^{-1}, #sqrt{s} = 13 TeV";
  string cmstext = "CMS ,2.6 fb^{-1}, #sqrt{s} = 13 TeV";
  if(decayMode.find("had")==string::npos){lumitext = "2.1 fb^{-1}, #sqrt{s} = 13 TeV";}
  string theory = "G #rightarrow WW, #Gamma = "+swidth;
  if(dependsOnKtilde)
  {
    theory = "G #rightarrow WW, #tilde{k} = "+sktilde;
  }
  if(ModelName.find("RSGrav")!=string::npos)
  {
   theory = "RS #rightarrow WW, #Gamma = "+swidth;
   if(dependsOnKtilde)
    {
      theory = "RS #rightarrow WW, #tilde{k} = "+sktilde;
    }
  }
  
  leg->AddEntry(grgreen,"Expected (95%)","f");
  leg->AddEntry(gryellow,"Expected (68%)","f");
  leg->AddEntry(limit,"observed","L");
  leg->AddEntry(N,theory.c_str(),"L");
  leg->Draw("same");
  
  TLatex CMS;
  int y = 1050;
  int x = 500;
  int x2 = 3400;
  if(decayMode.find("jjjj")!= string::npos){y=1050;x=1000;x2=3000;}
  CMS.SetTextFont(43);
  CMS.SetTextSize(18);
  CMS.DrawLatex(x,y,cms.c_str());
  CMS.DrawLatex(x2,y,lumitext.c_str());
  
  c_N->Update();
  if(dependsOnKtilde)
  {
    c_N->SaveAs(("/usr/users/dschaefer/root/results/misc/"+ModelName+"_limit_"+decayMode+"_ktilde"+swidth+".pdf").c_str());
  }
  else
  {
  c_N->SaveAs(("/usr/users/dschaefer/root/results/misc/"+ModelName+"_limit_"+decayMode+"_"+swidth+".pdf").c_str());
  }
  
  
  //===========================================================================================
  //======== my own produced samples with ktilde = 0.095 ======================================
  //===========================================================================================
  
  
  
  float* acc2 = getAcceptance(decayMode,0.095);
  float* xs_new = getTheoryCrossSection(ModelName,0.095);
  
  for(int i=0;i<10;i++)
  {
   std::cout << " acceptance int : " << acceptance[i] <<std::endl;
   std::cout << " acceptance 2   : " << acc2[i] << std::endl;
  }
  
   // TGraph* testa
   // TCanvas* test2 = new TCanvas("test2","test2",400,400);
//   obsl->Draw("AL");
//   Neve->Draw("LSAME");
  
  float* N_expected2 = getNumberOfExpectedEvents(xs_new,m_xs,acc2,ModelName,decayMode);
  TGraph* obsl = getObservedLimit(ModelName,decayMode,0.095,1);
  TGraph* Neve = new TGraph(10,m_xs,N_expected2);
  

  
  
  TGraph* pl = getExcludedPoints(ModelName,decayMode,obsl,Neve,0.095);
  pl->SetLineWidth(3);
  pl->SetLineColor(kWhite);
  //pl->SetFillStyle(3013);
  //pl->SetFillColor(kWhite);
  
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
  TCanvas* MyC = new TCanvas("MyC","MyC",800,600);
  MyC->SetRightMargin(0.19);
//   MyC->SetLeftMargin(0.12);
//   MyC->SetTopMargin(0.08);
//   MyC->SetBottomMargin(0.15);
  MyC->SetLogz();
  obsLim->Draw("COLZ");
  //pl->Draw("f");
  pl->Draw("Same");
  
  std::map<float,float> mass_acc;
  for(int i=0;i<10;i++)
  {
   mass_acc.insert(std::pair<float, float>(m_xs[i],acc2[i]));   
  }
  TGraph* allpoints = findAllExcludedPoints(ModelName,decayMode, mass_acc,0.095);
  MyC->cd();
  allpoints->Draw("Psame");
  
  
  float massmax = 4500;
  float massmin = 800;
  int n = (massmax-massmin)/100;
  float* k = new float[n*2];
  int t=0;
  for(int i=0;i<=n;i++)
  {
    k[i] = getKtilde("RSGrav",massmin+i*100,0.3);
    std::cout << "mass max: "<< massmin+i*100 << " ktilde " << k[i]<<std::endl;
  }
  for(int i=n;i<2*n;i++)
  {
   k[i] = getKtilde("RSGrav",massmin+(i-n)*100,0.02);
   std::cout << " mass min : "<< massmin+(i-n)*100 << " ktilde " << k[i] << std::endl;
  }
  
  printWidthForKtilde("RSGrav",0.12,3600,800);
  printWidthForKtilde("RSGrav",0.2 ,2400,800);
  printWidthForKtilde("RSGrav",0.3 ,1800,800);
  printWidthForKtilde("RSGrav",0.4 ,1500,800);
  printWidthForKtilde("RSGrav",0.5 ,1100 ,800);
  printWidthForKtilde("RSGrav",0.05,4500,2000);
  printWidthForKtilde("RSGrav",0.03,4600,3200);
  
}
