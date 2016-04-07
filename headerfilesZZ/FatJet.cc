#include "FatJet.h"
#include "Jet.h"
#include "ZZtree.h"
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include "Jet.h"
#include <vector>
#include "TLorentzVector.h"
#include "ZZConstants.h"
#include "Electron.h"
#include "Muon.h"
#include "RecParticle.h"

FatJet::FatJet(ZZtree* tree)
{
   Set_IndexMax(tree->FATnJet);
   Set_EventID(tree->eventId);
   Set_LooseID(tree->FATjetPassIDLoose);
   
}

FatJet::FatJet(int index ,ZZtree* tree)
{
   Set_IndexMax(tree->FATnJet);
   Set_EventID(tree->eventId);
   
   Init(index,tree);
  
}

FatJet::~FatJet(){}

Double_t FatJet::Get_Tau21(void) const {return subjettiness_;}
Double_t FatJet::Get_PrunedMass(void) const {return prunedMass_;}

void FatJet::Init(int index, ZZtree* tree)
{
   Set_Index(index);
   if(index <  Get_IndexMax())
   {
   TLorentzVector *v = dynamic_cast<TLorentzVector*>(tree->FATjetP4->At(index));
   SetLV(*v);
   subjettiness_ = tree->FATjetTau2->at(index)/tree->FATjetTau1->at(index);
   prunedMass_ = tree->FATjetPRmassL2L3Corr->at(index);
   //Set_LooseID(tree->FATjetPassIDLoose->at(index));
   Set_LooseID(tree->FATisPUJetID->at(index));
   }
   else
   {
    std::cout << " in FATJet Init index out of range " << std::endl; 
   }
}

bool FatJet::passedSubjettiness(bool isHP, bool isLP)
{
 bool passSubjettiness=0;
 double tau21Max =0;
 double tau21Min =0;
 if(isHP and !isLP){tau21Max = ZZCA8JETTAU21HIGHPURITY;}
 if(isHP and isLP){tau21Max = ZZCA8JETTAU21LOWPURITY;}
 if(!isHP and isLP){tau21Max = ZZCA8JETTAU21LOWPURITY;
   tau21Min = ZZCA8JETTAU21HIGHPURITY;}
 if(!isHP and !isLP){ passSubjettiness=1;}
 if(subjettiness_ < tau21Max and subjettiness_ > tau21Min) passSubjettiness =1;
 
 return passSubjettiness;
}

bool FatJet::passedKinematicCuts()
{
  bool passedCuts=0;
  TLorentzVector l = GetLV();
  Double_t pt = l.Pt();
  Double_t eta = l.Eta();
   if(pt> ZZCA8JETPT and TMath::Abs(eta)< ZZCA8JETETA) passedCuts=1;
   
   return passedCuts;
}

bool FatJet::passedID()
{
  bool passed=0;
 if(Get_LooseID()) passed = 1;
 return passed; 
}

bool FatJet::isInMassRegion()
{
  bool passed =0;
  Double_t mass = (GetLV()).M(); 
  if((mass> ZZCA8JETMASSMIN) and (mass< ZZCA8JETMASSMAX)) passed = 1;
  return passed;
}

bool FatJet::passedPrunedMass()
{
 bool passed =0;
 Double_t mass = Get_PrunedMass(); 
 if(mass> ZZCA8JETMASS) passed = 1;
 return passed;
}

bool FatJet::passedNearness(vector<int> eleCand, vector<int> muCand, ZZtree* tree)
{
  TLorentzVector jet = GetLV();
  TLorentzVector lepton;
  bool nearness =1;
  
  if(eleCand[0]>=0 and eleCand[1]>=0)
  {
      for(int i=0;i< 2;i++)
      {
	
	  Electron* ele = new Electron(tree);
	  ele->Init(eleCand[i],tree);
	  lepton= ele->GetLV(); 
	  if(lepton.DeltaR(jet)> ZZCA8JETDELTAR) continue;
	  nearness =0;
      }
  }
  if(muCand[0]>=0 and muCand[1]>=0)
  {
      for(int i=0;i< 2;i++)
      {
	
	  Muon* mu = new Muon(tree);
	  mu->Init(muCand[i],tree);
	  lepton= mu->GetLV(); 
	 if(lepton.DeltaR(jet)> ZZCA8JETDELTAR) continue;
	 nearness =0;
      }
    }
   return nearness;
}

//==========================================================================
bool FatJet::passedNearness(vector<vector<int> > leptCand, ZZtree* tree)
{
  TLorentzVector jet = GetLV();
  TLorentzVector lepton;
  bool nearness =1;
  vector<int> eleCand = leptCand[0];
  vector<int> muCand = leptCand[1];
  
  if(eleCand[0]>=0 and eleCand[1]>=0)
  {
      for(int i=0;i< 2;i++)
      {
	
	  Electron* ele = new Electron(tree);
	  ele->Init(eleCand[i],tree);
	  lepton= ele->GetLV(); 
	  if(lepton.DeltaR(jet)> ZZCA8JETDELTAR) continue;
	  nearness =0;
      }
  }
  if(muCand[0]>=0 and muCand[1]>=0)
  {
      for(int i=0;i< 2;i++)
      {
	
	  Muon* mu = new Muon(tree);
	  mu->Init(muCand[i],tree);
	  lepton= mu->GetLV(); 
	 if(lepton.DeltaR(jet)> ZZCA8JETDELTAR) continue;
	 nearness =0;
      }
    }
   return nearness;
}

// bool isRightJet(vector<vector<int> > leptCand, ZZtree* tree)
// {
//   if(passedKinematicCuts and passedID)
//   
// }

