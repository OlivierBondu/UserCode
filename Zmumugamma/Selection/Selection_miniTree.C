#include "Selection_miniTree.h"

	// ____________________________________________
	// Event information
	// ____________________________________________
	Int_t iEvent, iEventID, iLumiID, iRunID;
	Int_t isSignalApplied, isStewApplied, isZJetsApplied;

	Int_t isBeforeAllCuts, isAfterCutPthatFilter, isAfterCutZJETVETO;
	Int_t isVeryLooseMMG, isLooseMMG, isMM, isTightMMG, isMMGCandidate;
	Int_t isAfterFSRCut1, isAfterFSRCut2, isAfterFSRCut3;
	Int_t isAfterFSRCut4, isMultipleCandidate, isAfterCut5, isAfterCut6, isAfterCut7, isAfterCut8, isAfterCut9, isAfterCut10;
	Int_t isSelected;
	
	Int_t isNotCommissionned;

	Int_t Muon_eventPassHLT_Mu11;
	Int_t nVertices;
	Int_t nGenVertices;
	Float_t weight_pileUp, weight_Xsection;

	// ____________________________________________
	// Muon variables
	// ____________________________________________
	Int_t NbMuons;

	Float_t Pt_allMuons, Eta_allMuons, Phi_allMuons, Charge_allMuons;
// (M minus charge, P plus charge), (F far, N near), (L leading, S subleading)
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
	Int_t Photon_convNTracks, Photon_isConverted;
	Float_t Photon_convEoverP, Photon_convMass, Photon_convCotanTheta, Photon_convLikely, Photon_convVertexX, Photon_convVertexY, Photon_convVertexZ;
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
	Float_t Photon_lambdaRatio, Photon_ratioSeed, Photon_ratioS4, Photon_lamdbaDivCov;
	Float_t Photon_SC_rawE_x_fEta;
	Float_t Photon_SC_rawE_x_fEta_x_fBrem, Photon_SC_rawE_x_fEta_x_fBrem_AF, Photon_SC_rawE_x_fEta_x_fBrem_L, Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta, Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta, Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta;
	Float_t Photon_secondMomentMaj, Photon_secondMomentMin, Photon_secondMomentAlpha;

	// ____________________________________________
	// mugamma / mumu / mumugamma information
	// ____________________________________________
	
	Float_t Mmumu, Mmumugamma, Mmumugamma_5x5, Mmumugamma_SC, Mmumugamma_SCraw, Mmumugamma_SCraw_fEta;
	Float_t Ptmumu;
	Float_t deltaRNear, deltaRFar, deltaRMinus, deltaRPlus, deltaRLeading, deltaRSubleading;
	Float_t mmg_k, mmg_ik, mmg_s, mmg_logk, mmg_logik, mmg_logs;
	Float_t mmg_k_5x5, mmg_ik_5x5, mmg_s_5x5, mmg_logk_5x5, mmg_logik_5x5, mmg_logs_5x5;
	Float_t mmg_k_SC, mmg_ik_SC, mmg_s_SC, mmg_logk_SC, mmg_logik_SC, mmg_logs_SC;
	Float_t mmg_k_SCraw, mmg_ik_SCraw, mmg_s_SCraw, mmg_logk_SCraw, mmg_logik_SCraw, mmg_logs_SCraw;
	Float_t mmg_k_SCraw_fEta, mmg_ik_SCraw_fEta, mmg_s_SCraw_fEta, mmg_logk_SCraw_fEta, mmg_logik_SCraw_fEta, mmg_logs_SCraw_fEta;
	Float_t Mmumugamma_SCraw_fEta_fBrem, Mmumugamma_SCraw_fEta_fBrem_AF, Mmumugamma_SCraw_fEta_fBrem_L, Mmumugamma_SCraw_fEta_fBrem_fEtEta, Mmumugamma_SCraw_fEta_fBrem_AF_fEtEta, Mmumugamma_SCraw_fEta_fBrem_L_fEtEta;
	Float_t mmg_ik_SCraw_fEta_fBrem, mmg_ik_SCraw_fEta_fBrem_AF, mmg_ik_SCraw_fEta_fBrem_L, mmg_ik_SCraw_fEta_fBrem_fEtEta, mmg_ik_SCraw_fEta_fBrem_AF_fEtEta, mmg_ik_SCraw_fEta_fBrem_L_fEtEta; 
  // ____________________________________________
  // Neural Network variables
  // ____________________________________________
	Float_t Photon_NNshapeOutput;

	// ____________________________________________
  // MC Truth
  // ___________________________________________

  Float_t Photon_MC_E, Photon_MC_Px, Photon_MC_Py, Photon_MC_Pz, Photon_MC_Phi, Photon_MC_Eta;
  Int_t Photon_MCisConverted;
  Float_t Photon_MCconvEoverP, Photon_MCconvMass, Photon_MCconvCotanTheta, Photon_MCconvVertexX, Photon_MCconvVertexY, Photon_MCconvVertexZ;
  Float_t MuonM_MC_E, MuonM_MC_Px, MuonM_MC_Py, MuonM_MC_Pz, MuonM_MC_Phi, MuonM_MC_Eta;
  Float_t MuonP_MC_E, MuonP_MC_Px, MuonP_MC_Py, MuonP_MC_Pz, MuonP_MC_Phi, MuonP_MC_Eta;
  Float_t MuonN_MC_E, MuonN_MC_Px, MuonN_MC_Py, MuonN_MC_Pz, MuonN_MC_Phi, MuonN_MC_Eta;
  Float_t MuonF_MC_E, MuonF_MC_Px, MuonF_MC_Py, MuonF_MC_Pz, MuonF_MC_Phi, MuonF_MC_Eta;
  Float_t MuonL_MC_E, MuonL_MC_Px, MuonL_MC_Py, MuonL_MC_Pz, MuonL_MC_Phi, MuonL_MC_Eta;
  Float_t MuonS_MC_E, MuonS_MC_Px, MuonS_MC_Py, MuonS_MC_Pz, MuonS_MC_Phi, MuonS_MC_Eta;
  Float_t Photon_SC_rawE_x_fEta_o_MC_E, Photon_E_o_MC_E;
  Float_t Photon_SC_rawE_x_fEta_x_fBrem_o_MC_E, Photon_SC_rawE_x_fEta_x_fBrem_AF_o_MC_E, Photon_SC_rawE_x_fEta_x_fBrem_L_o_MC_E, Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta_o_MC_E, Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta_o_MC_E, Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta_o_MC_E;	

	Float_t Mmumu_Photon_MC, Mmumugamma_Photon_MC, mmg_k_Photon_MC, mmg_ik_Photon_MC, mmg_s_Photon_MC, mmg_logk_Photon_MC, mmg_logik_Photon_MC, mmg_logs_Photon_MC;
	Float_t Mmumu_Muons_MC, Mmumugamma_Muons_MC, mmg_k_Muons_MC, mmg_ik_Muons_MC, mmg_s_Muons_MC, mmg_logk_Muons_MC, mmg_logik_Muons_MC, mmg_logs_Muons_MC;
	Float_t Mmumu_MMG_MC, Mmumugamma_MMG_MC, mmg_k_MMG_MC, mmg_ik_MMG_MC, mmg_s_MMG_MC, mmg_logk_MMG_MC, mmg_logik_MMG_MC, mmg_logs_MMG_MC;



//int Selection_miniTree()
int main(int argc, char *argv[])
//int main()
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
//	char* sample_char2 = argv[1];

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
	string correction = "";
	bool isManualCorrectionsApplied = false;
	if( argc > 4 )
	{
		correction = argv[4];
		if( (correction == "Louis") || (correction == "Anne-Fleur") || (correction == "START42_V11") )
		{
			cout << correction << " correction set will be applied upstream" << endl;
			isManualCorrectionsApplied = true;
		} else {
			std::stringstream ss ( argv[4] );
			ss >> EScale;
		}
	}
	double EScale_inj = EScale;
	
// Optional argument is extra resolution
	double EResolution = 0.0;
	if( argc > 5 )
	{
		std::stringstream ss ( argv[5] );
		ss >> EResolution;
	}
	EResolution = (double)EResolution / (double)100.0;
	TTimeStamp *time = new TTimeStamp();
	TRandom3* generator = new TRandom3(time->GetNanoSec());
		// TODO

//	char* inputfile = argv[6];

//	TProof * p = TProof::Open("ccaplmaster.in2p3.fr");
	gSystem->Load("libToto.so");
	bool doHLT										= false;
	bool doMC										 = (bool)(isZgammaMC >= 1);
	bool doJetMC									= false;
	bool doMETMC									= false;
	bool doPDFInfo								= false;
	bool doSignalMuMuGamma				= (bool)(isZgammaMC >= 1);
	bool doSignalTopTop					 = false;
	bool doPhotonConversionMC		 = true;
	bool doBeamSpot							 = false;
	bool doPrimaryVertex					= true;
	bool doZeePrimaryVertex			 = false;
	bool doTrack									= false;
	bool doJet										= false;
	bool doMuon									 = true;
	bool doElectron							 = false;
	bool doPhoton								 = true;
	bool doCluster								= false;
	bool doPhotonConversion			 = true;
	bool doMET										= false;
	bool doBardak								 = false;
	bool doPhotonVertexCorrection = false;
	bool doPhotonIsolation				= false;

	//cout<<endl<<"doMC du debut = "<<doMC<<endl;
	//cout<<endl<<"doSignalMuMuGamma = "<<doSignalMuMuGamma<<endl;
	// DATASET	
	TChain *inputEventTree = new TChain("eventTree");
	TChain *inputRunTree = new TChain("runTree");

	inputEventTree->Add(Form("/sps/cms/obondu/CMSSW_4_2_3_patch2/src/Zmumugamma/RecoSamples/%s/%s*root", sample_char, sample_char));
	inputRunTree->Add(Form("/sps/cms/obondu/CMSSW_4_2_3_patch2/src/Zmumugamma/RecoSamples/%s/%s*root", sample_char, sample_char));
//		inputRunTree->Add("DYToMuMu_*root");
//		inputRunTree->Add("DYToMuMu_*root");
//	inputEventTree->Add(inputfile);
//	inputRunTree->Add(inputfile);

// INSERTFILES

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
/*	
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
*/	
		TBranch* mcSignalMuMuGamma_br = 0;
		TRootSignalEvent* mcMuMuGammaEvent = 0;
	if(doSignalMuMuGamma)
	{
		inputEventTree->SetBranchAddress("MuMuGamma", &mcMuMuGammaEvent, &mcSignalMuMuGamma_br);
		inputEventTree->SetBranchStatus("MuMuGamma", 1);
	}
