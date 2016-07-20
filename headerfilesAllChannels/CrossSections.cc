#include "TGraphAsymmErrors.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
#include "TCanvas.h"
#include "TPad.h"
#include "TEfficiency.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLatex.h"
#include <sstream>
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
#include "/usr/users/dschaefer/root/headerfilesAllChannels/CrossSections.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/CrossSections2.h"
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"




void printWidthForKtilde(string ModelName,float ktilde, float massmax, float massmin)
{
  std::cout << ktilde << " : "<<std::endl;
  for(int i=0;i<(massmax-massmin)/100;i++)
  {
  std::cout << massmin+i*100 << " : "<< getWidthForKtilde(ModelName,massmin+i*100,ktilde) << std::endl;
  }
    
}


TGraph* findAllExcludedPoints(std::string ModelName,std::string decayMode,std::map<float,float> mass_acceptance,float ktilde)
{
  TGraph* g;
  float massmin = 800;
  float massmax  = 4500;
  int points = mass_acceptance.size();
  std::cout << points << std::endl;
  float* mass_tmp = new float[points];
  float* acc_tmp  = new float[points];
  vector<float> excludedPoints_w;
  vector<float> excludedPoints_m;
  
  
  
  int n = (massmax-massmin)/100;
  float* k = new float[n];
  float* acc = new float[n];
  int t=0;
  for(int i=0;i<=n;i++)
  {
    k[i] = getKtilde("RSGrav",massmin+i*100,0.3);
    //std::cout <<massmin+i*100 << " "<< k[i] << std::endl;
    if(mass_acceptance.find(massmin+i*100)!=mass_acceptance.end())
    {
        mass_tmp[t] = massmin+i*100;
        acc_tmp[t]  = mass_acceptance.find(massmin+i*100)->second;
        std::cout<< mass_tmp[t] << std::endl;
        t++;
    }
  }

  if(decayMode.find("jjjj")!=string::npos)
  {
   massmin  = 1200;
   massmax = 4500;
  }
  
    //TCanvas* tmp = new TCanvas("tmp","tmp",400,400);
    //tmp->SetLogy();
    //TGraph* x = new TGraph(10,mass_tmp,acc_tmp);
    //x->Draw("AL");
  for(int i=n-1;i>=0;i--)
  {
    float* xs_new     = getTheoryCrossSection(ModelName,k[i]);
    std::cout <<"ktilde " << k[i] << std::endl;
    float* N_expected = getNumberOfExpectedEvents(xs_new,mass_tmp,acc_tmp,ModelName,decayMode);
    
    TGraph* Nexp = new TGraph(points,mass_tmp,N_expected);
    TGraph* obsl = getObservedLimit(ModelName,decayMode,k[i],1);
    
    TGraph* x = new TGraph(points,mass_tmp,xs_new);
//     if(i==n-1)
//     {
//      Nexp->Draw("AL"); 
//     //x->Draw("AL");
//     }
//     Nexp->Draw("same");
    //x->Draw("same");
    
    for(int ii=0;ii<=i+1;ii++)
    {
     float mWW = massmin+ii*100;
     //std::cout << "masspoints "  << mWW << std::endl;
     float diff = obsl->Eval(mWW) - Nexp->Eval(mWW);
     //std::cout << obsl->Eval(mWW) << " " << Nexp->Eval(mWW)<<std::endl;
     //std::cout << diff << std::endl;
     if(diff<0)
     {
        excludedPoints_m.push_back(mWW);
        float w = getWidthForKtilde(ModelName,mWW,k[i]);
        excludedPoints_w.push_back(w);
     }
        
    }
  }
  int points_excl = excludedPoints_m.size();
  float* p_excludedPoints_m = new float[points_excl];
  float* p_excludedPoints_w = new float[points_excl];
  for(int b=0;b< excludedPoints_m.size();b++)
  {
      p_excludedPoints_m[b] = excludedPoints_m.at(b);
      p_excludedPoints_w[b] = excludedPoints_w.at(b);
  }
  
  g = new TGraph(points_excl,p_excludedPoints_m,p_excludedPoints_w);
  
  return g;
}


