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
#include "TGraph.h"
#include "../interface/setTDRStyle.C"
#include "../interface/fitParameter.h"
#include "../interface/Parameters.h"	// Define parameters, input/input files
#include "../interface/index_ROC.h"	// Define parameters 
#include "../interface/TH1Info.h"	// Histogram details are defined here
#include "../interface/TH1InfoClass.h"	 
using namespace std;

const int treeSize = Col_Size/2;
const int run34 = 4;
const int run35 = 4;

// Change int to string
string int2str(int i){
	string s;
	stringstream ss(s);
	ss << i;
	return ss.str();
}

void outputTGraph( TCanvas* c1, int num, double* x, double* y, 
		   string xTitle, string yTitle, string output ){
	
	TGraph* g = new TGraph(num, x, y);
	g->SetTitle("");
	g->UseCurrentStyle();
	g->GetXaxis()->SetTitle(xTitle.c_str());
	g->GetYaxis()->SetTitle(yTitle.c_str());
	g->SetLineColor(3);
	g->SetLineWidth(3);
	g->SetMarkerColor(2);
	g->SetMarkerSize(2.5);
	g->SetMarkerStyle(22);
	g->Draw("A");
	//c1->SaveAs(output.c_str());
}

void drawIneffFlux(){
	
	string inputPath = storeRootPath + "/" + "2ColFitParameter" + ".root";
	TFile* input = new TFile(inputPath.c_str()); 
	TTree* tree[ROC_Size][treeSize];
	fitParameter par[ROC_Size][treeSize];

	setTDRStyle();
	TCanvas* c1 = new TCanvas("c1", "", 850, 700);

	//for( int i=0; i<ROC_Size; i++){
	for( int i=4; i<5; i++){
		//for( int j=0; j<treeSize; j++){
		for( int j=8; j<9; j++){
			cout<<"Creating tree..."<<endl;
			string name= index_ROC[i] + "/2Col_" + int2str(j*2) + "." + int2str(j*2+1);
			tree[i][j] = (TTree*)input->Get(name.c_str());
			par[i][j].Register(tree[i][j]);

			double flux34[run34];
			double flux35[run35];
			double ineff34[run34];
			double ineff35[run35];
			int i34=0;			
			int i35=0;			
			
			for( int k=0; k<Sample_Size; k++){
				tree[i][j]->GetEntry(k);
				if( par[i][j].RunNumber >= 35000 ){
					flux35[i35]  = par[i][j].Flux/1000000;
					ineff35[i35] = par[i][j].p1_2*100*100;
					i35++;
				}else if( par[i][j].RunNumber >= 34000 ){
					flux34[i34]  = par[i][j].Flux/1000000;
					ineff34[i34] = par[i][j].p1_2*100*100;
					i34++;
				}		
			}
	
			string xTitle = "Intensity/10^{6}";
			string yTitle = "2Col[" + int2str(j*2) + "." + int2str(j*2+1) + "]  Ineff-Rate[%]_{x100}";
			string output34png = storePlotsPath + "/" + "IneffFlux_Run34_" + index_ROC[i] + "_2Col_" + int2str(j*2) + "." + int2str(j*2+1) + ".png";
			string output35png = storePlotsPath + "/" + "IneffFlux_Run35_" + index_ROC[i] + "_2Col_" + int2str(j*2) + "." + int2str(j*2+1) + ".png";
			string output34pdf, output35pdf;
			if( j==0 ){
				output34pdf = storePlotsPath + "/" + "IneffFlux_Run34_" + index_ROC[i] + ".pdf(";
				output35pdf = storePlotsPath + "/" + "IneffFlux_Run35_" + index_ROC[i] + ".pdf(";
			}else if( j==treeSize-1){
				output34pdf = storePlotsPath + "/" + "IneffFlux_Run34_" + index_ROC[i] + ".pdf)";
				output35pdf = storePlotsPath + "/" + "IneffFlux_Run35_" + index_ROC[i] + ".pdf)";
				cout<<"Here"<<endl;
			}else{
				output34pdf = storePlotsPath + "/" + "IneffFlux_Run34_" + index_ROC[i] + ".pdf";
				output35pdf = storePlotsPath + "/" + "IneffFlux_Run35_" + index_ROC[i] + ".pdf";
			}
			
			outputTGraph(c1, run34, flux34, ineff34, xTitle, yTitle, output34png);
			//outputTGraph(c1, run34, flux34, ineff34, xTitle, yTitle, output34pdf);
			//outputTGraph(c1, run35, flux35, ineff35, xTitle, yTitle, output35png);
			//outputTGraph(c1, run35, flux35, ineff35, xTitle, yTitle, output35pdf);
			
		} //DOUBLE COL
	} //ROC
}





