// compile with : g++ reweightTree.cc  -o reweightTree.exe `root-config --cflags --glibs --libs --evelibs`
           
#include "/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include/TTree.h"
#include "/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include/TBranch.h"
#include "/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include/TFile.h"
#include "/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include/TMath.h"
#include "/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include/TLorentzVector.h"
#include "/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include/TCanvas.h"
#include "/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include/TH1.h"
#include "/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include/TTreeReader.h"
#include "/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include/TTreeReaderValue.h"
#include "/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include/TTreeReaderArray.h"
//#include "/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd5/include/TTreeReaderValueBase.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include "/usr/users/dschaefer/root/headerfilesAllChannels/emEff.h"
#include "/usr/users/dschaefer/root/headerfilesAllChannels/hadEff.h"
#include "/usr/users/dschaefer/root/headerfiles/AllHadronicConstants.h"
#include "/usr/users/dschaefer/root/headerfiles/WWConstants.h"


TLorentzVector getLV(float Wlep_pt, float Wlep_eta, float Wlep_phi, float Wlep_E);
//TLorentzVector getLV(float Whad_pt, float Whad_eta, float Whad_phi, float Whad_E);

float reweightWlep(TLorentzVector Wlep,int pdgId);
float reweightWhad(TLorentzVector Whad,std::string channel);

bool passedAcceptanceSemilep(TLorentzVector Wlep, TLorentzVector Whad,TLorentzVector l, TLorentzVector n, int pdgId);
bool passedAcceptanceHadronic(TLorentzVector Wplus, TLorentzVector Wminus);

bool passedEtaCutMu(TLorentzVector l);
bool passedPtCutMu(TLorentzVector l);
bool passedPtCutMuonNeutrino(TLorentzVector n);
bool passedEtaCutEl(TLorentzVector l);
bool passedPtCutEl(TLorentzVector l);
bool passedPtCutElectronNeutrino(TLorentzVector n);
bool passedBackToBack(TLorentzVector Wlep, TLorentzVector Whad, TLorentzVector l, TLorentzVector n);
bool passedMassCut(TLorentzVector G);
bool passedCutsOnWlep(TLorentzVector Wlep);
bool passedCutsOnWhad(TLorentzVector Whad);

void PrintInfo(int pdgId,TLorentzVector Wlep, TLorentzVector Whad, TLorentzVector l, TLorentzVector n);