/*	
		TBranch* mcTopTopEvent_br = 0;
		TRootSignalEvent* mcTopTopEvent = 0;
	if(doSignalTopTop)
	{
		inputEventTree->SetBranchAddress("rootMCTopTop", &mcTopTopEvent, &mcTopTopEvent_br);
		inputEventTree->SetBranchStatus("rootMCTopTop", 1);
	}
*/	
		TBranch* mcPhotons_br = 0;
		TClonesArray* mcPhotons = new TClonesArray("TRootMCPhoton", 0);
	if(doPhotonConversionMC)
	{
		inputEventTree->SetBranchAddress("MCPhotons", &mcPhotons, &mcPhotons_br);
		inputEventTree->SetBranchStatus("MCPhotons", 1);
	}
/*	
		TBranch* beamSpot_br = 0;
		TRootBeamSpot* beamSpot = 0;
	if(doBeamSpot)
	{
		inputEventTree->SetBranchAddress("BeamSpot", &beamSpot, &beamSpot_br);
		inputEventTree->SetBranchStatus("BeamSpot", 1);
	}
*/
		TBranch* vertices_br = 0;
		TClonesArray* vertices = new TClonesArray("TRootVertex", 0);
	if(doPrimaryVertex)
	{
		inputEventTree->SetBranchAddress("Vertices", &vertices, &vertices_br);
		inputEventTree->SetBranchStatus("Vertices", 1);
	}
/*	
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
*/	
		TBranch* muons_br = 0;
		TClonesArray* muons = new TClonesArray("TRootMuon", 0);
	if(doMuon)
	{
		inputEventTree->SetBranchAddress("muons", &muons, &muons_br);
		inputEventTree->SetBranchStatus("muons", 1);
	}
/*	
		TBranch* electrons_br = 0;
		TClonesArray* electrons = new TClonesArray("TRootElectron", 0);
	if(doElectron)
	{
		inputEventTree->SetBranchAddress("gsfElectrons", &electrons, &electrons_br);
		inputEventTree->SetBranchStatus("gsfElectrons", 1);
	}
*/	
		TBranch* photons_br = 0;
		TClonesArray* photons = new TClonesArray("TRootPhoton", 0);
	if(doPhoton)
	{
		inputEventTree->SetBranchAddress("photons", &photons, &photons_br);
		inputEventTree->SetBranchStatus("photons", 1);
	}
/*	
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
*/

  int* NumWantedHLTnames;

  string ListWantedHLTnames[1];
	ListWantedHLTnames[0] = "HLT_Mu11";
	

	// ____________________________________________
	// preparing the tree
	// ____________________________________________

	TTree* miniTree = new TTree("miniTree","Mu Mu Gamma informations");
	TTree* miniTree_allmuons = new TTree("miniTree_allmuons","all muons informations");
	TTree* miniTree_allphotons = new TTree("miniTree_allphotons","all photons informations");
