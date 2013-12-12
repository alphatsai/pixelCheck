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
using namespace std;

string samplePath    = "/afs/cern.ch/work/r/rslu/public/FNAL2013_data";
string storeRootPath = "../result/root";
string storePngPath  = "../result/png";
vector<string> sampleName;
	samples.push_back("tree_34318_");
	samples.push_back("tree_35113_");

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

pixelCheck(){
	for( unsigned int ismaple=0; isample<sampleName.size(); isample++){
		////= Input and prepare the out files ===========================================================================
		string input  	=    samplePath + "/" + sampleName[isample] + ".root";
		string output 	= storeRootPath + "/" + sampleName[isample] + ".root";
		TFile* input_f  = new TFile(input.c_str()); 
		TFile* output_f = new TFile(output.c_str(),"RECREATE"); 	
	
		for( int index=0; index<ROC_Size; index++){ 
			output_f->mkdir(index_ROC[i]);
			output_f->cd(index_ROC[i]);
				TH1F*  
			output_f->cd(); 
		}	
		
		////= Regist tree and branch ====================================================================================
		TTree* tree = (TTree*)input_f->Get("tree");
		Branches Hit;
		Hit.Register(tree);	
		
		////= Loop for each hit =========================================================================================
		for( int hit=0; hit<tree->GetEntries; hit++){
			tree->GetEntry(hit);				
			output_f->cd(index_ROC[Hit.ROCnumber]);
			
		}//Hit	
		output_f->Write();
	}//sample
}


















