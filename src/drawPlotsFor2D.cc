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
#include "TText.h"
#include "TFile.h"
#include "../interface/setTDRStyleFor2D.C"
#include "../interface/Parameters.h"	// Define parameters, input/output files
#include "../interface/index_ROC.h"	// Define parameters, input/output files
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


template<typename TH2>
void drawTH2( TCanvas* c2, TH2* h, string title, double xT, double yT, string savePath){
	TText* Title = new TText(xT,yT, title.c_str()); 
	h->SetFillColor(0);
	h->Draw("COLZ");
	Title->Draw("SAME");
	c2->SaveAs(savePath.c_str());
}


void drawPlotsFor2D(){
	
	setTDRStyleFor2D();	
	
	TCanvas* c2 = new TCanvas("c2", "", 960, 700);
	for( int isample=0; isample<Sample_Size; isample++){
		////= Input and prepare the out files ===========================================================================
		string input	= storeRootPath + "/" + sampleName[isample] + ".root";
		TFile* input_f	= new TFile(input.c_str()); 
		cout<<"Success read "<<input<<" !"<<endl;	
	
		////= Create Histogram, create sub-directory and initialize variables ===========================================
		TH2InfoClass<TH2_Type> h2[ROC_Size];

		for( int index=0; index<ROC_Size; index++){ 
			string dirName = index_ROC[index] + "/";
			h2[index].CreateTH2(input_f, dirName);
			h2[index].SetTitles();
			cout<<"Success register TH2 from "<<index_ROC[index]<<" !"<<endl;	
		} // roc
	
		////= Loop for each hit, Fill Histogram =========================================================================================
		cout<<"Running..."<<endl;	
	
		for( int i=0; i<ROC_Size; i++){ 
			for( int th2=0; th2<TH2_Size_; th2++){
				string saveTH2 = storePlotsPath + "/" + sampleName[isample] + index_ROC[i] + "_" + TH2Info[th2].Name + ".png";
				string title = index_ROC[i] + " " + TH2Info[th2].Title;
				h2[i].GetTH2(TH2Info[th2].Name)->UseCurrentStyle();
				drawTH2(c2, h2[i].GetTH2(TH2Info[th2].Name),title, Col_Size/2.8,Row_Size+2, saveTH2);
			}
		} // Roc
	} // sample
}





