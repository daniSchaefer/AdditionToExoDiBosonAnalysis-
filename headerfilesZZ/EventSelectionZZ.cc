#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include "ZZConstants.h"
#include "RecParticle.h"
#include "Electron.h"
#include "Muon.h"
#include "EventSelectionZZ.h"
#include "ReconstructLeptonicZ.h"
#include "ReconstructHadronicZ.h"
#include "GenParticle.h"
#include "ZZtree.h"
#include "FatJet.h"

bool passedTrigger(int pdgId,ZZtree* tree)
{
  bool passed=0;
 if(pdgId==11)
 {
    Electron* ele = new Electron(tree);
      if(ele->passedTrigger()){ passed =1;}
 }
 if(pdgId==13)
 {
    Muon* mu = new Muon(tree);
      if(mu->passedTrigger())
      {passed =1;}
 }
 return passed;
  
}

//===============================================================================

bool LeptonSelection(int pdgId, ZZtree* tree)
{
  vector<vector<int> > candList = leptonCandidates(tree);
  vector<int> result;
  if(pdgId ==11)
  {
   Electron* ele1 = new Electron(tree);
   Electron* ele2 = new Electron(tree);
   result = leptonPair(ele1,ele2,candList, tree);
  }
  if(pdgId ==13)
  {
   Muon* mu1 = new Muon(tree);
   Muon* mu2 = new Muon(tree);
   result =  leptonPair(mu1,mu2,candList,tree);
  }
  return isValidLeptonPair(result);
}

//================================================================================
bool isValidLeptonPair(vector<int> lept)
{
 if(lept[0]>=0 and lept[1]>=0 and (lept[0] != lept[1])) return 1;
 else return 0;
}

//=================================================================================

bool hasGenLepton(ZZtree *tree)
{
  GenParticle* genZ = new GenParticle(tree);
  int counter=0;
  bool hasLepton=0;
  for(int i=0;i<genZ->Get_IndexMax();i++)
  {
    genZ->Init(i,tree);
    if(TMath::Abs(genZ->Get_pdgId())!=23) continue;
    counter +=1;
    if(genZ->isLeptonicZ()) hasLepton =1;
    if(counter<2) continue;
    break;
  }
  return hasLepton;
}

//===============================================================================

bool hasGenLepton(int pdgId, ZZtree *tree)
{
  GenParticle* genZ = new GenParticle(tree);
  int counter=0;
  bool hasLepton=0;
  for(int i=0;i<genZ->Get_IndexMax();i++)
  {
    genZ->Init(i,tree);
    if(TMath::Abs(genZ->Get_pdgId())!=23) continue;
    counter +=1;
    if(genZ->isLeptonicZ(pdgId)) hasLepton =1;
    if(counter<2) continue;
    break;
  }
  return hasLepton;
}

//=================================================================================
bool hasGenHadron(ZZtree* tree)
{
  GenParticle* genP = new GenParticle(tree);
  int counter=0;
  bool hasHadron=0;
  for(int i=0;i<genP->Get_IndexMax();i++)
  {
    genP->Init(i,tree);
    if(TMath::Abs(genP->Get_pdgId())!=23 and TMath::Abs(genP->Get_pdgId())!=24) continue;
    counter +=1;
    if(genP->isHadronicZ() or genP->isHadronicW()) hasHadron =1;
    if(counter<2) continue;
    break;
  }
  return hasHadron;
}

//==================================================================================
bool GeneratedSelection(ZZtree* tree)
{
  bool passed=0;
  TLorentzVector Z_lep;
  TLorentzVector Z_had;
  if(hasGenHadron(tree) and hasGenLepton(tree))
  {
    Z_had = GetGeneratedZ(tree,1);
    if(Z_had.M()==0){Z_had = GetGeneratedW(tree);}
    Z_lep = GetGeneratedZ(tree,0);
  }
  if(isHadronicZ(Z_had) and isLeptonicZ(Z_lep)) passed =1;
  
  return passed;
}

//==================================================================================

bool HadronSelection(vector<vector<int> > leptCand, ZZtree* tree, bool isHP, bool isLP)
{   bool passed=0;
    int jetIndex = FatJetCandidate(leptCand,tree);
    if(jetIndex >-1)
    {
    FatJet* jet = new FatJet(jetIndex,tree);
    if(jet->passedSubjettiness(isHP,isLP) and jet->passedPrunedMass()) passed =1;
    }
    return passed;
}

//==============================================================================

bool GravitonSelection(TLorentzVector Z_had, TLorentzVector Z_lep)
{
  bool passed=0;
  TLorentzVector G = Z_had+Z_lep;
  if(G.M()> ZZMASSMIN and G.M()<ZZMASSMAX) passed =1;
  return passed;
}