int main(int argc, char** argv)
{
  if(argc<3)
  {
   std::cout << " needs at least two argument: input-filename, channel " << std::endl;
   return 1;
  }
  
  std::string filename = argv[1];
  std::string channel = argv[2];
  std::string dir = "/storage/jbod/dschaefer/";
  if(argc==4){dir = argv[3];}
  
  
  
  TFile* f = new TFile((dir+filename).c_str(),"UPDATE");
  if(f==0){std::cout << "file could not be opened "<< std::endl; return 1;}
  
  TTreeReader* myreader = new TTreeReader("tree",f);
  TTree* tree = (TTree*) f->Get("tree");
  float eventWeight;
  TBranch* bw = tree->Branch("eventWeight",&eventWeight,"eventWeight/F");
  bool passedAcceptence;
  TBranch* ba = tree->Branch("passedAcceptence",&passedAcceptence,"passedAcceptence/O");
  float w_tauBR;
  TBranch* b_w_tauBR = tree->Branch("w_tauBR",&w_tauBR ,"w_tauBR/F");
  
  
 if(channel.find("em")!=std::string::npos)
 {
    TTreeReaderValue<float> Wlep_pt (*myreader,"Wlep_pt" );
    TTreeReaderValue<float> Wlep_eta(*myreader,"Wlep_eta");
    TTreeReaderValue<float> Wlep_phi(*myreader,"Wlep_phi");
    TTreeReaderValue<float> Wlep_E  (*myreader,"Wlep_E"  );
    TTreeReaderValue<float> lepton_pt (*myreader,"lepton_pt" );
    TTreeReaderValue<float> lepton_eta(*myreader,"lepton_eta");
    TTreeReaderValue<float> lepton_phi(*myreader,"lepton_phi");
    TTreeReaderValue<float> lepton_E  (*myreader,"lepton_E"  );
    TTreeReaderValue<float> neutrino_pt (*myreader,"neutrino_pt" );
    TTreeReaderValue<float> neutrino_eta(*myreader,"neutrino_eta");
    TTreeReaderValue<float> neutrino_phi(*myreader,"neutrino_phi");
    TTreeReaderValue<float> neutrino_E  (*myreader,"neutrino_E"  );
    TTreeReaderValue<float> Whad_pt (*myreader,"Whad_pt" );
    TTreeReaderValue<float> Whad_eta(*myreader,"Whad_eta");
    TTreeReaderValue<float> Whad_phi(*myreader,"Whad_phi");
    TTreeReaderValue<float> Whad_E  (*myreader,"Whad_E"  );
    TTreeReaderValue<int>   leptonID(*myreader,"leptonID");
    TTreeReaderValue<bool>  isTauEvent(*myreader,"isTauEvent");
    
    TTreeReaderValue<float> tau_pt (*myreader,"tau_pt");
    TTreeReaderValue<float> tau_eta(*myreader,"tau_eta");
    TTreeReaderValue<float> tau_phi(*myreader,"tau_phi");
    TTreeReaderValue<float> tau_E(*myreader,"tau_E");
 
    float NumberOfEventsWithGenHadronicW=0;
    float NumberOfEventsWithGenLeptonicWElPlusMu=0;
    float NumberOfEventsWithGenLeptonicWEl=0;
    float NumberOfEventsWithGenLeptonicWMu=0;
    float ReweightOfElW=0;
    float ReweightOfMuW=0;
    float ReweightOfHadW=0;
    float ReweightAllEl=0;
    float ReweightAllMu=0;
    float NumberOfEventsPassingGenCutsMu=0;
    float NumberOfEventsPassingGenCutsEl=0;
    int eventNumber =-1;
     while(myreader->Next())
      {
	eventNumber++;
	std::cout << eventNumber << std::endl;
	TLorentzVector Wlep = getLV(*Wlep_pt,*Wlep_eta,*Wlep_phi,*Wlep_E);
	TLorentzVector Whad = getLV(*Whad_pt,*Whad_eta,*Whad_phi,*Whad_E);
	TLorentzVector lepton = getLV(*lepton_pt,*lepton_eta,*lepton_phi,*lepton_E);
	TLorentzVector neutrino = Wlep-lepton;
        TLorentzVector neutrino2 = getLV(*neutrino_pt,*neutrino_eta,*neutrino_phi,*neutrino_E);
        TLorentzVector tau = getLV(*tau_pt,*tau_eta,*tau_phi,*tau_E);
        
        //std::cout << neutrino.Pt() << " " << neutrino2.Pt() <<std::endl;
	if(*leptonID!=11 and *leptonID!=13)
        {
         std::cout << *leptonID << std::endl;   
        }
        
	NumberOfEventsWithGenHadronicW+=1;
        w_tauBR =1;
	
        if(*isTauEvent)
        {
         w_tauBR = 0.1741;
         if(*leptonID == 11)
         {
          w_tauBR = 0.1783;   
         }
        }
    
        
 	if(*leptonID == 11)
	{
         std::cout << "electron event " << std::endl;
	  eventWeight =  reweightWlep(Wlep,11)*reweightWhad(Whad,channel)*Vetos;
	  if(filename.find("RS")!=std::string::npos)
	  {
	   eventWeight = eventWeight/PolarisationFactor; 
	  }
	  passedAcceptence = passedAcceptanceSemilep(Wlep,Whad,lepton,neutrino,11);
//          if(!passedPtCutEl(lepton) and lepton.Pt()<120)
//           {
//            std::cout << std::endl;
//            std::cout << tau.Pt() << " "<<lepton.Pt() << std::endl;
//            PrintInfo(11, Wlep,Whad,lepton,neutrino);
//           }
          if(eventNumber==5 or eventNumber==38 or eventNumber==109)
        {
            std::cout<< eventNumber << std::endl;
            PrintInfo(11, Wlep,Whad,lepton,neutrino);
          std::cout << passedAcceptence << std::endl;
        }
	}
 	if(*leptonID == 13)
	{
          std::cout << "muon event" << std::endl;
	  eventWeight = reweightWlep(Wlep,13)*reweightWhad(Whad,channel)*Vetos;
	  if(filename.find("RS")!=std::string::npos)
	  {
	   eventWeight = eventWeight/PolarisationFactor; 
	  }
	  passedAcceptence = passedAcceptanceSemilep(Wlep,Whad,lepton,neutrino,13);
    
          //std::cout << "13 : "<<std::endl;
//           if(tau.Pt()!=0 and !passedPtCutMu(lepton))
//           {
//            std::cout << std::endl;
//            std::cout << tau.Pt() << " "<<lepton.Pt() << std::endl;
//            PrintInfo(13, Wlep,Whad,lepton,neutrino);
//           }
          }
	
	bw->Fill();
	ba->Fill();
	b_w_tauBR->Fill();
        
	 NumberOfEventsWithGenLeptonicWElPlusMu +=w_tauBR;
	if(*leptonID ==11)
	{
	  NumberOfEventsWithGenLeptonicWEl+=1;
	  ReweightOfElW += reweightWlep(Wlep,11);
	  if(passedAcceptanceSemilep(Wlep,Whad,lepton,neutrino,11))
	  {
	  ReweightAllEl += reweightWlep(Wlep,11)*reweightWhad(Whad,channel)*BVeto*LooseLeptonVeto*w_tauBR;
	  NumberOfEventsPassingGenCutsEl+=1;
          
	  }
	}
	if(*leptonID ==13)
	{
	  NumberOfEventsWithGenLeptonicWMu+=1;
	  ReweightOfMuW += reweightWlep(Wlep,13);
	  if(passedAcceptanceSemilep(Wlep,Whad,lepton,neutrino,13))
	  {
	  ReweightAllMu += reweightWlep(Wlep,13)*reweightWhad(Whad,channel)*BVeto*LooseLeptonVeto*w_tauBR;
	  NumberOfEventsPassingGenCutsMu+=1;
	  }
	}
	//bw->Fill();
	
      
      if(filename.find("RS")!=std::string::npos)
      {
	   ReweightAllMu = ReweightAllMu/PolarisationFactor; 
	   ReweightAllEl = ReweightAllEl/PolarisationFactor; 
      }
      
      }
      tree->Print();
      //tree->Write();
      
      //bw->Print();
      
      
    delete f;
    float amu = (NumberOfEventsPassingGenCutsMu)/(NumberOfEventsWithGenLeptonicWElPlusMu);
    float ael = (NumberOfEventsPassingGenCutsEl)/(NumberOfEventsWithGenLeptonicWElPlusMu);
    float emu = ReweightAllMu/float(NumberOfEventsPassingGenCutsMu);
    float eel = ReweightAllEl/float(NumberOfEventsPassingGenCutsEl);
    std::cout << filename << std::endl;
    std::cout <<" ============================================================================="<<std::endl;  
    std::cout <<"# events              " << NumberOfEventsWithGenHadronicW <<std::endl;
    std::cout <<"#events with el or mu "<< NumberOfEventsWithGenLeptonicWElPlusMu <<std::endl;
    std::cout <<"# pass gen cuts mu    " << NumberOfEventsPassingGenCutsMu<<std::endl;
    std::cout <<"# pass gen cuts el    " << NumberOfEventsPassingGenCutsEl<<std::endl;
    std::cout <<"#events reweighted mu "<< ReweightAllMu <<std::endl;
    std::cout <<"#events reweighted el "<< ReweightAllEl  <<std::endl;
    std::cout <<"efficiency mu         "<< emu <<std::endl;
    std::cout << "efficiency el        "<< eel <<std::endl;
    std::cout <<"acceptance mu         "<< NumberOfEventsPassingGenCutsMu/float(NumberOfEventsWithGenLeptonicWElPlusMu)<<std::endl;
    std::cout <<"acceptance el         "<< NumberOfEventsPassingGenCutsEl/float(NumberOfEventsWithGenLeptonicWElPlusMu)<<std::endl;
    std::cout << std::endl;
    std::cout << "acceptance*efficiency mu "<< emu*amu<<std::endl;
    std::cout << "acceptance*efficiency el "<< eel*ael <<std::endl;
    std::cout <<" ============================================================================="<<std::endl;
    return 0;
 }
 if(channel.find("had")!=std::string::npos)
 {
    TTreeReaderValue<float> Wplus_pt (*myreader,"Wplus_pt" );
    TTreeReaderValue<float> Wplus_eta(*myreader,"Wplus_eta");
    TTreeReaderValue<float> Wplus_phi(*myreader,"Wplus_phi");
    TTreeReaderValue<float> Wplus_E  (*myreader,"Wplus_E"  );
    TTreeReaderValue<float> Wminus_pt (*myreader,"Wminus_pt" );
    TTreeReaderValue<float> Wminus_eta(*myreader,"Wminus_eta");
    TTreeReaderValue<float> Wminus_phi(*myreader,"Wminus_phi");
    TTreeReaderValue<float> Wminus_E  (*myreader,"Wminus_E"  );
 
    float NumberOfEventsWithGenHadronicW=0;
    float NumberOfEventsWithGenLeptonicW=0;
    float NumberOfEventsPassingGenCuts=0;
  
    float ReweightAll=0;
    float ReweightWplus=0;
    float ReweightWminus=0;
 
     while(myreader->Next())
    //for(int i=0;i<tree->GetEntries();i++)
      {
	
	//myreader->Next();
	TLorentzVector Wplus = getLV(*Wplus_pt,*Wplus_eta,*Wplus_phi,*Wplus_E);
	TLorentzVector Wminus = getLV(*Wminus_pt,*Wminus_eta,*Wminus_phi,*Wminus_E);
	
	NumberOfEventsWithGenHadronicW+=1;
	
 	eventWeight =  reweightWhad(Wminus,channel)*reweightWhad(Wplus,channel)*effDEtaCut;
	//std::cout << eventWeight << std::endl;
	if(filename.find("RS")!=std::string::npos)
	{
	 eventWeight=eventWeight/std::pow(PolarisationFactor,2); 
	}
	passedAcceptence = passedAcceptanceHadronic(Wplus,Wminus);
 	bw->Fill();
	ba->Fill();
	if(passedAcceptence)
	{
	ReweightAll+=eventWeight;
	NumberOfEventsPassingGenCuts+=1;
	}
	ReweightWminus+=reweightWhad(Wminus,channel);
	ReweightWplus += reweightWhad(Wplus,channel);
	
      }
      
      
      tree->Print();
      //tree->Write();
      
      //bw->Print();
      
      
    delete f;
    std::cout <<" ============================================================================="<<std::endl;  
    std::cout <<"# events              " << NumberOfEventsWithGenHadronicW <<std::endl;
    std::cout <<"#events with lepton   "<< NumberOfEventsWithGenLeptonicW <<std::endl;
    std::cout <<"#events rew. W+       "<< ReweightWplus <<std::endl;
    std::cout <<"#events rew. W-       "<< ReweightWminus <<std::endl;
    std::cout <<"#events reweighted    "<< ReweightAll <<std::endl;
    std::cout <<"efficiency had        "<< ReweightAll/NumberOfEventsPassingGenCuts<<std::endl;
    std::cout <<"acceptance had        "<< NumberOfEventsPassingGenCuts/NumberOfEventsWithGenHadronicW<<std::endl;
    std::cout <<"#events pass gen cuts "<< NumberOfEventsPassingGenCuts<<std::endl;
    std::cout <<"acceptance*efficiency "<< ReweightAll/NumberOfEventsWithGenHadronicW<<std::endl;
    std::cout <<" ============================================================================="<<std::endl;
   
  return 0; 
 }
 else
 {
   return 1;
 }
} 

