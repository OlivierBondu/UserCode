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

#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootBardak.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootBeamSpot.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootCluster.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootEcalRecHit.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootElectron.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootEvent.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootJet.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootMCParticle.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootMCPhoton.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootMET.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootMuon.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootParticle.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootPhoton.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootRun.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootSignalEvent.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootSuperCluster.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootTopTop.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootTrack.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootVertex.h"



#pragma optimize 0

using namespace std;
	
//int plotDataMC_TDR_miniTree()
int main()
{
	string selection = "loose";
	gSystem->Load("/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/src/libToto.so");
	gROOT->ProcessLine(".x setTDRStyle.C");
	string Data = "miniTree_v2_DATA_2011_ALL.root"; 
	string FSR_DYToMuMu = "miniTree_v2_FSR_DYToMuMu.root";
	string nonFSR_DYToMuMu = "miniTree_v2_nonFSR_DYToMuMu.root";
	string TTJets = "miniTree_v2_TTJets.root";
//	string WJetsToLNu = "Selected/" + selection + "/WJetsToLNu/miniTree_WJetsToLNu.root";
	string QCDMu = "miniTree_v2_QCD.root"; 

	TFile *Data_File = new TFile(Data.c_str());
	TTree* Data_miniTree = (TTree*) Data_File->Get("miniTree");
	TTree* Data_miniTree_allmuons = (TTree*) Data_File->Get("miniTree_allmuons");
	TTree* Data_miniTree_allphotons = (TTree*) Data_File->Get("miniTree_allphotons");
	TFile *FSR_DYToMuMu_File = new TFile(FSR_DYToMuMu.c_str());
	TTree* FSR_DYToMuMu_miniTree = (TTree*) FSR_DYToMuMu_File->Get("miniTree");
	TTree* FSR_DYToMuMu_miniTree_allmuons = (TTree*) FSR_DYToMuMu_File->Get("miniTree_allmuons");
	TTree* FSR_DYToMuMu_miniTree_allphotons = (TTree*) FSR_DYToMuMu_File->Get("miniTree_allphotons");
	TFile *nonFSR_DYToMuMu_File = new TFile(nonFSR_DYToMuMu.c_str());
	TTree* nonFSR_DYToMuMu_miniTree = (TTree*) nonFSR_DYToMuMu_File->Get("miniTree");
	TTree* nonFSR_DYToMuMu_miniTree_allmuons = (TTree*) nonFSR_DYToMuMu_File->Get("miniTree_allmuons");
	TTree* nonFSR_DYToMuMu_miniTree_allphotons = (TTree*) nonFSR_DYToMuMu_File->Get("miniTree_allphotons");
	TFile *TTJets_File = new TFile(TTJets.c_str());
	TTree* TTJets_miniTree = (TTree*) TTJets_File->Get("miniTree");
	TTree* TTJets_miniTree_allmuons = (TTree*) TTJets_File->Get("miniTree_allmuons");
	TTree* TTJets_miniTree_allphotons = (TTree*) TTJets_File->Get("miniTree_allphotons");
//	TFile *WJetsToLNu_File = new TFile(WJetsToLNu.c_str());
//	TTree* WJetsToLNu_miniTree = (TTree*) WJetsToLNu_File->Get("miniTree");
//	TTree* WJetsToLNu_miniTree_allmuons = (TTree*) WJetsToLNu_File->Get("miniTree_allmuons");
//	TTree* WJetsToLNu_miniTree_allphotons = (TTree*) WJetsToLNu_File->Get("miniTree_allphotons");

	TFile *QCDMu_File = new TFile(QCDMu.c_str());
	TTree* QCDMu_miniTree = (TTree*) QCDMu_File->Get("miniTree");
	TTree* QCDMu_miniTree_allmuons = (TTree*) QCDMu_File->Get("miniTree_allmuons");
	TTree* QCDMu_miniTree_allphotons = (TTree*) QCDMu_File->Get("miniTree_allphotons");


	TCanvas *c1 = new TCanvas("Default", "Default");

	DrawDataMCplot(Data_miniTree_allmuons, FSR_DYToMuMu_miniTree_allmuons, nonFSR_DYToMuMu_miniTree_allmuons, QCDMu_miniTree_allmuons, TTJets_miniTree_allmuons, "Ptmumu", "Ptmumu", "(100,0,200)", "isMM", "dimuon", "p_{T}^{#mu#mu} [GeV]", true, false, c1);

	vector<string> set_of_cuts;
	vector<string> name;

	set_of_cuts.push_back("isLooseMMG");
  name.push_back("selected-loose");
	set_of_cuts.push_back("isLooseMMG && Photon_isEB");
  name.push_back("selected-loose-EB");
	set_of_cuts.push_back("isLooseMMG && Photon_isEE");
  name.push_back("selected-loose-EE");
	set_of_cuts.push_back("isTightMMG");
  name.push_back("selected-tight");
	set_of_cuts.push_back("isTightMMG && Photon_isEB");
  name.push_back("selected-tight-EB");
	set_of_cuts.push_back("isTightMMG && Photon_isEE");
  name.push_back("selected-tight-EE");


	for(int i=0; i<set_of_cuts.size() ; i++)
	{
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Ptmumu", "Ptmumu", "(100,0,200)", set_of_cuts[i], name[i], "p_{T}^{#mu#mu} [GeV]", true, false, c1);
/*
		DrawDataMCplot_TH1I(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "NbMuons", "NbMuons", "(10,0,10)", set_of_cuts[i], name[i], "# of muons", true, false, c1);
		DrawDataMCplot_TH1I(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "NbPhotons", "NbPhotons", "(10,0,10)", set_of_cuts[i], name[i], "# of photons", true, false, c1);

*/
/*

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "MuonL_Pt", "MuonL_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{leading} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "MuonS_Pt", "MuonS_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{trailing} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "MuonL_Eta", "MuonL_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "MuonS_Eta", "MuonS_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{trailing}", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "MuonL_Phi", "MuonL_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "MuonS_Phi", "MuonS_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{trailing}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "MuonL_Charge", "MuonL_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{leading}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "MuonS_Charge", "MuonS_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{trailing}", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "MuonF_Pt", "MuonF_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{far} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "MuonN_Pt", "MuonN_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{near} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "MuonF_Eta", "MuonF_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "MuonN_Eta", "MuonN_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{near}", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "MuonF_Phi", "MuonF_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "MuonN_Phi", "MuonN_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{near}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "MuonF_Charge", "MuonF_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{far}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "MuonN_Charge", "MuonN_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{near}", true, false, c1);
*/
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Mmumu", "Mmumu", "(150,0,300)", set_of_cuts[i], name[i], "M_{#mu#mu} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Mmumu", "Mmumu_extended", "(30,30,90)", set_of_cuts[i], name[i], "M_{#mu#mu} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Mmumugamma", "Mmumugamma", "(300,0,300)", set_of_cuts[i], name[i], "M_{#mu#mu#gamma} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Mmumugamma", "Mmumugamma_extended", "(60,60,120)", set_of_cuts[i], name[i], "M_{#mu#mu#gamma} [GeV]", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Mmumugamma_SCraw", "Mmumugamma_SCraw", "(60,60,120)", set_of_cuts[i], name[i], "M_{#mu#mu#gamma}^{SCraw} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Mmumugamma_SCraw_fEta", "Mmumugamma_SCraw_fEta", "(60,60,120)", set_of_cuts[i], name[i], "M_{#mu#mu#gamma}^{SCraw x fEta} [GeV]", true, false, c1);
	

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "deltaRNear", "deltaRNear", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{near})", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "deltaRFar", "deltaRFar", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{far})", true, false, c1);
//		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "deltaRPlus", "deltaRPlus", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{plus})", true, false, c1);
//		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "deltaRMinus", "deltaRMinus", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{minus})", true, false, c1);
//		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "deltaRLeading", "deltaRLeading", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{leading})", true, false, c1);
//		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "deltaRSubleading", "deltaRSubleading", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{trailing})", true, false, c1);


//		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Photon_Eta", "Photon_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta^{#gamma}", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Photon_Eta", "Photon_Eta", "(16,-3.2,3.2)", set_of_cuts[i], name[i], "#eta^{#gamma}", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Photon_Phi", "Photon_Phi", "(21,-3.15,3.15)", set_of_cuts[i], name[i], "#phi^{#gamma}", true, false, c1);

/*
*/
//		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Photon_E", "Photon_E", "(100, 0, 100)", set_of_cuts[i], name[i], "E^{#gamma} [GeV]", true, false, c1);
//		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Photon_E", "Photon_E_extended", "(100, 0, 150)", set_of_cuts[i], name[i], "E^{#gamma} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Photon_E", "Photon_E", "(50, 0, 250)", set_of_cuts[i], name[i], "E^{#gamma} [GeV]", true, false, c1);

//		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Photon_Et", "Photon_Et", "(100, 0, 100)", set_of_cuts[i], name[i], "E_{T}^{#gamma} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Photon_Et", "Photon_Et", "(50, 0, 100)", set_of_cuts[i], name[i], "E_{T}^{#gamma} [GeV]", true, false, c1);
/*
		DrawDataMCplot_TH2F(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Mmumu", "Mmumugamma", "(900,0,300,900,0,300)", set_of_cuts[i], name[i], "M_{#mu#mu} [GeV]", "M_{#mu#mu#gamma} [GeV]", "Mmumu_VS_Mmumugamma", false, false, c1);
		DrawDataMCplot_TH2F(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Mmumu", "Mmumugamma", "(450,20,100,450,80,110)", set_of_cuts[i], name[i], "M_{#mu#mu} [GeV]", "M_{#mu#mu#gamma} [GeV]", "Mmumu_VS_Mmumugamma_extended", false, false, c1);

DrawDataMCplot_TH2F(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "((91.1876**2 - Mmumu**2 ) / (Mmumugamma**2 - Mmumu**2))*Photon_E", "Photon_E", "(400,0,100,400,0,100)", set_of_cuts[i], name[i], "E_{true} = k*E_{reco} [GeV]", "E_{reco} [GeV]", "Etrue_VS_Ereco", false, false, c1, true);
DrawDataMCplot_TH2F(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "((91.1876**2 - Mmumu**2 ) / (Mmumugamma**2 - Mmumu**2))*Photon_E", "Photon_E", "(600,0,150,600,0,150)", set_of_cuts[i], name[i], "E_{true} = k*E_{reco} [GeV]", "E_{reco} [GeV]", "Etrue_VS_Ereco_extended", false, false, c1, true);
*/


	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "mmg_k", "mmg_k", "(40,0,2.0)", set_of_cuts[i], name[i], "k = E_{muons} / E_{reco}", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "mmg_s", "mmg_s", "(40,-1.0,1.0)", set_of_cuts[i], name[i], "s = 1 - E_{reco} / E_{muons}", true, false, c1);

	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "mmg_k", "mmg_k_extended", "(20,0,2.0)", set_of_cuts[i], name[i], "k = E_{muons} / E_{reco}", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "mmg_s", "mmg_s_extended", "(20,-1.0,1.0)", set_of_cuts[i], name[i], "s = 1 - E_{reco} / E_{muons}", true, false, c1);

	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "mmg_k_SCraw", "mmg_k_SCraw", "(20,0,2.0)", set_of_cuts[i], name[i], "k_{SCraw} = E_{muons} / E_{SCraw}", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "mmg_s_SCraw", "mmg_s_SCraw", "(20,0,2.0)", set_of_cuts[i], name[i], "s_{SCraw} = 1 - E_{SCraw} / E_{muons}", true, false, c1);

	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "mmg_k_SCraw_fEta", "mmg_k_SCraw_fEta", "(20,0,2.0)", set_of_cuts[i], name[i], "k_{SCraw x fEta} = E_{muons} / E_{SCraw x fEta}", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "mmg_s_SCraw_fEta", "mmg_s_SCraw_fEta", "(20,0,2.0)", set_of_cuts[i], name[i], "s_{SCraw x fEta} = 1 -  E_{SCraw x fEta} /  E_{muons}", true, false, c1);

/*
//DrawDataMCplot_TH2F(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Photon_convNTracks", "MuonN_isoR03_sumPt", "(16,0,4,200,0,10)", set_of_cuts[i], name[i], "Photon_convNTracks", "MuonN_isoR03_sumPt", "Photon_convNTracks_VS_MuonN_isoR03_sumPt", false, false, c1, false);
//DrawDataMCplot_TH2F(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "Photon_convNTracks", "MuonN_isoR03_sumPt", "(12,0,3,200,0,3)", set_of_cuts[i], name[i], "Photon_convNTracks", "MuonN_isoR03_sumPt", "Photon_convNTracks_VS_MuonN_isoR03_sumPt_extended", false, false, c1, false);
	//	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, "MuonN_isoR03_sumPt", "MuonN_isoR03_sumPt", "(100,0,10)", set_of_cuts[i], name[i], "MuonN_isoR03_sumPt", true, false, c1);
*/
	}
	return 0;	
}

