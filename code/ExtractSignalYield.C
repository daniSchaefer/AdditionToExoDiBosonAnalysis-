#include "TGraphAsymmErrors.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"
#include "/usr/users/dschaefer/root/headerfiles/Op.h"
#include "/usr/users/dschaefer/root/headerfiles/EventSelection.h"
#include "/usr/users/dschaefer/root/headerfiles/GenFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/RecFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/StyleFunc.h"
#include "/usr/users/dschaefer/root/headerfiles/DebugFunc.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/General.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies2.h"
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"


using namespace RooFit;

namespace{
  int loadMyLibraryTriggerFunc(){
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/StyleFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/General.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/WorkOnHistos.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/MyClass.C+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/Op.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/EventSelection.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/GenFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/RecFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/passed_mu_jes.C+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfiles/DebugFunc.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies.cc+");
    gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/Efficiencies2.cc+");

 return 0;
}
  int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
}


float* getAcceptance(string ModelName,string decayMode,float* masspoints, int numberOfMassPoints);
float* getTheoryCrossSection(string ModelName,float ktilde);
float  getTheoryCrossSection(string ModelName, float mass, float ktilde);
float  getKtilde(string ModelName,float mass, float natural_width);
TGraph* getObservedLimit(string ModelName,string decayMode,float width,bool dependsOnKtilde=0);
TGraph* getLimitUp(string ModelName,string decayMode,float width,int sigma, bool dependsOnKtilde=0);
TGraph* getLimitDown(string ModelName,string decayMode,float width,int sigma, bool dependsOnKtilde =0);
float  getBranchingRatioToWW(string ModelName, float mass);
float  getBranchingRatioToZZ(string ModelName, float mass);
float  getWidthForKtilde(string ModelName,float mass,float ktilde);



