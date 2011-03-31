#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TBranch.h"
#include "TChain.h"
#include "TFile.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TString.h"
#include "TBits.h"
#include "TMath.h"
#include "TSystem.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <utility>
#pragma optimize 0

#include "interface/TRootBardak.h"
#include "interface/TRootBeamSpot.h"
#include "interface/TRootCluster.h"
#include "interface/TRootDummyEvent.h"
#include "interface/TRootEcalRecHit.h"
#include "interface/TRootElectron.h"
#include "interface/TRootEvent.h"
#include "interface/TRootJet.h"
#include "interface/TRootMCParticle.h"
#include "interface/TRootMCPhoton.h"
#include "interface/TRootMET.h"
#include "interface/TRootMuon.h"
#include "interface/TRootParticle.h"
#include "interface/TRootPhoton.h"
#include "interface/TRootRun.h"
#include "interface/TRootSignalEvent.h"
#include "interface/TRootSuperCluster.h"
#include "interface/TRootTopTop.h"
#include "interface/TRootTrack.h"
#include "interface/TRootVertex.h"

int factorial(int number) {
	int temp;

	if(number <= 1) return 1;

	temp = number * factorial(number - 1);
	return temp;
}


double DeltaR( double eta1, double phi1, double eta2, double phi2)
{
	double DeltaEta = fabs( eta1-eta2 );
	double DeltaPhi = fabs( phi1-phi2 );
	// Returning DeltaPhi in the correct range (0, 2pi)
	while (DeltaPhi >	 TMath::Pi()) DeltaPhi -= 2*TMath::Pi();
	while (DeltaPhi <= -TMath::Pi()) DeltaPhi += 2*TMath::Pi();
	return sqrt(DeltaEta*DeltaEta + DeltaPhi*DeltaPhi);
}

