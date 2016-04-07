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
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"

vector<double> makeEfficiencyTest(string ModelName,string channel,string category ,float mass, float width)
{
  //string dir = "/storage/a/mmozer/Res_Sig/";
  string dir ="/storage/jbod/dschaefer/Res_Sig/";
  string Sinput_filename1 = getFileName(dir,ModelName,mass,width,1,1);
  string Sinput_filename2 = getFileName(dir,ModelName,mass,width,2,1);
  string Sinput_filename3 = getFileName(dir,ModelName,mass,width,3,1);
  
 
 
 
  int isGood=0;
  
  ifstream fTEST(Sinput_filename1.c_str());
  if(fTEST.good())
  {
    isGood +=1;
    fTEST.close();
  }
  if(!isGood)
  {
    dir = "/storage/jbod/dschaefer/Res_Sig/";
    Sinput_filename1 = getFileName(dir,ModelName,mass,width,1,1);
    Sinput_filename2 = getFileName(dir,ModelName,mass,width,2,1);
    Sinput_filename3 = getFileName(dir,ModelName,mass,width,3,1);
    
  }
   const char* input_filename1 = Sinput_filename1.c_str();
   const char* input_filename2 = Sinput_filename2.c_str();
   const char* input_filename3 = Sinput_filename3.c_str();
  isGood =0;
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
  }
  if(isGood ==1)
  {
    tree.Add(input_filename2);
   tree.Add(input_filename1);
  }
  else if(isGood>1 and width>=0.1)
  {
   tree.Add(input_filename2);
   tree.Add(input_filename1);
   tree.Add(input_filename3);
  }
   
  
  string filename = ModelName+"ToWKinematics_"+channel+"_"+category+"_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
   

MyClass* t12 = new MyClass(&tree);
int howmany = t12->fChain->GetEntries();
std::cout<<" the files have " <<howmany << " events in total" <<std::endl;
string SBGEff =    "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/BulkGravToWWKinematics_el_"+category+".root";
string SBGEff2 =   "/storage/jbod/dschaefer/EfficiencyHistos/semileptonic/ToWW/BulkGravToWWKinematics_mu_"+category+".root";
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

string outputDirectory = "/storage/jbod/dschaefer/testEff/";
//"/usr/users/dschaefer/root/results/Efficiency/histos/testEff/";
string NameOutputFile = outputDirectory+filename;

 
 int nBinsX = 16;
 int nBinsY = 10;
 vector<double> BinsX={0,200,250,300,400,500,600,700,800,1000,1200,1500,2000,2500,3000,4000};
 vector<double> BinsY={0,0.2,0.4,0.6,0.8,1.0,1.25,1.5,2.0,2.5};
 double scale=1;

TFile *f = new TFile(BGEff,"READ");
TFile *f2 = new TFile(BGEff2,"READ");
TFile *fZ = new TFile(ZhadEff,"READ");
TFile *fZ2 = new TFile(ZhadEff2,"READ");


TH2F* hLep_rec = (TH2F*) f->Get("hW_lep_rec");
TH2F* hHad_rec;
TH2F* hHad_gen; 
TH2F* hHad_rec2;
TH2F* hHad_gen2; 
if(ModelName.find("Wprime")!=string::npos)
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

vector<double> vetoEff = testEfficiency(ModelName,channel, category,t12,NameOutputFile,hadronEff,leptonEff,BVEff,LLVEff,scale);

//std::cout << " mass " << mass << " BV eff " <<vetoEff[0] << " LLV eff " <<vetoEff[1] << std::endl;
return vetoEff;
}
//=====================================================================================================




