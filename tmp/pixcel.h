//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Dec 12 14:12:59 2013 by ROOT version 5.32/00
// from TTree tree/tree
// found on file: /afs/cern.ch/work/r/rslu/public/FNAL2013_data/tree_34318_.root
//////////////////////////////////////////////////////////

#ifndef pixcel_h
#define pixcel_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class pixcel {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           EventNumber;
   Int_t           TriggerCount;
   Int_t           TriggerPhase;
   Int_t           TriggerPattern;
   Int_t           TimeStamp;
   Int_t           ROCnumber;
   Int_t           col;
   Int_t           row;
   Int_t           raw;
   Int_t           flag;

   // List of branches
   TBranch        *b_EventNumber;   //!
   TBranch        *b_TriggerCount;   //!
   TBranch        *b_TriggerPhase;   //!
   TBranch        *b_TriggerPattern;   //!
   TBranch        *b_TimeStamp;   //!
   TBranch        *b_ROCnumber;   //!
   TBranch        *b_col;   //!
   TBranch        *b_row;   //!
   TBranch        *b_raw;   //!
   TBranch        *b_flag;   //!

   pixcel(TTree *tree=0);
   virtual ~pixcel();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef pixcel_cxx
pixcel::pixcel(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/cern.ch/work/r/rslu/public/FNAL2013_data/tree_34318_.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/afs/cern.ch/work/r/rslu/public/FNAL2013_data/tree_34318_.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

pixcel::~pixcel()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t pixcel::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t pixcel::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void pixcel::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("TriggerCount", &TriggerCount, &b_TriggerCount);
   fChain->SetBranchAddress("TriggerPhase", &TriggerPhase, &b_TriggerPhase);
   fChain->SetBranchAddress("TriggerPattern", &TriggerPattern, &b_TriggerPattern);
   fChain->SetBranchAddress("TimeStamp", &TimeStamp, &b_TimeStamp);
   fChain->SetBranchAddress("ROCnumber", &ROCnumber, &b_ROCnumber);
   fChain->SetBranchAddress("col", &col, &b_col);
   fChain->SetBranchAddress("row", &row, &b_row);
   fChain->SetBranchAddress("raw", &raw, &b_raw);
   fChain->SetBranchAddress("flag", &flag, &b_flag);
   Notify();
}

Bool_t pixcel::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void pixcel::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t pixcel::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef pixcel_cxx
