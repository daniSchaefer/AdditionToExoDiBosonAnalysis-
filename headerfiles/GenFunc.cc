#include "MyClass.h"
#include "GenFunc.h"
#include "RecFunc.h"
#include "Op.h"
#include "EventSelection.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TChain.h"
#include <vector>
#include <vector>
#include <vector>
#include "vector"
#include "iostream"
#include "iomanip"
#include "fstream"
#include "cmath"
#include "cassert"




//------------------------------------------------------------------------------//------------------------------------------------------------------------------

void getGenWKinematics(TH2F* histo,  int pdgId, MyClass* t12)
{
 
  TLorentzVector W;
  TLorentzVector Z;
  TLorentzVector l;
  TLorentzVector n;
 if(pdgId ==11 or pdgId==13)
 {
    l = getLVofGenParticle(pdgId,t12);
    n = getLVofGenParticle(pdgId+1,t12);
    W = n + l;
    if(W.M()!=0 and kinematicCuts(W.Pt(),W.Eta(),24)==1)
      {
	histo->Fill(W.Pt(),TMath::Abs(W.Eta()));
      }
  }
    //zero for hadronic W kinematics
  if(pdgId ==0 or 23)
    {
	W = getLVofGenParticle(24,t12); 
	Z = getLVofGenParticle(23,t12);
	if(W.M()!=0 and Z.M()==0)
	{
	  if(kinematicCuts(W.Pt(),W.Eta(),24)==1)
	  {
	    histo->Fill(W.Pt(),TMath::Abs(W.Eta()));
	  }
	}
	if(W.M()==0 and Z.M()!=0)
	{
	 if(kinematicCuts(Z.Pt(),Z.Eta(),24))
	 {
	 histo->Fill(Z.Pt(),TMath::Abs(Z.Eta())); 
	 }
	}
      }
  
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

TLorentzVector getGeneratedLepton( int pdgId, MyClass* t12)
{
  int case1=-99999;
  TLorentzVector l;
  vector<int> candidate = findParticle(pdgId,t12);
  for(int i=0;i<candidate.size();i++)
  {
   if(rightMother(candidate.at(i),t12)==0)
     continue;
   if(rightMother(candidate.at(i),t12)==2)
   {
    vector<int> tau=findParticle(pdgId,t12);
    for(int l=0;l<tau.size();l++)
    {if(rightMother(tau.at(i),t12)==1){case1=candidate.at(i);}}
    l= getLorentzVector(candidate.at(i),t12);
   }
  }
  if(case1>=0)
  {l= getLorentzVector(case1,t12);}
  return l;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void getInvariantWmass(TH1F* histo,vector<int> events, int pdgId_lepton, int pdgId_mother, MyClass* t12)
{
  

for(int i=0;i<events.size();i++)
   {
     t12->fChain->GetEntry(events.at(i));
     TLorentzVector lepton;
     TLorentzVector neutrino;
     for(int ii=0;ii<t12->genParticle_N;ii++)
       {
	 if(TMath::Abs(t12->genParticle_pdgId->at(ii))== pdgId_lepton)
	   {
	     vector<int> l_moth = t12->genParticle_mother->at(ii);
	     for(int iii=0;iii<l_moth.size();iii++)
	       {
		 if(TMath::Abs(l_moth.at(iii))==pdgId_mother)
		   {
		     lepton.SetPx(t12->genParticle_px->at(ii));
		     lepton.SetPy(t12->genParticle_py->at(ii));
		     lepton.SetPz(t12->genParticle_pz->at(ii));
		     lepton.SetE(t12->genParticle_e->at(ii));
		   }
	       }
	   }
	 if(TMath::Abs(t12->genParticle_pdgId->at(ii))== (pdgId_lepton +1))
	   {
	     vector<int> n_moth = t12->genParticle_mother->at(ii);
	     for(int iii=0;iii<n_moth.size();iii++)
	       {
		 if(TMath::Abs(n_moth.at(iii))==pdgId_mother)
		   {
		     neutrino.SetPx(t12->genParticle_px->at(ii));
		     neutrino.SetPy(t12->genParticle_py->at(ii));
		     neutrino.SetPz(t12->genParticle_pz->at(ii));
		     neutrino.SetE(t12->genParticle_e->at(ii));
		   }
	       }
	   }
       }
     TLorentzVector Wboson= lepton +neutrino;
     histo->Fill(Wboson.M());

   }

}


//-------------------------------------------------------------------------------
//----------------------------------------------------------------------------

void getKinematicsFromGeneratedEvents(TH1F* histo1,TH1F* histo2, vector<int> events,int pdgId, MyClass* t12)
{
  
 
  TLorentzVector l;
  for(int i=0;i<events.size();i++)
  {
    t12->fChain->GetEntry(events.at(i));
  l = getLVofGenParticle(pdgId,t12);
  if(l.Pt()!=0)
  {
    histo1->Fill(l.Eta());
    histo2->Fill(l.Pt());
  }
  }
  
}



//-------------------------------------------------------------------------------
//----------------------------------------------------------------------------

void getKinematicsFromGeneratedEvents(TH2F* histo, int pdgId,MyClass* t12)
{
    TLorentzVector v;
  
 
       vector<int> particleNum = findParticle(pdgId,t12);
      for(int p=0;p<particleNum.size();p++)
	{
	  int rM=rightMother(particleNum.at(p),t12);
	  if(rM==0)
	    {continue;}
	  if(rM==2)
	    {
	      // should check for mother of tauon in this case
	      vector<int> tauNum = findParticle(15,t12);
	      for(int m=0;m<tauNum.size();m++)
		{
		  if(rightMother(tauNum.at(m),t12)==0)
		    continue;
		  else
		    {
		      vector<int> dau=getDaughterPdgId(tauNum.at(m),t12);
		      for(int n=0;n<dau.size();n++)
			{
			  if(TMath::Abs(dau.at(n))==pdgId)
			    {
			      v = getLorentzVector(particleNum.at(p),t12);
			     if(kinematicCuts(v.Pt(),v.Eta(),pdgId)==1)
			     {
				histo->Fill(v.Pt(),TMath::Abs(v.Eta()));
			     }
			    }
			}
		    }
		}

	    }
	  else
	    {  
	      v = getLorentzVector(particleNum.at(p),t12);
	      if(kinematicCuts(v.Pt(),v.Eta(),pdgId)==1)
		{
		  histo->Fill(v.Pt(),TMath::Abs(v.Eta()));
		 }
	      
	    }
	}
 
}





//-------------------------------------------------------------------------------
//----------------------------------------------------------------------------

void getKinematicsFromGeneratedEvents(TH1F* histo1,TH1F* histo2, int pdgId, MyClass* t12)
{
  
  TLorentzVector v;
  
  
      vector<int> particleNum = findParticle(pdgId,t12);
      for(int p=0;p<particleNum.size();p++)
	{
	  int rM=rightMother(particleNum.at(p),t12);
	  if(rM==0)
	    {continue;}
	  if(rM==2)
	    {
	      // should check for mother of tauon in this case
	      vector<int> tauNum = findParticle(15,t12);
	      for(int m=0;m<tauNum.size();m++)
		{
		  if(rightMother(tauNum.at(m),t12)==0)
		    continue;
		  else
		    {
		      vector<int> dau=getDaughterPdgId(tauNum.at(m),t12);
		      for(int n=0;n<dau.size();n++)
			{
			  if(TMath::Abs(dau.at(n))==pdgId)
			    {
			      v = getLorentzVector(particleNum.at(p),t12);
			      if(kinematicCuts(v.Pt(),v.Eta(),pdgId)==1)
			      {
				histo1->Fill(v.Eta());
				histo2->Fill(v.Pt());
			      }
			    }
			}
		    }
		}

	    }
	  else
	    {  
	      v = getLorentzVector(particleNum.at(p),t12);
	      if(kinematicCuts(v.Pt(),v.Eta(),pdgId)==1)
		{
		  histo1->Fill(v.Eta());
		  histo2->Fill(v.Pt());
		}
	    
	    }
	}
 
}
 
 
// ------------------------------------------------------------------------------
// -----------------------------------------------------------------------------
vector<int> getTauBranchingRatio(vector<int> events, MyClass* t12)
{

  vector<int> BRatio={0,0};
  vector<int> help={};
  vector<int> help2={};
  int isRight=0;
  int isEl=0;
  int isMuon=0;
  for(int i=0;i<events.size();i++)
    {
      t12->fChain->GetEntry(events.at(i));
      vector<int> tau =findParticle(15,t12);
      for(int k=0; k<tau.size();k++)
	{
	  vector<int> dau= getDaughterPdgId(tau.at(k),t12);	
	  
	  if(rightMother(tau.at(k),t12)==1 or rightMother(tau.at(k),t12)==2)
	   {
	      for(int m=0;m<dau.size();m++)
		{
		  if(TMath::Abs(dau.at(m))== 16)
		    {isRight +=1;}
		  if(TMath::Abs(dau.at(m))== 11)
		    {isEl +=1;}
		  if(TMath::Abs(dau.at(m))== 13)
		    {isMuon+=1;}
		}
	      
	    }
	}
      if(isRight>0 and isEl>0)
	{BRatio[0]+=1;}
      if(isRight>0 and isMuon>0)
	{BRatio[1]+=1;}
      isRight=0;
      isEl=0;
      isMuon=0;
	
    }

  return BRatio;
}
