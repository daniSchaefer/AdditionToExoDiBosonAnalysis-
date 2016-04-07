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



void testEfficienciesPart2()
{
  
string ModelName = "RSGrav";
string dir = "/storage/jbod/dschaefer/testEff/";
// string Sinput_filename1 = "/storage/jbod/dschaefer/EfficiencyHistos/"+ModelName+"ToWKinematicsEl.root";
// const char* input_filename1 = Sinput_filename1.c_str();
// string Sinput_filename2 = "/storage/jbod/dschaefer/EfficiencyHistos/"+ModelName+"ToWKinematicsMu.root";
// const char* input_filename2 = Sinput_filename2.c_str();
string Sinput_filename3 = dir+ModelName+"ToWKinematicsEl_testEff.root";
string Sinput_filename4 = dir+ModelName+"ToWKinematicsMu_testEff.root";
const char* input_filename3 = Sinput_filename3.c_str();
const char* input_filename4 = Sinput_filename4.c_str();
//TFile * EffEl = new TFile(input_filename1,"READ");
//TFile * EffMu = new TFile(input_filename2,"READ");
TFile * RewEl = new TFile(input_filename3,"READ");
TFile * RewMu = new TFile(input_filename4,"READ");

TH2F* hMu_rec 		= (TH2F*) RewMu->Get("hW_lep_rec");
TH2F* hEl_rec 		= (TH2F*) RewEl->Get("hW_lep_rec");
TH2F* hHad_rec 		= (TH2F*) RewMu->Get("hW_had_rec");
TH2F* hHad2_rec		= (TH2F*) RewEl->Get("hW_had_rec");
hHad_rec->Add(hHad2_rec);
TH2F* hMu_rew 		= (TH2F*) RewMu->Get("hW_lep_rew");
TH2F* hEl_rew 		= (TH2F*) RewEl->Get("hW_lep_rew");
TH2F* hHad_rew 		= (TH2F*) RewMu->Get("hW_had_rew");
TH2F* hHad2_rew		= (TH2F*) RewEl->Get("hW_had_rew");
hHad_rew->Add(hHad2_rew);
TH2F* hMu_gen 		= (TH2F*) RewMu->Get("hW_lep_gen");
TH2F* hEl_gen 		= (TH2F*) RewEl->Get("hW_lep_gen");
TH2F* hHad_gen		= (TH2F*) RewMu->Get("hW_had_gen");
TH2F* hHad2_gen		= (TH2F*) RewEl->Get("hW_had_gen");
hHad_gen->Add(hHad2_gen);
int nBinsX =16;
int nBinsY =10;
vector<double> SumMu_rec = SumOverAllFilledBins(hMu_rec,nBinsX,nBinsY);
vector<double> SumEl_rec = SumOverAllFilledBins(hEl_rec,nBinsX,nBinsY);
vector<double> SumMu_rew = SumOverAllFilledBins(hMu_rew,nBinsX,nBinsY);
vector<double> SumEl_rew = SumOverAllFilledBins(hEl_rew,nBinsX,nBinsY);
vector<double> SumHad_rec = SumOverAllFilledBins(hHad_rec,nBinsX,nBinsY);
vector<double> SumHad_rew = SumOverAllFilledBins(hHad_rew,nBinsX,nBinsY);
vector<double> SumMu_gen = SumOverAllFilledBins(hMu_gen,nBinsX,nBinsY);
vector<double> SumEl_gen = SumOverAllFilledBins(hEl_gen,nBinsX,nBinsY);

std::cout <<"number of reconstructed events muon channel "<< SumMu_rec[1] << " : reweighted events muon channel "<<SumMu_rew[1] << std::endl;
std::cout <<"number of reconstructed events ele channel "<< SumEl_rec[1]<< "  : reweighted events ele channel " <<SumEl_rew[1] <<std::endl;
std::cout <<"number of reconstructed events hadronic channel "<< SumHad_rec[1]<<" : reweighted events hadronic channel "<<SumHad_rew[1]<<std::endl;


TCanvas *c1 = new TCanvas("c1","c1",800,800);
c1->Divide(2,2);
c1->cd(1);
hMu_rec->Draw("COLZ");
c1->cd(2);
hMu_rew->Draw("COLZ");
c1->cd(3);
hEl_rec->Draw("COLZ");
c1->cd(4);
hEl_rew->Draw("COLZ");

TCanvas *v1 = new TCanvas("v1","v1",800,800);
v1->Divide(2,2);
TH2F* RatioMu = (TH2F*) hMu_rec->Clone("RatioMu");
RatioMu->Divide(hMu_rew);
RatioMu->SetTitle("ele channel: rec. events/reweighted events");
RatioMu->SetMaximum(2.0);
TH2F* RatioEl = (TH2F*) hEl_rec->Clone("RatioEl");
RatioEl->Divide(hEl_rew);
RatioEl->SetTitle("ele channel: rec. events/reweighted events");
RatioEl->SetMaximum(2.0);
TH2F* RatioHad = (TH2F*) hHad_rec->Clone("RatioHad");
RatioHad->Divide(hHad_rew);
RatioHad->SetTitle("hadronic channel: rec. events/reweighted events");
RatioHad->SetMaximum(2.0);


v1->cd(1);
RatioMu->Draw("COLZ");
v1->cd(2);
RatioEl->Draw("COLZ");
v1->cd(3);
RatioHad->Draw("COLZ");



 
 
 
 
}