//int Selection_miniTree()
int main(int argc, char *argv[])
{
	cout << "argc= " << argc << endl;
	for(int iarg = 0 ; iarg < argc; iarg++)
	{
		cout << "argv[" << iarg << "]= " << argv[iarg] << endl;
	}
	
	if( argc == 1 )
	{
		cerr << "arguments should be passed !! sample (outputname) (isZgammaMC) (extra scale) (extra resolution)" << endl;
		return 1;
	}
	// First argument is sample
	char* sample_char = argv[1];

	// Optional argument : output root file
	string sample = argv[1];
	if( argc > 2 )
	{
		sample = argv[2];
	}

	// Optional argument : isZgammaMC
	int isZgammaMC = 0;
	if( argc > 3 )
	{
		std::stringstream ss ( argv[3] );
		ss >> isZgammaMC;
	}
	
	// Optional argument extra scale
	double EScale = 1.0;
	if( argc > 4 )
	{
		std::stringstream ss ( argv[4] );
		ss >> EScale;
	}
	
// Optional argument is extra resolution
	double EResolution = 0.0;
	// TODO

	gSystem->Load("libToto.so");
	bool doHLT										= true;
	bool doMC										 = (bool)(isZgammaMC >= 1);
	bool doJetMC									= false;
	bool doMETMC									= false;
	bool doPDFInfo								= false;
	bool doSignalMuMuGamma				= (bool)(isZgammaMC >= 1);
	bool doSignalTopTop					 = false;
	bool doPhotonConversionMC		 = false;
	bool doBeamSpot							 = false;
	bool doPrimaryVertex					= true;
	bool doZeePrimaryVertex			 = false;
	bool doTrack									= false;
	bool doJet										= false;
	bool doMuon									 = true;
	bool doElectron							 = false;
	bool doPhoton								 = true;
	bool doCluster								= true;
	bool doPhotonConversion			 = false;
	bool doMET										= false;
	bool doBardak								 = true;
	bool doPhotonVertexCorrection = false;
	bool doPhotonIsolation				= false;

	// DATASET	
	TChain *inputEventTree = new TChain("eventTree");
	TChain *inputRunTree = new TChain("runTree");

	inputEventTree->Add(Form("/sps/cms/obondu/CMSSW_3_9_7_v2/src/Zmumugamma/RecoSamples/%s/%s*root", sample_char, sample_char));
	inputRunTree->Add(Form("/sps/cms/obondu/CMSSW_3_9_7_v2/src/Zmumugamma/RecoSamples/%s/%s*root", sample_char, sample_char));

//	inputEventTree->Add("../RecoSamples/DYToMuMu/DYToMuMu*root");
//	inputRunTree->Add("../RecoSamples/DYToMuMu/DYToMuMu*root");
//	string sample = "DYToMuMu";

/*
	inputEventTree->Add("");
	inputRunTree->Add("");
	string sample = "";
*/

// INSERTFILES
//  string sample = "SAMPLEPART";
//	ofstream outfile("event_dump_SAMPLEPART.out");

	TFile* OutputRootFile = new TFile(Form("miniTree_%s.root", sample.c_str()), "RECREATE");
	
	TBranch* event_br = 0;
	TRootEvent* event = 0;
	inputEventTree->SetBranchAddress("Event", &event, &event_br);
	inputEventTree->SetBranchStatus("Event", 1);

  TBranch* run_br = 0;
  TRootRun* runInfos = 0;
  inputRunTree->SetBranchAddress("runInfos", &runInfos, &run_br);
  inputRunTree->SetBranchStatus("runInfos", 1);
	
	TBranch* mcParticles_br = 0;
	TClonesArray* mcParticles = new TClonesArray("TRootMCParticle", 0);
	if(doMC)
	{
		inputEventTree->SetBranchAddress("MCParticles", &mcParticles, &mcParticles_br);
		inputEventTree->SetBranchStatus("MCParticles", 1);
	}
	
	TBranch* genJets_br = 0;
	TClonesArray* genJets = new TClonesArray("TRootParticle", 0);
	if(doJetMC)
	{
		inputEventTree->SetBranchAddress("genJets", &genJets, &genJets_br);
		inputEventTree->SetBranchStatus("genJets", 1);
	}
	
		TBranch* genMETs_br = 0;
		TClonesArray* genMETs = new TClonesArray("TRootParticle", 0);
	if(doMETMC)
	{
		inputEventTree->SetBranchAddress("genMETs", &genMETs, &genMETs_br);
		inputEventTree->SetBranchStatus("genMETs", 1);
	}
	
		TBranch* mcSignalMuMuGamma_br = 0;
		TRootSignalEvent* mcMuMuGammaEvent = 0;
	if(doSignalMuMuGamma)
	{
		inputEventTree->SetBranchAddress("MuMuGamma", &mcMuMuGammaEvent, &mcSignalMuMuGamma_br);
		inputEventTree->SetBranchStatus("MuMuGamma", 1);
	}
	
		TBranch* mcTopTopEvent_br = 0;
		TRootSignalEvent* mcTopTopEvent = 0;
	if(doSignalTopTop)
	{
		inputEventTree->SetBranchAddress("rootMCTopTop", &mcTopTopEvent, &mcTopTopEvent_br);
		inputEventTree->SetBranchStatus("rootMCTopTop", 1);
	}
	
		TBranch* mcPhotons_br = 0;
		TClonesArray* mcPhotons = new TClonesArray("TRootMCPhoton", 0);
	if(doPhotonConversionMC)
	{
		inputEventTree->SetBranchAddress("MCPhotons", &mcPhotons, &mcPhotons_br);
		inputEventTree->SetBranchStatus("MCPhotons", 1);
	}
	
		TBranch* beamSpot_br = 0;
		TRootBeamSpot* beamSpot = 0;
	if(doBeamSpot)
	{
		inputEventTree->SetBranchAddress("BeamSpot", &beamSpot, &beamSpot_br);
		inputEventTree->SetBranchStatus("BeamSpot", 1);
	}
	
		TBranch* vertices_br = 0;
		TClonesArray* vertices = new TClonesArray("TRootVertex", 0);
	if(doPrimaryVertex)
	{
		inputEventTree->SetBranchAddress("Vertices", &vertices, &vertices_br);
		inputEventTree->SetBranchStatus("Vertices", 1);
	}
	
		TBranch* zeeVertices_br = 0;
		TClonesArray* zeeVertices = new TClonesArray("TRootVertex", 0);
	if(doZeePrimaryVertex)
	{
		inputEventTree->SetBranchAddress("ZeeVertices", &zeeVertices, &zeeVertices_br);
		inputEventTree->SetBranchStatus("ZeeVertices", 1);
	}
	
		TBranch* tracks_br = 0;
		TClonesArray* tracks = new TClonesArray("TRootTrack", 0);
	if(doTrack)
	{
		inputEventTree->SetBranchAddress("Tracks", &tracks, &tracks_br);
		inputEventTree->SetBranchStatus("Tracks", 1);
	}
	
		TBranch* jets_br = 0;
		TClonesArray* jets = new TClonesArray("TRootJet", 0);
	if(doJet)	{
		inputEventTree->SetBranchAddress("ak5CaloJets", &jets, &jets_br);
		inputEventTree->SetBranchStatus("ak5CaloJets", 1);
	}
	
		TBranch* muons_br = 0;
		TClonesArray* muons = new TClonesArray("TRootMuon", 0);
	if(doMuon)
	{
		inputEventTree->SetBranchAddress("muons", &muons, &muons_br);
		inputEventTree->SetBranchStatus("muons", 1);
	}
	
		TBranch* electrons_br = 0;
		TClonesArray* electrons = new TClonesArray("TRootElectron", 0);
	if(doElectron)
	{
		inputEventTree->SetBranchAddress("gsfElectrons", &electrons, &electrons_br);
		inputEventTree->SetBranchStatus("gsfElectrons", 1);
	}
	
		TBranch* photons_br = 0;
		TClonesArray* photons = new TClonesArray("TRootPhoton", 0);
	if(doPhoton)
	{
		inputEventTree->SetBranchAddress("photons", &photons, &photons_br);
		inputEventTree->SetBranchStatus("photons", 1);
	}
	
		TBranch* clusters_br = 0;
		TClonesArray* clusters = new TClonesArray("TRootCluster", 0);
	if(doCluster)
	{
		inputEventTree->SetBranchAddress("BasicClusters", &clusters, &clusters_br);
		inputEventTree->SetBranchStatus("BasicClusters", 1);
	}
	
		TBranch* superClusters_br = 0;
		TClonesArray* superClusters = new TClonesArray("TRootSuperCluster", 0);
	if(doCluster)
	{
		inputEventTree->SetBranchAddress("SuperClusters", &superClusters, &superClusters_br);
		inputEventTree->SetBranchStatus("SuperClusters", 1);
	}
	
		TBranch* conversions_br = 0;
		TClonesArray* conversionTracks = new TClonesArray("TRootTrack", 0);
	if(doPhotonConversion)
	{
		inputEventTree->SetBranchAddress("ConversionTracks", &conversionTracks, &conversions_br);
		inputEventTree->SetBranchStatus("ConversionTracks", 1);
	}
	
		TBranch* met_br = 0;
		TClonesArray* met = new TClonesArray("TRootMET", 0);
	if(doMET)
	{
		inputEventTree->SetBranchAddress("met", &met, &met_br);
		inputEventTree->SetBranchStatus("met", 1);
	}
	
		TBranch* bardak_br = 0;
		TRootBardak* bardak = 0;
	if(doBardak)
	{
		inputEventTree->SetBranchAddress("Bardak", &bardak, &bardak_br);
		inputEventTree->SetBranchStatus("Bardak", 1);
	}


  int* NumWantedHLTnames;

  string ListWantedHLTnames[1];
	ListWantedHLTnames[0] = "HLT_Mu11";
	
	
	// ____________________________________________
	// Event information
	// ____________________________________________
	Int_t iEvent, iEventID, iLumiID, iRunID;
	Int_t isSignalApplied, isStewApplied, isZJetsApplied;

	Int_t isBeforeAllCuts, isAfterCutPthatFilter, isAfterCutZJETVETO;
	Int_t isLooseMMG, isTightMMG, isAfterCut1c, isAfterCut1d, isAfterCut1e;
	Int_t isAfterCut2a, isAfterCut2b, isAfterCut2c;
	Int_t isAfterCut3, isAfterCut4, isAfterCut5, isAfterCut6, isAfterCut7, isAfterCut8, isAfterCut9, isAfterCut10;
	Int_t isSelected;
	
	Int_t isNotCommissionned;

	Int_t Muon_eventPassHLT_Mu11;
	Int_t nVertices;

	// ____________________________________________
	// Muon variables
	// ____________________________________________
	Int_t NbMuons;

	Float_t Pt_allMuons, Eta_allMuons, Phi_allMuons, Charge_allMuons;
// (M minus charge, P plus charge), (F far, N near), (H high, L low)
	Float_t MuonM_Pt, MuonP_Pt, MuonN_Pt, MuonF_Pt, MuonL_Pt, MuonS_Pt;
	Float_t MuonM_Eta, MuonP_Eta, MuonN_Eta, MuonF_Eta, MuonL_Eta, MuonS_Eta;
	Float_t MuonM_Phi, MuonP_Phi, MuonN_Phi, MuonF_Phi, MuonL_Phi, MuonS_Phi;
	Int_t MuonF_Charge, MuonN_Charge, MuonL_Charge, MuonS_Charge;

	Float_t MuonM_isoR03_emEt, MuonP_isoR03_emEt, MuonN_isoR03_emEt, MuonF_isoR03_emEt, MuonL_isoR03_emEt, MuonS_isoR03_emEt;
	Float_t MuonM_isoR03_hadEt, MuonP_isoR03_hadEt, MuonN_isoR03_hadEt, MuonF_isoR03_hadEt, MuonL_isoR03_hadEt, MuonS_isoR03_hadEt;
	Float_t MuonM_isoR03_hoEt, MuonP_isoR03_hoEt, MuonN_isoR03_hoEt, MuonF_isoR03_hoEt, MuonL_isoR03_hoEt, MuonS_isoR03_hoEt;
	Float_t MuonM_isoR03_nJets, MuonP_isoR03_nJets, MuonN_isoR03_nJets, MuonF_isoR03_nJets, MuonL_isoR03_nJets, MuonS_isoR03_nJets;
	Float_t MuonM_isoR03_nTracks, MuonP_isoR03_nTracks, MuonN_isoR03_nTracks, MuonF_isoR03_nTracks, MuonL_isoR03_nTracks, MuonS_isoR03_nTracks;
	Float_t MuonM_isoR03_sumPt, MuonP_isoR03_sumPt, MuonN_isoR03_sumPt, MuonF_isoR03_sumPt, MuonL_isoR03_sumPt, MuonS_isoR03_sumPt;

	Float_t MuonM_isoR05_emEt, MuonP_isoR05_emEt, MuonN_isoR05_emEt, MuonF_isoR05_emEt, MuonL_isoR05_emEt, MuonS_isoR05_emEt;
	Float_t MuonM_isoR05_hadEt, MuonP_isoR05_hadEt, MuonN_isoR05_hadEt, MuonF_isoR05_hadEt, MuonL_isoR05_hadEt, MuonS_isoR05_hadEt;
	Float_t MuonM_isoR05_hoEt, MuonP_isoR05_hoEt, MuonN_isoR05_hoEt, MuonF_isoR05_hoEt, MuonL_isoR05_hoEt, MuonS_isoR05_hoEt;
	Float_t MuonM_isoR05_nJets, MuonP_isoR05_nJets, MuonN_isoR05_nJets, MuonF_isoR05_nJets, MuonL_isoR05_nJets, MuonS_isoR05_nJets;
	Float_t MuonM_isoR05_nTracks, MuonP_isoR05_nTracks, MuonN_isoR05_nTracks, MuonF_isoR05_nTracks, MuonL_isoR05_nTracks, MuonS_isoR05_nTracks;
	Float_t MuonM_isoR05_sumPt, MuonP_isoR05_sumPt, MuonN_isoR05_sumPt, MuonF_isoR05_sumPt, MuonL_isoR05_sumPt, MuonS_isoR05_sumPt;

	// ____________________________________________
	// Photon variables
	// ___________________________________________
	Int_t NbPhotons;
	Float_t Pt_allPhotons, Eta_allPhotons, Phi_allPhotons, Cross_allPhotons;
	Int_t isEBorEE_allPhotons, isEB_allPhotons, isEE_allPhotons, isEEP_allPhotons, isEEM_allPhotons;
	Float_t Photon_Eta, Photon_Phi;
	Int_t Photon_isEBorEE, Photon_isEB, Photon_isEE, Photon_isEEP, Photon_isEEM;

	Int_t Photon_hasPixelSeed, Photon_isAlsoElectron, Photon_Nclusters, Photon_nBasicClusters, Photon_nXtals;
	Int_t Photon_isTightPhoton, Photon_isLoosePhoton;
	Int_t Photon_convNTracks;
	Float_t Photon_E, Photon_Et, Photon_E2x2, Photon_E3x3, Photon_E5x5, Photon_Emax, Photon_E2nd;
	Float_t Photon_r19, Photon_r9, Photon_cross;
	Float_t Photon_caloConeSize, Photon_PreshEnergy, Photon_HoE;
	Float_t Photon_sigmaEtaEta, Photon_sigmaIetaIeta;
	Float_t Photon_covEtaEta, Photon_covPhiPhi, Photon_covEtaPhi;
	Float_t Photon_etaWidth, Photon_phiWidth;
	Float_t Photon_dR03isoEcalRecHit, Photon_dR03isoHcalRecHit, Photon_dR03isoSolidTrkCone, Photon_dR03isoHollowTrkCone, Photon_dR03isoNTracksSolidCone, Photon_dR03isoNTracksHollowCone;
	Float_t Photon_dR04isoEcalRecHit, Photon_dR04isoHcalRecHit, Photon_dR04isoSolidTrkCone, Photon_dR04isoHollowTrkCone, Photon_dR04isoNTracksSolidCone, Photon_dR04isoNTracksHollowCone;
	Float_t Photon_seedTime, Photon_seedFlag;
	Int_t Photon_seedPosition1, Photon_seedPosition2;
	Float_t Photon_SC_Eta, Photon_SC_Phi, Photon_SC_brem;
	Float_t Photon_SC_E, Photon_SC_Et, Photon_SC_rawE, Photon_SC_rawEt;

	// ____________________________________________
	// mugamma / mumu / mumugamma information
	// ____________________________________________
	
	Float_t Mmumu, Mmumugamma, Mmumugamma_5x5, Mmumugamma_SC, Mmumugamma_SCraw;
	Float_t deltaRNear, deltaRFar, deltaRMinus, deltaRPlus, deltaRLeading, deltaRSubleading;
	Float_t mmg_k, mmg_ik, mmg_s, mmg_logk, mmg_logik, mmg_logs;
	Float_t mmg_k_5x5, mmg_ik_5x5, mmg_s_5x5, mmg_logk_5x5, mmg_logik_5x5, mmg_logs_5x5;
	Float_t mmg_k_SC, mmg_ik_SC, mmg_s_SC, mmg_logk_SC, mmg_logik_SC, mmg_logs_SC;
	Float_t mmg_k_SCraw, mmg_ik_SCraw, mmg_s_SCraw, mmg_logk_SCraw, mmg_logik_SCraw, mmg_logs_SCraw;
 
	// ____________________________________________
	// preparing the tree
	// ____________________________________________

	TTree* miniTree = new TTree("miniTree","Mu Mu Gamma informations");
	TTree* miniTree_allmuons = new TTree("miniTree_allmuons","all muons informations");
	TTree* miniTree_allphotons = new TTree("miniTree_allphotons","all photons informations");
	TTree *outputEventTree = inputEventTree->CloneTree(0);

	// ____________________________________________
	// Event information
	// ____________________________________________
	
	miniTree->Branch("iEvent", &iEvent, "iEvent/I");
	miniTree->Branch("iEventID", &iEventID, "iEventID/I");
	miniTree->Branch("iLumiID", &iLumiID, "iLumiID/I");
	miniTree->Branch("iRunID", &iRunID, "iRunID/I");

	miniTree->Branch("isSignalApplied", &isSignalApplied, "isSignalApplied/I");
	miniTree->Branch("isStewApplied", &isStewApplied, "isStewApplied/I");
	miniTree->Branch("isZJetsApplied", &isZJetsApplied, "isZJetsApplied/I");

	miniTree->Branch("isBeforeAllCuts", &isBeforeAllCuts, "isBeforeAllCuts/I");
	miniTree->Branch("isAfterCutPthatFilter", &isAfterCutPthatFilter, "isAfterCutPthatFilter/I");
	miniTree->Branch("isAfterCutZJETVETO", &isAfterCutZJETVETO, "isAfterCutZJETVETO/I");

	miniTree->Branch("isLooseMMG", &isLooseMMG, "isLooseMMG/I");
	miniTree->Branch("isTightMMG", &isTightMMG, "isTightMMG/I");
	miniTree->Branch("isAfterCut1c", &isAfterCut1c, "isAfterCut1c/I");
	miniTree->Branch("isAfterCut1d", &isAfterCut1d, "isAfterCut1d/I");
	miniTree->Branch("isAfterCut1e", &isAfterCut1e, "isAfterCut1e/I");

	miniTree->Branch("isAfterCut2a", &isAfterCut2a, "isAfterCut2a/I");
	miniTree->Branch("isAfterCut2b", &isAfterCut2b, "isAfterCut2b/I");
	miniTree->Branch("isAfterCut2c", &isAfterCut2c, "isAfterCut2c/I");

	miniTree->Branch("isAfterCut3", &isAfterCut3, "isAfterCut3/I");
	miniTree->Branch("isAfterCut4", &isAfterCut4, "isAfterCut4/I");
	miniTree->Branch("isAfterCut5", &isAfterCut5, "isAfterCut5/I");
	miniTree->Branch("isAfterCut6", &isAfterCut6, "isAfterCut6/I");
	miniTree->Branch("isAfterCut7", &isAfterCut7, "isAfterCut7/I");
	miniTree->Branch("isAfterCut8", &isAfterCut8, "isAfterCut8/I");
	miniTree->Branch("isAfterCut9", &isAfterCut9, "isAfterCut9/I");
	miniTree->Branch("isAfterCut10", &isAfterCut10, "isAfterCut10/I");

	miniTree->Branch("isSelected", &isSelected, "isSelected/I");
	miniTree->Branch("nVertices", &nVertices, "nVertices/I");

	miniTree_allmuons->Branch("iEvent", &iEvent, "iEvent/I");
	miniTree_allmuons->Branch("iEventID", &iEventID, "iEventID/I");
	miniTree_allmuons->Branch("iLumiID", &iLumiID, "iLumiID/I");
	miniTree_allmuons->Branch("iRunID", &iRunID, "iRunID/I");

	miniTree_allmuons->Branch("isSignalApplied", &isSignalApplied, "isSignalApplied/I");
	miniTree_allmuons->Branch("isStewApplied", &isStewApplied, "isStewApplied/I");
	miniTree_allmuons->Branch("isZJetsApplied", &isZJetsApplied, "isZJetsApplied/I");

	miniTree_allmuons->Branch("isBeforeAllCuts", &isBeforeAllCuts, "isBeforeAllCuts/I");
	miniTree_allmuons->Branch("isAfterCutPthatFilter", &isAfterCutPthatFilter, "isAfterCutPthatFilter/I");
	miniTree_allmuons->Branch("isAfterCutZJETVETO", &isAfterCutZJETVETO, "isAfterCutZJETVETO/I");

	miniTree_allmuons->Branch("isLooseMMG", &isLooseMMG, "isLooseMMG/I");
	miniTree_allmuons->Branch("isTightMMG", &isTightMMG, "isTightMMG/I");
	miniTree_allmuons->Branch("isAfterCut1c", &isAfterCut1c, "isAfterCut1c/I");
	miniTree_allmuons->Branch("isAfterCut1d", &isAfterCut1d, "isAfterCut1d/I");
	miniTree_allmuons->Branch("isAfterCut1e", &isAfterCut1e, "isAfterCut1e/I");

	miniTree_allmuons->Branch("isAfterCut2a", &isAfterCut2a, "isAfterCut2a/I");
	miniTree_allmuons->Branch("isAfterCut2b", &isAfterCut2b, "isAfterCut2b/I");
	miniTree_allmuons->Branch("isAfterCut2c", &isAfterCut2c, "isAfterCut2c/I");

	miniTree_allmuons->Branch("isAfterCut3", &isAfterCut3, "isAfterCut3/I");
	miniTree_allmuons->Branch("isAfterCut4", &isAfterCut4, "isAfterCut4/I");
	miniTree_allmuons->Branch("isAfterCut5", &isAfterCut5, "isAfterCut5/I");
	miniTree_allmuons->Branch("isAfterCut6", &isAfterCut6, "isAfterCut6/I");
	miniTree_allmuons->Branch("isAfterCut7", &isAfterCut7, "isAfterCut7/I");
	miniTree_allmuons->Branch("isAfterCut8", &isAfterCut8, "isAfterCut8/I");
	miniTree_allmuons->Branch("isAfterCut9", &isAfterCut9, "isAfterCut9/I");
	miniTree_allmuons->Branch("isAfterCut10", &isAfterCut10, "isAfterCut10/I");

	miniTree_allmuons->Branch("isSelected", &isSelected, "isSelected/I");

	miniTree_allphotons->Branch("iEvent", &iEvent, "iEvent/I");
	miniTree_allphotons->Branch("iEventID", &iEventID, "iEventID/I");
	miniTree_allphotons->Branch("iLumiID", &iLumiID, "iLumiID/I");
	miniTree_allphotons->Branch("iRunID", &iRunID, "iRunID/I");

	miniTree_allphotons->Branch("isSignalApplied", &isSignalApplied, "isSignalApplied/I");
	miniTree_allphotons->Branch("isStewApplied", &isStewApplied, "isStewApplied/I");
	miniTree_allphotons->Branch("isZJetsApplied", &isZJetsApplied, "isZJetsApplied/I");

	miniTree_allphotons->Branch("isBeforeAllCuts", &isBeforeAllCuts, "isBeforeAllCuts/I");
	miniTree_allphotons->Branch("isAfterCutPthatFilter", &isAfterCutPthatFilter, "isAfterCutPthatFilter/I");
	miniTree_allphotons->Branch("isAfterCutZJETVETO", &isAfterCutZJETVETO, "isAfterCutZJETVETO/I");

	miniTree_allphotons->Branch("isLooseMMG", &isLooseMMG, "isLooseMMG/I");
	miniTree_allphotons->Branch("isTightMMG", &isTightMMG, "isTightMMG/I");
	miniTree_allphotons->Branch("isAfterCut1c", &isAfterCut1c, "isAfterCut1c/I");
	miniTree_allphotons->Branch("isAfterCut1d", &isAfterCut1d, "isAfterCut1d/I");
	miniTree_allphotons->Branch("isAfterCut1e", &isAfterCut1e, "isAfterCut1e/I");

	miniTree_allphotons->Branch("isAfterCut2a", &isAfterCut2a, "isAfterCut2a/I");
	miniTree_allphotons->Branch("isAfterCut2b", &isAfterCut2b, "isAfterCut2b/I");
	miniTree_allphotons->Branch("isAfterCut2c", &isAfterCut2c, "isAfterCut2c/I");

	miniTree_allphotons->Branch("isAfterCut3", &isAfterCut3, "isAfterCut3/I");
	miniTree_allphotons->Branch("isAfterCut4", &isAfterCut4, "isAfterCut4/I");
	miniTree_allphotons->Branch("isAfterCut5", &isAfterCut5, "isAfterCut5/I");
	miniTree_allphotons->Branch("isAfterCut6", &isAfterCut6, "isAfterCut6/I");
	miniTree_allphotons->Branch("isAfterCut7", &isAfterCut7, "isAfterCut7/I");
	miniTree_allphotons->Branch("isAfterCut8", &isAfterCut8, "isAfterCut8/I");
	miniTree_allphotons->Branch("isAfterCut9", &isAfterCut9, "isAfterCut9/I");
	miniTree_allphotons->Branch("isAfterCut10", &isAfterCut10, "isAfterCut10/I");

	miniTree_allphotons->Branch("isSelected", &isSelected, "isSelected/I");
	miniTree_allphotons->Branch("isNotCommissionned", &isNotCommissionned, "isNotCommissionned/I");

	// ____________________________________________
	// Muon variables
	// ____________________________________________

	miniTree->Branch("NbMuons", &NbMuons, "NbMuons/I");

	miniTree_allmuons->Branch("Pt_allMuons", &Pt_allMuons, "Pt_allMuons/F");
	miniTree_allmuons->Branch("Eta_allMuons", &Eta_allMuons, "Eta_allMuons/F");
	miniTree_allmuons->Branch("Phi_allMuons", &Phi_allMuons, "Phi_allMuons/F");
	miniTree_allmuons->Branch("Charge_allMuons", &Charge_allMuons, "Charge_allMuons/F");

	miniTree->Branch("MuonM_Pt", &MuonM_Pt, "MuonM_Pt/F");
	miniTree->Branch("MuonP_Pt", &MuonP_Pt, "MuonP_Pt/F");
	miniTree->Branch("MuonF_Pt", &MuonF_Pt, "MuonF_Pt/F");
	miniTree->Branch("MuonN_Pt", &MuonN_Pt, "MuonN_Pt/F");
	miniTree->Branch("MuonL_Pt", &MuonL_Pt, "MuonL_Pt/F");
	miniTree->Branch("MuonS_Pt", &MuonS_Pt, "MuonS_Pt/F");

	miniTree->Branch("MuonM_Eta", &MuonM_Eta, "MuonM_Eta/F");
	miniTree->Branch("MuonP_Eta", &MuonP_Eta, "MuonP_Eta/F");
	miniTree->Branch("MuonF_Eta", &MuonF_Eta, "MuonF_Eta/F");
	miniTree->Branch("MuonN_Eta", &MuonN_Eta, "MuonN_Eta/F");
	miniTree->Branch("MuonL_Eta", &MuonL_Eta, "MuonL_Eta/F");
	miniTree->Branch("MuonS_Eta", &MuonS_Eta, "MuonS_Eta/F");

	miniTree->Branch("MuonM_Phi", &MuonM_Phi, "MuonM_Phi/F");
	miniTree->Branch("MuonP_Phi", &MuonP_Phi, "MuonP_Phi/F");
	miniTree->Branch("MuonF_Phi", &MuonF_Phi, "MuonF_Phi/F");
	miniTree->Branch("MuonN_Phi", &MuonN_Phi, "MuonN_Phi/F");
	miniTree->Branch("MuonL_Phi", &MuonL_Phi, "MuonL_Phi/F");
	miniTree->Branch("MuonS_Phi", &MuonS_Phi, "MuonS_Phi/F");

	miniTree->Branch("MuonF_Charge", &MuonF_Charge, "MuonF_Charge/I");
	miniTree->Branch("MuonN_Charge", &MuonN_Charge, "MuonN_Charge/I");
	miniTree->Branch("MuonL_Charge", &MuonL_Charge, "MuonL_Charge/I");
	miniTree->Branch("MuonS_Charge", &MuonS_Charge, "MuonS_Charge/I");
	
	miniTree->Branch("MuonM_isoR03_emEt", &MuonM_isoR03_emEt, "MuonM_isoR03_emEt/F");
	miniTree->Branch("MuonP_isoR03_emEt", &MuonP_isoR03_emEt, "MuonP_isoR03_emEt/F");
	miniTree->Branch("MuonF_isoR03_emEt", &MuonF_isoR03_emEt, "MuonF_isoR03_emEt/F");
	miniTree->Branch("MuonN_isoR03_emEt", &MuonN_isoR03_emEt, "MuonN_isoR03_emEt/F");
	miniTree->Branch("MuonL_isoR03_emEt", &MuonL_isoR03_emEt, "MuonL_isoR03_emEt/F");
	miniTree->Branch("MuonS_isoR03_emEt", &MuonS_isoR03_emEt, "MuonS_isoR03_emEt/F");

	miniTree->Branch("MuonM_isoR03_hadEt", &MuonM_isoR03_hadEt, "MuonM_isoR03_hadEt/F");
	miniTree->Branch("MuonP_isoR03_hadEt", &MuonP_isoR03_hadEt, "MuonP_isoR03_hadEt/F");
	miniTree->Branch("MuonF_isoR03_hadEt", &MuonF_isoR03_hadEt, "MuonF_isoR03_hadEt/F");
	miniTree->Branch("MuonN_isoR03_hadEt", &MuonN_isoR03_hadEt, "MuonN_isoR03_hadEt/F");
	miniTree->Branch("MuonL_isoR03_hadEt", &MuonL_isoR03_hadEt, "MuonL_isoR03_hadEt/F");
	miniTree->Branch("MuonS_isoR03_hadEt", &MuonS_isoR03_hadEt, "MuonS_isoR03_hadEt/F");

	miniTree->Branch("MuonM_isoR03_hoEt", &MuonM_isoR03_hoEt, "MuonM_isoR03_hoEt/F");
	miniTree->Branch("MuonP_isoR03_hoEt", &MuonP_isoR03_hoEt, "MuonP_isoR03_hoEt/F");
	miniTree->Branch("MuonF_isoR03_hoEt", &MuonF_isoR03_hoEt, "MuonF_isoR03_hoEt/F");
	miniTree->Branch("MuonN_isoR03_hoEt", &MuonN_isoR03_hoEt, "MuonN_isoR03_hoEt/F");
	miniTree->Branch("MuonL_isoR03_hoEt", &MuonL_isoR03_hoEt, "MuonL_isoR03_hoEt/F");
	miniTree->Branch("MuonS_isoR03_hoEt", &MuonS_isoR03_hoEt, "MuonS_isoR03_hoEt/F");

	miniTree->Branch("MuonM_isoR03_nJets", &MuonM_isoR03_nJets, "MuonM_isoR03_nJets/F");
	miniTree->Branch("MuonP_isoR03_nJets", &MuonP_isoR03_nJets, "MuonP_isoR03_nJets/F");
	miniTree->Branch("MuonF_isoR03_nJets", &MuonF_isoR03_nJets, "MuonF_isoR03_nJets/F");
	miniTree->Branch("MuonN_isoR03_nJets", &MuonN_isoR03_nJets, "MuonN_isoR03_nJets/F");
	miniTree->Branch("MuonL_isoR03_nJets", &MuonL_isoR03_nJets, "MuonL_isoR03_nJets/F");
	miniTree->Branch("MuonS_isoR03_nJets", &MuonS_isoR03_nJets, "MuonS_isoR03_nJets/F");

	miniTree->Branch("MuonM_isoR03_nTracks", &MuonM_isoR03_nTracks, "MuonM_isoR03_nTracks/F");
	miniTree->Branch("MuonP_isoR03_nTracks", &MuonP_isoR03_nTracks, "MuonP_isoR03_nTracks/F");
	miniTree->Branch("MuonF_isoR03_nTracks", &MuonF_isoR03_nTracks, "MuonF_isoR03_nTracks/F");
	miniTree->Branch("MuonN_isoR03_nTracks", &MuonN_isoR03_nTracks, "MuonN_isoR03_nTracks/F");
	miniTree->Branch("MuonL_isoR03_nTracks", &MuonL_isoR03_nTracks, "MuonL_isoR03_nTracks/F");
	miniTree->Branch("MuonS_isoR03_nTracks", &MuonS_isoR03_nTracks, "MuonS_isoR03_nTracks/F");

	miniTree->Branch("MuonM_isoR03_sumPt", &MuonM_isoR03_sumPt, "MuonM_isoR03_sumPt/F");
	miniTree->Branch("MuonP_isoR03_sumPt", &MuonP_isoR03_sumPt, "MuonP_isoR03_sumPt/F");
	miniTree->Branch("MuonF_isoR03_sumPt", &MuonF_isoR03_sumPt, "MuonF_isoR03_sumPt/F");
	miniTree->Branch("MuonN_isoR03_sumPt", &MuonN_isoR03_sumPt, "MuonN_isoR03_sumPt/F");
	miniTree->Branch("MuonL_isoR03_sumPt", &MuonL_isoR03_sumPt, "MuonL_isoR03_sumPt/F");
	miniTree->Branch("MuonS_isoR03_sumPt", &MuonS_isoR03_sumPt, "MuonS_isoR03_sumPt/F");

	miniTree->Branch("MuonM_isoR05_emEt", &MuonM_isoR05_emEt, "MuonM_isoR05_emEt/F");
	miniTree->Branch("MuonP_isoR05_emEt", &MuonP_isoR05_emEt, "MuonP_isoR05_emEt/F");
	miniTree->Branch("MuonF_isoR05_emEt", &MuonF_isoR05_emEt, "MuonF_isoR05_emEt/F");
	miniTree->Branch("MuonN_isoR05_emEt", &MuonN_isoR05_emEt, "MuonN_isoR05_emEt/F");
	miniTree->Branch("MuonL_isoR05_emEt", &MuonL_isoR05_emEt, "MuonL_isoR05_emEt/F");
	miniTree->Branch("MuonS_isoR05_emEt", &MuonS_isoR05_emEt, "MuonS_isoR05_emEt/F");

	miniTree->Branch("MuonM_isoR05_hadEt", &MuonM_isoR05_hadEt, "MuonM_isoR05_hadEt/F");
	miniTree->Branch("MuonP_isoR05_hadEt", &MuonP_isoR05_hadEt, "MuonP_isoR05_hadEt/F");
	miniTree->Branch("MuonF_isoR05_hadEt", &MuonF_isoR05_hadEt, "MuonF_isoR05_hadEt/F");
	miniTree->Branch("MuonN_isoR05_hadEt", &MuonN_isoR05_hadEt, "MuonN_isoR05_hadEt/F");
	miniTree->Branch("MuonL_isoR05_hadEt", &MuonL_isoR05_hadEt, "MuonL_isoR05_hadEt/F");
	miniTree->Branch("MuonS_isoR05_hadEt", &MuonS_isoR05_hadEt, "MuonS_isoR05_hadEt/F");

	miniTree->Branch("MuonM_isoR05_hoEt", &MuonM_isoR05_hoEt, "MuonM_isoR05_hoEt/F");
	miniTree->Branch("MuonP_isoR05_hoEt", &MuonP_isoR05_hoEt, "MuonP_isoR05_hoEt/F");
	miniTree->Branch("MuonF_isoR05_hoEt", &MuonF_isoR05_hoEt, "MuonF_isoR05_hoEt/F");
	miniTree->Branch("MuonN_isoR05_hoEt", &MuonN_isoR05_hoEt, "MuonN_isoR05_hoEt/F");
	miniTree->Branch("MuonL_isoR05_hoEt", &MuonL_isoR05_hoEt, "MuonL_isoR05_hoEt/F");
	miniTree->Branch("MuonS_isoR05_hoEt", &MuonS_isoR05_hoEt, "MuonS_isoR05_hoEt/F");

	miniTree->Branch("MuonM_isoR05_nJets", &MuonM_isoR05_nJets, "MuonM_isoR05_nJets/F");
	miniTree->Branch("MuonP_isoR05_nJets", &MuonP_isoR05_nJets, "MuonP_isoR05_nJets/F");
	miniTree->Branch("MuonF_isoR05_nJets", &MuonF_isoR05_nJets, "MuonF_isoR05_nJets/F");
	miniTree->Branch("MuonN_isoR05_nJets", &MuonN_isoR05_nJets, "MuonN_isoR05_nJets/F");
	miniTree->Branch("MuonL_isoR05_nJets", &MuonL_isoR05_nJets, "MuonL_isoR05_nJets/F");
	miniTree->Branch("MuonS_isoR05_nJets", &MuonS_isoR05_nJets, "MuonS_isoR05_nJets/F");

	miniTree->Branch("MuonM_isoR05_nTracks", &MuonM_isoR05_nTracks, "MuonM_isoR05_nTracks/F");
	miniTree->Branch("MuonP_isoR05_nTracks", &MuonP_isoR05_nTracks, "MuonP_isoR05_nTracks/F");
	miniTree->Branch("MuonF_isoR05_nTracks", &MuonF_isoR05_nTracks, "MuonF_isoR05_nTracks/F");
	miniTree->Branch("MuonN_isoR05_nTracks", &MuonN_isoR05_nTracks, "MuonN_isoR05_nTracks/F");
	miniTree->Branch("MuonL_isoR05_nTracks", &MuonL_isoR05_nTracks, "MuonL_isoR05_nTracks/F");
	miniTree->Branch("MuonS_isoR05_nTracks", &MuonS_isoR05_nTracks, "MuonS_isoR05_nTracks/F");

	miniTree->Branch("MuonM_isoR05_sumPt", &MuonM_isoR05_sumPt, "MuonM_isoR05_sumPt/F");
	miniTree->Branch("MuonP_isoR05_sumPt", &MuonP_isoR05_sumPt, "MuonP_isoR05_sumPt/F");
	miniTree->Branch("MuonF_isoR05_sumPt", &MuonF_isoR05_sumPt, "MuonF_isoR05_sumPt/F");
	miniTree->Branch("MuonN_isoR05_sumPt", &MuonN_isoR05_sumPt, "MuonN_isoR05_sumPt/F");
	miniTree->Branch("MuonL_isoR05_sumPt", &MuonL_isoR05_sumPt, "MuonL_isoR05_sumPt/F");
	miniTree->Branch("MuonS_isoR05_sumPt", &MuonS_isoR05_sumPt, "MuonS_isoR05_sumPt/F");

	// ____________________________________________
	// Photon variables
	// ___________________________________________

	miniTree->Branch("NbPhotons", &NbPhotons, "NbPhotons/I");

	miniTree_allphotons->Branch("Pt_allPhotons", &Pt_allPhotons, "Pt_allPhotons/F");
	miniTree_allphotons->Branch("Eta_allPhotons", &Eta_allPhotons, "Eta_allPhotons/F");
	miniTree_allphotons->Branch("Phi_allPhotons", &Phi_allPhotons, "Phi_allPhotons/F");
	miniTree_allphotons->Branch("Cross_allPhotons", &Cross_allPhotons, "Cross_allPhotons/F");
	
	miniTree_allphotons->Branch("isEBorEE_allPhotons", &isEBorEE_allPhotons, "isEBorEE_allPhotons/I");
	miniTree_allphotons->Branch("isEB_allPhotons", &isEB_allPhotons, "isEB_allPhotons/I");
	miniTree_allphotons->Branch("isEE_allPhotons", &isEE_allPhotons, "isEE_allPhotons/I");
	miniTree_allphotons->Branch("isEEM_allPhotons", &isEEM_allPhotons, "isEEM_allPhotons/I");
	miniTree_allphotons->Branch("isEEP_allPhotons", &isEEP_allPhotons, "isEEP_allPhotons/I");

	miniTree->Branch("Photon_Eta", &Photon_Eta, "Photon_Eta/F");
	miniTree->Branch("Photon_Phi", &Photon_Phi, "Photon_Phi/F");

	miniTree->Branch("Photon_isEBorEE", &Photon_isEBorEE, "Photon_isEBorEE/I");
	miniTree->Branch("Photon_isEB", &Photon_isEB, "Photon_isEB/I");
	miniTree->Branch("Photon_isEE", &Photon_isEE, "Photon_isEE/I");
	miniTree->Branch("Photon_isEEP", &Photon_isEEP, "Photon_isEEP/I");
	miniTree->Branch("Photon_isEEM", &Photon_isEEM, "Photon_isEEM/I");

	miniTree->Branch("Photon_hasPixelSeed", &Photon_hasPixelSeed, "Photon_hasPixelSeed/I");
	miniTree->Branch("Photon_isAlsoElectron", &Photon_isAlsoElectron, "Photon_isAlsoElectron/I");
	miniTree->Branch("Photon_Nclusters", &Photon_Nclusters, "Photon_Nclusters/I");
	miniTree->Branch("Photon_nBasicClusters", &Photon_nBasicClusters, "Photon_nBasicClusters/I");
	miniTree->Branch("Photon_nXtals", &Photon_nXtals, "Photon_nXtals/I"); // Variable not filled in current version

	miniTree->Branch("Photon_isTightPhoton", &Photon_isTightPhoton, "Photon_isTightPhoton/I");
	miniTree->Branch("Photon_isLoosePhoton", &Photon_isLoosePhoton, "Photon_isLoosePhoton/I");

	miniTree->Branch("Photon_E", &Photon_E, "Photon_E/F");
	miniTree->Branch("Photon_Et", &Photon_Et, "Photon_Et/F");
	miniTree->Branch("Photon_E2x2", &Photon_E2x2, "Photon_E2x2/F");
	miniTree->Branch("Photon_E3x3", &Photon_E3x3, "Photon_E3x3/F");
	miniTree->Branch("Photon_E5x5", &Photon_E5x5, "Photon_E5x5/F");
	miniTree->Branch("Photon_Emax", &Photon_Emax, "Photon_Emax/F");
	miniTree->Branch("Photon_E2nd", &Photon_E2nd, "Photon_E2nd/F");

	miniTree->Branch("Photon_r19", &Photon_r19, "Photon_r19/F");
	miniTree->Branch("Photon_r9", &Photon_r9, "Photon_r9/F");
	miniTree->Branch("Photon_cross", &Photon_cross, "Photon_cross/F");

	miniTree->Branch("Photon_caloConeSize", &Photon_caloConeSize, "Photon_caloConeSize/F");
	miniTree->Branch("Photon_PreshEnergy", &Photon_PreshEnergy, "Photon_PreshEnergy/F");
	miniTree->Branch("Photon_HoE", &Photon_HoE, "Photon_HoE/F");
	miniTree->Branch("Photon_sigmaEtaEta", &Photon_sigmaEtaEta, "Photon_sigmaEtaEta/F");
  miniTree->Branch("Photon_sigmaIetaIeta", &Photon_sigmaIetaIeta, "Photon_sigmaIetaIeta/F");
	miniTree->Branch("Photon_covEtaEta", &Photon_covEtaEta, "Photon_covEtaEta/F");
	miniTree->Branch("Photon_covPhiPhi", &Photon_covPhiPhi, "Photon_covPhiPhi/F");
  miniTree->Branch("Photon_covEtaPhi", &Photon_covEtaPhi, "Photon_covEtaPhi/F");
	miniTree->Branch("Photon_convNTracks", &Photon_convNTracks, "Photon_convNTracks/I");
	miniTree->Branch("Photon_etaWidth", &Photon_etaWidth, "Photon_etaWidth/F");
	miniTree->Branch("Photon_phiWidth", &Photon_phiWidth, "Photon_phiWidth/F");

	miniTree->Branch("Photon_dR03isoEcalRecHit", &Photon_dR03isoEcalRecHit, "Photon_dR03isoEcalRecHit/F");
	miniTree->Branch("Photon_dR03isoHcalRecHit", &Photon_dR03isoHcalRecHit, "Photon_dR03isoHcalRecHit/F");
	miniTree->Branch("Photon_dR03isoSolidTrkCone", &Photon_dR03isoSolidTrkCone, "Photon_dR03isoSolidTrkCone/F");
	miniTree->Branch("Photon_dR03isoHollowTrkCone", &Photon_dR03isoHollowTrkCone, "Photon_dR03isoHollowTrkCone/F");
	miniTree->Branch("Photon_dR03isoNTracksSolidCone", &Photon_dR03isoNTracksSolidCone, "Photon_dR03isoNTracksSolidCone/I");
	miniTree->Branch("Photon_dR03isoNTracksHollowCone", &Photon_dR03isoNTracksHollowCone, "Photon_dR03isoNTracksHollowCone/I");

	miniTree->Branch("Photon_dR04isoEcalRecHit", &Photon_dR04isoEcalRecHit, "Photon_dR04isoEcalRecHit/F");
	miniTree->Branch("Photon_dR04isoHcalRecHit", &Photon_dR04isoHcalRecHit, "Photon_dR04isoHcalRecHit/F");
	miniTree->Branch("Photon_dR04isoSolidTrkCone", &Photon_dR04isoSolidTrkCone, "Photon_dR04isoSolidTrkCone/F");
	miniTree->Branch("Photon_dR04isoHollowTrkCone", &Photon_dR04isoHollowTrkCone, "Photon_dR04isoHollowTrkCone/F");
	miniTree->Branch("Photon_dR04isoNTracksSolidCone", &Photon_dR04isoNTracksSolidCone, "Photon_dR04isoNTracksSolidCone/I");
	miniTree->Branch("Photon_dR04isoNTracksHollowCone", &Photon_dR04isoNTracksHollowCone, "Photon_dR04isoNTracksHollowCone/I");

	miniTree->Branch("Photon_seedTime", &Photon_seedTime, "Photon_seedTime/F");
	miniTree->Branch("Photon_seedFlag", &Photon_seedFlag, "Photon_seedFlag/F");
	miniTree->Branch("Photon_seedPosition1", &Photon_seedPosition1, "Photon_seedPosition1/I");
	miniTree->Branch("Photon_seedPosition2", &Photon_seedPosition2, "Photon_seedPosition2/I");
	miniTree->Branch("Photon_SC_Eta", &Photon_SC_Eta, "Photon_SC_Eta/F");
	miniTree->Branch("Photon_SC_Phi", &Photon_SC_Phi, "Photon_SC_Phi/F");
	miniTree->Branch("Photon_SC_brem", &Photon_SC_brem, "Photon_SC_brem/F");
	miniTree->Branch("Photon_SC_E", &Photon_SC_E, "Photon_SC_E/F");
	miniTree->Branch("Photon_SC_Et", &Photon_SC_Et, "Photon_SC_Et/F");
	miniTree->Branch("Photon_SC_rawEt", &Photon_SC_rawEt, "Photon_SC_rawEt/F");
	miniTree->Branch("Photon_SC_rawE", &Photon_SC_rawE, "Photon_SC_rawE/F");

	// ____________________________________________
	// mugamma / mumu / mumugamma information
	// ____________________________________________

	miniTree->Branch("Mmumu", &Mmumu, "Mmumu/F");
	miniTree->Branch("Mmumugamma", &Mmumugamma, "Mmumugamma/F");
	miniTree->Branch("Mmumugamma_5x5", &Mmumugamma_5x5, "Mmumugamma_5x5/F");
	miniTree->Branch("Mmumugamma_SC", &Mmumugamma_SC, "Mmumugamma_SC/F");
	miniTree->Branch("Mmumugamma_SCraw", &Mmumugamma_SCraw, "Mmumugamma_SCraw/F");

	miniTree->Branch("deltaRNear", &deltaRNear, "deltaRNear/F");
	miniTree->Branch("deltaRFar", &deltaRFar, "deltaRFar/F");
	miniTree->Branch("deltaRPlus", &deltaRPlus, "deltaRPlus/F");
	miniTree->Branch("deltaRMinus", &deltaRMinus, "deltaRMinus/F");
	miniTree->Branch("deltaRLeading", &deltaRLeading, "deltaRLeading/F");
	miniTree->Branch("deltaRSubleading", &deltaRSubleading, "deltaRSubleading/F");

	miniTree->Branch("mmg_k", &mmg_k, "mmg_k/F");
  miniTree->Branch("mmg_ik", &mmg_ik, "mmg_ik/F");
  miniTree->Branch("mmg_s", &mmg_s, "mmg_s/F");
  miniTree->Branch("mmg_logk", &mmg_logk, "mmg_logk/F");
  miniTree->Branch("mmg_logik", &mmg_logik, "mmg_logik/F");
  miniTree->Branch("mmg_logs", &mmg_logs, "mmg_logs/F");

	miniTree->Branch("mmg_k_5x5", &mmg_k_5x5, "mmg_k_5x5/F");
  miniTree->Branch("mmg_ik_5x5", &mmg_ik_5x5, "mmg_ik_5x5/F");
  miniTree->Branch("mmg_s_5x5", &mmg_s_5x5, "mmg_s_5x5/F");
  miniTree->Branch("mmg_logk_5x5", &mmg_logk_5x5, "mmg_logk_5x5/F");
  miniTree->Branch("mmg_logik_5x5", &mmg_logik_5x5, "mmg_logik_5x5/F");
  miniTree->Branch("mmg_logs_5x5", &mmg_logs_5x5, "mmg_logs_5x5/F");

	miniTree->Branch("mmg_k_SC", &mmg_k_SC, "mmg_k_SC/F");
  miniTree->Branch("mmg_ik_SC", &mmg_ik_SC, "mmg_ik_SC/F");
  miniTree->Branch("mmg_s_SC", &mmg_s_SC, "mmg_s_SC/F");
  miniTree->Branch("mmg_logk_SC", &mmg_logk_SC, "mmg_logk_SC/F");
  miniTree->Branch("mmg_logik_SC", &mmg_logik_SC, "mmg_logik_SC/F");
  miniTree->Branch("mmg_logs_SC", &mmg_logs_SC, "mmg_logs_SC/F");

	miniTree->Branch("mmg_k_SCraw", &mmg_k_SCraw, "mmg_k_SCraw/F");
  miniTree->Branch("mmg_ik_SCraw", &mmg_ik_SCraw, "mmg_ik_SCraw/F");
  miniTree->Branch("mmg_s_SCraw", &mmg_s_SCraw, "mmg_s_SCraw/F");
  miniTree->Branch("mmg_logk_SCraw", &mmg_logk_SCraw, "mmg_logk_SCraw/F");
  miniTree->Branch("mmg_logik_SCraw", &mmg_logik_SCraw, "mmg_logik_SCraw/F");
  miniTree->Branch("mmg_logs_SCraw", &mmg_logs_SCraw, "mmg_logs_SCraw/F");

	
	// SETUP PARAMETERS	
	unsigned int NbEvents = (int)inputEventTree->GetEntries();
//	unsigned int NbEvents = 1000;
	bool powheg = (bool)(isZgammaMC >= 1);
	bool signal = false;
	bool stew = false;
	bool zjet_veto = (bool)(isZgammaMC >= 1);
	cout << "Nb of events : " << NbEvents << endl;
	cout << "Signal is: " << signal <<endl;
	cout << "Stew is: " << stew << endl;
	cout << "ZJet veto is: " << zjet_veto << endl;
	int nBeforeAllCuts, nAfterCutPthatFilter, nAfterCutCSA07ID, nAfterCutZJETVETO, nAfterLooseMMG, nAfterTightMMG, nAfterCut1c, nAfterCut1d, nAfterCut1e, nAfterCut2a, nAfterCut2b, nAfterCut2c, nAfterCut3, nAfterCut4, nAfterCut5, nAfterCut6, nAfterCut7, nAfterCut8, nAfterCut9, nAfterCut10, nSelected;
	nBeforeAllCuts = nAfterCutPthatFilter = nAfterCutCSA07ID = nAfterCutZJETVETO = nAfterLooseMMG = nAfterTightMMG = nAfterCut1c = nAfterCut1d = nAfterCut1e = nAfterCut2a = nAfterCut2b = nAfterCut2c = nAfterCut3 = nAfterCut4 = nAfterCut5 = nAfterCut6 = nAfterCut7 = nAfterCut8 = nAfterCut9 = nAfterCut10 = nSelected = 0;
	vector<int> SelectedEvent_RunNumber;
	vector<int> SelectedEvent_LumiNumber;
	vector<int> SelectedEvent_EventNumber;
	vector<double> SelectedEvent_mumugammaInvMass;
	vector<double> SelectedEvent_Eta_gamma;
	vector<double> SelectedEvent_Eta_muonNear;
	vector<double> SelectedEvent_Eta_muonFar;
	vector<double> SelectedEvent_Et_gamma;
	vector<double> SelectedEvent_Pt_muonNear;
	vector<double> SelectedEvent_Pt_muonFar;
	vector<double> SelectedEvent_DeltaRNear;
	vector<double> SelectedEvent_DeltaRFar;
	vector<double> SelectedEvent_mumuInvMass;
	SelectedEvent_RunNumber.clear();
	SelectedEvent_LumiNumber.clear();
	SelectedEvent_EventNumber.clear();
	SelectedEvent_mumugammaInvMass.clear();
	SelectedEvent_Eta_gamma.clear();
	SelectedEvent_Eta_muonNear.clear();
	SelectedEvent_Eta_muonFar.clear();
	SelectedEvent_Et_gamma.clear();
	SelectedEvent_Pt_muonNear.clear();
	SelectedEvent_Pt_muonFar.clear();
	SelectedEvent_DeltaRNear.clear();
	SelectedEvent_DeltaRFar.clear();
	SelectedEvent_mumuInvMass.clear();

	inputRunTree->GetEvent(0);
  string lastFile = "";
	double minPtHat = -100;
  double maxPtHat = 1000000;
  int verbosity = 0;
	int TOTALnbMuonsAfterID[12] = {0};
	int TOTALnbEventsAfterMuonID[12] = {0};
	int TOTALnbDimuonsAfterID[3] = {0};
	int TOTALnbEventsAfterDimuonID[3] = {0};
	int TOTALnbPhotonsAfterID[6] = {0};
	int TOTALnbEventsAfterPhotonID[6] = {0};
	int TOTALnbMuMuGammaAfterID[7] = {0};
	int TOTALnbEventsAfterMuMuGammaID[7] = {0};

	for(unsigned int ievt=0; ievt<NbEvents; ievt++)
//	for(unsigned int ievt=9680; ievt<NbEvents; ievt++)
	{
		if(verbosity>4) cout << "analysing event ievt= " << ievt << endl;
		nBeforeAllCuts++;
		isBeforeAllCuts = 1;
		int nprint = (int)((double)NbEvents/(double)100.0);
		if( (ievt % nprint)==0 ){ cout<< ievt <<" events done over "<<NbEvents<<" ( "<<ceil((double)ievt/(double)NbEvents*100)<<" \% )"<<endl; }
		iEvent = ievt;
		inputEventTree->GetEvent(ievt);
    if( lastFile == "" ){
      lastFile = string(inputEventTree->GetCurrentFile()->GetName());
      cout << ievt << "\t" << lastFile << endl;
    }

		// ____________________________________________
		// Event information
		// ____________________________________________
		iEventID = event->eventId();
		iLumiID = event->luminosityBlock();
		iRunID = event->runId();
//		if(iRunID != 149291) continue;
		nVertices = vertices->GetEntries();
		isSignalApplied = signal;
		isStewApplied = stew;
		isZJetsApplied = zjet_veto;
		isAfterCutPthatFilter = isAfterCutZJETVETO = 0;
		isLooseMMG = isTightMMG = isAfterCut1c = isAfterCut1d = isAfterCut1e = 0;
		isAfterCut2a = isAfterCut2b = isAfterCut2c = 0;
		isAfterCut3 = isAfterCut4 = isAfterCut5 = isAfterCut6 = isAfterCut7 = isAfterCut8 = isAfterCut9 = isAfterCut10 = 0;
		isSelected = 0;

		// ____________________________________________
		// Muon variables
		// ____________________________________________
		NbMuons = muons->GetEntries();
		Pt_allMuons = Eta_allMuons = Phi_allMuons = Charge_allMuons = -99;
		MuonM_Pt = MuonP_Pt = MuonN_Pt = MuonF_Pt = MuonL_Pt = MuonS_Pt = -99;
		MuonM_Eta = MuonP_Eta = MuonN_Eta = MuonF_Eta = MuonL_Eta = MuonS_Eta = -99;
		MuonM_Phi = MuonP_Phi = MuonN_Phi = MuonF_Phi = MuonL_Phi = MuonS_Phi = -99;
		MuonF_Charge = MuonN_Charge = MuonL_Charge = MuonS_Charge = -99;
		MuonM_isoR03_emEt = MuonP_isoR03_emEt = MuonN_isoR03_emEt = MuonF_isoR03_emEt = MuonL_isoR03_emEt = MuonS_isoR03_emEt = -99;
		MuonM_isoR03_hadEt = MuonP_isoR03_hadEt = MuonN_isoR03_hadEt = MuonF_isoR03_hadEt = MuonL_isoR03_hadEt = MuonS_isoR03_hadEt = -99;
		MuonM_isoR03_hoEt = MuonP_isoR03_hoEt = MuonN_isoR03_hoEt = MuonF_isoR03_hoEt = MuonL_isoR03_hoEt = MuonS_isoR03_hoEt = -99;
		MuonM_isoR03_nJets = MuonP_isoR03_nJets = MuonN_isoR03_nJets = MuonF_isoR03_nJets = MuonL_isoR03_nJets = MuonS_isoR03_nJets = -99;
		MuonM_isoR03_nTracks = MuonP_isoR03_nTracks = MuonN_isoR03_nTracks = MuonF_isoR03_nTracks = MuonL_isoR03_nTracks = MuonS_isoR03_nTracks = -99;
		MuonM_isoR03_sumPt = MuonP_isoR03_sumPt = MuonN_isoR03_sumPt = MuonF_isoR03_sumPt = MuonL_isoR03_sumPt = MuonS_isoR03_sumPt = -99;
		MuonM_isoR05_emEt = MuonP_isoR05_emEt = MuonN_isoR05_emEt = MuonF_isoR05_emEt = MuonL_isoR05_emEt = MuonS_isoR05_emEt = -99;
		MuonM_isoR05_hadEt = MuonP_isoR05_hadEt = MuonN_isoR05_hadEt = MuonF_isoR05_hadEt = MuonL_isoR05_hadEt = MuonS_isoR05_hadEt = -99;
		MuonM_isoR05_hoEt = MuonP_isoR05_hoEt = MuonN_isoR05_hoEt = MuonF_isoR05_hoEt = MuonL_isoR05_hoEt = MuonS_isoR05_hoEt = -99;
		MuonM_isoR05_nJets = MuonP_isoR05_nJets = MuonN_isoR05_nJets = MuonF_isoR05_nJets = MuonL_isoR05_nJets = MuonS_isoR05_nJets = -99;
		MuonM_isoR05_nTracks = MuonP_isoR05_nTracks = MuonN_isoR05_nTracks = MuonF_isoR05_nTracks = MuonL_isoR05_nTracks = MuonS_isoR05_nTracks = -99;
		MuonM_isoR05_sumPt = MuonP_isoR05_sumPt = MuonN_isoR05_sumPt = MuonF_isoR05_sumPt = MuonL_isoR05_sumPt = MuonS_isoR05_sumPt = -99;

		// ____________________________________________
		// Photon variables
		// ___________________________________________
		NbPhotons = photons->GetEntries();
		Pt_allPhotons = Eta_allPhotons = Phi_allPhotons = Cross_allPhotons = -99;
		isNotCommissionned = -99;
		isEBorEE_allPhotons = 1;
		isEB_allPhotons, isEE_allPhotons, isEEM_allPhotons, isEEP_allPhotons = -99;
		Photon_Eta = Photon_Phi = -99;
		Photon_isEBorEE = 1;
		Photon_isEB = Photon_isEE = Photon_isEEP = Photon_isEEM = -99;
		Photon_hasPixelSeed = Photon_isAlsoElectron = Photon_Nclusters = Photon_nBasicClusters = Photon_nXtals = -99;
		Photon_isTightPhoton = Photon_isLoosePhoton = -99;
		Photon_convNTracks = -99;
		Photon_E = Photon_Et = Photon_E2x2 = Photon_E3x3 = Photon_E5x5 = Photon_Emax = Photon_E2nd = -99;
		Photon_r19 = Photon_r9 = Photon_cross = -99;
		Photon_caloConeSize = Photon_PreshEnergy = Photon_HoE = Photon_sigmaEtaEta = Photon_sigmaIetaIeta = Photon_covEtaEta = Photon_covPhiPhi = Photon_covEtaPhi = Photon_etaWidth = Photon_phiWidth = -99;
		Photon_dR03isoEcalRecHit = Photon_dR03isoHcalRecHit = Photon_dR03isoSolidTrkCone = Photon_dR03isoHollowTrkCone = Photon_dR03isoNTracksSolidCone = Photon_dR03isoNTracksHollowCone = -99;
		Photon_dR04isoEcalRecHit = Photon_dR04isoHcalRecHit = Photon_dR04isoSolidTrkCone = Photon_dR04isoHollowTrkCone = Photon_dR04isoNTracksSolidCone = Photon_dR04isoNTracksHollowCone = -99;
		Photon_seedTime = Photon_seedFlag = -99;
		Photon_seedPosition1 = Photon_seedPosition2 = -99;
		Photon_SC_Eta = Photon_SC_Phi = Photon_SC_brem = -99.0;
		Photon_SC_E = Photon_SC_Et = Photon_SC_rawE = Photon_SC_rawEt = -99.0;

		// ____________________________________________
		// mugamma / mumu / mumugamma information
		// ____________________________________________
		Mmumu = Mmumugamma = Mmumugamma_5x5 = Mmumugamma_SC = Mmumugamma_SCraw = -99;
		deltaRNear = deltaRFar = deltaRPlus = deltaRMinus = deltaRLeading = deltaRSubleading = -99;
		mmg_k = mmg_ik = mmg_s = mmg_logk = mmg_logik = mmg_logs = -99.0;
		mmg_k_5x5 = mmg_ik_5x5 = mmg_s_5x5 = mmg_logk_5x5 = mmg_logik_5x5 = mmg_logs_5x5 = -99.0;
		mmg_k_SC = mmg_ik_SC = mmg_s_SC = mmg_logk_SC = mmg_logik_SC = mmg_logs_SC = -99.0;
		mmg_k_SCraw = mmg_ik_SCraw = mmg_s_SCraw = mmg_logk_SCraw = mmg_logik_SCraw = mmg_logs_SCraw = -99.0;
 


		// ____________________________________________
		// END OF INITIALIZATION
		// ____________________________________________

		// HLT information		
/*
		if(doHLT){
			if( ievt==0 ){ inputRunTree->GetEvent(ievt); NumWantedHLTnames = InitializeHLTinfo(inputRunTree, runInfos, event->nHLTPaths(), ListWantedHLTnames, 1);  }
			if ( string(inputEventTree->GetCurrentFile()->GetName()) != lastFile ){
				inputRunTree->GetEntry(inputEventTree->GetTreeNumber());
     	  lastFile = string(inputEventTree->GetCurrentFile()->GetName());
     	  cout << ievt << "\t" << lastFile << endl;
     	 	NumWantedHLTnames = InitializeHLTinfo(inputRunTree, runInfos, event->nHLTPaths(), ListWantedHLTnames, 1);
     	}
      doHLTInfo(event, runInfos, NumWantedHLTnames, 1, &Muon_eventPassHLT_Mu11);
		}
*/
/*
		if (!((event->ptHat()>=minPtHat)&&(event->ptHat()<maxPtHat)))
		{
      cerr << "CUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )" << " CUT for pthat filtering" << endl;
			continue;
		}
		isAfterCutPthatFilter = 1;
		nAfterCutPthatFilter++;
*/
		// Signal MC Truth
    // ZJET VETO
    bool MCphotons_from_muons_from_Z = false;
    bool MC_first_muon_in_phase_space = false;
    bool MC_second_muon_in_phase_space = false;
    bool MCsignal_in_phase_space = false;

    if( zjet_veto && powheg )
    {
      if( mcMuMuGammaEvent->nZ() == 1 )
      {// consistency check
        cerr << "There is " << mcMuMuGammaEvent->nFSR() << " fsr photons in the event" << endl;
        if( mcMuMuGammaEvent->nFSR() < 1 )
        {// if there is no fsr photon, don't bother
          MCsignal_in_phase_space = false;
        }
        else
        {// if there is a fsr photon, check further
          for( int imcphoton = 0 ; imcphoton < mcMuMuGammaEvent->nFSR() ; imcphoton++ )
          {// loop over mc photons
            TRootParticle *myphoton;
            myphoton = (mcMuMuGammaEvent->photonFSR(imcphoton));
            // mc-acceptance cuts on photons
            if( EScale*(myphoton->Pt()>8.0) && (abs(myphoton->Eta())<3.0) ) MCphotons_from_muons_from_Z = true;
          }// end of loop over mc photons
          if( MCphotons_from_muons_from_Z )
          { // if there is a fsr photon passing acceptance cuts, then look at muons coming from the Z
            if( (mcMuMuGammaEvent->muplus()->Pt()>10.0) && (abs((mcMuMuGammaEvent->muplus()->Eta())<3.0)) )
            {
              MC_first_muon_in_phase_space = true;
              if( (mcMuMuGammaEvent->muminus()->Pt()>10.0) && (abs((mcMuMuGammaEvent->muminus()->Eta())<3.0)) )
              {
                MC_second_muon_in_phase_space = true;
                MCsignal_in_phase_space = true;
              }
            }
          } // end of cuts on muons coming from the Z
        }// end of check if the event is a mc fsr passing acceptance cuts
//        if(   MCsignal_in_phase_space ) // ***** WARNING *****  veto currently normal to consider background
//        if( !  MCsignal_in_phase_space ) // ***** WARNING *****  veto currently REVERSED to consider SIGNAL

				if( ((isZgammaMC == 1) && (!MCsignal_in_phase_space)) || ((isZgammaMC == 2) && (MCsignal_in_phase_space)) )
        {
          cerr<<"SAFE: photon(s) coming from muon, aborting event " << ievt << endl;

          continue;
        }
        isAfterCutZJETVETO = 1;
        nAfterCutZJETVETO++;
      } else {
        cout << "Failed POWHEG mumugamma consistency check" << endl;
      }// end of consistency check
    }// end of if Z+Jets veto for powheg


		if(verbosity>1) cout << "Start loop over muon objects" << endl;
    // Cleaning: muon quality
    vector<int> muonIsNotCommissioned;
    muonIsNotCommissioned.clear();
    vector<int> muonIdentified;
    muonIdentified.clear();
		int nbMuonsAfterID[12] = {0};
		
    if(verbosity>0) cerr << "\t\tThere is " << NbMuons << " muons in the muon collection" << endl;

		nbMuonsAfterID[0] = NbMuons;
		TOTALnbMuonsAfterID[0] += NbMuons;
    for(int imuon=0 ; imuon<NbMuons ; imuon++){
      TRootMuon *mymuon;
      mymuon = (TRootMuon*) muons->At(imuon);

			if(! (mymuon->isGlobalMuon()) ){
				muonIsNotCommissioned.push_back(1);
			if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because not global muon" << endl;
        continue;
      }
			nbMuonsAfterID[1]++;
			TOTALnbMuonsAfterID[1]++;

      if(! (mymuon->normalizedGlobalChi2()<10.0) ){// chi2/ndof of the global muon fit < 10
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because chi2/ndof of the global muon fit < 10 (" << mymuon->normalizedGlobalChi2() << ")" << endl;
        continue;
      }
			nbMuonsAfterID[2]++;
			TOTALnbMuonsAfterID[2]++;

			if(! (mymuon->numberOfValidGlobalHits()>0) ){// number of valid muon hits matched to the global fit
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because number of valid muon hits matched to the global fit too low (" << mymuon->numberOfValidGlobalHits() << ")" << endl;
        continue;
      }
			nbMuonsAfterID[3]++;
			TOTALnbMuonsAfterID[3]++;

      if(! (mymuon->isTrackerMuon()) ){// The muon must be identified as Tracker Muon.
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because not tracker muon" << endl;
        continue;
      }
			nbMuonsAfterID[4]++;
			TOTALnbMuonsAfterID[4]++;

      if(! (mymuon->numberOfMatches()>1) ){// number of muon stations with matched segments (global track: out-in fit)
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because number of muon stations with matched segments (global track: out-in fit) too low" << endl;
        continue;
      }
			nbMuonsAfterID[5]++;
			TOTALnbMuonsAfterID[5]++;

      if(! (mymuon->numberOfValidTrackerHits()>10) ){// number of tracker (pixels + strips) hits
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because number of tracker (pixels + strips) hits" << endl;
        continue;
      }
			nbMuonsAfterID[6]++;
			TOTALnbMuonsAfterID[6]++;

      if(! (mymuon->numberOfValidPixelHits()>0) ){// number of pixel hits
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because number of pixel hits" << endl;
        continue;
      }
			nbMuonsAfterID[7]++;
			TOTALnbMuonsAfterID[7]++;

      if(! (fabs(mymuon->GlobaldB())<0.2) )
//      if(! (fabs(mymuon->dB())<0.2) )
			{// inner track transverse impact parameter w.r.t the beam spot |d_xy|
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because inner track transverse impact parameter w.r.t the beam spot |d_xy|" << endl;
        continue;
      }
			nbMuonsAfterID[8]++;
			TOTALnbMuonsAfterID[8]++;

      if(! (mymuon->isoR03_sumPt()<3.0) ){// sum of pT of tracks with pT >1.5 within a cone of DR < 0.3 around the muon direction, vetoing a cone of 0.015 around that direction
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because sum of pT of tracks with pT >1.5 within a cone of DR < 0.3 around the muon direction, vetoing a cone of 0.015 around that direction" << endl;
        continue;
      }
			nbMuonsAfterID[9]++;
			TOTALnbMuonsAfterID[9]++;

      if(! (mymuon->Pt()>10.0) ){// transverse momentum
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because transverse momentum" << endl;
        continue;
      }
			nbMuonsAfterID[10]++;
			TOTALnbMuonsAfterID[10]++;

      if(! (fabs(mymuon->Eta())<2.4) ){// |eta_muon|< 2.1
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because high eta (" << mymuon->Eta() << ")" << endl;
        continue;
      }
			nbMuonsAfterID[11]++;
			TOTALnbMuonsAfterID[11]++;


/*
      if(! (mymuon->) ){// 
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because" << endl;
        continue;
      }
*/


      if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " accepted" << endl;
      muonIsNotCommissioned.push_back(0);
      muonIdentified.push_back(imuon);
			mymuon->Clear();
    }
    unsigned int NbMuonsIdentified = muonIdentified.size();
		
		// Increasing counter
		for(int i = 0; i < 12 ; i++)
		{
			if(nbMuonsAfterID[i] >= 2){ TOTALnbEventsAfterMuonID[i]++;}
		}

		if(! (nbMuonsAfterID[11] >=2) )// Not enough dimuon candidates, skip the event
		{

        continue;

		}



		if(verbosity>1) cout << "Filling dimuon pair holder" << endl;


		// Making dimuon pairs holder
		int numberOfDimuons[3] = {0};
		numberOfDimuons[0] = factorial(nbMuonsAfterID[11] -1);

		if(! (numberOfDimuons[0] >= 1) )// Not enough dimuon candidates, skip the event. This cut is redundant with the previous one, should do nothing
    {
      continue;

    }

		TOTALnbDimuonsAfterID[0] += numberOfDimuons[0];
		TOTALnbEventsAfterDimuonID[0] += 1;



		pair <int, int> IDofMuons[3][numberOfDimuons[0]];

		if(verbosity>2) cout << "initializing dimuon pair object" << endl;
		// Initializing pair object
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < numberOfDimuons[0]; j++) IDofMuons[i][j] = make_pair(0, 0);
		}

		if(verbosity>2) cout << "Filling pair object for dimuon pairs composed of ID'ed muons" << endl;
		// Filling pair object for dimuon pairs composed of ID'ed muons
		for(int i_dimuons = 0; i_dimuons < numberOfDimuons[0]; i_dimuons++)
    {
			for(int muon_i = 0; muon_i < nbMuonsAfterID[11] ; muon_i++)
			{
				for(int muon_j = muon_i +1; muon_j < nbMuonsAfterID[11]; muon_j++)
				{
					IDofMuons[0][i_dimuons] = make_pair(muonIdentified[muon_i], muonIdentified[muon_j]);
				}
			}
		}

	
		if(verbosity>2) cout << "loop over possible muon pairs, fill dimuons candidates with opposite charge" << endl;	
		// loop over possible muon pairs, fill dimuons candidates with opposite charge
		for(int i_dimuons = 0; i_dimuons < numberOfDimuons[0]; i_dimuons++)
    {
			TRootMuon *Muon1 = (TRootMuon*) muons->At(IDofMuons[0][i_dimuons].first);
			TRootMuon *Muon2 = (TRootMuon*) muons->At(IDofMuons[0][i_dimuons].second);
			double chargeproduct = ( Muon1->charge() ) * (Muon2->charge() );
			if( chargeproduct < 0.0 )
			{
				numberOfDimuons[1] += 1;
				IDofMuons[1][i_dimuons] = make_pair(IDofMuons[0][i_dimuons].first, IDofMuons[0][i_dimuons].second);
			}
			Muon1->Clear();
			Muon2->Clear();
		}
		if(! (numberOfDimuons[1] >= 1) ) continue; // Not enough dimuon candidates, skip the event
		TOTALnbDimuonsAfterID[1] += numberOfDimuons[1];
		TOTALnbEventsAfterDimuonID[1] += 1;

		if(verbosity>2) cout << "loop over possible muon pairs, fill dimuons candidates with valid invariant mass" << endl;
		// loop over possible muon pairs, fill dimuons candidates with valid invariant mass
		for(int i_dimuons = 0; i_dimuons < numberOfDimuons[1]; i_dimuons++)
    {
			TRootMuon *Muon1 = (TRootMuon*) muons->At(IDofMuons[1][i_dimuons].first);
			TRootMuon *Muon2 = (TRootMuon*) muons->At(IDofMuons[1][i_dimuons].second);
			TLorentzVector mumu;
			mumu = (*Muon1) + (*Muon2);
			if( (40.0 < mumu.M()) && (mumu.M() < 80.0) )
			{
				numberOfDimuons[2] += 1;
				IDofMuons[2][i_dimuons] = make_pair(IDofMuons[1][i_dimuons].first, IDofMuons[1][i_dimuons].second);
			}
			Muon1->Clear();
			Muon2->Clear();
		}

		if(! (numberOfDimuons[2] >= 1) )// Not enough dimuon candidates, skip the event
    {
       continue;

    }

		TOTALnbDimuonsAfterID[2] += numberOfDimuons[2];
		TOTALnbEventsAfterDimuonID[2] += 1;



		if(verbosity>1) cout << "cleaning photon collection" << endl;
   // Cleaning: removing not commissionned superclusters and spikes
    vector<int> photonsNoSpike;
    photonsNoSpike.clear();
    vector<int> photonIsNotCommissioned;
    if(verbosity>0) cerr << "\t\tThere is " << NbPhotons << " photons in the photon collection" << endl;
    photonIsNotCommissioned.clear();
		int nbPhotonsAfterID[6] = {0};
    nbPhotonsAfterID[0] = NbPhotons;
		TOTALnbPhotonsAfterID[0] += nbPhotonsAfterID[0];

		for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
      TRootPhoton *myphoton;
      myphoton = (TRootPhoton*) photons->At(iphoton);

      if( (fabs(myphoton->superCluster()->Eta()))>2.5 ){ // high eta clusters, not commisionned
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because high eta" << endl;
        continue;
      }
			nbPhotonsAfterID[1]++;
			if( nbPhotonsAfterID[1] > nbPhotonsAfterID[0] ) cout << "WHOOOPS!!" << endl;
			TOTALnbPhotonsAfterID[1] += 1;

      if( fabs(myphoton->superCluster()->Eta())>1.4442 && fabs(myphoton->superCluster()->Eta())<1.566 ){// eta gap clusters, not commissionned
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because eta gap" << endl;
        continue;
      }
			nbPhotonsAfterID[2]++;
			TOTALnbPhotonsAfterID[2] += 1;

      if( myphoton->superCluster()->seedSeverity()==4 ){ // kWeird
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because kWeird" << endl;
        continue;
      }
			nbPhotonsAfterID[3]++;
			TOTALnbPhotonsAfterID[3] += 1;

      if( myphoton->superCluster()->seedRecoFlag()==2 ){ // kOutOfTime
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because kOutOfTime" << endl;
        continue;
      }
			nbPhotonsAfterID[4]++;
			TOTALnbPhotonsAfterID[4] += 1;

      if( EScale*(myphoton->Pt()) <= 10.0 ){ // Transverse momentum
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because kOutOfTime" << endl;
        continue;
      }
			nbPhotonsAfterID[5]++;
			TOTALnbPhotonsAfterID[5] += 1;

