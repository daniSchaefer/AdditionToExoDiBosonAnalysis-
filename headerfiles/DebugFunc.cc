#include "MyClass.h"
#include "passed_mu_jes.h"
#include "DebugFunc.h"
#include "TChain.h"
#include "TTree.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "MyClass.h"
#include "RecFunc.h"
#include "GenFunc.h"
#include "Op.h"
#include "EventSelection.h"
#include "WWConstants.h"

using namespace std;


//============================================================================

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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------




void get_pdgId(vector<int> event, string name_output_file, MyClass* t12)
{


  //write the pdgId of event in file "name_output_file"
  ofstream file;
  file.open(name_output_file,ios::ate);
  //get pdgId

 for(int h =0;h<event.size();h++)
   {
     t12->fChain->GetEntry(event.at(h));
     for(int i=0;i<80;i++)
       {file <<"-" ;}
     file << endl;
     for(int i=0;i<80;i++)
       {file <<"-" ;}
     file << endl;
     file<< "event " << event.at(h) << endl;
     file << t12->genParticle_N << " = number of particles" << endl;
     file << endl;


	  //loop over particles in event
	  for(int k =0;k<t12->genParticle_N ;k++)
	    {
	      for(int i=0;i<80;i++)
	  	{file <<"-" ;}
	      file << endl;
	      file << "pdgId " << t12->genParticle_pdgId->at(k) << endl;
	      for(int i=0;i<80;i++)
	  	{file <<"-" ;}
	      file << endl;
	      file <<"# of mother particles " << t12->genParticle_nMoth->at(k)<<endl;
	   
	      if(t12->genParticle_nMoth->at(k) != 0)
	  	{
	  	  vector<int> tmp_moth =t12->genParticle_mother->at(k);
		  
	  	  for(int i=0;i<tmp_moth.size();i++)
	  	    {
	  	      file <<tmp_moth.at(i)<< " , ";
	  	    }
	  	  file << " size of vector " << tmp_moth.size()<<endl;
		  
	  	  file << endl;
	  	}
	      file <<"# of daughter particles " << t12->genParticle_nDau->at(k)<<endl;
	      if(t12->genParticle_nDau->at(k) != 0)
	  	{
	     
	  	  vector<int> tmp_dau =t12->genParticle_dau->at(k);
		 
	  	  for(int i=0;i<tmp_dau.size();i++)
	  	    {
	  	      file << tmp_dau.at(i)<< " , ";
	  	    }
	  	  file << " size of vector " << tmp_dau.size()<<endl;
	
	  	}
	      file << endl;
	    }

 for(int i=0;i<80;i++)
   {file <<"-" ;}
 file << endl;
 for(int i=0;i<80;i++)
   {file <<"-" ;}
 file << endl;
   }
 file.close();
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------




void get_pdgId( string name_output_file, MyClass* t12)
{


  //write the pdgId of event in file "name_output_file"
  ofstream file;
  file.open(name_output_file,ios::app);
  //get pdgId

     for(int i=0;i<80;i++)
       {file <<"-" ;}
     file << endl;
     for(int i=0;i<80;i++)
       {file <<"-" ;}
     file << endl;
     file<< "event " << t12->EVENT_event << endl;
     file << t12->genParticle_N << " = number of particles" << endl;
     file << endl;


	  //loop over particles in event
	  for(int k =0;k<t12->genParticle_N ;k++)
	    {
	      for(int i=0;i<80;i++)
	  	{file <<"-" ;}
	      file << endl;
	      file << "particle number " <<k <<"  pdgId " << t12->genParticle_pdgId->at(k) <<" pt "<< t12->genParticle_pt->at(k) <<endl;
	      for(int i=0;i<80;i++)
	  	{file <<"-" ;}
	      file << endl;
	      file <<"# of mother particles " << t12->genParticle_nMoth->at(k)<<endl;
	   
	      if(t12->genParticle_nMoth->at(k) != 0)
	  	{
	  	  vector<int> tmp_moth =t12->genParticle_mother->at(k);
		  
	  	  for(int i=0;i<tmp_moth.size();i++)
	  	    {
	  	      file <<tmp_moth.at(i)<< " , ";
	  	    }
	  	  file << " size of vector " << tmp_moth.size()<<endl;
		  
	  	  file << endl;
	  	}
	      file <<"# of daughter particles " << t12->genParticle_nDau->at(k)<<endl;
	      if(t12->genParticle_nDau->at(k) != 0)
	  	{
	     
	  	  vector<int> tmp_dau =t12->genParticle_dau->at(k);
		 
	  	  for(int i=0;i<tmp_dau.size();i++)
	  	    {
	  	      file << tmp_dau.at(i)<< " , ";
	  	    }
	  	  file << " size of vector " << tmp_dau.size()<<endl;
	
	  	}
	      file << endl;
	    }

 for(int i=0;i<80;i++)
   {file <<"-" ;}
 file << endl;
 for(int i=0;i<80;i++)
   {file <<"-" ;}
 file << endl;
   
 file.close();
}


// ------------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool isEventInList(int event, vector<int> listOfEvents)
{
  for(int i=0;i<listOfEvents.size();i++)
    {
      if(listOfEvents.at(i)== event)
	return 1;
    }
  return 0;
}



// ------------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool isEventInList(double pt, double eta, vector<double> list_pt, vector<double> list_eta)
{
  for(int i=0;i<list_pt.size();i++)
    {
      if(list_pt.at(i)== pt && list_eta.at(i) == eta)
      {return 1;
	break;
      }
    }
  return 0;
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

vector<int> compareLists(vector<int> events, vector<double> list1_pt, vector<double> list1_eta, vector<double> list2_pt, vector<double> list2_eta)
{
  vector<int> result={};
  
  for(int i=0;i<list1_pt.size();i++)
    {
      if(isEventInList(list1_pt.at(i),list1_eta.at(i), list2_pt, list2_eta)==0)
	{result.push_back(events.at(i));}
    }
 
      return result;
}

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

void SetTreeToEvent(int event,MyClass* t12)
{ 
  int N = t12->fChain->GetEntries();
  for(int i=0;i<N;i++)
  {
    t12->GetEntry(i);
    if(t12->EVENT_event == event)
    {break;}
  }

}

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

void SetTreeToEvent(int event,passed_mu_jes * t12)
{ 
  int N = t12->fChain->GetEntries();
  for(int i=0;i<N;i++)
  {
    t12->GetEntry(i);
    if(t12->event == event)
    {break;}
  }

}

//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------

vector<vector<int> > missingEvents(MyClass* t12, passed_mu_jes* t, int pdgId, bool isHP, bool isLP)
{
   vector<vector<int> > result(2);
   //vector<int> gen_event ={};
   //vector<int> jes_event={};
   int howmany = t->fChain->GetEntries();
   int howmany2 = t12->fChain->GetEntries();
   int howmanyEvents=0;
 for(int i=0;i<howmany;i++)
 {

   t->fChain->GetEntry(i);
   //jes_event.push_back(t->event);
   result[0].push_back(t->event);
 }
  
  for(int i=0;i<howmany2;i++)
 {
    
   t12->fChain->GetEntry(i);
   //if(generatedEventSelection(pdgId,t12)==0)
    // continue;
   if(applyBVeto(t12)==0)
     continue;
   if(applyLeptonSelection_NoVeto(pdgId,t12)==0)
     continue;
    if(applyLooseLeptonVeto(pdgId,t12)==0)
     continue;
   if(applyMET(pdgId,t12)==0)
     continue;
   if(applyTrigger(pdgId,t12)==0)
     continue;
     //hadron Selection for debugging purposes
   if(applyHadronSelection(t12,isHP,isLP)==0)
     continue;
	TLorentzVector W_had = reconstructHadronicWOrZ(t12);
	TLorentzVector W_lep = reconstructLeptonicW(pdgId,t12);
	TLorentzVector l     = reconstructLepton(pdgId,t12);
	TLorentzVector n = W_lep - l;

	if(!applyBackToBackTopology(l ,W_had,W_lep,n))
		continue;
  howmanyEvents +=1;
  //gen_event.push_back(t12->EVENT_event);
  result[1].push_back(t12->EVENT_event);
 }
 
  std::cout<<"# of events that pass all selections "<<howmanyEvents<< std::endl;
  return result;
   //result[0] = compareLists(jes_event,gen_event);

  //return compareLists(gen_event,jes_event);
}
//=================================================================================
vector<double> testSelfConsistency( int pdgId, MyClass* t12,vector<vector<double> > leptonEff, vector<vector<double> > hadronEff, double BVEff, double LLVEff ,bool isHP, bool isLP)
{
  int howmany = t12->fChain->GetEntries();
  int howmanyEvents =0;
  int howmanyPassedEvents =0;
  double eventsReweighted = 0.0;
  double wHad = 0.0;
  double wLep = 0.0;
   for(int i=0;i<howmany;i++)
 {
    
   t12->fChain->GetEntry(i);
   
   
   TLorentzVector W_had_gen = getLVofGenParticle(24,t12);
   if(W_had_gen.M()==0){W_had_gen = getLVofGenParticle(23,t12);}
   TLorentzVector l_gen = getLVofGenParticle(pdgId,t12);
   TLorentzVector n_gen = getLVofGenParticle(pdgId+1,t12);
   TLorentzVector W_lep_gen = l_gen + n_gen; 
   Double_t WWmass = (W_had_gen + W_lep_gen).M();
 
   if(W_had_gen.M()!=0 and W_lep_gen.M() != 0)
   {
      if(generatedEventSelection(pdgId,t12))
      //if(applyBackToBackTopology(l_gen,W_had_gen,W_lep_gen,n_gen) and WWmass< WWMASSMAX and WWmass> WWMASSMIN)
      {
	for(int loop=0;loop<leptonEff[0].size();loop++)
	{
	if(W_lep_gen.Pt()>= leptonEff[1][loop]) continue;
	if(TMath::Abs(W_lep_gen.Eta())>= leptonEff[3][loop]) continue;
	wLep = leptonEff[4][loop];
	break;
	}
	for(int loop=0;loop<hadronEff[0].size();loop++)
	{
	  if(W_had_gen.Pt()>= hadronEff[1][loop]) continue;
	  if(TMath::Abs(W_had_gen.Eta())>= hadronEff[3][loop]) continue;
	  wHad = hadronEff[4][loop];
	  break;
	}
      eventsReweighted += 1*wHad*wLep*BVEff*LLVEff; 
      }
   }
    howmanyEvents +=1;
   if(generatedEventSelection(pdgId,t12)==0) continue;
   if(applyBVeto(t12)==0) continue;
   if(applyLooseLeptonVeto(pdgId,t12)==0) continue;
   if(applyLeptonSelection_NoVeto(pdgId,t12)==0) continue;
   if(applyMET(pdgId,t12)==0) continue;
   if(applyTrigger(pdgId,t12)==0) continue;
     //hadron Selection for debugging purposes
   if(applyHadronSelection(t12,isHP,isLP)==0) continue;
	TLorentzVector W_had = reconstructHadronicWOrZ(t12);
	TLorentzVector W_lep = reconstructLeptonicW(pdgId,t12);
	TLorentzVector l     = reconstructLepton(pdgId,t12);
	TLorentzVector n = W_lep - l;

    if(!applyBackToBackTopology(l ,W_had,W_lep,n)) continue;
    howmanyPassedEvents +=1;
 }
  std::cout<<"number of passed events "<< howmanyPassedEvents << std::endl;
  std::cout <<" number of events in file " << howmanyEvents << std::endl;
  std::cout << " number of events where each event is weighted with the efficiency for its reconstruction " << eventsReweighted << std::endl;
  std::cout << "sum over reweighted events/ number of passed events "<< eventsReweighted/double(howmanyPassedEvents)<<std::endl;
  vector<double> result ={eventsReweighted,double(howmanyPassedEvents)};
  return result;
}
