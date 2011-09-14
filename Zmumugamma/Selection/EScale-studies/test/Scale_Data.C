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
#include <iostream>
#include <iomanip>
#include <sstream>
#include <TLatex.h>
#include "TProof.h"

//gROOT->Reset();

/*
double weight_DYToMuMu(int nGenVertices)
{
	double weight[51] = {
0, 0.192859, 0.37571, 0.98006, 1.47381, 2.13772, 1.97435, 1.75482, 1.61272, 1.30487, 0.858989, 0.593953, 0.406, 0.271559, 0.200834, 0.123192, 0.101752, 0.0724765, 0.0505275, 0.0609286, 0.0265446, 0.0178984, 0.0603881, 0, 0.00990419, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
	return weight[nGenVertices];
}
*/

void Scale_Data(){
//	gStyle->SetOptTitle(0);
	gROOT->ProcessLine(".x setTDRStyle.C");
	CMSstyle();
	using namespace RooFit;

//	TProof * p = TProof::Open("ccaplmaster.in2p3.fr");

//	TFile* file_Data = new TFile("../../miniTree_v11_Run2011A_July6_ALL.root");
//	TFile* file_Data = new TFile("../../miniTree_v12_Run2011A-ZMu-05Jul2011ReReco-ECAL-v1.root");
//	TFile* file_Data = new TFile("../../miniTree_v13_Run2011A-ZMu-05Jul2011ReReco-ECAL-v1.root");
//	TFile* file_Data = new TFile("../../miniTree_v13_Run2011A-May10ReReco_PromptReco-v4_July6.root");
//	TFile* file_Data = new TFile("../../miniTree_v13_Run2011A-May10ReReco_PromptReco-v4_June17.root");
	TFile* file_Data = new TFile("../../miniTree_v16_DATA_875pb-1.root");
//	TFile* file_MC = new TFile("../../miniTree_v11_DYToMuMu_M-20_TuneZ2_7TeV-pythia6_v3.root");
//	TFile* file_MC = new TFile("../../miniTree_v12_DYToMuMu_M-20_TuneZ2_7TeV-pythia6_v3.root");
//	TFile* file_MC = new TFile("../../miniTree_v12_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_v2.root");
//	TFile* file_MC = new TFile("../../miniTree_v13_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_v2.root");
	TFile* file_MC = new TFile("../../miniTree_v16_DYToMuMu.root");
	TTree* Tree_Data = (TTree*) file_Data->Get("miniTree");
	TTree* Tree_MC = (TTree*) file_MC->Get("miniTree");

	RooRealVar Photon_isEB("Photon_isEB", "Photon_isEB", 0, 1);
	RooRealVar Photon_isEE("Photon_isEE", "Photon_isEE", 0, 1);
 
	RooRealVar Mmumu("Mmumu", "Mmumu", 40, 80, "GeV");
	RooRealVar Mmumugamma("Mmumugamma", "m_{#mu#mu#gamma}", 60, 120, "GeV");

	RooRealVar mmg_k("mmg_k", "k", 0.0, 2.0, ""); 
	RooRealVar mmg_ik("mmg_ik", "mmg_ik", -500, 500, "");
	RooRealVar mmg_s("mmg_s", "s = E_{reco} / E_{kin.} - 1", -1.0, 1.0, "");
//	RooRealVar mmg_s("mmg_s", "s = E_{reco} / E_{kin.} - 1", -0.5, 0.5, "");
	RooRealVar mmg_logk("mmg_logk", "mmg_logk", -500, 500, ""); 
	RooRealVar mmg_logik("mmg_logik", "mmg_logik", -500, 500, "");
	RooRealVar mmg_logs("mmg_logs", "mmg_logs", -500, 500, "");
	RooRealVar Photon_r9("Photon_r9", "Photon_r9", -2.0, 2.0);
	RooRealVar isVeryLooseMMG("isVeryLooseMMG", "isVeryLooseMMG", -2.0, 2.0);
	RooRealVar isLooseMMG("isLooseMMG", "isLooseMMG", -2.0, 2.0);
	RooRealVar isTightMMG("isTightMMG", "isTightMMG", -2.0, 2.0);
	RooRealVar isAfterFSRCut1("isAfterFSRCut1", "isAfterFSRCut1", -2.0, 2.0);
	RooRealVar isAfterFSRCut2("isAfterFSRCut2", "isAfterFSRCut2", -2.0, 2.0);
	RooRealVar isAfterFSRCut3("isAfterFSRCut3", "isAfterFSRCut3", -2.0, 2.0);
	RooRealVar isAfterFSRCut4("isAfterFSRCut4", "isAfterFSRCut4", -2.0, 2.0);
	RooRealVar isMultipleCandidate("isMultipleCandidate", "isMultipleCandidate", -2.0, 2.0);
	RooRealVar nGenVerticess("nGenVertices", "nGenVertices", -0.5, 50.5);
  RooRealVar weight_pileUp("weight_pileUp", "weight_pileUp", 0.0, 10000000);
  RooRealVar weight_Xsection("weight_Xsection", "weight_Xsection", 0.0, 10000000);
	RooRealVar iRunID("iRunID", "iRunID", 0, 10000000);
	RooRealVar Photon_Et("Photon_Et", "Photon_Et", 0, 10000000);

	

	RooArgSet *ntplVars = new RooArgSet(Photon_isEB, Mmumu, Mmumugamma, mmg_k, mmg_ik, mmg_s, mmg_logk, mmg_logik, mmg_logs);
ntplVars->add(Photon_r9);
ntplVars->add(isVeryLooseMMG);
ntplVars->add(isLooseMMG);
ntplVars->add(isTightMMG);
ntplVars->add(isAfterFSRCut1);
ntplVars->add(isAfterFSRCut2);
ntplVars->add(isAfterFSRCut3);
ntplVars->add(isAfterFSRCut4);
ntplVars->add(isMultipleCandidate);
ntplVars->add(nGenVerticess);
ntplVars->add(weight_pileUp);
ntplVars->add(weight_Xsection);
ntplVars->add(iRunID);
ntplVars->add(Photon_Et);
ntplVars->add(Photon_isEE);

//	RooArgSet ntplVars(Mmumu, Mmumugamma, Mmumugamma_5x5, Mmumugamma_SC, Mmumugamma_SCraw, mmg_k, mmg_ik, mmg_s, mmg_logk, mmg_logik, mmg_logs, mmg_k_5x5, mmg_ik_5x5, mmg_s_5x5, mmg_logk_5x5, mmg_logik_5x5, mmg_logs_5x5, mmg_k_SC, mmg_ik_SC, mmg_s_SC, mmg_logk_SC, mmg_logik_SC, mmg_logs_SC, mmg_k_SCraw, mmg_ik_SCraw, mmg_s_SCraw, mmg_logk_SCraw, mmg_logik_SCraw, mmg_logs_SCraw);
//	RooMCSet *MC = new RooMCSet("MC", "MC", Tree_MC, *ntplVars);

	vector<string> set_of_cuts;
	vector<string> set_of_cuts_DATA;
  vector<string> name;
  vector<string> name_DATA;
	vector<string> display;
	vector<string> display2;
	vector<string> display_DATA;
	vector<string> display_latex;
	vector<string> display_latex_DATA;
	vector<double> mc_alpha;
	vector<double> mc_alpha_err;
	vector<double> mc_m0;
	vector<double> mc_m0_err;
	vector<double> mc_n;
	vector<double> mc_n_err;
	vector<double> mc_sigma;
	vector<double> mc_sigma_err;

	vector<double> data_alpha;
	vector<double> data_alpha_err;
	vector<double> data_m0;
	vector<double> data_m0_err;
	vector<double> data_n;
	vector<double> data_n_err;
	vector<double> data_sigma;
	vector<double> data_sigma_err;

/*
  set_of_cuts.push_back("Photon_isEB == 1");
  display.push_back("EB, loose m_{#mu#mu#gamma}");
	name.push_back("EB_loose");


  set_of_cuts.push_back("Photon_isEB == 0");
  display.push_back("EE, loose m_{#mu#mu#gamma}");
	name.push_back("EE_loose");
*/
/*
	set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0");
  display.push_back("EB, tight m_{#mu#mu#gamma}");
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight");

  set_of_cuts.push_back("Photon_isEB == 0 && isTightMMG && isMultipleCandidate == 0");
  display.push_back("EE, tight m_{#mu#mu#gamma}");
//  display.push_back("ECAL Endcaps");
	name.push_back("EE_tight");
*/
/*
	set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.94");
  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 > .94");
  display_latex.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 > .94$");
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight-highR9");

	set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 < 0.94");
  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 < .94");
  display_latex.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 < .94$");
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight-lowR9");

  set_of_cuts.push_back("Photon_isEB == 0 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.95");
  display.push_back("EE, tight m_{#mu#mu#gamma}, r9 > .95");
  display_latex.push_back("EE, tight $m_{\\mu\\mu\\gamma}$, $r9 > .95$");
//  display.push_back("ECAL Endcaps");
	name.push_back("EE_tight-highR9");

  set_of_cuts.push_back("Photon_isEB == 0 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 < 0.95");
  display.push_back("EE, tight m_{#mu#mu#gamma}, r9 < .95");
  display_latex.push_back("EE, tight $m_{\\mu\\mu\\gamma}$, $r9 < .95$");
//  display.push_back("ECAL Endcaps");
	name.push_back("EE_tight-lowR9");
*/

	for( int iEB = 0 ; iEB < 2 ; iEB++ )
//	for( int iEB = 0 ; iEB < 1 ; iEB++ )
	{
		string sEB = "";
		if( iEB == 0 ) sEB = "EB";
		else sEB = "EE";
		for( int ir9 = 0 ; ir9 < 3 ; ir9++ )
//		for( int ir9 = 0 ; ir9 < 1 ; ir9++ )
		{
			string sR9 = "";
			string cutR9 = "";
				string displayR9 = "";
			if( ir9 == 0 ){
				sR9 = "-highR9-";
				if( iEB == 0 ){ cutR9 = "Photon_r9 > 0.94"; displayR9 = "R_{9} > .94"; }
				else { cutR9 = "Photon_r9 > 0.95"; displayR9 = "R_{9} > .95"; }
			} else if (ir9 == 1 ){
				sR9 = "-lowR9-";
        if( iEB == 0 ) { cutR9 = "Photon_r9 < 0.94"; displayR9 = "R_{9} < .94"; }
        else { cutR9 = "Photon_r9 <0.95"; displayR9 = "R_{9} < .95"; }
			} else {
				sR9 = "-inclusiveR9-";
				cutR9 = "1";
				displayR9 = " ";
			}
			for( int ipt = 0 ; ipt < 7 ; ipt++ )
//			for( int ipt = 4 ; ipt < 5 ; ipt++ )
			{
				string spt = "";
				string cutpt = "";
				string displaypt = "";
				string srun = "";
				string cutrun = "";
				string displayrun = "";
				srun = "-inclusive_run-";
				cutrun = "1";
				displayrun = " ";
				if( ipt == 0 ) {
					spt = "-10_lt_pt_lt_12-";
					cutpt = "10.0 < Photon_Et && Photon_Et < 12.0";
					displaypt = "10.0 < p_{T} < 12.0";
						// #######################################
						set_of_cuts.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str()));
						set_of_cuts_DATA.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str(), cutrun.c_str()));
						display.push_back(Form("%s, tight m_{#mu#mu#gamma}", sEB.c_str()));
						display2.push_back(Form("%s, %s", displayR9.c_str(), displaypt.c_str()));
					  display_DATA.push_back(Form("%s", displayrun.c_str()));
					  display_latex.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$", sEB.c_str(), displayR9.c_str(), displaypt.c_str()));
					  display_latex_DATA.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$, $%s$",  sEB.c_str(), displayR9.c_str(), displaypt.c_str(), displayrun.c_str()));
						name.push_back(Form("%s_tight%s%s", sEB.c_str(), sR9.c_str(), spt.c_str()));
						name_DATA.push_back(Form("%s_tight%s%s%s", sEB.c_str(), sR9.c_str(), spt.c_str(), srun.c_str()));
					} else if ( ipt == 1 ) {
					spt = "-12_lt_pt_lt_15-";
					cutpt = "12.0 < Photon_Et && Photon_Et < 15.0";
					displaypt = "12.0 < p_{T} < 15.0";
						// #######################################
						set_of_cuts.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str()));
						set_of_cuts_DATA.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str(), cutrun.c_str()));
						display.push_back(Form("%s, tight m_{#mu#mu#gamma}", sEB.c_str()));
						display2.push_back(Form("%s, %s", displayR9.c_str(), displaypt.c_str()));
					  display_DATA.push_back(Form("%s", displayrun.c_str()));
					  display_latex.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$", sEB.c_str(), displayR9.c_str(), displaypt.c_str()));
					  display_latex_DATA.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$, $%s$",  sEB.c_str(), displayR9.c_str(), displaypt.c_str(), displayrun.c_str()));
						name.push_back(Form("%s_tight%s%s", sEB.c_str(), sR9.c_str(), spt.c_str()));
						name_DATA.push_back(Form("%s_tight%s%s%s", sEB.c_str(), sR9.c_str(), spt.c_str(), srun.c_str()));
					} else if ( ipt == 2 ) {
					spt = "-15_lt_pt_lt_20-";
					cutpt = "15.0 < Photon_Et && Photon_Et < 20.0";
					displaypt = "15.0 < p_{T} < 20.0";
						// #######################################
						set_of_cuts.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str()));
						set_of_cuts_DATA.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str(), cutrun.c_str()));
						display.push_back(Form("%s, tight m_{#mu#mu#gamma}", sEB.c_str()));
						display2.push_back(Form("%s, %s", displayR9.c_str(), displaypt.c_str()));
					  display_DATA.push_back(Form("%s", displayrun.c_str()));
					  display_latex.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$", sEB.c_str(), displayR9.c_str(), displaypt.c_str()));
					  display_latex_DATA.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$, $%s$",  sEB.c_str(), displayR9.c_str(), displaypt.c_str(), displayrun.c_str()));
						name.push_back(Form("%s_tight%s%s", sEB.c_str(), sR9.c_str(), spt.c_str()));
						name_DATA.push_back(Form("%s_tight%s%s%s", sEB.c_str(), sR9.c_str(), spt.c_str(), srun.c_str()));
					} else if ( ipt == 3 ) {
					spt = "-20_lt_pt_lt_25-";
					cutpt = "20.0 < Photon_Et && Photon_Et < 25.0";
					displaypt = "20.0 < p_{T} < 25.0";
						// #######################################
						set_of_cuts.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str()));
						set_of_cuts_DATA.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str(), cutrun.c_str()));
						display.push_back(Form("%s, tight m_{#mu#mu#gamma}", sEB.c_str()));
						display2.push_back(Form("%s, %s", displayR9.c_str(), displaypt.c_str()));
					  display_DATA.push_back(Form("%s", displayrun.c_str()));
					  display_latex.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$", sEB.c_str(), displayR9.c_str(), displaypt.c_str()));
					  display_latex_DATA.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$, $%s$",  sEB.c_str(), displayR9.c_str(), displaypt.c_str(), displayrun.c_str()));
						name.push_back(Form("%s_tight%s%s", sEB.c_str(), sR9.c_str(), spt.c_str()));
						name_DATA.push_back(Form("%s_tight%s%s%s", sEB.c_str(), sR9.c_str(), spt.c_str(), srun.c_str()));
					} else if ( ipt == 4 ) {
					spt = "-25_lt_pt_lt_30-";
					cutpt = "25.0 < Photon_Et && Photon_Et < 30.0";
					displaypt = "25.0 < p_{T} < 30.0";
						// #######################################
						set_of_cuts.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str()));
						set_of_cuts_DATA.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str(), cutrun.c_str()));
						display.push_back(Form("%s, tight m_{#mu#mu#gamma}", sEB.c_str()));
						display2.push_back(Form("%s, %s", displayR9.c_str(), displaypt.c_str()));
					  display_DATA.push_back(Form("%s", displayrun.c_str()));
					  display_latex.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$", sEB.c_str(), displayR9.c_str(), displaypt.c_str()));
					  display_latex_DATA.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$, $%s$",  sEB.c_str(), displayR9.c_str(), displaypt.c_str(), displayrun.c_str()));
						name.push_back(Form("%s_tight%s%s", sEB.c_str(), sR9.c_str(), spt.c_str()));
						name_DATA.push_back(Form("%s_tight%s%s%s", sEB.c_str(), sR9.c_str(), spt.c_str(), srun.c_str()));
					} else if ( ipt == 5 ) {
					spt = "-30_lt_pt_lt_inf-";
					cutpt = "30.0 < Photon_Et";
					displaypt = "30.0 < p_{T}";
						// #######################################
						set_of_cuts.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str()));
						set_of_cuts_DATA.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str(), cutrun.c_str()));
						display.push_back(Form("%s, tight m_{#mu#mu#gamma}", sEB.c_str()));
						display2.push_back(Form("%s, %s", displayR9.c_str(), displaypt.c_str()));
					  display_DATA.push_back(Form("%s", displayrun.c_str()));
					  display_latex.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$", sEB.c_str(), displayR9.c_str(), displaypt.c_str()));
					  display_latex_DATA.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$, $%s$",  sEB.c_str(), displayR9.c_str(), displaypt.c_str(), displayrun.c_str()));
						name.push_back(Form("%s_tight%s%s", sEB.c_str(), sR9.c_str(), spt.c_str()));
						name_DATA.push_back(Form("%s_tight%s%s%s", sEB.c_str(), sR9.c_str(), spt.c_str(), srun.c_str()));
					} else if ( ipt == 6 ) {
          spt = "-inclusivept-";
          cutpt = "1";
          displaypt = "inclusive p_{T}";

					for( int irun = 0 ; irun < 6 ; irun++ )
	//				for( int irun = 0 ; irun < 1 ; irun++ )
					{
						if( irun == 0 ) {
							srun = "-160431_lt_run_lt_163869-";
							cutrun = "160431 < iRunID && iRunID < 163869";
							displayrun = "160431 < run < 163869";
						} else if ( irun == 1 ) {
							srun = "-165071_lt_run_lt_165970-";
							cutrun = "165071 < iRunID && iRunID < 165970";
							displayrun = "165071 < run < 165970";
						} else if ( irun == 2 ) {
							srun = "-165971_lt_run_lt_166502-";
							cutrun = "165971 < iRunID && iRunID < 166502";
							displayrun = "165971 < run < 166502";
						} else if ( irun == 3 ) {
							srun = "-166503_lt_run_lt_166861-";
							cutrun = "166503 < iRunID && iRunID < 166861";
							displayrun = "166503 < run < 166861";
						} else if ( irun == 4 ) {
							srun = "-166862_lt_run_lt_166967-";
							cutrun = "166862 < iRunID && iRunID < 166967";
							displayrun = "166862 < run < 166967";
						}	else {
							srun = "-inclusive_run-";
							cutrun = "1";
							displayrun = " ";
						}				
						// #######################################
						set_of_cuts.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str()));
						set_of_cuts_DATA.push_back(Form("Photon_is%s == 1 && isTightMMG && isMultipleCandidate == 0 && %s && %s && %s", sEB.c_str(), cutR9.c_str(), cutpt.c_str(), cutrun.c_str()));
						display.push_back(Form("%s, tight m_{#mu#mu#gamma}", sEB.c_str()));
						display2.push_back(Form("%s, %s", displayR9.c_str(), displaypt.c_str()));
					  display_DATA.push_back(Form("%s", displayrun.c_str()));
					  display_latex.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$", sEB.c_str(), displayR9.c_str(), displaypt.c_str()));
					  display_latex_DATA.push_back(Form("%s, tight $m_{\\mu\\mu\\gamma}$, $%s$, $%s$, $%s$",  sEB.c_str(), displayR9.c_str(), displaypt.c_str(), displayrun.c_str()));
						name.push_back(Form("%s_tight%s%s", sEB.c_str(), sR9.c_str(), spt.c_str()));
						name_DATA.push_back(Form("%s_tight%s%s%s", sEB.c_str(), sR9.c_str(), spt.c_str(), srun.c_str()));
	
	//					set_of_cuts_DATA.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.94 && 160431 < iRunID && iRunID < 163869");
	//				  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 > .94");
	//				  display_DATA.push_back("160431 < Run < 163869");
	//				  display_latex.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 > .94$");
	//				  display_latex_DATA.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 > .94$, 160431 < Run < 163869");
	//				  name.push_back("EB_tight-highR9");
	//				  name_DATA.push_back("EB_tight-highR9_160431_lt_Run_lt163869");
	
						// #######################################
	
        	} 
				}
			}
		}
	}



