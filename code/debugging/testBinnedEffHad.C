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
#include "/usr/users/dschaefer/root/headerfiles/AllHadronicConstants.h"


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


void testBinnedEffHad()
{
  string inputFileRadionM2000 = "/storage/jbod/dschaefer/testEff/hadronic/ToWW/RadionToWW_jjjj_Kinematics_had_HP_M2000_width0p0_testEff.root";
  string inputFileBulkGravM2000 = "/storage/jbod/dschaefer/testEff/hadronic/ToWW/BulkGravToWW_jjjj_Kinematics_had_HP_M2500_width0p0_testEff.root";
  
  TFile* histos1 = new TFile(inputFileBulkGravM2000.c_str(),"READ");
  TFile* histos2 = new TFile(inputFileRadionM2000.c_str(),"READ");
  
  std::cout << histos1 <<std::endl;
  std::cout <<histos2 <<std::endl;
  
  
  TH2F* hRadion_Wplus = (TH2F*) histos2->Get("BinnedEffTest_plus");
  TH2F* hRadion_Wminus= (TH2F*) histos2->Get("BinnedEffTest_minus");
  
  TH2F* hBG_Wplus = (TH2F*) histos1->Get("BinnedEffTest_plus");
  TH2F* hBG_Wminus = (TH2F*) histos1->Get("BinnedEffTest_minus");
  
  std::cout<< hRadion_Wminus <<std::endl;
  std::cout<< hRadion_Wplus <<std::endl;
  std::cout << hBG_Wminus <<std::endl;
  std::cout << hBG_Wplus <<std::endl;
  
  TCanvas* c1 = new TCanvas("c1","c1",800,800);
  c1->Divide(2,2);
  c1->cd(1);
  gPad->SetRightMargin(0.15);
  hRadion_Wplus->SetTitle("radion Wplus");
  hRadion_Wplus->Draw("COLZ");
  c1->cd(2);
  gPad->SetRightMargin(0.15);
  hRadion_Wminus->SetTitle("radion Wminus");
  hRadion_Wminus->Draw("COLZ");
  c1->cd(3);
  gPad->SetRightMargin(0.15);
  hBG_Wplus->SetTitle("bulk g Wplus");
  hBG_Wplus->Draw("COLZ");
  c1->cd(4);
  gPad->SetRightMargin(0.15);
  hBG_Wminus->SetTitle("bulk g Wminus");
  hBG_Wminus->Draw("COLZ");
  
  vector<double> BinsX = ALLHADBINNINGX;
  vector<double> BinsY = ALLHADBINNINGY;
  int NBinsX = ALLHADNBINSX;
  int NBinsY = ALLHADNBINSY;
  
  vector<double> ALL_Radion_Wplus = SumOverAllFilledBins(hRadion_Wplus,NBinsX,NBinsY);
  vector<double> ALL_Radion_Wminus = SumOverAllFilledBins(hRadion_Wminus,NBinsX,NBinsY);
  
   vector<double> ALL_BG_Wplus = SumOverAllFilledBins(hBG_Wplus,NBinsX,NBinsY);
  vector<double> ALL_BG_Wminus = SumOverAllFilledBins(hBG_Wminus,NBinsX,NBinsY);
  
  PrintBinContents(hRadion_Wplus,BinsX,BinsY,"Radion Wplus");
  PrintBinContents(hRadion_Wminus,BinsX,BinsY, "Radion Wminus");
  PrintBinContents(hBG_Wplus,BinsX,BinsY,"BG Wplus");
  PrintBinContents(hBG_Wminus,BinsX,BinsY, "BG Wminus");
  
  std::cout<< ALL_Radion_Wplus[1]/ALL_Radion_Wplus[0] <<std::endl;
  std::cout<< ALL_Radion_Wminus[1]/ALL_Radion_Wminus[0] <<std::endl;
  std::cout<< ALL_BG_Wplus[1]/ALL_BG_Wplus[0] <<std::endl;
  std::cout<< ALL_BG_Wminus[1]/ALL_BG_Wminus[0] <<std::endl;
  
}