void PrintInfo(int pdgId,TLorentzVector Wlep, TLorentzVector Whad, TLorentzVector l, TLorentzVector n)
{
 
    bool passedLepPt =0;
    bool passedLepEta=0;
    bool passedNeuPt =0;
    if(pdgId==11)
    {
     passedLepPt = passedPtCutEl(l);
     passedLepEta = passedEtaCutEl(l);
     passedNeuPt = passedPtCutElectronNeutrino(n);
    }
    if(pdgId==13)
    {
     passedLepPt = passedPtCutMu(l);
     passedLepEta = passedEtaCutMu(l);
     passedNeuPt = passedPtCutMuonNeutrino(n); 
    }
   std::cout << "lepton:"<<std::endl;
   std::cout << "pt : "  << l.Pt() << " "<< passedLepPt << std::endl;
   std::cout << "eta : " << l.Eta() << " " << passedLepEta << std::endl;
   std::cout << "neutrino: "<<std::endl;
   std::cout << "pt : "<< n.Pt() << " "<< passedNeuPt << std::endl;
   std::cout << "Wlep : "<<std::endl;
   std::cout << "pt : "<< Wlep.Pt() <<  " "<< passedCutsOnWlep(Wlep) <<std::endl;
   std::cout << "Whad : "<<std::endl;
   std::cout << "pt : " << Whad.Pt() << std::endl;
   std::cout << "eta: " << Whad.Eta() <<  " " <<passedCutsOnWhad(Whad) << std::endl;
   std::cout << "G  " << std::endl;
   std::cout << "mass : " << (Wlep+Whad).M() << " "<< passedMassCut(Wlep+Whad) << std::endl;
   std::cout << "B2B  : "<< passedBackToBack(Wlep,Whad,l,n)<<std::endl;
    
}