/*
	set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.94");
	set_of_cuts_DATA.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.94 && 160431 < iRunID && iRunID < 163869");
  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 > .94");
  display_DATA.push_back("160431 < Run < 163869");
  display_latex.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 > .94$");
  display_latex_DATA.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 > .94$, 160431 < Run < 163869");
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight-highR9");
	name_DATA.push_back("EB_tight-highR9_160431_lt_Run_lt163869");


	set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.94");
	set_of_cuts_DATA.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.94 && 160431 < iRunID && iRunID < 163869");
  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 > .94");
  display_DATA.push_back("160431 < Run < 163869");
  display_latex.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 > .94$");
  display_latex_DATA.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 > .94$, 160431 < Run < 163869");
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight-highR9");
	name_DATA.push_back("EB_tight-highR9_160431_lt_Run_lt163869");
*/

/*
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight-highR9_160431_lt_Run_lt163869");

	set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.94 && 165071 < iRunID && iRunID < 165970");
  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 > .94, 165071 < Run < 165970");
  display_latex.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 > .94$, 165071 < Run < 165970");
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight-highR9_165071_lt_Run_lt165970");

	set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.94 && 165971 < iRunID && iRunID < 166502");
  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 > .94, 165971 < Run < 166502");
  display_latex.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 > .94$, 165971 < Run < 166502");
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight-highR9_165971_lt_Run_lt166502");

	set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.94 && 166503 < iRunID && iRunID < 166861");
  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 > .94, 166503 < Run < 166861");
  display_latex.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 > .94$, 166503 < Run < 166861");
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight-highR9_166503_lt_Run_lt166861");

	set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.94 && 166862 < iRunID && iRunID < 167784");
  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 > .94, 166862 < Run < 167784");
  display_latex.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 > .94$, 166862 < Run < 167784");
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight-highR9_166862_lt_Run_lt167784");
*/

