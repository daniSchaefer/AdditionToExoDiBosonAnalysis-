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
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "WorkOnHistos.h"
#include "TLatex.h"
// #include "/home/dschaefer/root/analysisCodeJennifer/EXOVVFitter-master_original/PDFs/HWWLVJRooPdfs.h"
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "RooFFTConvPdf.h"
#include "TObject.h"
#include "TLegend.h"
#include "RooHist.h"



//=============================================================================
void PrintBinContents(TH2* histo, vector<double> BinsX, vector<double> BinsY,const char* title, bool printErrors)
{
  int nBinsX = BinsX.size();
  int nBinsY = BinsY.size();
//   if(isPrecisionSet)
//   {
   std::cout.unsetf ( std::ios::floatfield );
   std::cout.setf(std::ios::fixed);
   std::cout.precision(2);
//   }
//   if(!isPrecisionSet)
//   {
//    std::cout.unsetf ( std::ios::floatfield );
//    std::cout.setf(std::ios::fixed);
//    std::cout.precision(0);
//   }
  std::cout << "\\begin{table} \\small"<< std::endl;
 
  std::cout<<"\\caption{"<< title <<"}"<<std::endl;
  std::cout<<"\\begin{tabular}{|";
  for(int i=0;i<nBinsY;i++)
  {
   std::cout<<"c";
  }
  std::cout<<"|}"<<std::endl;
  std::cout<<"\\hline"<<std::endl;
  std::cout<<"$p_T$ range in GeV & \\multicolumn{"<<nBinsY-1<<"}{c|}{$|\\eta|$ range}\\\\"<<std::endl;
 std::cout<<"\\hline"<<std::endl;
 std::cout<<"\\hline"<<std::endl;
 std::cout.precision(1); 
 for(int i=0;i<nBinsY-1;i++)
  {
    if(i==6)
    {
     std::cout.precision(2); 
    }
    std::cout<< " & $"<<BinsY[i]<<"-" << BinsY[i+1]<<"$";
    std::cout.precision(1);
  }
   std::cout.precision(2); 
  std::cout<<" \\\\ " << std::endl;
  std::cout<<"\\hline"<<std::endl;
  int i =0;
  //for(int y=(nBinsY-1);y>0;y--)
  //for(int x=(nBinsX-1);x>0; x--)
  for(int x=1;x<=(nBinsX-1);x++)
 {
   std::cout<< "$"<< int(BinsX[i])<<"-"<<int(BinsX[i+1])<<"$";
   for(int y=1;y<(nBinsY-0);y++)
//    for(int x=1;x<=(nBinsX-1); x++)
    {
      if(histo->GetBinContent(histo->GetBin(x,y))<0.001)
      {
	std::cout << " & - ";
      }
      else
      {
      std::cout /*<< hWElEff->GetBin(x,y)*/ <<  " & " << histo->GetBinContent(histo->GetBin(x,y));
      }
      if(printErrors)
      {std::cout << "$\\pm$ "<< histo->GetBinError(histo->GetBin(x,y)); }
    }
    std::cout <<" \\\\ " << std::endl;
   i++;
 }
 std::cout<<"\\hline"<<std::endl;
 std::cout << "\\end{tabular}"<< std::endl;
  std::cout<<"\\end{table}"<<std::endl;
 std::cout.setf(std::ios::floatfield); 
}

//=============================================================================

