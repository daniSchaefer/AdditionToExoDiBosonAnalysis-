
#include "TROOT.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#define MyClass_cxx
#include "TChain.h"
#include "MyClass.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include <vector>
#include <vector>
#include <vector>

//#include "TTreeReader.h"     these classes apparantly only exist in root 6
//#include "TTreeReaderValue.h"


#include "vector"
#include "iostream"
#include "iomanip"
#include "fstream"
#include "cmath"
#include "cassert"

using namespace std;

 const char* filename = "data/EXOVVTree_BulkGravToWWToWlepWhad_narrow_M_1200_1.root";

TFile *gendata = new TFile(filename,"READ");
TTree *t12 = (TTree*) gendata->Get("ntuplizer/tree");


 Int_t           genParticle_N=0;
 vector<int>    *genParticle_pdgId=0;
 vector<vector<int> > *genParticle_mother =0;
 vector<int>     *genParticle_nMoth =0;
 vector<int>     *genParticle_nDau=0;
 vector<vector<int> > *genParticle_dau = 0;
 vector<float>   *genParticle_px={};
 vector<float>   *genParticle_py={};
 vector<float>   *genParticle_pz={};
 vector<float>   *genParticle_e={};
 vector<float>   *genParticle_pt={};
 vector<float>   *genParticle_eta={};
 vector<float>   *genParticle_phi={};
vector<float>   *el_hOverE={};
  Int_t           el_N=0;
vector<float>   *el_e={};
vector<float>   *el_eta={};
vector<float>   *el_phi={};
vector<float>   *el_mass={};
vector<float>   *el_pt={};
vector<float>   *el_et={};
vector<float>   *MET_et;
vector<float>   *MET_phi;
vector<float>   *MET_sumEt;
vector<float>   *jetAK4_cisv;
vector<int>     *el_isVetoElectron={};
vector<int>     *el_isMediumElectron={};
vector<int>     *el_isTightElectron={};
vector<int>     *el_isHeepElectron={};
vector<int>     *el_isHeep51Electron={};
vector<int>     *el_isLooseElectron={};
vector<int>     *el_isVetoElectronBoosted={};
vector<int>     *el_isMediumElectronBoosted={};
vector<int>     *el_isTightElectronBoosted={};
vector<int>     *el_isHeepElectronBoosted={};
vector<int>     *el_isHeep51ElectronBoosted={};
vector<int>     *el_isLooseElectronBoosted={};
vector<float>   *el_pfRelIso={};
vector<float>   *el_trackIso={};
Int_t           mu_N=0;
vector<int>     *mu_pdgId={};
vector<float>   *mu_charge={};
vector<float>   *mu_e={};
vector<float>   *mu_eta={};
vector<float>   *mu_phi={};
vector<float>   *mu_mass={};
vector<float>   *mu_pt={};
vector<int>     *mu_isHighPtMuon={};
vector<int>     *mu_isTightMuon={};
vector<int>     *mu_isLooseMuon={};
vector<int>     *mu_isPFMuon={};
vector<int>     *mu_isSoftMuon={};
vector<float>   *mu_trackIso={};
vector<float>   *mu_pfRelIso={};
vector<float>   *mu_photonIso={};
vector<float>   *mu_neutralHadIso={};
vector<float>   *mu_chargedHadIso={};
vector<float>   *mu_pfRhoCorrRelIso03={};
vector<float>   *mu_pfRhoCorrRelIso04={};
vector<float>   *mu_pfDeltaCorrRelIso={};
Int_t           jetAK4_N=0;
vector<float>   *jetAK4_pt={};
vector<float>   *jetAK4_eta={};
vector<float>   *jetAK4_mass={};
vector<float>   *jetAK4_phi={};
vector<float>   *jetAK4_e={};
vector<int>     *jetAK4_nbHadrons={};
Int_t           jetAK8_N=0;
vector<float>   *jetAK8_pt={};
vector<float>   *jetAK8_eta={};
vector<float>   *jetAK8_mass={};
vector<float>   *jetAK8_phi={};
vector<float>   *jetAK8_e={};
TBranch        *b_el_hOverE;   //!
TBranch        *b_jetAK4_cisv;   //!
TBranch        *b_el_trackIso;   //!
TBranch        *b_MET_et;   //!
TBranch        *b_MET_phi;   //!
TBranch        *b_MET_sumEt;   //!
TBranch        *b_jetAK4_nbHadrons;   //!
TBranch        *b_jetAK4_N;   //!
TBranch        *b_jetAK4_pt;   //!
TBranch        *b_jetAK4_eta;   //!
TBranch        *b_jetAK4_mass;   //!
TBranch        *b_jetAK4_phi;   //!
TBranch        *b_jetAK4_e;   //!
TBranch        *b_jetAK8_N;   //!
TBranch        *b_jetAK8_pt;   //!
TBranch        *b_jetAK8_eta;   //!
TBranch        *b_jetAK8_mass;   //!
TBranch        *b_jetAK8_phi;   //!
TBranch        *b_jetAK8_e;   //!
TBranch        *b_mu_pfRhoCorrRelIso03;   //!
TBranch        *b_mu_pfRhoCorrRelIso04;   //!
TBranch        *b_mu_pfDeltaCorrRelIso;   //!
TBranch        *b_mu_pfRelIso;   //!
TBranch        *b_mu_photonIso;   //!
TBranch        *b_mu_neutralHadIso;   //!
TBranch        *b_mu_chargedHadIso;   //!
TBranch        *b_el_N;   //!
TBranch        *b_el_e;   //!
TBranch        *b_el_eta;   //!
TBranch        *b_el_phi;   //!
TBranch        *b_el_mass;   //!
TBranch        *b_el_pt;   //!
TBranch        *b_el_et;   //!
TBranch        *b_el_isVetoElectron;   //!
TBranch        *b_el_isMediumElectron;   //!
TBranch        *b_el_isTightElectron;   //!
TBranch        *b_el_isHeepElectron;   //!
TBranch        *b_el_isHeep51Electron;   //!
TBranch        *b_el_isLooseElectron;   //!
TBranch        *b_el_isVetoElectronBoosted;   //!
TBranch        *b_el_isMediumElectronBoosted;   //!
TBranch        *b_el_isTightElectronBoosted;   //!
TBranch        *b_el_isHeepElectronBoosted;   //!
TBranch        *b_el_isHeep51ElectronBoosted;   //!
TBranch        *b_el_isLooseElectronBoosted;   //!
TBranch        *b_el_pfRelIso;   //!
TBranch        *b_mu_N;   //!
TBranch        *b_mu_pdgId;   //!
TBranch        *b_mu_charge;   //!
TBranch        *b_mu_e;   //!
TBranch        *b_mu_eta;   //!
TBranch        *b_mu_phi;   //!
TBranch        *b_mu_mass;   //!
TBranch        *b_mu_pt;   //!
TBranch        *b_mu_isHighPtMuon;   //!
TBranch        *b_mu_isTightMuon;   //!
TBranch        *b_mu_isLooseMuon;   //!
TBranch        *b_mu_isPFMuon;   //!
TBranch        *b_mu_isSoftMuon;   //!
TBranch        *b_mu_trackIso;   //!
TBranch        *b_genParticle_pt;   //!
TBranch        *b_genParticle_eta;   //!
TBranch        *b_genParticle_phi;   //!
TBranch        *b_genParticle_px;   //!
TBranch        *b_genParticle_py;   //!
TBranch        *b_genParticle_pz;   //!
TBranch        *b_genParticle_e;   //!
TBranch        *b_genParticle_N;   //!
TBranch        *b_genParticle_pdgId;   //!
TBranch        *b_genParticle_mother;   //!
TBranch        *b_genParticle_nMoth;   //!
TBranch        *b_genParticle_nDau;   //!
TBranch        *b_genParticle_dau;   //!


//-----------------------------------------------------------------------------
//--------------------function deklarations------------------------------------

//get pdgIds of every particle, and his mother and daughter particles of events in vector event
void get_pdgId(vector<int> event, string name_output_file);
//fill a histo with the reconstructed W mass of events in vec. event. Function works for W->l nu or G-> l nu (with missing W)
void getInvariantWmass(TH1F* histo,vector<int> events, int pdgId_lepton, int pdgId_mother=24);
// set Axis Titles and offset for TH1F histo
void style1D(TH1F* histo, TString nameXaxis, TString nameYaxis, Double_t  offset=1.2);
//gives the number of events that have tau-> e nu nu and tau -> mu nu nu out of the events in vec. events
vector<int> getTauBranchingRatio(vector<int> events, int pdgId_lepton, int pdgId_mother=24);
vector<int> getTauBranchingRatio(vector<int> events);
//fills histo2 with the recontructed transversal impulse and histo1 with the pseudorapidity of the W boson
// decauymode has to be leptonic; the generated events are used
void getgenX_eta_pt(TH1F* histo1, TH1F* histo2,vector<int> events, int pdgId_lepton, int pdgId_mother,vector<vector<double> > leptonSelection, int X=24 );
//same as above but without kinematic constrictions on leptons
void getgenX_eta_pt_wv(TH1F* histo1,TH1F* histo2 ,vector<int> events, int pdgId_lepton, int pdgId_mother ,vector<vector<double> >leptonSelection , int X);
// seperate the event in lists that contain the events with W->e, W-> mu ...
vector<vector<int> > genDataEventSeparationSemileptonicWW(int howmany);
// seperate events in G->WW, G->Wl, G->W had, G-> l, had
vector<vector<int> > generatedSemiLepEventClassification(int howmany);
// gives the events with tau->e nu nu in [0] and tau->mu nu nu in [1]
vector<vector<int> >selectTauEvents(vector<int> events,int pdgId_lepton, int pdgId_mother);
//get kinematics of particle X , first howmany events
//applies lepton cuts, b-jet veto and missing Et cut
void getX_eta_pt(TH1F* histo1, TH1F* histo2, int howmany, int X,vector<vector<double> >leptonSelction_tight,vector<vector<double> > leptonSelection_loose);
// same as above but applies only lepton cuts
void getX_eta_pt_onlyLeptonCuts(TH1F* histo1,TH1F* histo2 ,int howmany, int X,vector<vector<double> >leptonSelection_tight,vector<vector<double> >leptonSelection_loose);
//applies Muon selection criteria on MC after detector simulation
// gives list of events which fulfill these criteria
vector<int> EventSelectionMuon(int howmany, vector<vector<double> > leptonSelection_tight, vector<vector<double> > leptonSelection_loose);
//applies Electron selection criteria on MC after detector simulation
// gives list of events which fulfill these criteria
vector<int> EventSelectionElectron(int howmany, vector<vector<double> > leptonSelection_tight, vector<vector<double> > leptonSelection_loose);
// recontruct the leptonically decaying W boson from lepton 4-momentum and missing transverse Energie
TLorentzVector recNeutrino(Double_t MET,Double_t MET_phi ,TLorentzVector lepton);
//fill histo1 with eta, histo2 with pt of the particle with pdgId "pdgId" 
//from the events in list "events"
//function checks for mother particles and fills only if mother = 24,39 or 15
void getKinematicsFromGeneratedEvents(TH1F* histo1,TH1F* histo2, vector<int> events, int pdgId);
//checks if mother particle of particleNumber in event is W,G or tau
int rightMother(int event, int particleNumber);
//gives a list of all particles in event with pdgId
vector<int> findParticle(int event, int pdgId);
//get the lorentz vector of particleNumber in event
TLorentzVector getLorentzVector(int event, int particleNumber);
vector<int> getDaughterPdgId(int event, int numParticle);
//CHECK for some criteria
int isLooseElectron(int event, int p, vector<vector<double> >loose);
int isTightElectron(int event, int p, vector<vector<double> >tight);
int isTightMuon(int event, int p, vector<vector<double> >tight);
int isLooseMuon(int event, int p, vector<vector<double> >loose);
int isRightAK8jet(int event,int p);
int isVetoAK4jet(int event,int p);

bool isEventInList(int event, vector<int> listOfEvents);
vector<int> compareLists(vector<int> list1, vector<int> list2);
//-----------------------------------------------------------------------------
//---------------------Main function begins here-------------------------------

