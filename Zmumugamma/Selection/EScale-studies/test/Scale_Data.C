// ROOT headers
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"

// RooFit headers
#include "RooAbsPdf.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooHistPdf.h"
#include "RooMsgService.h"
#include "RooNLLVar.h"
#include "RooPlot.h"
#include "RooRandom.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "RooFFTConvPdf.h"
#include "CMSStyle.C"
//gROOT->Reset();

// RooStats headers
//#include "RooStats/HLFactory.h"

void Scale_Data(){
	CMSstyle();
	using namespace RooFit;

//	TFile* file_Data = new TFile("miniTree_Run2010_ALL_v2.root");
	TFile* file_Data = new TFile("miniTree_FSR_DYToMuMu_v2.root");
	TTree* Tree_Data = (TTree*) file_Data->Get("miniTree");

	RooRealVar Photon_isEB("Photon_isEB", "Photon_isEB", 0, 1);
 
	RooRealVar Mmumu("Mmumu", "Mmumu", 40, 80, "GeV");
	RooRealVar Mmumugamma("Mmumugamma", "Mmumugamma", 60, 120, "GeV");
/*
	RooRealVar Mmumugamma_5x5("Mmumugamma_5x5", "Mmumugamma_5x5", 60, 120, "GeV");
	RooRealVar Mmumugamma_SC("Mmumugamma_SC", "Mmumugamma_SC", 60, 120, "GeV");
	RooRealVar Mmumugamma_SCraw("Mmumugamma_SCraw", "Mmumugamma_SCraw", 60, 120, "GeV");
*/
	RooRealVar mmg_k("mmg_k", "mmg_k", -500, 500, ""); 
	RooRealVar mmg_ik("mmg_ik", "mmg_ik", -500, 500, "");
	RooRealVar mmg_s("mmg_s", "mmg_s", -500, 500, "");
	RooRealVar mmg_logk("mmg_logk", "mmg_logk", -500, 500, ""); 
	RooRealVar mmg_logik("mmg_logik", "mmg_logik", -500, 500, "");
	RooRealVar mmg_logs("mmg_logs", "mmg_logs", -500, 500, "");
/*
	RooRealVar mmg_k_5x5("mmg_k_5x5", "mmg_k_5x5", -500, 500, "");
	RooRealVar mmg_ik_5x5("mmg_ik_5x5", "mmg_ik_5x5", -500, 500, "");
	RooRealVar mmg_s_5x5("mmg_s_5x5", "mmg_s_5x5", -500, 500, "");
	RooRealVar mmg_logk_5x5("mmg_logk_5x5", "mmg_logk_5x5", -500, 500, "");
	RooRealVar mmg_logik_5x5("mmg_logik_5x5", "mmg_logik_5x5", -500, 500, "");
	RooRealVar mmg_logs_5x5("mmg_logs_5x5", "mmg_logs_5x5", -500, 500, "");
	RooRealVar mmg_k_SC("mmg_k_SC", "mmg_k_SC", -500, 500, "");
	RooRealVar mmg_ik_SC("mmg_ik_SC", "mmg_ik_SC", -500, 500, "");
	RooRealVar mmg_s_SC("mmg_s_SC", "mmg_s_SC", -500, 500, "");
	RooRealVar mmg_logk_SC("mmg_logk_SC", "mmg_logk_SC", -500, 500, "");
	RooRealVar mmg_logik_SC("mmg_logik_SC", "mmg_logik_SC", -500, 500, "");
	RooRealVar mmg_logs_SC("mmg_logs_SC", "mmg_logs_SC", -500, 500, "");
	RooRealVar mmg_k_SCraw("mmg_k_SCraw", "mmg_k_SCraw", -500, 500, "");
	RooRealVar mmg_ik_SCraw("mmg_ik_SCraw", "mmg_ik_SCraw", -500, 500, "");
	RooRealVar mmg_s_SCraw("mmg_s_SCraw", "mmg_s_SCraw", -500, 500, "");
	RooRealVar mmg_logk_SCraw("mmg_logk_SCraw", "mmg_logk_SCraw", -500, 500, "");
	RooRealVar mmg_logik_SCraw("mmg_logik_SCraw", "mmg_logik_SCraw", -500, 500, "");
	RooRealVar mmg_logs_SCraw("mmg_logs_SCraw", "mmg_logs_SCraw", -500, 500, "");
*/
	
	RooArgSet *ntplVars = new RooArgSet(Photon_isEB, Mmumu, Mmumugamma, mmg_k, mmg_ik, mmg_s, mmg_logk, mmg_logik, mmg_logs);
//	RooArgSet ntplVars(Mmumu, Mmumugamma, Mmumugamma_5x5, Mmumugamma_SC, Mmumugamma_SCraw, mmg_k, mmg_ik, mmg_s, mmg_logk, mmg_logik, mmg_logs, mmg_k_5x5, mmg_ik_5x5, mmg_s_5x5, mmg_logk_5x5, mmg_logik_5x5, mmg_logs_5x5, mmg_k_SC, mmg_ik_SC, mmg_s_SC, mmg_logk_SC, mmg_logik_SC, mmg_logs_SC, mmg_k_SCraw, mmg_ik_SCraw, mmg_s_SCraw, mmg_logk_SCraw, mmg_logik_SCraw, mmg_logs_SCraw);
	RooDataSet *Data = new RooDataSet("Data", "Data", Tree_Data, *ntplVars);
	RooDataSet *EB_Data = Data->reduce("Photon_isEB == 1");

	// BREIT-WIGNER
	RooRealVar mmg_BW_mean("mmg_BW_mean", "mmg_BW_mean",  91.188, 85.0, 95.0,"GeV/c^{2}");
	RooRealVar mmg_BW_width("mmg_BW_width", "mmg_BW_width", 2.45, 2.0,3.0,"GeV/c^{2}");
	mmg_BW_mean.setConstant();
	mmg_BW_width.setConstant();
	RooBreitWigner mmg_BW("mmg_BW", "mmg_BW", Mmumugamma, mmg_BW_mean, mmg_BW_width);


	// CRYSTALBALL
  RooRealVar mmg_CB_m0("mmg_CB_m0","mmg_CB_m0", 0.0, -10.0, 10.0);  
  RooRealVar mmg_CB_sigma("mmg_CB_sigma","mmg_CB_sigma", 1.45, 1.0, 5.0);
  RooRealVar mmg_CB_alpha("mmg_CB_alpha","mmg_CB_alpha", 0.98, 0.0, 2.0);
  RooRealVar mmg_CB_n("mmg_CB_n","mmg_CB_n", 3.8, 0.5, 10.0);
  RooCBShape mmg_CrystalBall("mmg_CrystalBall","mmg_CrystalBall", Mmumugamma, mmg_CB_m0, mmg_CB_sigma, mmg_CB_alpha, mmg_CB_n);

	// CONVOLUTION
//	RooFFTConvPdf mmg_BWxCB("mmg_BWxCB", "mmg_BWxCB", Mmumugamma, mmg_CrystalBall, mmg_BW);
	RooFFTConvPdf mmg_BWxCB("mmg_BWxCB", "mmg_BWxCB", Mmumugamma, mmg_BW, mmg_CrystalBall);
//	RooNumConvPdf mmg_BWxCB("mmg_BWxCB", "mmg_BWxCB", Mmumugamma, mmg_CrystalBall, mmg_BW);

	mmg_BWxCB.fitTo(*EB_Data);
//	mmg_CrystalBall.fitTo(*EB_Data);
//	mmg_CrystalBall.fitTo(*Data);
//	RooArgSet* mmg_CB_param = mmg_CrystalBall.getVariables();
	RooArgSet* mmg_BWxCB_param = mmg_BWxCB.getVariables();
//	mmg_CB_param->Print("v");
	mmg_BWxCB_param->Print("v");

//	TCanvas* mmg_CB_canvas = new TCanvas("mmg_CB_canvas", "mmg_CB_canvas");
	TCanvas* mmg_BWxCB_canvas = new TCanvas("mmg_BWxCB_canvas", "mmg_BWxCB_canvas");
//	RooPlot* mmg_CB_frame = Mmumugamma.frame(Title("m_{#mu#mu#gamma} fitted with a Crystal Ball"));
	RooPlot* mmg_BWxCB_frame = Mmumugamma.frame(Title("m_{#mu#mu#gamma} fitted with a Crystal Ball convoluted with a Z^{0} Breit-Wigner"));
//	Data->plotOn(mmg_CB_frame);
//	EB_Data->plotOn(mmg_CB_frame, Name("data"));
	EB_Data->plotOn(mmg_BWxCB_frame, Name("data"));
//	mmg_CrystalBall.plotOn(mmg_CB_frame, Name("model"));
	mmg_BWxCB.plotOn(mmg_BWxCB_frame, Name("model"));
//	mmg_CB_frame->Draw();
	mmg_BWxCB_frame->Draw();
//	Double_t mmg_CB_chi2_ndf = mmg_CB_frame->chiSquare("model", "data", 4);
	Double_t mmg_BWxCB_chi2_ndf = mmg_BWxCB_frame->chiSquare("model", "data", 4);
//	cout << "mmg_CB_chi2_ndf= " << mmg_CB_chi2_ndf << endl;
	cout << "mmg_BWxCB_chi2_ndf= " << mmg_BWxCB_chi2_ndf << endl;




return;
}
