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

//#include "interface/TRootBardak.h"
//#include "interface/TRootBeamSpot.h"
//#include "interface/TRootCluster.h"
//#include "interface/TRootEcalRecHit.h"
//#include "interface/TRootElectron.h"
//#include "interface/TRootEvent.h"
//#include "interface/TRootJet.h"
//#include "interface/TRootMCParticle.h"
//#include "interface/TRootMCPhoton.h"
//#include "interface/TRootMET.h"
//#include "interface/TRootMuon.h"
//#include "interface/TRootParticle.h"
//#include "interface/TRootPhoton.h"
//#include "interface/TRootRun.h"
//#include "interface/TRootSignalEvent.h"
//#include "interface/TRootSuperCluster.h"
//#include "interface/TRootTopTop.h"
//#include "interface/TRootTrack.h"
//#include "interface/TRootVertex.h"



#pragma optimize 0

using namespace std;
	
//int plotDataMC_TDR_miniTree()
int main()
{
	string selection = "loose";
//	gSystem->Load("libToto.so");
	gROOT->ProcessLine(".x setTDRStyle.C");
//	string Data = "miniTree_v2_DATA_2011_ALL.root"; 
//	string Data = "miniTree_v2_DoubleMu-Run2011A_160404-163369_vALL_v02.root"; 
//	string Data = "miniTree_v2_DoubleMu-Run2011A_160404-163757_vALL.root";
//	string Data = "miniTree_v4_DoubleMu-Run2011A_160404-163869_vALL.root";
	string Data = "miniTree_v2_Run2011A-PromptReco-v4_June17_ALL.root";
	string FSR_DYToMuMu = "miniTree_v2_FSR_DYToMuMu_M-20_TuneZ2_7TeV-pythia6_v3.root";
	string nonFSR_DYToMuMu = "miniTree_v2_nonFSR_DYToMuMu_M-20_TuneZ2_7TeV-pythia6_v3.root";
	string TTJets = "miniTree_v2_TT_TuneZ2_7TeV-pythia6-tauola.root";
	string WJetsToLNu = "miniTree_v2_WToMuNu_TuneZ2_7TeV-pythia6.root";
	string QCDMu = "miniTree_v2_QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6.root"; 

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
	TFile *WJetsToLNu_File = new TFile(WJetsToLNu.c_str());
	TTree* WJetsToLNu_miniTree = (TTree*) WJetsToLNu_File->Get("miniTree");
	TTree* WJetsToLNu_miniTree_allmuons = (TTree*) WJetsToLNu_File->Get("miniTree_allmuons");
	TTree* WJetsToLNu_miniTree_allphotons = (TTree*) WJetsToLNu_File->Get("miniTree_allphotons");

	TFile *QCDMu_File = new TFile(QCDMu.c_str());
	TTree* QCDMu_miniTree = (TTree*) QCDMu_File->Get("miniTree");
	TTree* QCDMu_miniTree_allmuons = (TTree*) QCDMu_File->Get("miniTree_allmuons");
	TTree* QCDMu_miniTree_allphotons = (TTree*) QCDMu_File->Get("miniTree_allphotons");


	TCanvas *c1 = new TCanvas("Default", "Default");

//	DrawDataMCplot(Data_miniTree_allmuons, FSR_DYToMuMu_miniTree_allmuons, nonFSR_DYToMuMu_miniTree_allmuons, QCDMu_miniTree_allmuons, TTJets_miniTree_allmuons, WJetsToLNu_miniTree_allmuons, "Ptmumu", "Ptmumu", "(100,0,200)", "isMM", "dimuon", "p_{T}^{#mu#mu} [GeV]", true, false, c1);

	vector<string> set_of_cuts;
	vector<string> name;


	set_of_cuts.push_back("isMMGCandidate");
	name.push_back("selected-00-beforeFSRcuts");
	set_of_cuts.push_back("isAfterFSRCut1");
	name.push_back("selected-01");
	set_of_cuts.push_back("isAfterFSRCut2");
	name.push_back("selected-02");
	set_of_cuts.push_back("isAfterFSRCut3");
	name.push_back("selected-03");
	set_of_cuts.push_back("isAfterFSRCut4");
	name.push_back("selected-04");
	set_of_cuts.push_back("isVeryLooseMMG");
	name.push_back("selected-veryloose");


	set_of_cuts.push_back("isLooseMMG");
  name.push_back("selected-loose");
	set_of_cuts.push_back("isLooseMMG && Photon_isEB");
  name.push_back("selected-loose-EB");
	set_of_cuts.push_back("isLooseMMG && Photon_isEB && Photon_r9 < .94");
  name.push_back("selected-loose-EB-lowR9");
	set_of_cuts.push_back("isLooseMMG && Photon_isEB && Photon_r9 > .94");
  name.push_back("selected-loose-EB-highR9");
	set_of_cuts.push_back("isLooseMMG && Photon_isEE");
  name.push_back("selected-loose-EE");
	set_of_cuts.push_back("isLooseMMG && Photon_isEE && Photon_r9 < .95");
  name.push_back("selected-loose-EE-lowR9");
	set_of_cuts.push_back("isLooseMMG && Photon_isEE && Photon_r9 > .95");
  name.push_back("selected-loose-EE-highR9");
/*
	set_of_cuts.push_back("isTightMMG");
  name.push_back("selected-tight");
	set_of_cuts.push_back("isTightMMG && Photon_isEB");
  name.push_back("selected-tight-EB");
	set_of_cuts.push_back("isTightMMG && Photon_isEB && Photon_r9 < .94");
  name.push_back("selected-tight-EB-lowR9");
	set_of_cuts.push_back("isTightMMG && Photon_isEB && Photon_r9 > .94");
  name.push_back("selected-tight-EB-highR9");
	set_of_cuts.push_back("isTightMMG && Photon_isEE");
  name.push_back("selected-tight-EE");
	set_of_cuts.push_back("isTightMMG && Photon_isEE && Photon_r9 < .95");
  name.push_back("selected-tight-EE-lowR9");
	set_of_cuts.push_back("isTightMMG && Photon_isEE && Photon_r9 > .95");
  name.push_back("selected-tight-EE-highR9");

	
set_of_cuts.push_back("isLooseMMG && isMultipleCandidate==0");
  name.push_back("selected-loose-nomultiple");
	set_of_cuts.push_back("isLooseMMG && Photon_isEB && isMultipleCandidate==0");
  name.push_back("selected-loose-EB-nomultiple");
	set_of_cuts.push_back("isLooseMMG && Photon_isEE && isMultipleCandidate==0");
  name.push_back("selected-loose-EE-nomultiple");
	set_of_cuts.push_back("isTightMMG && isMultipleCandidate==0");
  name.push_back("selected-tight-nomultiple");
	set_of_cuts.push_back("isTightMMG && Photon_isEB && isMultipleCandidate==0");
  name.push_back("selected-tight-EB-nomultiple");
	set_of_cuts.push_back("isTightMMG && Photon_isEE && isMultipleCandidate==0");
  name.push_back("selected-tight-EE-nomultiple");

	set_of_cuts.push_back("isTightMMG && isMultipleCandidate==0 && Photon_hasPixelSeed == 0 && Photon_dR04isoHollowTrkCone < 2.0 && Photon_dR04isoEcalRecHit < 4.2 && Photon_dR04isoHcalRecHit < 2.2 && Photon_Et > 30.0 && ((Photon_isEB && Photon_sigmaIetaIeta < .01) || (Photon_isEE && Photon_sigmaIetaIeta < .03) ) && Photon_HoE < 0.05");
  name.push_back("selected-tight-EGM-10-006-pt30");
	set_of_cuts.push_back("isTightMMG && isMultipleCandidate==0 && Photon_hasPixelSeed == 0 && Photon_dR04isoHollowTrkCone < 2.0 && Photon_dR04isoEcalRecHit < 4.2 && Photon_dR04isoHcalRecHit < 2.2 && Photon_Et > 30.0 && ((Photon_isEB && Photon_sigmaIetaIeta < .01) || (Photon_isEE && Photon_sigmaIetaIeta < .03) ) && Photon_HoE < 0.05 && Photon_isEB");
  name.push_back("selected-tight-EGM-10-006-pt30-EB");
	set_of_cuts.push_back("isTightMMG && isMultipleCandidate==0 && Photon_hasPixelSeed == 0 && Photon_dR04isoHollowTrkCone < 2.0 && Photon_dR04isoEcalRecHit < 4.2 && Photon_dR04isoHcalRecHit < 2.2 && Photon_Et > 30.0 && ((Photon_isEB && Photon_sigmaIetaIeta < .01) || (Photon_isEE && Photon_sigmaIetaIeta < .03) ) && Photon_HoE < 0.05 && Photon_isEE");
  name.push_back("selected-tight-EGM-10-006-pt30-EE");

	set_of_cuts.push_back("isTightMMG && isMultipleCandidate==0 && Photon_hasPixelSeed == 0 && Photon_dR04isoHollowTrkCone < 2.0 && Photon_dR04isoEcalRecHit < 4.2 && Photon_dR04isoHcalRecHit < 2.2 && Photon_Et > 20.0 && ((Photon_isEB && Photon_sigmaIetaIeta < .01) || (Photon_isEE && Photon_sigmaIetaIeta < .03) ) && Photon_HoE < 0.05");
  name.push_back("selected-tight-EGM-10-006-pt20");
	set_of_cuts.push_back("isTightMMG && isMultipleCandidate==0 && Photon_hasPixelSeed == 0 && Photon_dR04isoHollowTrkCone < 2.0 && Photon_dR04isoEcalRecHit < 4.2 && Photon_dR04isoHcalRecHit < 2.2 && Photon_Et > 20.0 && ((Photon_isEB && Photon_sigmaIetaIeta < .01) || (Photon_isEE && Photon_sigmaIetaIeta < .03) ) && Photon_HoE < 0.05 && Photon_isEB");
  name.push_back("selected-tight-EGM-10-006-pt20-EB");
	set_of_cuts.push_back("isTightMMG && isMultipleCandidate==0 && Photon_hasPixelSeed == 0 && Photon_dR04isoHollowTrkCone < 2.0 && Photon_dR04isoEcalRecHit < 4.2 && Photon_dR04isoHcalRecHit < 2.2 && Photon_Et > 20.0 && ((Photon_isEB && Photon_sigmaIetaIeta < .01) || (Photon_isEE && Photon_sigmaIetaIeta < .03) ) && Photon_HoE < 0.05 && Photon_isEE");
  name.push_back("selected-tight-EGM-10-006-pt20-EE");


string selection_ID[9];
string name_selection_ID[9];
  selection_ID[0] = "(abs(Photon_SC_Eta)<=2.5)";
	name_selection_ID[0] = "wo-eta";
  selection_ID[1] =  "Photon_hasPixelSeed==0";
	name_selection_ID[1] =  "wo-hasPixelSeed";
  selection_ID[2] =  "Photon_dR04isoHollowTrkCone<2";
	name_selection_ID[2] =  "wo-dR04isoHollowTrkCone";
  selection_ID[3] =  "Photon_dR04isoEcalRecHit<4.2";
	name_selection_ID[3] =  "wo-dR04isoEcalRecHit";
  selection_ID[4] =  "Photon_dR04isoHcalRecHit<2.2";
	name_selection_ID[4] =  "wo-dR04isoHcalRecHit";
  selection_ID[5] =  "Photon_Et>30";
	name_selection_ID[5] =  "wo-pt30";
  selection_ID[6] =   "(((Photon_isEB==1)&&(Photon_sigmaIetaIeta<0.01))||((Photon_isEE==1)&&(Photon_sigmaIetaIeta<0.03)))";
	name_selection_ID[6] =   "wo-sigmaIetaIeta";
  selection_ID[7] =   "Photon_HoE<0.05";
	name_selection_ID[7] =   "wo-HoE";
  selection_ID[8] =   "(!((abs(Photon_SC_Eta)>1.4442)&&(abs(Photon_SC_Eta)<1.566)))";
	name_selection_ID[8] =   "wo-crack";

for(int j=0; j < 9; j++)
{
	string temp = "isTightMMG && isMultipleCandidate==0";
	string name_temp = "selected-tight-EGM-10-006-";
	for(int k = 0; k < 9; k++ )
	{
		if( k == j )
		{
			name_temp += name_selection_ID[k];
			continue;
		}
		temp += "&&" + selection_ID[k];
	}
//	cout << name_temp << "\t\t\t" << temp << endl;
	set_of_cuts.push_back(temp);
	name.push_back(name_temp);
}
*/


	for(int i=0; i<set_of_cuts.size() ; i++)
	{
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_dR04isoHollowTrkCone - MuonN_Pt", "Photon_dR04isoHollowTrkCone_minusMuonTrack", "(100, -1.0, 10.0)", set_of_cuts[i], name[i], "dR04isoHollowTrkCone - p_{T}^{#mu near}", true, false, c1);
	
//	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Ptmumu", "Ptmumu", "(100,0,200)", set_of_cuts[i], name[i], "p_{T}^{#mu#mu} [GeV]", true, false, c1);


		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Mmumu", "Mmumu", "(150,0,300)", set_of_cuts[i], name[i], "m_{#mu#mu} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Mmumu", "Mmumu_extended", "(30,30,90)", set_of_cuts[i], name[i], "m_{#mu#mu} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Mmumugamma", "Mmumugamma", "(300,0,300)", set_of_cuts[i], name[i], "m_{#mu#mu#gamma} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Mmumugamma", "Mmumugamma_extended", "(60,60,120)", set_of_cuts[i], name[i], "m_{#mu#mu#gamma} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Mmumugamma", "Mmumugamma_zoom", "(48,85,97)", set_of_cuts[i], name[i], "m_{#mu#mu#gamma} [GeV]", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Mmumugamma_5x5", "Mmumugamma_5x5", "(50,0,200)", set_of_cuts[i], name[i], "m_{#mu#mu#gamma}^{5x5} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Mmumugamma_SC", "Mmumugamma_SC", "(50,0,200)", set_of_cuts[i], name[i], "m_{#mu#mu#gamma}^{SC} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Mmumugamma_SCraw", "Mmumugamma_SCraw", "(50,0,200)", set_of_cuts[i], name[i], "m_{#mu#mu#gamma}^{SCraw} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Mmumugamma_SCraw_fEta", "Mmumugamma_SCraw_fEta", "(50,0,200)", set_of_cuts[i], name[i], "m_{#mu#mu#gamma}^{SCraw x fEta} [GeV]", true, false, c1);
	

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "deltaRNear", "deltaRNear", "(100,0,1)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{near})", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "deltaRFar", "deltaRFar", "(100,0,5)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{far})", true, false, c1);


		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_Eta", "Photon_Eta", "(16,-3.2,3.2)", set_of_cuts[i], name[i], "#eta^{#gamma}", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_Phi", "Photon_Phi", "(21,-3.15,3.15)", set_of_cuts[i], name[i], "#phi^{#gamma}", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_E", "Photon_E", "(50, 0, 300)", set_of_cuts[i], name[i], "E^{#gamma} [GeV]", true, false, c1);

		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_Et", "Photon_Et", "(50, 0, 250)", set_of_cuts[i], name[i], "E_{T}^{#gamma} [GeV]", true, false, c1);
		DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_Et", "Photon_Et_finer", "(150, 0, 150)", set_of_cuts[i], name[i], "E_{T}^{#gamma} [GeV]", true, false, c1);

	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "mmg_k", "mmg_k", "(40,0,2.0)", set_of_cuts[i], name[i], "k = E_{muons} / E_{reco}", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "mmg_s", "mmg_s", "(40,-1.0,1.0)", set_of_cuts[i], name[i], "s = E_{reco} / E_{muons} - 1", true, false, c1);

	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "mmg_k", "mmg_k_extended", "(20,0,2.0)", set_of_cuts[i], name[i], "k = E_{muons} / E_{reco}", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "mmg_s", "mmg_s_extended", "(20,-1.0,1.0)", set_of_cuts[i], name[i], "s = E_{reco} / E_{muons} - 1", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "mmg_k", "mmg_k_zoom", "(20,0.6,1.6)", set_of_cuts[i], name[i], "k = E_{muons} / E_{reco}", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "mmg_s", "mmg_s_zoom", "(20,-0.5,0.5)", set_of_cuts[i], name[i], "s = E_{reco} / E_{muons} - 1", true, false, c1);

	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "mmg_k_SCraw", "mmg_k_SCraw", "(60,-1.0,3.0)", set_of_cuts[i], name[i], "k_{SCraw} = E_{muons} / E_{SCraw}", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "mmg_s_SCraw", "mmg_s_SCraw", "(60,-2.0,2.0)", set_of_cuts[i], name[i], "s_{SCraw} = E_{SCraw} / E_{muons} - 1", true, false, c1);

	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "mmg_k_SCraw_fEta", "mmg_k_SCraw_fEta", "(60,-1.0,3.0)", set_of_cuts[i], name[i], "k_{SCraw x fEta} = E_{muons} / E_{SCraw x fEta}", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "mmg_s_SCraw_fEta", "mmg_s_SCraw_fEta", "(60,-2.0,2.0)", set_of_cuts[i], name[i], "s_{SCraw x fEta} = E_{SCraw x fEta} /  E_{muons} - 1", true, false, c1);

// Event Pile-up variable
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "nVertices", "nVertices", "(30.0, .0, 30.0)", set_of_cuts[i], name[i], "nVertices", true, false, c1);

