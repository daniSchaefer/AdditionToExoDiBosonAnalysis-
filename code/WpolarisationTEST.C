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


 
void WpolarisationTEST(string ModelName1, string ModelName2,string category, int mass=0)
{
 
  string Sinput_filename1;
  string Sinput_filename2;
  string Sinput_filename3;
  string Sinput_filename4;
  
 string outputfileName;
 if(mass==0)
 {
  outputfileName = "/usr/users/dschaefer/root/results/Efficiency/semileptonic/ToWW/Wpolarisation_Ratios_"+ModelName1+"_"+ModelName2+"_"+category+".pdf"; 
   
  
 }
  else
  {
    outputfileName = "/usr/users/dschaefer/root/results/Efficiency/semileptonic/ToWW/Wpolarisation_Ratios_"+ModelName1+"_"+ModelName2+"_"+category+"_"+std::to_string(int(mass))+".pdf";
  } 
  
 if(mass == 0)
 {
  Sinput_filename1 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/"+ModelName1+"ToWWKinematics_el_"+category+".root";
  Sinput_filename2 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/"+ModelName1+"ToWWKinematics_mu_"+category+".root";
  Sinput_filename3 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/"+ModelName2+"ToWWKinematics_el_"+category+".root";
  Sinput_filename4 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/"+ModelName2+"ToWWKinematics_mu_"+category+".root";
  if(ModelName1.find("Wprime")!=string::npos)
  {
    Sinput_filename1 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/"+ModelName1+"ToWZKinematics_el_"+category+".root";
    Sinput_filename2 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/"+ModelName1+"ToWZKinematics_mu_"+category+".root";
  }
  if(ModelName2.find("Wprime")!=string::npos)
  {
    Sinput_filename3 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/"+ModelName2+"ToWZKinematics_el_"+category+".root";
    Sinput_filename4 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/"+ModelName2+"ToWZKinematics_mu_"+category+".root";
  }
  
 }
 else
 {
   float width = 0.1;
   if(ModelName1.find("BulkGrav")!=string::npos)
   {width =0.0;}
    
   Sinput_filename1="/storage/jbod/dschaefer/testEff/"+ ModelName1+"ToWKinematics_el_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
   Sinput_filename2 ="/storage/jbod/dschaefer/testEff/"+ ModelName1+"ToWKinematics_mu_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
   width =0.1;
    if(ModelName2.find("BulkGrav")!=string::npos)
   {width =0.0;}
   Sinput_filename3="/storage/jbod/dschaefer/testEff/"+ ModelName2+"ToWKinematics_el_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
   Sinput_filename4="/storage/jbod/dschaefer/testEff/"+ ModelName2+"ToWKinematics_mu_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
 }
  
  std::cout<< Sinput_filename1<< std::endl;
  std::cout<< Sinput_filename2<< std::endl;
  std::cout<< Sinput_filename3<< std::endl;
  std::cout<< Sinput_filename4<< std::endl;
 const char* input_filename1 = Sinput_filename1.c_str();
const char* input_filename2 = Sinput_filename2.c_str();
const char* input_filename3 = Sinput_filename3.c_str();
const char* input_filename4 = Sinput_filename4.c_str();
TFile * BulkGravEl = new TFile(input_filename1,"READ");
TFile * BulkGravMu = new TFile(input_filename2,"READ");
TFile * RSGravEl = new TFile(input_filename3,"READ");
TFile * RSGravMu = new TFile(input_filename4,"READ");

 TH2F* hBulkGMu_rec 		= (TH2F*) BulkGravMu->Get("hW_lep_rec");
 TH2F* hBulkG_had_rec		= (TH2F*) BulkGravMu->Get("hW_had_rec");
 TH2F* hBulkGEl_rec 		= (TH2F*) BulkGravEl->Get("hW_lep_rec");
 TH2F* hBulkG_had_rec_El	= (TH2F*) BulkGravEl->Get("hW_had_rec");
 
 TH2F* hBulkG_had_gen_El;
 TH2F* hBulkGMu_gen;
 TH2F* hBulkG_had_gen;
 TH2F* hBulkGEl_gen;
 TH2F* hRSG_had_gen_El;
 TH2F* hRSGMu_gen;
 TH2F* hRSG_had_gen;
 TH2F* hRSGEl_gen;
 if(mass==0)
 {
  hBulkG_had_gen_El	= (TH2F*) BulkGravEl->Get("hW_had_genWithVeto");
  hBulkGMu_gen		= (TH2F*) BulkGravMu->Get("hW_lep_genWithVeto");
  hBulkG_had_gen	= (TH2F*) BulkGravMu->Get("hW_had_genWithVeto");
  hBulkGEl_gen 		= (TH2F*) BulkGravEl->Get("hW_lep_genWithVeto");
  hRSG_had_gen_El	= (TH2F*) RSGravEl->Get("hW_had_genWithVeto");
  hRSGMu_gen		= (TH2F*) RSGravMu->Get("hW_lep_genWithVeto");
  hRSG_had_gen		= (TH2F*) RSGravMu->Get("hW_had_genWithVeto");
  hRSGEl_gen 		= (TH2F*) RSGravEl->Get("hW_lep_genWithVeto");
 }
 else{
   
 hBulkG_had_gen_El	= (TH2F*) BulkGravEl->Get("hW_had_gen"); 
 hBulkGMu_gen		= (TH2F*) BulkGravMu->Get("hW_lep_gen"); 
 hBulkG_had_gen		= (TH2F*) BulkGravMu->Get("hW_had_gen"); 
 hBulkGEl_gen 		= (TH2F*) BulkGravEl->Get("hW_lep_gen"); 
 hRSG_had_gen_El	= (TH2F*) RSGravEl->Get("hW_had_gen");
 hRSGMu_gen		= (TH2F*) RSGravMu->Get("hW_lep_gen"); 
 hRSG_had_gen		= (TH2F*) RSGravMu->Get("hW_had_gen"); 
 hRSGEl_gen 		= (TH2F*) RSGravEl->Get("hW_lep_gen");
 }
 
 
 TH2F* hRSGMu_rec 	= (TH2F*) RSGravMu->Get("hW_lep_rec");
 TH2F* hRSG_had_rec	= (TH2F*) RSGravMu->Get("hW_had_rec");
 TH2F* hRSGEl_rec 	= (TH2F*) RSGravEl->Get("hW_lep_rec");
 TH2F* hRSG_had_rec_El	= (TH2F*) RSGravEl->Get("hW_had_rec");
 
 
 
 
 
  
 hBulkG_had_gen->Add(hBulkG_had_gen_El);
 hBulkG_had_rec->Add(hBulkG_had_rec_El);
 hRSG_had_gen->Add(hRSG_had_gen_El);
 hRSG_had_rec->Add(hRSG_had_rec_El);
 
 double Nevents_BG 	= hBulkG_had_gen->GetEntries();
 double Nevents_BG_mu   = hBulkGMu_rec->GetEntries();
 double Nevents_BG_mu_gen = hBulkGMu_gen->GetEntries();
 double Nevents_BG_el	= hBulkGEl_rec->GetEntries();
 double Nevents_BG_el_gen = hBulkGEl_gen->GetEntries();
 double Nevents_BG_had	= hBulkG_had_rec->GetEntries();
 
 double Nevents_RSG 	= hRSG_had_gen->GetEntries();
 double Nevents_RSG_mu   = hRSGMu_rec->GetEntries();
  double Nevents_RSG_mu_gen   = hRSGMu_gen->GetEntries();
 double Nevents_RSG_el	= hRSGEl_rec->GetEntries();
  double Nevents_RSG_el_gen   = hRSGEl_gen->GetEntries();
 double Nevents_RSG_had	= hRSG_had_rec->GetEntries();
  
 std::cout<<"Number of generated Events in "<<ModelName1<<" : " <<Nevents_BG<<std::endl;
 std::cout<<"Efficiency "<<ModelName1 << " muon channel : "<<Nevents_BG_mu/Nevents_BG_mu_gen<<std::endl;
 std::cout<<"Efficiency "<<ModelName1 << " sample ele channel : "<<Nevents_BG_el/Nevents_BG_el_gen<<std::endl;
 std::cout<<"Efficiency "<<ModelName1 <<" sample hadronic W : "<<Nevents_BG_had/Nevents_BG<<std::endl;
  std::cout <<std::endl;
 std::cout<<"Number of generated Events in "<<ModelName2<< " sample : "<<Nevents_RSG<<std::endl;
 std::cout<<"Efficiency " << ModelName2 << " sample muon channel : "<<Nevents_RSG_mu/Nevents_RSG_mu_gen<<std::endl;
 std::cout<<"Efficiency "<<ModelName2 <<" sample ele channel : "<<Nevents_RSG_el/Nevents_RSG_el_gen<<std::endl;
 std::cout<<"Efficiency "<< ModelName2 <<" sample hadronic W : "<<Nevents_RSG_had/Nevents_RSG<<std::endl;
  
  double ratio = Nevents_BG_had/Nevents_BG*Nevents_RSG/Nevents_RSG_had;

  
 string titleEFF = ModelName1+" mu-channel";
 TCanvas *ceff1 = new TCanvas("ceff1",titleEFF.c_str(),400,400);
 titleEFF = ModelName1+" el-channel";         
 TCanvas *ceff2 = new TCanvas("ceff2",titleEFF.c_str(),400,400);
 titleEFF = ModelName1+" had-channel";        
 TCanvas *ceff3 = new TCanvas("ceff3",titleEFF.c_str(),400,400);
  titleEFF = ModelName2+" mu-channel";
 TCanvas *RSceff1 = new TCanvas("RSceff1",titleEFF.c_str(),400,400);
 titleEFF = ModelName2+" el-channel";
 TCanvas *RSceff2 = new TCanvas("RSceff2",titleEFF.c_str(),400,400);
  titleEFF = ModelName2+" had-channel";
 TCanvas *RSceff3 = new TCanvas("RSceff3",titleEFF.c_str(),400,400);
 
 const char* zAxistitle = "Reconstruction and ID efficiencies #times 1/2";
  
 TH2* eff_hBulkGMu =  		GetEfficiencies(hBulkGMu_rec,hBulkGMu_gen,ceff1,zAxistitle);
 TH2* eff_hBulkGEl = 		GetEfficiencies(hBulkGEl_rec,hBulkGEl_gen,ceff2,zAxistitle);
 TH2* eff_hBulkG_had = 		GetEfficiencies(hBulkG_had_rec,hBulkG_had_gen,ceff3,zAxistitle);
 TH2* eff_hRSGMu =		GetEfficiencies(hRSGMu_rec,hRSGMu_gen,RSceff1,zAxistitle);
 TH2* eff_hRSGEl = 		GetEfficiencies(hRSGEl_rec,hRSGEl_gen,RSceff2,zAxistitle);
 TH2* eff_hRSG_had = 		GetEfficiencies(hRSG_had_rec,hRSG_had_gen,RSceff3,zAxistitle);
 
 eff_hBulkGMu->GetZaxis()->SetTitle("meep");
 eff_hBulkGEl->GetZaxis()->SetTitle("meep");
 eff_hBulkG_had->GetZaxis()->SetTitle("meep");
 eff_hRSGMu->GetZaxis()->SetTitle("meep");
 
 SetStyleEffPlots(eff_hBulkG_had,ceff3, ModelName1.c_str(),"W #rightarrow q #bar{q}'","",2500,zAxistitle);
 SetStyleEffPlots(eff_hRSG_had,RSceff3,ModelName2.c_str(),"W #rightarrow q #bar{q}'","",2500,zAxistitle);
 SetStyleEffPlots(eff_hBulkGMu,ceff1,ModelName1.c_str(),"W #rightarrow  #mu #nu","",2500,zAxistitle);
 SetStyleEffPlots(eff_hRSGMu,RSceff1,ModelName2.c_str(),"W #rightarrow #mu #nu","",2500,zAxistitle);
 SetStyleEffPlots(eff_hBulkGEl,ceff2,ModelName1.c_str(),"W #rightarrow e #nu","",2500,zAxistitle);
 SetStyleEffPlots(eff_hRSGEl,RSceff2,ModelName2.c_str(),"W #rightarrow e #nu","",2500,zAxistitle);
  
 TH1D* proj_BulkG_had_pt = eff_hBulkG_had->ProjectionX("proj_BulkG_had_pt");
 TH1D* proj_RSG_had_pt = eff_hRSG_had->ProjectionX("proj_RSG_had_pt");
 TH1D* proj_BulkG_had_eta = eff_hBulkG_had->ProjectionY("proj_BulkG_had_eta");
 TH1D* proj_RSG_had_eta = eff_hRSG_had->ProjectionY("proj_RSG_had_eta");
 
/* 
 
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
 //canvas->SaveAs("/usr/users/dschaefer/root/results/Efficiency/compareRS_BG_eff.pdf");
    */
 string title = ModelName1+"/"+ModelName2+", hadronic channel";
 TCanvas* vis = new TCanvas("vis","vis",800,800);
 vis->Divide(2,2);
 TH2* Ratio_eff = (TH2*) eff_hBulkG_had->Clone("Ratio_eff");
 Ratio_eff->GetZaxis()->SetTitle("Reconstruction and ID efficiencies #times 1/2");
 Ratio_eff->GetZaxis()->SetTitle("Reconstruction and ID efficiencies #times 1/2");
 Ratio_eff->Divide(eff_hRSG_had);
 //Ratio_eff->GetZaxis()->SetRangeUser(0.5,2.0);
 //Ratio_eff->SetMinimum(0.5);
 Ratio_eff->SetMaximum(2.0);
 Ratio_eff->SetTitle(title.c_str());
 vis->cd(1);
 Ratio_eff->Draw("COLZ");
 Ratio_eff->GetZaxis()->SetTitle("Reconstruction and ID efficiencies #times 1/2");
 vis->cd(2);
 eff_hRSG_had->Scale(ratio);
 TH2* Ratio_eff_rescaled = (TH2*) eff_hBulkG_had->Clone("Ratio_eff_rescaled");
 Ratio_eff_rescaled->Divide(eff_hRSG_had);
 Ratio_eff_rescaled->SetMaximum(2.0);
 Ratio_eff->SetMaximum(2.0);
 Ratio_eff_rescaled->GetZaxis()->SetTitle("Reconstruction #times ID Efficiencies #times 1/2");
 title = ModelName1+"/"+ModelName2+", hadronic channel rescaled with"+std::to_string(ratio);
 Ratio_eff_rescaled->SetTitle(title.c_str());
 Ratio_eff_rescaled->Draw("COLZ");
 vis->cd(3);
 TH2* Ratio_eff_mu = (TH2*) eff_hBulkGMu->Clone("Ratio_eff_mu");
 Ratio_eff_mu->Divide(eff_hRSGMu);
 title = ModelName1+"/"+ModelName2+", muon channel";
 Ratio_eff_mu->SetTitle(title.c_str());
 Ratio_eff_mu->SetMaximum(2.0);
 Ratio_eff_mu->GetZaxis()->SetTitle("Reconstruction and ID efficiencies #times 1/2");
 Ratio_eff_mu->Draw("COLZ");
 vis->cd(4);
 TH2* Ratio_eff_el = (TH2*) eff_hBulkGEl->Clone("Ratio_eff_el");
 Ratio_eff_el->Divide(eff_hRSGEl);
 title = ModelName1+"/"+ModelName2+", muon channel";
 Ratio_eff_el->SetTitle(title.c_str());
 Ratio_eff_el->SetMaximum(2.0);
 Ratio_eff_el->GetZaxis()->SetTitle("Reconstruction and ID efficiencies #times 1/2");
 Ratio_eff_el->Draw("COLZ");
 vis->Update();
 
 
 vis->SaveAs(outputfileName.c_str());
 
 
 double testChi2_2D_eff_mu = eff_hBulkGMu->Chi2Test(eff_hRSGMu,"WWP");
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout<<"histo 1(W_pt, W_eta) = efficiency (mu Events after selection/mu Events generated), Bulk Graviton sample;" <<std::endl;
 std::cout<<"histo 2(W_pt, W_eta) = efficiency (mu Events after selection/mu Events generated) , RS Sample" << std::endl;
 std::cout<<" p-Value: Chi2(histo1,histo2) = " << testChi2_2D_eff_mu << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 double testChi2_2D_eff_el = eff_hBulkGEl->Chi2Test(eff_hRSGEl,"WWP");
 std::cout << std::endl;
 std::cout << std::endl;
  std::cout<<"histo 1(W_pt, W_eta) = efficiency (el Events after selection/el Events generated), Bulk Graviton sample;" <<std::endl;
 std::cout<<"histo 2(W_pt, W_eta) = efficiency (el Events after selection/el Events generated) , RS Sample" << std::endl;
 std::cout<<" p-Value: Chi2(histo1,histo2) = " << testChi2_2D_eff_el << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
  double testChi2_2D_eff       = eff_hBulkG_had->Chi2Test(eff_hRSG_had,"WWP");
 std::cout << std::endl;
 std::cout << std::endl;
  std::cout<<"histo 1(W_pt, W_eta) = efficiency (hadronic Events after selection/hadronic Events generated), Bulk Graviton sample;" <<std::endl;
 std::cout<<"histo 2(W_pt, W_eta) = efficiency (hadronic Events after selection/hadronic Events generated) , RS Sample, normalised to *eff_BG/eff_RS" << std::endl;
 std::cout<<" p-Value: Chi2(histo1,histo2) = " << testChi2_2D_eff << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 std::cout << std::endl;
 
}
 
 
 
 
 
 