// This is now implemented at clustering level
//      if( myphoton->superCluster()->seedSeverity()==5 ){ // kBad
//        photonIsNotCommissioned.push_back(1);
//        continue;
//        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because kBad" << endl;
//      }


      if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " accepted" << endl;
      photonsNoSpike.push_back(iphoton);
      photonIsNotCommissioned.push_back(0);
    }
    unsigned int NbPhotonsNoSpike = photonsNoSpike.size();


		// Increasing counter
		for(int i = 0; i < 6 ; i++)
		{
			if(nbPhotonsAfterID[i] >= 1){ TOTALnbEventsAfterPhotonID[i]++;}
		}

		if(! (nbPhotonsAfterID[5] >=1) ) // Not enough photon candidates, skipping the event
    {
			if(verbosity>1) cerr << "Not enough photon candidates, skipping the event" << endl;
          continue;

    }


		if(verbosity>2) cout << "creating triplet pair object" << endl;

		int nbMuMuGammaAfterID[7] = {0};
		// Build mumugamma candidates
		int nbMuMuGammaCandidates = ( nbPhotonsAfterID[5] )*( numberOfDimuons[2] );
		nbMuMuGammaAfterID[0] = nbMuMuGammaCandidates;
		TOTALnbMuMuGammaAfterID[0] += nbMuMuGammaAfterID[0];
		TOTALnbEventsAfterMuMuGammaID[0]++ ;
