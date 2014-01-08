#ifndef FITPARAMETER_H
#define FITPARAMETER_H


#include <TTree.h>

class fitParameter{
 public:
  int RunNumber;
  double Flux;
  double p0_1;
  double p1_1;
  double e0_1;
  double e1_1;
  double p0_2;
  double p1_2;
  double e0_2;
  double e1_2;
  
  void RegisterTree(TTree *root) {
  	root->Branch("RunNumber",	&RunNumber,	"RunNumber/I");
  	root->Branch("Flux",	&Flux,	"Flux/D");
  	root->Branch("p0_1",	&p0_1,	"p0_1/D");
  	root->Branch("p1_1",	&p1_1,	"p1_1/D");
  	root->Branch("e0_1",	&e0_1,	"e0_1/D");
  	root->Branch("e1_1",	&e1_1,	"e1_1/D");
  	root->Branch("p0_2",	&p0_2,	"p0_2/D");
  	root->Branch("p1_2",	&p1_2,	"p1_2/D");
  	root->Branch("e0_2",	&e0_2,	"e0_2/D");
  	root->Branch("e1_2",	&e1_2,	"e1_2/D");
  }										    

  void Register(TTree *root) {
  	root->SetBranchAddress("RunNumber",	&RunNumber);
  	root->SetBranchAddress("Flux",	&Flux);
  	root->SetBranchAddress("p0_1",	&p0_1);
  	root->SetBranchAddress("p1_1",	&p1_1);
  	root->SetBranchAddress("e0_1",	&e0_1);
  	root->SetBranchAddress("e1_1",	&e1_1);
  	root->SetBranchAddress("p0_2",	&p0_2);
  	root->SetBranchAddress("p1_2",	&p1_2);
  	root->SetBranchAddress("e0_2",	&e0_2);
  	root->SetBranchAddress("e1_2",	&e1_2);
  }  


}; 

#endif  
    
