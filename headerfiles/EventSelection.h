#ifndef EVENTSELECTION_H
#define EVENTSELECTION_H

#include "MyClass.h"
#include "TLorentzVector.h"

//go through inclusive trees and return 1 if the event corresponds to the decayMode, 0 otherwise
//possibilities for decayMode: lvlv, llll, jjjj, lvjj, lljj
//if decayMode doesn't match these strings it just returns 0 
bool genEventSelectionInclusive(MyClass* t12, string decayMode);

//classifiy events in WW, WZ and ZZ
//return value = 24*number of W's in event + 23 * number of Z's in event
int genEventVVClassification(MyClass* t12);
//apply generator level kinematic cuts for the all hadronic channel
bool applyGeneratorKinematicSelectionsAllHad(TLorentzVector V1, TLorentzVector V2);

// seperate events in G->WW, G->Wl, G->W had, G-> l, had
//operates on generated events
vector<vector<int> > generatedSemiLepEventClassification(int howmany,MyClass* t12);

// gives the events with tau->e nu nu in [0] and tau->mu nu nu in [1]
//operates on generated events
vector<vector<int> > selectTauEvents(vector<int> events,int pdgId_lepton, int pdgId_mother, MyClass* t12);

//applies Muon selection criteria on MC after detector simulation
// gives list of events which fulfill these criteria
//works on reconstructed events
vector<int> EventSelectionMuon(int howmany, MyClass* t12);


//applies Electron selection criteria on MC after detector simulation
// gives list of events which fulfill these criteria
//works on reconstructed events
vector<int> EventSelectionElectron(int howmany, MyClass* t12);




//returns 1 if the event fulfills the following contraints:
//1) lepton (pdgId) fullfills its cuts on pt and eta
//2) the lepton is eithter
//          - a Heep 6 electron
//          - a HighPT muon
//there are no loose electrons/muons detected in the event
//3) the number of b-tagged AK4 jets is zero
//4) MET is > 80 GeV for electrons, and > 40 GeV for muons
//returns 0 if these conditions are not met by the event.
int applyLeptonSelection( int pdgId ,  MyClass* t12);

//same as function above but:
//does not apply additional loose lepton veto
int applyLeptonSelection_NoLooseLeptonVeto( int pdgId , MyClass* t12);

//same as applyLeptonSelection but:
//does not apply the b-tagged AK4 jet veto
int applyLeptonSelection_NoBVeto( int pdgId , MyClass* t12);

//same as applyLeptonSelection but:
//does not apply b-tagged AK4 jet veto and
//does not apply additional loose lepton veto
//does not apply MET veto
int applyLeptonSelection_NoVeto( int pdgId ,  MyClass* t12);

//looks if there  is a tight lepton with pdgId in event
int hasTightLepton( int pdgId ,  MyClass* t12);

//returns 1 if event has not b-tagged AK4 jet and no additional loose electrons
int applyVetos(int pdgId, MyClass * t12);
// applies only b-tagged jet veto !
int applyBVeto(MyClass* t12);
//appy only the loose lepton veto
int applyLooseLeptonVeto(int pdgId, MyClass* t12);
//apply the missing Et constrictions.
int applyMET(int pdgId, MyClass* t12);

//selects events with one or more AK8 Jet with:
//pt> 200 GeV
//|eta|<2.4
// isHP=1 and isLP=0 -> high purity subjettiness
// isHP =0 and isLP=1 -> low purity subjettiness
// isHP =0 and isLP=0 -> no subjettiness tested
// isHP=1 and isLP=1 -> combined categories
//for region used:
// isW =1 and isZ =1 ->use full mass Region : m_pruned in the range of 65-105 GeV
// is W=0 and isZ =1 -> use Z Region
//isW =1 and isZ=0 -> use W Region
// isW=0 and isZ =0 -> apply no mass cut
int applyHadronSelection( MyClass* t12,bool isHP =0, bool isLP = 0, bool isW=1, bool isZ=1);

//returns 1 if the event is sufficiently back to back i.e.
//DR(W_had,l)>pi/2 and Dphi(W_had,MET)>2 and Dphi(W_had,W_lep)>2
int applyBackToBackTopology(TLorentzVector l,TLorentzVector W_had, TLorentzVector W_lep , TLorentzVector n);

//applies back to back topology and the mVV mass cut
bool recoEventSelectionMVVSystemSemilep(TLorentzVector l, TLorentzVector n, TLorentzVector W_had);

//applies both hadronic and leptonic event selection
int EventSelection( int pdgId,MyClass* t12);

//applies all kinematic selections including back to back topology to the generated events
//if applyMassCut ==0 then the cuts on m_VV are not applied!
//we need this for the fitting of the wider low mass samples!
//but not for the calculation of Efficiencies
int generatedEventSelection( int pdgId, MyClass* t12,bool applyMassCut =1);

vector<vector<int> > genDataEventSeparationSemileptonicWW(int howmany, MyClass* t12);

//applies all nececary muon or electron triggers depending on pdgId
//returns 1 if event passed one of the triggers, 0 otherwise
//for muons:
//HLT_Mu45_eta2p1 or HLT_Mu50 mussed be passed by the event
//for electrons:
//HLT_Ele105_CloIdVT_GsfTrkIdT or HLT_Ele105_CloIdVT_GsfTrkIdT mussed be passed.
bool applyTrigger(int pdgId, MyClass* t12);

//applies all hadronic analysis triggers (see AN2015_211_v10)
//with an or! 
bool applyTriggerAllHadronic(MyClass* t12);
#endif
