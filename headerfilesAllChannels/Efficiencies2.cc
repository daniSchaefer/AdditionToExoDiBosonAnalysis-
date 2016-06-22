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
#include <map>
#include <string>
#include "/usr/users/dschaefer/root/headerfiles/MyClass.h"
#include "/usr/users/dschaefer/root/headerfiles/passed_mu_jes.h"
#include "/usr/users/dschaefer/root/headerfiles/Op.h"
#include "/usr/users/dschaefer/root/headerfiles/EventSelection.h"
#include "/usr/users/dschaefer/root/headerfiles/GenFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/RecFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies2.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"
#include "/usr/users/dschaefer/root/headerfiles/WWConstants.h"
#include "/usr/users/dschaefer/root/headerfiles/AllHadronicConstants.h"



vector<double> makeEfficiencyTestSemileptonicChannel(string ModelName, string channel, string category,string decayMode, MyClass* t12,const char* BGEff, const char* BGEff2, const char* ZhadEff, const char* ZhadEff2, string NameOutputFile)
{
 int nBinsX = NBINSX;
 int nBinsY = NBINSY;
 vector<double> BinsX= BINNINGX;
 vector<double> BinsY= BINNINGY;
 double scale=1;
 vector<double> vetoEff;

TFile *f = new TFile(BGEff,"READ");
TFile *f2 = new TFile(BGEff2,"READ");
TFile *fZ = new TFile(ZhadEff,"READ");
TFile *fZ2 = new TFile(ZhadEff2,"READ");


  TH2F* hLep_rec = (TH2F*) f->Get("hW_lep_rec");
  TH2F* hHad_rec;
  TH2F* hHad_gen; 
  TH2F* hHad_rec2;
  TH2F* hHad_gen2; 
  if(ModelName.find("Wprime")!=string::npos or decayMode.find("WZ")!=string::npos)
  {
    hHad_rec = (TH2F*) fZ->Get("hW_had_rec");
    hHad_gen = (TH2F*) fZ->Get("hW_had_genWithVeto");
    hHad_rec2 = (TH2F*) fZ2->Get("hW_had_rec");
    hHad_gen2 = (TH2F*) fZ2->Get("hW_had_genWithVeto");
  }
  else
  {
    hHad_gen = (TH2F*) f->Get("hW_had_genWithVeto");
    hHad_rec = (TH2F*) f->Get("hW_had_rec");
    hHad_gen2 = (TH2F*) f2->Get("hW_had_genWithVeto");
    hHad_rec2 = (TH2F*) f2->Get("hW_had_rec");
  }
  hHad_gen->Add(hHad_gen2);
  hHad_rec->Add(hHad_rec2);
  TH2F* hLep_genWV = (TH2F*) f->Get("hW_lep_genWithVeto");
  TH2F* hLep_genBV = (TH2F*) f->Get("hW_lep_genWithBVeto");
  TH2F* hLep_gen  = (TH2F*) f->Get("hW_lep_gen");
  TH2F* hLep_genLLV = (TH2F*) f->Get("hW_lep_genWithLooseLeptonVeto");


  TH2* hLepEff = GetEfficiencies(hLep_rec,hLep_genWV);
  TH2* hHadEff = GetEfficiencies(hHad_rec,hHad_gen);
 
  TH2* hBTagEff = GetEfficiencies(hLep_genBV,hLep_gen);
  TH2* hLLVetoEff = GetEfficiencies(hLep_genLLV,hLep_gen);

  vector<double> BV = SumOverAllFilledBins(hBTagEff,nBinsX,nBinsY);
  double BVEff = BV[1]/BV[0];
  vector<double> LLV = SumOverAllFilledBins(hLLVetoEff,nBinsX,nBinsY);
  double LLVEff = LLV[1]/LLV[0];

  vector<vector<double> > leptonEff = MakeListOfWeights(hLepEff,BinsX,BinsY);
  vector<vector<double> > hadronEff = MakeListOfWeights(hHadEff,BinsX,BinsY);

  if(ModelName.find("RSGrav") != string::npos)
  {
    scale = 1/1.30528;
  }

  vetoEff = testEfficiency(ModelName,channel, category,t12,NameOutputFile,hadronEff,leptonEff,BVEff,LLVEff,scale);
  
  return vetoEff;
}


