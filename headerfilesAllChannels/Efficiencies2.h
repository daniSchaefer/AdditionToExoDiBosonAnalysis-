#ifndef EFFICIENCY2_H
#define EFFICIENCY2_H

//writes following histos in file:
//h_lep_rec ->full analysis selection even hadronic part!
//h_lep_gen ->only vetos
//h_had_rec same as above only function of hadronic W pt and eta
//h_had_gen
//h_lep_rew -> leptonic W pt and eta reweighted with the efficiencies from narrow BG sample
//h_had_rew ->same for hadronic pt eta
//file ending is _testEff.root !
vector<double> makeEfficiencyTest(string ModelName,string channel,string category ,float mass, float width);

//returns:
//result[0] ->exact efficiency
//result[1] ->Eff from bulk G narrow sample tables
//result[x][0] mu channel
//result[x][1] el channel
//result[x][2] hadronic channel (ele and mu combined)
 vector<vector<double> > ExtractRecoAndTestEfficiency(string ModelName,string category ,float mass ,float width);
 

 void PrintReconstructionEfficiencyTable(string ModelName,string category,vector<float> massPoints,float width ,string caption);
 
 void EfficiencyUncertaintyForDatacards(vector<float> mass,string channel, string category);
#endif