//return;

for(int idata=0; idata < 2; idata++){
	RooDataSet *Data = new RooDataSet();
	bool isData;
	if(idata ==0)
	{
		Data = new RooDataSet("Data", "Data", Tree_Data, *ntplVars);
		isData = true;
	} else {
		Data = new RooDataSet("MC", "MC", Tree_MC, *ntplVars, "", "weight_pileUp");
		isData = false;
	}

const int size = set_of_cuts.size();
	RooDataSet* Data_subset[size];


for(int i=0; i<set_of_cuts.size() ; i++){

	if( idata == 0 ) Data_subset[i] = (RooDataSet*)Data->reduce(set_of_cuts_DATA[i].c_str());
  else Data_subset[i] = (RooDataSet*)Data->reduce(set_of_cuts[i].c_str());

/*	
// ***************************************************************
// ***** Mmumugamma fit
// ***************************************************************


	// BREIT-WIGNER
	RooRealVar mmg_BW_mean("mmg_BW_mean", "BW m_{0}",  91.188, 85.0, 95.0,"GeV");
	RooRealVar mmg_BW_width("mmg_BW_width", "BW #Gamma", 2.45, 2.0,3.0,"GeV");
	mmg_BW_mean.setConstant();
	mmg_BW_width.setConstant();
	RooBreitWigner mmg_BW("mmg_BW", "mmg_BW", Mmumugamma, mmg_BW_mean, mmg_BW_width);


	// CRYSTALBALL
  RooRealVar mmg_CB_m0("mmg_CB_m0", "CB #Delta m_{0}", 0.0, -10.0, 10.0, "GeV");  
  RooRealVar mmg_CB_sigma("mmg_CB_sigma", "CB #sigma", 1.45, 0.01, 5.0, "GeV");
  RooRealVar mmg_CB_alpha("mmg_CB_alpha", "CB #alpha", 0.98, 0.01, 10.0);
  RooRealVar mmg_CB_n("mmg_CB_n", "CB n", 3.8, 0.5, 50.0);
  RooCBShape mmg_CrystalBall("mmg_CrystalBall","mmg_CrystalBall", Mmumugamma, mmg_CB_m0, mmg_CB_sigma, mmg_CB_alpha, mmg_CB_n);

	// CONVOLUTION
	RooFFTConvPdf mmg_BWxCB("mmg_BWxCB", "mmg_BWxCB", Mmumugamma, mmg_BW, mmg_CrystalBall);

	mmg_BWxCB.fitTo(*Data_subset[i]);
	RooArgSet* mmg_BWxCB_param = mmg_BWxCB.getVariables();
	mmg_BWxCB_param->Print("v");

	TCanvas* mmg_BWxCB_canvas = new TCanvas("mmg_BWxCB_canvas", "mmg_BWxCB_canvas");
	RooPlot* mmg_BWxCB_frame = Mmumugamma.frame(Title("m_{#mu#mu#gamma} fitted with Z^{0} Breit-Wigner convoluted with  a Crystal Ball"));
//	RooPlot* mmg_BWxCB_frame = Mmumugamma.frame(Title(" "));
	Data_subset[i]->plotOn(mmg_BWxCB_frame, Name("data"));
	mmg_BWxCB.plotOn(mmg_BWxCB_frame, Name("model"));
//	mmg_BWxCB.paramOn(mmg_BWxCB_frame, Format("NEU", AutoPrecision(2)), Parameters(RooArgSet(mmg_BW_mean, mmg_BW_width, mmg_CB_m0, mmg_CB_sigma, mmg_CB_alpha, mmg_CB_n)), ShowConstants(kTRUE));
	mmg_BWxCB_frame->Draw();


	Double_t mmg_BWxCB_chi2_ndf = mmg_BWxCB_frame->chiSquare("model", "data", 4);
	cout << "mmg_BWxCB_chi2_ndf= " << mmg_BWxCB_chi2_ndf << endl;

	TLatex latexLabel;
	latexLabel.SetTextSize(0.06);
	latexLabel.SetNDC();
	latexLabel.DrawLatex(0.20, 0.88, "CMS Preliminary 2011");
	latexLabel.DrawLatex(0.20, 0.82, "#sqrt{s} = 7 TeV");
	latexLabel.DrawLatex(0.70, 0.88, isData ? "DATA" : "MC");
	latexLabel.DrawLatex(0.70, 0.82, display[i].c_str());
	latexLabel.SetTextSize(0.03);

	TIterator *it = (TIterator*) mmg_BWxCB_param->createIterator();	
//	cout << mmg_BWxCB_param->getRealValue("BW #Gamma") << endl;
//	mmg_BWxCB_param->printValue(cout);
//	it->Next()->Print();
//	mmg_BW_width.Print();
//	cout << "mmg_BW_width.GetName()= " << mmg_BW_width.GetName() << "\tmmg_BW_width.getVal()= " << mmg_BW_width.getVal() << endl;
	RooRealVar* obj = new RooRealVar();
	double position = 0.82;
	gStyle->SetOptTitle(0);
	position -= 0.04;
	latexLabel.DrawLatex(0.20, position, "Fit: BW #otimes CB");
	while(( (RooRealVar*)obj = it->Next()) != 0)
	{
		if( ! strcmp(((char*)obj->GetName()), "Mmumugamma") ) continue;
//		cout << "obj->getTitle()= " << obj->getTitle() << endl; // char*
//		cout << "obj->GetName()= " << obj->GetName() << endl; // char*
//		cout << "obj->getVal()= " << obj->getVal() << endl; // Double_t
//		cout << "obj->getError()= " << obj->getError() << endl; // Double_t
//		cout << "obj->getUnit()= " << obj->getUnit() << endl; // Text_t
//		cout << endl;
		position -= 0.04;
//		double plaf = (double)obj->getVal();
//		cout << "plaf= " << plaf << endl;
		std::ostringstream valueStream;
		if( (double)obj->getError() != 0.0 )
		{
			valueStream << setprecision (3) << fixed << (double)obj->getVal() << " +- " << (double)obj->getError();
		} else {
			 valueStream << setprecision (3) << fixed << (double)obj->getVal();
		}
		string valueString = valueStream.str();
		latexLabel.DrawLatex(0.20, position, Form("%s = %s %s", obj->GetTitle(), valueString.c_str(), (char*)obj->getUnit()));
//		latexLabel.DrawLatex(0.18, position, Form("%s = %d \pm %d (%s)", obj->GetTitle(), (double)obj->getVal(), (double)obj->getError(), (char*)obj->getUnit()));
	}
//	cout << "it->Next()->GetName()= " << it->Next()->GetName() << "\tit->Next()->getVal()= " << it->Next()->getVal() << endl;

	position -= 0.04;
	std::ostringstream valueStream;
	valueStream << setprecision (4) << fixed << (double)mmg_BWxCB_chi2_ndf;
	string valueString = valueStream.str();
	latexLabel.DrawLatex(0.20, position, Form("#chi^{2} / ndf = %s", valueString.c_str()));

//	Data_subset[i]->Clear();
	mmg_BWxCB_canvas->Print(Form("gif/mmg_BWxCB_%s.gif", name[i].c_str()));
	mmg_BWxCB_canvas->Print(Form("eps/mmg_BWxCB_%s.eps", name[i].c_str()));
	mmg_BWxCB_canvas->Print(Form("png/mmg_BWxCB_%s.png", name[i].c_str()));
	mmg_BWxCB_canvas->Print(Form("C/mmg_BWxCB_%s.C", name[i].c_str()));
	system(Form("convert eps/mmg_BWxCB_%s.eps pdf/mmg_BWxCB_%s.pdf", name[i].c_str(), name[i].c_str()));

*/
// ***************************************************************
// ***** k fit
// ***************************************************************
/*
  // CRYSTALBALL
  RooRealVar mmg_k_CB_m0("mmg_k_CB_m0", "CB #Delta m_{0}", 1.0, -5.0, 5.0, "GeV");  
  RooRealVar mmg_k_CB_sigma("mmg_k_CB_sigma", "CB #sigma", 0.45, 0.01, 0.5, "GeV");
  RooRealVar mmg_k_CB_alpha("mmg_k_CB_alpha", "CB #alpha", -1.0, -10.01, 10.0);
  RooRealVar mmg_k_CB_n("mmg_k_CB_n", "CB n", 2.0, 0.5, 500.0);
//  RooCBShape mmg_k_CrystalBall("mmg_k_CrystalBall","mmg_k_CrystalBall", mmg_k, mmg_k_CB_m0, mmg_k_CB_sigma, mmg_k_CB_alpha, mmg_k_CB_n);
  RooCBShape model("mmg_k_CrystalBall","mmg_k_CrystalBall", mmg_k, mmg_k_CB_m0, mmg_k_CB_sigma, mmg_k_CB_alpha, mmg_k_CB_n);

	// BREIT-WIGNER
	RooRealVar mmg_k_BW_mean("mmg_k_BW_mean", "BW m_{0}", 0.0 , -2.0, 2.0 ,"GeV");
	RooRealVar mmg_k_BW_width("mmg_k_BW_width", "BW #Gamma", 1.0, 0.0, 5.0,"GeV");
	RooBreitWigner mmg_k_BW("mmg_k_BW", "mmg_k_BW", mmg_k, mmg_k_BW_mean, mmg_k_BW_width);


  // CONVOLUTION
//  RooFFTConvPdf model("mmg_k_BWxCB", "mmg_k_BWxCB", mmg_k, mmg_k_BW, mmg_k_CrystalBall);


	model.fitTo(*Data_subset[i]);
  RooArgSet* mmg_k_BWxCB_param = model.getVariables();
  mmg_k_BWxCB_param->Print("v");

	TCanvas *mmg_k_BWxCB_canvas = new TCanvas("mmg_k_BWxCB_canvas", "mmg_k_BWxCB_canvas");
	RooPlot* mmg_k_frame = mmg_k.frame(Title("k"));
	Data_subset[i]->plotOn(mmg_k_frame, Name("data"));
	model.plotOn(mmg_k_frame, Name("model"));
	mmg_k_frame->Draw();

//	Double_t mmg_k_BWxCB_chi2_ndf = mmg_k_frame->chiSquare("model", "data", 6);
	Double_t mmg_k_BWxCB_chi2_ndf = mmg_k_frame->chiSquare("model", "data", 4);
	cout << "mmg_k_BWxCB_chi2_ndf= " << mmg_k_BWxCB_chi2_ndf << endl;	
	TLatex latexLabel;
	latexLabel.SetTextSize(0.06);
	latexLabel.SetNDC();
	latexLabel.DrawLatex(0.20, 0.88, "CMS Preliminary 2011");
	latexLabel.DrawLatex(0.20, 0.82, "#sqrt{s} = 7 TeV");
	latexLabel.DrawLatex(0.70, 0.88, isData ? "DATA" : "MC");
	latexLabel.DrawLatex(0.70, 0.82, display[i].c_str());
	latexLabel.SetTextSize(0.03);

	TIterator *it = (TIterator*) mmg_k_BWxCB_param->createIterator();	
//	cout << mmg_k_BWxCB_param->getRealValue("BW #Gamma") << endl;
//	mmg_k_BWxCB_param->printValue(cout);
//	it->Next()->Print();
//	mmg_BW_width.Print();
//	cout << "mmg_BW_width.GetName()= " << mmg_BW_width.GetName() << "\tmmg_BW_width.getVal()= " << mmg_BW_width.getVal() << endl;
	RooRealVar* obj = new RooRealVar();
	double position = 0.82;
	gStyle->SetOptTitle(0);
	position -= 0.04;
//	latexLabel.DrawLatex(0.20, position, "Fit: BW #otimes CB");
	latexLabel.DrawLatex(0.20, position, "Fit: Crystal-Ball");
	while(( (RooRealVar*)obj = it->Next()) != 0)
	{
		if( ! strcmp(((char*)obj->GetName()), "mmg_k") ) continue;
//		cout << "obj->getTitle()= " << obj->getTitle() << endl; // char*
//		cout << "obj->GetName()= " << obj->GetName() << endl; // char*
//		cout << "obj->getVal()= " << obj->getVal() << endl; // Double_t
//		cout << "obj->getError()= " << obj->getError() << endl; // Double_t
//		cout << "obj->getUnit()= " << obj->getUnit() << endl; // Text_t
//		cout << endl;
		position -= 0.04;
//		double plaf = (double)obj->getVal();
//		cout << "plaf= " << plaf << endl;
		std::ostringstream valueStream;
		if( (double)obj->getError() != 0.0 )
		{
			valueStream << setprecision (3) << fixed << (double)obj->getVal() << " +- " << (double)obj->getError();
		} else {
			 valueStream << setprecision (3) << fixed << (double)obj->getVal();
		}
		string valueString = valueStream.str();
		latexLabel.DrawLatex(0.20, position, Form("%s = %s %s", obj->GetTitle(), valueString.c_str(), (char*)obj->getUnit()));
//		latexLabel.DrawLatex(0.18, position, Form("%s = %d \pm %d (%s)", obj->GetTitle(), (double)obj->getVal(), (double)obj->getError(), (char*)obj->getUnit()));
	}
//	cout << "it->Next()->GetName()= " << it->Next()->GetName() << "\tit->Next()->getVal()= " << it->Next()->getVal() << endl;

	position -= 0.04;
	std::ostringstream valueStream;
	valueStream << setprecision (4) << fixed << (double)mmg_k_BWxCB_chi2_ndf;
	string valueString = valueStream.str();
	latexLabel.DrawLatex(0.20, position, Form("#chi^{2} / ndf = %s", valueString.c_str()));
*/
//	Data_subset[i]->Clear();
/*
	mmg_k_BWxCB_canvas->Print(Form("gif/mmg_k_BWxCB_%s.gif", name[i].c_str()));
	mmg_k_BWxCB_canvas->Print(Form("eps/mmg_k_BWxCB_%s.eps", name[i].c_str()));
	mmg_k_BWxCB_canvas->Print(Form("png/mmg_k_BWxCB_%s.png", name[i].c_str()));
	mmg_k_BWxCB_canvas->Print(Form("C/mmg_k_BWxCB_%s.C", name[i].c_str()));
	system(Form("convert eps/mmg_k_BWxCB_%s.eps pdf/mmg_k_BWxCB_%s.pdf", name[i].c_str(), name[i].c_str()));
*/
/*
	mmg_k_BWxCB_canvas->Print(Form("gif/mmg_k_CB_%s_%s.gif", isData?"DATA":"MC", name[i].c_str()));
	mmg_k_BWxCB_canvas->Print(Form("eps/mmg_k_CB_%s_%s.eps", isData?"DATA":"MC", name[i].c_str()));
	mmg_k_BWxCB_canvas->Print(Form("png/mmg_k_CB_%s_%s.png", isData?"DATA":"MC", name[i].c_str()));
	mmg_k_BWxCB_canvas->Print(Form("C/mmg_k_CB_%s_%s.C", isData?"DATA":"MC", name[i].c_str()));
	system(Form("convert eps/mmg_k_CB_%s_%s.eps pdf/mmg_k_CB_%s_%s.pdf", isData?"DATA":"MC", name[i].c_str(), isData?"DATA":"MC", name[i].c_str()));
*/

// ***************************************************************
// ***** s fit
// ***************************************************************
  // CRYSTALBALL
  RooRealVar mmg_s_CB_m0("mmg_s_CB_m0", "CB #Delta m_{0}", 1.0, -5.0, 5.0, "GeV");  
  RooRealVar mmg_s_CB_sigma("mmg_s_CB_sigma", "CB #sigma", 0.45, 0.0, 0.5, "GeV");
  RooRealVar mmg_s_CB_alpha("mmg_s_CB_alpha", "CB #alpha", 1.0, 0.0, 10.0);
  RooRealVar mmg_s_CB_n("mmg_s_CB_n", "CB n", 2.0, 0.5, 20.0);
  RooCBShape mmg_s_CrystalBall("mmg_s_CrystalBall","mmg_s_CrystalBall", mmg_s, mmg_s_CB_m0, mmg_s_CB_sigma, mmg_s_CB_alpha, mmg_s_CB_n);
  RooCBShape model("mmg_s_CrystalBall","mmg_s_CrystalBall", mmg_s, mmg_s_CB_m0, mmg_s_CB_sigma, mmg_s_CB_alpha, mmg_s_CB_n);

	// BREIT-WIGNER
	RooRealVar mmg_s_BW_mean("mmg_s_BW_mean", "BW m_{0}", 0.0 , -2.0, 2.0 , "GeV");
	RooRealVar mmg_s_BW_width("mmg_s_BW_width", "BW #Gamma", 1.0, 0.0, 5.0, "GeV");
	RooBreitWigner mmg_s_BW("mmg_s_BW", "mmg_s_BW", mmg_s, mmg_s_BW_mean, mmg_s_BW_width);

	// GAUSSIAN
	RooRealVar mmg_s_G_frac("mmg_s_G_frac", "G fraction", 0.2, 0.0, 0.5); 
  RooRealVar mmg_s_G_mu("mmg_s_G_mu", "mmg_s_G_mu", 0.0, -2.0, 2.0);
  RooRealVar mmg_s_G_sigmagauss("mmg_s_G_sigmagauss", "G #sigma", 0.8, 0.05, 2.0, "GeV");
  //RooGaussian mmg_s_G_Gauss("mmg_s_G_Gauss", "mmg_s_G_Gauss", mmg_s, mmg_s_G_mu, mmg_s_G_sigmagauss);
  RooGaussian mmg_s_G_Gauss("mmg_s_G_Gauss", "mmg_s_G_Gauss", mmg_s, mmg_s_CB_m0, mmg_s_G_sigmagauss);

  // CONVOLUTION
  //RooFFTConvPdf model("mmg_s_BWxCB", "mmg_s_BWxCB", mmg_s, mmg_s_BW, mmg_s_CrystalBall);
  //RooFFTConvPdf model("mmg_s_BWxCB", "mmg_s_BWxCB", mmg_s, mmg_s_CrystalBall, mmg_s_G_Gauss);

	// SUM
	//RooAddPdf model("mmg_s_CB_plus_G", "mmg_s_CB_plus_G", RooArgList(mmg_s_G_Gauss, mmg_s_CrystalBall), mmg_s_G_frac);

//	model.fitTo(*Data_subset[i], Range(-0.2, 0.2));
	model.fitTo(*Data_subset[i]);
  RooArgSet* mmg_s_BWxCB_param = model.getVariables();
  mmg_s_BWxCB_param->Print("v");

	if(isData)
	{
		data_alpha.push_back(mmg_s_CB_alpha.getVal());
		data_alpha_err.push_back(mmg_s_CB_alpha.getError());
		data_m0.push_back(mmg_s_CB_m0.getVal());
		data_m0_err.push_back(mmg_s_CB_m0.getError());
		data_sigma.push_back(mmg_s_CB_sigma.getVal());
		data_sigma_err.push_back(mmg_s_CB_sigma.getError());
		data_n.push_back(mmg_s_CB_n.getVal());
		data_n_err.push_back(mmg_s_CB_n.getError());
	} else {
		mc_alpha.push_back(mmg_s_CB_alpha.getVal());
		mc_alpha_err.push_back(mmg_s_CB_alpha.getError());
		mc_m0.push_back(mmg_s_CB_m0.getVal());
		mc_m0_err.push_back(mmg_s_CB_m0.getError());
		mc_sigma.push_back(mmg_s_CB_sigma.getVal());
		mc_sigma_err.push_back(mmg_s_CB_sigma.getError());
		mc_n.push_back(mmg_s_CB_n.getVal());
		mc_n_err.push_back(mmg_s_CB_n.getError());
	}



	TCanvas *mmg_s_BWxCB_canvas = new TCanvas("mmg_s_BWxCB_canvas", "mmg_s_BWxCB_canvas");
	RooPlot* mmg_s_frame = mmg_s.frame(Title("k"));
	Data_subset[i]->plotOn(mmg_s_frame, Name("data"));
//	model.plotOn(mmg_s_frame, Components("mmg_s_CrystalBall"), LineStyle(kDashed), LineColor(kRed));
//	model.plotOn(mmg_s_frame, Components("mmg_s_G_Gauss"), LineStyle(kDashed), LineColor(kGreen));
	model.plotOn(mmg_s_frame, Name("model"));
	mmg_s_frame->Draw();

//	Double_t mmg_s_BWxCB_chi2_ndf = mmg_s_frame->chiSquare("model", "data", 6);
	Double_t mmg_s_BWxCB_chi2_ndf = mmg_s_frame->chiSquare("model", "data", 4);
	cout << "mmg_s_BWxCB_chi2_ndf= " << mmg_s_BWxCB_chi2_ndf << endl;	
	TLatex latexLabel;
	latexLabel.SetNDC();
	latexLabel.SetTextSize(0.03);
	latexLabel.DrawLatex(0.13, 0.96, "CMS Preliminary 2011");
	latexLabel.DrawLatex(0.42, 0.96, "#sqrt{s} = 7 TeV");
	latexLabel.DrawLatex(0.57, 0.96, isData ? "DATA" : "Simulation");
	latexLabel.SetTextSize(0.05);
//	latexLabel.DrawLatex(0.20, 0.88, "CMS Preliminary 2011");
//	latexLabel.DrawLatex(0.20, 0.82, "#sqrt{s} = 7 TeV");
//	latexLabel.DrawLatex(0.65, 0.88, isData ? "DATA" : "Simulation");
	latexLabel.DrawLatex(0.65, 0.88, display[i].c_str());
	latexLabel.DrawLatex(0.65, 0.80, display2[i].c_str());
	if( idata == 0 ) latexLabel.DrawLatex(0.65, 0.72, display_DATA[i].c_str());
	latexLabel.SetTextSize(0.03);

	TIterator *it = (TIterator*) mmg_s_BWxCB_param->createIterator();	
//	cout << mmg_s_BWxCB_param->getRealValue("BW #Gamma") << endl;
//	mmg_s_BWxCB_param->printValue(cout);
//	it->Next()->Print();
//	mmg_BW_width.Print();
//	cout << "mmg_BW_width.GetName()= " << mmg_BW_width.GetName() << "\tmmg_BW_width.getVal()= " << mmg_BW_width.getVal() << endl;
	RooRealVar* obj = new RooRealVar();
	double position = 0.92;
	gStyle->SetOptTitle(0);
	position -= 0.04;
//	latexLabel.DrawLatex(0.20, position, "Fit: BW #otimes CB");
	latexLabel.DrawLatex(0.20, position, "Fit: Crystal-Ball + Gaussian");
	while(( (RooRealVar*)obj = it->Next()) != 0)
	{
		if( ! strcmp(((char*)obj->GetName()), "mmg_s") ) continue;
//		cout << "obj->getTitle()= " << obj->getTitle() << endl; // char*
//		cout << "obj->GetName()= " << obj->GetName() << endl; // char*
//		cout << "obj->getVal()= " << obj->getVal() << endl; // Double_t
//		cout << "obj->getError()= " << obj->getError() << endl; // Double_t
//		cout << "obj->getUnit()= " << obj->getUnit() << endl; // Text_t
//		cout << endl;
		position -= 0.04;
//		double plaf = (double)obj->getVal();
//		cout << "plaf= " << plaf << endl;
		std::ostringstream valueStream;
		if( (double)obj->getError() != 0.0 )
		{
			valueStream << setprecision (3) << fixed << (double)obj->getVal() << " +- " << (double)obj->getError();
		} else {
			 valueStream << setprecision (3) << fixed << (double)obj->getVal();
		}
		string valueString = valueStream.str();
		latexLabel.DrawLatex(0.20, position, Form("%s = %s %s", obj->GetTitle(), valueString.c_str(), (char*)obj->getUnit()));
//		latexLabel.DrawLatex(0.18, position, Form("%s = %d \pm %d (%s)", obj->GetTitle(), (double)obj->getVal(), (double)obj->getError(), (char*)obj->getUnit()));
	}
//	cout << "it->Next()->GetName()= " << it->Next()->GetName() << "\tit->Next()->getVal()= " << it->Next()->getVal() << endl;

	position -= 0.04;
	std::ostringstream valueStream;
	valueStream << setprecision (4) << fixed << (double)mmg_s_BWxCB_chi2_ndf;
	string valueString = valueStream.str();
	latexLabel.DrawLatex(0.20, position, Form("#chi^{2} / ndf = %s", valueString.c_str()));

//	Data_subset[i]->Clear();
/*
	mmg_s_BWxCB_canvas->Print(Form("gif/mmg_s_BWxCB_%s.gif", name[i].c_str()));
	mmg_s_BWxCB_canvas->Print(Form("eps/mmg_s_BWxCB_%s.eps", name[i].c_str()));
	mmg_s_BWxCB_canvas->Print(Form("png/mmg_s_BWxCB_%s.png", name[i].c_str()));
	mmg_s_BWxCB_canvas->Print(Form("C/mmg_s_BWxCB_%s.C", name[i].c_str()));
	system(Form("convert eps/mmg_s_BWxCB_%s.eps pdf/mmg_s_BWxCB_%s.pdf", name[i].c_str(), name[i].c_str()));
*/
	if( idata == 0 )
	{
		mmg_s_BWxCB_canvas->Print(Form("gif/mmg_s_CB_%s_%s.gif", isData?"DATA":"MC", name_DATA[i].c_str()));
		mmg_s_BWxCB_canvas->Print(Form("eps/mmg_s_CB_%s_%s.eps", isData?"DATA":"MC", name_DATA[i].c_str()));
		mmg_s_BWxCB_canvas->Print(Form("png/mmg_s_CB_%s_%s.png", isData?"DATA":"MC", name_DATA[i].c_str()));
		mmg_s_BWxCB_canvas->Print(Form("C/mmg_s_CB_%s_%s.C", isData?"DATA":"MC", name_DATA[i].c_str()));
		system(Form("convert eps/mmg_s_CB_%s_%s.eps pdf/mmg_s_CB_%s_%s.pdf", isData?"DATA":"MC", name_DATA[i].c_str(), isData?"DATA":"MC", name_DATA[i].c_str()));
	} else {
		mmg_s_BWxCB_canvas->Print(Form("gif/mmg_s_CB_%s_%s.gif", isData?"DATA":"MC", name[i].c_str()));
		mmg_s_BWxCB_canvas->Print(Form("eps/mmg_s_CB_%s_%s.eps", isData?"DATA":"MC", name[i].c_str()));
		mmg_s_BWxCB_canvas->Print(Form("png/mmg_s_CB_%s_%s.png", isData?"DATA":"MC", name[i].c_str()));
		mmg_s_BWxCB_canvas->Print(Form("C/mmg_s_CB_%s_%s.C", isData?"DATA":"MC", name[i].c_str()));
		system(Form("convert eps/mmg_s_CB_%s_%s.eps pdf/mmg_s_CB_%s_%s.pdf", isData?"DATA":"MC", name[i].c_str(), isData?"DATA":"MC", name[i].c_str()));
	}

} // end of loop over categories
}// end of loop over data / mc