// Cluster shape variables
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_hasPixelSeed", "Photon_hasPixelSeed", "(4, -1.0, 3.0)", set_of_cuts[i], name[i], "hasPixelSeed", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_isAlsoElectron", "Photon_isAlsoElectron", "(4, -1.0, 3.0)", set_of_cuts[i], name[i], "isAlsoElectron", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_convNTracks", "Photon_convNTracks", "(5, 0.0, 5.0)", set_of_cuts[i], name[i], "convNTracks", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_r9", "Photon_r9", "(40,0.0,1.2)", set_of_cuts[i], name[i], "E^{3x3} / E^{SC}", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_r19", "Photon_r19", "(50, .0, 1.0)", set_of_cuts[i], name[i], "r19", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_HoE", "Photon_HoE", "(100, -0.1, 0.6)", set_of_cuts[i], name[i], "HoE", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_sigmaEtaEta", "Photon_sigmaEtaEta", "(100, 0.0, 0.06)", set_of_cuts[i], name[i], "#sigma_{#eta #eta}", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_sigmaIetaIeta", "Photon_sigmaIetaIeta", "(100, 0.0, 0.07)", set_of_cuts[i], name[i], "#sigma_{i#eta i#eta}", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_covEtaEta", "Photon_covEtaEta", "(100, -0.005, 0.005)", set_of_cuts[i], name[i], "covEtaEta", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_covPhiPhi", "Photon_covPhiPhi", "(100, -0.005, 0.005)", set_of_cuts[i], name[i], "covPhiPhi", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_covEtaPhi", "Photon_covEtaPhi", "(100, -0.005, 0.005)", set_of_cuts[i], name[i], "covEtaPhi", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_etaWidth", "Photon_etaWidth", "(100, 0.0, 0.06)", set_of_cuts[i], name[i], "etaWidth", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_phiWidth", "Photon_phiWidth", "(100, 0.0, 0.25)", set_of_cuts[i], name[i], "phiWidth", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_dR04isoEcalRecHit", "Photon_dR04isoEcalRecHit", "(100, -3.0, 15.0)", set_of_cuts[i], name[i], "dR04isoEcalRecHit", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_dR04isoHcalRecHit", "Photon_dR04isoHcalRecHit", "(100, -1.0, 15.0)", set_of_cuts[i], name[i], "dR04isoHcalRecHit", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_dR04isoHollowTrkCone", "Photon_dR04isoHollowTrkCone", "(100, -1.0, 10.0)", set_of_cuts[i], name[i], "dR04isoHollowTrkCone", true, false, c1);
	DrawDataMCplot(Data_miniTree, FSR_DYToMuMu_miniTree, nonFSR_DYToMuMu_miniTree, QCDMu_miniTree, TTJets_miniTree, WJetsToLNu_miniTree, "Photon_SC_brem", "Photon_SC_brem", "(100, .0, 20.0)", set_of_cuts[i], name[i], "SC brem", true, false, c1);


	}
	return 0;	
}

