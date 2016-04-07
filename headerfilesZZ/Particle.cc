#include "ZZtree.h"
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include "ZZConstants.h"

//============================================================================

// constructor only for the generated particles! the reconstructed variables do not get initialized, hence the virtual 
virtual RecParticle::RecParticle()
{ 
}


Double_t RecParticle::Pt(){ return pt_rec_;}
Double_t RecParticle::Eta(){return eta_rec_;}
Double_t RecParticle::Phi(){return phi_rec_;}
Double_t RecParticle::E(){return e_rec_;}

TLorentzVector RecParticle::GetLV()
{
 TLorentzVector v;
 v.SetPtEtaPhiE(pt_rec_,eta_rec_,phi_rec_,e_rec_);
 return v:
}


int RecParticle::Get_pdgId(){return pdgId_;}
int RecParticle::Get_Charge(){return charge_;}
int RecParticle::Get_Index(){return index_;}
int RecParticle::Get_EventID(){return eventID_;}

void RecParticle::SetPt(Double_t pt){pt_rec_ = pt;}
void RecParticle::SetEta(Double_t eta){eta_rec_ =eta;}
void RecParticle::SetPhi(Double_t phi){phi_rec_ =phi;}
void RecParticle::SetE(Double_t e){e_rec_ = e;}
void RecParticle::SetLV(TLorentzvector v)
{
 pt_rec_ = v.Pt();
 eta_rec_ = v.Eta();
 phi_rec_ = v.Phi();
 e_rec_ = v.E();
}
  
void RecParticle::Debug(int eventID)
{
  if(eventID_ == eventID)
  {std::cout << " stuff I want shown in case of debugging for given event" << std::endl;}
}
 