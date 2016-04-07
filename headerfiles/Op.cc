#include "TChain.h"
#include "TTree.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "TLorentzVector.h"
#include "WWConstants.h"
#include "Op.h"
#include "MyClass.h"
#include "AllHadronicConstants.h"

//------------------------------------------------------------------------------
//----------------------------------------------------------------------------

TLorentzVector getLorentzVector( int particleNumber, MyClass* t12)
{
 
  TLorentzVector V;
 
 Double_t pt  = t12->genParticle_pt->at(particleNumber);
 Double_t eta = t12->genParticle_eta->at(particleNumber);
 Double_t phi = t12->genParticle_phi->at(particleNumber);
 Double_t e   = t12->genParticle_e->at(particleNumber);
 V.SetPtEtaPhiE(pt,eta,phi,e);

 return V;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

TLorentzVector getLVofGenZhad(MyClass* t12)
{
  TLorentzVector Z;
  for(int i=0;i<t12->genParticle_N;i++)
    {
      if(TMath::Abs(t12->genParticle_pdgId->at(i))!=23) continue;
      vector<int> da = getDaughterPdgId(i,t12);
      Z = getLorentzVector(i,t12);
      break;
    }
  return Z;
}
//==============================================================================

TLorentzVector getLVofGenParticle( int pdgId, MyClass* t12)
  {
    int case1=0;
    TLorentzVector P;
    TLorentzVector n_t;
    TLorentzVector tmp;
 
    //attention 24 gives only hadronic W!
    if(pdgId ==24)
      { /*vector<int> h;*/
      for(int i=0;i<t12->genParticle_N;i++)
	  {
	    if(TMath::Abs(t12->genParticle_pdgId->at(i))>8)
	      {continue;}
	    if(rightMother(i,t12) !=1)
	      {continue;}
	    P = P + getLorentzVector(i,t12);
// 	    h.push_back(i);
	  }
// 	  cout << "---------------------------------" << endl;
// 	  cout<< event << endl;
// 	  cout<< h.size()<< endl;
// 	  for(int i=0;i<h.size();i++)
// 	  {cout<< h.at(i)<<endl;}
// 	  cout << "---------------------------------" << endl;
      }
     if(pdgId ==11 or pdgId ==13 or pdgId ==12 or pdgId ==14)
      {
        for(int i=0;i<t12->genParticle_N;i++)
	  {
	     if(TMath::Abs(t12->genParticle_pdgId->at(i))==pdgId)
	      {
		int rM =rightMother(i,t12);
		  if(rM==0)
		    continue;
		  if(rM==1)
		    {
		      P = getLorentzVector(i,t12);
		    }
		  if(rM==2)
		    {
		     
			tmp = getLorentzVector(i,t12);
			vector<int> tau= findParticle(15,t12);
			  for(int t=0;t<tau.size();t++)
			    {
				if(rightMother(tau.at(t),t12)!=1)
				  continue;
			      case1 +=1;
			    }
			if(pdgId ==14 or pdgId ==12)
			{
			  vector<int> n_tau= findParticle(16,t12);
			  for(int t=0;t<n_tau.size();t++)
			    {
				if(rightMother(n_tau.at(t),t12)==0)
				  continue;
			      n_t =n_t + getLorentzVector(n_tau.at(t),t12);
			    }
			  }
		    if((pdgId ==11 or pdgId ==13) and case1 ==1)
		      {P = tmp;}
		if((pdgId ==12 or pdgId ==14) and case1==1)
		  {P = n_t + tmp;}
		    
		    }
	
		 }
	    }
       
	}
	if(pdgId ==23)
	  P = getLVofGenZhad(t12);
  return P;

  }
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------


int kinematicCuts(Double_t pt, Double_t eta, int pdgId)
{
  int h=0;
  if(pdgId ==11)
  {
    if(pt> WWELEPT and (TMath::Abs(eta)< WWELEECALGAPMIN or (TMath::Abs(eta)> WWELEECALGAPMAX and TMath::Abs(eta)< WWELEETA)))
    {h+=1;}
  }
  if(pdgId==13)
    {
      if(pt> WWMUPT and TMath::Abs(eta)< WWMUETA)
      {h+=1;}
    }
  if(pdgId==14)
    {
      if(pt> WWMETPTMU)
	{h+=1;}
    }
  if(pdgId==12)
    {
      if(pt> WWMETPTELE)
	{h+=1;}
    }
  if(pdgId==24)
  {
    if(pt> WWPTW)
    {h+=1;}
  }
  return h;
}

//==============================================================================
/*
vector<int> leptonicZRecontructionCandidates(int pdgId, MyClass* t12)
{
  int MaxLept=0;
  vector<int> leptCand;
  if(pdgId==11){MaxLept = t12->el_N;}
  if(pdgId==13){MaxLept =  t12->mu_N;}
  for(int i=0;i<MaxLept;i++)
  {
    if(pdgId==13)
    {
    if()  
      
    }
    
  }
}*/


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int isTightMuon(int p, MyClass* t12)
{

 bool MuonProp_t=0;
 bool MuonKin_t=0;
 double MuonIso_t=0;

 if((t12->mu_pt->at(p)> WWMUPT)and ( TMath::Abs(t12->mu_eta->at(p))< WWMUETA))
 {MuonKin_t = 1;}
 if(t12->mu_isHighPtMuon->at(p)==1 /*and (t12->mu_isTightMuon->at(p) == 1)*/)
 {MuonProp_t = 1;}

 MuonIso_t=t12->mu_trackIso->at(p)/double(t12->mu_pt->at(p));
	     	     
 if(MuonProp_t and MuonKin_t  and MuonIso_t < WWMUISO)
   {return 1;}
 else
   {return 0;}

}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int isLooseMuon(int p, MyClass* t12)
{
 
  bool MuonProp_l=0;
  bool MuonKin_l=0;
  double MuonIso_l=0;
  
if((t12->mu_pt->at(p)> WWMUPTLOOSE)and ( TMath::Abs(t12->mu_eta->at(p))< WWMUETALOOSE))
 {MuonKin_l = 1;}
 if(t12->mu_isHighPtMuon->at(p)==1 /*and (t12->mu_isLooseMuon->at(p) == 1)*/)
 {MuonProp_l = 1;}

  MuonIso_l=t12->mu_trackIso->at(p)/double(t12->mu_pt->at(p));
  
  if(MuonProp_l and MuonKin_l and MuonIso_l< WWMUISOLOOSE)
    {return 1;}
  else
    {return 0;}

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

bool ElectronPassedEtaCuts(int p, MyClass* t12)
{
  bool ElEta=0;
  ElEta=(TMath::Abs(t12->el_eta->at(p))<WWELEETA and TMath::Abs(t12->el_eta->at(p))> WWELEECALGAPMAX) or (TMath::Abs(t12->el_eta->at(p))< WWELEECALGAPMIN);
  return ElEta;
}

//==============================================================================

int isTightElectron(int p, MyClass* t12)
{
 bool ElPt_t=0;
 double ElIso_t=0;
 bool ElHeep6addition=0;
 
 // there is a eta_Cluster in the HEEP ID that already checks for the ecal gap
 // jennifer checks this (below) only when reconstructing the Z but not in the lepton selection
 //ElEta_t=(TMath::Abs(t12->el_eta->at(p))< WWELEETA and TMath::Abs(t12->el_eta->at(p))>WWELEECALGAPMAX) or (TMath::Abs(t12->el_eta->at(p))< WWELEECALGAPMIN);
 
 ElPt_t= t12->el_pt->at(p)> WWELEPT;
 
 //jennifer does not do an iso requirement other than the one already in the HEEP ID!
 //ElIso_t= (el_pfRelIso->at(p))*el_pt->at(p);
 //ElIso_t = t12->el_trackIso->at(p);
 
 //if(TMath::Abs(t12->el_eta->at(p))< WWELEECALGAPMIN)
 if(TMath::Abs(t12->el_superCluster_eta->at(p)) < WWELEECALGAPMIN)
   {
     if(t12->el_hOverE->at(p)<(1/double(t12->el_e->at(p))+ 0.05))
       {ElHeep6addition =1;}
   }
 //if(TMath::Abs(t12->el_eta->at(p))> WWELEECALGAPMAX)
 if(TMath::Abs(t12->el_superCluster_eta->at(p)) > WWELEECALGAPMAX)
   {
     if(t12->el_hOverE->at(p)<(5/double(t12->el_e->at(p))+0.05))
       {ElHeep6addition=1;}
   }
 if(( ElPt_t)==1 /*and ElIso_t< WWELEISO*/ and t12->el_isHeep51Electron->at(p)==1 and ElHeep6addition==1)
   {
     return 1;
   }
 else 
   {
     return 0;	 
   }

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int isLooseElectron(int p, MyClass* t12)
{
 
 
 bool ElPt=0;
 double ElIso=0;
 bool ElHeep6addition=0;

 // there is a eta_Cluster in the HEEP ID that already checks for the ecal gap
 // jennifer checks this (below) only when reconstructing the Z but not in the lepton selection
 //ElEta=(TMath::Abs(t12->el_eta->at(p))<WWELEETA and TMath::Abs(t12->el_eta->at(p))> WWELEECALGAPMAX) or (TMath::Abs(t12->el_eta->at(p))< WWELEECALGAPMIN);

 
 ElPt= t12->el_pt->at(p)> WWELEPTLOOSE;
 
 // not needed iso requirement already in HEEP51-> thats the one jennifer used
// ElIso = t12->el_trackIso->at(p);
 
 //if(TMath::Abs(t12->el_eta->at(p))< WWELEECALGAPMIN)
 if(TMath::Abs(t12->el_superCluster_eta->at(p))< WWELEECALGAPMIN)
   {
     if(t12->el_hOverE->at(p)<(1/double(t12->el_e->at(p))+ 0.05))
       {ElHeep6addition =1;}
   }
 //if(TMath::Abs(t12->el_eta->at(p))> WWELEECALGAPMAX)
 if(TMath::Abs(t12->el_superCluster_eta->at(p)) > WWELEECALGAPMAX)
   {
     if(t12->el_hOverE->at(p)<(5/double(t12->el_e->at(p))+0.05))
       {ElHeep6addition=1;}
   }
  
   if((ElPt)==1 and ElIso< WWELEISO and t12->el_isHeep51Electron->at(p)==1 and ElHeep6addition ==1)
   {
     return 1;
   }
 else 
   {
     
     return 0;	 
   }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int isRightAK8jet( int p,MyClass* t12)
{
  
  bool JetKin=0;
  bool subjettiness=0;
  bool nearness =1;
  TLorentzVector jet;
  TLorentzVector l;
  Double_t DR=10000;

  jet.SetPtEtaPhiE(t12->jetAK8_pt->at(p),t12->jetAK8_eta->at(p),t12->jetAK8_phi->at(p),t12->jetAK8_e->at(p));
  
  if(jet.Pt()> WWAK8JETPT and TMath::Abs(jet.Eta())< WWAK8JETETA and t12->jetAK8_IDLoose->at(p)) 
    {JetKin=1;}
  
  for(int e=0;e<t12->el_N;e++)
  {
    if(nearness ==0)
      continue;
    if(isTightElectron(e,t12)==0)
      continue;
    l.SetPtEtaPhiE(t12->el_pt->at(e),t12->el_eta->at(e),t12->el_phi->at(e),t12->el_e->at(e));
    DR = l.DeltaR(jet);
    if(TMath::Abs(DR)< WWAK8JETDELTAR)
      nearness =0;  
  }
  for(int m=0;m<t12->mu_N;m++)
  {
    if(nearness ==0)
      continue;
    if(isTightMuon(m,t12)==0)
      continue;
    l.SetPtEtaPhiE(t12->mu_pt->at(m),t12->mu_eta->at(m),t12->mu_phi->at(m),t12->mu_e->at(m));
    DR = l.DeltaR(jet);
    if(TMath::Abs(DR)< WWAK8JETDELTAR)
      nearness =0;  
  }
  if(JetKin and nearness)
    {return 1;}
  else
    {return 0;}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

TLorentzVector reconstructWithMatchedJet(TLorentzVector W_had_gen, MyClass* t12)
{
  TLorentzVector jet;
  TLorentzVector W_had;
  
  for(int i=0;i<t12->jetAK8_N;i++)
  {
    jet.SetPtEtaPhiE(t12->jetAK8_pt->at(i),t12->jetAK8_eta->at(i),t12->jetAK8_phi->at(i),t12->jetAK8_e->at(i));
    
    if(W_had_gen.DeltaR(jet)>0.8) continue;
    W_had = jet;
    break;
  }
  return W_had;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int isVetoAK4jet( int p, MyClass* t12)
{
   Double_t DR = 10000;
   bool nearness =1;
   TLorentzVector jet;
   TLorentzVector l;
   
   
   if((t12->jetAK4_pt->at(p)> WWAK4JETPT) and (TMath::Abs(t12->jetAK4_eta->at(p))< WWAK4JETETA) and (t12->jetAK4_cisv->at(p)> WWAK4JETBTAGGERMEDIUMWP))
   {
    jet.SetPtEtaPhiE(t12->jetAK4_pt->at(p),t12->jetAK4_eta->at(p),t12->jetAK4_phi->at(p),t12->jetAK4_e->at(p));
  //b-tagging should be adressed here!
  //should return 1 when jet is b-tagged and has the right kinematic constraints
  
      for(int e=0;e<t12->el_N;e++)
      {
	if(nearness ==0)
	  continue;
	if(isTightElectron(e,t12)==0)
	  continue;
	l.SetPtEtaPhiE(t12->el_pt->at(e),t12->el_eta->at(e),t12->el_phi->at(e),t12->el_e->at(e));
	DR = jet.DeltaR(l);
	if(TMath::Abs(DR)< WWAK4JETDELTARLEPTON)
	{ nearness =0;}  
      }
      for(int m=0;m<t12->mu_N;m++)
      {
	if(nearness ==0)
	  continue;
	if(isTightMuon(m,t12)==0)
	  continue;
	l.SetPtEtaPhiE(t12->mu_pt->at(m),t12->mu_eta->at(m),t12->mu_phi->at(m),t12->mu_e->at(m));
	DR = jet.DeltaR(l);
	if(TMath::Abs(DR)< WWAK4JETDELTARLEPTON)
	{nearness =0;}  
      }
      // use only jet with highest Pt that is the hadronic W reconstruction Candidate 
      for(int j=0;j<t12->jetAK8_N;j++)
      {
	if(nearness ==0)
	  continue;
	if(isRightAK8jet(j,t12)==0)
	  continue;
	l.SetPtEtaPhiE(t12->jetAK8_pt->at(j),t12->jetAK8_eta->at(j),t12->jetAK8_phi->at(j),t12->jetAK8_e->at(j));
	DR = jet.DeltaR(l);
	if(TMath::Abs(DR)< WWAK4JETDELTARAK8JET)
	{nearness =0;}
	break;
    
      }
  }
//   cout<< " nearness : "<<nearness<<" eta "<<t12->jetAK4_eta->at(p)<<" pt "<<t12->jetAK4_pt->at(p) <<" b-tag "<<t12->jetAK4_cisv->at(p)<<" ID "<<t12->jetAK4_IDLoose->at(p)<< endl;
//  
//   cout<< " nearness : "<<nearness<<" eta "<< (TMath::Abs(t12->jetAK4_eta->at(p))<2.4)<<" pt "<<(t12->jetAK4_pt->at(p)>30) <<" b-tag "<<((t12->jetAK4_cisv->at(p)-0.89)>0)<<" ID "<<t12->jetAK4_IDLoose->at(p)<< endl;
//   
  if((t12->jetAK4_pt->at(p)> WWAK4JETPT) and (TMath::Abs(t12->jetAK4_eta->at(p))< WWAK4JETETA) and (t12->jetAK4_cisv->at(p)> WWAK4JETBTAGGERMEDIUMWP) and nearness==1 and t12->jetAK4_IDLoose->at(p))
    {return 1;}
  else
    {return 0;}
}


//-------------------------------------------------------------------------------
//----------------------------------------------------------------------------

// goes through the mother particles of particle number "particleNumber" 
//in event "event", if the mother is either a W Boson, a Graviton
// it returns 1 it returns 2 of mother is a tauon
//otherwise it returns zero.
int rightMother( int particleNumber, MyClass* t12)
{

  
  vector<int> pdgIdMother =t12->genParticle_mother->at(particleNumber);
  int numberOfMotherP = pdgIdMother.size();
  int rightMum=0;
  for(int i=0;i<numberOfMotherP;i++)
    {
      if(TMath::Abs(pdgIdMother.at(i))==24)
	{rightMum= 1;}
      if(TMath::Abs(pdgIdMother.at(i))==39)
	{rightMum= 1;}
      if(TMath::Abs(pdgIdMother.at(i))==15)
	{rightMum= 2;}
    }
  if(rightMum==1)
    return 1;
  if(rightMum==2)
    return 2;
  else
    return 0;
}


//-------------------------------------------------------------------------------
//----------------------------------------------------------------------------

// goes through all particles in event
// and returns a list with the numbers of the particles with pdgId
vector<int> findParticle( int pdgId, MyClass* t12)
{
  vector<int> particleNumbers={};
 
  for(int count=0;count<t12->genParticle_N;count++)
    {
      if(TMath::Abs(t12->genParticle_pdgId->at(count))== pdgId)
	{particleNumbers.push_back(count);}
    }
  return particleNumbers;
}
//---------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
vector<int> getDaughterPdgId(int numParticle, MyClass* t12)
{
 
  vector<int> daughter={};
 
  daughter= t12->genParticle_dau->at(numParticle);
  return daughter;
}


//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

bool isTriggerFired(const char* trigger, MyClass* t12)
{
  bool isfired=0;
  std::map<string,bool> *HLT_isFired = t12->HLT_isFired;
  for(map<string,bool>::iterator it = HLT_isFired->begin();it!= HLT_isFired->end(); it++)
  {
    if((it->first).find(trigger) != std::string::npos)
    {
      if(it->second ==1)
      {isfired =1;}
      break;
    }
  }
  return isfired;
}

//=======================================================================================
//===== jet selection for all hadronic analysis =========================================
//=======================================================================================

vector<int> hadronicJetCandidates(MyClass*t12)
{
  
    vector<float>* jet_pt = t12->jetAK8_pt;
    vector<float>* jet_eta = t12->jetAK8_eta;
    
    bool eventHasCandidates=0;
    bool passedPT =0;
    bool passedEta =0;
    
    vector<int> result ={-99,-99};
    int NJets = t12->jetAK8_N;
    vector<bool>*  jetID = t12->jetAK8_IDTight;
    vector<bool>*  jetIDloose = t12->jetAK8_IDLoose;
    int index1=-99;
    int index2=-99;
  for(int i=0;i<NJets;i++)
  {
   if(jetID->at(i) and jet_pt->at(i)>JETPT and TMath::Abs(jet_eta->at(i)) <JETETA)
   {
     index1 = i;
     for(int k=i+1;k<NJets;k++)
     {
      if(jetID->at(k) and jet_pt->at(k)>JETPT and TMath::Abs(jet_eta->at(k)) <JETETA)
      {
	index2=k;
	break;
      }
     }
     break;
   }
  }
  if(index1!=-99 and index2!=-99)
  {
    result[0]=index1;
    result[1]=index2;
  }
 return result; 
  
}

//========================================================================================

bool AllHadPassedDEtajj(MyClass* t12 , vector<int> index)
{
   vector<float>* jet_eta = t12->jetAK8_eta;
   if(index[0]!=-99 and index[1]!=-99)
   {
     int i1 =index[0];
     int i2 =index[1];
    double Deta = TMath::Abs(jet_eta->at(i1)-jet_eta->at(i2));
    //std::cout << " D eta_jj " <<Deta <<std::endl; 
    if(Deta <DELTAETAJETJET)
      return 1;
    else 
      return 0;
   }
   else 
     return 0;
}

//=========================================================================================

bool AllHadPassedMjj(MyClass* t12, vector<int> index)
{
  TLorentzVector j1;
  TLorentzVector j2;
  bool passed=0;
   if(index[0]!=-99 and index[1]!=-99)
   {
    int p =  index[0];
    int p2 = index[1];
    j1.SetPtEtaPhiE(t12->jetAK8_pt->at(p),t12->jetAK8_eta->at(p),t12->jetAK8_phi->at(p),t12->jetAK8_e->at(p));
    j2.SetPtEtaPhiE(t12->jetAK8_pt->at(p2),t12->jetAK8_eta->at(p2),t12->jetAK8_phi->at(p2),t12->jetAK8_e->at(p2));
    //std::cout << "Mjj "<< (j1+j2).M() <<std::endl;
    if((j1+j2).M()>DIJETMASS)
      passed =1;
    }
  //  std::cout <<passed <<std::endl;
  return passed;
  
}

//=========================================================================================

bool AllHadPassedPrunedMassCut(MyClass* t12, vector<int> index)
{
  bool passed=0;
   if(index[0]!=-99 and index[1]!=-99)
   {
     double mass = t12->jetAK8_pruned_massCorr->at(index[0]);
     double mass2 = t12->jetAK8_pruned_massCorr->at(index[1]);
     if(mass > JETPRUNEDMASSMIN and mass2 >JETPRUNEDMASSMIN)
     {
       passed =1;
     }
   }
  return passed;
}

//==========================================================================================

bool highestPtJetsAreCandidates(MyClass* t12)
{
    
    vector<int> indices = hadronicJetCandidates(t12);
    int index1 = indices[0];
    int index2 = indices[1];
    vector<float>* jet_eta = t12->jetAK8_eta;
    
    
    bool eventHasCandidates=0;
    bool passedPT =0;
    bool passedEta =0;

    if(index1 >=0 and index2>=0)
    {
      if(TMath::Abs(jet_eta->at(index1)-jet_eta->at(index2))< DELTAETAJETJET)
      {
	eventHasCandidates=1;
      }
    }
  return eventHasCandidates;
}


    
    



