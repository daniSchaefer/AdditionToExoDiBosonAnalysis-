#ifndef GENFUNC_H
#define GENFUNC_H

#include "TH1F.h"
#include "TH2F.h"
#include "MyClass.h"
#include "TLorentzVector.h"

//fill a histo with the reconstructed W mass of events in vec. event. Function works for W->l nu or G-> l nu (with missing W)
void getInvariantWmass(TH1F* histo,vector<int> events, int pdgId_lepton, int pdgId_mother , MyClass* t12);

//fills a 2d histo with pt and eta of gen. W
//finds leptons in event and makes sure that they came from a decaying W boson
//reconstucts W through Lvector of lepton and neutrino
//valiable candidates for pdfId are: 11, 13
// if pdfId =0, function gets the kinematics for the hadronically decaying W
void getGenWKinematics(TH2F* histo, int pdgId, MyClass* t12);

//gives the number of events that have tau-> e nu nu and tau -> mu nu nu out of the events in vec. events
vector<int> getTauBranchingRatio(vector<int> events, MyClass* t12);


//fill histo1 with eta, histo2 with pt of the particle with pdgId "pdgId" 
//from the events in list "events"
//function checks for mother particles and fills only if mother = 24,39 or 15
void getKinematicsFromGeneratedEvents(TH1F* histo1,TH1F* histo2, vector<int> events, int pdgId, MyClass* t12);

void getKinematicsFromGeneratedEvents(TH1F* histo1,TH1F* histo2, int pdgId, MyClass* t12);

//this version fills one 2d histo with eta and pt
void getKinematicsFromGeneratedEvents(TH2F* histo, int pdgId, MyClass* t12);

//get the LV of the lepton from W-> l,n or W->tau,n->l,n,n,n
//finds the right lepton in the generated events
//returns the generated LV of lepton
TLorentzVector getGeneratedLepton(int pdgId, MyClass* t12);

//returns vector with pt,eta,phi,e of two hadronically decaying V (W or Z) bosons.
//the first four elements belong to the first LV, the second 4 to the second
vector<float> getGenLVAllHadronic(MyClass* t12);
TLorentzVector getGenLV_V1(MyClass* t12);
TLorentzVector getGenLV_V2(MyClass* t12);

int calcQuarkCharge(int pdgId_q1);
#endif
