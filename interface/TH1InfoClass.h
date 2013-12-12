#ifndef TH1INFOCLASS_H
#define TH1INFOCLASS_H

#include <map>
#include "TH1Info.h"
using namespace std;

//template<typename TH1> 
class TH1InfoClass{
        public:
                //Detail info
                map<string, TH1D*> mapTH1;
                string  Name[TH1_Size_];
		string 	Title[TH1_Size_];
		string 	xTitle[TH1_Size_];
		string 	yTitle[TH1_Size_];
		string 	Unit[TH1_Size_];
                int     Bin[TH1_Size_];
                double  Min[TH1_Size_];
                double  Max[TH1_Size_];

                //Fun. of initial TH1
                //TH1InfoClass();
		void Initialize();
                void Sumw2();
                TH1D* GetTH1(string Name_);
};

// Define function
//TH1InfoClass::TH1InfoClass(){
void TH1InfoClass::Initialize(){
        for(int i=0; i<TH1_Size_; i++){ //Loop all kind of TH1
                Name[i] = TH1Info[i].Name;
		Title[i] = TH1Info[i].Title;
		xTitle[i] = TH1Info[i].xTitle;
		yTitle[i] = TH1Info[i].yTitle;
		Unit[i] = TH1Info[i].Unit;
                Bin[i]  = TH1Info[i].Bin;
                Max[i]  = TH1Info[i].Max;
                Min[i]  = TH1Info[i].Min;
                mapTH1[Name[i]] = new TH1D(Name[i].c_str(),"",Bin[i], Min[i], Max[i]);
        }

}
void TH1InfoClass::Sumw2(){
        for(int i=0; i<TH1_Size_; i++){ //Loop all kind of TH1
                mapTH1.find(Name[i])->second->Sumw2();
        }
}
TH1D* TH1InfoClass::GetTH1(string Name_){
        return mapTH1.find(Name_)->second;
}

#endif
