#ifndef ELECTRON_H
#define ELECTRON_H

#include "RecParticle.h"

class Electron : public RecParticle
{
private:
  // welche variablen mussen true sein? bis jetzt noch keine angeschaut (electronCandidate)
 // int isHEEP6Electron;
  Int_t hlt_nTrigs_;
  vector<bool> *hlt_trigResult_;
  vector<string> * hlt_trigName_;
  const char* trigger_ = "HLT_Ele105_CaloIdVT_GsfTrkIdT";//"HLT_Ele105";
  Double_t trackIso_;
  Double_t miniIso_;
  Double_t HoverE_;
  
  bool isHEEPNoIso_;
  bool isHEEP_;
  bool isLoose_;
  bool isLooseNoIso_;
  
  Double_t SuperClusterEta_;
  
  
public:
  Electron(int index, ZZtree* tree);
  Electron(ZZtree* tree);
  ~Electron();
  void Init(int index, ZZtree* tree);
  void Set_Trigger(const char* trigger_name);
  void Set_TrackIso(Double_t iso);
  void Set_miniIso(Double_t iso);
  void Set_HoverE(Double_t HoverE);
  void Set_HEEPNoIso(bool isHEEP);
  void Set_HEEP(bool isHEEP);
  void Set_Loose(bool isTrue);
  void Set_LooseNoIso(bool isTrue);
  void Set_SuperClusterEta(Double_t eta);
  
  const char* Get_Trigger(void) const;
  Double_t Get_TrackIso(void) const;
  Double_t Get_miniIso(void) const;
  Double_t Get_HoverE(void) const;
  bool Get_HEEPNoIso(void) const;
  bool Get_HEEP(void) const;
  bool Get_LooseNoIso(void) const;
  bool Get_Loose(void) const;
  Double_t Get_SuperClusterEta(void) const;
  
  int passedID(void);
  int passedTrigger(void);
  int passedKinematicCuts(void);
  int passedIsolation(void);
  
};

#endif