void PrintBinContentsMinus1(TH2* histo, vector<double> BinsX, vector<double> BinsY,const char* title, bool isPrecisionSet)
{
  
  int nBinsX = BinsX.size();
  int nBinsY = BinsY.size();
//   if(isPrecisionSet)
//   {
//   std::cout.unsetf ( std::ios::floatfield );
//   std::cout.setf(std::ios::fixed);
//   std::cout.precision(2);
//   }
//   if(!isPrecisionSet)
//   {
//    std::cout.unsetf ( std::ios::floatfield );
//    std::cout.setf(std::ios::fixed);
//    std::cout.precision(0);
//   }
  std::cout << "\\begin{table}"<< std::endl;
 
  std::cout<<"\\caption{"<< title <<"}"<<std::endl;
  std::cout<<"\\begin{tabular}{";
  for(int i=0;i<nBinsY+1;i++)
  {
   std::cout<<"c";
  }
  std::cout<<"}"<<std::endl;
  std::cout<<"$p_T$ range & \\multicolumn{"<<nBinsY<<"}{c}{$|\\eta|$ range}\\\\"<<std::endl;
 
  for(int i=0;i<nBinsY-1;i++)
  {
    std::cout<< " & $"<<BinsY[i]<<"-" << BinsY[i+1]<<"$";
  }
  std::cout<<" \\\\ " << std::endl;
 
  int i =0;
  //for(int y=(nBinsY-1);y>0;y--)
  //for(int x=(nBinsX-1);x>0; x--)
   for(int x=1;x<=(nBinsX-1);x++)
 {
   std::cout<<"$" <<BinsX[i]<<"-"<<BinsX[i+1]<<"$";
   for(int y=1;y<(nBinsY-0);y++)
//    for(int x=1;x<=(nBinsX-1); x++)
    {
      
      if(histo->GetBinContent(histo->GetBin(x,y)) !=0)
      {
      std::cout /*<< hWElEff->GetBin(x,y)*/ <<  " & " << TMath::Abs(histo->GetBinContent(histo->GetBin(x,y))-1);
      }
      else
      {
	std::cout << " & " << histo->GetBinContent(histo->GetBin(x,y));
      }
    }
    std::cout <<" \\\\ " << std::endl;
   i++;
 }
 std::cout << "\\end{tabular}"<< std::endl;
  std::cout<<"\\end{table}"<<std::endl;
  
}

//=============================================================================

vector<double> SumOverAllFilledBins(TH2* histo,int nBinsX,int nBinsY)
{
  double sum=0.0;
  double NumberBins=0;
  vector<double> result;
   for(int y= 0;y<(nBinsY-0);y++)
 {
   for(int x=0;x<=(nBinsX-1); x++)
    {
      int BinNumber= histo->GetBin(x,y);
      if(histo->GetBinContent(BinNumber)>0)
      {
      sum +=histo->GetBinContent(BinNumber);
      NumberBins+=1;
      }
    }
 }
 result.push_back(NumberBins);
 result.push_back(sum);
 return result;
 
}
//=============================================================================
double GetMaxValue(TH1* histo,int nBins)
{
  double max =0;
  for(int x=0;x<nBins;x++)
  {
    if(histo->GetBinContent(x)>max )
      max = histo->GetBinContent(x);
  }
  return max;
}


//=============================================================================

vector<vector<double> > MakeListOfWeights(TH2* histo, int nBinsX, int nBinsY)
{
  vector<vector<double> > weights(2);
  for(int y= 0;y<(nBinsY-0);y++)
 {
   for(int x=0;x<=(nBinsX-0); x++)
    {
      int BinNumber= histo->GetBin(x,y);
      weights[0].push_back(BinNumber);
      weights[1].push_back(histo->GetBinContent(BinNumber));
    }
 }
 return weights;
}


//=============================================================================

vector<vector<double> > MakeListOfWeights(TH2* histo, vector<double> BinsX, vector<double> BinsY)
{
  int nBinsY = BinsY.size();
  int nBinsX = BinsX.size();
  vector<vector<double> > weights(6);
  
//   for(int i=0;i<nBinsY-1;i++)
//   {
//    weights[2].push_back(BinsY.at(i));
//    weights[3].push_back(BinsY.at(i+1));
//   }
  for(int x= 0;x<(nBinsX-1);x++)
 {
//    weights[0].push_back(BinsX[x]);
//    weights[1].push_back(BinsX[x+1]);
   for(int y=0;y<(nBinsY-1); y++)
    {
      int BinNumber= histo->GetBin((x+1),(y+1));
      weights[5].push_back(BinNumber);
      weights[4].push_back(histo->GetBinContent(BinNumber));
      weights[0].push_back(BinsX[x]);
      weights[1].push_back(BinsX[x+1]);
      weights[2].push_back(BinsY.at(y));
      weights[3].push_back(BinsY.at(y+1));
    }
 }
 return weights;
}

