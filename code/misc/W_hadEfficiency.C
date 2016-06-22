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


void W_hadEfficiency(int howmany)
{
  MyClass* t12 = new MyClass(tree);
//electron muon and W pt and eta with cuts for lepton detection applied
 //here only for W->l nu_l

// selection criteria for leptons
vector<vector<double> > leptonSelection_loose(4, vector<double> (3));
vector<vector<double> > leptonSelection_tight(4, vector<double> (3));
for(int m=0;m<4;m++){for(int m1=0;m1<3;m1++)
    {leptonSelection_loose[m][m1]=0;leptonSelection_tight[m][m1]=0;}}
// order:  leptonSelection[0][x]= electron pt bounds
leptonSelection_loose[0][0]= 35;
leptonSelection_tight[0][0]= 120;
//         leptonSelection[1][x]= muon pt bounds
leptonSelection_loose[1][0]= 20;
leptonSelection_tight[1][0]= 53;
//         leptonSelection[2][x]= electron eta bounds
leptonSelection_loose[2][0]= 2.5;
leptonSelection_loose[2][1]= 1.4442;
leptonSelection_loose[2][2]= 1.566;

leptonSelection_tight[2][0]= 2.5;
leptonSelection_tight[2][1]= 1.4442;
leptonSelection_tight[2][2]= 1.566;
//         leptonSelection[3][x]= muon eta bounds
leptonSelection_loose[3][0]= 2.4;
leptonSelection_tight[3][0]= 2.1;

cout<<"we look at the first " << howmany << " events."<<endl;

//point of this function:
//write Pt over Eta for the leptonically and hadronically decaying W boson for electrons or muons 
//make the following distinctions:
//hWMu = All generated Events with Muons in final state i.e W-> mu,nu and W-> tau,nu -> mu, nu, nu, nu
//hWMu_rec = Muon Channel with all leptonic and B tagging Cuts and Vetos applied
//hWMu_NoVeto = with no Veto on reconstructed Events
//hWMu_NoLooseLeptonVeto  = with no 2nd loose lepton veto
//hWMu_NoBVeto = with no B-tagged jet veto

TFile Wkinematics("results/W_hadkinematics.root","RECREATE");

//same for Electron decay channel
 const Float_t xbinsW[14]={0,200,250,300,400,500,600,700,800,1000,1200,1500,2000,2500};
 const Float_t ybinsW[10]={0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};
 
 TH2F* hW_had = new TH2F("hW_had","hadronic W decay",13,xbinsW,9,ybinsW);
 TH2F* hW_had_genWithVeto = new TH2F("hW_had_genWithVeto","hadronic W decay",13,xbinsW,9,ybinsW);
 TH2F* hW_had_rec = new TH2F("hW_had_rec","hadronic W decay",13,xbinsW,9,ybinsW);
 
 TLorentzVector W_lep;
 TLorentzVector W_had;
 for(int i=0;i<howmany;i++)
   {
     getGenWKinematics(hW_had,i,0,t12);
     if(generatedEventSelection(i,11,t12)==0 and generatedEventSelection(i,13,t12)==0)
	continue;
     if(applyVetos(i,11,t12)==0 and applyVetos(i,13,t12)==0 )
	continue;
     getGenWKinematics(hW_had_genWithVeto,i,0,t12);
     if(applyHadronSelection(i,t12)==0)
	continue;
     W_had =reconstructHadronicW(i,t12);
     if(W_had.Pt()<200)
	continue;
	//back to back topology missing!!
     getGenWKinematics(hW_had_rec,i,0,t12);    
   }

 hW_had_genWithVeto->Write();
 hW_had->Write();
 hW_had_rec->Write();
 Wkinematics.Close();

}
