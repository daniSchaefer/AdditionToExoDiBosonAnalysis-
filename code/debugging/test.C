#include "TROOT.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TChain.h"
#include "TEfficiency.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cassert>
#include "/usr/users/dschaefer/root/headerfilesAllChannels/CMS_lumi.h"

using namespace std;


// note to this construct:
// is needed in this version of root in order to get the header functions right
//also the order in which these files are compiled matters!
// namespace{
//   int loadMyLibraryTriggerFunc(){
//  gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/CMS_lumi.C+");
//   //gROOT->ProcessLine(".L /usr/users/dschaefer/root/headerfilesAllChannels/tdrstyle.C+");
//  return 0;
// }
//   int loadMyLibraryTrigger = loadMyLibraryTriggerFunc();
// }

#include <map>
#include <string>




void test()
{
//   std::map<char,float> mymap;
//   mymap.insert(char,float>('a',0.56));
//   
//  std::cout << mymap.find('a')<<std::endl;
  
  std::map<char,float> mymap;

  // first insert function version (single parameter):
  mymap.insert ( std::pair<char,float>('a',100) );
  mymap.insert ( std::pair<char,float>('z',200) );
  std::cout << mymap.find('a')->second <<std::endl;
  
  std::map<std::string,float> mymap2;
  string s1 = "affe";
  string s2 = "blabla";
  // first insert function version (single parameter):
  mymap2.insert ( std::pair<std::string,float>(s1,100) );
  mymap2.insert ( std::pair<std::string,float>(s2,200) );
  std::cout << mymap2.find("affe")->second <<std::endl;
  
  
  
}