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

#include "DrawDataMC.h"

#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootBardak.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootBeamSpot.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootCluster.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootEcalRecHit.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootElectron.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootEvent.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootJet.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootMCParticle.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootMCPhoton.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootMET.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootMuon.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootParticle.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootPhoton.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootRun.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootSignalEvent.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootSuperCluster.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootTopTop.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootTrack.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootVertex.h"



#pragma optimize 0

using namespace std;
/*
void DrawDataMCplot(TTree *Data_miniTree, TTree *QCD_Pt15_miniTree, TTree *QCD_Pt30_miniTree, TTree *QCD_Pt80_miniTree, TTree *QCD_Pt170_miniTree, TTree *QCD_Pt300_miniTree, TTree *QCD_Pt470_miniTree, TTree *PhotonJet_Pt15_miniTree, TTree *PhotonJet_Pt30_miniTree, TTree *PhotonJet_Pt80_miniTree, TTree *PhotonJet_Pt170_miniTree, TTree *PhotonJet_Pt300_miniTree, TTree *TTbarJets_Tauola_miniTree, TTree *WJets_7TeV_miniTree, TTree *ZJets_7TeV_miniTree, TTree *QCD_Mu_Pt20to30_miniTree, TTree *QCD_Mu_Pt30to50_miniTree, TTree *QCD_Mu_Pt50to80_miniTree, TTree *QCD_Mu_Pt80to120_miniTree, TTree *QCD_Mu_Pt120to170_miniTree, TTree *QCD_Mu_Pt170toInf_miniTree, TTree *InclusiveMu15_miniTree, TTree *ZmumuJet_Pt0to15_miniTree, TTree *ZmumuJet_Pt15to20_miniTree, TTree *ZmumuJet_Pt20to30_miniTree, TTree *ZmumuJet_Pt30to50_miniTree, TTree *ZmumuJet_Pt50to80_miniTree, TTree *ZmumuJet_Pt80to120_miniTree, TTree *ZmumuJet_Pt120to170_miniTree, TTree *ZmumuJet_Pt170to230_miniTree, TTree *ZmumuJet_Pt230to300_miniTree, TTree *ZmumuJet_Pt300toInf_miniTree, string var, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1){

	// Get Histo_Data from eventTree
	TH1F *Histo_Data_temp = new TH1F();
	string variable_Data = var + ">>Histo_Data_temp" + limits;
	Data_miniTree->Draw(variable_Data.c_str(), cut.c_str());
	TH1F *Histo_Data = (TH1F*)gDirectory->Get("Histo_Data_temp"); 
	c1->Clear();

	// Get Histo_PhotonJet_Pt15 from eventTree
	TH1F *Histo_PhotonJet_Pt15_temp = new TH1F();
	string variable_PhotonJet_Pt15 = var + ">>Histo_PhotonJet_Pt15_temp" + limits;
	PhotonJet_Pt15_miniTree->Draw(variable_PhotonJet_Pt15.c_str(), cut.c_str());
	TH1F *Histo_PhotonJet_Pt15 = (TH1F*)gDirectory->Get("Histo_PhotonJet_Pt15_temp");
	c1->Clear();

	// Get Histo_PhotonJet_Pt30 from eventTree
	TH1F *Histo_PhotonJet_Pt30_temp = new TH1F();
	string variable_PhotonJet_Pt30 = var + ">>Histo_PhotonJet_Pt30_temp" + limits;
	PhotonJet_Pt30_miniTree->Draw(variable_PhotonJet_Pt30.c_str(), cut.c_str());
	TH1F *Histo_PhotonJet_Pt30 = (TH1F*)gDirectory->Get("Histo_PhotonJet_Pt30_temp");
	c1->Clear();

	// Get Histo_PhotonJet_Pt80 from eventTree
	TH1F *Histo_PhotonJet_Pt80_temp = new TH1F();
	string variable_PhotonJet_Pt80 = var + ">>Histo_PhotonJet_Pt80_temp" + limits;
	PhotonJet_Pt80_miniTree->Draw(variable_PhotonJet_Pt80.c_str(), cut.c_str());
	TH1F *Histo_PhotonJet_Pt80 = (TH1F*)gDirectory->Get("Histo_PhotonJet_Pt80_temp");
	c1->Clear();

	// Get Histo_PhotonJet_Pt170 from eventTree
	TH1F *Histo_PhotonJet_Pt170_temp = new TH1F();
	string variable_PhotonJet_Pt170 = var + ">>Histo_PhotonJet_Pt170_temp" + limits;
	PhotonJet_Pt170_miniTree->Draw(variable_PhotonJet_Pt170.c_str(), cut.c_str());
	TH1F *Histo_PhotonJet_Pt170 = (TH1F*)gDirectory->Get("Histo_PhotonJet_Pt170_temp");
	c1->Clear();

	// Get Histo_PhotonJet_Pt300 from eventTree
	TH1F *Histo_PhotonJet_Pt300_temp = new TH1F();
	string variable_PhotonJet_Pt300 = var + ">>Histo_PhotonJet_Pt300_temp" + limits;
	PhotonJet_Pt300_miniTree->Draw(variable_PhotonJet_Pt300.c_str(), cut.c_str());
	TH1F *Histo_PhotonJet_Pt300 = (TH1F*)gDirectory->Get("Histo_PhotonJet_Pt300_temp");
	c1->Clear();

	// Get Histo_QCD_Pt15 from eventTree
	TH1F *Histo_QCD_Pt15_temp = new TH1F();
	string variable_QCD_Pt15 = var + ">>Histo_QCD_Pt15_temp" + limits;
	QCD_Pt15_miniTree->Draw(variable_QCD_Pt15.c_str(), cut.c_str());
	TH1F *Histo_QCD_Pt15 = (TH1F*)gDirectory->Get("Histo_QCD_Pt15_temp");
	c1->Clear();

	// Get Histo_QCD_Pt30 from eventTree
	TH1F *Histo_QCD_Pt30_temp = new TH1F();
	string variable_QCD_Pt30 = var + ">>Histo_QCD_Pt30_temp" + limits;
	QCD_Pt30_miniTree->Draw(variable_QCD_Pt30.c_str(), cut.c_str());
	TH1F *Histo_QCD_Pt30 = (TH1F*)gDirectory->Get("Histo_QCD_Pt30_temp");
	c1->Clear();

	// Get Histo_QCD_Pt80 from eventTree
	TH1F *Histo_QCD_Pt80_temp = new TH1F();
	string variable_QCD_Pt80 = var + ">>Histo_QCD_Pt80_temp" + limits;
	QCD_Pt80_miniTree->Draw(variable_QCD_Pt80.c_str(), cut.c_str());
	TH1F *Histo_QCD_Pt80 = (TH1F*)gDirectory->Get("Histo_QCD_Pt80_temp");
	c1->Clear();

	// Get Histo_QCD_Pt170 from eventTree
	TH1F *Histo_QCD_Pt170_temp = new TH1F();
	string variable_QCD_Pt170 = var + ">>Histo_QCD_Pt170_temp" + limits;
	QCD_Pt170_miniTree->Draw(variable_QCD_Pt170.c_str(), cut.c_str());
	TH1F *Histo_QCD_Pt170 = (TH1F*)gDirectory->Get("Histo_QCD_Pt170_temp");
	c1->Clear();

	// Get Histo_QCD_Pt300 from eventTree
	TH1F *Histo_QCD_Pt300_temp = new TH1F();
	string variable_QCD_Pt300 = var + ">>Histo_QCD_Pt300_temp" + limits;
	QCD_Pt300_miniTree->Draw(variable_QCD_Pt300.c_str(), cut.c_str());
	TH1F *Histo_QCD_Pt300 = (TH1F*)gDirectory->Get("Histo_QCD_Pt300_temp");
	c1->Clear();

	// Get Histo_QCD_Pt470 from eventTree
	TH1F *Histo_QCD_Pt470_temp = new TH1F();
	string variable_QCD_Pt470 = var + ">>Histo_QCD_Pt470_temp" + limits;
	QCD_Pt470_miniTree->Draw(variable_QCD_Pt470.c_str(), cut.c_str());
	TH1F *Histo_QCD_Pt470 = (TH1F*)gDirectory->Get("Histo_QCD_Pt470_temp");
	c1->Clear();

	// Get Histo_TTbarJets_Tauola from eventTree
	TH1F *Histo_TTbarJets_Tauola_temp = new TH1F();
	string variable_TTbarJets_Tauola = var + ">>Histo_TTbarJets_Tauola_temp" + limits;
	TTbarJets_Tauola_miniTree->Draw(variable_TTbarJets_Tauola.c_str(), cut.c_str());
	TH1F *Histo_TTbarJets_Tauola = (TH1F*)gDirectory->Get("Histo_TTbarJets_Tauola_temp");
	c1->Clear();

	// Get Histo_WJets_7TeV from eventTree
	TH1F *Histo_WJets_7TeV_temp = new TH1F();
	string variable_WJets_7TeV = var + ">>Histo_WJets_7TeV_temp" + limits;
	WJets_7TeV_miniTree->Draw(variable_WJets_7TeV.c_str(), cut.c_str());
	TH1F *Histo_WJets_7TeV = (TH1F*)gDirectory->Get("Histo_WJets_7TeV_temp");
	c1->Clear();

	// Get Histo_ZJets_7TeV from eventTree
	TH1F *Histo_ZJets_7TeV_temp = new TH1F();
	string variable_ZJets_7TeV = var + ">>Histo_ZJets_7TeV_temp" + limits;
	ZJets_7TeV_miniTree->Draw(variable_ZJets_7TeV.c_str(), cut.c_str());
	TH1F *Histo_ZJets_7TeV = (TH1F*)gDirectory->Get("Histo_ZJets_7TeV_temp");
	c1->Clear();

	// Get Histo_QCD_Mu_Pt20to30 from eventTree
	TH1F *Histo_QCD_Mu_Pt20to30_temp = new TH1F();
	string variable_QCD_Mu_Pt20to30 = var + ">>Histo_QCD_Mu_Pt20to30_temp" + limits;
	QCD_Mu_Pt20to30_miniTree->Draw(variable_QCD_Mu_Pt20to30.c_str(), cut.c_str());
	TH1F *Histo_QCD_Mu_Pt20to30 = (TH1F*)gDirectory->Get("Histo_QCD_Mu_Pt20to30_temp");
	c1->Clear();

	// Get Histo_QCD_Mu_Pt30to50 from eventTree
	TH1F *Histo_QCD_Mu_Pt30to50_temp = new TH1F();
	string variable_QCD_Mu_Pt30to50 = var + ">>Histo_QCD_Mu_Pt30to50_temp" + limits;
	QCD_Mu_Pt30to50_miniTree->Draw(variable_QCD_Mu_Pt30to50.c_str(), cut.c_str());
	TH1F *Histo_QCD_Mu_Pt30to50 = (TH1F*)gDirectory->Get("Histo_QCD_Mu_Pt30to50_temp");
	c1->Clear();

	// Get Histo_QCD_Mu_Pt50to80 from eventTree
	TH1F *Histo_QCD_Mu_Pt50to80_temp = new TH1F();
	string variable_QCD_Mu_Pt50to80 = var + ">>Histo_QCD_Mu_Pt50to80_temp" + limits;
	QCD_Mu_Pt50to80_miniTree->Draw(variable_QCD_Mu_Pt50to80.c_str(), cut.c_str());
	TH1F *Histo_QCD_Mu_Pt50to80 = (TH1F*)gDirectory->Get("Histo_QCD_Mu_Pt50to80_temp");
	c1->Clear();

	// Get Histo_QCD_Mu_Pt80to120 from eventTree
	TH1F *Histo_QCD_Mu_Pt80to120_temp = new TH1F();
	string variable_QCD_Mu_Pt80to120 = var + ">>Histo_QCD_Mu_Pt80to120_temp" + limits;
	QCD_Mu_Pt80to120_miniTree->Draw(variable_QCD_Mu_Pt80to120.c_str(), cut.c_str());
	TH1F *Histo_QCD_Mu_Pt80to120 = (TH1F*)gDirectory->Get("Histo_QCD_Mu_Pt80to120_temp");
	c1->Clear();

	// Get Histo_QCD_Mu_Pt120to170 from eventTree
	TH1F *Histo_QCD_Mu_Pt120to170_temp = new TH1F();
	string variable_QCD_Mu_Pt120to170 = var + ">>Histo_QCD_Mu_Pt120to170_temp" + limits;
	QCD_Mu_Pt120to170_miniTree->Draw(variable_QCD_Mu_Pt120to170.c_str(), cut.c_str());
	TH1F *Histo_QCD_Mu_Pt120to170 = (TH1F*)gDirectory->Get("Histo_QCD_Mu_Pt120to170_temp");
	c1->Clear();

	// Get Histo_QCD_Mu_Pt170toInf from eventTree
	TH1F *Histo_QCD_Mu_Pt170toInf_temp = new TH1F();
	string variable_QCD_Mu_Pt170toInf = var + ">>Histo_QCD_Mu_Pt170toInf_temp" + limits;
	QCD_Mu_Pt170toInf_miniTree->Draw(variable_QCD_Mu_Pt170toInf.c_str(), cut.c_str());
	TH1F *Histo_QCD_Mu_Pt170toInf = (TH1F*)gDirectory->Get("Histo_QCD_Mu_Pt170toInf_temp");
	c1->Clear();

	// Get Histo_InclusiveMu15 from eventTree
	TH1F *Histo_InclusiveMu15_temp = new TH1F();
	string variable_InclusiveMu15 = var + ">>Histo_InclusiveMu15_temp" + limits;
	InclusiveMu15_miniTree->Draw(variable_InclusiveMu15.c_str(), cut.c_str());
	TH1F *Histo_InclusiveMu15 = (TH1F*)gDirectory->Get("Histo_InclusiveMu15_temp");
	c1->Clear();

	// Get Histo_ZmumuJet_Pt0to15 from eventTree
	TH1F *Histo_ZmumuJet_Pt0to15_temp = new TH1F();
	string variable_ZmumuJet_Pt0to15 = var + ">>Histo_ZmumuJet_Pt0to15_temp" + limits;
	ZmumuJet_Pt0to15_miniTree->Draw(variable_ZmumuJet_Pt0to15.c_str(), cut.c_str());
	TH1F *Histo_ZmumuJet_Pt0to15 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt0to15_temp");
	c1->Clear();

	// Get Histo_ZmumuJet_Pt15to20 from eventTree
	TH1F *Histo_ZmumuJet_Pt15to20_temp = new TH1F();
	string variable_ZmumuJet_Pt15to20 = var + ">>Histo_ZmumuJet_Pt15to20_temp" + limits;
	ZmumuJet_Pt15to20_miniTree->Draw(variable_ZmumuJet_Pt15to20.c_str(), cut.c_str());
	TH1F *Histo_ZmumuJet_Pt15to20 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt15to20_temp");
	c1->Clear();

	// Get Histo_ZmumuJet_Pt20to30 from eventTree
	TH1F *Histo_ZmumuJet_Pt20to30_temp = new TH1F();
	string variable_ZmumuJet_Pt20to30 = var + ">>Histo_ZmumuJet_Pt20to30_temp" + limits;
	ZmumuJet_Pt20to30_miniTree->Draw(variable_ZmumuJet_Pt20to30.c_str(), cut.c_str());
	TH1F *Histo_ZmumuJet_Pt20to30 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt20to30_temp");
	c1->Clear();

	// Get Histo_ZmumuJet_Pt30to50 from eventTree
	TH1F *Histo_ZmumuJet_Pt30to50_temp = new TH1F();
	string variable_ZmumuJet_Pt30to50 = var + ">>Histo_ZmumuJet_Pt30to50_temp" + limits;
	ZmumuJet_Pt30to50_miniTree->Draw(variable_ZmumuJet_Pt30to50.c_str(), cut.c_str());
	TH1F *Histo_ZmumuJet_Pt30to50 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt30to50_temp");
	c1->Clear();

	// Get Histo_ZmumuJet_Pt50to80 from eventTree
	TH1F *Histo_ZmumuJet_Pt50to80_temp = new TH1F();
	string variable_ZmumuJet_Pt50to80 = var + ">>Histo_ZmumuJet_Pt50to80_temp" + limits;
	ZmumuJet_Pt50to80_miniTree->Draw(variable_ZmumuJet_Pt50to80.c_str(), cut.c_str());
	TH1F *Histo_ZmumuJet_Pt50to80 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt50to80_temp");
	c1->Clear();

	// Get Histo_ZmumuJet_Pt80to120 from eventTree
	TH1F *Histo_ZmumuJet_Pt80to120_temp = new TH1F();
	string variable_ZmumuJet_Pt80to120 = var + ">>Histo_ZmumuJet_Pt80to120_temp" + limits;
	ZmumuJet_Pt80to120_miniTree->Draw(variable_ZmumuJet_Pt80to120.c_str(), cut.c_str());
	TH1F *Histo_ZmumuJet_Pt80to120 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt80to120_temp");
	c1->Clear();

	// Get Histo_ZmumuJet_Pt120to170 from eventTree
	TH1F *Histo_ZmumuJet_Pt120to170_temp = new TH1F();
	string variable_ZmumuJet_Pt120to170 = var + ">>Histo_ZmumuJet_Pt120to170_temp" + limits;
	ZmumuJet_Pt120to170_miniTree->Draw(variable_ZmumuJet_Pt120to170.c_str(), cut.c_str());
	TH1F *Histo_ZmumuJet_Pt120to170 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt120to170_temp");
	c1->Clear();

	// Get Histo_ZmumuJet_Pt170to230 from eventTree
	TH1F *Histo_ZmumuJet_Pt170to230_temp = new TH1F();
	string variable_ZmumuJet_Pt170to230 = var + ">>Histo_ZmumuJet_Pt170to230_temp" + limits;
	ZmumuJet_Pt170to230_miniTree->Draw(variable_ZmumuJet_Pt170to230.c_str(), cut.c_str());
	TH1F *Histo_ZmumuJet_Pt170to230 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt170to230_temp");
	c1->Clear();

	// Get Histo_ZmumuJet_Pt230to300 from eventTree
	TH1F *Histo_ZmumuJet_Pt230to300_temp = new TH1F();
	string variable_ZmumuJet_Pt230to300 = var + ">>Histo_ZmumuJet_Pt230to300_temp" + limits;
	ZmumuJet_Pt230to300_miniTree->Draw(variable_ZmumuJet_Pt230to300.c_str(), cut.c_str());
	TH1F *Histo_ZmumuJet_Pt230to300 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt230to300_temp");
	c1->Clear();

	// Get Histo_ZmumuJet_Pt300toInf from eventTree
	TH1F *Histo_ZmumuJet_Pt300toInf_temp = new TH1F();
	string variable_ZmumuJet_Pt300toInf = var + ">>Histo_ZmumuJet_Pt300toInf_temp" + limits;
	ZmumuJet_Pt300toInf_miniTree->Draw(variable_ZmumuJet_Pt300toInf.c_str(), cut.c_str());
	TH1F *Histo_ZmumuJet_Pt300toInf = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt300toInf_temp");
	c1->Clear();


	// TODO: implement drawUnderOverFsubleading

	// Get the number of entries for further normalization
	double a = Histo_Data->Integral();

//	double b_PhotonJet_Pt15 = Histo_PhotonJet_Pt15->Integral();
//	if( (a==0.0) || (b_PhotonJet_Pt15==0.0) ){
//		cout << "no entries to plots" <<endl;
//		return; 
//	}
	// Normalize
	Histo_Data->Sumw2(); // In order to have the correct error bars on data after renormalization
	// // Normalize MC and Data to 1
	//Histo_Data->Scale((double)((double)1.0/(double)a));
	//Histo_MC->Scale((double)((double)1.0/(double)b));
	// // Normalize MC to Data number of entries
	double integratedLuminosity = 301.213e-03;

	double XSectionQCD_Pt15 = 8.762e+08;
	double XSectionQCD_Pt30 = 6.041e+07;
	double XSectionQCD_Pt80 = 9.238e+05;
	double XSectionQCD_Pt170 = 2.547e+04;
	double XSectionQCD_Pt300 = 1.256e+03;
	double XSectionQCD_Pt470 = 8.798e+01;
	double XSectionPhotonJet_Pt15 = 1.922e+05;
	double XSectionPhotonJet_Pt30 = 2.007e+04;
	double XSectionPhotonJet_Pt80 = 5.565e+02;
	double XSectionPhotonJet_Pt170 = 2.437e+01;
	double XSectionPhotonJet_Pt300 = 1.636e+00;
	double XSectionTTbarJets_Tauola = 95.0;
	double XSectionWJets_7TeV = 25090.0;
	double XSectionZJets_7TeV = 2224.0;
	double XSectionQCD_Mu_Pt20to30 = 1208700.0;
	double XSectionQCD_Mu_Pt30to50 = 654360.0;
	double XSectionQCD_Mu_Pt50to80 = 138846.0;
	double XSectionQCD_Mu_Pt80to120 = 29045.0;
	double XSectionQCD_Mu_Pt120to170 = 6095.0;
	double XSectionQCD_Mu_Pt170toInf = 1612.8;
	double XSectionInclusiveMu15 = 79687.96;
	double XSectionZmumuJet_Pt0to15 = 4.434e+03;
	double XSectionZmumuJet_Pt15to20 = 1.454e+02;
	double XSectionZmumuJet_Pt20to30 = 1.318e+02;
	double XSectionZmumuJet_Pt30to50 = 8.438e+01;
	double XSectionZmumuJet_Pt50to80 = 3.235e+01;
	double XSectionZmumuJet_Pt80to120 = 9.981e+00;
	double XSectionZmumuJet_Pt120to170 = 2.760e+00;
	double XSectionZmumuJet_Pt170to230 = 7.241e-01;
	double XSectionZmumuJet_Pt230to300 = 1.946e-01;
	double XSectionZmumuJet_Pt300toInf = 7.627e-02;

	double InitialNumberQCD_Pt15 = 6196800;
	double InitialNumberQCD_Pt30 = 5093840;
	double InitialNumberQCD_Pt80 = 3229000;
	double InitialNumberQCD_Pt170 = 3162500;
	double InitialNumberQCD_Pt300 = 3269645;
	double InitialNumberQCD_Pt470 = 2093653;
	double InitialNumberPhotonJet_Pt15 = 1221770;
	double InitialNumberPhotonJet_Pt30 = 1025300;
	double InitialNumberPhotonJet_Pt80 = 1287711;
	double InitialNumberPhotonJet_Pt170 = 1209600;
	double InitialNumberPhotonJet_Pt300 = 1033240;
	double InitialNumberTTbarJets_Tauola = 1463572;
	double InitialNumberWJets_7TeV = 10218854;
	double InitialNumberZJets_7TeV = 1047008;
	double InitialNumberQCD_Mu_Pt20to30 = 11035188;
	double InitialNumberQCD_Mu_Pt30to50 = 6951182;
	double InitialNumberQCD_Mu_Pt50to80 = 2542308;
	double InitialNumberQCD_Mu_Pt80to120 = 523053;
	double InitialNumberQCD_Mu_Pt120to170 = 316630;
	double InitialNumberQCD_Mu_Pt170toInf = 262036;
	double InitialNumberInclusiveMu15 = 5120334;
	double InitialNumberZmumuJet_Pt0to15 = 235420;
	double InitialNumberZmumuJet_Pt15to20 = 222730;
	double InitialNumberZmumuJet_Pt20to30 = 164190;
	double InitialNumberZmumuJet_Pt30to50 = 163920;
	double InitialNumberZmumuJet_Pt50to80 = 106016;
	double InitialNumberZmumuJet_Pt80to120 = 107759;
	double InitialNumberZmumuJet_Pt120to170 = 177408;
	double InitialNumberZmumuJet_Pt170to230 = 178400;
	double InitialNumberZmumuJet_Pt230to300 = 176485;
	double InitialNumberZmumuJet_Pt300toInf = 109316;

	Histo_PhotonJet_Pt15->Scale((double)(  (double)((double)(XSectionPhotonJet_Pt15) / (double)(InitialNumberPhotonJet_Pt15)) * (double)integratedLuminosity));
	Histo_PhotonJet_Pt30->Scale((double)(  (double)((double)(XSectionPhotonJet_Pt30) / (double)(InitialNumberPhotonJet_Pt30)) * (double)integratedLuminosity));
	Histo_PhotonJet_Pt80->Scale((double)(  (double)((double)(XSectionPhotonJet_Pt80) / (double)(InitialNumberPhotonJet_Pt80)) * (double)integratedLuminosity));
	Histo_PhotonJet_Pt170->Scale((double)(  (double)((double)(XSectionPhotonJet_Pt170) / (double)(InitialNumberPhotonJet_Pt170)) * (double)integratedLuminosity));
	Histo_PhotonJet_Pt300->Scale((double)(  (double)((double)(XSectionPhotonJet_Pt300) / (double)(InitialNumberPhotonJet_Pt300)) * (double)integratedLuminosity));
	Histo_QCD_Pt15->Scale((double)(  (double)((double)(XSectionQCD_Pt15) / (double)(InitialNumberQCD_Pt15)) * (double)integratedLuminosity));
	Histo_QCD_Pt30->Scale((double)(  (double)((double)(XSectionQCD_Pt30) / (double)(InitialNumberQCD_Pt30)) * (double)integratedLuminosity));
	Histo_QCD_Pt80->Scale((double)(  (double)((double)(XSectionQCD_Pt80) / (double)(InitialNumberQCD_Pt80)) * (double)integratedLuminosity));
	Histo_QCD_Pt170->Scale((double)(  (double)((double)(XSectionQCD_Pt170) / (double)(InitialNumberQCD_Pt170)) * (double)integratedLuminosity));
	Histo_QCD_Pt300->Scale((double)(  (double)((double)(XSectionQCD_Pt300) / (double)(InitialNumberQCD_Pt300)) * (double)integratedLuminosity));
	Histo_QCD_Pt470->Scale((double)(  (double)((double)(XSectionQCD_Pt470) / (double)(InitialNumberQCD_Pt470)) * (double)integratedLuminosity));
	Histo_TTbarJets_Tauola->Scale((double)(  (double)((double)(XSectionTTbarJets_Tauola) / (double)(InitialNumberTTbarJets_Tauola)) * (double)integratedLuminosity));
	Histo_WJets_7TeV->Scale((double)(  (double)((double)(XSectionWJets_7TeV) / (double)(InitialNumberWJets_7TeV)) * (double)integratedLuminosity));
	Histo_ZJets_7TeV->Scale((double)(  (double)((double)(XSectionZJets_7TeV) / (double)(InitialNumberZJets_7TeV)) * (double)integratedLuminosity));
	Histo_QCD_Mu_Pt20to30->Scale((double)(  (double)((double)(XSectionQCD_Mu_Pt20to30) / (double)(InitialNumberQCD_Mu_Pt20to30)) * (double)integratedLuminosity));
	Histo_QCD_Mu_Pt30to50->Scale((double)(  (double)((double)(XSectionQCD_Mu_Pt30to50) / (double)(InitialNumberQCD_Mu_Pt30to50)) * (double)integratedLuminosity));
	Histo_QCD_Mu_Pt50to80->Scale((double)(  (double)((double)(XSectionQCD_Mu_Pt50to80) / (double)(InitialNumberQCD_Mu_Pt50to80)) * (double)integratedLuminosity));
	Histo_QCD_Mu_Pt80to120->Scale((double)(  (double)((double)(XSectionQCD_Mu_Pt80to120) / (double)(InitialNumberQCD_Mu_Pt80to120)) * (double)integratedLuminosity));
	Histo_QCD_Mu_Pt120to170->Scale((double)(  (double)((double)(XSectionQCD_Mu_Pt120to170) / (double)(InitialNumberQCD_Mu_Pt120to170)) * (double)integratedLuminosity));
	Histo_QCD_Mu_Pt170toInf->Scale((double)(  (double)((double)(XSectionQCD_Mu_Pt170toInf) / (double)(InitialNumberQCD_Mu_Pt170toInf)) * (double)integratedLuminosity));
	Histo_InclusiveMu15->Scale((double)(  (double)((double)(XSectionInclusiveMu15) / (double)(InitialNumberInclusiveMu15)) * (double)integratedLuminosity));
	Histo_ZmumuJet_Pt0to15->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt0to15) / (double)(InitialNumberZmumuJet_Pt0to15)) * (double)integratedLuminosity));
	Histo_ZmumuJet_Pt15to20->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt15to20) / (double)(InitialNumberZmumuJet_Pt15to20)) * (double)integratedLuminosity));
	Histo_ZmumuJet_Pt20to30->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt20to30) / (double)(InitialNumberZmumuJet_Pt20to30)) * (double)integratedLuminosity));
	Histo_ZmumuJet_Pt30to50->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt30to50) / (double)(InitialNumberZmumuJet_Pt30to50)) * (double)integratedLuminosity));
	Histo_ZmumuJet_Pt50to80->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt50to80) / (double)(InitialNumberZmumuJet_Pt50to80)) * (double)integratedLuminosity));
	Histo_ZmumuJet_Pt80to120->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt80to120) / (double)(InitialNumberZmumuJet_Pt80to120)) * (double)integratedLuminosity));
	Histo_ZmumuJet_Pt120to170->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt120to170) / (double)(InitialNumberZmumuJet_Pt120to170)) * (double)integratedLuminosity));
	Histo_ZmumuJet_Pt170to230->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt170to230) / (double)(InitialNumberZmumuJet_Pt170to230)) * (double)integratedLuminosity));
	Histo_ZmumuJet_Pt230to300->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt230to300) / (double)(InitialNumberZmumuJet_Pt230to300)) * (double)integratedLuminosity));
	Histo_ZmumuJet_Pt300toInf->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt300toInf) / (double)(InitialNumberZmumuJet_Pt300toInf)) * (double)integratedLuminosity));

	// Adding histograms for binned samples
	Histo_QCD_Pt15->Add(Histo_QCD_Pt30);
	Histo_QCD_Pt15->Add(Histo_QCD_Pt80);
	Histo_QCD_Pt15->Add(Histo_QCD_Pt170);
	Histo_QCD_Pt15->Add(Histo_QCD_Pt300);
	Histo_QCD_Pt15->Add(Histo_QCD_Pt470);

  Histo_QCD_Mu_Pt20to30->Add(Histo_QCD_Mu_Pt30to50);
  Histo_QCD_Mu_Pt20to30->Add(Histo_QCD_Mu_Pt50to80);
  Histo_QCD_Mu_Pt20to30->Add(Histo_QCD_Mu_Pt80to120);
  Histo_QCD_Mu_Pt20to30->Add(Histo_QCD_Mu_Pt120to170);
  Histo_QCD_Mu_Pt20to30->Add(Histo_QCD_Mu_Pt170toInf);

  Histo_PhotonJet_Pt15->Add(Histo_PhotonJet_Pt30);
  Histo_PhotonJet_Pt15->Add(Histo_PhotonJet_Pt80);
  Histo_PhotonJet_Pt15->Add(Histo_PhotonJet_Pt170);
  Histo_PhotonJet_Pt15->Add(Histo_PhotonJet_Pt300);

  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt15to20);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt20to30);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt30to50);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt50to80);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt80to120);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt120to170);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt170to230);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt230to300);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt300toInf);


	// Get the maxs and the mins to further correct the Y-axis
	double dataMax = Histo_Data->GetMaximum();
	double YMax = dataMax;
	double PhotonJet_Pt15Max = Histo_PhotonJet_Pt15->GetMaximum();
	YMax = max(YMax, PhotonJet_Pt15Max);
	double QCD_Pt15Max = Histo_QCD_Pt15->GetMaximum();
	YMax = max(YMax, QCD_Pt15Max);
	double TTbarJets_TauolaMax = Histo_TTbarJets_Tauola->GetMaximum();
	YMax = max(YMax, TTbarJets_TauolaMax);
	double WJets_7TeVMax = Histo_WJets_7TeV->GetMaximum();
	YMax = max(YMax, WJets_7TeVMax);
	double ZJets_7TeVMax = Histo_ZJets_7TeV->GetMaximum();
	YMax = max(YMax, ZJets_7TeVMax);
	double QCD_Mu_Pt20to30Max = Histo_QCD_Mu_Pt20to30->GetMaximum();
	YMax = max(YMax, QCD_Mu_Pt20to30Max);
	double InclusiveMu15Max = Histo_InclusiveMu15->GetMaximum();
	YMax = max(YMax, InclusiveMu15Max);
	double ZmumuJet_Pt0to15Max = Histo_ZmumuJet_Pt0to15->GetMaximum();
	YMax = max(YMax, ZmumuJet_Pt0to15Max);

	double dataMin = YMax;
	double PhotonJet_Pt15Min = YMax;
	double QCD_Pt15Min = YMax;
	double TTbarJets_TauolaMin = YMax;
	double WJets_7TeVMin = YMax;
	double ZJets_7TeVMin = YMax;
	double QCD_Mu_Pt20to30Min = YMax;
	double InclusiveMu15Min = YMax;
	double ZmumuJet_Pt0to15Min = YMax;
	double YMin = YMax;
	// Gets the actual minimum for each histogram, and not the unfilled bin if any
	for( int ibin=1 ; ibin<Histo_Data->GetNbinsX() ; ibin++ ){
		if( ((Histo_Data->GetBinContent(ibin))!=0) && ((Histo_Data->GetBinContent(ibin))<dataMin) ){
			dataMin = Histo_Data->GetBinContent(ibin);
		}
	}
	YMin = min(YMin, dataMin);
	for( int ibin=1 ; ibin<Histo_PhotonJet_Pt15->GetNbinsX() ; ibin++ ){
		if( ((Histo_PhotonJet_Pt15->GetBinContent(ibin))!=0) && ((Histo_PhotonJet_Pt15->GetBinContent(ibin))<PhotonJet_Pt15Min) ){
			PhotonJet_Pt15Min = Histo_PhotonJet_Pt15->GetBinContent(ibin);
		}
	}
	YMin = min(YMin, PhotonJet_Pt15Min);
	for( int ibin=1 ; ibin<Histo_QCD_Pt15->GetNbinsX() ; ibin++ ){
		if( ((Histo_QCD_Pt15->GetBinContent(ibin))!=0) && ((Histo_QCD_Pt15->GetBinContent(ibin))<QCD_Pt15Min) ){
			QCD_Pt15Min = Histo_QCD_Pt15->GetBinContent(ibin);
		}
	}
	YMin = min(YMin, QCD_Pt15Min);
	for( int ibin=1 ; ibin<Histo_TTbarJets_Tauola->GetNbinsX() ; ibin++ ){
		if( ((Histo_TTbarJets_Tauola->GetBinContent(ibin))!=0) && ((Histo_TTbarJets_Tauola->GetBinContent(ibin))<TTbarJets_TauolaMin) ){
			TTbarJets_TauolaMin = Histo_TTbarJets_Tauola->GetBinContent(ibin);
		}
	}
	YMin = min(YMin, TTbarJets_TauolaMin);
	for( int ibin=1 ; ibin<Histo_WJets_7TeV->GetNbinsX() ; ibin++ ){
		if( ((Histo_WJets_7TeV->GetBinContent(ibin))!=0) && ((Histo_WJets_7TeV->GetBinContent(ibin))<WJets_7TeVMin) ){
			WJets_7TeVMin = Histo_WJets_7TeV->GetBinContent(ibin);
		}
	}
	YMin = min(YMin, WJets_7TeVMin);
	for( int ibin=1 ; ibin<Histo_ZJets_7TeV->GetNbinsX() ; ibin++ ){
		if( ((Histo_ZJets_7TeV->GetBinContent(ibin))!=0) && ((Histo_ZJets_7TeV->GetBinContent(ibin))<ZJets_7TeVMin) ){
			ZJets_7TeVMin = Histo_ZJets_7TeV->GetBinContent(ibin);
		}
	}
	YMin = min(YMin, ZJets_7TeVMin);
	for( int ibin=1 ; ibin<Histo_QCD_Mu_Pt20to30->GetNbinsX() ; ibin++ ){
		if( ((Histo_QCD_Mu_Pt20to30->GetBinContent(ibin))!=0) && ((Histo_QCD_Mu_Pt20to30->GetBinContent(ibin))<QCD_Mu_Pt20to30Min) ){
			QCD_Mu_Pt20to30Min = Histo_QCD_Mu_Pt20to30->GetBinContent(ibin);
		}
	}
	YMin = min(YMin, QCD_Mu_Pt20to30Min);
	for( int ibin=1 ; ibin<Histo_InclusiveMu15->GetNbinsX() ; ibin++ ){
		if( ((Histo_InclusiveMu15->GetBinContent(ibin))!=0) && ((Histo_InclusiveMu15->GetBinContent(ibin))<InclusiveMu15Min) ){
			InclusiveMu15Min = Histo_InclusiveMu15->GetBinContent(ibin);
		}
	}
	YMin = min(YMin, InclusiveMu15Min);
	for( int ibin=1 ; ibin<Histo_ZmumuJet_Pt0to15->GetNbinsX() ; ibin++ ){
		if( ((Histo_ZmumuJet_Pt0to15->GetBinContent(ibin))!=0) && ((Histo_ZmumuJet_Pt0to15->GetBinContent(ibin))<ZmumuJet_Pt0to15Min) ){
			ZmumuJet_Pt0to15Min = Histo_ZmumuJet_Pt0to15->GetBinContent(ibin);
		}
	}
	YMin = min(YMin, ZmumuJet_Pt0to15Min);

//	cout << "YMax= "<< YMax << "\t\tYMin= " << YMin << endl;
	double YMin_lin = (double)YMin / (double)10.0;
//	double Range_lin = ((double)(YMax - YMin_lin)) / ((double)(0.8));
	double Range_lin = ((double)(YMax - YMin_lin)) / ((double)(1.0));
	double YMax_lin = 0.2*Range_lin + YMax;

//	double Range_lin = ((double)(YMax - YMin)) / ((double)(0.77));
//  double YMax_lin = 0.2*Range_lin + YMax;
//  double YMin_lin = max(YMin - 0.03*Range_lin, (double)YMin / (double)10.0);

  double Range_log = ((double)(log10(YMax) - log10(YMin))) / ((double)(0.77));
//	cout << "Range_lin= " << Range_lin << "\t\tRange_log= " << Range_log << endl;
  double YMax_log = pow(10.0, 0.2*Range_log + log10(YMax));
  double YMin_log = pow(10.0, log10(YMin) - 0.03*Range_log);
//	cout << "YMin_lin= " << YMin_lin << "\t\tYMax_lin= " << YMax_lin << endl;
//	cout << "YMin_log= " << YMin_log << "\t\tYMax_log= " << YMax_log << endl;


	// Setup the histo and canvas names and title
	string data_name = "Data_" + var + "_" + name;
	string mc_name = "MC_" + var + "_" + name;
	string canvas_name = "DataMC_" + var + "_" + name;
	std::ostringstream binWidthOSS;
	binWidthOSS << (double)Histo_Data->GetBinWidth(1);
	string binWidth = binWidthOSS.str();
	string YaxisTitle = "";
	if((Title.rfind("(") < Title.size()) && (Title.rfind(")") < Title.size())){
		string unit = Title.substr(Title.rfind("(")+1, Title.size()-Title.rfind("(")-2);
		YaxisTitle = "# events / " + binWidth + " " + unit;
	} else {
		YaxisTitle = "# events / " + binWidth;
	}
	Histo_Data->SetName(data_name.c_str());
	Histo_QCD_Pt15->SetName(mc_name.c_str());
	c1->SetName(canvas_name.c_str());
	c1->SetTitle(canvas_name.c_str());

	// Draw the comparison plots

	TLegend *legend = new TLegend(0.75, 0.80, 0.90, 0.93, "");
	legend->SetTextSize(0.025);
	legend->SetFillColor(kWhite);
	legend->SetLineColor(kWhite);
	legend->SetShadowColor(kWhite);

	// // First: draw the data to get correct Y-axis scale
	Histo_Data->GetXaxis()->SetTitle(Title.c_str());
	Histo_Data->GetYaxis()->SetTitle(YaxisTitle.c_str());
	Histo_Data->SetLineColor(kBlack);
	Histo_Data->SetMarkerColor(kBlack);
	Histo_Data->SetMarkerSize(0.7);
	Histo_Data->SetMarkerStyle(20);
	Histo_Data->SetMaximum(YMax_lin);
	Histo_Data->SetMinimum(YMin_lin);
//	Histo_Data->GetYaxis()->SetRangeUser(YMin_lin, YMax_lin);
	Histo_Data->Draw("E1");
	legend->AddEntry(Histo_Data->GetName(), "Data", "lp");

	// // Second: draw MC on the same canvas
	Histo_QCD_Pt15->SetLineColor(kBlack);
	Histo_QCD_Pt15->SetFillColor(kGreen+3);
	Histo_QCD_Pt15->SetFillStyle(3001);
	Histo_QCD_Pt15->SetMaximum(YMax_lin);
	Histo_QCD_Pt15->SetMinimum(YMin_lin);
//	Histo_QCD_Pt15->Draw("same");
//	legend->AddEntry(Histo_QCD_Pt15->GetName(), "QCD", "f");

  Histo_QCD_Mu_Pt20to30->SetLineColor(kBlack);
  Histo_QCD_Mu_Pt20to30->SetFillColor(kGreen);
  Histo_QCD_Mu_Pt20to30->SetFillStyle(3001);
  Histo_QCD_Mu_Pt20to30->SetMaximum(YMax_lin);
  Histo_QCD_Mu_Pt20to30->SetMinimum(YMin_lin);
  Histo_QCD_Mu_Pt20to30->Draw("same");
	legend->AddEntry(Histo_QCD_Mu_Pt20to30->GetName(), "QCD Mu", "f");

	Histo_InclusiveMu15->SetLineColor(kBlack);
	Histo_InclusiveMu15->SetFillColor(kGreen-6);
	Histo_InclusiveMu15->SetFillStyle(3001);
	Histo_InclusiveMu15->SetMaximum(YMax_lin);
	Histo_InclusiveMu15->SetMinimum(YMin_lin);
//	Histo_InclusiveMu15->Draw("same");	
//	legend->AddEntry(Histo_InclusiveMu15->GetName(), "InclusiveMu15", "f");

  Histo_ZmumuJet_Pt0to15->SetLineColor(kBlack);
  Histo_ZmumuJet_Pt0to15->SetFillColor(kRed);
  Histo_ZmumuJet_Pt0to15->SetFillStyle(3001);
  Histo_ZmumuJet_Pt0to15->SetMaximum(YMax_lin);
  Histo_ZmumuJet_Pt0to15->SetMinimum(YMin_lin);
  Histo_ZmumuJet_Pt0to15->Draw("same");
	legend->AddEntry(Histo_ZmumuJet_Pt0to15->GetName(), "ZmumuJet", "f");

  Histo_ZJets_7TeV->SetLineColor(kBlack);
  Histo_ZJets_7TeV->SetFillColor(kOrange);
  Histo_ZJets_7TeV->SetFillStyle(3001);
  Histo_ZJets_7TeV->SetMaximum(YMax_lin);
  Histo_ZJets_7TeV->SetMinimum(YMin_lin);
  Histo_ZJets_7TeV->Draw("same");
	legend->AddEntry(Histo_ZJets_7TeV->GetName(), "ZJets", "f");

  Histo_WJets_7TeV->SetLineColor(kBlack);
  Histo_WJets_7TeV->SetFillColor(kMagenta+3);
  Histo_WJets_7TeV->SetFillStyle(3001);
  Histo_WJets_7TeV->SetMaximum(YMax_lin);
  Histo_WJets_7TeV->SetMinimum(YMin_lin);
  Histo_WJets_7TeV->Draw("same");
	legend->AddEntry(Histo_WJets_7TeV->GetName(), "WJets", "f");

 	Histo_TTbarJets_Tauola->SetLineColor(kBlack);
  Histo_TTbarJets_Tauola->SetFillColor(kBlue);
  Histo_TTbarJets_Tauola->SetFillStyle(3001);
  Histo_TTbarJets_Tauola->SetMaximum(YMax_lin);
  Histo_TTbarJets_Tauola->SetMinimum(YMin_lin);
  Histo_TTbarJets_Tauola->Draw("same");
	legend->AddEntry(Histo_TTbarJets_Tauola->GetName(), "TTbarJets", "f");

	Histo_PhotonJet_Pt15->SetLineColor(kBlack);
	Histo_PhotonJet_Pt15->SetFillColor(kMagenta);
	Histo_PhotonJet_Pt15->SetFillStyle(3001);
	Histo_PhotonJet_Pt15->SetMaximum(YMax_lin);
	Histo_PhotonJet_Pt15->SetMinimum(YMin_lin);
	Histo_PhotonJet_Pt15->Draw("same");
	legend->AddEntry(Histo_PhotonJet_Pt15->GetName(), "PhotonJet", "f");

	// // Third: re-draw Data so that data appears in front of MC
	Histo_Data->Draw("E1same");

	// // Fourth: redraw axis so that axis appears in front of everything
	gPad->RedrawAxis();

	// // Fifth: draw legend
	legend->Draw();

	TLatex latexLabel;
	std::ostringstream intLumiString;
	intLumiString << setprecision (3) << fixed << integratedLuminosity;
	string intLumiText = "#intL= " + intLumiString.str() + " pb^{-1}";
  latexLabel.SetTextSize(0.03);
  latexLabel.SetNDC();
  latexLabel.DrawLatex(0.18, 0.90, "CMS Preliminary 2010");
  latexLabel.DrawLatex(0.18, 0.86, "#sqrt{s} = 7 TeV");
	latexLabel.DrawLatex(0.16, 0.82, intLumiText.c_str());

	// // Sixth: update canvas
	c1->Update();
	c1->Draw();

	// Print the canvas
	string PicName="Plots_TEST/gif/DataMC_" + var + "_" + name + ".gif";
	c1->Print(PicName.c_str());
	PicName="Plots_TEST/eps/DataMC_" + var + "_" + name + ".eps";
	c1->Print(PicName.c_str());
	string convert = "convert Plots_TEST/eps/DataMC_" + var + "_" + name + ".eps" + " Plots_TEST/pdf/DataMC_" + var + "_" + name + ".pdf";
	system(convert.c_str());
	if (inlog==true) {
		c1->cd(1);
		Histo_Data->SetMaximum(YMax_log);
		Histo_Data->SetMinimum(YMin_log);
		Histo_Data->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
		Histo_PhotonJet_Pt15->SetMaximum(YMax_log);
		Histo_PhotonJet_Pt15->SetMinimum(YMin_log);
		Histo_PhotonJet_Pt15->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
		Histo_QCD_Pt15->SetMaximum(YMax_log);
		Histo_QCD_Pt15->SetMinimum(YMin_log);
		Histo_QCD_Pt15->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
		Histo_TTbarJets_Tauola->SetMaximum(YMax_log);
		Histo_TTbarJets_Tauola->SetMinimum(YMin_log);
		Histo_TTbarJets_Tauola->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
		Histo_WJets_7TeV->SetMaximum(YMax_log);
		Histo_WJets_7TeV->SetMinimum(YMin_log);
		Histo_WJets_7TeV->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
		Histo_ZJets_7TeV->SetMaximum(YMax_log);
		Histo_ZJets_7TeV->SetMinimum(YMin_log);
		Histo_ZJets_7TeV->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
		Histo_QCD_Mu_Pt20to30->SetMaximum(YMax_log);
		Histo_QCD_Mu_Pt20to30->SetMinimum(YMin_log);
		Histo_QCD_Mu_Pt20to30->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
		Histo_InclusiveMu15->SetMaximum(YMax_log);
		Histo_InclusiveMu15->SetMinimum(YMin_log);
		Histo_InclusiveMu15->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
		Histo_ZmumuJet_Pt0to15->SetMaximum(YMax_log);
		Histo_ZmumuJet_Pt0to15->SetMinimum(YMin_log);
		Histo_ZmumuJet_Pt0to15->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
		c1->SetLogy(1);
		c1->Update();
		c1->Draw();
		string PicName_log="Plots_TEST/gif/DataMC_" + var + "_" + name + "_log.gif";
		c1->Print(PicName_log.c_str());
		PicName="Plots_TEST/eps/DataMC_" + var + "_" + name + "_log.eps";
	  c1->Print(PicName.c_str());
		string convert = "convert Plots_TEST/eps/DataMC_" + var + "_" + name + "_log.eps" + " Plots_TEST/pdf/DataMC_" + var + "_" + name + "_log.pdf";
	  system(convert.c_str());
		c1->SetLogy(0);
		c1->Update();
	} 

	// Clean the memory
	c1->Clear();
	legend->Clear();
	Histo_Data_temp->Delete();
	Histo_Data->Delete();
	Histo_PhotonJet_Pt15_temp->Delete();
	Histo_PhotonJet_Pt15->Delete();
	Histo_PhotonJet_Pt30_temp->Delete();
	Histo_PhotonJet_Pt30->Delete();
	Histo_PhotonJet_Pt170_temp->Delete();
	Histo_PhotonJet_Pt170->Delete();
	Histo_PhotonJet_Pt300_temp->Delete();
	Histo_PhotonJet_Pt300->Delete();
	Histo_QCD_Pt15_temp->Delete();
	Histo_QCD_Pt15->Delete();
	Histo_QCD_Pt30_temp->Delete();
	Histo_QCD_Pt30->Delete();
	Histo_QCD_Pt80_temp->Delete();
	Histo_QCD_Pt80->Delete();
	Histo_QCD_Pt170_temp->Delete();
	Histo_QCD_Pt170->Delete();
	Histo_QCD_Pt300_temp->Delete();
	Histo_QCD_Pt300->Delete();
	Histo_QCD_Pt470_temp->Delete();
	Histo_QCD_Pt470->Delete();
	Histo_TTbarJets_Tauola_temp->Delete();
	Histo_TTbarJets_Tauola->Delete();
	Histo_WJets_7TeV_temp->Delete();
	Histo_WJets_7TeV->Delete();
	Histo_ZJets_7TeV_temp->Delete();
	Histo_ZJets_7TeV->Delete();
	Histo_QCD_Mu_Pt20to30_temp->Delete();
	Histo_QCD_Mu_Pt20to30->Delete();
	Histo_QCD_Mu_Pt30to50_temp->Delete();
	Histo_QCD_Mu_Pt30to50->Delete();
	Histo_QCD_Mu_Pt50to80_temp->Delete();
	Histo_QCD_Mu_Pt50to80->Delete();
	Histo_QCD_Mu_Pt80to120_temp->Delete();
	Histo_QCD_Mu_Pt80to120->Delete();
	Histo_QCD_Mu_Pt120to170_temp->Delete();
	Histo_QCD_Mu_Pt120to170->Delete();
	Histo_QCD_Mu_Pt170toInf_temp->Delete();
	Histo_QCD_Mu_Pt170toInf->Delete();
	Histo_InclusiveMu15_temp->Delete();
	Histo_InclusiveMu15->Delete();
	Histo_ZmumuJet_Pt0to15_temp->Delete();
	Histo_ZmumuJet_Pt0to15->Delete();
	Histo_ZmumuJet_Pt15to20_temp->Delete();
	Histo_ZmumuJet_Pt15to20->Delete();
	Histo_ZmumuJet_Pt20to30_temp->Delete();
	Histo_ZmumuJet_Pt20to30->Delete();
	Histo_ZmumuJet_Pt30to50_temp->Delete();
	Histo_ZmumuJet_Pt30to50->Delete();
	Histo_ZmumuJet_Pt50to80_temp->Delete();
	Histo_ZmumuJet_Pt50to80->Delete();
	Histo_ZmumuJet_Pt80to120_temp->Delete();
	Histo_ZmumuJet_Pt80to120->Delete();
	Histo_ZmumuJet_Pt120to170_temp->Delete();
	Histo_ZmumuJet_Pt120to170->Delete();
	Histo_ZmumuJet_Pt170to230_temp->Delete();
	Histo_ZmumuJet_Pt170to230->Delete();
	Histo_ZmumuJet_Pt230to300_temp->Delete();
	Histo_ZmumuJet_Pt230to300->Delete();
	Histo_ZmumuJet_Pt300toInf_temp->Delete();
	Histo_ZmumuJet_Pt300toInf->Delete();

}
*/
	
