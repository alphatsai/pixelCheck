#ifndef FORMAT_H
#define FORMAT_H


#include <TTree.h>

class Branches{
 public:
  int EventNumber;
  int TriggerCount;
  int TriggerPhase;
  int TriggerPattern;
  int TimeStamp;
  int ROCnumber;
  int col;
  int row;
  int raw;
  int flag;
  
  void RegisterTree(TTree *root) {
  	root->Branch("EventNumber",	&EventNumber,	"EventNumber/I");
  	root->Branch("TriggerCount",	&TriggerCount,	"TriggerCount/I");
  	root->Branch("TriggerPhase",	&TriggerPhase,	"TriggerPhase/I");
  	root->Branch("TriggerPattern",	&TriggerPattern,	"TriggerPattern/I");
  	root->Branch("TimeStamp",	&TimeStamp,	"TimeStamp/I");
  	root->Branch("ROCnumber",	&ROCnumber,	"ROCnumber/I");
  	root->Branch("col",	&col,	"col/I");
  	root->Branch("row",	&row,	"row/I");
  	root->Branch("raw",	&raw,	"raw/I");
  	root->Branch("flag",	&flag,	"flag/I");
  }										    

  void Register(TTree *root) {
  	root->SetBranchAddress("EventNumber",	&EventNumber);
  	root->SetBranchAddress("TriggerCount",	&TriggerCount);
  	root->SetBranchAddress("TriggerPhase",	&TriggerPhase);
  	root->SetBranchAddress("TriggerPattern",	&TriggerPattern);
  	root->SetBranchAddress("TimeStamp",	&TimeStamp);
  	root->SetBranchAddress("ROCnumber",	&ROCnumber);
  	root->SetBranchAddress("col",	&col);
  	root->SetBranchAddress("row",	&row);
  	root->SetBranchAddress("raw",	&raw);
  	root->SetBranchAddress("flag",	&flag);
  }  


}; 

  
    
