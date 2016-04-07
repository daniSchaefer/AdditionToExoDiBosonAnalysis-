#include "TROOT.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TChain.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
 #include "/usr/users/dschaefer/root/headerfilesZZ/ZZtree.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/GenParticle.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/RecParticle.h"
 #include "/usr/users/dschaefer/root/headerfilesZZ/GenParticle.h"
 #include "/usr/users/dschaefer/root/headerfilesZZ/Electron.h"
 #include "/usr/users/dschaefer/root/headerfilesZZ/Muon.h"
 #include "/usr/users/dschaefer/root/headerfilesZZ/ReconstructLeptonicZ.h"
 #include "/usr/users/dschaefer/root/headerfilesZZ/Jet.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/FatJet.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/ReconstructHadronicZ.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/EventSelectionZZ.h"
#include "/usr/users/dschaefer/root/headerfilesZZ/DebugFuncZZ.h"

using namespace std;

 const char* input_filename1 = "/usr/users/dschaefer/root/data/crab_BulkGravToZZToZlepZhad_narrow_M-600_13TeV-madgraph.root";
 const char* input_filename2 ="/usr/users/dschaefer/root/data/crab_BulkGravToZZToZlepZhad_narrow_M-2000_13TeV-madgraph.root";
 const char* input_filename3 ="/usr/users/dschaefer/root/data/crab_BulkGravToZZToZlepZhad_narrow_M-800_13TeV-madgraph.root";
 const char* input_filename4 ="/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-3500_13TeV-madgraph.root";
 
 const char* input_filename5 ="/storage/jbod/dschaefer/BulkGravToZZToZlepZhad_narrow_M/crab_BulkGravToZZToZlepZhad_narrow_M-1000_13TeV-madgraph.root";
 
 