void ExtractSignalYield(string ModelName, string decayMode, float natural_width, bool dependsOnKtilde=0)
{
  
  string dir = "/usr/users/dschaefer/root/results/";
  string outputfile = ModelName+"_"+decayMode+"_signalYield.root";
  //float natural_width =0.05;
  std::stringstream s;
      if(int(natural_width*100+0.5) == 10 or int(100*natural_width+0.5)==20 or int(natural_width*100+0.5)==30)
      {
	s << std::fixed << std::setprecision(1) << natural_width;
      }
      else
      {
	s << std::fixed << std::setprecision(2) << natural_width;
      }
  string swidth = s.str();
  float ktilde;
  string sktilde;
  if(dependsOnKtilde)
  {
   ktilde = natural_width;
   sktilde = swidth;
  }
  
  TGraph* limit = getObservedLimit(ModelName,decayMode,natural_width,dependsOnKtilde);
  TGraph* limitUP = getLimitUp(ModelName,decayMode,natural_width,1,dependsOnKtilde);
  TGraph* limitDOWN = getLimitDown(ModelName,decayMode,natural_width,1,dependsOnKtilde);
  TGraph* limitUP2 = getLimitUp(ModelName,decayMode,natural_width,2,dependsOnKtilde);
  TGraph* limitDOWN2 = getLimitDown(ModelName,decayMode,natural_width,2,dependsOnKtilde);
  
  std::cout << limit <<std::endl;
  std::cout << limitUP <<std::endl;
  std::cout << limitUP2 <<std::endl;
  std::cout << limitDOWN <<std::endl;
  std::cout << limitDOWN2 <<std::endl;
  
  int number;
  float* masses;
  if(decayMode.find("lvjj")!=string::npos)
  {
    masses = new float[38];
    number =38;
    float array[38] = {800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000,4100,4200,4300,4400,4500};
    masses = array;
  }
  else
  {
   number = 29;
   masses = new float[29];
   float array[29] = {1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000};
   masses = array;
  }
  TGraph* gryellow = new TGraph(2*number);
  TGraph* grgreen  = new TGraph(2*number);
  
  for(int m=0;m<number;m++)
  {
    gryellow->SetPoint(m,masses[m],limitUP->Eval(masses[m]));
    gryellow->SetPoint(number+m,masses[number-m-1],limitDOWN->Eval(masses[number-m-1]));
    grgreen->SetPoint(m,masses[m],limitUP2->Eval(masses[m]));
    grgreen->SetPoint(number+m,masses[number-m-1],limitDOWN2->Eval(masses[number-m-1]));
    
  }
  gryellow->SetFillColor(kYellow);
  grgreen->SetFillColor(kGreen);
  
  TCanvas* test = new TCanvas("test","test",400,400);
  test->SetLogy();
  limitUP->SetFillColor(kGreen+2);
  limitUP->SetLineColor(kGreen+2);
  limitUP->SetLineWidth(-1504);
  
  //limitUP->Draw("ACP");
  limitDOWN->SetFillColor(kBlue);
  limitDOWN->SetLineColor(kGreen+2);
  limitDOWN->SetLineWidth(-1504);
  //limitDOWN->Draw("CPsame");
  gryellow->Draw("AFsame");
  grgreen->Draw("Fsame");
  limit->SetLineColor(kBlue);
  limit->SetLineWidth(3);
  limit->Draw("Lsame");
  test->Update();
  
  float lumi = 2.10*1000;  //pb^-1
  if(decayMode.find("jjjj")!=string::npos){lumi = 2.6*1000;}//pb^-1
  float BR_W_to_lv = 0.327;
  float BR_W_to_jj = 0.674;
  float BR_Z_to_jj = 0.6991;
  
  
  
  //float *xs = getTheoryCrossSection(ModelName,0.1);
  
  //x values for which a theory prediction for production cross section exists
  float m_xs[10]  =  {800,900,1000,1500,1800,2000,2500,3000,3500,4500};
  float BR_G_to_WW[10];
  float BR_G_to_ZZ[10];
  float *acceptance;
  float N_expected[10];
  //float xs = 0.01;
  float *xs = new float[10];
  
  if(dependsOnKtilde)
  {
    xs = getTheoryCrossSection(ModelName,ktilde);
  }
  else
  {
    for(int i=0;i<10;i++)
    {
    if(natural_width!=0)
    {
      ktilde = getKtilde(ModelName,m_xs[i],natural_width);
      std::cout << m_xs[i] << " k = " << ktilde <<std::endl;
      xs[i] = getTheoryCrossSection(ModelName,m_xs[i],ktilde);
    }
    else
    {
      ktilde = getKtilde(ModelName,m_xs[i],0.02);
      std::cout <<  m_xs[i] << " k = " << ktilde <<std::endl;
      xs[i] = getTheoryCrossSection(ModelName,m_xs[i],ktilde);
    }
    }
  }
  
 
  
  TGraph* production_xs = new TGraph(10,m_xs,xs);
  
  TCanvas* c_xs = new TCanvas("c_xs","c_xs",400,400);
  c_xs->SetLogy();
  production_xs->SetMarkerColor(1);
  production_xs->GetXaxis()->SetTitle("m_G [GeV]");
  production_xs->GetYaxis()->SetTitle("theory production cross section");
  production_xs->Draw("AL");
  
  
  
  //if in hadronic case xs has to be a different number 
  //also this should then be the RS-grav cross section?!
  
  acceptance = getAcceptance(ModelName,decayMode,m_xs,10);
  
  for(int j =0;j<10;j++)
  {
    BR_G_to_WW[j] = getBranchingRatioToWW(ModelName,m_xs[j]);
    BR_G_to_ZZ[j] = getBranchingRatioToZZ(ModelName,m_xs[j]);
    if(decayMode.find("lvjj")!=string::npos)
    {
      N_expected[j] = acceptance[j]*xs[j]*lumi*BR_G_to_WW[j]*2*BR_W_to_jj*BR_W_to_lv;
    }
    if(decayMode.find("jjjj")!=string::npos)
    {
      N_expected[j] = acceptance[j]*xs[j]*lumi*(BR_G_to_WW[j]*2*BR_W_to_jj*BR_W_to_jj + BR_G_to_ZZ[j]*BR_Z_to_jj*BR_Z_to_jj);
    }
  }
  
  TGraph* N = new TGraph(10,m_xs,N_expected);
  //N->SetName("expected signal yield");
  grgreen->GetXaxis()->SetTitle("m_{VV} [GeV]");
  grgreen->GetYaxis()->SetTitle("number signal events");
  grgreen->GetYaxis()->SetTitleOffset(1.3);
  grgreen->SetTitle("");
  TCanvas* c_N = new TCanvas("c_N","c_N",600,400);
  gPad->SetRightMargin(0.1);
  gPad->SetLeftMargin(0.1);
  limit->SetLineColor(kBlue);
  limit->SetLineWidth(3);
  c_N->SetLogy();
  N->SetLineColor(kRed);
  N->SetLineWidth(2);
  //N->Draw("A");
  grgreen->SetMaximum(1000);
  grgreen->Draw("AF");
  gryellow->Draw("Fsame");
  limit->Draw("Csame");
  N->Draw("Csame");
  TLegend* leg = new TLegend(0.59,0.65,0.95,0.89);
  leg->SetFillColor(kWhite);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.04);
  leg->SetBorderSize(0);
  
  string title = "Preliminary";
  string cms = "#font[62]{CMS} #font[52]{"+string(title)+"} ";
  string lumitext = "2.6 fb^{-1}, #sqrt{s} = 13 TeV";
  string cmstext = "CMS ,2.6 fb^{-1}, #sqrt{s} = 13 TeV";
  if(decayMode.find("had")==string::npos){lumitext = "2.1 fb^{-1}, #sqrt{s} = 13 TeV";}
  string theory = "G #rightarrow WW, #Gamma = "+swidth;
  if(dependsOnKtilde)
  {
    theory = "G #rightarrow WW, #tilde{k} = "+sktilde;
  }
  if(ModelName.find("RSGrav")!=string::npos)
  {
   theory = "RS #rightarrow WW, #Gamma = "+swidth;
   if(dependsOnKtilde)
    {
      theory = "RS #rightarrow WW, #tilde{k} = "+sktilde;
    }
  }
  
  leg->AddEntry(grgreen,"Expected (95%)","f");
  leg->AddEntry(gryellow,"Expected (68%)","f");
  leg->AddEntry(limit,"observed","L");
  leg->AddEntry(N,theory.c_str(),"L");
  leg->Draw("same");
  
  TLatex CMS;
  int y = 1050;
  int x = 500;
  int x2 = 3400;
  if(decayMode.find("jjjj")!= string::npos){y=1050;x=1000;x2=3000;}
  CMS.SetTextFont(43);
  CMS.SetTextSize(18);
  CMS.DrawLatex(x,y,cms.c_str());
  CMS.DrawLatex(x2,y,lumitext.c_str());
  
  c_N->Update();
  if(dependsOnKtilde)
  {
    c_N->SaveAs(("/usr/users/dschaefer/root/results/misc/"+ModelName+"_limit_"+decayMode+"_ktilde"+swidth+".pdf").c_str());
  }
  else
  {
  c_N->SaveAs(("/usr/users/dschaefer/root/results/misc/"+ModelName+"_limit_"+decayMode+"_"+swidth+".pdf").c_str());
  }
  //c_N->SaveAs(("/usr/users/dschaefer/root/results/misc/limit_"+decayMode+"_"+swidth+".pdf").c_str());
  //limit->Draw("same");
}



