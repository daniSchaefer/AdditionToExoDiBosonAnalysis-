#ifndef RECONTRUCTLEPTONICZ_H
#define RECONTRUCTLEPTONICZ_H


//both functions return the Lorentz Vector of the leptonic Z if the reonstruction is possible
//a zero Vector otherwise
//first function calculates the lepton Pair (LP) again intrinsic
//the second needs the indices of the lepton pair as argument (pdgId and LP have to fit!)
//reconstruct the leptonic Z with LP=vector containing the lepton candidates
TLorentzVector reconstructLeptonicZ(int pdgId,vector<int> LP, ZZtree* tree);
TLorentzVector reconstructLeptonicZ(int pdgId, ZZtree* tree);

//returns 1 if the leptonic Z passes the mass requirement
//otherwise this is 0
bool isLeptonicZ(TLorentzVector Z_lep);



//gives Vector of candidate leptons that passed the crit. in electron(muon)Candidate
//the [0] components hold the electrons the [1] component the muons
vector<vector<int> > leptonCandidates(ZZtree* tree);

int muonCandidate(Muon* mu);

int electronCandidate(Electron* ele);

int isUnchargedPair(RecParticle* p1, RecParticle* p2);



//returns leptonnumber of leptons that passed all crit.
//if there are not two leptons that pass all criteria it returns a
//vector with -99 in both components
// returns always a vector of size three!
//the third component is the pdgId for cross checking purposes
vector<int> leptonPair(RecParticle* particle1,RecParticle* particle2,vector<vector<int> > CandNumber,ZZtree* tree);

//returns the two Candidate leptons for ZZ reconstruction
// first component electrons
//second vector muons
//if there are no candidates the vector contains -99,-99, pdgId
vector<vector<int> > GetIndicesLeptonPairs(ZZtree* t);

//returns the momentum 4 vector of the generated Z
//if isHadronic =1; returns hadronic Z
// else returns leptonic Z
TLorentzVector GetGeneratedZ(ZZtree* tree, bool isHadronic);

//if sample with W'->Z W ->ll, q q'resonance are used:
//this function gives momentum 4 vector of hadronic W boson
TLorentzVector GetGeneratedW(ZZtree* tree);

//returns momentum four vector of the generated Z or W boson
//depending on which vector is not 0
TLorentzVector GetGeneratedZOrW(ZZtree* tree);
#endif