//		if( nbMuMuGammaCandidates >= 2 ) { cout << "Arf, there is more than one possible candidate, what should I do ?? I'll take the first one for now. ("<< nbPhotonsAfterID[5] << " photons, " << numberOfDimuons[2] << " dimuon pairs)" << endl; }
		pair <int, pair<int, int> > MuMuGammaCandidates[6][nbMuMuGammaCandidates];

		if(verbosity>2) cout << "initializing triplet objects" << endl;
		// Initializing triplet objects
		for(int i = 0; i < 6; i++)
		{
			for(int j = 0; j < nbMuMuGammaCandidates; j++)
			{
				MuMuGammaCandidates[i][j] = make_pair(0, make_pair(0,0));
			}
		}

		if(verbosity>2) cout << "Filling triplet objects with ID'ed dimuons and photons" << endl;
		// Filling triplet objects with ID'ed dimuons and photons
		int i_cand = 0;
		for(int i_dimuons = 0; i_dimuons < numberOfDimuons[2]; i_dimuons++)
		{
			for(int i_photon = 0; i_photon < nbPhotonsAfterID[5]; i_photon++)
			{
				if(verbosity>5) cerr << "photonsNoSpike[i_photon]= " << photonsNoSpike[i_photon] << endl;
				if(verbosity>5) cerr << "IDofMuons[2][i_dimuons].first= " << IDofMuons[2][i_dimuons].first << endl;
				if(verbosity>5) cerr << "muonIdentified[IDofMuons[2][i_dimuons].first]= " << muonIdentified[IDofMuons[2][i_dimuons].first] << endl;
				if(verbosity>5) cerr << "IDofMuons[2][i_dimuons].second= " << IDofMuons[2][i_dimuons].second << endl;
				if(verbosity>5) cerr << "muonIdentified[IDofMuons[2][i_dimuons].second]= " << muonIdentified[IDofMuons[2][i_dimuons].second] << endl;
				MuMuGammaCandidates[0][i_cand] = make_pair(photonsNoSpike[i_photon], make_pair( IDofMuons[2][i_dimuons].first, IDofMuons[2][i_dimuons].second));
				i_cand++;
			}
		}	

		if(verbosity>3) cout << "start looping over triplet candidates" << endl;	
		if(verbosity>4) cout << "nbMuMuGammaAfterID[0]= " << nbMuMuGammaAfterID[0] << endl;


		for(int i_mmg = 0; i_mmg < nbMuMuGammaAfterID[0] ; i_mmg++)
		{
			if(verbosity>5) cerr << "examining i_mmg= " << i_mmg << " over nbMuMuGammaAfterID[0]= " << nbMuMuGammaAfterID[0] << endl;
			TRootPhoton* myphoton;
			TRootMuon* mymuon1;
			TRootMuon* mymuon2;
			if(verbosity>5) cerr << "fetch photon photons->At(MuMuGammaCandidates[0][i_mmg].first)" << endl;
			myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[0][i_mmg].first);
			if(verbosity>5) cerr << "fetch muon1 muons->At(MuMuGammaCandidates[0][i_mmg].second.first )" << endl;
			mymuon1 = (TRootMuon*) muons->At(MuMuGammaCandidates[0][i_mmg].second.first );
			if(verbosity>5) cerr << "fetch muon2 muons->At( MuMuGammaCandidates[0][i_mmg].second.second )" << endl;
			mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[0][i_mmg].second.second );
			if(verbosity>5) cerr << "getting phi, eta" << endl;
			double phiPhoton = myphoton->Phi();
			double etaPhoton = myphoton->Eta();
			double phiMuon1 = mymuon1->Phi();
			double etaMuon1 = mymuon1->Eta();
			double phiMuon2 = mymuon2->Phi();
			double etaMuon2 = mymuon2->Eta();
			if(verbosity>5) cerr << "compute deltaRs" << endl;
			double deltaRphomu1 = DeltaR(etaPhoton, phiPhoton, etaMuon1, phiMuon1);
			double deltaRphomu2 = DeltaR(etaPhoton, phiPhoton, etaMuon2, phiMuon2);
			if(verbosity>5) cerr << "check what is close_isoR03_hadEt" << endl;
			double close_isoR03_hadEt = (deltaRphomu1 < deltaRphomu2) ? (mymuon1->isoR03_hadEt()) : (mymuon2->isoR03_hadEt());