// TGraph* findAllExcludedPointsBelow(std::string ModelName,std::string decayMode,std::map<float,float> mass_acceptance,float ktilde)
// {
//     
//     
// }



TGraph* getExcludedPoints(string ModelName,string decayMode,TGraph* observedlimit,TGraph* expectedEventNumbers,float ktilde)
{
  float massmin=1200;
  float massmax=4000;
  vector<float> yv;
  vector<float> xv;
  int b=0;
   if(decayMode.find("lvjj")!=string::npos)
   {
     massmin = 800;
     massmax = 4500;
   }
   
  for(int i=0;i<(massmax-massmin)/100;i++)
  {
   float widths  = getWidthForKtilde(ModelName,massmin+100*i,ktilde);
   //std::cout << "mass : "<< massmin+100*i << " width : "<<widths <<std::endl;
   //std::cout << " obs lim : " <<observedlimit->Eval(massmin+100*i) << " expected number of events : "<< expectedEventNumbers->Eval(massmin+100*i) <<std::endl;
   if(observedlimit->Eval(massmin+100*i) > expectedEventNumbers->Eval(massmin+100*i))
    continue;
   yv.push_back(widths);
   xv.push_back(massmin+100*i);
   b++;
  }
  float * x = new float[xv.size()+3];
  float * y = new float[yv.size()+3];
  for(int i=0;i<xv.size();i++)
  {
    x[i] = xv.at(i);
  }
  for(int i=0;i<yv.size();i++)
  {
    y[i] = yv.at(i);
  }
  y[yv.size()] = 0.325;
  x[xv.size()] = x[xv.size()-1];
  y[yv.size()+1] = 0.325;
  x[xv.size()+1] = massmin;
  x[xv.size()+2] = x[0];
  y[yv.size()+2] = y[0];
  TGraph *p = new TGraph(b,x,y);
  return p;
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
  
  natural_width = g->Eval(mass,0,"S")/mass*pow(ktilde,2)/pow(0.1,2);
  //std::cout << mass << " " << natural_width << std::endl;
  return natural_width; 
  
}

float  getKtilde(string ModelName,float mass, float natural_width)
{
  float result =0;
  float gamma[10];
  int index =-1;
  float* masses = new float[10];
  masses[0] = 800;
  masses[1] = 900;
  masses[2] =1000;
  masses[3] =1500;
  masses[4] =1800;
  masses[5] =2000;
  masses[6] =2500;
  masses[7] =3000;
  masses[8] =3500;
  masses[9] =4500;
  
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
  float gammaX = g->Eval(mass);
  result = TMath::Sqrt(natural_width*mass/gammaX)*0.1;
  return result; 
}