//==========================================================================================================================

vector<double> makeEfficiencyTest(string ModelName,string channel,string category,string decayMode ,float mass, float width)
{
  //string dir = "/storage/a/mmozer/Res_Sig/";
  string OUTDIR = "/storage/jbod/dschaefer/testEff/";
 // string OUTDIR = "/usr/users/dschaefer/how-to_jdl_creator/efficiencies";
  vector<double> vetoEff;
  string dir ="/storage/jbod/dschaefer/Res_Sig/";
  string Sinput_filename1 = getFileName(dir,ModelName,decayMode,mass,width,1);
  string Sinput_filename2 = getFileName(dir,ModelName,decayMode,mass,width,2);
  string Sinput_filename3 = getFileName(dir,ModelName,decayMode,mass,width,3);
 
  //test if files exist:
  
   const char* input_filename1 = Sinput_filename1.c_str();
   const char* input_filename2 = Sinput_filename2.c_str();
   const char* input_filename3 = Sinput_filename3.c_str();
  int isGood =0;
  ifstream fTEST;
  fTEST.open(input_filename2);
  if(fTEST.good())
  {
    isGood +=1;
    fTEST.close();
  }
  fTEST.open(input_filename3);
  if(fTEST.good())
  {
   isGood +=1;
   fTEST.close();
  }
  
  TChain tree("ntuplizer/tree");
  if(width <0.1 or isGood ==0)
  {
    tree.Add(input_filename1);
   // std::cout << input_filename1 <<std::endl;
  }
  if(isGood ==1)
  {
    tree.Add(input_filename2);
   tree.Add(input_filename1);
   //std::cout << input_filename1<<std::endl;
   //std::cout << input_filename2<<std::endl;
  }
  else if(isGood>1 and width>=0.1)
  {
   tree.Add(input_filename2);
   tree.Add(input_filename1);
   tree.Add(input_filename3);
   //std::cout << input_filename1<<std::endl;
  // std::cout << input_filename2<<std::endl;
   //std::cout << input_filename3<<std::endl;
  }
   
  string VV = determineVV(decayMode);
  string mode = determineSemilepHadOrLep(decayMode);
  
  string outputDirectory = OUTDIR+mode+"/To"+VV+"/";
  
  string filename = ModelName+"To"+decayMode+"_Kinematics_"+channel+"_"+category+"_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
   

MyClass* t12 = new MyClass(&tree);
int howmany = t12->fChain->GetEntries();
std::cout<<" the files have " <<howmany << " events in total" <<std::endl;

string WW = "WW";
if(decayMode.find("ZZ")!=string::npos)
{
  WW = "ZZ";
}

string SBGEff =    "/storage/jbod/dschaefer/EfficiencyHistos/"+mode+"/To"+WW+"/BulkGravTo"+WW+"Kinematics_el_"+category+".root";
string SBGEff2 =   "/storage/jbod/dschaefer/EfficiencyHistos/"+mode+"/To"+WW+"/BulkGravTo"+WW+"Kinematics_mu_"+category+".root";
string SZhadEff =  "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/WprimeToWZKinematics_el_"+category+".root";
string SZhadEff2 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/WprimeToWZKinematics_mu_"+category+".root"; 
const char* BGEff 	=  SBGEff.c_str() ;
const char* BGEff2 	=  SBGEff2.c_str();
const char* ZhadEff	=  SZhadEff.c_str();
const char* ZhadEff2  	=  SZhadEff2.c_str();
if(channel.find("mu") !=string::npos)
{
   BGEff 	=  SBGEff2.c_str() ;
   BGEff2 	=  SBGEff.c_str();
   ZhadEff	=  SZhadEff2.c_str();
   ZhadEff2  	=  SZhadEff.c_str();
}
if(channel.find("had") !=string::npos or decayMode.find("jjjj")!=string::npos)
{
 SBGEff = "/storage/jbod/dschaefer/EfficiencyHistos/"+mode+"/To"+WW+"/BulkGravTo"+WW+"Kinematics_had_"+category+".root"; 
 //SBGEff = "/storage/jbod/dschaefer/EfficiencyHistos/"+mode+"/To"+WW+"/RadionTo"+WW+"Kinematics_had_"+category+".root"; 
 SZhadEff = "/storage/jbod/dschaefer/EfficiencyHistos/"+mode+"/ToZZ/RadionToZZKinematics_had_"+category+".root"; 
 ZhadEff = SZhadEff.c_str();
 BGEff =SBGEff.c_str();
}


//"/usr/users/dschaefer/root/results/Efficiency/histos/testEff/";
string NameOutputFile = outputDirectory+filename;

 if(decayMode.find("lvjj")!=string::npos)
{
  vetoEff =  makeEfficiencyTestSemileptonicChannel(ModelName,channel,category,decayMode,t12, BGEff,BGEff2,ZhadEff,ZhadEff2, NameOutputFile);
}
else if(decayMode.find("jjjj")!=string::npos)
{
  //implement the same for the all hadronic channel here!
 int nBinsX = ALLHADNBINSX;
 int nBinsY = ALLHADNBINSY;
 float scale =1;
 vector<double> BinsX= ALLHADBINNINGX;
 vector<double> BinsY= ALLHADBINNINGY;
 
  TFile *f = new TFile(BGEff,"READ");
  TH2F* h_Wplus_denominator = (TH2F*) f->Get("h_jet1_denominator");
  TH2F* h_Wplus_numerator = (TH2F*) f->Get("h_jet1_numerator");
  TH2F* h_Wminus_denominator = (TH2F*) f->Get("h_jet2_denominator");
  TH2F* h_Wminus_numerator = (TH2F*) f->Get("h_jet2_numerator");
  
  TH2* EffJET1 = GetEfficiencies(h_Wplus_numerator,h_Wplus_denominator);
  TH2* EffJET2 = GetEfficiencies(h_Wminus_numerator,h_Wminus_denominator);
  vector<vector<double> > effJET1 = MakeListOfWeights(EffJET1,BinsX,BinsY);
  vector<vector<double> > effJET2 = MakeListOfWeights(EffJET2,BinsX,BinsY);
  h_Wplus_denominator->Add(h_Wminus_denominator);
  h_Wplus_numerator->Add(h_Wminus_numerator);
  TH2* Eff = GetEfficiencies(h_Wplus_numerator,h_Wplus_denominator);
  vector<vector<double> > eff = MakeListOfWeights(Eff,BinsX,BinsY);
  
  //PrintBinContents(Eff,BinsX,BinsY,"test");
  if(decayMode.find("jjjj")!=string::npos)
  {
   scale = 0.985207; 
  }
  if(ModelName.find("RSGrav")!=string::npos)
  {
   scale = scale*1/(1.30528*1.30528);
  }
  std::cout <<scale <<std::endl;
  if(ModelName.find("Wprime")!=string::npos or decayMode.find("WZ")!=string::npos)
  {
   //scale=scale*TMath::Sqrt(1.144); 
   TFile *fZ = new TFile(ZhadEff,"READ");
   TH2F* h_Z1_denominator = (TH2F*) fZ->Get("h_jet1_denominator");
   TH2F* h_Z1_numerator = (TH2F*) fZ->Get("h_jet1_numerator");
   TH2F* h_Z2_denominator = (TH2F*) fZ->Get("h_jet2_denominator");
   TH2F* h_Z2_numerator = (TH2F*) fZ->Get("h_jet2_numerator");
   h_Z1_denominator->Add(h_Z2_denominator);
   h_Z1_numerator->Add(h_Z2_numerator);
   TH2* EffZ = GetEfficiencies(h_Z1_numerator,h_Z1_denominator);
   vector<vector<double> > effZ = MakeListOfWeights(EffZ,BinsX,BinsY);
   
   testEfficiencyAllHadTEST("Wprime","had","WZ_jjjj",t12,NameOutputFile,eff,effZ,scale);
  }
  else
  {
    testEfficiencyAllHad(ModelName,"had",category,t12,NameOutputFile,eff,scale);
  }
}

return vetoEff;
}

