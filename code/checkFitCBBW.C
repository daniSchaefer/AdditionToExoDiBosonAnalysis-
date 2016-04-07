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
 gROOT->ProcessLine(".L /home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/PDFs/HWWLVJRooPdfs.cxx+");
  gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

//run with: root -l
//.x checkFitCBBW(3000,0.1,"el","Wprime",Ymax)
//fits the DCB to the narrow width sameple -> draws convolution width BW into Canvas with MC sample with width >0
//possible models: BulkGrav, Wprime, Zprime, Radion, RSGrav but look out: not all files for all models exist
//Ymax is the maximum for the y-Axis of the convolution plot -> must be set per hand to a value so that the plot looks good


void checkFitCBBW(float mass,float width,string channel, string modelName,double Ymax,bool testGeneratedKinematics=0,bool testKinematicsWithoutSelection =0)
{
  
   
  float gamma = width*mass;
  
  std::ostringstream s;
  s<< mass;
  std::string Mass(s.str());
  std::ostringstream ss; int temp_width = width*10;
  ss<<temp_width;
  std::string swidth(ss.str());
  
  
  string sMCname = "MC sample, m_{VV}="+Mass+", width=0."+swidth;
  string suffix ="#"+channel;
  if(channel.find("mu")==string::npos)
  {
    suffix = "e";
  }
  string name= modelName+" #rightarrow "+suffix+", m_{WW} = "+Mass;
  string soutput_pdf_name = "/usr/users/dschaefer/root/results/testFit/M"+Mass+"/"+modelName+"_M"+Mass+"_"+"width0p"+swidth+"_"+channel+"_matchedJet.pdf";
  if(testGeneratedKinematics)
  {
    soutput_pdf_name = "/usr/users/dschaefer/root/results/testFit/M"+Mass+"/"+modelName+"_M"+Mass+"_"+"width0p"+swidth+"_"+channel+"_matchedJet_gen.pdf";
  }
  if(testKinematicsWithoutSelection)
  {
    soutput_pdf_name = "/usr/users/dschaefer/root/results/testFit/M"+Mass+"/"+modelName+"_M"+Mass+"_"+"width0p"+swidth+"_"+channel+"_withoutSelections.pdf";
  }
  string sfile_narrow;
  if(mass == 800 or mass ==1600)
  {
    sfile_narrow ="/usr/users/dschaefer/root/results/BulkGrav/BulkGrav_M"+Mass+"_width0p0_mWW_"+channel+".root";
    if(testKinematicsWithoutSelection)
    {
       sfile_narrow ="/usr/users/dschaefer/root/results/BulkGrav/BulkGrav_M"+Mass+"_width0p0_mWW_"+channel+"_withoutSelection.root";
    }
  }
  else
  {
  sfile_narrow ="/usr/users/dschaefer/root/results/Wprime/Wprime_M"+Mass+"_width0p0_mWW_"+channel+".root";

  }
  string sfile_width ="/usr/users/dschaefer/root/results/"+modelName+"/"+modelName+"_M"+Mass+"_width0p"+swidth+"_mWW_"+channel+".root";
  if(testGeneratedKinematics)
  {
    sfile_width ="/usr/users/dschaefer/root/results/"+modelName+"/"+modelName+"_M"+Mass+"_width0p"+swidth+"_mWW_"+channel+"_gen.root";
  }
  if(testKinematicsWithoutSelection)
  {
    sfile_width ="/usr/users/dschaefer/root/results/"+modelName+"/"+modelName+"_M"+Mass+"_width0p"+swidth+"_mWW_"+channel+"_withoutSelection.root";
  }
  const char* file_width = sfile_width.c_str();
  const char* file_narrow = sfile_narrow.c_str();
  const char* MCname= sMCname.c_str();
  const char* title = name.c_str();
  const char* output_pdf_name = soutput_pdf_name.c_str();
  
  TFile *f = new TFile(file_width,"READ");
  TFile *f_narrow = new TFile(file_narrow,"READ");
  TH1F* h = (TH1F*) f->Get("hmWW");
  TH1F* h_narrow = (TH1F*) f_narrow->Get("hmWW");
  int tmp = h_narrow->GetSize()-2;
  double massMax_narrow = h_narrow->GetBinLowEdge(h_narrow->GetBin(tmp));
  double massMin_narrow = h_narrow->GetBinLowEdge(0);
  tmp = h->GetSize()-2;
  double massMax_width = h->GetBinLowEdge(h->GetBin(tmp));
  double massMin_width = h->GetBinLowEdge(0);
  RooRealVar m_narrow("m","m",massMin_narrow, massMax_narrow);
  RooRealVar m_width("m_w","m_w",massMin_width,massMax_width);
  
  float mCBMin;
  float mCBMax;
  float sCB;
  float sCBMin;
  float sCBMax;
  float n1;
  float n1Max;
  float n1Min;
  float n2Max;
  float n2Min;
  float n2;
  float alpha1;
  float alpha11Min;
  float alpha1Max;
  float alpha1Min;
  float alpha2Max;
  float alpha2Min;
  float alpha2;
  
 
  
  if(mass == 800)
  {
    
   sCB =50; sCBMin =40; sCBMax=70;
   n1 = 15.; n1Min=5.;n1Max =25.;
   n2 = 15.; n2Min=5.;n2Max =25.;
   alpha1 =1.5;alpha1Min=1.;alpha1Max=1.9;
   alpha2 =1.64;alpha2Min=1.;alpha2Max=1.9;
  }
  if(mass == 1200)
  {
    
   sCB =50; sCBMin =40; sCBMax=70;
   n1 = 15.; n1Min=5.;n1Max =25.;
   n2 = 15.; n2Min=5.;n2Max =25.;
   alpha1 =1.5;alpha1Min=1.;alpha1Max=1.9;
   alpha2 =1.64;alpha2Min=1.;alpha2Max=1.9;
  }
  if(mass == 2000)
  {
    sCB =150; sCBMin =110; sCBMax=175;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
    
  }
  if(mass == 3000)
  {
   sCB =150; sCBMin =110; sCBMax=175;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
  }
  if(mass==4000)
  {
  sCB =200; sCBMin =140; sCBMax=230;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
  }
  
 
  
  
  
  
  RooRealVar m_new = m_width;
  m_new.setBins(1000,"cache");
  RooRealVar mean_CB("mean_CB","mean_CB",mass+90,mass-20,mass+100);
  RooRealVar sigma_CB("sigma_CB","sigma_CB",sCB,sCBMin,sCBMax);
  RooRealVar n1_CB("n1_CB","n1_CB",n1,n1Min,n1Max);
  RooRealVar alpha2_CB("alpha2_CB","alpha2_CB",alpha2,alpha2Min,alpha2Max);
  RooRealVar n2_CB("n2_CB","n2_CB",n2,n2Min,n2Max);
  RooRealVar alpha1_CB("alpha1_CB","alpha1_CB",alpha1,alpha1Min,alpha1Max); 
  
  RooRealVar mean_conv("mean_conv","mean_conv",0);
  RooRealVar width_BW("width_BW","width_BW",gamma);
 
  
  RooDoubleCrystalBall CB("CB","CB",m_narrow,mean_CB,sigma_CB,alpha1_CB,n1_CB,alpha2_CB,n2_CB);
  
  RooDataHist dh_narrow("dh_narrow","dh_narrow",m_narrow,Import(*h_narrow));
  CB.fitTo(dh_narrow);
  mean_CB.getVal();
  sigma_CB.getVal();
  n1_CB.getVal();
  n2_CB.getVal();
  alpha1_CB.getVal();
  alpha2_CB.getVal();
  RooBWRunPdf BW("BW","BW",m_new,mean_CB,width_BW);
  RooDoubleCrystalBall CB_fitted("CB_fitted","CB_fitted",m_new,mean_conv,sigma_CB,alpha1_CB,n1_CB,alpha2_CB,n2_CB);
  
  RooDataHist dh("dh","dh",m_width,Import(*h));
  
  RooPlot* frame = m_width.frame();
  frame->GetXaxis()->SetTitle("m_{VV} [GeV]");
  frame->SetTitle(title);
  frame->GetYaxis()->SetTitleOffset(1.4);
  frame->setPadFactor(1);
  dh.plotOn(frame,"name_dh");
  
  if(testKinematicsWithoutSelection)
  {
    RooBWRunPdf BW_withoutSelection("BW_wS","BW_wS",m_width,mean_CB,width_BW);
    BW_withoutSelection.plotOn(frame,"name_model_pdf");
   
  }
  else
  {
  RooFFTConvPdf model_pdf("conv","conv",m_new,BW,CB_fitted); 
  model_pdf.setBufferFraction(5.0);
  model_pdf.plotOn(frame,"name_model_pdf");
  }

  
 
  
  //BW.plotOn(frame,MarkerColor(kRed),LineColor(kRed));
  //CB.plotOn(frame,MarkerColor(kGreen),LineColor(kGreen));
  
  
  //model_pdf.fitTo(dh);
  
  RooPlot* frame_narrow_fit = m_narrow.frame();
  frame_narrow_fit->GetXaxis()->SetTitle("m_{VV} [GeV]");
  frame_narrow_fit->SetTitle("Double Crystall Ball");
  dh_narrow.plotOn(frame_narrow_fit);
  CB.plotOn(frame_narrow_fit);
  
  
  
  TCanvas* canvas1 = new TCanvas("canvas1","canvas1",400,600);
  gPad->SetLeftMargin(0.15);
  TPad* pad1 = new TPad("pad1","pad1",0.,0.2,1.,1.0);
  TPad* pad2 = new TPad("pad2","pad2",0.,0.,1.0,0.2);
  pad1->SetLeftMargin(0.15);
  pad2->SetLeftMargin(0.15);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  frame->GetYaxis()->SetTitleOffset(2.0);
  //double Ymax = 400;
  frame->SetMaximum(Ymax);
  frame->Draw();
  TString dh_name = frame->nameOf(0);
  TString model_pdf_name = frame->nameOf(1);
  TLegend* leg = new TLegend(0.48,0.89,0.89,0.8);//0.48,0.89,0.9,0.8)
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(frame->findObject(dh_name),MCname,"lep");
  if(testKinematicsWithoutSelection)
  {
  leg->AddEntry(frame->findObject(model_pdf_name),"Breit-Wigner ","L");
  }
  else
  {
    leg->AddEntry(frame->findObject(model_pdf_name),"(CB*BW)(m) ","L");
  }
  leg->Draw();
  double chi2 = frame->chiSquare();
  string schi2 = "X^{2} ="+std::to_string(chi2); 
  const char* textChi2 = schi2.c_str();
  TLatex text;
  text.SetTextFont(43);
  text.SetTextSize(16);
  text.DrawLatex(massMin_width+(massMax_width-massMin_width)/10.,Ymax-Ymax/10.,textChi2);
  
  RooPlot* frame2 = m_width.frame();
  frame2->addObject(frame->pullHist());
  frame2->SetMinimum(-25);
  frame2->SetMaximum(15);
  frame2->SetTitle("pulls");
  pad2->cd();
  frame2->Draw();
  canvas1->SaveAs(output_pdf_name);
  
  TCanvas* canvas2 = new TCanvas("canvas2","canvas2",400,400);
  canvas2->cd();
  frame_narrow_fit->Draw();
 
   
}