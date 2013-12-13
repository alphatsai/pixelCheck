#ifndef SETTDRSTYLEFOR2D_H
#define SETTDRSTYLEFOR2D_H


#include "TStyle.h"

void setTDRStyleFor2D() {

  TStyle *tdrStyle2 = new TStyle("tdrStyle2","Style for P-TDR");

// For the canvas:
  tdrStyle2->SetCanvasBorderMode(0);
  tdrStyle2->SetCanvasColor(kWhite);
  tdrStyle2->SetCanvasDefH(600); //Height of canvas
  tdrStyle2->SetCanvasDefW(600); //Width of canvas
  tdrStyle2->SetCanvasDefX(0);   //POsition on screen
  tdrStyle2->SetCanvasDefY(0);

// For the Pad:
  tdrStyle2->SetPadBorderMode(0);
  // tdrStyle2->SetPadBorderSize(Width_t size = 1);
  tdrStyle2->SetPadColor(kWhite);
  tdrStyle2->SetPadGridX(false);
  tdrStyle2->SetPadGridY(false);
  tdrStyle2->SetGridColor(0);
  tdrStyle2->SetGridStyle(3);
  tdrStyle2->SetGridWidth(1);

// For the frame:
  tdrStyle2->SetFrameBorderMode(0);
  tdrStyle2->SetFrameBorderSize(1);
  tdrStyle2->SetFrameFillColor(0);
  tdrStyle2->SetFrameFillStyle(0);
  tdrStyle2->SetFrameLineColor(1);
  tdrStyle2->SetFrameLineStyle(1);
  tdrStyle2->SetFrameLineWidth(1);

// For the histo:
  // tdrStyle2->SetHistFillColor(1);
  // tdrStyle2->SetHistFillStyle(0);
  tdrStyle2->SetHistLineColor(1);
  tdrStyle2->SetHistLineStyle(0);
  tdrStyle2->SetHistLineWidth(1);
  // tdrStyle2->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle2->SetNumberContours(Int_t number = 20);

  tdrStyle2->SetEndErrorSize(2);
  // tdrStyle2->SetErrorMarker(20);
  //tdrStyle2->SetMarkerStyle(20);
  tdrStyle2->SetErrorX(0.);

// For the fit/function:
  tdrStyle2->SetOptFit(1);
  tdrStyle2->SetFitFormat("5.4g");
  tdrStyle2->SetFuncColor(2);
  tdrStyle2->SetFuncStyle(1);
  tdrStyle2->SetFuncWidth(1);


//For the date:
  tdrStyle2->SetOptDate(0);
  // tdrStyle2->SetDateX(Float_t x = 0.01);
  // tdrStyle2->SetDateY(Float_t y = 0.01);


// For the statistics box:
  tdrStyle2->SetOptFile(0);
  tdrStyle2->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle2->SetStatColor(kWhite);
  tdrStyle2->SetStatFont(42);
  tdrStyle2->SetStatFontSize(0.025);
  tdrStyle2->SetStatTextColor(1);
  tdrStyle2->SetStatFormat("6.4g");
  tdrStyle2->SetStatBorderSize(1);
  tdrStyle2->SetStatH(0.1);
  tdrStyle2->SetStatW(0.15);
  // tdrStyle2->SetStatStyle(Style_t style = 1212);
  // tdrStyle2->SetStatX(Float_t x = 0);
  // tdrStyle2->SetStatY(Float_t y = 0);

// Margins:
  tdrStyle2->SetPadTopMargin(0.05);
  tdrStyle2->SetPadBottomMargin(0.13);
  tdrStyle2->SetPadLeftMargin(0.14);
  tdrStyle2->SetPadRightMargin(0.14);

// For the Global title:
  // tdrStyle2->SetOptTitle(0);
  tdrStyle2->SetTitleFont(42);
  tdrStyle2->SetTitleColor(1);
  tdrStyle2->SetTitleTextColor(1);
  tdrStyle2->SetTitleFillColor(10);
  tdrStyle2->SetTitleFontSize(0.05);
  // tdrStyle2->SetTitleH(0); // Set the height of the title box
  // tdrStyle2->SetTitleW(0); // Set the width of the title box
  // tdrStyle2->SetTitleX(0); // Set the position of the title box
  // tdrStyle2->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle2->SetTitleStyle(Style_t style = 1212);
  // tdrStyle2->SetTitleBorderSize(2);

// For the axis titles:
  tdrStyle2->SetTitleColor(1, "XYZ");
  tdrStyle2->SetTitleFont(42, "XYZ");
  tdrStyle2->SetTitleSize(0.06, "XYZ");
  // tdrStyle2->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle2->SetTitleYSize(Float_t size = 0.02);
  tdrStyle2->SetTitleXOffset(0.9);
  tdrStyle2->SetTitleYOffset(1.05);
  //tdrStyle2->SetTitleYOffset(0.05);
  // tdrStyle2->SetTitleOffset(1.1, "Y"); // Another way to set the Offset


// For the axis labels:
  tdrStyle2->SetLabelColor(1, "XYZ");
  tdrStyle2->SetLabelFont(42, "XYZ");
  tdrStyle2->SetLabelOffset(0.007, "XYZ");
  tdrStyle2->SetLabelSize(0.05, "XYZ");

// For the axis:
  tdrStyle2->SetAxisColor(1, "XYZ");
  tdrStyle2->SetStripDecimals(kTRUE);
  tdrStyle2->SetTickLength(0.03, "XYZ");
  tdrStyle2->SetNdivisions(510, "XYZ");
  tdrStyle2->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle2->SetPadTickY(1);

// Change for log plots:
  tdrStyle2->SetOptLogx(0);
  tdrStyle2->SetOptLogy(0);
  tdrStyle2->SetOptLogz(0);

// Postscript options:
  // tdrStyle2->SetPaperSize(15.,15.);
  // tdrStyle2->SetLineScalePS(Float_t scale = 3);
  // tdrStyle2->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle2->SetHeaderPS(const char* header);
  // tdrStyle2->SetTitlePS(const char* pstitle);

  // tdrStyle2->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle2->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle2->SetPaintTextFormat(const char* format = "g");
  // tdrStyle2->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle2->SetTimeOffset(Double_t toffset);
  // tdrStyle2->SetHistMinimumZero(kTRUE);

  tdrStyle2->SetPalette(1);


  tdrStyle2->cd();

}
#endif