//int plotDataMC_TDR_miniTree()
int main()
{
	gSystem->Load("/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/src/libToto.so");
	gROOT->ProcessLine(".x setTDRStyle.C");
	string Data = "Selected/noMuIso-hadEt/miniTree_DATA_ALL.root"; 
	string PhotonJet_Pt15 = "Selected/noMuIso-hadEt/PhotonJet_Pt15/miniTree_PhotonJet_Pt15_ALL.root"; 
	string PhotonJet_Pt30 = "Selected/noMuIso-hadEt/PhotonJet_Pt30/miniTree_PhotonJet_Pt30_ALL.root"; 
	string PhotonJet_Pt80 = "Selected/noMuIso-hadEt/PhotonJet_Pt80/miniTree_PhotonJet_Pt80_ALL.root"; 
	string PhotonJet_Pt170 = "Selected/noMuIso-hadEt/PhotonJet_Pt170/miniTree_PhotonJet_Pt170_ALL.root"; 
	string PhotonJet_Pt300 = "Selected/noMuIso-hadEt/PhotonJet_Pt300/miniTree_PhotonJet_Pt300_ALL.root"; 
	string QCD_Pt15 = "Selected/noMuIso-hadEt/QCD_Pt15/miniTree_QCD_Pt15_ALL.root"; 
	string QCD_Pt30 = "Selected/noMuIso-hadEt/QCD_Pt30/miniTree_QCD_Pt30_ALL.root"; 
	string QCD_Pt80 = "Selected/noMuIso-hadEt/QCD_Pt80/miniTree_QCD_Pt80_ALL.root"; 
	string QCD_Pt170 = "Selected/noMuIso-hadEt/QCD_Pt170/miniTree_QCD_Pt170_ALL.root"; 
	string QCD_Pt300 = "Selected/noMuIso-hadEt/QCD_Pt300/miniTree_QCD_Pt300_ALL.root"; 
	string QCD_Pt470 = "Selected/noMuIso-hadEt/QCD_Pt470/miniTree_QCD_Pt470_ALL.root"; 
	string TTbarJets_Tauola = "Selected/noMuIso-hadEt/TTbarJets_Tauola-madgraph/miniTree_TTbarJets_Tauola-madgraph_ALL.root";
	string WJets_7TeV = "Selected/noMuIso-hadEt/WJets_7TeV-madgraph-tauola/miniTree_WJets_7TeV-madgraph-tauola_ALL.root";
	string ZJets_7TeV = "Selected/noMuIso-hadEt/ZJets_7TeV-madgraph-tauola/miniTree_ZJets_7TeV-madgraph-tauola_ALL.root";
	string QCD_Mu_Pt20to30 = "Selected/noMuIso-hadEt/QCD_Mu_Pt20to30/miniTree_QCD_Mu_Pt20to30_ALL.root";
	string QCD_Mu_Pt30to50 = "Selected/noMuIso-hadEt/QCD_Mu_Pt30to50/miniTree_QCD_Mu_Pt30to50_ALL.root";
	string QCD_Mu_Pt50to80 = "Selected/noMuIso-hadEt/QCD_Mu_Pt50to80/miniTree_QCD_Mu_Pt50to80_ALL.root";
	string QCD_Mu_Pt80to120 = "Selected/noMuIso-hadEt/QCD_Mu_Pt80to120/miniTree_QCD_Mu_Pt80to120_ALL.root";
	string QCD_Mu_Pt120to170 = "Selected/noMuIso-hadEt/QCD_Mu_Pt120to170/miniTree_QCD_Mu_Pt120to170_ALL.root";
	string QCD_Mu_Pt170toInf = "Selected/noMuIso-hadEt/QCD_Mu_Pt170toInf/miniTree_QCD_Mu_Pt170toInf_ALL.root";
	string InclusiveMu15 = "Selected/noMuIso-hadEt/InclusiveMu15/miniTree_InclusiveMu15_ALL.root"; 
	string ZmumuJet_Pt0to15 = "Selected/noMuIso-hadEt/ZmumuJet_Pt0to15/miniTree_ZmumuJet_Pt0to15_ALL.root";
	string ZmumuJet_Pt15to20 = "Selected/noMuIso-hadEt/ZmumuJet_Pt15to20/miniTree_ZmumuJet_Pt15to20_ALL.root";
	string ZmumuJet_Pt20to30 = "Selected/noMuIso-hadEt/ZmumuJet_Pt20to30/miniTree_ZmumuJet_Pt20to30_ALL.root";
	string ZmumuJet_Pt30to50 = "Selected/noMuIso-hadEt/ZmumuJet_Pt30to50/miniTree_ZmumuJet_Pt30to50_ALL.root";
	string ZmumuJet_Pt50to80 = "Selected/noMuIso-hadEt/ZmumuJet_Pt50to80/miniTree_ZmumuJet_Pt50to80_ALL.root";
	string ZmumuJet_Pt80to120 = "Selected/noMuIso-hadEt/ZmumuJet_Pt80to120/miniTree_ZmumuJet_Pt80to120_ALL.root";
	string ZmumuJet_Pt120to170 = "Selected/noMuIso-hadEt/ZmumuJet_Pt120to170/miniTree_ZmumuJet_Pt120to170_ALL.root";
	string ZmumuJet_Pt170to230 = "Selected/noMuIso-hadEt/ZmumuJet_Pt170to230/miniTree_ZmumuJet_Pt170to230_ALL.root";
	string ZmumuJet_Pt230to300 = "Selected/noMuIso-hadEt/ZmumuJet_Pt230to300/miniTree_ZmumuJet_Pt230to300_ALL.root";
	string ZmumuJet_Pt300toInf = "Selected/noMuIso-hadEt/ZmumuJet_Pt300toInf/miniTree_ZmumuJet_Pt300toInf_ALL.root";
	
	TFile *Data_File = new TFile(Data.c_str());
	TTree* Data_miniTree = (TTree*) Data_File->Get("miniTree");
	TTree* Data_miniTree_allmuons = (TTree*) Data_File->Get("miniTree_allmuons");
	TTree* Data_miniTree_allphotons = (TTree*) Data_File->Get("miniTree_allphotons");
	TFile *PhotonJet_Pt15_File = new TFile(PhotonJet_Pt15.c_str());
	TTree* PhotonJet_Pt15_miniTree = (TTree*) PhotonJet_Pt15_File->Get("miniTree");
	TTree* PhotonJet_Pt15_miniTree_allmuons = (TTree*) PhotonJet_Pt15_File->Get("miniTree_allmuons");
	TTree* PhotonJet_Pt15_miniTree_allphotons = (TTree*) PhotonJet_Pt15_File->Get("miniTree_allphotons");
	TFile *PhotonJet_Pt30_File = new TFile(PhotonJet_Pt30.c_str());
	TTree* PhotonJet_Pt30_miniTree = (TTree*) PhotonJet_Pt30_File->Get("miniTree");
	TTree* PhotonJet_Pt30_miniTree_allmuons = (TTree*) PhotonJet_Pt30_File->Get("miniTree_allmuons");
	TTree* PhotonJet_Pt30_miniTree_allphotons = (TTree*) PhotonJet_Pt30_File->Get("miniTree_allphotons");
	TFile *PhotonJet_Pt80_File = new TFile(PhotonJet_Pt80.c_str());
	TTree* PhotonJet_Pt80_miniTree = (TTree*) PhotonJet_Pt80_File->Get("miniTree");
	TTree* PhotonJet_Pt80_miniTree_allmuons = (TTree*) PhotonJet_Pt80_File->Get("miniTree_allmuons");
	TTree* PhotonJet_Pt80_miniTree_allphotons = (TTree*) PhotonJet_Pt80_File->Get("miniTree_allphotons");
	TFile *PhotonJet_Pt170_File = new TFile(PhotonJet_Pt170.c_str());
	TTree* PhotonJet_Pt170_miniTree = (TTree*) PhotonJet_Pt170_File->Get("miniTree");
	TTree* PhotonJet_Pt170_miniTree_allmuons = (TTree*) PhotonJet_Pt170_File->Get("miniTree_allmuons");
	TTree* PhotonJet_Pt170_miniTree_allphotons = (TTree*) PhotonJet_Pt170_File->Get("miniTree_allphotons");
	TFile *PhotonJet_Pt300_File = new TFile(PhotonJet_Pt300.c_str());
	TTree* PhotonJet_Pt300_miniTree = (TTree*) PhotonJet_Pt300_File->Get("miniTree");
	TTree* PhotonJet_Pt300_miniTree_allmuons = (TTree*) PhotonJet_Pt300_File->Get("miniTree_allmuons");
	TTree* PhotonJet_Pt300_miniTree_allphotons = (TTree*) PhotonJet_Pt300_File->Get("miniTree_allphotons");
	TFile *QCD_Pt15_File = new TFile(QCD_Pt15.c_str());
	TTree* QCD_Pt15_miniTree = (TTree*) QCD_Pt15_File->Get("miniTree");
	TTree* QCD_Pt15_miniTree_allmuons = (TTree*) QCD_Pt15_File->Get("miniTree_allmuons");
	TTree* QCD_Pt15_miniTree_allphotons = (TTree*) QCD_Pt15_File->Get("miniTree_allphotons");
	TFile *QCD_Pt30_File = new TFile(QCD_Pt30.c_str());
	TTree* QCD_Pt30_miniTree = (TTree*) QCD_Pt30_File->Get("miniTree");
	TTree* QCD_Pt30_miniTree_allmuons = (TTree*) QCD_Pt30_File->Get("miniTree_allmuons");
	TTree* QCD_Pt30_miniTree_allphotons = (TTree*) QCD_Pt30_File->Get("miniTree_allphotons");
	TFile *QCD_Pt80_File = new TFile(QCD_Pt80.c_str());
	TTree* QCD_Pt80_miniTree = (TTree*) QCD_Pt80_File->Get("miniTree");
	TTree* QCD_Pt80_miniTree_allmuons = (TTree*) QCD_Pt80_File->Get("miniTree_allmuons");
	TTree* QCD_Pt80_miniTree_allphotons = (TTree*) QCD_Pt80_File->Get("miniTree_allphotons");
	TFile *QCD_Pt170_File = new TFile(QCD_Pt170.c_str());
	TTree* QCD_Pt170_miniTree = (TTree*) QCD_Pt170_File->Get("miniTree");
	TTree* QCD_Pt170_miniTree_allmuons = (TTree*) QCD_Pt170_File->Get("miniTree_allmuons");
	TTree* QCD_Pt170_miniTree_allphotons = (TTree*) QCD_Pt170_File->Get("miniTree_allphotons");
	TFile *QCD_Pt300_File = new TFile(QCD_Pt300.c_str());
	TTree* QCD_Pt300_miniTree = (TTree*) QCD_Pt300_File->Get("miniTree");
	TTree* QCD_Pt300_miniTree_allmuons = (TTree*) QCD_Pt300_File->Get("miniTree_allmuons");
	TTree* QCD_Pt300_miniTree_allphotons = (TTree*) QCD_Pt300_File->Get("miniTree_allphotons");
	TFile *QCD_Pt470_File = new TFile(QCD_Pt470.c_str());
	TTree* QCD_Pt470_miniTree = (TTree*) QCD_Pt470_File->Get("miniTree");
	TTree* QCD_Pt470_miniTree_allmuons = (TTree*) QCD_Pt470_File->Get("miniTree_allmuons");
	TTree* QCD_Pt470_miniTree_allphotons = (TTree*) QCD_Pt470_File->Get("miniTree_allphotons");
	TFile *TTbarJets_Tauola_File = new TFile(TTbarJets_Tauola.c_str());
	TTree* TTbarJets_Tauola_miniTree = (TTree*) TTbarJets_Tauola_File->Get("miniTree");
	TTree* TTbarJets_Tauola_miniTree_allmuons = (TTree*) TTbarJets_Tauola_File->Get("miniTree_allmuons");
	TTree* TTbarJets_Tauola_miniTree_allphotons = (TTree*) TTbarJets_Tauola_File->Get("miniTree_allphotons");
	TFile *WJets_7TeV_File = new TFile(WJets_7TeV.c_str());
	TTree* WJets_7TeV_miniTree = (TTree*) WJets_7TeV_File->Get("miniTree");
	TTree* WJets_7TeV_miniTree_allmuons = (TTree*) WJets_7TeV_File->Get("miniTree_allmuons");
	TTree* WJets_7TeV_miniTree_allphotons = (TTree*) WJets_7TeV_File->Get("miniTree_allphotons");
	TFile *ZJets_7TeV_File = new TFile(ZJets_7TeV.c_str());
	TTree* ZJets_7TeV_miniTree = (TTree*) ZJets_7TeV_File->Get("miniTree");
	TTree* ZJets_7TeV_miniTree_allmuons = (TTree*) ZJets_7TeV_File->Get("miniTree_allmuons");
	TTree* ZJets_7TeV_miniTree_allphotons = (TTree*) ZJets_7TeV_File->Get("miniTree_allphotons");
	TFile *QCD_Mu_Pt20to30_File = new TFile(QCD_Mu_Pt20to30.c_str());
	TTree* QCD_Mu_Pt20to30_miniTree = (TTree*) QCD_Mu_Pt20to30_File->Get("miniTree");
	TTree* QCD_Mu_Pt20to30_miniTree_allmuons = (TTree*) QCD_Mu_Pt20to30_File->Get("miniTree_allmuons");
	TTree* QCD_Mu_Pt20to30_miniTree_allphotons = (TTree*) QCD_Mu_Pt20to30_File->Get("miniTree_allphotons");
	TFile *QCD_Mu_Pt30to50_File = new TFile(QCD_Mu_Pt30to50.c_str());
	TTree* QCD_Mu_Pt30to50_miniTree = (TTree*) QCD_Mu_Pt30to50_File->Get("miniTree");
	TTree* QCD_Mu_Pt30to50_miniTree_allmuons = (TTree*) QCD_Mu_Pt30to50_File->Get("miniTree_allmuons");
	TTree* QCD_Mu_Pt30to50_miniTree_allphotons = (TTree*) QCD_Mu_Pt30to50_File->Get("miniTree_allphotons");
	TFile *QCD_Mu_Pt50to80_File = new TFile(QCD_Mu_Pt50to80.c_str());
	TTree* QCD_Mu_Pt50to80_miniTree = (TTree*) QCD_Mu_Pt50to80_File->Get("miniTree");
	TTree* QCD_Mu_Pt50to80_miniTree_allmuons = (TTree*) QCD_Mu_Pt50to80_File->Get("miniTree_allmuons");
	TTree* QCD_Mu_Pt50to80_miniTree_allphotons = (TTree*) QCD_Mu_Pt50to80_File->Get("miniTree_allphotons");
	TFile *QCD_Mu_Pt80to120_File = new TFile(QCD_Mu_Pt80to120.c_str());
	TTree* QCD_Mu_Pt80to120_miniTree = (TTree*) QCD_Mu_Pt80to120_File->Get("miniTree");
	TTree* QCD_Mu_Pt80to120_miniTree_allmuons = (TTree*) QCD_Mu_Pt80to120_File->Get("miniTree_allmuons");
	TTree* QCD_Mu_Pt80to120_miniTree_allphotons = (TTree*) QCD_Mu_Pt80to120_File->Get("miniTree_allphotons");
	TFile *QCD_Mu_Pt120to170_File = new TFile(QCD_Mu_Pt120to170.c_str());
	TTree* QCD_Mu_Pt120to170_miniTree = (TTree*) QCD_Mu_Pt120to170_File->Get("miniTree");
	TTree* QCD_Mu_Pt120to170_miniTree_allmuons = (TTree*) QCD_Mu_Pt120to170_File->Get("miniTree_allmuons");
	TTree* QCD_Mu_Pt120to170_miniTree_allphotons = (TTree*) QCD_Mu_Pt120to170_File->Get("miniTree_allphotons");
	TFile *QCD_Mu_Pt170toInf_File = new TFile(QCD_Mu_Pt170toInf.c_str());
	TTree* QCD_Mu_Pt170toInf_miniTree = (TTree*) QCD_Mu_Pt170toInf_File->Get("miniTree");
	TTree* QCD_Mu_Pt170toInf_miniTree_allmuons = (TTree*) QCD_Mu_Pt170toInf_File->Get("miniTree_allmuons");
	TTree* QCD_Mu_Pt170toInf_miniTree_allphotons = (TTree*) QCD_Mu_Pt170toInf_File->Get("miniTree_allphotons");
	TFile *InclusiveMu15_File = new TFile(InclusiveMu15.c_str());
	TTree* InclusiveMu15_miniTree = (TTree*) InclusiveMu15_File->Get("miniTree");
	TTree* InclusiveMu15_miniTree_allmuons = (TTree*) InclusiveMu15_File->Get("miniTree_allmuons");
	TTree* InclusiveMu15_miniTree_allphotons = (TTree*) InclusiveMu15_File->Get("miniTree_allphotons");
	TFile *ZmumuJet_Pt0to15_File = new TFile(ZmumuJet_Pt0to15.c_str());
	TTree* ZmumuJet_Pt0to15_miniTree = (TTree*) ZmumuJet_Pt0to15_File->Get("miniTree");
	TTree* ZmumuJet_Pt0to15_miniTree_allmuons = (TTree*) ZmumuJet_Pt0to15_File->Get("miniTree_allmuons");
	TTree* ZmumuJet_Pt0to15_miniTree_allphotons = (TTree*) ZmumuJet_Pt0to15_File->Get("miniTree_allphotons");
	TFile *ZmumuJet_Pt15to20_File = new TFile(ZmumuJet_Pt15to20.c_str());
	TTree* ZmumuJet_Pt15to20_miniTree = (TTree*) ZmumuJet_Pt15to20_File->Get("miniTree");
	TTree* ZmumuJet_Pt15to20_miniTree_allmuons = (TTree*) ZmumuJet_Pt15to20_File->Get("miniTree_allmuons");
	TTree* ZmumuJet_Pt15to20_miniTree_allphotons = (TTree*) ZmumuJet_Pt15to20_File->Get("miniTree_allphotons");
	TFile *ZmumuJet_Pt20to30_File = new TFile(ZmumuJet_Pt20to30.c_str());
	TTree* ZmumuJet_Pt20to30_miniTree = (TTree*) ZmumuJet_Pt20to30_File->Get("miniTree");
	TTree* ZmumuJet_Pt20to30_miniTree_allmuons = (TTree*) ZmumuJet_Pt20to30_File->Get("miniTree_allmuons");
	TTree* ZmumuJet_Pt20to30_miniTree_allphotons = (TTree*) ZmumuJet_Pt20to30_File->Get("miniTree_allphotons");
	TFile *ZmumuJet_Pt30to50_File = new TFile(ZmumuJet_Pt30to50.c_str());
	TTree* ZmumuJet_Pt30to50_miniTree = (TTree*) ZmumuJet_Pt30to50_File->Get("miniTree");
	TTree* ZmumuJet_Pt30to50_miniTree_allmuons = (TTree*) ZmumuJet_Pt30to50_File->Get("miniTree_allmuons");
	TTree* ZmumuJet_Pt30to50_miniTree_allphotons = (TTree*) ZmumuJet_Pt30to50_File->Get("miniTree_allphotons");
	TFile *ZmumuJet_Pt50to80_File = new TFile(ZmumuJet_Pt50to80.c_str());
	TTree* ZmumuJet_Pt50to80_miniTree = (TTree*) ZmumuJet_Pt50to80_File->Get("miniTree");
	TTree* ZmumuJet_Pt50to80_miniTree_allmuons = (TTree*) ZmumuJet_Pt50to80_File->Get("miniTree_allmuons");
	TTree* ZmumuJet_Pt50to80_miniTree_allphotons = (TTree*) ZmumuJet_Pt50to80_File->Get("miniTree_allphotons");
	TFile *ZmumuJet_Pt80to120_File = new TFile(ZmumuJet_Pt80to120.c_str());
	TTree* ZmumuJet_Pt80to120_miniTree = (TTree*) ZmumuJet_Pt80to120_File->Get("miniTree");
	TTree* ZmumuJet_Pt80to120_miniTree_allmuons = (TTree*) ZmumuJet_Pt80to120_File->Get("miniTree_allmuons");
	TTree* ZmumuJet_Pt80to120_miniTree_allphotons = (TTree*) ZmumuJet_Pt80to120_File->Get("miniTree_allphotons");
	TFile *ZmumuJet_Pt120to170_File = new TFile(ZmumuJet_Pt120to170.c_str());
	TTree* ZmumuJet_Pt120to170_miniTree = (TTree*) ZmumuJet_Pt120to170_File->Get("miniTree");
	TTree* ZmumuJet_Pt120to170_miniTree_allmuons = (TTree*) ZmumuJet_Pt120to170_File->Get("miniTree_allmuons");
	TTree* ZmumuJet_Pt120to170_miniTree_allphotons = (TTree*) ZmumuJet_Pt120to170_File->Get("miniTree_allphotons");
	TFile *ZmumuJet_Pt170to230_File = new TFile(ZmumuJet_Pt170to230.c_str());
	TTree* ZmumuJet_Pt170to230_miniTree = (TTree*) ZmumuJet_Pt170to230_File->Get("miniTree");
	TTree* ZmumuJet_Pt170to230_miniTree_allmuons = (TTree*) ZmumuJet_Pt170to230_File->Get("miniTree_allmuons");
	TTree* ZmumuJet_Pt170to230_miniTree_allphotons = (TTree*) ZmumuJet_Pt170to230_File->Get("miniTree_allphotons");
	TFile *ZmumuJet_Pt230to300_File = new TFile(ZmumuJet_Pt230to300.c_str());
	TTree* ZmumuJet_Pt230to300_miniTree = (TTree*) ZmumuJet_Pt230to300_File->Get("miniTree");
	TTree* ZmumuJet_Pt230to300_miniTree_allmuons = (TTree*) ZmumuJet_Pt230to300_File->Get("miniTree_allmuons");
	TTree* ZmumuJet_Pt230to300_miniTree_allphotons = (TTree*) ZmumuJet_Pt230to300_File->Get("miniTree_allphotons");
	TFile *ZmumuJet_Pt300toInf_File = new TFile(ZmumuJet_Pt300toInf.c_str());
	TTree* ZmumuJet_Pt300toInf_miniTree = (TTree*) ZmumuJet_Pt300toInf_File->Get("miniTree");
	TTree* ZmumuJet_Pt300toInf_miniTree_allmuons = (TTree*) ZmumuJet_Pt300toInf_File->Get("miniTree_allmuons");
	TTree* ZmumuJet_Pt300toInf_miniTree_allphotons = (TTree*) ZmumuJet_Pt300toInf_File->Get("miniTree_allphotons");


	TCanvas *c1 = new TCanvas("Default", "Default");

// NOTES:
// NO PHOTON/MUON INFORMATION IS FILLED IN BEFORE 2B
	vector<string> set_of_cuts;
	vector<string> name;
//	set_of_cuts.push_back("isBeforeAllCuts");
//	name.push_back("00Before");
//	set_of_cuts.push_back("isAfterCutPthatFilter");
//	name.push_back("0AfterCutPthatFilter");
//	set_of_cuts.push_back("isAfterCut1a");
//	name.push_back("After1a");
//	set_of_cuts.push_back("isAfterCut1b");
//	name.push_back("After1b");
//	set_of_cuts.push_back("isAfterCut1c");
//	name.push_back("After1c");
//	set_of_cuts.push_back("isAfterCut1d");
//	name.push_back("After1d");
//	set_of_cuts.push_back("isAfterCut1e");
//	name.push_back("After1e");
//	set_of_cuts.push_back("isAfterCut2a");
//	name.push_back("After2a");
//	set_of_cuts.push_back("isAfterCut2b");
//	name.push_back("After2b");
//	set_of_cuts.push_back("isAfterCut2c");
//	name.push_back("After2c");
//	set_of_cuts.push_back("isAfterCut3");
//  name.push_back("After3");
//	set_of_cuts.push_back("isAfterCut4");
//  name.push_back("After4");
//	set_of_cuts.push_back("isAfterCut5");
//  name.push_back("After5");
//	set_of_cuts.push_back("isAfterCut6");
//  name.push_back("After6");
//	set_of_cuts.push_back("isAfterCut7");
//  name.push_back("After7");
//	set_of_cuts.push_back("isAfterCut8");
//  name.push_back("After8");

/*	set_of_cuts.push_back("isSelected");
  name.push_back("SELECTED");
	set_of_cuts.push_back("isSelected && Mmumugamma < 95.2 && Mmumugamma > 87.2");
  name.push_back("SELECTED_restrained_masswindow");
*/

	for(int i=0; i<set_of_cuts.size() ; i++){

		DrawDataMCplot_TH1I(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "NbMuons", "(10,0,10)", set_of_cuts[i], name[i], "# of muons", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "NbPhotons", "(10,0,10)", set_of_cuts[i], name[i], "# of photons", true, false, c1);

		DrawDataMCplot(Data_miniTree_allmuons, QCD_Pt15_miniTree_allmuons, QCD_Pt30_miniTree_allmuons, QCD_Pt80_miniTree_allmuons, QCD_Pt170_miniTree_allmuons, QCD_Pt300_miniTree_allmuons, QCD_Pt470_miniTree_allmuons, PhotonJet_Pt15_miniTree_allmuons, PhotonJet_Pt30_miniTree_allmuons, PhotonJet_Pt80_miniTree_allmuons, PhotonJet_Pt170_miniTree_allmuons, PhotonJet_Pt300_miniTree_allmuons, TTbarJets_Tauola_miniTree_allmuons, WJets_7TeV_miniTree_allmuons, ZJets_7TeV_miniTree_allmuons, QCD_Mu_Pt20to30_miniTree_allmuons, QCD_Mu_Pt30to50_miniTree_allmuons, QCD_Mu_Pt50to80_miniTree_allmuons, QCD_Mu_Pt80to120_miniTree_allmuons, QCD_Mu_Pt120to170_miniTree_allmuons, QCD_Mu_Pt170toInf_miniTree_allmuons, InclusiveMu15_miniTree_allmuons, ZmumuJet_Pt0to15_miniTree_allmuons, ZmumuJet_Pt15to20_miniTree_allmuons, ZmumuJet_Pt20to30_miniTree_allmuons, ZmumuJet_Pt30to50_miniTree_allmuons, ZmumuJet_Pt50to80_miniTree_allmuons, ZmumuJet_Pt80to120_miniTree_allmuons, ZmumuJet_Pt120to170_miniTree_allmuons, ZmumuJet_Pt170to230_miniTree_allmuons, ZmumuJet_Pt230to300_miniTree_allmuons, ZmumuJet_Pt300toInf_miniTree_allmuons, "Pt_allMuons", "(100,0,100)", set_of_cuts[i], name[i], "p_{T_{#mu}} (GeV)", true, false, c1);
		DrawDataMCplot(Data_miniTree_allmuons, QCD_Pt15_miniTree_allmuons, QCD_Pt30_miniTree_allmuons, QCD_Pt80_miniTree_allmuons, QCD_Pt170_miniTree_allmuons, QCD_Pt300_miniTree_allmuons, QCD_Pt470_miniTree_allmuons, PhotonJet_Pt15_miniTree_allmuons, PhotonJet_Pt30_miniTree_allmuons, PhotonJet_Pt80_miniTree_allmuons, PhotonJet_Pt170_miniTree_allmuons, PhotonJet_Pt300_miniTree_allmuons, TTbarJets_Tauola_miniTree_allmuons, WJets_7TeV_miniTree_allmuons, ZJets_7TeV_miniTree_allmuons, QCD_Mu_Pt20to30_miniTree_allmuons, QCD_Mu_Pt30to50_miniTree_allmuons, QCD_Mu_Pt50to80_miniTree_allmuons, QCD_Mu_Pt80to120_miniTree_allmuons, QCD_Mu_Pt120to170_miniTree_allmuons, QCD_Mu_Pt170toInf_miniTree_allmuons, InclusiveMu15_miniTree_allmuons, ZmumuJet_Pt0to15_miniTree_allmuons, ZmumuJet_Pt15to20_miniTree_allmuons, ZmumuJet_Pt20to30_miniTree_allmuons, ZmumuJet_Pt30to50_miniTree_allmuons, ZmumuJet_Pt50to80_miniTree_allmuons, ZmumuJet_Pt80to120_miniTree_allmuons, ZmumuJet_Pt120to170_miniTree_allmuons, ZmumuJet_Pt170to230_miniTree_allmuons, ZmumuJet_Pt230to300_miniTree_allmuons, ZmumuJet_Pt300toInf_miniTree_allmuons, "Phi_allMuons", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi_{#mu}", true, false, c1);
		DrawDataMCplot(Data_miniTree_allmuons, QCD_Pt15_miniTree_allmuons, QCD_Pt30_miniTree_allmuons, QCD_Pt80_miniTree_allmuons, QCD_Pt170_miniTree_allmuons, QCD_Pt300_miniTree_allmuons, QCD_Pt470_miniTree_allmuons, PhotonJet_Pt15_miniTree_allmuons, PhotonJet_Pt30_miniTree_allmuons, PhotonJet_Pt80_miniTree_allmuons, PhotonJet_Pt170_miniTree_allmuons, PhotonJet_Pt300_miniTree_allmuons, TTbarJets_Tauola_miniTree_allmuons, WJets_7TeV_miniTree_allmuons, ZJets_7TeV_miniTree_allmuons, QCD_Mu_Pt20to30_miniTree_allmuons, QCD_Mu_Pt30to50_miniTree_allmuons, QCD_Mu_Pt50to80_miniTree_allmuons, QCD_Mu_Pt80to120_miniTree_allmuons, QCD_Mu_Pt120to170_miniTree_allmuons, QCD_Mu_Pt170toInf_miniTree_allmuons, InclusiveMu15_miniTree_allmuons, ZmumuJet_Pt0to15_miniTree_allmuons, ZmumuJet_Pt15to20_miniTree_allmuons, ZmumuJet_Pt20to30_miniTree_allmuons, ZmumuJet_Pt30to50_miniTree_allmuons, ZmumuJet_Pt50to80_miniTree_allmuons, ZmumuJet_Pt80to120_miniTree_allmuons, ZmumuJet_Pt120to170_miniTree_allmuons, ZmumuJet_Pt170to230_miniTree_allmuons, ZmumuJet_Pt230to300_miniTree_allmuons, ZmumuJet_Pt300toInf_miniTree_allmuons, "Eta_allMuons", "(50,-3.0,3.0)", set_of_cuts[i], name[i], "#eta_{#mu}", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree_allmuons, QCD_Pt15_miniTree_allmuons, QCD_Pt30_miniTree_allmuons, QCD_Pt80_miniTree_allmuons, QCD_Pt170_miniTree_allmuons, QCD_Pt300_miniTree_allmuons, QCD_Pt470_miniTree_allmuons, PhotonJet_Pt15_miniTree_allmuons, PhotonJet_Pt30_miniTree_allmuons, PhotonJet_Pt80_miniTree_allmuons, PhotonJet_Pt170_miniTree_allmuons, PhotonJet_Pt300_miniTree_allmuons, TTbarJets_Tauola_miniTree_allmuons, WJets_7TeV_miniTree_allmuons, ZJets_7TeV_miniTree_allmuons, QCD_Mu_Pt20to30_miniTree_allmuons, QCD_Mu_Pt30to50_miniTree_allmuons, QCD_Mu_Pt50to80_miniTree_allmuons, QCD_Mu_Pt80to120_miniTree_allmuons, QCD_Mu_Pt120to170_miniTree_allmuons, QCD_Mu_Pt170toInf_miniTree_allmuons, InclusiveMu15_miniTree_allmuons, ZmumuJet_Pt0to15_miniTree_allmuons, ZmumuJet_Pt15to20_miniTree_allmuons, ZmumuJet_Pt20to30_miniTree_allmuons, ZmumuJet_Pt30to50_miniTree_allmuons, ZmumuJet_Pt50to80_miniTree_allmuons, ZmumuJet_Pt80to120_miniTree_allmuons, ZmumuJet_Pt120to170_miniTree_allmuons, ZmumuJet_Pt170to230_miniTree_allmuons, ZmumuJet_Pt230to300_miniTree_allmuons, ZmumuJet_Pt300toInf_miniTree_allmuons, "Charge_allMuons", "(20,-2,2)", set_of_cuts[i], name[i], "Charge_{#mu}", true, false, c1);

		DrawDataMCplot(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, ZmumuJet_Pt0to15_miniTree_allphotons, ZmumuJet_Pt15to20_miniTree_allphotons, ZmumuJet_Pt20to30_miniTree_allphotons, ZmumuJet_Pt30to50_miniTree_allphotons, ZmumuJet_Pt50to80_miniTree_allphotons, ZmumuJet_Pt80to120_miniTree_allphotons, ZmumuJet_Pt120to170_miniTree_allphotons, ZmumuJet_Pt170to230_miniTree_allphotons, ZmumuJet_Pt230to300_miniTree_allphotons, ZmumuJet_Pt300toInf_miniTree_allphotons, "Pt_allPhotons", "(100,0,100)", set_of_cuts[i], name[i], "p_{T_{#gamma}} (GeV)", true, false, c1);
		DrawDataMCplot(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, ZmumuJet_Pt0to15_miniTree_allphotons, ZmumuJet_Pt15to20_miniTree_allphotons, ZmumuJet_Pt20to30_miniTree_allphotons, ZmumuJet_Pt30to50_miniTree_allphotons, ZmumuJet_Pt50to80_miniTree_allphotons, ZmumuJet_Pt80to120_miniTree_allphotons, ZmumuJet_Pt120to170_miniTree_allphotons, ZmumuJet_Pt170to230_miniTree_allphotons, ZmumuJet_Pt230to300_miniTree_allphotons, ZmumuJet_Pt300toInf_miniTree_allphotons, "Phi_allPhotons", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi_{#gamma}", true, false, c1);
		DrawDataMCplot(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, ZmumuJet_Pt0to15_miniTree_allphotons, ZmumuJet_Pt15to20_miniTree_allphotons, ZmumuJet_Pt20to30_miniTree_allphotons, ZmumuJet_Pt30to50_miniTree_allphotons, ZmumuJet_Pt50to80_miniTree_allphotons, ZmumuJet_Pt80to120_miniTree_allphotons, ZmumuJet_Pt120to170_miniTree_allphotons, ZmumuJet_Pt170to230_miniTree_allphotons, ZmumuJet_Pt230to300_miniTree_allphotons, ZmumuJet_Pt300toInf_miniTree_allphotons, "Eta_allPhotons", "(50,-3.0,3.0)", set_of_cuts[i], name[i], "#eta_{#gamma}", true, false, c1);
//FIXME		DrawDataMCplot(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, ZmumuJet_Pt0to15_miniTree_allphotons, ZmumuJet_Pt15to20_miniTree_allphotons, ZmumuJet_Pt20to30_miniTree_allphotons, ZmumuJet_Pt30to50_miniTree_allphotons, ZmumuJet_Pt50to80_miniTree_allphotons, ZmumuJet_Pt80to120_miniTree_allphotons, ZmumuJet_Pt120to170_miniTree_allphotons, ZmumuJet_Pt170to230_miniTree_allphotons, ZmumuJet_Pt230to300_miniTree_allphotons, ZmumuJet_Pt300toInf_miniTree_allphotons, "Cross_allPhotons", "(50,-1.0,1.5)", set_of_cuts[i], name[i], "cross_{#gamma}", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, ZmumuJet_Pt0to15_miniTree_allphotons, ZmumuJet_Pt15to20_miniTree_allphotons, ZmumuJet_Pt20to30_miniTree_allphotons, ZmumuJet_Pt30to50_miniTree_allphotons, ZmumuJet_Pt50to80_miniTree_allphotons, ZmumuJet_Pt80to120_miniTree_allphotons, ZmumuJet_Pt120to170_miniTree_allphotons, ZmumuJet_Pt170to230_miniTree_allphotons, ZmumuJet_Pt230to300_miniTree_allphotons, ZmumuJet_Pt300toInf_miniTree_allphotons, "isEB_allPhotons", "(20,-1,2)", set_of_cuts[i], name[i], "#gamma isEB", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, ZmumuJet_Pt0to15_miniTree_allphotons, ZmumuJet_Pt15to20_miniTree_allphotons, ZmumuJet_Pt20to30_miniTree_allphotons, ZmumuJet_Pt30to50_miniTree_allphotons, ZmumuJet_Pt50to80_miniTree_allphotons, ZmumuJet_Pt80to120_miniTree_allphotons, ZmumuJet_Pt120to170_miniTree_allphotons, ZmumuJet_Pt170to230_miniTree_allphotons, ZmumuJet_Pt230to300_miniTree_allphotons, ZmumuJet_Pt300toInf_miniTree_allphotons, "isEE_allPhotons", "(20,-1,2)", set_of_cuts[i], name[i], "#gamma isEE", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, ZmumuJet_Pt0to15_miniTree_allphotons, ZmumuJet_Pt15to20_miniTree_allphotons, ZmumuJet_Pt20to30_miniTree_allphotons, ZmumuJet_Pt30to50_miniTree_allphotons, ZmumuJet_Pt50to80_miniTree_allphotons, ZmumuJet_Pt80to120_miniTree_allphotons, ZmumuJet_Pt120to170_miniTree_allphotons, ZmumuJet_Pt170to230_miniTree_allphotons, ZmumuJet_Pt230to300_miniTree_allphotons, ZmumuJet_Pt300toInf_miniTree_allphotons, "isEEM_allPhotons", "(20,-1,2)", set_of_cuts[i], name[i], "#gamma isEEM", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, ZmumuJet_Pt0to15_miniTree_allphotons, ZmumuJet_Pt15to20_miniTree_allphotons, ZmumuJet_Pt20to30_miniTree_allphotons, ZmumuJet_Pt30to50_miniTree_allphotons, ZmumuJet_Pt50to80_miniTree_allphotons, ZmumuJet_Pt80to120_miniTree_allphotons, ZmumuJet_Pt120to170_miniTree_allphotons, ZmumuJet_Pt170to230_miniTree_allphotons, ZmumuJet_Pt230to300_miniTree_allphotons, ZmumuJet_Pt300toInf_miniTree_allphotons, "isEEP_allPhotons", "(20,-1,2)", set_of_cuts[i], name[i], "#gamma isEEP", true, false, c1);

		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonL_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{leading} (GeV)", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonS_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{subleading} (GeV)", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonL_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonS_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{subleading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonL_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonS_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{subleading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonL_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonS_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonF_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{far} (GeV)", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonN_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{near} (GeV)", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonF_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonN_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonF_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonN_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonF_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "MuonN_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{near}", true, false, c1);

		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "Mmumu", "(100,0,300)", set_of_cuts[i], name[i], "M_{#mu#mu} (GeV)", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "Mmumugamma", "(100,0,300)", set_of_cuts[i], name[i], "M_{#mu#mu#gamma} (GeV)", true, false, c1);
	

		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "deltaRNear", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{near})", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "deltaRFar", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{far})", true, false, c1);
//		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "deltaRPlus", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{plus})", true, false, c1);
//		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "deltaRMinus", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{minus})", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "deltaRLeading", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{leading})", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "deltaRSubleading", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{subleading})", true, false, c1);

		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "Photon_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta of photon", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "Photon_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi of photon", true, false, c1);

		DrawDataMCplot_TH1I(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "Photon_isEB", "(10,-1,2)", set_of_cuts[i], name[i], "photon is in barrel", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "Photon_isEE", "(10,-1,2)", set_of_cuts[i], name[i], "photon is in endcap", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "Photon_isEEP", "(10,-1,2)", set_of_cuts[i], name[i], "photon is in endcap plus", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "Photon_isEEM", "(10,-1,2)", set_of_cuts[i], name[i], "photon is in endcap minus", true, false, c1);

		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "Photon_E", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon Energy (GeV)", true, false, c1);
		DrawDataMCplot(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "Photon_Et", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon Et (GeV)", true, false, c1);

		DrawDataMCplot_TH2F(Data_miniTree, QCD_Pt15_miniTree, QCD_Pt30_miniTree, QCD_Pt80_miniTree, QCD_Pt170_miniTree, QCD_Pt300_miniTree, QCD_Pt470_miniTree, PhotonJet_Pt15_miniTree, PhotonJet_Pt30_miniTree, PhotonJet_Pt80_miniTree, PhotonJet_Pt170_miniTree, PhotonJet_Pt300_miniTree, TTbarJets_Tauola_miniTree, WJets_7TeV_miniTree, ZJets_7TeV_miniTree, QCD_Mu_Pt20to30_miniTree, QCD_Mu_Pt30to50_miniTree, QCD_Mu_Pt50to80_miniTree, QCD_Mu_Pt80to120_miniTree, QCD_Mu_Pt120to170_miniTree, QCD_Mu_Pt170toInf_miniTree, InclusiveMu15_miniTree, ZmumuJet_Pt0to15_miniTree, ZmumuJet_Pt15to20_miniTree, ZmumuJet_Pt20to30_miniTree, ZmumuJet_Pt30to50_miniTree, ZmumuJet_Pt50to80_miniTree, ZmumuJet_Pt80to120_miniTree, ZmumuJet_Pt120to170_miniTree, ZmumuJet_Pt170to230_miniTree, ZmumuJet_Pt230to300_miniTree, ZmumuJet_Pt300toInf_miniTree, "Mmumu", "Mmumugamma", "(900,0,300,900,0,300)", set_of_cuts[i], name[i], "M_{#mu#mu} (GeV)", "M_{#mu#mu#gamma} (GeV)", false, false, c1);
	}
/*
	set_of_cuts.clear();
	name.clear();
	set_of_cuts.push_back("isBeforeAllCuts && isEB_allPhotons");
	name.push_back("BeforeEB");
	set_of_cuts.push_back("isAfterCut1a && isEB_allPhotons");
	name.push_back("After1aEB");
	set_of_cuts.push_back("isAfterCut1b && isEB_allPhotons");
	name.push_back("After1bEB");
	set_of_cuts.push_back("isAfterCut1c && isEB_allPhotons");
	name.push_back("After1cEB");
	set_of_cuts.push_back("isAfterCut1d && isEB_allPhotons");
	name.push_back("After1dEB");
	set_of_cuts.push_back("isAfterCut1e && isEB_allPhotons");
	name.push_back("After1eEB");
	set_of_cuts.push_back("isAfterCut2a && isEB_allPhotons");
	name.push_back("After2aEB");
	set_of_cuts.push_back("isAfterCut2b && isEB_allPhotons");
	name.push_back("After2bEB");
	set_of_cuts.push_back("isAfterCut2c && isEB_allPhotons");
	name.push_back("After2cEB");
	set_of_cuts.push_back("isBeforeAllCuts && isEE_allPhotons");
	name.push_back("BeforeEE");
	set_of_cuts.push_back("isAfterCut1a && isEE_allPhotons");
	name.push_back("After1aEE");
	set_of_cuts.push_back("isAfterCut1b && isEE_allPhotons");
	name.push_back("After1bEE");
	set_of_cuts.push_back("isAfterCut1c && isEE_allPhotons");
	name.push_back("After1cEE");
	set_of_cuts.push_back("isAfterCut1d && isEE_allPhotons");
	name.push_back("After1dEE");
	set_of_cuts.push_back("isAfterCut1e && isEE_allPhotons");
	name.push_back("After1eEE");
	set_of_cuts.push_back("isAfterCut2a && isEE_allPhotons");
	name.push_back("After2aEE");
	set_of_cuts.push_back("isAfterCut2b && isEE_allPhotons");
	name.push_back("After2bEE");
	set_of_cuts.push_back("isAfterCut2c && isEE_allPhotons");
	name.push_back("After2cEE");
	set_of_cuts.push_back("isBeforeAllCuts && isEEM_allPhotons");
	name.push_back("BeforeEEM");
	set_of_cuts.push_back("isAfterCut1a && isEEM_allPhotons");
	name.push_back("After1aEEM");
	set_of_cuts.push_back("isAfterCut1b && isEEM_allPhotons");
	name.push_back("After1bEEM");
	set_of_cuts.push_back("isAfterCut1c && isEEM_allPhotons");
	name.push_back("After1cEEM");
	set_of_cuts.push_back("isAfterCut1d && isEEM_allPhotons");
	name.push_back("After1dEEM");
	set_of_cuts.push_back("isAfterCut1e && isEEM_allPhotons");
	name.push_back("After1eEEM");
	set_of_cuts.push_back("isAfterCut2a && isEEM_allPhotons");
	name.push_back("After2aEEM");
	set_of_cuts.push_back("isAfterCut2b && isEEM_allPhotons");
	name.push_back("After2bEEM");
	set_of_cuts.push_back("isAfterCut2c && isEEM_allPhotons");
	name.push_back("After2cEEM");
	set_of_cuts.push_back("isBeforeAllCuts && isEEP_allPhotons");
	name.push_back("BeforeEEP");
	set_of_cuts.push_back("isAfterCut1a && isEEP_allPhotons");
	name.push_back("After1aEEP");
	set_of_cuts.push_back("isAfterCut1b && isEEP_allPhotons");
	name.push_back("After1bEEP");
	set_of_cuts.push_back("isAfterCut1c && isEEP_allPhotons");
	name.push_back("After1cEEP");
	set_of_cuts.push_back("isAfterCut1d && isEEP_allPhotons");
	name.push_back("After1dEEP");
	set_of_cuts.push_back("isAfterCut1e && isEEP_allPhotons");
	name.push_back("After1eEEP");
	set_of_cuts.push_back("isAfterCut2a && isEEP_allPhotons");
	name.push_back("After2aEEP");
	set_of_cuts.push_back("isAfterCut2b && isEEP_allPhotons");
	name.push_back("After2bEEP");
	set_of_cuts.push_back("isAfterCut2c && isEEP_allPhotons");
	name.push_back("After2cEEP");

	for(int i=0; i<set_of_cuts.size() ; i++){
		DrawDataMCplot(Data_miniTree_allphotons, MC_miniTree_allphotons, "Pt_allPhotons", "(100,0,100)", set_of_cuts[i], name[i], "p_{T_{#gamma}}", true, false, c1);
		DrawDataMCplot(Data_miniTree_allphotons, MC_miniTree_allphotons, "Phi_allPhotons", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi_{#gamma}", true, false, c1);
		DrawDataMCplot(Data_miniTree_allphotons, MC_miniTree_allphotons, "Eta_allPhotons", "(50,-3.0,3.0)", set_of_cuts[i], name[i], "#eta_{#gamma}", true, false, c1);
	}
*/

//	for(int i=0; i<set_of_cuts.size() ; i++){ // loop over different set of cuts
	// ____________________________________________
	// Muon variables
	// ____________________________________________
/*

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu^{+}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_Eta", "(10,-3,3)", set_of_cuts[i], name[i], "#eta #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_Eta", "(10,-3,3)", set_of_cuts[i], name[i], "#eta #mu^{+}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{near}", true, false, c1);


		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonL_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonS_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonL_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonS_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonL_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonS_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonL_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonS_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonL_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonS_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonL_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonS_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonL_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonS_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonL_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonS_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonL_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonS_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonL_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonS_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonL_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonS_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonM_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu^{-}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonP_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu^{+}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonF_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonN_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonL_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "MuonS_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu_{subleading}", true, false, c1);

	// ____________________________________________
	// Photon variables
	// ___________________________________________

		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_hasPixelSeed", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon hasPixelSeed", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_isAlsoElectron", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isAlsoElectron", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_Nclusters", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon Nclusters", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_nBasicClusters", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon nBasicClusters", true, false, c1);
//		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_nXtals", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon nXtals", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_isTightPhoton", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isTightPhoton", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_isLoosePhoton", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isLoosePhoton", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_E2x2", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E2x2", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_E3x3", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E3x3", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_E5x5", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E5x5", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_Emax", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon Emax", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_E2nd", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon E2nd", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_r19", "(100, 0, 2)", set_of_cuts[i], name[i], "Photon r19", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_r9", "(100, 0, 2)", set_of_cuts[i], name[i], "r9", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_cross", "(50, 0, 1.1)", set_of_cuts[i], name[i], "Photon cross", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_caloConeSize", "(30, 0, 0.5)", set_of_cuts[i], name[i], "Photon caloConeSize", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_PreshEnergy", "(40, 0, 10)", set_of_cuts[i], name[i], "Photon Preshower Energy", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_HoE", "(30, 0, 0.55)", set_of_cuts[i], name[i], "Photon HoE", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_covIetaIeta", "(30, 0, 0.02)", set_of_cuts[i], name[i], "Photon covIetaIeta", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_covIphiIphi", "(30, 0, 0.025)", set_of_cuts[i], name[i], "Photon covIphiIphi", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_convNTracks", "(5, -1, 4)", set_of_cuts[i], name[i], "Photon convNTracks", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_etaWidth", "(20, 0, 0.2)", set_of_cuts[i], name[i], "Photon Eta Width", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_phiWidth", "(20, 0, 0.2)", set_of_cuts[i], name[i], "Photon Phi Width", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_isoEcalRecHit", "(70, -2, 20)", set_of_cuts[i], name[i], "Photon isoEcalRecHit", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_isoHcalRecHit", "(100, -1, 10)", set_of_cuts[i], name[i], "Photon isoHcalRecHit", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_isoSolidTrkCone", "(100, -1, 20)", set_of_cuts[i], name[i], "Photon isoSolidTrkCone", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_isoHolsubleadingTrkCone", "(100, -1, 20)", set_of_cuts[i], name[i], "Photon isoHolsubleadingTrkCone", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_isoNTracksSolidCone", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon isoNTracksSolidCone", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_isoNTracksHolsubleadingCone", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon isoNTracksHolsubleadingCone", true, false, c1);

		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_seedTime", "(50,-50,50)", set_of_cuts[i], name[i], "Photon seed Time", true, false, c1);
		DrawDataMCplot(Data_miniTree, MC_miniTree, "Photon_seedFlag", "(50,0,50)", set_of_cuts[i], name[i], "Photon seed Flag", true, false, c1);

	// ____________________________________________
	// mugamma / mumu / mumugamma information
	// ____________________________________________

*/
//	} // end of loop over set of cuts



	return 0;	
}