// TWIKI TABLES
cout << "|\t *DATA* \t|\t *s* \t|\t *sigma* \t|\t *alpha* \t|\t *n* \t|" << endl; 

for(int i=0; i < data_alpha.size(); i++)
{
	cout << setprecision (3) << fixed  << "|\t" << name_DATA[i] << "\t"
	<< "|\t" << data_m0[i] << " +- " << data_m0_err[i] << "\t"
	<< "|\t" << data_sigma[i] << " +- " << data_sigma_err[i] << "\t"
	<< "|\t" << data_alpha[i] << " +- " << data_alpha_err[i] << "\t"
	<< "|\t" << data_n[i] << " +- " << data_n_err[i] << "\t|" << endl;
}

cout << "|\t *MC* \t|\t *s* \t|\t *sigma* \t|\t *alpha* \t|\t *n* \t|" << endl; 

for(int i=0; i < mc_alpha.size(); i++)
{
	cout << setprecision (3) << fixed  << "|\t" << name[i] << "\t"
	<< "|\t" << mc_m0[i] << " +- " << mc_m0_err[i] << "\t"
	<< "|\t" << mc_sigma[i] << " +- " << mc_sigma_err[i] << "\t"
	<< "|\t" << mc_alpha[i] << " +- " << mc_alpha_err[i] << "\t"
	<< "|\t" << mc_n[i] << " +- " << mc_n_err[i] << "\t|" << endl;
}

