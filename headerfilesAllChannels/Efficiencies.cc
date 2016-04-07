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
//#include "/usr/users/dschaefer/root/headerfiles/DebugFunc.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"

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

double NumberOfEventsInFile(string ModelName,float mass,float width)
{
    string smass = std::to_string(int(mass));
  int temp_width = width*10;
  string swidth = std::to_string(temp_width);
  //string directory ="/storage/a/mmozer/Res_Sig/";
  string directory ="/storage/jbod/dschaefer/Res_Sig/";
  string sfileName= 	getFileName(directory,ModelName,mass,width,1);
  string sfileName1= 	getFileName(directory,ModelName,mass,width,2);
  string sfileName2= 	getFileName(directory,ModelName,mass,width,3);

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
    sfileName= 	getFileName(directory,ModelName,mass,width,1,1);
    sfileName1= getFileName(directory,ModelName,mass,width,2,1);
    sfileName2= getFileName(directory,ModelName,mass,width,3,1);
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
  int howmany = t12->fChain->GetEntries();
  return howmany;
}
//=========================================================================================

void makeRootFileForCheckFitCBBW_genMC_withSelection(string ModelName,string channel,string category,float mass, float width)
{
 makeRootFileForCheckFitCBBW(ModelName, channel,category ,mass ,width,0,1,0); 
}

//=========================================================================================

void makeRootFileForCheckFitCBBW_genMC_withoutSelection(string ModelName,string channel,string category,float mass, float width)
{
makeRootFileForCheckFitCBBW(ModelName, channel,category, mass ,width,0,0,1); 
}

//=========================================================================================

void makeRootFileForCheckFitCBBW_recMC_matched(string ModelName,string channel,string category,float mass, float width)
{
 makeRootFileForCheckFitCBBW(ModelName, channel,category, mass ,width,1,0,0);  
}

//=========================================================================================
void makeRootFileForCheckFitCBBW_matching_withoutSelection(string ModelName,string channel,float mass, float width)
{
  string smass = std::to_string(int(mass));
  int temp_width = width*10;
  string swidth = std::to_string(temp_width);
  //string directory ="/storage/a/mmozer/Res_Sig/";
  string directory ="/storage/jbod/dschaefer/Res_Sig/";
  string sfileName= 	getFileName(directory,ModelName,mass,width,1);
  string sfileName1= 	getFileName(directory,ModelName,mass,width,2);
  string sfileName2= 	getFileName(directory,ModelName,mass,width,3);
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

void makeRootFileForCheckFitCBBW(string ModelName,string channel,string category ,float mass, float width, bool matchV,bool getGeneratedKinematics,bool getGeneratedKinematicsWithoutSelection)
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
  string sfileName= 	getFileName(directory,ModelName,mass,width,1,1);
  string sfileName1= 	getFileName(directory,ModelName,mass,width,2,1);
  string sfileName2= 	getFileName(directory,ModelName,mass,width,3,1);
  string soutput_filename = "/usr/users/dschaefer/root/results/"+ModelName+"/"+ModelName+"_M"+smass+"_width0p"+swidth+"_mWW_"+channel+"_"+category+".root";
  if(getGeneratedKinematics)
  {
    soutput_filename = "/usr/users/dschaefer/root/results/"+ModelName+"/"+ModelName+"_M"+smass+"_width0p"+swidth+"_mWW_"+channel+"_"+category+"_gen.root";
  }
  if(getGeneratedKinematicsWithoutSelection)
  {
    soutput_filename = "/usr/users/dschaefer/root/results/"+ModelName+"/"+ModelName+"_M"+smass+"_width0p"+swidth+"_mWW_"+channel+"_"+category+"_withoutSelection.root";
  }
  if(matchV)
  {
    soutput_filename = "/usr/users/dschaefer/root/results/"+ModelName+"/"+ModelName+"_M"+smass+"_width0p"+swidth+"_mWW_"+channel+"_"+category+"_matchedJet.root";
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
  TH1F* hmWW = new TH1F("hmWW_full","mWW spectrum",1000,0,13000);
  TH1F* hmPt = new TH1F("hmPt","pt of resonance",1000,0,4000);
  TH1F* hmEta = new TH1F("hmEta","eta of resonance",50,-4,4);
  
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
  const Float_t xbinsW[16]={0,200,250,300,400,500,600,700,800,1000,1200,1500,2000,2500,3000,4000};
  const Float_t ybinsW[10]={0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};
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
  
  
  TH2F* hW_lep_rew = new TH2F("hW_lep_rew","W #rightarrow l #nu_{l}, reweighted with efficiencies",15,xbinsW,9,ybinsW);
  TH2F* hW_had_rew = new TH2F("hW_had_rew","W #rightarrow q #bar_{q}', reweighted with efficiencies",15,xbinsW,9,ybinsW);
  TH2F* hW_lep_rec = new TH2F("hW_lep_rec","W #rightarrow l #nu_{l}, reconstructed full selection",15,xbinsW,9,ybinsW);
  TH2F* hW_had_rec = new TH2F("hW_had_rec","W #rightarrow q #bar_{q}', reconstructed full selection",15,xbinsW,9,ybinsW);
  TH2F* hW_lep_gen = new TH2F("hW_lep_gen","W #rightarrow l #nu_{l}, only vetos applied",15,xbinsW,9,ybinsW);
  TH2F* hW_had_gen = new TH2F("hW_had_gen","W #rightarrow q #bar_{q}',only vetos applied",15,xbinsW,9,ybinsW);
  
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
   if(generatedEventSelection(pdgId,t12)==0) continue;
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

    if(!applyBackToBackTopology(l ,W_had,W_lep,n)) continue;
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
  
  
  hW_had_gen->Write();
  hW_lep_gen->Write();
  hW_lep_rew->Write();
  hW_had_rew->Write();
  hW_lep_rec->Write();
  hW_had_rec->Write();
  
 vector<double> result ={BVevents/double(generatedEvents),LLVevents/double(BVevents)};
 return result;
}













