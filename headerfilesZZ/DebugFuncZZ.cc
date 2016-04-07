#include "TMath.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include "ZZConstants.h"
#include "RecParticle.h"
#include "Electron.h"
#include "Muon.h"
#include "ReconstructLeptonicZ.h"
#include "ReconstructHadronicZ.h"
#include "EventSelectionZZ.h"
#include "Jet.h"
#include "FatJet.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
/*
void InfoEvent(int event, int pdgId, ofstream &file)
{
  
  
}*/

void printParticleInfo(Electron* particle, ZZtree* t)
{
  std::cout << t->eventId << std::endl;
  std::cout << " number of particles : " <<particle->Get_IndexMax()<<std::endl;
 
  
  for(int i=0;i<particle->Get_IndexMax(); i++)
  {
   particle->Init(i,t);
  
   std::cout<<" pt : " << particle->Pt() <<" : eta : "<< particle->Get_SuperClusterEta()<<" : phi : " << particle->Phi() << " : charge : "<< particle->Get_Charge()<< std::endl;
   std::cout <<" : passed ID : "<< particle->passedID() << " : passed Trigger : " << particle->passedTrigger() << std::endl;
   std::cout << " : passed Kinematic Cuts : " << particle->passedKinematicCuts() << " : passed Isolation : " << particle->passedIsolation() << " : is Candidate : " ;

     std::cout << electronCandidate(particle) << std::endl;
  
  }
  
}
//===========================================================================

void printParticleInfo(Muon* particle, ZZtree* t)
{
  std::cout << t->eventId << std::endl;
  std::cout << " number of particles : " <<particle->Get_IndexMax()<<std::endl;
 
  
  for(int i=0;i<particle->Get_IndexMax(); i++)
  {
   particle->Init(i,t);
  
   std::cout<<" pt : " << particle->Pt() <<" : eta : "<< particle->Eta()<<" : phi : " << particle->Phi() << " : charge : "<< particle->Get_Charge()<< std::endl;
   std::cout <<" : passed ID : "<< particle->passedID() << " : passed Trigger : " << particle->passedTrigger() << std::endl;
   std::cout << " : passed Kinematic Cuts : " << particle->passedKinematicCuts() << " : passed Isolation : " << particle->passedIsolation() << " : is Candidate : " ;
  
   std::cout << muonCandidate(particle) <<std::endl;

  }
  
}
//================================================================================
void printAllFatJetInfo(ZZtree* t)
{
  
   FatJet* jet = new FatJet(t);
  vector<vector<int> > leptCand = GetIndicesLeptonPairs(t);
  vector<int> eleCand = leptCand[0];
  vector<int> muCand = leptCand[1];
  
  std::cout << t->eventId<< std::endl;
  for(int i=0;i<jet->Get_IndexMax();i++)
  {
    jet->Init(i,t);
   std::cout<<" jet index : "<< jet->Get_Index() << " pt : " << jet->Pt() << " eta : " << jet->Eta() << " phi : " << jet->Phi() << " passed Kinematics : "<< jet->passedKinematicCuts() << " jet loose ID : "<< jet->passedID() << std:: endl;
   std::cout << " is in mass Region : "<< jet->isInMassRegion() << " mass : " << t->FATjetPRmassL2L3Corr->at(i)<< " jet isolation : " << jet->passedNearness(eleCand,muCand,t) << " subjettiness : " << jet->Get_Tau21()<< " passed subjettiness  : "<<jet->passedSubjettiness() << std::endl;
  }
  
  delete jet;
}

//====================================================================================

bool isEventInList(int event, vector<int> listOfEvents)
{
  for(int i=0;i<listOfEvents.size();i++)
    {
      if(listOfEvents.at(i)== event)
	return 1;
    }
  return 0;
}

//====================================================================================
vector<int> compareLists(vector<int> list1, vector<int> list2)
{
  vector<int> result={};
  for(int i=0;i<list1.size();i++)
    {
      if(isEventInList(list1.at(i), list2)==0)
	{result.push_back(list1.at(i));}
    }
      return result;
}

//====================================================================================

vector<int> GetEventsFromFile(ifstream &myfile)
{
  vector<int> JosesEvents;
  string line;
  int numb;
  
    if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      
     numb = atoi(line.c_str());
     JosesEvents.push_back(numb);
//      if(numb ==3)
//      {
//      cout << line << '\n';
//       std::cout << numb<< std::endl;
//      }
    }
    //myfile.close();
  }
  return JosesEvents;
}

//==================================================================================

void WriteEventsToFile(vector<int> events, ofstream  &myfile)
{
  for(int i=0;i<events.size();i++)
  {
    myfile << events.at(i) << std::endl;
  }
  
}

//=====================================================================================

