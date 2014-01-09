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
#include "TF1.h"
#include "../interface/fitParameter.h"
#include "../interface/Parameters.h"	// Define parameters, input/output files
#include "../interface/index_ROC.h"	// Define parameters 
#include "../interface/TH1Info.h"	// Histogram details are defined here
#include "../interface/TH1InfoClass.h"	 
using namespace std;

const int treeSize = Col_Size/2;

// Change int to string
string int2str(int i){
	string s;
	stringstream ss(s);
	ss << i;
	return ss.str();
}

void saveFitParameter(){
	
	string outputPath = storeRootPath + "/" + "2ColFitParameter" + ".root";
	TFile* output = new TFile(outputPath.c_str(), "RECREATE" ); 
	TTree* tree[ROC_Size][treeSize];
	fitParameter par[ROC_Size][treeSize];
	cout<<"Creating tree..."<<endl;
	for( int i=0; i<ROC_Size; i++){
		output->mkdir(index_ROC[i].c_str());	
		output->cd(index_ROC[i].c_str());
			for( int j=0; j<treeSize; j++){
				string name= "2Col_" + int2str(j*2) + "." + int2str(j*2+1);
				tree[i][j] = new TTree(name.c_str(),"");
				par[i][j].RegisterTree(tree[i][j]);
			}
		output->cd();
	}
	
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
			cout<<"Success register TH1 from "<<index_ROC[index]<<" !"<<endl;	
		} // roc
	
		////= Loop for each hit, Fill Histogram =========================================================================================
		cout<<"Running..."<<endl;	
	
		for( int i=0; i<ROC_Size; i++){
			for( int j=0; j<treeSize; j++){
				int fitMin=0;
				int fitMax=160;	

				string hits_2col   = "Hits_2Col_" + int2str(j*2) + "." + int2str(j*2+1);
				string hits_2col_i = "Hits_2Col_" + int2str(j*2) + "." + int2str(j*2+1) + "_ideal";
				
				h1[i].GetTH1(hits_2col)->Sumw2();
				h1[i].GetTH1(hits_2col_i)->Sumw2();

				TF1* fpol1  = new TF1("fpol1", "pol1", fitMin, fitMax);	

				TH1* hRatio = (TH1*)h1[i].GetTH1(hits_2col)->Clone("clone_record");
				hRatio->Divide(h1[i].GetTH1(hits_2col_i));
				hRatio->Fit("fpol1", "L");
	
				double p0_1 = fpol1->GetParameter(0);
				double p1_1 = fpol1->GetParameter(1);
				double e0_1 = fpol1->GetParError(0);			
				double e1_1 = fpol1->GetParError(1);			
				double endPoint = fitMax*p1_1+p0_1;
				double endPoint_error = sqrt(fitMax*fitMax*e1_1*e1_1+e0_1*e0_1);
				double p0_2 = 1;	
				double p1_2 = (endPoint-p0_2)/(fitMax-fitMin);
				double e0_2 = 0;			
				double e1_2 = sqrt(endPoint_error*endPoint_error+e0_2*e0_2)/(fitMax-fitMin);			
	
				par[i][j].RunNumber = sampleInfo[isample].RunNumber;			
				par[i][j].Flux = sampleInfo[isample].Flux;			
				par[i][j].p0_1 = p0_1;			
				par[i][j].p1_1 = p1_1;			
				par[i][j].e0_1 = e0_1;			
				par[i][j].e1_1 = e1_1;			
				par[i][j].p0_2 = p0_2;			
				par[i][j].p1_2 = p1_2;			
				par[i][j].e0_2 = e0_2;
				par[i][j].e1_2 = e1_2;

				tree[i][j]->Fill();
			}
		} // Roc
	} // sample
	output->Write();
}





