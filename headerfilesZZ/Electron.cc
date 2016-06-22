#include "TMath.h"
#include "ZZtree.h"
#include "RecParticle.h"
#include <iostream>
#include "Electron.h"
#include "ZZConstants.h"

Electron::Electron(int index, ZZtree* tree)
{
  int indexRange = tree->nEle;
  Set_IndexMax(indexRange);
  Set_EventID(tree->eventId);
  Set_Index(index);
  Set_pdgId(11);
  hlt_nTrigs_  = tree->hlt_nTrigs;
  hlt_trigResult_ = tree->hlt_trigResult;
  hlt_trigName_ =  tree->hlt_trigName;
  Init(index,tree);
 
}

Electron::Electron(ZZtree* tree)
{
  Set_EventID( tree->eventId);
  Set_pdgId(11);
  Set_IndexMax(tree->nEle);
  hlt_nTrigs_  = tree->hlt_nTrigs;
  hlt_trigResult_ = tree->hlt_trigResult;
  hlt_trigName_ =  tree->hlt_trigName;
}

Electron::~Electron()
{
}

void Electron::Init(int index, ZZtree* tree)
{
  Set_Index( index);
  int indexRange = Get_IndexMax();
   if(index<indexRange)
  {
  TLorentzVector *v = dynamic_cast<TLorentzVector*>(tree->eleP4->At(index));
  SetLV(*v);
  Set_Charge(tree->eleCharge->at(index));
  miniIso_     = tree->eleMiniIsoEA->at(index);
  HoverE_      = tree->eleHoverE->at(index);
  isHEEPNoIso_ = tree->eleIsPassHEEPNoIso->at(index);
  isHEEP_      = tree->eleIsPassHEEP->at(index);
  isLoose_     = tree->eleIsPassLoose->at(index);
  isLooseNoIso_ = tree->eleIsPassLooseNoIso->at(index);
  SuperClusterEta_ = tree->eleScEta->at(index);

  }
  else
  {
    std::cout << "in electron constructor  in " << Get_EventID() <<" index out of range "<< std::endl;
  }
  
}


 // void ~Electron();
 
void Electron::Set_Trigger(const char* trigger_name){trigger_ = trigger_name;}
void Electron::Set_TrackIso(Double_t iso){trackIso_ = iso;}
void Electron::Set_miniIso(Double_t iso){miniIso_ = iso;}
void Electron::Set_HoverE(Double_t HoverE){HoverE_ = HoverE;}
void Electron::Set_HEEPNoIso(bool isHEEP){isHEEPNoIso_ = isHEEP;}
void Electron::Set_HEEP(bool isHEEP){isHEEP_ = isHEEP;}
void Electron::Set_LooseNoIso(bool isTrue){isLooseNoIso_ = isTrue;}
void Electron::Set_Loose(bool isTrue){isLoose_ = isTrue;}
void Electron::Set_SuperClusterEta(Double_t eta){SuperClusterEta_ = eta;}
  
const char* Electron::Get_Trigger() const{return trigger_;}
Double_t Electron::Get_TrackIso() const {return trackIso_;}
Double_t Electron::Get_miniIso() const {return miniIso_;}
Double_t Electron::Get_HoverE() const {return HoverE_;}
bool Electron::Get_HEEPNoIso() const {return isHEEPNoIso_;}
bool Electron::Get_HEEP() const {return isHEEP_;}
bool Electron::Get_LooseNoIso() const {return isLooseNoIso_;}
bool Electron::Get_Loose() const {return isLoose_;}
Double_t Electron::Get_SuperClusterEta() const {return SuperClusterEta_;}
 
 int Electron::passedID()
 {
   int isPassed =0;
   //if(isHEEPNoIso_) {isPassed = 1;}
   if(Get_LooseNoIso()){isPassed =1;}
   return isPassed;
 }
 
  int Electron::passedTrigger()
  {
   bool passedTrig = 0;
   //debug
   if(hlt_nTrigs_ != hlt_trigResult_->size())
     std::cout <<" look at function passedTrigger "<< endl;
   for(int i=0;i<hlt_nTrigs_;i++)
   {
    if((hlt_trigName_->at(i)).find(trigger_)== std::string::npos) continue;
    passedTrig = hlt_trigResult_->at(i);
    break;
   }
   return passedTrig;
  }
  
  
  int Electron::passedKinematicCuts()
  {
   Double_t pt = (GetLV()).Pt();
   Double_t eta = Get_SuperClusterEta();
   bool passedKin = 0;
   
   if(((TMath::Abs(eta)< ZZELEETA /*and TMath::Abs(eta)>  ZZELEECALGAPMAX) or (TMath::Abs(eta)<ZZELEECALGAPMIN*/ and TMath::Abs(eta)>0)) and pt> ZZELEPT) passedKin=1;
    
   return passedKin;
  }
  
  
  //value here from Eikos function ! 
  int Electron::passedIsolation()
  {
    bool passedIso = 0;
    if(miniIso_<=0.1) passedIso =1;
    return passedIso;
  }

  