float getBranchingRatioToWW(string ModelName, float mass)
{
   float BR_G_to_WW[10];
   int index =-1;
  if(mass ==800){index=0;}
  if(mass ==900){index=1;}
  if(mass ==1000){index=2;}
  if(mass ==1500){index=3;}
  if(mass ==1800){index=4;}
  if(mass ==2000){index=5;}
  if(mass ==2500){index=6;}
  if(mass ==3000){index=7;}
  if(mass ==3500){index=8;}
  if(mass ==4500){index=9;}
   if(ModelName.find("RSGrav")!=string::npos)
  {
   
	BR_G_to_WW[0] =  0.1334101405587990;
	BR_G_to_WW[1] =  0.1327240001449074;
	BR_G_to_WW[2] =  0.1322234359393874;
	BR_G_to_WW[3] =  0.1310058659239328;
	BR_G_to_WW[4] =  0.1307014833581888;
	BR_G_to_WW[5] =  0.1305692351528377;
	BR_G_to_WW[6] =  0.1303653230380301;
	BR_G_to_WW[7] =  0.1302540775411912;
	BR_G_to_WW[8] =  0.1301868377445514;
	BR_G_to_WW[9] =  0.1301131367091213;
       
  }
  if(ModelName.find("BulkGrav")!=string::npos)
  {
    
    BR_G_to_WW[0] = 0.2781621777017708	;
    BR_G_to_WW[1] = 0.2600300284419047	;
    BR_G_to_WW[2] = 0.24760630932823052	;
    BR_G_to_WW[3] = 0.22005013790397887	;
    BR_G_to_WW[4] = 0.21371662932013388	;
    BR_G_to_WW[5] = 0.21103043636291363	;
    BR_G_to_WW[6] = 0.20696480536908055	;
    BR_G_to_WW[7] = 0.20478514049527263	;
    BR_G_to_WW[8] = 0.20348064946832398	;
    BR_G_to_WW[9] = 0.2020619221283911	;
    }
    if(index>=0)
    {
      return BR_G_to_WW[index];
    }
    else return 0;
}

