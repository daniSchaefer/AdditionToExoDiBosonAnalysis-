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
#include "RooCBShape.h"
  
  
  
//===========================================================================================

void checkFitCBBW(ofstream &logfile,float mass,float width,string channel, string modelName,string category,string decayMode,double Ymax, bool testGeneratedKinematics,bool testKinematicsWithoutSelection, bool testMatchedJet)
{
   
  float gamma = width*mass;
  
  string Mass = std::to_string(int(mass));
    int temp_width = width*10;
  string swidth = std::to_string(temp_width);
  string VV = determineVV(decayMode);
  string mode = determineSemilepHadOrLep(decayMode);
  
  logfile << modelName <<" : "<<mass<< " : "<< width  << std::endl;
  std::cout << modelName << " mass : "<< mass << " width : " <<width << std::endl;
  
  string sMCname = "MC sample, m_{VV}="+Mass+", width=0."+swidth;
  string suffix ="#"+channel;
  if(channel.find("el")!=string::npos)
  {
    suffix = "e";
  }
  else if(channel.find("had")!=string::npos)
  {
    suffix = "q #bar{q}'"; 
    if(modelName.find("Zprime")!=string::npos)
    {
     suffix = "q #bar{q}"; 
    }
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
  ("/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/logfiles/Narrow_Fit_M"+Mass+"_"+channel+"_HP.txt");
  
  string NameWideFitResult = ("/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/logfiles/"+modelName+"_Fit_M"+Mass+"_width0p"+swidth+"_"+channel+"_"+category+".txt");
  
  string soutput_pdf_name = "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/M"+Mass+"/"+modelName+"_M"+Mass+"_"+"width0p"+swidth+"_"+label+".pdf";
  
   string soutput_pdf_name2 = "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/M"+Mass+"/BulkG_M"+Mass+"_"+"width0p0_"+channel+"_"+category+"_narrow.pdf";
   
   string sfile_narrow ="/usr/users/dschaefer/root/results/testFit/"+mode+"/ToWW/BulkGrav/BulkGrav_M"+Mass+"_width0p0_mWW_"+channel+"_"+category+".root";
   
   if(decayMode.find("jjjj")!=string::npos)
   {
     sfile_narrow ="/usr/users/dschaefer/root/results/testFit/"+mode+"/ToWW/BulkGrav/BulkGrav_M"+Mass+"_width0p0_mWW_"+channel+"_"+category+".root";
     soutput_pdf_name2 = "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/M"+Mass+"/BulkGrav_M"+Mass+"_"+"width0p0_"+channel+"_"+category+"_narrow.pdf";
//      if(mass == 1200 or mass == 1600 or mass == 2500)
//      {
//         sfile_narrow ="/usr/users/dschaefer/root/results/testFit/"+mode+"/ToZZ/Radion/Radion_M"+Mass+"_width0p0_mWW_"+channel+"_"+category+".root";
// 	soutput_pdf_name2 = "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/M"+Mass+"/Radion_M"+Mass+"_"+"width0p0_"+channel+"_"+category+"_narrow.pdf";
//      }
   }
   
    if(testKinematicsWithoutSelection)
    {
       sfile_narrow ="/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/BulkGrav/BulkGrav_M"+Mass+"_width0p0_mWW_"+channel+"_"+category+"_withoutSelection.root";
    }
 
  string sfile_width ="/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/"+modelName+"/"+modelName+"_M"+Mass+"_width0p"+swidth+"_mWW_"+label+".root";
 
  const char* file_width = sfile_width.c_str();
  const char* file_narrow = sfile_narrow.c_str();
  const char* MCname= sMCname.c_str();
  const char* title = name.c_str();
  const char* output_pdf_name = soutput_pdf_name.c_str();
  const char* output_pdf_name2 = soutput_pdf_name2.c_str();
  
  TFile *f = new TFile(file_width,"READ");
  TFile *f_narrow = new TFile(file_narrow,"READ");
  TH1F* h = (TH1F*) f->Get("hmWW");
  //TH1F* h_narrow = (TH1F*) f_narrow->Get("hmWW_full");
  TH1F* h_narrow = (TH1F*) f_narrow->Get("hmWW");
  int tmp = h_narrow->GetSize()-2;
  double massMax_narrow = h_narrow->GetBinLowEdge(h_narrow->GetBin(tmp));
  double massMin_narrow = h_narrow->GetBinLowEdge(1);
  tmp = h->GetSize()-2;
  logfile << "number bins : " << tmp << " chi2 : ";
  double massMax_width = h->GetBinLowEdge(h->GetBin(tmp));
  double massMin_width = h->GetBinLowEdge(1);
  RooRealVar m_narrow("m","m",massMin_narrow, massMax_narrow);
  RooRealVar m_width("m_w","m_w",massMin_width,massMax_width);
  float ndf = tmp;
  std::cout << massMax_narrow <<std::endl;
  
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
    sCB =100; sCBMin =50; sCBMax=175;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
    
  }
  if(mass < 3500 and mass >=2500)
  {
   sCB =150; sCBMin =80; sCBMax=175;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
  }
  if(mass >=3500)
  {
  sCB =200; sCBMin =110; sCBMax=230;
   n1 = 10.; n1Min=0.01;n1Max =35.;
   n2 = 20; n2Min=0.01;n2Max =35.;
   alpha1 =1.5;alpha1Min=0.5;alpha1Max=3.;
   alpha2 =1.5;alpha2Min=0.5;alpha2Max=3.0;
  }
  
 
  
  
  
  
  RooRealVar m_new = m_width;
  m_new.setBins(1000,"cache");
  RooRealVar mean_CB(("mean_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("mean_CB_M"+Mass+"_"+channel+"_"+category).c_str(),mass+90,mass-20,mass+100);
  RooRealVar sigma_CB(("sigma_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("sigma_CB_M"+Mass+"_"+channel+"_"+category).c_str(),sCB,sCBMin,sCBMax);
  RooRealVar sigma_gauss(("sigma_gauss_M"+Mass+"_"+channel+"_"+category).c_str(),("sigma_gauss_M"+Mass+"_"+channel+"_"+category).c_str(),sCB,sCBMin,sCBMax);
  RooRealVar n1_CB(("n1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("n1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),n1,n1Min,n1Max);
  RooRealVar alpha2_CB(("alpha2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("alpha2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),alpha2,alpha2Min,alpha2Max);
  RooRealVar n2_CB(("n2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("n2_CB_M"+Mass+"_"+channel+"_"+category).c_str(),n2,n2Min,n2Max);
  RooRealVar alpha1_CB(("alpha1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),("alpha1_CB_M"+Mass+"_"+channel+"_"+category).c_str(),alpha1,alpha1Min,alpha1Max); 
  RooRealVar sig_frac("sig_frac","sig_frac",0.5,0.0,1.0);
  
  RooRealVar mean_conv("mean_conv","mean_conv",0);
  RooRealVar width_BW("width_BW","width_BW",gamma);
 
  
  RooDoubleCrystalBall CB("CB","CB",m_narrow,mean_CB,sigma_CB,alpha1_CB,n1_CB,alpha2_CB,n2_CB);
  
  RooCBShape ssCB("ssCB","ssCB",m_narrow,mean_CB,sigma_CB,alpha1_CB,n1_CB);
  RooGaussian gauss("gauss","gauss",m_narrow,mean_CB,sigma_gauss);
  //later: use sum pdf for all had signal modeling
  RooAddPdf sum_ssCB_gauss("ssCB_gauss","ssCB_gauss",gauss,ssCB,sig_frac);
  
  
  
  RooDataHist dh_narrow("dh_narrow","dh_narrow",m_narrow,RooFit::Import(*h_narrow));
  
  if(decayMode.find("jjjj")!=string::npos)
  {
    RooFitResult* FitRESULT_narrow = ssCB.fitTo(dh_narrow,RooFit::Save());
    FitRESULT_narrow->Print();
    RooArgList finalParameters = FitRESULT_narrow->floatParsFinal();
    RooArgSet *FitRESULT_narrow_set = new RooArgSet(finalParameters);
    FitRESULT_narrow_set->writeToFile(NameNarrowFitResult.c_str());
   
  }
  else
  {
    RooFitResult* FitRESULT_narrow = CB.fitTo(dh_narrow,RooFit::Save());
    FitRESULT_narrow->Print();
    RooArgList finalParameters = FitRESULT_narrow->floatParsFinal();
    RooArgSet *FitRESULT_narrow_set = new RooArgSet(finalParameters);
    FitRESULT_narrow_set->writeToFile(NameNarrowFitResult.c_str());
  }
  
  mean_CB.getVal();
  sigma_CB.getVal();
  n1_CB.getVal();
  n2_CB.getVal();
  alpha1_CB.getVal();
  alpha2_CB.getVal();
  sig_frac.getVal();
  sigma_gauss.getVal();
  RooBWRunPdf BW("BW","BW",m_new,mean_CB,width_BW);
  RooDoubleCrystalBall CB_fitted("CB_fitted","CB_fitted",m_new,mean_conv,sigma_CB,alpha1_CB,n1_CB,alpha2_CB,n2_CB);
  RooCBShape sCB_fitted("sCB_fitted","sCB_fitted",m_new,mean_conv,sigma_CB,alpha1_CB,n1_CB);
  
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
	
	if(decayMode.find("jjjj")!=string::npos)
	{
	  RooCBShape 							sDCB_fitted("sDCB_fitted","sDCB_fitted",m_width,mean_conv,sigma_CB_fitted,alpha1_CB_fitted,n1_CB_fitted);
	  RooBWRunPdf BW_fitted("BW_fitted","BW_fitted",m_width,mean_CB_fitted,width_BW);
   
   
	  RooAbsPdf* MyPDF = new RooFFTConvPdf("MyPDF","MyPDF",m_new,BW_fitted,sDCB_fitted);
 
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
	}
      else
      {
	if(decayMode.find("jjjj")!=string::npos)
	{
	   RooFFTConvPdf model_pdf1("conv1","conv1",m_new,BW,sCB_fitted); 
	   model_pdf1.setBufferFraction(5.0);
	   model_pdf1.plotOn(frame,"name_model_pdf"); 
	  if(mass ==1200)
	  {
	    float m_add = 80;
	    if(width < 0.3){m_add=40;}
	    if(width < 0.15){m_add=30;}
	    RooRealVar mean_new("mean_new","mean_new",mean_CB.getValV()+m_add);
	    RooBWRunPdf BW_new("BW_n","BW_n",m_width,mean_new,width_BW);
	    RooFFTConvPdf model_pdf("conv","conv",m_new,BW_new,sCB_fitted); 
	    model_pdf.setBufferFraction(5.0); model_pdf.plotOn(frame,"name_model_pdf",RooFit::MarkerColor(kRed),RooFit::LineColor(kRed));
	  }
	  else
	  {
	   RooFFTConvPdf model_pdf("conv","conv",m_new,BW,sCB_fitted); 
	   model_pdf.setBufferFraction(5.0);
	   model_pdf.plotOn(frame,"name_model_pdf"); 
	  }
	}
	else
	{
	  RooFFTConvPdf model_pdf("conv","conv",m_new,BW,CB_fitted); 
	  model_pdf.setBufferFraction(5.0);
	  model_pdf.plotOn(frame,"name_model_pdf");
	}
	
      }
  }
  
  //BW.plotOn(frame,MarkerColor(kRed),LineColor(kRed));
  //CB.plotOn(frame,MarkerColor(kGreen),LineColor(kGreen));
  
  
  //model_pdf.fitTo(dh);
  
  RooPlot* frame_narrow_fit = m_narrow.frame();
  frame_narrow_fit->GetXaxis()->SetTitle("m_{VV} [GeV]");
  frame_narrow_fit->SetTitle("Double Crystall Ball");
  dh_narrow.plotOn(frame_narrow_fit);
  if(decayMode.find("jjjj")!=string::npos)
  {
    ssCB.plotOn(frame_narrow_fit);
  }
  else
  {
    CB.plotOn(frame_narrow_fit);
  }
  
  
  
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
  double chi2 = frame->chiSquare(model_pdf_name,"dh_width");
  double chi2quantile = TMath::ChisquareQuantile(0.5,ndf);
  logfile<< chi2 <<" chi crit. : "<<chi2quantile  <<std::endl;
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

void checkNarrowFit(float mass,string channel, string modelName, string category,string decayMode)
{
   
  string VV = determineVV(decayMode);
  string mode = determineSemilepHadOrLep(decayMode);
  
  string Mass = std::to_string(int(mass));
  
  string sMCname = "MC sample, m_{VV}="+Mass+", width=0.0";
  string suffix ="#"+channel;
  if(channel.find("mu")==string::npos)
  {
    suffix = "e";
  }
  string name= modelName+" #rightarrow "+suffix+", m_{WW} = "+Mass;
  
   string soutput_pdf_name2 = "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/narrow/"+modelName+"_M"+Mass+"_"+"width0p0_"+channel+"_"+category+"_narrow.pdf";
 
  string sfile_narrow = "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/"+modelName+"/"+modelName+"_M"+Mass+"_width0p0_mWW_"+channel+"_"+category+".root";
  
  string NameNarrowFitResult =
  "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/logfiles/Narrow_Fit_"+modelName+"_M"+Mass+"_"+channel+"_"+category+".txt";
  
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
    g_a0_M4000 = (TGraph*) tmp->Get("a0_over_gamma_M4000_mu");
    g_a0_M3000 = (TGraph*) tmp->Get("a0_over_gamma_M3000_mu");
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
  std::cout << " a :  " << a << std::endl;
  std::cout << " a00 :  " << a00 << std::endl;
  std::cout << "g_M3 eval : " << g_a0_M3000->Eval(float(GMRatio),0,"a") <<std::endl;
  std::cout << "g_M4 eval : " << g_a0_M4000->Eval(float(GMRatio),0,"a") <<std::endl;
  }
  double error = TMath::Abs((a0_max-a0_min)/2);
  RooRealVar a0_final("a0","a0",a0_min+error);
  a0_final.setError(error);
  
  std::cout <<"a0 : " << a0_final.getValV()<<std::endl;
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

//===========================================================================
//===== all hadronic channel -> fit narrow function        ==================
//===========================================================================
// RooAddPdf* narrow_model_allHad_fitted(string category,float mass,float mean_value_for_return_pdf,RooRealVar m_width)
// {
//   string file_narrow = "/usr/users/dschaefer/root/results/testFit/hadronic/ToWW/BulkGrav/BulkGrav_M"+std::to_string(int(mass))+"_width0p0_mWW_had_"+category+".root";
//   TFile *f_narrow = new TFile(file_narrow.c_str(),"READ");
//   TH1F* h_narrow = dynamic_cast<TH1F*>(f_narrow->Get("hmWW"));
//   int tmp = h_narrow->GetSize()-2;
//   double massMax_narrow = h_narrow->GetBinLowEdge(h_narrow->GetBin(tmp));
//   double massMin_narrow = h_narrow->GetBinLowEdge(1);
//   RooRealVar m_narrow("m","m",massMin_narrow, massMax_narrow);
//   
//   float sCB = 50;
//   float sCBMin = 40;
//   float sCBMax = 230;
//   float n1 =15.;
//   float n1Max = 35.;
//   float n1Min = 5.;
//   float alpha1 = 1.5;
//   float alpha1Min = 0.5;
//   float alpha1Max = 5.;
//   
//   RooRealVar mean_CB(("mean_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("mean_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),mass+90,mass-20,mass+100);
//   RooRealVar sigma_CB(("sigma_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sigma_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),sCB,sCBMin,sCBMax);
//   RooRealVar sigma_gauss(("sigma_gauss_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sigma_gauss_M"+std::to_string(int(mass))+"_had_"+category).c_str(),sCB,sCBMin,sCBMax);
//   RooRealVar n1_CB(("n1_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("n1_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),n1,n1Min,n1Max);
//   RooRealVar alpha1_CB(("alpha1_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("alpha1_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),alpha1,alpha1Min,alpha1Max); 
//   RooRealVar sig_frac(("sig_frac_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sig_frac_M"+std::to_string(int(mass))+"_had_"+category).c_str(),0.5,0.0,1.0);
//   
//   RooCBShape ssCB("ssCB","ssCB",m_narrow,mean_CB,sigma_CB,alpha1_CB,n1_CB);
//   RooGaussian gauss("gauss","gauss",m_narrow,mean_CB,sigma_gauss);
//   //later: use sum pdf for all had signal modeling
//   RooAddPdf sum_ssCB_gauss("ssCB_gauss","ssCB_gauss",gauss,ssCB,sig_frac);
//   
//   RooDataHist dh_narrow("dh_narrow","dh_narrow",m_narrow,RooFit::Import(*h_narrow));
//   
//   RooFitResult* fit_narrow = sum_ssCB_gauss.fitTo(dh_narrow,RooFit::Save());
//   fit_narrow->Print();
//   
//   RooPlot* frame_narrow = m_narrow.frame();
//   frame_narrow->GetXaxis()->SetTitle("m_{VV} [GeV]");
//   frame_narrow->SetTitle("narrow fit with gauss + sCB");
//   dh_narrow.plotOn(frame_narrow);
//   sum_ssCB_gauss.plotOn(frame_narrow);
//   TCanvas*c_narrow = new TCanvas("c_narrow","c_narrow",400,400);
//   c_narrow->cd();
//   frame_narrow->Draw();
//   
//   std::cout << mean_CB.getVal()       <<std::endl;
//   std::cout << sigma_CB.getVal()      <<std::endl;
//   std::cout << sigma_gauss.getVal()   <<std::endl;
//   std::cout << n1_CB.getVal()         <<std::endl;
//   std::cout << alpha1_CB.getVal()     <<std::endl;
//   std::cout << sig_frac.getVal()      <<std::endl; 
//   
//   RooRealVar mean_fitted(("mean_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("mean_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),mean_CB.getVal());
//   RooRealVar sigma_fitted(("sigma_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sigma_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(), sigma_CB.getVal());
//   RooRealVar sigma_gauss_fitted(("sigma_gauss_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sigma_gauss_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),sigma_gauss.getVal() );
//   RooRealVar n1_fitted(("n1_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("n1_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),n1_CB.getVal() );
//   RooRealVar alpha1_fitted(("alpha1_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("alpha1_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),alpha1_CB.getVal()); 
//   RooRealVar sig_frac_fitted(("sig_frac_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sig_frac_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),sig_frac.getVal());
//   
//   RooRealVar mean_conv("mean_conv","mean_conv",mean_value_for_return_pdf);
//   
//   if(mean_value_for_return_pdf<0)
//   {
//     mean_conv.setVal( mean_CB.getVal());
//   }
//  
//   
//   RooCBShape CB_fitted("CB_fitted","CB_fitted",m_width,mean_conv,sigma_fitted,alpha1_fitted,n1_fitted);
//   RooGaussian gauss_fitted("gauss_fitted","gauss_fitted",m_width,mean_conv,sigma_gauss_fitted);
//   RooAddPdf* sum_fitted = new RooAddPdf("ssCB_gauss","ssCB_gauss",gauss_fitted,CB_fitted,sig_frac_fitted);
//   
//   return sum_fitted;
// }


//===========================================================================
//===== all hadronic channel -> fit shift for small masses ==================
//===========================================================================

RooFitResult* AllHadFitMeanShift(string modelName,string category,float mass, float width)
{
  string input_dir = "/usr/users/dschaefer/root/results/testFit/hadronic/ToWW/"+modelName+"/";
  if(modelName.find("Wprime")!=string::npos)
  {
    input_dir = "/usr/users/dschaefer/root/results/testFit/hadronic/ToWZ/"+modelName+"/";
  }
  string file_width = input_dir+modelName+"_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(width*10))+"_mWW_had_"+category+".root";
  std::cout << file_width <<std::endl;
  
  
  string directory = "/usr/users/dschaefer/root/results/misc/AllHadHistosForLimits/";
  
  TFile *f_width = new TFile(file_width.c_str(),"READ");
 
  
  TH1F* h_width = dynamic_cast<TH1F*>(f_width->Get("hmWW"));
  int tmp = h_width->GetSize()-2;
  
  double massMax_width = h_width->GetBinLowEdge(h_width->GetBin(tmp));
  double massMin_width = h_width->GetBinLowEdge(1);
  
  RooRealVar m_width("m_w","m_w",massMin_width,massMax_width);
  
  RooRealVar m_new = m_width;
  m_new.setBins(1000,"cache");
  
  //RooRealVar mean_conv("mean_conv","mean_conv",0);
  RooRealVar width_BW("width_BW","width_BW",width*mass);
  
  RooDataHist dh_width("dh_width","dh_width",m_width,RooFit::Import(*h_width));
  
 
  RooRealVar mean_new("mean","mean",mass,mass-100,mass+100);
  
  RooBWRunPdf BW("BW","BW",m_width,mean_new,width_BW);
  
    string file_narrow = "/usr/users/dschaefer/root/results/testFit/hadronic/ToWW/BulkGrav/BulkGrav_M"+std::to_string(int(mass))+"_width0p0_mWW_had_"+category+".root";
  TFile *f_narrow = new TFile(file_narrow.c_str(),"READ");
  TH1F* h_narrow = dynamic_cast<TH1F*>(f_narrow->Get("hmWW"));
  tmp = h_narrow->GetSize()-2;
  double massMax_narrow = h_narrow->GetBinLowEdge(h_narrow->GetBin(tmp));
  double massMin_narrow = h_narrow->GetBinLowEdge(1);
  RooRealVar m_narrow("m","m",massMin_narrow, massMax_narrow);
  
  float sCB = 50;
  float sCBMin = 40;
  float sCBMax = 230;
  float n1 =15.;
  float n1Max = 35.;
  float n1Min = 5.;
  float alpha1 = 1.5;
  float alpha1Min = 0.5;
  float alpha1Max = 5.;
  
  RooRealVar mean_CB("mean_CB","mean_CB",mass+90,mass-20,mass+100);
  RooRealVar sigma_CB(("sigma_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sigma_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),sCB,sCBMin,sCBMax);
  RooRealVar sigma_gauss(("sigma_gauss_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sigma_gauss_M"+std::to_string(int(mass))+"_had_"+category).c_str(),sCB,sCBMin,sCBMax);
  RooRealVar n1_CB(("n1_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("n1_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),n1,n1Min,n1Max);
  RooRealVar alpha1_CB(("alpha1_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("alpha1_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),alpha1,alpha1Min,alpha1Max); 
  RooRealVar sig_frac(("sig_frac_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sig_frac_M"+std::to_string(int(mass))+"_had_"+category).c_str(),0.5,0.0,1.0);
  
  RooCBShape ssCB("ssCB","ssCB",m_narrow,mean_CB,sigma_CB,alpha1_CB,n1_CB);
  RooGaussian gauss("gauss","gauss",m_narrow,mean_CB,sigma_gauss);
  //later: use sum pdf for all had signal modeling
  RooAddPdf sum_ssCB_gauss("ssCB_gauss","ssCB_gauss",gauss,ssCB,sig_frac);
  
  RooDataHist dh_narrow("dh_narrow","dh_narrow",m_narrow,RooFit::Import(*h_narrow));
  
  RooFitResult* fit_narrow = sum_ssCB_gauss.fitTo(dh_narrow,RooFit::Save());
  fit_narrow->Print();
  
  RooPlot* frame_narrow = m_narrow.frame();
  frame_narrow->GetXaxis()->SetTitle("m_{VV} [GeV]");
  frame_narrow->SetTitle("narrow fit with gauss + sCB");
  dh_narrow.plotOn(frame_narrow);
  sum_ssCB_gauss.plotOn(frame_narrow);
  TCanvas*c_narrow = new TCanvas("c_narrow","c_narrow",400,400);
  c_narrow->cd();
  frame_narrow->Draw();
  
  if(width<0.1)
  {
   return fit_narrow; 
  }
  
  std::cout << mean_CB.getVal()       <<std::endl;
  std::cout << sigma_CB.getVal()      <<std::endl;
  std::cout << sigma_gauss.getVal()   <<std::endl;
  std::cout << n1_CB.getVal()         <<std::endl;
  std::cout << alpha1_CB.getVal()     <<std::endl;
  std::cout << sig_frac.getVal()      <<std::endl; 
  
  RooRealVar mean_fitted(("mean_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("mean_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),mean_CB.getVal());
  RooRealVar sigma_fitted(("sigma_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sigma_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(), sigma_CB.getVal());
  RooRealVar sigma_gauss_fitted(("sigma_gauss_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sigma_gauss_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),sigma_gauss.getVal() );
  RooRealVar n1_fitted(("n1_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("n1_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),n1_CB.getVal() );
  RooRealVar alpha1_fitted(("alpha1_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("alpha1_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),alpha1_CB.getVal()); 
  RooRealVar sig_frac_fitted(("sig_frac_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sig_frac_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),sig_frac.getVal());
  
  RooRealVar mean_conv("mean_conv","mean_conv",0);
  RooCBShape CB_fitted("CB_fitted","CB_fitted",m_width,mean_conv,sigma_fitted,alpha1_fitted,n1_fitted);
  RooGaussian gauss_fitted("gauss_fitted","gauss_fitted",m_width,mean_conv,sigma_gauss_fitted);
  RooAddPdf* sum_fitted = new RooAddPdf("ssCB_gauss","ssCB_gauss",gauss_fitted,CB_fitted,sig_frac_fitted);
  
  
  //RooAddPdf* sum_fitted = narrow_model_allHad_fitted(category,mass,0,m_new);
  
  RooFFTConvPdf* sig_model  = new  RooFFTConvPdf(("sig_model_w0p"+std::to_string(int(width*10))+"_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sig_model_w0p"+std::to_string(int(width*10))+"_M"+std::to_string(int(mass))+"_had_"+category).c_str(),m_new,BW,*sum_fitted);
  sig_model->setBufferFraction(5.0);
  RooFitResult* fit_width = sig_model->fitTo(dh_width,RooFit::Save());
  
  RooPlot* frame_width = m_width.frame();
  frame_width->GetXaxis()->SetTitle("m_{VV} [GeV]");
  frame_width->SetTitle("BW #otimes CB+gauss, mean shifted");
  dh_width.plotOn(frame_width);
  sig_model->plotOn(frame_width);
  //BW.plotOn(frame_width,RooFit::LineColor(kRed));
  
  
  TCanvas* c_width = new TCanvas("c_width","c_width",400,400);
  c_width->cd();
  frame_width->Draw();
  c_width->SaveAs((directory+modelName+"_fit_WW_jjjj_M"+std::to_string(int(mass))+"_w0p"+std::to_string(int(10*width))+".pdf").c_str());
  
  
 return fit_width;
}

//===========================================================================
//===== all hadronic channel -> extra DoF for high  masses ==================
//===========================================================================

RooFitResult* AllHadFitDoF(string modelName,string category,float mass, float width)
{
  
  string input_dir = "/usr/users/dschaefer/root/results/testFit/hadronic/ToWW/"+modelName+"/";
  if(modelName.find("Wprime")!=string::npos)
  {
    input_dir = "/usr/users/dschaefer/root/results/testFit/hadronic/ToWZ/"+modelName+"/";
  }
  string directory = "/usr/users/dschaefer/root/results/misc/AllHadHistosForLimits/";
  string file_width = input_dir+modelName+"_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(width*10))+"_mWW_had_"+category+".root";
  TFile *f_width = new TFile(file_width.c_str(),"READ");
 
  
  TH1F* h_width = dynamic_cast<TH1F*>(f_width->Get("hmWW"));
  int tmp = h_width->GetSize()-2;
  
  double massMax_width = h_width->GetBinLowEdge(h_width->GetBin(tmp));
  double massMin_width = h_width->GetBinLowEdge(1);
  
  RooRealVar m_width("m_w","m_w",massMin_width,massMax_width);
  
  string file_narrow = "/usr/users/dschaefer/root/results/testFit/hadronic/ToWW/BulkGrav/BulkGrav_M"+std::to_string(int(mass))+"_width0p0_mWW_had_"+category+".root";
  TFile *f_narrow = new TFile(file_narrow.c_str(),"READ");
  TH1F* h_narrow = dynamic_cast<TH1F*>(f_narrow->Get("hmWW"));
  tmp = h_narrow->GetSize()-2;
  double massMax_narrow = h_narrow->GetBinLowEdge(h_narrow->GetBin(tmp));
  double massMin_narrow = h_narrow->GetBinLowEdge(1);
  RooRealVar m_narrow("m","m",massMin_narrow, massMax_narrow);
  
  float sCB = 50;
  float sCBMin = 40;
  float sCBMax = 230;
  float n1 =15.;
  float n1Max = 35.;
  float n1Min = 5.;
  float alpha1 = 1.5;
  float alpha1Min = 0.5;
  float alpha1Max = 5.;
  
  RooRealVar mean_CB(("mean_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("mean_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),mass+90,mass-20,mass+100);
  RooRealVar sigma_CB(("sigma_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sigma_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),sCB,sCBMin,sCBMax);
  RooRealVar sigma_gauss(("sigma_gauss_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sigma_gauss_M"+std::to_string(int(mass))+"_had_"+category).c_str(),sCB,sCBMin,sCBMax);
  RooRealVar n1_CB(("n1_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("n1_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),n1,n1Min,n1Max);
  RooRealVar alpha1_CB(("alpha1_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("alpha1_CB_M"+std::to_string(int(mass))+"_had_"+category).c_str(),alpha1,alpha1Min,alpha1Max); 
  RooRealVar sig_frac(("sig_frac_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sig_frac_M"+std::to_string(int(mass))+"_had_"+category).c_str(),0.5,0.0,1.0);
  
  RooCBShape ssCB("ssCB","ssCB",m_narrow,mean_CB,sigma_CB,alpha1_CB,n1_CB);
  RooGaussian gauss("gauss","gauss",m_narrow,mean_CB,sigma_gauss);
  //later: use sum pdf for all had signal modeling
  RooAddPdf sum_ssCB_gauss("ssCB_gauss","ssCB_gauss",gauss,ssCB,sig_frac);
  
  RooDataHist dh_narrow("dh_narrow","dh_narrow",m_narrow,RooFit::Import(*h_narrow));
  
  RooFitResult* fit_narrow = sum_ssCB_gauss.fitTo(dh_narrow,RooFit::Save());
  fit_narrow->Print();
  
  RooPlot* frame_narrow = m_narrow.frame();
  frame_narrow->GetXaxis()->SetTitle("m_{VV} [GeV]");
  frame_narrow->SetTitle("narrow fit with gauss + sCB");
  dh_narrow.plotOn(frame_narrow);
  sum_ssCB_gauss.plotOn(frame_narrow);
  TCanvas*c_narrow = new TCanvas("c_narrow","c_narrow",400,400);
  c_narrow->cd();
  frame_narrow->Draw();
  
  std::cout << mean_CB.getVal()       <<std::endl;
  std::cout << sigma_CB.getVal()      <<std::endl;
  std::cout << sigma_gauss.getVal()   <<std::endl;
  std::cout << n1_CB.getVal()         <<std::endl;
  std::cout << alpha1_CB.getVal()     <<std::endl;
  std::cout << sig_frac.getVal()      <<std::endl; 
  
  RooRealVar mean_fitted(("mean_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("mean_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),mean_CB.getVal());
  RooRealVar sigma_fitted(("sigma_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sigma_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(), sigma_CB.getVal());
  RooRealVar sigma_gauss_fitted(("sigma_gauss_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sigma_gauss_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),sigma_gauss.getVal() );
  RooRealVar n1_fitted(("n1_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("n1_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),n1_CB.getVal() );
  RooRealVar alpha1_fitted(("alpha1_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("alpha1_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),alpha1_CB.getVal()); 
  RooRealVar sig_frac_fitted(("sig_frac_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sig_frac_fitted_M"+std::to_string(int(mass))+"_had_"+category).c_str(),sig_frac.getVal());
  
  RooRealVar mean_conv("mean_conv","mean_conv",0);
  
  
  // wide extension
  
  RooRealVar m_new = m_width;
  m_new.setBins(3000,"cache");
  
  RooCBShape CB_fitted("CB_fitted","CB_fitted",m_new,mean_conv,sigma_fitted,alpha1_fitted,n1_fitted);
  RooGaussian gauss_fitted("gauss_fitted","gauss_fitted",m_new,mean_conv,sigma_gauss_fitted);
  RooAddPdf* sum_fitted = new RooAddPdf("ssCB_gauss","ssCB_gauss",gauss_fitted,CB_fitted,sig_frac_fitted);
  
  //RooRealVar mean_conv("mean_conv","mean_conv",0);
  RooRealVar width_BW("width_BW","width_BW",width*mass);
  
  RooDataHist dh_width("dh_width","dh_width",m_width,RooFit::Import(*h_width));
  
  RooBWRunPdf BW("BW","BW",m_new,mean_fitted,width_BW);
  RooRealVar a0("a0","a0",0,-20,20);
  RooChebychev p1("p1","p1",m_new,RooArgList(a0));
  
  
  RooFFTConvPdf* model_pdf  = new  RooFFTConvPdf("model_pdf","model_pdf",m_new,BW,*sum_fitted);
  model_pdf->setBufferFraction(7.0);
  model_pdf->setBufferStrategy(RooFFTConvPdf::Extend);
  RooProdPdf * sig_model  = new RooProdPdf(("sig_model_w0p"+std::to_string(int(width*10))+"_M"+std::to_string(int(mass))+"_had_"+category).c_str(),("sig_model_w0p"+std::to_string(int(width*10))+"_M"+std::to_string(int(mass))+"_had_"+category).c_str(),*model_pdf,p1);
  
  RooFitResult* fit_width = sig_model->fitTo(dh_width,RooFit::Save());
  
  RooPlot* frame_width = m_width.frame();
  frame_width->GetXaxis()->SetTitle("m_{VV} [GeV]");
  frame_width->SetTitle("(BW #otimes CB+gauss) *p1");
  dh_width.plotOn(frame_width);
  sig_model->plotOn(frame_width);
  model_pdf->plotOn(frame_width,RooFit::LineColor(kRed));
  BW.plotOn(frame_width,RooFit::LineColor(kGreen));
  
  
  TCanvas* c_width = new TCanvas("c_width","c_width",400,400);
  c_width->cd();
  frame_width->Draw();
  c_width->SaveAs((directory+modelName+"_DoF_WW_jjjj_M"+std::to_string(int(mass))+"_w0p"+std::to_string(int(10*width))+".pdf").c_str());
  
  return fit_width;
}


