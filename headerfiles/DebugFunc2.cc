#include "TTree.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "MyClass.h"
#include "Op.h"
#include "EventSelection.h"
#include "RecFunc.h"
#include "GenFunc.h"
#include "WWConstants.h"
#include "AllHadronicConstants.h"

using namespace std;


//============================================================================
void InfoEvent(int pdgId, int event, MyClass* t12, const char* filename)
{
  if(t12->EVENT_event == event)
{
  ofstream file2;
 file2.open(filename,ios::ate|ios::app);

 
        TLorentzVector W_had_gen = getLVofGenParticle(24,t12);
	TLorentzVector l_gen = getLVofGenParticle(pdgId,t12);
	TLorentzVector n_gen = getLVofGenParticle(pdgId+1,t12);
	TLorentzVector W_had = reconstructHadronicWOrZ(t12);
	TLorentzVector W_lep = reconstructLeptonicW(pdgId,t12);
	TLorentzVector l = reconstructLepton(pdgId,t12);
	TLorentzVector n = W_lep - l; 
  
  file2 <<  "event : " <<t12->EVENT_event  << " BV: " <<applyBVeto(t12)<<" LLV: "<< applyLooseLeptonVeto(pdgId,t12)<< " TR: "<< applyTrigger(pdgId,t12) <<" LS: "<< applyLeptonSelection_NoVeto(pdgId,t12) << " MET : " << applyMET(pdgId,t12)<< " HS :  "<< applyHadronSelection(t12)<<" gen B2B : "<< applyBackToBackTopology(l_gen,W_had_gen,l_gen+n_gen,n_gen) <<" rec B2B :  "<< applyBackToBackTopology(l ,W_had,W_lep,n) <<" Delta R (W_had,l) :  " << l.DeltaR(W_had) <<" Delta phi (W_had,W_lep) : "<< TMath::Abs(W_had.DeltaPhi(W_lep)) << " Delta Phi(W_had,MET) : "<<TMath::Abs(W_had.DeltaPhi(n)) <<std::endl;
  file2 << " W_lep pt : " << W_lep.Pt() << " MET : " << n.Pt() << "MET phi : "<< n.Phi() << std::endl;
	file2 << "      " << "  rec  " << "  gen " << std::endl;
	file2 << " pt:  " << W_had.Pt() <<" " << W_had_gen.Pt()<<std::endl;
	file2 << " eta:  " << W_had.Eta() <<" " << W_had_gen.Eta()<<std::endl;
	file2 << " phi:  " << W_had.Phi() <<" " << W_had_gen.Phi()<<std::endl;
	file2 << " mass:  " << W_had.M() <<" " << W_had_gen.M()<<std::endl;
  file2 << "lepton Candidate " << endl;
  if(pdgId==13)
  {
  for(int i=0;i<t12->mu_N;i++)
  {
   if(!isTightMuon(i,t12)) continue;
   file2 <<" pt : " << t12->mu_pt->at(i)<< " eta : " << t12->mu_eta->at(i)<< endl;
  }
  }
  if(pdgId==11)
  {
   for(int i=0;i<t12->el_N;i++)
  {
   if(!isTightElectron(i,t12)) continue;
   file2 <<" pt : " << t12->el_pt->at(i)<< " eta : " << t12->el_eta->at(i)<< endl;
  }
  }
  file2 << "AK8 jet Candidate " << endl;
  for(int i=0;i<t12->jetAK8_N;i++)
  {
  // if(!isRightAK8jet(i,t12)) continue;
   file2 << " jet number " << i << " pt : "<< t12->jetAK8_pt->at(i) << " eta : "<< t12->jetAK8_eta->at(i) <<" pruned mass : "<<t12->jetAK8_pruned_massCorr->at(i) << " isRightAK8jet : " << isRightAK8jet(i,t12)<< endl;
  }
    
  file2 << "AK4 jets " << endl;
  for(int i=0;i<t12->jetAK4_N;i++)
  {
   file2 <<"jet number " << i << " pt: "<< t12->jetAK4_pt->at(i) << " eta : "<< t12->jetAK4_eta->at(i) <<" b-tag : " << t12->jetAK4_cisv->at(i) <<" isVetoAK4jet : "<< isVetoAK4jet(i,t12) << endl; 
  }
  file2 << " all leptons " << std::endl;
  for(int i=0;i<t12->el_N;i++)
  {
    bool ElHeep6addition =0;
    if(TMath::Abs(t12->el_eta->at(i))< WWELEECALGAPMIN)
   {
     if(t12->el_hOverE->at(i)<(1/double(t12->el_e->at(i))+ 0.05))
       {ElHeep6addition =1;}
   }
 if(TMath::Abs(t12->el_eta->at(i))> WWELEECALGAPMAX)
   {
     if(t12->el_hOverE->at(i)<(5/double(t12->el_e->at(i))+0.05))
       {ElHeep6addition=1;}
   }
    
   file2 <<" electron number : " << i<<" pt : " << t12->el_pt->at(i)<< " eta : " << t12->el_eta->at(i)<< " phi : " << t12->el_phi->at(i)<< " isHeep5 : "<< t12->el_isHeep51Electron->at(i)<< " HoverE : "<< t12->el_hOverE->at(i) << " passed heep 6.0 : "<< ElHeep6addition /*<< "  iso : " << t12->el_trackIso->at(i)*/ << std::endl;
  }

 file2.close();
}
}

