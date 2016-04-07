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


 
void testCategories(string ModelName)
{
 

 string Sinput_filename3 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/"+ModelName+"ToWWKinematics_el_HP.root";
 string Sinput_filename4 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/"+ModelName+"ToWWKinematics_mu_HP.root";
 string name_lep = "/usr/users/dschaefer/root/results/Efficiency/semileptonic/ToWW/QuantileBulkGOver"+ModelName+"_leptonicW.pdf";

 string name_em = "/usr/users/dschaefer/root/results/Efficiency/semileptonic/ToWW/Quantile"+ModelName+"_elmuChannel.pdf";

 string name_had = "/usr/users/dschaefer/root/results/Efficiency/semileptonic/ToWW/QuantileBulkGOver"+ModelName+"_hadronicW.pdf";
 
 
 
 if(ModelName.find("Wprime")!=string::npos)
   {
    Sinput_filename3 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/"+ModelName+"ToWZKinematics_el_HP.root";
    Sinput_filename4 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/"+ModelName+"ToWZKinematics_mu_HP.root";
    
     name_lep = "/usr/users/dschaefer/root/results/Efficiency/semileptonic/ToWZ/QuantileBulkGOver"+ModelName+"_leptonicW.pdf";
 
      name_em = "/usr/users/dschaefer/root/results/Efficiency/semileptonic/ToWZ/Quantile"+ModelName+"_elmuChannel.pdf";
      name_had = "/usr/users/dschaefer/root/results/Efficiency/semileptonic/ToWZ/QuantileBulkGOver"+ModelName+"_hadronicZ.pdf";

   }
 
 const char* input_filename1 ="/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/BulkGravToWWKinematics_el_HP.root";
const char* input_filename2 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/BulkGravToWWKinematics_mu_HP.root";





const char* input_filename3 = Sinput_filename3.c_str();
const char* input_filename4 = Sinput_filename4.c_str();
TFile * BulkGravEl = new TFile(input_filename1,"READ");
TFile * BulkGravMu = new TFile(input_filename2,"READ");
TFile * RSGravEl = new TFile(input_filename3,"READ");
TFile * RSGravMu = new TFile(input_filename4,"READ");

 TH2F* hBulkGMu_rec 		= (TH2F*) BulkGravMu->Get("hW_lep_rec_fb");
 TH2F* hBulkGMu_gen		= (TH2F*) BulkGravMu->Get("hW_lep_genWithVeto_fb");
 TH2F* hBulkG_had_rec		= (TH2F*) BulkGravMu->Get("hW_had_rec_fb");
 TH2F* hBulkG_had_gen		= (TH2F*) BulkGravMu->Get("hW_had_genWithVeto_fb");
 TH2F* hBulkGEl_rec 		= (TH2F*) BulkGravEl->Get("hW_lep_rec_fb");
 TH2F* hBulkGEl_gen 		= (TH2F*) BulkGravEl->Get("hW_lep_genWithVeto_fb");
 TH2F* hBulkG_had_rec_El	= (TH2F*) BulkGravEl->Get("hW_had_rec_fb");
 TH2F* hBulkG_had_gen_El	= (TH2F*) BulkGravEl->Get("hW_had_genWithVeto_fb");

 
 TH2F* hRSGMu_rec 	= (TH2F*) RSGravMu->Get("hW_lep_rec_fb");
 TH2F* hRSGMu_gen	= (TH2F*) RSGravMu->Get("hW_lep_genWithVeto_fb");
 TH2F* hRSG_had_rec	= (TH2F*) RSGravMu->Get("hW_had_rec_fb");
 TH2F* hRSG_had_gen	= (TH2F*) RSGravMu->Get("hW_had_genWithVeto_fb");
 TH2F* hRSGEl_rec 	= (TH2F*) RSGravEl->Get("hW_lep_rec_fb");
 TH2F* hRSGEl_gen 	= (TH2F*) RSGravEl->Get("hW_lep_genWithVeto_fb");
 TH2F* hRSG_had_rec_El	= (TH2F*) RSGravEl->Get("hW_had_rec_fb");
 TH2F* hRSG_had_gen_El	= (TH2F*) RSGravEl->Get("hW_had_genWithVeto_fb");
  
 hBulkG_had_gen->Add(hBulkG_had_gen_El);
 hBulkG_had_rec->Add(hBulkG_had_rec_El);
 hRSG_had_gen->Add(hRSG_had_gen_El);
 hRSG_had_rec->Add(hRSG_had_rec_El);
 double ratio = hBulkG_had_rec->GetEntries()/hBulkG_had_gen->GetEntries()*hRSG_had_gen->GetEntries()/hRSG_had_rec->GetEntries();
 //double ratio =1;
 std::cout << ratio << std::endl;
  
 TH2* eff_hBulkGMu = GetEfficiencies(hBulkGMu_rec,hBulkGMu_gen);
 TH2* eff_hBulkGEl = GetEfficiencies(hBulkGEl_rec,hBulkGEl_gen);
 TH2* eff_hBulkG_had = GetEfficiencies(hBulkG_had_rec,hBulkG_had_gen);
 TH2* eff_hRSGMu = GetEfficiencies(hRSGMu_rec,hRSGMu_gen);
 TH2* eff_hRSGEl = GetEfficiencies(hRSGEl_rec,hRSGEl_gen);
 TH2* eff_hRSG_had = GetEfficiencies(hRSG_had_rec,hRSG_had_gen);
 //eff_hRSG_had->Scale(ratio);
 
 TH1D* proj_hBulkGMu_pt = eff_hBulkGMu->ProjectionX("proj_hBulkGMu_pt");
 TH1D* proj_hRSGMu_pt = eff_hRSGMu->ProjectionX("proj_hRSGMu_pt");
 TH1D* proj_hBulkGEl_pt = eff_hBulkGEl->ProjectionX("proj_hBulkGEl_pt");
 TH1D* proj_hRSGEl_pt = eff_hRSGEl->ProjectionX("proj_hRSGEl_pt");
 TH1D* proj_hBulkGMu_eta = eff_hBulkGMu->ProjectionY("proj_hBulkGMu_eta");
 TH1D* proj_hRSGMu_eta = eff_hRSGMu->ProjectionY("proj_hRSGMu_eta");
 TH1D* proj_hBulkGEl_eta = eff_hBulkGEl->ProjectionY("proj_hBulkGEl_eta");
 TH1D* proj_hRSGEl_eta = eff_hRSGEl->ProjectionY("proj_hRSGEl_eta");

  
 int Nq_pt = 50;
 int Nq_eta = 50;
 
 Double_t RSG_mu[Nq_pt];
 Double_t BG_mu[Nq_pt];
 Double_t RSG_el[Nq_pt];
 Double_t BG_el[Nq_pt];
 Double_t RSG_mu2[Nq_eta];
 Double_t BG_mu2[Nq_eta];
 Double_t RSG_el2[Nq_eta];
 Double_t BG_el2[Nq_eta];

 
  Double_t probSumPt[Nq_pt];
 for(int i=1;i<=Nq_pt;i++)
 {probSumPt[i-1]=i/double(Nq_pt);}
 Double_t probSumEta[Nq_eta];
 for(int i=1;i<=Nq_eta;i++)
 {probSumEta[i-1]=i/double(Nq_eta);}
 
 
 

 
 proj_hRSGEl_pt->GetQuantiles(Nq_pt,RSG_el,probSumPt);
 proj_hBulkGEl_pt->GetQuantiles(Nq_pt,BG_el,probSumPt);
 proj_hRSGMu_pt->GetQuantiles(Nq_pt,RSG_mu,probSumPt);
 proj_hBulkGMu_pt->GetQuantiles(Nq_pt,BG_mu,probSumPt);
 proj_hRSGEl_eta->GetQuantiles(Nq_eta,RSG_el2,probSumEta);
 proj_hBulkGEl_eta->GetQuantiles(Nq_eta,BG_el2,probSumEta);
 proj_hRSGMu_eta->GetQuantiles(Nq_eta,RSG_mu2,probSumEta);
 proj_hBulkGMu_eta->GetQuantiles(Nq_eta,BG_mu2,probSumEta);
 
 string title_mu_pt  = "quantile BulkGrav/"+ModelName+" muon channel, p_{T} distribution";
 string title_el_pt  = "quantile BulkGrav/"+ModelName+" electron channel, p_{T} distribution";
 string title_mu_eta = "quantile BulkGrav/"+ModelName+" muon channel, |#eta| distribution";
 string title_el_eta = "quantile BulkGrav/"+ModelName+" electron channel, |#eta| distribution";
 
 
 TGraphQQ* qGraph_mu = new TGraphQQ(Nq_pt-1,BG_mu,Nq_pt-1,RSG_mu);
 qGraph_mu->SetTitle(title_mu_pt.c_str());
 TGraphQQ* qGraph_el = new TGraphQQ(Nq_pt-1,BG_el,Nq_pt-1,RSG_el);
 qGraph_el->SetTitle(title_el_pt.c_str());
 TGraphQQ* qGraph_mu2 = new TGraphQQ(Nq_eta-1,BG_mu2,Nq_eta-1,RSG_mu2);
 qGraph_mu2->SetTitle(title_mu_eta.c_str());
 TGraphQQ* qGraph_el2 = new TGraphQQ(Nq_eta-1,BG_el2,Nq_eta-1,RSG_el2);
  qGraph_el2->SetTitle(title_el_eta.c_str());

 qGraph_mu->GetXaxis()->SetTitle("p_{T} [GeV]"); 
 qGraph_mu->GetYaxis()->SetTitleOffset(1.5);
 qGraph_mu->GetYaxis()->SetTitle("p_{T} [GeV]");
 qGraph_el->GetXaxis()->SetTitle("p_{T} [GeV]"); 
 qGraph_el->GetYaxis()->SetTitleOffset(1.5);
 qGraph_el->GetYaxis()->SetTitle("p_{T} [GeV]");
 qGraph_mu2 ->GetXaxis()->SetTitle("|#eta|");
 qGraph_mu2 ->GetYaxis()->SetTitleOffset(1.5);
 qGraph_mu2 ->GetYaxis()->SetTitle("|#eta|");
 qGraph_el2->GetXaxis()->SetTitle("|#eta|"); 
 qGraph_el2->GetYaxis()->SetTitleOffset(1.5);
 qGraph_el2->GetYaxis()->SetTitle("|#eta|");
 
 
  string title_mu_el_pt = "quantile mu/el p_{t} distribution, "+ModelName+" sample";
  string title_mu_el_eta = "quantile mu/el |#eta| distribution, "+ModelName+" sample";
  
   TGraphQQ* qGraph_em_pt_RS = new TGraphQQ(Nq_pt-1,RSG_mu,Nq_pt-1,RSG_el);
   qGraph_em_pt_RS->SetTitle(title_mu_el_pt.c_str());
   TGraphQQ* qGraph_em_pt_BG = new TGraphQQ(Nq_pt-1,BG_mu,Nq_pt-1,BG_el);
   qGraph_em_pt_BG->SetTitle("quantile mu/el p_{t} distribution, BG sample");
   TGraphQQ* qGraph_em_eta_RS = new TGraphQQ(Nq_eta-1,RSG_mu2,Nq_eta-1,RSG_el2);
   qGraph_em_eta_RS->SetTitle(title_mu_el_eta.c_str());
   TGraphQQ* qGraph_em_eta_BG = new TGraphQQ(Nq_eta-1,BG_mu2,Nq_eta-1,BG_el2);
   qGraph_em_eta_BG->SetTitle("quantile mu/el |#eta| distribution, BG sample");
   
 TCanvas* q = new TCanvas("q","q",800,800);
 gPad->SetLeftMargin(0.16);
 q->Divide(2,2);
 q->cd(1);
 qGraph_mu->Draw("A*");
 q->cd(2);
 qGraph_mu2->Draw("A*");
 q->cd(3);
  qGraph_el->Draw("A*");
 q->cd(4);
 qGraph_el2->Draw("A*");
 
 TCanvas* q2 = new TCanvas("q2","q2",800,400);
 q2->Divide(2,1);
 q2->cd(1);
 qGraph_em_pt_RS->Draw("A*");
 q2->cd(2);
 //qGraph_em_pt_BG->Draw("A*");
 //q2->cd(3);
 qGraph_em_eta_RS->Draw("A*");
 //q2->cd(4);
 //qGraph_em_eta_BG->Draw("A*");
 
 q->SaveAs(name_lep.c_str());
 q2->SaveAs(name_em.c_str());
 
 
 TH1D* proj_hBulkG_had_pt = eff_hBulkG_had->ProjectionX("proj_hBulkG_had_pt");
 TH1D* proj_hRSG_had_pt = eff_hRSG_had->ProjectionX("proj_hRSG_had_pt");
 TH1D* proj_hBulkG_had_eta = eff_hBulkG_had->ProjectionY("proj_hBulkG_had_eta");
 TH1D* proj_hRSG_had_eta = eff_hRSG_had->ProjectionY("proj_hRSG_had_eta");
//   proj_hBulkG_had_pt->Sumw2(kTRUE);
//   proj_hBulkG_had_pt->Scale(1/proj_hBulkG_had_pt->GetEntries());
//   proj_hRSG_had_pt->Sumw2(kTRUE);
//   proj_hRSG_had_pt->Scale(1/proj_hRSG_had_pt->GetEntries());
 

 Double_t RSG_had[Nq_pt];
 Double_t BG_had[Nq_pt];
 Double_t RSG_had2[Nq_eta];
 Double_t BG_had2[Nq_eta];

 
 proj_hRSG_had_pt->GetQuantiles(Nq_pt,RSG_had,probSumPt);
 proj_hBulkG_had_pt->GetQuantiles(Nq_pt,BG_had,probSumPt);
 proj_hRSG_had_eta->GetQuantiles(Nq_eta,RSG_had2,probSumEta);
 proj_hBulkG_had_eta->GetQuantiles(Nq_eta,BG_had2,probSumEta);
 
 string title_had_pt = "quantile hadron channel Bulk Grav/"+ModelName+", p_T distribution. ";
 string title_had_eta = "quantile hadron channel Bulk Grav/"+ModelName+", |#eta| distribution.";

 TGraphQQ* qGraph_had = new TGraphQQ(Nq_pt,BG_had,Nq_pt,RSG_had);
 qGraph_had->SetTitle(title_had_pt.c_str());
 TGraphQQ* qGraph_had2 = new TGraphQQ(Nq_eta,BG_had2,Nq_eta,RSG_had2);
 qGraph_had2->SetTitle(title_had_eta.c_str());

 qGraph_had->GetXaxis()->SetTitle("p_{T} [GeV]"); 
 qGraph_had->GetYaxis()->SetTitleOffset(1.5);
 qGraph_had->GetYaxis()->SetTitle("p_{T} [GeV]");
 qGraph_had2 ->GetXaxis()->SetTitle("|#eta|");
 qGraph_had2 ->GetYaxis()->SetTitleOffset(1.5);
 qGraph_had2 ->GetYaxis()->SetTitle("|#eta|");
 
 
 TCanvas* qhad = new TCanvas("qhad","qhad",800,400);
 qhad->Divide(2,1);
 qhad->cd(1);
 qGraph_had->Draw("A*");
 qhad->cd(2);
 qGraph_had2->Draw("A*"); 
 
 
 qhad->SaveAs(name_had.c_str());
}