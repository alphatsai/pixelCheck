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

const int Sample_Size = 2;
const string sampleName[Sample_Size] = {
	"tree_34318_", 
	"tree_35113_",
};



#endif