float* getTheoryCrossSection(string ModelName)
{
  float* xs = new float[10];
  float ktilde = 0.1;
  
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




vector<float> getMassesForKtilde(string decayMode, float ktilde)
{
    vector<float> masses;
    if(decayMode.find("lvjj")!=string::npos)
    {
        std::cout << "lvjj" << std::endl;
        
          if(TMath::Abs(ktilde- 0.07)<0.005)
     {
         masses.push_back(800);
         masses.push_back(1200);
         masses.push_back(1500);
         masses.push_back(2000);
         masses.push_back(2500);
         masses.push_back(3000);
         masses.push_back(3500);
         masses.push_back(4000);
         masses.push_back(4500);
     }
        if(TMath::Abs(ktilde- 0.15)<0.005)
     {
         masses.push_back(800);
         masses.push_back(1200);
         masses.push_back(1500);
         masses.push_back(2000);
         masses.push_back(2500);
         masses.push_back(3000);
     }
     if(TMath::Abs(ktilde- 0.095)<0.005)
     {
         std::cout << "ktilde = 0.095 " << std::endl;
         masses.push_back(800);
         masses.push_back(900);
         masses.push_back(1000);
         masses.push_back(1500);
         masses.push_back(1800);
         masses.push_back(2000);
         masses.push_back(2500);
         masses.push_back(3000);
         masses.push_back(3500);
         masses.push_back(4500);
     }
     if(TMath::Abs(ktilde-0.05)<0.001)
     {   
         masses.push_back(800);
         masses.push_back(1200);
         masses.push_back(1500);
         masses.push_back(2000);
         masses.push_back(3000);
         masses.push_back(3500);
         masses.push_back(4000);
         //masses.push_back(4500);
     }
     if(TMath::Abs(ktilde-0.03)<0.001)
     {
         masses.push_back(800);
         masses.push_back(1200);
         masses.push_back(1500);
         masses.push_back(2000);
         masses.push_back(3000);
         masses.push_back(3500);
         masses.push_back(4000); 
         masses.push_back(4500);
     }
     if(TMath::Abs(ktilde-0.12)<0.001)
     {
         masses.push_back(800);
         masses.push_back(1200);
         masses.push_back(1500);
         masses.push_back(2000);
         masses.push_back(3000);
         masses.push_back(3500); 
     }
     if(TMath::Abs(ktilde-0.2)<0.001)
     {
         masses.push_back(800);
         masses.push_back(1200);
         masses.push_back(1500);
         masses.push_back(2000);
     }
     if(TMath::Abs(ktilde-0.3)<0.001)
     {
         masses.push_back(800);
         masses.push_back(1200);
         masses.push_back(1500);
     }
     if(TMath::Abs(ktilde-0.4)<0.001)
     {
         masses.push_back(800);
         masses.push_back(1200);
     }
    }
    return masses;
}
 
 
 
vector<float> getProducedWitdhForKtilde(string decayMode, float ktilde)
{
    vector<float> masses;
    if(decayMode.find("lvjj")!=string::npos)
    {
       
     if(TMath::Abs(ktilde- 0.07)<0.005)
     {
         masses.push_back(0.009);
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.05);
         masses.push_back(0.07);
         masses.push_back(0.10);
         masses.push_back(0.13);
         masses.push_back(0.16);
     }
     if(TMath::Abs(ktilde- 0.15)<0.005)
     {
         masses.push_back(0.02);
         masses.push_back(0.05);
         masses.push_back(0.08);
         masses.push_back(0.15);
         masses.push_back(0.23);
         masses.push_back(0.34);
     }
     if(TMath::Abs(ktilde- 0.095)<0.001)
     {
         masses.push_back(0.009);
         masses.push_back(0.012);
         masses.push_back(0.015);
         masses.push_back(0.034);
         masses.push_back(0.048);
         masses.push_back(0.060);
         masses.push_back(0.093);
         masses.push_back(0.135);
         masses.push_back(0.183);
         masses.push_back(0.303);
     }
     if(TMath::Abs(ktilde - 0.05)<0.001)
     {   
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.05);
         masses.push_back(0.07);
         //masses.push_back(0.08);
     }
     if(TMath::Abs(ktilde -0.03)<0.001)
     {
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.02);
         
    }                           
     if(TMath::Abs(ktilde-0.12)<0.001)
     {
         masses.push_back(0.02);
         masses.push_back(0.02);
         masses.push_back(0.05);
         masses.push_back(0.1);
         masses.push_back(0.21);
         masses.push_back(0.29); 
     }
     if(TMath::Abs(ktilde-0.2)<0.001)
     {
         masses.push_back(0.02);
         masses.push_back(0.12);
         masses.push_back(0.15);
         masses.push_back(0.26);
     }
     if(TMath::Abs(ktilde-0.3)<0.001)
     {
         masses.push_back(0.09);
         masses.push_back(0.24);
         masses.push_back(0.34);
     }
     if(TMath::Abs(ktilde-0.4)<0.001)
     {
         masses.push_back(0.09);
         masses.push_back(0.12);
     }
    }
    return masses;
}




