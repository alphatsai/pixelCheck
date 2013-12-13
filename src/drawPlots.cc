#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TMath.h"
#include "TFile.h"
#include "../interface/setTDRStyle.C"
#include "../interface/ratioPlots.C"
#include "../interface/Parameters.h"	// Define parameters, input/output files
#include "../interface/index_ROC.h"	// Define parameters, input/output files
#include "../interface/TH1Info.h"	// Histogram details are defined here
#include "../interface/TH1InfoClass.h"	 
using namespace std;

// Change int to string
string int2str(int &i){
	string s;
	stringstream ss(s);
	ss << i;
	return ss.str();
}

void drawPlots(){

	setTDRStyle();

	for( int isample=0; isample<Sample_Size; isample++){
	//for( int isample=0; isample<1; isample++){
		////= Input and prepare the out files ===========================================================================
		string input	= storeRootPath + "/" + sampleName[isample] + ".root";
		TFile* input_f	= new TFile(input.c_str()); 
		cout<<"Success read "<<input<<" !"<<endl;	
	
		////= Create Histogram, create sub-directory and initialize variables ===========================================
		TH1InfoClass<TH1_Type> h1[ROC_Size];

		for( int index=0; index<ROC_Size; index++){ 
			string dirName = index_ROC[index] + "/";
			h1[index].CreateTH1(input_f, dirName);
			//h1[index].SetTitles();
			cout<<"Success register TH1 from "<<index_ROC[index]<<" !"<<endl;	
		} // roc
	
		////= Loop for each hit, Fill Histogram =========================================================================================
		cout<<"Running..."<<endl;	
	
		TCanvas* c1 = new TCanvas("c1", "", 850, 700);
		for( int i=0; i<ROC_Size; i++){ 
			for( int j=0; j<Row_Size; j++){
				string hits_row   = "Hits_Row_" + int2str(j);
				string hits_row_i = "Hits_Row_" + int2str(j) + "_ideal";
				string output;
				if( j==0 ){
					output = storePlotsPath + "/" + sampleName[isample] + index_ROC[i] + "_HitsRatio.pdf(";
				}else if( j==Row_Size-1){
					output = storePlotsPath + "/" + sampleName[isample] + index_ROC[i] + "_HitsRatio.pdf)";
				}else{
					output = storePlotsPath + "/" + sampleName[isample] + index_ROC[i] + "_HitsRatio.pdf";
				}	
				h1[i].GetTH1(hits_row)->UseCurrentStyle();	
				h1[i].GetTH1(hits_row)->SetLineWidth(2);	
				h1[i].GetTH1(hits_row)->SetLineColor(4);
				h1[i].GetTH1(hits_row_i)->UseCurrentStyle();	
				h1[i].GetTH1(hits_row_i)->SetLineWidth(2);	
				h1[i].GetTH1(hits_row_i)->SetLineStyle(7);	
				h1[i].GetTH1(hits_row_i)->SetLineColor(2);	

				ratioPlots( c1, h1[i].GetTH1(hits_row), h1[i].GetTH1(hits_row_i), 
						h1[i].GetVar(hits_row).xTitle, (index_ROC[i]+" "+h1[i].GetVar(hits_row).Title), output);
			} //Row
		} // Roc
	} // sample
}





