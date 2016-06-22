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
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc2.h"
#include "/usr/users/dschaefer/root/headerfiles/passed_mu_jes.h"

using namespace std;


// note to this construct:
// is needed in this version of root in order to get the header functions right
//also the order in which these files are compiled matters!
namespace{
  int loadMyLibraryTriggerFunc(){
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/General.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/Op.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/EventSelection.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/GenFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/RecFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc2.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.cc+");

 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void allHadMakeHistosOfVariables(string ModelName, string decayMode)
{
  string dir = "/storage/jbod/dschaefer/Res_Sig/";
  vector<float> masses = {1400,1800,2000,3000,3500,4000,4500};
  string outputname = ModelName+"_"+decayMode+"_genWkin.root";
  
  TFile genVariables(outputname.c_str(),"RECREATE");
  
  TH1F* W_pt 		= new TH1F("W_pt","W_pt",100,0,4000);
  TH1F* W_eta 		= new TH1F("W_eta","W_eta",100,-4,4);
  
  TH1F* W_pt_rec	 = new TH1F("W_pt_rec","W_pt_rec",100,0,4000);
  TH1F* W_eta_rec 	= new TH1F("W_eta_rec","W_eta_rec",100,-4,4);
  
  TH1F* W_tau21 	= new TH1F("W_tau21","W_tau21",100,0,1);
  TH1F* W_prunedmass 	= new TH1F("W_prunedmass","W_prunedmass",100,0,200);
  
  //========== correlation histos ==========================================
  TH2F* ptplus_ptminus  = new TH2F("ptplus_ptminus","ptplus_ptminus",100,0,4000,100,0,4000);
  TH2F* etaplus_etaminus  = new TH2F("etaplus_etaminus","etaplus_etaminus",100,-4,4,100,-4,4);
  TH2F* tau21plus_tau21minus  = new TH2F("tau21plus_tau21minus","tau21plus_tau21minus",100,0,1,100,0,1);
  TH2F* mprunedplus_mprunedminus  = new TH2F("mprunedplus_mprunedminus","mprunedplus_mprunedminus",100,0,200,100,0,200);
  
  TH2F* pt_eta           = new TH2F("pt_eta"          ,"pt_eta"          ,100,0,4000,100,-4,4);
  TH2F* pt_tau21         = new TH2F("pt_tau21"        ,"pt_tau21"        ,100,0,4000,100,0,1);
  TH2F* pt_prunedmass    = new TH2F("pt_prunedmass"   ,"pt_prunedmass"   ,100,0,4000,100,0,200);
  TH2F* eta_tau21        = new TH2F("eta_tau21"       ,"eta_tau21"       ,100,-4,4,100,0,1);
  TH2F* eta_prunedmass   = new TH2F("eta_prunedmass"  ,"eta_prunedmass"  ,100,-4,4,100,0,200);
  TH2F* tau21_prunedmass = new TH2F("tau21_prunedmass","tau21_prunedmass",100,0,1,100,0,200);
  
  int in1=-1;
  int in2=-1;
  
  vector<float> ne_pt= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  vector<float> ne_eta={0,0,0,0,0,0,0,0,0,0};
  vector<float> negen_pt= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  vector<float> negen_eta={0,0,0,0,0,0,0,0,0,0};
  vector<float> pt = {0,200,250,300,350,400,500,600,700,800,1000,1200,1500,2000,2500,3000,4000};
  vector<float> eta = {0,0.2,0.3,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.4};
  
  for(int m=0;m<masses.size();m++)
  {
    string filename = getFileName(dir,ModelName,decayMode,masses[m],0.0,1);
    TChain tree("ntuplizer/tree");
    tree.Add(filename.c_str());
    MyClass* t12 = new MyClass(&tree);
    int howmany = t12->fChain->GetEntries();
    
  int numberMatchedEvents=0;
  int numberEventsPassedEtaCut=0;
  int numberEventsPassedPrunedMassCut=0;
  int numberEventsPassedPtCut=0;
  int numberEventsPassedTau21Cut=0;
  
    
    for(int i=0;i<howmany;i++)
    {
      t12->fChain->GetEntry(i);
      if(!genEventSelectionInclusive(t12,"jjjj")) continue;
      
      TLorentzVector W1 = getGenLV_V1(t12);
      TLorentzVector W2 = getGenLV_V2(t12);
      TLorentzVector jet;
      
      W_pt->Fill(W1.Pt());
      W_pt->Fill(W2.Pt());
      W_eta->Fill((W1.Eta()));
      W_eta->Fill((W2.Eta()));
      
      vector<float>* jet_pt = t12->jetAK8_pt;
      vector<float>* jet_eta = t12->jetAK8_eta;
      vector<float>* jet_phi = t12->jetAK8_phi;
      vector<float>* jet_e = t12->jetAK8_e;
      int Njets = t12->jetAK8_N;
      
      for(int j=0;j<Njets;j++)
      {
	float tau21 = t12->jetAK8_tau2->at(j)/t12->jetAK8_tau1->at(j);
	float prunedmass = t12->jetAK8_pruned_massCorr->at(j);
	jet.SetPtEtaPhiE(jet_pt->at(j),jet_eta->at(j),jet_phi->at(j),jet_e->at(j));
	
	if(isMatched(W1,jet))
	{
	  W_pt_rec->Fill(jet.Pt());
	  W_eta_rec->Fill((jet.Eta()));
	  W_tau21->Fill(tau21);
	  W_prunedmass->Fill(prunedmass);
	  in1=j;
	  break;
	}
      }
      for(int j=0;j<Njets;j++)
      {
	float tau21 = t12->jetAK8_tau2->at(j)/t12->jetAK8_tau1->at(j);
	float prunedmass = t12->jetAK8_pruned_massCorr->at(j);
	jet.SetPtEtaPhiE(jet_pt->at(j),jet_eta->at(j),jet_phi->at(j),jet_e->at(j));
	
	if(isMatched(W2,jet))
	{
	  W_pt_rec->Fill(jet.Pt());
	  W_eta_rec->Fill((jet.Eta()));
	  W_tau21->Fill(tau21);
	  W_prunedmass->Fill(prunedmass);
	  in2=j;
	  break;
	}
      }
      if(in1>=0 and in2>=0)
      {
	TLorentzVector jet1;
	TLorentzVector jet2;
	jet1.SetPtEtaPhiE(jet_pt->at(in1),jet_eta->at(in1),jet_phi->at(in1),jet_e->at(in1));
	jet2.SetPtEtaPhiE(jet_pt->at(in2),jet_eta->at(in2),jet_phi->at(in2),jet_e->at(in2));
	float tau21_1 = t12->jetAK8_tau2->at(in1)/t12->jetAK8_tau1->at(in1);
	float tau21_2 = t12->jetAK8_tau2->at(in2)/t12->jetAK8_tau1->at(in2);
	float prunedmass1 = t12->jetAK8_pruned_massCorr->at(in1);
	float prunedmass2 = t12->jetAK8_pruned_massCorr->at(in2);
	
	ptplus_ptminus->Fill(jet1.Pt(),jet2.Pt());
	etaplus_etaminus->Fill((jet1.Eta()),(jet2.Eta()));
	tau21plus_tau21minus->Fill(tau21_1,tau21_2);
	mprunedplus_mprunedminus->Fill(prunedmass1,prunedmass2);
	pt_eta->Fill(jet1.Pt(),(jet2.Eta()));          
	pt_tau21->Fill(jet1.Pt(),tau21_2);        
	pt_prunedmass->Fill(jet1.Pt(),prunedmass2);   
	eta_tau21->Fill((jet1.Eta()),tau21_2);       
	eta_prunedmass->Fill((jet1.Eta()),prunedmass2);  
	tau21_prunedmass->Fill(tau21_1,prunedmass2);
	
	numberMatchedEvents +=1;
	
	for(int p=0;p<ne_pt.size();p++)
	{
	if(jet1.Pt()<pt.at(p+1) and jet1.Pt()>pt.at(p))
	{
	  negen_pt.at(p)+=1;
	  if(tau21_1<0.45)
	  {
	   ne_pt.at(p)+=1; 
	  }
	}
	if(jet2.Pt()<pt.at(p+1) and jet2.Pt()>pt.at(p))
	{
	  negen_pt.at(p)+=1;
	  if(tau21_2<0.45)
	  {
	   ne_pt.at(p)+=1; 
	  }
	}
	
	}
	for(int p=0;p<ne_eta.size();p++)
	{
	  if(jet1.Eta()<eta.at(p+1) and jet1.Eta()>eta.at(p))
	  {
	   negen_eta.at(p) +=1;
	   if(tau21_1<0.45)
	   {
	    ne_eta.at(p) +=1; 
	   }
	  }
	  if(jet2.Eta()<eta.at(p+1) and jet2.Eta()>eta.at(p))
	  {
	   negen_eta.at(p) +=1;
	   if(tau21_2<0.45)
	   {
	    ne_eta.at(p) +=1; 
	   }
	  }
	  
	}
	
	if(jet1.Pt()>200 and jet2.Pt()>200)
	{
	 numberEventsPassedPtCut+=1; 
	
	if(jet1.Eta()<2.4 and jet2.Eta()<2.4)
	{
	 numberEventsPassedEtaCut+=1; 
	if((prunedmass1<105 and prunedmass1>65) and (prunedmass2<105 and prunedmass2>65))
	{
	  numberEventsPassedPrunedMassCut+=1;
	
	if(tau21_1<0.45 and tau21_2<0.45)
	{
	 numberEventsPassedTau21Cut+=1; 
	}
	}
	}
	}
      }
     in1=-1;
     in2=-1;
     
    }
    std::cout << "==========================================================="<<std::endl;
    std::cout << "======= mass = "<< masses[m] << " ============"<< std::endl;
    std::cout << "==========================================================="<<std::endl;
    std::cout << " eff pt cut | "<< numberEventsPassedPtCut/double(numberMatchedEvents) <<std::endl;
    std::cout << " eff eta cut | "<< numberEventsPassedEtaCut/double(numberEventsPassedPtCut) <<std::endl;
    std::cout << " eff tau21 cut | "<< numberEventsPassedTau21Cut/double(numberEventsPassedPrunedMassCut) <<std::endl;
    std::cout << " eff pruned mass cut | "<< numberEventsPassedPrunedMassCut/double(numberEventsPassedEtaCut) <<std::endl;
    std::cout << "==========================================================="<<std::endl;
    
  }
  for(int p=0;p<ne_pt.size();p++)
  {
   ne_pt.at(p) = ne_pt.at(p)/double(negen_pt.at(p)); 
   std::cout << pt.at(p) << " - " <<pt.at(p+1) <<": "<< ne_pt.at(p) <<std::endl;
  }
  for(int p=0;p<ne_eta.size();p++)
  {
   ne_eta.at(p) = ne_eta.at(p)/double(negen_eta.at(p)); 
   std::cout << eta.at(p) <<"-"<<eta.at(p+1)<<": "<< ne_eta.at(p) <<std::endl;
   
  }
   W_pt->Write();
   W_eta->Write();
   W_pt_rec->Write();
   W_eta_rec->Write();
   W_tau21->Write();
   W_prunedmass->Write();
   ptplus_ptminus->Write();
   etaplus_etaminus->Write();
   tau21plus_tau21minus->Write();
   mprunedplus_mprunedminus->Write();
   pt_eta->Write();         
   pt_tau21->Write();        
   pt_prunedmass->Write();   
   eta_tau21->Write();       
   eta_prunedmass->Write();  
   tau21_prunedmass->Write();
   
}