bool passedEtaCutMu(TLorentzVector l)
{
 bool passed =0;
 if(TMath::Abs(l.Eta())<WWMUETA )
 {
  passed =1;   
 }
 return passed;
}

bool passedPtCutMu(TLorentzVector l)
{
 bool passed =0;
 if(l.Pt()>WWMUPT)
 {
  passed =1;   
 }
 return passed;
}

bool passedPtCutMuonNeutrino(TLorentzVector n)
{
  bool passed =0;
 if(n.Pt()>WWMETPTMU)
 {
  passed =1;   
 }
 return passed;  
}

bool passedEtaCutEl(TLorentzVector l)
{
 bool passed =0;
 if(TMath::Abs(l.Eta())<WWELEECALGAPMIN or (TMath::Abs(l.Eta())>WWELEECALGAPMAX and TMath::Abs(l.Eta())<WWELEETA))
 {
  passed =1;   
 }
 return passed;
}

bool passedPtCutEl(TLorentzVector l)
{
 bool passed =0;
 if(l.Pt()>WWELEPT )
 {
  passed =1;   
 }
 return passed;
}

bool passedPtCutElectronNeutrino(TLorentzVector n)
{
  bool passed =0;
 if(n.Pt()>WWMETPTELE)
 {
  passed =1;   
 }
 return passed;  
}

