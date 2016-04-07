#include "ZZtree.h"
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include "ZZConstants.h"
#include "RecParticle.h"
#include "TLorentzVector.h"

//============================================================================

// constructor only for the generated particles! the reconstructed variables do not get initialized, hence the virtual 
RecParticle::RecParticle()
{ 
}
RecParticle::~RecParticle()
{
}

void RecParticle::Init(int index, ZZtree* tree)
{
}



Double_t RecParticle::Pt() const { return v_.Pt();}
Double_t RecParticle::Eta() const {return v_.Eta();}
Double_t RecParticle::Phi() const {return v_.Phi();}
Double_t RecParticle::E() const {return v_.E();}

TLorentzVector RecParticle::GetLV() const {return v_;}




int RecParticle::Get_pdgId() const {return pdgId_;}
int RecParticle::Get_Charge() const {return charge_;}
int RecParticle::Get_Index() const {return index_;}
int RecParticle::Get_IndexMax() const {return indexMax_;}
int RecParticle::Get_EventID() const {return eventID_;}

void RecParticle::Set_pdgId(int pdgId){pdgId_ = pdgId;}
void RecParticle::Set_Charge(int charge){charge_ = charge;}
void RecParticle::Set_Index(int index){index_ = index;}
void RecParticle::Set_IndexMax(int indexMax){indexMax_ = indexMax;}
void RecParticle::Set_EventID(int event){eventID_= event;}
// void RecParticle::SetPt(Double_t pt){pt_rec_ = pt;}
// void RecParticle::SetEta(Double_t eta){eta_rec_ =eta;}
// void RecParticle::SetPhi(Double_t phi){phi_rec_ =phi;}
// void RecParticle::SetE(Double_t e){e_rec_ = e;}
void RecParticle::SetLV(TLorentzVector v)
{
//  pt_rec_ = v.Pt();
//  eta_rec_ = v.Eta();
//  phi_rec_ = v.Phi();
//  e_rec_ = v.E();
  v_ = v;
}
  
void RecParticle::Debug(int eventID)
{
  if(eventID_ == eventID)
  {std::cout << " stuff I want shown in case of debugging for given event" << std::endl;}
}
 