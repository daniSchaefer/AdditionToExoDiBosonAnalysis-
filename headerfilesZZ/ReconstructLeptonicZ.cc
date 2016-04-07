#include "ZZtree.h"
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include "ZZConstants.h"
#include "RecParticle.h"
#include "Electron.h"
#include "Muon.h"
#include "ReconstructLeptonicZ.h"
#include "GenParticle.h"
#include "ZZConstants.h"



int isUnchargedPair(RecParticle* p1, RecParticle* p2)
{
  Int_t charge;
  charge = p1->Get_Charge() + p2->Get_Charge();
 if(charge==0)
    return 1;
  else 
    return 0;
}


//========================================================================
int electronCandidate(Electron* ele)
{
  if(ele->passedKinematicCuts() and ele->passedIsolation() and ele->passedID())
    return 1;
  else
    return 0;
}

//========================================================================
int muonCandidate(Muon* mu)
{
  if(mu->passedKinematicCuts() and mu->passedIsolation() and mu->passedID())
    return 1;
  else
    return 0;
  
}
//========================================================================
vector<vector<int> > leptonCandidates(ZZtree* tree)
{
   vector<vector<int> > CandNumber(2);
  int leptNumber = 0;
  
  leptNumber = tree->nEle;
  Electron* ele = new Electron(tree); 
   for(int i=0;i<leptNumber;i++)
  {
    ele->Init(i,tree);
    if(!electronCandidate(ele)) continue;
     CandNumber[0].push_back(i);
  }
  delete ele;
  leptNumber = tree->nMu;
  Muon* mu = new Muon(tree);
    for(int i=0;i<leptNumber;i++)
  {
    mu->Init(i,tree);
    if(!muonCandidate(mu)) continue;
     CandNumber[1].push_back(i);
  }
  delete mu;
  return CandNumber;
}

//========================================================================

vector<int> leptonPair(RecParticle* particle1, RecParticle* particle2, vector<vector<int> >  CandNumber, ZZtree* tree)
{
 
   if(particle1->Get_pdgId()!= particle2->Get_pdgId())
   {std::cout <<" warning in function leptonPair, no matching pdgIds" << std::endl;}
   
   int pdgId = particle1->Get_pdgId();
   vector<int> result={-99,-99,pdgId};
   int index;
   if(pdgId==11) index =0;
   if(pdgId==13) index =1;
   
   for(int l =0;l<CandNumber[index].size();l++)
    {
      for(int ll =0;ll<l;ll++)
      {
	particle1->Init(CandNumber[index][l],tree);
	particle2->Init(CandNumber[index][ll],tree);
	if(!isUnchargedPair(particle1,particle2)) continue;
	TLorentzVector pZ = particle1->GetLV()+ particle2->GetLV();
	if(pZ.Pt()<ZZLEPTONICZPT or pZ.M()>ZZLEPTONICZMASSMAX or pZ.M()< ZZLEPTONICZMASSMIN) continue;
   
	result[0]= CandNumber[index][l]; 
	result[1]= CandNumber[index][ll];
      }
    }
    //check that at least one muon has pt>40
      if(pdgId==13 and result[0]!=-99)
      {
      Muon * mu1 = new Muon(result[0],tree);
      Muon * mu2 = new Muon(result[1],tree);
      double pt1 = mu1->Pt();
      double pt2 = mu2->Pt();
      double eta1 = mu1->Eta();
      double eta2 = mu2->Eta();
      if(pt1<pt2){pt1 = mu2->Pt(); pt2 = mu1->Pt();
      eta2 = mu1->Eta();
      eta1 = mu2->Eta();}
      bool isHPT_p1 = mu1->Get_HighPtMuon();
      bool isHPT_p2 = mu2->Get_HighPtMuon();
      bool isCTR_p1 = mu1->Get_CustomTrackerMuon();
      bool isCTR_p2 = mu2->Get_CustomTrackerMuon();
      delete mu1;
      delete mu2;
      
      if(pt1< ZZMUPTBIG and pt2< ZZMUPTBIG){result[0]=-99; result[1]=-99;}
      //if(eta1>2.1){result[0]=-99; result[1]=-99;}
      //there has to be at least one High Pt muon in the event!
      if(!((isHPT_p1 and isCTR_p2) or (isHPT_p2 and isCTR_p1))){result[0]=-99; result[1]=-99;}
      }
      if(pdgId==11 and result[0]!=-99)
      {
      particle1->Init(result[0],tree);
      particle2->Init(result[1],tree);
      Double_t pt1 = (particle1->GetLV()).Pt();
      Double_t pt2 = (particle2->GetLV()).Pt();
   
      if(pt1< ZZELEPTBIG and pt2< ZZELEPTBIG){result[0]=-99; result[1]=-99;}
      }
      
      
   
  return result;
}
//========================================================================
bool isLeptonicZ(TLorentzVector Z_lep)
{
  Double_t mass = Z_lep.M();
  Double_t pt = Z_lep.Pt();
  if(mass> ZZLEPTONICZMASSMIN and mass< ZZLEPTONICZMASSMAX and pt> ZZLEPTONICZPT)
    return 1;
  else
    return 0;
}