bool passedBackToBack(TLorentzVector Wlep, TLorentzVector Whad, TLorentzVector l, TLorentzVector n)
{
    bool passed=0;
    Double_t Delta_phi 	 = TMath::Abs(Whad.DeltaPhi(n));
    Double_t Delta_phi_W = TMath::Abs(Whad.DeltaPhi(Wlep));
    Double_t Delta_R 	 = TMath::Abs(l.DeltaR(Whad));
  //std::cout << " dphi_nu_whad: " << Delta_phi 
    //<<" dphi_whad_wlep: " << Delta_phi_W
     //<< " dr_l_whad " << Delta_R <<std::endl;
  
    if(Delta_phi> WWDELTAPHIWHADMET and Delta_phi_W> WWDELTAPHIWHADWLEP and Delta_R> WWDELTARWHADLEPTON)
    {
     passed = 1; 
    } 
    return passed;
}

bool passedMassCut(TLorentzVector G)
{
 bool passed =0;
 float mass = G.M();
 if(mass< WWMASSMAX and mass> WWMASSMIN)
 {
  passed =1;   
 }
 return passed;
}

bool passedCutsOnWlep(TLorentzVector Wlep)
{
 bool passed=0;
 if(Wlep.Pt()>WWPTW)
     passed =1;
 return passed;
}

bool passedCutsOnWhad(TLorentzVector Whad)
{
 bool passed=0;
 if(Whad.Pt()>WWPTW  and TMath::Abs(Whad.Eta())<WWAK8JETETA)
     passed=1;
 return passed;
}