cout << endl << endl;
for(int i=0; i < mc_alpha.size(); i++)
{
	cout << "|\t *" << name_DATA[i] << "* \t|\t *s* \t|\t *sigma* \t|\t *alpha* \t|\t *n* \t|" << endl;
  cout << setprecision (3) << fixed  << "|\t" << " data " << "\t"
  << "|\t" << data_m0[i] << " +- " << data_m0_err[i] << "\t"
  << "|\t" << data_sigma[i] << " +- " << data_sigma_err[i] << "\t"
  << "|\t" << data_alpha[i] << " +- " << data_alpha_err[i] << "\t"
  << "|\t" << data_n[i] << " +- " << data_n_err[i] << "\t|"
	<< endl;
  cout << setprecision (3) << fixed  << "|\t" << " data (%)" << "\t"
  << "|\t" << 100.0 * data_m0[i] << " +- " << 100.0 * data_m0_err[i] << "\t"
  << "|\t" << 100.0 * data_sigma[i] << " +- " << 100.0 * data_sigma_err[i] << "\t"
  << "|\t\t"
  << "|\t\t|"
	<< endl;
  cout << setprecision (3) << fixed  << "|\t" << " mc " << "\t"
  << "|\t" << mc_m0[i] << " +- " << mc_m0_err[i] << "\t"
  << "|\t" << mc_sigma[i] << " +- " << mc_sigma_err[i] << "\t"
  << "|\t" << mc_alpha[i] << " +- " << mc_alpha_err[i] << "\t"
  << "|\t" << mc_n[i] << " +- " << mc_n_err[i] << "\t|"
	<< endl;
  cout << setprecision (3) << fixed  << "|\t" << " mc (%)" << "\t"
  << "|\t" << 100.0 * mc_m0[i] << " +- " << 100.0 * mc_m0_err[i] << "\t"
  << "|\t" << 100.0 * mc_sigma[i] << " +- " << 100.0 * mc_sigma_err[i] << "\t"
  << "|\t\t"
  << "|\t\t|"
	<< endl;
	cout << setprecision (3) << fixed  << "|\t" << " data - mc " << "\t"
	<< "|\t" << setprecision (3) << fixed << data_m0[i] - mc_m0[i] << " +- " << sqrt( data_m0_err[i]*data_m0_err[i] + mc_m0_err[i]*mc_m0_err[i]) << "\t"
	<< "|\t" << setprecision (3) << fixed << data_sigma[i] - mc_sigma[i] << " +- " << sqrt( data_sigma_err[i]*data_sigma_err[i] + mc_sigma_err[i]*mc_sigma_err[i]) << "\t"
	<< "| | |"
//	<< "|\t" << setprecision (8) << fixed << data_alpha[i] - mc_alpha[i] << " +- " << sqrt( data_alpha_err[i]*data_alpha_err[i] + mc_alpha_err[i]*mc_alpha_err[i]) << "\t"
//	<< "|\t" << setprecision (8) << fixed << data_n[i] - mc_n[i] << " +- " << sqrt( data_n_err[i]*data_n_err[i] + mc_n_err[i]*mc_n_err[i]) << "\t|"
	<< endl;
	cout << setprecision (3) << fixed  << "|\t" << " data - mc (%)" << "\t"
	<< "|\t" << setprecision (3) << fixed << (data_m0[i] - mc_m0[i])*100.0 << " +- " << 100.0 * sqrt( data_m0_err[i]*data_m0_err[i] + mc_m0_err[i]*mc_m0_err[i]) << "\t"
	<< "|\t" << setprecision (3) << fixed << (data_sigma[i] - mc_sigma[i])*100.0 << " +- " << 100.0 * sqrt( data_sigma_err[i]*data_sigma_err[i] + mc_sigma_err[i]*mc_sigma_err[i]) << "\t"
	<< "| | |"
//	<< "|\t" << setprecision (5) << fixed << (data_alpha[i] - mc_alpha[i])*100.0 << " +- " << 100.0 * sqrt( data_alpha_err[i]*data_alpha_err[i] + mc_alpha_err[i]*mc_alpha_err[i]) << "\t"
//	<< "|\t" << setprecision (5) << fixed << (data_n[i] - mc_n[i])*100.0 << " +- " << 100.0 * sqrt( data_n_err[i]*data_n_err[i] + mc_n_err[i]*mc_n_err[i]) << "\t|"
	<< endl;
}
cout << endl << endl;
cout << endl << endl;


