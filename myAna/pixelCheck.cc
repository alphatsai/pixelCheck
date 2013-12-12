#include <fstream>
#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <cstdlib>
#include <vector>
#include "TChain.h"
#include "TPad.h"
#include "TMath.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "../interface/format.h"
#include "../interface/TH1InfoClass.h"
using namespace std;

const string samplePath    = "/afs/cern.ch/work/r/rslu/public/FNAL2013_data";
const string storeRootPath = "../result/root";
const string storePngPath  = "../result/png";

const int Sample_Size = 2;
const string sampleName[Sample_Size] = {
	"tree_34318_",
	"tree_35113_"
};

const int ROC_Size = 8;
const char* index_ROC[ROC_Size] = {
	"ROC_0",
	"ROC_1",
	"ROC_2",
	"ROC_3",
	"ROC_4",
	"ROC_5",
	"ROC_6",
	"ROC_7",
};

void pixelCheck(){

	for( int isample=0; isample<Sample_Size; isample++){
		////= Input and prepare the out files ===========================================================================
		string input  	=    samplePath + "/" + sampleName[isample] + ".root";
		string output 	= storeRootPath + "/" + sampleName[isample] + ".root";
		TFile* input_f  = new TFile(input.c_str()); 
		TFile* output_f = new TFile(output.c_str(),"RECREATE"); 
		cout<<"Success read "<<input<<" !"<<endl;	
	
		////= Regist tree and branch ====================================================================================
		TTree* tree = (TTree*)input_f->Get("tree");
		Branches Hit;
		Hit.Register(tree);	
		cout<<"Success register tree!"<<endl;	

		////= Create Histogram and sub-directory ========================================================================
		TH1D* h_hits = new TH1D("TotalHits", "Total Hits", 8, 0, 8);
		h_hits->GetXaxis()->SetBinLabel(1,"ROC_0");
		h_hits->GetXaxis()->SetBinLabel(2,"ROC_1");
		h_hits->GetXaxis()->SetBinLabel(3,"ROC_2");
		h_hits->GetXaxis()->SetBinLabel(4,"ROC_3");
		h_hits->GetXaxis()->SetBinLabel(5,"ROC_4");
		h_hits->GetXaxis()->SetBinLabel(6,"ROC_5");
		h_hits->GetXaxis()->SetBinLabel(7,"ROC_6");
		h_hits->GetXaxis()->SetBinLabel(8,"ROC_7");

		TH1InfoClass h[ROC_Size];
		for( int index=0; index<ROC_Size; index++){ 
			output_f->mkdir(index_ROC[index]);
			output_f->cd(index_ROC[index]);
				h[index].Initialize();
				cout<<"Success create TH1 in "<<index_ROC[index]<<" !"<<endl;	
			output_f->cd(); 
		}	
		
		////= Loop for each hit =========================================================================================
		cout<<"Running..."<<endl;	
		for( int hit=0; hit<tree->GetEntries(); hit++){
			tree->GetEntry(hit);			
			if( Hit.ROCnumber < 0 ) continue; //Some Hit.ROCnumber = -1	
			h_hits->Fill(Hit.ROCnumber);
			output_f->cd(index_ROC[Hit.ROCnumber]);
				h[Hit.ROCnumber].GetTH1("ROCnumber")->Fill(Hit.ROCnumber);
			output_f->cd();
		}//Hit
		output_f->Write();
		cout<<"Success write into "<<output<<" !"<<endl<<endl;	
	}//sample
}


