//			if(verbosity>0) cout << "(run, lumi, event)= " << iRunID << "\t" << iLumiID << "\t" << iEventID << endl;

			if(verbosity>5) cerr << "close_isoR03_hadEt= " << close_isoR03_hadEt << endl;
			if( close_isoR03_hadEt >= 1.0)
			{
				if(verbosity>3) cerr << "candidate thrown because close_isoR03_hadEt= " << close_isoR03_hadEt << endl;
				continue;
			} else {
				if(verbosity>5) cerr << "candidate accepted: close_isoR03_hadEt= " << close_isoR03_hadEt << endl;
			}
		
			if(verbosity>5) cerr << " filling new pair " << endl;
			MuMuGammaCandidates[1][nbMuMuGammaAfterID[1]] = make_pair(MuMuGammaCandidates[0][i_mmg].first, make_pair(MuMuGammaCandidates[0][i_mmg].second.first, MuMuGammaCandidates[0][i_mmg].second.second) );
			nbMuMuGammaAfterID[1]++;
			TOTALnbMuMuGammaAfterID[1]++;
			myphoton->Clear();
			mymuon1->Clear();
			mymuon2->Clear();
		}
		if(verbosity>4) cout << "nbMuMuGammaAfterID[1]= " << nbMuMuGammaAfterID[1] << endl;
		if(! (nbMuMuGammaAfterID[1] > 0) )
    {
					if(verbosity>2) cerr << "not enough triplet candidate passing close_isoR03_hadEt cut " << endl;
        continue;

    }

		TOTALnbEventsAfterMuMuGammaID[1]++ ;

//		cout << "loop over nbMuMuGammaAfterID[1]= " << nbMuMuGammaAfterID[1] << " candidates" << endl;
		for(int i_mmg = 0; i_mmg < nbMuMuGammaAfterID[1] ; i_mmg++)
		{
			TRootPhoton* myphoton;
			TRootMuon* mymuon1;
			TRootMuon* mymuon2;
			myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[1][i_mmg].first);
			mymuon1 = (TRootMuon*) muons->At( MuMuGammaCandidates[1][i_mmg].second.first );
			mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[1][i_mmg].second.second );
			double phiPhoton = myphoton->Phi();
			double etaPhoton = myphoton->Eta();
			double phiMuon1 = mymuon1->Phi();
			double etaMuon1 = mymuon1->Eta();
			double phiMuon2 = mymuon2->Phi();
			double etaMuon2 = mymuon2->Eta();
			double deltaRphomu1 = DeltaR(etaPhoton, phiPhoton, etaMuon1, phiMuon1);
			double deltaRphomu2 = DeltaR(etaPhoton, phiPhoton, etaMuon2, phiMuon2);
			double far_isoR03_emEt = (deltaRphomu1 > deltaRphomu2) ? mymuon1->isoR03_emEt() : mymuon2->isoR03_emEt();
			if( far_isoR03_emEt >= 1.0) 
			{
				if(verbosity>4) cerr << "candidate thrown because far_isoR03_emEt= " << far_isoR03_emEt << endl;
				continue;
			}
			MuMuGammaCandidates[2][nbMuMuGammaAfterID[2]] = make_pair(MuMuGammaCandidates[1][i_mmg].first, make_pair(MuMuGammaCandidates[1][i_mmg].second.first, MuMuGammaCandidates[1][i_mmg].second.second) );
      nbMuMuGammaAfterID[2]++;
			myphoton->Clear();
			mymuon1->Clear();
			mymuon2->Clear();
    }
		if(verbosity>4) cout << "nbMuMuGammaAfterID[2]= " << nbMuMuGammaAfterID[2] << endl;
    if(! (nbMuMuGammaAfterID[2] > 0) )
    {
      continue;

    }

		TOTALnbMuMuGammaAfterID[2] += nbMuMuGammaAfterID[2];
		TOTALnbEventsAfterMuMuGammaID[2]++ ;

//		cout << "loop over nbMuMuGammaAfterID[2]= " << nbMuMuGammaAfterID[2] << " candidates" << endl;
		for(int i_mmg = 0; i_mmg < nbMuMuGammaAfterID[2] ; i_mmg++)
		{
			TRootPhoton* myphoton;
			TRootMuon* mymuon1;
			TRootMuon* mymuon2;
			myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[2][i_mmg].first);
			mymuon1 = (TRootMuon*) muons->At( MuMuGammaCandidates[2][i_mmg].second.first );
			mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[2][i_mmg].second.second );
			double phiPhoton = myphoton->Phi();
			double etaPhoton = myphoton->Eta();
			double phiMuon1 = mymuon1->Phi();
			double etaMuon1 = mymuon1->Eta();
			double phiMuon2 = mymuon2->Phi();
			double etaMuon2 = mymuon2->Eta();
			double deltaRphomu1 = DeltaR(etaPhoton, phiPhoton, etaMuon1, phiMuon1);
			double deltaRphomu2 = DeltaR(etaPhoton, phiPhoton, etaMuon2, phiMuon2);
			double min_DeltaR = min(deltaRphomu1, deltaRphomu2);
			if( min_DeltaR >= 0.8 ) continue;
			MuMuGammaCandidates[3][nbMuMuGammaAfterID[3]] = make_pair(MuMuGammaCandidates[2][i_mmg].first, make_pair(MuMuGammaCandidates[2][i_mmg].second.first, MuMuGammaCandidates[2][i_mmg].second.second) );
      nbMuMuGammaAfterID[3]++;
      myphoton->Clear();
      mymuon1->Clear();
      mymuon2->Clear();

    }
    if(! (nbMuMuGammaAfterID[3] > 0) )
    {
         continue;

    }

		TOTALnbMuMuGammaAfterID[3] += nbMuMuGammaAfterID[3];
		TOTALnbEventsAfterMuMuGammaID[3]++ ;

