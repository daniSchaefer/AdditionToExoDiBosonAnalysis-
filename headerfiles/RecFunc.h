#ifndef RECFUNC_H
#define RECFUNC_H

#include "TLorentzVector.h"
#include "MyClass.h"

// recontruct the leptonically decaying W boson from lepton 4-momentum and missing transverse Energie
TLorentzVector recNeutrino(Double_t MET,Double_t MET_phi ,TLorentzVector lepton);

TLorentzVector reconstructLepton(int pdgId,MyClass* t12);

//recunstruct the W boson four momentum from rec. Neutrino and lepton.
//works on the reconstructed MC events
//takes the four momentum of tight lepton -> has to be used on preselected
// events i.e. the lepton cuts and vetoes already applied
TLorentzVector reconstructLeptonicW(int pdgIdLepton,MyClass* t12);

//reconstruct the lorentz Vector of the hadronic W or Z
//reconstruction works with AK8 jets
//if isW and isZ takes whole mass region
//if isW and !isZ takes mass region for W
//if !isW ans isZ takes mass region for Z
TLorentzVector reconstructHadronicWOrZ(MyClass *t12,bool isW=1, bool isZ=1);

#endif
