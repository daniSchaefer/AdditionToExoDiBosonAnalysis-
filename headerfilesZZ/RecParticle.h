#ifndef RECPARTICLE_H
#define RECPARTICLE_H
#include "/usr/users/dschaefer/root/headerfilesZZ/ZZtree.h"
#include "TLorentzVector.h"

// use the aproach where we initialize the member variables using a pointer to ZZtree
class RecParticle
{
private:
  
  int index_;
  int indexMax_;
//   Double_t pt_rec_;
//   Double_t eta_rec_;
//   Double_t phi_rec_;
//   Double_t e_rec_;
  TLorentzVector v_;
  
  int charge_;
  int pdgId_;
  int eventID_;
  
public:
  
  RecParticle( void );
  virtual ~RecParticle( void ) = 0;
  
  virtual void Init(int index, ZZtree* tree) =0;
  Double_t Pt(void) const;
  Double_t Eta(void) const;
  Double_t Phi(void) const;
  Double_t E(void) const;
  TLorentzVector GetLV(void) const;
  
//   void SetPt(Double_t pt);
//   void SetEta(Double_t eta);
//   void SetPhi(Double_t phi);
//   void SetE(Double_t e);
  void SetLV(TLorentzVector v);
  void Set_pdgId(int pdgId);
  void Set_Charge(int charge);
  void Set_Index(int index);
  void Set_IndexMax(int indexMax);
  void Set_EventID(int event);
  
  int  Get_pdgId(void) const;
  int  Get_Charge(void) const;
  int  Get_Index(void) const;
  int  Get_IndexMax(void) const;
  int  Get_EventID(void) const;
  
  void Debug(int eventID);
  
};



#endif