//		cout << "loop over nbMuMuGammaAfterID[3]= " << nbMuMuGammaAfterID[3] << " candidates" << endl;
		for(int i_mmg = 0; i_mmg < nbMuMuGammaAfterID[3] ; i_mmg++)
		{
			TRootPhoton* myphoton;
			TRootMuon* mymuon1;
			TRootMuon* mymuon2;
			myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[3][i_mmg].first);
			mymuon1 = (TRootMuon*) muons->At( MuMuGammaCandidates[3][i_mmg].second.first );
			mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[3][i_mmg].second.second );
			double phiPhoton = myphoton->Phi();
			double etaPhoton = myphoton->Eta();
			double phiMuon1 = mymuon1->Phi();
			double etaMuon1 = mymuon1->Eta();
			double phiMuon2 = mymuon2->Phi();
			double etaMuon2 = mymuon2->Eta();
			double deltaRphomu1 = DeltaR(etaPhoton, phiPhoton, etaMuon1, phiMuon1);
			double deltaRphomu2 = DeltaR(etaPhoton, phiPhoton, etaMuon2, phiMuon2);
			double far_muonPt = (deltaRphomu1 > deltaRphomu2) ? mymuon1->Pt() : mymuon2->Pt();
			if( far_muonPt <= 30.0 ) continue;
			MuMuGammaCandidates[4][nbMuMuGammaAfterID[4]] = make_pair(MuMuGammaCandidates[3][i_mmg].first, make_pair(MuMuGammaCandidates[3][i_mmg].second.first, MuMuGammaCandidates[3][i_mmg].second.second) );
      nbMuMuGammaAfterID[4]++;
      myphoton->Clear();
      mymuon1->Clear();
      mymuon2->Clear();

    }
    if(! (nbMuMuGammaAfterID[4] > 0) )
    {
      continue;

    }

		TOTALnbMuMuGammaAfterID[4] += nbMuMuGammaAfterID[4];
		TOTALnbEventsAfterMuMuGammaID[4]++ ;

//		cout << "loop over nbMuMuGammaAfterID[4]= " << nbMuMuGammaAfterID[4] << " candidates" << endl;
		for(int i_mmg = 0; i_mmg < nbMuMuGammaAfterID[4] ; i_mmg++)
		{
			TRootPhoton* myphoton;
			TRootMuon* mymuon1;
			TRootMuon* mymuon2;
			myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[4][i_mmg].first);
			mymuon1 = (TRootMuon*) muons->At( MuMuGammaCandidates[4][i_mmg].second.first );
			mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[4][i_mmg].second.second );
			double phiPhoton = myphoton->Phi();
			double etaPhoton = myphoton->Eta();
			double phiMuon1 = mymuon1->Phi();
			double etaMuon1 = mymuon1->Eta();
			double phiMuon2 = mymuon2->Phi();
			double etaMuon2 = mymuon2->Eta();
			double deltaRphomu1 = DeltaR(etaPhoton, phiPhoton, etaMuon1, phiMuon1);
			double deltaRphomu2 = DeltaR(etaPhoton, phiPhoton, etaMuon2, phiMuon2);
			TLorentzVector mumugamma;
			TLorentzVector *PhotonEScale = new TLorentzVector( EScale*(myphoton->Px()), EScale*(myphoton->Py()), EScale*(myphoton->Pz()), EScale*(myphoton->Energy()));
//			mumugamma = (*myphoton) + (*mymuon1) + (*mymuon2);
			mumugamma = (*PhotonEScale) + (*mymuon1) + (*mymuon2);
			if( (mumugamma.M() < 70.0) || (110.0 < mumugamma.M())  ) continue;
			MuMuGammaCandidates[5][nbMuMuGammaAfterID[5]] = make_pair(MuMuGammaCandidates[4][i_mmg].first, make_pair(MuMuGammaCandidates[4][i_mmg].second.first, MuMuGammaCandidates[4][i_mmg].second.second) );
      nbMuMuGammaAfterID[5]++;
			PhotonEScale->Clear();
      myphoton->Clear();
      mymuon1->Clear();
      mymuon2->Clear();

    }
    if(! (nbMuMuGammaAfterID[5] > 0) )
    {
//			miniTree->Fill();
      continue;
    }
		for(int i_mmg = 0; i_mmg < 1 ; i_mmg++)
    {
      TRootPhoton* myphoton;
      TRootMuon* mymuon1;
      TRootMuon* mymuon2;
      myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[5][i_mmg].first);
      mymuon1 = (TRootMuon*) muons->At( MuMuGammaCandidates[5][i_mmg].second.first );
      mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[5][i_mmg].second.second );

			// Fill photon stuff
			Photon_Eta = myphoton->Eta();
	    Photon_Phi = myphoton->Phi();
	    if( myphoton->isEBPho() ){ Photon_isEB=1; } else { Photon_isEB=0; }
	    if( myphoton->isEEPho() ){ Photon_isEE=1; } else { Photon_isEE=0; }
	    if( myphoton->isEEPho() && myphoton->Eta()<0 ){ Photon_isEEM=1; } else { Photon_isEEM=0; }
	    if( myphoton->isEEPho() && myphoton->Eta()>0 ){ Photon_isEEP=1; } else { Photon_isEEP=0; }
	    Photon_hasPixelSeed = myphoton->hasPixelSeed();
	    Photon_isAlsoElectron = myphoton->isAlsoElectron();
	    Photon_Nclusters = myphoton->nbClusters();
	//    cout << "myphoton->superCluster()=" << myphoton->superCluster() << endl; // FIXME
	//    Photon_nBasicClusters = myphoton->superCluster()->nBasicClusters();
	    Photon_isTightPhoton = myphoton->isTightPhoton();
	    Photon_isLoosePhoton = myphoton->isLoosePhoton();
	    Photon_convNTracks = myphoton->convNTracks();
	    Photon_E = EScale*(myphoton->Energy());
	    Photon_Et = EScale*(myphoton->Et());
	    Photon_E2x2 = EScale*(myphoton->e2x2());
	    Photon_E3x3 = EScale*(myphoton->e3x3());
	    Photon_E5x5 = EScale*(myphoton->e5x5());
	    Photon_Emax = EScale*(myphoton->eMax());
	    Photon_E2nd = EScale*(myphoton->e2nd());
	    Photon_r19 = myphoton->r19();
	    Photon_r9 = myphoton->r9();
	//FIXME   Photon_cross = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));   
	    Photon_caloConeSize = myphoton->caloConeSize();
	    Photon_PreshEnergy = myphoton->preshowerEnergy();
	    Photon_HoE = myphoton->hoe();
	    Photon_sigmaEtaEta = myphoton->sigmaEtaEta();
	    Photon_sigmaIetaIeta = myphoton->sigmaIetaIeta();
	    Photon_covEtaEta = myphoton->covEtaEta();
	    Photon_covPhiPhi = myphoton->covPhiPhi();
	    Photon_covEtaPhi = myphoton->covEtaPhi();
	    Photon_etaWidth = myphoton->superCluster()->etaWidth();
	    Photon_phiWidth = myphoton->superCluster()->phiWidth();
	    Photon_dR03isoEcalRecHit = myphoton->dR03IsolationEcalRecHit();
	    Photon_dR03isoHcalRecHit = myphoton->dR03IsolationHcalRecHit();
	    Photon_dR03isoSolidTrkCone = myphoton->dR03IsolationSolidTrkCone();
	    Photon_dR03isoHollowTrkCone = myphoton->dR03IsolationHollowTrkCone();
	    Photon_dR03isoNTracksSolidCone = myphoton->dR03IsolationNTracksSolidCone();
	    Photon_dR03isoNTracksHollowCone = myphoton->dR03IsolationNTracksHollowCone();
	    Photon_dR04isoEcalRecHit = myphoton->dR04IsolationEcalRecHit();
	    Photon_dR04isoHcalRecHit = myphoton->dR04IsolationHcalRecHit();
	    Photon_dR04isoSolidTrkCone = myphoton->dR04IsolationSolidTrkCone();
	    Photon_dR04isoHollowTrkCone = myphoton->dR04IsolationHollowTrkCone();
	    Photon_dR04isoNTracksSolidCone = myphoton->dR04IsolationNTracksSolidCone();
	    Photon_dR04isoNTracksHollowCone = myphoton->dR04IsolationNTracksHollowCone();
	    Photon_seedTime = myphoton->superCluster()->seedTime();
	    Photon_seedFlag = myphoton->superCluster()->seedRecoFlag();
	    Photon_seedPosition1 = myphoton->superCluster()->seedPosition1();
	    Photon_seedPosition2 = myphoton->superCluster()->seedPosition2();
	    Photon_SC_Eta = myphoton->superCluster()->Eta();
	    Photon_SC_Phi = myphoton->superCluster()->Phi();
			Photon_SC_brem = (double)(Photon_phiWidth) / (double)(Photon_etaWidth);
			Photon_SC_E = myphoton->superCluster()->Mag();
			Photon_SC_Et = Photon_SC_E * (sin(myphoton->superCluster()->Theta()));
			Photon_SC_rawE = myphoton->superCluster()->rawEnergy();
			Photon_SC_rawEt = Photon_SC_rawE * (sin(myphoton->superCluster()->Theta()));
			

			// Fill muons stuff
			TRootMuon *leadingMuon;
	    TRootMuon *subleadingMuon;
			if( (mymuon1->Pt()) > (mymuon2->Pt()) )
			{
				leadingMuon = mymuon1;
				subleadingMuon = mymuon2;
			} else {
				leadingMuon = mymuon2;
				subleadingMuon = mymuon1;
			}
			MuonL_Pt = leadingMuon->Pt();
	    MuonL_Eta = leadingMuon->Eta();
	    MuonL_Phi = leadingMuon->Phi();
	    MuonL_Charge = leadingMuon->charge();
	    MuonL_isoR03_emEt = leadingMuon->isoR03_emEt();
	    MuonL_isoR03_hadEt = leadingMuon->isoR03_hadEt();
	    MuonL_isoR03_hoEt = leadingMuon->isoR03_hoEt();
	    MuonL_isoR03_nJets = leadingMuon->isoR03_nJets();
	    MuonL_isoR03_nTracks = leadingMuon->isoR03_nTracks();
	    MuonL_isoR03_sumPt = leadingMuon->isoR03_sumPt();
	    MuonL_isoR05_emEt = leadingMuon->isoR05_emEt();
	    MuonL_isoR05_hadEt = leadingMuon->isoR05_hadEt();
	    MuonL_isoR05_hoEt = leadingMuon->isoR05_hoEt();
	    MuonL_isoR05_nJets = leadingMuon->isoR05_nJets();
	    MuonL_isoR05_nTracks = leadingMuon->isoR05_nTracks();
	    MuonL_isoR05_sumPt = leadingMuon->isoR05_sumPt();
	    MuonS_Pt = subleadingMuon->Pt();
	    MuonS_Eta = subleadingMuon->Eta();
	    MuonS_Phi = subleadingMuon->Phi();
	    MuonS_Charge = subleadingMuon->charge();
	    MuonS_isoR03_emEt = subleadingMuon->isoR03_emEt();
	    MuonS_isoR03_hadEt = subleadingMuon->isoR03_hadEt();
	    MuonS_isoR03_hoEt = subleadingMuon->isoR03_hoEt();
	    MuonS_isoR03_nJets = subleadingMuon->isoR03_nJets();
	    MuonS_isoR03_nTracks = subleadingMuon->isoR03_nTracks();
	    MuonS_isoR03_sumPt = subleadingMuon->isoR03_sumPt();
	    MuonS_isoR05_emEt = subleadingMuon->isoR05_emEt();
	    MuonS_isoR05_hadEt = subleadingMuon->isoR05_hadEt();
	    MuonS_isoR05_hoEt = subleadingMuon->isoR05_hoEt();
	    MuonS_isoR05_nJets = subleadingMuon->isoR05_nJets();
	    MuonS_isoR05_nTracks = subleadingMuon->isoR05_nTracks();
	    MuonS_isoR05_sumPt = subleadingMuon->isoR05_sumPt();
	
	    TLorentzVector mumu;
	    mumu = (*leadingMuon) + (*subleadingMuon);
	    double mumuInvMass = mumu.M();
	    cerr << "\t\tINFO: Dimuon invariant mass : Mmumu = " << mumuInvMass << endl;
	    mumu.Clear();
	    Mmumu = mumuInvMass;

    // ********************************************************************
    // *** Compute mumugamma invariant mass ***
    // ********************************************************************
    TLorentzVector mumugamma;
    TLorentzVector mumuSC;
    TLorentzVector mumu5x5;
    TLorentzVector mumuSC_raw;
    TLorentzVector *PhotonEScale = new TLorentzVector( EScale*(myphoton->Px()), EScale*(myphoton->Py()), EScale*(myphoton->Pz()), EScale*(myphoton->Energy()));
		TLorentzVector *PhotonSC = new TLorentzVector( myphoton->Px(), myphoton->Py(), myphoton->Pz(), EScale*(myphoton->superCluster()->Mag()));
    TLorentzVector *Photon5x5 = new TLorentzVector( myphoton->Px(), myphoton->Py(), myphoton->Pz(), EScale*(myphoton->e5x5()));
    TLorentzVector *PhotonSC_raw = new TLorentzVector( myphoton->Px(), myphoton->Py(), myphoton->Pz(), EScale*(myphoton->superCluster()->rawEnergy()));
//    mumugamma = (*leadingMuon) + (*subleadingMuon) + (*myphoton);
		mumugamma = (*leadingMuon) + (*subleadingMuon) + (*PhotonEScale);
    mumuSC = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC);
    mumu5x5 = (*leadingMuon) + (*subleadingMuon) + (*Photon5x5);
    mumuSC_raw = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw);
    double mumugammaInvMass = mumugamma.M();
    double mumuSCInvMass = mumuSC.M();
    double mumu5x5InvMass = mumu5x5.M();
    double mumuSC_rawInvMass = mumuSC_raw.M();
    Mmumugamma = mumugammaInvMass;
    Mmumugamma_SC = mumuSCInvMass;
    Mmumugamma_5x5 = mumu5x5InvMass;
    Mmumugamma_SCraw = mumuSC_rawInvMass;
    mumugamma.Clear();
    mumuSC.Clear();
    mumu5x5.Clear();
    mumuSC_raw.Clear();
		PhotonEScale->Clear();
    PhotonSC->Clear();
    Photon5x5->Clear();
    PhotonSC_raw->Clear();

    mmg_k = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma,2) - pow(Mmumu,2));
    mmg_ik = (double)(pow(Mmumugamma,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s = mmg_ik - 1.0;
    mmg_logk = log(mmg_k);
    mmg_logik = log(mmg_ik);
    mmg_logs = log(mmg_s);

    mmg_k_5x5 = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma_5x5,2) - pow(Mmumu,2));
    mmg_ik_5x5 = (double)(pow(Mmumugamma_5x5,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s_5x5 = mmg_ik_5x5 - 1.0;
    mmg_logk_5x5 = log(mmg_k_5x5);
    mmg_logik_5x5 = log(mmg_ik_5x5);
    mmg_logs_5x5 = log(mmg_s_5x5);

    mmg_k_SC = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma_SC,2) - pow(Mmumu,2));
    mmg_ik_SC = (double)(pow(Mmumugamma_SC,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s_SC = mmg_ik_SC - 1.0;
    mmg_logk_SC = log(mmg_k_SC);
    mmg_logik_SC = log(mmg_ik_SC);
    mmg_logs_SC = log(mmg_s_SC);

    mmg_k_SCraw = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma_SCraw,2) - pow(Mmumu,2));
    mmg_ik_SCraw = (double)(pow(Mmumugamma_SCraw,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s_SCraw = mmg_ik_SCraw - 1.0;
    mmg_logk_SCraw = log(mmg_k_SCraw);
    mmg_logik_SCraw = log(mmg_ik_SCraw);
    mmg_logs_SCraw = log(mmg_s_SCraw);


    cerr << "\t\tINFO: mumugamma invariant mass : Mmumugamma = " << mumugammaInvMass << endl;

    double phiPhoton = myphoton->Phi();
    double etaPhoton = myphoton->Eta();
    double phiMuon = mymuon1->Phi();
    double etaMuon = mymuon1->Eta();
    double phiMuon_oppositeCharge = mymuon2->Phi();
    double etaMuon_oppositeCharge = mymuon2->Eta();
    double deltaRPM = DeltaR(etaPhoton, phiPhoton, etaMuon, phiMuon);
    double deltaRPAM = DeltaR(etaPhoton, phiPhoton, etaMuon_oppositeCharge, phiMuon_oppositeCharge);

    double deltaRmin;
    TRootMuon *farMuon;
    TRootMuon *nearMuon;
    TRootMuon *minusMuon;
    TRootMuon *plusMuon;

    if(deltaRPM < deltaRPAM){
      deltaRmin = deltaRPM;
      farMuon = (TRootMuon*) mymuon2;
      nearMuon = (TRootMuon*) mymuon1;
    } else {
      deltaRmin = deltaRPAM;
      farMuon = (TRootMuon*) mymuon1;
      nearMuon = (TRootMuon*) mymuon2;
    }
    if( mymuon1->charge()>0 ){
      plusMuon  = (TRootMuon*) mymuon1;
      minusMuon = (TRootMuon*) mymuon2;
    } else {
      minusMuon = (TRootMuon*) mymuon1;
      plusMuon  = (TRootMuon*) mymuon2;
    }

    // FILLING MINITREE INFORMATION
    MuonM_Pt = minusMuon->Pt();
    MuonM_Eta = minusMuon->Eta();
    MuonM_Phi = minusMuon->Phi();
    MuonM_isoR03_emEt = minusMuon->isoR03_emEt();
    MuonM_isoR03_hadEt = minusMuon->isoR03_hadEt();
    MuonM_isoR03_hoEt = minusMuon->isoR03_hoEt();
    MuonM_isoR03_nJets = minusMuon->isoR03_nJets();
    MuonM_isoR03_nTracks = minusMuon->isoR03_nTracks();
    MuonM_isoR03_sumPt = minusMuon->isoR03_sumPt();
    MuonM_isoR05_emEt = minusMuon->isoR05_emEt();
    MuonM_isoR05_hadEt = minusMuon->isoR05_hadEt();
    MuonM_isoR05_hoEt = minusMuon->isoR05_hoEt();
    MuonM_isoR05_nJets = minusMuon->isoR05_nJets();
    MuonM_isoR05_nTracks = minusMuon->isoR05_nTracks();
    MuonM_isoR05_sumPt = minusMuon->isoR05_sumPt();
    MuonP_Pt = plusMuon->Pt();
    MuonP_Eta = plusMuon->Eta();
    MuonP_Phi = plusMuon->Phi();
    MuonP_isoR03_emEt = plusMuon->isoR03_emEt();
    MuonP_isoR03_hadEt = plusMuon->isoR03_hadEt();
    MuonP_isoR03_hoEt = plusMuon->isoR03_hoEt();
    MuonP_isoR03_nJets = plusMuon->isoR03_nJets();
    MuonP_isoR03_nTracks = plusMuon->isoR03_nTracks();
    MuonP_isoR03_sumPt = plusMuon->isoR03_sumPt();
    MuonP_isoR05_emEt = plusMuon->isoR05_emEt();
    MuonP_isoR05_hadEt = plusMuon->isoR05_hadEt();
    MuonP_isoR05_hoEt = plusMuon->isoR05_hoEt();
    MuonP_isoR05_nJets = plusMuon->isoR05_nJets();
    MuonP_isoR05_nTracks = plusMuon->isoR05_nTracks();
    MuonP_isoR05_sumPt = plusMuon->isoR05_sumPt();
    MuonF_Pt = farMuon->Pt();
    MuonF_Eta = farMuon->Eta();
    MuonF_Phi = farMuon->Phi();
    MuonF_Charge = farMuon->charge();
    MuonF_isoR03_emEt = farMuon->isoR03_emEt();
    MuonF_isoR03_hadEt = farMuon->isoR03_hadEt();
    MuonF_isoR03_hoEt = farMuon->isoR03_hoEt();
    MuonF_isoR03_nJets = farMuon->isoR03_nJets();
    MuonF_isoR03_nTracks = farMuon->isoR03_nTracks();
    MuonF_isoR03_sumPt = farMuon->isoR03_sumPt();
    MuonF_isoR05_emEt = farMuon->isoR05_emEt();
    MuonF_isoR05_hadEt = farMuon->isoR05_hadEt();
    MuonF_isoR05_hoEt = farMuon->isoR05_hoEt();
    MuonF_isoR05_nJets = farMuon->isoR05_nJets();
    MuonF_isoR05_nTracks = farMuon->isoR05_nTracks();
    MuonF_isoR05_sumPt = farMuon->isoR05_sumPt();
    MuonN_Pt = nearMuon->Pt();
    MuonN_Eta = nearMuon->Eta();
    MuonN_Phi = nearMuon->Phi();
    MuonN_Charge = nearMuon->charge();
    MuonN_isoR03_emEt = nearMuon->isoR03_emEt();
    MuonN_isoR03_hadEt = nearMuon->isoR03_hadEt();
    MuonN_isoR03_hoEt = nearMuon->isoR03_hoEt();
    MuonN_isoR03_nJets = nearMuon->isoR03_nJets();
    MuonN_isoR03_nTracks = nearMuon->isoR03_nTracks();
    MuonN_isoR03_sumPt = nearMuon->isoR03_sumPt();
    MuonN_isoR05_emEt = nearMuon->isoR05_emEt();
    MuonN_isoR05_hadEt = nearMuon->isoR05_hadEt();
    MuonN_isoR05_hoEt = nearMuon->isoR05_hoEt();
    MuonN_isoR05_nJets = nearMuon->isoR05_nJets();
    MuonN_isoR05_nTracks = nearMuon->isoR05_nTracks();
    MuonN_isoR05_sumPt = nearMuon->isoR05_sumPt();

    deltaRNear = DeltaR(etaPhoton, phiPhoton, nearMuon->Eta(), nearMuon->Phi());
    deltaRFar = DeltaR(etaPhoton, phiPhoton, farMuon->Eta(), farMuon->Phi());
    deltaRMinus = DeltaR(etaPhoton, phiPhoton, minusMuon->Eta(), minusMuon->Phi());
    deltaRPlus = DeltaR(etaPhoton, phiPhoton, plusMuon->Eta(), plusMuon->Phi());
    deltaRLeading = DeltaR(etaPhoton, phiPhoton, leadingMuon->Eta(), leadingMuon->Phi());
    deltaRSubleading = DeltaR(etaPhoton, phiPhoton, subleadingMuon->Eta(), subleadingMuon->Phi());


		myphoton->Clear();
		mymuon1->Clear();
		mymuon2->Clear();
    farMuon->Clear();
    nearMuon->Clear();
    minusMuon->Clear();
    plusMuon->Clear();
    PhotonSC->Clear();
    Photon5x5->Clear();
    PhotonSC_raw->Clear();
    leadingMuon->Clear();
    subleadingMuon->Clear();

		}
			isLooseMMG = 1;
			nAfterLooseMMG++;

		TOTALnbMuMuGammaAfterID[5] += nbMuMuGammaAfterID[5];
		TOTALnbEventsAfterMuMuGammaID[5]++ ;

		for(int i_mmg = 0; i_mmg < nbMuMuGammaAfterID[5] ; i_mmg++)
		{
			TRootPhoton* myphoton;
			TRootMuon* mymuon1;
			TRootMuon* mymuon2;
			myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[5][i_mmg].first);
			mymuon1 = (TRootMuon*) muons->At( MuMuGammaCandidates[5][i_mmg].second.first );
			mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[5][i_mmg].second.second );
			double phiPhoton = myphoton->Phi();
			double etaPhoton = myphoton->Eta();
			double phiMuon1 = mymuon1->Phi();
			double etaMuon1 = mymuon1->Eta();
			double phiMuon2 = mymuon2->Phi();
			double etaMuon2 = mymuon2->Eta();
			double deltaRphomu1 = DeltaR(etaPhoton, phiPhoton, etaMuon1, phiMuon1);
			double deltaRphomu2 = DeltaR(etaPhoton, phiPhoton, etaMuon2, phiMuon2);
			TLorentzVector mumugamma;
			TLorentzVector *PhotonEScale = new TLorentzVector( EScale*(myphoton->Px()), EScale*(myphoton->Py()), EScale*(myphoton->Pz()), EScale*(myphoton->Energy()));
