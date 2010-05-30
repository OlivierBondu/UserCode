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


double DeltaR( double eta1, double phi1, double eta2, double phi2){
	double DeltaEta = fabs( eta1-eta2 );
	double DeltaPhi = fabs( phi1-phi2 );
	// Returning DeltaPhi in the correct range (0, 2pi)
	while (DeltaPhi >   TMath::Pi()) DeltaPhi -= 2*TMath::Pi();
	while (DeltaPhi <= -TMath::Pi()) DeltaPhi += 2*TMath::Pi();
	return sqrt(DeltaEta*DeltaEta + DeltaPhi*DeltaPhi);
}


//int Selection_miniTree(){
int main(){
	gSystem->Load("/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/src/libToto.so");
	
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

	// ____________________________________________
	// Event information
	// ____________________________________________
	Int_t iEvent, iEventID, iRunID;
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
	Int_t Photon_convNTracks, Photon_isoNTracksSolidCone, Photon_isoNTracksHollowCone;
	Float_t Photon_E, Photon_Et, Photon_E2x2, Photon_E3x3, Photon_E5x5, Photon_Emax, Photon_E2nd;
	Float_t Photon_r19, Photon_r9, Photon_cross;
	Float_t Photon_caloConeSize, Photon_PreshEnergy, Photon_HoE, Photon_covIetaIeta, Photon_covIphiIphi, Photon_etaWidth, Photon_phiWidth;
	Float_t Photon_isoEcalRecHit, Photon_isoHcalRecHit, Photon_isoSolidTrkCone, Photon_isoHollowTrkCone;
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
	miniTree->Branch("iRunID", &iRunID, "iRunID/I");

	miniTree->Branch("isSignalApplied", &isSignalApplied, "isSignalApplied/I");
	miniTree->Branch("isStewApplied", &isStewApplied, "isStewApplied/I");
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
	
	
	unsigned int NbEvents = (int)inputEventTree->GetEntries();
	//unsigned int NbEvents = 5;
	bool signal = false;
	bool stew = false;
	bool zjet_veto = false;
	cout << "Nb of events : " << NbEvents << endl;
	cout << "Signal is: " << signal <<endl;
	cout << "Stew is: " << stew << endl;
	cout << "ZJet veto is: " << zjet_veto << endl;


	for(unsigned int ievt=0; ievt<NbEvents; ievt++)
	{
		int nprint = (int)((double)NbEvents/(double)100.0);
		if( (ievt % nprint)==0 ){ cout<< ievt <<" events done over "<<NbEvents<<" ( "<<ceil((double)ievt/(double)NbEvents*100)<<" \% )"<<endl; }
		iEvent = ievt;
		inputEventTree->GetEvent(ievt);

		// ____________________________________________
		// Event information
		// ____________________________________________
		iEventID = event->eventId();
		iRunID = event->runId();
		isSignalApplied = signal;
		isStewApplied = stew;
		isZJetsApplied = zjet_veto;
		isBeforeAllCuts = 1;
		isAfterCutCSA07ID = isAfterCutZJETVETO = 0;
		isAfterCut1a = isAfterCut1b = isAfterCut1c = isAfterCut1d = isAfterCut1e = 0;
		isAfterCut2a = isAfterCut2b = isAfterCut2c = 0;
		isAfterCut3 = isAfterCut4 = isAfterCut5 = isAfterCut6 = isAfterCut7 = isAfterCut8 = isAfterCut9 = isAfterCut10 = 0;
		isSelected = 0;

		// ____________________________________________
		// Muon variables
		// ____________________________________________
		NbMuons = muons->GetEntries();
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
		NbPhotons = photons->GetEntries();
		Photon_Eta = Photon_Phi = -999;
		Photon_isEBorEE = 1;
		Photon_isEB = Photon_isEE = Photon_isEEP = Photon_isEEM = -999;
		Photon_Multiplicity = Photon_hasPixelSeed = Photon_isAlsoElectron = Photon_Nclusters = Photon_nBasicClusters = Photon_nXtals = -999;
		Photon_isTightPhoton = Photon_isLoosePhoton = -999;
		Photon_convNTracks = Photon_isoNTracksSolidCone = Photon_isoNTracksHollowCone = -999;
		Photon_E = Photon_Et = Photon_E2x2 = Photon_E3x3 = Photon_E5x5 = Photon_Emax = Photon_E2nd = -999;
		Photon_r19 = Photon_r9 = Photon_cross = -999;
		Photon_caloConeSize = Photon_PreshEnergy = Photon_HoE = Photon_covIetaIeta = Photon_covIphiIphi = Photon_etaWidth = Photon_phiWidth = -999;
		Photon_isoEcalRecHit = Photon_isoHcalRecHit = Photon_isoSolidTrkCone = Photon_isoHollowTrkCone = -999;
		Photon_seedTime = Photon_seedFlag = -999;

		// ____________________________________________
		// mugamma / mumu / mumugamma information
		// ____________________________________________
		Mmumu = Mmumugamma = -999;
		deltaRNear = deltaRFar = deltaRPlus = deltaRMinus = deltaRHigh = deltaRLow = -999;
		// ____________________________________________
		// END OF INITIALIZATION
		// ____________________________________________
		
	
		// CSA07 ID
		if( stew ){
			if( (event->csa07id() != 62) && (event->csa07id() != 63) ){
				cerr<<"CSA07ID is not 62/63 ( "<< event->csa07id() << ") aborting event " << ievt << endl;
				miniTree->Fill();
				continue;
			}
			isAfterCutCSA07ID = 1;
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
				mcParticleCandidate->~TRootMCParticle();
			}// end of loop over MC particles
			if( MCphotons_from_muons ){
				cerr<<"SAFE: photon(s) coming from muon, aborting event " << ievt << endl;
				miniTree->Fill();
				continue;
			}
			isAfterCutZJETVETO = 1;
		}// end of if Z+Jets veto

		// CUT 1a: nb of muons > 1
		if(!( NbMuons>1 )){
			cerr << "\tCUT: event " << ievt << " CUT at level I because "<< NbMuons	<< " muons only" << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut1a = 1;

		// CUT 1b: (nb of muons with |eta| < 2.5) > 1
		vector<int> muonsValidEta;
		muonsValidEta.clear();
//		TRootMuon *muonValidEtaCandidate = new TRootMuon();
		TRootMuon *muonValidEtaCandidate;
		for(int imuon=0 ; imuon<NbMuons ; imuon++){
//			TRootMuon *muonValidEtaCandidate = (TRootMuon*) muons->At(imuon);
			muonValidEtaCandidate = (TRootMuon*) muons->At(imuon);
			if( fabs(muonValidEtaCandidate->Eta())<2.5 ){
				muonsValidEta.push_back(imuon);
			}
		}
		muonValidEtaCandidate->~TRootMuon();

		unsigned int NbMuonsValidEta = muonsValidEta.size();
		if(!( NbMuonsValidEta>1 )) {
			miniTree->Fill();
			cerr << "\tCUT: event " << ievt << " CUT at level I because of bad muons (eta)" << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut1b = 1;

		// CUT 1c: two muons with correct eta AND with opposite charge
		TRootMuon *MPtMuon = (TRootMuon*) muons->At(muonsValidEta[0]);
		double PtMuon = MPtMuon->Pt();
		int imuonValidEtaMPt = 0;
		TRootMuon *MPtMuonCandidate;
//		MPtMuonCandidate = new TRootMuon();
		for(int imuon=1 ; imuon<NbMuonsValidEta ; imuon++){
//			MPtMuonCandidate = new TRootMuon();
			MPtMuonCandidate = (TRootMuon*) muons->At(muonsValidEta[imuon]);
			if(MPtMuonCandidate->Pt() > PtMuon){
				MPtMuon = MPtMuonCandidate;
				PtMuon = MPtMuon->Pt();
				imuonValidEtaMPt = imuon;
			}
		}
//FIXME		MPtMuonCandidate->Clear();
//		TRootMuon *MPtMuon_oppositeCharge = new TRootMuon();
		TRootMuon *MPtMuon_oppositeCharge;
		double PtMuon_oppositeCharge = 0.0;
		bool isThereOppositeCharge = false;
		for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
//			TRootMuon *MPtMuon_oppositeChargeCandidate = new TRootMuon();
			TRootMuon *MPtMuon_oppositeChargeCandidate;
// FIXME			TRootMuon *MPtMuon_oppositeChargeCandidate = (TRootMuon*) muons->At(muonsValidEta[imuon]);
			MPtMuon_oppositeChargeCandidate = (TRootMuon*) muons->At(muonsValidEta[imuon]);
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
			miniTree->Fill();
			continue;
		}
		isAfterCut1c = 1;

		// CUT 1d: two muons with correct eta with opposite charge AND pT>10 GeV
		if(!( (PtMuon>10.0) && (PtMuon_oppositeCharge>10.0) )){
			cerr << "\tCUT: event " << ievt << " CUT at level I because of bad muons (pt)" << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut1d = 1;

		// CUT 1e: dimuon invariant mass >= 20 GeV
//		TRootParticle *mumu = new TRootParticle();
		TLorentzVector mumu;
//		TRootParticle *mumu;
		mumu = (*MPtMuon) + (*MPtMuon_oppositeCharge);
		double mumuInvMass = mumu.M();
		cerr << "\t\tINFO: Dimuon invariant mass : Mmumu = " << mumuInvMass << endl;
//FIXME		mumu->Clear();
		if(!( mumuInvMass >= 20.0 )){
			cerr << "\tCUT: event " << ievt << " CUT at level I because of m(mumu)" << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut1e = 1;

		// CUT 2a: nb of photons > 0
		if(!( NbPhotons>0 )){
			cerr << "\tCUT: event " << ievt << " CUT at level II because "<<  NbPhotons  << " gamma" << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut2a = 1;

		// CUT 2b: one photon with |eta| < 2.5 and pT>10GeV
		unsigned int NbPhotonsValidEta = 0;
		vector<int> photonsValidEta;
		photonsValidEta.clear();
//		TRootPhoton *photonValidEtaCandidate = new TRootPhoton();
		TRootPhoton *photonValidEtaCandidate;
		for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
			TRootPhoton *photonValidEtaCandidate = (TRootPhoton*) photons->At(iphoton);
			if( (photonValidEtaCandidate->Pt()>10.0) && (fabs(photonValidEtaCandidate->Eta())<2.5) ){
				photonsValidEta.push_back(iphoton);
			}
		}
//FIXME		photonValidEtaCandidate->Clear();
		NbPhotonsValidEta = photonsValidEta.size();
		if(!( NbPhotonsValidEta>0 )){
			cerr << "\tCUT: event " << ievt << " CUT at level II because of bad gamma" << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut2b = 1;

		// GET most energetic photon
//		TRootPhoton *MPtPhoton = new TRootPhoton();
		TRootPhoton *MPtPhoton;
// FIXME		TRootPhoton *MPtPhoton = (TRootPhoton*) photons->At(photonsValidEta[0]);
		MPtPhoton = (TRootPhoton*) photons->At(photonsValidEta[0]);
		double PtPhoton = MPtPhoton->Pt();
		for(int iphoton=0 ; iphoton<NbPhotonsValidEta ; iphoton++){
//			TRootPhoton *MPtPhotonCandidate = new TRootPhoton();
			TRootPhoton *MPtPhotonCandidate;
// FIXME			TRootPhoton *MPtPhotonCandidate = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
			MPtPhotonCandidate = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
			if(MPtPhotonCandidate->Pt() > PtPhoton){
				MPtPhoton = MPtPhotonCandidate;
				PtPhoton = MPtPhoton->Pt();
			}
//FIXME			MPtPhotonCandidate->Clear();
		}
		// FILL THE MINITREE
		Photon_Eta = MPtPhoton->Eta();
		Photon_Phi = MPtPhoton->Phi();
		Photon_isEB = MPtPhoton->isEBPho();
		Photon_isEE = MPtPhoton->isEEPho();
		if( MPtPhoton->isEEPho() && MPtPhoton->Eta()<0 ){ Photon_isEEM = 1; }
		if( MPtPhoton->isEEPho() && MPtPhoton->Eta()>0 ){ Photon_isEEP = 1; }
		Photon_Multiplicity = photons->GetEntriesFast();
		Photon_hasPixelSeed = MPtPhoton->hasPixelSeed();
		Photon_isAlsoElectron = MPtPhoton->isAlsoElectron();
		Photon_Nclusters = MPtPhoton->nbClusters();
		Photon_nBasicClusters = MPtPhoton->superCluster()->nBasicClusters();
		Photon_isTightPhoton = MPtPhoton->isTightPhoton();
		Photon_isLoosePhoton = MPtPhoton->isLoosePhoton();
		Photon_convNTracks = MPtPhoton->convNTracks();
		Photon_isoNTracksSolidCone = MPtPhoton->isolationNTracksSolidCone();
		Photon_isoNTracksHollowCone = MPtPhoton->isolationNTracksHollowCone();
		Photon_E = MPtPhoton->Energy();
		Photon_Et = MPtPhoton->Et();
		Photon_E2x2 = MPtPhoton->e2x2();
		Photon_E3x3 = MPtPhoton->e3x3();
		Photon_E5x5 = MPtPhoton->e5x5();
		Photon_Emax = MPtPhoton->eMax();
		Photon_E2nd = MPtPhoton->e2nd();
		Photon_r19 = MPtPhoton->r19();
		Photon_r9 = MPtPhoton->r9();
		Photon_cross = 1-((MPtPhoton->superCluster()->s4())/(MPtPhoton->superCluster()->eMax()));		
		Photon_caloConeSize = MPtPhoton->caloConeSize();
		Photon_PreshEnergy = MPtPhoton->preshowerEnergy();
		Photon_HoE = MPtPhoton->hoe();
		Photon_covIetaIeta = MPtPhoton->covIetaIeta();
		Photon_covIphiIphi = MPtPhoton->covIphiIphi();
		Photon_etaWidth = MPtPhoton->superCluster()->etaWidth();
		Photon_phiWidth = MPtPhoton->superCluster()->phiWidth();
		Photon_isoEcalRecHit = MPtPhoton->isolationEcalRecHit();
		Photon_isoHcalRecHit = MPtPhoton->isolationHcalRecHit();
		Photon_isoSolidTrkCone = MPtPhoton->isolationSolidTrkCone();
		Photon_isoHollowTrkCone = MPtPhoton->isolationHollowTrkCone();
		Photon_seedTime = MPtPhoton->superCluster()->hitAt(MPtPhoton->superCluster()->nRecHits()-1)->time();
		Photon_seedFlag = MPtPhoton->superCluster()->hitAt(MPtPhoton->superCluster()->nRecHits()-1)->recoFlag();


		// ********************************************************************
		// *** Compute mumugamma invariant mass ***
		// ********************************************************************
//		TRootParticle *mumugamma = new TRootParticle();
//		TRootParticle *mumugamma;
		TLorentzVector mumugamma;
		mumugamma = (*MPtMuon) + (*MPtMuon_oppositeCharge) + (*MPtPhoton);
		double mumugammaInvMass = mumugamma.M();
// FIXME		mumugamma->Clear();

		double phiPhoton = MPtPhoton->Phi();
		double etaPhoton = MPtPhoton->Eta();
		double phiMuon = MPtMuon->Phi();
		double etaMuon = MPtMuon->Eta();
		double phiMuon_oppositeCharge = MPtMuon_oppositeCharge->Phi();
		double etaMuon_oppositeCharge = MPtMuon_oppositeCharge->Eta();

		double deltaRPM  = DeltaR(etaPhoton, phiPhoton, etaMuon, phiMuon);
		double deltaRPAM = DeltaR(etaPhoton, phiPhoton, etaMuon_oppositeCharge, phiMuon_oppositeCharge);

		double deltaRmin;
		TRootMuon *farMuon;
		TRootMuon *nearMuon;
		TRootMuon *minusMuon;
		TRootMuon *plusMuon;
		TRootMuon *highMuon;
		TRootMuon *lowMuon;

		if(deltaRPM < deltaRPAM){
			deltaRmin = deltaRPM;
			farMuon  = (TRootMuon*) MPtMuon_oppositeCharge;
			nearMuon = (TRootMuon*) MPtMuon;
		} else {
			deltaRmin = deltaRPAM;
			farMuon  = (TRootMuon*) MPtMuon;
			nearMuon = (TRootMuon*) MPtMuon_oppositeCharge;
		}
		if( MPtMuon->charge()>0 ){
			plusMuon  = (TRootMuon*) MPtMuon;
			minusMuon = (TRootMuon*) MPtMuon_oppositeCharge;
		} else {
			minusMuon = (TRootMuon*) MPtMuon;
			plusMuon  = (TRootMuon*) MPtMuon_oppositeCharge;
		}
		highMuon = (TRootMuon*) MPtMuon;
		lowMuon  = (TRootMuon*) MPtMuon_oppositeCharge;

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
		MuonH_Pt = highMuon->Pt();
		MuonH_Eta = highMuon->Eta();
		MuonH_Phi = highMuon->Phi();
		MuonH_Charge = highMuon->charge();
		MuonH_isoR03_emEt = highMuon->isoR03_emEt();
		MuonH_isoR03_hadEt = highMuon->isoR03_hadEt();
		MuonH_isoR03_hoEt = highMuon->isoR03_hoEt();
		MuonH_isoR03_nJets = highMuon->isoR03_nJets();
		MuonH_isoR03_nTracks = highMuon->isoR03_nTracks();
		MuonH_isoR03_sumPt = highMuon->isoR03_sumPt();
		MuonH_isoR05_emEt = highMuon->isoR05_emEt();
		MuonH_isoR05_hadEt = highMuon->isoR05_hadEt();
		MuonH_isoR05_hoEt = highMuon->isoR05_hoEt();
		MuonH_isoR05_nJets = highMuon->isoR05_nJets();
		MuonH_isoR05_nTracks = highMuon->isoR05_nTracks();
		MuonH_isoR05_sumPt = highMuon->isoR05_sumPt();
		MuonL_Pt = lowMuon->Pt();
		MuonL_Eta = lowMuon->Eta();
		MuonL_Phi = lowMuon->Phi();
		MuonL_Charge = lowMuon->charge();
		MuonL_isoR03_emEt = lowMuon->isoR03_emEt();
		MuonL_isoR03_hadEt = lowMuon->isoR03_hadEt();
		MuonL_isoR03_hoEt = lowMuon->isoR03_hoEt();
		MuonL_isoR03_nJets = lowMuon->isoR03_nJets();
		MuonL_isoR03_nTracks = lowMuon->isoR03_nTracks();
		MuonL_isoR03_sumPt = lowMuon->isoR03_sumPt();
		MuonL_isoR05_emEt = lowMuon->isoR05_emEt();
		MuonL_isoR05_hadEt = lowMuon->isoR05_hadEt();
		MuonL_isoR05_hoEt = lowMuon->isoR05_hoEt();
		MuonL_isoR05_nJets = lowMuon->isoR05_nJets();
		MuonL_isoR05_nTracks = lowMuon->isoR05_nTracks();
		MuonL_isoR05_sumPt = lowMuon->isoR05_sumPt();

		// CUT 2c: DeltaR(photon, close muon) >= 0.05
		if(!( deltaRmin>=0.05 )){
			cerr << "\tCUT: event " << ievt  << " CUT at level II for Photons (deltar)" << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut2c = 1;


		// CUT 3: 40GeV <= dimuon invariant mass <= 80GeV
		if(!( (mumuInvMass>=40.0)&&(mumuInvMass<=80.0) )){
			cerr << "\tCUT: event " << ievt  << " CUT at level III for Drell-Yan " << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut3 = 1;

		// CUT 4: photon_Et >= 12GeV && DeltaR(photon, close muon)<=0.8
		if(!( (MPtPhoton->Et()>=12.0)&&(deltaRmin<=0.8) )){
			cerr << "\tCUT: event " << ievt  << " CUT at level IV for gamma momentum" << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut4 = 1;

		// CUT 5: 87.2GeV <= mumugamma invariant mass <= 95.2GeV *** *** *** 70GeV <= mumugamma invariant mass <= 110GeV
		bool cutMuMuGammaWindow = false;
		if(signal){
			cutMuMuGammaWindow = (mumugammaInvMass >=87.2) && (mumugammaInvMass <=95.2);} // in case of signal
		else {
			cutMuMuGammaWindow = (mumugammaInvMass >=70.0) && (mumugammaInvMass <=110.0);} // in case of background
		if(!( cutMuMuGammaWindow )){
			cerr << "\tCUT: event " << ievt  << " CUT at level V for Z Mass Window " << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut5 = 1;
	
		// CUT 6: farMuon->isoR03_emEt() <= 1.0
		if(!( farMuon->isoR03_emEt()<=1.0 )) {
			cerr << "\tCUT: event " << ievt  << " CUT at level VI for large emEt " << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut6 = 1;

		// CUT 7: farMuon->Pt() >= 30.0
		if(!( farMuon->Pt()>=30.0 )) {
			cerr << "\tCUT: event " << ievt  << " CUT at level VII for soft far muon " << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut7 = 1;

		// CUT 8: nearMuon->isoR03_hadEt() < 1.0
		if(!( nearMuon->isoR03_hadEt()<1.0 )){
			cerr << "\tCUT: event " << ievt  << " CUT at level VIII for large hadEt " << endl;
			miniTree->Fill();
			continue;
		}
		isAfterCut8 = 1;
		isAfterCut9 = 1;
		isAfterCut10 = 1;
		isSelected = 1;

		farMuon->Clear();
		nearMuon->Clear();
		

		miniTree->Fill();
	} // fin boucle sur evts

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
