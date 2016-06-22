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
#include <sys/stat.h>
#include <unistd.h>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
#include "/usr/users/dschaefer/root/headerfiles/MyClass.h"
//#include "/usr/users/dschaefer/root/headerfiles/passed_mu_jes.h"
#include "/usr/users/dschaefer/root/headerfiles/Op.h"
#include "/usr/users/dschaefer/root/headerfiles/EventSelection.h"
#include "/usr/users/dschaefer/root/headerfiles/GenFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/RecFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc2.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"
//#include "/usr/users/dschaefer/root/headerfilesZZ/ZZtree.h"
#include "/usr/users/dschaefer/root/headerfiles/WWConstants.h"
#include "/usr/users/dschaefer/root/headerfiles/AllHadronicConstants.h"


bool isMatched(TLorentzVector W, TLorentzVector jet)
{
  bool passed=0;
  if(W.DeltaR(jet)<1.0)
  {
    passed =1; 
  }
  return passed;
}


//================================================================================================

bool isMatchedJet(MyClass* t12, bool isW, bool isZ)
{
  bool isMatched=0;
  TLorentzVector W_rec = reconstructHadronicWOrZ(t12, isW,isZ);
  TLorentzVector W_gen = getLVofGenParticle(24,t12);
  double DR = W_gen.DeltaR(W_rec);
  if(DR<0.8)
  {isMatched =1;}
  return isMatched;

}

//=================================================================================================

bool hasMatchedJetsAllHad(MyClass*t12)
{
 bool isMatched=0;
 TLorentzVector V1 = getGenLV_V1(t12);
 TLorentzVector V2 = getGenLV_V2(t12);
 TLorentzVector jet1 = reconstructV1(t12);
 TLorentzVector jet2 = reconstructV2(t12);
 
 double DR1 = V1.DeltaR(jet1);
 double DR2 = V2.DeltaR(jet2);
 if(DR1<0.8 and DR2<0.8)
 {
  isMatched =1; 
 }
  return isMatched;
}

//================================================================================================

void WEfficiencyGetMCEffperSample(int pdgId,const char* input_filename,ofstream &f)
{
  TChain tree("ntuplizer/tree");
   tree.Add(input_filename);
  
  MyClass* t12 = new MyClass(&tree);

int howmany = t12->fChain->GetEntries();

 
 TLorentzVector W_lep;
 TLorentzVector W_had;
 TLorentzVector l;
 int help=0;
 int help2=0;
 int help3=0;
 
 
 int eventNumber=0;
 int NumberOfEventsRightLepton =0;
 

 
 for(int i=0;i<howmany;i++)
   {
      
      t12->fChain->GetEntry(i);
      eventNumber +=1;
 
     if(generatedEventSelection(pdgId,t12)==0)
       continue;
     
     NumberOfEventsRightLepton+=1;
 
     if(applyBVeto(t12)==0) continue;
     
     if(applyLooseLeptonVeto(pdgId,t12)==0) continue;
     
     if(!applyVetos(pdgId,t12)) continue;
  
     if(applyLeptonSelection_NoVeto(pdgId,t12)==0 and applyMET(pdgId,t12)==0 and applyTrigger(pdgId,t12)==0) continue;
     W_lep = reconstructLeptonicW(pdgId,t12);
     if(W_lep.Pt()<200) continue;
     
     if(applyHadronSelection(t12,1,0,1,1)==0) continue;
     W_had = reconstructHadronicWOrZ(t12,1,1);
     if(W_had.Pt()<200)    continue;
	  help3+=1;
	
       
  }
  
 
 f<<NumberOfEventsRightLepton/double(eventNumber)<<std::endl;
 f<< help3/double(NumberOfEventsRightLepton) << std::endl;
 
}

//=========================================================================================

double NumberOfEventsInFile(string ModelName,string decayMode,float mass,float width)
{
    string smass = std::to_string(int(mass));
  int temp_width = width*10;
  string swidth = std::to_string(temp_width);
  //string directory ="/storage/a/mmozer/Res_Sig/";
  string directory ="/storage/jbod/dschaefer/Res_Sig/";
  string sfileName= 	getFileName(directory,ModelName,decayMode,mass,width,1);
  string sfileName1= 	getFileName(directory,ModelName,decayMode,mass,width,2);
  string sfileName2= 	getFileName(directory,ModelName,decayMode,mass,width,3);
  int howmany =0;
  
  int isGood=0;
  ifstream f(sfileName.c_str());
  if(f.good())
  {
   isGood+=1;
   f.close();
  }
  if(!isGood)
  {
    directory = "/storage/jbod/dschaefer/Res_Sig/";
    sfileName= 	getFileName(directory,ModelName,decayMode,mass,width,1);
    sfileName1= getFileName(directory,ModelName,decayMode,mass,width,2);
    sfileName2= getFileName(directory,ModelName,decayMode,mass,width,3);
  }
  isGood =0;
  f.open(sfileName1.c_str());
  if(f.good())
  {
    isGood +=1;
    f.close();
  }
  f.open(sfileName2.c_str());
  if(f.good())
  {
   isGood +=1;
   f.close();
  }
  //std::cout<<isGood<<std::endl;
  const char* fileName = sfileName.c_str();
  const char* fileName2 = sfileName1.c_str();
  const char* fileName3 = sfileName2.c_str();
  
  if(decayMode.find("lvjj") !=string::npos or decayMode.find("jjjj")!=string::npos)
  {
  TChain tree("ntuplizer/tree");
  if(width <0.1 or isGood ==0)
  {
    tree.Add(fileName);
  }
  if(isGood ==1)
  {
    tree.Add(fileName2);
   tree.Add(fileName);
  }
  else if(isGood>1 and width>=0.1)
  {
   tree.Add(fileName2);
   tree.Add(fileName);
   tree.Add(fileName3);
  }
 
  
  MyClass* t12 = new MyClass(&tree);
  howmany = t12->fChain->GetEntries();
  }
//   if(decayMode.find("jjjj")!=string::npos)
//   {
//    int tmp =0;
//    TChain tree("ntuplizer/tree");
//    if(width <0.1 or isGood ==0)
//   {
//     tree.Add(fileName);
//   }
//   if(isGood ==1)
//   {
//     tree.Add(fileName2);
//    tree.Add(fileName);
//   }
//   else if(isGood>1 and width>=0.1)
//   {
//    tree.Add(fileName2);
//    tree.Add(fileName);
//    tree.Add(fileName3);
//   }
//   MyClass* t12 = new MyClass(&tree);
//   tmp = t12->fChain->GetEntries();
//   for(int i=0;i<tmp;i++)
//   {
//     if(!genEventSelectionInclusive(t12,"jjjj")) continue;
//     howmany+=1;
//   }
//     
//   }
//   if(decayMode.find("lljj")!=string::npos)
//   {
//   TChain tree("tree/treeMaker");
//   if(width <0.1 or isGood ==0)
//   {
//     tree.Add(fileName);
//   }
//   if(isGood ==1)
//   {
//     tree.Add(fileName2);
//    tree.Add(fileName);
//   }
//   else if(isGood>1 and width>=0.1)
//   {
//    tree.Add(fileName2);
//    tree.Add(fileName);
//    tree.Add(fileName3);
//   }
//  
//   
//   ZZtree* t12 = new ZZtree(&tree);
//   howmany = t12->fChain->GetEntries();
//     
//   }
  
  
  return howmany;
}
//=========================================================================================

void makeRootFileForCheckFitCBBW_genMC_withSelection(string ModelName,string channel,string category,string decayMode,float mass, float width)
{
 makeRootFileForCheckFitCBBW(ModelName, channel,category,decayMode ,mass ,width,0,1,0); 
}

//=========================================================================================

