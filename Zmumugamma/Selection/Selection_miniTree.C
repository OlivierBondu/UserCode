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

#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootBardak.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootBeamSpot.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootCluster.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootDummyEvent.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootEcalRecHit.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootElectron.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootEvent.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootJet.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootMCParticle.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootMCPhoton.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootMET.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootMuon.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootParticle.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootPhoton.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootRun.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootSignalEvent.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootSuperCluster.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootTopTop.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootTrack.h"
#include "/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/interface/TRootVertex.h"


int Selection_miniTree(){
//int main(){
	//gSystem->Load("libPhysics.so");
	//gSystem->Load("libEG.so");
	//gSystem->Load("/afs/cern.ch/cms/CAF/CMSCOMM/COMM_ECAL/lethuill/Skim_PTString plotDir=aolo_MinimumBias_BeamCommissioning09_BSCFilter_v6/libToto.so");
	gSystem->Load("/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/src/libToto.so");
//	gSystem->Load("/sps/cms/chanon/Samples/DATA_MC_IpnTreeProducer35701_CMSSW356_EGskim/libToto.so");
	
	bool doHLT                    = true;
	bool doMC                     = false;
	bool doJetMC                  = false;
	bool doMETMC                  = false;
	bool doPDFInfo                = true;
	bool doSignalMuMuGamma        = false;
	bool doSignalTopTop           = false;
	bool doPhotonConversionMC     = false;
	bool doBeamSpot               = true;
	bool doPrimaryVertex          = true;
	bool doZeePrimaryVertex       = false;
	bool doTrack                  = true;
	bool doJet                    = false;
	bool doMuon                   = true;
	bool doElectron               = true;
	bool doPhoton                 = true;
	bool doCluster                = true;
	bool doPhotonConversion       = true;
	bool doMET                    = false;
	bool doBardak                 = false;
	bool doPhotonVertexCorrection = false;
	bool doPhotonIsolation        = true;
	
	TString dataset = "DATA";
	TChain *inputEventTree = new TChain("eventTree");
	//inputEventTree->Add("/sps/cms/chanon/Samples/DATA_MC_IpnTreeProducer35701_CMSSW356_EGskim/DATA_MinimumBias__Commissioning10-Apr15Skim_356_PreProduction_SD_EG-v2__RECO_TOTOANA_1_1.root");
	//inputEventTree->Add("/sps/cms/chanon/Samples/DATA_MC_IpnTreeProducer35701_CMSSW356_EGskim/MC_MinBias_V26A_356ReReco-v1_EGskim/MC__MinBias__Spring10-START3X_V26A_356ReReco-v1__GEN-SIM-RECO__FILTER__TOTOANA_*root");
	inputEventTree->Add("/sps/cms/obondu/CMSSW_3_5_8_patch3/src/Zmumugamma/RecoSamples/2010-05-25-RUN-136033_LUMI-1007/Toto_2010-05-25-RUN-136033_LUMI-1007_1.root");
	
	TFile* OutputRootFile = new TFile("miniTree_TEST_data.root", "RECREATE");
	
	TBranch* event_br = 0;
	TRootEvent* event = 0;
	inputEventTree->SetBranchAddress("Event", &event, &event_br);
	inputEventTree->SetBranchStatus("Event", 1);
	
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
		inputEventTree->SetBranchAddress("Jets", &jets, &jets_br);
		inputEventTree->SetBranchStatus("Jets", 1);
	}
	
		TBranch* muons_br = 0;
		TClonesArray* muons = new TClonesArray("TRootMuon", 0);
	if(doMuon)
	{
		inputEventTree->SetBranchAddress("Muons", &muons, &muons_br);
		inputEventTree->SetBranchStatus("Muons", 1);
	}
	
		TBranch* electrons_br = 0;
		TClonesArray* electrons = new TClonesArray("TRootElectron", 0);
	if(doElectron)
	{
		inputEventTree->SetBranchAddress("Electrons", &electrons, &electrons_br);
		inputEventTree->SetBranchStatus("Electrons", 1);
	}
	
//	TClonesArray* photons = 0;
		TBranch* photons_br = 0;
		TClonesArray* photons = new TClonesArray("TRootPhoton", 0);
	if(doPhoton)
	{
		inputEventTree->SetBranchAddress("Photons", &photons, &photons_br);
		inputEventTree->SetBranchStatus("Photons", 1);
	}
	
	//	if(doCluster)
	//	{

		TBranch* clusters_br = 0;
		TClonesArray* clusters = new TClonesArray("TRootCluster", 0);
		inputEventTree->SetBranchAddress("BasicClusters", &clusters, &clusters_br);
		inputEventTree->SetBranchStatus("BasicClusters", 1);
		
		TBranch* superClusters_br = 0;
		TClonesArray* superClusters = new TClonesArray("TRootSuperCluster", 0);
		inputEventTree->SetBranchAddress("SuperClusters", &superClusters, &superClusters_br);
		inputEventTree->SetBranchStatus("SuperClusters", 1);
		//	}
	
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
		inputEventTree->SetBranchAddress("MET", &met, &met_br);
		inputEventTree->SetBranchStatus("MET", 1);
	}
	
		TBranch* bardak_br = 0;
		TRootBardak* bardak = 0;
	if(doBardak)
	{
		inputEventTree->SetBranchAddress("bardak", &bardak, &bardak_br);
		inputEventTree->SetBranchStatus("bardak", 1);
	}
	
	
	//cout << "runTree->GetEntries()="<<runTree->GetEntries()<<endl;MinimumBias__BeamCommissioning09-BSCNOBEAMHALO-Dec19thSkim_336p3_v1__TOTOANA_1.root
	//runTree->GetEvent(0);
	
	// Dataset infos
	//cout << "Dataset desciption:"<<runInfos->description()<<endl;
	//cout << "Dataset xsection:"<<runInfos->xsection()<<endl;
	
	// HLT Run Summary
	/*
	if (doHLT)
	{
		cout << dec << endl;
		cout << "HLT-Report " << "---------- Event  Summary ------------\n";
		cout << "HLT-Report"
		<< " Events total = " << runInfos->nHLTEvents()
		<< "  wasrun = " << runInfos->nHLTWasRun()
		<< "  passed = " << runInfos->nHLTAccept()
		<< "  errors = " << runInfos->nHLTErrors()
		<< "\n";
		
		cout << endl;
		cout << "HLT-Report " << "---------- HLTrig Summary ------------\n";
		cout << "HLT-Report   HLT Bit#     WasRun     Passed     Errors  Name\n";
		
		for (unsigned int i=0; i!=runInfos->nHLTPaths(); ++i)
		{
			printf("HLT-Report %10u %10u %10u %10u  ", i, runInfos->hltWasRun(i), runInfos->hltAccept(i), runInfos->hltErrors(i));
			cout << runInfos->hltNames(i) << endl;
}

cout << endl;
}
*/
	Double_t MYPI = 3.1415926535897932384626433832795028841972;

	// ____________________________________________
	// Event information
	// ____________________________________________
	Int_t iEvent, iEventID;
	Int_t isSignalApplied, isStewApplied, isZJetsApplied;

	Int_t isBeforeAllCuts, isAfterCutCSA07ID, isAfterCutZJETVETO;
	Int_t isAfterCut1a, isAfterCut1b, isAfterCut1c, isAfterCut1d, isAfterCut1e;
	Int_t isAfterCut2a, isAfterCut2b, isAfterCut2c;
	Int_t isAfterCut3, isAfterCut4, isAfterCut5, isAfterCut6, isAfterCut7, isAfterCut8, isAfterCut9, isAfterCut10;
	Int_t isSelected;

	// ____________________________________________
	// Muon variables
	// ____________________________________________
	Int_t NbMuons;