//	TTree *outputEventTree = inputEventTree->CloneTree(0);

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

	miniTree->Branch("isVeryLooseMMG", &isVeryLooseMMG, "isVeryLooseMMG/I");
	miniTree->Branch("isLooseMMG", &isLooseMMG, "isLooseMMG/I");
	miniTree->Branch("isMM", &isMM, "isMM/I");
	miniTree->Branch("isTightMMG", &isTightMMG, "isTightMMG/I");
	miniTree->Branch("isMMGCandidate", &isMMGCandidate, "isMMGCandidate/I");

	miniTree->Branch("isAfterFSRCut1", &isAfterFSRCut1, "isAfterFSRCut1/I");
	miniTree->Branch("isAfterFSRCut2", &isAfterFSRCut2, "isAfterFSRCut2/I");
	miniTree->Branch("isAfterFSRCut3", &isAfterFSRCut3, "isAfterFSRCut3/I");

	miniTree->Branch("isAfterFSRCut4", &isAfterFSRCut4, "isAfterFSRCut4/I");
	miniTree->Branch("isMultipleCandidate", &isMultipleCandidate, "isMultipleCandidate/I");
	miniTree->Branch("isAfterCut5", &isAfterCut5, "isAfterCut5/I");
	miniTree->Branch("isAfterCut6", &isAfterCut6, "isAfterCut6/I");
	miniTree->Branch("isAfterCut7", &isAfterCut7, "isAfterCut7/I");
	miniTree->Branch("isAfterCut8", &isAfterCut8, "isAfterCut8/I");
	miniTree->Branch("isAfterCut9", &isAfterCut9, "isAfterCut9/I");
	miniTree->Branch("isAfterCut10", &isAfterCut10, "isAfterCut10/I");

	miniTree->Branch("isSelected", &isSelected, "isSelected/I");
	miniTree->Branch("nVertices", &nVertices, "nVertices/I");
	miniTree->Branch("nGenVertices", &nGenVertices, "nGenVertices/I");
	miniTree->Branch("weight_pileUp", &weight_pileUp, "weight_pileUp/F");
	miniTree->Branch("weight_Xsection", &weight_Xsection, "weight_Xsection/F");

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

	miniTree_allmuons->Branch("isVeryLooseMMG", &isVeryLooseMMG, "isVeryLooseMMG/I");
	miniTree_allmuons->Branch("isLooseMMG", &isLooseMMG, "isLooseMMG/I");
	miniTree_allmuons->Branch("isMM", &isMM, "isMM/I");
	miniTree_allmuons->Branch("isTightMMG", &isTightMMG, "isTightMMG/I");
	miniTree_allmuons->Branch("isMMGCandidate", &isMMGCandidate, "isMMGCandidate/I");

	miniTree_allmuons->Branch("isAfterFSRCut1", &isAfterFSRCut1, "isAfterFSRCut1/I");
	miniTree_allmuons->Branch("isAfterFSRCut2", &isAfterFSRCut2, "isAfterFSRCut2/I");
	miniTree_allmuons->Branch("isAfterFSRCut3", &isAfterFSRCut3, "isAfterFSRCut3/I");

	miniTree_allmuons->Branch("isAfterFSRCut4", &isAfterFSRCut4, "isAfterFSRCut4/I");
	miniTree_allmuons->Branch("isMultipleCandidate", &isMultipleCandidate, "isMultipleCandidate/I");
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

	miniTree_allphotons->Branch("isVeryLooseMMG", &isVeryLooseMMG, "isVeryLooseMMG/I");
	miniTree_allphotons->Branch("isLooseMMG", &isLooseMMG, "isLooseMMG/I");
	miniTree_allphotons->Branch("isMM", &isMM, "isMM/I");
	miniTree_allphotons->Branch("isTightMMG", &isTightMMG, "isTightMMG/I");
	miniTree_allphotons->Branch("isMMGCandidate", &isMMGCandidate, "isMMGCandidate/I");

	miniTree_allphotons->Branch("isAfterFSRCut1", &isAfterFSRCut1, "isAfterFSRCut1/I");
	miniTree_allphotons->Branch("isAfterFSRCut2", &isAfterFSRCut2, "isAfterFSRCut2/I");
	miniTree_allphotons->Branch("isAfterFSRCut3", &isAfterFSRCut3, "isAfterFSRCut3/I");

	miniTree_allphotons->Branch("isAfterFSRCut4", &isAfterFSRCut4, "isAfterFSRCut4/I");
	miniTree_allphotons->Branch("isMultipleCandidate", &isMultipleCandidate, "isMultipleCandidate/I");
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
	miniTree->Branch("Photon_isConverted", &Photon_isConverted, "Photon_isConverted/I");
	miniTree->Branch("Photon_convEoverP", &Photon_convEoverP, "Photon_convEoverP/F");
	miniTree->Branch("Photon_convMass", &Photon_convMass, "Photon_convMass/F");
	miniTree->Branch("Photon_convCotanTheta", &Photon_convCotanTheta, "Photon_convCotanTheta/F");
	miniTree->Branch("Photon_convLikely", &Photon_convLikely, "Photon_convLikely/F");
	miniTree->Branch("Photon_convVertexX", &Photon_convVertexX, "Photon_convVertexX/F");
	miniTree->Branch("Photon_convVertexY", &Photon_convVertexY, "Photon_convVertexY/F");
	miniTree->Branch("Photon_convVertexZ", &Photon_convVertexZ, "Photon_convVertexZ/F");
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

	miniTree->Branch("Photon_lambdaRatio", &Photon_lambdaRatio, "Photon_lambdaRatio/F");
	miniTree->Branch("Photon_ratioSeed", &Photon_ratioSeed, "Photon_ratioSeed/F");
	miniTree->Branch("Photon_ratioS4", &Photon_ratioS4, "Photon_ratioS4/F");
	miniTree->Branch("Photon_lamdbaDivCov", &Photon_lamdbaDivCov, "Photon_lamdbaDivCov/F");
	miniTree->Branch("Photon_SC_rawE_x_fEta", &Photon_SC_rawE_x_fEta, "Photon_SC_rawE_x_fEta/F");

	miniTree->Branch("Photon_SC_rawE_x_fEta_x_fBrem", &Photon_SC_rawE_x_fEta_x_fBrem, "Photon_SC_rawE_x_fEta_x_fBrem/F");
	miniTree->Branch("Photon_SC_rawE_x_fEta_x_fBrem_AF", &Photon_SC_rawE_x_fEta_x_fBrem_AF, "Photon_SC_rawE_x_fEta_x_fBrem_AF/F");
	miniTree->Branch("Photon_SC_rawE_x_fEta_x_fBrem_L", &Photon_SC_rawE_x_fEta_x_fBrem_L, "Photon_SC_rawE_x_fEta_x_fBrem_L/F");
	miniTree->Branch("Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta", &Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta, "Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta/F");
	miniTree->Branch("Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta", &Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta, "Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta/F");
	miniTree->Branch("Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta", &Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta, "Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta/F");


	miniTree->Branch("Photon_secondMomentMaj", &Photon_secondMomentMaj, "Photon_secondMomentMaj/F");
	miniTree->Branch("Photon_secondMomentMin", &Photon_secondMomentMin, "Photon_secondMomentMin/F");
	miniTree->Branch("Photon_secondMomentAlpha", &Photon_secondMomentAlpha, "Photon_secondMomentAlpha/F");
	  
	// ____________________________________________
	// mugamma / mumu / mumugamma information
	// ____________________________________________

	miniTree->Branch("Mmumu", &Mmumu, "Mmumu/F");
	miniTree->Branch("Mmumugamma", &Mmumugamma, "Mmumugamma/F");
	miniTree->Branch("Mmumugamma_5x5", &Mmumugamma_5x5, "Mmumugamma_5x5/F");
	miniTree->Branch("Mmumugamma_SC", &Mmumugamma_SC, "Mmumugamma_SC/F");
	miniTree->Branch("Mmumugamma_SCraw", &Mmumugamma_SCraw, "Mmumugamma_SCraw/F");
	miniTree->Branch("Mmumugamma_SCraw_fEta", &Mmumugamma_SCraw_fEta, "Mmumugamma_SCraw_fEta/F");
	
	miniTree->Branch("Mmumugamma_SCraw_fEta_fBrem", &Mmumugamma_SCraw_fEta_fBrem, "Mmumugamma_SCraw_fEta_fBrem/F");
	miniTree->Branch("Mmumugamma_SCraw_fEta_fBrem_AF", &Mmumugamma_SCraw_fEta_fBrem_AF, "Mmumugamma_SCraw_fEta_fBrem_AF/F");	
	miniTree->Branch("Mmumugamma_SCraw_fEta_fBrem_L", &Mmumugamma_SCraw_fEta_fBrem_L, "Mmumugamma_SCraw_fEta_fBrem_L/F");
	miniTree->Branch("Mmumugamma_SCraw_fEta_fBrem_fEtEta", &Mmumugamma_SCraw_fEta_fBrem_fEtEta, "Mmumugamma_SCraw_fEta_fBrem_fEtEta/F");
	miniTree->Branch("Mmumugamma_SCraw_fEta_fBrem_AF_fEtEta", &Mmumugamma_SCraw_fEta_fBrem_AF_fEtEta, "Mmumugamma_SCraw_fEta_fBrem_AF_fEtEta/F");
	miniTree->Branch("Mmumugamma_SCraw_fEta_fBrem_L_fEtEta", &Mmumugamma_SCraw_fEta_fBrem_L_fEtEta, "Mmumugamma_SCraw_fEta_fBrem_L_fEtEta/F");



	miniTree->Branch("Ptmumu", &Ptmumu, "Ptmumu/F");
	miniTree_allmuons->Branch("Ptmumu", &Ptmumu, "Ptmumu/F");

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

	miniTree->Branch("mmg_k_SCraw_fEta", &mmg_k_SCraw_fEta, "mmg_k_SCraw_fEta/F");
  miniTree->Branch("mmg_ik_SCraw_fEta", &mmg_ik_SCraw_fEta, "mmg_ik_SCraw_fEta/F");
  miniTree->Branch("mmg_s_SCraw_fEta", &mmg_s_SCraw_fEta, "mmg_s_SCraw_fEta/F");
  miniTree->Branch("mmg_logk_SCraw_fEta", &mmg_logk_SCraw_fEta, "mmg_logk_SCraw_fEta/F");
  miniTree->Branch("mmg_logik_SCraw_fEta", &mmg_logik_SCraw_fEta, "mmg_logik_SCraw_fEta/F");
  miniTree->Branch("mmg_logs_SCraw_fEta", &mmg_logs_SCraw_fEta, "mmg_logs_SCraw_fEta/F");


  	miniTree->Branch("mmg_ik_SCraw_fEta_fBrem", &mmg_ik_SCraw_fEta_fBrem, "mmg_ik_SCraw_fEta_fBrem/F");
	miniTree->Branch("mmg_ik_SCraw_fEta_fBrem_AF", &mmg_ik_SCraw_fEta_fBrem_AF, "mmg_ik_SCraw_fEta_fBrem_AF/F");
	miniTree->Branch("mmg_ik_SCraw_fEta_fBrem_L", &mmg_ik_SCraw_fEta_fBrem_L, "mmg_ik_SCraw_fEta_fBrem_L/F");
	miniTree->Branch("mmg_ik_SCraw_fEta_fBrem_fEtEta", &mmg_ik_SCraw_fEta_fBrem_fEtEta, "mmg_ik_SCraw_fEta_fBrem_fEtEta/F");
	miniTree->Branch("mmg_ik_SCraw_fEta_fBrem_AF_fEtEta", &mmg_ik_SCraw_fEta_fBrem_AF_fEtEta, "mmg_ik_SCraw_fEta_fBrem_AF_fEtEta/F");
	miniTree->Branch("mmg_ik_SCraw_fEta_fBrem_L_fEtEta", &mmg_ik_SCraw_fEta_fBrem_L_fEtEta, "mmg_ik_SCraw_fEta_fBrem_L_fEtEta/F");
 
	// ____________________________________________
  // Neural Network variables
  // ____________________________________________
	miniTree->Branch("Photon_NNshapeOutput", &Photon_NNshapeOutput, "Photon_NNshapeOutput/F");
 
	// ____________________________________________
  // MC Truth
  // ___________________________________________

	miniTree->Branch("Photon_MC_E", &Photon_MC_E, "Photon_MC_E/F");
	miniTree->Branch("Photon_MC_Px", &Photon_MC_Px, "Photon_MC_Px/F");
	miniTree->Branch("Photon_MC_Py", &Photon_MC_Py, "Photon_MC_Py/F");
	miniTree->Branch("Photon_MC_Pz", &Photon_MC_Pz, "Photon_MC_Pz/F");
	miniTree->Branch("Photon_MC_Phi", &Photon_MC_Phi, "Photon_MC_Phi/F");
	miniTree->Branch("Photon_MC_Eta", &Photon_MC_Eta, "Photon_MC_Eta/F");
	miniTree->Branch("Photon_MCisConverted", &Photon_MCisConverted, "Photon_MCisConverted/F");
	miniTree->Branch("Photon_MCconvEoverP", &Photon_MCconvEoverP, "Photon_MCconvEoverP/F");
	miniTree->Branch("Photon_MCconvMass", &Photon_MCconvMass, "Photon_MCconvMass/F");
	miniTree->Branch("Photon_MCconvCotanTheta", &Photon_MCconvCotanTheta, "Photon_MCconvCotanTheta/F");
	miniTree->Branch("Photon_MCconvVertexX", &Photon_MCconvVertexX, "Photon_MCconvVertexX/F");
	miniTree->Branch("Photon_MCconvVertexY", &Photon_MCconvVertexY, "Photon_MCconvVertexY/F");
	miniTree->Branch("Photon_MCconvVertexZ", &Photon_MCconvVertexZ, "Photon_MCconvVertexZ/F");
	miniTree->Branch("MuonM_MC_E", &MuonM_MC_E, "MuonM_MC_E/F");
	miniTree->Branch("MuonM_MC_Px", &MuonM_MC_Px, "MuonM_MC_Px/F");
	miniTree->Branch("MuonM_MC_Py", &MuonM_MC_Py, "MuonM_MC_Py/F");
	miniTree->Branch("MuonM_MC_Pz", &MuonM_MC_Pz, "MuonM_MC_Pz/F");
	miniTree->Branch("MuonM_MC_Phi", &MuonM_MC_Phi, "MuonM_MC_Phi/F");
	miniTree->Branch("MuonM_MC_Eta", &MuonM_MC_Eta, "MuonM_MC_Eta/F");
	miniTree->Branch("MuonP_MC_E", &MuonP_MC_E, "MuonP_MC_E/F");
	miniTree->Branch("MuonP_MC_Px", &MuonP_MC_Px, "MuonP_MC_Px/F");
	miniTree->Branch("MuonP_MC_Py", &MuonP_MC_Py, "MuonP_MC_Py/F");
	miniTree->Branch("MuonP_MC_Pz", &MuonP_MC_Pz, "MuonP_MC_Pz/F");
	miniTree->Branch("MuonP_MC_Phi", &MuonP_MC_Phi, "MuonP_MC_Phi/F");
	miniTree->Branch("MuonP_MC_Eta", &MuonP_MC_Eta, "MuonP_MC_Eta/F");
	miniTree->Branch("MuonN_MC_E", &MuonN_MC_E, "MuonN_MC_E/F");
	miniTree->Branch("MuonN_MC_Px", &MuonN_MC_Px, "MuonN_MC_Px/F");
	miniTree->Branch("MuonN_MC_Py", &MuonN_MC_Py, "MuonN_MC_Py/F");
	miniTree->Branch("MuonN_MC_Pz", &MuonN_MC_Pz, "MuonN_MC_Pz/F");
	miniTree->Branch("MuonN_MC_Phi", &MuonN_MC_Phi, "MuonN_MC_Phi/F");
	miniTree->Branch("MuonN_MC_Eta", &MuonN_MC_Eta, "MuonN_MC_Eta/F");
	miniTree->Branch("MuonF_MC_E", &MuonF_MC_E, "MuonF_MC_E/F");
	miniTree->Branch("MuonF_MC_Px", &MuonF_MC_Px, "MuonF_MC_Px/F");
	miniTree->Branch("MuonF_MC_Py", &MuonF_MC_Py, "MuonF_MC_Py/F");
	miniTree->Branch("MuonF_MC_Pz", &MuonF_MC_Pz, "MuonF_MC_Pz/F");
	miniTree->Branch("MuonF_MC_Phi", &MuonF_MC_Phi, "MuonF_MC_Phi/F");
	miniTree->Branch("MuonF_MC_Eta", &MuonF_MC_Eta, "MuonF_MC_Eta/F");
	miniTree->Branch("MuonL_MC_E", &MuonL_MC_E, "MuonL_MC_E/F");
	miniTree->Branch("MuonL_MC_Px", &MuonL_MC_Px, "MuonL_MC_Px/F");
	miniTree->Branch("MuonL_MC_Py", &MuonL_MC_Py, "MuonL_MC_Py/F");
	miniTree->Branch("MuonL_MC_Pz", &MuonL_MC_Pz, "MuonL_MC_Pz/F");
	miniTree->Branch("MuonL_MC_Phi", &MuonL_MC_Phi, "MuonL_MC_Phi/F");
	miniTree->Branch("MuonL_MC_Eta", &MuonL_MC_Eta, "MuonL_MC_Eta/F");
	miniTree->Branch("MuonS_MC_E", &MuonS_MC_E, "MuonS_MC_E/F");
	miniTree->Branch("MuonS_MC_Px", &MuonS_MC_Px, "MuonS_MC_Px/F");
	miniTree->Branch("MuonS_MC_Py", &MuonS_MC_Py, "MuonS_MC_Py/F");
	miniTree->Branch("MuonS_MC_Pz", &MuonS_MC_Pz, "MuonS_MC_Pz/F");
	miniTree->Branch("MuonS_MC_Phi", &MuonS_MC_Phi, "MuonS_MC_Phi/F");
	miniTree->Branch("MuonS_MC_Eta", &MuonS_MC_Eta, "MuonS_MC_Eta/F");
	miniTree->Branch("Photon_SC_rawE_x_fEta_o_MC_E", &Photon_SC_rawE_x_fEta_o_MC_E, "Photon_SC_rawE_x_fEta_o_MC_E/F");
	miniTree->Branch("Photon_E_o_MC_E", &Photon_E_o_MC_E, "Photon_E_o_MC_E/F");

	miniTree->Branch("Photon_SC_rawE_x_fEta_x_fBrem_o_MC_E", &Photon_SC_rawE_x_fEta_x_fBrem_o_MC_E, "Photon_SC_rawE_x_fEta_x_fBrem_o_MC_E/F");
	miniTree->Branch("Photon_SC_rawE_x_fEta_x_fBrem_AF_o_MC_E", &Photon_SC_rawE_x_fEta_x_fBrem_AF_o_MC_E, "Photon_SC_rawE_x_fEta_x_fBrem_AF_o_MC_E/F");
	miniTree->Branch("Photon_SC_rawE_x_fEta_x_fBrem_L_o_MC_E", &Photon_SC_rawE_x_fEta_x_fBrem_L_o_MC_E, "Photon_SC_rawE_x_fEta_x_fBrem_L_o_MC_E/F");
	miniTree->Branch("Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta_o_MC_E", &Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta_o_MC_E, "Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta_o_MC_E/F");
	miniTree->Branch("Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta_o_MC_E", &Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta_o_MC_E, "Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta_o_MC_E/F");
	miniTree->Branch("Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta_o_MC_E", &Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta_o_MC_E, "Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta_o_MC_E/F");


	miniTree->Branch("Mmumu_Photon_MC", &Mmumu_Photon_MC, "Mmumu_Photon_MC/F");
	miniTree->Branch("Mmumugamma_Photon_MC", &Mmumugamma_Photon_MC, "Mmumugamma_Photon_MC/F");
	miniTree->Branch("mmg_k_Photon_MC", &mmg_k_Photon_MC, "mmg_k_Photon_MC/F");
	miniTree->Branch("mmg_ik_Photon_MC", &mmg_ik_Photon_MC, "mmg_ik_Photon_MC/F");
	miniTree->Branch("mmg_s_Photon_MC", &mmg_s_Photon_MC, "mmg_s_Photon_MC/F");
	miniTree->Branch("mmg_logk_Photon_MC", &mmg_logk_Photon_MC, "mmg_logk_Photon_MC/F");
	miniTree->Branch("mmg_logik_Photon_MC", &mmg_logik_Photon_MC, "mmg_logik_Photon_MC/F");
	miniTree->Branch("mmg_logs_Photon_MC", &mmg_logs_Photon_MC, "mmg_logs_Photon_MC/F");
	miniTree->Branch("Mmumu_Muons_MC", &Mmumu_Muons_MC, "Mmumu_Muons_MC/F");
	miniTree->Branch("Mmumugamma_Muons_MC", &Mmumugamma_Muons_MC, "Mmumugamma_Muons_MC/F");
	miniTree->Branch("mmg_k_Muons_MC", &mmg_k_Muons_MC, "mmg_k_Muons_MC/F");
	miniTree->Branch("mmg_ik_Muons_MC", &mmg_ik_Muons_MC, "mmg_ik_Muons_MC/F");
	miniTree->Branch("mmg_s_Muons_MC", &mmg_s_Muons_MC, "mmg_s_Muons_MC/F");
	miniTree->Branch("mmg_logk_Muons_MC", &mmg_logk_Muons_MC, "mmg_logk_Muons_MC/F");
	miniTree->Branch("mmg_logik_Muons_MC", &mmg_logik_Muons_MC, "mmg_logik_Muons_MC/F");
	miniTree->Branch("mmg_logs_Muons_MC", &mmg_logs_Muons_MC, "mmg_logs_Muons_MC/F");
	miniTree->Branch("Mmumu_MMG_MC", &Mmumu_MMG_MC, "Mmumu_MMG_MC/F");
	miniTree->Branch("Mmumugamma_MMG_MC", &Mmumugamma_MMG_MC, "Mmumugamma_MMG_MC/F");
	miniTree->Branch("mmg_k_MMG_MC", &mmg_k_MMG_MC, "mmg_k_MMG_MC/F");
	miniTree->Branch("mmg_ik_MMG_MC", &mmg_ik_MMG_MC, "mmg_ik_MMG_MC/F");
	miniTree->Branch("mmg_s_MMG_MC", &mmg_s_MMG_MC, "mmg_s_MMG_MC/F");
	miniTree->Branch("mmg_logk_MMG_MC", &mmg_logk_MMG_MC, "mmg_logk_MMG_MC/F");
	miniTree->Branch("mmg_logik_MMG_MC", &mmg_logik_MMG_MC, "mmg_logik_MMG_MC/F");
	miniTree->Branch("mmg_logs_MMG_MC", &mmg_logs_MMG_MC, "mmg_logs_MMG_MC/F");

  TMVA::Reader* reader = new TMVA::Reader( "!Color:!Silent" );
  reader->AddVariable("pho_cEP",&Photon_covEtaPhi);
  reader->AddVariable("pho_SCbr",&Photon_SC_brem);
  reader->AddVariable("(pho_cEE+pho_cPP-sqrt((pho_cEE-pho_cPP)**2+4*pho_cEP**2))/(pho_cEE+pho_cPP+sqrt((pho_cEE-pho_cPP)**2+4*pho_cEP**2))",&Photon_lambdaRatio);
  reader->AddVariable("pho_eMax/pho_SCEraw",&Photon_ratioSeed);
  reader->AddVariable("pho_etawidth",&Photon_etaWidth);
  reader->AddVariable("pho_e2x2/pho_e5x5",&Photon_ratioS4);
  reader->AddVariable("(pho_cEE+pho_cPP-sqrt((pho_cEE-pho_cPP)**2+4*pho_cEP**2))/pho_cEE",&Photon_lamdbaDivCov);
  reader->AddVariable("pho_r19",&Photon_r19);
  reader->BookMVA("MLP method","/sps/cms/hbrun/DiPhotons41X/diPhotonMC/weights/TMVAClassification_MLP.weights.xml");


	
	// SETUP PARAMETERS	
	unsigned int NbEvents = (int)inputEventTree->GetEntries();