//================================================================================

void printInfoEventSemileptonic(int pdgId,int event,MyClass* t12,const char* filename)
{
   ofstream file2;
 file2.open(filename,ios::ate|ios::app);

 
        TLorentzVector W_had_gen = getLVofGenParticle(24,t12);
	TLorentzVector l_gen = getLVofGenParticle(pdgId,t12);
	TLorentzVector n_gen = getLVofGenParticle(pdgId+1,t12);
	TLorentzVector W_lep_gen = l_gen+n_gen;
	TLorentzVector W_had = reconstructHadronicWOrZ(t12);
	TLorentzVector W_lep = reconstructLeptonicW(pdgId,t12);
	TLorentzVector l = reconstructLepton(pdgId,t12);
	TLorentzVector n = W_lep - l; 
 
  file2 << "event : "<<event <<std::endl;
  file2 << "gen : " <<std::endl;
  file2 << " kin cuts lepton " << kinematicCuts(l_gen.Pt(),l_gen.Eta(),pdgId) <<std::endl;
  file2 << " kin cuts neutrino " << kinematicCuts(n_gen.Pt(),n_gen.Eta(),pdgId+1) << " MET : "<< n_gen.Pt()<<std::endl;
  file2 << " kin cuts W_had " <<kinematicCuts(W_had_gen.Pt(),W_had_gen.Eta(),1) <<std::endl;
  file2 << " kin cuts W_lep " <<kinematicCuts(W_lep_gen.Pt(),W_lep_gen.Eta(),24) <<std::endl;
  file2 << " B2B " << applyBackToBackTopology(l_gen,W_had_gen,W_lep_gen,n_gen)<<std::endl;
  bool passedMasscut = (((W_had_gen+W_lep_gen).M()>WWMASSMIN) and ((W_had_gen+W_lep_gen).M()<WWMASSMAX));
  file2 << " mass cuts " << passedMasscut<<std::endl;
  file2 << "rec : " <<std::endl;
  file2 << " kin cuts lepton " << kinematicCuts(l.Pt(),l.Eta(),pdgId) <<std::endl;
  file2 << " kin cuts neutrino " << kinematicCuts(n.Pt(),n.Eta(),pdgId+1)<< " MET : "<<n.Pt() <<std::endl;
  file2 << " kin cuts W_had " <<kinematicCuts(W_had.Pt(),W_had.Eta(),1) <<std::endl;
  file2 << " kin cuts W_lep " <<kinematicCuts(W_lep.Pt(),W_lep.Eta(),24) <<std::endl;
  file2 << " B2B " << applyBackToBackTopology(l,W_had,W_lep,n)<<std::endl;
  passedMasscut = (((W_had+W_lep).M()>WWMASSMIN) and ((W_had+W_lep).M()<WWMASSMAX));
  file2 << " mass cuts " << passedMasscut<<std::endl;
  file2<<std::endl;
  
}

//================================================================================

