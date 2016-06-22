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
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
#include "/usr/users/dschaefer/root/headerfiles/MyClass.h"
#include "/usr/users/dschaefer/root/headerfiles/Op.h"
#include "/usr/users/dschaefer/root/headerfiles/EventSelection.h"
#include "/usr/users/dschaefer/root/headerfiles/GenFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/RecFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc2.h"
#include "/usr/users/dschaefer/root/headerfiles/passed_mu_jes.h"

using namespace std;


// note to this construct:
// is needed in this version of root in order to get the header functions right
//also the order in which these files are compiled matters!
namespace{
  int loadMyLibraryTriggerFunc(){
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/General.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/Op.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/EventSelection.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/GenFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/RecFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc+");
 gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc2.cc+");

 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void debugHad()
{
 // string filename = "/storage/jbod/dschaefer/Res_Sig/EXOVVTree_BulkGravToWW_narrow_M-1800_13TeV-madgraph_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_1.root";
  string filename = "/storage/jbod/dschaefer/Res_Sig/RSGravToWW_width0p1_M-2000_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/EXOVVTree_RSGravToWW_width0p1_M-2000_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_1.root";

  
  
  TChain tree("ntuplizer/tree");
  tree.Add(filename.c_str());
  
  MyClass* t12 = new MyClass(&tree);
  
  int numberHad =0;
  int numberHadPreselection=0;
  int numberHadTrigger =0;
  int numberHadDetajj=0;
  int numberHadMjj=0;
  int numberHadPrunedMassCut=0;
  int howmany = t12->fChain->GetEntries();
  int help=0;
  //int howmany = 12;
  vector<int> listOfPreselectedEvents;
  vector<int> listOfEventsDEtajj;
  vector<int> listOfEventsMjj;
  vector<int> listOfEventsPrunedMass;
  
  std::cout<< "# events overall "<< howmany << std::endl;
  
 ofstream debugfile;
 debugfile.open("test.txt",ios::ate);
  
  for(int i=0;i<howmany;i++)
  {
    t12->fChain->GetEntry(i);
    int jetN = t12->jetAK8_N;
    //std::cout << t12->EVENT_event <<std::endl;
    if(i<20)
    {
      get_pdgId("testWideSample.txt",t12);
    }
    
    for(int loop =0; loop<20;loop++)
    {
    printInfoEventHadronic(loop,t12,debugfile);
    }
    //if(!genEventSelectionInclusive(t12,"jjjj"))
     // continue;
    numberHad +=1;
    // if(!applyTriggerAllHadronic(t12))
      // continue;
      
     //  if(!passedAllHadronicSelections(t12))
	// continue;
       
        numberHadTrigger +=1;
       vector<int> indices = hadronicJetCandidates(t12);

     if(indices[0]==-99 or indices[1] ==-99)
       continue;
      numberHadPreselection+=1;
      listOfPreselectedEvents.push_back(t12->EVENT_event);
     if(!AllHadPassedDEtajj(t12,indices))
       continue;
     numberHadDetajj+=1;
     listOfEventsDEtajj.push_back(t12->EVENT_event);
     
      if(!AllHadPassedMjj(t12,indices))
       continue;
     numberHadMjj+=1;
     listOfEventsMjj.push_back(t12->EVENT_event);
     
     if(!AllHadPassedPrunedMassCut(t12,indices))
       continue;
     numberHadPrunedMassCut+=1;
     listOfEventsPrunedMass.push_back(t12->EVENT_event);
     
  
  }
  debugfile.close();
  std::cout<< "number after generated hadronic selections "<< numberHad <<std::endl;
   std::cout << "number after Triggers applied " << numberHadTrigger <<std::endl;
  std::cout << "number after preselections " << numberHadPreselection <<std::endl;
  std::cout << "number after Delta Eta_jj " << numberHadDetajj <<std::endl;
  std::cout << "number after Mjj " << numberHadMjj <<std::endl;
  std::cout << "number after pruned Mass cut " << numberHadPrunedMassCut <<std::endl;
  std::cout << listOfPreselectedEvents.size() <<std::endl;
  std::cout << listOfEventsDEtajj.size() <<std::endl;
  std::cout << listOfEventsMjj.size() <<std::endl;
  std::cout << listOfEventsPrunedMass.size() <<std::endl;
  
  ifstream eventList("eventList2.txt");
  vector<int> theaEvents = GetEventsFromFile(eventList);
  std::cout << " thea's number of event last selection cut " << theaEvents.size()<<std::endl;
  
  vector<int> missingEvents = compareLists(theaEvents,listOfEventsPrunedMass);
  vector<int> toomanyEvents = compareLists(listOfEventsPrunedMass,theaEvents);
  
  ofstream file3;
  file3.open("missingEvents.txt",ios::ate);
  WriteEventsToFile(missingEvents,file3);
  file3.close();
  
  ofstream file4;
  file4.open("toomanyEvents.txt",ios::ate);
  WriteEventsToFile(toomanyEvents,file4);
  file4.close();
  
  
  
}