#ifndef WORKONHISTOS2_H
#define WORKONHISTOS2_H


//run with:
//checkFitCBBW(3000,0.1,"el","Wprime",Ymax)
//fits the DCB to the narrow width sameple -> draws convolution width BW into Canvas with MC sample with width >0
//possible models: BulkGrav, Wprime, Zprime, Radion, RSGrav but look out: not all files for all models exist
//Ymax is the maximum for the y-Axis of the convolution plot -> must be set per hand to a value so that the plot looks good
void checkFitCBBW(ofstream &logfile,float mass,float width,string channel, string modelName,string category,string decayMode,double Ymax,bool testGeneratedKinematics=0,bool testKinematicsWithoutSelection=0, bool testMatchedJet=0);

//fits only narrow shapes and writes the fit parameters to file
void checkNarrowFit(float mass,string channel, string modelName,string category,string decayMode);
//take as input a histogram instead of using my files -> this function is for debugging purposes so I can run it with jennifers preselected trees
void checkNarrowFit(float mass,string channel,string modelName ,string category, TH1F* h_narrow);

RooRealVar InterpolateExtraDegreeOfFreedom(string channel,string category,float mass, float GMRatio);

void getShapeFromInterpolation(string Model, string channel,string category,float mass,float GMRatio, RooRealVar rrv_x, RooPlot* frame,int color,string ColorScheme="kRed");
RooAddPdf* narrow_model_allHad_fitted(string category,float mass,float mean_value_for_return_pdf,RooRealVar m_width);

RooFitResult* AllHadFitMeanShift(string modelName,string category,float mass, float width);
RooFitResult* AllHadFitDoF(string modelName,string category,float mass, float width);
#endif