float getBranchingRatioToZZ(string ModelName, float mass)
{
  float BR_G_to_ZZ[10];
  int index =-1;
  if(mass ==800){index=0;}
  if(mass ==900){index=1;}
  if(mass ==1000){index=2;}
  if(mass ==1500){index=3;}
  if(mass ==1800){index=4;}
  if(mass ==2000){index=5;}
  if(mass ==2500){index=6;}
  if(mass ==3000){index=7;}
  if(mass ==3500){index=8;}
  if(mass ==4500){index=9;}
   if(ModelName.find("RSGrav")!=string::npos)
  {
	BR_G_to_ZZ[0] = 0.06704449099329272;
	BR_G_to_ZZ[1] = 0.0666303374283415 ;
	BR_G_to_ZZ[2] = 0.0663290555435926 ;
	BR_G_to_ZZ[3] = 0.06559935893649155;
	BR_G_to_ZZ[4] = 0.06537514401426231;
	BR_G_to_ZZ[5] = 0.06533879600711626;
	BR_G_to_ZZ[6] = 0.06521731448413957;
	BR_G_to_ZZ[7] = 0.06515109475152146;
	BR_G_to_ZZ[8] = 0.06511108871210751;
	BR_G_to_ZZ[9] = 0.0650672548341389 ;
       
  }
  if(ModelName.find("BulkGrav")!=string::npos)
  { 
    
    BR_G_to_ZZ[0] = 0.14301853100044015	;
    BR_G_to_ZZ[1] = 0.13294832734981618	;
    BR_G_to_ZZ[2] = 0.12607893374826087	;
    BR_G_to_ZZ[3] = 0.1109356953055133	;
    BR_G_to_ZZ[4] = 0.10747431531156655	;
    BR_G_to_ZZ[5] = 0.10600852517377926	;
    BR_G_to_ZZ[6] = 0.10379262318163233	;
    BR_G_to_ZZ[7] = 0.102605948149462	;
    BR_G_to_ZZ[8] = 0.1018961877814816	;
    BR_G_to_ZZ[9] = 0.1011246527052455	;  
   }
   if(index>-1)
   {
    return BR_G_to_ZZ[index];
   }
   else return 0;
}

float getWidthForKtilde(string ModelName, float mass, float ktilde)
{
  float gamma[10];
  float natural_width=0;
  float masses[10] = {800,900,1000,1500,1800,2000,2500,3000,3500,4500};
//   int index =-1;
//   if(mass >=800){index=0;}
//   if(mass >=900){index=1;}
//   if(mass >=1000){index=2;}
//   if(mass >=1500){index=3;}
//   if(mass >=1800){index=4;}
//   if(mass >=2000){index=5;}
//   if(mass >=2500){index=6;}
//   if(mass >=3000){index=7;}
//   if(mass >=3500){index=8;}
//   if(mass >=4500){index=9;}
  
  if(ModelName.find("BulkGrav")!=string::npos)
  {
	gamma[0]= 0.3372775058720474;
	gamma[1]= 0.5034518558626884;
	gamma[2]= 0.7147811639996965;
	gamma[3]= 2.621511614223211 ;
	gamma[4]= 4.624277270488186 ;
	gamma[5]= 6.4001849578035515;
	gamma[6]= 12.673149556967278;
	gamma[7]= 22.063436031770127;
	gamma[8]= 35.1942784732252  ;
	gamma[9]= 75.1709133299643  ;
  }
  if(ModelName.find("RSGrav")!=string::npos)
  {
	gamma[0]= 8.417560627337052;
	gamma[1]= 12.003250025993921;
	gamma[2]= 16.484442265444965;
	gamma[3]= 55.80278563385167;
	gamma[4]= 96.5038526679864;
	gamma[5]= 132.42477053185272;
	gamma[6]= 258.7833784314215;
	gamma[7]= 447.31224220622227;
	gamma[8]= 710.4451904556967;
	gamma[9]= 1510.2589884045055;
  }
  TGraph* g = new TGraph(10,masses,gamma);
  
  natural_width = g->Eval(mass)/mass*pow(ktilde,2)/pow(0.1,2);
  std::cout << mass << " " << natural_width << std::endl;
  return natural_width; 
  
}

