#include "EventSelection.h"
#include "MyClass.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TChain.h"
#include <vector>
#include <vector>
#include <vector>
#include "vector"
#include "iostream"
#include "iomanip"
#include "fstream"
#include "cmath"
#include "cassert"
#include "WWConstants.h"
#include "Op.h"
#include "AllHadronicConstants.h"

//=====================================================================================
//====== selection of hadronic/semileptonic/leptonic  events on inclusive trees =======
//=====================================================================================

bool genEventSelectionInclusive(MyClass* t12, string decayMode)
{
  int Nparticles = t12->genParticle_N;
  vector<int> pdgId_dau;
  int particle_pdgId;
  int isHadronic=0;
  int isLeptonic=0;
  bool ishad=0;
  bool islep=0;
  bool islephad=0;
  int howmanyWs=0;
  
  for(int i=0;i<Nparticles;i++)
  {
    particle_pdgId = t12->genParticle_pdgId->at(i);
    if(TMath::Abs(particle_pdgId) != 23 and TMath::Abs(particle_pdgId) != 24)
    { continue;}
    howmanyWs+=1;
    pdgId_dau = t12->genParticle_dau->at(i);
    for(int d=0;d<pdgId_dau.size();d++)
    {
      if(TMath::Abs(pdgId_dau.at(d)) <= 8)
      {
	isHadronic +=1;
      }
      if(TMath::Abs(pdgId_dau.at(d)) <= 18 and TMath::Abs(pdgId_dau.at(d)) >=11)
      {
	isLeptonic +=1;
      }
    }
  }
  if(howmanyWs!=2)
  {
    return 1;
  }
//   std::cout << "Ws : " <<howmanyWs <<std::endl;
//   std::cout <<"had :  " <<isHadronic << std::endl;
//   std::cout <<"lep :  " <<isLeptonic << std::endl;
  if(isHadronic >=4)
  {
    ishad =1;
  }
  if(isLeptonic>=4)
  {
   islep=1; 
  }
  if(isHadronic ==2 and isLeptonic ==2)
  {
   islephad=1; 
  }
  if(decayMode.find("lvjj")!=string::npos or decayMode.find("lljj")!=string::npos)
  {
    return islephad; 
  }
  if(decayMode.find("lvlv")!=string::npos or decayMode.find("llll")!=string::npos)
  {
    return islep; 
  }
  if(decayMode.find("jjjj") !=string::npos)
  {
    return ishad; 
  }
  else
    return 0;
}