//=====================================================================================================

 vector<vector<double> > ExtractRecoAndTestEfficiency(string ModelName,string category ,float mass ,float width)
 {
   string outputDirectory ="/storage/jbod/dschaefer/testEff/"; //"/usr/users/dschaefer/root/results/Efficiency/histos/testEff/";
   string fileName_el =  outputDirectory+ModelName+"ToWKinematics_el_"+category+"_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
   string fileName_mu =  outputDirectory+ModelName+"ToWKinematics_mu_"+category+"_M"+std::to_string(int(mass))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
   
   const char* input_filename3 = fileName_el.c_str();
   const char* input_filename4 = fileName_mu.c_str();
   
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

vector<vector<double> > result(2);
/*
result[0].push_back(SumMu_rec[1]/(SumMu_gen[1]+SumEl_gen[1]));
result[1].push_back(SumMu_rew[1]/(SumMu_gen[1]+SumEl_gen[1]));
result[0].push_back(SumEl_rec[1]/(SumEl_gen[1]+SumMu_gen[1]));
result[1].push_back(SumEl_rew[1]/(SumEl_gen[1]+SumMu_gen[1]));
result[0].push_back(SumHad_rec[1]/SumHad_gen[1]);
result[1].push_back(SumHad_rew[1]/SumHad_gen[1]);
result[0].push_back(TMath::Sqrt(SumMu_rec[1])/(SumMu_gen[1]+SumEl_gen[1])+ TMath::Sqrt((SumMu_gen[1]+SumEl_gen[1]))*SumMu_rec[1]/((SumMu_gen[1]+SumEl_gen[1])*(SumMu_gen[1]+SumEl_gen[1])));
result[1].push_back(0);
result[0].push_back(TMath::Sqrt(SumEl_rec[1])/(SumMu_gen[1]+SumEl_gen[1])+ TMath::Sqrt((SumMu_gen[1]+SumEl_gen[1]))*SumEl_rec[1]/((SumMu_gen[1]+SumEl_gen[1])*(SumMu_gen[1]+SumEl_gen[1])));
result[1].push_back(0);
*/
double Nevents = NumberOfEventsInFile(ModelName,mass,width);
//std::cout << Nevents << std::endl;
double acceptanceMu = SumMu_gen[1]/Nevents;
double acceptanceEl = SumEl_gen[1]/Nevents;
result[0].push_back(SumMu_rec[1]/(SumMu_gen[1])*acceptanceMu);
result[1].push_back(SumMu_rew[1]/(SumMu_gen[1])*acceptanceMu);
result[0].push_back(SumEl_rec[1]/(SumEl_gen[1])*acceptanceEl);
result[1].push_back(SumEl_rew[1]/(SumEl_gen[1])*acceptanceEl);
result[0].push_back(SumHad_rec[1]/SumHad_gen[1]);
result[1].push_back(SumHad_rew[1]/SumHad_gen[1]);
result[0].push_back(TMath::Sqrt(SumMu_rec[1])/Nevents+ TMath::Sqrt(Nevents)*SumMu_rec[1]/((Nevents)*(Nevents)));
result[1].push_back(0);
result[0].push_back(TMath::Sqrt(SumEl_rec[1])/Nevents+ TMath::Sqrt(Nevents)*SumMu_rec[1]/((Nevents)*(Nevents)));
result[1].push_back(0);
   return result;
 }
 //=====================================================================================================
 void PrintReconstructionEfficiencyTable(string ModelName, string category ,vector<float> massPoints,float width,string caption)
 {
    std::cout.unsetf ( std::ios::floatfield );
   std::cout.setf(std::ios::fixed);
   std::cout.precision(3);
   string X = "X";
   string VV = "WW";
   if(ModelName.find("Wprime") != string::npos)
   {
    X = "W$'$"; 
    VV="WZ";
   }
   if(ModelName.find("Zprime") != string::npos)
   {
    X = "Z$'$"; 
   }
   
   
   std::cout<< " Model: " << ModelName<< std::endl;
   std::cout<<"\\begin{table}"<<std::endl;
   std::cout<<"\\caption{"<<caption <<"}"<<std::endl;
   std::cout<<"\\begin{tabular}{|l|c|c|c|c|c|c|}"<<std::endl;
   std::cout<<"\\hline"<<std::endl; 
   std::cout << " & \\multicolumn{3}{c|}{"<<X<<"$\\rightarrow$"<< VV<< "$\\rightarrow e \\nu q \\bar{q}'$ } & \\multicolumn{3}{c|}{ "<<X<<"$\\rightarrow$ "<< VV <<"$\\rightarrow \\mu \\nu q \\bar{q}' $} \\\\"<<std::endl; 
   std::cout<<"\\hline"<<std::endl;
   std::cout<<"$M_x$ & \\tiny{exact efficiency}&\\tiny{parametrised efficiency}& \\tiny{relative error (in \\%)}  & \\tiny{exact efficiency}& \\tiny{parametrised efficiency} & \\tiny{relative error (in \\%)} \\\\"<< std::endl;
   std::cout<<"\\hline"<<std::endl;
   for(int i=0;i<massPoints.size();i++)
   {
     vector<vector<double> > eff = ExtractRecoAndTestEfficiency(ModelName,category ,massPoints[i],width);
     std::cout<< int(massPoints[i]) << " & "<< eff[0][1]<< " & "<< eff[1][1]<< "&";
     std::cout.precision(0);
     std::cout<< TMath::Abs(eff[0][1]-eff[1][1])/eff[1][1]*100;
     std::cout.precision(3);
     std::cout<< " & " << eff[0][0]<< " & " << eff[1][0]<<" & ";
     std::cout.precision(0);
     std::cout<< TMath::Abs(eff[0][0]-eff[1][0])/eff[1][0]*100  <<" \\\\"<<std::endl;
     std::cout.precision(3);
   }
   
   std::cout<<"\\hline"<<std::endl;
   std::cout<<"\\end{tabular}"<<std::endl;
   std::cout<<"\\label{tab:EffTest"<<ModelName<<"}"<<std::endl;
   std::cout<<"\\end{table}"<<std::endl;
 }

 //======================================================================================================
 
 void EfficiencyUncertaintyForDatacards(vector<float> mass,string channel, string category)
 {
  float width =0.1;
  vector<vector<double> > eff;
  vector<string> modelList = {"Wprime","Zprime","RSGrav","Radion"};
  int index = 0;
  double uncertainty;
  string filename = "/home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/sys/signal_eff_uncertainty_"+channel+"_"+category+".txt";
  ofstream f;
  f.open(filename,ios::ate);
  f<< "effUnc"<<std::endl;
  if(channel.find("mu")!=string::npos)
  {
   index =1; 
  }
  
  for(int i=0;i< mass.size();i++)
  {
  for(int l=0;l< modelList.size();l++)
  {
   eff = ExtractRecoAndTestEfficiency(modelList[l],category,mass.at(i),width);
   double tmp = TMath::Abs(eff[0][index]-eff[1][index])/eff[1][index];
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
   f<< "BulkG_WW_lvjj_M" << mass[i]<<" "<< u/100.  << std::endl;
   }
   f.close();
 }