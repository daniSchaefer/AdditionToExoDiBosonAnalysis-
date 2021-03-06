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
#include "/usr/users/dschaefer/root/headerfilesAllChannels/CMS_lumi.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/tdrstyle.C"
#include "TStyle.h"
#include "/usr/users/dschaefer/root/headerfiles/WWConstants.h"
#include "/usr/users/dschaefer/root/headerfiles/AllHadronicConstants.h"

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
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/CMS_lumi.C+");
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}


// const char* input_filename6 = "/storage/a/mmozer/Res_Sig/BulkGravToWWToWlepWhad_narrow_M_2000/EXOVVTree_BulkGravToWWToWlepWhad_narrow_M_2000_1.root";
// const char* input_filename6 ="/storage/a/mmozer/Res_Sig/WprimeToWZToWlepZhad_narrow_M-2000/EXOVVTree_WprimeToWZToWlepZhad_narrow_M-2000_1.root";
// 
// TFile *gendata = new TFile(input_filename6,"READ");
// TTree *tree = (TTree*) gendata->Get("ntuplizer/tree");

void get2DEffW(string modelName, string category, string decayMode= "WW_lvjj")
{
  
 // gROOT->LoadMacro("/usr/users/dschaefer/root/headerfilesAllChannels/tdrstyle.C");
  //setTDRStyle();
  string VV = determineVV(decayMode);
  string mode = determineSemilepHadOrLep(decayMode);
  string Vlep = "W";
  string Vhad = "W";
  if(VV.find("ZZ")!=string::npos)
  {
    Vlep = "Z";
    Vhad = "Z";
  }
  if(VV.find("WZ")!=string::npos)
  {
    Vlep = "W";
    Vhad = "Z";
  }
  
  
if(decayMode.find("lvjj")!=string::npos)
{
  //  string Sinput_filename1 = "/storage/jbod/dschaefer/EfficiencyHistos/"+mode+"/To"+VV+"/"+modelName+"To"+VV+"Kinematics_el_"+category+".root";
  //  string Sinput_filename2 = "/storage/jbod/dschaefer/EfficiencyHistos/"+mode+"/To"+VV+"/"+modelName+"To"+VV+"Kinematics_mu_"+category+".root";
  string Sinput_filename1 = determineFileName("EfficiencyHistos",modelName,"el",category,decayMode);
  string Sinput_filename2 = determineFileName("EfficiencyHistos",modelName,"mu",category,decayMode);
  

  string VToX1 =Vlep+"$\\rightarrow  \\mu \\nu$ and"+Vlep+" $\\rightarrow  \\tau \\nu \\rightarrow \\mu \\nu \\nu \\nu$ efficiency";
  string VToX2 = Vlep+" $\\rightarrow  e \\nu$ and"+Vlep+" $\\rightarrow  \\tau \\nu \\rightarrow e \\nu \\nu \\nu$ efficiency";
  string VToX3 = Vhad+" $\\rightarrow  q q'$ efficiency";
 
  string SchannelWToMuNu =  Vlep+" #rightarrow #mu #nu";  
  string SchannelWToTauNuMu = Vlep+" #rightarrow #tau #nu #rightarrow #mu #nu #nu #nu";
  string SchannelWToElNu =   Vlep+" #rightarrow e #nu";
  string SchannelWToTauNuEl = Vlep+" #rightarrow #tau #nu #rightarrow e #nu #nu #nu";
  string SchannelVToHad = Vhad+" #rightarrow q #bar{q}'";
  
  const char* channelWToMuNu = 	   SchannelWToMuNu.c_str();	
  const char* channelWToTauNuMu =    SchannelWToTauNuMu.c_str(); 
  const char* channelWToElNu = 	   SchannelWToElNu.c_str();	
  const char* channelWToTauNuEl =    SchannelWToTauNuEl.c_str(); 
  const char* channelVToHad = 	   SchannelVToHad.c_str(); 	
  
  const char* input_filename1 = Sinput_filename1.c_str();
  const char* input_filename2 = Sinput_filename2.c_str();
  TFile * histos1 = new TFile(input_filename1,"READ");
  TFile * histos2 = new TFile(input_filename2,"READ");
  float wtagging = 1.007; //74x V5
  float wtaggingErr = 0.028;
    
    
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
  
  //hW_had_rec->Scale(wtagging);
  
  int nBinsX = 16;
  int nBinsY = 10;
  vector<double> BinsX=BINNINGX;
  //{0,200,250,300,400,500,600,700,800,1000,1200,1500,2000,2500,3000,4000};
  vector<double> BinsY= BINNINGY;//{0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};

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

  hWhadEff->Scale(wtagging);
  
  PrintBinContents(hWMuEff,BinsX,BinsY,VToX1.c_str());
  PrintBinContents(hWElEff,BinsX,BinsY,VToX2.c_str());
  PrintBinContents(hWhadEff,BinsX,BinsY,VToX3.c_str());
 
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
  //const char* title = "work in progress      #sqrt{s} = 13 TeV";
  const char* title = "";//"preliminary";

  int H_ref = 400; 
  int W_ref = 400; 
  int W = 400;
  int H = 400;
  
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

  const char* canvName="canv";

  TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);
  SetStyleEffPlots(hWMuEff,canv,title,channelWToMuNu,channelWToTauNuMu);
//pad1->Update();
  CMS_lumi(canv,4,0); 





  TCanvas* c1 = new TCanvas("c1","c1",50,50,W,H);
  SetStyleEffPlots(hWMuEff,c1,title,channelWToMuNu,channelWToTauNuMu);

  




  TCanvas *c2 = new TCanvas("c2","vetos on gen. and rec. events applied",400,400);
  SetStyleEffPlots(hWElEff,c2,title,channelWToElNu,channelWToTauNuEl);
  TCanvas *c3 = new TCanvas("c3","vetos on gen. and rec. events applied",400,400);
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
if(decayMode.find("jjjj")!=string::npos)
{
  
  string Sinput_had = determineFileName("EfficiencyHistos",modelName,"had",category,decayMode);

  string VToHad = Vhad+" $\\rightarrow  q q'$ efficiency";
  string SchannelVToHadplus = Vhad+"^{+} #rightarrow q #bar{q}'";
  string SchannelVToHadminus = Vhad+"^{-} #rightarrow q #bar{q}'";
  
  const char* channelVToHadplus = SchannelVToHadplus.c_str();
  const char* channelVToHadminus = SchannelVToHadminus.c_str(); 
  const char* input_had = Sinput_had.c_str();
  
  float  wtaggingHP = 0.951;
  
  TFile * histos1 = new TFile(input_had,"READ");    
    
  TH2F* hhad_Wtag_rec	= (TH2F*) histos1->Get("hhad_Wtag_rec");
  TH2F* hhad_Wtag_gen 	= (TH2F*) histos1->Get("hhad_Wtag_gen");
  TH2F* hhad_Ztag_rec 	= (TH2F*) histos1->Get("hhad_Ztag_rec");
  TH2F* hhad_Ztag_gen	= (TH2F*) histos1->Get("hhad_Ztag_gen");
  TH2F* hhad_WZtag_rec	= (TH2F*) histos1->Get("hhad_WZtag_rec");
  TH2F* hhad_WZtag_gen	= (TH2F*) histos1->Get("hhad_WZtag_gen");
  TH2F* hhad_Vtag_rec	= (TH2F*) histos1->Get("hhad_rec");
  TH2F* hhad_Vtag_gen	= (TH2F*) histos1->Get("hhad_gen");
  
  TH2F* h_jet1_denominator = (TH2F*) histos1->Get("h_jet1_denominator");
  TH2F* h_jet1_numerator = (TH2F*) histos1->Get("h_jet1_numerator");
  TH2F* h_jet2_denominator = (TH2F*) histos1->Get("h_jet2_denominator");
  TH2F* h_jet2_numerator = (TH2F*) histos1->Get("h_jet2_numerator");
  
 
  //int nBinsX = 16;//ALLHADNBINSX;
  //int nBinsY = 10;//ALLHADNBINSY;
  vector<double> BinsX= ALLHADBINNINGX;
  vector<double> BinsY= ALLHADBINNINGY;
  int nBinsX = BinsX.size();
  int nBinsY = BinsY.size();
  
  vector<double> BinsXNew= ALLHADBINNINGXBOTHJETS;
  vector<double> BinsYNew= ALLHADBINNINGYBOTHJETS;
  int nBinsXNew = BinsXNew.size();
  int nBinsYNew = BinsYNew.size();
  
 
  TH2* Eff_Vtag = GetEfficiencies(hhad_Vtag_rec,hhad_Vtag_gen);
  TH2* Eff_Wtag = GetEfficiencies(hhad_Wtag_rec,hhad_Vtag_gen);
  TH2* Eff_Ztag = GetEfficiencies(hhad_Ztag_rec,hhad_Vtag_gen);
  TH2* Eff_WZtag = GetEfficiencies(hhad_WZtag_rec,hhad_Vtag_gen); 
  
    TH2* jet1Eff = GetEfficiencies(h_jet1_numerator,h_jet1_denominator);
    TH2* jet2Eff = GetEfficiencies(h_jet2_numerator,h_jet2_denominator);
    jet1Eff->Scale(wtaggingHP);
    jet2Eff->Scale(wtaggingHP);
  
  std::cout <<Eff_Vtag <<std::endl;
  std::cout << Eff_Wtag  <<std::endl;
  std::cout << Eff_Ztag  <<std::endl;
  std::cout << Eff_WZtag <<std::endl;
  
   std::cout << jet1Eff <<std::endl;
   std::cout << jet2Eff <<std::endl;

  //========print all that stuff on canvas ==============================================
  //const char* title = "work in progress      #sqrt{s} = 13 TeV";
  const char* title = "";//"preliminary";
  string channelAllHad = "WW #rightarrow q #bar{q}'q #bar{q}'";
  string namehad = "W #rightarrow q #bar{q}'";
  if(decayMode.find("WZ")!=string::npos)
  {
    channelAllHad = "WZ #rightarrow q #bar{q}'q #bar{q}'";
  }
  if(decayMode.find("ZZ")!=string::npos)
  {
   channelAllHad = "ZZ #rightarrow q #bar{q}'q #bar{q}'";
   namehad = "Z #rightarrow q #bar{q}";
  }
  
  TCanvas* c1 = new TCanvas("c1","c1",400,400);
  SetStyleEffPlotsAllHad(Eff_Vtag,c1,title,channelAllHad.c_str(),2500);

  TCanvas *c2 = new TCanvas("c2","c2",400,400);
  SetStyleEffPlotsAllHad(Eff_Wtag,c2,title,channelAllHad.c_str(),2500);
  TCanvas *c3 = new TCanvas("c3","c3",400,400);
  SetStyleEffPlotsAllHad(Eff_Ztag,c3,title,channelAllHad.c_str(),2500); 
  TCanvas *c4 = new TCanvas("c4","c4",400,400);
  SetStyleEffPlotsAllHad(Eff_WZtag,c4,title,channelAllHad.c_str(),2500); 
  
  TCanvas* c5 = new TCanvas("c5","c5",400,400);
  SetStyleEffPlotsAllHad(jet1Eff,c5,title,channelVToHadplus); 
  TCanvas* c6 = new TCanvas("c6","c6",400,400);
  SetStyleEffPlotsAllHad(jet2Eff,c6,title,channelVToHadminus);
  
  TCanvas* c7 = new TCanvas("c7","c7",800,800);
  c7->Divide(2,2);
  c7->cd(1);
  gPad->SetRightMargin(0.15);
  h_jet1_denominator->Draw("COLZ");
  c7->cd(2);
   gPad->SetRightMargin(0.15);
  h_jet1_numerator->Draw("COLZ");
  c7->cd(3);
   gPad->SetRightMargin(0.15);
  h_jet2_denominator->Draw("COLZ");
  c7->cd(4);
   gPad->SetRightMargin(0.15);
  h_jet2_numerator->Draw("COLZ");
  
  TCanvas* c8 = new TCanvas("c8","c8",400,400);
  c8->cd(1);
  TH2* Ratio = (TH2*) jet1Eff->Clone("Ratio");
  Ratio->Divide(jet2Eff);
  Ratio->SetMaximum(2);
  Ratio->Draw("COLZ");
  
  TCanvas* ceff_ges = new TCanvas("ceff_ges","ceff_ges",400,400);
  ceff_ges->cd(1);
  h_jet1_numerator->Add(h_jet2_numerator);
  h_jet1_denominator->Add(h_jet2_denominator);
  TH2* Eff_ges = GetEfficiencies(h_jet1_numerator,h_jet1_denominator);
  SetStyleEffPlotsAllHad(Eff_ges,ceff_ges,title,namehad.c_str());
  Eff_ges->Scale(wtaggingHP);
  
  
 vector<double> SumHad = SumOverAllFilledBins(Eff_Vtag,nBinsX,nBinsY);
 std::cout << "eff " << SumHad[1]/SumHad[0] <<std::endl;
  PrintBinContents(Eff_Vtag,BinsXNew,BinsYNew,VToHad.c_str());
  PrintBinContents(Eff_Ztag,BinsXNew,BinsYNew,VToHad.c_str());
  PrintBinContents(Eff_Wtag,BinsXNew,BinsYNew,VToHad.c_str());
  PrintBinContents(Eff_WZtag,BinsXNew,BinsYNew,VToHad.c_str());
  PrintBinContents(jet1Eff,BinsX,BinsY,"efficiency Wplus ");
  PrintBinContents(jet2Eff,BinsX,BinsY,"efficiency Wminus ");
  
  PrintBinContents(h_jet1_numerator,BinsX,BinsY,"W plus numerator");
  PrintBinContents(h_jet1_denominator,BinsX,BinsY,"W plus denominator");
  PrintBinContents(h_jet2_numerator,BinsX,BinsY,"W minus numerator");
  PrintBinContents(h_jet2_denominator,BinsX,BinsY,"W minus denominator");
  
  PrintBinContents(Eff_ges,BinsX,BinsY,"all");
  
  
  
  string dir = "/usr/users/dschaefer/root/results/Efficiency/"+mode+"/To"+VV+"/";
  string pdfname = dir+modelName+"To"+VV+"_"+category+"_";
  
  c1->SaveAs((pdfname+"_Vtag.pdf").c_str());
  c2->SaveAs((pdfname+"_Wtag.pdf").c_str());
  c3->SaveAs((pdfname+"_Ztag.pdf").c_str());
  c4->SaveAs((pdfname+"_WZtag.pdf").c_str());
  c5->SaveAs((pdfname+"_jet1.pdf").c_str());
  c6->SaveAs((pdfname+"_jet2.pdf").c_str());
  ceff_ges->SaveAs((pdfname+"_all.pdf").c_str());
  
  
}
 
}