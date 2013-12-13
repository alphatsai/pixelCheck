#ifndef TH2INFOCLASS_H
#define TH2INFOCLASS_H

#include <map>
#include <string>
#include "TFile.h"
#include "TH2Info.h"
using namespace std;

template<typename TH2> 
class TH2InfoClass{
        public:
                //Detail info
                map<string, TH2*> mapTH2;
                string  Name[TH2_Size_];
		string 	Title[TH2_Size_];
		string 	xTitle[TH2_Size_];
		string 	yTitle[TH2_Size_];
		string 	xUnit[TH2_Size_];
		string 	yUnit[TH2_Size_];
                int     xBin[TH2_Size_];
                int     yBin[TH2_Size_];
                double  xMin[TH2_Size_];
                double  yMin[TH2_Size_];
                double  xMax[TH2_Size_];
                double  yMax[TH2_Size_];

                //Fun. of initial TH2
                TH2InfoClass();
		void CreateTH2();
		void CreateTH2( TFile* f, string dirName ); // dirName, ex: "ROC_1/"
                void Sumw2();
                TH2* GetTH2(string Name_);
};

// Define function
template<typename TH2> 
TH2InfoClass<TH2>::TH2InfoClass(){
        for(int i=0; i<TH2_Size_; i++){ //Loop all kind of TH2
                Name[i] = TH2Info[i].Name;
		Title[i] = TH2Info[i].Title;
		xTitle[i] = TH2Info[i].xTitle;
		yTitle[i] = TH2Info[i].yTitle;
		xUnit[i] = TH2Info[i].xUnit;
		yUnit[i] = TH2Info[i].yUnit;
                xBin[i]  = TH2Info[i].xBin;
               	yBin[i]  = TH2Info[i].yBin;
                xMax[i]  = TH2Info[i].xMax;
                yMax[i]  = TH2Info[i].yMax;
                xMin[i]  = TH2Info[i].xMin;
                yMin[i]  = TH2Info[i].yMin;
        }
}
template<typename TH2> 
void TH2InfoClass<TH2>::CreateTH2(){
        for(int i=0; i<TH2_Size_; i++){ 
                mapTH2[Name[i]] = new TH2(Name[i].c_str(),"",xBin[i], xMin[i], xMax[i], yBin[i], yMin[i], yMax[i]);
        }

}
template<typename TH2> 
void TH2InfoClass<TH2>::CreateTH2( TFile* f, string dirName="" ){
        for(int i=0; i<TH2_Size_; i++){ 
                mapTH2[Name[i]] = (TH2*)f->Get( (dirName+Name[i]).c_str());
        }
}
template<typename TH2> 
void TH2InfoClass<TH2>::Sumw2(){
        for(int i=0; i<TH2_Size_; i++){ 
                mapTH2.find(Name[i])->second->Sumw2();
        }
}
template<typename TH2> 
TH2* TH2InfoClass<TH2>::GetTH2(string Name_){
        return mapTH2.find(Name_)->second;
}

#endif
