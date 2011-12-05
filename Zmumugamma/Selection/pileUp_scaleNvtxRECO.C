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

#include "CMSStyle.C"

#pragma optimize 0

using namespace std;

//int main()
int pileUp_scaleNvtxRECO()
{

  CMSstyle();
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

// Get true distribution from lumiDB information :
//	string Data = "pileUp_Run2011A-June17.root";
//	string Data = "pileUp_Run2011A-ZMu-05Jul2011ReReco-ECAL-v1_ALL.root";
//	string Data = "pileUp_Data_May10.root";
//	string Data = "Cert_160404-163869_7TeV_May10ReReco_Collisions11_JSON_v3.pileupTruth_v2_finebin.root";
  string Data = "Cert_160404-163869_7TeV_May10ReReco_Collisions11_JSON_v3.pileup_v2.root";
//  string Data = "pileUp_Data_Promptv4.root";
//  string Data = "Cert_165088-167913_7TeV_PromptReco_JSON.pileupTruth_v2_finebin.root";
//  string Data = "Cert_165088-167913_7TeV_PromptReco_JSON.pileup_v2.root";
//  string Data = "pileUp_Data_July05.root";
//  string Data = "Cert_160404-167913_July05.root";
//  string Data = "Cert_160404-167913_July05_v2.root";
//  string Data = "pileUp_Data_Aug05.root";
//  string Data = "Cert_170249-172619_7TeV_ReReco5Aug_Collisions11_JSON_v2.pileupTruth_v2_finebin.root";
//  string Data = "Cert_170249-172619_7TeV_ReReco5Aug_Collisions11_JSON_v2.pileup_v2.root";
//  string Data = "pileUp_Data_Oct03.root";
//  string Data = "Cert_172620-173692_PromptReco_JSON.pileupTruth_v2_finebin.root";
//  string Data = "Cert_172620-173692_PromptReco_JSON.pileup_v2.root";
//  string Data = "pileUp_Data_2011A.root";
//  string Data = "Cert_160404-173692_2011A.root";
//  string Data = "Cert_160404-173692_2011A_v2.root";
//  string Data = "pileUp_Data_2011B.root";
//  string Data = "Cert_175832-180252_2011B.root";
//  string Data = "Cert_175832-180252_2011B_v2.root";
//  string Data = "pileUp_Data_2011.root";
//  string Data = "Cert_160404-180252_2011.root";
//  string Data = "Cert_160404-180252_2011_v2.root";
/*
Cert_175832-177515_PromptReco_JSON.pileup_v2.root
Cert_177718_178078_7TeV_PromptReco_Collisons11_JSON.pileup_v2.root
Cert_178098-180252_7TeV_PromptReco_Collisions11_JSON.pileup_v2.root
*/
/*
Cert_175832-177515_PromptReco_JSON.pileupTruth_v2_finebin.root
Cert_177718_178078_7TeV_PromptReco_Collisons11_JSON.pileupTruth_v2_finebin.root
Cert_177878-179431_7TeV_PromptReco_Collisions11_JSON.pileupTruth_v2_finebin.root
Cert_178098-180252_7TeV_PromptReco_Collisions11_JSON.pileupTruth_v2_finebin.root
*/
	TFile* data_file = new TFile(Data.c_str());
	TH1D* data_histo = (TH1D*)data_file->Get("pileup");
	double data_integral = data_histo->Integral();
	cout << "data_integral= " << data_integral << endl;
//	TH1D* data_pdf = new TH1D("data_pdf", "data_pdf", 51, -0.5, 50.5);
	TH1D* data_pdf = new TH1D("data_pdf", "data_pdf", 36, -0.5, 35.5);
//	TH1D* data_pdf = new TH1D("data_pdf", "data_pdf", 1000, 0.0, 25);
	data_pdf->Add(data_histo);
//	data_pdf->Rebin(40);
	data_pdf->Scale((double)(1.0)/(double)(data_integral) );
	cout << data_pdf->GetBinContent(0) << "\t" << data_pdf->GetBinContent(1) << endl;
	data_pdf->Draw();

// Get MC distribution before selection but after skim (for now, will switch to before skim whenever possible)
//	string DYToMuMu = "miniTree_pileUp_v2_DYToMuMu_M-20_TuneZ2_7TeV-pythia6_v3.root";
//	string DYToMuMu = "miniTree_pileUp_v2_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_v2.root";
//	string DYToMuMu = "miniTree_pileUp_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_PU_S6_partALL.root";
//	string DYToMuMu = "miniTree_pileUp_pileUp_v02_DYToMuMu_PU_S6_partALL.root";
//	string DYToMuMu = "miniTree_pileUp_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_PU_S6_partALL.root";
	string DYToMuMu = "miniTree_pileUp_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_v6_partALL.root";
//	string DYToMuMu = "miniTree_pileUp_pileUp_v02_DYToMuMu_PU_S6_partALL.root";
	TFile* DYToMuMu_file = new TFile(DYToMuMu.c_str());
	TH1D* DYToMuMu_histo = (TH1D*)DYToMuMu_file->Get("pileup");
	double DYToMuMu_integral = DYToMuMu_histo->Integral();
	cout << "DYToMuMu_integral= " << DYToMuMu_integral << endl;
//	TH1D* DYToMuMu_pdf = new TH1D("DYToMuMu_pdf", "DYToMuMu_pdf", 51, -0.5, 50.5);
	TH1D* DYToMuMu_pdf = new TH1D("DYToMuMu_pdf", "DYToMuMu_pdf", 36, -0.5, 35.5);
//	TH1D* DYToMuMu_pdf = new TH1D("DYToMuMu_pdf", "DYToMuMu_pdf", 1000, 0.0, 25.0);
	DYToMuMu_pdf->Add(DYToMuMu_histo);
//	DYToMuMu_pdf->Rebin(40);
	DYToMuMu_pdf->Scale((double)(1.0)/(double)(DYToMuMu_integral) );
//	TH1D* DYToMuMu_weights = new TH1D("DYToMuMu_weights", "DYToMuMu_weights", 51, -0.5, 50.5);
	TH1D* DYToMuMu_weights = new TH1D("DYToMuMu_weights", "DYToMuMu_weights", 36, -0.5, 35.5);
//	TH1D* DYToMuMu_weights = new TH1D("DYToMuMu_weights", "DYToMuMu_weights", 1000, 0.0, 25.0);
//	TH1D* DYToMuMu_weights = new TH1D("DYToMuMu_weights", "DYToMuMu_weights", 25, 0.0, 25.0);
	DYToMuMu_weights->Divide(data_pdf, DYToMuMu_pdf);
//	double DYToMuMu_weights_integral = DYToMuMu_weights->Integral();
//	DYToMuMu_weights->Scale( (double)(1.0)/(double)(DYToMuMu_weights_integral) );

	TH1D* DYToMuMu_reweighted = new TH1D("DYToMuMu_reweighted", "DYToMuMu_reweighted", 36, -.5, 35.5);
//	TH1D* DYToMuMu_reweighted = new TH1D("DYToMuMu_reweighted", "DYToMuMu_reweighted", 1000, 0.0, 25.0);
	DYToMuMu_reweighted->Add(DYToMuMu_histo);
//	DYToMuMu_reweighted->Rebin(40);
	DYToMuMu_reweighted->Multiply(DYToMuMu_weights);
	double DYToMuMu_reweighted_integral = DYToMuMu_reweighted->Integral();
	DYToMuMu_reweighted->Scale((double)(1.0)/(double)(DYToMuMu_reweighted_integral));
//	string TTJets = "miniTree_pileUp_v2_TT_TuneZ2_7TeV-pythia6-tauola.root";
//	string TTJets = "miniTree_pileUp_v2_TTJets_TuneZ2_7TeV-madgraph-tauola_v2.root";
//  TFile* TTJets_file = new TFile(TTJets.c_str());
//  TH1D* TTJets_histo = (TH1D*)TTJets_file->Get("pileup");
//  double TTJets_integral = TTJets_histo->Integral();
//  TH1D* TTJets_pdf = new TH1D("TTJets_pdf", "TTJets_pdf", 51, -0.5, 50.5);
//	TTJets_pdf->Add(TTJets_histo);
//  TTJets_pdf->Scale((double)(1.0)/(double)(TTJets_integral) );
//  TH1D* TTJets_weights = new TH1D("TTJets_weights", "TTJets_weights", 51, -0.5, 50.5);
//  TTJets_weights->Divide(data_pdf, TTJets_pdf);
//  double TTJets_weights_integral = TTJets_weights->Integral();
//  TTJets_weights->Scale( (double)(1.0)/(double)(TTJets_weights_integral) );

//	string QCDMu = "miniTree_pileUp_v2_QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6.root";
//  TFile* QCDMu_file = new TFile(QCDMu.c_str());
//  TH1D* QCDMu_histo = (TH1D*)QCDMu_file->Get("pileup");
//  double QCDMu_integral = QCDMu_histo->Integral();
//  TH1D* QCDMu_pdf = new TH1D("QCDMu_pdf", "QCDMu_pdf", 51, -0.5, 50.5);
//	QCDMu_pdf->Add(QCDMu_histo);
//  QCDMu_pdf->Scale((double)(1.0)/(double)(QCDMu_integral) );
//  TH1D* QCDMu_weights = new TH1D("QCDMu_weights", "QCDMu_weights", 51, -0.5, 50.5);
//  QCDMu_weights->Divide(data_pdf, QCDMu_pdf);
//  double QCDMu_weights_integral = QCDMu_weights->Integral();
//  QCDMu_weights->Scale( (double)(1.0)/(double)(QCDMu_weights_integral) );

//	string WJetsToLNu = "miniTree_pileUp_v2_WToMuNu_TuneZ2_7TeV-pythia6.root";
//  TFile* WJetsToLNu_file = new TFile(WJetsToLNu.c_str());
//  TH1D* WJetsToLNu_histo = (TH1D*)WJetsToLNu_file->Get("pileup");
//  double WJetsToLNu_integral = WJetsToLNu_histo->Integral();
//  TH1D* WJetsToLNu_pdf = new TH1D("WJetsToLNu_pdf", "WJetsToLNu_pdf", 51, -0.5, 50.5);
//	WJetsToLNu_pdf->Add(WJetsToLNu_histo);
//  WJetsToLNu_pdf->Scale((double)(1.0)/(double)(WJetsToLNu_integral) );
//  TH1D* WJetsToLNu_weights = new TH1D("WJetsToLNu_weights", "WJetsToLNu_weights", 51, -0.5, 50.5);
//  WJetsToLNu_weights->Divide(data_pdf, WJetsToLNu_pdf);
//  double WJetsToLNu_weights_integral = WJetsToLNu_weights->Integral();
//  WJetsToLNu_weights->Scale( (double)(1.0)/(double)(WJetsToLNu_weights_integral) );

	cout << "DYToMuMu" << endl;
	for(int i=0; i < DYToMuMu_weights->GetNbinsX(); i++){ cout << DYToMuMu_weights->GetBinContent(i) << ", ";  }
//	cout << endl << "TTJets" << endl;
//	for(int i=0; i < TTJets_weights->GetNbinsX(); i++){ cout << TTJets_weights->GetBinContent(i) << ", ";  }
//	cout << endl << "QCDMu" << endl;
//	for(int i=0; i < QCDMu_weights->GetNbinsX(); i++){ cout << QCDMu_weights->GetBinContent(i) << ", ";  }
//	cout << endl << "WJetsToLNu" << endl;
//	for(int i=0; i < WJetsToLNu_weights->GetNbinsX(); i++){ cout << WJetsToLNu_weights->GetBinContent(i) << ", ";  }
	cout << endl;	

	TFile* weights_file = new TFile("pileUp_weights_June17.root", "recreate");
	weights_file->cd();
	DYToMuMu_weights->Write();
	DYToMuMu_reweighted->Write();
	data_pdf->Write();
//	TTJets_weights->Write();
//	QCDMu_weights->Write();
//	WJetsToLNu_weights->Write();
	weights_file->Close();
/*
  string Data = "miniTree_v2_Run2011A-PromptReco-v4_June17.root";
  string DYToMuMu = "miniTree_v2_DYToMuMu_M-20_TuneZ2_7TeV-pythia6_v3.root";
  string TTJets = "miniTree_v2_TT_TuneZ2_7TeV-pythia6-tauola.root";
  string WJetsToLNu = "miniTree_v2_WToMuNu_TuneZ2_7TeV-pythia6.root";
  string QCDMu = "miniTree_v2_QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6.root";

  TFile *Data_File = new TFile(Data.c_str());
  TTree* Data_miniTree = (TTree*) Data_File->Get("miniTree");
  TFile *DYToMuMu_File = new TFile(DYToMuMu.c_str());
  TTree* DYToMuMu_miniTree = (TTree*) DYToMuMu_File->Get("miniTree");
  TFile *TTJets_File = new TFile(TTJets.c_str());
  TTree* TTJets_miniTree = (TTree*) TTJets_File->Get("miniTree");
  TFile *WJetsToLNu_File = new TFile(WJetsToLNu.c_str());
  TTree* WJetsToLNu_miniTree = (TTree*) WJetsToLNu_File->Get("miniTree");
  TFile *QCDMu_File = new TFile(QCDMu.c_str());
  TTree* QCDMu_miniTree = (TTree*) QCDMu_File->Get("miniTree");

  TCanvas *c1 = new TCanvas("Default", "Default");

	string limits = "(50,0,50)";
	string var = "nVertices";
	

	TH1F *Histo_Data_temp = new TH1F();
  string variable_Data = var + ">>Histo_Data_temp" + limits;
  Data_miniTree->Draw(variable_Data.c_str(), cut.c_str());
  TH1F *Histo_Data = (TH1F*)gDirectory->Get("Histo_Data_temp");
  c1->Clear();
*/

return 0;
}