void lookAtParticleTree(int which, int howmany)
{
//Set all relevant Branch adress

  t12->SetBranchAddress("genParticle_N", &genParticle_N, &b_genParticle_N);
  t12->SetBranchAddress("genParticle_pdgId", &genParticle_pdgId, &b_genParticle_pdgId);
  t12->SetBranchAddress("genParticle_mother", &genParticle_mother, &b_genParticle_mother);
  t12->SetBranchAddress("genParticle_nMoth", &genParticle_nMoth, &b_genParticle_nMoth);
  t12->SetBranchAddress("genParticle_nDau", &genParticle_nDau, &b_genParticle_nDau);
  t12->SetBranchAddress("genParticle_dau", &genParticle_dau, &b_genParticle_dau);
  t12->SetBranchAddress("genParticle_pt", &genParticle_pt, &b_genParticle_pt);
  t12->SetBranchAddress("genParticle_px", &genParticle_px, &b_genParticle_px);
  t12->SetBranchAddress("genParticle_py", &genParticle_py, &b_genParticle_py);
  t12->SetBranchAddress("genParticle_pz", &genParticle_pz, &b_genParticle_pz);
  t12->SetBranchAddress("genParticle_e", &genParticle_e, &b_genParticle_e);
  t12->SetBranchAddress("genParticle_pt", &genParticle_pt, &b_genParticle_pt);
  t12->SetBranchAddress("genParticle_eta", &genParticle_eta, &b_genParticle_eta);
  t12->SetBranchAddress("genParticle_phi", &genParticle_phi, &b_genParticle_phi);
  t12->SetBranchAddress("genParticle_e", &genParticle_e, &b_genParticle_e);
  t12->SetBranchAddress("el_N", &el_N, &b_el_N);
  t12->SetBranchAddress("el_e", &el_e, &b_el_e);
  t12->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
  t12->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
  t12->SetBranchAddress("el_mass", &el_mass, &b_el_mass);
  t12->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
  t12->SetBranchAddress("el_et", &el_et, &b_el_et);
  t12->SetBranchAddress("el_isVetoElectron", &el_isVetoElectron, &b_el_isVetoElectron);
  t12->SetBranchAddress("el_isMediumElectron", &el_isMediumElectron, &b_el_isMediumElectron);
  t12->SetBranchAddress("el_isTightElectron", &el_isTightElectron, &b_el_isTightElectron);
  t12->SetBranchAddress("el_isHeepElectron", &el_isHeepElectron, &b_el_isHeepElectron);
  t12->SetBranchAddress("el_isHeep51Electron", &el_isHeep51Electron, &b_el_isHeep51Electron);
  t12->SetBranchAddress("el_isLooseElectron", &el_isLooseElectron, &b_el_isLooseElectron);
  t12->SetBranchAddress("el_isVetoElectronBoosted", &el_isVetoElectronBoosted, &b_el_isVetoElectronBoosted);
  t12->SetBranchAddress("el_isMediumElectronBoosted", &el_isMediumElectronBoosted, &b_el_isMediumElectronBoosted);
  t12->SetBranchAddress("el_isTightElectronBoosted", &el_isTightElectronBoosted, &b_el_isTightElectronBoosted);
  t12->SetBranchAddress("el_isHeepElectronBoosted", &el_isHeepElectronBoosted, &b_el_isHeepElectronBoosted);
  t12->SetBranchAddress("el_isHeep51ElectronBoosted", &el_isHeep51ElectronBoosted, &b_el_isHeep51ElectronBoosted);
  t12->SetBranchAddress("el_isLooseElectronBoosted", &el_isLooseElectronBoosted, &b_el_isLooseElectronBoosted);
  t12->SetBranchAddress("el_hOverE",&el_hOverE, &b_el_hOverE);
  t12->SetBranchAddress("mu_N", &mu_N, &b_mu_N);
  t12->SetBranchAddress("mu_pdgId", &mu_pdgId, &b_mu_pdgId);
  t12->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
  t12->SetBranchAddress("mu_e", &mu_e, &b_mu_e);
  t12->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
  t12->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
  t12->SetBranchAddress("mu_mass", &mu_mass, &b_mu_mass);
  t12->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
  t12->SetBranchAddress("mu_isHighPtMuon", &mu_isHighPtMuon, &b_mu_isHighPtMuon);
  t12->SetBranchAddress("mu_isTightMuon", &mu_isTightMuon, &b_mu_isTightMuon);
  t12->SetBranchAddress("mu_isLooseMuon", &mu_isLooseMuon, &b_mu_isLooseMuon);
  t12->SetBranchAddress("mu_isPFMuon", &mu_isPFMuon, &b_mu_isPFMuon);
  t12->SetBranchAddress("mu_isSoftMuon", &mu_isSoftMuon, &b_mu_isSoftMuon);
  t12->SetBranchAddress("mu_trackIso", &mu_trackIso, &b_mu_trackIso);
  t12->SetBranchAddress("mu_pfRelIso", &mu_pfRelIso, &b_mu_pfRelIso);
  t12->SetBranchAddress("mu_photonIso", &mu_photonIso, &b_mu_photonIso);
  t12->SetBranchAddress("mu_neutralHadIso", &mu_neutralHadIso, &b_mu_neutralHadIso);
  t12->SetBranchAddress("mu_chargedHadIso", &mu_chargedHadIso, &b_mu_chargedHadIso);
  t12->SetBranchAddress("mu_pfRhoCorrRelIso03", &mu_pfRhoCorrRelIso03, &b_mu_pfRhoCorrRelIso03);
  t12->SetBranchAddress("mu_pfRhoCorrRelIso04", &mu_pfRhoCorrRelIso04, &b_mu_pfRhoCorrRelIso04);
  t12->SetBranchAddress("mu_pfDeltaCorrRelIso", &mu_pfDeltaCorrRelIso, &b_mu_pfDeltaCorrRelIso);
  t12->SetBranchAddress("mu_pfRelIso", &mu_pfRelIso, &b_mu_pfRelIso);
  t12->SetBranchAddress("el_pfRelIso", &el_pfRelIso, &b_el_pfRelIso);
  t12->SetBranchAddress("jetAK4_N", &jetAK4_N, &b_jetAK4_N);
  t12->SetBranchAddress("jetAK4_pt", &jetAK4_pt, &b_jetAK4_pt);
  t12->SetBranchAddress("jetAK4_eta", &jetAK4_eta, &b_jetAK4_eta);
  t12->SetBranchAddress("jetAK4_mass", &jetAK4_mass, &b_jetAK4_mass);
  t12->SetBranchAddress("jetAK4_phi", &jetAK4_phi, &b_jetAK4_phi);
  t12->SetBranchAddress("jetAK4_e", &jetAK4_e, &b_jetAK4_e);
  t12->SetBranchAddress("jetAK8_N", &jetAK8_N, &b_jetAK8_N);
  t12->SetBranchAddress("jetAK8_pt", &jetAK8_pt, &b_jetAK8_pt);
  t12->SetBranchAddress("jetAK8_eta", &jetAK8_eta, &b_jetAK8_eta);
  t12->SetBranchAddress("jetAK8_mass", &jetAK8_mass, &b_jetAK8_mass);
  t12->SetBranchAddress("jetAK8_phi", &jetAK8_phi, &b_jetAK8_phi);
  t12->SetBranchAddress("jetAK8_e", &jetAK8_e, &b_jetAK8_e);
  t12->SetBranchAddress("jetAK4_nbHadrons", &jetAK4_nbHadrons, &b_jetAK4_nbHadrons);
  t12->SetBranchAddress("MET_et", &MET_et, &b_MET_et);
  t12->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
  t12->SetBranchAddress("MET_sumEt", &MET_sumEt, &b_MET_sumEt);
  t12->SetBranchAddress("el_trackIso", &el_trackIso, &b_el_trackIso);
  t12->SetBranchAddress("jetAK4_cisv", &jetAK4_cisv, &b_jetAK4_cisv);
//------------------------------------------------------------------------------



 cout<< "we look at the first "<< howmany << " events "<< endl;

 vector<vector<int> > sep_result =genDataEventSeparationSemileptonicWW(howmany);
 vector<int> missingW= sep_result.at(0);
 // these lists contain the events with one or two W, one of them decaying in
 // a lepton of the marked flavour
 vector<int> WWelectron = sep_result.at(1);
 vector<int> WWtauon =sep_result.at(3);
 vector<int> WWmuon=sep_result.at(2);
 // these lists contain events where a W direktly decays(W is missing in pdgId)
 vector<int> Wmisselectron = sep_result.at(4);
 vector<int> Wmissmuon = sep_result.at(5);
 vector<int> Wmisstauon = sep_result.at(6);
 //lists contain events with W->tau + nu_tau, tau->e/mu + neutrinos
 vector<vector<int> > sep_tau_result = selectTauEvents(WWtauon,15,24);
 vector<int> WTAUelectron = sep_tau_result.at(0);
 vector<int> WTAUmuon = sep_tau_result.at(1);
 //these lists contain  missingW -> tau+nu_tau, tau-> e/mu + neutrinos
 sep_tau_result = selectTauEvents(Wmisstauon,15,39);
 vector<int> TAUelectron = sep_tau_result.at(0);
 vector<int> TAUmuon = sep_tau_result.at(1);
 

 cout <<"total # of events with W -> e(+/-):  " << WWelectron.size()+ Wmisselectron.size()<< endl; 
 cout <<"total # of events with W -> mu(+/-):  " << WWmuon.size()+ Wmissmuon.size()<< endl;
 cout <<"total # of events with W -> tau(+/-):  " << WWtauon.size()+ Wmisstauon.size()<< endl;

 vector<vector<int> > new_result = generatedSemiLepEventClassification(howmany);
 vector<int> EventWithEl = new_result[4];
 vector<int> EventWithMu = new_result[5];
 vector<int> EventWithTau = new_result[6];

 vector<int> help = compareLists(EventWithTau,WWtauon);
 cout<< help.size()<< " comparison between EventWithTau, WWtauon "<< endl;
 get_pdgId(help,"tests/debug4.txt");
//find invariant W mass for missingW.>e(+/-) nu_e and for normal leptonically decaying W
 if(which ==3)
   {
     TH1F *hvWmass_e= new TH1F("hvWmass_e", "invariant mass of virtual W in e-decay",100, 0, 100);
     TH1F *hvWmass_mu= new TH1F("hvWmass_mu", "invariant mass of virtual W in mu-decay",100, 0, 100);
     TH1F *hvWmass_tau= new TH1F("hvWmass_tau", "invariant mass of virtual W in tau-decay",100, 0, 100);
     TH1F *hWmass_e= new TH1F("hWmass_e", "invariant mass of W in e-decay",100, 0, 100);
     TH1F *hWmass_mu= new TH1F("hWmass_mu", "invariant mass of W in mu-decay",100, 0, 100);
     TH1F *hWmass_tau= new TH1F("hWmass_tau", "invariant mass of W in tau-decay",100, 0, 100);

     getInvariantWmass(hvWmass_e, Wmisselectron, 11,39);
     getInvariantWmass(hvWmass_mu, Wmissmuon,13,39);
     getInvariantWmass(hvWmass_tau,Wmisstauon,15,39);
     getInvariantWmass(hWmass_e, WWelectron, 11,24);
     getInvariantWmass(hWmass_mu, WWmuon,13,24);
     getInvariantWmass(hWmass_tau,WWtauon,15,24);
     TCanvas *c1 = new TCanvas("c1","c1",1600,1600);
     c1->Divide(3,2);
     c1->cd(1);
     style1D(hvWmass_e, "W mass [GeV]", "number of events");
     hvWmass_e->Draw();
     c1->cd(2);
     style1D(hvWmass_mu, "W mass [GeV]", "number of events");
     hvWmass_mu->Draw();
     c1->cd(3);
     style1D(hvWmass_tau, "W mass [GeV]", "number of events");
     hvWmass_tau->Draw();
     c1->cd(4);
     style1D(hWmass_e, "W mass [GeV]", "number of events" ,1.5 );
     hWmass_e->Draw();
     c1->cd(5);
     style1D(hWmass_mu, "W mass [GeV]", "number of events",1.5);
     hWmass_mu->Draw();
     c1->cd(6);
     style1D(hWmass_tau, "W mass [GeV]", "number of events",1.5);
     hWmass_tau->Draw();
     c1->SaveAs("invariantWmass.pdf");
   }



 //electron muon and W pt and eta with cuts for lepton detection applied
 //here only for W->l nu_l

     // selection criteria for leptons
     vector<vector<double> > leptonSelection_loose(4, vector<double> (3));
     vector<vector<double> > leptonSelection_tight(4, vector<double> (3));
     for(int m=0;m<4;m++){for(int m1=0;m1<3;m1++)
	 {leptonSelection_loose[m][m1]=0;leptonSelection_tight[m][m1]=0;}}
     // order:  leptonSelection[0][x]= electron pt bounds
     leptonSelection_loose[0][0]= 35;
     leptonSelection_tight[0][0]= 120;
     //         leptonSelection[1][x]= muon pt bounds
     leptonSelection_loose[1][0]= 20;
     leptonSelection_tight[1][0]= 53;
     //         leptonSelection[2][x]= electron eta bounds
     leptonSelection_loose[2][0]= 2.5;
     leptonSelection_loose[2][1]= 1.4442;
     leptonSelection_loose[2][2]= 1.566;

     leptonSelection_tight[2][0]= 2.5;
     leptonSelection_tight[2][1]= 1.4442;
     leptonSelection_tight[2][2]= 1.566;
     //         leptonSelection[3][x]= muon eta bounds
     leptonSelection_loose[3][0]= 2.4;
     leptonSelection_tight[3][0]= 2.1;
    

     if(which ==4)
       {
     TH1F *hgenW_e_eta= new TH1F("hgenW_e_eta","pseudorapidity of gen. W with W->e nu_e",100,-4,4);
     TH1F *hgenW_mu_eta= new TH1F("hgenW_mu_eta","pseudorapidity of gen. W with W->mu nu_mu",100, -4, 4);
     TH1F *hgenW_e_pt= new TH1F("hgenW_e_pt","transversial impulse of gen. W with W->e nu_e",100, 100, 1000);
     TH1F *hgenW_mu_pt= new TH1F("hgenW_mu_pt","transversial impulse of gen. W with W->mu nu_mu",100, 100, 1000);
     //W->e
     getgenX_eta_pt(hgenW_e_eta, hgenW_e_pt,WWelectron,11, 24,leptonSelection_tight);
     // missing W -> e
     getgenX_eta_pt(hgenW_e_eta,hgenW_e_pt,Wmisselectron,11, 39,leptonSelection_tight);
     //W missingW -> tau -> e
     getgenX_eta_pt(hgenW_e_eta,hgenW_e_pt,TAUelectron,15, 39,leptonSelection_tight);
       //W->tau->e
    getgenX_eta_pt(hgenW_e_eta,hgenW_e_pt,WTAUelectron,15, 24,leptonSelection_tight);
       //W->mu
     getgenX_eta_pt(hgenW_mu_eta,hgenW_mu_pt,WWmuon,13, 24,leptonSelection_tight);
     //missing W -> mu
     getgenX_eta_pt(hgenW_mu_eta,hgenW_mu_pt,Wmissmuon,13,39,leptonSelection_tight);
     //missing W -> tau -> mu
     getgenX_eta_pt(hgenW_mu_eta,hgenW_mu_pt,TAUmuon,15,39,leptonSelection_tight);
       //W->tau->e
    getgenX_eta_pt(hgenW_mu_eta,hgenW_mu_pt,WTAUmuon,15,24,leptonSelection_tight);
     TCanvas *c1 = new TCanvas("c1","c1",1600,1600);
     style1D(hgenW_e_eta,"pseudorapidity of generated W","# events");
     style1D(hgenW_e_pt,"transversial impulse of generated W","# events");
     style1D(hgenW_mu_eta,"pseudorapidity of generated W","# events");
     style1D(hgenW_mu_pt,"transversial impulse of generated W","# events");

     c1->Divide(2,2);
     c1->cd(1);
     hgenW_e_eta->Draw();
     c1->cd(2);
     hgenW_e_pt->Draw();
     c1->cd(3);
     hgenW_mu_eta->Draw();
     c1->cd(4);
     hgenW_mu_pt->Draw();
     c1->SaveAs("genWkinematics.pdf");

     TH1F *hgenE_eta= new TH1F("hgenE_eta","pseudorapidity of gen. e(+/-)" ,100,-3,3);
     TH1F *hgenMu_eta= new TH1F("hgenMu_eta","pseudorapidity of gen. mu(+/-) ",100, -3, 3);
     TH1F *hgenE_pt= new TH1F("hgenE_pt","transversial impulse of gen. e(+/-)",100, 0, 1000);
     TH1F *hgenMu_pt= new TH1F("hgenMu_pt","transversial impulse of gen. mu(+/-) ",100, 0, 1000);
     //W->e
     getgenX_eta_pt(hgenE_eta, hgenE_pt,WWelectron,11, 24,leptonSelection_tight,11);
     // missing W -> e
     getgenX_eta_pt(hgenE_eta,hgenE_pt,Wmisselectron,11, 39,leptonSelection_tight,11);
     //W missingW -> tau -> e
     getgenX_eta_pt(hgenE_eta,hgenE_pt,TAUelectron,15, 39,leptonSelection_tight,11);
       //W->tau->e
     getgenX_eta_pt(hgenE_eta,hgenE_pt,WTAUelectron,15, 24,leptonSelection_tight,11);
       //W->mu
     getgenX_eta_pt(hgenMu_eta,hgenMu_pt,WWmuon,13, 24,leptonSelection_tight,13);
     //missing W -> mu
     getgenX_eta_pt(hgenMu_eta,hgenMu_pt,Wmissmuon,13,39,leptonSelection_tight,13);
     //missing W -> tau -> mu
     getgenX_eta_pt(hgenMu_eta,hgenMu_pt,TAUmuon,15,39,leptonSelection_tight,13);
       //W->tau->e
     getgenX_eta_pt(hgenMu_eta,hgenMu_pt,WTAUmuon,15,24,leptonSelection_tight,13);
     TCanvas *c2 = new TCanvas("c2","c2",1600,1600);
     style1D(hgenE_eta,"pseudorapidity of generated electron","# events");
     style1D(hgenE_pt,"transversial impulse of generated electron","# events");
     style1D(hgenMu_eta,"pseudorapidity of generated muon","# events");
     style1D(hgenMu_pt,"transversial impulse of generated muon","# events");

     c2->Divide(2,2);
     c2->cd(1);
     hgenE_eta->Draw();
     c2->cd(2);
     hgenE_pt->Draw();
     c2->cd(3);
     hgenMu_eta->Draw();
     c2->cd(4);
     hgenMu_pt->Draw();
     c2->SaveAs("genEandMUkinematics.pdf");
       }
 //get electron an muon kinematic distributions after the detector simulation 

 if(which==5)
   {

     TH1F *hE_eta= new TH1F("hE_eta","eta of e(+/-)",100, -3, 3);
     TH1F *hE_pt= new TH1F("hE_pt","transversial impulse of e(+/-) ",100, 0, 1000);
     TH1F *hMu_eta= new TH1F("hMu_eta","eta of mu(+/-)",100, -3, 3);
     TH1F *hMu_pt= new TH1F("hMu_pt","transversial impulse of mu(+/-) ",100, 0, 1000);
  
     getX_eta_pt(hE_eta,hE_pt,howmany,11,leptonSelection_tight, leptonSelection_loose);
     getX_eta_pt(hMu_eta,hMu_pt,howmany,13,leptonSelection_tight, leptonSelection_loose);
     TCanvas *c3= new TCanvas("c3","c3",1600,1600);
     c3->Divide(2,2);
     c3->cd(1);
     hE_eta->Draw();
     c3->cd(2);
     hE_pt->Draw();
     c3->cd(3);
     hMu_eta->Draw();
     c3->cd(4);
     hMu_pt->Draw();
     c3->SaveAs("genEandMUkinematics.pdf");


   }
 // tau decay branching ratio:

 vector<int> TauBratio= getTauBranchingRatio(Wmisstauon,15,39);
 cout<< Wmisstauon.size()<<" # of events with missing W decaying into tau"<< endl; 
 cout<<" Tau into e(+/-) decays "<< TauBratio[0]<< endl;
 cout <<" Tau into mu(+/-) decays "<<  TauBratio[1]<< endl;
 // get_pdgId(Wmisstauon,"test.txt","data/EXOVVTree_BulkGravToWWToWlepWhad_narrow_M_1200_1.root");
 vector<int> TauBratioW= getTauBranchingRatio(WWtauon,15,24);
 cout<< WWtauon.size()<<" # of events with W decaying into tau"<< endl; 
 cout<<" Tau into e(+/-) decays "<< TauBratioW[0]<< endl;
 cout <<" Tau into mu(+/-) decays "<<  TauBratioW[1]<< endl;
 cout<< "Branching ratio e: " << (TauBratioW[0]+TauBratio[0])/float(WWtauon.size()+ Wmisstauon.size())*100 << endl;
 cout<< "Branching ratio mu: " << (TauBratioW[1]+TauBratio[1])/float(WWtauon.size()+ Wmisstauon.size())*100 << endl;

 vector<int> TauBratio2= getTauBranchingRatio(EventWithTau); 
 cout<<" Tau into e(+/-) decays "<< TauBratio2[0]<< endl;
 cout <<" Tau into mu(+/-) decays "<<  TauBratio2[1]<< endl;

 


 //detector effieciency for muons with muon selection criteria applied
 if(which==6)
   {
     TH1F* Average_eta = new TH1F("Average_eta","average (eta)",100,-3,3);
     TH1F* Average_pt = new TH1F("Average_pt","average (pt)",80,0,1000);
     TH1F* hgenMuon_eta = new TH1F("hgenMuon_eta","pseudorapidity of gen. muon",100,-3,3);
     TH1F* hMuon_eta = new TH1F("hMuon_eta","pseudorapidity of mu with kin. cuts and vetoes",100,-3,3);
     TH1F* hgenMuon_pt = new TH1F("hgenMuon_pt","Pt of gen. muon",80,0,1000);
     TH1F* hMuon_pt = new TH1F("hMuon_pt","Pt of muon with kin. cuts and vetoes",80,0,1000);

     vector<int> events ={};
     for(int  i=0;i<howmany;i++)
       {events.push_back(i);}

     getgenX_eta_pt(hgenMuon_eta,hgenMuon_pt,WWmuon,13, 24,leptonSelection_tight,13);
 //missing W -> mu
     getgenX_eta_pt(hgenMuon_eta,hgenMuon_pt,Wmissmuon,13,39,leptonSelection_tight,13);
 //missing W -> tau -> mu
     getgenX_eta_pt(hgenMuon_eta,hgenMuon_pt,TAUmuon,15,39,leptonSelection_tight,13);
 //W->tau->e
     getgenX_eta_pt(hgenMuon_eta,hgenMuon_pt,WTAUmuon,15,24,leptonSelection_tight,13);
 //     getgenX_eta_pt_wv(hgenMuon_eta,hgenMuon_pt,WWmuon,13, 24,leptonSelection_tight,13);
 // //missing W -> mu
 //     getgenX_eta_pt_wv(hgenMuon_eta,hgenMuon_pt,Wmissmuon,13,39,leptonSelection_tight,13);
 // //missing W -> tau -> mu
 //     getgenX_eta_pt_wv(hgenMuon_eta,hgenMuon_pt,TAUmuon,15,39,leptonSelection_tight,13);
 // //W->tau->e
 //     getgenX_eta_pt_wv(hgenMuon_eta,hgenMuon_pt,WTAUmuon,15,24,leptonSelection_tight,13);
     
 getX_eta_pt(hMuon_eta,hMuon_pt,howmany,13,leptonSelection_tight,leptonSelection_loose);
 style1D(Average_eta,"pseudorapidity"," ");
 style1D(Average_pt,"pt (GeV)"," ");
 style1D(hgenMuon_eta,"pseudorapidity mu","# events ");
 style1D(hgenMuon_pt,"pt mu (GeV)","# events ");
 style1D(hMuon_pt,"pt mu (GeV)","# events ");
 style1D(hMuon_eta,"pseudorapidity mu","# events ");
 //hMuon_eta->Sumw2(kTrue);
 //hgenMuon_eta->Sumw2(kTrue);
     TCanvas *c =new TCanvas("c","c",800,1600);
     c->Divide(2,4);
     c->cd(1);
     hMuon_eta->Draw();
     c->cd(2);
     hgenMuon_eta->Draw();
     c->cd(3);
     hMuon_pt->Draw();
     c->cd(4);
     hgenMuon_pt->Draw();
     c->cd(5);
     if(TEfficiency::CheckConsistency(*hMuon_eta,*hgenMuon_eta))
       {
	 TEfficiency* etaEff= new TEfficiency(*hMuon_eta,*hgenMuon_eta);
	 //TGraphAsymmErrors* g= etaEff->CreateGraph();
	 etaEff->Draw();
       }
     c->cd(6);
     Average_eta->Add(hMuon_eta,hgenMuon_eta,-1.0,1.0);
     Average_eta->Draw("E1");
     c->cd(7);
     if(TEfficiency::CheckConsistency(*hMuon_pt,*hgenMuon_pt))
       {
	 TEfficiency* ptEff= new TEfficiency(*hMuon_pt,*hgenMuon_pt);
	 //TGraphAsymmErrors* g= ptEff->CreateGraph();
	 ptEff->Draw();
       }
     c->cd(8);
     Average_pt->Add(hMuon_pt,hgenMuon_pt,-1.0,1.0);
     Average_pt->Draw("E1");
     c->SaveAs("MuEffAndgenCuts.pdf");


 TH1F* Average1_eta = new TH1F("Average1_eta","average (eta)",100,-3,3);
     TH1F* Average1_pt = new TH1F("Average1_pt","average (pt)",80,0,1000);
     TH1F* hgenMuon1_eta = new TH1F("hgenMuon1_eta","pseudorapidity of gen. muon",100,-3,3);
     TH1F* hMuon1_eta = new TH1F("hMuon1_eta","pseudorapidity of mu with kin. cuts and vetoes",100,-3,3);
     TH1F* hgenMuon1_pt = new TH1F("hgenMuon1_pt","Pt of gen. muon",80,0,1000);
     TH1F* hMuon1_pt = new TH1F("hMuon1_pt","Pt of muon with kin. cuts and vetoes",80,0,1000);

    
  getgenX_eta_pt(hgenMuon1_eta,hgenMuon1_pt,WWmuon,13, 24,leptonSelection_tight,13);
 //missing W -> mu
     getgenX_eta_pt(hgenMuon1_eta,hgenMuon1_pt,Wmissmuon,13,39,leptonSelection_tight,13);
 //missing W -> tau -> mu
     getgenX_eta_pt(hgenMuon1_eta,hgenMuon1_pt,TAUmuon,15,39,leptonSelection_tight,13);
 //W->tau->e
     getgenX_eta_pt(hgenMuon1_eta,hgenMuon1_pt,WTAUmuon,15,24,leptonSelection_tight,13);
    //  getgenX_eta_pt_wv(hgenMuon1_eta,hgenMuon1_pt,WWmuon,13, 24,leptonSelection_tight,13);
 // //missing W -> mu
 //     getgenX_eta_pt_wv(hgenMuon1_eta,hgenMuon1_pt,Wmissmuon,13,39,leptonSelection_tight,13);
 // //missing W -> tau -> mu
 //     getgenX_eta_pt_wv(hgenMuon1_eta,hgenMuon1_pt,TAUmuon,15,39,leptonSelection_tight,13);
 // //W->tau->e
 //     getgenX_eta_pt_wv(hgenMuon1_eta,hgenMuon1_pt,WTAUmuon,15,24,leptonSelection_tight,13);
 getX_eta_pt_onlyLeptonCuts(hMuon1_eta,hMuon1_pt,howmany,13,leptonSelection_tight,leptonSelection_loose);
 style1D(Average1_eta,"pseudorapidity"," ");
 style1D(Average1_pt,"pt (GeV)"," ");
 style1D(hgenMuon1_eta,"pseudorapidity mu","# events ");
 style1D(hgenMuon1_pt,"pt mu (GeV)","# events ");
 style1D(hMuon1_pt,"pt mu (GeV)","# events ");
 style1D(hMuon1_eta,"pseudorapidity mu","# events ");
 //hMuon1_eta->Sumw2(kTrue);
 //hgenMuon1_eta->Sumw2(kTrue);
     TCanvas *c1 =new TCanvas("c1","c1",800,1600);
     c1->Divide(2,4);
     c1->cd(1);
     hMuon1_eta->Draw();
     c1->cd(2);
     hgenMuon1_eta->Draw();
     c1->cd(3);
     hMuon1_pt->Draw();
     c1->cd(4);
     hgenMuon1_pt->Draw();
     c1->cd(5);
     if(TEfficiency::CheckConsistency(*hMuon1_eta,*hgenMuon1_eta))
       {
	 TEfficiency* etaEff= new TEfficiency(*hMuon1_eta,*hgenMuon1_eta);
	 //TGraphAsymmErrors* g= etaEff->CreateGraph();
	 etaEff->Draw();
       }
     c1->cd(6);
     Average1_eta->Add(hMuon1_eta,hgenMuon1_eta,-1.0,1.0);
     Average1_eta->Draw("E1");
     c1->cd(7);
     if(TEfficiency::CheckConsistency(*hMuon1_pt,*hgenMuon1_pt))
       {
	 TEfficiency* ptEff= new TEfficiency(*hMuon1_pt,*hgenMuon1_pt);
	 //TGraphAsymmErrors* g= ptEff->CreateGraph();
	 ptEff->Draw();
       }
     c1->cd(8);
     Average1_pt->Add(hMuon1_pt,hgenMuon1_pt,-1.0,1.0);
     Average1_pt->Draw("E1");
     c1->SaveAs("MuEffonlyLeptonCutsAndgenCuts.pdf");
    
   }

 if(which ==7)
   {
     TH1F* Average_eta = new TH1F("Average_eta","average (eta)",100,-3,3);
     TH1F* Average_pt = new TH1F("Average_pt","average (pt)",80,0,1000);
     TH1F* hgenElectron_eta = new TH1F("hgenElectron_eta","pseudorapidity of gen. electron",100,-3,3);
     TH1F* hElectron_eta = new TH1F("hElectron_eta","pseudorapidity of mu with kin. cuts and vetoes",100,-3,3);
     TH1F* hgenElectron_pt = new TH1F("hgenElectron_pt","Pt of gen. electron",80,0,1000);
     TH1F* hElectron_pt = new TH1F("hElectron_pt","Pt of electron with kin. cuts and vetoes",80,0,1000);

     vector<int> events ={};
     for(int  i=0;i<howmany;i++)
       {events.push_back(i);}

     getgenX_eta_pt_wv(hgenElectron_eta,hgenElectron_pt,WWelectron,11, 24,leptonSelection_tight,11);
 //missing W -> mu
     getgenX_eta_pt_wv(hgenElectron_eta,hgenElectron_pt,Wmisselectron,11,39,leptonSelection_tight,11);
 //missing W -> tau -> mu
     getgenX_eta_pt_wv(hgenElectron_eta,hgenElectron_pt,TAUelectron,15,39,leptonSelection_tight,11);
 //W->tau->e
     getgenX_eta_pt_wv(hgenElectron_eta,hgenElectron_pt,WTAUelectron,15,24,leptonSelection_tight,11);
  
 getX_eta_pt(hElectron_eta,hElectron_pt,howmany,11,leptonSelection_tight,leptonSelection_loose);
 style1D(Average_eta,"pseudorapidity"," ");
 style1D(Average_pt,"pt (GeV)"," ");
 style1D(hgenElectron_eta,"pseudorapidity el","# events ");
 style1D(hgenElectron_pt,"pt el (GeV)","# events ");
 style1D(hElectron_pt,"pt el (GeV)","# events ");
 style1D(hElectron_eta,"pseudorapidity el","# events ");
 //hElectron_eta->Sumw2(kTrue);
 //hgenElectron_eta->Sumw2(kTrue);
     TCanvas *c =new TCanvas("c","c",800,1600);
     c->Divide(2,4);
     c->cd(1);
     hElectron_eta->Draw();
     c->cd(2);
     hgenElectron_eta->Draw();
     c->cd(3);
     hElectron_pt->Draw();
     c->cd(4);
     hgenElectron_pt->Draw();
     c->cd(5);
     if(TEfficiency::CheckConsistency(*hElectron_eta,*hgenElectron_eta))
       {
	 TEfficiency* etaEff= new TEfficiency(*hElectron_eta,*hgenElectron_eta);
	 //TGraphAsymmErrors* g= etaEff->CreateGraph();
	 etaEff->Draw();
       }
     c->cd(6);
     Average_eta->Add(hElectron_eta,hgenElectron_eta,-1.0,1.0);
     Average_eta->Draw("E1");
     c->cd(7);
     if(TEfficiency::CheckConsistency(*hElectron_pt,*hgenElectron_pt))
       {
	 TEfficiency* ptEff= new TEfficiency(*hElectron_pt,*hgenElectron_pt);
	 //TGraphAsymmErrors* g= ptEff->CreateGraph();
	 ptEff->Draw();
       }
     c->cd(8);
     Average_pt->Add(hElectron_pt,hgenElectron_pt,-1.0,1.0);
     Average_pt->Draw("E1");
     // c->SaveAs("ElEff.pdf");


 TH1F* Average1_eta = new TH1F("Average1_eta","average (eta)",100,-3,3);
     TH1F* Average1_pt = new TH1F("Average1_pt","average (pt)",80,0,1000);
     TH1F* hgenElectron1_eta = new TH1F("hgenElectron1_eta","pseudorapidity of gen. electron",100,-3,3);
     TH1F* hElectron1_eta = new TH1F("hElectron1_eta","pseudorapidity of mu with kin. cuts and vetoes",100,-3,3);
     TH1F* hgenElectron1_pt = new TH1F("hgenElectron1_pt","Pt of gen. electron",80,0,1000);
     TH1F* hElectron1_pt = new TH1F("hElectron1_pt","Pt of electron with kin. cuts and vetoes",80,0,1000);

    

     getgenX_eta_pt_wv(hgenElectron1_eta,hgenElectron1_pt,WWelectron,11, 24,leptonSelection_tight,11);
 //missing W -> mu
     getgenX_eta_pt_wv(hgenElectron1_eta,hgenElectron1_pt,Wmisselectron,11,39,leptonSelection_tight,11);
 //missing W -> tau -> mu
     getgenX_eta_pt_wv(hgenElectron1_eta,hgenElectron1_pt,TAUelectron,15,39,leptonSelection_tight,11);
 //W->tau->e
     getgenX_eta_pt_wv(hgenElectron1_eta,hgenElectron1_pt,WTAUelectron,15,24,leptonSelection_tight,11);
 getX_eta_pt_onlyLeptonCuts(hElectron1_eta,hElectron1_pt,howmany,11,leptonSelection_tight,leptonSelection_loose);
 style1D(Average1_eta,"pseudorapidity"," ");
 style1D(Average1_pt,"pt (GeV)"," ");
 style1D(hgenElectron1_eta,"pseudorapidity mu","# events ");
 style1D(hgenElectron1_pt,"pt mu (GeV)","# events ");
 style1D(hElectron1_pt,"pt mu (GeV)","# events ");
 style1D(hElectron1_eta,"pseudorapidity mu","# events ");
 
     TCanvas *c1 =new TCanvas("c1","c1",800,1600);
     c1->Divide(2,4);
     c1->cd(1);
     hElectron1_eta->Draw();
     c1->cd(2);
     hgenElectron1_eta->Draw();
     c1->cd(3);
     hElectron1_pt->Draw();
     c1->cd(4);
     hgenElectron1_pt->Draw();
     c1->cd(5);
     if(TEfficiency::CheckConsistency(*hElectron1_eta,*hgenElectron1_eta))
       {
	 TEfficiency* etaEff= new TEfficiency(*hElectron1_eta,*hgenElectron1_eta);
	 //TGraphAsymmErrors* g= etaEff->CreateGraph();
	 etaEff->Draw();
       }
     c1->cd(6);
     Average1_eta->Add(hElectron1_eta,hgenElectron1_eta,-1.0,1.0);
     Average1_eta->Draw("E1");
     c1->cd(7);
     if(TEfficiency::CheckConsistency(*hElectron1_pt,*hgenElectron1_pt))
       {
	 TEfficiency* ptEff= new TEfficiency(*hElectron1_pt,*hgenElectron1_pt);
	 //TGraphAsymmErrors* g= ptEff->CreateGraph();
	 ptEff->Draw();
       }
     c1->cd(8);
     Average1_pt->Add(hElectron1_pt,hgenElectron1_pt,-1.0,1.0);
     Average1_pt->Draw("E1");
     // c1->SaveAs("ElEffonlyLeptonCuts.pdf");
    
   }

 // test getKinematicsFromGeneratedEvents
 if(which==8)
   {
     vector<int> events ={};
     for(int  i=0;i<howmany;i++)
       {events.push_back(i);}

     TH1F* histo1 = new TH1F("histo1"," pseudorapidity",80,-3,3);
     TH1F* histo2 = new TH1F("histo2","pt",100,0,1000);

     TH1F* histo3 = new TH1F("histo3"," pseudorapidity",80,-3,3);
     TH1F* histo4 = new TH1F("histo4","pt",100,0,1000);
     cout<<WWmuon.size()<< endl;
     cout<<WWtauon.size()<<endl;
     cout<<Wmissmuon.size()<< endl;
     getKinematicsFromGeneratedEvents(histo1,histo2,WWmuon,13);
     getKinematicsFromGeneratedEvents(histo1,histo2,WWtauon,13);
     getKinematicsFromGeneratedEvents(histo1,histo2,Wmissmuon,13);
     getKinematicsFromGeneratedEvents(histo3,histo4,events,11);
     TCanvas* c1=new TCanvas("c1","c1",1600,1600);
     c1->Divide(2,2);
     c1->cd(1);
     histo1->Draw();
     c1->cd(2);
     histo2->Draw();
     c1->cd(3);
     histo3->Draw();
     c1->cd(4);
     histo4->Draw();
   }


}




