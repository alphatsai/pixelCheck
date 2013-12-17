#ifndef RATIOPLOTS_C
#define RATIOPLOTS_C

#include <string>
#include "TH1F.h"
#include "TH1D.h"
#include "TPad.h"
#include "TLegend.h"
#include "TCanvas.h"

template<typename TH1>
void ratioPlots( TCanvas* c1, TH1* h_r, TH1* h_i, string xTitle, string yTitle, string savePath ){

	double yMaximum;
	if( h_r->GetMaximum()>h_i->GetMaximum()){
		yMaximum = h_r->GetMaximum();
	}else{
		yMaximum = h_i->GetMaximum();
	}	

	h_i->Sumw2();
	h_r->Sumw2();
	h_i->SetMaximum(yMaximum+yMaximum/10);
		
	TH1* hRatio = (TH1*)h_r->Clone("clone_record");
	hRatio->Divide(h_i);
	hRatio->SetXTitle(xTitle.c_str());
	//hRatio->SetYTitle("Record/Ideal");
	hRatio->SetYTitle(yTitle.c_str());
	hRatio->SetLineColor(9); 
	hRatio->SetLineWidth(2); 
	hRatio->SetMarkerStyle(8); 
	hRatio->Draw("e");
	c1->SaveAs(savePath.c_str());
	c1->cd();
}


#endif
