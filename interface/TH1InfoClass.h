#ifndef TH1INFOCLASS_H
#define TH1INFOCLASS_H

#include <map>
#include <string>
#include "TFile.h"
#include "TH1Info.h"

using namespace std;

template<typename TH1> 
class TH1InfoClass{
        public:
                //Detail info
                map<string, TH1*> mapTH1;
                map<string, int> indexTH1;
                string  Name[TH1_Size_];
		string 	Title[TH1_Size_];
		string 	xTitle[TH1_Size_];
		string 	yTitle[TH1_Size_];
		string 	Unit[TH1_Size_];
                int     Bin[TH1_Size_];
                double  Min[TH1_Size_];
                double  Max[TH1_Size_];

                //Fun. of initial TH1
                TH1InfoClass();
		void CreateTH1();
		void CreateTH1(TFile* f, string dirName ); // dirName, ex: "ROC_1/"
		void SetTitles(); 
                void Sumw2();
                TH1* GetTH1(string Name_);
};

/////// Define function ==============================================
// Constructor
template<typename TH1> 
TH1InfoClass<TH1>::TH1InfoClass(){
        for(int i=0; i<TH1_Size_; i++){ //Loop all kind of TH1
                Name[i] = TH1Info[i].Name;
		Title[i] = TH1Info[i].Title;
		xTitle[i] = TH1Info[i].xTitle;
		yTitle[i] = TH1Info[i].yTitle;
		Unit[i] = TH1Info[i].Unit;
                Bin[i]  = TH1Info[i].Bin;
                Max[i]  = TH1Info[i].Max;
                Min[i]  = TH1Info[i].Min;
		indexTH1[Name[i]]=i;
        }

}

// Create Histogram
template<typename TH1> 
void TH1InfoClass<TH1>::CreateTH1(){
        for(int i=0; i<TH1_Size_; i++){
                mapTH1[Name[i]] = new TH1(Name[i].c_str(),"",Bin[i], Min[i], Max[i]);
        }

}

template<typename TH1> 
void TH1InfoClass<TH1>::CreateTH1( TFile* f, string dirName="" ){
        for(int i=0; i<TH1_Size_; i++){ 
                mapTH1[Name[i]] =(TH1*)f->Get( (dirName+Name[i]).c_str() );
        }

}

// Set some option for Histogram
template<typename TH1> 
void TH1InfoClass<TH1>::SetTitles(){
        for(int i=0; i<TH1_Size_; i++){ 
                //mapTH1[Name[i]]->SetTile(Title[i].c_str());
                mapTH1[Name[i]]->SetXTitle( (xTitle[i]+" ["+Unit[i]+"]").c_str());
                mapTH1[Name[i]]->SetYTitle( yTitle[i].c_str() );
        }
}
 
template<typename TH1> 
void TH1InfoClass<TH1>::Sumw2(){
        for(int i=0; i<TH1_Size_; i++){ 
                mapTH1.find(Name[i])->second->Sumw2();
        }
}

// Get Histogram
template<typename TH1> 
TH1* TH1InfoClass<TH1>::GetTH1(string Name_){
        return mapTH1.find(Name_)->second;
}

#endif