void makeRootFileForCheckFitCBBW_genMC_withoutSelection(string ModelName,string channel,string category,string decayMode,float mass, float width)
{
makeRootFileForCheckFitCBBW(ModelName, channel,category,decayMode, mass ,width,0,0,1); 
}

//=========================================================================================

void makeRootFileForCheckFitCBBW_recMC_matched(string ModelName,string channel,string category,string decayMode,float mass, float width)
{
 makeRootFileForCheckFitCBBW(ModelName, channel,category,decayMode, mass ,width,1,0,0);  
}

//=========================================================================================
void makeRootFileForCheckFitCBBW_matching_withoutSelection(string ModelName,string channel,float mass, float width)
{
  string smass = std::to_string(int(mass));
  int temp_width = width*10;
  string swidth = std::to_string(temp_width);
  //string directory ="/storage/a/mmozer/Res_Sig/";
  string directory ="/storage/jbod/dschaefer/Res_Sig/";
  string decayMode = "WW_lvjj";
  string sfileName= 	getFileName(directory,ModelName,decayMode,mass,width,1);
  string sfileName1= 	getFileName(directory,ModelName,decayMode,mass,width,2);
  string sfileName2= 	getFileName(directory,ModelName,decayMode,mass,width,3);
  string soutput_filename = "/usr/users/dschaefer/root/results/"+ModelName+"/"+ModelName+"_M"+smass+"_width0p"+swidth+"_mWW_"+channel+"_jetMatchingNoSelections.root";
  
 
   std::cout <<"run sample "<<ModelName<<" mass = "<<smass << ", width = "<<swidth <<" channel = " <<channel << std::endl;
  
  
  const char* fileName = sfileName.c_str();
  const char* fileName2 = sfileName1.c_str();
  const char* fileName3 = sfileName2.c_str();
  const char* output_filename = soutput_filename.c_str();

  
  TFile mWWSpectrum(output_filename,"RECREATE");
  TH1F* hmWW= new TH1F("hmWW_full","mWW spectrum",1000,0,13000);
  
   int numberFiles=1;
  ifstream fTEST(fileName2);
  if(fTEST.good())
  {
    numberFiles+=1;
    fTEST.close();
  }
  fTEST.open(fileName3);
  if(fTEST.good())
  {
    numberFiles+=1;
    fTEST.close();
  }
  
  
  TChain tree("ntuplizer/tree");
  if(numberFiles ==1)
  {
  tree.Add(fileName);
  }
  if(numberFiles==2)
  {
   tree.Add(fileName2);
   tree.Add(fileName);
  }
   if(numberFiles==3)
  {
   tree.Add(fileName2);
   tree.Add(fileName);
   tree.Add(fileName3);
  }
 
  
  MyClass* t12 = new MyClass(&tree);
  int howmany = t12->fChain->GetEntries();
  TLorentzVector W_had_gen;
  TLorentzVector W_lep_gen;
  
  int pdgId= 13;
  if(channel.find("el") != string::npos)
  {pdgId =11;}
  TLorentzVector W_lep;
  TLorentzVector W_had;
  for(int i=0;i<howmany;i++)
  {
  
    t12->fChain->GetEntry(i);
  
   W_had_gen = getLVofGenParticle(24,t12);
   if(W_had_gen.Pt() ==0)
   {
     W_had_gen = getLVofGenParticle(23,t12);
   }
   W_lep_gen = getLVofGenParticle(pdgId,t12)+ getLVofGenParticle(pdgId+1,t12);
   
   //mass cut on m_VV is not applied!
    if(!generatedEventSelection(pdgId,t12,0))
       continue;
    if(!applyVetos(pdgId,t12))
      continue;
    if(!applyLeptonSelection(pdgId,t12))
      continue;
    if((reconstructWithMatchedJet(W_had_gen,t12)).Pt()==0)
      continue;
    W_had = reconstructWithMatchedJet(W_had_gen,t12);
    W_lep = reconstructLeptonicW(pdgId,t12);
    TLorentzVector l     = reconstructLepton(pdgId,t12);
    TLorentzVector n = W_lep - l;
    if(!applyBackToBackTopology(l ,W_had,W_lep,n)) continue;
    hmWW->Fill((W_had+W_lep).M());
  }
  
  TH1* h = fillHistoWithFractionOfSignalEvents(0.9,hmWW,1000);
  hmWW->Write();
  h->Write();
  mWWSpectrum.Close();
}

//=========================================================================================

