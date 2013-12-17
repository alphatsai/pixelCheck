#ifndef RATIOPLOTSALL_C
#define RATIOPLOTSALL_C

#include <string>
#include "TH1F.h"
#include "TH1D.h"
#include "TPad.h"
#include "TLegend.h"
#include "TCanvas.h"

template<typename TH1>
void ratioPlotsAll( TCanvas* c1, TH1* h_r, TH1* h_i, string xTitle, string yTitle, string savePath ){

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
	h_i->Sumw2();
	h_r->Sumw2();
	h_i->SetMaximum(yMaximum+yMaximum/10);
	h_i->SetYTitle(yTitle.c_str());
	h_r->SetYTitle(yTitle.c_str());
	h_r->Draw("HIST");
	h_i->Draw("HIST SAME");
	lg->Draw("SAME");

	c1->cd();
	pad2->SetTopMargin(0);
	pad2->SetBottomMargin(0.4);
	pad2->SetGrid();
	pad2->Draw();
	pad2->cd();
		
	TH1* hRatio = (TH1*)h_r->Clone("clone_record");
	hRatio->Divide(h_i);
	hRatio->SetXTitle(xTitle.c_str());
	hRatio->SetYTitle("Record/Ideal");
	hRatio->GetXaxis()->SetLabelSize(0.055);
	hRatio->GetYaxis()->SetTitleOffset(0.23);
	hRatio->GetYaxis()->SetTitleSize(0.18);
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
	//hRatio->SetMarkerStyle(7); 
	hRatio->Draw("e");
	c1->SaveAs(savePath.c_str());
	c1->cd();
}


#endif