bool passedAcceptanceSemilep(TLorentzVector Wlep, TLorentzVector Whad,TLorentzVector l, TLorentzVector n,int pdgId)
{
  bool passed=0;
  bool R=0;
  bool WM=0;
  bool K=0;
  bool Klepton=0;
  TLorentzVector G = Wlep+Whad;
  if(passedMassCut(G))
  {
   WM=1;   
  }
    if(passedCutsOnWhad(Whad) and passedCutsOnWlep(Wlep))
    {
     K=1; 
    }
   
   
    if(pdgId==13)
    {
      if(passedPtCutMu(l) and passedEtaCutMu(l) and passedPtCutMuonNeutrino(n))
      {
       Klepton =1;   
      }
    }
    if(pdgId==11)
    {
      if(passedPtCutEl(l) and passedEtaCutEl(l) and passedPtCutElectronNeutrino(n))
      {
	Klepton=1;
      }
    }
   
    if(passedBackToBack(Wlep,Whad,l,n))
    {
     R = 1; 
    }
  if(R and WM and K and Klepton)
  {
    passed =1;
  }
 
  return passed;
}


bool passedAcceptanceHadronic(TLorentzVector Wplus, TLorentzVector Wminus)
{ 
  bool passed =1;
    if(Wplus.Pt()<= JETPT or Wminus.Pt()<= JETPT)
    {passed =0;}
    if(TMath::Abs(Wplus.Eta())>=JETETA or TMath::Abs(Wminus.Eta())>=JETETA)
    {passed =0;}
    if(TMath::Abs(Wplus.Eta()-Wminus.Eta())>=DELTAETAJETJET)
    {passed=0;}
    if((Wplus+Wminus).M()<=DIJETMASS)
    {passed=0;}
  return passed;
}

float reweightWlep(TLorentzVector Wlep,int pdgId)
{
  float result =0;
  int indexX =-1;
  int indexY =-1;
  for(int i=0;i<NX-1;i++)
  {
       if(/*Wlep.Pt()> masses[i] and */Wlep.Pt()<pt[i+1])
       {
	 indexX = i+1;
	 //std::cout << Wlep.Pt() << " "<< pt[i]<<"-"<<pt[i+1]<<std::endl;
	 break;
       }
  }
  for(int i=0;i<NY-1;i++)
  {
      if(TMath::Abs(Wlep.Eta())<binsY[i+1])
      {
	indexY = i;
	//std::cout <<Wlep.Eta()<< " "<<binsY[i]<<"-"<<binsY[i+1]<<std::endl;
	break;
      }
  }
  if(indexX>-1 and indexY>-1)
  {
  if(pdgId == 11)
  {
    if(indexX==1 ){result = eleff1 [indexY];}
    if(indexX==2 ){result = eleff2 [indexY];}
    if(indexX==3 ){result = eleff3 [indexY];}
    if(indexX==4 ){result = eleff4 [indexY];}
    if(indexX==5 ){result = eleff5 [indexY];}
    if(indexX==6 ){result = eleff6 [indexY];}
    if(indexX==7 ){result = eleff7 [indexY];}
    if(indexX==8 ){result = eleff8 [indexY];}
    if(indexX==9 ){result = eleff9 [indexY];}
    if(indexX==10){result = eleff10[indexY];}
    if(indexX==11){result = eleff11[indexY];}
    if(indexX==12){result = eleff12[indexY];}
    if(indexX==13){result = eleff13[indexY];}
    if(indexX==14){result = eleff14[indexY];}
    if(indexX==15){result = eleff15[indexY];}
  }
  else
  {
    if(indexX==1 ){result = mueff1 [indexY];}
    if(indexX==2 ){result = mueff2 [indexY];}
    if(indexX==3 ){result = mueff3 [indexY];}
    if(indexX==4 ){result = mueff4 [indexY];}
    if(indexX==5 ){result = mueff5 [indexY];}
    if(indexX==6 ){result = mueff6 [indexY];}
    if(indexX==7 ){result = mueff7 [indexY];}
    if(indexX==8 ){result = mueff8 [indexY];}
    if(indexX==9 ){result = mueff9 [indexY];}
    if(indexX==10){result = mueff10[indexY];}
    if(indexX==11){result = mueff11[indexY];}
    if(indexX==12){result = mueff12[indexY];}
    if(indexX==13){result = mueff13[indexY];}
    if(indexX==14){result = mueff14[indexY];}
    if(indexX==15){result = mueff15[indexY];}
  }
  }
  else
  {
    result =0; 
  }
  return result;
}



