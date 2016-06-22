#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
#include "TH1.h"
#include "TH2.h"
#include "TEfficiency.h"
#include "TCanvas.h"

string getFileName(string directory, string ModelName,string decayMode,float mass,float width, int number)
{
  string Smass = std::to_string(int(mass));
  string Swidth = std::to_string(int(width*10));
  string Snumber = std::to_string(number);
  
  string SfileName = "had no name yet";
  string VV = "WW";
  string Vlep ="W";
  string Vhad ="W";
  
  if(decayMode.find("ll")!=string::npos)
  {
    Vlep = "Z";
  }
  
  if(decayMode.find("ZZ")!=string::npos)
  {
    VV="ZZ";
    Vhad="Z";
  }
  if(decayMode.find("WZ")!=string::npos or ModelName.find("Wprime")!=string::npos)
  {
   VV="WZ";
   if(decayMode.find("lv")!=string::npos)
   {
   Vhad="Z";
   }
  }
  
  if(decayMode.find("lvjj")!=string::npos)
  {
    if(width==0.0)
    {
    SfileName =directory+ModelName+"To"+VV+"To"+Vlep+"lep"+Vhad+"had_narrow_M-"+Smass+"/EXOVVTree_"+ModelName+"To"+VV+"To"+Vlep+"lep"+Vhad+"had_narrow_M-"+Smass+"_"+Snumber+".root";
    }
    else
    {
       SfileName =directory+ModelName+"To"+VV+"To"+Vlep+"lep"+Vhad+"had_width0p"+Swidth+"_M-"+Smass+"/EXOVVTree_"+ModelName+"To"+VV+"To"+Vlep+"lep"+Vhad+"had_width0p"+Swidth+"_M-"+Smass+"_"+Snumber+".root";
    }
  }
  else if(decayMode.find("lljj") !=string::npos)
  {
    //naming not clear yet! (ZZ channel)
  }
  
  else if(decayMode.find("jjjj") !=string::npos)
  {
    if(width==0.0)
    {
      SfileName = directory+ModelName+"To"+VV+"_narrow_M-"+Smass+"_13TeV-madgraph_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/EXOVVTree_"+ModelName+"To"+VV+"_narrow_M-"+Smass+"_13TeV-madgraph_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_"+Snumber+".root";
      ifstream f(SfileName.c_str());
      if(!(f.good()))
      {
	SfileName = directory+ModelName+"To"+VV+"_narrow_M-"+Smass+"_13TeV-madgraph_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/EXOVVTree_"+ModelName+"To"+VV+"_narrow_M-"+Smass+"_13TeV-madgraph_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2_"+Snumber+".root";
	f.close();
      f.open(SfileName.c_str());
      if(!f.good())
      {
	SfileName = directory+ModelName+"To"+VV+"_narrow_M-"+Smass+"_13TeV-madgraph_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/EXOVVTree_"+ModelName+"To"+VV+"_narrow_M-"+Smass+"_13TeV-madgraph_RunIIFall15MiniAODv1_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_"+Snumber+".root";
      }
      }
      f.close();
    }
    else
    {
      SfileName = directory+ModelName+"To"+VV+"_width0p"+Swidth+"_M-"+Smass+"_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/EXOVVTree_"+ModelName+"To"+VV+"_width0p"+Swidth+"_M-"+Smass+"_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_"+Snumber+".root";
      ifstream f(SfileName.c_str());
      if(!(f.good()))
      {
	SfileName = directory+ModelName+"To"+VV+"_width0p"+Swidth+"_M-"+Smass+"_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/EXOVVTree_"+ModelName+"To"+VV+"_width0p"+Swidth+"_M-"+Smass+"_TuneCUETP8M1_13TeV-madgraph-pythia8_RunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2_"+Snumber+".root";
	
      }
      f.close();
    }
  }
  else
  {
   std::cout << " no valid decayMode given " << decayMode <<std::endl;
  }
  
  
  return SfileName;  
}

//=================================================================================================
string determineVV(string decayMode)
{
  string VV = "WW";
  if(decayMode.find("ZZ")!=string::npos)
   {
    VV="ZZ"; 
   }
   if(decayMode.find("W")!=string::npos and decayMode.find("Z")!=string::npos)
   {
      VV="WZ";
   }
   return VV;
}
//=================================================================================================

