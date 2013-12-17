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
#include "../interface/index_ROC.h"	// Define parameters, input/output files
#include "../interface/format.h"
#include "../interface/TH1Info.h"	// Histogram details are defined here
#include "../interface/TH1InfoClass.h"	 
#include "../interface/TH2Info.h"	// Histogram details are defined here
#include "../interface/TH2InfoClass.h"	 
using namespace std;

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
			output_f->mkdir(index_ROC[index].c_str());
			output_f->cd(index_ROC[index].c_str());

				h2[index].CreateTH2();
				h1[index].CreateTH1();
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
		h_hits->GetXaxis()->SetBinLabel(2,index_ROC[0].c_str());
		h_hits->GetXaxis()->SetBinLabel(3,index_ROC[1].c_str());
		h_hits->GetXaxis()->SetBinLabel(4,index_ROC[2].c_str());
		h_hits->GetXaxis()->SetBinLabel(5,index_ROC[3].c_str());
		h_hits->GetXaxis()->SetBinLabel(6,index_ROC[4].c_str());
		h_hits->GetXaxis()->SetBinLabel(7,index_ROC[5].c_str());
		h_hits->GetXaxis()->SetBinLabel(8,index_ROC[6].c_str());
		h_hits->GetXaxis()->SetBinLabel(9,index_ROC[7].c_str());	

		////= Loop for each hit, Fill Histogram =========================================================================================
		cout<<"Running..."<<endl;	
		for( int hit=0; hit<tree->GetEntries(); hit++){
			tree->GetEntry(hit);			
			h_hits->Fill(Hit.ROCnumber);
			if( Hit.ROCnumber < 0 ) continue; 	// Some Hit.ROCnumber = -1	
			output_f->cd(index_ROC[Hit.ROCnumber].c_str());	// Enter the ROC_number directory
			
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

		// Caculate ideal hits for each column in each row
		for( int i=0; i<ROC_Size; i++){ 
			for( int j=0; j<Row_Size; j++){
				string hits_row   = "Hits_Row_" + int2str(j);
				string hits_row_i = "Hits_Row_" + int2str(j) + "_ideal";
				string ratio      = "Ratio_Row_" + int2str(j);

				for( int k=0; k<Col_Size; k++){
					double idealHits;
					if( k%2==1 ){ // Odd cloumn
						idealHits =  hits[i][j][k-1];
					}else{
						idealHits = hits[i][j][k+1];
					}	
					h1[i].GetTH1(hits_row_i)->Fill(k,idealHits);
				} // Column

				h1[i].GetTH1(ratio)->Divide( h1[i].GetTH1(hits_row), h1[i].GetTH1(hits_row_i) );	
			} //Row
		} // Roc

		output_f->Write();
		cout<<"Success write into "<<output<<" !"<<endl<<endl;	
	} // sample
}



		// Caculate ideal hits for each column in each row
/*		for( int i=0; i<ROC_Size; i++){ 
			for( int j=0; j<Row_Size; j++){
				string hits_row   = "Hits_Row_" + int2str(j);
				string hits_row_i = "Hits_Row_" + int2str(j) + "_ideal";
				string ratio      = "Ratio_Row_" + int2str(j);

				for( int k=0; k<Col_Size; k++){
					double idealHits;
					if( k>0 && k<Col_Size-1 ){
					//if( k>1 && k<Col_Size-2 ){
						idealHits = double( hits[i][j][k+1] + hits[i][j][k-1] )/2;
						//idealHits = double( hits[i][j][k+2] + hits[i][j][k+1] + hits[i][j][k-1] + hits[i][j][k-2])/4;
					}else{
						idealHits = hits[i][j][k];
					}	
					h1[i].GetTH1(hits_row_i)->Fill(k,idealHits);
				} // Column

				h1[i].GetTH1(ratio)->Divide( h1[i].GetTH1(hits_row), h1[i].GetTH1(hits_row_i) );	
			} //Row
		} // Roc
*/

