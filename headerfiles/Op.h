#ifndef OP_H
#define OP_H

#include "MyClass.h"
#include "TLorentzVector.h"


//checks if mother particle of particleNumber in event is W,G or tau
int rightMother( int particleNumber , MyClass* t12);

//gives a list of all particles in event with pdgId
vector<int> findParticle( int pdgId, MyClass* t12);

//get the lorentz vector of particleNumber in event
vector<int> getDaughterPdgId( int numParticle,  MyClass* t12);

//following functions chech for some selection criteria in reconstructed events


// checks if electron is loose (crit Run2)-> doesn't check for eta cuts on electron eta
//in HEEP 6 Id is an eta check but this works on el_superCluster_eta !
int isLooseElectron( int p, MyClass* t12);
//checks if electron is tight
int isTightElectron( int p, MyClass* t12);

//returns true if electron passes the eta cuts (on el_eta)
//jennifer checks this before reconstructing the W Boson!
bool ElectronPassedEtaCuts(int p, MyClass* t12);

//same for muon
int isTightMuon( int p, MyClass* t12);
int isLooseMuon( int p, MyClass* t12);

//matched jet with generated W_had and returns the matched jet vector
//no selections applied here!
TLorentzVector reconstructWithMatchedJet(TLorentzVector W_had_gen, MyClass* t12);
// checks if AK8 jet can be used for W reconstruction 
int isRightAK8jet(int p, MyClass* t12/*,const char* category="hp"*/);
//checks if the p-th AK4Jet in event gives a b-tagger Veto 
int isVetoAK4jet(int p, MyClass* t12);
  
//following function checks only the kinematic criteria 
int kinematicCuts(Double_t pt, Double_t eta,int pdgId);

//get the P 4 vector of generated hadronic Z
TLorentzVector getLVofGenZhad(MyClass* t12);
//works on generated events and writes eta,e,phi,pt in a lorentz Vector 
// construct
//returns the LV of the particle with particleNumber
TLorentzVector getLorentzVector( int particleNumber, MyClass* t12);


//get LotenzVektor of right particle (from X decay) 
//this function checks explicitly if the particle with pdgId has the right mother i.e. 24 or 39!
//if a neutrino is asked for it returns the sum of LVs of the neutrinos i.e
//for an event with W -> n,tau-> l,n,n,n it returns the sum of all neutrino LVs.
TLorentzVector getLVofGenParticle( int pdgId, MyClass* t12);


//checks if the trigger with key trigger is 1 or 0.
//possible arguments:
//"HLT_Mu45_eta2p1"
//"HLT_Mu50"
//"HLT_Ele105_CaloIdVT_GsfTrkIdT"
//"HLT_Ele115_CaloIdVT_GsfTrkIdT"
bool isTriggerFired(const char* trigger, MyClass* t12);

//all hadronic analysis: find jets with highest Pt that have a tight jet ID
vector<int> hadronicJetCandidates(MyClass*t12);
//for all hadronic part, checks preselections from AN2015_211_v10
bool highestPtJetsAreCandidates(MyClass* t12);

//apply D eta_jj < 1.3
bool AllHadPassedDEtajj(MyClass* t12 , vector<int> index);
//apply M_jj >1000
bool AllHadPassedMjj(MyClass* t12, vector<int> index);
//apply lower pruned mass cut
bool AllHadPassedPrunedMassCut(MyClass* t12, vector<int> index);

#endif
