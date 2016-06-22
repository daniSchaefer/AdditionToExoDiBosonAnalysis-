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
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
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
  gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.cc+");

 
 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}

void debugHadEff()
{
  string filename ="/storage/jbod/dschaefer/Res_Sig/BulkGravToWW_narrow_M-2000_13TeV-madgraph_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/EXOVVTree_BulkGravToWW_narrow_M-2000_13TeV-madgraph_RunIIFall15MiniAODv1_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_1.root";
  
  //string filename ="/storage/jbod/dschaefer/Res_Sig/RadionToWW_narrow_M-4000_13TeV-madgraph_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/EXOVVTree_RadionToWW_narrow_M-4000_13TeV-madgraph_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_1.root";

  
  
  
  
  //string filename = "/storage/jbod/dschaefer/Res_Sig/RadionToWW_width0p1_M-2000_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/EXOVVTree_RadionToWW_width0p1_M-2000_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_1.root";

  
  
  TChain tree("ntuplizer/tree");
  tree.Add(filename.c_str());
  
  MyClass* t12 = new MyClass(&tree);
  
  int howmany = t12->fChain->GetEntries();
  std::cout<< "# events overall "<< howmany << std::endl;
  TLorentzVector Vplus;
  TLorentzVector Vminus;
  TLorentzVector jet1;
  TLorentzVector jet2;
  int events=0;
  int selected_events=0;
  int eventsVminusMatched=0;
  int eventsVplusMatched=0;
  int numberOfEventsWithBothJetsNotMatched=0;
  int numberBothVmatchjet1=0;
  int numberBothVmatchjet2=0;
  int numberOfEventsWithJet1NotMatched=0;
  int numberOfEventsWithJet2NotMatched=0;
  int veto=0;
  int veto_denom=0;
  int eventsWithWplusPtGreaterWminusPtgen =0;
  
  TFile test("testBulkGravM2000.root","RECREATE");
  TH2F* had_reco_Vplus = new TH2F("had_reco_Vplus","V_plus",4000,0,4000,100,0,2.4);
  TH2F* had_reco_Vminus = new TH2F("had_reco_Vminus","V_minus",4000,0,4000,100,0,2.4);
  
  TH2F* had_gen_Vplus = new TH2F("had_gen_Vplus","V_plus",4000,0,4000,100,0,2.4);
  TH2F* had_gen_Vminus = new TH2F("had_gen_Vminus","V_minus",4000,0,4000,100,0,2.4);
  
  for(int i=0;i<howmany;i++)
  {
    t12->fChain->GetEntry(i);
    if(!genEventSelectionInclusive(t12,"jjjj"))
      continue;
   Vplus = getGenLV_V1(t12);
   Vminus = getGenLV_V2(t12);
   vector<float>* jet_pt = t12->jetAK8_pt;
   vector<float>* jet_eta = t12->jetAK8_eta;
   vector<float>* jet_phi = t12->jetAK8_phi;
   vector<float>* jet_e = t12->jetAK8_e;
  
   if(!applyGeneratorKinematicSelectionsAllHad(Vplus,Vminus))
     continue;

   had_gen_Vminus->Fill(Vminus.Pt(),Vminus.Eta());
   had_gen_Vplus->Fill(Vplus.Pt(),Vplus.Eta());
   events+=1;
   if(Vplus.Pt()>Vminus.Pt())
   {
    eventsWithWplusPtGreaterWminusPtgen+=1; 
   }
   
    if(!applyTriggerAllHadronic(t12))
      continue;
    int index1 = findFirstJet(t12);
    int index2 = findSecondJet(t12);
     if(index1==-99)
       continue;
     if(index2==-99)
      continue;
    jet2.SetPtEtaPhiE(jet_pt->at(index2),jet_eta->at(index2),jet_phi->at(index2),jet_e->at(index2));
    jet1.SetPtEtaPhiE(jet_pt->at(index1),jet_eta->at(index1),jet_phi->at(index1),jet_e->at(index1));
    
    if(applyPrunedMassCutAndSubjettinessHighPurity(index1,t12))
    { 
    
      if(isMatched(Vplus,jet1))
      {
	eventsVplusMatched+=1;
      }
      if(isMatched(Vminus,jet1))
      {
	eventsVminusMatched+=1;
      }
      if(!isMatched(Vminus,jet1) and !isMatched(Vplus,jet1))
      {
	numberOfEventsWithJet1NotMatched+=1;
      }
      if(isMatched(Vminus,jet1) and isMatched(Vplus,jet1))
      {
	numberBothVmatchjet1+=1;
      }
    }
    //===========================================================================================
    
    
    //============= find second jet that passed m_pruned and tau21 cuts? ==========================
    if(applyPrunedMassCutAndSubjettinessHighPurity(index2,t12))
    {
      if(isMatched(Vplus,jet2))
      {
	eventsVplusMatched+=1;
      }
      if(isMatched(Vminus,jet2))
      {
	eventsVminusMatched+=1;
      }
      if(!isMatched(Vminus,jet2) and !isMatched(Vplus,jet2))
      {
	numberOfEventsWithJet2NotMatched+=1;
	
	if(!isMatched(Vminus,jet1) and !isMatched(Vplus,jet1))
	{
	  numberOfEventsWithBothJetsNotMatched+=1;
	}
      }
       if(isMatched(Vminus,jet2) and isMatched(Vplus,jet2))
      {
	numberBothVmatchjet2+=1;
      }
      
    }
    
    
    //=================================================================================================
    
    if(!applyPrunedMassCutAndSubjettinessHighPurity(index1,t12) or !applyPrunedMassCutAndSubjettinessHighPurity(index2,t12))
      continue;
    veto_denom+=1;
    vector<int> index = {index1,index2};
    if(!AllHadPassedDEtajj(t12,index))
      continue;
    if(!AllHadPassedMjj(t12,index))
      continue;
    veto+=1;
    
    //================================================================================================
   
    selected_events+=1;
    had_reco_Vplus->Fill(Vplus.Pt(),Vplus.Eta());
    had_reco_Vminus->Fill(Vminus.Pt(),Vminus.Eta());
     
  }

  had_reco_Vminus->Write();
  had_reco_Vplus->Write();
  had_gen_Vminus->Write();
  had_gen_Vplus->Write();
  
  std::cout << "# events genererated : "<< events <<std::endl;
  std::cout << "# events Vplus rec. : " << eventsVplusMatched << std::endl;
  std::cout << "# events Vminus rec. : "<< eventsVminusMatched <<std::endl;
  std::cout << "# all selections applied : "<< selected_events <<std::endl;
  
  
 std::cout <<std::endl;
 std::cout << " veto efficiency : " << veto/double(veto_denom) <<std::endl;
 float effjet1 = eventsVplusMatched/double(events);
 float effjet2 = eventsVminusMatched/double(events);
 std::cout << " efficiency Vplus " << effjet1 << std::endl;
 std::cout << " efficiency vminus " << effjet2 <<std::endl;
 double effreco = selected_events/double(events);
 double effWpm = effjet1*effjet2*veto/double(veto_denom);
 std::cout << " efficiency overal " <<  selected_events/double(events) << "  " << effjet1*effjet2*veto/double(veto_denom) << "    "<< (effreco-effWpm)/effWpm*100  <<std::endl;
 std::cout << eventsWithWplusPtGreaterWminusPtgen/double(events)*100 << "% of events have Wplus Pt > Wminus Pt " <<std::endl;
 
 
}