float  getKtilde(string ModelName,float mass, float natural_width)
{
  float result =0;
  float gamma[10];
  int index =-1;
  if(mass ==800){index=0;}
  if(mass ==900){index=1;}
  if(mass ==1000){index=2;}
  if(mass ==1500){index=3;}
  if(mass ==1800){index=4;}
  if(mass ==2000){index=5;}
  if(mass ==2500){index=6;}
  if(mass ==3000){index=7;}
  if(mass ==3500){index=8;}
  if(mass ==4500){index=9;}
  
  if(ModelName.find("BulkGrav")!=string::npos)
  {
	gamma[0]= 0.3372775058720474;
	gamma[1]= 0.5034518558626884;
	gamma[2]= 0.7147811639996965;
	gamma[3]= 2.621511614223211 ;
	gamma[4]= 4.624277270488186 ;
	gamma[5]= 6.4001849578035515;
	gamma[6]= 12.673149556967278;
	gamma[7]= 22.063436031770127;
	gamma[8]= 35.1942784732252  ;
	gamma[9]= 75.1709133299643  ;
  }
  if(ModelName.find("RSGrav")!=string::npos)
  {
	gamma[0]= 8.417560627337052;
	gamma[1]= 12.003250025993921;
	gamma[2]= 16.484442265444965;
	gamma[3]= 55.80278563385167;
	gamma[4]= 96.5038526679864;
	gamma[5]= 132.42477053185272;
	gamma[6]= 258.7833784314215;
	gamma[7]= 447.31224220622227;
	gamma[8]= 710.4451904556967;
	gamma[9]= 1510.2589884045055;
  }
  if(index!=-1)
  {
     result = TMath::Sqrt(natural_width*mass/gamma[index])*0.1;
  }
  return result; 
}

float* getTheoryCrossSection(string ModelName,float ktilde)
{
  float* xs = new float[10];
  
   if(ModelName.find("BulkGrav")!=string::npos)
  {
    
    xs[0] = 0.018199328025736643;	
    xs[1] = 0.009802248453866633;	
    xs[2] = 0.0056657071801246945;	
    xs[3] = 0.0005727231501579456;	
    xs[4] = 0.00018315617607742797;	
    xs[5] = 0.00009062263600103764;	
    xs[6] = 0.00001868308774736877;	
    xs[7] = 4.412202866735033e-6;	
    xs[8] = 1.1518090410508347e-6;	
    xs[9] = 8.933087336020322e-8;
  }
  if(ModelName.find("RSGrav")!=string::npos)
  {
    xs[0] = 105.82236140624998;	
    xs[1] = 60.50468506172839;	
    xs[2] = 36.1295007;		
    xs[3] = 4.104032244444444;	
    xs[4] = 1.4021476327160491;	
    xs[5] = 0.7389458374999999;	
    xs[6] = 0.1726236152;		
    xs[7] = 0.04560398022222222;	
    xs[8] = 0.013291819591836734;	
    xs[9] = 0.001273477837037037;
  }
  for(int i=0;i<10;i++)
  {
   xs[i] = (ktilde*ktilde)/(0.1*0.1)*xs[i]; 
  }
  return xs;
}