//	unsigned int NbEvents = 10000;
//	bool powheg = false;
	bool powheg = true;
	bool signal = false;
	bool stew = false;
	bool zjet_veto = (bool)(isZgammaMC >= 1);
	cout << "Nb of events : " << NbEvents << endl;
	cout << "Signal is: " << signal <<endl;
	cout << "Stew is: " << stew << endl;
	cout << "ZJet veto is: " << zjet_veto << endl;
	int nBeforeAllCuts, nAfterCutPthatFilter, nAfterCutCSA07ID, nAfterCutZJETVETO, nAfterVeryLooseMMG, nAfterLooseMMG, nAfterCut1c, nAfterTightMMG, nAfterCut1e, nAfterCut2a, nAfterCut2b, nAfterCut2c, nAfterCut3, nAfterCut4, nAfterCut5, nAfterCut6, nAfterCut7, nAfterCut8, nAfterCut9, nAfterCut10, nSelected;
	nBeforeAllCuts = nAfterCutPthatFilter = nAfterCutCSA07ID = nAfterCutZJETVETO = nAfterVeryLooseMMG = nAfterLooseMMG = nAfterCut1c = nAfterTightMMG = nAfterCut1e = nAfterCut2a = nAfterCut2b = nAfterCut2c = nAfterCut3 = nAfterCut4 = nAfterCut5 = nAfterCut6 = nAfterCut7 = nAfterCut8 = nAfterCut9 = nAfterCut10 = nSelected = 0;

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

//	cout << "inputRunTree->GetEntries()= " << inputRunTree->GetEntries() << endl;
//	cout << "inputRunTree->GetCurrentFile()->GetName()= " << inputRunTree->GetCurrentFile()->GetName() << endl;
//	cout << "inputRunTree->GetMaxTreeSize()= " << inputRunTree->GetMaxTreeSize() << endl;
//	inputRunTree->GetEvent(0);
//	inputRunTree->GetEntry(0);
//	cout << "inputRunTree->GetCurrentFile()->GetName()= " << inputRunTree->GetCurrentFile()->GetName() << endl;
//	inputRunTree->~TTree();
//	inputRunTree->Clear();
//	delete inputRunTree;
//	free(inputRunTree);
  string lastFile = "";

	double integratedLuminosity = 1078.19387;
//  double XSectionDYToMuMu = 1300.0 * 1.2416;
  double XSectionDYToMuMu = 1626.0;
//  double XSectionTTJets = 94.0;
  double XSectionTTJets = 94.76;
  double XSectionWJetsToLNu = 7899.0;
  double XSectionQCDMu = 349988.0;

//  double InitialNumberDYToMuMu = 2148325.0;
  double InitialNumberDYToMuMu = 29743564.0;
//  double InitialNumberTTJets = 1089625.0;
  double InitialNumberTTJets = 3701947.0;
  double InitialNumberWJetsToLNu = 5413258.0;
  double InitialNumberQCDMu = 8797418.0;

	double minPtHat = -100;
  double maxPtHat = 1000000;
  int verbosity = 0;
	int Nb_events_outside_powheg_cuts = 0;
	int TOTALnbMuonsAfterID[12] = {0};
	int TOTALnbEventsAfterMuonID[12] = {0};
	int TOTALnbDimuonsAfterID[3] = {0};
	int TOTALnbEventsAfterDimuonID[3] = {0};
	int TOTALnbPhotonsAfterID[6] = {0};
	int TOTALnbEventsAfterPhotonID[6] = {0};
	int TOTALnbMuMuGammaAfterID[8] = {0};
	int TOTALnbEventsAfterMuMuGammaID[8] = {0};

	// LOOP over events
