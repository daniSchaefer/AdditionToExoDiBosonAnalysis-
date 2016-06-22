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
#include "headerfiles/StyleFunc.h"


using namespace std;

namespace{
  int loadMyLibraryTriggerFunc(){
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc");
 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

TFile * histos = new TFile("results/W_hadkinematics.root","READ");

void get2DEffW_had()
{
 TH2F* hW_had 			= (TH2F*) histos->Get("hW_had");
 TH2F* hW_had_rec 		= (TH2F*) histos->Get("hW_had_rec");
 TH2F* hW_had_genWithVeto 	= (TH2F*) histos->Get("hW_had_genWithVeto");
 
 
 //efficiencies like in the sqrt(8) cms paper:
 //generated events kinematic cuts and vetos applied
 //reconstructed events with all hadronic cuts but no back to back topology jet
 TCanvas *c3 = new TCanvas("c3","vetos on gen. and rec. events applied",800,400);
 c3->Divide(2,1);
 c3->cd(1);
 gPad->SetRightMargin(0.15);
 c3->cd(2);
 
 TEfficiency* W_hadEff_wV=0;
 
 if(TEfficiency::CheckConsistency(*hW_had_rec,*hW_had_genWithVeto))
 {
   W_hadEff_wV=new TEfficiency(*hW_had_rec,*hW_had_genWithVeto);
   TH2* hW_hadEff_wV = W_hadEff_wV->CreateHistogram();
   hW_hadEff_wV->SetTitle("W #rightarrow q q^{,}");
   style2D(hW_hadEff_wV,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
   c3->cd(1);
   hW_hadEff_wV->Draw("COLZ");
 }
}