void makeRootFileForCheckFitCBBW(string ModelName,string channel,string category,string decayMode ,float mass, float width, bool matchV,bool getGeneratedKinematics,bool getGeneratedKinematicsWithoutSelection)
{
  //typedef basic_ostringstream<char> ostringstream;
  //std::ostringstream s;
  //s<< mass;
  //std::string smass(s.str());
  
  string smass = std::to_string(int(mass));
  //std::ostringstream ss; 
  int temp_width = width*10;
  //ss<<temp_width;
  //std::string swidth(ss.str());
  string swidth = std::to_string(temp_width);
  //string directory ="/storage/a/mmozer/Res_Sig/";
  string directory ="/storage/jbod/dschaefer/Res_Sig/";
  string sfileName= 	getFileName(directory,ModelName,decayMode,mass,width,1);
  string sfileName1= 	getFileName(directory,ModelName,decayMode,mass,width,2);
  string sfileName2= 	getFileName(directory,ModelName,decayMode,mass,width,3);
  string VV = determineVV(decayMode);
  string mode = determineSemilepHadOrLep(decayMode);
  
  string soutput_filename = "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/"+ModelName+"/"+ModelName+"_M"+smass+"_width0p"+swidth+"_mWW_"+channel+"_"+category+".root";
  if(getGeneratedKinematics)
  {
    soutput_filename = "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/"+ModelName+"/"+ModelName+"_M"+smass+"_width0p"+swidth+"_mWW_"+channel+"_"+category+"_gen.root";
  }
  if(getGeneratedKinematicsWithoutSelection)
  {
    soutput_filename = "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/"+ModelName+"/"+ModelName+"_M"+smass+"_width0p"+swidth+"_mWW_"+channel+"_"+category+"_withoutSelection.root";
  }
  if(matchV)
  {
    soutput_filename = "/usr/users/dschaefer/root/results/testFit/"+mode+"/To"+VV+"/"+ModelName+"/"+ModelName+"_M"+smass+"_width0p"+swidth+"_mWW_"+channel+"_"+category+"_matchedJet.root";
  }
    
  std::cout <<"run sample "<<ModelName<<" mass = "<<smass << ", width = "<<swidth <<" channel = " <<channel << std::endl;
  
  
  const char* fileName = sfileName.c_str();
  const char* fileName2 = sfileName1.c_str();
  const char* fileName3 = sfileName2.c_str();
  const char* output_filename = soutput_filename.c_str();
  bool isHP=1;
  bool isLP=0;
  bool useWRegion=1;
  bool useZRegion=1;
  if(category.find("LP")!=string::npos)
  {
    isLP =1;
    isHP =0;
  }
  if(category.find("W") !=string::npos)
  {
    useZRegion=0;
  }
  if(category.find("Z") !=string::npos)
  {
   useWRegion=0; 
  }
  
  TFile mWWSpectrum(output_filename,"RECREATE");
  
  int numberFiles=1;
  ifstream fTEST(fileName2);
  if(fTEST.good())
  {
    numberFiles+=1;
    fTEST.close();
  }
  fTEST.open(fileName3);
  if(fTEST.good())
  {
    numberFiles+=1;
    fTEST.close();
  }
  
  
  
  TChain tree("ntuplizer/tree");
  if(numberFiles ==1)
  {
  tree.Add(fileName);
  }
  if(numberFiles==2)
  {
   tree.Add(fileName2);
   tree.Add(fileName);
  }
   if(numberFiles==3)
  {
   tree.Add(fileName2);
   tree.Add(fileName);
   tree.Add(fileName3);
  }
 
  
  MyClass* t12 = new MyClass(&tree);
  int howmany = t12->fChain->GetEntries();
  TLorentzVector W_had_gen;
  TLorentzVector W_lep_gen;
  
  int pdgId= 13;
  if(channel.find("el") != string::npos)
  {pdgId =11;}
  TLorentzVector W_lep;
  TLorentzVector W_had;
  
  if(decayMode.find("lvjj")!=string::npos)
  {
    TH1F* hmWW = new TH1F("hmWW_full","mWW spectrum",1000,0,13000);
    TH1F* hmPt = new TH1F("hmPt","pt of resonance",1000,0,4000);
    TH1F* hmEta = new TH1F("hmEta","eta of resonance",50,-4,4);
  
    for(int i=0;i<howmany;i++)
    {
      t12->fChain->GetEntry(i);
      W_had_gen = getLVofGenParticle(24,t12);
      if(W_had_gen.Pt() ==0)
      {
	W_had_gen = getLVofGenParticle(23,t12);
      }
      W_lep_gen = getLVofGenParticle(pdgId,t12)+ getLVofGenParticle(pdgId+1,t12);
   
      if(getGeneratedKinematicsWithoutSelection)
      {
	hmWW->Fill((W_had_gen+W_lep_gen).M());
	hmPt->Fill((W_had_gen+W_lep_gen).Pt());
	hmEta->Fill((W_had_gen+W_lep_gen).Eta());
	continue;
      }
    //m_VV mass cut is not applied!
      if(!generatedEventSelection(pdgId,t12,0))
	continue;
      if(!applyVetos(pdgId,t12))
	continue;
      if(!applyLeptonSelection_NoVeto(pdgId,t12))
	continue;
      if(!applyMET(pdgId,t12))
	continue;
      if(!applyHadronSelection(t12,isHP,isLP,useWRegion,useZRegion))
	continue;
      if(!applyTrigger(pdgId,t12))
	continue;
      W_had = reconstructHadronicWOrZ(t12,1,1);
      W_lep = reconstructLeptonicW(pdgId,t12);
      TLorentzVector l     = reconstructLepton(pdgId,t12);
      TLorentzVector n = W_lep - l;
      if(!applyBackToBackTopology(l ,W_had,W_lep,n)) continue;
      if(matchV){
	if(isMatchedJet(t12,1,1))
	{
	  hmWW->Fill((W_had+W_lep).M());
	  hmPt->Fill((W_had_gen+W_lep_gen).Pt());
	  hmEta->Fill((W_had_gen+W_lep_gen).Eta());
	}
      }
      else
      {
	if(getGeneratedKinematics)
	{
	  hmWW->Fill((W_had_gen+W_lep_gen).M());
	  hmPt->Fill((W_had_gen+W_lep_gen).Pt());
	  hmEta->Fill((W_had_gen+W_lep_gen).Eta());
	}
	else
	{
	  hmWW->Fill((W_had+W_lep).M());
	  hmPt->Fill((W_had_gen+W_lep_gen).Pt());
	  hmEta->Fill((W_had_gen+W_lep_gen).Eta());
	}
      }
    }
    TH1* h = fillHistoWithFractionOfSignalEvents(0.9,hmWW,1000);
    h->Write();
    hmWW->Write();
    hmPt->Write();
    hmEta->Write();
    
  }
  else if(decayMode.find("jjjj")!=string::npos)
  {
    TLorentzVector V1;
    TLorentzVector V2;
    TLorentzVector jet1;
    TLorentzVector jet2;
    TH1F* hmWW = new TH1F("hmWW_full","mWW spectrum",1000,0,13000);
    TH1F* hmPt = new TH1F("hmPt","pt of resonance",1000,0,4000);
    TH1F* hmEta = new TH1F("hmEta","eta of resonance",50,-4,4);
  
    for(int i=0;i<howmany;i++)
    {
      t12->fChain->GetEntry(i);
      V1 = getGenLV_V1(t12);
      V2 = getGenLV_V2(t12);
      if(getGeneratedKinematicsWithoutSelection)
      {
	hmWW->Fill((V1+V2).M());
	hmPt->Fill((V1+V2).Pt());
	hmEta->Fill((V1+V2).Eta());
	continue;
      }
      if(!genEventSelectionInclusive(t12,"jjjj"))
	continue;
      if(!applyTriggerAllHadronic(t12))
	continue;
      if(!passedAllHadronicSelections(t12))
	continue;
      if(!passedSubstructureSelection(t12,("VV_"+category).c_str()))
	continue;
      jet1 = reconstructV1(t12);
      jet2 = reconstructV2(t12);
    
	if(matchV)
	{
	  if(hasMatchedJetsAllHad(t12))
	  {
	    hmWW->Fill((W_had+W_lep).M());
	    hmPt->Fill((W_had_gen+W_lep_gen).Pt());
	    hmEta->Fill((W_had_gen+W_lep_gen).Eta());
	  }
	}
       else
       {
	if(getGeneratedKinematics)
	{
	  hmWW->Fill((V1+V2).M());
	  hmPt->Fill((V1+V2).Pt());
	  hmEta->Fill((V1+V2).Eta());
	}
	else
	{
	  hmWW->Fill((jet1+jet2).M());
	  hmPt->Fill((jet1+jet2).Pt());
	  hmEta->Fill((jet1+jet2).Eta());
	}
      }
    }
    TH1* h = fillHistoWithFractionOfSignalEvents(0.9,hmWW,1000);
    h->Write();
    hmWW->Write();
    hmPt->Write();
    hmEta->Write();  
  }
  mWWSpectrum.Close();
}

//============================================================================================

