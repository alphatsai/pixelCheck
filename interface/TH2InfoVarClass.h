#ifndef TH2INFOVARCLASS_H
#define TH2INFOVARCLASS_H

#include <string>
//#include "TH2Info.h" // Variables accoding from here

class TH2InfoVarClass{
	public:
		string  Name;
		string 	Title;
		string 	xTitle;
		string 	yTitle;
		string 	xUnit;
		string 	yUnit;
                int     xBin;
                int     yBin;
                double  xMin;
                double  yMin;
                double  xMax;
                double  yMax;
};

#endif
