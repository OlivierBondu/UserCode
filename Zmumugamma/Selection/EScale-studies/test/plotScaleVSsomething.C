
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
#include <THStack.h>
#include <TLegendEntry.h>
#include <TMinuit.h>
#include <TPaveStats.h>
#include <TGraphErrors.h>

gROOT->Reset();

#include "CMSStyle.C"

#pragma optimize 0
using namespace std;

int plotScaleVSsomething()
//int main()
{
gROOT->ProcessLine(".x setTDRStyle.C");
CMSstyle();

gStyle->SetOptFit(0);
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);

TCanvas *c1 = new TCanvas("c1", "c1");
TCanvas *c2 = new TCanvas("c2", "c2");
bool dorun = true;
bool dopt = true;


		
for(int iestimator=0 ; iestimator < 2 ; iestimator++)
{
	string string_estimator = iestimator==0 ? "s" : "f";
	for(int idata=0 ; idata < 2 ; idata++)
	{
		string string_data = idata==0 ? "DATA" : "MC";
		TTree *tree = new TTree();
		tree->ReadFile(idata==0 ? "VGamma_875pb-1_v2_f_DATA.out" : "VGamma_875pb-1_v2_f_MC.out", "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
//		tree->ReadFile(idata==0 ? "info_data.raw" : "vgamma_f_MC.out", "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
//		tree->ReadFile("vgamma_f_MC.out", "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
		for(int iEBEE=0 ; iEBEE < 2 ; iEBEE++)
		{
			for(int iR9=0 ; iR9 < 3 ; iR9++)
			{
				if( dopt )
				{
		
				c1->cd();
				const Long64_t N = tree->Draw("PT:F:DELTAF", Form("EBEE == %i && R9 == %i && RUN == 5", iEBEE, iR9));
				c2->cd();
				TGraphErrors *gr = new TGraphErrors(N, tree->GetV1(), tree->GetV2(), 0, tree->GetV3());
				gr->Draw("AP");
				double xmin = gr->GetXaxis()->GetXmin() - (gr->GetXaxis()->GetXmax() - 6.0);
				gr->GetXaxis()->SetLimits(xmin, gr->GetXaxis()->GetXmax());
				gr->GetXaxis()->SetTitle("p_{T}");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(0.0), "[10 ; 12]");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(1.0), "[12 ; 15]");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(2.0), "[15 ; 20]");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(3.0), "[20 ; 25]");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(4.0), "[25 ; 30]");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(5.0), "[30 ; inf[");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(6.0), "[10 ; inf[");
				gr->SetMaximum(1.075);
				gr->SetMinimum(0.925);
				gr->GetXaxis()->LabelsOption("h");
				gr->GetYaxis()->SetTitle( string_estimator.c_str() );
				TLatex latexLabel;
			  latexLabel.SetNDC();
			  latexLabel.SetTextSize(0.04);
			  latexLabel.DrawLatex(0.13, 0.96, "CMS Preliminary 2011");
			  latexLabel.DrawLatex(0.42, 0.96, "#sqrt{s} = 7 TeV");
			  latexLabel.DrawLatex(0.57, 0.96, string_data.c_str() );
			  latexLabel.SetTextSize(0.05);
				double position = 0.92;
				position -= 0.04;
				latexLabel.DrawLatex(0.65, position, iEBEE==0 ? "EB" : "EE");
				position -= 0.04;
				if( iR9 == 2) latexLabel.DrawLatex(0.65, position, "no R9 category");
				else latexLabel.DrawLatex(0.65, position, iR9==0 ? "low R9" : "high R9");
				position -= 0.04;
				latexLabel.DrawLatex(0.65, position, "all runs");
				c2->Update();
				string string_EBEE = "";
				string string_R9 = "";
				string string_pt = "";
				string string_run = "";
				string string_VS = "";
				if( iEBEE==0 ) string_EBEE = "EB";
				else string_EBEE = "EE";
				if( iR9==2 ) string_R9 = "inclusiveR9";
				else string_R9 = iR9==0 ? "lowR9" : "highR9";
				string_pt = "";
				string_run = "inclusiveRun";
				string_VS = "pt";
				c2->Update();
				c2->Print(Form("eps/mmg_%s_%s_%s_%s_%s_%s_VS_%s.eps", string_estimator.c_str(), string_data.c_str(), string_EBEE.c_str(), string_R9.c_str(), string_pt.c_str(), string_run.c_str(), string_VS.c_str()));
				c2->Print(Form("gif/mmg_%s_%s_%s_%s_%s_%s_VS_%s.gif", string_estimator.c_str(), string_data.c_str(), string_EBEE.c_str(), string_R9.c_str(), string_pt.c_str(), string_run.c_str(), string_VS.c_str()));
				c2->Print(Form("png/mmg_%s_%s_%s_%s_%s_%s_VS_%s.png", string_estimator.c_str(), string_data.c_str(), string_EBEE.c_str(), string_R9.c_str(), string_pt.c_str(), string_run.c_str(), string_VS.c_str()));
				c2->Print(Form("C/mmg_%s_%s_%s_%s_%s_%s_VS_%s.C", string_estimator.c_str(), string_data.c_str(), string_EBEE.c_str(), string_R9.c_str(), string_pt.c_str(), string_run.c_str(), string_VS.c_str()));
				system(Form("convert eps/mmg_%s_%s_%s_%s_%s_%s_VS_%s.eps pdf/mmg_%s_%s_%s_%s_%s_%s_VS_%s.pdf", string_estimator.c_str(), string_data.c_str(), string_EBEE.c_str(), string_R9.c_str(), string_pt.c_str(), string_run.c_str(), string_VS.c_str(), string_estimator.c_str(), string_data.c_str(), string_EBEE.c_str(), string_R9.c_str(), string_pt.c_str(), string_run.c_str(), string_VS.c_str()));
		
				}
				if( dorun )
				{
				c1->cd();
				const Long64_t N = tree->Draw("RUN:F:DELTAF", Form("EBEE == %i && R9 == %i && PT == 6", iEBEE, iR9));
				c2->cd();
				TGraphErrors *gr = new TGraphErrors(N, tree->GetV1(), tree->GetV2(), 0, tree->GetV3());
				gr->Draw("AP");
				double xmin = gr->GetXaxis()->GetXmin() - (gr->GetXaxis()->GetXmax() - 5.0);
				gr->GetXaxis()->SetLimits(xmin, gr->GetXaxis()->GetXmax());
				gr->GetXaxis()->SetTitle("run");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(0.0), "160431-163869");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(1.0), "165071-165970");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(2.0), "165971-166502");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(3.0), "166503-166861");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(4.0), "166862-166967");
				gr->GetXaxis()->SetBinLabel(gr->GetXaxis()->FindBin(5.0), "all");
				gr->SetMaximum(1.075);
				gr->SetMinimum(0.925);
				gr->GetXaxis()->LabelsOption("v");
				gr->GetYaxis()->SetTitle( string_estimator.c_str() );
				TLatex latexLabel;
			  latexLabel.SetNDC();
			  latexLabel.SetTextSize(0.04);
				c2->cd();
			  latexLabel.DrawLatex(0.13, 0.96, "CMS Preliminary 2011");
			  latexLabel.DrawLatex(0.42, 0.96, "#sqrt{s} = 7 TeV");
			  latexLabel.DrawLatex(0.57, 0.96, string_data.c_str() );
			  latexLabel.SetTextSize(0.05);
				double position = 0.92;
				position -= 0.04;
				latexLabel.DrawLatex(0.65, position, iEBEE==0 ? "EB" : "EE");
				position -= 0.04;
				if( iR9 == 2) latexLabel.DrawLatex(0.65, position, "no R9 category");
				else latexLabel.DrawLatex(0.65, position, iR9==0 ? "low R9" : "high R9");
				position -= 0.04;
				latexLabel.DrawLatex(0.65, position, "all p_{T}");
				c2->Update();
				string string_EBEE = "";
				string string_R9 = "";
				string string_pt = "";
				string string_run = "";
				string string_VS = "";
				if( iEBEE==0 ) string_EBEE = "EB";
				else string_EBEE = "EE";
				if( iR9==2 ) string_R9 = "inclusiveR9";
				else string_R9 = iR9==0 ? "lowR9" : "highR9";
				string_pt = "inclusivePt";
				string_run = "";
				string_VS = "run";
				c2->Update();
								c2->Print(Form("eps/mmg_%s_%s_%s_%s_%s_%s_VS_%s.eps", string_estimator.c_str(), string_data.c_str(), string_EBEE.c_str(), string_R9.c_str(), string_pt.c_str(), string_run.c_str(), string_VS.c_str()));
				c2->Print(Form("gif/mmg_%s_%s_%s_%s_%s_%s_VS_%s.gif", string_estimator.c_str(), string_data.c_str(), string_EBEE.c_str(), string_R9.c_str(), string_pt.c_str(), string_run.c_str(), string_VS.c_str()));
				c2->Print(Form("png/mmg_%s_%s_%s_%s_%s_%s_VS_%s.png", string_estimator.c_str(), string_data.c_str(), string_EBEE.c_str(), string_R9.c_str(), string_pt.c_str(), string_run.c_str(), string_VS.c_str()));
				c2->Print(Form("C/mmg_%s_%s_%s_%s_%s_%s_VS_%s.C", string_estimator.c_str(), string_data.c_str(), string_EBEE.c_str(), string_R9.c_str(), string_pt.c_str(), string_run.c_str(), string_VS.c_str()));
				system(Form("convert eps/mmg_%s_%s_%s_%s_%s_%s_VS_%s.eps pdf/mmg_%s_%s_%s_%s_%s_%s_VS_%s.pdf", string_estimator.c_str(), string_data.c_str(), string_EBEE.c_str(), string_R9.c_str(), string_pt.c_str(), string_run.c_str(), string_VS.c_str(), string_estimator.c_str(), string_data.c_str(), string_EBEE.c_str(), string_R9.c_str(), string_pt.c_str(), string_run.c_str(), string_VS.c_str()));
		//		return 1;
				}
			}
		}
	}
}


return 0;
}