//=====================================================================================================

vector<double> makeEfficiencyTestVersion2HAD(string ModelName,string channel,string category,string decayMode ,float mass, float width)
{
  //string dir = "/storage/a/mmozer/Res_Sig/";
  string OUTDIR = "/storage/jbod/dschaefer/testEff/";
 // string OUTDIR = "/usr/users/dschaefer/how-to_jdl_creator/efficiencies";
  vector<double> vetoEff;
  string dir ="/storage/jbod/dschaefer/Res_Sig/";
  string Sinput_filename1 = getFileName(dir,ModelName,decayMode,mass,width,1);
  string Sinput_filename2 = getFileName(dir,ModelName,decayMode,mass,width,2);
  string Sinput_filename3 = getFileName(dir,ModelName,decayMode,mass,width,3);
 
  //test if files exist:
  
   const char* input_filename1 = Sinput_filename1.c_str();
   const char* input_filename2 = Sinput_filename2.c_str();
   const char* input_filename3 = Sinput_filename3.c_str();
  int isGood =0;
  ifstream fTEST;
  fTEST.open(input_filename2);
  if(fTEST.good())
  {
    isGood +=1;
    fTEST.close();
  }
  fTEST.open(input_filename3);
  if(fTEST.good())
  {
   isGood +=1;
   fTEST.close();
  }
  
  TChain tree("ntuplizer/tree");
  if(width <0.1 or isGood ==0)
  {
    tree.Add(input_filename1);
   // std::cout << input_filename1 <<std::endl;
  }
  if(isGood ==1)
  {
    tree.Add(input_filename2);
   tree.Add(input_filename1);
   //std::cout << input_filename1<<std::endl;
   //std::cout << input_filename2<<std::endl;
  }
  else if(isGood>1 and width>=0.1)
  {
   tree.Add(input_filename2);
   tree.Add(input_filename1);
   tree.Add(input_filename3);
   //std::cout << input_filename1<<std::endl;
  // std::cout << input_filename2<<std::endl;
   //std::cout << input_filename3<<std::endl;
  }
   
  string VV = determineVV(decayMode);
  string mode = determineSemilepHadOrLep(decayMode);
  
  string outputDirectory = OUTDIR+mode+"/To"+VV+"/";
  
  string filename = ModelName+"To"+decayMode+"_Kinematics_"+channel+"_"+category+"_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
   

MyClass* t12 = new MyClass(&tree);
int howmany = t12->fChain->GetEntries();
std::cout<<" the files have " <<howmany << " events in total" <<std::endl;

string WW = "WW";
if(decayMode.find("ZZ")!=string::npos)
{
  WW = "ZZ";
}

string SBGEff =    "/storage/jbod/dschaefer/EfficiencyHistos/"+mode+"/To"+WW+"/BulkGravTo"+WW+"Kinematics_el_"+category+".root";
string SBGEff2 =   "/storage/jbod/dschaefer/EfficiencyHistos/"+mode+"/To"+WW+"/BulkGravTo"+WW+"Kinematics_mu_"+category+".root";
string SZhadEff =  "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/WprimeToWZKinematics_el_"+category+".root";
string SZhadEff2 = "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWZ/WprimeToWZKinematics_mu_"+category+".root"; 
const char* BGEff 	=  SBGEff.c_str() ;
const char* BGEff2 	=  SBGEff2.c_str();
const char* ZhadEff	=  SZhadEff.c_str();
const char* ZhadEff2  	=  SZhadEff2.c_str();
if(channel.find("mu") !=string::npos)
{
   BGEff 	=  SBGEff2.c_str() ;
   BGEff2 	=  SBGEff.c_str();
   ZhadEff	=  SZhadEff2.c_str();
   ZhadEff2  	=  SZhadEff.c_str();
}
if(channel.find("had") !=string::npos or decayMode.find("jjjj")!=string::npos)
{
 SBGEff = "/storage/jbod/dschaefer/EfficiencyHistos/"+mode+"/To"+WW+"/RadionTo"+WW+"Kinematics_had_"+category+".root"; 
 BGEff =SBGEff.c_str();
}


//"/usr/users/dschaefer/root/results/Efficiency/histos/testEff/";
string NameOutputFile = outputDirectory+filename;

if(decayMode.find("lvjj")!=string::npos)
{
  vetoEff =  makeEfficiencyTestSemileptonicChannel(ModelName,channel,category,decayMode,t12,BGEff,BGEff2,ZhadEff,ZhadEff2, NameOutputFile);
}
else if(decayMode.find("jjjj")!=string::npos)
{
  //implement the same for the all hadronic channel here!
 int nBinsX = ALLHADNBINSXBOTHJETS;
 int nBinsY = ALLHADNBINSYBOTHJETS;
 float scale =1;
 vector<double> BinsX= ALLHADBINNINGXBOTHJETS;
 vector<double> BinsY= ALLHADBINNINGYBOTHJETS;
 
  TFile *f = new TFile(BGEff,"READ");
  TH2F* hhad_gen = (TH2F*) f->Get("hhad_gen");
  TH2F* hhad_rec = (TH2F*) f->Get("hhad_rec");
  
  TH2* Eff = GetEfficiencies(hhad_rec,hhad_gen);
  vector<vector<double> > eff = MakeListOfWeights(Eff,BinsX,BinsY);
  //PrintBinContents(Eff,BinsX,BinsY,"test");
  if(ModelName.find("RSGrav")!=string::npos)
  {
   scale = 1/(1.30528*1.30528);
  }
  if(decayMode.find("WZ")!=string::npos or ModelName.find("Wprime")!=string::npos)
  {
   scale = TMath::Sqrt(0.322246/0.299918); 
  }
  std::cout <<scale <<std::endl;
  //testEfficiencyAllHadTEST(ModelName,"had",category,t12,NameOutputFile,eff,scale);
  
}

return vetoEff;
}