float getTheoryCrossSection(string ModelName,float mass,float ktilde)
{
  float* xs = new float[10];
  float result =0;
  int index =-1;
  if(mass ==800){index=0;}
  if(mass ==900){index=1;}
  if(mass ==1000){index=2;}
  if(mass ==1500){index=3;}
  if(mass ==1800){index=4;}
  if(mass ==2000){index=5;}
  if(mass ==2500){index=6;}
  if(mass ==3000){index=7;}
  if(mass ==3500){index=8;}
  if(mass ==4500){index=9;}
  
   if(ModelName.find("BulkGrav")!=string::npos)
  {
    
    xs[0] = 0.018199328025736643;	
    xs[1] = 0.009802248453866633;	
    xs[2] = 0.0056657071801246945;	
    xs[3] = 0.0005727231501579456;	
    xs[4] = 0.00018315617607742797;	
    xs[5] = 0.00009062263600103764;	
    xs[6] = 0.00001868308774736877;	
    xs[7] = 4.412202866735033e-6;	
    xs[8] = 1.1518090410508347e-6;	
    xs[9] = 8.933087336020322e-8;
  }
  if(ModelName.find("RSGrav")!=string::npos)
  {
    xs[0] = 105.82236140624998;	
    xs[1] = 60.50468506172839;	
    xs[2] = 36.1295007;		
    xs[3] = 4.104032244444444;	
    xs[4] = 1.4021476327160491;	
    xs[5] = 0.7389458374999999;	
    xs[6] = 0.1726236152;		
    xs[7] = 0.04560398022222222;	
    xs[8] = 0.013291819591836734;	
    xs[9] = 0.001273477837037037;
  }
  if(index!=-1)
  {
    result = (ktilde*ktilde)/(0.1*0.1)*xs[index];
  }
  return result;
}




float* getAcceptance(string ModelName, string decayMode, float* masspoints,int numberOfMassPoints)
{
  float masses[5] = {800,1200,2000,3000,4000};
  int n = 5;
  float sy[n];
  float sy_el[n];
  float D_sy[n];
  int numberselectedEvents=0;
  int numbergeneratedEvents=0;
  float width = 0.1;
  float* acceptance = new float[numberOfMassPoints];
  string VV = determineVV(decayMode);
  string mode = determineSemilepHadOrLep(decayMode);
  
  string inputDir = "/storage/jbod/dschaefer/testEff/"+mode+"/To"+VV+"/";
  string inputfile = "";
  string category = "HP";
  
  TFile* f = new TFile();
  
  string channel = "had";
  if(decayMode.find("lvjj")!=string::npos)
  {
   channel = "mu"; 
  }
  if(ModelName.find("BulkGrav")!=string::npos){width = 0.0;}
  
  for(int m=0;m<n;m++)
  {
    if(decayMode.find("jjjj")!=string::npos)
    {
      inputfile = inputDir+ModelName+"To"+decayMode+"_Kinematics_"+channel+"_"+category+"_M"+std::to_string(int(masses[m]))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";

      
      TFile* tmp = f->Open(inputfile.c_str(),"READ");
      TH2F* histo = (TH2F*) tmp->Get("hW_had_rew");
      TH2F* histo_gen = (TH2F*) tmp->Get("hW_had_gen");
      
      numberselectedEvents = histo->GetEffectiveEntries(); //histo->GetEntries();
      numbergeneratedEvents = histo_gen->GetEntries();
      sy[m] = numberselectedEvents/double(numbergeneratedEvents);
      
      tmp->Close();
    }
    if(decayMode.find("lvjj")!=string::npos)
    {
      channel = "mu";
      for(int i=0;i<2;i++)
      {
	if(i==1){channel = "el";}
	inputfile = inputDir+ModelName+"To"+decayMode+"_Kinematics_"+channel+"_"+category+"_M"+std::to_string(int(masses[m]))+"_width0p"+std::to_string(int(10*width))+"_testEff.root";
	
	TFile* tmp = f->Open(inputfile.c_str(),"READ");
	TH2F* histo = (TH2F*) tmp->Get("hW_lep_rew");
	
	numberselectedEvents = histo->GetEffectiveEntries();//histo->GetEntries();
	numbergeneratedEvents = NumberOfEventsInFile(ModelName,decayMode,masses[m],width);
	
	if(i==0)
	{
	 sy[m] =numberselectedEvents/double(numbergeneratedEvents);
	}
	else
	{
	  sy_el[m] = numberselectedEvents/double(numbergeneratedEvents);
	}
	tmp->Close();
      } 
    }
  }
  
  if(decayMode.find("lvjj")!=string::npos)
  {
//     TGraph* g2 = new TGraph(n,masses,sy_el);
//     g2->SetName("signal yield");
//     g2->GetXaxis()->SetTitle("m_{VV} [GeV]");
//     g2->GetYaxis()->SetTitle("sy");
//     
//     c1->cd(2);
//     g2->Draw("AL");
//     g2->Write();
    
    //combine acceptance for electron and muon channel:
    for(int i=0;i<n;i++)
    {
      sy[i] = sy[i]+sy_el[i];
    }
  }
  TGraph* g = new TGraph(n,masses,sy);
  g->SetName("signal yield");
  g->GetXaxis()->SetTitle("m_{VV} [GeV]");
  g->GetYaxis()->SetTitle("sy");
  
  TCanvas* c1 = new TCanvas("c1","c1",400,400);
  //c1->Divide(2,1);
  c1->cd(1);
  g->Draw("AL");
  
  for(int j=0;j<numberOfMassPoints;j++)
  {
     acceptance[j] = g->Eval(masspoints[j]); 
  }
  
  return acceptance;
}






