#ifndef MUON_H
#define MUON_H

#include "RecParticle.h"
#include "ZZtree.h"

class Muon : public RecParticle
{
private:
 
  Int_t hlt_nTrigs_;
  vector<bool> *hlt_trigResult_;
  vector<string> * hlt_trigName_;
  const char* trigger_ = "HLT_Mu45_eta2p1";//"HLT_Mu45";
  Double_t miniIso_;
  
  bool isHighPtMuon_;
  bool isCustomTrackerMuon_;
  
  
  
public:
  Muon(int index, ZZtree* tree);
  Muon(ZZtree* tree);
  ~Muon();
  void Init(int index, ZZtree* tree);
  
  void Set_Trigger(const char* trigger_name);
  //void Set_TrackIso(Double_t iso);
  void Set_miniIso(Double_t iso);
  void Set_HighPtMuon(bool isHighPtMuon);
  void Set_CustomTrackerMuon(bool isCustomTrackerMuon);
  
  
  const char* Get_Trigger(void) const;
  //Double_t Get_TrackIso(void) const;
  Double_t Get_miniIso(void) const;
  bool Get_HighPtMuon(void) const;
  bool Get_CustomTrackerMuon(void) const;
  
  int passedID(void);
  int passedTrigger(void);
  int passedKinematicCuts(void);
  int passedIsolation(void);
  
};

#endif