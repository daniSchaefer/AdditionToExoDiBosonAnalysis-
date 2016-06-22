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


void Efficiency( int howmany)
{
  MyClass* t12 = new MyClass(tree);
//electron muon and W pt and eta with cuts for lepton detection applied
 //here only for W->l nu_l


 cout<<"we look at the first " << howmany << " events."<<endl;


//
 //TFile kinematics("results/kinematicsVarBinSizes.root", "RECREATE");
 
 const Float_t ybinsMu[13]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4};
 const Float_t xbinsMu[10]={0,50,100,178,303,428,553,678,1000,1400};
 const Float_t ybinsEl[14]={0,0.2,0.4,0.6,0.8,1.0,1.2,1.3,1.4442,1.566,1.7,1.8,2.0,2.4};
 const Float_t xbinsEl[10]={0,115,120,200,300,400,500,600,800,1400};
 const Float_t xbinsW[12]={0,200,250,300,400,500,600,800,1000,1200,1500,2000};
 const Float_t ybinsW[10]={0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};

 // TH2F* hMu = new TH2F("hMu","gen pt over eta of mu",50,0,2000,50,0,2.5);
 //TH2F* hEl = new TH2F("hEl","gen pt over eta of el",50,0,2000,50,0,2.5);
 // TH2F* hMu_rec = new TH2F("hMu_rec","gen pt over eta of rec. mu",50,0,2000,50,0,2.5);
 //TH2F* hEl_rec = new TH2F("hEl_rec","gen pt over eta of rec. el",50,0,2000,50,0,2.5);

 TH2F* hMu_genWithVeto = new TH2F("hMu","gen p_{t} over #eta of muons",9,xbinsMu,12,ybinsMu);
 TH2F* hMu_rec = new TH2F("hMu_rec","gen p_{t} over #eta of muons",9,xbinsMu,12, ybinsMu);
 TH2F* hEl_genWithVeto = new TH2F("hEl","gen p_{t} over #eta of electrons",9, xbinsEl,13,ybinsEl);
 TH2F* hEl_rec = new TH2F("hEl_rec","gen p_{t} over #eta of rec. electrons",9,xbinsEl,13,ybinsEl);

 
     for(int counter=0;counter<howmany;counter++)
       {
	 t12->fChain->GetEntry(counter);
	 if(generatedEventSelection(11,t12)==1)
	 {
	    getKinematicsFromGeneratedEvents(hEl_genWithVeto,11,t12);
	    if(applyLeptonSelection(11,t12)==1)
	    {getKinematicsFromGeneratedEvents(hEl_rec,11,t12);}
	 }
	 if(generatedEventSelection(13,t12)==1)
	 {getKinematicsFromGeneratedEvents(hMu_genWithVeto,13,t12);
	   if(applyLeptonSelection(13,t12)==1)
	   {getKinematicsFromGeneratedEvents(hMu_rec,13,t12);}
	 }
	
       }
/*
     hEl->Write();
     hMu->Write();
     hMu_rec->Write();
     hEl_rec->Write();
     kinematics.Close();*/
    

     TCanvas* c1 = new TCanvas("c1","c1",800,1600);
     c1->Divide(2,3);     
     c1->cd(1);
      hMu_genWithVeto->Draw("COLZ");
     c1->cd(2);
     hMu_rec->Draw("COLZ");
     c1->cd(3);
     //hW_Mass_yLess0->Draw();
     hEl_genWithVeto->Draw("COLZ");
     c1->cd(4);
     hEl_rec->Draw("COLZ");
     
     //hW_Mass_yMore0->Draw();

    
}