vector<double> testEfficiency(string ModelName, string channel,string category,MyClass* t12 ,string outputFile,vector<vector<double> > hadronEff,vector<vector<double> > leptonEff, double BVEff, double LLVEff,double scale)
{
  int howmany = t12->fChain->GetEntries();
  int howmanyEvents =0;
  int BVevents=0;
  int LLVevents=0;
  int generatedEvents=0;
  int number_events_migrated_down_MET=0;
  int pdgId =13;
  if(channel.find("el")!=string::npos){pdgId=11;}
  double wHad = 0.0;
  double wLep = 0.0;
  double eventsReweighted = 0.0;
  int howmanyPassedEvents=0;
  int bin_lep=-1;
  int bin_had=-1;
  string soutput_filename = outputFile;
  const char* output_filename = soutput_filename.c_str();
  TFile ReweightedHisto(output_filename,"RECREATE");
  const Float_t xbinsW[NBINSX]= BINNINGX;
  const Float_t ybinsW[NBINSY]= BINNINGY;
  int nbinsx = NBINSX-1;
  int nbinsy = NBINSY-1;
  vector<vector<double> > histo_lep(2);
  vector<vector<double> > histo_had(2);
  for(int i=0;i<leptonEff[0].size();i++)
  {histo_lep[0].push_back(leptonEff[5][i]);
    histo_lep[1].push_back(0);
  }
  for(int i=0;i<hadronEff[0].size();i++)
  {histo_had[0].push_back(hadronEff[5][i]);
   histo_had[1].push_back(0);
  }
  
  bool isHP=1;
  bool isLP=0;
  bool useWRegion=1;
  bool useZRegion=1;
  if(category.find("LP")!=string::npos)
  {
    isLP =1;
    isHP =0;
  }
  if(category.find("W") !=string::npos)
  {
    useZRegion=0;
  }
  if(category.find("Z") !=string::npos)
  {
   useWRegion=0; 
  }
  
  
  TH2F* hW_lep_rew = new TH2F("hW_lep_rew","W #rightarrow l #nu_{l}, reweighted with efficiencies",nbinsx,xbinsW,nbinsy,ybinsW);
  TH2F* hW_had_rew = new TH2F("hW_had_rew","W #rightarrow q #bar_{q}', reweighted with efficiencies",nbinsx,xbinsW,nbinsy,ybinsW);
  TH2F* hW_lep_rec = new TH2F("hW_lep_rec","W #rightarrow l #nu_{l}, reconstructed full selection",nbinsx,xbinsW,nbinsy,ybinsW);
  TH2F* hW_had_rec = new TH2F("hW_had_rec","W #rightarrow q #bar_{q}', reconstructed full selection",nbinsx,xbinsW,nbinsy,ybinsW);
  TH2F* hW_lep_gen = new TH2F("hW_lep_gen","W #rightarrow l #nu_{l}, only vetos applied",nbinsx,xbinsW,nbinsy,ybinsW);
  TH2F* hW_had_gen = new TH2F("hW_had_gen","W #rightarrow q #bar_{q}',only vetos applied",nbinsx,xbinsW,nbinsy,ybinsW);
  
  int number_migrated_events_up=0;
  int number_migrated_events_down=0;
  
   for(int i=0;i<howmany;i++)
 {
    
   t12->fChain->GetEntry(i);
   
     
   TLorentzVector W_had_gen = getLVofGenParticle(24,t12);
   if(W_had_gen.Pt()==0){W_had_gen=getLVofGenParticle(23,t12);}
   if(W_had_gen.M()==0){W_had_gen = getLVofGenParticle(23,t12);}
   TLorentzVector l_gen = getLVofGenParticle(pdgId,t12);
   TLorentzVector n_gen = getLVofGenParticle(pdgId+1,t12);
   TLorentzVector W_lep_gen = l_gen + n_gen; 
   //Double_t WWmass = (W_had_gen + W_lep_gen).M();
 
   //fixed bug?
   wHad = 0.0;
   wLep = 0.0;
   if(W_had_gen.M()!=0 and W_lep_gen.M() != 0)
   {
      if(generatedEventSelection(pdgId,t12))
      {
	for(int loop=0;loop<leptonEff[0].size();loop++)
	{
	if(W_lep_gen.Pt()>= leptonEff[1][loop]) continue;
	if(TMath::Abs(W_lep_gen.Eta())>= leptonEff[3][loop]) continue;
	wLep = leptonEff[4][loop];
	bin_lep= leptonEff[5][loop];
	break;
	}
	for(int loop=0;loop<hadronEff[0].size();loop++)
	{
	  if(W_had_gen.Pt()>= hadronEff[1][loop]) continue;
	  if(TMath::Abs(W_had_gen.Eta())>= hadronEff[3][loop]) continue;
	  wHad = hadronEff[4][loop];
	  bin_had = hadronEff[5][loop];
	  break;
	}
      eventsReweighted += 1*wHad*wLep*BVEff*LLVEff*scale;
      //hW_lep_rew->Fill(W_lep_gen.Pt(),TMath::Abs(W_lep_gen.Eta()),wLep*BVEff*LLVEff);
      //hW_had_rew->Fill(W_had_gen.Pt(),TMath::Abs(W_had_gen.Eta()),wHad*BVEff*LLVEff*scale);
      for(int loop2=0;loop2<histo_lep[0].size();loop2++)
      {
	if(histo_lep[0][loop2]!=bin_lep) continue;
	histo_lep[1][loop2]+= wHad*scale*wLep*BVEff*LLVEff;
      }
      for(int loop3=0;loop3<histo_had[0].size();loop3++)
      {
	if(histo_had[0][loop3]!=bin_had) continue;
	histo_had[1][loop3]+= wLep*wHad*BVEff*LLVEff*scale;
      }
      
      //std::cout<<" had : "<<wHad*BVEff*LLVEff*scale << std::endl;
      //std::cout<<" lep : "<<wLep*BVEff*LLVEff<<std::endl;
      }
   }
    howmanyEvents +=1;
    
   //if(generatedEventSelection(pdgId,t12)==0) continue;
   generatedEvents +=1;
   if(applyBVeto(t12)==0) continue;
   BVevents+=1;
   if(applyLooseLeptonVeto(pdgId,t12)==0) continue;
   LLVevents+=1;
   hW_had_gen->Fill(W_had_gen.Pt(),TMath::Abs(W_had_gen.Eta()));
   hW_lep_gen->Fill(W_lep_gen.Pt(),TMath::Abs(W_lep_gen.Eta()));
   if(applyLeptonSelection_NoVeto(pdgId,t12)==0) continue;
   if(applyMET(pdgId,t12)==0) continue;
   if(applyTrigger(pdgId,t12)==0) continue;
     //hadron Selection for debugging purposes
   if(applyHadronSelection(t12,isHP,isLP,useWRegion,useZRegion)==0) continue;
	TLorentzVector W_had = reconstructHadronicWOrZ(t12);
	TLorentzVector W_lep = reconstructLeptonicW(pdgId,t12);
	TLorentzVector l     = reconstructLepton(pdgId,t12);
	TLorentzVector n = W_lep - l;
     if(generatedEventSelection(pdgId,t12) and !recoEventSelectionMVVSystemSemilep(l,n,W_had))
   {
     number_migrated_events_up+=1;
     //printInfoEventSemileptonic(pdgId,t12->EVENT_event,t12,"migration_up.txt");
   }
   if(!generatedEventSelection(pdgId,t12) and recoEventSelectionMVVSystemSemilep(l,n,W_had))
   {
      number_migrated_events_down+=1;
     // printInfoEventSemileptonic(pdgId,t12->EVENT_event,t12,"migration_down.txt");
      if(t12->EVENT_event == 15438)
      {
      //get_pdgId("testsemilep_migration_down.txt",t12);
      }
      if(!kinematicCuts(n_gen.Pt(),n_gen.Eta(),pdgId+1))
      {
	number_events_migrated_down_MET+=1;
      }
   }
   
    if(!recoEventSelectionMVVSystemSemilep(l,n,W_had)) continue;
    if(W_lep.Pt()<200) continue;
    if(W_had.Pt()<200) continue;
    howmanyPassedEvents +=1;
    hW_had_rec->Fill(W_had_gen.Pt(),TMath::Abs(W_had_gen.Eta()));
    hW_lep_rec->Fill(W_lep_gen.Pt(),TMath::Abs(W_lep_gen.Eta()));
 }
  //eventsReweighted = eventsReweighted/scale;
  std::cout<<" number of events in file : "<<howmanyEvents<<std::endl;
  std::cout<<" number of events passing all selections : " << howmanyPassedEvents<<std::endl;
  std::cout<<" events Reweighted : "<<eventsReweighted << std::endl;
  for(int loop=0;loop<histo_lep[0].size();loop++)
  {
   hW_lep_rew->SetBinContent(histo_lep[0][loop],histo_lep[1][loop]); 
  }
   for(int loop=0;loop<histo_had[0].size();loop++)
  {
   hW_had_rew->SetBinContent(histo_had[0][loop],histo_had[1][loop]); 
  }
 int nBinsX = 16;
 int nBinsY = 10;
vector<double> SumMu_rec = SumOverAllFilledBins(hW_lep_rec,nBinsX,nBinsY);
vector<double> SumMu_rew = SumOverAllFilledBins(hW_lep_rew,nBinsX,nBinsY);
vector<double> SumHad_rec = SumOverAllFilledBins(hW_had_rec,nBinsX,nBinsY);
vector<double> SumHad_rew = SumOverAllFilledBins(hW_had_rew,nBinsX,nBinsY);

std::cout <<"number of reconstructed events leptonic W "<< SumMu_rec[1] << " : reweighted events leptonic W "<<SumMu_rew[1] << std::endl;
std::cout <<"number of reconstructed events hadronic channel "<< SumHad_rec[1]<<" : reweighted events hadronic channel "<<SumHad_rew[1]<<std::endl;
std::cout << " exact efficiency*acceptance "<< SumMu_rec[1]/50000. << std::endl;
std::cout << " reweighted efff.*acceptance "<< SumMu_rew[1]/50000. << std::endl;
std::cout << " difference : " << (SumMu_rec[1]-SumMu_rew[1])/SumMu_rew[1]*100 <<std::endl;

std::cout << " events that pass gen. cuts but not rec. cuts " << number_migrated_events_up <<std::endl;
std::cout << " events that pass rec. cuts but nor gen. cuts "<<number_migrated_events_down <<std::endl;
std::cout << " not pass MET gen, but passed MET rec " << number_events_migrated_down_MET <<std::endl;
  hW_had_gen->Write();
  hW_lep_gen->Write();
  hW_lep_rew->Write();
  hW_had_rew->Write();
  hW_lep_rec->Write();
  hW_had_rec->Write();
  
 vector<double> result ={BVevents/double(generatedEvents),LLVevents/double(BVevents)};
 return result;
}


