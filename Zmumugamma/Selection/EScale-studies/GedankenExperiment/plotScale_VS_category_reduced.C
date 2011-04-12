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
MC_scale->Draw("estimator:category>>h2_scale_temp(23,0,23,500,-5,5)", "estimatorName==0&&(category<5 || category == 10 || category == 11 || category == 12 || category ==15 ||category ==16)");
DATA_scale->Draw("estimator:category>>h2_data_scale_temp(23,0,23,500,-5,5)", "estimatorName==0&&(category<5 || category == 10 || category == 11 || category == 12 || category ==15 ||category ==16)");
MC_scale->Draw("deltaEstimator:category>>h2_scale_error_temp(23,0,23,1000,0,10)", "estimatorName==0&&(category<5 || category == 10 || category == 11 || category == 12 || category ==15 ||category ==16)");
DATA_scale->Draw("deltaEstimator:category>>h2_data_scale_error_temp(23,0,23,1000,0,10)", "estimatorName==0&&(category<5 || category == 10 || category == 11 || category == 12 || category ==15 ||category ==16)");
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

//TCanvas c3;
TProfile* h2_scale_profile = (TProfile*)h2_scale->ProfileX();
TProfile* h2_data_scale_profile = (TProfile*)h2_data_scale->ProfileX();
TProfile* h2_scale_error_profile = (TProfile*)h2_scale_error->ProfileX();
TProfile* h2_data_scale_error_profile = (TProfile*)h2_data_scale_error->ProfileX();
char* label[10];
label[0] = "EB + EE";
label[1] = "EB";
label[2] = "EE";
label[3] = "EB+";
label[4] = "EB-";
//label[5] = "EB ref";
//label[6] = "EB+ ref";
//label[7] = "EB- ref";
//label[8] = "EE+";
//label[9] = "EE-";
label[5] = "EB |#eta| < .5";
label[6] = "EB .5 < |#eta| < 1.";
label[7] = "EB 1. < |#eta| < 1.44";
//label[13] = "EE+ with ES";
//label[14] = "EE- with ES";
label[8] = "EB unconverted (R9)";
label[9] = "EB converted (R9)";
/*
label[17] = "EE unconverted (R9)";
label[18] = "EE converted (R9)";
label[19] = "EB unconverted (ntracks)";
label[20] = "EB converted (ntracks)";
label[21] = "EE unconverted (ntracks)";
label[22] = "EE converted (ntracks)";
*/
h2_scale_profile->GetYaxis()->SetTitle("k");
h2_data_scale_profile->GetYaxis()->SetTitle("k");

Double_t error[11];
for(int i = 0 ;  i < 10 ; i++){
	h2_scale_profile->GetXaxis()->SetBinLabel(i+1, label[i]);
	h2_data_scale_profile->GetXaxis()->SetBinLabel(i+1, label[i]);
//	cout << "h2_scale_error_profile->GetBinContent(i+1)" << h2_scale_error_profile->GetBinContent(i+1) << endl;
////	error[i+1] = h2_scale_error_profile->GetBinContent(i+1);
//	h2_scale_profile->SetBinError(i+1, i+1);
//	h2_scale_profile->SetBinError(i+1, h2_scale_error_profile->GetBinContent(i+1));
}
//h2_scale_profile->SetError(error);
//h2_scale_profile->Draw();

//TCanvas c4;
TH1D *h1_scale = h2_scale_profile->ProjectionX();
TH1D *h1_data_scale = h2_data_scale_profile->ProjectionX();
//h1_scale->SetError(error);
//h1_scale->SetBinsLength(11);
//gPad->Update();

h1_data_scale->SetBinContent(6, h2_data_scale_profile->GetBinContent(11));
h1_data_scale->SetBinContent(7, h2_data_scale_profile->GetBinContent(12));
h1_data_scale->SetBinContent(8, h2_data_scale_profile->GetBinContent(13));
h1_data_scale->SetBinContent(9, h2_data_scale_profile->GetBinContent(16));
h1_data_scale->SetBinContent(10, h2_data_scale_profile->GetBinContent(17));

