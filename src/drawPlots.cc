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

template<typename TH1>
void ratioPlots( TCanvas* c1, TH1* h_r, TH1* h_i, string xTitle, string yTitle, string savePath ){

	TPad *pad1 = new TPad("pad1","pad1",0,0.147,1,1);
	TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.19);

	TLegend* lg= new TLegend(0.72,0.75,0.92,0.90);
        lg->SetBorderSize(0);
        lg->SetFillColor(0);
        lg->SetFillStyle(0);
        lg->SetNColumns(1);
        lg->SetTextSize(0.04);
        lg->SetTextSizePixels(25);
	lg->AddEntry(h_i,"Ideal hits","l");
	lg->AddEntry(h_r,"Record hits","l");
	
	double yMaximum;
	if( h_r->GetMaximum()>h_i->GetMaximum()){
		yMaximum = h_r->GetMaximum();
	}else{
		yMaximum = h_i->GetMaximum();
	}	

	c1->cd();
	pad1->SetBottomMargin(0.05);
	pad1->SetTopMargin(0.06);
	pad1->Draw();
	pad1->cd();
	h_i->SetMaximum(yMaximum+yMaximum/10);
	h_i->SetYTitle(yTitle.c_str());
	h_r->SetYTitle(yTitle.c_str());
	h_i->Draw();
	h_r->Draw("SAME");

	c1->cd();
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.4);
	pad2->SetGrid();
	pad2->Draw();
	pad2->cd();
		
	h_i->Sumw2();
	h_r->Sumw2();
	TH1* hRatio = (TH1*)h_r->Clone("clone_record");
	hRatio->Divide(h_i);
	hRatio->SetXTitle(xTitle.c_str());
	hRatio->SetYTitle("Record/Ideal");
	hRatio->GetXaxis()->SetLabelSize(0.055);
	hRatio->GetYaxis()->SetTitleOffset(0.23);
	hRatio->GetYaxis()->SetTitleSize(0.22);
	hRatio->GetYaxis()->SetRangeUser(0.0,2);
	hRatio->GetXaxis()->SetTitleOffset(0.8);
	hRatio->GetXaxis()->SetTitleSize(0.18);
	hRatio->GetXaxis()->SetLabelSize(0.2);
	hRatio->GetYaxis()->SetLabelSize(0.2);
	hRatio->GetXaxis()->SetNdivisions(510);
	hRatio->GetYaxis()->SetNdivisions(502);
	hRatio->GetYaxis()->SetRangeUser(0,2);
	hRatio->SetLineColor(1); 
	hRatio->SetLineWidth(2); 
	hRatio->SetMarkerStyle(8); 
	hRatio->Draw("ep");
	c1->SaveAs(savePath.c_str());
	c1->cd();
}



void drawPlots(){

	setTDRStyle();

	for( int isample=0; isample<Sample_Size; isample++){
		////= Input and prepare the out files ===========================================================================
		string input	= storeRootPath + "/" + sampleName[isample] + ".root";
		TFile* input_f	= new TFile(input.c_str()); 
		cout<<"Success read "<<input<<" !"<<endl;	
	
		////= Create Histogram, create sub-directory and initialize variables ===========================================
		TH2InfoClass<TH2_Type> h2[ROC_Size];
		TH1InfoClass<TH1_Type> h1[ROC_Size];

		for( int index=0; index<ROC_Size; index++){ 
			string dirName = index_ROC[index] + "/";
			h2[index].CreateTH2(input_f, dirName);
			h1[index].CreateTH1(input_f, dirName);
			h2[index].SetTitles();
			//h1[index].SetTitles();
			cout<<"Success register TH1 and TH2 from "<<index_ROC[index]<<" !"<<endl;	
		} // roc
	
		////= Loop for each hit, Fill Histogram =========================================================================================
		cout<<"Running..."<<endl;	
	
		//TCanvas* c1 = new TCanvas("c1", "", 850, 700);
		for( int i=0; i<ROC_Size; i++){ 
			for( int j=0; j<Row_Size; j++){
				string hits_row   = "Hits_Row_" + int2str(j);
				string hits_row_i = "Hits_Row_" + int2str(j) + "_ideal";
					
				h1[i].GetTH1(hits_row)->UseCurrentStyle();	
				h1[i].GetTH1(hits_row)->SetLineWidth(2);	
				h1[i].GetTH1(hits_row)->SetLineColor(4);
	
				h1[i].GetTH1(hits_row_i)->UseCurrentStyle();	
				h1[i].GetTH1(hits_row_i)->SetLineWidth(2);	
				h1[i].GetTH1(hits_row_i)->SetLineColor(2);	

				//ratioPlots(c1, h1[i].GetTH1(hits_row), h1[i].GetTH1(hits_row_i), "Column" ,)
			} //Row
		} // Roc

		//cout<<"Success write into "<<output<<" !"<<endl<<endl;	
	} // sample
}





