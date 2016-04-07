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
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "WorkOnHistos.h"
#include "TLatex.h"
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
#include "RooFFTConvPdf.h"
#include "TObject.h"
#include "TLegend.h"
#include "RooHist.h"
#include "RooPolynomial.h"
#include "RooChebychev.h"
#include "RooProdPdf.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
  
  
  
//===========================================================================================

void checkFitCBBW(ofstream &logfile,float mass,float width,string channel, string modelName,string category,double Ymax, bool testGeneratedKinematics,bool testKinematicsWithoutSelection, bool testMatchedJet)
{
   
  float gamma = width*mass;
  
  string Mass = std::to_string(int(mass));
    int temp_width = width*10;
  string swidth = std::to_string(temp_width);

  
  logfile << modelName <<" : "<<mass<< " : "<< width  << std::endl;
  
  string sMCname = "MC sample, m_{VV}="+Mass+", width=0."+swidth;
  string suffix ="#"+channel;
  if(channel.find("mu")==string::npos)
  {
    suffix = "e";
  }
  string name= modelName+" #rightarrow "+suffix+", m_{WW} = "+Mass;
  string label = channel+"_"+category;
  if(testGeneratedKinematics)
  {label= label+"_matchedJet_gen";}
  if(testKinematicsWithoutSelection)
  {label= label+"_withoutSelections";}
  if(testMatchedJet)
  {label= label+"_jetMatchingNoSelections";}
  
  string NameNarrowFitResult =
  ("/usr/users/dschaefer/root/results/testFit/logfiles/Narrow_Fit_M"+Mass+"_"+channel+"_HP.txt");
  
  string NameWideFitResult = ("/usr/users/dschaefer/root/results/testFit/semileptonic/ToWW/logfiles/"+modelName+"_Fit_M"+Mass+"_width0p"+swidth+"_"+channel+"_"+category+".txt");
  
  string soutput_pdf_name = "/usr/users/dschaefer/root/results/testFit/semileptonic/ToWW/M"+Mass+"/"+modelName+"_M"+Mass+"_"+"width0p"+swidth+"_"+label+".pdf";
  
   string soutput_pdf_name2 = "/usr/users/dschaefer/root/results/testFit/semileptonic/ToWW/M"+Mass+"/BulkG_M"+Mass+"_"+"width0p0_"+channel+"_"+category+"_narrow.pdf";
   
   string sfile_narrow ="/usr/users/dschaefer/root/results/BulkGrav/BulkGrav_M"+Mass+"_width0p0_mWW_"+channel+"_"+category+".root";
   
    if(testKinematicsWithoutSelection)
    {
       sfile_narrow ="/usr/users/dschaefer/root/results/BulkGrav/BulkGrav_M"+Mass+"_width0p0_mWW_"+channel+"_"+category+"_withoutSelection.root";
    }
 
  string sfile_width ="/usr/users/dschaefer/root/results/"+modelName+"/"+modelName+"_M"+Mass+"_width0p"+swidth+"_mWW_"+label+".root";
 
  const char* file_width = sfile_width.c_str();
  const char* file_narrow = sfile_narrow.c_str();
  const char* MCname= sMCname.c_str();
  const char* title = name.c_str();
  const char* output_pdf_name = soutput_pdf_name.c_str();
  const char* output_pdf_name2 = soutput_pdf_name2.c_str();
  
  TFile *f = new TFile(file_width,"READ");
  TFile *f_narrow = new TFile(file_narrow,"READ");
  TH1F* h = (TH1F*) f->Get("hmWW");
  TH1F* h_narrow = (TH1F*) f_narrow->Get("hmWW_full");
  int tmp = h_narrow->GetSize()-2;
  double massMax_narrow = h_narrow->GetBinLowEdge(h_narrow->GetBin(tmp));
  double massMin_narrow = h_narrow->GetBinLowEdge(1);
  tmp = h->GetSize()-2;
  logfile << "number bins : " << tmp << " chi2 : ";
  double massMax_width = h->GetBinLowEdge(h->GetBin(tmp));
  double massMin_width = h->GetBinLowEdge(1);
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
  
  if(mass < 1200)
  {
    
   sCB =50; sCBMin =40; sCBMax=70;
   n1 = 15.; n1Min=5.;n1Max =25.;
   n2 = 15.; n2Min=5.;n2Max =25.;
   alpha1 =1.5;alpha1Min=1.;alpha1Max=1.9;
   alpha2 =1.64;alpha2Min=1.;alpha2Max=1.9;
  }
  if(mass < 1800 and mass >=1200)
  {
    
   sCB =77; sCBMin =40; sCBMax=90;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20.; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.9;
   alpha2 =1.64;alpha2Min=0.5;alpha2Max=3.9;
  }
  if(mass < 2500 and mass >=1800)
  {
    sCB =100; sCBMin =80; sCBMax=175;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
    
  }
  if(mass < 3500 and mass >=2500)
  {
   sCB =150; sCBMin =110; sCBMax=175;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
  }
  if(mass >=3500)
  {
  sCB =200; sCBMin =140; sCBMax=230;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
  }
  
 
  
  
  
  
  RooRealVar m_new = m_width;
  m_new.setBins(1000,"cache");
  RooRealVar mean_CB(("mean_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("mean_CB_M"+Mass+"_"+channel+"_"+category).c_str(),mass+90,mass-20,mass+100);
  RooRealVar sigma_CB(("sigma_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("sigma_CB_M"+Mass+"_"+channel+"_"+category).c_str(),sCB,sCBMin,sCBMax);
  RooRealVar n1_CB(("n1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("n1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),n1,n1Min,n1Max);
  RooRealVar alpha2_CB(("alpha2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("alpha2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),alpha2,alpha2Min,alpha2Max);
  RooRealVar n2_CB(("n2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("n2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),n2,n2Min,n2Max);
  RooRealVar alpha1_CB(("alpha1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("alpha1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),alpha1,alpha1Min,alpha1Max); 
  
  RooRealVar mean_conv("mean_conv","mean_conv",0);
  RooRealVar width_BW("width_BW","width_BW",gamma);
 
  
  RooDoubleCrystalBall CB("CB","CB",m_narrow,mean_CB,sigma_CB,alpha1_CB,n1_CB,alpha2_CB,n2_CB);
  
  RooDataHist dh_narrow("dh_narrow","dh_narrow",m_narrow,RooFit::Import(*h_narrow));
  RooFitResult* FitRESULT_narrow = CB.fitTo(dh_narrow,RooFit::Save());
  FitRESULT_narrow->Print();
  RooArgList finalParameters = FitRESULT_narrow->floatParsFinal();
  RooArgSet *FitRESULT_narrow_set = new RooArgSet(finalParameters);
  FitRESULT_narrow_set->writeToFile(NameNarrowFitResult.c_str());
  
  mean_CB.getVal();
  sigma_CB.getVal();
  n1_CB.getVal();
  n2_CB.getVal();
  alpha1_CB.getVal();
  alpha2_CB.getVal();
  RooBWRunPdf BW("BW","BW",m_new,mean_CB,width_BW);
  RooDoubleCrystalBall CB_fitted("CB_fitted","CB_fitted",m_new,mean_conv,sigma_CB,alpha1_CB,n1_CB,alpha2_CB,n2_CB);
  
  RooDataHist dh("dh","dh",m_width,RooFit::Import(*h));
  
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
     if(mass == 3000 or mass ==4000)
      {
	RooRealVar a0("a0","a0",0,-10,10);
	//RooRealVar a1("a1","a1",0);
	//RooRealVar a2("a2","a2",0,-10,10);
	RooRealVar mean_CB_fitted("mean_CB_fitted","mean_CB_fitted",mean_CB.getValV());
	RooRealVar sigma_CB_fitted("sigma_CB_fitted","sigma_CB_fitted",sigma_CB.getValV());
	RooRealVar n1_CB_fitted("n1_CB_fitted","n1_CB_fitted",n1_CB.getValV());
	RooRealVar alpha2_CB_fitted("alpha2_CB_fitted","alpha2_CB_fitted",alpha2_CB.getValV());
	RooRealVar n2_CB_fitted("n2_CB_fitted","n2_CB_fitted",n2_CB.getValV());
	RooRealVar alpha1_CB_fitted("alpha1_CB_fitted","alpha1_CB_fitted",alpha1_CB.getValV()); 
   
	RooChebychev p1("p1","p1",m_width,RooArgList(a0));
	RooDoubleCrystalBall 									DCB_fitted("DCB_fitted","DCB_fitted",m_width,mean_conv,sigma_CB_fitted,alpha1_CB_fitted,n1_CB_fitted,alpha2_CB_fitted,n2_CB_fitted);
	RooBWRunPdf BW_fitted("BW_fitted","BW_fitted",m_width,mean_CB_fitted,width_BW);
   
   
	RooAbsPdf* MyPDF = new RooFFTConvPdf("MyPDF","MyPDF",m_new,BW_fitted,DCB_fitted);
 
	RooProdPdf model_pdf("model_pdf","model_pdf",*MyPDF,p1);
	//model_pdf.setBufferFraction(5.0);
	RooFitResult* fitRESULT = model_pdf.fitTo(dh,RooFit::Save());
	fitRESULT->Print();
	RooArgList finalParameters = fitRESULT->floatParsFinal();
	RooArgSet *FitRESULT_set = new RooArgSet(finalParameters);
	FitRESULT_set->writeToFile(NameWideFitResult.c_str());
	
	
	
	MyPDF->plotOn(frame);
	model_pdf.plotOn(frame,"name_model_pdf",RooFit::MarkerColor(kRed),RooFit::LineColor(kRed));
   
  
	}
      else
      {
	RooFFTConvPdf model_pdf("conv","conv",m_new,BW,CB_fitted); 
	model_pdf.setBufferFraction(5.0);
	model_pdf.plotOn(frame,"name_model_pdf");
      }
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
  TPad* pad1 = new TPad("pad1","pad1",0.,0.3,1.,1.0);
  TPad* pad2 = new TPad("pad2","pad2",0.,0.,1.0,0.3);
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
  logfile<< chi2 << std::endl;
  string schi2 = "X^{2} ="+std::to_string(chi2); 
  const char* textChi2 = schi2.c_str();
//   TLatex text;
//   text.SetTextFont(43);
//   text.SetTextSize(16);
//   text.DrawLatex(massMin_width+(massMax_width-massMin_width)/10.,Ymax-Ymax/10.,textChi2);
  
  RooPlot* frame2 = m_width.frame();
  TObject* obj = (TObject*) frame->pullHist();
  
   double max = 1;
   if(temp_width <= 1)
   {max =5;}
   if(temp_width <= 2)
   {max =8;}
   if(temp_width <= 3)
   {max=15;}
   
  frame2->addObject(obj);
  frame2->SetMinimum(-max);
  frame2->SetMaximum(max);
  frame2->SetTitle("pulls");
  pad2->cd();
  frame2->Draw();
  
  
  canvas1->SaveAs(output_pdf_name);
  
  TCanvas* canvas2 = new TCanvas("canvas2","canvas2",400,400);
  canvas2->cd();
  frame_narrow_fit->SetTitle("fit of narrow resonance with DCB function");
  frame_narrow_fit->Draw();
  canvas2->SaveAs(output_pdf_name2);
  
}

//===========================================================================================

void checkNarrowFit(float mass,string channel, string modelName, string category)
{
   
  
  
  string Mass = std::to_string(int(mass));
  
  string sMCname = "MC sample, m_{VV}="+Mass+", width=0.0";
  string suffix ="#"+channel;
  if(channel.find("mu")==string::npos)
  {
    suffix = "e";
  }
  string name= modelName+" #rightarrow "+suffix+", m_{WW} = "+Mass;
  
   string soutput_pdf_name2 = "/usr/users/dschaefer/root/results/testFit/semileptonic/ToWW/narrow/"+modelName+"_M"+Mass+"_"+"width0p0_"+channel+"_"+category+"_narrow.pdf";
 
  string sfile_narrow = "/usr/users/dschaefer/root/results/"+modelName+"/"+modelName+"_M"+Mass+"_width0p0_mWW_"+channel+"_"+category+".root";
  
  string NameNarrowFitResult =
  "/usr/users/dschaefer/root/results/testFit/semileptonic/ToWW/logfiles/Narrow_Fit_"+modelName+"_M"+Mass+"_"+channel+"_"+category+".txt";
  
  const char* file_narrow = sfile_narrow.c_str();
  const char* MCname= sMCname.c_str();
  const char* title = name.c_str();
  const char* output_pdf_name2 = soutput_pdf_name2.c_str();
  
  
  TFile *f_narrow = new TFile(file_narrow,"READ");
  TH1F* h_narrow = (TH1F*) f_narrow->Get("hmWW");
  int tmp = h_narrow->GetSize()-1;
  double massMax_narrow = h_narrow->GetBinLowEdge(h_narrow->GetBin(tmp));
  double massMin_narrow = h_narrow->GetBinLowEdge(1);
  
  RooRealVar m_narrow("m","m",massMin_narrow, massMax_narrow);
  
  
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
  
 
  
  if(mass < 1200)
  {
    
   sCB =50; sCBMin =40; sCBMax=70;
   n1 = 15.; n1Min=5.;n1Max =25.;
   n2 = 15.; n2Min=5.;n2Max =25.;
   alpha1 =1.5;alpha1Min=1.;alpha1Max=1.9;
   alpha2 =1.64;alpha2Min=1.;alpha2Max=1.9;
  }
  if(mass < 1800 and mass >=1200)
  {
    
   sCB =77; sCBMin =40; sCBMax=90;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20.; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.9;
   alpha2 =1.64;alpha2Min=0.5;alpha2Max=3.9;
  }
  if(mass < 2500 and mass >=1800)
  {
    sCB =100; sCBMin =80; sCBMax=175;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
    
  }
  if(mass < 3500 and mass >=2500)
  {
   sCB =150; sCBMin =110; sCBMax=175;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
  }
  if(mass >=3500)
  {
  sCB =200; sCBMin =140; sCBMax=230;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
  }

  
 
  RooRealVar mean_CB(("mean_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("mean_CB_M"+Mass+"_"+channel+"_"+category).c_str(),mass+90,mass-20,mass+100);
  RooRealVar sigma_CB(("sigma_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("sigma_CB_M"+Mass+"_"+channel+"_"+category).c_str(),sCB,sCBMin,sCBMax);
  RooRealVar n1_CB(("n1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("n1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),n1,n1Min,n1Max);
  RooRealVar alpha2_CB(("alpha2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("alpha2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),alpha2,alpha2Min,alpha2Max);
  RooRealVar n2_CB(("n2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("n2_CB_M"+Mass+"_"+channel+"_"+category+"_HP").c_str(),n2,n2Min,n2Max);
  RooRealVar alpha1_CB(("alpha1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("alpha1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),alpha1,alpha1Min,alpha1Max); 
  
 
  
  RooDoubleCrystalBall CB("CB","CB",m_narrow,mean_CB,sigma_CB,alpha1_CB,n1_CB,alpha2_CB,n2_CB);
  
  RooDataHist dh_narrow("dh_narrow","dh_narrow",m_narrow,RooFit::Import(*h_narrow));
  RooFitResult* FitRESULT_narrow = CB.fitTo(dh_narrow,RooFit::Save());
  FitRESULT_narrow->Print();
  RooArgList finalParameters = FitRESULT_narrow->floatParsFinal();
  RooArgSet *FitRESULT_narrow_set = new RooArgSet(finalParameters);
  FitRESULT_narrow_set->writeToFile((NameNarrowFitResult).c_str());
  
  mean_CB.getVal();
  sigma_CB.getVal();
  n1_CB.getVal();
  n2_CB.getVal();
  alpha1_CB.getVal();
  alpha2_CB.getVal();
  RooDoubleCrystalBall CB_fitted("CB_fitted","CB_fitted",m_narrow,mean_CB,sigma_CB,alpha1_CB,n1_CB,alpha2_CB,n2_CB);
  
  
  RooPlot* frame_narrow_fit = m_narrow.frame();
  frame_narrow_fit->GetXaxis()->SetTitle("m_{VV} [GeV]");
  frame_narrow_fit->SetTitle("Double Crystall Ball");
  dh_narrow.plotOn(frame_narrow_fit);
  CB.plotOn(frame_narrow_fit);
  
  TCanvas* canvas2 = new TCanvas("canvas2","canvas2",400,400);
  canvas2->cd();
  frame_narrow_fit->SetTitle("fit of narrow resonance with DCB function");
  frame_narrow_fit->Draw();
  canvas2->SaveAs(output_pdf_name2);
  
}

//===================================================================================

void checkNarrowFit(float mass,string channel,string modelName ,string category, TH1F* h_narrow)
{
 
  string Mass = std::to_string(int(mass));
  category = category+"_debug";
  string sMCname = "MC sample, m_{VV}="+Mass+", width=0.0";
  string suffix ="#"+channel;
  if(channel.find("mu")==string::npos)
  {
    suffix = "e";
  }
  string name= modelName+" #rightarrow "+suffix+", m_{WW} = "+Mass;
  
   string soutput_pdf_name2 = "/usr/users/dschaefer/root/results/testFit/narrow/"+modelName+"_M"+Mass+"_"+"width0p0_"+channel+"_"+category+"_narrow.pdf";
 
 
  const char* MCname= sMCname.c_str();
  const char* title = name.c_str();
  const char* output_pdf_name2 = soutput_pdf_name2.c_str();
  
 
  int tmp = h_narrow->GetSize()-1;
  double massMax_narrow = h_narrow->GetBinLowEdge(h_narrow->GetBin(tmp));
  double massMin_narrow = h_narrow->GetBinLowEdge(1);
  
  RooRealVar m_narrow("m","m",massMin_narrow, massMax_narrow);
  
  
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
  
 
  
  if(mass < 1200)
  {
    
   sCB =50; sCBMin =40; sCBMax=70;
   n1 = 15.; n1Min=5.;n1Max =25.;
   n2 = 15.; n2Min=5.;n2Max =25.;
   alpha1 =1.5;alpha1Min=1.;alpha1Max=1.9;
   alpha2 =1.64;alpha2Min=1.;alpha2Max=1.9;
  }
  if(mass < 1800 and mass >=1200)
  {
    
   sCB =77; sCBMin =40; sCBMax=90;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20.; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.9;
   alpha2 =1.64;alpha2Min=0.5;alpha2Max=3.9;
  }
  if(mass < 2500 and mass >=1800)
  {
    sCB =100; sCBMin =80; sCBMax=175;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
    
  }
  if(mass < 3500 and mass >=2500)
  {
   sCB =150; sCBMin =110; sCBMax=175;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
  }
  if(mass >=3500)
  {
  sCB =200; sCBMin =140; sCBMax=230;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
  }

  
 
  RooRealVar mean_CB(("mean_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("mean_CB_M"+Mass+"_"+channel+"_"+category).c_str(),mass+90,mass-20,mass+100);
  RooRealVar sigma_CB(("sigma_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("sigma_CB_M"+Mass+"_"+channel+"_"+category).c_str(),sCB,sCBMin,sCBMax);
  RooRealVar n1_CB(("n1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("n1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),n1,n1Min,n1Max);
  RooRealVar alpha2_CB(("alpha2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("alpha2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),alpha2,alpha2Min,alpha2Max);
  RooRealVar n2_CB(("n2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("n2_CB_M"+Mass+"_"+channel+"_"+category+"_HP").c_str(),n2,n2Min,n2Max);
  RooRealVar alpha1_CB(("alpha1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("alpha1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),alpha1,alpha1Min,alpha1Max); 
  
 
  
  RooDoubleCrystalBall CB("CB","CB",m_narrow,mean_CB,sigma_CB,alpha1_CB,n1_CB,alpha2_CB,n2_CB);
  
  RooDataHist dh_narrow("dh_narrow","dh_narrow",m_narrow,RooFit::Import(*h_narrow));
  RooFitResult* FitRESULT_narrow = CB.fitTo(dh_narrow,RooFit::Save());
  FitRESULT_narrow->Print();
  RooArgList finalParameters = FitRESULT_narrow->floatParsFinal();
  RooArgSet *FitRESULT_narrow_set = new RooArgSet(finalParameters);
  FitRESULT_narrow_set->writeToFile(("/usr/users/dschaefer/root/results/testFit/logfiles/Narrow_Fit_M"+Mass+"_"+channel+"_"+category+".txt").c_str());
  
  mean_CB.getVal();
  sigma_CB.getVal();
  n1_CB.getVal();
  n2_CB.getVal();
  alpha1_CB.getVal();
  alpha2_CB.getVal();
  RooDoubleCrystalBall CB_fitted("CB_fitted","CB_fitted",m_narrow,mean_CB,sigma_CB,alpha1_CB,n1_CB,alpha2_CB,n2_CB);
  
  
  RooPlot* frame_narrow_fit = m_narrow.frame();
  frame_narrow_fit->GetXaxis()->SetTitle("m_{VV} [GeV]");
  frame_narrow_fit->SetTitle("Double Crystall Ball");
  dh_narrow.plotOn(frame_narrow_fit);
  CB.plotOn(frame_narrow_fit);
  
  TCanvas* canvas2 = new TCanvas("canvas2","canvas2",400,400);
  canvas2->cd();
  frame_narrow_fit->SetTitle("fit of narrow resonance with DCB function");
  frame_narrow_fit->Draw();
  canvas2->SaveAs(output_pdf_name2); 
 
}

//=====================================================================================================

RooRealVar InterpolateExtraDegreeOfFreedom(string channel,string category,float mass, float GMRatio)
{
  string modelList[3] ={"Wprime","Zprime","RSGrav"};
  double a0_max;
  double a0_min;
  TFile *fileIn2 =new TFile();
  for(int i=0;i<3;i++)
  {
    string filename = "/home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/interpolationFiles/InterpolateHighMassCorrections_"+modelList[i]+"_"+category+".root";
    std::cout << filename << std::endl;
    TFile* tmp = fileIn2->Open(filename.c_str(),"READ");
    std::cout<<tmp<<std::endl;
    TGraph* g_a0_M4000 = (TGraph*) tmp->Get("a0_over_gamma_M4000_el");
    TGraph* g_a0_M3000 = (TGraph*) tmp->Get("a0_over_gamma_M3000_el");
    if(channel.find("mu")!=string::npos)
    {
    TGraph* g_a0_M4000 = (TGraph*) tmp->Get("a0_over_gamma_M4000_mu");
    TGraph* g_a0_M3000 = (TGraph*) tmp->Get("a0_over_gamma_M3000_mu");
    }
    fileIn2->Close();
    //RooRealVar rrv_a0("rrv_a0","rrv_a0", g_a0->Eval(float(GMRatio),0,"a"));
    double a = (g_a0_M3000->Eval(float(GMRatio),0,"a")-g_a0_M4000->Eval(float(GMRatio),0,"a"))/(3000-4000);
    double a00 = g_a0_M4000->Eval(float(GMRatio),0,"a") - a*4000;
    double a0 = a*mass + a00;
    if(i==0)
    {
     a0_max = a0;
     a0_min = a0;
    }
    if(a0>a0_max)
    {
     a0_max = a0; 
    }
    if(a0<a0_min)
    {
     a0_min = a0; 
    }
  
  }
  double error = TMath::Abs((a0_max-a0_min)/2);
  RooRealVar a0_final("a0","a0",a0_min+error);
  a0_final.setError(error);
  return a0_final;
}

//=====================================================================================================

void getShapeFromInterpolation(string Model, string channel,string category,float mass,float GMRatio, RooRealVar rrv_x, RooPlot* frame, int color,string ColorScheme)
{
    double gamma = GMRatio*mass;
    string fileName1 = "/home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/interpolationFiles/BulkG_WW_lvjj_"+channel+"_"+category+".root";
    TFile *fileIn = new TFile(fileName1.c_str(),"READ");
    
    TGraph* g_mean = (TGraph*) fileIn->Get("mean");
    TGraph* g_sigma = (TGraph*) fileIn->Get("sigma");
    TGraph* g_n1 = (TGraph*) fileIn->Get("n1");
    TGraph* g_n2 = (TGraph*) fileIn->Get("n2");
    TGraph* g_alpha1 = (TGraph*) fileIn->Get("alpha1");
    TGraph* g_alpha2 = (TGraph*) fileIn->Get("alpha2");
  
  RooRealVar rrv_mean_CB("rrv_mean_CB","rrv_mean_CB", g_mean->Eval(int(mass)));
  RooRealVar rrv_sigma_CB ("rrv_sigma_CB","rrv_sigma_CB", g_sigma->Eval(int(mass)));
  RooRealVar rrv_n1_CB("rrv_n1_CB","rrv_n1_CB", g_n1->Eval(int(mass)));
  RooRealVar rrv_alpha2_CB("rrv_alpha2_CB","rrv_alpha2_CB",g_alpha2->Eval(int(mass)));
  RooRealVar rrv_n2_CB("rrv_n2_CB","rrv_n2_CB",g_n2->Eval(int(mass)));
  RooRealVar rrv_alpha1_CB("rrv_alpha1_CB","rrv_alpha1_CB",g_alpha1->Eval(int(mass)));
  string model_pdf_name ="model_pdf"+channel+std::to_string(mass)+"width_"+std::to_string(GMRatio);
  
  if(Model.find("narrow")==string::npos)
  {
       rrv_x.setBins(1000,"cache");
       RooRealVar rrv_mean_conv("rrv_mean_conv","rrv_mean_conv",0);
       RooRealVar rrv_width_BW("rrv_width_BW","rrv_width_BW",gamma);
       RooDoubleCrystalBall CB_pdf("CB_pdf","CB_pdf",rrv_x,rrv_mean_conv,rrv_sigma_CB,rrv_alpha1_CB,rrv_n1_CB,rrv_alpha2_CB,rrv_n2_CB);
       RooBWRunPdf BW_pdf("BW_pdf","BW_pdf",rrv_x,rrv_mean_CB,rrv_width_BW);
  
       RooRealVar rrv_a0 = InterpolateExtraDegreeOfFreedom(channel,category, mass,GMRatio);
       if(rrv_a0.getValV()<0)
       {
	 std::cout <<mass <<" "<< rrv_a0.getValV() << " +/- "<<rrv_a0.getError() << std::endl;
// 	string fileName2 =  "/home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/interpolationFiles/InterpolateHighMassCorrections.root";
// 	TFile *fileIn2 = new TFile(fileName2.c_str(),"READ");
// 	TGraph* g_a0 = (TGraph*) fileIn2->Get("Graph;2");
// 	
// 	if(channel.find("el")!=string::npos)
// 	{
// 	   g_a0 = (TGraph*) fileIn2->Get("Graph;1"); 
// 	}
//         RooRealVar rrv_a0("rrv_a0","rrv_a0", g_a0->Eval(float(GMRatio),0,"a"));
        RooFFTConvPdf model_tmp("model_tmp","model_tmp", rrv_x,BW_pdf,CB_pdf,2);
        model_tmp.setBufferFraction(1.0);
        RooChebychev p1("p1","p1",rrv_x,RooArgList(rrv_a0));
        RooProdPdf model_pdf(model_pdf_name.c_str(),model_pdf_name.c_str(),model_tmp,p1);
	if(ColorScheme.find("kRed")!=string::npos)
	{
        model_pdf.plotOn(frame,RooFit::LineColor(kRed+color));
	}
	if(ColorScheme.find("kBlue")!=string::npos)
	{
	  model_pdf.plotOn(frame,RooFit::LineColor(kBlue+color));
	}
	if(ColorScheme.find("kGreen")!=string::npos)
	{
	  model_pdf.plotOn(frame,RooFit::LineColor(kGreen+color));
	}
	if(ColorScheme.find("kCyan")!=string::npos)
	{
	  model_pdf.plotOn(frame,RooFit::LineColor(kCyan+color));
	}
	if(ColorScheme.find("kYellow")!=string::npos)
	{
	  model_pdf.plotOn(frame,RooFit::LineColor(kYellow+color));
	}
        }
       else
       {
	 std::cout << "CB*BW"<<std::endl;
	 RooFFTConvPdf model_pdf(model_pdf_name.c_str(),model_pdf_name.c_str(),rrv_x,BW_pdf,CB_pdf,2);
	 model_pdf.setBufferFraction(1.0);
// 	 model_pdf.setBufferStrategy(RooFFTConvPdf::Extend);
	 if(ColorScheme.find("kRed")!=string::npos)
	{
        model_pdf.plotOn(frame,RooFit::LineColor(kRed+color));
	}
	if(ColorScheme.find("kBlue")!=string::npos)
	{
	  model_pdf.plotOn(frame,RooFit::LineColor(kBlue+color));
	}
	if(ColorScheme.find("kGreen")!=string::npos)
	{
	  model_pdf.plotOn(frame,RooFit::LineColor(kGreen+color));
	}
	if(ColorScheme.find("kCyan")!=string::npos)
	{
	  model_pdf.plotOn(frame,RooFit::LineColor(kCyan+color));
	}
	if(ColorScheme.find("kYellow")!=string::npos)
	{
	  model_pdf.plotOn(frame,RooFit::LineColor(kYellow+color));
	}
	 		
       }
  
  }
  else
  {    
    std::cout << "CB "<<std::endl;
     RooDoubleCrystalBall model_pdf(model_pdf_name.c_str(),model_pdf_name.c_str(), rrv_x,rrv_mean_CB,rrv_sigma_CB,rrv_alpha1_CB,rrv_n1_CB,rrv_alpha2_CB,rrv_n2_CB);
    // model_pdf.plotOn(frame,RooFit::LineColor(kRed+color)); 
      if(ColorScheme.find("kRed")!=string::npos)
	{
        model_pdf.plotOn(frame,RooFit::LineColor(kRed+color));
	}
	if(ColorScheme.find("kBlue")!=string::npos)
	{
	  model_pdf.plotOn(frame,RooFit::LineColor(kBlue+color));
	}
	if(ColorScheme.find("kGreen")!=string::npos)
	{
	  model_pdf.plotOn(frame,RooFit::LineColor(kGreen+color));
	}
	if(ColorScheme.find("kCyan")!=string::npos)
	{
	  model_pdf.plotOn(frame,RooFit::LineColor(kCyan+color));
	}
	if(ColorScheme.find("kYellow")!=string::npos)
	{
	  model_pdf.plotOn(frame,RooFit::LineColor(kYellow+color));
	}
  }
  
}