namespace{
  int loadMyLibraryTriggerFunc(){
  
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/ZZtree.C+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/RecParticle.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/GenParticle.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/Electron.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/Muon.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/Jet.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/FatJet.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/ReconstructLeptonicZ.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/ReconstructHadronicZ.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/EventSelectionZZ.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesZZ/DebugFuncZZ.cc+");
   
 return 0; 
}
int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void SynchronizeZZ(int pdgId)
{
  TChain treeChain("tree/treeMaker");
  //treeChain.Add(input_filename1);
  //treeChain.Add(input_filename2);
  //treeChain.Add(input_filename3);
  //treeChain.Add(input_filename4);
  treeChain.Add(input_filename5);
  
  ZZtree* tree = new ZZtree(&treeChain);
 

  bool isHP =0;
  bool isLP =0;
  
  TLorentzVector Z_lep;
  TLorentzVector Z_had;
  TLorentzVector Z_lep_gen;
  TLorentzVector Z_had_gen;
  vector<vector<int> > lept;
int AllEvts=0;
int GenZlep=0;
int HLT =0;
int LeptSelections=0;

int Zpeak =0;
int GenZhad=0;
int Jet=0;
int JetID=0;
int JetClean=0;
int JetKin=0;
int JetSubj=0;
int JetMass=0;
int JetPrunedMass=0;
int ZhadKin=0;
int Graviton=0;

  vector<int> myEventsmu;
  vector<int> myEventsel;

  
  int howmany = tree->fChain->GetEntries();
  std::cout<< howmany<< " events are beeing processed "<<std::endl;
  for(int i=0;i<howmany;i++)
  {
  tree->GetEntry(i);
  
  //PrintEventInfo(26520,tree);
  //PrintEventInfo(10488,tree);
  PrintEventInfo(10,tree);
  PrintEventInfo(15,tree);
  PrintEventInfo(22,tree);
  PrintEventInfo(33,tree);
  PrintEventInfo(36,tree);
  
  
  AllEvts+=1;
  if(!hasGenLepton(pdgId,tree)) continue;
  GenZlep +=1;
  if(!passedTrigger(pdgId,tree)) continue;
  HLT +=1;
  
  if(!LeptonSelection(pdgId,tree)) continue;
  LeptSelections+=1;
  lept = GetIndicesLeptonPairs(tree);
  int index;
  if(pdgId ==13) index =1;
  if(pdgId ==11) index =0;
  Z_lep = reconstructLeptonicZ(pdgId,lept[index],tree);
  if(!isLeptonicZ(Z_lep)) continue;
  Zpeak+=1;
  if(pdgId==11){myEventsel.push_back(tree->eventId);}
  if(pdgId==13){myEventsmu.push_back(tree->eventId);}
  if(!hasGenHadron(tree)) continue;
  GenZhad+=1;


  //if(tree->eventId == 7967) continue;
  FatJet* jet = new FatJet(tree);
  bool passedID=0;
  bool passedKin=0;
  bool passedNear=0;
  bool passedSubj=0;
  bool passedMass=0;
  bool passedPrunedMass=0;
  int indexjet=0;
  for(int i=0;i<jet->Get_IndexMax();i++)
  {jet->Init(i,tree);
  //if(!jet->passedID()) continue;
   if(jet->passedID()){
  passedID=1;}
  if(!jet->passedNearness(lept,tree))continue;
  passedNear=1;
  if(!jet->passedKinematicCuts()) continue;
  passedKin=1;
  if(!jet->passedSubjettiness(isHP,isLP)) continue;
  passedSubj=1;
  if(!jet->passedPrunedMass()) continue;
  passedPrunedMass=1;
  if(!jet->isInMassRegion()) continue;
  passedMass =1;
  break;
  }
  if(passedID){
  JetID+=1;}
  if(passedNear){
  JetClean +=1;}
  if(passedKin){
  JetKin +=1;}
  if(passedSubj){
  JetSubj +=1;}
//   jet->Init(indexjet,tree);
//   if(!jet->isInMassRegion()) continue;
//   JetMass +=1;
  if(passedMass) {
  JetMass +=1;}
  if(passedPrunedMass) {
  JetPrunedMass+=1;}
  
  if(!HadronSelection(lept,tree, isHP, isLP)) continue;
  Jet+=1;
  
  Z_had = reconstructHadronicZ(lept, tree,isHP, isLP);
  if(!isHadronicZ(Z_had)) continue;
  ZhadKin+=1;
  if(!GravitonSelection(Z_had, Z_lep)) continue;
  Graviton+=1;
  }
   std::cout <<" All events " <<  AllEvts << std::endl;
std::cout <<" gen Z selection " << GenZlep << std::endl;
std::cout << " trigger " << HLT << std::endl;
std::cout << " lept selections " <<LeptSelections << std::endl;
std::cout << " Z lept sel " << Zpeak << std::endl;
std::cout << "GenZhad " << GenZhad <<std::endl;
std::cout << " jet id " <<  JetID << std::endl;
std::cout << " jet clean " <<  JetClean << std::endl;
std::cout << " jet kin " <<  JetKin << std::endl;
std::cout << " jet subj " << JetSubj << std::endl;
std::cout << " jet mass " << JetMass << std::endl;
std::cout << " jet pruned mass " << JetPrunedMass << std::endl;
std::cout << " jet sel " <<  Jet << std::endl;
std::cout << " Z had kin " <<  ZhadKin << std::endl;
std::cout << " Grav " << Graviton <<std::endl;
  
  if(pdgId == 13)
  {
  // ifstream joseMu ("/usr/users/dschaefer/root/data/list_BulkGrav_M-800_muChannel.txt");
//   vector<int> josesEvents = GetEventsFromFile(jose800TeVmu);
   ifstream joseMu ("/usr/users/dschaefer/root/data/list_BulkGrav_M-3500_muChannel.txt");
  
  // ifstream joseMu ("/usr/users/dschaefer/root/data/list_BulkGrav_M-1000_muChannel.txt");
  
  vector<int> josesEvents = GetEventsFromFile(joseMu);
  
  std::cout << " number of selected events jose " << josesEvents.size()<< std::endl;
  
  
  vector<int> missingEvents = compareLists(josesEvents, myEventsmu);
  std::cout<<"number of missing Events " << missingEvents.size()<< std::endl;
  vector<int> toomanyEvents = compareLists(myEventsmu,josesEvents);
  std::cout <<"number of events too many " << toomanyEvents.size()<<std::endl;
  
  
  ofstream file1;
  file1.open("missingEventsMuZZ.txt",ios::ate);
  WriteEventsToFile(missingEvents,file1);
  file1.close();
  
  ofstream file2;
  file2.open("toomanyEventsMuZZ.txt",ios::ate);
  WriteEventsToFile(toomanyEvents,file2);
  file2.close();
  }
  
  if(pdgId ==11)
  {
   //ifstream joseEl ("/usr/users/dschaefer/root/data/list_BulkGrav_M-800_elChannel.txt");
//   vector<int> josesEventsEl = GetEventsFromFile(jose800TeVel);
//   
 // ifstream joseEl ("/usr/users/dschaefer/root/data/list_BulkGrav_M-3500_elChannel.txt");
  ifstream joseEl ("/usr/users/dschaefer/root/data/list_BulkGrav_M-1000_elChannel.txt");
  
  vector<int> josesEventsEl = GetEventsFromFile(joseEl);
    
    
  std::cout << " number of selected events jose " << josesEventsEl.size() << std::endl;
  vector<int> missingEventsEL = compareLists(josesEventsEl, myEventsel);
  std::cout<<"number of missing Events " << missingEventsEL.size()<< std::endl;
  vector<int> toomanyEventsEL = compareLists(myEventsel,josesEventsEl);
  std::cout <<"number of events too many " << toomanyEventsEL.size()<<std::endl;
  
  
  ofstream file3;
  file3.open("missingEventsElZZ.txt",ios::ate);
  WriteEventsToFile(missingEventsEL,file3);
  file3.close();
  
  ofstream file4;
  file4.open("toomanyEventsElZZ.txt",ios::ate);
  WriteEventsToFile(toomanyEventsEL,file4);
  file3.close();
  }
  
 
}