// (M minus charge, P plus charge), (F far, N near), (H high, L low)
	Float_t MuonM_Pt, MuonP_Pt, MuonN_Pt, MuonF_Pt, MuonH_Pt, MuonL_Pt;
	Float_t MuonM_Eta, MuonP_Eta, MuonN_Eta, MuonF_Eta, MuonH_Eta, MuonL_Eta;
	Float_t MuonM_Phi, MuonP_Phi, MuonN_Phi, MuonF_Phi, MuonH_Phi, MuonL_Phi;
	Int_t MuonF_Charge, MuonN_Charge, MuonH_Charge, MuonL_Charge;

	Float_t MuonM_isoR03_emEt, MuonP_isoR03_emEt, MuonN_isoR03_emEt, MuonF_isoR03_emEt, MuonH_isoR03_emEt, MuonL_isoR03_emEt;
	Float_t MuonM_isoR03_hadEt, MuonP_isoR03_hadEt, MuonN_isoR03_hadEt, MuonF_isoR03_hadEt, MuonH_isoR03_hadEt, MuonL_isoR03_hadEt;
	Float_t MuonM_isoR03_hoEt, MuonP_isoR03_hoEt, MuonN_isoR03_hoEt, MuonF_isoR03_hoEt, MuonH_isoR03_hoEt, MuonL_isoR03_hoEt;
	Float_t MuonM_isoR03_nJets, MuonP_isoR03_nJets, MuonN_isoR03_nJets, MuonF_isoR03_nJets, MuonH_isoR03_nJets, MuonL_isoR03_nJets;
	Float_t MuonM_isoR03_nTracks, MuonP_isoR03_nTracks, MuonN_isoR03_nTracks, MuonF_isoR03_nTracks, MuonH_isoR03_nTracks, MuonL_isoR03_nTracks;
	Float_t MuonM_isoR03_sumPt, MuonP_isoR03_sumPt, MuonN_isoR03_sumPt, MuonF_isoR03_sumPt, MuonH_isoR03_sumPt, MuonL_isoR03_sumPt;

	Float_t MuonM_isoR05_emEt, MuonP_isoR05_emEt, MuonN_isoR05_emEt, MuonF_isoR05_emEt, MuonH_isoR05_emEt, MuonL_isoR05_emEt;
	Float_t MuonM_isoR05_hadEt, MuonP_isoR05_hadEt, MuonN_isoR05_hadEt, MuonF_isoR05_hadEt, MuonH_isoR05_hadEt, MuonL_isoR05_hadEt;
	Float_t MuonM_isoR05_hoEt, MuonP_isoR05_hoEt, MuonN_isoR05_hoEt, MuonF_isoR05_hoEt, MuonH_isoR05_hoEt, MuonL_isoR05_hoEt;
	Float_t MuonM_isoR05_nJets, MuonP_isoR05_nJets, MuonN_isoR05_nJets, MuonF_isoR05_nJets, MuonH_isoR05_nJets, MuonL_isoR05_nJets;
	Float_t MuonM_isoR05_nTracks, MuonP_isoR05_nTracks, MuonN_isoR05_nTracks, MuonF_isoR05_nTracks, MuonH_isoR05_nTracks, MuonL_isoR05_nTracks;
	Float_t MuonM_isoR05_sumPt, MuonP_isoR05_sumPt, MuonN_isoR05_sumPt, MuonF_isoR05_sumPt, MuonH_isoR05_sumPt, MuonL_isoR05_sumPt;
