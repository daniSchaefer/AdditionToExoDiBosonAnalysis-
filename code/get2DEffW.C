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
#include "/usr/users/dschaefer/root/headerfiles/MyClass.h"
#include "/usr/users/dschaefer/root/headerfiles/passed_mu_jes.h"
#include "/usr/users/dschaefer/root/headerfiles/Op.h"
#include "/usr/users/dschaefer/root/headerfiles/EventSelection.h"
#include "/usr/users/dschaefer/root/headerfiles/GenFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/RecFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc.h"


using namespace std;

namespace{
  int loadMyLibraryTriggerFunc(){
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/General.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/Op.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/EventSelection.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/GenFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/RecFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C+");
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

// const char* input_filename6 = "/storage/a/mmozer/Res_Sig/BulkGravToWWToWlepWhad_narrow_M_2000/EXOVVTree_BulkGravToWWToWlepWhad_narrow_M_2000_1.root";
// const char* input_filename6 ="/storage/a/mmozer/Res_Sig/WprimeToWZToWlepZhad_narrow_M-2000/EXOVVTree_WprimeToWZToWlepZhad_narrow_M-2000_1.root";
// 
// TFile *gendata = new TFile(input_filename6,"READ");
// TTree *tree = (TTree*) gendata->Get("ntuplizer/tree");

void get2DEffW(string modelName, string category)
{

 string Sinput_filename1 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/"+modelName+"ToWWKinematics_el_"+category+".root";
 string Sinput_filename2 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/"+modelName+"ToWWKinematics_mu_"+category+".root";
  if(modelName.find("Wprime")!=string::npos)
   {
    Sinput_filename1 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/"+modelName+"ToWZKinematics_el_"+category+".root";
    Sinput_filename2 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/"+modelName+"ToWZKinematics_mu_"+category+".root";
    
   }
 
 const char* input_filename1 = Sinput_filename1.c_str();
 const char* input_filename2 = Sinput_filename2.c_str();
 TFile * histos1 = new TFile(input_filename1,"READ");
 TFile * histos2 = new TFile(input_filename2,"READ"); 
  
  
 TH2F* hWMu_rec 			= (TH2F*) histos2->Get("hW_lep_rec");
 TH2F* hWMu_gen 			= (TH2F*) histos2->Get("hW_lep_gen");
 TH2F* hWMu_genWithVeto 		= (TH2F*) histos2->Get("hW_lep_genWithVeto");
 TH2F* hWMu_genWithBVeto 		= (TH2F*) histos2->Get("hW_lep_genWithBVeto");
 TH2F* hWMu_genWithLooseLeptonVeto 	= (TH2F*) histos2->Get("hW_lep_genWithLooseLeptonVeto");
 TH2F* hW_had_rec			= (TH2F*) histos2->Get("hW_had_rec");
 TH2F* hW_had_genWithVeto		= (TH2F*) histos2->Get("hW_had_genWithVeto");
 TH2F* hW_had_genWithBVeto		= (TH2F*) histos2->Get("hW_had_genWithBVeto");
 TH2F* hW_had_genWithLooseLeptonVeto	= (TH2F*) histos2->Get("hW_had_genWithLooseLeptonVeto");
 
 TH2F* hWEl_rec 			= (TH2F*) histos1->Get("hW_lep_rec");
 TH2F* hWEl_gen  			= (TH2F*) histos1->Get("hW_lep_gen");
 TH2F* hWEl_genWithVeto 		= (TH2F*) histos1->Get("hW_lep_genWithVeto");
 TH2F* hWEl_genWithBVeto 		= (TH2F*) histos1->Get("hW_lep_genWithBVeto");
 TH2F* hWEl_genWithLooseLeptonVeto 	= (TH2F*) histos1->Get("hW_lep_genWithLooseLeptonVeto");
 TH2F* hW_had_gen 			= (TH2F*) histos2->Get("hW_had_gen");
 TH2F* hW_had_rec_El			= (TH2F*) histos1->Get("hW_had_rec");
 TH2F* hW_had_gen_El 			= (TH2F*) histos1->Get("hW_had_gen");
 TH2F* hW_had_genWithVeto_El		= (TH2F*) histos1->Get("hW_had_genWithVeto");
 TH2F* hW_had_genWithBVeto_El		= (TH2F*) histos1->Get("hW_had_genWithBVeto");
 TH2F* hW_had_genWithLooseLeptonVeto_El	= (TH2F*) histos1->Get("hW_had_genWithLooseLeptonVeto");
//  
 
 hWEl_gen->Print();
 hW_had_gen->Add(hW_had_gen_El);
 hW_had_genWithVeto->Add(hW_had_genWithVeto_El);
 hW_had_genWithBVeto->Add(hW_had_genWithBVeto_El);
 hW_had_genWithLooseLeptonVeto->Add(hW_had_genWithLooseLeptonVeto_El);
 hW_had_rec->Add(hW_had_rec_El);
 
  
 int nBinsX = 16;
 int nBinsY = 10;
 vector<double> BinsX={0,200,250,300,400,500,600,700,800,1000,1200,1500,2000,2500,3000,4000};
 vector<double> BinsY={0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};

 //efficiencies like in the sqrt(8) cms paper:
 //generated events kinematic cuts and vetos applied
 //reconstructed events also with all vetos and kin. cuts
 
 
 TH2* hWMuEff = GetEfficiencies(hWMu_rec,hWMu_genWithVeto);
 
 TH2* hWElEff = GetEfficiencies(hWEl_rec,hWEl_genWithVeto);
 
 TH2* hWhadEff = GetEfficiencies(hW_had_rec,hW_had_genWithVeto);
 
 TH2* hBTagEffMu = GetEfficiencies(hWMu_genWithBVeto,hWMu_gen);
 TH2* hBTagEffEl = GetEfficiencies(hWEl_genWithBVeto,hWEl_gen);
 
 TH2* hLVetoMu = GetEfficiencies(hWMu_genWithLooseLeptonVeto,hWMu_gen);
 TH2* hLVetoEl = GetEfficiencies(hWEl_genWithLooseLeptonVeto,hWEl_gen);

 TH2* hBTagEff_had = GetEfficiencies(hW_had_genWithBVeto,hW_had_gen);
 TH2* hLVeto_had = GetEfficiencies(hW_had_genWithLooseLeptonVeto,hW_had_gen);

 PrintBinContents(hWMuEff,BinsX,BinsY," W $\\rightarrow  \\mu \\nu$ and W $\\rightarrow  \\tau \\nu \\rightarrow \\mu \\nu \\nu \\nu$ efficiency");
 PrintBinContents(hWElEff,BinsX,BinsY," W $\\rightarrow  e \\nu$ and W $\\rightarrow  \\tau \\nu \\rightarrow e \\nu \\nu \\nu$ efficiency");
 if(modelName.find("Wprime")!=string::npos)
 {
 PrintBinContents(hWhadEff,BinsX,BinsY," Z $\\rightarrow  q q'$ efficiency");
 }
 else
 {
   PrintBinContents(hWhadEff,BinsX,BinsY," W $\\rightarrow  q q'$ efficiency");
 }
 
 vector<double> BVelectrons = SumOverAllFilledBins(hBTagEffEl,nBinsX,nBinsY);
 vector<double> BVmuons = SumOverAllFilledBins(hBTagEffMu,nBinsX,nBinsY);
 vector<double> LLVelectrons = SumOverAllFilledBins(hLVetoEl ,nBinsX,nBinsY);
 vector<double> LLVmuons = SumOverAllFilledBins(hLVetoMu ,nBinsX,nBinsY);
 
 vector<vector<double> > muonEff = MakeListOfWeights(hWMuEff,BinsX,BinsY);
 vector<vector<double> > electronEff = MakeListOfWeights(hWElEff,BinsX,BinsY);
 vector<vector<double> >  hadronEff = MakeListOfWeights(hWhadEff,BinsX,BinsY);
 double LLVEff = (LLVmuons[1] + LLVelectrons[1])/(LLVmuons[0]+LLVelectrons[0]);
 double BVEff = (BVmuons[1] + BVelectrons[1])/(BVmuons[0]+BVelectrons[0]);
 std::cout.precision(6);
std::cout << BVEff << std::endl;
std::cout << LLVEff << std::endl;
 
// MyClass* t12 = new MyClass(tree);
 
//vector<double> testMuon = testSelfConsistency(13,t12,muonEff,hadronEff,BVEff,LLVEff);
//vector<double> testElectron = testSelfConsistency(11,t12,electronEff,hadronEff,BVEff,LLVEff);

//std::cout << (testMuon[0]+testElectron[0])/(testMuon[1] + testElectron[1])<<std::endl; 


//========print all that stuff on canvas ==============================================
const char* title = "work in progress      #sqrt{s} = 13 TeV";
 
 
TCanvas *c1 = new TCanvas("c1","vetos on gen. and rec. events applied",400,400);
const char* channelWToMuNu = "W #rightarrow #mu #nu";  
const char* channelWToTauNu = "W #rightarrow #tau #nu #rightarrow #mu #nu #nu #nu";
SetStyleEffPlots(hWMuEff,c1,title,channelWToMuNu,channelWToTauNu);

TCanvas *c2 = new TCanvas("c2","vetos on gen. and rec. events applied",400,400);
const char* channelWToElNu = "W #rightarrow e #nu";
channelWToTauNu = "W #rightarrow #tau #nu #rightarrow e #nu #nu #nu";
SetStyleEffPlots(hWElEff,c2,title,channelWToElNu,channelWToTauNu);

TCanvas *c3 = new TCanvas("c3","vetos on gen. and rec. events applied",400,400);
const char* channelVToHad = " ";

if(modelName.find("Wprime") != string::npos)
{
  channelVToHad= "Z #rightarrow q #bar{q}";
}
else
{
  channelVToHad = "W #rightarrow q #bar{q}'";
}
SetStyleEffPlots(hWhadEff,c3,title,channelVToHad); 

  //check efficiencies for the b-tagged jets veto
 TCanvas *c5 = new TCanvas("c5","c6",800,400);
 c5->Divide(2,1);
 c5->cd(1);
  gPad->SetLeftMargin(0.15);
 gPad->SetRightMargin(0.175);
 c5->cd(2);
  gPad->SetLeftMargin(0.15);
 gPad->SetRightMargin(0.175);
  
 TCanvas *c6 = new TCanvas("c6","c6",800,400);
 c6->Divide(2,1);
 c6->cd(1);
  gPad->SetLeftMargin(0.15);
 gPad->SetRightMargin(0.175);
 c6->cd(2);
  gPad->SetLeftMargin(0.15);
 gPad->SetRightMargin(0.175);
 // check efficiency of the loose lepton veto and b-tag for hadronic W
 TCanvas *c7 = new TCanvas("c7","c7",850,400);
 c7->Divide(2,1);
 c7->cd(1);
 gPad->SetLeftMargin(0.15);
 gPad->SetRightMargin(0.175);
 c7->cd(2);
 gPad->SetLeftMargin(0.15);
 gPad->SetRightMargin(0.175);
 
  hBTagEffMu->SetTitle("muon channel: b-tagger efficiency");
    hBTagEffMu->SetMaximum(1);
    hBTagEffMu->SetMinimum(0.3);
   style2D(hBTagEffMu,"Generator p_{t}^{W} [GeV]","Generator |#eta|","b-tagger efficiency");
   c5->cd(1);
   hBTagEffMu->Draw("COLZ");
   hBTagEffEl->SetMaximum(1);
   hBTagEffEl->SetMinimum(0.3);
   hBTagEffEl->SetTitle("electron channel: b-tagger efficiency");
   style2D(hBTagEffEl,"Generator p_{t}^{W} [GeV]","Generator |#eta|","b-tagger efficiency");
   c5->cd(2);
   hBTagEffEl->Draw("COLZ");
   hLVetoMu->SetTitle("muon channel: lepton veto efficiency");
    hLVetoMu->SetMaximum(1);
    hLVetoMu->SetMinimum(0.98);
   style2D(hLVetoMu,"Generator p_{t}^{W} [GeV]","Generator |#eta|","lepton veto efficiency",1.2,1.4,2.0);
   c6->cd(1);
   hLVetoMu->Draw("COLZ");
   hLVetoEl->SetTitle("electron channel: lepton veto efficiency");
   hLVetoEl->SetMaximum(1);
   hLVetoEl->SetMinimum(0.98);
   style2D(hLVetoEl,"Generator p_{t}^{W} [GeV]","Generator |#eta|","lepton veto efficiency",1.2,1.4,2.0);
   c6->cd(2);
   hLVetoEl->Draw("COLZ");
    hBTagEff_had->SetTitle("W had : b-tagger efficiency");
   hBTagEff_had->SetMaximum(1);
   hBTagEff_had->SetMinimum(0.3);
   style2D(hBTagEff_had,"Generator p_{t}^{W} [GeV]","Generator |#eta|","b-tagger efficiency",1.2,1.4);
   c7->cd(1);
   hBTagEff_had->Draw("COLZ");
    hLVeto_had->SetTitle("W had: lepton veto efficiency");
   hLVeto_had->SetMaximum(1);
    hLVeto_had->SetMinimum(0.98);
   style2D(hLVeto_had,"Generator p_{t}^{W} [GeV]","Generator |#eta|","lepton veto efficiency",1.2,1.4,2.0);
   c7->cd(2);
   hLVeto_had->Draw("COLZ");
 
   
 string dir = "/usr/users/dschaefer/root/results/Efficiency/semileptonic/ToWW/";
 string pdfname = dir+modelName+"ToWW_"+category+"_";
 if(modelName.find("Wprime")!=string::npos)
 {
  pdfname =  "/usr/users/dschaefer/root/results/Efficiency/semileptonic/ToWZ/"+modelName+"ToWZ_"+category+"_";
 }
 
 c3->SaveAs((pdfname+"_hadEff_all_NoVetos.pdf").c_str());
 c2->SaveAs((pdfname+"_ElEff_all_NoVetos.pdf").c_str());
 c1->SaveAs((pdfname+"_MuEff_all_NoVetos.pdf").c_str());
 c5->SaveAs((pdfname+"leptonic_BVeto.pdf").c_str());
 c6->SaveAs((pdfname+"leptonic_LLVeto.pdf").c_str());
 c7->SaveAs((pdfname+"hadronic_BVeto_LLVeto.pdf").c_str());
 
}