#ifndef GENPARTICLE_H
#define GENPARTICLE_H

#include "TLorentzVector.h"
class GenParticle
{
private:

  int index_gen_;
  int indexMax_;
  TLorentzVector v_;
  TClonesArray* generatedParticleP4_;
  
  int pdgId_;
  int eventID_;
  int pdgId_Mo1_;
  int pdgId_Mo2_;
  int pdgId_Da1_;
  int pdgId_Da2_;
  
  vector<int> *genDa1_;
  vector<int> *genDa2_;
  
public:
  
  GenParticle( int index, ZZtree* tree);
  GenParticle(ZZtree* tree);
  ~GenParticle( void );
  
  
  void Init(int index, ZZtree* tree);
  Double_t Pt(void) const;
  Double_t Eta(void) const;
  Double_t Phi(void) const;
  Double_t E(void) const;
  TLorentzVector GetLV(void) const;
  
  

  void SetLV(TLorentzVector v);
 // void Set_IndexMax(int Max);
  
  int Get_Index(void) const;
  int Get_IndexMax(void) const;
  int  Get_pdgId(void) const;
  int  Get_EventID(void) const;
  int  Get_pdgId_Mo1() const;
  int  Get_pdgId_Mo2() const;
  int  Get_pdgId_Da1() const;
  int  Get_pdgId_Da2() const;
  
  void Print(void);
  void Debug(int eventID);
  bool isHadronicZ(void);
  bool isLeptonicZ(void);
  bool isLeptonicZ(int pdgId);
  bool isHadronicW(void);
//   
};
#endif