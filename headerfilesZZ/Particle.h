#ifndef PARTICLE_H
#define PARTICLE_H


// use the aproach where we initialize the member variables using a pointer to ZZtree
class Particle
{
private:
  
  Int_t index_rec_;
  Double_t pt_rec_;
  Double_t eta_rec_;
  Double_t phi_rec_;
  Double_t e_rec_;
  
  Int_t index_gen_;
  Double_t pt_gen_;
  Double_t eta_gen_;
  Double_t phi_gen_;
  Double_t e_gen_;
  
  int charge_;
  int pdgID_;
  int eventID_;
  int Nmother_;
  int Ndaughter_;
  vector<int> mother_pdgId_;
  vector<in> daughter_pdgId_;
  
public:
  
  virtual Particle( int index, int pdgId, ZZtree* tree, bool isRec) = 0;
  virtual ~Particle( void ) =0;
  
  Double_t Pt_rec(void) const;
  Double_t Eta_rec(void) const;
  Double_t Phi_rec(void) const;
  Double_t E_rec(void) const;
  TLorentzVector GetLV_rec(void) const;
  
  Double_t Pt_gen(void) const;
  Double_t Eta_gen(void) const;
  Double_t Phi_gen(void) const;
  Double_t E_gen(void) const;
  TLorentzVector GetLV_gen(void) const;
  
  void SetPt_rec(Double_t pt);
  void SetEta_rec(Double_t eta);
  void SetPhi_rec(Double_t phi);
  void SetE_rec(Double_t e);
  void SetKin_rec(TLorentzvector v);
  
  void SetPt_gen(Double_t pt);
  void SetEta_gen(Double_t eta);
  void SetPhi_gen(Double_t phi);
  void SetE_gen(Double_t e);
  void SetKin_gen(TLorentzvector v);
  
  int  Get_pdgId(void) const;
  int  Get_Charge(void) const;
  int  Get_Nmother(void) const;
  int  Get_Ndaughter(void) const;
 // int  Get_index(void) const;
  
};



#endif