//	for(unsigned int ievt=0; ievt<NbEvents; ievt++)
	for(unsigned int ievt=0; ievt<100; ievt++)
	{
		if(verbosity>4) cout << "analysing event ievt= " << ievt << endl;
		nBeforeAllCuts++;
		isBeforeAllCuts = 1;
		int nprint = (int)((double)NbEvents/(double)100.0);
		if( (ievt % nprint)==0 ){ cout<< ievt <<" events done over "<<NbEvents<<" ( "<<ceil((double)ievt/(double)NbEvents*100)<<" \% )"<<endl; }

		iEvent = ievt;
		inputEventTree->GetEvent(ievt);
//    if( lastFile == "" ){
//      lastFile = string(inputEventTree->GetCurrentFile()->GetName());
//      cout << ievt << "\t" << lastFile << endl;
//    }

		// ____________________________________________
		// Event information
		// ____________________________________________
		iEventID = event->eventId();
		iLumiID = event->luminosityBlock();
		iRunID = event->runId();
//		if(iRunID != 149291) continue;
		nVertices = vertices->GetEntries();
		nGenVertices = vertices->GetEntries();
		if( (isZgammaMC >= 1) )
		{
			nGenVertices = event->nInTimePUVertices();
		}
		isSignalApplied = signal;
		isStewApplied = stew;
		isZJetsApplied = zjet_veto;
		isAfterCutPthatFilter = isAfterCutZJETVETO = 0;
		isVeryLooseMMG = isLooseMMG = isMM = isTightMMG = isMMGCandidate = 0;
		isAfterFSRCut1 = isAfterFSRCut2 = isAfterFSRCut3 = 0;
		isAfterFSRCut4 = isMultipleCandidate = isAfterCut5 = isAfterCut6 = isAfterCut7 = isAfterCut8 = isAfterCut9 = isAfterCut10 = 0;
		isSelected = 0;

		weight_Xsection = weight_pileUp = 1.0;

		string sample(sample_char);

//		if( sample == "DYToMuMu_M-20_TuneZ2_7TeV-pythia6_v3" ){
		if( (sample == "DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_v2") || (sample == "DYToMuMu") ){
			weight_Xsection = (double)(  (double)((double)(XSectionDYToMuMu) / (double)(InitialNumberDYToMuMu)) * (double)integratedLuminosity);
			weight_pileUp = weight_DYToMuMu(nGenVertices+1);
		}
		if( sample == "QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6" )
		{
			weight_Xsection = (double)(  (double)((double)(XSectionQCDMu) / (double)(InitialNumberQCDMu)) * (double)integratedLuminosity);
			weight_pileUp = weight_QCDMu(nGenVertices+1);
		}
//		if( sample == "TT_TuneZ2_7TeV-pythia6-tauola" )
		if( sample == "TTJets_TuneZ2_7TeV-madgraph-tauola_v2" )
		{
			weight_Xsection = (double)(  (double)((double)(XSectionTTJets) / (double)(InitialNumberTTJets)) * (double)integratedLuminosity);
			weight_pileUp = weight_TTJets(nGenVertices+1);
		}
		if( sample == "WToMuNu_TuneZ2_7TeV-pythia6" )
		{
			weight_Xsection = (double)(  (double)((double)(XSectionWJetsToLNu) / (double)(InitialNumberWJetsToLNu)) * (double)integratedLuminosity);
			weight_pileUp = weight_WJetsToLNu(nGenVertices+1);
		}


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
		vector<double> Photon_scale;
		if( (argc > 5) && (EResolution != 0) )
		{ // If there is an extra resolution to smear the photon energy
			for(int iphoton = 0; iphoton < NbPhotons ; iphoton++)
			{
				Photon_scale.push_back(generator->Gaus(EScale_inj, EResolution));
			}
//			cout << "Photon_scale = " << Photon_scale[Photon_scale.size() -1] << endl;
		} else {
			if( (argc > 4) && isManualCorrectionsApplied)
			{
        for(int iphoton = 0; iphoton < NbPhotons ; iphoton++)
        {
					TRootPhoton *myphotontocorrect;
					myphotontocorrect = (TRootPhoton*) photons->At(iphoton);
          Photon_scale.push_back(photonManualCorrectionFactor(myphotontocorrect, correction));
/*
					cout << "myphotontocorrect->isEBPho()= " << myphotontocorrect->isEBPho() << endl;
					cout << "myphotontocorrect->r9()= " << myphotontocorrect->r9() << endl;
					cout << "brem= " << (double)(myphotontocorrect->superCluster()->phiWidth()) / (double)(myphotontocorrect->superCluster()->etaWidth()) << endl;
					cout << "myphotontocorrect->superCluster()->rawEnergy()= " << myphotontocorrect->superCluster()->rawEnergy() << endl;
					cout << "myphotontocorrect->preshowerEnergy()= " << myphotontocorrect->preshowerEnergy() << endl;
*/
					cout << "myphotontocorrect->Energy()= " << myphotontocorrect->Energy() << endl;
					cout << "photonManualCorrectionFactor= " << Photon_scale[Photon_scale.size() - 1] << endl;
					cout << "photonManualCorrectionFactor * myphotontocorrect->Energy()= " << Photon_scale[Photon_scale.size() - 1] * myphotontocorrect->Energy() << endl;
					cout << endl << endl;
//					return 2;
        }
			} else {
				for(int iphoton = 0; iphoton < NbPhotons ; iphoton++)
	      {
					Photon_scale.push_back(EScale_inj);
				}
			}
		}
		Pt_allPhotons = Eta_allPhotons = Phi_allPhotons = Cross_allPhotons = -99;
		isNotCommissionned = -99;
		isEBorEE_allPhotons = 1;
		isEB_allPhotons, isEE_allPhotons, isEEM_allPhotons, isEEP_allPhotons = -99;
		Photon_Eta = Photon_Phi = -99;
		Photon_isEBorEE = 1;
		Photon_isEB = Photon_isEE = Photon_isEEP = Photon_isEEM = -99;
		Photon_hasPixelSeed = Photon_isAlsoElectron = Photon_Nclusters = Photon_nBasicClusters = Photon_nXtals = -99;
		Photon_isTightPhoton = Photon_isLoosePhoton = -99;
		Photon_convNTracks = Photon_isConverted = -99;
		Photon_convEoverP = Photon_convMass = Photon_convCotanTheta = Photon_convLikely = Photon_convVertexX = Photon_convVertexY = Photon_convVertexZ = -99.0;	
		Photon_E = Photon_Et = Photon_E2x2 = Photon_E3x3 = Photon_E5x5 = Photon_Emax = Photon_E2nd = -99.0;
		Photon_r19 = Photon_r9 = Photon_cross = -99.0;
		Photon_caloConeSize = Photon_PreshEnergy = Photon_HoE = Photon_sigmaEtaEta = Photon_sigmaIetaIeta = Photon_covEtaEta = Photon_covPhiPhi = Photon_covEtaPhi = Photon_etaWidth = Photon_phiWidth = -99.0;
		Photon_dR03isoEcalRecHit = Photon_dR03isoHcalRecHit = Photon_dR03isoSolidTrkCone = Photon_dR03isoHollowTrkCone = Photon_dR03isoNTracksSolidCone = Photon_dR03isoNTracksHollowCone = -99.0;
		Photon_dR04isoEcalRecHit = Photon_dR04isoHcalRecHit = Photon_dR04isoSolidTrkCone = Photon_dR04isoHollowTrkCone = Photon_dR04isoNTracksSolidCone = Photon_dR04isoNTracksHollowCone = -99.0;
		Photon_seedTime = Photon_seedFlag = -99.0;
		Photon_seedPosition1 = Photon_seedPosition2 = -99;
		Photon_SC_Eta = Photon_SC_Phi = Photon_SC_brem = -99.0;
		Photon_SC_E = Photon_SC_Et = Photon_SC_rawE = Photon_SC_rawEt = -99.0;
		Photon_lambdaRatio = Photon_ratioSeed = Photon_ratioS4 = Photon_lamdbaDivCov = -99.0;
		Photon_SC_rawE_x_fEta = -99.0;
		Photon_SC_rawE_x_fEta_x_fBrem = Photon_SC_rawE_x_fEta_x_fBrem_AF = Photon_SC_rawE_x_fEta_x_fBrem_L = Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta = Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta = Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta = -99.0;
		Photon_secondMomentMaj = Photon_secondMomentMin = Photon_secondMomentAlpha = -99.0;

		// ____________________________________________
		// mugamma / mumu / mumugamma information
		// ____________________________________________
		Mmumu = Mmumugamma = Mmumugamma_5x5 = Mmumugamma_SC = Mmumugamma_SCraw = Mmumugamma_SCraw_fEta = -99.0;
		Mmumugamma_SCraw_fEta_fBrem = Mmumugamma_SCraw_fEta_fBrem_AF = Mmumugamma_SCraw_fEta_fBrem_L = Mmumugamma_SCraw_fEta_fBrem_fEtEta = Mmumugamma_SCraw_fEta_fBrem_AF_fEtEta = Mmumugamma_SCraw_fEta_fBrem_L_fEtEta = -99.0;
		Ptmumu = -99.0;
		deltaRNear = deltaRFar = deltaRPlus = deltaRMinus = deltaRLeading = deltaRSubleading = -99.0;
		mmg_k = mmg_ik = mmg_s = mmg_logk = mmg_logik = mmg_logs = -99.0;
		mmg_k_5x5 = mmg_ik_5x5 = mmg_s_5x5 = mmg_logk_5x5 = mmg_logik_5x5 = mmg_logs_5x5 = -99.0;
		mmg_k_SC = mmg_ik_SC = mmg_s_SC = mmg_logk_SC = mmg_logik_SC = mmg_logs_SC = -99.0;
		mmg_k_SCraw = mmg_ik_SCraw = mmg_s_SCraw = mmg_logk_SCraw = mmg_logik_SCraw = mmg_logs_SCraw = -99.0;
		mmg_k_SCraw_fEta = mmg_ik_SCraw_fEta = mmg_s_SCraw_fEta = mmg_logk_SCraw_fEta = mmg_logik_SCraw_fEta = mmg_logs_SCraw_fEta = -99.0;

		mmg_ik_SCraw_fEta_fBrem = mmg_ik_SCraw_fEta_fBrem_AF = mmg_ik_SCraw_fEta_fBrem_L = mmg_ik_SCraw_fEta_fBrem_fEtEta = mmg_ik_SCraw_fEta_fBrem_AF_fEtEta = mmg_ik_SCraw_fEta_fBrem_L_fEtEta = -99.0;

		// ____________________________________________
	  // Neural Network variables
  	// ____________________________________________
		Photon_NNshapeOutput = -99.0;

		// ____________________________________________
	  // MC Truth
	  // ___________________________________________
	  Photon_MC_E = Photon_MC_Px = Photon_MC_Py = Photon_MC_Pz = Photon_MC_Phi = Photon_MC_Eta = -99.0;
	  Photon_MCisConverted = -99;
	  Photon_MCconvEoverP = Photon_MCconvMass = Photon_MCconvCotanTheta = Photon_MCconvVertexX = Photon_MCconvVertexY = Photon_MCconvVertexZ = -99.0;
	  MuonM_MC_E = MuonM_MC_Px = MuonM_MC_Py = MuonM_MC_Pz = MuonM_MC_Phi = MuonM_MC_Eta = -99.0;
	  MuonP_MC_E = MuonP_MC_Px = MuonP_MC_Py = MuonP_MC_Pz = MuonP_MC_Phi = MuonP_MC_Eta = -99.0;
	  MuonN_MC_E = MuonN_MC_Px = MuonN_MC_Py = MuonN_MC_Pz = MuonN_MC_Phi = MuonN_MC_Eta = -99.0;
	  MuonF_MC_E = MuonF_MC_Px = MuonF_MC_Py = MuonF_MC_Pz = MuonF_MC_Phi = MuonF_MC_Eta = -99.0;
	  MuonL_MC_E = MuonL_MC_Px = MuonL_MC_Py = MuonL_MC_Pz = MuonL_MC_Phi = MuonL_MC_Eta = -99.0;
	  MuonS_MC_E = MuonS_MC_Px = MuonS_MC_Py = MuonS_MC_Pz = MuonS_MC_Phi = MuonS_MC_Eta = -99.0;
		Photon_SC_rawE_x_fEta_o_MC_E = Photon_E_o_MC_E = -99.0;
		Photon_SC_rawE_x_fEta_x_fBrem_o_MC_E = Photon_SC_rawE_x_fEta_x_fBrem_AF_o_MC_E  = Photon_SC_rawE_x_fEta_x_fBrem_L_o_MC_E  = Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta_o_MC_E  = Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta_o_MC_E  = Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta_o_MC_E  = -99.0;

		Mmumu_Photon_MC = Mmumugamma_Photon_MC = mmg_k_Photon_MC = mmg_ik_Photon_MC = mmg_s_Photon_MC = mmg_logk_Photon_MC = mmg_logik_Photon_MC = mmg_logs_Photon_MC = -99.0;
		Mmumu_Muons_MC = Mmumugamma_Muons_MC = mmg_k_Muons_MC = mmg_ik_Muons_MC = mmg_s_Muons_MC = mmg_logk_Muons_MC = mmg_logik_Muons_MC = mmg_logs_Muons_MC = -99.0;
		Mmumu_MMG_MC = Mmumugamma_MMG_MC = mmg_k_MMG_MC = mmg_ik_MMG_MC = mmg_s_MMG_MC = mmg_logk_MMG_MC = mmg_logik_MMG_MC = mmg_logs_MMG_MC = -99.0;

		// ____________________________________________
		// END OF INITIALIZATION
		// ____________________________________________

// ********************************************************************************************************************
// ***** MC-TRUTH SIGNAL MATCHING *****
// ********************************************************************************************************************

    bool MCphotons_from_muons_from_Z = false;
    bool MC_first_muon_in_phase_space = false;
    bool MC_second_muon_in_phase_space = false;
    bool MCsignal_in_phase_space = false;

    if( zjet_veto && (!powheg) ){
      // ****
      // First loop: look for a photon
      for( int iMCparticle = 0 ; iMCparticle < mcParticles->GetEntries() ; iMCparticle++ ){
        TRootMCParticle *mcParticleCandidate = (TRootMCParticle *)mcParticles->At(iMCparticle);
        if( (mcParticleCandidate->status()==1) && (mcParticleCandidate->type() == 22) ){ // if the particle is a true MC photon
          if( abs(mcParticleCandidate->motherType()) == 13 ){// if the true MC photon origins from a muon
//							cout << "mother: " << abs(mcParticleCandidate->motherType()) << "\tgranny: " << abs(mcParticleCandidate->grannyType()) << "\toldgranny: " << abs(mcParticleCandidate->oldgrannyType()) << endl;
            if( abs(mcParticleCandidate->oldgrannyType()) == 23 ){// photon coming from a muon coming from a Z
//            if( abs(mcParticleCandidate->grannyType()) == 23 ){// photon coming from a muon coming from a Z
              if( (mcParticleCandidate->Pt()>8.0) && (abs(mcParticleCandidate->Eta())<3.0) ){
                MCphotons_from_muons_from_Z = true;
              }
            }
          }
        } // end of origin of the photon
      }// end of loop over MC particles
      // ****
      // Second loop: look for muons
      for( int iMCparticle = 0 ; iMCparticle < mcParticles->GetEntries() ; iMCparticle++ ){
        TRootMCParticle *mcParticleCandidate = (TRootMCParticle *)mcParticles->At(iMCparticle);
        if( MCphotons_from_muons_from_Z == true ){ // if there is a photon coming from a muon coming from a Z and photon in MC phase space, THEN, look for muons in phase space
          if( (MC_first_muon_in_phase_space == false) && (mcParticleCandidate->status()==1) && (abs(mcParticleCandidate->type()) == 13) ){// if the particle is a final state muon
            if( abs(mcParticleCandidate->motherType()) == 13 ){
              if( abs(mcParticleCandidate->oldgrannyType()) == 23 ){// muon is coming from a Z
//              if( abs(mcParticleCandidate->grannyType()) == 23 ){// muon is coming from a Z
                if( (mcParticleCandidate->Pt()>8.0) && (abs(mcParticleCandidate->Eta())<3.0) ){
                  MC_first_muon_in_phase_space = true;
                }
              }
            }
          } // end of selecting first muon
          if( (MC_first_muon_in_phase_space == true) && (mcParticleCandidate->status()==1) && (abs(mcParticleCandidate->type()) == 13) ){// if the particle is a final state muon
            if( abs(mcParticleCandidate->motherType()) == 13 ){
              if( abs(mcParticleCandidate->oldgrannyType()) == 23 ){// muon is coming from a Z
//              if( abs(mcParticleCandidate->grannyType()) == 23 ){// muon is coming from a Z
                if( (mcParticleCandidate->Pt()>8.0) && (abs(mcParticleCandidate->Eta())<3.0) ){
                  MC_second_muon_in_phase_space = true;
                  MCsignal_in_phase_space = true;
                }
              }
            }
          }// end of selecting second muon
        }
      }// end of loop over MC particles
 			if( ((isZgammaMC == 1) && (!MCsignal_in_phase_space)) || ((isZgammaMC == 2) && (MCsignal_in_phase_space)) )
      {
//        cerr<<"SAFE: photon(s) coming from muon, aborting event " << ievt << endl;
        continue;
      }
      isAfterCutZJETVETO = 1;
      nAfterCutZJETVETO++;
     }// end of if Z+Jets veto for anything but powheg

    if( zjet_veto && powheg )
    {
			// POWHEG GENERATOR CUTS
			TRootParticle *mymuplus;
      mymuplus = (mcMuMuGammaEvent->muplus());
      TRootParticle *mymuminus;
      mymuminus = (mcMuMuGammaEvent->muminus());
      TRootParticle dimuon;
      dimuon = *mymuplus + *mymuminus;
      //cout << "dimuon.M()= " << dimuon.M() << endl;
/*
      if( (dimuon.M() < 20.0) || (dimuon.M() > 500.0) )
      {
        cout << "This event " << ievt << "is outside powheg range" << endl;
        Nb_events_outside_powheg_cuts++;
//				continue;
      }
*/


			// FSR-tagging
      if( mcMuMuGammaEvent->nZ() == 1 )
      {// consistency check
//        cerr << "There is " << mcMuMuGammaEvent->nFSR() << " fsr photons in the event" << endl;
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
            if( (myphoton->Pt()>8.0) && (abs(myphoton->Eta())<3.0) ) MCphotons_from_muons_from_Z = true;
          }// end of loop over mc photons
          if( MCphotons_from_muons_from_Z )
          { // if there is a fsr photon passing acceptance cuts, then look at muons coming from the Z
            if( (mcMuMuGammaEvent->muplus()->Pt()>8.0) && (abs((mcMuMuGammaEvent->muplus()->Eta())<3.0)) )
            {
              MC_first_muon_in_phase_space = true;
              if( (mcMuMuGammaEvent->muminus()->Pt()>8.0) && (abs((mcMuMuGammaEvent->muminus()->Eta())<3.0)) )
              {
                MC_second_muon_in_phase_space = true;
                MCsignal_in_phase_space = true;
              }
            }
          } // end of cuts on muons coming from the Z
        }// end of check if the event is a mc fsr passing acceptance cuts

				if( ((isZgammaMC == 1) && (!MCsignal_in_phase_space)) || ((isZgammaMC == 2) && (MCsignal_in_phase_space)) )
        {
//          cerr<<"SAFE: photon(s) coming from muon, aborting event " << ievt << endl;

          continue;
        }
        isAfterCutZJETVETO = 1;
        nAfterCutZJETVETO++;
      } else {
        cout << "Failed POWHEG mumugamma consistency check" << endl;
      }// end of consistency check
    }// end of if Z+Jets veto for powheg

