#include "TGraphAsymmErrors.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
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

void lab()
{
  float time[14] = {0,2,4,6,8,10,15,20,25,30,35,40,45,50};
  float temperatureT1[14] = {17.5,14.9,14.0,13.5,12.9,12.8,11.9,10.8,11.0,10.3,10.3,11.5,12.4,13.3};
  float temperatureT2[14] = {18.6,19.5,20.3,20.6,20.4,20.8,19.7,18.8,19.8,17.4,18.5,20.5,21.4,22.5};
  
  float time2[7] = {0,2,3,4,5,6,43};
  float temperature2T1[7] = {16,17.1,17.7,18.3,18.8,19.2,22.6};
  float temperature2T2[7] = {22.2,22.3,22.3,23.3,22.3,22.5,23.2};
  
  
 TGraph* t1 = new TGraph(14,time,temperatureT1); 
 TGraph* t2 = new TGraph(14,time,temperatureT2);
 
 TCanvas* c1 = new TCanvas("c1","c1",400,400);
 t2->SetMaximum(23);
 t2->SetMinimum(0);
 t2->GetXaxis()->SetTitle("t [min]");
 t2->GetYaxis()->SetTitle("temperature [#circ C]");
 t2->SetTitle("a temperature measurement");
 t2->SetLineColor(kBlue);
 t2->SetLineWidth(3);
 t2->SetMarkerStyle(4);
 t1->SetLineColor(kRed);
 t1->SetLineWidth(3);
 t1->SetMarkerStyle(3);
 t2->Draw("ALP");
 t1->Draw("LPsame");
  TLegend* leg = new TLegend(0.53,0.3,0.25,0.2);
  leg->SetFillColor(kWhite);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.04);
  leg->SetBorderSize(0);
  
  leg->AddEntry(t2,"temperature T2","L");
  leg->AddEntry(t1,"temperature T1","L");
  leg->Draw("same");
  c1->SaveAs("Tmeasurement1.pdf");
  
  
  t1 = new TGraph(7,time2,temperature2T1); 
  t2 = new TGraph(7,time2,temperature2T2);
 
 TCanvas* c2 = new TCanvas("c1","c1",400,400);
 t2->SetMaximum(25);
 t2->SetMinimum(0);
 t2->GetXaxis()->SetTitle("t [min]");
 t2->GetYaxis()->SetTitle("temperature [#circ C]");
 t2->SetTitle("a temperature measurement");
 t2->SetLineColor(kBlue);
 t2->SetLineWidth(3);
 t2->SetMarkerStyle(4);
 t1->SetLineColor(kRed);
 t1->SetLineWidth(3);
 t1->SetMarkerStyle(3);
 t2->Draw("ALP");
 t1->Draw("LPsame");
  leg = new TLegend(0.53,0.3,0.25,0.2);
  leg->SetFillColor(kWhite);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.04);
  leg->SetBorderSize(0);
  
  leg->AddEntry(t2,"temperature T2","L");
  leg->AddEntry(t1,"temperature T1","L");
  leg->Draw("same");
  c2->SaveAs("Tmeasurement2.pdf");
  
}