//=========================================================================================

TLorentzVector reconstructLeptonicZ(int pdgId,vector<int> LP, ZZtree* tree)
{
  TLorentzVector l1;
  TLorentzVector l2;
  TLorentzVector Z_lep;

  if(LP[2]!=pdgId) 
  {
    std::cout<< " in function reconstructLeptonicZ wrong pdgId"<< endl; 
  }
  
  if(!(LP[0] == -99 or LP[1]==-99))
  {
    if(pdgId == 11)
    {
      Electron * ele = new Electron(tree);
      ele->Init(LP[0],tree);
      l1 = ele->GetLV();
      ele->Init(LP[1],tree);
      l2 = ele->GetLV();
    }
    if(pdgId ==13)
    {
     Muon* mu = new Muon(tree);
     mu->Init(LP[0],tree);
     l1 = mu->GetLV();
     mu->Init(LP[1],tree);
     l2 = mu->GetLV();
    }
  Z_lep = l1+l2;
  }
  return Z_lep;
  
}

//==========================================================================


TLorentzVector reconstructLeptonicZ(int pdgId, ZZtree* tree)
{
  vector<vector<int> > CandNumber = leptonCandidates(tree);
  vector<int> LI;
  if(pdgId==11)
  {
  Electron* p1 = new Electron(tree);
  Electron* p2 = new Electron(tree);
  LI = leptonPair(p1,p2,CandNumber,tree);
  }
  if(pdgId ==13)
  {
   Muon* p1 = new Muon(tree);
   Muon* p2 = new Muon(tree);
   LI = leptonPair(p1,p2,CandNumber,tree);
  }
  else
  {
    LI ={-99,-99,0};
  }
  return reconstructLeptonicZ(pdgId, LI, tree);
}

//==========================================================================

vector<vector<int> > GetIndicesLeptonPairs(ZZtree* t)
{
 vector<vector<int> > result(2);
  vector<vector<int> > leptCand = leptonCandidates(t);
  Electron* ele1 = new Electron(t);
  Electron* ele2 = new Electron(t);
  vector<int> eleCand = leptonPair(ele1,ele2, leptCand,t);
  Muon* mu1 = new Muon(t);
  Muon* mu2 = new Muon(t);
  vector<int> muCand =leptonPair(mu1,mu2,leptCand,t);
  delete ele1;
  delete ele2;
  delete mu1;
  delete mu2;
  result[0] = eleCand;
  result[1] = muCand;
  return result;
}

//===========================================================================

TLorentzVector GetGeneratedZ(ZZtree* tree, bool isHadronic)
{
  int Zcounter=0;
  TLorentzVector result;
  GenParticle* genZ = new GenParticle(tree);
  for(int i=0;i<genZ->Get_IndexMax();i++)
  {
    genZ->Init(i,tree);
    if(TMath::Abs(genZ->Get_pdgId()) != 23) continue;
    Zcounter +=1;
    if(isHadronic and genZ->isHadronicZ()) result = genZ->GetLV();
    if(!isHadronic and genZ->isLeptonicZ()) result = genZ->GetLV();
    if(Zcounter<2) continue;
    break;
  }
  return result;
}

//==============================================================================

TLorentzVector GetGeneratedW(ZZtree* tree)
{
  TLorentzVector result;
  GenParticle* genW = new GenParticle(tree);
  for(int i=0;i<genW->Get_IndexMax();i++)
  {
   genW->Init(i,tree);
   if(!genW->isHadronicW()) continue;
   result = genW->GetLV();
  }
  return result;
}

//===============================================================================

TLorentzVector GetGeneratedZOrW(ZZtree* tree)
{
 TLorentzVector particle = GetGeneratedZ(tree,1);
 if(particle.M()==0)
 {particle = GetGeneratedW(tree);}
 return particle;
}