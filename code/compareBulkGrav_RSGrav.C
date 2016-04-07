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
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"


using namespace std;

namespace{
  int loadMyLibraryTriggerFunc(){
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/General.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

const char* input_filename1 = "/usr/users/dschaefer/root/results/Efficiency/histos/BulkGravToWKinematicsEl.root";
const char* input_filename2 = "/usr/users/dschaefer/root/results/Efficiency/histos/BulkGravToWKinematicsMu.root";
const char* input_filename3 = "/usr/users/dschaefer/root/results/Efficiency/histos/RSGravToWKinematicsEl.root";
const char* input_filename4 = "/usr/users/dschaefer/root/results/Efficiency/histos/RSGravToWKinematicsMu.root";
TFile * BulkGravEl = new TFile(input_filename1,"READ");
TFile * BulkGravMu = new TFile(input_filename2,"READ");
TFile * RSGravEl = new TFile(input_filename3,"READ");
TFile * RSGravMu = new TFile(input_filename4,"READ");


void compareBulkGrav_RSGrav()
{

 TH2F* hBulkGMu_rec 		= (TH2F*) BulkGravMu->Get("hW_lep_rec");
 TH2F* hBulkGMu_gen		= (TH2F*) BulkGravMu->Get("hW_lep_genWithVeto");
 TH2F* hBulkG_had_rec		= (TH2F*) BulkGravMu->Get("hW_had_rec");
 TH2F* hBulkG_had_gen		= (TH2F*) BulkGravMu->Get("hW_had_genWithVeto");
 TH2F* hBulkGEl_rec 		= (TH2F*) BulkGravEl->Get("hW_lep_rec");
 TH2F* hBulkGEl_gen 		= (TH2F*) BulkGravEl->Get("hW_lep_genWithVeto");
 TH2F* hBulkG_had_rec_El	= (TH2F*) BulkGravEl->Get("hW_had_rec");
 TH2F* hBulkG_had_gen_El	= (TH2F*) BulkGravEl->Get("hW_had_genWithVeto");
 
 
 hBulkG_had_gen->Add(hBulkG_had_gen_El);
 hBulkG_had_rec->Add(hBulkG_had_rec_El);
 
 TH2F* hRSGMu_rec 	= (TH2F*) RSGravMu->Get("hW_lep_rec");
 TH2F* hRSGMu_gen	= (TH2F*) RSGravMu->Get("hW_lep_genWithVeto");
 TH2F* hRSG_had_rec	= (TH2F*) RSGravMu->Get("hW_had_rec");
 TH2F* hRSG_had_gen	= (TH2F*) RSGravMu->Get("hW_had_genWithVeto");
 TH2F* hRSGEl_rec 	= (TH2F*) RSGravEl->Get("hW_lep_rec");
 TH2F* hRSGEl_gen 	= (TH2F*) RSGravEl->Get("hW_lep_genWithVeto");
 TH2F* hRSG_had_rec_El	= (TH2F*) RSGravEl->Get("hW_had_rec");
 TH2F* hRSG_had_gen_El	= (TH2F*) RSGravEl->Get("hW_had_genWithVeto");
 
 
 hRSG_had_gen->Add(hRSG_had_gen_El);
 hRSG_had_rec->Add(hRSG_had_rec_El);
 
 hBulkGMu_rec->Sumw2(kTRUE);
 hBulkGMu_gen->Sumw2(kTRUE);
 hBulkG_had_rec->Sumw2(kTRUE);
 hBulkG_had_gen->Sumw2(kTRUE);
 hBulkGEl_rec->Sumw2(kTRUE);
 hBulkGEl_gen->Sumw2(kTRUE);
 hBulkG_had_rec_El->Sumw2(kTRUE);
 hBulkG_had_gen_El->Sumw2(kTRUE);
 hRSGMu_rec->Sumw2(kTRUE);
 hRSGMu_gen->Sumw2(kTRUE);
 hRSG_had_rec->Sumw2(kTRUE);
 hRSG_had_gen->Sumw2(kTRUE);
 hRSGEl_rec->Sumw2(kTRUE);
 hRSGEl_gen->Sumw2(kTRUE);
 hRSG_had_rec_El->Sumw2(kTRUE);
 hRSG_had_gen_El->Sumw2(kTRUE);
 
 
 
 
  
 int nBinsX = 16;
 int nBinsY = 10;
 vector<double> BinsX={0,200,250,300,400,500,600,700,800,1000,1200,1500,2000,2500,3000,4000};
 vector<double> BinsY={0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};
 
 vector<double> AlleventsBulkG = SumOverAllFilledBins(hBulkG_had_gen,nBinsX,nBinsY);
 vector<double> AlleventsRSGG = SumOverAllFilledBins(hRSG_had_gen,nBinsX,nBinsY);
 vector<double> AlleventsBulkGlep = SumOverAllFilledBins(hBulkGMu_gen,nBinsX,nBinsY);
 vector<double> AlleventsRSGGlep = SumOverAllFilledBins(hRSGMu_gen,nBinsX,nBinsY);
 vector<double> MueventsBulkG = SumOverAllFilledBins(hBulkGMu_rec,nBinsX,nBinsY);
 vector<double> MueventsRSGG = SumOverAllFilledBins(hRSGMu_rec,nBinsX,nBinsY);
 vector<double> EleventsBulkG = SumOverAllFilledBins(hBulkGEl_rec,nBinsX,nBinsY);
 vector<double> EleventsRSGG = SumOverAllFilledBins(hRSGEl_rec,nBinsX,nBinsY);
 vector<double> ReceventsBulkG = SumOverAllFilledBins(hBulkG_had_rec,nBinsX,nBinsY);
 vector<double> ReceventsRSGG = SumOverAllFilledBins(hRSG_had_rec,nBinsX,nBinsY);
 
 std::cout<< " number of all events BG " << AlleventsBulkGlep[1] << std::endl;
 std::cout << " number of all events RSG " << AlleventsRSGGlep[1]<<std::endl;
 std::cout<< " number of mu events BG " << MueventsBulkG[1] << std::endl;
 std::cout << " number of mu events RSG " << MueventsRSGG[1]<<std::endl;
 std::cout<< " number of el events BG " << EleventsBulkG[1] << std::endl;
 std::cout << " number of el events RSG " << EleventsRSGG[1]<<std::endl;
 std::cout<< " number of had rec events BG " << ReceventsBulkG[1] << std::endl;
 std::cout << " number of had rec events RSG " << ReceventsRSGG[1]<<std::endl;
 
 std::cout << " eff mu BG " << MueventsBulkG[1]/AlleventsBulkGlep[1] << std::endl;
 std::cout << " eff mu RSG " << MueventsRSGG[1]/AlleventsRSGGlep[1] << std::endl;

  std::cout << " eff el BG " << EleventsBulkG[1]/AlleventsBulkGlep[1] << std::endl;
  std::cout << " eff el RSG " << EleventsRSGG[1]/AlleventsRSGGlep[1] << std::endl;
 
  std::cout << " eff had BG " << ReceventsBulkG[1]/AlleventsBulkG[1] << "  +/- "<< TMath::Sqrt(ReceventsBulkG[1])/AlleventsBulkGlep[1] +  EleventsBulkG[1]/pow(AlleventsBulkGlep[1],2)*TMath::Sqrt(AlleventsBulkGlep[1])<< std::endl;
 std::cout << " eff had RSG " << ReceventsRSGG[1]/AlleventsRSGG[1] <<  "  +/- "<< TMath::Sqrt(ReceventsRSGG[1])/AlleventsRSGGlep[1] +  EleventsRSGG[1]/pow(AlleventsRSGGlep[1],2)*TMath::Sqrt(AlleventsRSGGlep[1])<< std::endl;
 double eff_had_BG = ReceventsBulkG[1]/AlleventsBulkG[1];
 double eff_had_RSG = ReceventsRSGG[1]/AlleventsRSGG[1];
 
 
 hBulkGMu_rec->Sumw2(kTRUE);
 hRSGMu_rec->Sumw2(kTRUE);
 //hBulkGMu_rec->Scale(1/AlleventsBulkG[1]);
 //hRSGMu_rec->Scale(1/AlleventsRSGG[1]);
 TCanvas *ceff1 = new TCanvas("ceff1","ceff1",400,400);
 gPad->SetRightMargin(0.15);
 gStyle->SetOptStat(0);
 TCanvas *ceff2 = new TCanvas("ceff2","ceff2",400,400);
 gPad->SetRightMargin(0.15);
 gStyle->SetOptStat(0);
 TCanvas *ceff3 = new TCanvas("ceff3","ceff3",400,400);
 gPad->SetRightMargin(0.15);
 gStyle->SetOptStat(0);
 
 TCanvas *RSceff1 = new TCanvas("RSceff1","RSceff1",400,400);
 gPad->SetRightMargin(0.15);
 gStyle->SetOptStat(0);
 TCanvas *RSceff2 = new TCanvas("RSceff2","RSceff2",400,400);
 gPad->SetRightMargin(0.15);
 gStyle->SetOptStat(0);
 TCanvas *RSceff3 = new TCanvas("RSceff3","RSceff3",400,400);
 gPad->SetRightMargin(0.15);
 gStyle->SetOptStat(0);
 
 TH2* eff_hBulkGMu = GetEfficiencies(hBulkGMu_rec,hBulkGMu_gen,ceff1);
 TH2* eff_hBulkGEl = GetEfficiencies(hBulkGEl_rec,hBulkGEl_gen,ceff2);
 TH2* eff_hBulkG_had = GetEfficiencies(hBulkG_had_rec,hBulkG_had_gen,ceff3);
 
 TH2* eff_hRSGMu = GetEfficiencies(hRSGMu_rec,hRSGMu_gen,RSceff1);
 TH2* eff_hRSGEl = GetEfficiencies(hRSGEl_rec,hRSGEl_gen,RSceff2);
 TH2* eff_hRSG_had = GetEfficiencies(hRSG_had_rec,hRSG_had_gen,RSceff3);
 
 SetStyleEffPlots(eff_hBulkG_had,ceff3,"Bulk Graviton","W #rightarrow q #bar{q}'","",2500);
 SetStyleEffPlots(eff_hRSG_had,RSceff3,"RS Graviton","W #rightarrow q #bar{q}'","",2500);
 SetStyleEffPlots(eff_hBulkGMu,ceff1,"Bulk Graviton","W #rightarrow  #mu #nu","",2500);
 SetStyleEffPlots(eff_hRSGMu,RSceff1,"RS Graviton","W #rightarrow #mu #nu","",2500);
 SetStyleEffPlots(eff_hBulkGEl,ceff2,"Bulk Graviton","W #rightarrow e #nu","",2500);
 SetStyleEffPlots(eff_hRSGEl,RSceff2,"RS Graviton","W #rightarrow e #nu","",2500);
 

 
 hBulkG_had_rec->Sumw2(kTRUE);
 hRSG_had_rec->Sumw2(kTRUE);
 
 
 
 
 std::cout<< eff_had_RSG/eff_had_BG << " " << 1/(eff_had_RSG/eff_had_BG) << std::endl;
 
std::cout << " error BG createHisto " << eff_hBulkG_had->GetBinError(eff_hBulkG_had->GetBin(2,2))<< std::endl;
 
 TCanvas* vis = new TCanvas("vis","vis",800,800);
 vis->Divide(2,2);
 TH2* Ratio_eff = (TH2*) eff_hRSG_had->Clone("Ratio_eff");
 Ratio_eff->Divide(eff_hBulkG_had);
 //Ratio_eff->GetZaxis()->SetRangeUser(0.5,2.0);
 //Ratio_eff->SetMinimum(0.5);
 //Ratio_eff->SetMaximum(2.0);
 PrintBinContents(eff_hBulkG_had,BinsX,BinsY,"efficiency ratio for RS-Graviton/Bulk-Graviton binwise",1);

 Ratio_eff->SetTitle("Ratio of BG/ RS efficiency, hadronic channel");
 vis->cd(1);
 Ratio_eff->Draw("COLZ");
 vis->cd(2);
 eff_hRSG_had->Scale(eff_had_BG/eff_had_RSG);
 TH2* Ratio_eff_rescaled = (TH2*) eff_hBulkG_had->Clone("Ratio_eff_rescaled");
 Ratio_eff_rescaled->Divide(eff_hRSG_had);
 Ratio_eff_rescaled->SetMaximum(2.0);
 Ratio_eff->SetMaximum(2.0);
 Ratio_eff_rescaled->SetTitle("Ratio of BG/ rescaled RS efficiency, hadronic channel");
 Ratio_eff_rescaled->Draw("COLZ");
 vis->cd(3);
 TH2* Ratio_eff_mu = (TH2*) eff_hRSGMu->Clone("Ratio_eff_mu");
 Ratio_eff_mu->Divide(eff_hBulkGMu);
 Ratio_eff_mu->SetTitle("Ratio BS_Mu/BG_Mu");
 Ratio_eff_mu->SetMaximum(2.0);
 Ratio_eff_mu->Draw("COLZ");
 vis->cd(4);
 TH2* Ratio_eff_el = (TH2*) eff_hRSGEl->Clone("Ratio_eff_el");
 Ratio_eff_el->Divide(eff_hBulkGEl);
 Ratio_eff_el->SetTitle("Ratio BS_El/BG_El");
 Ratio_eff_el->SetMaximum(2.0);
 Ratio_eff_el->Draw("COLZ");
 vis->Update();
 //vis->SaveAs("/usr/users/dschaefer/root/results/Efficiency/Ratio_effBG_effRSrescaled.pdf");
 
 
 //hRSG_had_gen->Scale(1/AlleventsRSGG[1]);
 //hBulkG_had_gen->Scale(1/AlleventsBulkG[1]);
 hRSG_had_rec->Scale(1/ReceventsRSGG[1]*ReceventsBulkG[1]/ReceventsRSGG[1]);
 hBulkG_had_rec->Scale(1/ReceventsBulkG[1]);
 
 
 //double *res_had  = new double(300);
 //double *res_mu = new double(300);
 //double *res_el = new double(300);
 Double_t res_had[160];
 Double_t res_mu[160];
 Double_t res_el[160];
 
 double* x = new double(113);
 for(int i=1;i<114;i++){x[i-1]=i;}
 double testChi2_2D_eff       = eff_hBulkG_had->Chi2Test(eff_hRSG_had,"WWP",res_had);
 std::cout << std::endl;
 std::cout << std::endl;
  std::cout<<"histo 1(W_pt, W_eta) = efficiency (hadronic Events after selection/hadronic Events generated), Bulk Graviton sample;" <<std::endl;
 std::cout<<"histo 2(W_pt, W_eta) = efficiency (hadronic Events after selection/hadronic Events generated) , RS Sample, normalised to *eff_BG/eff_RS" << std::endl;
 std::cout<<" p-Value: Chi2(histo1,histo2) = " << testChi2_2D_eff << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 

 double testChi2_2D_eff_mu = eff_hBulkGMu->Chi2Test(eff_hRSGMu,"WWP",res_mu);
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout<<"histo 1(W_pt, W_eta) = efficiency (mu Events after selection/mu Events generated), Bulk Graviton sample;" <<std::endl;
 std::cout<<"histo 2(W_pt, W_eta) = efficiency (mu Events after selection/mu Events generated) , RS Sample" << std::endl;
 std::cout<<" p-Value: Chi2(histo1,histo2) = " << testChi2_2D_eff_mu << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
 
 double testChi2_2D_eff_el = eff_hBulkGEl->Chi2Test(eff_hRSGEl,"WWP",res_el);
 std::cout << std::endl;
 std::cout << std::endl;
  std::cout<<"histo 1(W_pt, W_eta) = efficiency (el Events after selection/el Events generated), Bulk Graviton sample;" <<std::endl;
 std::cout<<"histo 2(W_pt, W_eta) = efficiency (el Events after selection/el Events generated) , RS Sample" << std::endl;
 std::cout<<" p-Value: Chi2(histo1,histo2) = " << testChi2_2D_eff_el << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
/* 
 TGraph* g_had = new TGraph(112,x,res_had);
 TGraph* g_mu = new TGraph(112,x,res_mu);
 TGraph* g_el = new TGraph(112,x,res_el);
 
  TCanvas* canvasRes = new TCanvas("canvasRes","residuals",800,800);
  canvasRes->Divide(2,2);
  canvasRes->cd(1);
  g_el->SetTitle("normalised residuals e-channel");
  g_el->Draw("A*");
  canvasRes->cd(2);
  g_mu->SetTitle("normalised residuals #mu -channel");
  g_mu->Draw("A*");
  canvasRes->cd(3);
  g_had->SetTitle("normalised  residuals had channel");
  g_had->Draw("A*");
  canvasRes->Update();
  */
TH1D* proj_hBulkGMu_pt = eff_hBulkGMu->ProjectionX("proj_BulkG_mu_pt");
TH1D* proj_hRSGMu_pt = eff_hRSGMu->ProjectionX("proj_RSG_mu_pt");

// TGraph* qGraph_mu = new TGraph(17);
// proj_hRSGMu_pt->GetQuantiles(17,qGraph_mu->GetY());
// proj_hBulkGMu_pt->GetQuantiles(17,qGraph_mu->GetX());
//  TCanvas* q = new TCanvas("q","q",800,800);
//  q->cd(1);
//  qGraph_mu->Draw("alp");
 
  
//   TF1* gauss = new TF1("gauss","TMath::Gaus(x,0,1)",-10,10);
//   TGraphQQ *qqplot = new TGraphQQ(16,res_mu,gauss);
//   
//   TCanvas* q = new TCanvas("q","q",800,800);
//   q->Divide(2,2);
//   q->cd(1);
//   qqplot->Draw("A*");
 
 
/*
 TH1D* proj_BulkG_had_pt = eff_hBulkG_had->ProjectionX("proj_BulkG_had_pt");
 TH1D* proj_RSG_had_pt = eff_hRSG_had->ProjectionX("proj_RSG_had_pt");
 TH1D* proj_BulkG_had_eta = eff_hBulkG_had->ProjectionY("proj_BulkG_had_eta");
 TH1D* proj_RSG_had_eta = eff_hRSG_had->ProjectionY("proj_RSG_had_eta");
 

 TCanvas* canvas = new TCanvas("canvas","canvas",800,400);
 canvas->Divide(2,1);
 canvas->cd(1);
 gStyle->SetOptStat(0);
 proj_BulkG_had_pt->SetLineColor(kRed);
 proj_RSG_had_pt->SetLineColor(kBlue);
 proj_BulkG_had_pt->SetFillColor(4000);
 proj_RSG_had_pt->SetFillColor(4000);
 proj_BulkG_had_eta->SetFillColor(4000);
 proj_RSG_had_eta->SetFillColor(4000);
 proj_BulkG_had_pt->Draw("E1");
 proj_RSG_had_pt->Draw("E1SAME");
 TLegend* leg1= new TLegend(0.9,0.68,0.5,0.8);
 leg1->SetBorderSize(0);
 leg1->SetFillColor(0);
 leg1->AddEntry(proj_BulkG_had_pt,"x projection Bulk-G. Eff.","lep"); 
 leg1->AddEntry(proj_RSG_had_pt,"x projection RS-G. Eff.*1.3","lep"); 
 leg1->Draw();
 canvas->cd(2);
 proj_BulkG_had_eta->SetLineColor(kRed);
 proj_RSG_had_eta->SetLineColor(kBlue);
 proj_BulkG_had_eta->Draw("E1");
 proj_RSG_had_eta->Draw("E1SAME");
 TLegend* leg= new TLegend(0.9,0.68,0.5,0.8);
 leg->SetBorderSize(0);
 leg->SetFillColor(0);
 leg->AddEntry(proj_BulkG_had_eta,"y projection Bulk-G. Eff.","lep"); 
 leg->AddEntry(proj_RSG_had_eta,"y projection RS-G. Eff.*1.3","lep"); 
 leg->Draw();
 canvas->Update();
 canvas->SaveAs("/usr/users/dschaefer/root/results/Efficiency/compareRS_BG_eff.pdf");
 */
 
 
 /*
 hRSG_had_gen->Scale(AlleventsBulkG[1]/AlleventsRSGG[1]);
 //hBulkG_had_gen->Scale(AlleventsBulkG[1]);
 TCanvas* vis1 = new TCanvas("vis1","vis1",800,800);
 vis1->Divide(2,2);
 //TH2* Ratio_eff_gen = GetRatioHisto(hBulkG_had_gen,hRSG_had_gen,nBinsX,nBinsY);
 //Ratio_eff_gen->SetMinimum(0);
 //Ratio_eff_gen->SetTitle("Ratio of BG/ rescaled RS efficiency, hadronic channel");
 TH2* temp = (TH2*) hBulkG_had_gen->Clone("temp");
 temp->Add(hRSG_had_gen,-1);
 vis1->cd(1);
 gPad->SetRightMargin(0.15);
 //Ratio_eff_gen->Draw("COLZ");
 temp->Draw("COLZ");
 vis1->cd(2);
 gPad->SetRightMargin(0.15);
 hBulkG_had_gen->SetTitle("gen. Bulk-Graviton");
 hBulkG_had_gen->Draw("COLZ");
 vis1->cd(3);
 gPad->SetRightMargin(0.15);
 hRSG_had_gen->SetTitle("gen. RS-Graviton");
 hRSG_had_gen->Draw("COLZ");
 */
 
 
 
 
}