void printInfoEventHadronic(int event, MyClass* t12, ofstream &file)
{
 vector<int> index;
 //file << t12->EVENT_event << std::endl;
 if(t12->EVENT_event == event)
 {
   index = hadronicJetCandidates(t12);
   bool passedPres=0;
   if(index[0]>=0 and index[1]>=0)
   {passedPres=1;}
   file <<std::endl;
   file << std::endl;
   file<<" event : " << event << std::endl;
   file<<" passed preselections:  "<< passedPres << " passed Delta Eta_jj : " << AllHadPassedDEtajj(t12,index) << " passed Mjj : "<< AllHadPassedMjj(t12,index) << " passed pruned Mass cut : "<<AllHadPassedPrunedMassCut(t12,index) <<std::endl;
   file<< std::endl;
   file<< "info about AK8 jets : "<<std::endl;
   file << " jet Candidates indices : "<<index[0] << " "<< index[1] <<std::endl;
   int NJets = t12->jetAK8_N;
   vector<float>* jet_pt = t12->jetAK8_pt;
   vector<float>* jet_eta = t12->jetAK8_eta;
   vector<float>* jet_phi = t12->jetAK8_phi;
   vector<float>* jet_e = t12->jetAK8_e;
   vector<float>* jet_mass = t12->jetAK8_pruned_massCorr;
   vector<bool>*  jetID = t12->jetAK8_IDTight;
   TLorentzVector jet;
   
   for(int i =0;i<NJets;i++)
   {
     jet.SetPtEtaPhiE(jet_pt->at(i),jet_eta->at(i),jet_phi->at(i),jet_e->at(i));
    file << "index : "<< i <<" pt : "<<jet_pt->at(i) << " |eta| : "<< TMath::Abs(jet_eta->at(i)) << " ID tight : " << jetID->at(i) << " pruned Mass : "<< jet_mass->at(i) << " passed overlap : "<< passedOverlap(jet,t12) <<std::endl; 
     
   }
   if(passedPres)
   {
    TLorentzVector j1;
    TLorentzVector j2;
    j1.SetPtEtaPhiE(jet_pt->at(index[0]),jet_eta->at(index[0]),jet_phi->at(index[0]),jet_e->at(index[0]));
    j2.SetPtEtaPhiE(jet_pt->at(index[1]),jet_eta->at(index[1]),jet_phi->at(index[1]),jet_e->at(index[1]));
    file << " Delta Eta_jj : "<< TMath::Abs(j1.Eta()-j2.Eta()) << " Mjj : "<< (j1+j2).M() <<std::endl;
   }
 }
 //else 
 //{
  //file << " no event with this ID " <<std::endl; 
 //}
}

//================================================================================

void printEventList(int pdgId, vector<int> events, MyClass* t12, ofstream &file)
{
  
  for(int iii=0;iii<events.size();iii++)
  {
	  if(t12->EVENT_event != events.at(iii))
	    continue;
     
	TLorentzVector W_had_gen = getLVofGenParticle(24,t12);
	TLorentzVector l_gen = getLVofGenParticle(pdgId,t12);
	TLorentzVector n_gen = getLVofGenParticle(pdgId+1,t12);
	TLorentzVector W_had = reconstructHadronicWOrZ(t12);
	TLorentzVector W_lep = reconstructLeptonicW(pdgId,t12);
	TLorentzVector l = reconstructLepton(pdgId,t12);
	TLorentzVector n = W_lep - l; //recNeutrino(t12->MET_et->at(0), t12->MET_phi->at(0),l);


	file << "event : " <<t12->EVENT_event  << " BV: " <<applyBVeto(t12)<<" LLV: "<< applyLooseLeptonVeto(pdgId,t12)<< " TR: "<< applyTrigger(pdgId,t12) <<" LS: "<< applyLeptonSelection_NoVeto(pdgId,t12) << " MET : " << applyMET(pdgId,t12)<< " HS :  "<< applyHadronSelection(t12)<<" gen B2B : "<< applyBackToBackTopology(l_gen,W_had_gen,l_gen+n_gen,n_gen) <<" rec B2B :  "<< applyBackToBackTopology(l ,W_had,W_lep,n) <<std::endl;
  }
}


//===================================================================================

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
//=======================================================================================

void WriteEventsToFile(vector<int> events, ofstream  &myfile)
{
  for(int i=0;i<events.size();i++)
  {
    myfile << events.at(i) << std::endl;
  }
  
}