//	Float_t MuonM_, MuonP_, MuonN_, MuonF_, MuonH_, MuonL_;

	// ____________________________________________
	// Photon variables
	// ___________________________________________
	Int_t NbPhotons;
	Float_t Photon_Eta, Photon_Phi;
	Int_t Photon_isEBorEE, Photon_isEB, Photon_isEE, Photon_isEEP, Photon_isEEM;

	Int_t Photon_Multiplicity, Photon_hasPixelSeed, Photon_isAlsoElectron, Photon_Nclusters, Photon_nBasicClusters, Photon_nXtals;
	Int_t Photon_isTightPhoton, Photon_isLoosePhoton;
	Int_t Photon_convNTracks, Photon_isoNTracksSolidCone, Photon_isoNTracksHollowCone, Photon_isolationPersoNTracksSolidCone;
	Float_t Photon_E, Photon_Et, Photon_E2x2, Photon_E3x3, Photon_E5x5, Photon_Emax, Photon_E2nd;
	Float_t Photon_r19, Photon_r9, Photon_cross;
	Float_t Photon_caloConeSize, Photon_PreshEnergy, Photon_HoE, Photon_covIetaIeta, Photon_covIphiIphi, Photon_etaWidth, Photon_phiWidth;
	Float_t Photon_isoEcalRecHit, Photon_isoHcalRecHit, Photon_isoSolidTrkCone, Photon_isoHollowTrkCone, Photon_isoPersoSolidTrkCone, Photon_isolationPersoTracksSolidCone;
	Float_t Photon_seedTime, Photon_seedFlag;

	// ____________________________________________
	// mugamma / mumu / mumugamma information
	// ____________________________________________
	
	Float_t Mmumu, Mmumugamma;
	Float_t deltaRNear, deltaRFar, deltaRMinus, deltaRPlus, deltaRHigh, deltaRLow;
 
	// ____________________________________________
	// preparing the tree
	// ____________________________________________

	TTree* miniTree = new TTree("miniTree","Mu Mu Gamma informations");

	// ____________________________________________
	// Event information
	// ____________________________________________
	
	miniTree->Branch("iEvent", &iEvent, "iEvent/I");
	miniTree->Branch("iEventID", &iEventID, "iEventID/I");

	miniTree->Branch("isSignalApplied", &isSignalApplied, "isSignalApplied/I");
	miniTree->Branch("sStewApplied", &isStewApplied, "isStewApplied/I");
	miniTree->Branch("isZJetsApplied", &isZJetsApplied, "isZJetsApplied/I");

	miniTree->Branch("isBeforeAllCuts", &isBeforeAllCuts, "isBeforeAllCuts/I");
	miniTree->Branch("isAfterCutCSA07ID", &isAfterCutCSA07ID, "isAfterCutCSA07ID/I");
	miniTree->Branch("isAfterCutZJETVETO", &isAfterCutZJETVETO, "isAfterCutZJETVETO/I");

	miniTree->Branch("isAfterCut1a", &isAfterCut1a, "isAfterCut1a/I");
	miniTree->Branch("isAfterCut1b", &isAfterCut1b, "isAfterCut1b/I");
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

	// ____________________________________________
	// Muon variables
	// ____________________________________________

	miniTree->Branch("NbMuons", &NbMuons, "NbMuons/I");

	miniTree->Branch("MuonM_Pt", &MuonM_Pt, "MuonM_Pt/F");
	miniTree->Branch("MuonP_Pt", &MuonP_Pt, "MuonP_Pt/F");
	miniTree->Branch("MuonF_Pt", &MuonF_Pt, "MuonF_Pt/F");
	miniTree->Branch("MuonN_Pt", &MuonN_Pt, "MuonN_Pt/F");
	miniTree->Branch("MuonH_Pt", &MuonH_Pt, "MuonH_Pt/F");
	miniTree->Branch("MuonL_Pt", &MuonL_Pt, "MuonL_Pt/F");

	miniTree->Branch("MuonM_Eta", &MuonM_Eta, "MuonM_Eta/F");
	miniTree->Branch("MuonP_Eta", &MuonP_Eta, "MuonP_Eta/F");
	miniTree->Branch("MuonF_Eta", &MuonF_Eta, "MuonF_Eta/F");
	miniTree->Branch("MuonN_Eta", &MuonN_Eta, "MuonN_Eta/F");
	miniTree->Branch("MuonH_Eta", &MuonH_Eta, "MuonH_Eta/F");
	miniTree->Branch("MuonL_Eta", &MuonL_Eta, "MuonL_Eta/F");

	miniTree->Branch("MuonM_Phi", &MuonM_Phi, "MuonM_Phi/F");
	miniTree->Branch("MuonP_Phi", &MuonP_Phi, "MuonP_Phi/F");
	miniTree->Branch("MuonF_Phi", &MuonF_Phi, "MuonF_Phi/F");
	miniTree->Branch("MuonN_Phi", &MuonN_Phi, "MuonN_Phi/F");
	miniTree->Branch("MuonH_Phi", &MuonH_Phi, "MuonH_Phi/F");
	miniTree->Branch("MuonL_Phi", &MuonL_Phi, "MuonL_Phi/F");

	miniTree->Branch("MuonF_Charge", &MuonF_Charge, "MuonF_Charge/I");
	miniTree->Branch("MuonN_Charge", &MuonN_Charge, "MuonN_Charge/I");
	miniTree->Branch("MuonH_Charge", &MuonH_Charge, "MuonH_Charge/I");
	miniTree->Branch("MuonL_Charge", &MuonL_Charge, "MuonL_Charge/I");
	
	miniTree->Branch("MuonM_isoR03_emEt", &MuonM_isoR03_emEt, "MuonM_isoR03_emEt/F");
	miniTree->Branch("MuonP_isoR03_emEt", &MuonP_isoR03_emEt, "MuonP_isoR03_emEt/F");
	miniTree->Branch("MuonF_isoR03_emEt", &MuonF_isoR03_emEt, "MuonF_isoR03_emEt/F");
	miniTree->Branch("MuonN_isoR03_emEt", &MuonN_isoR03_emEt, "MuonN_isoR03_emEt/F");
	miniTree->Branch("MuonH_isoR03_emEt", &MuonH_isoR03_emEt, "MuonH_isoR03_emEt/F");
	miniTree->Branch("MuonL_isoR03_emEt", &MuonL_isoR03_emEt, "MuonL_isoR03_emEt/F");

	miniTree->Branch("MuonM_isoR03_hadEt", &MuonM_isoR03_hadEt, "MuonM_isoR03_hadEt/F");
	miniTree->Branch("MuonP_isoR03_hadEt", &MuonP_isoR03_hadEt, "MuonP_isoR03_hadEt/F");
	miniTree->Branch("MuonF_isoR03_hadEt", &MuonF_isoR03_hadEt, "MuonF_isoR03_hadEt/F");
	miniTree->Branch("MuonN_isoR03_hadEt", &MuonN_isoR03_hadEt, "MuonN_isoR03_hadEt/F");
	miniTree->Branch("MuonH_isoR03_hadEt", &MuonH_isoR03_hadEt, "MuonH_isoR03_hadEt/F");
	miniTree->Branch("MuonL_isoR03_hadEt", &MuonL_isoR03_hadEt, "MuonL_isoR03_hadEt/F");

	miniTree->Branch("MuonM_isoR03_hoEt", &MuonM_isoR03_hoEt, "MuonM_isoR03_hoEt/F");
	miniTree->Branch("MuonP_isoR03_hoEt", &MuonP_isoR03_hoEt, "MuonP_isoR03_hoEt/F");
	miniTree->Branch("MuonF_isoR03_hoEt", &MuonF_isoR03_hoEt, "MuonF_isoR03_hoEt/F");
	miniTree->Branch("MuonN_isoR03_hoEt", &MuonN_isoR03_hoEt, "MuonN_isoR03_hoEt/F");
	miniTree->Branch("MuonH_isoR03_hoEt", &MuonH_isoR03_hoEt, "MuonH_isoR03_hoEt/F");
	miniTree->Branch("MuonL_isoR03_hoEt", &MuonL_isoR03_hoEt, "MuonL_isoR03_hoEt/F");

	miniTree->Branch("MuonM_isoR03_nJets", &MuonM_isoR03_nJets, "MuonM_isoR03_nJets/F");
	miniTree->Branch("MuonP_isoR03_nJets", &MuonP_isoR03_nJets, "MuonP_isoR03_nJets/F");
	miniTree->Branch("MuonF_isoR03_nJets", &MuonF_isoR03_nJets, "MuonF_isoR03_nJets/F");
	miniTree->Branch("MuonN_isoR03_nJets", &MuonN_isoR03_nJets, "MuonN_isoR03_nJets/F");
	miniTree->Branch("MuonH_isoR03_nJets", &MuonH_isoR03_nJets, "MuonH_isoR03_nJets/F");
	miniTree->Branch("MuonL_isoR03_nJets", &MuonL_isoR03_nJets, "MuonL_isoR03_nJets/F");

	miniTree->Branch("MuonM_isoR03_nTracks", &MuonM_isoR03_nTracks, "MuonM_isoR03_nTracks/F");
	miniTree->Branch("MuonP_isoR03_nTracks", &MuonP_isoR03_nTracks, "MuonP_isoR03_nTracks/F");
	miniTree->Branch("MuonF_isoR03_nTracks", &MuonF_isoR03_nTracks, "MuonF_isoR03_nTracks/F");
	miniTree->Branch("MuonN_isoR03_nTracks", &MuonN_isoR03_nTracks, "MuonN_isoR03_nTracks/F");
	miniTree->Branch("MuonH_isoR03_nTracks", &MuonH_isoR03_nTracks, "MuonH_isoR03_nTracks/F");
	miniTree->Branch("MuonL_isoR03_nTracks", &MuonL_isoR03_nTracks, "MuonL_isoR03_nTracks/F");

	miniTree->Branch("MuonM_isoR03_sumPt", &MuonM_isoR03_sumPt, "MuonM_isoR03_sumPt/F");
	miniTree->Branch("MuonP_isoR03_sumPt", &MuonP_isoR03_sumPt, "MuonP_isoR03_sumPt/F");
	miniTree->Branch("MuonF_isoR03_sumPt", &MuonF_isoR03_sumPt, "MuonF_isoR03_sumPt/F");
	miniTree->Branch("MuonN_isoR03_sumPt", &MuonN_isoR03_sumPt, "MuonN_isoR03_sumPt/F");
	miniTree->Branch("MuonH_isoR03_sumPt", &MuonH_isoR03_sumPt, "MuonH_isoR03_sumPt/F");
	miniTree->Branch("MuonL_isoR03_sumPt", &MuonL_isoR03_sumPt, "MuonL_isoR03_sumPt/F");

	miniTree->Branch("MuonM_isoR05_emEt", &MuonM_isoR05_emEt, "MuonM_isoR05_emEt/F");
	miniTree->Branch("MuonP_isoR05_emEt", &MuonP_isoR05_emEt, "MuonP_isoR05_emEt/F");
	miniTree->Branch("MuonF_isoR05_emEt", &MuonF_isoR05_emEt, "MuonF_isoR05_emEt/F");
	miniTree->Branch("MuonN_isoR05_emEt", &MuonN_isoR05_emEt, "MuonN_isoR05_emEt/F");
	miniTree->Branch("MuonH_isoR05_emEt", &MuonH_isoR05_emEt, "MuonH_isoR05_emEt/F");
	miniTree->Branch("MuonL_isoR05_emEt", &MuonL_isoR05_emEt, "MuonL_isoR05_emEt/F");

	miniTree->Branch("MuonM_isoR05_hadEt", &MuonM_isoR05_hadEt, "MuonM_isoR05_hadEt/F");
	miniTree->Branch("MuonP_isoR05_hadEt", &MuonP_isoR05_hadEt, "MuonP_isoR05_hadEt/F");
	miniTree->Branch("MuonF_isoR05_hadEt", &MuonF_isoR05_hadEt, "MuonF_isoR05_hadEt/F");
	miniTree->Branch("MuonN_isoR05_hadEt", &MuonN_isoR05_hadEt, "MuonN_isoR05_hadEt/F");
	miniTree->Branch("MuonH_isoR05_hadEt", &MuonH_isoR05_hadEt, "MuonH_isoR05_hadEt/F");
	miniTree->Branch("MuonL_isoR05_hadEt", &MuonL_isoR05_hadEt, "MuonL_isoR05_hadEt/F");

	miniTree->Branch("MuonM_isoR05_hoEt", &MuonM_isoR05_hoEt, "MuonM_isoR05_hoEt/F");
	miniTree->Branch("MuonP_isoR05_hoEt", &MuonP_isoR05_hoEt, "MuonP_isoR05_hoEt/F");
	miniTree->Branch("MuonF_isoR05_hoEt", &MuonF_isoR05_hoEt, "MuonF_isoR05_hoEt/F");
	miniTree->Branch("MuonN_isoR05_hoEt", &MuonN_isoR05_hoEt, "MuonN_isoR05_hoEt/F");
	miniTree->Branch("MuonH_isoR05_hoEt", &MuonH_isoR05_hoEt, "MuonH_isoR05_hoEt/F");
	miniTree->Branch("MuonL_isoR05_hoEt", &MuonL_isoR05_hoEt, "MuonL_isoR05_hoEt/F");

	miniTree->Branch("MuonM_isoR05_nJets", &MuonM_isoR05_nJets, "MuonM_isoR05_nJets/F");
	miniTree->Branch("MuonP_isoR05_nJets", &MuonP_isoR05_nJets, "MuonP_isoR05_nJets/F");
	miniTree->Branch("MuonF_isoR05_nJets", &MuonF_isoR05_nJets, "MuonF_isoR05_nJets/F");
	miniTree->Branch("MuonN_isoR05_nJets", &MuonN_isoR05_nJets, "MuonN_isoR05_nJets/F");
	miniTree->Branch("MuonH_isoR05_nJets", &MuonH_isoR05_nJets, "MuonH_isoR05_nJets/F");
	miniTree->Branch("MuonL_isoR05_nJets", &MuonL_isoR05_nJets, "MuonL_isoR05_nJets/F");

	miniTree->Branch("MuonM_isoR05_nTracks", &MuonM_isoR05_nTracks, "MuonM_isoR05_nTracks/F");
	miniTree->Branch("MuonP_isoR05_nTracks", &MuonP_isoR05_nTracks, "MuonP_isoR05_nTracks/F");
	miniTree->Branch("MuonF_isoR05_nTracks", &MuonF_isoR05_nTracks, "MuonF_isoR05_nTracks/F");
	miniTree->Branch("MuonN_isoR05_nTracks", &MuonN_isoR05_nTracks, "MuonN_isoR05_nTracks/F");
	miniTree->Branch("MuonH_isoR05_nTracks", &MuonH_isoR05_nTracks, "MuonH_isoR05_nTracks/F");
	miniTree->Branch("MuonL_isoR05_nTracks", &MuonL_isoR05_nTracks, "MuonL_isoR05_nTracks/F");

	miniTree->Branch("MuonM_isoR05_sumPt", &MuonM_isoR05_sumPt, "MuonM_isoR05_sumPt/F");
	miniTree->Branch("MuonP_isoR05_sumPt", &MuonP_isoR05_sumPt, "MuonP_isoR05_sumPt/F");
	miniTree->Branch("MuonF_isoR05_sumPt", &MuonF_isoR05_sumPt, "MuonF_isoR05_sumPt/F");
	miniTree->Branch("MuonN_isoR05_sumPt", &MuonN_isoR05_sumPt, "MuonN_isoR05_sumPt/F");
	miniTree->Branch("MuonH_isoR05_sumPt", &MuonH_isoR05_sumPt, "MuonH_isoR05_sumPt/F");
	miniTree->Branch("MuonL_isoR05_sumPt", &MuonL_isoR05_sumPt, "MuonL_isoR05_sumPt/F");

	// ____________________________________________
	// Photon variables
	// ___________________________________________

	miniTree->Branch("NbPhotons", &NbPhotons, "NbPhotons/I");

	miniTree->Branch("Photon_Eta", &Photon_Eta, "Photon_Eta/F");
	miniTree->Branch("Photon_Phi", &Photon_Phi, "Photon_Phi/F");

	miniTree->Branch("Photon_isEBorEE", &Photon_isEBorEE, "Photon_isEBorEE/I");
	miniTree->Branch("Photon_isEB", &Photon_isEB, "Photon_isEB/I");
	miniTree->Branch("Photon_isEE", &Photon_isEE, "Photon_isEE/I");
	miniTree->Branch("Photon_isEEP", &Photon_isEEP, "Photon_isEEP/I");
	miniTree->Branch("Photon_isEEM", &Photon_isEEM, "Photon_isEEM/I");

	miniTree->Branch("Photon_Multiplicity", &Photon_Multiplicity, "Photon_Multiplicity/I");
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
	miniTree->Branch("Photon_covIetaIeta", &Photon_covIetaIeta, "Photon_covIetaIeta/F");
	miniTree->Branch("Photon_covIphiIphi", &Photon_covIphiIphi, "Photon_covIphiIphi/F");
	miniTree->Branch("Photon_convNTracks", &Photon_convNTracks, "Photon_convNTracks/I");
	miniTree->Branch("Photon_etaWidth", &Photon_etaWidth, "Photon_etaWidth/F");
	miniTree->Branch("Photon_phiWidth", &Photon_phiWidth, "Photon_phiWidth/F");

	miniTree->Branch("Photon_isoEcalRecHit", &Photon_isoEcalRecHit, "Photon_isoEcalRecHit/F");
	miniTree->Branch("Photon_isoHcalRecHit", &Photon_isoHcalRecHit, "Photon_isoHcalRecHit/F");
	miniTree->Branch("Photon_isoSolidTrkCone", &Photon_isoSolidTrkCone, "Photon_isoSolidTrkCone/F");
	miniTree->Branch("Photon_isoHollowTrkCone", &Photon_isoHollowTrkCone, "Photon_isoHollowTrkCone/F");
	miniTree->Branch("Photon_isoNTracksSolidCone", &Photon_isoNTracksSolidCone, "Photon_isoNTracksSolidCone/I");
	miniTree->Branch("Photon_isoNTracksHollowCone", &Photon_isoNTracksHollowCone, "Photon_isoNTracksHollowCone/I");
	miniTree->Branch("Photon_isoPersoSolidTrkCone", &Photon_isoPersoSolidTrkCone, "Photon_isoPersoSolidTrkCone/F");
	miniTree->Branch("Photon_isolationPersoTracksSolidCone", &Photon_isolationPersoTracksSolidCone, "Photon_isolationPersoTracksSolidCone/F");
	miniTree->Branch("Photon_isolationPersoNTracksSolidCone", &Photon_isolationPersoNTracksSolidCone, "Photon_isolationPersoNTracksSolidCone/I");

	miniTree->Branch("Photon_seedTime", &Photon_seedTime, "Photon_seedTime/F");
	miniTree->Branch("Photon_seedFlag", &Photon_seedFlag, "Photon_seedFlag/F");

	// ____________________________________________
	// mugamma / mumu / mumugamma information
	// ____________________________________________

	miniTree->Branch("Mmumu", &Mmumu, "Mmumu/F");
	miniTree->Branch("Mmumugamma", &Mmumugamma, "Mmumugamma/F");

	miniTree->Branch("deltaRNear", &deltaRNear, "deltaRNear/F");
	miniTree->Branch("deltaRFar", &deltaRFar, "deltaRFar/F");
	miniTree->Branch("deltaRPlus", &deltaRPlus, "deltaRPlus/F");
	miniTree->Branch("deltaRMinus", &deltaRMinus, "deltaRMinus/F");
	miniTree->Branch("deltaRHigh", &deltaRHigh, "deltaRHigh/F");
	miniTree->Branch("deltaRLow", &deltaRLow, "deltaRLow/F");
	
	
	//unsigned int NbEvents = (int)inputEventTree->GetEntries();
	unsigned int NbEvents = 5;
		cout<<"Nb of events : "<<NbEvents<<endl;
	


	for(unsigned int ievt=0; ievt<NbEvents; ievt++)
	{
//		int nprint = (int)((double)NbEvents/(double)100.0);
//		if( (ievt % nprint)==0 ){ cout<< ievt <<" events done over "<<NbEvents<<" ( "<<ceil((double)ievt/(double)NbEvents*100)<<" \% )"<<endl; }
		iEvent = ievt;

		// ____________________________________________
		// Event information
		// ____________________________________________
		iEventID = 0;
		isSignalApplied = isStewApplied = isZJetsApplied = 0;
		isBeforeAllCuts = isAfterCutCSA07ID = isAfterCutZJETVETO = 0;
		isAfterCut1a = isAfterCut1b = isAfterCut1c = isAfterCut1d = isAfterCut1e = 0;
		isAfterCut2a = isAfterCut2b = isAfterCut2c = 0;
		isAfterCut3 = isAfterCut4 = isAfterCut5 = isAfterCut6 = isAfterCut7 = isAfterCut8 = isAfterCut9 = isAfterCut10 = 0;
		isSelected = 0;

		// ____________________________________________
		// Muon variables
		// ____________________________________________
		NbMuons = -999;
		MuonM_Pt = MuonP_Pt = MuonN_Pt = MuonF_Pt = MuonH_Pt = MuonL_Pt = -999;
		MuonM_Eta = MuonP_Eta = MuonN_Eta = MuonF_Eta = MuonH_Eta = MuonL_Eta = -999;
		MuonM_Phi = MuonP_Phi = MuonN_Phi = MuonF_Phi = MuonH_Phi = MuonL_Phi = -999;
		MuonF_Charge = MuonN_Charge = MuonH_Charge = MuonL_Charge = -999;
		MuonM_isoR03_emEt = MuonP_isoR03_emEt = MuonN_isoR03_emEt = MuonF_isoR03_emEt = MuonH_isoR03_emEt = MuonL_isoR03_emEt = -999;
		MuonM_isoR03_hadEt = MuonP_isoR03_hadEt = MuonN_isoR03_hadEt = MuonF_isoR03_hadEt = MuonH_isoR03_hadEt = MuonL_isoR03_hadEt = -999;
		MuonM_isoR03_hoEt = MuonP_isoR03_hoEt = MuonN_isoR03_hoEt = MuonF_isoR03_hoEt = MuonH_isoR03_hoEt = MuonL_isoR03_hoEt = -999;
		MuonM_isoR03_nJets = MuonP_isoR03_nJets = MuonN_isoR03_nJets = MuonF_isoR03_nJets = MuonH_isoR03_nJets = MuonL_isoR03_nJets = -999;
		MuonM_isoR03_nTracks = MuonP_isoR03_nTracks = MuonN_isoR03_nTracks = MuonF_isoR03_nTracks = MuonH_isoR03_nTracks = MuonL_isoR03_nTracks = -999;
		MuonM_isoR03_sumPt = MuonP_isoR03_sumPt = MuonN_isoR03_sumPt = MuonF_isoR03_sumPt = MuonH_isoR03_sumPt = MuonL_isoR03_sumPt = -999;
		MuonM_isoR05_emEt = MuonP_isoR05_emEt = MuonN_isoR05_emEt = MuonF_isoR05_emEt = MuonH_isoR05_emEt = MuonL_isoR05_emEt = -999;
		MuonM_isoR05_hadEt = MuonP_isoR05_hadEt = MuonN_isoR05_hadEt = MuonF_isoR05_hadEt = MuonH_isoR05_hadEt = MuonL_isoR05_hadEt = -999;
		MuonM_isoR05_hoEt = MuonP_isoR05_hoEt = MuonN_isoR05_hoEt = MuonF_isoR05_hoEt = MuonH_isoR05_hoEt = MuonL_isoR05_hoEt = -999;
		MuonM_isoR05_nJets = MuonP_isoR05_nJets = MuonN_isoR05_nJets = MuonF_isoR05_nJets = MuonH_isoR05_nJets = MuonL_isoR05_nJets = -999;
		MuonM_isoR05_nTracks = MuonP_isoR05_nTracks = MuonN_isoR05_nTracks = MuonF_isoR05_nTracks = MuonH_isoR05_nTracks = MuonL_isoR05_nTracks = -999;
		MuonM_isoR05_sumPt = MuonP_isoR05_sumPt = MuonN_isoR05_sumPt = MuonF_isoR05_sumPt = MuonH_isoR05_sumPt = MuonL_isoR05_sumPt = -999;

		// ____________________________________________
		// Photon variables
		// ___________________________________________
		NbPhotons = -999;
		Photon_Eta = Photon_Phi = -999;
		Photon_isEBorEE = Photon_isEB = Photon_isEE = Photon_isEEP = Photon_isEEM = -999;
		Photon_Multiplicity = Photon_hasPixelSeed = Photon_isAlsoElectron = Photon_Nclusters = Photon_nBasicClusters = Photon_nXtals = -999;
		Photon_isTightPhoton = Photon_isLoosePhoton = -999;
		Photon_convNTracks = Photon_isoNTracksSolidCone = Photon_isoNTracksHollowCone = Photon_isolationPersoNTracksSolidCone = -999;
		Photon_E = Photon_Et = Photon_E2x2 = Photon_E3x3 = Photon_E5x5 = Photon_Emax = Photon_E2nd = -999;
		Photon_r19 = Photon_r9 = Photon_cross = -999;
		Photon_caloConeSize = Photon_PreshEnergy = Photon_HoE = Photon_covIetaIeta = Photon_covIphiIphi = Photon_etaWidth = Photon_phiWidth = -999;
		Photon_isoEcalRecHit = Photon_isoHcalRecHit = Photon_isoSolidTrkCone = Photon_isoHollowTrkCone = Photon_isoPersoSolidTrkCone = Photon_isolationPersoTracksSolidCone = -999;
		Photon_seedTime = Photon_seedFlag = -999;

		// ____________________________________________
		// mugamma / mumu / mumugamma information
		// ____________________________________________
		Mmumu = Mmumugamma = -999;
		deltaRNear = deltaRFar = deltaRPlus = deltaRMinus = deltaRHigh = deltaRLow = -999;
		// ____________________________________________
		// END OF INITIALIZATION
		// ____________________________________________
		
		inputEventTree->GetEvent(ievt);
		iEventID = event->eventId();
		isBeforeAllCuts = 1;
	
		// FIXME
		bool stew = false; bool zjet_veto = false;
	
		// CSA07 ID
		if(stew){
			if( (event->csa07id() != 62) && (event->csa07id() != 63) ){
				cerr<<"CSA07ID is not 62/63 ( "<< event->csa07id() << ") aborting event " << ievt << endl;
				isAfterCutCSA07ID = 0;
				continue;
			} else {
				isAfterCutCSA07ID = 1;
			}
		}
		
		// ZJET VETO
		if( zjet_veto ){
			bool MCphotons_from_muons = false;
			for( int iMCparticle = 0 ; iMCparticle < mcParticles->GetEntries() ; iMCparticle++ ){
				TRootMCParticle *mcParticleCandidate = (TRootMCParticle *)mcParticles->At(iMCparticle);
				if( (mcParticleCandidate->status()==1) && (mcParticleCandidate->type() == 22) ){ // if the particle is a true MC photon
					if( abs(mcParticleCandidate->motherType()) == 13 ){// if the true MC photon origins from a muon
						MCphotons_from_muons = true;
					}
				}
			}// end of loop over MC particles
			if( MCphotons_from_muons ){
				cerr<<"SAFE: photon(s) coming from muon, aborting event " << ievt << endl;
				isAfterCutZJETVETO = 0;
				continue;
			} else {
				isAfterCutZJETVETO = 1;
			}
		}// end of if Z+Jets veto

		NbMuons = muons->GetEntries();
		NbPhotons = photons->GetEntries();

		// CUT 1a: nb of muons > 1
		if(!( NbMuons>1 )){
			cerr << "\tCUT: event " << ievt << " CUT at level I because "<< NbMuons	<< " muons only" << endl;
			continue;
		}

		// CUT 1b: (nb of muons with |eta| < 2.5) > 1
		vector<int> muonsValidEta;
			muonsValidEta.clear();
			TRootMuon *muonValidEtaCandidate = new TRootMuon();
			for(int imuon=0 ; imuon<NbMuons ; imuon++){
				TRootMuon *muonValidEtaCandidate = (TRootMuon*) muons->At(imuon);
				if( fabs(muonValidEtaCandidate->Eta())<2.5 ){
					muonsValidEta.push_back(imuon);
				}
			}
			muonValidEtaCandidate->Clear();
			unsigned int NbMuonsValidEta = muonsValidEta.size();
		if(!( NbMuonsValidEta>1 )) {
			cerr << "\tCUT: event " << ievt << " CUT at level I because of bad muons (eta)" << endl;
			continue;
		}

		// CUT 1c: two muons with correct eta AND with opposite charge
		TRootMuon *MPtMuon = (TRootMuon*) muons->At(muonsValidEta[0]);
		double PtMuon = MPtMuon->Pt();
		int imuonValidEtaMPt = 0;
		TRootMuon *MPtMuonCandidate;
		MPtMuonCandidate = new TRootMuon();
		for(int imuon=1 ; imuon<NbMuonsValidEta ; imuon++){
			MPtMuonCandidate = new TRootMuon();
			MPtMuonCandidate = (TRootMuon*) muons->At(muonsValidEta[imuon]);
			if(MPtMuonCandidate->Pt() > PtMuon){
				MPtMuon = MPtMuonCandidate;
				PtMuon = MPtMuon->Pt();
				imuonValidEtaMPt = imuon;
			}
		}
		MPtMuonCandidate->Clear();
		TRootMuon *MPtMuon_oppositeCharge = new TRootMuon();
		double PtMuon_oppositeCharge = 0.0;
		bool isThereOppositeCharge = false;
		for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
			TRootMuon *MPtMuon_oppositeChargeCandidate = new TRootMuon();
			TRootMuon *MPtMuon_oppositeChargeCandidate = (TRootMuon*) muons->At(muonsValidEta[imuon]);
			if( imuon != imuonValidEtaMPt ){
				if( (MPtMuon_oppositeChargeCandidate->charge())*(MPtMuon->charge()) < 0.0 ){
					if(MPtMuon_oppositeChargeCandidate->Pt() > PtMuon_oppositeCharge){
						MPtMuon_oppositeCharge = MPtMuon_oppositeChargeCandidate;
						PtMuon_oppositeCharge = MPtMuon_oppositeCharge->Pt();
						isThereOppositeCharge = true;
					}
				}
			}
		}
		if(!( isThereOppositeCharge )){
			cerr << "\tCUT: event " << ievt << " CUT at level I because of bad muons (charge)" << endl;
			continue;
		}

		// CUT 1d: two muons with correct eta with opposite charge AND pT>10 GeV
		if(!( (PtMuon>10.0) && (PtMuon_oppositeCharge>10.0) )){
			cerr << "\tCUT: event " << ievt << " CUT at level I because of bad muons (pt)" << endl;
			continue;
		}

		// CUT 1e: dimuon invariant mass >= 20 GeV
		TRootParticle *mumu = new TRootParticle();
		*mumu = (*MPtMuon) + (*MPtMuon_oppositeCharge);
		double mumuInvMass = mumu->M();
		cerr << "\t\tINFO: Dimuon invariant mass : Mmumu = " << mumuInvMass << endl;
		mumu->Clear();
		if(!( mumuInvMass >= 20.0 )){
			cerr << "\tCUT: event " << ievt << " CUT at level I because of m(mumu)" << endl;
			continue;
		}

		// CUT 2a: nb of photons > 0
		if(!( NbPhotons>0 )){
			cerr << "\tCUT: event " << ievt << " CUT at level II because "<<  NbPhotons  << " gamma" << endl;
			continue;
		}

		// CUT 2b: one photon with |eta| < 2.5 and pT>10GeV
		unsigned int NbPhotonsValidEta = 0;
		vector<int> photonsValidEta;
		photonsValidEta.clear();
		TRootPhoton *photonValidEtaCandidate = new TRootPhoton();
		for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
			TRootPhoton *photonValidEtaCandidate = (TRootPhoton*) photons->At(iphoton);
			if( (photonValidEtaCandidate->Pt()>10.0) && (fabs(photonValidEtaCandidate->Eta())<2.5) ){
				photonsValidEta.push_back(iphoton);
			}
		}
		photonValidEtaCandidate->Clear();
		NbPhotonsValidEta = photonsValidEta.size();
		if(!( NbPhotonsValidEta>0 )){
			cerr << "\tCUT: event " << ievt << " CUT at level II because of bad gamma" << endl;
			continue;
		}

		// GET most energetic photon
		TRootPhoton *MPtPhoton = new TRootPhoton();
		TRootPhoton *MPtPhoton = (TRootPhoton*) photons->At(photonsValidEta[0]);
		double PtPhoton = MPtPhoton->Pt();
		for(int iphoton=0 ; iphoton<NbPhotonsValidEta ; iphoton++){
			TRootPhoton *MPtPhotonCandidate = new TRootPhoton();
			TRootPhoton *MPtPhotonCandidate = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
			if(MPtPhotonCandidate->Pt() > PtPhoton){
				MPtPhoton = MPtPhotonCandidate;
				PtPhoton = MPtPhoton->Pt();
			}
			MPtPhotonCandidate->Clear();
		}

		// ********************************************************************
		// *** Compute mumugamma invariant mass ***
		// ********************************************************************
		TRootParticle *mumugamma = new TRootParticle();
		*mumugamma = (*MPtMuon) + (*MPtMuon_oppositeCharge) + (*MPtPhoton);
		double mumugammaInvMass = mumugamma->M();
		mumugamma->Clear();

		double phiPhoton = MPtPhoton->Phi();
		double etaPhoton = MPtPhoton->Eta();
		double phiMuon = MPtMuon->Phi();
		double etaMuon = MPtMuon->Eta();
		double phiMuon_oppositeCharge = MPtMuon_oppositeCharge->Phi();
		double etaMuon_oppositeCharge = MPtMuon_oppositeCharge->Eta();
		double dphiPM = fabs(phiPhoton - phiMuon);
		while (dphiPM > TMath::Pi()) dphiPM -= 2*TMath::Pi();
		while (dphiPM <= -TMath::Pi()) dphiPM += 2*TMath::Pi();
		double dphiPAM = fabs(phiPhoton - phiMuon_oppositeCharge);
		while (dphiPAM > TMath::Pi()) dphiPAM -= 2*TMath::Pi();
		while (dphiPAM <= -TMath::Pi()) dphiPAM += 2*TMath::Pi();
		double detaPM = fabs(etaPhoton - etaMuon);
		double detaPAM = fabs(etaPhoton - etaMuon_oppositeCharge);
		double deltaRPM = sqrt(detaPM*detaPM + dphiPM*dphiPM);
		double deltaRPAM = sqrt(detaPAM*detaPAM + dphiPAM*dphiPAM);

		double deltaRmin;
		TRootMuon *farMuon;
		TRootMuon *nearMuon;
		if(deltaRPM < deltaRPAM){
			deltaRmin = deltaRPM;
			farMuon = (TRootMuon*) MPtMuon_oppositeCharge;
			nearMuon = (TRootMuon*) MPtMuon;
		} else {
			deltaRmin = deltaRPAM;
			farMuon = (TRootMuon*) MPtMuon;
			nearMuon = (TRootMuon*) MPtMuon_oppositeCharge;
		}

		// CUT 2c: DeltaR(photon, close muon) >= 0.05
		if(!( deltaRmin>=0.05 )){
			cerr << "\tCUT: event " << ievt  << " CUT at level II for Photons (deltar)" << endl;
			continue;
		}

		// CUT 3: 40GeV <= dimuon invariant mass <= 80GeV
		if(!( (mumuInvMass>=40.0)&&(mumuInvMass<=80.0) )){
			cerr << "\tCUT: event " << ievt  << " CUT at level III for Drell-Yan " << endl;
			continue;
		}

		// CUT 4: photon_Et >= 12GeV && DeltaR(photon, close muon)<=0.8
		if(!( (MPtPhoton->Et()>=12.0)&&(deltaRmin<=0.8) )){
			cerr << "\tCUT: event " << ievt  << " CUT at level IV for gamma momentum" << endl;
			continue;
		}

		// CUT 5: 87.2GeV <= mumugamma invariant mass <= 95.2GeV *** *** *** 70GeV <= mumugamma invariant mass <= 110GeV
		// FIXME
		bool signal = false;
		bool cutMuMuGammaWindow = false;
		if(signal){
			cutMuMuGammaWindow = (mumugammaInvMass >=87.2) && (mumugammaInvMass <=95.2);} // in case of signal
		else {
			cutMuMuGammaWindow = (mumugammaInvMass >=70.0) && (mumugammaInvMass <=110.0);} // in case of background
		if(!( cutMuMuGammaWindow )){
			cerr << "\tCUT: event " << ievt  << " CUT at level V for Z Mass Window " << endl;
			continue;
		}
	
		// CUT 6: farMuon->isoR03_emEt() <= 1.0
		if(!( farMuon->isoR03_emEt()<=1.0 )) {
			cerr << "\tCUT: event " << ievt  << " CUT at level VI for large emEt " << endl;
			continue;
		}

		// CUT 7: farMuon->Pt() >= 30.0
		if(!( farMuon->Pt()>=30.0 )) {
			cerr << "\tCUT: event " << ievt  << " CUT at level VII for soft far muon " << endl;
			continue;
		}

		// CUT 8: nearMuon->isoR03_hadEt() < 1.0
		if(!( nearMuon->isoR03_hadEt()<1.0 )){
			cerr << "\tCUT: event " << ievt  << " CUT at level VIII for large hadEt " << endl;
			continue;
		}


		farMuon->Clear();
		nearMuon->Clear();



































