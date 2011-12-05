// ROOT HEADERS
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
#include <TBranch.h>
#include <TString.h>
#include <TBits.h>
#include <TMath.h>
#include "TROOT.h"
#include <TLatex.h>
#include "TProof.h"

// C++ HEADERS
#include <string.h>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

// DISPLAY HEADERS
#include "CMSStyle.C"

#pragma optimize 0

using namespace std;


//int plot2D()
int main()
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
	vector<string> y_variable;
	vector<string> y_title;
	vector<int> x_nbins;
//	typedef vector<double> vd;
	vector< vector<double> > x_bins;
//	vector<double*> x_bins;
//	vector<double[]> x_bins;
//return 3;
/*
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
*/
	x_variable.push_back("Photon_Et");
	x_title.push_back("E_{T}^{#gamma}");
	x_nbins.push_back(6);
	double t[] = {10., 12., 15., 20., 25., 30., 100.};
	vector<double> vt(t+0, t+7);
	x_bins.push_back(vt);
//	double t[] = {10., 12., 15., 20., 25., 30, 200.};
//	x_bins.push_back(t);
//);
	y_variable.push_back("mmg_s * 100");
  y_title.push_back("s (%)");
	
/*
	x_variable.push_back("Photon_Eta");
	x_title.push_back("#eta^{#gamma}");
	y_variable.push_back("mmg_s * 100");
  y_title.push_back("s (%)");
	x_variable.push_back("Photon_Phi");
	x_title.push_back("#phi^{#gamma}");
	y_variable.push_back("mmg_s * 100");
  y_title.push_back("s (%)");
*/

cout << "x_nbins[0]= " << x_nbins[0] << endl;
for( int isize= 0 ; isize <= x_nbins[0] ; isize++ ){
	cout << "x_bins[0][" << isize << "]= " << x_bins[0][isize] << endl;
}
//double a[] = x_bins[0].toArray();
//return 1;



	vector<string> cat_cut;
	vector<string> cat_title;

	cat_cut.push_back("1");
	cat_title.push_back("tight");
/*
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
*/
	string tight_cut = "isTightMMG && isMultipleCandidate == 0";

//	for(int idata = 0 ; idata < 2 ; idata++)
	for(int idata = 1 ; idata < 2 ; idata++)
	{
		TChain *data = new TChain("miniTree");
//		data->Add( idata == 0 ? "miniTree_v16_DATA_875pb-1.root" : "miniTree_v16_DYToMuMu.root");
//		data->Add( idata == 0 ? "miniTree_v17_Run2011A-ZMu-Jul05-Aug05-PromptSkim-v6.root" : "miniTree_v17_DYToMuMu.root");
			data->Add( idata == 0 ? "miniTree_v12_2011_40_80_partALL.root" : "miniTree_v10_DYToMuMu_S6_2011_40_80_partALL.root");
		for(int icat = 0 ; icat < cat_cut.size() ; icat++)
		{
			for(int ivar = 0 ; ivar < x_variable.size() ; ivar++)
			{
				TH2F* hist = new TH2F("hist", "hist", x_nbins[ivar], &x_bins[ivar][0], 500, -.5, .5);
//				hist->SetBins(x_nbins[ivar], &x_bins[ivar][0]);
//				data->Draw(Form("mmg_s:%s", x_variable[ivar].c_str()), Form("(%s && %s )* weight_pileUp", tight_cut.c_str(), cat_cut[icat].c_str()), "COLZ");
				data->Draw(Form("(%s):(%s)>>hist", y_variable[ivar].c_str(), x_variable[ivar].c_str()), Form("(%s && %s )* weight_pileUp", tight_cut.c_str(), cat_cut[icat].c_str()), "goff");
//				data->Draw(Form("(%s):(%s)>>hist", y_variable[ivar].c_str(), x_variable[ivar].c_str()), Form("(%s && %s )* weight_pileUp", tight_cut.c_str(), cat_cut[icat].c_str()), "COLZ");
				//hist = (TH2F*)(gROOT->FindObject("htemp"));
//				double *arr = &x_bins[0];
//				std::copy(x_bins[ivar].begin(), x_bins[ivar].end(), arr);
//cout << "oups" << endl;
//				hist->SetBit(TH1::kCanRebin);
//				hist->SetBins(x_nbins[ivar], arr);
//				hist->SetBins(x_nbins[ivar], &x_bins[ivar][0]);
//				hist->ProfileX()->Draw();
//				TProfile* hist_pfx = (TProfile*)(gROOT->FindObject("hist_pfx"));
				TProfile* hist_pfx = (TProfile*)(hist->ProfileX());
				hist_pfx->SetMarkerStyle(25);
				hist_pfx->SetMarkerSize(1);
				hist_pfx->Draw();
				hist_pfx->GetYaxis()->SetTitle(y_title[ivar].c_str());
				hist_pfx->GetXaxis()->SetTitle(x_title[ivar].c_str());
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
	
				hist->Clear();
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
