#ifndef GENERAL_H
#define GENERAL_H


//this function gives the correct filename for the EXOVV analysis (WV with W leptonic)
//modelName: BulkGrav,RSGrav,Wprime, Zprime,Radion
//directory: at the moment storage in which the files are stored is /storage/a/mmozer/Res_Sig/
// channel: el,mu
//width: 0.0,0.1,0.2,0.3
//mass: depends on model which masses are available to which width
//number:1,2,3 ->sometimes trees get truncated in three files,or two depending on magic things happening while writing them
string getFileName(string directory, string ModelName,float mass,float width, int number=1, bool isInJbod=0);


//function fills a histogram with a fraction of events that are in hSignal
//and returns that histogram
TH1F* fillHistoWithFractionOfSignalEvents(float fraction,TH1* hSignal,int nBins);


//if one creates a histogram from a TEfficiency object with CreateHistogram the errors are not proberly handled
//this function is the attempt to take care of that wrong error handling
//problem: since TH2 has only one Error internaly stored, max(ErrorUp,ErrorLow) of the TEfficiency object is used
void setErrors(TH2* histo, TEfficiency* Eff);
#endif