//==============================================================================

void PrintRatioWithWeights(TH2* passedHisto, TH2* reweightHisto, vector<vector<double> > weights, vector<double> BinsX, vector<double> BinsY,const char* title, bool isPrecisionSet)
{
  int nBinsX = BinsX.size();
  int nBinsY = BinsY.size();
  ReweightHistogram(reweightHisto,weights);
  vector<vector<double> > newWeights(2);
  for(int x=0;x<nBinsX;x++)
  {
   for(int y=0;y<nBinsY;y++)
   {
     double binContent = passedHisto->GetBinContent(x,y);
     double binNumber = passedHisto->GetBin(x,y);
     newWeights[0].push_back(binNumber);
    if(binContent!=0)
    {
     newWeights[1].push_back(1.0/double(binContent));
    }
    else {newWeights[1].push_back(0);}
   }
  }
  ReweightHistogram(reweightHisto,newWeights); 
  PrintBinContents(reweightHisto,BinsX, BinsY,title, isPrecisionSet);
}



//==============================================================================


void ReweightHistogram(TH2* histo, vector<vector<double> > weights, bool doNorm)
{
  double binContent=0;
  int size = weights[0].size();
  for(int i=0;i<size;i++)
  {
    binContent = histo->GetBinContent(weights[0][i]);
    //std::cout<< weights[0][i]<<std::endl;
    if(!doNorm)
    {
    histo->SetBinContent(weights[0][i],binContent*weights[1][i]);
    }
    if(doNorm and weights[1][i]!=0)
    {
      histo->SetBinContent(weights[0][i],binContent/weights[1][i]);
    }
  }
}


//=================================================================================

