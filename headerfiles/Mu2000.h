//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec  3 12:57:00 2015 by ROOT version 6.02/05
// from TTree tree/Format: User, data type: BulkGraviton
// found on file: passed_mu_2000.root
//////////////////////////////////////////////////////////

#ifndef Mu2000_h
#define Mu2000_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Mu2000 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         weight;
   Float_t         puweight;
   Float_t         hltweight;
   Float_t         lumiweight;
   Float_t         btagweight;
   Float_t         genweight;
   Int_t           channel;
   Float_t         MWW;
   Float_t         jet_mass;
   Float_t         Mjpruned;
   Float_t         Mjsoftdrop;
   Float_t         Whadr_pt;
   Float_t         Whadr_eta;
   Float_t         Whadr_phi;
   Float_t         tau21;
   Float_t         lept_pt;
   Float_t         lept_eta;
   Float_t         lept_phi;
   Float_t         lept_iso;
   Int_t           isGlobalMuon;
   Int_t           globalHits;
   Int_t           pixelHits;
   Int_t           trackerHits;
   Int_t           matchedStations;
   Float_t         bestTrack_ptErrRel;
   Float_t         d0;
   Float_t         dz;
   Float_t         Wlept_pt;
   Float_t         Wlept_mt;
   Float_t         met;
   Float_t         met_phi;
   Float_t         ltopmass;
   Float_t         htopmass;
   Bool_t          issignal;
   Float_t         dr_lepjet;
   Float_t         dphi_metjet;
   Float_t         dphi_jetw;
   Int_t           nPVs;
   Int_t           nsubj;
   Int_t           nsubjbtag;
   Int_t           nsubjbtagM;
   Float_t         subj1csv;
   Float_t         subj2csv;
   Int_t           subj1flavor;
   Int_t           subj2flavor;
   Float_t         subj1eta;
   Float_t         subj2eta;
   Float_t         subj1pt;
   Float_t         subj2pt;
   Int_t           nak4jets;
   Float_t         ak4jet1_csv;
   Float_t         ak4jet1_pt;
   Float_t         ak4jet2_csv;
   Float_t         ak4jet2_pt;
   Float_t         ak4jet3_csv;
   Float_t         ak4jet3_pt;

   // List of branches
   TBranch        *b_weight;   //!
   TBranch        *b_puweight;   //!
   TBranch        *b_hltweight;   //!
   TBranch        *b_lumiweight;   //!
   TBranch        *b_btagweight;   //!
   TBranch        *b_genweight;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_MWW;   //!
   TBranch        *b_jet_mass;   //!
   TBranch        *b_Mjpruned;   //!
   TBranch        *b_Mjsoftdrop;   //!
   TBranch        *b_Whadr_pt;   //!
   TBranch        *b_Whadr_eta;   //!
   TBranch        *b_Whadr_phi;   //!
   TBranch        *b_tau21;   //!
   TBranch        *b_lept_pt;   //!
   TBranch        *b_lept_eta;   //!
   TBranch        *b_lept_phi;   //!
   TBranch        *b_lept_iso;   //!
   TBranch        *b_isGlobalMuon;   //!
   TBranch        *b_globalHits;   //!
   TBranch        *b_pixelHits;   //!
   TBranch        *b_trackerHits;   //!
   TBranch        *b_matchedStations;   //!
   TBranch        *b_bestTrack_ptErrRel;   //!
   TBranch        *b_d0;   //!
   TBranch        *b_dz;   //!
   TBranch        *b_Wlept_pt;   //!
   TBranch        *b_Wlept_mt;   //!
   TBranch        *b_met;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_ltopmass;   //!
   TBranch        *b_htopmass;   //!
   TBranch        *b_issignal;   //!
   TBranch        *b_dr_lepjet;   //!
   TBranch        *b_dphi_metjet;   //!
   TBranch        *b_dphi_jetw;   //!
   TBranch        *b_nPVs;   //!
   TBranch        *b_nsubj;   //!
   TBranch        *b_nsubjbtag;   //!
   TBranch        *b_nsubjbtagM;   //!
   TBranch        *b_subj1csv;   //!
   TBranch        *b_subj2csv;   //!
   TBranch        *b_subj1flavor;   //!
   TBranch        *b_subj2flavor;   //!
   TBranch        *b_subj1eta;   //!
   TBranch        *b_subj2eta;   //!
   TBranch        *b_subj1pt;   //!
   TBranch        *b_subj2pt;   //!
   TBranch        *b_nak4jets;   //!
   TBranch        *b_ak4jet1_csv;   //!
   TBranch        *b_ak4jet1_pt;   //!
   TBranch        *b_ak4jet2_csv;   //!
   TBranch        *b_ak4jet2_pt;   //!
   TBranch        *b_ak4jet3_csv;   //!
   TBranch        *b_ak4jet3_pt;   //!

   Mu2000(TTree *tree=0);
   virtual ~Mu2000();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Mu2000_cxx
