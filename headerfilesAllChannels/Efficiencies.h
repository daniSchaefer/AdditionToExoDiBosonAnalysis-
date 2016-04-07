#ifndef EFFICIENCY_H
#define EFFICIENCY_H


void WEfficiencyGetMCEffperSample(int pdgId,const char* input_filename,ofstream &f);


//writes Histo containing the m_VV spektrum of reconstructed events in:
// results/modelName/ModelName_M-**_width0p*.root
void makeRootFileForCheckFitCBBW(string ModelName,string channel,string category,float mass, float width, bool matchV =0,bool getGeneratedKinematics =0,bool getGeneratedKinematicsWithoutSelection =0);


//returns 1 if the difference of W_had_gen and W_had_rec is approximatly zero
//bool isW/isZ controlls which region in m_jet_prunde is taken to reconstruct the isMatchedJet
// 1/1 = 65-105
//1/0 = 65 - 85
//0/1 = 85 -105
//0/0 no cut
bool isMatchedJet(MyClass* t12, bool isW, bool isZ);

//writes mVV histo to file with full leptonic selections applied, but instead 
//of the hadronic selections, a matching of genereted  W and jet is performed
//to check if the pruned mass cuts are responsible for moving the mean value in mVV histo
void makeRootFileForCheckFitCBBW_matching_withoutSelection(string ModelName,string channel,float mass, float width);

void makeRootFileForCheckFitCBBW_recMC_matched(string ModelName,string channel,string category,float mass, float width,int numberFiles);

void makeRootFileForCheckFitCBBW_genMC_withSelection(string ModelName,string channel,string category,float mass, float width);

void makeRootFileForCheckFitCBBW_genMC_withoutSelection(string ModelName,string channel,string category,float mass, float width);

//writes to file with name: ModelNameToWKinematicschannel_EffReweightedHisto.root
//writes 2D histos with W_lep/W_had generated Pt and Eta, where each event is weighted accordingly with the Efficiencies from hadronEff, leptonEff, BVEff and LLVEff
//return the BV and LLV efficiency from the selections on the file
vector<double> testEfficiency(string ModelName, string channel,string category,MyClass* t12 ,string outputFile,vector<vector<double> > hadronEff,vector<vector<double> > leptonEff, double BVEff, double LLVEff,double scale);

//returns the total number of events in file
double NumberOfEventsInFile(string ModelName,float mass,float width);

#endif