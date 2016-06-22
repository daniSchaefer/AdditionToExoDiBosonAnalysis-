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
//#include "/usr/users/dschaefer/root/headerfiles/MyClass.h"
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





//-----------------------------------------------------------------------------
//---------------------Main function begins here-------------------------------

void lookAtParticleTree1(int which, int howmany)
{
  
//------------------------------------------------------------------------------
 

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
    

 // cout<< "we look at the first "<< howmany << " events "<< endl;
 // vector<int> event={3,5,7};
 // get_pdgId(event,"test.txt",tree);

 vector<vector<int> > new_result = generatedSemiLepEventClassification(howmany,tree);
 vector<int> EventWithEl = new_result[4];
 vector<int> EventWithMu = new_result[5];
 vector<int> EventWithTau = new_result[6];

 
 cout << EventWithEl.size() << " # of el"<< endl;

 cout << EventWithMu.size() << " # of mu"<< endl;

 cout << EventWithTau.size() << " # of tau"<< endl;



 // tau decay branching ratio:


 vector<int> TauBratio3= getTauBranchingRatio(EventWithTau,tree); 
 cout<<" Tau into e(+/-) decays "<< TauBratio3[0]<< endl;
 cout <<" Tau into mu(+/-) decays "<<  TauBratio3[1]<< endl;

 cout<< "Branching ratio e: " << (TauBratio3[0])/float(EventWithTau.size())*100 << endl;
 cout<< "Branching ratio mu: " << (TauBratio3[1])/float(EventWithTau.size())*100 << endl;


 // // test getKinematicsFromGeneratedEvents
 // if(which==8)
 //   {
     vector<int> events ={};
     for(int  i=0;i<howmany;i++)
       {events.push_back(i);}

     TH1F* histo1 = new TH1F("histo1"," pseudorapidity",80,-3,3);
     TH1F* histo2 = new TH1F("histo2","pt",100,0,1000);

     TH1F* histo3 = new TH1F("histo3"," pseudorapidity",80,-3,3);
     TH1F* histo4 = new TH1F("histo4","pt",100,0,1000);
    

     getKinematicsFromGeneratedEvents(histo1,histo2,events,13,tree);
     getKinematicsFromGeneratedEvents(histo3,histo4,events,11,tree);
     TCanvas* c1=new TCanvas("c1","c1",1600,1600);
     c1->Divide(2,2);
     c1->cd(1);
     histo1->Draw();
     c1->cd(2);
     histo2->Draw();
     c1->cd(3);
     histo3->Draw();
     c1->cd(4);
     histo4->Draw();
 //   }


}