cout << endl << endl;
for(int i=0; i < mc_alpha.size(); i++)
{
	cout << "|\t *" << name_DATA[i] << "* \t|\t *f = (1/(1+s))* \t|\t *sigma* \t|\t *alpha* \t|\t *n* \t|" << endl;
//  cout << "|\t" << " data " << "\t"
//  << "|\t" << data_m0[i] << " +- " << data_m0_err[i] << "\t"
//  << "|\t" << data_sigma[i] << " +- " << data_sigma_err[i] << "\t"
//  << "|\t" << data_alpha[i] << " +- " << data_alpha_err[i] << "\t"
//  << "|\t" << data_n[i] << " +- " << data_n_err[i] << "\t|"
//	<< endl;
  cout << setprecision (3) << fixed  << "|\t" << " data " << "\t"
  << "|\t" << 1.0 * ((double)(1.0)/(double)(1.0 + data_m0[i])) << " +- " << 1.0 * ((double)(data_m0_err[i])/(double)(pow(1.0 + data_m0[i], 2))) << "\t"
  << "|\t" << 1.0 * data_sigma[i] << " +- " << 1.0 * data_sigma_err[i] << "\t"
  << "|\t\t"
  << "|\t\t|"
	<< endl;
  cout << setprecision (3) << fixed  << "|\t" << " data (%)" << "\t"
  << "|\t" << 100.0 * ((double)(1.0)/(double)(1.0 + data_m0[i])) << " +- " << 100.0 * ((double)(data_m0_err[i])/(double)(pow(1.0 + data_m0[i], 2))) << "\t"
  << "|\t" << 100.0 * data_sigma[i] << " +- " << 100.0 * data_sigma_err[i] << "\t"
  << "|\t\t"
  << "|\t\t|"
	<< endl;
//  cout << "|\t" << " mc " << "\t"
//  << "|\t" << mc_m0[i] << " +- " << mc_m0_err[i] << "\t"
//  << "|\t" << mc_sigma[i] << " +- " << mc_sigma_err[i] << "\t"
//  << "|\t" << mc_alpha[i] << " +- " << mc_alpha_err[i] << "\t"
//  << "|\t" << mc_n[i] << " +- " << mc_n_err[i] << "\t|"
//	<< endl;
  cout << setprecision (3) << fixed  << "|\t" << " mc " << "\t"
  << "|\t" << 1.0 * ((double)(1.0)/(double)(1.0 + mc_m0[i])) << " +- " << 1.0 * ((double)(mc_m0_err[i])/(double)(pow(1.0 + mc_m0[i], 2))) << "\t"
  << "|\t" << 1.0 * mc_sigma[i] << " +- " << 1.0 * mc_sigma_err[i] << "\t"
  << "|\t\t"
  << "|\t\t|"
	<< endl;
  cout << setprecision (3) << fixed  << "|\t" << " mc (%)" << "\t"
  << "|\t" << 100.0 * ((double)(1.0)/(double)(1.0 + mc_m0[i])) << " +- " << 100.0 * ((double)(mc_m0_err[i])/(double)(pow(1.0 + mc_m0[i], 2))) << "\t"
  << "|\t" << 100.0 * mc_sigma[i] << " +- " << 100.0 * mc_sigma_err[i] << "\t"
  << "|\t\t"
  << "|\t\t|"
	<< endl;
	cout << setprecision (3) << fixed  << "|\t" << " data - mc " << "\t"
	<< "|\t" << setprecision (3) << fixed << ((double)(1.0)/(double)(1.0 + data_m0[i])) - ((double)(1.0)/(double)(1.0 + mc_m0[i])) << " +- " << sqrt( ((double)(data_m0_err[i])/(double)(pow(1.0 + data_m0[i], 2)))*((double)(data_m0_err[i])/(double)(pow(1.0 + data_m0[i], 2))) + ((double)(mc_m0_err[i])/(double)(pow(1.0 + mc_m0[i], 2)))*((double)(mc_m0_err[i])/(double)(pow(1.0 + mc_m0[i], 2)))) << "\t"
	<< "|\t" << setprecision (3) << fixed << data_sigma[i] - mc_sigma[i] << " +- " << sqrt( data_sigma_err[i]*data_sigma_err[i] + mc_sigma_err[i]*mc_sigma_err[i]) << "\t"
	<< "| | |"
//	<< "|\t" << setprecision (8) << fixed << data_alpha[i] - mc_alpha[i] << " +- " << sqrt( data_alpha_err[i]*data_alpha_err[i] + mc_alpha_err[i]*mc_alpha_err[i]) << "\t"
//	<< "|\t" << setprecision (8) << fixed << data_n[i] - mc_n[i] << " +- " << sqrt( data_n_err[i]*data_n_err[i] + mc_n_err[i]*mc_n_err[i]) << "\t|"
	<< endl;
	cout << setprecision (3) << fixed  << "|\t" << " data - mc (%)" << "\t"
	<< "|\t" << setprecision (3) << fixed << (((double)(1.0)/(double)(1.0 + data_m0[i])) - ((double)(1.0)/(double)(1.0 + mc_m0[i])))*100.0 << " +- " << 100.0 * sqrt( ((double)(data_m0_err[i])/(double)(pow(1.0 + data_m0[i], 2)))*((double)(data_m0_err[i])/(double)(pow(1.0 + data_m0[i], 2))) + ((double)(mc_m0_err[i])/(double)(pow(1.0 + mc_m0[i], 2)))*((double)(mc_m0_err[i])/(double)(pow(1.0 + mc_m0[i], 2)))) << "\t"
	<< "|\t" << setprecision (3) << fixed << (data_sigma[i] - mc_sigma[i])*100.0 << " +- " << 100.0 * sqrt( data_sigma_err[i]*data_sigma_err[i] + mc_sigma_err[i]*mc_sigma_err[i]) << "\t"
	<< "| | |"
//	<< "|\t" << setprecision (5) << fixed << (data_alpha[i] - mc_alpha[i])*100.0 << " +- " << 100.0 * sqrt( data_alpha_err[i]*data_alpha_err[i] + mc_alpha_err[i]*mc_alpha_err[i]) << "\t"
//	<< "|\t" << setprecision (5) << fixed << (data_n[i] - mc_n[i])*100.0 << " +- " << 100.0 * sqrt( data_n_err[i]*data_n_err[i] + mc_n_err[i]*mc_n_err[i]) << "\t|"
	<< endl;
}
cout << endl << endl;
cout << endl << endl;

