#ifndef WORKONHISTOS_H
#define WORKONHISTOS_H

//does not print the overflow and underflow bins!
void PrintBinContents(TH2* histo, vector<double> BinsX, vector<double> BinsY,const char* title ="title", bool printErrors =0);

void PrintBinContentsMinus1(TH2* histo, vector<double> BinsX,vector<double> BinsY,const char* title ="title",bool isPrecisionSet=1);

//return the bin number in [0] the value of the bin in [1]
vector<vector<double> > MakeListOfWeights(TH2* histo, int nBinsX, int nBinsY);

//return in [0] the min pT, in [1] pT max, in [2] eta min, in [3] eta max
// in [4] the value of the bin that is define through the boundaries above
vector<vector<double> > MakeListOfWeights(TH2* histo, vector<double> BinsX, vector<double> BinsY);


void PrintRatioWithWeights(TH2* passedHisto, TH2* reweightHisto, vector<vector<double> > weights , vector<double> BinsX, vector<double> BinsY,const char* title, bool isPrecisionSet=1);

//multiplies the contents of the in weigths[0] specified bins
//with weights[1]
void ReweightHistogram(TH2* histo, vector<vector<double> > weights,bool doNorm =0);

double GetMaxValue(TH1* histo,int nBins);


//make ratio of each bin in histo
TH2* GetRatioHisto(TH2* histo1, TH2* histo2,int nBinsX, int nBinsY);

//prints the following tables derived from the input histograms:
//Efficiencies (_rec/_genWithVeto)
//Entries (_2TeV)
//Entries (_rec_2TeV)
// (_2TeV* Efficiencies/_rec_2TeV)
// (_2TeV* Efficiencies/_rec_2TeV)-1 exept when Entry = 0 then prints 0
//
//returns the Histogram: _2TeV*Efficiencies/_rec_2TeV for each Bin
//displays the Efficiencies on Canvas
//needs:
//all histo pointer, a pointer to a canvas and the Binning of the Histograms (for printing the tables)
//nBinsX/Y are the overall number of Bins in X/Y axis
//pdgId for the captions
TH2F* GenerateAllTables(TH2F* hWEl_rec,TH2F* hWEl_genWithVeto,TH2F* hWEl_2TeV, TH2F* hWEl_rec_2TeV,int pdgId,int nBinsX, int nBinsY, vector<double> BinsX, vector<double> BinsY,TCanvas* c1);

//returns in [0] the number of Bins and in [1]  the sum over all  bins that are filled
vector<double> SumOverAllFilledBins(TH2* histo,int nBinsX,int nBinsY);

//returns pointer to hEff
//displays the efficiency on TCanvas
TH2* GetEfficiencies(TH2* passedHisto, TH2* Histo, TCanvas* c1);
TH2* GetEfficiencies(TH2* passedHisto, TH2* Histo, TCanvas* c1,const char* zAxistitle);
TH2* GetEfficiencies(TH2* passedHisto, TH2* Histo, TCanvas* c1, float max);
TH2* GetEfficiencies(TH2* passedHisto, TH2* Histo);
TH2* GetEfficienciesWithError(TH2* passedHisto, TH2* Histo,int nBinsX,int  nBinsY);
void SetBinsWithContentSmaller10EntriesToZero(TH2* passedHisto);


//return the ratio of (sum over all filled Bins histo1)/(sum over all filled bins histo2)
double GetRatio(TH2* histo1, TH2* histo2,int nBinsX, int nBinsY);


void SetStyleEffPlots(TH2* histo,TPad* c1,const char* title, const char* channel,const char * additional_channel= " ",int xPosition = 2000);
void SetStyleEffPlots(TH2* histo,TPad* c1,const char* title, const char* channel,const char * additional_channel,int xPosition, const char* zAxisTitle);
void SetStyleEffPlotsAllHad(TH2* histo,TPad* c1,const char* title, const char* channel,int xPosition = 2000);
#endif