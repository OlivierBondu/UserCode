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

#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootBardak.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootBeamSpot.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootCluster.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootEcalRecHit.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootElectron.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootEvent.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootJet.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootMCParticle.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootMCPhoton.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootMET.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootMuon.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootParticle.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootPhoton.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootRun.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootSignalEvent.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootSuperCluster.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootTopTop.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootTrack.h"
#include "/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/interface/TRootVertex.h"



#pragma optimize 0

using namespace std;
	
//int plotDataMC_TDR_miniTree()
int main()
{
	string selection = "hadEt-noDeltaRmin-relaxedMuEta";
	gSystem->Load("/sps/cms/obondu/CMSSW_3_8_6_v6/src/UserCode/IpnTreeProducer/src/libToto.so");
	gROOT->ProcessLine(".x setTDRStyle.C");
	string Data = "Selected/" + selection + "/miniTree_DATA_ALL.root"; 
	string FSR_DYToMuMu = "Selected/" + selection + "/FSR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia/miniTree_FSR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_ALL.root";
	string ISR_DYToMuMu = "Selected/" + selection + "/ISR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia/miniTree_ISR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_ALL.root";
	string TTJets = "Selected/" + selection + "/TTJets_TuneZ2_7TeV-madgraph-tauola_v2/miniTree_TTJets_TuneZ2_7TeV-madgraph-tauola_v2_ALL.root";

	TFile *Data_File = new TFile(Data.c_str());
	TTree* Data_miniTree = (TTree*) Data_File->Get("miniTree");
	TTree* Data_miniTree_allmuons = (TTree*) Data_File->Get("miniTree_allmuons");
	TTree* Data_miniTree_allphotons = (TTree*) Data_File->Get("miniTree_allphotons");
	TFile *FSR_DYToMuMu_File = new TFile(FSR_DYToMuMu.c_str());
	TTree* FSR_DYToMuMu_miniTree = (TTree*) FSR_DYToMuMu_File->Get("miniTree");
	TTree* FSR_DYToMuMu_miniTree_allmuons = (TTree*) FSR_DYToMuMu_File->Get("miniTree_allmuons");
	TTree* FSR_DYToMuMu_miniTree_allphotons = (TTree*) FSR_DYToMuMu_File->Get("miniTree_allphotons");
	TFile *ISR_DYToMuMu_File = new TFile(ISR_DYToMuMu.c_str());
	TTree* ISR_DYToMuMu_miniTree = (TTree*) ISR_DYToMuMu_File->Get("miniTree");
	TTree* ISR_DYToMuMu_miniTree_allmuons = (TTree*) ISR_DYToMuMu_File->Get("miniTree_allmuons");
	TTree* ISR_DYToMuMu_miniTree_allphotons = (TTree*) ISR_DYToMuMu_File->Get("miniTree_allphotons");
	TFile *TTJets_File = new TFile(TTJets.c_str());
	TTree* TTJets_miniTree = (TTree*) TTJets_File->Get("miniTree");
	TTree* TTJets_miniTree_allmuons = (TTree*) TTJets_File->Get("miniTree_allmuons");
	TTree* TTJets_miniTree_allphotons = (TTree*) TTJets_File->Get("miniTree_allphotons");


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
	set_of_cuts.push_back("isAfterCut8");
  name.push_back("After8");


	for(int i=0; i<set_of_cuts.size() ; i++){
/*
		DrawDataMCplot_TH1I(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "NbMuons", "NbMuons", "(10,0,10)", set_of_cuts[i], name[i], "# of muons", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "NbPhotons", "NbPhotons", "(10,0,10)", set_of_cuts[i], name[i], "# of photons", true, false, c1);

		DrawDataMCplot(Data_miniTree_allmuons, QCD_Pt15_miniTree_allmuons, QCD_Pt30_miniTree_allmuons, QCD_Pt80_miniTree_allmuons, QCD_Pt170_miniTree_allmuons, QCD_Pt300_miniTree_allmuons, QCD_Pt470_miniTree_allmuons, PhotonJet_Pt15_miniTree_allmuons, PhotonJet_Pt30_miniTree_allmuons, PhotonJet_Pt80_miniTree_allmuons, PhotonJet_Pt170_miniTree_allmuons, PhotonJet_Pt300_miniTree_allmuons, TTbarJets_Tauola_miniTree_allmuons, WJets_7TeV_miniTree_allmuons, ZJets_7TeV_miniTree_allmuons, QCD_Mu_Pt20to30_miniTree_allmuons, QCD_Mu_Pt30to50_miniTree_allmuons, QCD_Mu_Pt50to80_miniTree_allmuons, QCD_Mu_Pt80to120_miniTree_allmuons, QCD_Mu_Pt120to170_miniTree_allmuons, QCD_Mu_Pt170toInf_miniTree_allmuons, InclusiveMu15_miniTree_allmuons, FSR_ZmumuJet_Pt0to15_miniTree_allmuons, FSR_ZmumuJet_Pt15to20_miniTree_allmuons, FSR_ZmumuJet_Pt20to30_miniTree_allmuons, FSR_ZmumuJet_Pt30to50_miniTree_allmuons, FSR_ZmumuJet_Pt50to80_miniTree_allmuons, FSR_ZmumuJet_Pt80to120_miniTree_allmuons, FSR_ZmumuJet_Pt120to170_miniTree_allmuons, FSR_ZmumuJet_Pt170to230_miniTree_allmuons, FSR_ZmumuJet_Pt230to300_miniTree_allmuons, FSR_ZmumuJet_Pt300toInf_miniTree_allmuons, ISR_ZmumuJet_Pt0to15_miniTree_allmuons, ISR_ZmumuJet_Pt15to20_miniTree_allmuons, ISR_ZmumuJet_Pt20to30_miniTree_allmuons, ISR_ZmumuJet_Pt30to50_miniTree_allmuons, ISR_ZmumuJet_Pt50to80_miniTree_allmuons, ISR_ZmumuJet_Pt80to120_miniTree_allmuons, ISR_ZmumuJet_Pt120to170_miniTree_allmuons, ISR_ZmumuJet_Pt170to230_miniTree_allmuons, ISR_ZmumuJet_Pt230to300_miniTree_allmuons, ISR_ZmumuJet_Pt300toInf_miniTree_allmuons, "Pt_allMuons", "Pt_allMuons", "(100,0,100)", set_of_cuts[i], name[i], "p_{T_{#mu}} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree_allmuons, QCD_Pt15_miniTree_allmuons, QCD_Pt30_miniTree_allmuons, QCD_Pt80_miniTree_allmuons, QCD_Pt170_miniTree_allmuons, QCD_Pt300_miniTree_allmuons, QCD_Pt470_miniTree_allmuons, PhotonJet_Pt15_miniTree_allmuons, PhotonJet_Pt30_miniTree_allmuons, PhotonJet_Pt80_miniTree_allmuons, PhotonJet_Pt170_miniTree_allmuons, PhotonJet_Pt300_miniTree_allmuons, TTbarJets_Tauola_miniTree_allmuons, WJets_7TeV_miniTree_allmuons, ZJets_7TeV_miniTree_allmuons, QCD_Mu_Pt20to30_miniTree_allmuons, QCD_Mu_Pt30to50_miniTree_allmuons, QCD_Mu_Pt50to80_miniTree_allmuons, QCD_Mu_Pt80to120_miniTree_allmuons, QCD_Mu_Pt120to170_miniTree_allmuons, QCD_Mu_Pt170toInf_miniTree_allmuons, InclusiveMu15_miniTree_allmuons, FSR_ZmumuJet_Pt0to15_miniTree_allmuons, FSR_ZmumuJet_Pt15to20_miniTree_allmuons, FSR_ZmumuJet_Pt20to30_miniTree_allmuons, FSR_ZmumuJet_Pt30to50_miniTree_allmuons, FSR_ZmumuJet_Pt50to80_miniTree_allmuons, FSR_ZmumuJet_Pt80to120_miniTree_allmuons, FSR_ZmumuJet_Pt120to170_miniTree_allmuons, FSR_ZmumuJet_Pt170to230_miniTree_allmuons, FSR_ZmumuJet_Pt230to300_miniTree_allmuons, FSR_ZmumuJet_Pt300toInf_miniTree_allmuons, ISR_ZmumuJet_Pt0to15_miniTree_allmuons, ISR_ZmumuJet_Pt15to20_miniTree_allmuons, ISR_ZmumuJet_Pt20to30_miniTree_allmuons, ISR_ZmumuJet_Pt30to50_miniTree_allmuons, ISR_ZmumuJet_Pt50to80_miniTree_allmuons, ISR_ZmumuJet_Pt80to120_miniTree_allmuons, ISR_ZmumuJet_Pt120to170_miniTree_allmuons, ISR_ZmumuJet_Pt170to230_miniTree_allmuons, ISR_ZmumuJet_Pt230to300_miniTree_allmuons, ISR_ZmumuJet_Pt300toInf_miniTree_allmuons, "Phi_allMuons", "Phi_allMuons", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi_{#mu}", true, false, c1);
		DrawDataMCplot(Data_miniTree_allmuons, QCD_Pt15_miniTree_allmuons, QCD_Pt30_miniTree_allmuons, QCD_Pt80_miniTree_allmuons, QCD_Pt170_miniTree_allmuons, QCD_Pt300_miniTree_allmuons, QCD_Pt470_miniTree_allmuons, PhotonJet_Pt15_miniTree_allmuons, PhotonJet_Pt30_miniTree_allmuons, PhotonJet_Pt80_miniTree_allmuons, PhotonJet_Pt170_miniTree_allmuons, PhotonJet_Pt300_miniTree_allmuons, TTbarJets_Tauola_miniTree_allmuons, WJets_7TeV_miniTree_allmuons, ZJets_7TeV_miniTree_allmuons, QCD_Mu_Pt20to30_miniTree_allmuons, QCD_Mu_Pt30to50_miniTree_allmuons, QCD_Mu_Pt50to80_miniTree_allmuons, QCD_Mu_Pt80to120_miniTree_allmuons, QCD_Mu_Pt120to170_miniTree_allmuons, QCD_Mu_Pt170toInf_miniTree_allmuons, InclusiveMu15_miniTree_allmuons, FSR_ZmumuJet_Pt0to15_miniTree_allmuons, FSR_ZmumuJet_Pt15to20_miniTree_allmuons, FSR_ZmumuJet_Pt20to30_miniTree_allmuons, FSR_ZmumuJet_Pt30to50_miniTree_allmuons, FSR_ZmumuJet_Pt50to80_miniTree_allmuons, FSR_ZmumuJet_Pt80to120_miniTree_allmuons, FSR_ZmumuJet_Pt120to170_miniTree_allmuons, FSR_ZmumuJet_Pt170to230_miniTree_allmuons, FSR_ZmumuJet_Pt230to300_miniTree_allmuons, FSR_ZmumuJet_Pt300toInf_miniTree_allmuons, ISR_ZmumuJet_Pt0to15_miniTree_allmuons, ISR_ZmumuJet_Pt15to20_miniTree_allmuons, ISR_ZmumuJet_Pt20to30_miniTree_allmuons, ISR_ZmumuJet_Pt30to50_miniTree_allmuons, ISR_ZmumuJet_Pt50to80_miniTree_allmuons, ISR_ZmumuJet_Pt80to120_miniTree_allmuons, ISR_ZmumuJet_Pt120to170_miniTree_allmuons, ISR_ZmumuJet_Pt170to230_miniTree_allmuons, ISR_ZmumuJet_Pt230to300_miniTree_allmuons, ISR_ZmumuJet_Pt300toInf_miniTree_allmuons, "Eta_allMuons", "Eta_allMuons", "(50,-3.0,3.0)", set_of_cuts[i], name[i], "#eta_{#mu}", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree_allmuons, QCD_Pt15_miniTree_allmuons, QCD_Pt30_miniTree_allmuons, QCD_Pt80_miniTree_allmuons, QCD_Pt170_miniTree_allmuons, QCD_Pt300_miniTree_allmuons, QCD_Pt470_miniTree_allmuons, PhotonJet_Pt15_miniTree_allmuons, PhotonJet_Pt30_miniTree_allmuons, PhotonJet_Pt80_miniTree_allmuons, PhotonJet_Pt170_miniTree_allmuons, PhotonJet_Pt300_miniTree_allmuons, TTbarJets_Tauola_miniTree_allmuons, WJets_7TeV_miniTree_allmuons, ZJets_7TeV_miniTree_allmuons, QCD_Mu_Pt20to30_miniTree_allmuons, QCD_Mu_Pt30to50_miniTree_allmuons, QCD_Mu_Pt50to80_miniTree_allmuons, QCD_Mu_Pt80to120_miniTree_allmuons, QCD_Mu_Pt120to170_miniTree_allmuons, QCD_Mu_Pt170toInf_miniTree_allmuons, InclusiveMu15_miniTree_allmuons, FSR_ZmumuJet_Pt0to15_miniTree_allmuons, FSR_ZmumuJet_Pt15to20_miniTree_allmuons, FSR_ZmumuJet_Pt20to30_miniTree_allmuons, FSR_ZmumuJet_Pt30to50_miniTree_allmuons, FSR_ZmumuJet_Pt50to80_miniTree_allmuons, FSR_ZmumuJet_Pt80to120_miniTree_allmuons, FSR_ZmumuJet_Pt120to170_miniTree_allmuons, FSR_ZmumuJet_Pt170to230_miniTree_allmuons, FSR_ZmumuJet_Pt230to300_miniTree_allmuons, FSR_ZmumuJet_Pt300toInf_miniTree_allmuons, ISR_ZmumuJet_Pt0to15_miniTree_allmuons, ISR_ZmumuJet_Pt15to20_miniTree_allmuons, ISR_ZmumuJet_Pt20to30_miniTree_allmuons, ISR_ZmumuJet_Pt30to50_miniTree_allmuons, ISR_ZmumuJet_Pt50to80_miniTree_allmuons, ISR_ZmumuJet_Pt80to120_miniTree_allmuons, ISR_ZmumuJet_Pt120to170_miniTree_allmuons, ISR_ZmumuJet_Pt170to230_miniTree_allmuons, ISR_ZmumuJet_Pt230to300_miniTree_allmuons, ISR_ZmumuJet_Pt300toInf_miniTree_allmuons, "Charge_allMuons", "Charge_allMuons", "(20,-2,2)", set_of_cuts[i], name[i], "Charge_{#mu}", true, false, c1);

		DrawDataMCplot(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, FSR_ZmumuJet_Pt0to15_miniTree_allphotons, FSR_ZmumuJet_Pt15to20_miniTree_allphotons, FSR_ZmumuJet_Pt20to30_miniTree_allphotons, FSR_ZmumuJet_Pt30to50_miniTree_allphotons, FSR_ZmumuJet_Pt50to80_miniTree_allphotons, FSR_ZmumuJet_Pt80to120_miniTree_allphotons, FSR_ZmumuJet_Pt120to170_miniTree_allphotons, FSR_ZmumuJet_Pt170to230_miniTree_allphotons, FSR_ZmumuJet_Pt230to300_miniTree_allphotons, FSR_ZmumuJet_Pt300toInf_miniTree_allphotons, ISR_ZmumuJet_Pt0to15_miniTree_allphotons, ISR_ZmumuJet_Pt15to20_miniTree_allphotons, ISR_ZmumuJet_Pt20to30_miniTree_allphotons, ISR_ZmumuJet_Pt30to50_miniTree_allphotons, ISR_ZmumuJet_Pt50to80_miniTree_allphotons, ISR_ZmumuJet_Pt80to120_miniTree_allphotons, ISR_ZmumuJet_Pt120to170_miniTree_allphotons, ISR_ZmumuJet_Pt170to230_miniTree_allphotons, ISR_ZmumuJet_Pt230to300_miniTree_allphotons, ISR_ZmumuJet_Pt300toInf_miniTree_allphotons, "Pt_allPhotons", "Pt_allPhotons", "(100,0,100)", set_of_cuts[i], name[i], "p_{T_{#gamma}} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, FSR_ZmumuJet_Pt0to15_miniTree_allphotons, FSR_ZmumuJet_Pt15to20_miniTree_allphotons, FSR_ZmumuJet_Pt20to30_miniTree_allphotons, FSR_ZmumuJet_Pt30to50_miniTree_allphotons, FSR_ZmumuJet_Pt50to80_miniTree_allphotons, FSR_ZmumuJet_Pt80to120_miniTree_allphotons, FSR_ZmumuJet_Pt120to170_miniTree_allphotons, FSR_ZmumuJet_Pt170to230_miniTree_allphotons, FSR_ZmumuJet_Pt230to300_miniTree_allphotons, FSR_ZmumuJet_Pt300toInf_miniTree_allphotons, ISR_ZmumuJet_Pt0to15_miniTree_allphotons, ISR_ZmumuJet_Pt15to20_miniTree_allphotons, ISR_ZmumuJet_Pt20to30_miniTree_allphotons, ISR_ZmumuJet_Pt30to50_miniTree_allphotons, ISR_ZmumuJet_Pt50to80_miniTree_allphotons, ISR_ZmumuJet_Pt80to120_miniTree_allphotons, ISR_ZmumuJet_Pt120to170_miniTree_allphotons, ISR_ZmumuJet_Pt170to230_miniTree_allphotons, ISR_ZmumuJet_Pt230to300_miniTree_allphotons, ISR_ZmumuJet_Pt300toInf_miniTree_allphotons, "Phi_allPhotons", "Phi_allPhotons", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi_{#gamma}", true, false, c1);
*/
//		DrawDataMCplot(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, FSR_ZmumuJet_Pt0to15_miniTree_allphotons, FSR_ZmumuJet_Pt15to20_miniTree_allphotons, FSR_ZmumuJet_Pt20to30_miniTree_allphotons, FSR_ZmumuJet_Pt30to50_miniTree_allphotons, FSR_ZmumuJet_Pt50to80_miniTree_allphotons, FSR_ZmumuJet_Pt80to120_miniTree_allphotons, FSR_ZmumuJet_Pt120to170_miniTree_allphotons, FSR_ZmumuJet_Pt170to230_miniTree_allphotons, FSR_ZmumuJet_Pt230to300_miniTree_allphotons, FSR_ZmumuJet_Pt300toInf_miniTree_allphotons, ISR_ZmumuJet_Pt0to15_miniTree_allphotons, ISR_ZmumuJet_Pt15to20_miniTree_allphotons, ISR_ZmumuJet_Pt20to30_miniTree_allphotons, ISR_ZmumuJet_Pt30to50_miniTree_allphotons, ISR_ZmumuJet_Pt50to80_miniTree_allphotons, ISR_ZmumuJet_Pt80to120_miniTree_allphotons, ISR_ZmumuJet_Pt120to170_miniTree_allphotons, ISR_ZmumuJet_Pt170to230_miniTree_allphotons, ISR_ZmumuJet_Pt230to300_miniTree_allphotons, ISR_ZmumuJet_Pt300toInf_miniTree_allphotons, "Eta_allPhotons", "Eta_allPhotons", "(50,-3.0,3.0)", set_of_cuts[i], name[i], "#eta_{#gamma}", true, false, c1);
/*
//FIXME		DrawDataMCplot(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, FSR_ZmumuJet_Pt0to15_miniTree_allphotons, FSR_ZmumuJet_Pt15to20_miniTree_allphotons, FSR_ZmumuJet_Pt20to30_miniTree_allphotons, FSR_ZmumuJet_Pt30to50_miniTree_allphotons, FSR_ZmumuJet_Pt50to80_miniTree_allphotons, FSR_ZmumuJet_Pt80to120_miniTree_allphotons, FSR_ZmumuJet_Pt120to170_miniTree_allphotons, FSR_ZmumuJet_Pt170to230_miniTree_allphotons, FSR_ZmumuJet_Pt230to300_miniTree_allphotons, FSR_ZmumuJet_Pt300toInf_miniTree_allphotons, ISR_ZmumuJet_Pt0to15_miniTree_allphotons, ISR_ZmumuJet_Pt15to20_miniTree_allphotons, ISR_ZmumuJet_Pt20to30_miniTree_allphotons, ISR_ZmumuJet_Pt30to50_miniTree_allphotons, ISR_ZmumuJet_Pt50to80_miniTree_allphotons, ISR_ZmumuJet_Pt80to120_miniTree_allphotons, ISR_ZmumuJet_Pt120to170_miniTree_allphotons, ISR_ZmumuJet_Pt170to230_miniTree_allphotons, ISR_ZmumuJet_Pt230to300_miniTree_allphotons, ISR_ZmumuJet_Pt300toInf_miniTree_allphotons, "Cross_allPhotons", "Cross_allPhotons", "(50,-1.0,1.5)", set_of_cuts[i], name[i], "cross_{#gamma}", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, FSR_ZmumuJet_Pt0to15_miniTree_allphotons, FSR_ZmumuJet_Pt15to20_miniTree_allphotons, FSR_ZmumuJet_Pt20to30_miniTree_allphotons, FSR_ZmumuJet_Pt30to50_miniTree_allphotons, FSR_ZmumuJet_Pt50to80_miniTree_allphotons, FSR_ZmumuJet_Pt80to120_miniTree_allphotons, FSR_ZmumuJet_Pt120to170_miniTree_allphotons, FSR_ZmumuJet_Pt170to230_miniTree_allphotons, FSR_ZmumuJet_Pt230to300_miniTree_allphotons, FSR_ZmumuJet_Pt300toInf_miniTree_allphotons, ISR_ZmumuJet_Pt0to15_miniTree_allphotons, ISR_ZmumuJet_Pt15to20_miniTree_allphotons, ISR_ZmumuJet_Pt20to30_miniTree_allphotons, ISR_ZmumuJet_Pt30to50_miniTree_allphotons, ISR_ZmumuJet_Pt50to80_miniTree_allphotons, ISR_ZmumuJet_Pt80to120_miniTree_allphotons, ISR_ZmumuJet_Pt120to170_miniTree_allphotons, ISR_ZmumuJet_Pt170to230_miniTree_allphotons, ISR_ZmumuJet_Pt230to300_miniTree_allphotons, ISR_ZmumuJet_Pt300toInf_miniTree_allphotons, "isEB_allPhotons", "isEB_allPhotons", "(20,-1,2)", set_of_cuts[i], name[i], "#gamma isEB", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, FSR_ZmumuJet_Pt0to15_miniTree_allphotons, FSR_ZmumuJet_Pt15to20_miniTree_allphotons, FSR_ZmumuJet_Pt20to30_miniTree_allphotons, FSR_ZmumuJet_Pt30to50_miniTree_allphotons, FSR_ZmumuJet_Pt50to80_miniTree_allphotons, FSR_ZmumuJet_Pt80to120_miniTree_allphotons, FSR_ZmumuJet_Pt120to170_miniTree_allphotons, FSR_ZmumuJet_Pt170to230_miniTree_allphotons, FSR_ZmumuJet_Pt230to300_miniTree_allphotons, FSR_ZmumuJet_Pt300toInf_miniTree_allphotons, ISR_ZmumuJet_Pt0to15_miniTree_allphotons, ISR_ZmumuJet_Pt15to20_miniTree_allphotons, ISR_ZmumuJet_Pt20to30_miniTree_allphotons, ISR_ZmumuJet_Pt30to50_miniTree_allphotons, ISR_ZmumuJet_Pt50to80_miniTree_allphotons, ISR_ZmumuJet_Pt80to120_miniTree_allphotons, ISR_ZmumuJet_Pt120to170_miniTree_allphotons, ISR_ZmumuJet_Pt170to230_miniTree_allphotons, ISR_ZmumuJet_Pt230to300_miniTree_allphotons, ISR_ZmumuJet_Pt300toInf_miniTree_allphotons, "isEE_allPhotons", "isEE_allPhotons", "(20,-1,2)", set_of_cuts[i], name[i], "#gamma isEE", true, false, c1);
//		DrawDataMCplot_TH1I(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, FSR_ZmumuJet_Pt0to15_miniTree_allphotons, FSR_ZmumuJet_Pt15to20_miniTree_allphotons, FSR_ZmumuJet_Pt20to30_miniTree_allphotons, FSR_ZmumuJet_Pt30to50_miniTree_allphotons, FSR_ZmumuJet_Pt50to80_miniTree_allphotons, FSR_ZmumuJet_Pt80to120_miniTree_allphotons, FSR_ZmumuJet_Pt120to170_miniTree_allphotons, FSR_ZmumuJet_Pt170to230_miniTree_allphotons, FSR_ZmumuJet_Pt230to300_miniTree_allphotons, FSR_ZmumuJet_Pt300toInf_miniTree_allphotons, ISR_ZmumuJet_Pt0to15_miniTree_allphotons, ISR_ZmumuJet_Pt15to20_miniTree_allphotons, ISR_ZmumuJet_Pt20to30_miniTree_allphotons, ISR_ZmumuJet_Pt30to50_miniTree_allphotons, ISR_ZmumuJet_Pt50to80_miniTree_allphotons, ISR_ZmumuJet_Pt80to120_miniTree_allphotons, ISR_ZmumuJet_Pt120to170_miniTree_allphotons, ISR_ZmumuJet_Pt170to230_miniTree_allphotons, ISR_ZmumuJet_Pt230to300_miniTree_allphotons, ISR_ZmumuJet_Pt300toInf_miniTree_allphotons, "isEEM_allPhotons", "isEEM_allPhotons", "(20,-1,2)", set_of_cuts[i], name[i], "#gamma isEEM", true, false, c1);
//		DrawDataMCplot_TH1I(Data_miniTree_allphotons, QCD_Pt15_miniTree_allphotons, QCD_Pt30_miniTree_allphotons, QCD_Pt80_miniTree_allphotons, QCD_Pt170_miniTree_allphotons, QCD_Pt300_miniTree_allphotons, QCD_Pt470_miniTree_allphotons, PhotonJet_Pt15_miniTree_allphotons, PhotonJet_Pt30_miniTree_allphotons, PhotonJet_Pt80_miniTree_allphotons, PhotonJet_Pt170_miniTree_allphotons, PhotonJet_Pt300_miniTree_allphotons, TTbarJets_Tauola_miniTree_allphotons, WJets_7TeV_miniTree_allphotons, ZJets_7TeV_miniTree_allphotons, QCD_Mu_Pt20to30_miniTree_allphotons, QCD_Mu_Pt30to50_miniTree_allphotons, QCD_Mu_Pt50to80_miniTree_allphotons, QCD_Mu_Pt80to120_miniTree_allphotons, QCD_Mu_Pt120to170_miniTree_allphotons, QCD_Mu_Pt170toInf_miniTree_allphotons, InclusiveMu15_miniTree_allphotons, FSR_ZmumuJet_Pt0to15_miniTree_allphotons, FSR_ZmumuJet_Pt15to20_miniTree_allphotons, FSR_ZmumuJet_Pt20to30_miniTree_allphotons, FSR_ZmumuJet_Pt30to50_miniTree_allphotons, FSR_ZmumuJet_Pt50to80_miniTree_allphotons, FSR_ZmumuJet_Pt80to120_miniTree_allphotons, FSR_ZmumuJet_Pt120to170_miniTree_allphotons, FSR_ZmumuJet_Pt170to230_miniTree_allphotons, FSR_ZmumuJet_Pt230to300_miniTree_allphotons, FSR_ZmumuJet_Pt300toInf_miniTree_allphotons, ISR_ZmumuJet_Pt0to15_miniTree_allphotons, ISR_ZmumuJet_Pt15to20_miniTree_allphotons, ISR_ZmumuJet_Pt20to30_miniTree_allphotons, ISR_ZmumuJet_Pt30to50_miniTree_allphotons, ISR_ZmumuJet_Pt50to80_miniTree_allphotons, ISR_ZmumuJet_Pt80to120_miniTree_allphotons, ISR_ZmumuJet_Pt120to170_miniTree_allphotons, ISR_ZmumuJet_Pt170to230_miniTree_allphotons, ISR_ZmumuJet_Pt230to300_miniTree_allphotons, ISR_ZmumuJet_Pt300toInf_miniTree_allphotons, "isEEP_allPhotons", "isEEP_allPhotons", "(20,-1,2)", set_of_cuts[i], name[i], "#gamma isEEP", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonL_Pt", "MuonL_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{leading} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonS_Pt", "MuonS_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{subleading} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonL_Eta", "MuonL_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonS_Eta", "MuonS_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonL_Phi", "MuonL_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonS_Phi", "MuonS_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{subleading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonL_Charge", "MuonL_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonS_Charge", "MuonS_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{subleading}", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonF_Pt", "MuonF_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{far} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonN_Pt", "MuonN_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{near} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonF_Eta", "MuonF_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonN_Eta", "MuonN_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonF_Phi", "MuonF_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonN_Phi", "MuonN_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonF_Charge", "MuonF_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonN_Charge", "MuonN_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{near}", true, false, c1);
*/
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Mmumu", "Mmumu", "(300,0,300)", set_of_cuts[i], name[i], "M_{#mu#mu} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Mmumu", "Mmumu_extended", "(60,30,90)", set_of_cuts[i], name[i], "M_{#mu#mu} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Mmumugamma", "Mmumugamma", "(300,0,300)", set_of_cuts[i], name[i], "M_{#mu#mu#gamma} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Mmumugamma", "Mmumugamma_extended", "(40,70,110)", set_of_cuts[i], name[i], "M_{#mu#mu#gamma} [GeV]", true, false, c1);
	
/*
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "deltaRNear", "deltaRNear", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{near})", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "deltaRNear", "deltaRNear_extended", "(25,0,1)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{near})", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "deltaRNear", "deltaRNear_extended2", "(25,0,0.1)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{near})", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "deltaRFar", "deltaRFar", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{far})", true, false, c1);
//		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "deltaRPlus", "deltaRPlus", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{plus})", true, false, c1);
//		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "deltaRMinus", "deltaRMinus", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{minus})", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "deltaRLeading", "deltaRLeading", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{leading})", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "deltaRSubleading", "deltaRSubleading", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{subleading})", true, false, c1);

*/
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Photon_Eta", "Photon_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta^{#gamma}", true, false, c1);
/*
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Photon_Phi", "Photon_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi of photon", true, false, c1);

		DrawDataMCplot_TH1I(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Photon_isEB", "Photon_isEB", "(10,-1,2)", set_of_cuts[i], name[i], "photon is in barrel", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Photon_isEE", "Photon_isEE", "(10,-1,2)", set_of_cuts[i], name[i], "photon is in endcap", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Photon_isEEP", "Photon_isEEP", "(10,-1,2)", set_of_cuts[i], name[i], "photon is in endcap plus", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Photon_isEEM", "Photon_isEEM", "(10,-1,2)", set_of_cuts[i], name[i], "photon is in endcap minus", true, false, c1);
*/
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Photon_E", "Photon_E", "(100, 0, 100)", set_of_cuts[i], name[i], "E^{#gamma} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Photon_E", "Photon_E_extended", "(100, 0, 150)", set_of_cuts[i], name[i], "E^{#gamma} [GeV]", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Photon_Et", "Photon_Et", "(100, 0, 100)", set_of_cuts[i], name[i], "E_{T}^{#gamma} [GeV]", true, false, c1);
/*
		DrawDataMCplot_TH2F(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Mmumu", "Mmumugamma", "(900,0,300,900,0,300)", set_of_cuts[i], name[i], "M_{#mu#mu} [GeV]", "M_{#mu#mu#gamma} [GeV]", "Mmumu_VS_Mmumugamma", false, false, c1);
		DrawDataMCplot_TH2F(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Mmumu", "Mmumugamma", "(450,20,100,450,80,110)", set_of_cuts[i], name[i], "M_{#mu#mu} [GeV]", "M_{#mu#mu#gamma} [GeV]", "Mmumu_VS_Mmumugamma_extended", false, false, c1);

DrawDataMCplot_TH2F(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "((91.1876**2 - Mmumu**2 ) / (Mmumugamma**2 - Mmumu**2))*Photon_E", "Photon_E", "(400,0,100,400,0,100)", set_of_cuts[i], name[i], "E_{true} = k*E_{reco} [GeV]", "E_{reco} [GeV]", "Etrue_VS_Ereco", false, false, c1, true);
DrawDataMCplot_TH2F(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "((91.1876**2 - Mmumu**2 ) / (Mmumugamma**2 - Mmumu**2))*Photon_E", "Photon_E", "(600,0,150,600,0,150)", set_of_cuts[i], name[i], "E_{true} = k*E_{reco} [GeV]", "E_{reco} [GeV]", "Etrue_VS_Ereco_extended", false, false, c1, true);
*/

//	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "(Mmumugamma**2 - Mmumu**2) / (91.1876**2 - Mmumu**2 ) -1", "Photon_s", "(10,-1.0,1.0)", set_of_cuts[i], name[i], "s = E_{reco} / E_{muons} -1", true, false, c1, true);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "(Mmumugamma**2 - Mmumu**2) / (91.1876**2 - Mmumu**2 ) -1", "Photon_s_extended", "(40, -1.0,1.0)", set_of_cuts[i], name[i], "s = E_{reco} / E_{muons} -1", true, false, c1, true);
//	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "(Mmumugamma**2 - Mmumu**2) / (91.1876**2 - Mmumu**2 ) -1", "Photon_s_extended2", "(20, -1.0,1.0)", set_of_cuts[i], name[i], "s = E_{reco} / E_{muons} -1", true, false, c1, true);
//	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "(Mmumugamma**2 - Mmumu**2) / (91.1876**2 - Mmumu**2 ) -1", "Photon_s_extended3", "(320, -1.0,1.0)", set_of_cuts[i], name[i], "s = E_{reco} / E_{muons} -1", true, false, c1, true); 

//	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "(Mmumugamma**2 - Mmumu**2) / (91.1876**2 - Mmumu**2 )", "Photon_ik", "(10,0,2.0)", set_of_cuts[i], name[i], "1 / k = E_{reco} / E_{muons}", true, false, c1, true);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "(Mmumugamma**2 - Mmumu**2) / (91.1876**2 - Mmumu**2 )", "Photon_ik_extended", "(40, 0.0 , 2.0)", set_of_cuts[i], name[i], "1 / k = E_{reco} / E_{muons}", true, false, c1, true);
//	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "(Mmumugamma**2 - Mmumu**2) / (91.1876**2 - Mmumu**2 )", "Photon_ik_extended2", "(20, 0.0 , 2.0)", set_of_cuts[i], name[i], "1 / k = E_{reco} / E_{muons}", true, false, c1, true);
//	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "(Mmumugamma**2 - Mmumu**2) / (91.1876**2 - Mmumu**2 )", "Photon_ik_extended3", "(320, 0.0 , 2.0)", set_of_cuts[i], name[i], "1 / k = E_{reco} / E_{muons}", true, false, c1, true);

//	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "(91.1876**2 - Mmumu**2 ) / (Mmumugamma**2 - Mmumu**2)", "Photon_k", "(10,0,2.0)", set_of_cuts[i], name[i], "k = E_{muons} / E_{reco}", true, false, c1, true);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "(91.1876**2 - Mmumu**2 ) / (Mmumugamma**2 - Mmumu**2)", "Photon_k_extended", "(40, 0.0 , 2.0)", set_of_cuts[i], name[i], "k = E_{muons} / E_{reco}", true, false, c1, true);
//	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "(91.1876**2 - Mmumu**2 ) / (Mmumugamma**2 - Mmumu**2)", "Photon_k_extended2", "(20, 0.0 , 2.0)", set_of_cuts[i], name[i], "k = E_{muons} / E_{reco}", true, false, c1, true);
//	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "(91.1876**2 - Mmumu**2 ) / (Mmumugamma**2 - Mmumu**2)", "Photon_k_extended3", "(320, 0.0 , 2.0)", set_of_cuts[i], name[i], "k = E_{muons} / E_{reco}", true, false, c1, true);
/*
//DrawDataMCplot_TH2F(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Photon_convNTracks", "MuonN_isoR03_sumPt", "(16,0,4,200,0,10)", set_of_cuts[i], name[i], "Photon_convNTracks", "MuonN_isoR03_sumPt", "Photon_convNTracks_VS_MuonN_isoR03_sumPt", false, false, c1, false);
//DrawDataMCplot_TH2F(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "Photon_convNTracks", "MuonN_isoR03_sumPt", "(12,0,3,200,0,3)", set_of_cuts[i], name[i], "Photon_convNTracks", "MuonN_isoR03_sumPt", "Photon_convNTracks_VS_MuonN_isoR03_sumPt_extended", false, false, c1, false);
	//	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, ISR_DYToMuMu_miniTree, TTJets_miniTree, "MuonN_isoR03_sumPt", "MuonN_isoR03_sumPt", "(100,0,10)", set_of_cuts[i], name[i], "MuonN_isoR03_sumPt", true, false, c1);
*/
	}
	return 0;	
}

