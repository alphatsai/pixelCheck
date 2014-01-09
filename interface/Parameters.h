#ifndef PARAMETER_H
#define PARAMETER_H

#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"

// Define output Histogram type
typedef TH1D TH1_Type;
typedef TH2D TH2_Type;

// Set input/output files
// 	Expamles:
//		/afs/cern.ch/work/r/rslu/public/FNAL2013_data/tree_34318_.root
//		/afs/cern.ch/work/r/rslu/public/FNAL2013_data/tree_35113_.root
//		~~~~~~~~~~~~~~~~~~~~v~~~~~~~~~~~~~~~~~~~~~~~~ ~~~~v~~~~~~      
//				samplePath	 	      sampleName
//
const string samplePath    = "/afs/cern.ch/work/r/rslu/public/FNAL2013_data"; // All input files should be put int same folder 
const string storeRootPath = "../result/root";
const string storePlotsPath  = "../result/plots";

const int Sample_Size = 8;
const string sampleName[Sample_Size] = {
	"tree_35113_",
	"tree_35194_",
	"tree_35195_",
	"tree_35196_",
	"tree_34307_",
	"tree_34315_",
	"tree_34317_",
	"tree_34318_"
};

struct sampleInfo_{
	int RunNumber;
	double Flux;
};
struct sampleInfo_ sampleInfo[Sample_Size] = { //Accoding ../spillIntensity.txt
	{ 35113, 683200000.0},		//tree_35113_
	{ 35194, 634400000.0},		//tree_35194_
	{ 35195, 976000000.0},		//tree_35195_
	{ 35196, 536800000.0},		//tree_35196_
	{ 34307, 2147200000.0},		//tree_34307_
	{ 34315, 2244800000.0},		//tree_34315_
	{ 34317, 2196000000.0},		//tree_34317_
	{ 34318, 1854400000.0}		//tree_34318_
};


#endif