h1_data_scale->SetBinError(1, h2_data_scale_error_profile->GetBinContent(1));
h1_data_scale->SetBinError(2, h2_data_scale_error_profile->GetBinContent(2));
h1_data_scale->SetBinError(3, h2_data_scale_error_profile->GetBinContent(3));
h1_data_scale->SetBinError(4, h2_data_scale_error_profile->GetBinContent(4));
h1_data_scale->SetBinError(5, h2_data_scale_error_profile->GetBinContent(5));

h1_data_scale->SetBinError(6, h2_data_scale_error_profile->GetBinContent(11));
h1_data_scale->SetBinError(7, h2_data_scale_error_profile->GetBinContent(12));
h1_data_scale->SetBinError(8, h2_data_scale_error_profile->GetBinContent(13));
h1_data_scale->SetBinError(9, h2_data_scale_error_profile->GetBinContent(16));
h1_data_scale->SetBinError(10, h2_data_scale_error_profile->GetBinContent(17));

h1_data_scale->SetBinContent(11, 0);
h1_data_scale->SetBinContent(12, 0);
h1_data_scale->SetBinContent(13, 0);
h1_data_scale->SetBinContent(16, 0);
h1_data_scale->SetBinContent(17, 0);

h1_data_scale->GetXaxis()->SetRange(0,10);
h1_data_scale->Draw("E1");


h1_scale->SetBinContent(6, h2_scale_profile->GetBinContent(11));
h1_scale->SetBinContent(7, h2_scale_profile->GetBinContent(12));
h1_scale->SetBinContent(8, h2_scale_profile->GetBinContent(13));
h1_scale->SetBinContent(9, h2_scale_profile->GetBinContent(16));
h1_scale->SetBinContent(10, h2_scale_profile->GetBinContent(17));

h1_scale->SetBinError(1, h2_scale_error_profile->GetBinContent(1));
h1_scale->SetBinError(2, h2_scale_error_profile->GetBinContent(2));
h1_scale->SetBinError(3, h2_scale_error_profile->GetBinContent(3));
h1_scale->SetBinError(4, h2_scale_error_profile->GetBinContent(4));
h1_scale->SetBinError(5, h2_scale_error_profile->GetBinContent(5));
h1_scale->SetBinError(6, h2_scale_error_profile->GetBinContent(11));
h1_scale->SetBinError(7, h2_scale_error_profile->GetBinContent(12));
h1_scale->SetBinError(8, h2_scale_error_profile->GetBinContent(13));
h1_scale->SetBinError(9, h2_scale_error_profile->GetBinContent(16));
h1_scale->SetBinError(10, h2_scale_error_profile->GetBinContent(17));
h1_scale->SetBinContent(11, 0);
h1_scale->SetBinContent(12, 0);
h1_scale->SetBinContent(13, 0);
h1_scale->SetBinContent(16, 0);
h1_scale->SetBinContent(17, 0);
h1_scale->SetLineColor(kBlue);
h1_scale->SetMarkerColor(kBlue);
h1_scale->GetXaxis()->SetRange(0,10);
h1_scale->Draw("E1same");

TLegend *legend = new TLegend(0.65, 0.80, 0.90, 0.93, "");
legend->SetTextSize(0.050);
legend->SetFillColor(kWhite);
legend->SetLineColor(kWhite);
legend->SetShadowColor(kWhite);
legend->AddEntry(h1_data_scale->GetName(), "Data", "lp");
legend->AddEntry(h1_scale->GetName(), "<MC>_{exp}", "lp");
legend->Draw();

gPad->Update();

c1->Print("k_VS_category.pdf");
c1->Print("k_VS_category.eps");
c1->Print("k_VS_category.gif");
c1->Print("k_VS_category.png");
c1->Print("k_VS_category.C");


/*
//TProfile* h2_scale_profile_temp = new TProfile(h2_scale->ProfileX());
//h2_scale->ProfileX()->Draw();
//h2_scale->ProjectionY()->Draw();
//h2_scale->
*/
}