/*		Photon_iEvent = ievt;
		inputEventTree->GetEvent(ievt);
		if( (ievt%10==0 && ievt<=100)  || (ievt%100==0 && ievt<=1000)   || (ievt%1000==0 && ievt>1000)  )
		{
			cout <<"Analyzing "<< ievt << "th event: " << endl;
		}
		//_________________________________________
		//__________ TO BE CHECKED
		NbEventsSelectedRuns++;
		NbEventsSelectedL1++;
		NbEventsSelectedVertex++;

		// Count nb of evts with at least one SC with rawEt>2 GeV (for Eiko)
		Bool_t atLeastOneSChigherThan2GeV = false;
		TRootSuperCluster* mysc;
		for (int isc=0; isc< superClusters->GetEntriesFast(); isc++)
		{
			mysc = (TRootSuperCluster*) superClusters->At(isc);
			if ( ! ( mysc->type()==211 || mysc->type()==322 ) ) continue;
			Float_t rawEt = mysc->rawEnergy() * sin(mysc->Theta());
			if (rawEt>2.0) atLeastOneSChigherThan2GeV = true;
		}
		if (atLeastOneSChigherThan2GeV) nEventsWithScHigherThan2GeV++;

		//___ TO BE CHECKED
		// ________________________________________
		if(doPhoton)
		{
			TRootPhoton* myphoton;
			int nPhotons = 0; Photon_Multiplicity = 0;
			int nPhotons_EB = 0; Photon_isEB = 0;
			int nPhotons_EE = 0; Photon_isEE = 0;
			int nPhotons_EEM = 0; Photon_isEEM = 0;
			int nPhotons_EEP = 0; Photon_isEEP = 0;
			
			for (int iphoton=0; iphoton< photons->GetEntriesFast(); iphoton++)
			{
					Photon_isAfterCut1 = 0;
					Photon_isAfterCut2 = 0;
					Photon_isAfterCut3 = 0;
					Photon_isAfterCut4 = 0;
					Photon_isAfterCut5 = 0;
					Photon_isAfterCut6 = 0;
					Photon_isEB = 0;
					Photon_isEE = 0;
					Photon_isEEM = 0;
					Photon_isEEP = 0;
				nTotPhotons++;
					Photon_isEBorEE = 1;
					Photon_isAfterCut0 = 1;
				myphoton = (TRootPhoton*) photons->At(iphoton);

				if (myphoton->isEBPho()){ Photon_isEB = 1; Photon_isEE = 0; }
				if (myphoton->isEEPho()){ Photon_isEE = 1; Photon_isEB = 0; }
				if (myphoton->isEEPho() && myphoton->Eta()<0){ Photon_isEEM = 1; }
				if (myphoton->isEEPho() && myphoton->Eta()>0){ Photon_isEEP = 1; }
*/
				/*
				cout << "myphoton->clusterAlgo=" << myphoton->clusterAlgo() << " myphoton->isEBPho=" << myphoton->isEBPho() << " myphoton->isEEPho=" << myphoton->isEEPho() << endl;
				cout << "myphoton->superCluster()=" << myphoton->superCluster() << endl;
				cout << "myphoton->superClusterOfType(210)=" << myphoton->superClusterOfType(210) << endl;
				cout << "myphoton->superClusterOfType(211)=" << myphoton->superClusterOfType(211) << endl;
				cout << "myphoton->superClusterOfType(320)=" << myphoton->superClusterOfType(320) << endl;
				cout << "myphoton->superClusterOfType(322)=" << myphoton->superClusterOfType(322) << endl;
				cout << "myphoton->superClusterOfType(323)=" << myphoton->superClusterOfType(323) << endl;
				*/
				//if (myphoton->superClusterOfType(211) == 0 && myphoton->superClusterOfType(323) == 0 ) continue;
	/*				Photon_Multiplicity = photons->GetEntriesFast();
					Photon_E = myphoton->Energy();
					Photon_Et = myphoton->Et();
					Photon_Eta = myphoton->Eta();
					Photon_Phi = myphoton->Phi();
					Photon_E2x2 = myphoton->e2x2();
					Photon_E3x3 = myphoton->e3x3();
					Photon_E5x5 = myphoton->e5x5();
					Photon_Emax = myphoton->eMax();
					Photon_E2nd = myphoton->e2nd();
					Photon_r19 = myphoton->r19();
					Photon_r9 = myphoton->r9();
					Photon_caloConeSize = myphoton->caloConeSize();
					Photon_PreshEnergy = myphoton->preshowerEnergy();
					Photon_HoE = myphoton->hoe();
					Photon_Nclusters = myphoton->nbClusters();
					Photon_covIetaIeta = myphoton->covIetaIeta();
					Photon_covIphiIphi = myphoton->covIphiIphi();
					Photon_isoEcalRecHit = myphoton->isolationEcalRecHit();
					Photon_isoHcalRecHit = myphoton->isolationHcalRecHit();
					Photon_isoSolidTrkCone = myphoton->isolationSolidTrkCone();
					Photon_isoHollowTrkCone = myphoton->isolationHollowTrkCone();
					Photon_isoNTracksSolidCone = myphoton->isolationNTracksSolidCone();
					Photon_isoNTracksHollowCone = myphoton->isolationNTracksHollowCone();
					Photon_isoPersoSolidTrkCone = myphoton->isolationPersoTracksSolidCone();
					Photon_convNTracks = myphoton->convNTracks();
								if ( myphoton->superCluster() != 0 )
				{
						Photon_SCEta = myphoton->superCluster()->Eta();
						Photon_SCPhi = myphoton->superCluster()->Phi();
						Photon_SCEnergy = myphoton->superCluster()->Mag();
						Photon_SCEt = myphoton->superCluster()->Pt();
						Photon_SCRawEt = myphoton->superCluster()->rawEnergy() * sin(myphoton->superCluster()->Theta());
						Photon_etaWidth = myphoton->superCluster()->etaWidth();
						Photon_phiWidth = myphoton->superCluster()->phiWidth();
						Photon_nBasicClusters = myphoton->superCluster()->nBasicClusters();
						Photon_seedTime = myphoton->superCluster()->hitAt(myphoton->superCluster()->nRecHits()-1)->time();
						Photon_seedFlag = myphoton->superCluster()->hitAt(myphoton->superCluster()->nRecHits()-1)->recoFlag();
						Photon_cross = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
						Photon_isTightPhoton = myphoton->isTightPhoton();
						Photon_isLoosePhoton = myphoton->isLoosePhoton();
						Photon_isolationPersoTracksSolidCone = myphoton->isolationPersoTracksSolidCone();
						Photon_isolationPersoNTracksSolidCone = myphoton->isolationPersoNTracksSolidCone();
						Photon_SCRawEnergy = myphoton->superCluster()->rawEnergy();
				} // end of loop over photons having a supercluster
					if (myphoton->superCluster() == 0 ) {miniTree->Fill(); continue;}

				Float_t scRawEt = myphoton->superCluster()->rawEnergy() * sin(myphoton->superCluster()->Theta());

				nCut1++;
					Photon_isAfterCut1 = 1;

				if ( myphoton->isEBPho() &&(1 - ((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax())))>0.95 ) {miniTree->Fill(); continue;}
				//if ( myphoton->superCluster()->hitsDetector().size()<3 && fabs(myphoton->r19()-1)<0.05 ) continue;
				nCut2++;
					Photon_isAfterCut2 = 1;
				
					Photon_hasPixelSeed = myphoton->hasPixelSeed();
					Photon_isAlsoElectron = myphoton->isAlsoElectron();
				
				//if (myphoton->hasPixelSeed()) continue;
				nCut3++;
					Photon_isAfterCut3 = 1;
				//if (myphoton->isAlsoElectron()) continue;
				nCut4++;
					Photon_isAfterCut4 = 1;
				if ( scRawEt<2.0 ) {miniTree->Fill(); continue;}
				nCut5++;
					Photon_isAfterCut5 = 1;
				//if ( fabs(myphoton->Eta())>2.5 ) continue;
				Float_t abs_eta = fabs(myphoton->superCluster()->Eta());
				if ( (abs_eta>2.5) || ( abs_eta>1.4442 && abs_eta<1.566 ) ) {miniTree->Fill();  continue;}
				nCut6++;
					Photon_isAfterCut6 = 1;
				
				nPhotons++;
				nSelectedPhotons++;
		
				miniTree->Fill();	
			} // end of loop over photons
			
			
		} // end of do photons
		
		nSelectedEvents++;
*/		
	} // fin boucle sur evts

	
