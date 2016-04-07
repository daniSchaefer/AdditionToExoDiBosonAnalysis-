

//fills histo2 with the recontructed transversal impulse and histo1 with the pseudorapidity of the W boson
// decauymode has to be leptonic; the generated events are used
void getgenX_eta_pt(TH1F* histo1, TH1F* histo2,vector<int> events, int pdgId_lepton, int pdgId_mother,vector<vector<double> > leptonSelection, int X , MyClass* t12);


//same as above but without kinematic constrictions on leptons
void getgenX_eta_pt_wv(TH1F* histo1,TH1F* histo2 ,vector<int> events, int pdgId_lepton, int pdgId_mother ,vector<vector<double> >leptonSelection , int X, MyClass* t12);


// seperate the event in lists that contain the events with W->e, W-> mu ...
vector<vector<int> > genDataEventSeparationSemileptonicWW(int howmany, MyClass* t12);

//get kinematics of particle X , first howmany events
//applies lepton cuts, b-jet veto and missing Et cut
void getX_eta_pt(TH1F* histo1, TH1F* histo2, int howmany, int X, MyClass* t12);

// same as above but applies only lepton cuts
void getX_eta_pt_onlyLeptonCuts(TH1F* histo1,TH1F* histo2 ,int howmany, int X, MyClass* t12);
//-------------------------------------------------------------------------------
//----------------------------------------------------------------------------


