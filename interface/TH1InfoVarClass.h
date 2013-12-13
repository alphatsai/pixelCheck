#ifndef TH1INFOVARCLASS_H
#define TH1INFOVARCLASS_H

#include <string>
//#include "TH1Info.h" // Variables accoding from here

class TH1InfoVarClass{
	public:
                string  Name;
		string 	Title;
		string 	xTitle;
		string 	yTitle;
		string 	Unit;
                int     Bin;
                double  Min;
                double  Max;
};

#endif
