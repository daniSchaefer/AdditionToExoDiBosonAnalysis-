#ifndef EVENTSELECTIONZZ_H
#define EVENTSELECTIONZZ_H


bool passedTrigger(int pdgId, ZZtree* tree);

//return 1 if the current event has a valid lepton pair
//return 0 otherwise
bool LeptonSelection(int pdgId,ZZtree* tree);

bool HadronSelection(vector<vector<int> > leptCand, ZZtree* tree, bool isHP=1, bool isLP=0);

// checks if the values in lept are >=0 !
bool isValidLeptonPair(vector<int> lept);

//returns 1 if the event has a leptonic Z on generator level
bool hasGenLepton(ZZtree *tree);

bool hasGenLepton(int pdgId, ZZtree *tree);

//returns 1 if the event has a hadronic Z on generator level
bool hasGenHadron(ZZtree *tree);

bool GeneratedSelection(ZZtree* tree);

//selection on graviton mass
bool GravitonSelection(TLorentzVector Z_had, TLorentzVector Z_lep);

#endif