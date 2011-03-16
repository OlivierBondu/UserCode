#include <TLegend.h>
#include <TStyle.h>
#include <TFormula.h>
#include <TF1.h>
#include <TSystem.h>
#include <TClonesArray.h>
#include <TLeaf.h>
#include <TChain.h>
#include <TObject.h>
#include <string.h>
#include <algorithm>
#include <TBranch.h>
#include <TString.h>
#include <TBits.h>
#include <TMath.h>
#include "TROOT.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <TLatex.h>

#pragma optimize 0

using namespace std;

void DrawMCplot(TTree *FSR_DYToMuMu_powheg_miniTree, string var, string pic, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1, bool doFit = false);



