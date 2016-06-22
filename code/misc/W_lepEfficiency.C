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
#include "/usr/users/dschaefer/root/headerfiles/MyClass.h"
#include "/usr/users/dschaefer/root/headerfiles/Op.h"
#include "/usr/users/dschaefer/root/headerfiles/EventSelection.h"
#include "/usr/users/dschaefer/root/headerfiles/GenFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/RecFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"

using namespace std;

 const char* filename = "data/EXOVVTree_BulkGravToWWToWlepWhad_narrow_M_1200_1.root";

TFile *gendata = new TFile(filename,"READ");
TTree *tree = (TTree*) gendata->Get("ntuplizer/tree");

// note to this construct:
// is needed in this version of root in order to get the header functions right
//also the order in which these files are compiled matters!
namespace{
  int loadMyLibraryTriggerFunc(){
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/Op.cc");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/EventSelection.cc");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/GenFunc.cc");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/RecFunc.cc");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C");
 // gROOT->ProcessLine(".L testheader2.cc");
 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}
//_--------------------------------------------------------------------------
//---------------------main function-----------------------------------------


void W_lepEfficiency(int pdgId, int howmany)
{
  MyClass* t12 = new MyClass(tree);
//electron muon and W pt and eta with cuts for lepton detection applied
 //here only for W->l nu_l

cout<<"we look at the first " << howmany << " events."<<endl;

//point of this function:
//write Pt over Eta for the leptonically decaying W bosons in file "WKinematics.root"
//make the following distinctions:
//hWMu = All generated Events with Muons in final state i.e W-> mu,nu and W-> tau,nu -> mu, nu, nu, nu
//hWMu_rec = Muon Channel with all leptonic and B tagging Cuts and Vetos applied
//hWMu_NoVeto = with no Veto on reconstructed Events
//hWMu_NoLooseLeptonVeto  = with no 2nd loose lepton veto
//hWMu_NoBVeto = with no B-tagged jet veto
const char* filename =0;
if(pdgId==11)
{
  filename ="results/W_lepKinematicsEl.root";
}
if(pdgId==13)
{
  filename ="results/W_lepKinematicsMu.root";
}

TFile Wkinematics(filename, "RECREATE");
//same for Electron decay channel
 const Float_t xbinsW[13]={0,200,250,300,400,500,600,700,800,1000,1200,1500,2000};
 const Float_t ybinsW[10]={0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};
 
 TH2F* hW = new TH2F("hW","W #rightarrow l #nu_{l}",12,xbinsW,9,ybinsW);
 TH2F* hW_genWithVeto = new TH2F("hW_genWithVeto","W #rightarrow l #nu_{l}",12,xbinsW,9,ybinsW);
 TH2F* hW_rec = new TH2F("hW_rec","W #rightarrow l #nu_{l}, all vetos",12,xbinsW,9,ybinsW);
 TH2F* hW_NoVeto = new TH2F("hW_NoVeto","W #rightarrow l #nu_{l}, no vetos",12,xbinsW,9,ybinsW);
 TH2F* hW_NoBVeto = new TH2F("hW_NoBVeto","W #rightarrow l #nu_{l}, with loose lepton veto",12,xbinsW,9,ybinsW);
 TH2F* hW_NoLooseLeptonVeto = new TH2F("hW_NoLooseLeptonVeto","W #rightarrow l #nu_{l}, with b-tagged AK4 jet veto",12,xbinsW,9,ybinsW);


 TLorentzVector W;

 for(int i=0;i<howmany;i++)
   {
     t12->fChain->GetEntry(i);
     getGenWKinematics(hW,pdgId,t12);
     if(generatedEventSelection(pdgId,t12)==0)
       continue;
     
     if(applyVetos(pdgId,t12)==1)
	{
	  getGenWKinematics(hW_genWithVeto,pdgId,t12);
	}
     if(applyLeptonSelection_NoBVeto_NoLooseLeptonVeto(pdgId,t12)==0)
       continue;
     W = reconstructLeptonicW(pdgId,t12);
     if(W.Pt()<200)
       continue;
     getGenWKinematics(hW_NoVeto,pdgId,t12);
     if(applyLeptonSelection_NoBVeto(pdgId,t12))
      {
	 getGenWKinematics(hW_NoBVeto,pdgId,t12);
      }
     if(applyLeptonSelection_NoLooseLeptonVeto(pdgId,t12))
       {
	 getGenWKinematics(hW_NoLooseLeptonVeto,pdgId,t12);
	}
     if(applyLeptonSelection(pdgId,t12))
       {
	 getGenWKinematics(hW_rec,pdgId,t12);
       }
    
       
   }

 hW->Write();
 hW_rec->Write();
 hW_NoVeto->Write();
 hW_NoBVeto->Write();
 hW_NoLooseLeptonVeto->Write();
 hW_genWithVeto->Write();
 Wkinematics.Close();

}