//			mumugamma = (*myphoton) + (*mymuon1) + (*mymuon2);
			mumugamma = (*PhotonEScale) + (*mymuon1) + (*mymuon2);
			if( (mumugamma.M() < 87.2) || (95.2 < mumugamma.M())  ) continue;
			MuMuGammaCandidates[6][nbMuMuGammaAfterID[6]] = make_pair(MuMuGammaCandidates[5][i_mmg].first, make_pair(MuMuGammaCandidates[5][i_mmg].second.first, MuMuGammaCandidates[5][i_mmg].second.second) );
      nbMuMuGammaAfterID[6]++;
			PhotonEScale->Clear();
      myphoton->Clear();
      mymuon1->Clear();
      mymuon2->Clear();

    }
    if(! (nbMuMuGammaAfterID[6] > 0) )
    {
			miniTree->Fill();
      continue;
    }
			isTightMMG = 1;
			nAfterTightMMG++;

		TOTALnbMuMuGammaAfterID[6] += nbMuMuGammaAfterID[6];
		TOTALnbEventsAfterMuMuGammaID[6]++ ;

//		cout << "Finally found nbMuMuGammaAfterID[5]= " << nbMuMuGammaAfterID[5] << " candidates" << endl;

//    for(int i_mmg = 0; i_mmg < nbMuMuGammaAfterID[6] ; i_mmg++)
		for(int i_mmg = 0; i_mmg < 1 ; i_mmg++)
    {
      TRootPhoton* myphoton;
      TRootMuon* mymuon1;
      TRootMuon* mymuon2;
      myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[6][i_mmg].first);
      mymuon1 = (TRootMuon*) muons->At( MuMuGammaCandidates[6][i_mmg].second.first );
      mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[6][i_mmg].second.second );

			// Fill photon stuff
			Photon_Eta = myphoton->Eta();
	    Photon_Phi = myphoton->Phi();
	    if( myphoton->isEBPho() ){ Photon_isEB=1; } else { Photon_isEB=0; }
	    if( myphoton->isEEPho() ){ Photon_isEE=1; } else { Photon_isEE=0; }
	    if( myphoton->isEEPho() && myphoton->Eta()<0 ){ Photon_isEEM=1; } else { Photon_isEEM=0; }
	    if( myphoton->isEEPho() && myphoton->Eta()>0 ){ Photon_isEEP=1; } else { Photon_isEEP=0; }
	    Photon_hasPixelSeed = myphoton->hasPixelSeed();
	    Photon_isAlsoElectron = myphoton->isAlsoElectron();
	    Photon_Nclusters = myphoton->nbClusters();
	//    cout << "myphoton->superCluster()=" << myphoton->superCluster() << endl; // FIXME
	//    Photon_nBasicClusters = myphoton->superCluster()->nBasicClusters();
	    Photon_isTightPhoton = myphoton->isTightPhoton();
	    Photon_isLoosePhoton = myphoton->isLoosePhoton();
	    Photon_convNTracks = myphoton->convNTracks();
	    Photon_E = EScale*(myphoton->Energy());
	    Photon_Et = EScale*(myphoton->Et());
	    Photon_E2x2 = EScale*(myphoton->e2x2());
	    Photon_E3x3 = EScale*(myphoton->e3x3());
	    Photon_E5x5 = EScale*(myphoton->e5x5());
	    Photon_Emax = EScale*(myphoton->eMax());
	    Photon_E2nd = EScale*(myphoton->e2nd());
	    Photon_r19 = myphoton->r19();
	    Photon_r9 = myphoton->r9();
	//FIXME   Photon_cross = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));   
	    Photon_caloConeSize = myphoton->caloConeSize();
	    Photon_PreshEnergy = myphoton->preshowerEnergy();
	    Photon_HoE = myphoton->hoe();
	    Photon_sigmaEtaEta = myphoton->sigmaEtaEta();
	    Photon_sigmaIetaIeta = myphoton->sigmaIetaIeta();
	    Photon_covEtaEta = myphoton->covEtaEta();
	    Photon_covPhiPhi = myphoton->covPhiPhi();
	    Photon_covEtaPhi = myphoton->covEtaPhi();
	    Photon_etaWidth = myphoton->superCluster()->etaWidth();
	    Photon_phiWidth = myphoton->superCluster()->phiWidth();
	    Photon_dR03isoEcalRecHit = myphoton->dR03IsolationEcalRecHit();
	    Photon_dR03isoHcalRecHit = myphoton->dR03IsolationHcalRecHit();
	    Photon_dR03isoSolidTrkCone = myphoton->dR03IsolationSolidTrkCone();
	    Photon_dR03isoHollowTrkCone = myphoton->dR03IsolationHollowTrkCone();
	    Photon_dR03isoNTracksSolidCone = myphoton->dR03IsolationNTracksSolidCone();
	    Photon_dR03isoNTracksHollowCone = myphoton->dR03IsolationNTracksHollowCone();
	    Photon_dR04isoEcalRecHit = myphoton->dR04IsolationEcalRecHit();
	    Photon_dR04isoHcalRecHit = myphoton->dR04IsolationHcalRecHit();
	    Photon_dR04isoSolidTrkCone = myphoton->dR04IsolationSolidTrkCone();
	    Photon_dR04isoHollowTrkCone = myphoton->dR04IsolationHollowTrkCone();
	    Photon_dR04isoNTracksSolidCone = myphoton->dR04IsolationNTracksSolidCone();
	    Photon_dR04isoNTracksHollowCone = myphoton->dR04IsolationNTracksHollowCone();
	    Photon_seedTime = myphoton->superCluster()->seedTime();
	    Photon_seedFlag = myphoton->superCluster()->seedRecoFlag();
	    Photon_seedPosition1 = myphoton->superCluster()->seedPosition1();
	    Photon_seedPosition2 = myphoton->superCluster()->seedPosition2();
	    Photon_SC_Eta = myphoton->superCluster()->Eta();
	    Photon_SC_Phi = myphoton->superCluster()->Phi();
			Photon_SC_brem = (double)(Photon_phiWidth) / (double)(Photon_etaWidth);
			Photon_SC_E = myphoton->superCluster()->Mag();
			Photon_SC_Et = Photon_SC_E * (sin(myphoton->superCluster()->Theta()));
			Photon_SC_rawE = myphoton->superCluster()->rawEnergy();
			Photon_SC_rawEt = Photon_SC_rawE * (sin(myphoton->superCluster()->Theta()));
		

			// Fill muons stuff
			TRootMuon *leadingMuon;
	    TRootMuon *subleadingMuon;
			if( (mymuon1->Pt()) > (mymuon2->Pt()) )
			{
				leadingMuon = mymuon1;
				subleadingMuon = mymuon2;
			} else {
				leadingMuon = mymuon2;
				subleadingMuon = mymuon1;
			}
			MuonL_Pt = leadingMuon->Pt();
	    MuonL_Eta = leadingMuon->Eta();
	    MuonL_Phi = leadingMuon->Phi();
	    MuonL_Charge = leadingMuon->charge();
	    MuonL_isoR03_emEt = leadingMuon->isoR03_emEt();
	    MuonL_isoR03_hadEt = leadingMuon->isoR03_hadEt();
	    MuonL_isoR03_hoEt = leadingMuon->isoR03_hoEt();
	    MuonL_isoR03_nJets = leadingMuon->isoR03_nJets();
	    MuonL_isoR03_nTracks = leadingMuon->isoR03_nTracks();
	    MuonL_isoR03_sumPt = leadingMuon->isoR03_sumPt();
	    MuonL_isoR05_emEt = leadingMuon->isoR05_emEt();
	    MuonL_isoR05_hadEt = leadingMuon->isoR05_hadEt();
	    MuonL_isoR05_hoEt = leadingMuon->isoR05_hoEt();
	    MuonL_isoR05_nJets = leadingMuon->isoR05_nJets();
	    MuonL_isoR05_nTracks = leadingMuon->isoR05_nTracks();
	    MuonL_isoR05_sumPt = leadingMuon->isoR05_sumPt();
	    MuonS_Pt = subleadingMuon->Pt();
	    MuonS_Eta = subleadingMuon->Eta();
	    MuonS_Phi = subleadingMuon->Phi();
	    MuonS_Charge = subleadingMuon->charge();
	    MuonS_isoR03_emEt = subleadingMuon->isoR03_emEt();
	    MuonS_isoR03_hadEt = subleadingMuon->isoR03_hadEt();
	    MuonS_isoR03_hoEt = subleadingMuon->isoR03_hoEt();
	    MuonS_isoR03_nJets = subleadingMuon->isoR03_nJets();
	    MuonS_isoR03_nTracks = subleadingMuon->isoR03_nTracks();
	    MuonS_isoR03_sumPt = subleadingMuon->isoR03_sumPt();
	    MuonS_isoR05_emEt = subleadingMuon->isoR05_emEt();
	    MuonS_isoR05_hadEt = subleadingMuon->isoR05_hadEt();
	    MuonS_isoR05_hoEt = subleadingMuon->isoR05_hoEt();
	    MuonS_isoR05_nJets = subleadingMuon->isoR05_nJets();
	    MuonS_isoR05_nTracks = subleadingMuon->isoR05_nTracks();
	    MuonS_isoR05_sumPt = subleadingMuon->isoR05_sumPt();
	
	    TLorentzVector mumu;
	    mumu = (*leadingMuon) + (*subleadingMuon);
	    double mumuInvMass = mumu.M();
	    cerr << "\t\tINFO: Dimuon invariant mass : Mmumu = " << mumuInvMass << endl;
	    mumu.Clear();
	    Mmumu = mumuInvMass;

    // ********************************************************************
    // *** Compute mumugamma invariant mass ***
    // ********************************************************************
    TLorentzVector mumugamma;
    TLorentzVector mumuSC;
    TLorentzVector mumu5x5;
    TLorentzVector mumuSC_raw;
    TLorentzVector *PhotonEScale = new TLorentzVector( EScale*(myphoton->Px()), EScale*(myphoton->Py()), EScale*(myphoton->Pz()), EScale*(myphoton->Energy()));
		TLorentzVector *PhotonSC = new TLorentzVector( myphoton->Px(), myphoton->Py(), myphoton->Pz(), EScale*(myphoton->superCluster()->Mag()));
    TLorentzVector *Photon5x5 = new TLorentzVector( myphoton->Px(), myphoton->Py(), myphoton->Pz(), EScale*(myphoton->e5x5()));
    TLorentzVector *PhotonSC_raw = new TLorentzVector( myphoton->Px(), myphoton->Py(), myphoton->Pz(), EScale*(myphoton->superCluster()->rawEnergy()));
