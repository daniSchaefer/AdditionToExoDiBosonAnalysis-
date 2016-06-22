#ifndef DEBUGFUNC2_H
#define DEBUGFUNC2_H


//prints some infos of event in the file eventX.txt
void InfoEvent(int pdgId,int event, MyClass* t12, const char* filename);

//print reco and gen cuts passed?
void printInfoEventSemileptonic(int pdgId,int event,MyClass* t12,const char* filename);
//prints infos for all hadronic events
void printInfoEventHadronic(int event, MyClass* t12, ofstream &file);

void printEventList(int pdgId, vector<int> events, MyClass* t12, ofstream &file);

vector<int> GetEventsFromFile(ifstream &myfile);
void WriteEventsToFile(vector<int> events, ofstream  &myfile);
#endif