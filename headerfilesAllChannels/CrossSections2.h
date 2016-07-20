#ifndef CROSSSECTION2_H
#define CROSSSECTION2_H

#include "TPad.h"

class FminusG 
{
private:
    TF1* F_;
    TGraph* G_;
    float range_min_;
    float range_max_;
    string label_;
public:
    FminusG(TF1* function,TGraph* graph);
    FminusG(TF1* function,TGraph* graph,float range_min,float range_max);
    //float GetV(float x);
    double GetV(double x);
    void Draw(TPad* pad,std::string label= " ");
    int Sign(double x);
    double GetRoot(double min, double max);
protected:
    double inverseQuadratic(double a, double b, double c);
    double secant(double a , double b);
    double bisection(double a, double b);
    void   swap_ab_if(double &a, double &b);
};



bool hasDifferentSign(int sign1,int sign2);
bool conditionsMet(double a, double b, double c,double d,double s,bool mflag);
void order(double &a , double &b);
bool AlmostEqual(double a, double b);

#endif
