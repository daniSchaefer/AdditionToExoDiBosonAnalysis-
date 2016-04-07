#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
#include "TH1.h"
#include "TH2.h"
#include "TEfficiency.h"

string getFileName(string directory, string ModelName,float mass,float width, int number,bool isInJbod)
{
  string Smass = std::to_string(int(mass));
  string Swidth = std::to_string(int(width*10));
  string Snumber = std::to_string(number);
  
  string SfileName = "";
  
  if(ModelName.find("Wprime") !=string::npos)
  {
    if(width==0.0)
    {
   SfileName =directory+ModelName+"ToWZToWlepZhad_narrow_M-"+Smass+"/EXOVVTree_"+ModelName+"ToWZToWlepZhad_narrow_M-"+Smass+"_"+Snumber+".root";
    }
    else
    {
      if(isInJbod)
      {
      SfileName =directory+ModelName+"ToWZToWlepZhad_width0p"+Swidth+"_M-"+Smass+"/EXOVVTree_"+ModelName+"ToWZToWlepZhad_width0p"+Swidth+"_M-"+Smass+"_"+Snumber+".root";
      }
      else
      {
	 SfileName =directory+ModelName+"ToWWToWlepWhad_width0p"+Swidth+"_M-"+Smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_width0p"+Swidth+"_M-"+Smass+"_"+Snumber+".root";
      }
    }
  }
    if(ModelName.find("Radion") != string::npos /*or ModelName.find("Zprime") != string::npos*/ or ModelName.find("RSGrav") != string::npos )
  {
    if(width==0.0)
    {
      std::cout << " no narrow width sample exists" <<std::endl;
  
    }
    else
    {
      SfileName =directory+ModelName+"ToWWToWlepWhad_width0p"+Swidth+"_M-"+Smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_width0p"+Swidth+"_M-"+Smass+"_"+Snumber+".root";
    }
  }
     if(ModelName.find("BulkGrav") != string::npos)
  {
    if(width==0.0)
    {
      
   SfileName =directory+ModelName+"ToWWToWlepWhad_narrow_M-"+Smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_narrow_M-"+Smass+"_1.root";
    }
    else
    {
      std::cout << " no width sample exists" <<std::endl;
    }
  }
  
   if(ModelName.find("Zprime") != string::npos)
  {
    if(width==0.0)
    {
      
   SfileName =directory+ModelName+"ToWWToWlepWhad_narrow_M-"+Smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_narrow_M-"+Smass+"_1.root";
    }
    else
    {
      SfileName =directory+ModelName+"ToWWToWlepWhad_width0p"+Swidth+"_M-"+Smass+"/EXOVVTree_"+ModelName+"ToWWToWlepWhad_width0p"+Swidth+"_M-"+Smass+"_"+Snumber+".root";
    }
  }
    //const char* fileName = SfileName.c_str();
    return SfileName;
    
}

//=================================================================================================


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