// LATEX TABLES
cout << "\\begin{tabular}{ccccc}" << endl;
cout << "DATA \t&\t $s$ \t&\t $\\sigma$ \t&\t $\\alpha$ \t&\t $n$ \t\\\\" << endl; 
cout << "\\hline" << endl;
for(int i=0; i < data_alpha.size(); i++)
{
	cout << "\t" << display_latex_DATA[i] << "\t"
	<< setprecision (3) << fixed  << "&\t$" << data_m0[i] << " \\pm " << data_m0_err[i] << "$\t"
	<< "&\t$" << data_sigma[i] << " \\pm " << data_sigma_err[i] << "$\t"
	<< "&\t$" << data_alpha[i] << " \\pm " << data_alpha_err[i] << "$\t"
	<< "&\t$" << data_n[i] << " \\pm " << data_n_err[i] << "$\t\\\\" << endl;
}
cout << "\\end{tabular}" << endl;
cout << "\\begin{tabular}{ccccc}" << endl;
cout << "MC \t&\t $s$ \t&\t $\\sigma$ \t&\t $\\alpha$ \t&\t $n$ \t\\\\" << endl; 
cout << "\\hline" << endl;

for(int i=0; i < mc_alpha.size(); i++)
{
	cout << "\t" << display_latex[i] << "\t"
	<< setprecision (3) << fixed  << "&\t$" << mc_m0[i] << " \\pm " << mc_m0_err[i] << "$\t"
	<< "&\t$" << mc_sigma[i] << " \\pm " << mc_sigma_err[i] << "$\t"
	<< "&\t$" << mc_alpha[i] << " \\pm " << mc_alpha_err[i] << "$\t"
	<< "&\t$" << mc_n[i] << " \\pm " << mc_n_err[i] << "$\t\\\\" << endl;
}
cout << "\\end{tabular}" << endl;
cout << endl << endl;


// same table but with percentage
cout << "\\begin{tabular}{ccccc}" << endl;
cout << "DATA \t&\t $s (\\%)$ \t&\t $\\sigma (\\%)$ \t&\t $\\alpha$ \t&\t $n$ \t\\\\" << endl; 
cout << "\\hline" << endl;
for(int i=0; i < data_alpha.size(); i++)
{
	cout << "\t" << display_latex_DATA[i] << "\t"
	<< setprecision (3) << fixed  << "&\t$" << 100.0 * data_m0[i] << " \\pm " << 100.0 * data_m0_err[i] << "$\t"
	<< "&\t$" << 100.0 * data_sigma[i] << " \\pm " << 100.0 * data_sigma_err[i] << "$\t"
	<< "&\t$" << data_alpha[i] << " \\pm " << data_alpha_err[i] << "$\t"
	<< "&\t$" << data_n[i] << " \\pm " << data_n_err[i] << "$\t\\\\" << endl;
}
cout << "\\end{tabular}" << endl;
cout << "\\begin{tabular}{ccccc}" << endl;
cout << "MC \t&\t $s$ \t&\t $\\sigma$ \t&\t $\\alpha$ \t&\t $n$ \t\\\\" << endl; 
cout << "\\hline" << endl;

for(int i=0; i < mc_alpha.size(); i++)
{
	cout << "\t" << display_latex[i] << "\t"
	<< setprecision (3) << fixed  << "&\t$" << 100.0 * mc_m0[i] << " \\pm " << 100.0 * mc_m0_err[i] << "$\t"
	<< "&\t$" << 100.0 * mc_sigma[i] << " \\pm " << 100.0 * mc_sigma_err[i] << "$\t"
	<< "&\t$" << mc_alpha[i] << " \\pm " << mc_alpha_err[i] << "$\t"
	<< "&\t$" << mc_n[i] << " \\pm " << mc_n_err[i] << "$\t\\\\" << endl;
}
cout << "\\end{tabular}" << endl;
cout << endl << endl;


