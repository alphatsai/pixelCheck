#ifndef TH1INFO_H
#define TH1INFO_H

#include <string>
enum TH1List_{
	ROCnumber_,
	TH1_Size_,
};

struct TH1Info_{
	string 	Name;
	string 	Title;
	string 	xTitle;
	string 	yTitle;
	string 	Unit;
	int 	Bin;
	double 	Min;
	double 	Max;
};

struct TH1Info_ TH1Info[TH1_Size_] = {
	{ "ROCnumber", 	"ROC Number", 	"Number", 	"Hits", 	"", 	8, 0, 8},
};




#endif  
