#include "StyleFunc.h"
#include "TH1F.h"
#include "TH2.h"
#include "TStyle.h"
// --------------------------------------------------------------------------------
// -------------------------------------------------------------------------------


void style1D(TH1F *histo, TString nameXaxis, TString nameYaxis, Double_t offset)
{
  histo->GetXaxis()->SetTitle(nameXaxis);
  histo->GetYaxis()->SetTitle(nameYaxis);
  histo->GetXaxis()->SetTitleOffset(offset);
  histo->GetYaxis()->SetTitleOffset(offset);
  histo->GetXaxis()->CenterTitle();
  histo->GetYaxis()->CenterTitle();

}

// --------------------------------------------------------------------------------
// -------------------------------------------------------------------------------

void style2D(TH2* histo, TString nameXaxis, TString nameYaxis,TString nameZaxis, Double_t offsetX, Double_t offsetY, Double_t offsetZ,const char* statopt)
{
  gStyle->SetOptStat(statopt);
  histo->SetTitleOffset(offsetY,"y");
  histo->SetTitleOffset(offsetX,"x");
  histo->SetTitleOffset(offsetZ,"z");
  histo->GetXaxis()->SetTitle(nameXaxis);
  histo->GetYaxis()->SetTitle(nameYaxis);
  histo->GetZaxis()->SetTitle(nameZaxis);
}