/*	if(NbEvents>0) cout << "NbEvents=" << NbEvents << "  NbEventsSelectedRuns=" << NbEventsSelectedRuns << "  NbEventsSelectedL1=" << NbEventsSelectedL1
		<< "  NbEventsSelectedVertex=" << NbEventsSelectedVertex  << "  nSelectedEvents=" << nSelectedEvents   << "  nEventsWithScHigherThan2GeV=" << nEventsWithScHigherThan2GeV
	<< "  nSelectedEvents/NbEventsSelectedRuns=" <<100.*nSelectedEvents/NbEventsSelectedRuns << "%" << "  nSelectedEvents/NbEvents=" <<100.*nSelectedEvents/NbEvents << "%" << endl;
	if(nTotPhotons>0) cout << "nSelectedPhotons=" << nSelectedPhotons << "  nTotPhotons=" << nTotPhotons << "  Eff=" <<100.*nSelectedPhotons/nTotPhotons << "%" << endl;
	cout << "nCut1=" << nCut1 << "  nCut2=" << nCut2 << "  nCut3=" << nCut3 << "  nCut4=" << nCut4 << "  nCut5=" << nCut5 << "  nCut6=" << nCut6 << endl;
	*/
	OutputRootFile->cd();
	OutputRootFile->Write();
	OutputRootFile->Close();

/*
// FIXME
	cout << nSelected << " selected events out of " << NbEvents << endl;
  cout<<"Writing surviving events in OUTPUT.root"<<endl;
  outputEventTree->AutoSave();
  outputFile.Write();
  outputFile.Close();
  delete outputFile;
  delete inputEventTree;

*/



	return 0;
}