// ********************************************************************************************************************
// ***** HLT REQUIREMENT *****
// ********************************************************************************************************************

		// HLT information		

//		if(doHLT){
//			if( ievt==0 ){ inputRunTree->GetEvent(ievt); NumWantedHLTnames = InitializeHLTinfo(inputRunTree, runInfos, event->nHLTPaths(), ListWantedHLTnames, 1);  }
//			if ( string(inputEventTree->GetCurrentFile()->GetName()) != lastFile ){
//				inputRunTree->GetEntry(inputEventTree->GetTreeNumber());
//     	  lastFile = string(inputEventTree->GetCurrentFile()->GetName());
//     	  cout << ievt << "\t" << lastFile << endl;
//     	 	NumWantedHLTnames = InitializeHLTinfo(inputRunTree, runInfos, event->nHLTPaths(), ListWantedHLTnames, 1);
//     	}
//      doHLTInfo(event, runInfos, NumWantedHLTnames, 1, &Muon_eventPassHLT_Mu11);
//		}
//
//
//		if (!((event->ptHat()>=minPtHat)&&(event->ptHat()<maxPtHat)))
//		{
//      cerr << "CUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )" << " CUT for pthat filtering" << endl;
//			continue;
//		}
//		isAfterCutPthatFilter = 1;
//		nAfterCutPthatFilter++;