//=================================================================================
//======== test Efficiency for the all hadronic channel ===========================
//=================================================================================


void testEfficiencyAllHad(string ModelName,string channel, string category, MyClass* t12, string outputFile, vector<vector<double> > effJET1, /*vector<vector<double> > effJET2,*/float scale)
{
int howmany = t12->fChain->GetEntries();
  int howmanyEvents =0;
  int generatedEvents=0;
  double wHad1 = 0.0;
  double wHad2 = 0.0;
  double eventsReweighted = 0.0;
  int howmanyPassedEvents=0;
  int bin_had1=-1;
  int bin_had2=-1;
  string soutput_filename = outputFile;
  const char* output_filename = soutput_filename.c_str();
  TFile ReweightedHisto(output_filename,"RECREATE");
  const Float_t xbinsW[ALLHADNBINSX]= ALLHADBINNINGX;
  const Float_t ybinsW[ALLHADNBINSY]= ALLHADBINNINGY;
  int nBinsX = ALLHADNBINSX;
  int nBinsY = ALLHADNBINSY;
  
  vector<vector<double> > histo_had(2);
  vector<vector<double> > binnedEffTest_Wplus(2);
  vector<vector<double> > binnedEffTest_Wminus(2);
  
  vector<vector<double> > binnedEffTest_Wplus_reco(2);
  vector<vector<double> > binnedEffTest_Wminus_reco(2);
  
  vector<vector<double> > binnedEffTest_Wplus_gen(2);
  vector<vector<double> > binnedEffTest_Wminus_gen(2);
  for(int i=0;i< effJET1[0].size();i++)
  {
   // std::cout <<effList[5][i]<<std::endl;
   histo_had[0].push_back(effJET1[5][i]);
   histo_had[1].push_back(0);
   binnedEffTest_Wplus[0].push_back(effJET1[5][i]);
   binnedEffTest_Wplus[1].push_back(0);
   binnedEffTest_Wminus[0].push_back(effJET1[5][i]);
   binnedEffTest_Wminus[1].push_back(0);
   binnedEffTest_Wplus_reco[0].push_back(effJET1[5][i]);
   binnedEffTest_Wplus_reco[1].push_back(0);
   binnedEffTest_Wminus_reco[0].push_back(effJET1[5][i]);
   binnedEffTest_Wminus_reco[1].push_back(0);
   
   binnedEffTest_Wplus_gen[0].push_back(effJET1[5][i]);
   binnedEffTest_Wplus_gen[1].push_back(0);
   binnedEffTest_Wminus_gen[0].push_back(effJET1[5][i]);
   binnedEffTest_Wminus_gen[1].push_back(0);
  }
  
  string Purity = "HP";
  if(category.find("LP")!=string::npos)
  {
    Purity = "LP";
  }
  
  
  
  TH2F* hW_had_rew = new TH2F("hW_had_rew","W #rightarrow q #bar_{q}', reweighted with efficiencies",nBinsX-1,xbinsW,nBinsY-1,ybinsW);
  TH2F* hW_had_rec = new TH2F("hW_had_rec","W #rightarrow q #bar_{q}', reconstructed full selection",nBinsX-1,xbinsW,nBinsY-1,ybinsW);
  TH2F* hW_had_gen = new TH2F("hW_had_gen","W #rightarrow q #bar_{q}',only vetos applied",nBinsX-1,xbinsW,nBinsY-1,ybinsW);
  TH2F* hW_had_gen_plusSel = new TH2F("hW_had_gen_plusSel","W #rightarrow q #bar_{q}', generator selections applied",nBinsX-1,xbinsW,nBinsY-1,ybinsW);
  
  TH2F* BinnedEffTest_Wplus = new TH2F("BinnedEffTest_plus","BinnedEffTest overall eff. parametrised after Wplus kin.", nBinsX-1, xbinsW,nBinsY-1,ybinsW);
  TH2F* BinnedEffTest_Wminus = new TH2F("BinnedEffTest_minus","BinnedEffTest overall eff. parametrised after Wminus kin.", nBinsX-1, xbinsW,nBinsY-1,ybinsW);
  
  TLorentzVector V1;
  TLorentzVector V2;
  
  std::cout << scale << std::endl;
  
   for(int i=0;i<howmany;i++)
 {
    
   t12->fChain->GetEntry(i);
   if(!genEventSelectionInclusive(t12,"jjjj"))
      continue;
   V1 = getGenLV_V1(t12);
   V2 = getGenLV_V2(t12);
    howmanyEvents +=1;
    hW_had_gen->Fill(V1.Pt(),TMath::Abs(V1.Eta()));
    hW_had_gen->Fill(V2.Pt(),TMath::Abs(V2.Eta()));
   
    if(applyGeneratorKinematicSelectionsAllHad(V1,V2))
    {
      hW_had_gen_plusSel->Fill(V1.Pt(),TMath::Abs(V1.Eta()));
      hW_had_gen_plusSel->Fill(V2.Pt(),TMath::Abs(V2.Eta()));
    
    
      if(V1.Pt() == V2.Pt() and V1.Eta()==V2.Eta())
      {
	std::cout << t12->EVENT_event << std::endl; 
      }
   
      wHad1=0;
      wHad2=0;
	for(int loop=0;loop<effJET1[0].size();loop++)
	{
	  if(V1.Pt()>= effJET1[1][loop]) continue;
	  if(TMath::Abs(V1.Eta())>= effJET1[3][loop]) continue;
	  wHad1 = effJET1[4][loop];
	  bin_had1 = effJET1[5][loop];
	  break;
	}
// 	for(int loop=0;loop<effJET2[0].size();loop++)
// 	{
// 	  if(V2.Pt()>= effJET2[1][loop]) continue;
// 	  if(TMath::Abs(V2.Eta())>= effJET2[3][loop]) continue;
// 	  wHad2 = effJET2[4][loop];
// 	  bin_had2 = effJET2[5][loop];
// 	  break;
// 	}
	for(int loop=0;loop<effJET1[0].size();loop++)
	{
	  if(V2.Pt()>= effJET1[1][loop]) continue;
	  if(TMath::Abs(V2.Eta())>= effJET1[3][loop]) continue;
	  wHad2 = effJET1[4][loop];
	  bin_had2 = effJET1[5][loop];
	  break;
	}

	eventsReweighted += 1*wHad1*wHad2*scale;

      
	int tmp=0;
	for(int loop3=0;loop3<histo_had[0].size();loop3++)
	{
// 	if(binnedEffTest_Wplus[0][loop3]==bin_had1)
// 	{
// 	 binnedEffTest_Wplus[1][loop3]+=wHad1*wHad2; 
// 	}
// 	if(binnedEffTest_Wminus[0][loop3]==bin_had2)
// 	{
// 	  binnedEffTest_Wminus[1][loop3]+=wHad2*wHad1;
// 	}
	if(histo_had[0][loop3]!=bin_had1 and histo_had[0][loop3]!=bin_had2) continue;
	if(bin_had1==bin_had2)
	{
	  histo_had[1][loop3]+= wHad1*wHad2*2*scale;
	}
	else
	{
	  histo_had[1][loop3]+= wHad1*wHad2*scale;
	}
	
	tmp+=1;
	}
     
  
   
	for(int loop3=0;loop3<binnedEffTest_Wplus_gen[0].size();loop3++)
	{
	  if(binnedEffTest_Wplus_gen[0][loop3]==bin_had1)
	  {
	  binnedEffTest_Wplus_gen[1][loop3]+=1; 
	  }
	  if(binnedEffTest_Wminus_gen[0][loop3]==bin_had2)
	  {
	  binnedEffTest_Wminus_gen[1][loop3]+=1;
	  }
	}
      
//     hW_had_gen->Fill(V1.Pt(),TMath::Abs(V1.Eta()));
//     hW_had_gen->Fill(V2.Pt(),TMath::Abs(V2.Eta()));
//    
//     if(applyGeneratorKinematicSelectionsAllHad(V1,V2))
//     {
//       hW_had_gen_plusSel->Fill(V1.Pt(),TMath::Abs(V1.Eta()));
//       hW_had_gen_plusSel->Fill(V2.Pt(),TMath::Abs(V2.Eta()));
//     }
    }
    
   if(applyTriggerAllHadronic(t12)==0) continue;
   if(!passedAllHadronicSelections(t12))
      continue;
   if(category.find("NP")==string::npos)
   {
     if(!passedSubstructureSelection(t12,("VV_"+Purity).c_str()))
      continue;
   }
    hW_had_rec->Fill(V1.Pt(),TMath::Abs(V1.Eta()));
    hW_had_rec->Fill(V2.Pt(),TMath::Abs(V2.Eta()));
    howmanyPassedEvents+=1;
   
   for(int loop3=0;loop3<binnedEffTest_Wplus_reco[0].size();loop3++)
      {
	if(binnedEffTest_Wplus_reco[0][loop3]==bin_had1)
	{
	 binnedEffTest_Wplus_reco[1][loop3]+=1; 
	}
	if(binnedEffTest_Wminus_reco[0][loop3]==bin_had2)
	{
	  binnedEffTest_Wminus_reco[1][loop3]+=1;
	}
	
      }
   
   
 }

  std::cout<<" number of events in file : "<<howmanyEvents<<std::endl;
  std::cout<<" number of events passing all selections : " << howmanyPassedEvents<<std::endl;
  std::cout<<" events Reweighted : "<<eventsReweighted << std::endl;
  for(int i=0;i<binnedEffTest_Wplus[0].size();i++)
  {
    binnedEffTest_Wplus[1][i] = effJET1[1][i];
    binnedEffTest_Wminus[1][i]= effJET1[1][i];
  }
  
  
   for(int loop=0;loop<histo_had[0].size();loop++)
  {
   hW_had_rew->SetBinContent(histo_had[0][loop],histo_had[1][loop]);
   
   if(binnedEffTest_Wplus[1][loop]!=0)
   {
    double eff_reco = binnedEffTest_Wplus_reco[1][loop]/binnedEffTest_Wplus_gen[1][loop];
    double eff_reweighted = binnedEffTest_Wplus[1][loop];
   BinnedEffTest_Wplus->SetBinContent(binnedEffTest_Wplus[0][loop],(eff_reco-eff_reweighted)/eff_reweighted);
   }
   if(binnedEffTest_Wminus[1][loop]!=0)
   {
     double eff_reco_m = binnedEffTest_Wminus_reco[1][loop]/binnedEffTest_Wminus_gen[1][loop];
    double eff_reweighted_m = binnedEffTest_Wminus[1][loop]/binnedEffTest_Wminus_gen[1][loop];
    BinnedEffTest_Wminus->SetBinContent(binnedEffTest_Wminus[0][loop],(eff_reco_m-eff_reweighted_m)/eff_reweighted_m);
   }
  }


vector<double> SumHad_rec = SumOverAllFilledBins(hW_had_rec,nBinsX,nBinsY);
vector<double> SumHad_rew = SumOverAllFilledBins(hW_had_rew,nBinsX,nBinsY);
vector<double> SumHad_gen = SumOverAllFilledBins(hW_had_gen,nBinsX,nBinsY);
vector<double> SumHad_gen_plusSel = SumOverAllFilledBins(hW_had_gen_plusSel,nBinsX,nBinsY);
double acceptance = SumHad_gen_plusSel[1]/SumHad_gen[1];
double exact_eff = SumHad_rec[1]/SumHad_gen_plusSel[1];
double rew_eff = SumHad_rew[1]/SumHad_gen_plusSel[1];

std::cout <<"number of reconstructed events hadronic channel "<< SumHad_rec[1]<<" : reweighted events hadronic channel "<<SumHad_rew[1]<<std::endl;
  
std::cout << " exact efficiency*acceptance : " <<exact_eff*acceptance <<std::endl;
std::cout << " rew. efficiency*acceptance : " << rew_eff*acceptance  <<std::endl;
std::cout << " relative difference : " << (exact_eff*acceptance - rew_eff*acceptance )/double(rew_eff*acceptance)*100<<std::endl;
std::cout <<scale <<std::endl;
  
  hW_had_gen->Write();
  hW_had_gen_plusSel->Write();
  hW_had_rew->Write();
  hW_had_rec->Write();
  BinnedEffTest_Wplus->Write();
  BinnedEffTest_Wminus->Write();
 
}



