#include "TF1.h"
#include "TGraph.h"
#include "CrossSections2.h"
#include "TCanvas.h"
#include "TPad.h"
#include <cfloat>
#include "TLatex.h"
#include "TAxis.h"



FminusG::FminusG(TF1* function,TGraph* graph)
{
  F_ = function;
  G_ = graph;
  int N = G_->GetN();
  double* x = G_->GetX();
  range_min_ = float(x[0]);
  range_max_ = float(x[N-1]);
}

FminusG::FminusG(TF1* function, TGraph* graph,float range_min, float range_max)
{
 F_ = function;
 G_ = graph;
 range_min_ = range_min;
 range_max_ = range_max;
}

double FminusG::GetV(double x)
{
  if(x > range_max_ or x < range_min_)
  {
   std::cout << " mass value out of range "<<std::endl;   
  }
  double f_x = F_->Eval(x);
  double g_x = G_->Eval(x,0,"S");
  return (f_x - g_x);  
}

void FminusG::Draw(TPad* pad, std::string label)
{
    pad->cd();
    pad->SetLogy();
    TLatex text;
    text.SetTextFont(43);
    text.SetTextSize(16);
    text.SetTextColor(kRed);
    //int N = G_->GetN();
    //double*xg = G_->GetX();
    //float x = xg[N-1]-1000;
    float x =1000;
    float y = 150;
    std::cout <<"TLatex " << x  <<" "<< y <<" "<<label<< std::endl;
    text.DrawLatex(x,y,label.c_str());
    F_->SetLineWidth(2);
    F_->SetLineColor(kRed);
    G_->SetLineWidth(2);
    G_->SetLineColor(kGreen);
    G_->SetMarkerStyle(3);
    //G_->SetMaximum(1000);
    //G_->SetMinimum(0);
    //F_->SetMaximum(1000);
    //F_->SetMinimum(0);
    F_->Draw();
    G_->Draw("CPsame");
}

int FminusG::Sign(double x)
{
   double v = GetV(x);
   if(v<0)
   {
     return -1;
   }
   else
   {
     return 1;
   }
}

double FminusG::GetRoot(double min, double max)
{
   double root;
   double fmin = GetV(min);
   double fmax = GetV(max);
   double a = min;
   double b = max;
   if(fmin*fmax>0)
   {
    std::cout << "given interval must contain exactly one root. abort GetRoot" << std::endl;
    return 0;   
   }
   swap_ab_if(a,b);
   double deltaI = max -min;
   double c = a;
   double s = b;
   double d = 0;
   double fs;
   bool flag =1;
   do 
   {
     if(!AlmostEqual(GetV(a),GetV(c)) and !AlmostEqual(GetV(b),GetV(c)))
     {
      s = inverseQuadratic(a,b,c);   
     }
     else
     {
      s = secant(a,b);
     }
     if(conditionsMet(a,b,c,d,s,flag))
     {
      s = bisection(a,b);
      flag =1;
     }
     else
     {
      flag = 0;   
     }
     fs =GetV(s);
     d = c;
     c = b;
     if(GetV(a)*GetV(s) < 0)
     {
      b = s;   
     }
     else
     {
      a = s;   
     }
     //std::cout << s << std::endl;
     swap_ab_if(a,b);
     deltaI = TMath::Abs(a-b);
   }while(TMath::Abs(deltaI)>0.01 and !AlmostEqual(GetV(b),0.0));
   root =s;
   return root;
}

double FminusG::inverseQuadratic(double a, double b, double c)
{
   double sa = a*GetV(b)*GetV(c)/((GetV(a)-GetV(b))*(GetV(a)-GetV(c)));
   double sb = b*GetV(a)*GetV(c)/((GetV(b)-GetV(a))*(GetV(b)-GetV(c)));
   double sc = c*GetV(a)*GetV(b)/((GetV(c)-GetV(a))*(GetV(c)-GetV(b)));
   double s  = sa + sb + sc;
   return s;
}

bool conditionsMet(double a, double b, double c,double d,double s,bool mflag)
{
   double delta = 0.01;
   double b2 = (3*a+b)/4.;
   double b1 = b;
   order(b1,b2);
   if(s<b1 or s>b2)
   {
       return 1;
   }
   if(mflag and TMath::Abs(s-b) >= TMath::Abs(b-c)/2.)
   {
       return 1;   
   }
   if(!mflag and TMath::Abs(s-b)>=TMath::Abs(c-d)/2.)
   {
       return 1;  
   } 
   if(mflag and TMath::Abs(b-c) < TMath::Abs(delta))
   {
       return 1;   
   }
   if(!mflag and TMath::Abs(c-d) < TMath::Abs(delta))
   {
       return 1;   
   }
   return 0;
}

void order(double &a , double &b)
{
  if(a<b)
  {
    double tmp =a;
    a = b;
    b = tmp;
  }
}

double FminusG::secant(double a , double b)
{
   double s = b - GetV(b)*(b-a)/(GetV(b)-GetV(a));
   return s;
}

double FminusG::bisection(double a, double b)
{
   double s = (a + b)/2.;
   return s;
}

void FminusG::swap_ab_if(double &a, double &b)
{
    double fa = GetV(a);
    double fb = GetV(b);
    order(fa,fb);
}
 
bool hasDifferentSign(int sign1,int sign2)
{
   bool passed =0;
   if(sign1+sign2 ==0)
       passed = 1;
   return passed;
}

bool AlmostEqual(double a, double b)
{
    double MaxDiff = DBL_EPSILON;
    double    diff = fabs(a-b);
    a = fabs(a);
    b = fabs(b);
    double max = (b > a) ? b : a;
    if(diff <= max*MaxDiff)
        return true;
    return false;
}