string determineSemilepHadOrLep(string decayMode)
{
  string mode = "hadronic";
   if((decayMode.find("lv")!=string::npos or decayMode.find("ll")!=string::npos) and decayMode.find("jj")!=string::npos)
   {
    mode = "semileptonic"; 
   }
   if((decayMode.find("lvlv")!=string::npos or decayMode.find("llll")!=string::npos))
   {
    mode = "leptonic"; 
   }
  return mode;
}
//============================================================================================

string determineFileName(string WhichRootFile,string modelName, string channel, string category, string decayMode)
{
  string VV = determineVV(decayMode);
  string mode = determineSemilepHadOrLep(decayMode);
  string result;
  
 if(WhichRootFile.find("EfficiencyHistos")!=string::npos)
 {
   result = "/storage/jbod/dschaefer/EfficiencyHistos/"+mode+"/To"+VV+"/"+modelName+"To"+VV+"Kinematics_"+channel+"_"+category+".root";
   
 }
  
  return result;
}

//================================================================================================


TH1F* fillHistoWithFractionOfSignalEvents(float fraction,TH1* hSignal,int nBins)
{
  vector<double> edges;
  double Sum = hSignal->GetEntries();
  vector<double> entry;
  vector<double> mass;
  int binN;
  double binC;
  double binCenter;
  int max=0;
  int maxBin=0;
  int indexMin=0;
  int indexMax=0;
  double SumFraction=0;
  
  for(int x=0;x<nBins;x++)
  {
    binN = hSignal->GetBin(x);
    binC = hSignal->GetBinContent(binN);
    binCenter = hSignal->GetBinCenter(binN);
    edges.push_back(hSignal->GetBinLowEdge(binN));
    entry.push_back(binC);
    mass.push_back(binCenter);
    if(binC>max)
    {
      max = binC;
      maxBin = binN;
    }
  }
  //std::cout << mass.size()<< " " << entry.size()<< " " << edges.size() << std::endl;
  SumFraction =max;
  for(int i=1;i<int(nBins/2.0);i++)
  {
    if((maxBin-i)<0)
    {
      SumFraction += entry.at(maxBin+i);
    }
    else
    {
    SumFraction += entry.at(maxBin-i)+ entry.at(maxBin+i);
    }
    if(SumFraction > Sum*fraction)
    {
      indexMin=maxBin-i;
      if(indexMin<0)
      {
	indexMin =0;
      }
      indexMax=maxBin+i;
      break;
    }
  }
  if(SumFraction< Sum*fraction)
  {
    int i=1;
   while((maxBin+indexMax+i)<1000)
   {
    SumFraction += entry.at(maxBin+i);
     if(SumFraction > Sum*fraction)
    {
      indexMax=maxBin+indexMax+i;
      break;
    }
     i++;
   }
  }
 float* x = new float[indexMax-indexMin];
 
 for(int i=0;i<(indexMax-indexMin);i++)
 {
  x[i] = edges.at(indexMin+i); 
 }
 TH1F* h = new TH1F("hmWW","m_{WW} spectrum",(indexMax-indexMin)-1,x);
 for(int i=0;i<(indexMax-indexMin);i++)
 {
   for(int j=0;j<entry.at(indexMin+i);j++)
   {
    h->Fill(mass.at(indexMin+i)); 
   }
  }
  h->Sumw2(kTRUE);
  if((indexMax-indexMin)>=80)
    h->Rebin(2);
 return h; 
  
}


//============================================================================================

void setErrors(TH2* histo, TEfficiency* Eff)
{
  double ErrorLow=0;
  double ErrorHigh=0;
  int Bin=0;
  int nBinsX = histo->GetNbinsX();
  int nBinsY = histo->GetNbinsY();
  for(int x =0;x<nBinsX;x++)
  {
    for(int y = 0;y<nBinsY;y++)
    {
    Bin = histo->GetBin(x,y);
    ErrorLow = Eff->GetEfficiencyErrorLow(Bin);
    ErrorHigh = Eff->GetEfficiencyErrorUp(Bin);
    if(ErrorLow>ErrorHigh)
    {
     histo->SetBinError(Bin,ErrorLow);
    }
    else
    {
      histo->SetBinError(Bin,ErrorHigh);
    }
    }
  }
  
}

//==================================================================================================


void prepareCanvas(TCanvas* canv, int W, int H)
{
  int H_ref = H; 
  int W_ref = W; 
  
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);
  
  //return canv;
  
}