// ********************************************************************************************************************
// ***** MUON OBJECT SELECTION *****
// ********************************************************************************************************************

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

//      if(! (mymuon->) ){// 
//        muonIsNotCommissioned.push_back(1);
//        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because" << endl;
//        continue;
//      }

      if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " accepted" << endl;
      muonIsNotCommissioned.push_back(0);
      muonIdentified.push_back(imuon);
////			mymuon->Clear();
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

// ********************************************************************************************************************
// ***** DIMUON OBJECT SELECTION *****
// ********************************************************************************************************************


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

// --------------------------------------------------------------------------------------------------------------------
// ----- dimuon candidate of opposite charge -----
// --------------------------------------------------------------------------------------------------------------------

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
////			Muon1->Clear();
////			Muon2->Clear();
		}
		if(! (numberOfDimuons[1] >= 1) ) continue; // Not enough dimuon candidates, skip the event
		TOTALnbDimuonsAfterID[1] += numberOfDimuons[1];
		TOTALnbEventsAfterDimuonID[1] += 1;

// --------------------------------------------------------------------------------------------------------------------
// ----- dimuon candidate of correct invariant mass -----
// --------------------------------------------------------------------------------------------------------------------

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
////			Muon1->Clear();
////			Muon2->Clear();
		}

		if(! (numberOfDimuons[2] >= 1) )// Not enough dimuon candidates, skip the event
    {
       continue;

    }

		TOTALnbDimuonsAfterID[2] += numberOfDimuons[2];
		TOTALnbEventsAfterDimuonID[2] += 1;

		isMM = 1;
		for(int idimuon = 0 ; idimuon < numberOfDimuons[2]; idimuon++)
		{
      TRootMuon* mymuon1;
      TRootMuon* mymuon2;
      mymuon1 = (TRootMuon*) muons->At( IDofMuons[2][idimuon].first );
      mymuon2 = (TRootMuon*) muons->At( IDofMuons[2][idimuon].second );
			
	    TLorentzVector mumu;
			mumu = (*mymuon1) + (*mymuon2);
			Ptmumu = mumu.Pt();
////	    mumu.Clear();
////			mymuon1->Clear();
////			mymuon2->Clear();
			miniTree_allmuons->Fill();
		}

// ********************************************************************************************************************
// ***** PHOTON OBJECT SELECTION *****
// ********************************************************************************************************************

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

		for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++)
		{
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

/*
      if( myphoton->superCluster()->seedSeverity()==4 ){ // kWeird
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because kWeird" << endl;
        continue;
      }
*/
			nbPhotonsAfterID[3]++;
			TOTALnbPhotonsAfterID[3] += 1;
/*
      if( myphoton->superCluster()->seedRecoFlag()==2 ){ // kOutOfTime
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because kOutOfTime" << endl;
        continue;
      }
*/
			nbPhotonsAfterID[4]++;
			TOTALnbPhotonsAfterID[4] += 1;

      if( Photon_scale[iphoton]*(myphoton->Pt()) <= 10.0 ){ // Transverse momentum
				if(verbosity>2) cout << "\t\tmyphoton->Pt()= " << myphoton->Pt() << endl;
				if(verbosity>2) cout << "\t\tPhoton_scale["<<iphoton<<"]= " << Photon_scale[iphoton] << endl;
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because low pt" << endl;
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
// ********************************************************************************************************************
// ***** MUMUGAMMA FSR TRIPLET OBJECT SELECTION *****
// ********************************************************************************************************************

// --------------------------------------------------------------------------------------------------------------------
// ----- initializing mumugamma triplet candidates holder -----
// --------------------------------------------------------------------------------------------------------------------

		if(verbosity>2) cout << "creating triplet pair object" << endl;
		int nbMuMuGammaAfterID[8] = {0};
		// Build mumugamma candidates
		int nbMuMuGammaCandidates = ( nbPhotonsAfterID[5] )*( numberOfDimuons[2] );
		nbMuMuGammaAfterID[0] = nbMuMuGammaCandidates;
		TOTALnbMuMuGammaAfterID[0] += nbMuMuGammaAfterID[0];
		TOTALnbEventsAfterMuMuGammaID[0]++ ;
		pair <int, pair<int, int> > MuMuGammaCandidates[8][nbMuMuGammaCandidates];

		if(verbosity>2) cout << "initializing triplet objects" << endl;
		// Initializing triplet objects
		for(int i = 0; i < 8; i++)
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

// --------------------------------------------------------------------------------------------------------------------
// ----- cut on close_isoR03_hadEt -----
// --------------------------------------------------------------------------------------------------------------------
		isMMGCandidate = 1;

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

			if(verbosity>5) cerr << "close_isoR03_hadEt= " << close_isoR03_hadEt << endl;
			if( close_isoR03_hadEt >= 1.0)
			{
				if(verbosity>3) cerr << "candidate thrown because close_isoR03_hadEt= " << close_isoR03_hadEt << endl;
				FillMMG(myphoton, mymuon1, mymuon2, Photon_scale[MuMuGammaCandidates[0][i_mmg].first], doMC, doPhotonConversionMC, mcParticles, mcPhotons, reader);
				miniTree->Fill();
				continue;
			} else {
				if(verbosity>5) cerr << "candidate accepted: close_isoR03_hadEt= " << close_isoR03_hadEt << endl;
			}
		
			if(verbosity>5) cerr << " filling new pair " << endl;
			MuMuGammaCandidates[1][nbMuMuGammaAfterID[1]] = make_pair(MuMuGammaCandidates[0][i_mmg].first, make_pair(MuMuGammaCandidates[0][i_mmg].second.first, MuMuGammaCandidates[0][i_mmg].second.second) );
			nbMuMuGammaAfterID[1]++;
			TOTALnbMuMuGammaAfterID[1]++;
		}
		if(verbosity>4) cout << "nbMuMuGammaAfterID[1]= " << nbMuMuGammaAfterID[1] << endl;
		if(! (nbMuMuGammaAfterID[1] > 0) )
    {
					if(verbosity>2) cerr << "not enough triplet candidate passing close_isoR03_hadEt cut " << endl;
        continue;

    }

		TOTALnbEventsAfterMuMuGammaID[1]++ ;
		isAfterFSRCut1 = 1;
// --------------------------------------------------------------------------------------------------------------------
// ----- cut on far_isoR03_emEt -----
// --------------------------------------------------------------------------------------------------------------------

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
				FillMMG(myphoton, mymuon1, mymuon2, Photon_scale[MuMuGammaCandidates[1][i_mmg].first], doMC, doPhotonConversionMC, mcParticles, mcPhotons, reader);
				miniTree->Fill();
				continue;
			}
			MuMuGammaCandidates[2][nbMuMuGammaAfterID[2]] = make_pair(MuMuGammaCandidates[1][i_mmg].first, make_pair(MuMuGammaCandidates[1][i_mmg].second.first, MuMuGammaCandidates[1][i_mmg].second.second) );
      nbMuMuGammaAfterID[2]++;
    }
		if(verbosity>4) cout << "nbMuMuGammaAfterID[2]= " << nbMuMuGammaAfterID[2] << endl;
    if(! (nbMuMuGammaAfterID[2] > 0) )
    {
      continue;
    }

		TOTALnbMuMuGammaAfterID[2] += nbMuMuGammaAfterID[2];
		TOTALnbEventsAfterMuMuGammaID[2]++ ;
		isAfterFSRCut2 = 1;
// --------------------------------------------------------------------------------------------------------------------
// ----- cut on min_DeltaR -----
// --------------------------------------------------------------------------------------------------------------------

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
			if( min_DeltaR >= 0.8 )
			{
				FillMMG(myphoton, mymuon1, mymuon2, Photon_scale[MuMuGammaCandidates[2][i_mmg].first], doMC, doPhotonConversionMC, mcParticles, mcPhotons, reader);
				miniTree->Fill();
				continue;
			}
			MuMuGammaCandidates[3][nbMuMuGammaAfterID[3]] = make_pair(MuMuGammaCandidates[2][i_mmg].first, make_pair(MuMuGammaCandidates[2][i_mmg].second.first, MuMuGammaCandidates[2][i_mmg].second.second) );
      nbMuMuGammaAfterID[3]++;

    }
    if(! (nbMuMuGammaAfterID[3] > 0) )
    {
         continue;
    }

		TOTALnbMuMuGammaAfterID[3] += nbMuMuGammaAfterID[3];
		TOTALnbEventsAfterMuMuGammaID[3]++ ;
		isAfterFSRCut3 = 1;
// --------------------------------------------------------------------------------------------------------------------
// ----- cut on far_muonPt -----
// --------------------------------------------------------------------------------------------------------------------

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
			if( far_muonPt <= 30.0 )
			{
				FillMMG(myphoton, mymuon1, mymuon2, Photon_scale[MuMuGammaCandidates[3][i_mmg].first], doMC, doPhotonConversionMC, mcParticles, mcPhotons, reader);
				miniTree->Fill();
				continue;
			}
			MuMuGammaCandidates[4][nbMuMuGammaAfterID[4]] = make_pair(MuMuGammaCandidates[3][i_mmg].first, make_pair(MuMuGammaCandidates[3][i_mmg].second.first, MuMuGammaCandidates[3][i_mmg].second.second) );
      nbMuMuGammaAfterID[4]++;

    }
    if(! (nbMuMuGammaAfterID[4] > 0) )
    {
      continue;

    }

		TOTALnbMuMuGammaAfterID[4] += nbMuMuGammaAfterID[4];
		TOTALnbEventsAfterMuMuGammaID[4]++ ;
		isAfterFSRCut4 = 1;
