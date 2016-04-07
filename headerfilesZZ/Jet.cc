#include "ZZtree.h"
#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include "Jet.h"
#include <vector>

Jet::Jet(){}
Jet::~Jet(){}

// bool Jet::isRightJet(int index, vector<vector<int> > leptCand,ZZtree* tree)
// {}

void Jet::Set_LooseID(bool looseID){looseID_ = looseID;}
  void Jet::Set_Index(int index){index_ =index;}
  void Jet::Set_IndexMax(int indexMax){indexMax_ =indexMax;}
  void Jet::Set_EventID(int event){eventID_ = event;}
  void Jet::SetLV(TLorentzVector jetP4){jetP4_ = jetP4;}
  
  bool Jet::Get_LooseID(void) const{return looseID_;}
  int  Jet::Get_Index(void) const{return index_;}
  int  Jet::Get_IndexMax(void) const{return indexMax_;}
  int  Jet::Get_EventID(void ) const{return eventID_;}
  Double_t Jet::Pt(void) const {return jetP4_.Pt();}
  Double_t Jet::Eta(void) const{return jetP4_.Eta();}
  Double_t Jet::Phi(void) const{return jetP4_.Phi();}
  Double_t Jet::E(void) const{return jetP4_.E();}
  TLorentzVector Jet::GetLV(void) const{return jetP4_;}