TGraph* getObservedLimit(string ModelName,string decayMode,float width, bool dependsOnKtilde)
{
    TGraph* limit;
     std::stringstream s;
    if(int(width*100+0.5) == 10 or int(100*width+0.5)==20 or int(width*100+0.5)==30 or int(width*100) == 0)
      {
	s << std::fixed << std::setprecision(1) << width;
      }
      else
      {
	s << std::fixed << std::setprecision(2) << width;
      }
      string swidth = s.str();
    string dir = "/home/dschaefer/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/";
    string filename = "";
    int n=0;
    float startmass=0;
    if(decayMode.find("lvjj")!=string::npos)
    {
      filename = dir+"graphs_em.root";
      n = 37;
      startmass=800;
    }
    else 
    {
      filename = dir+"graphs_had.root";
      n = 28;
      startmass=1200;
    }
  if(dependsOnKtilde)
  {
    float ktilde = width;
    string sktilde = swidth;
    TFile* f = new TFile(filename.c_str(),"READ");
    float* masses = new float[n];
    float* l      = new float[n];
    for(int i=0;i<n;i++)
    {
      masses[i] = startmass +i*100;
      float width = getWidthForKtilde(ModelName,masses[i],ktilde);
      if(width<0.025){swidth = "0.0";}
      if(width>=0.025 and width<0.075){swidth = "0.05";}
      if(width>=0.075 and width<0.125){swidth = "0.1";}
      if(width>=0.125 and width<0.175){swidth = "0.15";}
      if(width>=0.175 and width<0.225){swidth = "0.2";}
      if(width>=0.225 and width<0.275){swidth = "0.25";}
      if(width>=0.275 and width<0.325){swidth = "0.3";}
      if(width>=0.325){swidth = "0.3"; /*std::cout << "width > 0.3 " <<width <<std::endl;*/}
      
     // std::cout << " width  : "<<width <<std::endl;
     // std::cout << masses[i]<<" width of limit taken : " << swidth <<std::endl;
      TGraph* tmp = (TGraph*) f->Get(("OL_"+swidth).c_str());
      l[i] = tmp->Eval(masses[i]);
    }
    limit = new TGraph(n,masses,l);
  }
  else
  {
      TFile* f = new TFile(filename.c_str(),"READ");
      std::cout <<"OL_"+swidth <<std::endl;
      limit = (TGraph*) f->Get(("OL_"+swidth).c_str());
  }
    return limit;
}


