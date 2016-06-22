#include "MyClass.h"
#include "RecFunc.h"
#include "Op.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1F.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "WWConstants.h"


//=============================================================================
//============== reconstruct Boson for all hadronic channel ===================
//=============================================================================
TLorentzVector reconstructV1(MyClass* t12)
{
      TLorentzVector jet1;
      vector<int> cand = hadronicJetCandidates(t12);
      vector<float>* jet_pt = t12->jetAK8_pt;
      vector<float>* jet_eta = t12->jetAK8_eta;
      vector<float>* jet_phi = t12->jetAK8_phi;
      vector<float>* jet_e = t12->jetAK8_e;
      jet1.SetPtEtaPhiE(jet_pt->at(cand[0]),jet_eta->at(cand[0]),jet_phi->at(cand[0]),jet_e->at(cand[0]));
  return jet1;
}
TLorentzVector reconstructV2(MyClass* t12)
{
      TLorentzVector jet1;
      vector<int> cand = hadronicJetCandidates(t12);
      vector<float>* jet_pt = t12->jetAK8_pt;
      vector<float>* jet_eta = t12->jetAK8_eta;
      vector<float>* jet_phi = t12->jetAK8_phi;
      vector<float>* jet_e = t12->jetAK8_e;
      jet1.SetPtEtaPhiE(jet_pt->at(cand[1]),jet_eta->at(cand[1]),jet_phi->at(cand[1]),jet_e->at(cand[1]));
  return jet1;
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
TLorentzVector reconstructLepton(int pdgId, MyClass* t12)
{
  TLorentzVector l;
  if(pdgId ==11)
    {
      for(int i=0;i< t12->el_N;i++)
	{
	  if(isTightElectron(i,t12)==0) continue;
	  Double_t  pt = t12->el_pt->at(i);
	  Double_t  phi = t12->el_phi->at(i);
	  Double_t  eta = t12->el_eta->at(i);
	  Double_t  e = t12->el_e->at(i);
	  l.SetPtEtaPhiE(pt,eta,phi,e);

	}
    }

  if(pdgId ==13)
    {
      for(int i=0;i< t12->mu_N;i++)
	{
	  if(isTightMuon(i,t12)==0) continue;
	   
	  Double_t  pt = t12->mu_pt->at(i);
	  Double_t  phi = t12->mu_phi->at(i);
	  Double_t  eta = t12->mu_eta->at(i);
	  Double_t  e = t12->mu_e->at(i);
	  l.SetPtEtaPhiE(pt,eta,phi,e);
	  
	}
    }
    return l;
}
 
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
TLorentzVector recNeutrino(Double_t MET,Double_t MET_phi ,TLorentzVector lepton)
{
 
  Double_t  M_W= 80.42;
  Double_t pz_nu =0;
  Double_t phi= lepton.Phi();
  Double_t pt= lepton.Pt();
  Double_t pz = lepton.Pz();
  Double_t E= lepton.E();
  Double_t mu = pow(M_W,2)/2.0 + TMath::Cos(-(phi-MET_phi))*MET*pt;
  Double_t b = mu*pz/double(pow(pt,2));
  Double_t c = (pow(E,2)*pow(MET,2)-pow(mu,2))/double(pow(pt,2));
  Double_t y= pow(b,2)-c;
  TLorentzVector neutrino;


  if(y<0)
    {
      pz_nu = b;
    }
  if(y>0)
    {
      Double_t a1= b + TMath::Sqrt(y);
      Double_t a2 = b - TMath::Sqrt(y);
      if(TMath::Abs(a1)>TMath::Abs(a2))
	pz_nu= a2;
      else if(TMath::Abs(a2)>TMath::Abs(a1))
	pz_nu = a1;
    }
  neutrino.SetE(TMath::Sqrt(pow(MET,2) + pow(pz_nu,2)));
  neutrino.SetPz(pz_nu);
  neutrino.SetPx(MET*TMath::Cos(MET_phi));
  neutrino.SetPy(MET*TMath::Sin(MET_phi));
  return neutrino;
} 




//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

TLorentzVector reconstructLeptonicW(int pdgIdLepton,MyClass* t12)
{
  TLorentzVector W;
  TLorentzVector l;
  TLorentzVector n;
  
  l= reconstructLepton(pdgIdLepton,t12);
  n= recNeutrino(t12->MET_et->at(0),t12->MET_phi->at(0),l);
  
  W = l+n;
  return W;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
TLorentzVector reconstructHadronicWOrZ(MyClass *t12,bool isW, bool isZ)
{
  
  TLorentzVector W;
  
  int Candidate =-99;
  for(int i=0;i<t12->jetAK8_N;i++)
  {
     if( !isRightAK8jet(i,t12) ) continue;
     Candidate = i;
     break;
    
   }
   double MassMin=0;	
   double MassMax=0;
   if(isW and !isZ){MassMin = WWAK8JETMASSMIN; MassMax = WWAK8JETMASSMAX;}
   if(!isW and isZ){MassMin = WZAK8JETMASSMIN; MassMax = WZAK8JETMASSMAX;}
   if(!isW and !isZ){}
   if(isW and isZ){MassMin =WWAK8JETMASSMIN; MassMax = WZAK8JETMASSMAX;}
   if(Candidate>=0)
   {
   if( (t12->jetAK8_pruned_massCorr->at(Candidate)> MassMin and t12->jetAK8_pruned_massCorr->at(Candidate)<MassMax))
   {
      Double_t pt = t12->jetAK8_pt->at(Candidate); 
      Double_t eta = t12->jetAK8_eta->at(Candidate);
      Double_t phi = t12->jetAK8_phi->at(Candidate);
      Double_t e = t12->jetAK8_e->at(Candidate);
      W.SetPtEtaPhiE(pt,eta,phi,e);
   }
   }
   return W;
}

//================================================================================



