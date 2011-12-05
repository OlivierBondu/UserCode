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
#include <iostream>
#include <iomanip>
#include <sstream>
#include <TLatex.h>
#include "TProof.h"
#include "CMSStyle.C"

using namespace std;

int plot2D()
{
//	gROOT->ProcessLine(".x setTDRStyle.C");
	CMSstyle();
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	gStyle->SetMarkerSize(0.1);
	gStyle->SetPalette(1);

//  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPadBottomMargin(0.17);
  gStyle->SetPadLeftMargin(0.17);



	TCanvas *c1 = new TCanvas("c1", "c1");

	vector<string> x_variable;
	vector<string> x_title;

	x_variable.push_back("MuonM_Phi");
	x_title.push_back("#phi^{#mu^{-}}");
	x_variable.push_back("MuonM_Eta");
	x_title.push_back("#eta^{#mu^{-}}");
	x_variable.push_back("MuonM_Pt");
	x_title.push_back("E_{T}^{#mu^{-}}");

	x_variable.push_back("MuonP_Phi");
	x_title.push_back("#phi^{#mu^{+}}");
	x_variable.push_back("MuonP_Eta");
	x_title.push_back("#eta^{#mu^{+}}");
	x_variable.push_back("MuonP_Pt");
	x_title.push_back("E_{T}^{#mu^{+}}");

	x_variable.push_back("MuonF_Phi");
	x_title.push_back("#phi^{#mu^{far}}");
	x_variable.push_back("MuonF_Eta");
	x_title.push_back("#eta^{#mu^{far}}");
	x_variable.push_back("MuonF_Pt");
	x_title.push_back("E_{T}^{#mu^{far}}");

	x_variable.push_back("MuonN_Phi");
	x_title.push_back("#phi^{#mu^{near}}");
	x_variable.push_back("MuonN_Eta");
	x_title.push_back("#eta^{#mu^{near}}");
	x_variable.push_back("MuonN_Pt");
	x_title.push_back("E_{T}^{#mu^{near}}");

	x_variable.push_back("MuonL_Phi");
	x_title.push_back("#phi^{#mu^{lead}}");
	x_variable.push_back("MuonL_Eta");
	x_title.push_back("#eta^{#mu^{lead}}");
	x_variable.push_back("MuonL_Pt");
	x_title.push_back("E_{T}^{#mu^{lead}}");

	x_variable.push_back("MuonS_Phi");
	x_title.push_back("#phi^{#mu^{trail}}");
	x_variable.push_back("MuonS_Eta");
	x_title.push_back("#eta^{#mu^{trail}}");
	x_variable.push_back("MuonS_Pt");
	x_title.push_back("E_{T}^{#mu^{trail}}");

	x_variable.push_back("Photon_Et");
	x_title.push_back("E_{T}^{#gamma}");
	x_variable.push_back("Photon_Eta");
	x_title.push_back("#eta^{#gamma}");
	x_variable.push_back("Photon_Phi");
	x_title.push_back("#phi^{#gamma}");

	



	vector<string> cat_cut;
	vector<string> cat_title;

	cat_cut.push_back("Photon_isEB");
	cat_title.push_back("EB-tight");
	cat_cut.push_back("Photon_isEB && Photon_r9 > .94");
	cat_title.push_back("EB-tight-highR9");
	cat_cut.push_back("Photon_isEB && Photon_r9 < .94");
	cat_title.push_back("EB-tight-lowR9");
	cat_cut.push_back("Photon_isEE");
	cat_title.push_back("EE-tight");
	cat_cut.push_back("Photon_isEE && Photon_r9 > .95");
	cat_title.push_back("EE-tight-highR9");
	cat_cut.push_back("Photon_isEE && Photon_r9 < .95");
	cat_title.push_back("EE-tight-lowR9");

	string tight_cut = "isTightMMG && isMultipleCandidate == 0";

	for(int idata = 0 ; idata < 2 ; idata++)
//	for(int idata = 1 ; idata < 2 ; idata++)
	{
		TChain *data = new TChain("miniTree");
//		data->Add( idata == 0 ? "miniTree_v16_DATA_875pb-1.root" : "miniTree_v16_DYToMuMu.root");
		data->Add( idata == 0 ? "miniTree_v17_Run2011A-ZMu-Jul05-Aug05-PromptSkim-v6.root" : "miniTree_v17_DYToMuMu.root");
		for(int icat = 0 ; icat < cat_cut.size() ; icat++)
		{
			for(int ivar = 0 ; ivar < x_variable.size() ; ivar++)
			{
				data->Draw(Form("mmg_s:%s", x_variable[ivar].c_str()), Form("(%s && %s )* weight_pileUp", tight_cut.c_str(), cat_cut[icat].c_str()), "COLZ");
				TH2F* hist = (TH2F*)(gROOT->FindObject("htemp"));
				hist->GetYaxis()->SetTitle("s");
				hist->GetXaxis()->SetTitle(x_title[ivar].c_str());
//				c1->Clear();
//				TProfile *profile = (TProfile*) hist->ProfileX();
//				profile->Draw();

				TLatex latexLabel;
			  latexLabel.SetNDC();
			  latexLabel.SetTextSize(0.04);
			  latexLabel.DrawLatex(0.13, 0.96, "CMS Preliminary 2011");
			  latexLabel.DrawLatex(0.40, 0.96, "#sqrt{s} = 7 TeV");
				latexLabel.SetTextSize(0.05);
			  latexLabel.DrawLatex(0.55, 0.96, idata == 0 ? "DATA" : "Simulation");
			  latexLabel.SetTextSize(0.04);
				latexLabel.DrawLatex(0.75, 0.96, cat_title[icat].c_str());
		
				c1->Print(Form("eps/%s_mmg_s_VS_%s_%s.eps", idata == 0 ? "DATA" : "MC", x_variable[ivar].c_str(), cat_title[icat].c_str()));
				c1->Print(Form("gif/%s_mmg_s_VS_%s_%s.gif", idata == 0 ? "DATA" : "MC", x_variable[ivar].c_str(), cat_title[icat].c_str()));
				c1->Print(Form("png/%s_mmg_s_VS_%s_%s.png", idata == 0 ? "DATA" : "MC", x_variable[ivar].c_str(), cat_title[icat].c_str()));
				c1->Print(Form("C/%s_mmg_s_VS_%s_%s.C", idata == 0 ? "DATA" : "MC", x_variable[ivar].c_str(), cat_title[icat].c_str()));
				system(Form("convert eps/%s_mmg_s_VS_%s_%s.eps pdf/%s_mmg_s_VS_%s_%s.pdf", idata == 0 ? "DATA" : "MC", x_variable[ivar].c_str(), cat_title[icat].c_str(), idata == 0 ? "DATA" : "MC", x_variable[ivar].c_str(), cat_title[icat].c_str()));

				c1->Clear();
//return 1;
			} // END OF LOOP OVER VARIABLES
		}	// END OF LOOP OVER CATEGORIES
	}	// END OF LOOP OVER DATA/MC

/*
	cat_cut.push_back("");
	cat_title.push_back("");
	cat_cut.push_back("");
	cat_title.push_back("");
*/
return 0;
}
