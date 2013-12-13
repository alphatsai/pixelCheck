#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include "TMath.h"
#include "TFile.h"
#include "../interface/Parameters.h"	// Define parameters, input/output files
#include "../interface/format.h"
#include "../interface/TH1Info.h"	// Histogram details are defined here
#include "../interface/TH1InfoClass.h"	 
#include "../interface/TH2Info.h"	// Histogram details are defined here
#include "../interface/TH2InfoClass.h"	 
using namespace std;

// Detail information for data
const int Row_Size = 80;
const int Col_Size = 52;
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

// Change int to string
string int2str(int &i){
	string s;
	stringstream ss(s);
	ss << i;
	return ss.str();
}

void pixelCheck(){
	for( int isample=0; isample<Sample_Size; isample++){
		////= Input and prepare the out files ===========================================================================
		string input 	=    samplePath + "/" + sampleName[isample] + ".root";
		string output	= storeRootPath + "/" + sampleName[isample] + ".root";
		TFile* input_f	= new TFile(input.c_str()); 
		TFile* output_f	= new TFile(output.c_str(),"RECREATE"); 
		cout<<"Success read "<<input<<" !"<<endl;	
	
		////= Regist tree and branch ====================================================================================
		TTree* tree = (TTree*)input_f->Get("tree");
		Branches Hit;
		Hit.Register(tree);	
		cout<<"Success register tree!"<<endl;	

		////= Create Histogram, create sub-directory and initialize variables ===========================================
		int hits[ROC_Size][Row_Size][Col_Size];

		TH2InfoClass<TH2_Type> h2[ROC_Size];
		TH1InfoClass<TH1_Type> h1[ROC_Size];

		for( int index=0; index<ROC_Size; index++){ 
			output_f->mkdir(index_ROC[index]);
			output_f->cd(index_ROC[index]);

				h2[index].Initialize();
				h1[index].Initialize();
				cout<<"Success create TH1 and TH2 in "<<index_ROC[index]<<" !"<<endl;	

			output_f->cd();

			for( int r=0; r<Row_Size; r++){
				for( int c=0; c<Col_Size; c++){
					hits[index][r][c]=0; // inintialize	
				} // colume
			} // row
			 
		} // roc
	
		TH1D* h_hits = new TH1D("TotalHits", "Total Hits", 9, -1, 8);
		h_hits->GetXaxis()->SetBinLabel(1,"X_X");
		h_hits->GetXaxis()->SetBinLabel(2,index_ROC[0]);
		h_hits->GetXaxis()->SetBinLabel(3,index_ROC[1]);
		h_hits->GetXaxis()->SetBinLabel(4,index_ROC[2]);
		h_hits->GetXaxis()->SetBinLabel(5,index_ROC[3]);
		h_hits->GetXaxis()->SetBinLabel(6,index_ROC[4]);
		h_hits->GetXaxis()->SetBinLabel(7,index_ROC[5]);
		h_hits->GetXaxis()->SetBinLabel(8,index_ROC[6]);
		h_hits->GetXaxis()->SetBinLabel(9,index_ROC[7]);	

		////= Loop for each hit, Fill Histogram =========================================================================================
		cout<<"Running..."<<endl;	
		for( int hit=0; hit<tree->GetEntries(); hit++){
			tree->GetEntry(hit);			
			h_hits->Fill(Hit.ROCnumber);
			if( Hit.ROCnumber < 0 ) continue; 	// Some Hit.ROCnumber = -1	
			output_f->cd(index_ROC[Hit.ROCnumber]);	// Enter the ROC_number directory
			
				string hits_row = "Hits_Row_" + int2str(Hit.row);	
				h2[Hit.ROCnumber].GetTH2("HitsMap")->Fill(Hit.col,Hit.row);
				h1[Hit.ROCnumber].GetTH1("ROCnumber")->Fill(Hit.ROCnumber);
				h1[Hit.ROCnumber].GetTH1("Row")->Fill(Hit.raw);
				h1[Hit.ROCnumber].GetTH1("Column")->Fill(Hit.col);
				if( Hit.raw>=0 && Hit.col>=0 ){
					h1[Hit.ROCnumber].GetTH1(hits_row)->Fill(Hit.col);	
					hits[Hit.ROCnumber][Hit.row][Hit.col]++;
				}

			output_f->cd(); // Exit
		} // Hit

		for( int i=0; i<ROC_Size; i++){ // Caculate ideal hits for each column in each row
			for( int j=0; j<Row_Size; j++){
				string hits_row = "Hits_Row_" + int2str(j) + "_ideal";
				for( int k=0; k<Col_Size; k++){
					double idealHits;
					//if( k>0 && k<Col_Size-1 ){
					if( k>1 && k<Col_Size-2 ){
						//idealHits = double( hits[i][j][k+1] + hits[i][j][k-1] )/2;
						idealHits = double( hits[i][j][k+2] + hits[i][j][k+1] + hits[i][j][k-1] + hits[i][j][k-2])/4;
					}else{
						idealHits = hits[i][j][k];
					}	
					h1[i].GetTH1(hits_row)->Fill(k,idealHits);
				} // Column
			} //Row
		} // Roc
		output_f->Write();
		cout<<"Success write into "<<output<<" !"<<endl<<endl;	
	} // sample
}