TH2F* GenerateAllTables(TH2F* hWEl_rec,TH2F* hWEl_genWithVeto,TH2F* hWEl_2TeV, TH2F* hWEl_rec_2TeV,int pdgId,int nBinsX, int nBinsY, vector<double> BinsX, vector<double> BinsY,TCanvas* c1)
{
  TH2F* hWEl_2TeV_weights	= new TH2F(*hWEl_2TeV);
  style2D(hWEl_rec_2TeV,"Generator p_{t}^{W} [GeV]","Generator |#eta|","# events");
  style2D(hWEl_2TeV_weights,"Generator p_{t}^{W} [GeV]","Generator |#eta|","# events");
  
 const char* title1;  
 const char* title2;  
 const char* title3;  
 const char* title4;
 const char* title5;
  
   TEfficiency* WElEff=0;
 
 
 if(TEfficiency::CheckConsistency(*hWEl_rec,*hWEl_genWithVeto))
 {
   
   if(pdgId ==11)
 {
   title1 ="events with no lepton selections on 2 TeV sample";
   title2 ="events with electron selection applied to 2 TeV sample";
   title3 ="ratio events without selections reweighted and events after electron selection";
   title4 = "W #rightarrow e #nu and W #rightarrow #tau #nu #rightarrow e #nu #nu #nu";
   title5 = "the ratio of the number of events without electron selection over the number of events with electron selection minus 1";
 }
 if(pdgId ==13)
 {
   title1 ="events with no lepton selections on 2 TeV sample";
   title2 ="events with muon selection applied to 2 TeV sample";
   title3 ="ratio events without selections reweighted and events after muon selection";
   title4 = "W #rightarrow #mu #nu and W #rightarrow #tau #nu #rightarrow #mu #nu #nu #nu";
   title5 = "the ratio of the number of events without muon selection over the number of events with moun selection minus 1";
   
 }
 if(pdgId ==24)
   {
   title1 ="events with no hadron selections on 2 TeV sample";
   title2 ="events with jet selection applied to 2 TeV sample";
   title3 ="ratio events without selections reweighted and events after hadron selection";
   title4 = "W #rightarrow q q' ";
   title5 = "the ratio of the number of events without hadron selection over the number of events with hadron selection minus 1";
   
 }
   
   WElEff=new TEfficiency(*hWEl_rec,*hWEl_genWithVeto);
   TH2* hWElEff = WElEff->CreateHistogram();
   hWElEff->SetTitle(title4);
   style2D(hWElEff,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
   c1->cd();
    gPad->SetRightMargin(0.15);
   hWElEff->Draw("COLZ");
 

 
 PrintBinContents(hWElEff, BinsX, BinsY);
 vector<vector<double> > weightsElectronChannel = MakeListOfWeights(hWElEff, nBinsX, nBinsY);
 std::cout << std::endl;
 PrintBinContents(hWEl_2TeV,BinsX,BinsY,title1,0);
 std::cout << std::endl;
 PrintBinContents(hWEl_rec_2TeV,BinsX, BinsY,title2,0);
 std::cout << std::endl;

  std::cout << std::endl;
   std::cout << std::endl;
 PrintRatioWithWeights(hWEl_rec_2TeV, hWEl_2TeV_weights, weightsElectronChannel, BinsX, BinsY,title3);
 std::cout<<std::endl;
 PrintBinContentsMinus1(hWEl_2TeV_weights,BinsX, BinsY, title5,1);
 

 }
 return hWEl_2TeV_weights;
}

//============================================================================================

TH2* GetEfficiencies(TH2* passedHisto, TH2* Histo, TCanvas* c1)
{
  TEfficiency* Eff=0;
  TH2* hEff=0;
  if(TEfficiency::CheckConsistency(*passedHisto,*Histo))
 {
   Eff=new TEfficiency(*passedHisto,*Histo);
   hEff = Eff->CreateHistogram();
   style2D(hEff,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
   c1->cd();
    gPad->SetRightMargin(0.15);
   hEff->Draw("COLZ");
   
 }
 setErrors(hEff,Eff);
 return hEff;
  
}

TH2* GetEfficiencies(TH2* passedHisto, TH2* Histo, TCanvas* c1,const char* zAxistitle)
{
  TEfficiency* Eff=0;
  TH2* hEff=0;
  if(TEfficiency::CheckConsistency(*passedHisto,*Histo))
 {
   Eff=new TEfficiency(*passedHisto,*Histo);
   hEff = Eff->CreateHistogram();
   style2D(hEff,"Generator p_{t}^{W} [GeV]","Generator |#eta|",zAxistitle);
   c1->cd();
    gPad->SetRightMargin(0.15);
   hEff->Draw("COLZ");
   
 }
 setErrors(hEff,Eff);
 return hEff;
  
}

TH2* GetEfficiencies(TH2* passedHisto, TH2* Histo, TCanvas* c1, float max)
{
  TEfficiency* Eff=0;
  TH2* hEff=0;
  if(TEfficiency::CheckConsistency(*passedHisto,*Histo))
 {
   Eff=new TEfficiency(*passedHisto,*Histo);
   hEff = Eff->CreateHistogram();
   style2D(hEff,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
   c1->cd();
    gPad->SetRightMargin(0.15);
   hEff->SetMaximum(max);
   hEff->Draw("COLZ");
   
 }
 setErrors(hEff,Eff);
 return hEff;
  
}

TH2* GetEfficiencies(TH2* passedHisto, TH2* Histo)
{
  TEfficiency* Eff=0;
  TH2* hEff=0;
  if(TEfficiency::CheckConsistency(*passedHisto,*Histo))
 {
   Eff=new TEfficiency(*passedHisto,*Histo);
   hEff = Eff->CreateHistogram();
   style2D(hEff,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
   
 }
 setErrors(hEff,Eff);
 return hEff;
  
}

TH2* GetEfficienciesWithError(TH2* passedHisto, TH2* Histo,int nBinsX,int nBinsY)
{
  TEfficiency* Eff=0;
  TH2* hEff=0;
  if(TEfficiency::CheckConsistency(*passedHisto,*Histo))
 {
   Eff=new TEfficiency(*passedHisto,*Histo);
   hEff = Eff->CreateHistogram();
   style2D(hEff,"Generator p_{t}^{W} [GeV]","Generator |#eta|","Reconstruction #times ID efficiency");
   
 }
 double sumLOW=0.0;
 double sumHIGH=0.0;
 double NumberBins=0;
 for(int y= 0;y<(nBinsY-0);y++)
 {
   for(int x=0;x<=(nBinsX-1); x++)
    {
      int BinNumber= hEff->GetBin(x,y);
      if(hEff->GetBinContent(BinNumber)>0)
      {
      sumLOW +=Eff->GetEfficiencyErrorLow(BinNumber);
      sumHIGH += Eff->GetEfficiencyErrorUp(BinNumber);
      NumberBins+=1;
      }
    }
 }
 std::cout<< sumLOW/double(NumberBins) << " error low" << std::endl;
 std::cout<< sumHIGH/double(NumberBins) << " error high"<<std::endl;
 setErrors(hEff,Eff);
 return hEff;
  
  
}

//============================================================================================

double GetRatio(TH2* histo1, TH2* histo2,int nBinsX, int nBinsY)
{
  vector<double> sum1 = SumOverAllFilledBins(histo1,nBinsX,nBinsY); 
  vector<double> sum2 = SumOverAllFilledBins(histo2,nBinsX,nBinsY);
  double result = sum1[1]/double(sum2[1]);
  return result;
}

//====================================================================================

TH2* GetRatioHisto(TH2* histo1, TH2* histo2,int nBinsX, int nBinsY)
{
  TH2* result = (TH2*) histo1->Clone("result");
  vector<vector<double> > weights = MakeListOfWeights(histo2,nBinsX,nBinsY);
  ReweightHistogram(result, weights,1);
  return result;
  
}

//====================================================================================


void SetStyleEffPlots(TH2* histo,TCanvas* c1,const char* title, const char* channel,const char * additional_channel,int xPosition)
{
  
  c1->cd();
  gPad->SetRightMargin(0.15);
  gPad->SetLeftMargin(0.13);
  string st= string(channel);
  if(st.find("W")== string::npos)
  {
    style2D(histo,"Generator p_{t}^{Z} [GeV]","Generator |#eta_{Z}|","Reconstruction #times ID efficiency");
  }
  else
  {
    style2D(histo,"Generator p_{t}^{W} [GeV]","Generator |#eta_{W}|","Reconstruction #times ID efficiency");
  }
  histo->SetTitle(title);
  histo->SetMaximum(1);
  histo->SetMinimum(0);
  histo->Draw("COLZ");
  TLatex text;
  text.SetTextFont(43); 
  text.SetTextSize(16);
  text.DrawLatex(xPosition, 2.3, channel);
  text.DrawLatex(xPosition, 2.1, additional_channel); 
}

void SetStyleEffPlots(TH2* histo,TCanvas* c1,const char* title, const char* channel,const char * additional_channel,int xPosition, const char* zAxisTitle)
{
  
  c1->cd();
  gPad->SetRightMargin(0.15);
  gPad->SetLeftMargin(0.13);
  string st= string(channel);
  if(st.find("W")== string::npos)
  {
    style2D(histo,"Generator p_{t}^{Z} [GeV]","Generator |#eta_{Z}|",zAxisTitle);
  }
  else
  {
    style2D(histo,"Generator p_{t}^{W} [GeV]","Generator |#eta_{W}|",zAxisTitle);
  }
  histo->SetTitle(title);
  histo->SetMaximum(1);
  histo->SetMinimum(0);
  histo->Draw("COLZ");
  TLatex text;
  text.SetTextFont(43); 
  text.SetTextSize(16);
  text.DrawLatex(xPosition, 2.3, channel);
  text.DrawLatex(xPosition, 2.1, additional_channel); 
}