// data - mc tables
for(int i=0; i < mc_alpha.size(); i++)
{
	cout << "\\begin{tabular}{ccc}" << endl;
	cout << display_latex_DATA[i] << "\t&\t $s$ \t&\t $\\sigma$ \\\\" << endl;
	cout << "\\hline" << endl;
  cout << "data " << "\t"
  << setprecision (3) << fixed  << "&\t$" << data_m0[i] << " \\pm " << data_m0_err[i] << "$\t"
  << "&\t$" << data_sigma[i] << " \\pm " << data_sigma_err[i] << "$\t\\\\"
//  << "&\t$" << data_alpha[i] << " \\pm " << data_alpha_err[i] << "$\t"
//  << "&\t$" << data_n[i] << " \\pm " << data_n_err[i] << "$\t\\\\"
	<< endl;
  cout << "data (\\%)" << "\t"
  << setprecision (3) << fixed  << "&\t$" << 100.0 * data_m0[i] << " \\pm " << 100.0 * data_m0_err[i] << "$\t"
  << "&\t$" << 100.0 * data_sigma[i] << " \\pm " << 100.0 * data_sigma_err[i] << "$\t\\\\"
//  << "&\t$" << data_alpha[i] << " \\pm " << data_alpha_err[i] << "$\t"
//  << "&\t$" << data_n[i] << " \\pm " << data_n_err[i] << "$\t\\\\"
	<< endl;
  cout << "mc " << "\t"
  << setprecision (3) << fixed  << "&\t$" << mc_m0[i] << " \\pm " << mc_m0_err[i] << "$\t"
  << "&\t$" << mc_sigma[i] << " \\pm " << mc_sigma_err[i] << "$\t\\\\"
//  << "&\t$" << mc_alpha[i] << " \\pm " << mc_alpha_err[i] << "$\t"
//  << "&\t$" << mc_n[i] << " \\pm " << mc_n_err[i] << "$\t\\\\"
	<< endl;
  cout << "mc (\\%)" << "\t"
  << setprecision (3) << fixed  << "&\t$" << 100.0 * mc_m0[i] << " \\pm " << 100.0 * mc_m0_err[i] << "$\t"
  << "&\t$" << 100.0 * mc_sigma[i] << " \\pm " << 100.0 * mc_sigma_err[i] << "$\t\\\\"
//  << "&\t$" << mc_alpha[i] << " \\pm " << mc_alpha_err[i] << "$\t"
//  << "&\t$" << mc_n[i] << " \\pm " << mc_n_err[i] << "$\t\\\\"
	<< endl;
	cout << " data - mc " << "\t"
	<< "&\t$" << setprecision (3) << fixed << data_m0[i] - mc_m0[i] << " \\pm " << sqrt( data_m0_err[i]*data_m0_err[i] + mc_m0_err[i]*mc_m0_err[i]) << "$\t"
	<< "&\t$" << setprecision (3) << fixed << data_sigma[i] - mc_sigma[i] << " \\pm " << sqrt( data_sigma_err[i]*data_sigma_err[i] + mc_sigma_err[i]*mc_sigma_err[i]) << "$\t"
	<< " \\\\"
//	<< "&\t" << setprecision (8) << fixed << data_alpha[i] - mc_alpha[i] << " \\pm " << sqrt( data_alpha_err[i]*data_alpha_err[i] + mc_alpha_err[i]*mc_alpha_err[i]) << "\t"
//	<< "&\t" << setprecision (8) << fixed << data_n[i] - mc_n[i] << " \\pm " << sqrt( data_n_err[i]*data_n_err[i] + mc_n_err[i]*mc_n_err[i]) << "\t&"
	<< endl;
	cout << " data - mc (\\%)" << "\t"
	<< "&\t$" << setprecision (3) << fixed << (data_m0[i] - mc_m0[i])*100.0 << " \\pm " << 100.0 * sqrt( data_m0_err[i]*data_m0_err[i] + mc_m0_err[i]*mc_m0_err[i]) << "$\t"
	<< "&\t$" << setprecision (3) << fixed << (data_sigma[i] - mc_sigma[i])*100.0 << " \\pm " << 100.0 * sqrt( data_sigma_err[i]*data_sigma_err[i] + mc_sigma_err[i]*mc_sigma_err[i]) << "$\t"
	<< " \\\\"
//	<< "&\t" << setprecision (5) << fixed << (data_alpha[i] - mc_alpha[i])*100.0 << " \\pm " << 100.0 * sqrt( data_alpha_err[i]*data_alpha_err[i] + mc_alpha_err[i]*mc_alpha_err[i]) << "\t"
//	<< "&\t" << setprecision (5) << fixed << (data_n[i] - mc_n[i])*100.0 << " \\pm " << 100.0 * sqrt( data_n_err[i]*data_n_err[i] + mc_n_err[i]*mc_n_err[i]) << "\t&"
	<< endl;
	cout << "\\end{tabular}" << endl;
}

// precentage table with f
for(int i=0; i < mc_alpha.size(); i++)
{
	cout << "\\begin{tabular}{ccc}" << endl;
	cout << display_latex_DATA[i] << "\t&\t $f$ \t&\t $\\sigma$ \\\\" << endl;
	cout << "\\hline" << endl;
  cout << "data " << "\t"
  << setprecision (3) << fixed << "&\t$" << ((double)(1.0)/(double)(1.0 + data_m0[i])) << " \\pm " << ((double)(data_m0_err[i])/(double)(pow(1.0 + data_m0[i], 2))) << "$\t"
  << "&\t$" << data_sigma[i] << " \\pm " << data_sigma_err[i] << "$\t\\\\"
//  << "&\t$" << data_alpha[i] << " \\pm " << data_alpha_err[i] << "$\t"
//  << "&\t$" << data_n[i] << " \\pm " << data_n_err[i] << "$\t\\\\"
	<< endl;
  cout << "data (\\%)" << "\t"
  << setprecision (3) << fixed << "&\t$" << 100.0 * ((double)(1.0)/(double)(1.0 + data_m0[i])) << " \\pm " << 100.0 * ((double)(data_m0_err[i])/(double)(pow(1.0 + data_m0[i], 2))) << "$\t"
  << "&\t$" << 100.0 * data_sigma[i] << " \\pm " << 100.0 * data_sigma_err[i] << "$\t\\\\"
//  << "&\t$" << data_alpha[i] << " \\pm " << data_alpha_err[i] << "$\t"
//  << "&\t$" << data_n[i] << " \\pm " << data_n_err[i] << "$\t\\\\"
	<< endl;
  cout << "mc " << "\t"
  << setprecision (3) << fixed << "&\t$" << ((double)(1.0)/(double)(1.0 + mc_m0[i])) << " \\pm " << ((double)(mc_m0_err[i])/(double)(pow(1.0 + mc_m0[i], 2))) << "$\t"
  << "&\t$" << mc_sigma[i] << " \\pm " << mc_sigma_err[i] << "$\t\\\\"
//  << "&\t$" << mc_alpha[i] << " \\pm " << mc_alpha_err[i] << "$\t"
//  << "&\t$" << mc_n[i] << " \\pm " << mc_n_err[i] << "$\t\\\\"
	<< endl;
  cout << "mc (\\%)" << "\t"
  << setprecision (3) << fixed << "&\t$" << 100.0 * ((double)(1.0)/(double)(1.0 + mc_m0[i])) << " \\pm " << 100.0 * ((double)(mc_m0_err[i])/(double)(pow(1.0 + mc_m0[i], 2))) << "$\t"
  << "&\t$" << 100.0 * mc_sigma[i] << " \\pm " << 100.0 * mc_sigma_err[i] << "$\t\\\\"
//  << "&\t$" << mc_alpha[i] << " \\pm " << mc_alpha_err[i] << "$\t"
//  << "&\t$" << mc_n[i] << " \\pm " << mc_n_err[i] << "$\t\\\\"
	<< endl;
	cout << " data - mc " << "\t"
	<< "&\t$" << setprecision (3) << fixed << ((double)(1.0)/(double)(1.0 + data_m0[i])) - ((double)(1.0)/(double)(1.0 + mc_m0[i])) << " \\pm " << sqrt( ((double)(data_m0_err[i])/(double)(pow(1.0 + data_m0[i], 2)))*((double)(data_m0_err[i])/(double)(pow(1.0 + data_m0[i], 2))) + ((double)(mc_m0_err[i])/(double)(pow(1.0 + mc_m0[i], 2)))*((double)(mc_m0_err[i])/(double)(pow(1.0 + mc_m0[i], 2)))) << "$\t"
	<< "&\t$" << setprecision (3) << fixed << data_sigma[i] - mc_sigma[i] << " \\pm " << sqrt( data_sigma_err[i]*data_sigma_err[i] + mc_sigma_err[i]*mc_sigma_err[i]) << "$\t"
	<< " \\\\"
//	<< "&\t" << setprecision (8) << fixed << data_alpha[i] - mc_alpha[i] << " \\pm " << sqrt( data_alpha_err[i]*data_alpha_err[i] + mc_alpha_err[i]*mc_alpha_err[i]) << "\t"
//	<< "&\t" << setprecision (8) << fixed << data_n[i] - mc_n[i] << " \\pm " << sqrt( data_n_err[i]*data_n_err[i] + mc_n_err[i]*mc_n_err[i]) << "\t&"
	<< endl;
	cout << " data - mc (\\%)" << "\t"
	<< "&\t$" << setprecision (3) << fixed << (((double)(1.0)/(double)(1.0 + data_m0[i])) - ((double)(1.0)/(double)(1.0 + mc_m0[i])))*100.0 << " \\pm " << 100.0 * sqrt( ((double)(data_m0_err[i])/(double)(pow(1.0 + data_m0[i], 2)))*((double)(data_m0_err[i])/(double)(pow(1.0 + data_m0[i], 2))) + ((double)(mc_m0_err[i])/(double)(pow(1.0 + mc_m0[i], 2)))*((double)(mc_m0_err[i])/(double)(pow(1.0 + mc_m0[i], 2)))) << "$\t"
	<< "&\t$" << setprecision (3) << fixed << (data_sigma[i] - mc_sigma[i])*100.0 << " \\pm " << 100.0 * sqrt( data_sigma_err[i]*data_sigma_err[i] + mc_sigma_err[i]*mc_sigma_err[i]) << "$\t"
	<< " \\\\"
//	<< "&\t" << setprecision (5) << fixed << (data_alpha[i] - mc_alpha[i])*100.0 << " \\pm " << 100.0 * sqrt( data_alpha_err[i]*data_alpha_err[i] + mc_alpha_err[i]*mc_alpha_err[i]) << "\t"
//	<< "&\t" << setprecision (5) << fixed << (data_n[i] - mc_n[i])*100.0 << " \\pm " << 100.0 * sqrt( data_n_err[i]*data_n_err[i] + mc_n_err[i]*mc_n_err[i]) << "\t&"
	<< endl;
	cout << "\\end{tabular}" << endl;
}


return;
}
