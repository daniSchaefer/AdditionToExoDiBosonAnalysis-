#ifndef CROSSSECTIONS_H
#define CROSSSECTIONS_H



float* getAcceptance(string ModelName,string decayMode,float* masspoints, int numberOfMassPoints);
float* getAcceptance(string decayMode,float ktilde);
float* getTheoryCrossSection(string ModelName,float ktilde);
float  getTheoryCrossSection(string ModelName, float mass, float ktilde);
float  getKtilde(string ModelName,float mass, float natural_width);
TGraph* getObservedLimit(string ModelName,string decayMode,float width,bool dependsOnKtilde=0);
TGraph* getLimitUp(string ModelName,string decayMode,float width,int sigma, bool dependsOnKtilde=0);
TGraph* getLimitDown(string ModelName,string decayMode,float width,int sigma, bool dependsOnKtilde =0);
float  getBranchingRatioToWW(string ModelName, float mass);
float  getBranchingRatioToZZ(string ModelName, float mass);
float  getWidthForKtilde(string ModelName,float mass,float ktilde);
float* getNumberOfExpectedEvents(float* xs,float* m_xs,float* acceptance,string ModelName,string decayMode);
TGraph* getExcludedPoints(string ModelName,string decayMode,TGraph* observedlimit,TGraph* expectedEventNumbers,float ktilde);
TGraph* findAllExcludedPoints(std::string ModelName,std::string decayMode,std::map<float,float> mass_acceptance,float ktilde);
void printWidthForKtilde(string ModelName,float ktilde, float massmax, float massmin);

vector<float> getMassesForKtilde(string decayMode, float ktilde);
vector<float> getProducedWitdhForKtilde(string decayMode, float ktilde);

TGraph* getNumberOfExpectedEvents(TGraph* g_xs, TGraph* g_acc,string ModelName,string decayMode, TGraph* g_acc_toZZ=0);
TGraph* getNumberOfExpectedEvents(TF1* g_xs, TGraph* g_acc,string ModelName,string decayMode,TGraph* g_acc_toZZ=0);

TGraph* IsoKtilde(std::string ModelName,std::string decayMode,float ktilde);
void    SetGraphStyle(TGraph* g , std::string title,float x,float y);
float findMassMaxForKtilde(std::string ModelName,std::string decayMode,float ktilde);
TGraph* getLimitOnNexpected(std::string decayMode,TGraph* g_iso_ktilde);
float* getLog(float* list, int length);

TF1* getFitFunction(TGraph* N_expected);
double* getLog(double* list, int length);

TF1* fitCrossSection(string ModelName);
TF1* getTheoryCrossSectionFitted(string ModelName,float ktilde);
#endif
