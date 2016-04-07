#include "TLorentzVector.h"
#include "Jet.h"
#include "FatJet.h"
#include "RecParticle.h"
#include "Electron.h"
#include "Muon.h"
#include "ZZtree.h"
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include "TLorentzVector.h"
#include "ReconstructHadronicZ.h"
#include "ZZConstants.h"




int FatJetCandidate(vector<vector<int> > leptCand, ZZtree* tree)
{
  int jetIndex = -99;
  FatJet* jet = new FatJet(tree);
  for(int i=0;i<jet->Get_IndexMax();i++)
  {
   jet->Init(i,tree);
   if(!jet->passedID()) continue;
   if(!jet->passedNearness(leptCand,tree)) continue;
   if(!jet->passedKinematicCuts()) continue;
   //if(!jet->passedPrunedMass()) continue;
   jetIndex = i;
   break;
  }
  return jetIndex;
}
//==============================================================================

TLorentzVector reconstructHadronicZ(vector<vector<int> > leptCand, ZZtree* tree)
{
  
  TLorentzVector Z_had;
  int jetIndex = FatJetCandidate(leptCand,tree);
  if(jetIndex<0) return Z_had;
  FatJet* jet = new FatJet(jetIndex,tree);
  Z_had = jet->GetLV();
  return Z_had;
}


//======================================================================
bool isHadronicZ(TLorentzVector Z_had)
{
  double mass = Z_had.M();
  bool passed=0;
  Double_t pt = Z_had.Pt();
  if(mass>ZZHADRONICZMASSMIN and mass<ZZHADRONICZMASSMAX  and pt > ZZHADRONICZPT) passed =1;
  return passed;
  
}
//======================================================================================

