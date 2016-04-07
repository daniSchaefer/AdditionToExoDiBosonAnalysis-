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

void makeShapeComparisonPlots()
{
  
  string channel = "el";
  string category = "HP";
  TLatex text;
  text.SetTextFont(43);
  text.SetTextSize(12);
  string preliminary = "preliminary simulation";
  string centerOfmass ="#sqrt{s} = 13 TeV";


  
  TCanvas* canvas = new TCanvas("canvas","canvas",400,400);
  canvas->cd();
  gPad->SetLeftMargin(0.16);
  RooRealVar x("x","x",600,4500);
  RooPlot* frame1 = x.frame();
  
  getShapeFromInterpolation("narrow",channel,category,800,0.0,x,frame1,0);
  getShapeFromInterpolation("narrow",channel,category,1000,0.0,x,frame1,1);
  getShapeFromInterpolation("narrow",channel,category,1200,0.0,x,frame1,2);
  getShapeFromInterpolation("narrow",channel,category,1500,0.0,x,frame1,3);
  getShapeFromInterpolation("narrow",channel,category,1900,0.0,x,frame1,4);
  getShapeFromInterpolation("narrow",channel,category,2300,0.0,x,frame1,-4);
  getShapeFromInterpolation("narrow",channel,category,2800,0.0,x,frame1,-3);
  getShapeFromInterpolation("narrow",channel,category,3200,0.0,x,frame1,-2);
  getShapeFromInterpolation("narrow",channel,category,4000,0.0,x,frame1,-1);
  frame1->SetTitle("");
  frame1->GetYaxis()->SetTitle("");
  frame1->SetMaximum(0.32);
  frame1->GetXaxis()->SetTitle("m_{WW} [GeV]");
  frame1->GetYaxis()->SetTitleOffset(2.0);
  frame1->Draw();
  string name1 = frame1->nameOf(0);
  string name2 = frame1->nameOf(1);
  string name3 = frame1->nameOf(2);
  string name4 = frame1->nameOf(3);
  string name5 = frame1->nameOf(4);
  string name6 = frame1->nameOf(5);
  string name7 = frame1->nameOf(6);
  string name8 = frame1->nameOf(7);
  text.DrawLatex(800, 0.3,preliminary.c_str());
  text.DrawLatex(3500, 0.3,centerOfmass.c_str());
  TLegend* leg = new TLegend(0.48,0.8,0.86,0.6);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->AddEntry(frame1->findObject(name1.c_str()),"M_{X} = 800 GeV","l");
  leg->AddEntry(frame1->findObject(name2.c_str()),"M_{X} = 1000 GeV","l");
  leg->AddEntry(frame1->findObject(name3.c_str()),"M_{X} = 1200 GeV","l");
  leg->AddEntry(frame1->findObject(name4.c_str()),"M_{X} = 1900 GeV","l");
  leg->AddEntry(frame1->findObject(name5.c_str()),"M_{X} = 2300 GeV","l");
  leg->AddEntry(frame1->findObject(name6.c_str()),"M_{X} = 2800 GeV","l");
  leg->AddEntry(frame1->findObject(name7.c_str()),"M_{X} = 3200 GeV","l");
  leg->AddEntry(frame1->findObject(name8.c_str()),"M_{X} = 4000 GeV","l");
  leg->Draw();
  canvas->Update();
  
  
  
  TCanvas* canvas1 = new TCanvas("canvas1","canvas1",400,400);
  canvas1->cd();
  gPad->SetLeftMargin(0.16);
  RooPlot* frame2 = x.frame();
  
  getShapeFromInterpolation("wide",channel,category,800, 0.21,x,frame2,0);
  getShapeFromInterpolation("wide",channel,category,1000,0.21,x,frame2,1);
  getShapeFromInterpolation("wide",channel,category,1200,0.21,x,frame2,2);
  getShapeFromInterpolation("wide",channel,category,1500,0.21,x,frame2,3);
  getShapeFromInterpolation("wide",channel,category,1900,0.21,x,frame2,4);
  getShapeFromInterpolation("wide",channel,category,2300,0.21,x,frame2,-4);
  getShapeFromInterpolation("wide",channel,category,2800,0.21,x,frame2,-3);
  getShapeFromInterpolation("wide",channel,category,3200,0.21,x,frame2,-2);
  getShapeFromInterpolation("wide",channel,category,3999,0.21,x,frame2,-1);
  frame2->SetTitle("");
  frame2->GetYaxis()->SetTitle("arbitrary scale");
  frame2->GetXaxis()->SetTitle("m_{WW} [GeV]");
  frame2->GetYaxis()->SetTitleOffset(2.0);
  frame2->Draw();
  frame2->SetMaximum(0.14);
  name1 = frame2->nameOf(0);
  name2 = frame2->nameOf(1);
  name3 = frame2->nameOf(2);
  name4 = frame2->nameOf(3);
  name5 = frame2->nameOf(4);
  name6 = frame2->nameOf(5);
  name7 = frame2->nameOf(6);
  name8 = frame2->nameOf(7);
  text.DrawLatex(800, 0.13,preliminary.c_str());
  text.DrawLatex(3500, 0.13,centerOfmass.c_str());
  TLegend* leg1 = new TLegend(0.48,0.8,0.86,0.6);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->AddEntry(frame2->findObject(name1.c_str()),"M_{X} = 800  GeV, width = 0.21","l");
  leg1->AddEntry(frame2->findObject(name2.c_str()),"M_{X} = 1000 GeV, width = 0.21","l");
  leg1->AddEntry(frame2->findObject(name3.c_str()),"M_{X} = 1200 GeV, width = 0.21","l");
  leg1->AddEntry(frame2->findObject(name4.c_str()),"M_{X} = 1900 GeV, width = 0.21","l");
  leg1->AddEntry(frame2->findObject(name5.c_str()),"M_{X} = 2300 GeV, width = 0.21","l");
  leg1->AddEntry(frame2->findObject(name6.c_str()),"M_{X} = 2800 GeV, width = 0.21","l");
  leg1->AddEntry(frame2->findObject(name7.c_str()),"M_{X} = 3200 GeV, width = 0.21","l");
  leg1->AddEntry(frame2->findObject(name8.c_str()),"M_{X} = 4000 GeV, width = 0.21","l");
  leg1->Draw();
  canvas1->Update();
  
 TCanvas* canvas3 = new TCanvas("canvas3","canvas3",400,400);
 canvas3->cd(); 
 gPad->SetLeftMargin(0.16); 
 RooPlot* frame3 = x.frame(); 
  
 getShapeFromInterpolation("narrow",channel,category,2200, 0.0,x,frame3,0); 
 getShapeFromInterpolation("wide",channel,category,2200,0.05,x,frame3,1); 
 getShapeFromInterpolation("wide",channel,category,2200,0.1,x,frame3,2); 
 getShapeFromInterpolation("wide",channel,category,2200,0.15,x,frame3,3); 
 getShapeFromInterpolation("wide",channel,category,2200,0.2,x,frame3,4); 
 getShapeFromInterpolation("wide",channel,category,2200,0.25,x,frame3,-4); 
 getShapeFromInterpolation("wide",channel,category,2200,0.3,x,frame3,-3); 
 getShapeFromInterpolation("wide",channel,category,2200,0.35,x,frame3,-2); 

 frame3->SetTitle(""); 
 frame3->GetYaxis()->SetTitle("arbitrary scale"); 
 frame3->GetXaxis()->SetTitle("m_{WW} [GeV]"); 
 frame3->GetYaxis()->SetTitleOffset(2.0); 
 frame3->Draw();
 name1 = frame3->nameOf(0);
 name2 = frame3->nameOf(1);
 name3 = frame3->nameOf(2);
 name4 = frame3->nameOf(3);
 name5 = frame3->nameOf(4);
 name6 = frame3->nameOf(5);
 name7 = frame3->nameOf(6);
 name8 = frame3->nameOf(7);
 
 frame3->SetMaximum(0.15);
 text.DrawLatex(800, 0.14,preliminary.c_str()); 
 text.DrawLatex(3500, 0.14,centerOfmass.c_str()); 
 TLegend* leg2 = new TLegend(0.5,0.8,0.86,0.6);
 leg2->SetFillColor(0);
 leg2->SetBorderSize(0);
 leg2->AddEntry(frame3->findObject(name1.c_str()),"M_{X} = 2200 GeV, width = 0.0","l");
 leg2->AddEntry(frame3->findObject(name2.c_str()),"M_{X} = 2200 GeV, width = 0.05","l");
 leg2->AddEntry(frame3->findObject(name3.c_str()),"M_{X} = 2200 GeV, width = 0.1","l");
 leg2->AddEntry(frame3->findObject(name4.c_str()),"M_{X} = 2200 GeV, width = 0.15","l");
 leg2->AddEntry(frame3->findObject(name5.c_str()),"M_{X} = 2200 GeV, width = 0.2","l");
 leg2->AddEntry(frame3->findObject(name6.c_str()),"M_{X} = 2200 GeV, width = 0.25","l");
 leg2->AddEntry(frame3->findObject(name7.c_str()),"M_{X} = 2200 GeV, width = 0.3","l");
leg2->Draw();
 canvas3->Update();
 
 TCanvas* canvas4 = new TCanvas("canvas4","canvas4",400,400);
 canvas4->cd(); 
 gPad->SetLeftMargin(0.16);
 RooRealVar x_new("x_new","x_new",2000,6000); 
 RooPlot* frame4 = x_new.frame();
 getShapeFromInterpolation("narrow",channel,category,4000, 0.0,x_new,frame4,0);
 getShapeFromInterpolation("wide",channel,category,4000,0.05,x_new,frame4,1); 
 getShapeFromInterpolation("wide",channel,category,4000,0.1,x_new, frame4,2); 
 getShapeFromInterpolation("wide",channel,category,4000,0.15,x_new,frame4,3); 
 getShapeFromInterpolation("wide",channel,category,4000,0.2,x_new, frame4,4); 
 getShapeFromInterpolation("wide",channel,category,4000,0.25,x_new,frame4,-4); 
 getShapeFromInterpolation("wide",channel,category,4000,0.3,x_new, frame4,-3); 
 getShapeFromInterpolation("wide",channel,category,4000,0.35,x_new,frame4,-2); 
 getShapeFromInterpolation("wide",channel,category,4000,0.35,x_new,frame4,-2); 
 frame4->SetTitle(""); 
 frame4->GetYaxis()->SetTitle("arbitrary scale"); 
 frame4->GetXaxis()->SetTitle("m_{WW} [GeV]"); 
 frame4->GetYaxis()->SetTitleOffset(2.0); 
  frame4->SetMaximum(0.14);
 frame4->Draw();
 name1 = frame4->nameOf(0);
 name2 = frame4->nameOf(1);
 name3 = frame4->nameOf(2);
 name4 = frame4->nameOf(3);
 name5 = frame4->nameOf(4);
 name6 = frame4->nameOf(5);
 name7 = frame4->nameOf(6);
 name8 = frame4->nameOf(7);
 text.DrawLatex(2050, 0.13,preliminary.c_str()); 
 text.DrawLatex(5000, 0.13,centerOfmass.c_str()); 
 TLegend* leg3 = new TLegend(0.6,0.8,0.9,0.6);
 leg3->SetFillColor(0);
 leg3->SetBorderSize(0);
 leg3->AddEntry(frame4->findObject(name1.c_str()),"M_{X} = 4000 GeV, width = 0.0","l");
 leg3->AddEntry(frame4->findObject(name2.c_str()),"M_{X} = 4000 GeV, width = 0.05","l");
 leg3->AddEntry(frame4->findObject(name3.c_str()),"M_{X} = 4000 GeV, width = 0.1","l");
 leg3->AddEntry(frame4->findObject(name4.c_str()),"M_{X} = 4000 GeV, width = 0.15","l");
 leg3->AddEntry(frame4->findObject(name5.c_str()),"M_{X} = 4000 GeV, width = 0.2","l");
 leg3->AddEntry(frame4->findObject(name6.c_str()),"M_{X} = 4000 GeV, width = 0.25","l");
 leg3->AddEntry(frame4->findObject(name7.c_str()),"M_{X} = 4000 GeV, width = 0.3","l");
 leg3->AddEntry(frame4->findObject(name8.c_str()),"M_{X} = 4000 GeV, width = 0.35","l");
 leg3->Draw();
 
 string SaveAs =  "/usr/users/dschaefer/root/results/testFit/shapeComparisonPlot_width0p0_"+channel+"_"+category+".pdf";
 canvas->SaveAs(SaveAs.c_str());
 SaveAs = "/usr/users/dschaefer/root/results/testFit/shapeComparisonPlot_width0p21"+channel+"_"+category+".pdf";
 canvas1->SaveAs(SaveAs.c_str());
 SaveAs = "/usr/users/dschaefer/root/results/testFit/shapeComparisonPlot_M2200"+channel+"_"+category+".pdf";
 canvas3->SaveAs(SaveAs.c_str());
 SaveAs = "/usr/users/dschaefer/root/results/testFit/shapeComparisonPlot_M4000"+channel+"_"+category+".pdf";
 canvas4->SaveAs(SaveAs.c_str());
 
 //========================================================================================
 //============= compare my interpolations (extra DoF) with samples =======================
 //========================================================================================
 string modelName[4]= {"Wprime","Zprime","RSGrav","Radion"};
 float mass =4000;
 float gamma = 0.3;
 TCanvas* c_DoF = new TCanvas("c_DoF","c_DoF",800,800);
 c_DoF->Divide(2,2);
 TFile* f = new TFile();
 TH1F* h[4];
 double *massMax_width=new double[4];
 double *massMin_width=new double[4];
 string canvasName = "/usr/users/dschaefer/root/results/testFit/semileptonic/ToWW/DoF_Interpolation_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(gamma*10))+"_"+channel+"_"+category+".pdf";
 
 
 for(int i=0;i<4;i++)
 {
 string sfile_width ="/usr/users/dschaefer/root/results/"+modelName[i]+"/"+modelName[i]+"_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(gamma*10))+"_mWW_"+channel+"_"+category+".root";
 TFile *tmp = f->Open(sfile_width.c_str(),"READ");
 h[i]= (TH1F*) tmp->Get("hmWW");
 int tmp2 = h[i]->GetSize()-2;
 massMax_width[i] = h[i]->GetBinLowEdge(h[i]->GetBin(tmp2));
 massMin_width[i] = h[i]->GetBinLowEdge(1);
 
 }
 RooRealVar m0("m0","m_{VV} [GeV]",massMin_width[0],massMax_width[0]);
 RooRealVar m1("m1","m_{VV} [GeV]",massMin_width[1],massMax_width[1]);
 RooRealVar m2("m2","m_{VV} [GeV]",massMin_width[2],massMax_width[2]);
 RooRealVar m3("m3","m_{VV} [GeV]",massMin_width[3],massMax_width[3]);
 
 RooDataHist d0("d0","d0",m0,RooFit::Import(*h[0]));
 RooDataHist d1("d1","d1",m1,RooFit::Import(*h[1]));
 RooDataHist d2("d2","d2",m2,RooFit::Import(*h[2]));
 RooDataHist d3("d3","d3",m3,RooFit::Import(*h[3]));
 
 RooPlot* f0 = m0.frame();
 RooPlot* f1 = m1.frame();
 RooPlot* f2 = m2.frame();
 RooPlot* f3 = m3.frame();
 
 d0.plotOn(f0);
 d1.plotOn(f1);
 d2.plotOn(f2);
 d3.plotOn(f3);
 
 getShapeFromInterpolation("wide",channel,category,mass,gamma,m0,f0,0);
 getShapeFromInterpolation("wide",channel,category,mass,gamma,m1,f1,0);
 getShapeFromInterpolation("wide",channel,category,mass,gamma,m2,f2,0);
 getShapeFromInterpolation("wide",channel,category,mass,gamma,m3,f3,0);
 
 f0->SetTitle(modelName[0].c_str());
 f1->SetTitle(modelName[1].c_str());
 f2->SetTitle(modelName[2].c_str());
 f3->SetTitle(modelName[3].c_str());
 
 
 c_DoF->cd(1);
 f0->Draw();
 c_DoF->cd(2);
 f1->Draw();
 c_DoF->cd(3);
 f2->Draw();
 c_DoF->cd(4);
 f3->Draw();
 
  c_DoF->SaveAs(canvasName.c_str());
 //========================================================================================
 //============= compare my interpolations with jennifers =================================
 //========================================================================================
 
 TCanvas* c_debug = new TCanvas("c_debug","c_debug",800,800);
 c_debug->Divide(2,2);
 string cat = "HPW";
 
 RooRealVar x_debug("x_debug","x_debug",1800,2800);
 RooPlot* frame_debug = x_debug.frame();
 getShapeFromInterpolation("narrow",channel,(cat+"_my"),2300,0.0,x_debug,frame_debug,0);
 getShapeFromInterpolation("narrow",channel,cat ,2300,0.0,x_debug,frame_debug,4);
 //getShapeFromInterpolation("narrow",channel,"HPW_debug",2300,0.0,x_debug,frame_debug,1,"kGreen");
 frame_debug->SetTitle(""); 
 frame_debug->GetYaxis()->SetTitle("arbitrary scale"); 
 frame_debug->GetXaxis()->SetTitle("m_{WW} [GeV]"); 
 frame_debug->GetYaxis()->SetTitleOffset(2.0); 
 c_debug->cd(1);
 frame_debug->Draw();
 RooRealVar x_debug1("x_debug1","x_debug1",500,1600);
 RooPlot* frame_debug1 = x_debug1.frame();
 getShapeFromInterpolation("narrow",channel,(cat+"_my"),1000,0.0,x_debug1,frame_debug1,0);
 getShapeFromInterpolation("narrow",channel,cat,1000,0.0,x_debug1,frame_debug1,4);
 //getShapeFromInterpolation("narrow",channel,"HPW_debug",1100,0.0,x_debug1,frame_debug1,1,"kGreen");
 frame_debug1->SetTitle(""); 
 frame_debug1->GetYaxis()->SetTitle("arbitrary scale"); 
 frame_debug1->GetXaxis()->SetTitle("m_{WW} [GeV]"); 
 frame_debug1->GetYaxis()->SetTitleOffset(2.0); 
 c_debug->cd(2);
 frame_debug1->Draw();
 RooRealVar x_debug2("x_debug2","x_debug2",2600,4000);
 RooPlot* frame_debug2 = x_debug2.frame();
 getShapeFromInterpolation("narrow",channel,(cat+"_my"),3400,0.0,x_debug2,frame_debug2,0);
 getShapeFromInterpolation("narrow",channel,cat,3400,0.0,x_debug2,frame_debug2,4);
 //getShapeFromInterpolation("narrow",channel,"HPW_debug",3400,0.0,x_debug2,frame_debug2,0,"kGreen");
 frame_debug2->SetTitle(""); 
 frame_debug2->GetYaxis()->SetTitle("arbitrary scale"); 
 frame_debug2->GetXaxis()->SetTitle("m_{WW} [GeV]"); 
 frame_debug2->GetYaxis()->SetTitleOffset(2.0); 
 c_debug->cd(3);
 frame_debug2->Draw();
 
 RooRealVar x_debug3("x_debug3","x_debug3",1500,2600);
 RooPlot* frame_debug3 = x_debug3.frame();
 getShapeFromInterpolation("narrow",channel,(cat+"_my"),2000,0.0,x_debug3,frame_debug3,0);
 getShapeFromInterpolation("narrow",channel,cat,2000,0.0,x_debug3,frame_debug3,4);
 //getShapeFromInterpolation("narrow",channel,"HPW_debug",2000,0.0,x_debug3,frame_debug3,0,"kGreen");
 frame_debug3->SetTitle(""); 
 frame_debug3->GetYaxis()->SetTitle("arbitrary scale"); 
 frame_debug3->GetXaxis()->SetTitle("m_{WW} [GeV]"); 
 frame_debug3->GetYaxis()->SetTitleOffset(2.0); 
 c_debug->cd(4);
 frame_debug3->Draw();
 
  
}