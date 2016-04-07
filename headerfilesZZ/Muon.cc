#include "TMath.h"
#include "ZZtree.h"
#include "RecParticle.h"
#include <iostream>
#include "Muon.h"
#include "ZZConstants.h"

 Muon::Muon(int index, ZZtree* tree)
{
  int indexRange = tree->nMu;
  Set_EventID(tree->eventId);
  Set_Index(index);
  Set_IndexMax(indexRange);
  Set_pdgId(13);
 
  if(index<indexRange)
  {
  TLorentzVector *v = dynamic_cast<TLorentzVector*>(tree->muP4->At(index));
  SetLV(*v);
  Set_Charge( tree->muCharge->at(index));
  miniIso_     = tree->muMiniIsoEA->at(index);
  
  isHighPtMuon_ = tree->isHighPtMuon->at(index);
  isCustomTrackerMuon_ = tree->isCustomTrackerMuon->at(index);
  
  hlt_nTrigs_  = tree->hlt_nTrigs;
  hlt_trigResult_ = tree->hlt_trigResult;
  hlt_trigName_ =  tree->hlt_trigName;
  }
  else
  {
    std::cout << "in muon constructor  in " << Get_EventID() <<" index out of range "<< std::endl;
  }
}

Muon::Muon(ZZtree* tree)
{
  
  Set_EventID( tree->eventId);
  Set_pdgId(13);
  Set_IndexMax(tree->nMu);
  hlt_nTrigs_  = tree->hlt_nTrigs;
  hlt_trigResult_ = tree->hlt_trigResult;
  hlt_trigName_ =  tree->hlt_trigName;
}

Muon::~Muon()
{
}

  void Muon::Set_Trigger(const char* trigger_name){trigger_ = trigger_name;}
  void Muon::Set_miniIso(Double_t iso){miniIso_ = iso;}
  void Muon::Set_HighPtMuon(bool isHighPtMuon){isHighPtMuon_ = isHighPtMuon;}
  void Muon::Set_CustomTrackerMuon(bool isCustomTrackerMuon){isCustomTrackerMuon_ = isCustomTrackerMuon;}
  
  
  const char* Muon::Get_Trigger(void) const {return trigger_;}
  //Double_t Get_TrackIso(void) const;
  Double_t Muon::Get_miniIso(void) const {return miniIso_;}
  bool Muon::Get_HighPtMuon(void) const {return isHighPtMuon_;}
  bool Muon::Get_CustomTrackerMuon(void) const {return isCustomTrackerMuon_;}



void Muon::Init(int index,ZZtree* tree)
{
  int indexRange = tree->nMu;
  Set_EventID(tree->eventId);
  Set_Index( index);
  
  if(index<indexRange)
  {
  TLorentzVector *v = dynamic_cast<TLorentzVector*>(tree->muP4->At(index));
  SetLV(*v);
  Set_Charge( tree->muCharge->at(index));
  miniIso_     = tree->muMiniIsoEA->at(index);
  
  isHighPtMuon_ = tree->isHighPtMuon->at(index);
  isCustomTrackerMuon_ = tree->isCustomTrackerMuon->at(index);
  }
  else
  {
    std::cout << "in muon init  in " << Get_EventID() <<" index out of range "<< std::endl;
  } 
}

int Muon::passedID()
{
  int isPassed=0;
  if(isHighPtMuon_ or isCustomTrackerMuon_) isPassed =1;
  return isPassed;

}


int Muon::passedTrigger()
{
   bool passedTrig = 0;
   //debug
   if(hlt_nTrigs_ != hlt_trigResult_->size())
     std::cout <<" look at function passedTrigger "<< endl;
   for(int i=0;i<hlt_nTrigs_;i++)
   {
    if((hlt_trigName_->at(i)).find(trigger_)== std::string::npos) continue;
    passedTrig = hlt_trigResult_->at(i);
   }
   return passedTrig; 
}

int Muon::passedKinematicCuts()
{
  Double_t pt;
  Double_t eta;
  TLorentzVector particle = GetLV();
  int passedKin =0;
  
   pt = particle.Pt();//tree->muPt->at(candidate); 
   eta = particle.Eta();//tree->muEta->at(candidate);
   if(TMath::Abs(eta)< ZZMUETA and pt> ZZMUPT) passedKin =1;
  
  return passedKin;
}

//like this from Eiko (https://github.com/syuvivida/xtozh_common/blob/13TeV_CMSSW747/macro_examples/synchronization/isPassZmumu.h) 
int Muon::passedIsolation()
{
  bool passedIso =0;
  if(miniIso_<0.2) passedIso =1;
  
  return passedIso;
}