void getgenX_eta_pt_wv(TH1F* histo1,TH1F* histo2 ,vector<int> events, int pdgId_lepton, int pdgId_mother ,vector<vector<double> >leptonSelection , int X , MyClass* t12)
{
  
  int case1 =0;
  int case2=0;
for(int i=0;i<events.size();i++)
   {
     t12->fChain->GetEntry(events.at(i));
     TLorentzVector lepton;
     TLorentzVector neutrino;
     TLorentzVector lepton1;
     for(int ii=0;ii<t12->genParticle_N;ii++)
       {
	 if(TMath::Abs(t12->genParticle_pdgId->at(ii))== pdgId_lepton)
	   {
	     vector<int> l_moth = t12->genParticle_mother->at(ii);
	     for(int iii=0;iii<l_moth.size();iii++)
	       {
		 if(TMath::Abs(l_moth.at(iii))==pdgId_mother)
		   {
		     Double_t pt =t12->genParticle_pt->at(ii);
		     Double_t eta =t12->genParticle_eta->at(ii);
		     Double_t phi =t12->genParticle_phi->at(ii);
		     Double_t e = t12->genParticle_e->at(ii);
		     lepton.SetPtEtaPhiE(pt,eta,phi,e);
		   }
	       }
	     if(pdgId_lepton == 15)
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
			       {
				 Double_t pt =t12->genParticle_pt->at(ii);
				 Double_t eta =t12->genParticle_eta->at(ii);
				 Double_t phi =t12->genParticle_phi->at(ii);
				 Double_t e = t12->genParticle_e->at(ii);
				 lepton1.SetPtEtaPhiE(pt,eta,phi,e);
			       }
			   }
		       }
		     if(TMath::Abs(l_dau.at(k))==13)
		       {for(int kk=0;kk<l_dau.size();kk++)
			   {
			     if(TMath::Abs(l_dau.at(kk))==14)
			       {
				 Double_t pt =t12->genParticle_pt->at(ii);
				 Double_t eta =t12->genParticle_eta->at(ii);
				 Double_t phi =t12->genParticle_phi->at(ii);
				 Double_t e = t12->genParticle_e->at(ii);
				 lepton1.SetPtEtaPhiE(pt,eta,phi,e);
				 case2+=1;
			       }
			   }
		       }

		   }
	       }
	   }
	 if(TMath::Abs(t12->genParticle_pdgId->at(ii))== (pdgId_lepton +1))
	   {
	     vector<int> n_moth = t12->genParticle_mother->at(ii);
	     for(int iii=0;iii<n_moth.size();iii++)
	       {
		 if(TMath::Abs(n_moth.at(iii))==pdgId_mother)
		   {
		     Double_t pt = t12->genParticle_pt->at(ii);
		     Double_t phi =t12->genParticle_phi->at(ii);
		     Double_t eta =t12->genParticle_eta->at(ii);
		     Double_t e = t12->genParticle_e->at(ii);
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


// ------------------------------------------------------------------------------
// -----------------------------------------------------------------------------



void getgenX_eta_pt(TH1F* histo1,TH1F* histo2 ,vector<int> events, int pdgId_lepton, int pdgId_mother ,vector<vector<double> >leptonSelection , int X,MyClass * t12)
{

int case1 =0;
int case2=0;
for(int i=0;i<events.size();i++)
   {
     t12->fChain->GetEntry(events.at(i));
     TLorentzVector lepton;
     TLorentzVector neutrino;
     TLorentzVector lepton1;
     for(int ii=0;ii<t12->genParticle_N;ii++)
       {
	 if(TMath::Abs(t12->genParticle_pdgId->at(ii))== pdgId_lepton)
	   {
	     vector<int> l_moth = t12->genParticle_mother->at(ii);
	     for(int iii=0;iii<l_moth.size();iii++)
	       {
		 if(TMath::Abs(l_moth.at(iii))==pdgId_mother)
		   {
		     Double_t pt =t12->genParticle_pt->at(ii);
		     Double_t eta =t12->genParticle_eta->at(ii);
		     Double_t phi =t12->genParticle_phi->at(ii);
		     Double_t e = t12->genParticle_e->at(ii);
		     lepton.SetPtEtaPhiE(pt,eta,phi,e);
		   }
	       }
	     if(pdgId_lepton == 15)
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
			       {
				 Double_t pt =t12->genParticle_pt->at(ii);
				 Double_t eta =t12->genParticle_eta->at(ii);
				 Double_t phi =t12->genParticle_phi->at(ii);
				 Double_t e = t12->genParticle_e->at(ii);
				 lepton1.SetPtEtaPhiE(pt,eta,phi,e);
			       }
			   }
		       }
		     if(TMath::Abs(l_dau.at(k))==13)
		       {for(int kk=0;kk<l_dau.size();kk++)
			   {
			     if(TMath::Abs(l_dau.at(kk))==14)
			       {
				 Double_t pt =t12->genParticle_pt->at(ii);
				 Double_t eta =t12->genParticle_eta->at(ii);
				 Double_t phi =t12->genParticle_phi->at(ii);
				 Double_t e = t12->genParticle_e->at(ii);
				 lepton1.SetPtEtaPhiE(pt,eta,phi,e);
				 case2+=1;
			       }
			   }
		       }

		   }
	       }
	   }
	 if(TMath::Abs(t12->genParticle_pdgId->at(ii))== (pdgId_lepton +1))
	   {
	     vector<int> n_moth = t12->genParticle_mother->at(ii);
	     for(int iii=0;iii<n_moth.size();iii++)
	       {
		 if(TMath::Abs(n_moth.at(iii))==pdgId_mother)
		   {
		     Double_t pt = t12->genParticle_pt->at(ii);
		     Double_t phi =t12->genParticle_phi->at(ii);
		     Double_t eta =t12->genParticle_eta->at(ii);
		     Double_t e = t12->genParticle_e->at(ii);
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

//-----------------------------------------------------------------------------
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


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void getX_eta_pt(TH1F* histo1,TH1F* histo2 ,int howmany, int X, MyClass* t12)
{

 
  Double_t eta=0;
  Double_t pt=0;
  
  for(int i=0;i<howmany;i++)
    {
      t12->fChain->GetEntry(i);
      if(TMath::Abs(X)==11)
	{
	  if(applyLeptonSelection(11,t12)==1)
	    {
	      for(int k=0;k<t12->el_N;k++)
		{
		  if(isTightElectron(k, t12)==1)
		    {
		      eta = t12->el_eta->at(k);
		      pt = t12->el_pt->at(k);
		      histo1->Fill(eta);
		      histo2->Fill(pt); 
		    }
		}
	      
	    }
	}
      if(TMath::Abs(X)==13)
	{
	  if(applyLeptonSelection(13,t12)==1)
	    {
	      for(int k=0;k<t12->mu_N;k++)
		{
		  if(isTightMuon(k, t12)==1)
		    {
		      eta = t12->mu_eta->at(k);
		      pt = t12->mu_pt->at(k);
		      histo1->Fill(eta);
		      histo2->Fill(pt); 
		    }
		}
	      
	    }
	}
    }
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


void getX_eta_pt_onlyLeptonCuts(TH1F* histo1,TH1F* histo2 ,int howmany, int X, MyClass* t12)
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
      t12->fChain->GetEntry(i);
      for(int k=0;k<t12->el_N;k++)
	{ if(isLooseElectron(k,t12)==1)
	       {N_loose_e +=1;}}
      for(int k=0;k<t12->mu_N;k++)
	{ if(isLooseMuon(k,t12)==1)
	    {N_loose_mu +=1;}}
      if(TMath::Abs(X) == 11)
	{
	  for(int p=0;p<t12->el_N;p++)
	    {
	      
	      if(isTightElectron(p,t12) ==1)
		{
		  eta= t12->el_eta->at(p);
		  pt = t12->el_pt->at(p);
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
	
  	  for(int p=0;p<t12->mu_N;p++)
  	    {
	      //muon kin. contrictions
	      if(isTightMuon(p,t12)==1)
  	    	{
  	    	  eta= t12->mu_eta->at(p);
  	    	  pt = t12->mu_pt->at(p);
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
