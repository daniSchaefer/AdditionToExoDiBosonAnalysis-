#ifndef DEBUGFUNC_H
#define DEBUGFUNC_H

#include "passed_mu_jes.h"

//get pdgIds of every particle, and his mother and daughter particles of events in vector event
void get_pdgId(vector<int> event, string name_output_file, MyClass* t12);
void get_pdgId( string name_output_file, MyClass* t12);

bool isEventInList(int event, vector<int> listOfEvents);



//this function returns a list that contains all events from list1
//that are not in list2 also.
vector<int> compareLists(vector<int> list1, vector<int> list2);

bool isEventInList(double pt, double eta, vector<double> list_pt, vector<double> list_eta);

vector<int> compareLists(vector<int> events, vector<double> list1_pt, vector<double> list1_eta, vector<double> list2_pt, vector<double> list2_eta);

void SetTreeToEvent(int event,MyClass* t12);
void SetTreeToEvent(int event,passed_mu_jes* t12);

//compare events from jennifers tree and my event selection
// here is everything implemented like it is done from jennifer
// i.e. complete selection so that hadronic and leptonic W can be reconstructed
vector<vector<int> > missingEvents(MyClass* t12, passed_mu_jes* t,int pdgId, bool isHP=0, bool isLP=0);

//returns in [0] the number of events that pass all selection criteria
//returns in [1] the overall number of events in the sample
vector<double> testSelfConsistency( int pdgId, MyClass* t12,vector<vector<double> > leptonEff, vector<vector<double> > hadronEff, double BVEff, double LLVEff ,bool isHP=1, bool isLP=0);
#endif