void testEfficiencyAllHadTEST(string ModelName,string channel, string category, MyClass* t12, string outputFile, vector<vector<double> > effW,vector<vector<double> > effZ  ,float scale)
{
  int howmany = t12->fChain->GetEntries();
  int howmanyEvents =0;
  int generatedEvents=0;
  double wHad1 = 0.0;
  double wHad2 = 0.0;
  double eventsReweighted = 0.0;
  int howmanyPassedEvents=0;
  int bin_had1=-1;
  int bin_had2=-1;
  string soutput_filename = outputFile;
  const char* output_filename = soutput_filename.c_str();
  TFile ReweightedHisto(output_filename,"RECREATE");
  const Float_t xbinsW[ALLHADNBINSX]= ALLHADBINNINGX;
  const Float_t ybinsW[ALLHADNBINSY]= ALLHADBINNINGY;
  int nBinsX = ALLHADNBINSX;
  int nBinsY = ALLHADNBINSY;
  
  vector<vector<double> > histo_had(2);
  vector<vector<double> > binnedEffTest_Wplus(2);
  vector<vector<double> > binnedEffTest_Wminus(2);
  
  vector<vector<double> > binnedEffTest_Wplus_reco(2);
  vector<vector<double> > binnedEffTest_Wminus_reco(2);
  
  vector<vector<double> > binnedEffTest_Wplus_gen(2);
  vector<vector<double> > binnedEffTest_Wminus_gen(2);
  for(int i=0;i< effW[0].size();i++)
  {
   // std::cout <<effList[5][i]<<std::endl;
   histo_had[0].push_back(effW[5][i]);
   histo_had[1].push_back(0);
   binnedEffTest_Wplus[0].push_back(effW[5][i]);
   binnedEffTest_Wplus[1].push_back(0);
   binnedEffTest_Wminus[0].push_back(effW[5][i]);
   binnedEffTest_Wminus[1].push_back(0);
   binnedEffTest_Wplus_reco[0].push_back(effW[5][i]);
   binnedEffTest_Wplus_reco[1].push_back(0);
   binnedEffTest_Wminus_reco[0].push_back(effW[5][i]);
   binnedEffTest_Wminus_reco[1].push_back(0);
   
   binnedEffTest_Wplus_gen[0].push_back(effW[5][i]);
   binnedEffTest_Wplus_gen[1].push_back(0);
   binnedEffTest_Wminus_gen[0].push_back(effW[5][i]);
   binnedEffTest_Wminus_gen[1].push_back(0);
  }
  
  string Purity = "HP";
  if(category.find("LP")!=string::npos)
  {
    Purity = "LP";
  }
  
  
  
  TH2F* hW_had_rew = new TH2F("hW_had_rew","W #rightarrow q #bar_{q}', reweighted with efficiencies",nBinsX-1,xbinsW,nBinsY-1,ybinsW);
  TH2F* hW_had_rec = new TH2F("hW_had_rec","W #rightarrow q #bar_{q}', reconstructed full selection",nBinsX-1,xbinsW,nBinsY-1,ybinsW);
  TH2F* hW_had_gen = new TH2F("hW_had_gen","W #rightarrow q #bar_{q}',only vetos applied",nBinsX-1,xbinsW,nBinsY-1,ybinsW);
  TH2F* hW_had_gen_plusSel = new TH2F("hW_had_gen_plusSel","W #rightarrow q #bar_{q}', generator selections applied",nBinsX-1,xbinsW,nBinsY-1,ybinsW);
  
  TH2F* BinnedEffTest_Wplus = new TH2F("BinnedEffTest_plus","BinnedEffTest overall eff. parametrised after Wplus kin.", nBinsX-1, xbinsW,nBinsY-1,ybinsW);
  TH2F* BinnedEffTest_Wminus = new TH2F("BinnedEffTest_minus","BinnedEffTest overall eff. parametrised after Wminus kin.", nBinsX-1, xbinsW,nBinsY-1,ybinsW);
  
  TLorentzVector V1;
  TLorentzVector V2;
  
  std::cout << scale << std::endl;
  
   for(int i=0;i<howmany;i++)
 {
    
   t12->fChain->GetEntry(i);
   if(!genEventSelectionInclusive(t12,"jjjj"))
      continue;
   V1 = getGenLV_V1(t12);
   V2 = getGenLV_V2(t12);
    howmanyEvents +=1;
    hW_had_gen->Fill(V1.Pt(),TMath::Abs(V1.Eta()));
    hW_had_gen->Fill(V2.Pt(),TMath::Abs(V2.Eta()));
   
    if(applyGeneratorKinematicSelectionsAllHad(V1,V2))
    {
      hW_had_gen_plusSel->Fill(V1.Pt(),TMath::Abs(V1.Eta()));
      hW_had_gen_plusSel->Fill(V2.Pt(),TMath::Abs(V2.Eta()));
    
    
      if(V1.Pt() == V2.Pt() and V1.Eta()==V2.Eta())
      {
	std::cout << t12->EVENT_event << std::endl; 
      }
   
      wHad1=0;
      wHad2=0;
	for(int loop=0;loop<effW[0].size();loop++)
	{
	  if(V1.Pt()>= effW[1][loop]) continue;
	  if(TMath::Abs(V1.Eta())>= effW[3][loop]) continue;
	  wHad1 = effW[4][loop];
	  bin_had1 = effW[5][loop];
	  break;
	}
	for(int loop=0;loop<effZ[0].size();loop++)
	{
	  if(V2.Pt()>= effZ[1][loop]) continue;
	  if(TMath::Abs(V2.Eta())>= effZ[3][loop]) continue;
	  wHad2 = effZ[4][loop];
	  bin_had2 = effZ[5][loop];
	  break;
	}
	

	eventsReweighted += 1*wHad1*wHad2*scale;

      
	int tmp=0;
	for(int loop3=0;loop3<histo_had[0].size();loop3++)
	{
// 		if(binnedEffTest_Wplus[0][loop3]==bin_had1)
// 		{
// 		 binnedEffTest_Wplus[1][loop3]+=wHad1*wHad2; 
// 		}
// 		if(binnedEffTest_Wminus[0][loop3]==bin_had2)
// 		{
// 	  	binnedEffTest_Wminus[1][loop3]+=wHad2*wHad1;
// 		}
	  if(histo_had[0][loop3]!=bin_had1 and histo_had[0][loop3]!=bin_had2) continue;
	  if(bin_had1==bin_had2)
	  {
	    histo_had[1][loop3]+= wHad1*wHad2*2*scale;
	  }
	  else
	  {
	    histo_had[1][loop3]+= wHad1*wHad2*scale;
	  }
	
	  tmp+=1;
	}
     
  
   
	for(int loop3=0;loop3<binnedEffTest_Wplus_gen[0].size();loop3++)
	{
	  if(binnedEffTest_Wplus_gen[0][loop3]==bin_had1)
	  {
	  binnedEffTest_Wplus_gen[1][loop3]+=1; 
	  }
	  if(binnedEffTest_Wminus_gen[0][loop3]==bin_had2)
	  {
	   binnedEffTest_Wminus_gen[1][loop3]+=1;
	  }
	}
    }
      
//     hW_had_gen->Fill(V1.Pt(),TMath::Abs(V1.Eta()));
//     hW_had_gen->Fill(V2.Pt(),TMath::Abs(V2.Eta()));
//    
//     if(applyGeneratorKinematicSelectionsAllHad(V1,V2))
//     {
//       hW_had_gen_plusSel->Fill(V1.Pt(),TMath::Abs(V1.Eta()));
//       hW_had_gen_plusSel->Fill(V2.Pt(),TMath::Abs(V2.Eta()));
//     }
    
   if(applyTriggerAllHadronic(t12)==0) continue;
   if(!passedAllHadronicSelections(t12))
      continue;
   if(category.find("NP")==string::npos)
   {
     if(!passedSubstructureSelection(t12,("VV_"+Purity).c_str()))
      continue;
   }
    hW_had_rec->Fill(V1.Pt(),TMath::Abs(V1.Eta()));
    hW_had_rec->Fill(V2.Pt(),TMath::Abs(V2.Eta()));
    howmanyPassedEvents+=1;
   
   for(int loop3=0;loop3<binnedEffTest_Wplus_reco[0].size();loop3++)
      {
	if(binnedEffTest_Wplus_reco[0][loop3]==bin_had1)
	{
	 binnedEffTest_Wplus_reco[1][loop3]+=1; 
	}
	if(binnedEffTest_Wminus_reco[0][loop3]==bin_had2)
	{
	  binnedEffTest_Wminus_reco[1][loop3]+=1;
	}
	
      }
   
   
 }

  std::cout<<" number of events in file : "<<howmanyEvents<<std::endl;
  std::cout<<" number of events passing all selections : " << howmanyPassedEvents<<std::endl;
  std::cout<<" events Reweighted : "<<eventsReweighted << std::endl;
  for(int i=0;i<binnedEffTest_Wplus[0].size();i++)
  {
    binnedEffTest_Wplus[1][i] = effW[1][i];
    binnedEffTest_Wminus[1][i]= effZ[1][i];
  }
  
  
   for(int loop=0;loop<histo_had[0].size();loop++)
  {
   hW_had_rew->SetBinContent(histo_had[0][loop],histo_had[1][loop]);
   
   if(binnedEffTest_Wplus[1][loop]!=0)
   {
    double eff_reco = binnedEffTest_Wplus_reco[1][loop]/binnedEffTest_Wplus_gen[1][loop];
    double eff_reweighted = binnedEffTest_Wplus[1][loop];
   BinnedEffTest_Wplus->SetBinContent(binnedEffTest_Wplus[0][loop],(eff_reco-eff_reweighted)/eff_reweighted);
   }
   if(binnedEffTest_Wminus[1][loop]!=0)
   {
     double eff_reco_m = binnedEffTest_Wminus_reco[1][loop]/binnedEffTest_Wminus_gen[1][loop];
    double eff_reweighted_m = binnedEffTest_Wminus[1][loop]/binnedEffTest_Wminus_gen[1][loop];
    BinnedEffTest_Wminus->SetBinContent(binnedEffTest_Wminus[0][loop],(eff_reco_m-eff_reweighted_m)/eff_reweighted_m);
   }
  }


vector<double> SumHad_rec = SumOverAllFilledBins(hW_had_rec,nBinsX,nBinsY);
vector<double> SumHad_rew = SumOverAllFilledBins(hW_had_rew,nBinsX,nBinsY);
vector<double> SumHad_gen = SumOverAllFilledBins(hW_had_gen,nBinsX,nBinsY);
vector<double> SumHad_gen_plusSel = SumOverAllFilledBins(hW_had_gen_plusSel,nBinsX,nBinsY);
double acceptance = SumHad_gen_plusSel[1]/SumHad_gen[1];
double exact_eff = SumHad_rec[1]/SumHad_gen_plusSel[1];
double rew_eff = SumHad_rew[1]/SumHad_gen_plusSel[1];

std::cout <<"number of reconstructed events hadronic channel "<< SumHad_rec[1]<<" : reweighted events hadronic channel "<<SumHad_rew[1]<<std::endl;
  
std::cout << " exact efficiency*acceptance : " <<exact_eff*acceptance <<std::endl;
std::cout << " rew. efficiency*acceptance : " << rew_eff*acceptance  <<std::endl;
std::cout << " relative difference : " << (exact_eff*acceptance - rew_eff*acceptance )/double(rew_eff*acceptance)*100<<std::endl;
std::cout <<scale <<std::endl;
  
  hW_had_gen->Write();
  hW_had_gen_plusSel->Write();
  hW_had_rew->Write();
  hW_had_rec->Write();
  BinnedEffTest_Wplus->Write();
  BinnedEffTest_Wminus->Write();
 
  /*
  int howmany = t12->fChain->GetEntries();
  int howmanyEvents =0;
  int generatedEvents=0;
  double wHad = 0.0;
  double eventsReweighted = 0.0;
  int howmanyPassedEvents=0;
  int bin_had=-1;
  string soutput_filename = outputFile;
  const char* output_filename = soutput_filename.c_str();
  TFile ReweightedHisto(output_filename,"RECREATE");
  const Float_t xbinsW[ALLHADNBINSXBOTHJETS]= ALLHADBINNINGXBOTHJETS;
  const Float_t ybinsW[ALLHADNBINSYBOTHJETS]= ALLHADBINNINGYBOTHJETS;
  int nBinsX = ALLHADNBINSXBOTHJETS;
  int nBinsY = ALLHADNBINSYBOTHJETS;
  
  vector<vector<double> > histo_had(2);
  for(int i=0;i< eff[0].size();i++)
  {
   // std::cout <<effList[5][i]<<std::endl;
   histo_had[0].push_back(eff[5][i]);
   histo_had[1].push_back(0);
  }
  
  string Purity = "HP";
  if(category.find("LP")!=string::npos)
  {
    Purity = "LP";
  }
  
  
  
  TH2F* hW_had_rew = new TH2F("hW_had_rew","W #rightarrow q #bar_{q}', reweighted with efficiencies",nBinsX-1,xbinsW,nBinsY-1,ybinsW);
  TH2F* hW_had_rec = new TH2F("hW_had_rec","W #rightarrow q #bar_{q}', reconstructed full selection",nBinsX-1,xbinsW,nBinsY-1,ybinsW);
  TH2F* hW_had_gen = new TH2F("hW_had_gen","W #rightarrow q #bar_{q}',only vetos applied",nBinsX-1,xbinsW,nBinsY-1,ybinsW);
  
  TLorentzVector V1;
  TLorentzVector V2;
  
   for(int i=0;i<howmany;i++)
 {
    
   t12->fChain->GetEntry(i);
   if(!genEventSelectionInclusive(t12,"jjjj"))
      continue;
   V1 = getGenLV_V1(t12);
   V2 = getGenLV_V2(t12);
   wHad=0;
	for(int loop=0;loop<eff[0].size();loop++)
	{
	  if((V1.Pt()+V2.Pt())>= eff[1][loop]) continue;
	  if(TMath::Abs(V1.Eta()-V2.Eta())>= eff[3][loop]) continue;
	  wHad = eff[4][loop]*scale;
	  bin_had = eff[5][loop];
	  //std::cout <<t12->EVENT_event<<std::endl;
	 // std::cout << V1.Pt()+V2.Pt() << " " << eff[0][loop] <<" - " <<eff[1][loop]<<std::endl;
	  //std::cout << TMath::Abs(V1.Eta()-V2.Eta()) << " " << eff[2][loop]<< " - "<<eff[3][loop] <<std::endl;
	  break;
	}
	
      eventsReweighted += 1*wHad;
      for(int loop3=0;loop3<histo_had[0].size();loop3++)
      {
	if(histo_had[0][loop3]!=bin_had)
	  continue;
	  histo_had[1][loop3]+= wHad;
      }
     
   howmanyEvents +=1;
   hW_had_gen->Fill(V1.Pt()+V2.Pt(),TMath::Abs(V1.Eta()-V2.Eta()));
       
   if(applyTriggerAllHadronic(t12)==0) continue;
   if(!passedAllHadronicSelections(t12))
      continue;
   if(!passedSubstructureSelection(t12,("VV_"+Purity).c_str()))
      continue;
    hW_had_rec->Fill(V1.Pt()+V2.Pt(),TMath::Abs(V1.Eta()-V2.Eta()));
    howmanyPassedEvents+=1;
 }

  std::cout<<" number of events in file : "<<howmanyEvents<<std::endl;
  std::cout<<" number of events passing all selections : " << howmanyPassedEvents<<std::endl;
  std::cout<<" events Reweighted : "<<eventsReweighted << std::endl;
   for(int loop=0;loop<histo_had[0].size();loop++)
  {
   hW_had_rew->SetBinContent(histo_had[0][loop],histo_had[1][loop]); 
  }


vector<double> SumHad_rec = SumOverAllFilledBins(hW_had_rec,nBinsX,nBinsY);
vector<double> SumHad_rew = SumOverAllFilledBins(hW_had_rew,nBinsX,nBinsY);
vector<double> SumHad_gen = SumOverAllFilledBins(hW_had_gen,nBinsX,nBinsY);

std::cout <<"number of reconstructed events hadronic channel "<< SumHad_rec[1]<<" : reweighted events hadronic channel "<<SumHad_rew[1]<<std::endl;
std::cout << " sum over gen events " << SumHad_gen[1] <<std::endl;


std::cout << " exact efficiency : " << howmanyPassedEvents/double(howmanyEvents) << "  " << SumHad_rec[1]/SumHad_gen[1] <<std::endl;
std::cout << " rew. efficiency : " << eventsReweighted/double(howmanyEvents) <<"  " << SumHad_rew[1]/SumHad_gen[1]  <<std::endl;
std::cout << " relative difference in percent : " << (howmanyPassedEvents/double(howmanyEvents) - eventsReweighted/double(howmanyEvents))/double(eventsReweighted/double(howmanyEvents))*100<<std::endl;
std::cout <<scale <<std::endl;
  
  hW_had_gen->Write();
  hW_had_rew->Write();
  hW_had_rec->Write();
  */
}