void PrintEventInfo(int event, ZZtree* tree,bool isHP,bool isLP)
{
  if(tree->eventId == event)
  {
    TLorentzVector Z_had_gen =GetGeneratedZ(tree,1);
    TLorentzVector Z_lep_gen =GetGeneratedZ(tree,0);
    vector<vector<int> > lept = GetIndicesLeptonPairs(tree);
   std::cout<<"event : "<< event<<" gen. event selection " << GeneratedSelection(tree) <<" gen Z kin. : "<< isLeptonicZ(Z_lep_gen) <<" Z mass " << Z_lep_gen.M() << "Z pt " << Z_lep_gen.Pt() << " lepton selection " <<  LeptonSelection(11, tree) << " "<< LeptonSelection(13,tree)<< " hadron selection " << HadronSelection(lept,tree,isHP, isLP) << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    Muon* mu = new Muon(tree);
    Electron* el = new Electron(tree);
    printParticleInfo(mu,tree);
    std::cout << std::endl;
    TLorentzVector Z_lep = reconstructLeptonicZ(13,lept[1],tree);
    std::cout << " Z rec pt : " <<Z_lep.Pt() << " Z rec mass : " << Z_lep.M()<<std::endl;
    std::cout << std::endl;
    TLorentzVector Z_had = reconstructHadronicZ(lept,tree);
    std::cout << " ZZ mass : " << (Z_lep+Z_had).M()<<std::endl;
    std::cout << std::endl;
    printParticleInfo(el,tree);
    Z_lep = reconstructLeptonicZ(11,lept[0],tree);
    std::cout << " Z rec pt : " <<Z_lep.Pt() << " Z rec mass : " << Z_lep.M()<<std::endl;
    std::cout << " ZZ mass : " << (Z_lep+Z_had).M()<<std::endl;
    
    
  }
}

//================================================================================

vector<double> testSelfConsistency(int pdgId, ZZtree* tree, vector<vector<double> > leptonEff, vector<vector<double> > hadronEff, bool isHP, bool isLP)
{
  
  int howmany = tree->fChain->GetEntries();
  int howmanyEvents =0;
  int howmanyPassedEvents =0;
  double eventsReweighted = 0.0;
  double eventsReweightedHad=0.0;
  double eventsReweightedLep=0.0;
  int help =0;
  int help2=0;
  double zhad = 0.0;
  double zlep = 0.0;
  vector<vector<int> > lept;
  TLorentzVector Z_lep;
  TLorentzVector Z_had;
  TLorentzVector Z_had_gen;
  TLorentzVector Z_lep_gen;
  
   for(int i=0;i<howmany;i++)
 {
    
   tree->fChain->GetEntry(i);
   

   
   if(!hasGenLepton(pdgId,tree)) continue;
   if(!hasGenHadron(tree)) continue;
   howmanyEvents +=1;
   Z_had_gen = GetGeneratedZ(tree,1);
   Z_lep_gen = GetGeneratedZ(tree,0);
   if(!isLeptonicZ(Z_lep_gen)) continue;
   if(!isHadronicZ(Z_had_gen)) continue;
   if(!GravitonSelection(Z_had_gen, Z_lep_gen)) continue;
   
   for(int loop=0;loop<leptonEff[0].size();loop++)
   {
    if(Z_lep_gen.Pt() >= leptonEff[1][loop])continue;
    if(TMath::Abs(Z_lep_gen.Eta()) >= leptonEff[3][loop])continue;
    zlep = leptonEff[4][loop];
    //std::cout << Z_lep_gen.Pt() << " "<<leptonEff[0][loop]<< "-" <<leptonEff[1][loop]<< " " <<Z_lep_gen.Eta() << "  "<<leptonEff[2][loop]<<"-"<< leptonEff[3][loop]<< std::endl;
    break;
   }
   for(int loop=0;loop<hadronEff[0].size();loop++)
   {
    if(Z_had_gen.Pt() >= hadronEff[1][loop])continue;
    if(TMath::Abs(Z_had_gen.Eta()) >= hadronEff[3][loop])continue;
    zhad = hadronEff[4][loop];
    break;
   }
   eventsReweighted += 1.0*zlep*zhad;
   
   eventsReweightedLep +=1.0*zlep;
 
   if(!passedTrigger(pdgId,tree)) continue;
   if(!LeptonSelection(pdgId,tree)) continue;
   help+=1;
   lept = GetIndicesLeptonPairs(tree);
   int index;
   if(pdgId ==13) index =1;
   if(pdgId ==11) index =0;
   //Z_lep = reconstructLeptonicZ(pdgId,lept[index],tree);
   //if(!isLeptonicZ(Z_lep)) continue;
   
   eventsReweightedHad +=1.0*zhad;
   
   if(!HadronSelection(lept,tree, isHP, isLP)) continue;
   //Z_had = reconstructHadronicZ(lept, tree);
   //if(!isHadronicZ(Z_had)) continue;
   //if(!GravitonSelection(Z_had, Z_lep)) continue;
   howmanyPassedEvents +=1;
   
 }
   std::cout<<"number of passed events "<< howmanyPassedEvents << std::endl;
  std::cout <<" number of events in file " << howmanyEvents << std::endl;
  std::cout << " number of events where each event is weighted with the efficiency for its reconstruction " << eventsReweighted << std::endl;
  std::cout << "sum over reweighted events/ number of passed events "<< eventsReweighted/double(howmanyPassedEvents)<<std::endl;
  vector<double> result ={eventsReweighted,double(howmanyPassedEvents)};
  std::cout <<  " number of events that passed lepton selection "<< help<< " events times lept eff "<< eventsReweightedLep << std::endl;
  help2 = help-howmanyPassedEvents;
  std::cout << "#events after final event selection " <<  howmanyPassedEvents << "   "<< eventsReweightedHad<< std::endl;
  
  
  return result;
 
}