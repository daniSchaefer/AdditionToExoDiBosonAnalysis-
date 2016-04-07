#ifndef DEBUGFUNC2_H
#define DEBUGFUNC2_H


//prints some infos of event in the file eventX.txt
void InfoEvent(int pdgId,int event, MyClass* t12, const char* filename);


void printEventList(int pdgId, vector<int> events, MyClass* t12, ofstream &file);

#endif