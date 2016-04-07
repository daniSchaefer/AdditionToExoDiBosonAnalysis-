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

void goodHypRange()
{
 string output_directory =  "/usr/users/dschaefer/root/results/testFit/semileptonic/ToWW/";
  
  
 TCanvas *c1 = new TCanvas();
 gPad->SetLeftMargin(0.15);
 double x[15] ={800,800,800,1200,1200,1200,2000,2000,2000,3000,3000,3000, 4000,4000,4000};
 double y[15] ={0.1*800,0.2*800,0.3*800,0.1*1200,0.2*1200,0.3*1200,0.1*2000,0.2*2000,0.3*2000,0.1*3000,0.2*3000,0.3*3000,0.1*4000,0.2*4000,0.3*4000};
 TGraph* g = new TGraph(15,x,y);
 g->GetXaxis()->SetTitle("m_{VV} [GeV]");
 g->GetYaxis()->SetTitleOffset(1.80);
 g->GetYaxis()->SetTitle("#Gamma [GeV]");
 g->SetTitle("good fit for DCB*BW");
  g->Draw("A*");
  TMarker* m1 = new TMarker(4000,4000*0.3,20);
  m1->SetMarkerColor(4);
  m1->Draw("Same");
  TMarker* m2 = new TMarker(1200,1200*0.3,20);
  m2->SetMarkerColor(4);
  m2->Draw("Same");
  c1->Update();
  
 // c1->SaveAs((output_directory+"pointsWithGoodFitRecSample.pdf").c_str());
  
  TCanvas *c2 = new TCanvas();
  gPad->SetLeftMargin(0.15);
  g->SetTitle("good fit for BW on gen. MC without selections");
  g->Draw("A*");
  TMarker* m12 = new TMarker(4000,4000*0.3,20);
  TMarker* m22 = new TMarker(4000,4000*0.2,20);
  TMarker* m32 = new TMarker(4000,4000*0.1,20);
 m12->SetMarkerColor(2);
 m22->SetMarkerColor(2);
 m32->SetMarkerColor(2);
 m12->Draw("Same");
 m22->Draw("Same");
 m32->Draw("Same");
  
 c2->Update();
 //c2->SaveAs((output_directory+"pointsWithGoodFitGenSample_withoutSelections.pdf").c_str());
 
}