// --------------------------------------------------------------------------------------------------------------------
// ----- cut on mumugamma.M() (very loose window) -----
// --------------------------------------------------------------------------------------------------------------------

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
			EScale = Photon_scale[MuMuGammaCandidates[4][i_mmg].first];
			TLorentzVector *PhotonEScale = new TLorentzVector( EScale*(myphoton->Px()), EScale*(myphoton->Py()), EScale*(myphoton->Pz()), EScale*(myphoton->Energy()));
			mumugamma = (*PhotonEScale) + (*mymuon1) + (*mymuon2);
			if( (mumugamma.M() < 30.0) || (180.0 < mumugamma.M())  )
			{
				FillMMG(myphoton, mymuon1, mymuon2, EScale, doMC, doPhotonConversionMC, mcParticles, mcPhotons, reader);
				miniTree->Fill();
				continue;
			}
			MuMuGammaCandidates[5][nbMuMuGammaAfterID[5]] = make_pair(MuMuGammaCandidates[4][i_mmg].first, make_pair(MuMuGammaCandidates[4][i_mmg].second.first, MuMuGammaCandidates[4][i_mmg].second.second) );
      nbMuMuGammaAfterID[5]++;
    }
    if(! (nbMuMuGammaAfterID[5] > 0) )
    {
//			miniTree->Fill();
      continue;
    }
//		for(int i_mmg = 0; i_mmg < 1 ; i_mmg++)
//    {
//      TRootPhoton* myphoton;
//      TRootMuon* mymuon1;
//      TRootMuon* mymuon2;
//      myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[5][i_mmg].first);
//      mymuon1 = (TRootMuon*) muons->At( MuMuGammaCandidates[5][i_mmg].second.first );
//      mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[5][i_mmg].second.second );
//			FillMMG(myphoton, mymuon1, mymuon2, EScale, doMC, doPhotonConversionMC, mcParticles, mcPhotons, reader);
//		}
		TOTALnbMuMuGammaAfterID[5] += nbMuMuGammaAfterID[5];
		TOTALnbEventsAfterMuMuGammaID[5]++ ;
			isVeryLooseMMG = 1;
			nAfterVeryLooseMMG++;
// --------------------------------------------------------------------------------------------------------------------
// ----- cut on mumugamma.M() (loose window) -----
// --------------------------------------------------------------------------------------------------------------------


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
			EScale = Photon_scale[MuMuGammaCandidates[5][i_mmg].first];
			TLorentzVector *PhotonEScale = new TLorentzVector( EScale*(myphoton->Px()), EScale*(myphoton->Py()), EScale*(myphoton->Pz()), EScale*(myphoton->Energy()));
			mumugamma = (*PhotonEScale) + (*mymuon1) + (*mymuon2);
			if( (mumugamma.M() < 70.0) || (110.0 < mumugamma.M())  )
			{
//				cout << "non-loose event: rejected: mumugamma.M()= " << mumugamma.M() << endl;
				FillMMG(myphoton, mymuon1, mymuon2, EScale, doMC, doPhotonConversionMC, mcParticles, mcPhotons, reader);
				miniTree->Fill();
				continue;
			}
			MuMuGammaCandidates[6][nbMuMuGammaAfterID[6]] = make_pair(MuMuGammaCandidates[5][i_mmg].first, make_pair(MuMuGammaCandidates[5][i_mmg].second.first, MuMuGammaCandidates[5][i_mmg].second.second) );
      nbMuMuGammaAfterID[6]++;
    }
    if(! (nbMuMuGammaAfterID[6] > 0) )
    {
//			miniTree->Fill();
      continue;
    }
			isLooseMMG = 1;
			nAfterLooseMMG++;

		TOTALnbMuMuGammaAfterID[6] += nbMuMuGammaAfterID[6];
		TOTALnbEventsAfterMuMuGammaID[6]++ ;

//    for(int i_mmg = 0; i_mmg < nbMuMuGammaAfterID[6] ; i_mmg++)
//		for(int i_mmg = 0; i_mmg < 1 ; i_mmg++)
//    {
//      TRootPhoton* myphoton;
//      TRootMuon* mymuon1;
//      TRootMuon* mymuon2;
//      myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[6][i_mmg].first);
//      mymuon1 = (TRootMuon*) muons->At( MuMuGammaCandidates[6][i_mmg].second.first );
//      mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[6][i_mmg].second.second );
//			FillMMG(myphoton, mymuon1, mymuon2, EScale, doMC, doPhotonConversionMC, mcParticles, mcPhotons, reader);
//		}
// --------------------------------------------------------------------------------------------------------------------
// ----- cut on mumugamma.M() (tight window) -----
// --------------------------------------------------------------------------------------------------------------------


		for(int i_mmg = 0; i_mmg < nbMuMuGammaAfterID[6] ; i_mmg++)
		{
			TRootPhoton* myphoton;
			TRootMuon* mymuon1;
			TRootMuon* mymuon2;
			myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[6][i_mmg].first);
			mymuon1 = (TRootMuon*) muons->At( MuMuGammaCandidates[6][i_mmg].second.first );
			mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[6][i_mmg].second.second );
			double phiPhoton = myphoton->Phi();
			double etaPhoton = myphoton->Eta();
			double phiMuon1 = mymuon1->Phi();
			double etaMuon1 = mymuon1->Eta();
			double phiMuon2 = mymuon2->Phi();
			double etaMuon2 = mymuon2->Eta();
			double deltaRphomu1 = DeltaR(etaPhoton, phiPhoton, etaMuon1, phiMuon1);
			double deltaRphomu2 = DeltaR(etaPhoton, phiPhoton, etaMuon2, phiMuon2);
			TLorentzVector mumugamma;
			EScale = Photon_scale[MuMuGammaCandidates[6][i_mmg].first];
			TLorentzVector *PhotonEScale = new TLorentzVector( EScale*(myphoton->Px()), EScale*(myphoton->Py()), EScale*(myphoton->Pz()), EScale*(myphoton->Energy()));
			mumugamma = (*PhotonEScale) + (*mymuon1) + (*mymuon2);
			if( (mumugamma.M() < 87.2) || (95.2 < mumugamma.M())  )
			{
//				cout << "non-tight event: rejected: mumugamma.M()= " << mumugamma.M() << endl;
//				cout << "*** isVeryLooseMMG:isLooseMMG:isTightMMG= " << isVeryLooseMMG << isLooseMMG << isTightMMG << endl;
				FillMMG(myphoton, mymuon1, mymuon2, EScale, doMC, doPhotonConversionMC, mcParticles, mcPhotons, reader);
//				cout << "*** isVeryLooseMMG:isLooseMMG:isTightMMG= " << isVeryLooseMMG << isLooseMMG << isTightMMG << endl;
				miniTree->Fill();
				continue;
			}
			MuMuGammaCandidates[7][nbMuMuGammaAfterID[7]] = make_pair(MuMuGammaCandidates[6][i_mmg].first, make_pair(MuMuGammaCandidates[6][i_mmg].second.first, MuMuGammaCandidates[6][i_mmg].second.second) );
      nbMuMuGammaAfterID[7]++;
    }
    if(! (nbMuMuGammaAfterID[7] > 0) )
    {
      continue;
    }

		TOTALnbMuMuGammaAfterID[7] += nbMuMuGammaAfterID[7];
		TOTALnbEventsAfterMuMuGammaID[7]++ ;

		isTightMMG = 1;
		nAfterTightMMG++;

		nAfterCut1e++;

		nAfterCut2a++;

		nAfterCut2b++;

		nAfterCut2c++;
		if( nbMuMuGammaAfterID[7] != 1 ){
			isMultipleCandidate = 1;
	    for(int i_mmg = 0; i_mmg < nbMuMuGammaAfterID[7] ; i_mmg++)
	    {
	      TRootPhoton* myphoton;
	      TRootMuon* mymuon1;
	      TRootMuon* mymuon2;
	      myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[7][i_mmg].first);
	      mymuon1 = (TRootMuon*) muons->At( MuMuGammaCandidates[7][i_mmg].second.first );
	      mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[7][i_mmg].second.second );
	      FillMMG(myphoton, mymuon1, mymuon2, Photon_scale[MuMuGammaCandidates[7][i_mmg].first], doMC, doPhotonConversionMC, mcParticles, mcPhotons, reader);
				miniTree->Fill();
	    }
			continue;
		}

		int i_mmg = 0;
		isMultipleCandidate = 0;
		TRootPhoton* myphoton;
		TRootMuon* mymuon1;
		TRootMuon* mymuon2;
		myphoton = (TRootPhoton*) photons->At(MuMuGammaCandidates[7][i_mmg].first);
    mymuon1 = (TRootMuon*) muons->At( MuMuGammaCandidates[7][i_mmg].second.first );
    mymuon2 = (TRootMuon*) muons->At( MuMuGammaCandidates[7][i_mmg].second.second );
    FillMMG(myphoton, mymuon1, mymuon2, Photon_scale[MuMuGammaCandidates[7][i_mmg].first], doMC, doPhotonConversionMC, mcParticles, mcPhotons, reader);
		isSelected = 1;
		nSelected++;
		cerr << "OK: Surviving veto event: "<< ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )"  << endl;
		miniTree->Fill();



		nAfterCut3++;

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
	} // fin boucle sur evts LOOP

		cout << "Nb_events_outside_powheg_cuts= " << Nb_events_outside_powheg_cuts << endl << endl;
		for(int i = 0; i < 12 ; i++)
		{
			cout << "TOTALnbMuonsAfterID["<<i<<"]= " << TOTALnbMuonsAfterID[i] << "\t\t" << "TOTALnbEventsAfterMuonID["<<i<<"]= " << TOTALnbEventsAfterMuonID[i] << endl;
		}
		cout << endl;
		for(int i = 0; i < 3 ; i++)
		{
			cout << "TOTALnbDimuonsAfterID["<<i<<"]= " << TOTALnbDimuonsAfterID[i] << "\t\t" << "TOTALnbEventsAfterDimuonID["<<i<<"]= " << TOTALnbEventsAfterDimuonID[i] << endl;
		}
		cout << endl;
		for(int i = 0; i < 6 ; i++)
    {
      cout << "TOTALnbPhotonsAfterID["<<i<<"]= " << TOTALnbPhotonsAfterID[i] << "\t\t" << "TOTALnbEventsAfterPhotonID["<<i<<"]= " << TOTALnbEventsAfterPhotonID[i] << endl;
		}
		cout << endl;
		for(int i = 0; i < 8 ; i++)
		{
			cout << "TOTALnbMuMuGammaAfterID["<<i<<"]= " << TOTALnbMuMuGammaAfterID[i] << "\t\t" << "TOTALnbEventsAfterMuMuGammaID["<<i<<"]= " << TOTALnbEventsAfterMuMuGammaID[i] << endl;
			if(i == 6) cout << endl;
		}

// Writing stuff out
	OutputRootFile->Write();
	OutputRootFile->Close();

	delete OutputRootFile;
	delete inputEventTree;
	delete inputRunTree;



	return 0;

}