Mu2000::Mu2000(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("passed_mu_2000.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("passed_mu_2000.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

Mu2000::~Mu2000()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Mu2000::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Mu2000::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Mu2000::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("puweight", &puweight, &b_puweight);
   fChain->SetBranchAddress("hltweight", &hltweight, &b_hltweight);
   fChain->SetBranchAddress("lumiweight", &lumiweight, &b_lumiweight);
   fChain->SetBranchAddress("btagweight", &btagweight, &b_btagweight);
   fChain->SetBranchAddress("genweight", &genweight, &b_genweight);
   fChain->SetBranchAddress("channel", &channel, &b_channel);
   fChain->SetBranchAddress("MWW", &MWW, &b_MWW);
   fChain->SetBranchAddress("jet_mass", &jet_mass, &b_jet_mass);
   fChain->SetBranchAddress("Mjpruned", &Mjpruned, &b_Mjpruned);
   fChain->SetBranchAddress("Mjsoftdrop", &Mjsoftdrop, &b_Mjsoftdrop);
   fChain->SetBranchAddress("Whadr_pt", &Whadr_pt, &b_Whadr_pt);
   fChain->SetBranchAddress("Whadr_eta", &Whadr_eta, &b_Whadr_eta);
   fChain->SetBranchAddress("Whadr_phi", &Whadr_phi, &b_Whadr_phi);
   fChain->SetBranchAddress("tau21", &tau21, &b_tau21);
   fChain->SetBranchAddress("lept_pt", &lept_pt, &b_lept_pt);
   fChain->SetBranchAddress("lept_eta", &lept_eta, &b_lept_eta);
   fChain->SetBranchAddress("lept_phi", &lept_phi, &b_lept_phi);
   fChain->SetBranchAddress("lept_iso", &lept_iso, &b_lept_iso);
   fChain->SetBranchAddress("isGlobalMuon", &isGlobalMuon, &b_isGlobalMuon);
   fChain->SetBranchAddress("globalHits", &globalHits, &b_globalHits);
   fChain->SetBranchAddress("pixelHits", &pixelHits, &b_pixelHits);
   fChain->SetBranchAddress("trackerHits", &trackerHits, &b_trackerHits);
   fChain->SetBranchAddress("matchedStations", &matchedStations, &b_matchedStations);
   fChain->SetBranchAddress("bestTrack_ptErrRel", &bestTrack_ptErrRel, &b_bestTrack_ptErrRel);
   fChain->SetBranchAddress("d0", &d0, &b_d0);
   fChain->SetBranchAddress("dz", &dz, &b_dz);
   fChain->SetBranchAddress("Wlept_pt", &Wlept_pt, &b_Wlept_pt);
   fChain->SetBranchAddress("Wlept_mt", &Wlept_mt, &b_Wlept_mt);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("ltopmass", &ltopmass, &b_ltopmass);
   fChain->SetBranchAddress("htopmass", &htopmass, &b_htopmass);
   fChain->SetBranchAddress("issignal", &issignal, &b_issignal);
   fChain->SetBranchAddress("dr_lepjet", &dr_lepjet, &b_dr_lepjet);
   fChain->SetBranchAddress("dphi_metjet", &dphi_metjet, &b_dphi_metjet);
   fChain->SetBranchAddress("dphi_jetw", &dphi_jetw, &b_dphi_jetw);
   fChain->SetBranchAddress("nPVs", &nPVs, &b_nPVs);
   fChain->SetBranchAddress("nsubj", &nsubj, &b_nsubj);
   fChain->SetBranchAddress("nsubjbtag", &nsubjbtag, &b_nsubjbtag);
   fChain->SetBranchAddress("nsubjbtagM", &nsubjbtagM, &b_nsubjbtagM);
   fChain->SetBranchAddress("subj1csv", &subj1csv, &b_subj1csv);
   fChain->SetBranchAddress("subj2csv", &subj2csv, &b_subj2csv);
   fChain->SetBranchAddress("subj1flavor", &subj1flavor, &b_subj1flavor);
   fChain->SetBranchAddress("subj2flavor", &subj2flavor, &b_subj2flavor);
   fChain->SetBranchAddress("subj1eta", &subj1eta, &b_subj1eta);
   fChain->SetBranchAddress("subj2eta", &subj2eta, &b_subj2eta);
   fChain->SetBranchAddress("subj1pt", &subj1pt, &b_subj1pt);
   fChain->SetBranchAddress("subj2pt", &subj2pt, &b_subj2pt);
   fChain->SetBranchAddress("nak4jets", &nak4jets, &b_nak4jets);
   fChain->SetBranchAddress("ak4jet1_csv", &ak4jet1_csv, &b_ak4jet1_csv);
   fChain->SetBranchAddress("ak4jet1_pt", &ak4jet1_pt, &b_ak4jet1_pt);
   fChain->SetBranchAddress("ak4jet2_csv", &ak4jet2_csv, &b_ak4jet2_csv);
   fChain->SetBranchAddress("ak4jet2_pt", &ak4jet2_pt, &b_ak4jet2_pt);
   fChain->SetBranchAddress("ak4jet3_csv", &ak4jet3_csv, &b_ak4jet3_csv);
   fChain->SetBranchAddress("ak4jet3_pt", &ak4jet3_pt, &b_ak4jet3_pt);
   Notify();
}

Bool_t Mu2000::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Mu2000::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Mu2000::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Mu2000_cxx