//=====================================================================================================


 std::map<string,double> ExtractRecoAndTestEfficiency(string ModelName,string category ,string decayMode,float mass ,float width)
{
   string VV = determineVV(decayMode);
   string mode = determineSemilepHadOrLep(decayMode);
   
   string outputDirectory ="/storage/jbod/dschaefer/testEff/"+mode+"/To"+VV+"/"; //"/usr/users/dschaefer/root/results/Efficiency/histos/testEff/";
   std::map<std::string,double> result;
   
    if(decayMode.find("lvjj")!=string::npos)
    {
    string fileName_el =  outputDirectory+ModelName+"To"+decayMode+"_Kinematics_el_"+category+"_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
    string fileName_mu =  outputDirectory+ModelName+"To"+decayMode+"_Kinematics_mu_"+category+"_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
    
    
    
    const char* input_filename3 = fileName_el.c_str();
    const char* input_filename4 = fileName_mu.c_str();
    
    //std::cout<< input_filename4 <<std::endl;
    
    TFile * RewEl = new TFile(input_filename3,"READ");
    TFile * RewMu = new TFile(input_filename4,"READ");

    TH2F* hMu_rec 		= (TH2F*) RewMu->Get("hW_lep_rec");
    TH2F* hEl_rec 		= (TH2F*) RewEl->Get("hW_lep_rec");
    TH2F* hHad_rec 		= (TH2F*) RewMu->Get("hW_had_rec");
    TH2F* hHad2_rec		= (TH2F*) RewEl->Get("hW_had_rec");
    hHad_rec->Add(hHad2_rec);
    TH2F* hMu_rew 		= (TH2F*) RewMu->Get("hW_lep_rew");
    TH2F* hEl_rew 		= (TH2F*) RewEl->Get("hW_lep_rew");
    TH2F* hHad_rew 		= (TH2F*) RewMu->Get("hW_had_rew");
    TH2F* hHad2_rew		= (TH2F*) RewEl->Get("hW_had_rew");
    hHad_rew->Add(hHad2_rew);
    TH2F* hMu_gen 		= (TH2F*) RewMu->Get("hW_lep_gen");
    TH2F* hEl_gen 		= (TH2F*) RewEl->Get("hW_lep_gen");
    TH2F* hHad_gen		= (TH2F*) RewMu->Get("hW_had_gen");
    TH2F* hHad2_gen		= (TH2F*) RewEl->Get("hW_had_gen");
    hHad_gen->Add(hHad2_gen);
    int nBinsX =16;
    int nBinsY =10;
    vector<double> SumMu_rec = SumOverAllFilledBins(hMu_rec,nBinsX,nBinsY);
    vector<double> SumEl_rec = SumOverAllFilledBins(hEl_rec,nBinsX,nBinsY);
    vector<double> SumMu_rew = SumOverAllFilledBins(hMu_rew,nBinsX,nBinsY);
    vector<double> SumEl_rew = SumOverAllFilledBins(hEl_rew,nBinsX,nBinsY);
    vector<double> SumHad_rec = SumOverAllFilledBins(hHad_rec,nBinsX,nBinsY);
    vector<double> SumHad_rew = SumOverAllFilledBins(hHad_rew,nBinsX,nBinsY);
    vector<double> SumMu_gen = SumOverAllFilledBins(hMu_gen,nBinsX,nBinsY);
    vector<double> SumEl_gen = SumOverAllFilledBins(hEl_gen,nBinsX,nBinsY);
    vector<double> SumHad_gen = SumOverAllFilledBins(hHad_gen,nBinsX,nBinsY);

    
    //std::cout << SumMu_rew[1] <<  " " << SumMu_rec[1] <<std::endl;
    double Nevents = NumberOfEventsInFile(ModelName,decayMode,mass,width);
    //std::cout << Nevents << std::endl;
    double acceptanceMu = SumMu_gen[1]/Nevents;
    double acceptanceEl = SumEl_gen[1]/Nevents;
    result.insert(std::pair<std::string,double>("mu_rec",(SumMu_rec[1]/SumMu_gen[1]*acceptanceMu)));
    result.insert(std::pair<std::string,double>("mu_rew",(SumMu_rew[1]/SumMu_gen[1]*acceptanceMu)));
    result.insert(std::pair<std::string,double>("el_rec",(SumEl_rec[1]/(SumEl_gen[1])*acceptanceEl)));
    result.insert(std::pair<std::string,double>("el_rew",(SumEl_rew[1]/(SumEl_gen[1])*acceptanceEl)));
    result.insert(std::pair<std::string,double>("had_rec",(SumHad_rec[1]/SumHad_gen[1])));
    result.insert(std::pair<std::string,double>("had_rew",(SumHad_rew[1]/SumHad_gen[1])));
    result.insert(std::pair<std::string,double>("err_mu",(TMath::Sqrt(SumMu_rec[1])/Nevents+ TMath::Sqrt(Nevents)*SumMu_rec[1]/((Nevents)*(Nevents)))));
    result.insert(std::pair<std::string,double>("err_el",(TMath::Sqrt(SumEl_rec[1])/Nevents+ TMath::Sqrt(Nevents)*SumMu_rec[1]/((Nevents)*(Nevents)))));
    result.insert(std::pair<std::string,double>("err_had",(0)));
  }
  if(decayMode.find("jjjj")!=string::npos)
  {
  
   string fileName =  outputDirectory+ModelName+"To"+decayMode+"_Kinematics_had_"+category+"_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
   
   const char* input_filename = fileName.c_str();
   
   TFile * RewHad = new TFile(input_filename,"READ");

 
    TH2F* hHad_rec 		= (TH2F*) RewHad->Get("hW_had_rec");
    TH2F* hHad_rew 		= (TH2F*) RewHad->Get("hW_had_rew");
    TH2F* hHad_gen		= (TH2F*) RewHad->Get("hW_had_gen");
    int nBinsX = ALLHADNBINSX;
    int nBinsY = ALLHADNBINSY;
    vector<double> Sum_rec = {0,hHad_rec->GetEntries()};//= SumOverAllFilledBins(hHad_rec,nBinsX,nBinsY);
    vector<double> Sum_rew = {double(nBinsX*nBinsY),hHad_rew->GetEffectiveEntries()}; //SumOverAllFilledBins(hHad_rew,nBinsX,nBinsY);
    vector<double> Sum_gen = {0,hHad_gen->GetEntries()}; //SumOverAllFilledBins(hHad_gen,nBinsX,nBinsY);
    double Nevents = Sum_gen[1];
//     std::cout << fileName <<std::endl;
//     std::cout << RewHad <<std::endl;
//     std::cout << hHad_gen <<std::endl;
//     std::cout << hHad_gen->GetEntries() <<std::endl;
//     std::cout << hHad_rec->GetEntries() <<std::endl;
//     std::cout << hHad_rew->GetEffectiveEntries() <<std::endl;
//     
//     std::cout <<std::endl;
//     std::cout << "#gen events " << Sum_gen[1] <<"#rec events "<<Sum_rec[1] <<"#rew events "<<Sum_rew[1]<<std::endl; 
//     std::cout <<std::endl;
  
    result.insert(std::pair<std::string,double>("mu_rec",0)); 
    result.insert(std::pair<std::string,double>("mu_rew",0));
    result.insert(std::pair<std::string,double>("el_rec",0));
    result.insert(std::pair<std::string,double>("el_rew",0));
    result.insert(std::pair<std::string,double>("had_rec",(Sum_rec[1]/Nevents)));
    result.insert(std::pair<std::string,double>("had_rew",(Sum_rew[1]/Nevents)));
    result.insert(std::pair<std::string,double>("err_mu",0));
    result.insert(std::pair<std::string,double>("err_el",0));
    result.insert(std::pair<std::string,double>("err_had",TMath::Sqrt(Sum_rec[1])/Nevents+ TMath::Sqrt(Nevents)*Sum_rec[1]/((Nevents)*(Nevents)))); 
    }
  return result;
}
 //=====================================================================================================
 void PrintReconstructionEfficiencyTable(string ModelName, string category,string decayMode ,vector<float> massPoints,float width,string caption)
 {
    std::cout.unsetf ( std::ios::floatfield );
   std::cout.setf(std::ios::fixed);
   std::cout.precision(3);
   string X = "X$";
   string VV = determineVV(decayMode);
   string  channelLATEX1 = "$\\rightarrow e \\nu q \\bar{q}'$";
   string  channelLATEX2 = "$\\rightarrow \\mu \\nu q \\bar{q}' $";
   if(ModelName.find("Wprime") != string::npos)
   {
    X = "W$'"; 
    
   }
   if(ModelName.find("Zprime") != string::npos)
   {
    X = "Z$'"; 
   }
   
   if(decayMode.find("lvjj")!=string::npos)
   {
   std::cout<< " Model: " << ModelName<< std::endl;
   std::cout<<"\\begin{table}"<<std::endl;
   std::cout<<"\\caption{"<<caption <<"}"<<std::endl;
   std::cout<<"\\begin{tabular}{|l|c|c|c|c|c|c|}"<<std::endl;
   std::cout<<"\\hline"<<std::endl; 
   std::cout << " & \\multicolumn{3}{c|}{"<<X<<"\\rightarrow$"<< VV<< channelLATEX1<<" } & \\multicolumn{3}{c|}{ "<<X<<"\\rightarrow$ "<< VV <<channelLATEX2<< "} \\\\"<<std::endl; 
   std::cout<<"\\hline"<<std::endl;
   std::cout<<"$M_x$ & \\tiny{exact efficiency}&\\tiny{parametrised efficiency}& \\tiny{relative error (in \\%)}  & \\tiny{exact efficiency}& \\tiny{parametrised efficiency} & \\tiny{relative error (in \\%)} \\\\"<< std::endl;
   std::cout<<"\\hline"<<std::endl;
   for(int i=0;i<massPoints.size();i++)
   {
     std::map<string,double> eff = ExtractRecoAndTestEfficiency(ModelName,category,decayMode ,massPoints[i],width);
     
     std::cout<< int(massPoints[i]) << " & "<< eff.find("el_rec")->second << " & "<< eff.find("el_rew")->second << "&";
     std::cout.precision(1);
     std::cout<< (eff.find("el_rec")->second - eff.find("el_rew")->second )/eff.find("el_rew")->second *100;
     std::cout.precision(4);
     std::cout<< " & " << eff.find("mu_rec")->second << " & " << eff.find("mu_rew")->second <<" & ";
     std::cout.precision(1);
     std::cout<< (eff.find("mu_rec")->second -eff.find("mu_rew")->second )/eff.find("mu_rew")->second *100  <<" \\\\"<<std::endl;
     std::cout.precision(4);
   }
   
   std::cout<<"\\hline"<<std::endl;
   std::cout<<"\\end{tabular}"<<std::endl;
   std::cout<<"\\label{tab:EffTest"<<ModelName<<"}"<<std::endl;
   std::cout<<"\\end{table}"<<std::endl;
   }
   if(decayMode.find("jjjj")!=string::npos)
   {
     channelLATEX1 = "$\\rightarrow q \\bar{q}' q \\bar{q}'$";
     std::cout<< " Model: " << ModelName<< std::endl;
     std::cout<<"\\begin{table}"<<std::endl;
     std::cout<<"\\caption{"<<caption <<"}"<<std::endl;
     std::cout<<"\\begin{tabular}{|l|c|c|c|}"<<std::endl;
   std::cout<<"\\hline"<<std::endl; 
   std::cout << " & \\multicolumn{3}{c|}{"<<X<<"\\rightarrow$"<< VV<< channelLATEX1<<" } "<< " \\\\"<<std::endl; 
   std::cout<<"\\hline"<<std::endl;
   std::cout<<"$M_x$ & \\tiny{exact efficiency}&\\tiny{parametrised efficiency}& \\tiny{relative error (in \\%)}  \\\\"<< std::endl;
   std::cout<<"\\hline"<<std::endl;
   for(int i=0;i<massPoints.size();i++)
   {
     std::map<string,double> eff = ExtractRecoAndTestEfficiency(ModelName,category,decayMode ,massPoints[i],width);
     
     std::cout<< int(massPoints[i]) << " & "<< eff.find("had_rec")->second << " & "<< eff.find("had_rew")->second << "&";
     std::cout.precision(1);
     std::cout<< (eff.find("had_rec")->second - eff.find("had_rew")->second )/eff.find("had_rew")->second *100;
     std::cout.precision(4);
     std::cout<<" \\\\"<<std::endl;
     std::cout.precision(4);
   }
   
   std::cout<<"\\hline"<<std::endl;
   std::cout<<"\\end{tabular}"<<std::endl;
   std::cout<<"\\label{tab:EffTest"<<ModelName<<"ALLHAD}"<<std::endl;
   std::cout<<"\\end{table}"<<std::endl;
   }
 }

 //======================================================================================================
 
 void EfficiencyUncertaintyForDatacards(vector<float> mass,string channel, string category,string decayMode)
 {
  float width =0.1;
  std::map<std::string,double> eff;
  vector<string> modelList = {"Wprime","Zprime","RSGrav","Radion"};
  string lep_rec = "el_rec";
  string lep_rew = "el_rew";
  double uncertainty;
  string filename = "/home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/sys/signal_eff_uncertainty_"+decayMode+"_"+channel+"_"+category+".txt";
  if(decayMode.find("jjjj")!=string::npos)
  {
   filename = "/home/dschaefer/CMSSW_7_1_5/src/DijetCombineLimitCode/signal_eff_uncertainty_"+decayMode+"_"+channel+"_"+category+".txt";
  }
  ofstream f;
  f.open(filename,ios::ate);
  f<< "effUnc"<<std::endl;
  if(channel.find("mu")!=string::npos)
  {
    lep_rec = "mu_rec";
    lep_rew = "mu_rew";
  }
  if(channel.find("had")!=string::npos or decayMode.find("jjjj")!=string::npos)
  {
   lep_rec = "had_rec";
   lep_rew = "had_rew";
  }
  
  for(int i=0;i< mass.size();i++)
  {
  for(int l=0;l< modelList.size();l++)
  {
    if(modelList[l].find("Wprime")!=string::npos)
    {
      if(decayMode.find("lvjj")!=string::npos)
      {
      eff = ExtractRecoAndTestEfficiency(modelList[l],category,"WZ_lvjj",mass.at(i),width);
      }
      else
      {
      eff = ExtractRecoAndTestEfficiency(modelList[l],category,"WZ_jjjj",mass.at(i),width);
      }
    }
    else
    {
   eff = ExtractRecoAndTestEfficiency(modelList[l],category,decayMode,mass.at(i),width);
    }
   double tmp = TMath::Abs(eff.find(lep_rec)->second -eff.find(lep_rew)->second)/ eff.find(lep_rew)->second;
   //f << tmp << std::endl;
   if(l==0)
   {
   uncertainty = tmp;
   }
   else if(tmp > uncertainty)
   {
     uncertainty = tmp;
   }
   }
   int u = round(uncertainty*100);
   //f << u << std::endl;
   int d0 = u/10;
   int d1 = u%10;
   //f << d0 << std::endl;
   //f<< d1 << std::endl;
   if(d1<5)
   {
    u = d0*10+5; 
    //f<<"round to 5 " << u << std::endl;
   }
   if(d1>=5)
   {
    u = d0*10 + 10; 
    //f<<"round to 10 " << u << std::endl;
   }
   f<< "BulkG_"<<decayMode<<"_M" << mass[i]<<" "<< u/100.  << std::endl;
   }
   f.close();
 }