//-----------------------------------------------------------------------------
//------------------------------------------------------------------------------
vector<vector<int> > generatedSemiLepEventClassification(int howmany,MyClass* t12)
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
     t12->fChain->GetEntry(i);
     for(int k=0;k<t12->genParticle_N;k++)
       {
	 if(TMath::Abs(t12->genParticle_pdgId->at(k))==39)
	   {
	     vector<int> GDaughter=t12->genParticle_dau->at(k);
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
	 vector<int> numW= findParticle(24,t12);
	 for(int count2=0;count2<numW.size();count2++)
	   {
	     vector<int> dau = getDaughterPdgId(numW.at(count2),t12);
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
	 vector<int> numW= findParticle(39,t12);
	 for(int count2=0;count2<numW.size();count2++)
	   {
	     vector<int> dau= getDaughterPdgId(numW.at(count2),t12);
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
 

 cout<<"# events with electrons in final state "<< NumberOfEventsWithEl<< endl; 
 cout<<"# events with muons in final state "<< NumberOfEventsWithMu<< endl; 
 cout<<"# events with tauons in final state "<< NumberOfEventsWithTau<< endl; 

 return result;
}
 




//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

vector<vector<int> > selectTauEvents(vector<int> events,int pdgId_lepton, int pdgId_mother, MyClass* t12)
{   
 

 vector<int> bratioTau={0,0};
 vector<vector<int> > result(2);
 int case1=0;

for(int i=0;i<events.size();i++)
   {
     t12->fChain->GetEntry(events.at(i));
     for(int ii=0;ii<t12->genParticle_N;ii++)
       {
	 if(TMath::Abs(t12->genParticle_pdgId->at(ii))== pdgId_lepton)
	   {
	     vector<int> l_moth = t12->genParticle_mother->at(ii);
	     for(int iii=0;iii<l_moth.size();iii++)
	       {
		 if(TMath::Abs(l_moth.at(iii))!=pdgId_mother and TMath::Abs(l_moth.at(iii)) != pdgId_lepton)
		   {case1 +=1;}
	       }
		   
	     if(case1>0)
	       continue;
	     vector<int> l_dau =t12->genParticle_dau->at(ii);
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

vector<int> EventSelectionElectron(int howmany, MyClass* t12)
{
 
  int N_loose =0;
  int N_tight =0;
  vector<int> event={};
  for(int i=0;i<howmany;i++)
    {
      t12->fChain->GetEntry(i);
      
      for(int p=0;p<t12->el_N;p++)
	{
	 
	  if(isTightElectron(p,t12)==1)
	    {
	      N_tight +=1;
	    }

	  if(isLooseElectron(p,t12)==1)
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


vector<int> EventSelectionMuon(int howmany, MyClass* t12)
{
 
 int N_loose =0;
 int N_tight =0;
 vector<int> event={};

 for(int i=0;i<howmany;i++)
   {
     t12->fChain->GetEntry(i);
	  for(int p=0;p<t12->mu_N;p++)
	    {
	      if(isTightMuon(p,t12)==1)
	    	{N_tight +=1;}
	      if(isLooseMuon(p,t12)==1)
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
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int applyLeptonSelection_NoVeto( int pdgId ,  MyClass* t12)
{
 bool  BV= 1;/*applyBVeto(t12);*/
  bool LLV= 1;/*applyLooseLeptonVeto(pdgId,t12);*/
  bool  TL= hasTightLepton(pdgId,t12);
  bool MET= 1;/*applyMET(pdgId,t12);*/
  
  if(BV and LLV and TL)
    return 1;
  else
    return 0;  
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

int applyLeptonSelection( int pdgId ,  MyClass* t12)
{
 bool  BV= applyBVeto(t12);
  bool LLV= applyLooseLeptonVeto(pdgId,t12);
  bool  TL= hasTightLepton(pdgId,t12);
  bool MET= applyMET(pdgId,t12);
  
  if(BV and LLV and TL)
    return 1;
  else
    return 0;  
}



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int applyLeptonSelection_NoBVeto( int pdgId , MyClass* t12)
{
  bool  BV= 1; /*applyBVeto(t12);*/
  bool LLV= applyLooseLeptonVeto(pdgId,t12);
  bool  TL= hasTightLepton(pdgId,t12);
  bool MET= applyMET(pdgId,t12);
  
  if(BV and LLV and TL)
    return 1;
  else
    return 0;

}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int applyLeptonSelection_NoLooseLeptonVeto( int pdgId ,  MyClass* t12)
{
  bool  BV= applyBVeto(t12);
  bool LLV= 1;/*applyLooseLeptonVeto(pdgId,t12);*/
  bool  TL= hasTightLepton(pdgId,t12);
  bool MET= applyMET(pdgId,t12);
  
  if(BV and LLV and TL)
    return 1;
  else
    return 0;
 
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int applyMET(int pdgId, MyClass* t12)
{
  int missEt=0;
  if(pdgId ==11)
  {
     //missing transverse Energy veto
      if(t12->MET_et->size()>1)
	{cout << " event with t12->MET vector bigger 1" << endl;}
      if(t12->MET_et->at(0)> WWMETPTELE)
	{missEt+=1;}
  }
  if(pdgId ==13)
  {
	//missing transverse Energy veto
      if(t12->MET_et->size()>1)
	{cout << " event with t12->MET vector bigger 1" << endl;}
      if(t12->MET_et->at(0)> WWMETPTMU)
	{missEt+=1;}
  }  
  return missEt;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int hasTightLepton( int pdgId ,  MyClass* t12)
{
  int N_tight=0;
  
  if(TMath::Abs(pdgId) == 11)
    {
      for(int p=0;p<t12->el_N;p++)
	{
	 if(isTightElectron(p,t12) ==0)
	    continue;
	 N_tight +=1;
	}
    }
  if(TMath::Abs(pdgId)==13)
    {
      
      for(int p=0;p<t12->mu_N;p++)
	{
	 if(isTightMuon(p,t12)==0)
	   continue;
	 N_tight +=1;
	}
      
    }
  if(N_tight!=0)
    return 1;
  else 
    return 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int applyVetos( int pdgId, MyClass* t12)
{
  if(applyBVeto(t12)==1 and applyLooseLeptonVeto(pdgId,t12)==1)
    return 1;
  else
    return 0;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int applyBVeto(MyClass* t12)
{
  int vetoAK4=0;
      //  b- tagged jet veto
   for(int j=0;j<t12->jetAK4_N;j++)
    {
      if(isVetoAK4jet(j,t12)==0)
	continue;
      vetoAK4 =1;
    }
    if(vetoAK4 ==0)
      return 1;
    else
      return 0;
  
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int applyLooseLeptonVeto(int pdgId, MyClass* t12)
{
  int N_loose_e =0;
  int N_loose_mu=0;
  
  for(int k=0;k<t12->el_N;k++)
    { if(isLooseElectron(k,t12)==0)
	continue;
      N_loose_e +=1;   
    }
  for(int k=0;k<t12->mu_N;k++)
    {
      if(isLooseMuon(k,t12)==0)
	 continue;
      N_loose_mu +=1;
    }
	
  if(pdgId==11 and N_loose_e<2 and N_loose_mu==0)
      return 1;
  if(pdgId==13 and N_loose_e==0 and N_loose_mu<2)
      return 1;
  else
      return 0;
  
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int applyHadronSelection( MyClass* t12,bool isHP, bool isLP, bool isW, bool isZ)
{
  int N_rightJets=0;

  for(int i=0;i<t12->jetAK8_N;i++)
  {
   if(isRightAK8jet(i,t12)==0)
     continue;
    else 
    {
   double MassMin=0;
   double MassMax=0;
   if(isW and !isZ){MassMin = WWAK8JETMASSMIN; MassMax = WWAK8JETMASSMAX;}
   if(!isW and isZ){MassMin = WZAK8JETMASSMIN; MassMax = WZAK8JETMASSMAX;}
   if(!isW and !isZ){}
   if(isW and isZ){MassMin =WWAK8JETMASSMIN; MassMax = WZAK8JETMASSMAX;}
     if( (t12->jetAK8_pruned_massCorr->at(i)> MassMin and t12->jetAK8_pruned_massCorr->at(i)< MassMax))
     {
     Double_t tau21 = t12->jetAK8_tau2->at(i)/t12->jetAK8_tau1->at(i);
     
     if(isHP and !isLP and tau21 < WWAK8JETTAU21HIGHPURITY){ N_rightJets = 1;}
     if(!isHP and isLP and (WWAK8JETTAU21HIGHPURITY < tau21 and tau21 < WWAK8JETTAU21LOWPURITY)) {N_rightJets =1;}
     if(!isHP and !isLP){N_rightJets =1;}
     if(isHP and isLP and tau21 < WWAK8JETTAU21LOWPURITY){ N_rightJets =1;}
     }
     break;
    }
  }
  
  return N_rightJets;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int applyBackToBackTopology(TLorentzVector l,TLorentzVector W_had, TLorentzVector W_lep , TLorentzVector n)
{
  
  Double_t Delta_phi 	= TMath::Abs(W_had.DeltaPhi(n));
  Double_t Delta_phi_W 	= TMath::Abs(W_had.DeltaPhi(W_lep));
  Double_t Delta_R 	= TMath::Abs(l.DeltaR(W_had));
  //std::cout << " dphi_nu_whad: " << Delta_phi 
  //  <<" dphi_whad_wlep: " << Delta_phi_W
  //   << " dr_l_whad " << Delta_R <<std::endl;
  
  if(Delta_phi> WWDELTAPHIWHADMET and Delta_phi_W> WWDELTAPHIWHADWLEP and Delta_R> WWDELTARWHADLEPTON)
    return 1;
  else
    return 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

int EventSelection( int pdgId,MyClass* t12)
{
  bool rightEvent = applyLeptonSelection( pdgId, t12) and applyHadronSelection(t12);
  if(rightEvent)
    return 1;
  else
    return 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


int generatedEventSelection( int pdgId, MyClass* t12,bool applyMassCut)
{
  bool R=0;
  bool WM=0;
  TLorentzVector W_had = getLVofGenParticle( 24, t12);
  if(W_had.M()==0){W_had = getLVofGenParticle(23,t12);}
  TLorentzVector l = getLVofGenParticle(pdgId,t12);
  TLorentzVector n = getLVofGenParticle(pdgId +1, t12);
  TLorentzVector W_lep = l+n;
  Double_t WWmass = (W_had + W_lep).M();
  if(WWmass< WWMASSMAX and WWmass> WWMASSMIN)
  {WM=1;}
  if(!applyMassCut)
  {WM=1;}
 // std::cout << " found W with mass: " << W_lep.M() << std::endl;
 // std::cout << "W_Lep_kin: " << kinematicCuts(W_lep.Pt(),W_lep.Eta(),24)
//    << " W_had_kin: " << kinematicCuts(W_had.Pt(),W_had.Eta(), 24)
 //   << " lep_kin: " << kinematicCuts(l.Pt(), l.Eta(),pdgId)
  //  << " nu_kin: " << kinematicCuts(n.Pt(), n.Eta(),pdgId+1)
   // << " b2b2: "<< applyBackToBackTopology(l,W_had,W_lep,n) <<std::endl;
    if(W_lep.M()!=0)
  {
    if(!applyMassCut)
    {
      R =(kinematicCuts(W_lep.Pt(),W_lep.Eta(),24) and kinematicCuts(l.Pt(), l.Eta(),pdgId) and kinematicCuts(n.Pt(),n.Eta(),pdgId+1)) and applyBackToBackTopology(l,W_had,W_lep,n); 
    }
    else
    {
    R =(kinematicCuts(W_had.Pt(),W_had.Eta(), 24) and kinematicCuts(W_lep.Pt(),W_lep.Eta(),24) and kinematicCuts(l.Pt(), l.Eta(),pdgId) and kinematicCuts(n.Pt(),n.Eta(),pdgId+1)) and applyBackToBackTopology(l,W_had,W_lep,n);
    }
  }
  if(R==1 and WM==1)
    return 1;
  else 
    return 0;

}

//-----------------------------------------------------------------------------

//goes through generated events and
//fills the vectors with the eventnumber of:
//WWelectron = #W =2, one W decays semileptonic to e
//WWmuon = #W =2, one W decays semileptonic to mu
//WWtauon = #W =2, one W decays semileptonic to tau
//missingW.=#W <2 
vector<vector<int> > genDataEventSeparationSemileptonicWW(int howmany,MyClass* t12)
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
 cout << " the file has " << t12->fChain->GetEntries()<< "events" << endl;

 for(int event=0; event<howmany; event++)
    {
      t12->fChain->GetEntry(event);
         
	  for(int loop =0;loop<t12->genParticle_N ;loop++)
	    {
	      if(TMath::Abs(t12->genParticle_pdgId->at(loop)) == 24)
		{
		  //counter2 counts W Bosons in the decay
		  counter2 +=1;
		  vector<int> pD = t12->genParticle_dau->at(loop);
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
	 t12->fChain->GetEntry(tmp.at(i));
	   for(int ii=0; ii<t12->genParticle_N;ii++)
	     {
	       if(t12->genParticle_pdgId->at(ii)== 39)
		 {
		   vector<int> gp_dau = t12->genParticle_dau->at(ii);
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

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

bool applyTrigger(int pdgId, MyClass* t12)
{
  bool passedTrigger=0;
  if(pdgId==11 && (isTriggerFired("HLT_Ele105_CaloIdVT_GsfTrkIdT",t12) or isTriggerFired("HLT_Ele115_CaloIdVT_GsfTrkIdT",t12)))
  {
    passedTrigger =1;
  }
  if(pdgId==13 && (isTriggerFired("HLT_Mu45_eta2p1",t12) /*or isTriggerFired("HLT_Mu50",t12)*/))
  {
    passedTrigger =1;
  }
  return passedTrigger;
}

//=======================================================================================
//=========== apply trigger for all-hadronic part =======================================
//=======================================================================================

bool applyTriggerAllHadronic(MyClass* t12)
{
  if(isTriggerFired(T1,t12))
    return 1;
  if(isTriggerFired(T2,t12))
    return 1;
  if(isTriggerFired(T3,t12))
    return 1;
  if(isTriggerFired(T4,t12))
    return 1;
  if(isTriggerFired(T5,t12))
    return 1;
  else
    return 0;
}



