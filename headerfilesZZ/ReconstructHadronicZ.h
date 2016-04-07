#ifndef RECONSTRUCTHADRONICZ_H
#define RECONSTRUCTHADRONICZ_H



//returns index of the reconstruction Candidate (jet that passes kinematic, and isolation criteria
//this is the jet with highest Pt!
// no loose jet ID !
int FatJetCandidate(vector<vector<int> > leptCand, ZZtree* tree);


//returns the momentum four vector of hadronic Z
//need lepton candidates to check the jet isolation criteria
TLorentzVector reconstructHadronicZ( vector<vector<int> > leptCand, ZZtree* tree);

bool isHadronicZ(TLorentzVector Z_had);

#endif