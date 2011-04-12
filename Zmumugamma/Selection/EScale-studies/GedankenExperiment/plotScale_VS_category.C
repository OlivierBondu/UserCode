{
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
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
#include <iomanip>
#include <sstream>
#include <TLatex.h>

gROOT->Reset();

#include "CMSStyle.C"

#pragma optimize 0
using namespace std;

gROOT->ProcessLine(".x setTDRStyle.C");
CMSstyle();
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);

TTree *MC_scale = new TTree ("scale", "Information for each Gedanken experiment with various estimators");
TTree *DATA_scale = new TTree ("scale", "Information for data with various estimators");

//MC_scale->ReadFile("mc.raw", "Gnumber/I:estimatorName/C:category/C:Nevents/I:chi2/F:constant/F:deltaConstant/F:estimator/F:deltaEstimator/F:deltaEstimator_estimator/F:sigma/F:deltaSigma/F:deltaSigma_sigma/F");
//MC_scale->ReadFile("mc.raw2", "Gnumber/I:estimatorName/I:category/C:Nevents/I:chi2/F:constant/F:deltaConstant/F:estimator/F:deltaEstimator/F:deltaEstimator_estimator/F:sigma/F:deltaSigma/F:deltaSigma_sigma/F");
//MC_scale->ReadFile("mc.raw3", "Gnumber/I:estimatorName/I:category/I:Nevents/I:chi2/F:constant/F:deltaConstant/F:estimator/F:deltaEstimator/F:deltaEstimator_estimator/F:sigma/F:deltaSigma/F:deltaSigma_sigma/F");
MC_scale->ReadFile("MC.RAW", "Gnumber/I:estimatorName/I:category/I:Nevents/I:chi2/F:constant/F:deltaConstant/F:estimator/F:deltaEstimator/F:deltaEstimator_estimator/F:sigma/F:deltaSigma/F:deltaSigma_sigma/F");
DATA_scale->ReadFile("data.RAW", "Gnumber/I:estimatorName/I:category/I:Nevents/I:chi2/F:constant/F:deltaConstant/F:estimator/F:deltaEstimator/F:deltaEstimator_estimator/F:sigma/F:deltaSigma/F:deltaSigma_sigma/F");

TCanvas c1;
TH2F *h2_scale_temp = new TH2F();
TH2F *h2_data_scale_temp = new TH2F();
TH2F *h2_scale_error_temp = new TH2F();
TH2F *h2_data_scale_error_temp = new TH2F();
//MC_scale->Draw("estimator:category>>h2_scale_temp", "estimatorName==0");
//MC_scale->Draw("estimator:category>>h2_scale_temp(500,0,2,22,0,22)", "estimatorName==0");
//MC_scale->Draw("estimator:category>>h2_scale_temp(5000,0,2,2,0,2)", "estimatorName==0 && estimator<2 && estimator > 0");
//MC_scale->Draw("estimator:category>>h2_scale_temp", "estimatorName==0 && estimator<2 && estimator > 0");
MC_scale->Draw("estimator:category>>h2_scale_temp(23,0,23,500,-5,5)", "estimatorName==0");
DATA_scale->Draw("estimator:category>>h2_data_scale_temp(23,0,23,500,-5,5)", "estimatorName==0");
MC_scale->Draw("deltaEstimator:category>>h2_scale_error_temp(23,0,23,1000,0,10)", "estimatorName==0");
DATA_scale->Draw("deltaEstimator:category>>h2_data_scale_error_temp(23,0,23,1000,0,10)", "estimatorName==0");
TH2F *h2_scale = (TH2F*)gDirectory->Get("h2_scale_temp");
TH2F *h2_data_scale = (TH2F*)gDirectory->Get("h2_data_scale_temp");
TH2F *h2_scale_error = (TH2F*)gDirectory->Get("h2_scale_error_temp");
TH2F *h2_data_scale_error = (TH2F*)gDirectory->Get("h2_data_scale_error_temp");
h2_scale->Sumw2();
h2_data_scale->Sumw2();
h2_scale_error->Sumw2();
h2_data_scale_error->Sumw2();

//TCanvas c2;
//h2_scale_error->Draw();

TCanvas c3;
TProfile* h2_scale_profile = (TProfile*)h2_scale->ProfileX();
TProfile* h2_scale_error_profile = (TProfile*)h2_scale_error->ProfileX();
char* label[23];
label[0] = "EB + EE";
label[1] = "EB";
label[2] = "EE";
label[3] = "EB+";
label[4] = "EB-";
label[5] = "EB ref";
label[6] = "EB+ ref";
label[7] = "EB- ref";
label[8] = "EE+";
label[9] = "EE-";
label[10] = "EB |#eta| < .5";
label[11] = "EB .5 < |#eta| < 1.";
label[12] = "EB 1. < |#eta| < 1.44";
label[13] = "EE+ with ES";
label[14] = "EE- with ES";
label[15] = "EB unconverted (R9)";
label[16] = "EB converted (R9)";
label[17] = "EE unconverted (R9)";
label[18] = "EE converted (R9)";
label[19] = "EB unconverted (ntracks)";
label[20] = "EB converted (ntracks)";
label[21] = "EE unconverted (ntracks)";
label[22] = "EE converted (ntracks)";

h2_scale_profile->GetYaxis()->SetTitle("k");

Double_t error[24];
for(int i = 0 ;  i < 23 ; i++){
	h2_scale_profile->GetXaxis()->SetBinLabel(i+1, label[i]);
//	cout << "h2_scale_error_profile->GetBinContent(i+1)" << h2_scale_error_profile->GetBinContent(i+1) << endl;
	error[i+1] = h2_scale_error_profile->GetBinContent(i+1);
//	h2_scale_profile->SetBinError(i+1, i+1);
//	h2_scale_profile->SetBinError(i+1, h2_scale_error_profile->GetBinContent(i+1));
}
//h2_scale_profile->SetError(error);
//h2_scale_profile->Draw();

TCanvas c4;
TH1D *h1_scale = h2_scale_profile->ProjectionX();
h1_scale->SetError(error);
h1_scale->Draw();

//TProfile* h2_scale_profile_temp = new TProfile(h2_scale->ProfileX());
//h2_scale->ProfileX()->Draw();
//h2_scale->ProjectionY()->Draw();
//h2_scale->

}