float reweightWhad(TLorentzVector Whad,std::string channel)
{
  float result =0;
  int indexX =-1;
  int indexY =-1;
  if(channel.find("em")!=std::string::npos)
  {
  for(int i=0;i<NX-1;i++)
  {
       if(/*Wlep.Pt()> masses[i] and */Whad.Pt()<pt[i+1])
       {
	 //std::cout << Whad.Pt() << " "<<pt[i]<<"-"<<pt[i+1]<<std::endl;
	 indexX = i+1;
	 break;
       }
  }
  for(int i=0;i<NY-1;i++)
  {
      if(TMath::Abs(Whad.Eta())<binsY[i+1])
      {
	indexY = i;
	break;
      }
  }
  if(indexX>-1 and indexY>-1)
  {
  
    if(indexX==1 ){result = hadeff1 [indexY];}
    if(indexX==2 ){result = hadeff2 [indexY];}
    if(indexX==3 ){result = hadeff3 [indexY];}
    if(indexX==4 ){result = hadeff4 [indexY];}
    if(indexX==5 ){result = hadeff5 [indexY];}
    if(indexX==6 ){result = hadeff6 [indexY];}
    if(indexX==7 ){result = hadeff7 [indexY];}
    if(indexX==8 ){result = hadeff8 [indexY];}
    if(indexX==9 ){result = hadeff9 [indexY];}
    if(indexX==10){result = hadeff10[indexY];}
    if(indexX==11){result = hadeff11[indexY];}
    if(indexX==12){result = hadeff12[indexY];}
    if(indexX==13){result = hadeff13[indexY];}
    if(indexX==14){result = hadeff14[indexY];}
    if(indexX==15){result = hadeff15[indexY];}
  }
  }
  else
  {
    for(int i=0;i<NX-1;i++)
  {
       if(/*Wlep.Pt()> masses[i] and */Whad.Pt()<pthad[i+1])
       {
	 indexX = i+1;
	 break;
       }
  }
  for(int i=0;i<NY-1;i++)
  {
      if(TMath::Abs(Whad.Eta())<binsYhad[i+1])
      {
	indexY = i;
	break;
      }
  }
  if(indexX>-1 and indexY>-1)
  {
  
    if(indexX==1 ){result = eff1 [indexY];}
    if(indexX==2 ){result = eff2 [indexY];}
    if(indexX==3 ){result = eff3 [indexY];}
    if(indexX==4 ){result = eff4 [indexY];}
    if(indexX==5 ){result = eff5 [indexY];}
    if(indexX==6 ){result = eff6 [indexY];}
    if(indexX==7 ){result = eff7 [indexY];}
    if(indexX==8 ){result = eff8 [indexY];}
    if(indexX==9 ){result = eff9 [indexY];}
    if(indexX==10){result = eff10[indexY];}
    if(indexX==11){result = eff11[indexY];}
    if(indexX==12){result = eff12[indexY];}
    if(indexX==13){result = eff13[indexY];}
    if(indexX==14){result = eff14[indexY];}
    if(indexX==15){result = eff15[indexY];}
  }
    
  }
  return result; 
}



TLorentzVector getLV(float Wlep_pt,float Wlep_eta,float Wlep_phi,float Wlep_E)
{
    TLorentzVector W;
    W.SetPtEtaPhiE(Wlep_pt,Wlep_eta,Wlep_phi,Wlep_E);
    return W;
}


// TLorentzVector getLV(float Whad_pt, float Whad_eta, float Whad_phi, float Whad_E)
// {
//     TLorentzVector W;
//     W.SetPtEtaPhiE(Whad_pt,Whad_eta,Whad_phi,Whad_E);
//     return W;
// }
// 
