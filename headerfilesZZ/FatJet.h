#ifndef FATJET_H
#define FATJET_H

#include "ZZtree.h"
#include "Jet.h"

class FatJet : public Jet
{
private:
Double_t subjettiness_;
Double_t prunedMass_;

public:
  FatJet(ZZtree* tree);
  FatJet(int index,ZZtree* tree);
  ~FatJet();
  
  void Init(int index, ZZtree* tree);
  Double_t Get_Tau21(void) const;
  Double_t Get_PrunedMass(void) const;
  //only HP category at the moment
  bool passedSubjettiness(bool isHP=1, bool isLP =0);
  bool passedKinematicCuts();
  bool passedID();
  bool passedPrunedMass();
  bool isInMassRegion();
  bool passedNearness(vector<int> eleCand, vector<int> muCand, ZZtree* tree);
  bool passedNearness(vector<vector<int> > leptCand, ZZtree* tree);
  //bool isRightJet(vector<vector<int> > leptCand, ZZtree* tree);
};
#endif