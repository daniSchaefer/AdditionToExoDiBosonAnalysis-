#ifndef DEBUGFUNCZZ_H
#define DEBUGFUNCZZ_H

//print further information on one particle
void printParticleInfo(Electron* particle, ZZtree* t);
void printParticleInfo(Muon* particle, ZZtree* t);

//prints information of all jets in event
void printAllFatJetInfo(ZZtree* t);

void PrintEventInfo(int event, ZZtree* tree,bool isHP=1,bool isLP=0);

bool isEventInList(int event, vector<int> listOfEvents);
//this function returns a list that contains all events from list1
//that are not in list2 also.
vector<int> compareLists(vector<int> list1, vector<int> list2);

vector<int> GetEventsFromFile(ifstream &myfile);

void WriteEventsToFile(vector<int> events,ofstream  &myfile);

vector<double> testSelfConsistency(int pdgId, ZZtree* tree, vector<vector<double> > leptonEff, vector<vector<double> > hadronEff, bool isHP, bool isLP);
#endif