float* getAcceptance(string decayMode,float ktilde)
{
    vector<float> masses =  getMassesForKtilde(decayMode,ktilde);
    vector<float> rel_width  =  getProducedWitdhForKtilde(decayMode, ktilde);
   
   int points = masses.size();
   std::cout << "points = " << points << std::endl;
   float* acceptance = new float[points];
   
   std::string dir = "/storage/jbod/dschaefer/";
   std::string filename;
   for(int i=0;i<points;i++)
   {
    float numerator=0;
    float denominator=0;
    std::stringstream s;
    if(TMath::Abs(ktilde- 0.095)<0.001)
    {
     s << std::fixed << std::setprecision(3) << rel_width[i];
    }
    else
    {
    s << std::fixed << std::setprecision(2) << rel_width[i];
    }
    std::string Swidth = s.str();
    //std::cout << Swidth << std::endl;
    if(decayMode.find("lvjj")!=std::string::npos)
    {
     filename = "RSGrav_WW_WlepWhad_width"+Swidth+"_M"+std::to_string(int(masses[i]))+".root";
     //std::cout << filename <<std::endl;
    }
    else
    {
     filename = "RSGrav_WW_WhadWhad_width"+Swidth+"_M"+std::to_string(int(masses[i]))+".root"; 
     //std::cout << filename <<std::endl;
    }
    TFile* f = new TFile((dir+filename).c_str(),"READ");
    TTree* tree = (TTree*) f->Get("tree");
    float eventWeight;
    bool passedAcceptence;
    float w_tauBR;
    tree->SetBranchAddress("eventWeight",&eventWeight);
    tree->SetBranchAddress("passedAcceptence",&passedAcceptence);
    if(decayMode.find("jjjj")!=std::string::npos)
    {
    for(int l=0;l<tree->GetEntries();l++)
    {
      tree->GetEntry(l);
      if(passedAcceptence)
      {
	numerator += eventWeight;
      }
    }
    denominator = tree->GetEntries(); 
    }
    else
    {
    tree->SetBranchAddress("w_tauBR",&w_tauBR);
     for(int l=0;l<tree->GetEntries();l++)
    {
      tree->GetEntry(l);
      if(passedAcceptence)
      {
	numerator += eventWeight*w_tauBR;
      }
    }   
     int leptonID;
     tree->SetBranchAddress("leptonID",&leptonID);
     for(int l=0;l<tree->GetEntries();l++)
     {
       tree->GetEntry(l);
       denominator+=1;
     }
    }
    //std::cout << denominator <<std::endl;
    if(denominator!=0)
    {
    acceptance[i] = numerator/denominator;
    }
    else
    {
     acceptance[i] = 0; 
    }
    //std::cout << " a " << acceptance[i]<<std::endl; 	
   }
  return acceptance;
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
  
  //TCanvas* c1 = new TCanvas("c1","c1",400,400);
  //c1->Divide(2,1);
  //c1->cd(1);
  //g->Draw("AL");
  
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
      //std::cout <<"OL_"+swidth <<std::endl;
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
      //std::cout <<"OL_"+swidth <<std::endl;
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

float* getNumberOfExpectedEvents(float* xs, float* m_xs, float* acceptance, string ModelName,string decayMode)
{
  float BR_W_to_lv = 0.327;
  float BR_W_to_jj = 0.674;
  float BR_Z_to_jj = 0.6991;
  float *BR_G_to_WW = new float[10];
  float* BR_G_to_ZZ = new float[10];
  float lumi = 2.10*1000;  //pb^-1
  if(decayMode.find("jjjj")!=string::npos){lumi = 2.6*1000;}//pb^-1
 float* N_expected = new float[10];
 for(int j =0;j<10;j++)
  {
    //std::cout << " acceptance " <<acceptance[j] <<std::endl;
    BR_G_to_WW[j] = getBranchingRatioToWW(ModelName,m_xs[j]);
    BR_G_to_ZZ[j] = getBranchingRatioToZZ(ModelName,m_xs[j]);
    if(decayMode.find("lvjj")!=string::npos)
    {
      N_expected[j] = acceptance[j]*xs[j]*lumi*BR_G_to_WW[j]*2*BR_W_to_jj*BR_W_to_lv;
    }
    if(decayMode.find("jjjj")!=string::npos)
    {
      N_expected[j] = acceptance[j]*xs[j]*lumi*2*(BR_G_to_WW[j]*BR_W_to_jj*BR_W_to_jj + BR_G_to_ZZ[j]*BR_Z_to_jj*BR_Z_to_jj);
    }
  } 
  return N_expected;
}


TGraph* getNumberOfExpectedEvents(TGraph* g_xs, TGraph* g_acc,string ModelName,string decayMode,TGraph* g_acc_toZZ)
{
  float BR_W_to_lv = 0.327;
  float BR_W_to_jj = 0.674;
  float BR_Z_to_jj = 0.6991;
  float *BR_G_to_WW = new float[10];
  float* BR_G_to_ZZ = new float[10];
  float lumi = 2.10*1000;  //pb^-1
  float massmin = 800;
  float massmax = 4500;
  if(decayMode.find("jjjj")!=string::npos){lumi = 2.6*1000; massmin = 1200; massmax = 4000;}//pb^-1
  int n = (massmax-massmin)/100;
  float m_xs[10] ={800,900,1000,1500,1800,2000,2500,3000,3500,4500};
  int N = g_acc->GetN();
  //std::cout << N << std::endl;
  double* x_values = g_acc->GetX(); 
 float* N_expected = new float[N];
 float* masses     = new float[N];
 for(int j =0;j<10;j++)
  {
    //std::cout << " acceptance " <<acceptance[j] <<std::endl;
    BR_G_to_WW[j] = getBranchingRatioToWW(ModelName,m_xs[j]);
    BR_G_to_ZZ[j] = getBranchingRatioToZZ(ModelName,m_xs[j]);
  }
  TGraph* g_BR_G_to_WW = new TGraph(10,m_xs,BR_G_to_WW);
  TGraph* g_BR_G_to_ZZ = new TGraph(10,m_xs,BR_G_to_ZZ);
 
 
  for(int i=0;i<=n;i++)
  {
    float m  = massmin+i*100;
    for(int l=0;l<N;l++)
    {
        //std::cout << m <<" "<<x_values[l] << std::endl;
        if(TMath::Abs(m-x_values[l])<0.001)
        {
        masses[l] = m;
        //std::cout << " a  "<<l << " "<< m <<  " ";
            if(decayMode.find("lvjj")!=string::npos)
            {
            N_expected[l] = g_acc->Eval(m,0,"S")*g_xs->Eval(m,0,"S")*lumi*g_BR_G_to_WW->Eval(m,0,"S")*2*BR_W_to_jj*BR_W_to_lv;
            std::cout <<" Nexp : "<< N_expected[l] << " xs : " <<g_xs->Eval(m,0,"S") << " acc : "<<g_acc->Eval(m,0,"S")<< " BR To WW : "<<g_BR_G_to_WW->Eval(m,0,"S") << std::endl;
            }
            if(decayMode.find("jjjj")!=string::npos)
            {
                if(g_acc_toZZ==0)
                {
                N_expected[l] = g_acc->Eval(m,0,"S")*g_xs->Eval(m,0,"S")*lumi*2*(g_BR_G_to_WW->Eval(m,0,"S")*BR_W_to_jj*BR_W_to_jj) ;
                }
                else
                {
          // acceptance for G->ZZ different but not yet produced
                N_expected[l] = g_xs->Eval(m,0,"S")*lumi*2*(g_acc->Eval(m,0,"S")*g_BR_G_to_WW->Eval(m,0,"S")*BR_W_to_jj*BR_W_to_jj + g_acc_toZZ->Eval(m)*g_BR_G_to_ZZ->Eval(m,0,"S")*BR_Z_to_jj*BR_Z_to_jj);
                }
            }
        }
    }
  } 
  TGraph* result = new TGraph(N,masses,N_expected);  
  return result;
}



TGraph* getNumberOfExpectedEvents(TF1* g_xs, TGraph* g_acc,string ModelName,string decayMode,TGraph* g_acc_toZZ)
{
  float BR_W_to_lv = 0.327;
  float BR_W_to_jj = 0.674;
  float BR_Z_to_jj = 0.6991;
  float *BR_G_to_WW = new float[10];
  float* BR_G_to_ZZ = new float[10];
  float lumi = 2.10*1000;  //pb^-1
  float massmin = 800;
  float massmax = 4500;
  if(decayMode.find("jjjj")!=string::npos){lumi = 2.6*1000; massmin = 1200; massmax = 4000;}//pb^-1
  int n = (massmax-massmin)/100;
  float m_xs[10] ={800,900,1000,1500,1800,2000,2500,3000,3500,4500};
  int N = g_acc->GetN();
  //std::cout << N << std::endl;
  double* x_values = g_acc->GetX(); 
 float* N_expected = new float[N];
 float* masses     = new float[N];
 for(int j =0;j<10;j++)
  {
    //std::cout << " acceptance " <<acceptance[j] <<std::endl;
    BR_G_to_WW[j] = getBranchingRatioToWW(ModelName,m_xs[j]);
    BR_G_to_ZZ[j] = getBranchingRatioToZZ(ModelName,m_xs[j]);
  }
  TGraph* g_BR_G_to_WW = new TGraph(10,m_xs,BR_G_to_WW);
  TGraph* g_BR_G_to_ZZ = new TGraph(10,m_xs,BR_G_to_ZZ);
 
 
  for(int i=0;i<=n;i++)
  {
    float m  = massmin+i*100;
    for(int l=0;l<N;l++)
    {
        //std::cout << m <<" "<<x_values[l] << std::endl;
        if(TMath::Abs(m-x_values[l])<0.001)
        {
        masses[l] = m;
        //std::cout << " a  "<<l << " "<< m <<  " ";
            if(decayMode.find("lvjj")!=string::npos)
            {
            N_expected[l] = g_acc->Eval(m,0,"S")*g_xs->Eval(m)*lumi*g_BR_G_to_WW->Eval(m,0,"S")*2*BR_W_to_jj*BR_W_to_lv;
            std::cout <<" Nexp : "<< N_expected[l] << " xs : " <<g_xs->Eval(m) << " acc : "<<g_acc->Eval(m,0,"S")<< " BR To WW : "<<g_BR_G_to_WW->Eval(m,0,"S") << std::endl;
            }
            if(decayMode.find("jjjj")!=string::npos)
            {
                if(g_acc_toZZ==0)
                {
                N_expected[l] = g_acc->Eval(m,0,"S")*g_xs->Eval(m)*lumi*2*(g_BR_G_to_WW->Eval(m,0,"S")*BR_W_to_jj*BR_W_to_jj) ;
                }
                else
                {
          // acceptance for G->ZZ different but not yet produced
                N_expected[l] = g_xs->Eval(m)*lumi*2*(g_acc->Eval(m,0,"S")*g_BR_G_to_WW->Eval(m,0,"S")*BR_W_to_jj*BR_W_to_jj + g_acc_toZZ->Eval(m)*g_BR_G_to_ZZ->Eval(m,0,"S")*BR_Z_to_jj*BR_Z_to_jj);
                }
            }
        }
    }
  } 
  TGraph* result = new TGraph(N,masses,N_expected);  
  return result;
}



TGraph* getLimitOnNexpected(std::string decayMode,TGraph* g_iso_ktilde)
{
    string channel = "had";
  if(decayMode.find("lvjj")!=std::string::npos)
  {
   channel = "em"; 
  }
  
  TFile* file = new TFile(("/home/dschaefer/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/graphs_"+channel+".root").c_str(),"READ");
  string histoname = "ExclusionLimitOnEventNumber_BulkG_WW_em_HP";
  if(channel.find("had")!=std::string::npos)
  {
   histoname =  "ExclusionLimitOnEventNumber_BulkWW_had_HP";
  }
  TH2F* obsLim = dynamic_cast<TH2F*>(file->Get(histoname.c_str()));
  
  int N = g_iso_ktilde->GetN();
  double* x = g_iso_ktilde->GetX();
  double* y = g_iso_ktilde->GetY();
  double* result_y = new double[N];
  
  for(int i=0;i<N;i++)
  {
   int bin = obsLim->FindBin(x[i],y[i]);
   result_y[i] = obsLim->GetBinContent(bin);   
  }
  TGraph* result = new TGraph(N-1,x,result_y);
  return result;
}

void    SetGraphStyle(TGraph* g , std::string title,float x, float y)
{
 g->SetLineWidth(2);
 g->SetLineColor(kWhite);
 TLatex text;
 text.SetTextFont(43);
 text.SetTextSize(16);
 text.SetTextColor(kWhite);
 text.DrawLatex(x,y,title.c_str());
    
}

float findMassMaxForKtilde(std::string ModelName,std::string decayMode,float ktilde)
{
  float massmin=1200;
  float massmax=4000;
  if(decayMode.find("lvjj")!=std::string::npos)
  {
    massmin = 800;
    massmax = 4500;
  }
  int n = (massmax-massmin)/100;
  float result = massmax;
  for(int i=0;i<n+1;i++)
  {
    float mass = massmin+i*100;
    if(getWidthForKtilde(ModelName,mass,ktilde) > 0.325)
    {
      result = mass;
      break;
    }
  }
 return result;   
}

TGraph* IsoKtilde(std::string ModelName,std::string decayMode,float ktilde)
{
    float massmin=1200;
  if(decayMode.find("lvjj")!=std::string::npos)
  {
    massmin = 800;
  }
  float massmax = findMassMaxForKtilde(ModelName,decayMode,ktilde);
  int n = (massmax-massmin)/100;
  
  
  
  
  float m_xs[10]  =  {800,900,1000,1500,1800,2000,2500,3000,3500,4500};
  float* masses = new float[n+2];
  float* gamma  = new float[n+2];
  for(int i=0;i<=n;i++)
  {
   float m = massmin+i*100;
//    for(int l=0;l<10;l++)
//    {
    masses[i] = m;
    gamma[i]  = getWidthForKtilde(ModelName,m,ktilde);
//    }
  }
   masses[n+1] = massmax+50;
   gamma[n+1]  =getWidthForKtilde(ModelName,massmax+50,ktilde);
  
  TGraph* g = new TGraph(n+2,masses,gamma);
return g;    
}

float* getLog(float* list, int length)
{
    float* result = new float[length];
    for(int i=0;i<length;i++)
    {
        
     result[i] = TMath::Log(list[i]);   
    }
 return result;   
}

double* getLog(double* list, int length)
{
    double* result = new double[length];
    for(int i=0;i<length;i++)
    {
     std::cout <<  list[i] <<  " "<< TMath::Log(list[i]) << std::endl;
     if(!AlmostEqual(list[i],0.0) and list[i]>0.0)
     {
     result[i] = TMath::Log(list[i]);
     }
     else
     {
      result[i] = 0.0;   
     }
    }
 return result;   
}

TF1* getFitFunction(TGraph* N_expected)
{
   int N = N_expected->GetN();
   double* x = N_expected->GetX();
   double* y = N_expected->GetY();
   double massmin = x[0];
   double massmax = x[N-1];
   
   double* logY = getLog(y,N);
   
   TGraph* log = new TGraph(N,x,logY);
   TF1* f1 = new TF1("f1","[0]*x+[1]+[2]*x*x",massmin,massmax);
   //f1->SetParLimits(1,500,10000);
  f1->SetLineColor(kGreen);
  log->SetLineColor(kBlue);
  log->SetLineWidth(3);
  //TCanvas* tm = new TCanvas("tm","tm",400,400);
  log->Fit(f1);
  //log->Draw();
  //f1->Draw("same");
  //tmp2->SetLogy();
  TF1* exp2 = new TF1("exp2","exp(f1)",massmin,massmax);
  //exp2->SetLineColor(kBlue);
  //N_expected->Draw("AL");
  //exp2->Draw("same");
    
  return exp2;  
}

TF1* fitCrossSection(string ModelName)
{
  float m_xs[10]  =  {800,900,1000,1500,1800,2000,2500,3000,3500,4500};
  float* xs = getTheoryCrossSection(ModelName);
  float errors[10] = {float(0.22*xs[0]),float(0.23*xs[1]),float(0.25*xs[2]),float(0.32*xs[3]),float(0.36*xs[4]),float(0.39*xs[5]),float(0.46*xs[6]),float(0.53*xs[7]),float(0.63*xs[8]),float(1.02*xs[9])};
  float errors_x[10] = {0,0,0,0,0,0,0,0,0,0};
  
  TGraphErrors* g_xs = new TGraphErrors(10,m_xs,xs,errors_x,errors);
  
  
  
  
  
  TF1* exp = new TF1("exp","[0]*exp([1]*x)",800,4500);
  
  std::cout << exp->Eval(3500)<< " "<<g_xs->Eval(3500) << std::endl;
  std::cout << exp->Eval(4000)<< " "<<g_xs->Eval(4000) << std::endl;
  
  float* logXS = getLog(xs,10);
  float errors_log[10] = {float(0.22*logXS[0]),float(0.23*logXS[1]),float(0.25*logXS[2]),float(0.32*logXS[3]),float(0.36*logXS[4]),float(0.39*logXS[5]),float(0.46*logXS[6]),float(0.53*logXS[7]),float(0.63*logXS[8]),float(1.02*logXS[9])};
  //TGraphErrors* g_xs_log = new TGraphErrors(10,m_xs,logXS,errors_x,errors_log);
  TGraph* g_xs_log = new TGraph(10,m_xs,logXS);
  
  TF1* f1 = new TF1("f1","[0]*x+[1]+[2]*x*x",800,4500);
   g_xs_log->Fit(f1);
   g_xs->Fit(exp);
   
  TF1* exp2 = new TF1("exp2","exp(f1)",800,4500);
  //TCanvas* tmp = new TCanvas("tmp","tmp",400,400);
  //tmp->SetLogy();
  //g_xs->Draw("AL");
  //exp->Draw("same");
  //tmp->cd();
  //exp2->SetLineColor(kBlue);
  //exp2->Draw("same");
  return exp2;
}

TF1* getTheoryCrossSectionFitted(string ModelName,float ktilde)
{
  TF1* xs = fitCrossSection(ModelName);
  double p0 = xs->GetParameter(0);
  double p1 = xs->GetParameter(1);
  double p2 = xs->GetParameter(2);
  double p0err = xs->GetParError(0);
  double p1err = xs->GetParError(1);
  double p2err = xs->GetParError(2);
  std::cout << p0 << " "<< p1 <<" "<<p2 << std::endl;
  TF1* rew_xs = new TF1("rew_xs","exp([0]*x+[1]+[2]*x*x)*[3]",xs->GetXmin(),xs->GetXmax());
  rew_xs->SetParameter(0,p0);
  rew_xs->SetParameter(1,p1);
  rew_xs->SetParameter(2,p2);
  rew_xs->SetParameter(3,(pow(ktilde,2)/(pow(0.1,2))));
  
  rew_xs->SetParError(0,p0err);
  rew_xs->SetParError(1,p1err);
  rew_xs->SetParError(2,p2err);
  //TF1* rew_xs  = new TF1("xs","xs*[0]*[0]/(0.1*0.1)",xs->GetXmin(),xs->GetXmax());
  //rew_xs->SetParameter(0,ktilde);
    
  return rew_xs; 
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

