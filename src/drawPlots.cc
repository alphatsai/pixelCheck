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
#include "../interface/ratioPlotsAll.C"
#include "../interface/ratioPlots.C"
#include "../interface/Parameters.h"	// Define parameters, input/output files
#include "../interface/index_ROC.h"	// Define parameters, input/output files
#include "../interface/TH1Info.h"	// Histogram details are defined here
#include "../interface/TH1InfoClass.h"	 
using namespace std;

// Change int to string
string int2str(int i){
	string s;
	stringstream ss(s);
	ss << i;
	return ss.str();
}

template<typename TH1>
void setXLableFor2Col( TH1* h, int index ){
	for( int i=1; i<=Row_Size; i++){
		string lable1= "(" + int2str(index*2) + "," + int2str(i) + ")";
		string lable2= "(" + int2str(index*2+1) + "," + int2str(i) + ")";
		h->GetXaxis()->SetBinLabel(i,lable1.c_str());
		h->GetXaxis()->SetBinLabel((161-i),lable2.c_str());
	}
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
			for( int j=0; j<Col_Size/2; j++){
				string hits_2col   = "Hits_2Col_" + int2str(j*2) + "." + int2str(j*2+1);
				string hits_2col_i = "Hits_2Col_" + int2str(j*2) + "." + int2str(j*2+1) + "_ideal";
				string ratio_2col = "Ratio_2Col_" + int2str(j*2) + "." + int2str(j*2+1) ;
				string output, output_r;
				output   = storePlotsPath + "/" + sampleName[isample] + index_ROC[i] + "_HitsRatio2Col_" + int2str(j*2) + "." + int2str(j*2+1) + ".png";
				output_r = storePlotsPath + "/" + sampleName[isample] + index_ROC[i] + "_OnlyRatio2Col_" + int2str(j*2) + "." + int2str(j*2+1) + ".png";

				h1[i].GetTH1(hits_2col)->UseCurrentStyle();	
				h1[i].GetTH1(hits_2col)->SetLineWidth(2);	
				h1[i].GetTH1(hits_2col)->SetLineColor(4);
				h1[i].GetTH1(hits_2col_i)->UseCurrentStyle();	
				h1[i].GetTH1(hits_2col_i)->SetLineWidth(2);	
				h1[i].GetTH1(hits_2col_i)->SetLineStyle(7);	
				h1[i].GetTH1(hits_2col_i)->SetLineColor(2);
	
				//setXLableFor2Col(h1[i].GetTH1(hits_2col), j);
				//setXLableFor2Col(h1[i].GetTH1(hits_2col_i), j);

				ratioPlotsAll( c1, h1[i].GetTH1(hits_2col), h1[i].GetTH1(hits_2col_i), 
						h1[i].GetVar(hits_2col).xTitle, (index_ROC[i]+" "+h1[i].GetVar(hits_2col).Title), output);
				ratioPlots( c1, h1[i].GetTH1(hits_2col), h1[i].GetTH1(hits_2col_i), 
						h1[i].GetVar(hits_2col).xTitle, (index_ROC[i]+" "+h1[i].GetVar(ratio_2col).Title), output_r, 0, 160, true);
			}
			for( int j=0; j<Row_Size; j++){
				string hits_row   = "Hits_Row_" + int2str(j);
				string hits_row_i = "Hits_Row_" + int2str(j) + "_ideal";
				string ratio_row = "Ratio_Row_" + int2str(j) ;
				string output, output_r;
				output   = storePlotsPath + "/" + sampleName[isample] + index_ROC[i] + "_HitsRatio_" + int2str(j) + ".png";
				output_r = storePlotsPath + "/" + sampleName[isample] + index_ROC[i] + "_OnlyRatio_" + int2str(j) + ".png";

				h1[i].GetTH1(hits_row)->UseCurrentStyle();	
				h1[i].GetTH1(hits_row)->SetLineWidth(2);	
				h1[i].GetTH1(hits_row)->SetLineColor(4);
				h1[i].GetTH1(hits_row_i)->UseCurrentStyle();	
				h1[i].GetTH1(hits_row_i)->SetLineWidth(2);	
				h1[i].GetTH1(hits_row_i)->SetLineStyle(7);	
				h1[i].GetTH1(hits_row_i)->SetLineColor(2);	

				ratioPlotsAll( c1, h1[i].GetTH1(hits_row), h1[i].GetTH1(hits_row_i), 
						h1[i].GetVar(hits_row).xTitle, (index_ROC[i]+" "+h1[i].GetVar(hits_row).Title), output);
				ratioPlots( c1, h1[i].GetTH1(hits_row), h1[i].GetTH1(hits_row_i), 
						h1[i].GetVar(hits_row).xTitle, (index_ROC[i]+" "+h1[i].GetVar(ratio_row).Title), output_r);
			} //Row
		} // Roc
	} // sample
}





