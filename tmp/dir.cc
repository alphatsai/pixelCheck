#include <map>
#include <iostream>
#include <string>
#include "TFile.h"
#include "TH1F.h"
using namespace std;
void dir(){
    /*map<int, string> d;
        d[0]="aa";
        d[1]="bb";*/
    const char* d[2]={
		"aa",
		"bb"

	};
//        d[0]="aa";
//        d[1]="bb";
    TFile* f=new TFile("dir.root","RECREATE");
    //for( unsigned int i=0; i<d.size(); i++){
    for( unsigned int i=0; i<2; i++){
      //f->mkdir(d.find(i)->second.c_str());
      f->mkdir(d[i]);
      f->cd(d[i]);
          TH1F* H1=new TH1F("H1","", 20,1,20);
          TH1F* H2=new TH1F("H2","", 20,1,20);
      f->cd();
    }
    f->Write();
}
