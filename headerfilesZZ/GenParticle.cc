#include "ZZtree.h"
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include "ZZConstants.h"
#include "GenParticle.h"
#include "TLorentzVector.h"

//============================================================================

GenParticle::GenParticle(int index, ZZtree* tree)
{
 
 eventID_ = tree->eventId;
 indexMax_ = tree->nGenPar;
 genDa1_ = tree->genDa1;
 genDa2_ = tree->genDa2;
 generatedParticleP4_ = tree->genParP4;
 Init(index,tree);
 
}

GenParticle::GenParticle(ZZtree* tree)
{
 eventID_ = tree->eventId;
 indexMax_ = tree->nGenPar;
 genDa1_ = tree->genDa1;
 genDa2_ = tree->genDa2;
 generatedParticleP4_ = tree->genParP4;
 //std::cout << eventID_ <<" " <<genDa1_->size() << "  " <<genDa2_->size() << std::endl;

}

GenParticle::~GenParticle(){}

void GenParticle::Init(int index, ZZtree* tree)
{
  
  if(index >=  indexMax_)
  {std::cout << "index "<<index <<" larger/equal than "<< indexMax_  << std::endl; }
  else{
    
    pdgId_ = tree->genParId->at(index);
    index_gen_ = index;
    TLorentzVector *v = dynamic_cast<TLorentzVector*>(generatedParticleP4_->At(index));
 
 //hier noch die initialisierung fuer die pdgIDs von mother particles
 //int Nmother = tree->
 
 if(genDa1_->at(index)>=0 and genDa2_->at(index)>=0 and TMath::Abs(pdgId_) == 23)
 {
  pdgId_Da1_ = tree->genParId->at(genDa1_->at(index));
  pdgId_Da2_ = tree->genParId->at(genDa2_->at(index));
 }
 else
 {
   pdgId_Da1_=0;
   pdgId_Da2_ =0;
 }

  v_ = *v;
  }

}

//void GenParticle::Set_IndexMax(int Max){indexMax_= Max;}

Double_t GenParticle::Pt() const {return v_.Pt();}
Double_t GenParticle::Eta() const {return v_.Eta();}
Double_t GenParticle::Phi() const {return v_.Phi();}
Double_t GenParticle::E() const {return v_.E();}


TLorentzVector GenParticle::GetLV() const {return v_;}
int GenParticle::Get_Index() const{return index_gen_;}
int GenParticle::Get_pdgId() const{return pdgId_;}
int GenParticle::Get_EventID() const{return eventID_;}
int GenParticle::Get_IndexMax() const {return indexMax_;}
int GenParticle::Get_pdgId_Mo1() const{return pdgId_Mo1_;}
int GenParticle::Get_pdgId_Mo2() const{return pdgId_Mo2_;}
int GenParticle::Get_pdgId_Da1() const{return pdgId_Da1_;}
int GenParticle::Get_pdgId_Da2() const{return pdgId_Da2_;}
/*
void GenParticle::SetPt(Double_t pt){pt_gen_ = pt;}
void GenParticle::SetEta(Double_t eta){eta_gen_ =eta;}
void GenParticle::SetPhi(Double_t phi){phi_gen_ =phi;}
void GenParticle::SetE(Double_t e){e_gen_ = e;}*/
void GenParticle::SetLV(TLorentzVector v){ v_ = v;}
 
 void GenParticle::Print()
 {
  std::cout<<" event " << eventID_<<" pdgID " << pdgId_ <<" daughter particles  " << pdgId_Da1_ << ", " <<pdgId_Da2_<< " pt " << v_.Pt()<< " is hadronic Z " <<isHadronicZ() << " is leptonic Z " <<isLeptonicZ() << std::endl; 
 }
 
 void GenParticle::Debug(int eventID)
 {
   if(eventID == eventID_)
   {std::cout << "write some stuff for debugging if we are in the right event " << std::endl;}
   
}

bool GenParticle::isHadronicZ()
{
  bool isHadronic =0;
  if(TMath::Abs(pdgId_)!= 23) return 0;
  else if(TMath::Abs(pdgId_Da1_)<=6 and TMath::Abs(pdgId_Da1_)>=1 and TMath::Abs(pdgId_Da2_)<=6 and TMath::Abs(pdgId_Da2_)>=1)
  {
   isHadronic =1; 
  }
  return isHadronic;
}

bool GenParticle::isLeptonicZ()
{
  bool isLeptonic =0;
 if(TMath::Abs(pdgId_)!= 23) return 0;
  else if((TMath::Abs(pdgId_Da1_)==11 or TMath::Abs(pdgId_Da1_) ==13 or TMath::Abs(pdgId_Da1_)==15) /*and (TMath::Abs(pdgId_Da2_)==11 or TMath::Abs(pdgId_Da2_)==13 or TMath::Abs(pdgId_Da2_) ==15)*/)
  {
   isLeptonic =1; 
  }
  return isLeptonic;
}

bool GenParticle::isLeptonicZ(int pdgId)
{
  bool isLeptonic =0;
 if(TMath::Abs(pdgId_)!= 23) return 0;
  else if((TMath::Abs(pdgId_Da1_)==pdgId))
  {
   isLeptonic =1; 
  }
  return isLeptonic;
}

bool GenParticle::isHadronicW()
{
 bool isHadronic =0;
 if(TMath::Abs(pdgId_)!=24) return 0;
 else if(TMath::Abs(pdgId_Da1_) <=6 and TMath::Abs(pdgId_Da1_)>=1)
 {
   isHadronic =1;
 }
 return isHadronic;
}