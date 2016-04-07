#ifndef JET_H
#define JET_H

#include "TLorentzVector.h"
class Jet
{
private:
  TLorentzVector jetP4_;
  bool looseID_;
  int index_;
  int indexMax_;
  int eventID_;
  
  
  
public:
  Jet();
  virtual ~Jet();
  
 // virtual bool isRightJet(int index, vector<vector<int> > leptCand, ZZtree* tree)=0;
  
  void Set_LooseID(bool looseID);
  void Set_Index(int index);
  void Set_IndexMax(int indexMax);
  void Set_EventID(int event);
  void SetLV(TLorentzVector jetP4);
  
  bool Get_LooseID(void) const;
  int  Get_Index(void) const;
  int  Get_IndexMax(void) const;
  int  Get_EventID(void ) const;
  Double_t Pt(void) const;
  Double_t Eta(void) const;
  Double_t Phi(void) const;
  Double_t E(void) const;
  TLorentzVector GetLV(void) const;
  
};


#endif