//    mumugamma = (*leadingMuon) + (*subleadingMuon) + (*myphoton);
		mumugamma = (*leadingMuon) + (*subleadingMuon) + (*PhotonEScale);
    mumuSC = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC);
    mumu5x5 = (*leadingMuon) + (*subleadingMuon) + (*Photon5x5);
    mumuSC_raw = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw);
    double mumugammaInvMass = mumugamma.M();
    double mumuSCInvMass = mumuSC.M();
    double mumu5x5InvMass = mumu5x5.M();
    double mumuSC_rawInvMass = mumuSC_raw.M();
    Mmumugamma = mumugammaInvMass;
    Mmumugamma_SC = mumuSCInvMass;
    Mmumugamma_5x5 = mumu5x5InvMass;
    Mmumugamma_SCraw = mumuSC_rawInvMass;
    mumugamma.Clear();
    mumuSC.Clear();
    mumu5x5.Clear();
    mumuSC_raw.Clear();
		PhotonEScale->Clear();
    PhotonSC->Clear();
    Photon5x5->Clear();
    PhotonSC_raw->Clear();

    mmg_k = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma,2) - pow(Mmumu,2));
    mmg_ik = (double)(pow(Mmumugamma,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s = mmg_ik - 1.0;
    mmg_logk = log(mmg_k);
    mmg_logik = log(mmg_ik);
    mmg_logs = log(mmg_s);

    mmg_k_5x5 = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma_5x5,2) - pow(Mmumu,2));
    mmg_ik_5x5 = (double)(pow(Mmumugamma_5x5,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s_5x5 = mmg_ik_5x5 - 1.0;
    mmg_logk_5x5 = log(mmg_k_5x5);
    mmg_logik_5x5 = log(mmg_ik_5x5);
    mmg_logs_5x5 = log(mmg_s_5x5);

    mmg_k_SC = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma_SC,2) - pow(Mmumu,2));
    mmg_ik_SC = (double)(pow(Mmumugamma_SC,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s_SC = mmg_ik_SC - 1.0;
    mmg_logk_SC = log(mmg_k_SC);
    mmg_logik_SC = log(mmg_ik_SC);
    mmg_logs_SC = log(mmg_s_SC);

    mmg_k_SCraw = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma_SCraw,2) - pow(Mmumu,2));
    mmg_ik_SCraw = (double)(pow(Mmumugamma_SCraw,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s_SCraw = mmg_ik_SCraw - 1.0;
    mmg_logk_SCraw = log(mmg_k_SCraw);
    mmg_logik_SCraw = log(mmg_ik_SCraw);
    mmg_logs_SCraw = log(mmg_s_SCraw);


    cerr << "\t\tINFO: mumugamma invariant mass : Mmumugamma = " << mumugammaInvMass << endl;

    double phiPhoton = myphoton->Phi();
    double etaPhoton = myphoton->Eta();
    double phiMuon = mymuon1->Phi();
    double etaMuon = mymuon1->Eta();
    double phiMuon_oppositeCharge = mymuon2->Phi();
    double etaMuon_oppositeCharge = mymuon2->Eta();
    double deltaRPM = DeltaR(etaPhoton, phiPhoton, etaMuon, phiMuon);
    double deltaRPAM = DeltaR(etaPhoton, phiPhoton, etaMuon_oppositeCharge, phiMuon_oppositeCharge);

    double deltaRmin;
    TRootMuon *farMuon;
    TRootMuon *nearMuon;
    TRootMuon *minusMuon;
    TRootMuon *plusMuon;

    if(deltaRPM < deltaRPAM){
      deltaRmin = deltaRPM;
      farMuon = (TRootMuon*) mymuon2;
      nearMuon = (TRootMuon*) mymuon1;
    } else {
      deltaRmin = deltaRPAM;
      farMuon = (TRootMuon*) mymuon1;
      nearMuon = (TRootMuon*) mymuon2;
    }
    if( mymuon1->charge()>0 ){
      plusMuon  = (TRootMuon*) mymuon1;
      minusMuon = (TRootMuon*) mymuon2;
    } else {
      minusMuon = (TRootMuon*) mymuon1;
      plusMuon  = (TRootMuon*) mymuon2;
    }

    // FILLING MINITREE INFORMATION
    MuonM_Pt = minusMuon->Pt();
    MuonM_Eta = minusMuon->Eta();
    MuonM_Phi = minusMuon->Phi();
    MuonM_isoR03_emEt = minusMuon->isoR03_emEt();
    MuonM_isoR03_hadEt = minusMuon->isoR03_hadEt();
    MuonM_isoR03_hoEt = minusMuon->isoR03_hoEt();
    MuonM_isoR03_nJets = minusMuon->isoR03_nJets();
    MuonM_isoR03_nTracks = minusMuon->isoR03_nTracks();
    MuonM_isoR03_sumPt = minusMuon->isoR03_sumPt();
    MuonM_isoR05_emEt = minusMuon->isoR05_emEt();
    MuonM_isoR05_hadEt = minusMuon->isoR05_hadEt();
    MuonM_isoR05_hoEt = minusMuon->isoR05_hoEt();
    MuonM_isoR05_nJets = minusMuon->isoR05_nJets();
    MuonM_isoR05_nTracks = minusMuon->isoR05_nTracks();
    MuonM_isoR05_sumPt = minusMuon->isoR05_sumPt();
    MuonP_Pt = plusMuon->Pt();
    MuonP_Eta = plusMuon->Eta();
    MuonP_Phi = plusMuon->Phi();
    MuonP_isoR03_emEt = plusMuon->isoR03_emEt();
    MuonP_isoR03_hadEt = plusMuon->isoR03_hadEt();
    MuonP_isoR03_hoEt = plusMuon->isoR03_hoEt();
    MuonP_isoR03_nJets = plusMuon->isoR03_nJets();
    MuonP_isoR03_nTracks = plusMuon->isoR03_nTracks();
    MuonP_isoR03_sumPt = plusMuon->isoR03_sumPt();
    MuonP_isoR05_emEt = plusMuon->isoR05_emEt();
    MuonP_isoR05_hadEt = plusMuon->isoR05_hadEt();
    MuonP_isoR05_hoEt = plusMuon->isoR05_hoEt();
    MuonP_isoR05_nJets = plusMuon->isoR05_nJets();
    MuonP_isoR05_nTracks = plusMuon->isoR05_nTracks();
    MuonP_isoR05_sumPt = plusMuon->isoR05_sumPt();
    MuonF_Pt = farMuon->Pt();
    MuonF_Eta = farMuon->Eta();
    MuonF_Phi = farMuon->Phi();
    MuonF_Charge = farMuon->charge();
    MuonF_isoR03_emEt = farMuon->isoR03_emEt();
    MuonF_isoR03_hadEt = farMuon->isoR03_hadEt();
    MuonF_isoR03_hoEt = farMuon->isoR03_hoEt();
    MuonF_isoR03_nJets = farMuon->isoR03_nJets();
    MuonF_isoR03_nTracks = farMuon->isoR03_nTracks();
    MuonF_isoR03_sumPt = farMuon->isoR03_sumPt();
    MuonF_isoR05_emEt = farMuon->isoR05_emEt();
    MuonF_isoR05_hadEt = farMuon->isoR05_hadEt();
    MuonF_isoR05_hoEt = farMuon->isoR05_hoEt();
    MuonF_isoR05_nJets = farMuon->isoR05_nJets();
    MuonF_isoR05_nTracks = farMuon->isoR05_nTracks();
    MuonF_isoR05_sumPt = farMuon->isoR05_sumPt();
    MuonN_Pt = nearMuon->Pt();
    MuonN_Eta = nearMuon->Eta();
    MuonN_Phi = nearMuon->Phi();
    MuonN_Charge = nearMuon->charge();
    MuonN_isoR03_emEt = nearMuon->isoR03_emEt();
    MuonN_isoR03_hadEt = nearMuon->isoR03_hadEt();
    MuonN_isoR03_hoEt = nearMuon->isoR03_hoEt();
    MuonN_isoR03_nJets = nearMuon->isoR03_nJets();
    MuonN_isoR03_nTracks = nearMuon->isoR03_nTracks();
    MuonN_isoR03_sumPt = nearMuon->isoR03_sumPt();
    MuonN_isoR05_emEt = nearMuon->isoR05_emEt();
    MuonN_isoR05_hadEt = nearMuon->isoR05_hadEt();
    MuonN_isoR05_hoEt = nearMuon->isoR05_hoEt();
    MuonN_isoR05_nJets = nearMuon->isoR05_nJets();
    MuonN_isoR05_nTracks = nearMuon->isoR05_nTracks();
    MuonN_isoR05_sumPt = nearMuon->isoR05_sumPt();

    deltaRNear = DeltaR(etaPhoton, phiPhoton, nearMuon->Eta(), nearMuon->Phi());
    deltaRFar = DeltaR(etaPhoton, phiPhoton, farMuon->Eta(), farMuon->Phi());
    deltaRMinus = DeltaR(etaPhoton, phiPhoton, minusMuon->Eta(), minusMuon->Phi());
    deltaRPlus = DeltaR(etaPhoton, phiPhoton, plusMuon->Eta(), plusMuon->Phi());
    deltaRLeading = DeltaR(etaPhoton, phiPhoton, leadingMuon->Eta(), leadingMuon->Phi());
    deltaRSubleading = DeltaR(etaPhoton, phiPhoton, subleadingMuon->Eta(), subleadingMuon->Phi());


		myphoton->Clear();
		mymuon1->Clear();
		mymuon2->Clear();
    farMuon->Clear();
    nearMuon->Clear();
    minusMuon->Clear();
    plusMuon->Clear();
    PhotonSC->Clear();
    Photon5x5->Clear();
    PhotonSC_raw->Clear();
    leadingMuon->Clear();
    subleadingMuon->Clear();

		}




		isAfterCut1c = 1;
		nAfterCut1c++;

		isAfterCut1d = 1;
		nAfterCut1d++;

		isAfterCut1e = 1;
		nAfterCut1e++;

		isAfterCut2a = 1;
		nAfterCut2a++;

		isAfterCut2b = 1;
		nAfterCut2b++;

		isAfterCut2c = 1;
		nAfterCut2c++;


		isAfterCut3 = 1;
		nAfterCut3++;

		isAfterCut4 = 1;
		nAfterCut4++;

		isAfterCut5 = 1;
		nAfterCut5++;

		isAfterCut6 = 1;
		nAfterCut6++;

		isAfterCut7 = 1;
		nAfterCut7++;

		isAfterCut8 = 1;
		nAfterCut8++;
		isAfterCut9 = 1;
		nAfterCut9++;
		isAfterCut10 = 1;
		nAfterCut10++;
		isSelected = 1;
		nSelected++;
		cerr << "OK: Surviving veto event: "<< ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )"  << endl;
/*
		SelectedEvent_RunNumber.push_back(event->runId());
		SelectedEvent_LumiNumber.push_back(event->luminosityBlock());
		SelectedEvent_EventNumber.push_back(event->eventId());
		SelectedEvent_mumugammaInvMass.push_back(mumugammaInvMass);
		SelectedEvent_Eta_gamma.push_back(Photon_Eta);
		SelectedEvent_Eta_muonNear.push_back(MuonN_Eta);
		SelectedEvent_Eta_muonFar.push_back(MuonF_Eta);
		SelectedEvent_Et_gamma.push_back(PtPhoton);
		SelectedEvent_Pt_muonNear.push_back(MuonN_Pt);
		SelectedEvent_Pt_muonFar.push_back(MuonF_Pt);
		SelectedEvent_DeltaRNear.push_back(deltaRNear);
		SelectedEvent_DeltaRFar.push_back(deltaRFar);
		SelectedEvent_mumuInvMass.push_back(mumuInvMass);

		outfile << Photon_SC_Eta << "\t" << Photon_SC_Phi << "\t" << Photon_isEB << "\t" << Photon_isEE << "\t" << Photon_Et << "\t" << Photon_seedPosition1 << "\t" << Photon_seedPosition2 << "\t" << Photon_r9 << "\t" << Photon_convNTracks
		 << "\t" << Mmumu << "\t" << Mmumugamma << "\t" << Mmumugamma_5x5 << "\t" << Mmumugamma_SC << "\t" << Mmumugamma_SCraw
		 << "\t" << mmg_k << "\t" << mmg_ik << "\t" << mmg_s << "\t" << mmg_logk << "\t" << mmg_logik << "\t" << mmg_logs
		 << "\t" << mmg_k_5x5 << "\t" << mmg_ik_5x5 << "\t" << mmg_s_5x5 << "\t" << mmg_logk_5x5 << "\t" << mmg_logik_5x5 << "\t" << mmg_logs_5x5
		 << "\t" << mmg_k_SC << "\t" << mmg_ik_SC << "\t" << mmg_s_SC << "\t" << mmg_logk_SC << "\t" << mmg_logik_SC << "\t" << mmg_logs_SC
		 << "\t" << mmg_k_SCraw << "\t" << mmg_ik_SCraw << "\t" << mmg_s_SCraw << "\t" << mmg_logk_SCraw << "\t" << mmg_logik_SCraw << "\t" << mmg_logs_SCraw
		<< endl;
*/
		miniTree->Fill();

//			event->printHltAcceptNames();
			outputEventTree->Fill();
	} // fin boucle sur evts

/*	cout << endl << "**************************************************************************" << endl;
	cout << "DUMPING THE INFORMATION ABOUT SELECTED EVENTS:" << endl;
	cout << "RUN\t\tLUMI SECTION\t\tEVENT NUMBER\t\t\t\tM(MUMUGAMMA)\t\tEt GAMMA\t\tPt MUON NEAR\t\tPt Muon FAR\t\tDELTAR MUON NEAR\t\tDELTAR MUON FAR\t\tM(MUMU)\t\tETA MUON NEAR\t\tETA MUON FAR\t\tETA PHOTON\t\tK" << endl;
	double k = 0;
	for( int iselected=0 ; iselected<nSelected ; iselected++ ){
		k = (double)(pow(91.1876, 2) - pow(SelectedEvent_mumuInvMass[iselected], 2))/(double)(pow(SelectedEvent_mumugammaInvMass[iselected], 2) - pow(SelectedEvent_mumuInvMass[iselected], 2));
		cout << SelectedEvent_RunNumber[iselected] << "\t\t" << SelectedEvent_LumiNumber[iselected] << "\t\t" << SelectedEvent_EventNumber[iselected] << "\t\t\t" << SelectedEvent_mumugammaInvMass[iselected] << "\t\t" << SelectedEvent_Et_gamma[iselected] << "\t\t" << SelectedEvent_Pt_muonNear[iselected] << "\t\t" << SelectedEvent_Pt_muonFar[iselected] << "\t\t" << SelectedEvent_DeltaRNear[iselected] << "\t\t" << SelectedEvent_DeltaRFar[iselected] << "\t\t" << SelectedEvent_mumuInvMass[iselected] << "\t\t" << SelectedEvent_Eta_muonNear[iselected] << "\t\t" << SelectedEvent_Eta_muonFar[iselected] << "\t\t" << SelectedEvent_Eta_gamma[iselected] << "\t\t" << k << endl;
	}

	cout << endl << "**************************************************************************" << endl;
	cout << "cut" << "\t\t" << "# events" << "\t\t" << "% rel"	<< "\t\t" << "% abs"<<endl;
	cout << "nBeforeAllCuts=" << "\t\t" << nBeforeAllCuts << "\t\t" << "-" << "\t\t" << "-" << endl;
	cout << "nAfterCutPthatFilter=" << "\t\t" << nAfterCutPthatFilter << "\t\t" << (double)nAfterCutPthatFilter/(double)nBeforeAllCuts*100.0 << "\t\t" << (double)nAfterCutPthatFilter/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCutCSA07ID=" << "\t\t" << nAfterCutCSA07ID << "\t\t" << (double)nAfterCutCSA07ID/(double)nBeforeAllCuts*100.0 << "\t\t" << (double)nAfterCutCSA07ID/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCutZJETVETO=" << "\t\t" << nAfterCutZJETVETO << "\t\t" << (double)nAfterCutZJETVETO/(double)nBeforeAllCuts*100.0 << "\t\t" << (double)nAfterCutZJETVETO/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterLooseMMG=" << "\t\t" << nAfterLooseMMG << "\t\t" << (double)nAfterLooseMMG/(double)nBeforeAllCuts*100.0 << "\t\t" << (double)nAfterLooseMMG/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterTightMMG=" << "\t\t" << nAfterTightMMG << "\t\t" << (double)nAfterTightMMG/(double)nAfterLooseMMG*100.0 << "\t\t" << (double)nAfterTightMMG/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut1c=" << "\t\t" << nAfterCut1c << "\t\t" << (double)nAfterCut1c/(double)nAfterTightMMG*100.0 << "\t\t" << (double)nAfterCut1c/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut1d=" << "\t\t" << nAfterCut1d << "\t\t" << (double)nAfterCut1d/(double)nAfterCut1c*100.0 << "\t\t" << (double)nAfterCut1d/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut1e=" << "\t\t" << nAfterCut1e << "\t\t" << (double)nAfterCut1e/(double)nAfterCut1d*100.0 << "\t\t" << (double)nAfterCut1e/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut2a=" << "\t\t" << nAfterCut2a << "\t\t" << (double)nAfterCut2a/(double)nAfterCut1e*100.0 << "\t\t" << (double)nAfterCut2a/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut2b=" << "\t\t" << nAfterCut2b << "\t\t" << (double)nAfterCut2b/(double)nAfterCut2a*100.0 << "\t\t" << (double)nAfterCut2b/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut2c=" << "\t\t" << nAfterCut2c << "\t\t" << (double)nAfterCut2c/(double)nAfterCut2b*100.0 << "\t\t" << (double)nAfterCut2c/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut3=" << "\t\t" << nAfterCut3 << "\t\t" << (double)nAfterCut3/(double)nAfterCut2c*100.0 << "\t\t" << (double)nAfterCut3/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut4=" << "\t\t" << nAfterCut4 << "\t\t" << (double)nAfterCut4/(double)nAfterCut3*100.0 << "\t\t" << (double)nAfterCut4/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut5=" << "\t\t" << nAfterCut5 << "\t\t" << (double)nAfterCut5/(double)nAfterCut4*100.0 << "\t\t" << (double)nAfterCut5/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut6=" << "\t\t" << nAfterCut6 << "\t\t" << (double)nAfterCut6/(double)nAfterCut5*100.0 << "\t\t" << (double)nAfterCut6/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut7=" << "\t\t" << nAfterCut7 << "\t\t" << (double)nAfterCut7/(double)nAfterCut6*100.0 << "\t\t" << (double)nAfterCut7/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut8=" << "\t\t" << nAfterCut8 << "\t\t" << (double)nAfterCut8/(double)nAfterCut7*100.0 << "\t\t" << (double)nAfterCut8/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut9=" << "\t\t" << nAfterCut9 << "\t\t" << (double)nAfterCut9/(double)nAfterCut8*100.0 << "\t\t" << (double)nAfterCut9/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut10=" << "\t\t" << nAfterCut10 << "\t\t" << (double)nAfterCut10/(double)nAfterCut9*100.0 << "\t\t" << (double)nAfterCut10/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nSelected=" << "\t\t" << nSelected << "\t\t" << (double)nSelected/(double)nAfterCut10*100.0 << "\t\t" << (double)nSelected/(double)nBeforeAllCuts*100.0 << endl;
*/

	outputEventTree->AutoSave();
	
	OutputRootFile->cd();
	OutputRootFile->Write();
	OutputRootFile->Close();

	OutputRootFile->Clear();
	inputEventTree->Clear();

		for(int i = 0; i < 12 ; i++)
		{
			cout << "TOTALnbMuonsAfterID["<<i<<"]= " << TOTALnbMuonsAfterID[i] << "\t\t" << "TOTALnbEventsAfterMuonID["<<i<<"]= " << TOTALnbEventsAfterMuonID[i] << endl;
		}
		for(int i = 0; i < 3 ; i++)
		{
			cout << "TOTALnbDimuonsAfterID["<<i<<"]= " << TOTALnbDimuonsAfterID[i] << "\t\t" << "TOTALnbEventsAfterDimuonID["<<i<<"]= " << TOTALnbEventsAfterDimuonID[i] << endl;
		}
		for(int i = 0; i < 6 ; i++)
    {
      cout << "TOTALnbPhotonsAfterID["<<i<<"]= " << TOTALnbPhotonsAfterID[i] << "\t\t" << "TOTALnbEventsAfterPhotonID["<<i<<"]= " << TOTALnbEventsAfterPhotonID[i] << endl;
		}
		for(int i = 0; i < 7 ; i++)
		{
			cout << "TOTALnbMuMuGammaAfterID["<<i<<"]= " << TOTALnbMuMuGammaAfterID[i] << "\t\t" << "TOTALnbEventsAfterMuMuGammaID["<<i<<"]= " << TOTALnbEventsAfterMuMuGammaID[i] << endl;
		}
	return 0;
}