//------------------------------------------------------------------------------
//-----------------place for user functions-------------------------------------

vector<int> compareLists(vector<int> list1, vector<int> list2)
{
  vector<int> result={};
  for(int i=0;i<list1.size();i++)
    {
      if(isEventInList(list1.at(i), list2)==0)
	{result.push_back(list1.at(i));}
    }
      return result;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


void get_pdgId(vector<int> event, string name_output_file)
{
  //write the pdgId of event in file "name_output_file"
  ofstream file;
  file.open(name_output_file,ios::ate);
  //get pdgId

 for(int h =0;h<event.size();h++)
   {
     t12->GetEntry(event.at(h));
     for(int i=0;i<80;i++)
       {file <<"-" ;}
     file << endl;
     for(int i=0;i<80;i++)
       {file <<"-" ;}
     file << endl;
     file<< "event " << event.at(h) << endl;
     file << genParticle_N << " = number of particles" << endl;
     file << endl;


	  //loop over particles in event
	  for(int k =0;k<genParticle_N ;k++)
	    {
	      for(int i=0;i<80;i++)
		{file <<"-" ;}
	      file << endl;
	      file << "pdgId " << genParticle_pdgId->at(k) << endl;
	      for(int i=0;i<80;i++)
		{file <<"-" ;}
	      file << endl;
	      file <<"# of mother particles " << genParticle_nMoth->at(k)<<endl;
	   
	      if(genParticle_nMoth->at(k) != 0)
		{
		  vector<int> tmp_moth =genParticle_mother->at(k);
		  
		  for(int i=0;i<tmp_moth.size();i++)
		    {
		      file <<tmp_moth.at(i)<< " , ";
		    }
		  file << " size of vector " << tmp_moth.size()<<endl;
		  
		  file << endl;
		}
	      file <<"# of daughter particles " << genParticle_nDau->at(k)<<endl;
	      if(genParticle_nDau->at(k) != 0)
		{
	     
		  vector<int> tmp_dau =genParticle_dau->at(k);
		 
		  for(int i=0;i<tmp_dau.size();i++)
		    {
		      file << tmp_dau.at(i)<< " , ";
		    }
		  file << " size of vector " << tmp_dau.size()<<endl;
	
		}
	      file << endl;
	    }

 for(int i=0;i<80;i++)
   {file <<"-" ;}
 file << endl;
 for(int i=0;i<80;i++)
   {file <<"-" ;}
 file << endl;
   }
 file.close();
}
// //-------------------------------------------------------------------------------------------------------------------------------------------------------------

void getInvariantWmass(TH1F* histo,vector<int> events, int pdgId_lepton, int pdgId_mother)
{


for(int i=0;i<events.size();i++)
   {
     t12->GetEntry(events.at(i));
     TLorentzVector lepton;
     TLorentzVector neutrino;
     for(int ii=0;ii<genParticle_N;ii++)
       {
	 if(TMath::Abs(genParticle_pdgId->at(ii))== pdgId_lepton)
	   {
	     vector<int> l_moth = genParticle_mother->at(ii);
	     for(int iii=0;iii<l_moth.size();iii++)
	       {
		 if(TMath::Abs(l_moth.at(iii))==pdgId_mother)
		   {
		     lepton.SetPx(genParticle_px->at(ii));
		     lepton.SetPy(genParticle_py->at(ii));
		     lepton.SetPz(genParticle_pz->at(ii));
		     lepton.SetE(genParticle_e->at(ii));
		   }
	       }
	   }
	 if(TMath::Abs(genParticle_pdgId->at(ii))== (pdgId_lepton +1))
	   {
	     vector<int> n_moth = genParticle_mother->at(ii);
	     for(int iii=0;iii<n_moth.size();iii++)
	       {
		 if(TMath::Abs(n_moth.at(iii))==pdgId_mother)
		   {
		     neutrino.SetPx(genParticle_px->at(ii));
		     neutrino.SetPy(genParticle_py->at(ii));
		     neutrino.SetPz(genParticle_pz->at(ii));
		     neutrino.SetE(genParticle_e->at(ii));
		   }
	       }
	   }
       }
     TLorentzVector Wboson= lepton +neutrino;
     histo->Fill(Wboson.M());

   }

}
// --------------------------------------------------------------------------------
// -------------------------------------------------------------------------------


void style1D(TH1F *histo, TString nameXaxis, TString nameYaxis, Double_t offset =1.2)
{
  histo->GetXaxis()->SetTitle(nameXaxis);
  histo->GetYaxis()->SetTitle(nameYaxis);
  histo->GetXaxis()->SetTitleOffset(offset);
  histo->GetYaxis()->SetTitleOffset(offset);
  histo->GetXaxis()->CenterTitle();
  histo->GetYaxis()->CenterTitle();

}
// ------------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool isEventInList(int event, vector<int> listOfEvents)
{
  for(int i=0;i<listOfEvents.size();i++)
    {
      if(listOfEvents.at(i)== event)
	return 1;
    }
  return 0;
}
// ------------------------------------------------------------------------------
// -----------------------------------------------------------------------------
vector<int> getTauBranchingRatio(vector<int> events)
{
  vector<int> BRatio={0,0};
  vector<int> help={};
  vector<int> help2={};
  int isRight=0;
  int isEl=0;
  int isMuon=0;
  for(int i=0;i<events.size();i++)
    {
      t12->GetEntry(events.at(i));
      vector<int> tau =findParticle(events.at(i),15);
      for(int k=0; k<tau.size();k++)
	{
	  vector<int> dau= getDaughterPdgId(events.at(i),tau.at(k));	
	  
        if(rightMother(events.at(i),tau.at(k))==1 or rightMother(events.at(i),tau.at(k))==2)
	   {
	      for(int m=0;m<dau.size();m++)
		{
		  if(TMath::Abs(dau.at(m))== 16)
		    {isRight +=1;}
		  if(TMath::Abs(dau.at(m))== 11)
		    {isEl +=1;}
		  if(TMath::Abs(dau.at(m))== 13)
		    {isMuon+=1;}
		}
	      
	    }
	}
      if(isRight>0 and isEl>0)
	{BRatio[0]+=1;}
      if(isRight>0 and isMuon>0)
	{BRatio[1]+=1;}
      isRight=0;
      isEl=0;
      isMuon=0;
	
    }

  return BRatio;
}

// ------------------------------------------------------------------------------
// -----------------------------------------------------------------------------


vector<int> getTauBranchingRatio(vector<int> events, int pdgId_lepton, int pdgId_mother)
{
  vector<int> help={};
 vector<int> bratioTau={0,0};
 int case1=0;

for(int i=0;i<events.size();i++)
   {
     t12->GetEntry(events.at(i));
     for(int ii=0;ii<genParticle_N;ii++)
       {
	 if(TMath::Abs(genParticle_pdgId->at(ii))== pdgId_lepton)
	   {
	     vector<int> l_moth = genParticle_mother->at(ii);
	     for(int iii=0;iii<l_moth.size();iii++)
	       {
	     	 if(TMath::Abs(l_moth.at(iii))!=pdgId_mother and TMath::Abs(l_moth.at(iii)) != pdgId_lepton)
	     	   {case1 +=1;}
	       }
		   
	     if(case1>0)
	       continue;
	     vector<int> l_dau =genParticle_dau->at(ii);
	     for(int k=0;k<l_dau.size();k++)
	       {
		 if(TMath::Abs(l_dau.at(k))== 11)
		   {
		     for(int kk=0;kk<l_dau.size();kk++)
		       {if(TMath::Abs(l_dau.at(kk))==12)
			   {bratioTau[0]+=1; help.push_back(i);}
		       }
		   }
		 if(TMath::Abs(l_dau.at(k))==13)
		   {for(int kk=0;kk<l_dau.size();kk++)
		       {
			 if(TMath::Abs(l_dau.at(kk))==14)
			   {bratioTau[1]+=1;}
		       }
		   }
		
	       }
	   }
	 case1 =0;
       }
   }
get_pdgId(help, "tests/debug3.txt");
 cout<< help.size()<< endl;
 cout<<" is 277 in this list " << isEventInList(277, help)<< endl;
 cout<<" is 269 in this list " << isEventInList(269, help)<< endl;
 return bratioTau;
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------



void getgenX_eta_pt(TH1F* histo1,TH1F* histo2 ,vector<int> events, int pdgId_lepton, int pdgId_mother ,vector<vector<double> >leptonSelection , int X)
{

int case1 =0;
int case2=0;
for(int i=0;i<events.size();i++)
   {
     t12->GetEntry(events.at(i));
     TLorentzVector lepton;
     TLorentzVector neutrino;
     TLorentzVector lepton1;
     for(int ii=0;ii<genParticle_N;ii++)
       {
	 if(TMath::Abs(genParticle_pdgId->at(ii))== pdgId_lepton)
	   {
	     vector<int> l_moth = genParticle_mother->at(ii);
	     for(int iii=0;iii<l_moth.size();iii++)
	       {
		 if(TMath::Abs(l_moth.at(iii))==pdgId_mother)
		   {
		     Double_t pt =genParticle_pt->at(ii);
		     Double_t eta =genParticle_eta->at(ii);
		     Double_t phi =genParticle_phi->at(ii);
		     Double_t e = genParticle_e->at(ii);
		     lepton.SetPtEtaPhiE(pt,eta,phi,e);
		   }
	       }
	     if(pdgId_lepton == 15)
	       {
		 vector<int> l_moth = genParticle_mother->at(ii);
		 for(int iii=0;iii<l_moth.size();iii++)
		   {
		     if(TMath::Abs(l_moth.at(iii))!=pdgId_mother and TMath::Abs(l_moth.at(iii)) != pdgId_lepton)
		       {case1 +=1;}
		   }
		   
		 if(case1>0)
		   continue;
		 vector<int> l_dau =genParticle_dau->at(ii);
		 for(int k=0;k<l_dau.size();k++)
		   {
		     if(TMath::Abs(l_dau.at(k))== 11)
		       {
			 for(int kk=0;kk<l_dau.size();kk++)
			   {if(TMath::Abs(l_dau.at(kk))==12)
			       {
				 Double_t pt =genParticle_pt->at(ii);
				 Double_t eta =genParticle_eta->at(ii);
				 Double_t phi =genParticle_phi->at(ii);
				 Double_t e = genParticle_e->at(ii);
				 lepton1.SetPtEtaPhiE(pt,eta,phi,e);
			       }
			   }
		       }
		     if(TMath::Abs(l_dau.at(k))==13)
		       {for(int kk=0;kk<l_dau.size();kk++)
			   {
			     if(TMath::Abs(l_dau.at(kk))==14)
			       {
				 Double_t pt =genParticle_pt->at(ii);
				 Double_t eta =genParticle_eta->at(ii);
				 Double_t phi =genParticle_phi->at(ii);
				 Double_t e = genParticle_e->at(ii);
				 lepton1.SetPtEtaPhiE(pt,eta,phi,e);
				 case2+=1;
			       }
			   }
		       }

		   }
	       }
	   }
	 if(TMath::Abs(genParticle_pdgId->at(ii))== (pdgId_lepton +1))
	   {
	     vector<int> n_moth = genParticle_mother->at(ii);
	     for(int iii=0;iii<n_moth.size();iii++)
	       {
		 if(TMath::Abs(n_moth.at(iii))==pdgId_mother)
		   {
		     Double_t pt = genParticle_pt->at(ii);
		     Double_t phi =genParticle_phi->at(ii);
		     Double_t eta =genParticle_eta->at(ii);
		     Double_t e = genParticle_e->at(ii);
		     neutrino.SetPtEtaPhiE(pt,eta,phi,e);
		   }
	       }
	   }
       }
     TLorentzVector Wboson= lepton +neutrino;
     if(pdgId_lepton == 11)
       {
	 // leptonic kinematic contraints 
	 if((TMath::Abs(lepton.Eta())>leptonSelection[2][0]) or ((leptonSelection[2][1]<=TMath::Abs(lepton.Eta()) and (TMath::Abs(lepton.Eta())<=leptonSelection[2][2]))))
	   {continue;}
	 if(lepton.Pt()<=leptonSelection[0][0])
	   {continue;}
	 // contraints on Etmiss i.e. the transverse momentum of the neutrin
	 // (taking neutrino masses to be zero)
	 if(neutrino.Pt()<=80)
	   {continue;}
	 if(X == 24)
	   {
	     histo2->Fill(Wboson.Pt());
	     histo1->Fill(Wboson.Eta());
	   }
	 if(X==11)
	   {
	     histo1->Fill(lepton.Eta());
	     histo2->Fill(lepton.Pt());
	   }
	 if(X==12)
	   {
	     histo1->Fill(neutrino.Eta());
	     histo2->Fill(neutrino.Pt());
	   }
	 else if(X!=12 and X!=11 and X!=24)
	   {cout<<"in getgenX_eta_pt, X is not valid"<< endl; }
       }
     if(pdgId_lepton == 13)
       {

	 if(TMath::Abs(lepton.Eta())> leptonSelection[3][0])
	   {continue;}
	 if(lepton.Pt()<=leptonSelection[1][0])
	   {continue;}
	 // contraints on Etmiss i.e. the transverse momentum of the neutrin
	 // (taking neutrino masses to be zero)
	 if(neutrino.Pt()<=40)
	   {continue;}
	 if(X == 24)
	   {
	     histo2->Fill(Wboson.Pt());
	     histo1->Fill(Wboson.Eta());
	   }
	 if(X==13)
	   {
	     histo1->Fill(lepton.Eta());
	     histo2->Fill(lepton.Pt());
	   }
	 if(X==14)
	   {
	     histo1->Fill(neutrino.Eta());
	     histo2->Fill(neutrino.Pt());
	   }
	 else if(X!=14 and X!=13 and X!=24)
	   {cout<<"in getgenX_eta_pt, X is not valid"<< endl;}
       }
     if(pdgId_lepton == 15 and case2==0)
       {
	 if(TMath::Abs(lepton1.Eta())> leptonSelection[2][0] or (leptonSelection[2][1]<=lepton1.Eta()and lepton1.Eta()<=leptonSelection[2][2]))
	   {continue;}
	 if(lepton1.Pt()<=leptonSelection[0][0])
	   {continue;}
	 // contraints on Etmiss i.e. the transverse momentum of the neutrin
	 // (taking neutrino masses to be zero)
	 if(neutrino.Pt()<=80)
	   {continue;}
	 if(X == 24)
	   {
	     histo2->Fill(Wboson.Pt());
	     histo1->Fill(Wboson.Eta());
	   }
	 if(X==11 or X ==13)
	   {
	     histo1->Fill(lepton1.Eta());
	     histo2->Fill(lepton1.Pt());
	   }
	 if(X==15)
	   {
	     histo1->Fill(lepton.Eta());
	     histo2->Fill(lepton.Pt());
	   }
	 if(X==16)
	   {
	     histo1->Fill(neutrino.Eta());
	     histo2->Fill(neutrino.Pt());
	   }


       }
     if(pdgId_lepton == 15 and case2>0)
       {
	 if(TMath::Abs(lepton1.Eta())> leptonSelection[3][0])
	   {continue;}
	 if(lepton1.Pt()<=leptonSelection[1][0])
	   {continue;}
	 // contraints on Etmiss i.e. the transverse momentum of the neutrino
	 // (taking neutrino masses to be zero)
	 if(neutrino.Pt()<=40)
	   {continue;}
	 if(X == 24)
	   {
	     histo2->Fill(Wboson.Pt());
	     histo1->Fill(Wboson.Eta());
	   }
	 if(X==11 or X ==13)
	   {
	     histo1->Fill(lepton1.Eta());
	     histo2->Fill(lepton1.Pt());
	   }
	 if(X==15)
	   {
	     histo1->Fill(lepton.Eta());
	     histo2->Fill(lepton.Pt());
	   }
	 if(X==16)
	   {
	     histo1->Fill(neutrino.Eta());
	     histo2->Fill(neutrino.Pt());
	   }
	 else if(X!=24 and X!=11 and X!=13 and X!=15 and X!=16)
	   {cout<<"in getgenX_eta_pt, X is not valid"<< endl; }

       }
     case1 =0;
     case2=0;
   }

 }

//-------------------------------------------------------------------------------
//----------------------------------------------------------------------------

void getKinematicsFromGeneratedEvents(TH1F* histo1,TH1F* histo2, vector<int> events, int pdgId)
{
  int help=0;
  int help1=0;
  vector<int> help2={};
  for(int i=0;i<events.size();i++)
    {
      vector<int> particleNum = findParticle(events.at(i),pdgId);
      if(particleNum.size()>0)
	{help+=1;}
      if(particleNum.size()==0)
	{help1+=1; help2.push_back(events.at(i));}
      for(int p=0;p<particleNum.size();p++)
	{
	  if(rightMother(events.at(i),particleNum.at(p))==0)
	    {continue;}
	  else
	    {  
	      TLorentzVector v = getLorentzVector(events.at(i),particleNum.at(p));
	      histo1->Fill(v.Eta());
	      histo2->Fill(v.Pt());
	    }
	}
    }
  get_pdgId(help2,"debug.txt");
  cout<< help << endl;
  cout<< help1<<endl;
}

//-------------------------------------------------------------------------------
//----------------------------------------------------------------------------

// goes through the mother particles of particle number "particleNumber" 
//in event "event", if the mother is either a W Boson, a Graviton
// it returns 1 it returns 2 of mother is a tauon
//otherwise it returns zero.
int rightMother(int event, int particleNumber)
{
  t12->GetEntry(event);
  vector<int> pdgIdMother =genParticle_mother->at(particleNumber);
  int numberOfMotherP = pdgIdMother.size();
  int rightMum=0;
  for(int i=0;i<numberOfMotherP;i++)
    {
      if(TMath::Abs(pdgIdMother.at(i))==24)
	{rightMum= 1;}
      if(TMath::Abs(pdgIdMother.at(i))==39)
	{rightMum= 1;}
      if(TMath::Abs(pdgIdMother.at(i))==15)
	{rightMum= 2;}
    }
  if(rightMum==1)
    return 1;
  if(rightMum==2)
    return 2;
  else
    return 0;
}

 
//-------------------------------------------------------------------------------
//----------------------------------------------------------------------------

// goes through all particles in event
// and returns a list with the numbers of the particles with pdgId
vector<int> findParticle(int event, int pdgId)
{
  vector<int> particleNumbers={};
  t12->GetEntry(event);
  for(int count=0;count<genParticle_N;count++)
    {
      if(TMath::Abs(genParticle_pdgId->at(count))== pdgId)
	{particleNumbers.push_back(count);}
    }
  return particleNumbers;
}
//---------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
vector<int> getDaughterPdgId(int event, int numParticle)
{
  vector<int> daughter={};
  t12->GetEntry(event);
  daughter= genParticle_dau->at(numParticle);
  return daughter;
}
//-------------------------------------------------------------------------------
//----------------------------------------------------------------------------

TLorentzVector getLorentzVector(int event, int particleNumber)
{
  TLorentzVector V;
  t12->GetEntry(event);
 Double_t pt =genParticle_pt->at(particleNumber);
 Double_t eta =genParticle_eta->at(particleNumber);
 Double_t phi =genParticle_phi->at(particleNumber);
 Double_t e = genParticle_e->at(particleNumber);
 V.SetPtEtaPhiE(pt,eta,phi,e);

 return V;
}

 
//-------------------------------------------------------------------------------
//----------------------------------------------------------------------------


void getgenX_eta_pt_wv(TH1F* histo1,TH1F* histo2 ,vector<int> events, int pdgId_lepton, int pdgId_mother ,vector<vector<double> >leptonSelection , int X)
{

int case1 =0;
int case2=0;
for(int i=0;i<events.size();i++)
   {
     t12->GetEntry(events.at(i));
     TLorentzVector lepton;
     TLorentzVector neutrino;
     TLorentzVector lepton1;
     for(int ii=0;ii<genParticle_N;ii++)
       {
	 if(TMath::Abs(genParticle_pdgId->at(ii))== pdgId_lepton)
	   {
	     vector<int> l_moth = genParticle_mother->at(ii);
	     for(int iii=0;iii<l_moth.size();iii++)
	       {
		 if(TMath::Abs(l_moth.at(iii))==pdgId_mother)
		   {
		     Double_t pt =genParticle_pt->at(ii);
		     Double_t eta =genParticle_eta->at(ii);
		     Double_t phi =genParticle_phi->at(ii);
		     Double_t e = genParticle_e->at(ii);
		     lepton.SetPtEtaPhiE(pt,eta,phi,e);
		   }
	       }
	     if(pdgId_lepton == 15)
	       {
		 vector<int> l_moth = genParticle_mother->at(ii);
		 for(int iii=0;iii<l_moth.size();iii++)
		   {
		     if(TMath::Abs(l_moth.at(iii))!=pdgId_mother and TMath::Abs(l_moth.at(iii)) != pdgId_lepton)
		       {case1 +=1;}
		   }
		   
		 if(case1>0)
		   continue;
		 vector<int> l_dau =genParticle_dau->at(ii);
		 for(int k=0;k<l_dau.size();k++)
		   {
		     if(TMath::Abs(l_dau.at(k))== 11)
		       {
			 for(int kk=0;kk<l_dau.size();kk++)
			   {if(TMath::Abs(l_dau.at(kk))==12)
			       {
				 Double_t pt =genParticle_pt->at(ii);
				 Double_t eta =genParticle_eta->at(ii);
				 Double_t phi =genParticle_phi->at(ii);
				 Double_t e = genParticle_e->at(ii);
				 lepton1.SetPtEtaPhiE(pt,eta,phi,e);
			       }
			   }
		       }
		     if(TMath::Abs(l_dau.at(k))==13)
		       {for(int kk=0;kk<l_dau.size();kk++)
			   {
			     if(TMath::Abs(l_dau.at(kk))==14)
			       {
				 Double_t pt =genParticle_pt->at(ii);
				 Double_t eta =genParticle_eta->at(ii);
				 Double_t phi =genParticle_phi->at(ii);
				 Double_t e = genParticle_e->at(ii);
				 lepton1.SetPtEtaPhiE(pt,eta,phi,e);
				 case2+=1;
			       }
			   }
		       }

		   }
	       }
	   }
	 if(TMath::Abs(genParticle_pdgId->at(ii))== (pdgId_lepton +1))
	   {
	     vector<int> n_moth = genParticle_mother->at(ii);
	     for(int iii=0;iii<n_moth.size();iii++)
	       {
		 if(TMath::Abs(n_moth.at(iii))==pdgId_mother)
		   {
		     Double_t pt = genParticle_pt->at(ii);
		     Double_t phi =genParticle_phi->at(ii);
		     Double_t eta =genParticle_eta->at(ii);
		     Double_t e = genParticle_e->at(ii);
		     neutrino.SetPtEtaPhiE(pt,eta,phi,e);
		   }
	       }
	   }
       }
     TLorentzVector Wboson= lepton +neutrino;
     if(pdgId_lepton == 11)
       {
	 if(X == 24)
	   {
	     histo2->Fill(Wboson.Pt());
	     histo1->Fill(Wboson.Eta());
	   }
	 if(X==11)
	   {
	     histo1->Fill(lepton.Eta());
	     histo2->Fill(lepton.Pt());
	   }
	 if(X==12)
	   {
	     histo1->Fill(neutrino.Eta());
	     histo2->Fill(neutrino.Pt());
	   }
	 else if(X!=12 and X!=11 and X!=24)
	   {cout<<"in getgenX_eta_pt, X is not valid"<< endl; }
       }
     if(pdgId_lepton == 13)
       {
	 if(X == 24)
	   {
	     histo2->Fill(Wboson.Pt());
	     histo1->Fill(Wboson.Eta());
	   }
	 if(X==13)
	   {
	     histo1->Fill(lepton.Eta());
	     histo2->Fill(lepton.Pt());
	   }
	 if(X==14)
	   {
	     histo1->Fill(neutrino.Eta());
	     histo2->Fill(neutrino.Pt());
	   }
	 else if(X!=14 and X!=13 and X!=24)
	   {cout<<"in getgenX_eta_pt, X is not valid"<< endl;}
       }
     if(pdgId_lepton == 15 and case2==0)
       {
	
	 if(X == 24)
	   {
	     histo2->Fill(Wboson.Pt());
	     histo1->Fill(Wboson.Eta());
	   }
	 if(X==11 or X ==13)
	   {
	     histo1->Fill(lepton1.Eta());
	     histo2->Fill(lepton1.Pt());
	   }
	 if(X==15)
	   {
	     histo1->Fill(lepton.Eta());
	     histo2->Fill(lepton.Pt());
	   }
	 if(X==16)
	   {
	     histo1->Fill(neutrino.Eta());
	     histo2->Fill(neutrino.Pt());
	   }


       }
     if(pdgId_lepton == 15 and case2>0)
       {
	
	 if(X == 24)
	   {
	     histo2->Fill(Wboson.Pt());
	     histo1->Fill(Wboson.Eta());
	   }
	 if(X==11 or X ==13)
	   {
	     histo1->Fill(lepton1.Eta());
	     histo2->Fill(lepton1.Pt());
	   }
	 if(X==15)
	   {
	     histo1->Fill(lepton.Eta());
	     histo2->Fill(lepton.Pt());
	   }
	 if(X==16)
	   {
	     histo1->Fill(neutrino.Eta());
	     histo2->Fill(neutrino.Pt());
	   }
	 else if(X!=24 and X!=11 and X!=13 and X!=15 and X!=16)
	   {cout<<"in getgenX_eta_pt, X is not valid"<< endl; }

       }
     case1 =0;
     case2=0;
   }

 }

//---------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
vector<vector<int> > generatedSemiLepEventClassification(int howmany)
{
vector<vector<int> > result(8);

 int GnachWW =0;
 int GnachWl =0;
 int GnachWhad=0;
 int Gnachlhad=0;
 int help_NumberW=0;
 int help_Numberlepton=0;

 for(int i=0;i<howmany;i++)
   {
     t12->GetEntry(i);
     for(int k=0;k<genParticle_N;k++)
       {
	 if(TMath::Abs(genParticle_pdgId->at(k))==39)
	   {
	     vector<int> GDaughter=genParticle_dau->at(k);
	     for(int l=0;l<GDaughter.size();l++)
	       {
		 if(TMath::Abs(GDaughter.at(l))==24)
		   {help_NumberW+=1;}
		 if(TMath::Abs(GDaughter.at(l))>=11 and TMath::Abs(GDaughter.at(l))<=18)
		   {help_Numberlepton+=1;}
	       }
	   }
       }
     if(help_NumberW ==2)
       {GnachWW +=1; result[0].push_back(i);}
     if(help_NumberW==1)
       {
	 if(help_Numberlepton>0)
	   {GnachWl +=1; result[2].push_back(i);}
	 else
	   {GnachWhad +=1;result[1].push_back(i);}
       }
     if(help_NumberW==0)
       {Gnachlhad+=1; result[3].push_back(i);}
     help_NumberW=0;
     help_Numberlepton=0;
   }
 cout<<"# of events with G-> WW "<< GnachWW << endl;
 cout<<"# of events with G-> Wl "<< GnachWl << endl;
 cout<<"# of events with G-> Whad "<< GnachWhad << endl;
 cout<<"# of events with G-> lhad "<< Gnachlhad << endl;
 int NumberOfEventsWithEl=0;
 int NumberOfEventsWithMu=0;
 int NumberOfEventsWithTau=0;

 //for G->WW and G->Whad search for daughters of W boson
 for(int i=0;i<2;i++)
   {
     for(int count1=0;count1<result[i].size();count1++)
       {
	 int event=result[i].at(count1);
	 vector<int> numW= findParticle(event,24);
	 for(int count2=0;count2<numW.size();count2++)
	   {
	     vector<int> dau = getDaughterPdgId(event,numW.at(count2));
	     for(int count3=0; count3<dau.size();count3++)
	       {
		 if(TMath::Abs(dau.at(count3))==11)
		   {result[4].push_back(event); NumberOfEventsWithEl+=1;}
		 if(TMath::Abs(dau.at(count3))==13)
		   {result[5].push_back(event); NumberOfEventsWithMu+=1;}
		 if(TMath::Abs(dau.at(count3))==15)
		   {result[6].push_back(event); NumberOfEventsWithTau+=1;}
	       }
	   }
       }

   }
 //for G->Wl and G->lhad search for daughters of G boson
 for(int i=2;i<4;i++)
   {
     for(int count1=0;count1<result[i].size();count1++)
       {
	 int event=result[i].at(count1);
	 vector<int> numW= findParticle(event,39);
	 for(int count2=0;count2<numW.size();count2++)
	   {
	     vector<int> dau= getDaughterPdgId(event,numW.at(count2));
	     for(int count3=0; count3<dau.size();count3++)
	       {
		 if(TMath::Abs(dau.at(count3))==11)
		   {result[4].push_back(event); NumberOfEventsWithEl+=1;}
		 if(TMath::Abs(dau.at(count3))==13)
		   {result[5].push_back(event); NumberOfEventsWithMu+=1;}
		 if(TMath::Abs(dau.at(count3))==15)
		   {result[6].push_back(event); NumberOfEventsWithTau+=1;}
	       }
	   }
       }

   }
 get_pdgId(result[2],"debug.txt");

 cout<<"# events with electrons in final state "<< NumberOfEventsWithEl<< endl; 
 cout<<"# events with muons in final state "<< NumberOfEventsWithMu<< endl; 
 cout<<"# events with tauons in final state "<< NumberOfEventsWithTau<< endl; 

 return result;
}
 



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//goes through generated events and
//fills the vectors with the eventnumber of:
//WWelectron = #W =2, one W decays semileptonic to e
//WWmuon = #W =2, one W decays semileptonic to mu
//WWtauon = #W =2, one W decays semileptonic to tau
//missingW.=#W <2 
vector<vector<int> > genDataEventSeparationSemileptonicWW(int howmany)
{
 vector<vector<int> > result(7);

 Int_t ca = 0;
 Int_t counter2=0;
 Int_t N_lep =0;
 Int_t N_had =0;
 Int_t N_semilep =0;
 Int_t N_WW_decay=0;
 Int_t N_Wmiss_decay =0;
 Int_t N_semilep_WW =0;
 Int_t N_semilep_Wmiss =0;
 Int_t N_had_WW =0;
 Int_t N_had_Wmiss=0;
 Int_t N_lep_WW =0;
 Int_t N_lep_Wmiss=0;
 cout << " the file has " << t12->GetEntries()<< "events" << endl;

 for(int event=0; event<howmany; event++)
    {
      t12->GetEntry(event);
         
	  for(int loop =0;loop<genParticle_N ;loop++)
	    {
	      if(TMath::Abs(genParticle_pdgId->at(loop)) == 24)
		{
		  //counter2 counts W Bosons in the decay
		  counter2 +=1;
		  vector<int> pD = genParticle_dau->at(loop);
		  for(int ld=0;ld<pD.size();ld++)
		    {
		      if(TMath::Abs(pD.at(ld))<=18 and TMath::Abs(pD.at(ld))>=11)
			{ ca +=1;
			  if(TMath::Abs(pD.at(ld))==11)
			    {result.at(1).push_back(event);}
			   if(TMath::Abs(pD.at(ld))==13)
			     {result.at(2).push_back(event);}
			  if(TMath::Abs(pD.at(ld))==15)
			    {result.at(3).push_back(event);}
			  
			}
		      if(TMath::Abs(pD.at(ld))==24)
			{// if there is a statement like W-> W do not count
			  // this as an extra W Boson
			  counter2 = counter2-1;
			}
		
		    }

		}
	    }
	  //make list with all events that are missing one or two W
	  if(counter2 ==1 or counter2 ==0)
	    {result.at(0).push_back(event);}
      //hadronic case
	  if(ca == 0)
	    {
	      N_had +=1;
	    }
      //semileptonic case
	  if(ca == 2)
	    {N_semilep +=1;}
      //leptonic case
	  if(ca ==4)
	    {N_lep +=1;}
	  else if(ca>4)
	    {cout <<"in event "<<event<<" the case specific. does not work.";
	      cout << endl << "ca =  " << ca << endl;
	    }
	  //decay with or without intermediate W in data
	  if(counter2==1)
	    {N_Wmiss_decay +=1;}
	  if(counter2 ==2)
	    {N_WW_decay+=1;
	    }
	  else if(counter2>2)
	    {cout << "event " << event << " has more than 2 W bosons " << endl;}
	  //how many decays with or without W are in which case
	  if(ca ==2 and counter2==2)
	    {N_semilep_WW +=1;}
	  if(ca==2 and counter2 ==1)
	    {N_semilep_Wmiss  +=1;}
	  if(ca==0 and counter2==2)
	    {N_had_WW +=1;}
	  if(ca==0 and counter2 ==1)
	    {N_had_Wmiss +=1;}
	  if(ca==4 and counter2==2)
	    {N_lep_WW +=1;}
	  if(ca==4 and counter2 ==1)
	    {N_lep_Wmiss +=1;}
	  else if(ca>2 or counter2>2 or counter2<0 or ca<0)
	    {cout << event << " is strange " <<endl;}
	  counter2 =0;
	  ca =0;
	  
    }	

     // which of the missing W decays into an electron, muon or tauon?
 vector <int> tmp  = result.at(0);

 for(int i=0;i<tmp.size();i++)
       {
	 t12->GetEntry(tmp.at(i));
	   for(int ii=0; ii<genParticle_N;ii++)
	     {
	       if(genParticle_pdgId->at(ii)== 39)
		 {
		   vector<int> gp_dau = genParticle_dau->at(ii);
		   for(int iii=0;iii<gp_dau.size();iii++)
		     {
		       if(TMath::Abs(gp_dau.at(iii))== 11)
			 {result.at(4).push_back(tmp.at(i));}
		       if(TMath::Abs(gp_dau.at(iii))== 13)
			 {result.at(5).push_back(tmp.at(i));}
		       if(TMath::Abs(gp_dau.at(iii))== 15)
			 {result.at(6).push_back(tmp.at(i));}
		     
		     }
		 }	 
	     }

       }

     cout<< "# of semileptonic events " << N_semilep<< endl;
     cout <<"# of leptonic events " << N_lep << endl;
     cout <<"# of hadronic events " << N_had << endl;
     cout <<"# of G decays with missing W " << N_Wmiss_decay << endl;
     cout <<"# of G -> WW decays " << N_WW_decay << endl;
     cout <<"# of semileptonic WW decays " << N_semilep_WW << endl;
     cout <<"# of semileptonic missing W decays "<< N_semilep_Wmiss << endl;
     cout <<"# of hadronic WW  decays " << N_had_WW << endl;
     cout <<"# of hadronic missing W decays " << N_had_Wmiss << endl;
     cout <<"# of lep WW  decays " << N_lep_WW << endl;
     cout <<"# of lep missing W decays " << N_lep_Wmiss << endl;
     return result;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

vector<vector<int> > selectTauEvents(vector<int> events,int pdgId_lepton, int pdgId_mother)
{   
 
 
 vector<int> bratioTau={0,0};
 vector<vector<int> > result(2);
 int case1=0;

for(int i=0;i<events.size();i++)
   {
     t12->GetEntry(events.at(i));
     for(int ii=0;ii<genParticle_N;ii++)
       {
	 if(TMath::Abs(genParticle_pdgId->at(ii))== pdgId_lepton)
	   {
	     vector<int> l_moth = genParticle_mother->at(ii);
	     for(int iii=0;iii<l_moth.size();iii++)
	       {
		 if(TMath::Abs(l_moth.at(iii))!=pdgId_mother and TMath::Abs(l_moth.at(iii)) != pdgId_lepton)
		   {case1 +=1;}
	       }
		   
	     if(case1>0)
	       continue;
	     vector<int> l_dau =genParticle_dau->at(ii);
	     for(int k=0;k<l_dau.size();k++)
	       {
		 if(TMath::Abs(l_dau.at(k))== 11)
		   {
		     for(int kk=0;kk<l_dau.size();kk++)
		       {if(TMath::Abs(l_dau.at(kk))==12)
			   {result.at(0).push_back(events.at(i));}
		       }
		   }
		 if(TMath::Abs(l_dau.at(k))==13)
		   {for(int kk=0;kk<l_dau.size();kk++)
		       {
			 if(TMath::Abs(l_dau.at(kk))==14)
			   {result.at(1).push_back(events.at(i));}
		       }
		   }
	       }
	   }
	 case1 =0;
       }
   }
 return result;
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

vector<int> EventSelectionElectron(int howmany, vector<vector<double> > leptonSelection_tight, vector<vector<double> > leptonSelection_loose)
{
  int N_loose =0;
  int N_tight =0;
  vector<int> event={};
  for(int i=0;i<howmany;i++)
    {
      t12->GetEntry(i);
      
      for(int p=0;p<el_N;p++)
	{
	 
	  if(isTightElectron(i,p,leptonSelection_tight)==1)
	    {
	      N_tight +=1;
	    }

	  if(isLooseElectron(i,p,leptonSelection_loose)==1)
	    {N_loose +=1;}
	}
      if(N_loose<=1 and N_tight==1)
	{
	  event.push_back(i);	  
	}
      
      N_loose =0;
      N_tight=0;
	
    }
  return event;
}
 
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


vector<int> EventSelectionMuon(int howmany, vector<vector<double> > leptonSelection_tight, vector<vector<double> > leptonSelection_loose)
{

 int N_loose =0;
 int N_tight =0;
 vector<int> event={};

 for(int i=0;i<howmany;i++)
   {
     t12->GetEntry(i);
	  for(int p=0;p<mu_N;p++)
	    {
	      if(isTightMuon(i,p,leptonSelection_tight)==1)
	    	{N_tight +=1;}
	      if(isLooseMuon(i,p,leptonSelection_loose)==1)
	    	{N_loose +=1;}
	    }
	  if(N_loose<=1 and N_tight ==1)
	    {
	      event.push_back(i);
	    }   
	
	  N_loose=0;
	  N_tight=0;
	   
   }
 return event;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int isTightMuon(int event, int p, vector<vector<double> >tight)
{
 bool MuonProp_t=0;
 bool MuonKin_t=0;
 double MuonIso_t=0;
 t12->GetEntry(event);
 MuonKin_t = (mu_pt->at(p)>tight[1][0])and ( TMath::Abs(mu_eta->at(p))<tight[3][0]);
 MuonProp_t = (mu_isHighPtMuon->at(p)==1) and (mu_isTightMuon->at(p) == 1);
 MuonIso_t=mu_pfRelIso->at(p);
	     	     

 if((MuonProp_t and MuonKin_t) == 1 and MuonIso_t <0.1)
   {return 1;}
 else
   {return 0;}

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int isLooseMuon(int event, int p, vector<vector<double> >loose)
{
  bool MuonProp_l=0;
  bool MuonKin_l=0;
  double MuonIso_l=0;
  t12->GetEntry(event);
  MuonProp_l = (mu_isHighPtMuon->at(p)==1) and(mu_isLooseMuon->at(p)==1);
  MuonKin_l = (mu_pt->at(p)>loose[1][0])and (TMath::Abs(mu_eta->at(p))<2.4);
  
  //pfRelIso is probably the right parameter since it is:
  //pfRelIso =(trackIso+photonIso+neutralHadIso+chargedHadIso)/muPt
  if((MuonProp_l and MuonKin_l) == 1 and MuonIso_l<0.1)
    {return 1;}
  else
    {return 0;}

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int isTightElectron(int event, int p, vector<vector<double> >  tight)
{
 bool ElEta_t=0;
 bool ElPt_t=0;
 double ElIso_t=0;
 t12->GetEntry(event);
 ElEta_t=(TMath::Abs(el_eta->at(p))<tight[2][0] and TMath::Abs(el_eta->at(p))>tight[2][2]) or (TMath::Abs(el_eta->at(p))<tight[2][1]);
 ElPt_t= el_pt->at(p)>tight[0][0];
 //ElIso_t= (el_pfRelIso->at(p))*el_pt->at(p);
 ElIso_t = el_trackIso->at(p);
 if((ElEta_t and ElPt_t)==1 and ElIso_t<5 and el_isHeep51Electron->at(p)==1)
   {
     return 1;
   }
 else 
   {
     return 0;	 
   }

}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int isLooseElectron(int event, int p, vector<vector<double> >loose)
{
 bool ElEta=0;
 bool ElPt=0;
 double ElIso=0;
 bool ElHeep6addition=0;
 t12->GetEntry(event);
 ElEta=(TMath::Abs(el_eta->at(p))<loose[2][0] and TMath::Abs(el_eta->at(p))>loose[2][2]) or (TMath::Abs(el_eta->at(p))<loose[2][1]);
 ElPt= el_pt->at(p)>loose[0][0];
 //ElIso= (el_pfRelIso->at(p))*el_pt->at(p);
 ElIso = el_trackIso->at(p);
 if(TMath::Abs(el_eta->at(p))<1.4442)
   {
     if(el_hOverE->at(p)<(1/double(el_e->at(p)+ 0.05)))
       {ElHeep6addition =1;}
   }
 if(TMath::Abs(el_eta->at(p))>1.566)
   {
     if(el_hOverE->at(p)<(5/double(el_e->at(p)+0.05)))
       {ElHeep6addition=1;}
   }
 if((ElEta and ElPt)==1 and ElIso<5 and el_isHeep51Electron->at(p)==1 and ElHeep6addition ==1)
   {
     return 1;
   }
 else 
   {
     return 0;	 
   }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int isRightAK8jet(int event,int p)
{
  t12->GetEntry(event);
  if(jetAK8_pt->at(p)> 200 and TMath::Abs(jetAK8_eta->at(p))<2.4)
    {return 1;}
  else
    {return 0;}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
TLorentzVector recNeutrino(Double_t MET,Double_t MET_phi ,TLorentzVector lepton)
{
  Double_t  M_W= 80.42;
  Double_t pz_nu =0;
  Double_t phi= lepton.Phi();
  Double_t pt= lepton.Pt();
  Double_t pz = lepton.Pz();
  Double_t E= lepton.E();
  Double_t x = pow(M_W,2)/2.0 + TMath::Cos(phi-MET_phi)*MET*pt;
  Double_t b = x*pz*2/double(pow(E,2)-pow(pz,2));
  Double_t c = (pow(E,2)*pow(MET,2)-pow(x,2))/double(pow(E,2)-pow(pz,2));
  Double_t y= pow(b,2)/4.0-c;
  TLorentzVector neutrino;


  if(y<0)
    {
      pz_nu = b/2.0;
    }
  if(y>0)
    {
      Double_t a1= b/2.0 + TMath::Sqrt(y);
      Double_t a2 = b/2.0 - TMath::Sqrt(y);
      if(TMath::Abs(a1)>TMath::Abs(a2))
	pz_nu= a2;
      else
	pz_nu = a1;
    }
  neutrino.SetE(TMath::Sqrt(pow(MET,2)+ TMath::Sqrt(pow(pz_nu,2))));
  neutrino.SetPz(pz_nu);
  neutrino.SetPx(MET*TMath::Cos(MET_phi));
  neutrino.SetPy(MET*TMath::Sin(MET_phi));
  return neutrino;
} 

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int isVetoAK4jet(int event,int p)
{
  //b-tagging should be adressed here!
  //should return 1 when jet is b-tagged and has the right kinematic constraints
  t12->GetEntry(event);
  if((jetAK4_pt->at(p)>30) and (TMath::Abs(jetAK4_eta->at(p))<2.4) and TMath::Abs(jetAK4_cisv->at(p))>0.89)
    {return 1;}
  else
    {return 0;}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void getX_eta_pt(TH1F* histo1,TH1F* histo2 ,int howmany, int X,vector<vector<double> >leptonSelection_tight,vector<vector<double> >leptonSelection_loose)
{
  int N_loose_e=0;
  int N_tight=0;
  int N_loose_mu=0;
  int vetoAK4=0;
  int missEt=0;
  Double_t eta=0;
  Double_t pt=0;
  
  for(int i=0;i<howmany;i++)
    {
      t12->GetEntry(i);
      for(int k=0;k<el_N;k++)
	{ if(isLooseElectron(i,k,leptonSelection_loose)==1)
	       {N_loose_e +=1;}}
      for(int k=0;k<mu_N;k++)
	{ if(isLooseMuon(i,k,leptonSelection_loose)==1)
	    {N_loose_mu +=1;}}
      if(TMath::Abs(X) == 11)
	{
	  for(int p=0;p<el_N;p++)
	    {
	      
	      if(isTightElectron(i,p,leptonSelection_tight) ==1)
		{
		  eta= el_eta->at(p);
		  pt =el_pt->at(p);
		  N_tight +=1;
		}
	    }
	  for(int j=0;j<jetAK4_N;j++)
	    {
	      if(isVetoAK4jet(i,j)==1)
		{
		  vetoAK4 +=1;
		}
	    }
	  //missing transverse Energy veto
	  if(MET_et->size()>1)
	    {cout << i << " event with MET vector bigger 1" << endl;}
	  if(MET_et->at(0)>80)
	    {missEt+=1;}

	  if(N_loose_e<=1 and N_loose_mu<1 and N_tight==1 and vetoAK4==0 and missEt==1)
	    {
	      histo1->Fill(eta);
	      histo2->Fill(pt);   
	    }
	  N_loose_e =0;
	  N_loose_mu=0;
	  N_tight=0;
	  vetoAK4=0;
	  missEt=0;
	}
    
      if(TMath::Abs(X)==13)
  	{
	
  	  for(int p=0;p<mu_N;p++)
  	    {
	      //muon kin. contrictions
	      if(isTightMuon(i,p,leptonSelection_tight)==1)
  	    	{
  	    	  eta= mu_eta->at(p);
  	    	  pt =mu_pt->at(p);
  	      	  N_tight +=1;
  	    	}
	      //muon veto
  	   
  	    }
	  //  b- tagged jet veto
	  for(int j=0;j<jetAK4_N;j++)
	    {
	      if(isVetoAK4jet(i,j)==1)
	  	{
	  	  vetoAK4 +=1;
	  	}
	    }
	  //missing transverse Energy veto
	  if(MET_et->size()>1)
	    {cout << i << " event with MET vector bigger 1" << endl;}
	  if(MET_et->at(0)>40)
	    {missEt+=1;}
  	  if(N_loose_mu<=1 and N_loose_e<1 and N_tight ==1 and vetoAK4==0 and missEt==1)
  	    {
  	      histo1->Fill(eta);
  	      histo2->Fill(pt);
  	    }  

  	    N_loose_mu =0;
	    N_loose_e=0;
  	    N_tight =0;
	    vetoAK4=0;
	    missEt=0;
	}
    }
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


void getX_eta_pt_onlyLeptonCuts(TH1F* histo1,TH1F* histo2 ,int howmany, int X,vector<vector<double> >leptonSelection_tight,vector<vector<double> >leptonSelection_loose)
{
  int N_loose_e=0;
  int N_tight=0;
  int N_loose_mu=0;
  int vetoAK4=0;
  int missEt=0;
  Double_t eta=0;
  Double_t pt=0;
  
  for(int i=0;i<howmany;i++)
    {
      t12->GetEntry(i);
      for(int k=0;k<el_N;k++)
	{ if(isLooseElectron(i,k,leptonSelection_loose)==1)
	       {N_loose_e +=1;}}
      for(int k=0;k<mu_N;k++)
	{ if(isLooseMuon(i,k,leptonSelection_loose)==1)
	    {N_loose_mu +=1;}}
      if(TMath::Abs(X) == 11)
	{
	  for(int p=0;p<el_N;p++)
	    {
	      
	      if(isTightElectron(i,p,leptonSelection_tight) ==1)
		{
		  eta= el_eta->at(p);
		  pt =el_pt->at(p);
		  N_tight +=1;
		}
	    }
	 

	  if(N_loose_e<=1 and N_loose_mu<1 and N_tight==1 )
	    {
	      histo1->Fill(eta);
	      histo2->Fill(pt);   
	    }
	  N_loose_e =0;
	  N_loose_mu=0;
	  N_tight=0;
	}
    
      if(TMath::Abs(X)==13)
  	{
	
  	  for(int p=0;p<mu_N;p++)
  	    {
	      //muon kin. contrictions
	      if(isTightMuon(i,p,leptonSelection_tight)==1)
  	    	{
  	    	  eta= mu_eta->at(p);
  	    	  pt =mu_pt->at(p);
  	      	  N_tight +=1;
  	    	}
	      //muon veto
  	   
  	    }

  	  if(N_loose_mu<=1 and N_loose_e<1 and N_tight ==1)
  	    {
  	      histo1->Fill(eta);
  	      histo2->Fill(pt);
  	    }  

  	    N_loose_mu =0;
	    N_loose_e=0;
  	    N_tight =0;
	}
    }
}