TGraph* getLimitUp(string ModelName,string decayMode,float width,int sigma,bool dependsOnKtilde)
{
  TGraph* limit;
    string dir = "/home/dschaefer/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/";
    std::stringstream s;
      if(int(width*100+0.5) == 10 or int(100*width+0.5)==20 or int(width*100+0.5)==30 or int(width*100) == 0)
      {
	s << std::fixed << std::setprecision(1) << width;
      }
      else
      {
	s << std::fixed << std::setprecision(2) << width;
      }
      string swidth = s.str();
      
    string filename = "";
    int n=0;
    float startmass=0;
    if(decayMode.find("lvjj")!=string::npos)
    {
      filename = dir+"graphs_em.root";
      n = 37;
      startmass=800;
    }
    else 
    {
      filename = dir+"graphs_had.root";
      n = 28;
      startmass=1200;
    }
  if(dependsOnKtilde)
  {
    float ktilde = width;
    string sktilde = swidth;
    TFile* f = new TFile(filename.c_str(),"READ");
    float* masses = new float[n];
    float* l      = new float[n];
    for(int i=0;i<n;i++)
    {
      masses[i] = startmass +i*100;
      float width = getWidthForKtilde(ModelName,masses[i],ktilde);
      if(width<0.025){swidth = "0.0";}
      if(width>=0.025 and width<0.075){swidth = "0.05";}
      if(width>=0.075 and width<0.125){swidth = "0.1";}
      if(width>=0.125 and width<0.175){swidth = "0.15";}
      if(width>=0.175 and width<0.225){swidth = "0.2";}
      if(width>=0.225 and width<0.275){swidth = "0.25";}
      if(width>=0.275 and width<0.325){swidth = "0.3";}
      if(width>=0.325){swidth = "0.3"; /*std::cout << "width > 0.3 " <<width <<std::endl;*/}
      
      TGraph* tmp = (TGraph*) f->Get(("UP_"+swidth+"_"+std::to_string(sigma)).c_str());
      l[i] = tmp->Eval(masses[i]);
    }
    limit = new TGraph(n,masses,l);
  }
  else
  {
      TFile* f = new TFile(filename.c_str(),"READ");
      std::cout <<"OL_"+swidth <<std::endl;
      limit = (TGraph*) f->Get(("UP_"+swidth+"_"+std::to_string(sigma)).c_str());
  }
    return limit; 
}


TGraph* getLimitDown(string ModelName,string decayMode,float width, int sigma,bool dependsOnKtilde)
{
    TGraph* limit;
    string dir = "/home/dschaefer/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/";
    std::stringstream s;
      if(int(width*100+0.5) == 10 or int(100*width+0.5)==20 or int(width*100+0.5)==30 or int(width*100) == 0)
      {
	s << std::fixed << std::setprecision(1) << width;
      }
      else
      {
	s << std::fixed << std::setprecision(2) << width;
      }
      string swidth = s.str();
     string filename = "";
    int n=0;
    float startmass=0;
    if(decayMode.find("lvjj")!=string::npos)
    {
      filename = dir+"graphs_em.root";
      n = 37;
      startmass=800;
    }
    else 
    {
      filename = dir+"graphs_had.root";
      n = 28;
      startmass=1200;
    }
  if(dependsOnKtilde)
  {
    float ktilde = width;
    string sktilde = swidth;
    TFile* f = new TFile(filename.c_str(),"READ");
    float* masses = new float[n];
    float* l      = new float[n];
    for(int i=0;i<n;i++)
    {
      masses[i] = startmass +i*100;
      float width = getWidthForKtilde(ModelName,masses[i],ktilde);
      if(width<0.025){swidth = "0.0";}
      if(width>=0.025 and width<0.075){swidth = "0.05";}
      if(width>=0.075 and width<0.125){swidth = "0.1";}
      if(width>=0.125 and width<0.175){swidth = "0.15";}
      if(width>=0.175 and width<0.225){swidth = "0.2";}
      if(width>=0.225 and width<0.275){swidth = "0.25";}
      if(width>=0.275 and width<0.325){swidth = "0.3";}
      if(width>=0.325){swidth = "0.3"; /*std::cout << "width > 0.3 " <<width <<std::endl;*/}
      
      TGraph* tmp = (TGraph*) f->Get(("DOWN_"+swidth+"_"+std::to_string(sigma)).c_str());
      l[i] = tmp->Eval(masses[i]);
    }
    limit = new TGraph(n,masses,l);
  }
  else
  {
      TFile* f = new TFile(filename.c_str(),"READ");
      limit = (TGraph*) f->Get(("DOWN_"+swidth+"_"+std::to_string(sigma)).c_str());
  }  
    return limit;
}