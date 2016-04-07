#ifndef STYLEFUNC_H
#define STYLEFUNC_H

#include "TH1F.h"
#include "TH2.h"

// set Axis Titles and offset for TH1F histo
void style1D(TH1F* histo, TString nameXaxis, TString nameYaxis, Double_t  offset=1.2);

void style2D(TH2* histo, TString nameXaxis, TString nameYaxis,TString nameZaxis ,Double_t offsetX=1.2, Double_t offsetY=1.4,Double_t offsetZ=1.4 ,const char* statopt="ne");
#endif
