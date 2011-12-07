
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

int plotScaleVSsomething_Mmumu()
//int main()
{
gROOT->ProcessLine(".x setTDRStyle.C");
CMSstyle();

gStyle->SetOptFit(0);
gStyle->SetOptTitle(0);
gStyle->SetOptStat(0);

TCanvas *c1 = new TCanvas("c1", "c1");
TCanvas *c2 = new TCanvas("c2", "c2");
bool dorun = false;
bool dopt = true;
bool dotruth = true;
string infile = "reco_cb_S6_2011";

		
for(int iestimator=0 ; iestimator < 1 ; iestimator++)
{
	string string_estimator = iestimator==0 ? "s" : "f";
	for(int idata=1 ; idata < 2 ; idata++)
	{
		string string_data = idata==0 ? "DATA" : "MC";
		TTree *tree_0 = new TTree();
		TTree *tree_1 = new TTree();
		TTree *tree_2 = new TTree();
		TTree *tree_3 = new TTree();
		TTree *tree_4 = new TTree();
		TTree *tree_5 = new TTree();
		TTree *tree_6 = new TTree();
		TTree *tree_7 = new TTree();
		TTree *tree_8 = new TTree();
		TTree *tree_9 = new TTree();
		tree_0->ReadFile(idata==0 ? Form("%s_38_82_Range90_%s_DATA.out", infile.c_str(), string_estimator.c_str()) : Form("%s_38_82_Range90_%s_MC.out", infile.c_str(), string_estimator.c_str()), "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
		tree_1->ReadFile(idata==0 ? Form("%s_36_84_Range90_%s_DATA.out", infile.c_str(), string_estimator.c_str()) : Form("%s_36_84_Range90_%s_MC.out", infile.c_str(), string_estimator.c_str()), "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
		tree_2->ReadFile(idata==0 ? Form("%s_38_84_Range90_%s_DATA.out", infile.c_str(), string_estimator.c_str()) : Form("%s_38_84_Range90_%s_MC.out", infile.c_str(), string_estimator.c_str()), "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
		tree_3->ReadFile(idata==0 ? Form("%s_38_86_Range90_%s_DATA.out", infile.c_str(), string_estimator.c_str()) : Form("%s_38_86_Range90_%s_MC.out", infile.c_str(), string_estimator.c_str()), "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
		tree_4->ReadFile(idata==0 ? Form("%s_38_88_Range90_%s_DATA.out", infile.c_str(), string_estimator.c_str()) : Form("%s_38_88_Range90_%s_MC.out", infile.c_str(), string_estimator.c_str()), "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
		tree_5->ReadFile(idata==0 ? Form("%s_38_78_Range90_%s_DATA.out", infile.c_str(), string_estimator.c_str()) : Form("%s_38_78_Range90_%s_MC.out", infile.c_str(), string_estimator.c_str()), "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
		tree_6->ReadFile(idata==0 ? Form("%s_40_80_Range90_%s_DATA.out", infile.c_str(), string_estimator.c_str()) : Form("%s_40_80_Range90_%s_MC.out", infile.c_str(), string_estimator.c_str()), "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
		tree_7->ReadFile(idata==0 ? Form("%s_42_82_Range90_%s_DATA.out", infile.c_str(), string_estimator.c_str()) : Form("%s_42_82_Range90_%s_MC.out", infile.c_str(), string_estimator.c_str()), "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
		tree_8->ReadFile(idata==0 ? Form("%s_36_76_Range90_%s_DATA.out", infile.c_str(), string_estimator.c_str()) : Form("%s_36_76_Range90_%s_MC.out", infile.c_str(), string_estimator.c_str()), "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
		tree_9->ReadFile(idata==0 ? Form("%s_44_84_Range90_%s_DATA.out", infile.c_str(), string_estimator.c_str()) : Form("%s_44_84_Range90_%s_MC.out", infile.c_str(), string_estimator.c_str()), "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
//		tree->ReadFile(idata==0 ? "info_data.raw" : "vgamma_f_v2_MC.out", "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
//		tree->ReadFile("vgamma_f_MC.out", "EBEE/I:R9/I:PT/I:RUN/I:F/F:DELTAF/F");
		for(int iEBEE=0 ; iEBEE < 2 ; iEBEE++)
		{
			//for(int iR9=0 ; iR9 < 3 ; iR9++)
			for(int iR9=0 ; iR9 < 2 ; iR9++)
			{
				if( dopt )
				{
				c1->Clear();
				c2->Clear();
				c1->cd();
				const Long64_t N_0 = tree_0->Draw("PT:F:DELTAF", Form("EBEE == %i && R9 == %i && RUN == 5", iEBEE, iR9));
				const Long64_t N_1 = tree_1->Draw("PT:F:DELTAF", Form("EBEE == %i && R9 == %i && RUN == 5", iEBEE, iR9));
				const Long64_t N_2 = tree_2->Draw("PT:F:DELTAF", Form("EBEE == %i && R9 == %i && RUN == 5", iEBEE, iR9));
				const Long64_t N_3 = tree_3->Draw("PT:F:DELTAF", Form("EBEE == %i && R9 == %i && RUN == 5", iEBEE, iR9));
				const Long64_t N_4 = tree_4->Draw("PT:F:DELTAF", Form("EBEE == %i && R9 == %i && RUN == 5", iEBEE, iR9));
				const Long64_t N_5 = tree_5->Draw("PT:F:DELTAF", Form("EBEE == %i && R9 == %i && RUN == 5", iEBEE, iR9));
				const Long64_t N_6 = tree_6->Draw("PT:F:DELTAF", Form("EBEE == %i && R9 == %i && RUN == 5", iEBEE, iR9));
				const Long64_t N_7 = tree_7->Draw("PT:F:DELTAF", Form("EBEE == %i && R9 == %i && RUN == 5", iEBEE, iR9));
				const Long64_t N_8 = tree_8->Draw("PT:F:DELTAF", Form("EBEE == %i && R9 == %i && RUN == 5", iEBEE, iR9));
				const Long64_t N_9 = tree_9->Draw("PT:F:DELTAF", Form("EBEE == %i && R9 == %i && RUN == 5", iEBEE, iR9));
				c2->cd();
				TGraphErrors *gr_0 = new TGraphErrors(N_0, tree_0->GetV1(), tree_0->GetV2(), 0, tree_0->GetV3());
				TGraphErrors *gr_1 = new TGraphErrors(N_1, tree_1->GetV1(), tree_1->GetV2(), 0, tree_1->GetV3());
				TGraphErrors *gr_2 = new TGraphErrors(N_2, tree_2->GetV1(), tree_2->GetV2(), 0, tree_2->GetV3());
				TGraphErrors *gr_3 = new TGraphErrors(N_3, tree_3->GetV1(), tree_3->GetV2(), 0, tree_3->GetV3());
				TGraphErrors *gr_4 = new TGraphErrors(N_4, tree_4->GetV1(), tree_4->GetV2(), 0, tree_4->GetV3());
				TGraphErrors *gr_5 = new TGraphErrors(N_5, tree_5->GetV1(), tree_5->GetV2(), 0, tree_5->GetV3());
				TGraphErrors *gr_6 = new TGraphErrors(N_6, tree_6->GetV1(), tree_6->GetV2(), 0, tree_6->GetV3());
				TGraphErrors *gr_7 = new TGraphErrors(N_7, tree_7->GetV1(), tree_7->GetV2(), 0, tree_7->GetV3());
				TGraphErrors *gr_8 = new TGraphErrors(N_8, tree_8->GetV1(), tree_8->GetV2(), 0, tree_8->GetV3());
				TGraphErrors *gr_9 = new TGraphErrors(N_9, tree_9->GetV1(), tree_9->GetV2(), 0, tree_9->GetV3());
				gr_0->SetMarkerColor(kRed+3);
				gr_0->SetMarkerStyle(kOpenSquare);
//				gr_0->SetMarkerSize(0.5);
				gr_1->SetMarkerColor(kMagenta);
				gr_1->SetMarkerStyle(kOpenSquare);
//				gr_1->SetMarkerSize(0.9);
				gr_2->SetMarkerColor(kBlue);
				gr_2->SetMarkerStyle(kOpenSquare);
//				gr_2->SetMarkerSize(0.8);
				gr_3->SetMarkerColor(kCyan);
				gr_3->SetMarkerStyle(kOpenSquare);
//				gr_3->SetMarkerSize(0.7);
				gr_4->SetMarkerColor(kGreen);
				gr_4->SetMarkerStyle(kOpenSquare);
//				gr_4->SetMarkerSize(0.6);
				gr_5->SetMarkerColor(kGreen);
				gr_5->SetMarkerStyle(kOpenSquare);
//				gr_5->SetMarkerSize(0.5);
				gr_6->SetMarkerColor(kPink);
				gr_6->SetMarkerStyle(kOpenSquare);
//				gr_6->SetMarkerSize(0.5);
				gr_7->SetMarkerColor(kViolet);
				gr_7->SetMarkerStyle(kOpenSquare);
//				gr_7->SetMarkerSize(0.5);
				gr_8->SetMarkerColor(kAzure);
				gr_8->SetMarkerStyle(kOpenSquare);
//				gr_8->SetMarkerSize(0.5);
				gr_9->SetMarkerColor(kTeal);
				gr_9->SetMarkerStyle(kOpenSquare);
//				gr_9->SetMarkerSize(0.5);
				TMultiGraph *mg = new TMultiGraph();

				mg->Add(gr_0);
				mg->Add(gr_1);
				mg->Add(gr_2);
				mg->Add(gr_3);
				mg->Add(gr_4);
/*
				mg->Add(gr_5);
				mg->Add(gr_8);
				mg->Add(gr_7);
				mg->Add(gr_9);
*/
				mg->Add(gr_6);
				mg->Draw("AP");
				gr_0->SetName("38-82");
				gr_1->SetName("36-84");
				gr_2->SetName("38-84");
				gr_3->SetName("38-86");
				gr_4->SetName("38-88");
				gr_5->SetName("38-78");
				gr_6->SetName("40-80");
				gr_7->SetName("42-82");
				gr_8->SetName("36-76");
				gr_9->SetName("44-84");
				TLegend *legend = new TLegend(0.77, 0.20, 0.90, 0.43, "");
				legend->SetTextSize(0.035);
				legend->SetFillColor(kWhite);
				legend->SetLineColor(kWhite);
				legend->SetShadowColor(kWhite);

				legend->AddEntry(gr_0->GetName(), "38-82", "lp");
				legend->AddEntry(gr_1->GetName(), "36-84", "lp");
				legend->AddEntry(gr_2->GetName(), "38-84", "lp");
				legend->AddEntry(gr_3->GetName(), "38-86", "lp");
				legend->AddEntry(gr_4->GetName(), "38-88", "lp");
/*
				legend->AddEntry(gr_8->GetName(), "36-76", "lp");
				legend->AddEntry(gr_5->GetName(), "38-78", "lp");
*/				legend->AddEntry(gr_6->GetName(), "40-80", "lp");
/*				legend->AddEntry(gr_7->GetName(), "42-82", "lp");
				legend->AddEntry(gr_9->GetName(), "44-84", "lp");
*/				legend->Draw();
//				c2->BuildLegend();
//				grTruth->Draw("AP");
//				gr->Draw("AP");
/*
				cout << "N_5= " << N_5 << "\tmin= " << gr_5->GetXaxis()->GetXmin() << "\tmax= " << gr_5->GetXaxis()->GetXmax() << endl;
				cout << "N_6= " << N_6 << "\tmin= " << gr_6->GetXaxis()->GetXmin() << "\tmax= " << gr_6->GetXaxis()->GetXmax() << endl;
				cout << "N_7= " << N_7 << "\tmin= " << gr_7->GetXaxis()->GetXmin() << "\tmax= " << gr_7->GetXaxis()->GetXmax() << endl;
				cout << "N_8= " << N_8 << "\tmin= " << gr_8->GetXaxis()->GetXmin() << "\tmax= " << gr_8->GetXaxis()->GetXmax() << endl;
				cout << "N_9= " << N_9 << "\tmin= " << gr_9->GetXaxis()->GetXmin() << "\tmax= " << gr_9->GetXaxis()->GetXmax() << endl;
*/
//				double xmin = mg->GetXaxis()->GetXmin() - (mg->GetXaxis()->GetXmax() - 4.0);
				double xmin = gr_5->GetXaxis()->GetXmin() - (gr_5->GetXaxis()->GetXmax() - 5.0);
//				mg->GetXaxis()->SetLimits(xmin, mg->GetXaxis()->GetXmax() + 1);
				mg->GetXaxis()->SetLimits(xmin, mg->GetXaxis()->GetXmax());
				mg->GetXaxis()->SetTitle("p_{T}");
				mg->GetXaxis()->SetBinLabel(mg->GetXaxis()->FindBin(0.0), "[10 ; 12]");
				mg->GetXaxis()->SetBinLabel(mg->GetXaxis()->FindBin(1.0), "[12 ; 15]");
				mg->GetXaxis()->SetBinLabel(mg->GetXaxis()->FindBin(2.0), "[15 ; 20]");
				mg->GetXaxis()->SetBinLabel(mg->GetXaxis()->FindBin(3.0), "[20 ; 25]");
				mg->GetXaxis()->SetBinLabel(mg->GetXaxis()->FindBin(4.0), "[25 ; 30]");
				mg->GetXaxis()->SetBinLabel(mg->GetXaxis()->FindBin(5.0), "[30 ; inf[");
//				mg->GetXaxis()->SetBinLabel(mg->GetXaxis()->FindBin(6.0), "[10 ; inf[");

				double Ymax = iestimator==0 ? 5.0 : 1.075;
				double Ymin = iestimator==0 ? -5.0 : 0.925;
//				mg->SetMaximum(Ymax);
//				mg->SetMinimum(Ymin);

				mg->GetXaxis()->LabelsOption("h");
				mg->GetYaxis()->SetTitle( Form("%s (%)", string_estimator.c_str()) );
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
				double Ymax = iestimator==0 ? 10.0 : 1.075;
				double Ymin = iestimator==0 ? -10.0 : 0.925;
				gr->SetMaximum(Ymax);
				gr->SetMinimum(Ymin);
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
