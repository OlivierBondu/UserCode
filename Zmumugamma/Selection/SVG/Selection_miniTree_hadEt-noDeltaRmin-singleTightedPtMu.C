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
#pragma optimize 0

#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootBardak.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootBeamSpot.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootCluster.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootDummyEvent.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootEcalRecHit.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootElectron.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootEvent.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootJet.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootMCParticle.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootMCPhoton.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootMET.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootMuon.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootParticle.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootPhoton.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootRun.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootSignalEvent.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootSuperCluster.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootTopTop.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootTrack.h"
#include "/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/interface/TRootVertex.h"


double DeltaR( double eta1, double phi1, double eta2, double phi2){
	double DeltaEta = fabs( eta1-eta2 );
	double DeltaPhi = fabs( phi1-phi2 );
	// Returning DeltaPhi in the correct range (0, 2pi)
	while (DeltaPhi >	 TMath::Pi()) DeltaPhi -= 2*TMath::Pi();
	while (DeltaPhi <= -TMath::Pi()) DeltaPhi += 2*TMath::Pi();
	return sqrt(DeltaEta*DeltaEta + DeltaPhi*DeltaPhi);
}

/*
int* InitializeHLTinfo(TChain* inputRunTree, TRootRun* runInfos, int nPaths, string* ListWantedHLTnames, int nPathWanted){

	cout << "Initializing HLT info"<<endl;

	cout << "\t\tnPaths="<<nPaths<<endl;
	cout << "\t\tnPathWanted="<<nPathWanted<<endl;
	if (nPathWanted==0) return NULL;

	int* ListHLT = new int[nPathWanted];

	//runInfos->printHLTSummary();

	//cout << "Boucle"<<endl;

	for (int ipath=0; ipath<nPaths; ipath++){
// cout << runInfos->hltNames(ipath)<<" num="<<ipath<<endl;
		for (int iwanted=0; iwanted<nPathWanted; iwanted++){
			if (ListWantedHLTnames[iwanted]==runInfos->hltNames(ipath)) ListHLT[iwanted]=ipath;

		}
	}

	cout<< "\t\tWanted HLT :"<<endl;
	for (int iwanted=0; iwanted<nPathWanted; iwanted++){
		cout << "\t\t\t" << ListWantedHLTnames[iwanted]<< " num="<< ListHLT[iwanted]<<endl;
	}

	return ListHLT;
}

*/
/*
*/
/*
void doHLTInfo(TRootEvent* event, TRootRun* runInfos, int* ListHLT, int nPathWanted, int* Muon_eventPassHLT_Mu9){

	for (int ipath=0; ipath<nPathWanted; ipath++){
		//cout <<"HLTInfo numHLT="<<ListHLT[ipath]<<" decision="<<event->trigHLT(ListHLT[ipath])<<endl;
		if (ipath==0) *Muon_eventPassHLT_Mu9 = (int)event->trigHLT(ListHLT[ipath]);
	}

	//for(unsigned int ipath=0; ipath<event->nHLTPaths(); ipath++) {
	//	cout << "ipath="<<ipath<<" "	<<	" decision=" << event->trigHLT(ipath) <<endl;
	//}
	//for(unsigned int ipath=0; ipath<5; ipath++) cout << "	" << runInfos->hltNames(ipath) << " decision=" << event->trigHLT(ipath) <<endl;
	return;
}

*/

void doGenInfo(TRootPhoton* myphoton, TClonesArray* mcParticles, Int_t* Photon_GenId, Int_t* Photon_MotherId, Int_t* Photon_isGenElectron, Int_t* Photon_isPromptGenPho, Int_t* Photon_isFromQuarkGen, Int_t* Photon_isPi0Gen, Int_t* Photon_isEtaGen, Int_t* Photon_isRhoGen, Int_t* Photon_isOmegaGen, Float_t* Photon_PromptGenIsoEnergyStatus1, Float_t* Photon_PromptGenIsoEnergyStatus2, double dRcone){
//	cout << "doing gen info" << endl;

	double etsumStatus1 = -1;
	double etsumStatus2 = -1;

	TRootMCParticle* mygenparticle;
	int NbMCpartInCone=0;
	double bestPtdiff=500.0;
	int igpsl=-1;
	for (int igp=0; igp<mcParticles->GetEntriesFast(); igp++) {
		mygenparticle = (TRootMCParticle*) mcParticles->At(igp);
		if (DeltaR(mygenparticle->Phi(), myphoton->Phi(), mygenparticle->Eta(), myphoton->Eta())<0.1){
			if (mygenparticle->status()==1){
				//HistoMCpartStatus1InConeId->Fill(mygenparticle->type());
				NbMCpartInCone++;
				if (fabs(mygenparticle->Pt()-myphoton->Pt())<bestPtdiff){
					bestPtdiff=fabs(mygenparticle->Pt()-myphoton->Pt());
					igpsl=igp;
				}
			}
		}
	}
	if (igpsl!=-1){
		TRootMCParticle* mygenparticle;

		*Photon_isFromQuarkGen = 0;
		*Photon_isPi0Gen = 0;
		*Photon_isEtaGen = 0;
		*Photon_isRhoGen = 0;
		*Photon_isOmegaGen = 0;

		mygenparticle = (TRootMCParticle*) mcParticles->At(igpsl);
		*Photon_GenId = mygenparticle->type();
		*Photon_MotherId = mygenparticle->motherType();
		if (abs(mygenparticle->type())==11) *Photon_isGenElectron = 1;
		else *Photon_isGenElectron = 0;

		if (mygenparticle->type()==22 && mygenparticle->motherType()==22) *Photon_isPromptGenPho = 1;
		else *Photon_isPromptGenPho = 0;

		if (mygenparticle->type()==22 && mygenparticle->motherType()!=22) {

			if (mygenparticle->motherType()==21 || abs(mygenparticle->motherType())==1 || abs(mygenparticle->motherType())==2 || abs(mygenparticle->motherType())==3 || abs(mygenparticle->motherType())==4 || abs(mygenparticle->motherType())==5 || abs(mygenparticle->motherType())==6 ) *Photon_isFromQuarkGen = 1;
			if (mygenparticle->motherType()==111) *Photon_isPi0Gen = 1;
			if (mygenparticle->motherType()==221) *Photon_isEtaGen = 1;
			if (mygenparticle->motherType()==113) *Photon_isRhoGen = 1;
			if (mygenparticle->motherType()==223) *Photon_isOmegaGen = 1;

		}

		if (*Photon_isFromQuarkGen==1 || *Photon_isPromptGenPho==1){
				etsumStatus1 = 0;
				etsumStatus2 = 0;
				//Isolated ?
				double dR, dR2;
				TRootMCParticle* photon = (TRootMCParticle*) mcParticles->At(igpsl);
				for (int igp=0; igp<mcParticles->GetEntriesFast(); igp++) {
					if (igp!=igpsl){
						TRootMCParticle* mygenpart = (TRootMCParticle*) mcParticles->At(igp);
						if (mygenpart->status()==1){
							if (mygenpart->type()!=22 || (fabs(mygenpart->Pt()-photon->Pt())>0.1 && mygenpart->type()==22)){
								dR = DeltaR(photon->Phi(), mygenpart->Phi(), photon->Eta(), mygenpart->Eta());
								if (dR<dRcone){
									etsumStatus1 += mygenpart->Et();
								}
							}
						}

						if (mygenpart->status()==2){
							if (mygenpart->type()!=22 || (fabs(mygenpart->Pt()-photon->Pt())>0.1 && mygenpart->type()==22)){
								if	(abs(mygenpart->type())>6 && mygenparticle->motherType()!=21){
									dR2 = DeltaR(photon->Phi(), mygenpart->Phi(), photon->Eta(), mygenpart->Eta());
									if (dR2<dRcone){
										etsumStatus2 += mygenpart->Et();
									}
								}
							}
						}


					}
				}

			}



	}

	*Photon_PromptGenIsoEnergyStatus1 = etsumStatus1;
	*Photon_PromptGenIsoEnergyStatus2 = etsumStatus2;

	return;
}


//int Selection_miniTree(){
int main(){
	gSystem->Load("/sps/cms/obondu/CMSSW_3_8_3/src/UserCode/IpnTreeProducer/src/libToto.so");
	
	bool doHLT										= true;
	bool doMC										 = true;
	bool doJetMC									= false;
	bool doMETMC									= false;
	bool doPDFInfo								= true;
	bool doSignalMuMuGamma				= false;
	bool doSignalTopTop					 = false;
	bool doPhotonConversionMC		 = false;
	bool doBeamSpot							 = true;
	bool doPrimaryVertex					= true;
	bool doZeePrimaryVertex			 = false;
	bool doTrack									= true;
	bool doJet										= false;
	bool doMuon									 = true;
	bool doElectron							 = true;
	bool doPhoton								 = true;
	bool doCluster								= true;
	bool doPhotonConversion			 = true;
	bool doMET										= false;
	bool doBardak								 = false;
	bool doPhotonVertexCorrection = false;
	bool doPhotonIsolation				= true;

	// DATASET	
	TChain *inputEventTree = new TChain("eventTree");
	TChain *inputRunTree = new TChain("runTree");

//	inputEventTree->Add("/sps/cms/obondu/CMSSW_3_8_3/src/Zmumugamma/RecoSamples/partI/partI__*root");
//	inputEventTree->Add("/sps/cms/obondu/CMSSW_3_8_3/src/Zmumugamma/RecoSamples/partII/partII__*root");
//	inputEventTree->Add("/sps/cms/obondu/CMSSW_3_8_3/src/Zmumugamma/RecoSamples/partIII/partIII__*root");
//	inputEventTree->Add("/sps/cms/obondu/CMSSW_3_8_3/src/Zmumugamma/RecoSamples/partIV/partIV__*root");
//	inputEventTree->Add("/sps/cms/obondu/CMSSW_3_8_3/src/Zmumugamma/RecoSamples/partV/partV__*root");
//	inputEventTree->Add("/sps/cms/obondu/CMSSW_3_8_3/src/Zmumugamma/RecoSamples/partIV/partIV__run_140059_IpnTree_*root");
//	inputEventTree->Add("/sps/cms/obondu/CMSSW_3_8_3/src/Zmumugamma/RecoSamples/partIV/partIV__run_140126_IpnTree_*root");
//	inputEventTree->Add("/sps/cms/obondu/CMSSW_3_8_3/src/Zmumugamma/RecoSamples/partIV/partIV__run_140124_IpnTree_*root");
//	inputEventTree->Add("/sps/cms/obondu/CMSSW_3_8_3/src/Zmumugamma/RecoSamples/partIII/partIII__run_139100_IpnTree_*root");
//	string sample = "JanCandidates_139100";

/*
	inputEventTree->Add("");
	inputRunTree->Add("");
	string sample = "";
*/

// INSERTFILES
  string sample = "SAMPLEPART";

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
		inputEventTree->SetBranchAddress("Jets", &jets, &jets_br);
		inputEventTree->SetBranchStatus("Jets", 1);
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


  int* NumWantedHLTnames;

  string ListWantedHLTnames[1];
	ListWantedHLTnames[0] = "HLT_Mu9";
	
	
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
		cout << "HLT-Report " << "---------- Event	Summary ------------\n";
		cout << "HLT-Report"
		<< " Events total = " << runInfos->nHLTEvents()
		<< "	wasrun = " << runInfos->nHLTWasRun()
		<< "	passed = " << runInfos->nHLTAccept()
		<< "	errors = " << runInfos->nHLTErrors()
		<< "\n";
		
		cout << endl;
		cout << "HLT-Report " << "---------- HLTrig Summary ------------\n";
		cout << "HLT-Report	 HLT Bit#		 WasRun		 Passed		 Errors	Name\n";
		
		for (unsigned int i=0; i!=runInfos->nHLTPaths(); ++i)
		{
			printf("HLT-Report %10u %10u %10u %10u	", i, runInfos->hltWasRun(i), runInfos->hltAccept(i), runInfos->hltErrors(i));
			cout << runInfos->hltNames(i) << endl;
}

cout << endl;
}
*/

	// ____________________________________________
	// Event information
	// ____________________________________________
	Int_t iEvent, iEventID, iLumiID, iRunID;
	Int_t isSignalApplied, isStewApplied, isZJetsApplied;

	Int_t isBeforeAllCuts, isAfterCutPthatFilter, isAfterCutCSA07ID, isAfterCutZJETVETO;
	Int_t isAfterCut1a, isAfterCut1b, isAfterCut1c, isAfterCut1d, isAfterCut1e;
	Int_t isAfterCut2a, isAfterCut2b, isAfterCut2c;
	Int_t isAfterCut3, isAfterCut4, isAfterCut5, isAfterCut6, isAfterCut7, isAfterCut8, isAfterCut9, isAfterCut10;
	Int_t isSelected;
	
	Int_t isNotCommissionned;

	Int_t Muon_eventPassHLT_Mu9;

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

	// ____________________________________________
	// mugamma / mumu / mumugamma information
	// ____________________________________________
	
	Float_t Mmumu, Mmumugamma;
	Float_t deltaRNear, deltaRFar, deltaRMinus, deltaRPlus, deltaRLeading, deltaRSubleading;
 
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

	miniTree_allmuons->Branch("iEvent", &iEvent, "iEvent/I");
	miniTree_allmuons->Branch("iEventID", &iEventID, "iEventID/I");
	miniTree_allmuons->Branch("iLumiID", &iLumiID, "iLumiID/I");
	miniTree_allmuons->Branch("iRunID", &iRunID, "iRunID/I");

	miniTree_allmuons->Branch("isSignalApplied", &isSignalApplied, "isSignalApplied/I");
	miniTree_allmuons->Branch("isStewApplied", &isStewApplied, "isStewApplied/I");
	miniTree_allmuons->Branch("isZJetsApplied", &isZJetsApplied, "isZJetsApplied/I");

	miniTree_allmuons->Branch("isBeforeAllCuts", &isBeforeAllCuts, "isBeforeAllCuts/I");
	miniTree_allmuons->Branch("isAfterCutPthatFilter", &isAfterCutPthatFilter, "isAfterCutPthatFilter/I");
	miniTree_allmuons->Branch("isAfterCutCSA07ID", &isAfterCutCSA07ID, "isAfterCutCSA07ID/I");
	miniTree_allmuons->Branch("isAfterCutZJETVETO", &isAfterCutZJETVETO, "isAfterCutZJETVETO/I");

	miniTree_allmuons->Branch("isAfterCut1a", &isAfterCut1a, "isAfterCut1a/I");
	miniTree_allmuons->Branch("isAfterCut1b", &isAfterCut1b, "isAfterCut1b/I");
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
	miniTree_allphotons->Branch("isAfterCutCSA07ID", &isAfterCutCSA07ID, "isAfterCutCSA07ID/I");
	miniTree_allphotons->Branch("isAfterCutZJETVETO", &isAfterCutZJETVETO, "isAfterCutZJETVETO/I");

	miniTree_allphotons->Branch("isAfterCut1a", &isAfterCut1a, "isAfterCut1a/I");
	miniTree_allphotons->Branch("isAfterCut1b", &isAfterCut1b, "isAfterCut1b/I");
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

	// ____________________________________________
	// mugamma / mumu / mumugamma information
	// ____________________________________________

	miniTree->Branch("Mmumu", &Mmumu, "Mmumu/F");
	miniTree->Branch("Mmumugamma", &Mmumugamma, "Mmumugamma/F");

	miniTree->Branch("deltaRNear", &deltaRNear, "deltaRNear/F");
	miniTree->Branch("deltaRFar", &deltaRFar, "deltaRFar/F");
	miniTree->Branch("deltaRPlus", &deltaRPlus, "deltaRPlus/F");
	miniTree->Branch("deltaRMinus", &deltaRMinus, "deltaRMinus/F");
	miniTree->Branch("deltaRLeading", &deltaRLeading, "deltaRLeading/F");
	miniTree->Branch("deltaRSubleading", &deltaRSubleading, "deltaRSubleading/F");
	
	// SETUP PARAMETERS	
	unsigned int NbEvents = (int)inputEventTree->GetEntries();
//	unsigned int NbEvents = 1000;
	bool signal = false;
	bool stew = false;
	bool zjet_veto = false;
	cout << "Nb of events : " << NbEvents << endl;
	cout << "Signal is: " << signal <<endl;
	cout << "Stew is: " << stew << endl;
	cout << "ZJet veto is: " << zjet_veto << endl;
	int nBeforeAllCuts, nAfterCutPthatFilter, nAfterCutCSA07ID, nAfterCutZJETVETO, nAfterCut1a, nAfterCut1b, nAfterCut1c, nAfterCut1d, nAfterCut1e, nAfterCut2a, nAfterCut2b, nAfterCut2c, nAfterCut3, nAfterCut4, nAfterCut5, nAfterCut6, nAfterCut7, nAfterCut8, nAfterCut9, nAfterCut10, nSelected;
	nBeforeAllCuts = nAfterCutPthatFilter = nAfterCutCSA07ID = nAfterCutZJETVETO = nAfterCut1a = nAfterCut1b = nAfterCut1c = nAfterCut1d = nAfterCut1e = nAfterCut2a = nAfterCut2b = nAfterCut2c = nAfterCut3 = nAfterCut4 = nAfterCut5 = nAfterCut6 = nAfterCut7 = nAfterCut8 = nAfterCut9 = nAfterCut10 = nSelected = 0;
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

/*
	vector<unsigned int> candidateRunID;
	vector<unsigned int> candidateEventID;
//	candidateRunID.push_back(136100);
//	candidateEventID.push_back(12147077);
//	candidateRunID.push_back(140331);
//	candidateEventID.push_back(202802546);
//	candidateRunID.push_back(140383);
//	candidateEventID.push_back(428106665);
//	candidateRunID.push_back(140059);
//	candidateEventID.push_back(120481780);
//	candidateRunID.push_back(140126);
//	candidateEventID.push_back(401672288);
//	candidateRunID.push_back(140124);
//	candidateEventID.push_back(1312967051);
	candidateRunID.push_back(139100);
	candidateEventID.push_back(46221215);
	unsigned int NbOfCandidates = candidateEventID.size();
*/

	inputRunTree->GetEvent(0);
  string lastFile = "";
	double minPtHat = -100;
  double maxPtHat = 1000000;
  int verbosity = 5;

	for(unsigned int ievt=0; ievt<NbEvents; ievt++)
	{
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

		if (!((event->ptHat()>=minPtHat)&&(event->ptHat()<maxPtHat)))
		{
      cerr << "CUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )" << " CUT for pthat filtering" << endl;
			continue;
		}
		isAfterCutPthatFilter = 1;
		nAfterCutPthatFilter++;

		// ____________________________________________
		// Event information
		// ____________________________________________
		iEventID = event->eventId();
		iLumiID = event->luminosityBlock();
		iRunID = event->runId();
		isSignalApplied = signal;
		isStewApplied = stew;
		isZJetsApplied = zjet_veto;
		isAfterCutPthatFilter = isAfterCutCSA07ID = isAfterCutZJETVETO = 0;
		isAfterCut1a = isAfterCut1b = isAfterCut1c = isAfterCut1d = isAfterCut1e = 0;
		isAfterCut2a = isAfterCut2b = isAfterCut2c = 0;
		isAfterCut3 = isAfterCut4 = isAfterCut5 = isAfterCut6 = isAfterCut7 = isAfterCut8 = isAfterCut9 = isAfterCut10 = 0;
		isSelected = 0;

/*
		if( NbOfCandidates != 0 ){
//			for( int icandidate = 0 ; icandidate < NbOfCandidates ; icandidate++ ){
				int icandidate = 0;
				if( iRunID == candidateRunID[icandidate] ){
					if( iEventID == candidateEventID[icandidate] ){
						cout << "iRunID\t\tiEventID" << endl;
						cout << iRunID << "\t\t" << iEventID << endl;
					} else continue;
				} else continue;
//			}
		}
*/
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

		// ____________________________________________
		// mugamma / mumu / mumugamma information
		// ____________________________________________
		Mmumu = Mmumugamma = -99;
		deltaRNear = deltaRFar = deltaRPlus = deltaRMinus = deltaRLeading = deltaRSubleading = -99;
		// ____________________________________________
		// END OF INITIALIZATION
		// ____________________________________________

		// HLT information		
		if(doHLT){
/*
			if( ievt==0 ){ inputRunTree->GetEvent(ievt); NumWantedHLTnames = InitializeHLTinfo(inputRunTree, runInfos, event->nHLTPaths(), ListWantedHLTnames, 1);  }
			if ( string(inputEventTree->GetCurrentFile()->GetName()) != lastFile ){
				inputRunTree->GetEntry(inputEventTree->GetTreeNumber());
     	  lastFile = string(inputEventTree->GetCurrentFile()->GetName());
     	  cout << ievt << "\t" << lastFile << endl;
     	 	NumWantedHLTnames = InitializeHLTinfo(inputRunTree, runInfos, event->nHLTPaths(), ListWantedHLTnames, 1);
     	}
      doHLTInfo(event, runInfos, NumWantedHLTnames, 1, &Muon_eventPassHLT_Mu9);
*/
			Muon_eventPassHLT_Mu9 = event->hltAccept("HLT_Mu9");
		}

   // Cleaning: removing not commissionned superclusters and spikes
    vector<int> photonsNoSpike;
    photonsNoSpike.clear();
    vector<int> photonIsNotCommissioned;
    if(verbosity>0) cerr << "\t\tThere is " << NbPhotons << " photons in the photon collection" << endl;
    photonIsNotCommissioned.clear();
    for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
      TRootPhoton *myphoton;
      myphoton = (TRootPhoton*) photons->At(iphoton);
      if( (myphoton->superCluster()==0) ){ // 'broken' photon, there should be none
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because no associated SC" << endl;
        continue;
      }
/*
      if( (1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()))>0.95) && (myphoton->isEBPho()) ){ // 'spike' photons
        photonIsNotCommissioned.push_back(1);
        cerr << "\t\t\tphoton " << iphoton << " rejected because" << endl;
        continue;
      }
      if( ((myphoton->superCluster()->rawEnergy())*sin(myphoton->superCluster()->Theta()))<2.0 ){ // very low energy clusters, not commissionned
        photonIsNotCommissioned.push_back(1);
        cerr << "\t\t\tphoton " << iphoton << " rejected because" << endl;
        continue;
      }
*/
      if( myphoton->superCluster()->seedSeverity()==3 ){ // kWeird
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because kWeird" << endl;
        continue;
      }
      if( myphoton->superCluster()->seedRecoFlag()==2 ){ // kOutOfTime
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because kOutOfTime" << endl;
        continue;
      }
      if( myphoton->superCluster()->seedSeverity()==4 ){ // kBad
        photonIsNotCommissioned.push_back(1);
        continue;
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because kBad" << endl;
      }

      if( (fabs(myphoton->superCluster()->Eta()))>2.5 ){ // high eta clusters, not commisionned
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because high eta" << endl;
        continue;
      }
      if( fabs(myphoton->superCluster()->Eta())>1.4442 && fabs(myphoton->superCluster()->Eta())<1.566 ){// eta gap clusters, not commissionned
        photonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " rejected because eta gap" << endl;
        continue;
      }
/*      if ( myphoton->hoe() > 0.05){ // HoE cut is here for trigger issues
        photonIsNotCommissioned.push_back(1);
        continue;
      }*/
      if(verbosity>0) cerr << "\t\t\tphoton " << iphoton << " accepted" << endl;
      photonsNoSpike.push_back(iphoton);
      photonIsNotCommissioned.push_back(0);
    }
    unsigned int NbPhotonsNoSpike = photonsNoSpike.size();

    // Cleaning: muon quality
    vector<int> muonIsNotCommissioned;
    muonIsNotCommissioned.clear();
    vector<int> muonIdentified;
    muonIdentified.clear();
    if(verbosity>0) cerr << "\t\tThere is " << NbMuons << " muons in the muon collection" << endl;
    for(int imuon=0 ; imuon<NbMuons ; imuon++){
      TRootMuon *mymuon;
      mymuon = (TRootMuon*) muons->At(imuon);
      if(! (mymuon->isGlobalMuon() && mymuon->isTrackerMuon()) ){// The muon must be identified both as Global Muon and Tracker Muon.
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because not global AND tracker muon" << endl;
        continue;
      }
      if(! (mymuon->numberOfValidTrackerHits()>10) ){// #tracker hits > 10
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because less than 10 tracker hits (" << mymuon->numberOfValidTrackerHits() << ")" << endl;
        continue;
      }
      if(! (mymuon->normalizedChi2()<10) ){// chi2/ndof of the global muon fit < 10
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because chi2/ndof of the global muon fit < 10 (" << mymuon->normalizedChi2() << ")" << endl;
        continue;
      }
/*
      if(! () ){// Number of valid muon-detector hits used in the global fit > 0
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because " << endl;
        continue;// FIXME
      }
*/
/*      if(! (mymuon->d0()<0.002) ){// Transverse impact parameter of the muon with respect to the beam spot < 2 mm
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because " << endl;
        continue;
      }
*/
      if(! (fabs(mymuon->Eta())<2.1) ){// |eta_muon|< 2.1
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because high eta (" << mymuon->Eta() << ")" << endl;
        continue;
      }

      if(! (Muon_eventPassHLT_Mu9==1) ){// HLT_Mu9
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because not passing HLT_Mu9" << endl;
        continue;
      }


/*
      if(! ((double)(mymuon->isoR03_sumPt() + mymuon->isoR03_emEt() + mymuon->isoR03_hadEt())/(double)(mymuon->Pt())<.15) ){// Relative combined isolation = (sumPt + emEt + hcalEt)/ptmu < 0.15 in a deltaR < 0.3 cone
        muonIsNotCommissioned.push_back(1);
        if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because relative combined isolation bad" << endl;
        continue;
      }
*/

			if(! ((double)(mymuon->isoR03_sumPt()) < 3.0) ){// tracker isolation
				muonIsNotCommissioned.push_back(1);
				if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " rejected because tracker isolation high (" << mymuon->isoR03_sumPt() << " GeV)" << endl;
				continue;
			}

      if(verbosity>0) cerr << "\t\t\tmuon " << imuon << " accepted" << endl;
      muonIsNotCommissioned.push_back(0);
      muonIdentified.push_back(imuon);
    }
    unsigned int NbMuonsIdentified = muonIdentified.size();




		// CSA07 ID
		if( stew ){
			if( (event->csa07id() != 62) && (event->csa07id() != 63) ){
				cerr<<"CSA07ID is not 62/63 ( "<< event->csa07id() << ") aborting event " << ievt << endl;
				miniTree->Fill();
				for(int imuon=0 ; imuon<NbMuons ; imuon++){
					TRootMuon *mymuon;
					mymuon = (TRootMuon*) muons->At(imuon);
					Pt_allMuons = mymuon->Pt();
					Eta_allMuons = mymuon->Eta();
					Phi_allMuons = mymuon->Phi();
					Charge_allMuons = mymuon->charge();
					miniTree_allmuons->Fill();
				}
				for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
					TRootPhoton *myphoton;
					myphoton = (TRootPhoton*) photons->At(iphoton);
					Pt_allPhotons = myphoton->Pt();
					Eta_allPhotons = myphoton->Eta();
					Phi_allPhotons = myphoton->Phi();
					isEBorEE_allPhotons = 1;
					if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
					if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
					if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
					if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
					isNotCommissionned = photonIsNotCommissioned[iphoton];
					miniTree_allphotons->Fill();
				}
				continue;
			}
			isAfterCutCSA07ID = 1;
			nAfterCutCSA07ID++;
		}

		// ZJET VETO
		if( zjet_veto ){
			bool MCphotons_from_muons_from_Z = false;
			bool MC_first_muon_in_phase_space = false;
			bool MC_second_muon_in_phase_space = false;
			bool MCsignal_in_phase_space = false;
			// ****
			// First loop: look for a photon
			for( int iMCparticle = 0 ; iMCparticle < mcParticles->GetEntries() ; iMCparticle++ ){
				TRootMCParticle *mcParticleCandidate = (TRootMCParticle *)mcParticles->At(iMCparticle);
				if( (mcParticleCandidate->status()==1) && (mcParticleCandidate->type() == 22) ){ // if the particle is a true MC photon
					if( abs(mcParticleCandidate->motherType()) == 13 ){// if the true MC photon origins from a muon
						if( abs(mcParticleCandidate->grannyType()) == 23 ){// photon coming from a muon coming from a Z
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
							if( abs(mcParticleCandidate->grannyType()) == 23 ){// muon is coming from a Z
								if( (mcParticleCandidate->Pt()>10.0) && (abs(mcParticleCandidate->Eta())<3.0) ){
									MC_first_muon_in_phase_space = true;
								}
							}
						}
					} // end of selecting first muon
					if( (MC_first_muon_in_phase_space == true) && (mcParticleCandidate->status()==1) && (abs(mcParticleCandidate->type()) == 13) ){// if the particle is a final state muon
            if( abs(mcParticleCandidate->motherType()) == 13 ){
              if( abs(mcParticleCandidate->grannyType()) == 23 ){// muon is coming from a Z
                if( (mcParticleCandidate->Pt()>10.0) && (abs(mcParticleCandidate->Eta())<3.0) ){
                 	MC_second_muon_in_phase_space = true;
									MCsignal_in_phase_space = true;
                }
              }
            }
          }// end of selecting second muon
				}
			}// end of loop over MC particles
			if(   MCsignal_in_phase_space ){ // ***** WARNING *****  veto currently normal to consider background
//			if( !  MCsignal_in_phase_space ){ // ***** WARNING *****  veto currently REVERSED to consider SIGNAL
				cerr<<"SAFE: photon(s) coming from muon, aborting event " << ievt << endl;
				miniTree->Fill();
				for(int imuon=0 ; imuon<NbMuons ; imuon++){
					TRootMuon *mymuon;
					mymuon = (TRootMuon*) muons->At(imuon);
					Pt_allMuons = mymuon->Pt();
					Eta_allMuons = mymuon->Eta();
					Phi_allMuons = mymuon->Phi();
					Charge_allMuons = mymuon->charge();
					miniTree_allmuons->Fill();
				}
				for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
					TRootPhoton *myphoton;
					myphoton = (TRootPhoton*) photons->At(iphoton);
					Pt_allPhotons = myphoton->Pt();
					Eta_allPhotons = myphoton->Eta();
					Phi_allPhotons = myphoton->Phi();
					isEBorEE_allPhotons = 1;
					if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
					if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
					if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
					if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
					isNotCommissionned = photonIsNotCommissioned[iphoton];
					miniTree_allphotons->Fill();
				}
				continue;
			}
			isAfterCutZJETVETO = 1;
			nAfterCutZJETVETO++;
		}// end of if Z+Jets veto


		// CUT 1a: nb of muons > 1
		if(!( NbMuonsIdentified>1 )){
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )" << " CUT at level I because "<< NbMuonsIdentified	<< " muons only" << endl;
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuons ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(imuon);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
				TRootPhoton *myphotonbis;
				myphotonbis = (TRootPhoton*) photons->At(iphoton);
				Pt_allPhotons = myphotonbis->Pt();
				Eta_allPhotons = myphotonbis->Eta();
				Phi_allPhotons = myphotonbis->Phi();
				isEBorEE_allPhotons = 1;
				if( myphotonbis->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphotonbis->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphotonbis->isEEPho()==1) && (myphotonbis->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphotonbis->isEEPho()==1) && (myphotonbis->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphotonbis->superCluster()->s4())/(myphotonbis->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[iphoton];
				miniTree_allphotons->Fill();
			}

			continue;
		}
		isAfterCut1a = 1;
		nAfterCut1a++;

		// CUT 1b: (nb of muons with |eta| < 2.4) > 1
		vector<int> muonsValidEta;
		muonsValidEta.clear();
		TRootMuon *muonValidEtaCandidate;
		for(int imuon=0 ; imuon<NbMuonsIdentified ; imuon++){
			muonValidEtaCandidate = (TRootMuon*) muons->At(muonIdentified[imuon]);
			if( fabs(muonValidEtaCandidate->Eta())<2.4 ){
				muonsValidEta.push_back(muonIdentified[imuon]);
			}
		}
		unsigned int NbMuonsValidEta = muonsValidEta.size();

		if(!( NbMuonsValidEta>1 )) {
			miniTree->Fill();
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )" << " CUT at level I because of bad muons (eta)" << endl;
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(iphoton);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[iphoton];
				miniTree_allphotons->Fill();
			}
			continue;
		}
		isAfterCut1b = 1;
		nAfterCut1b++;

		// CUT 1c: two muons with correct eta AND with opposite charge
		TRootMuon *MPtMuon = (TRootMuon*) muons->At(muonsValidEta[0]);
		TRootMuon *SecondMPtMuon = (TRootMuon*) muons->At(muonsValidEta[1]);
		double PtMuon = MPtMuon->Pt();
		int imuonValidEtaMPt = 0;
		TRootMuon *MPtMuonCandidate;
		for(int imuon=1 ; imuon<NbMuonsValidEta ; imuon++){
			MPtMuonCandidate = (TRootMuon*) muons->At(muonsValidEta[imuon]);
			if(MPtMuonCandidate->Pt() > PtMuon){
				MPtMuon = MPtMuonCandidate;
				SecondMPtMuon = MPtMuon;
				PtMuon = MPtMuon->Pt();
				imuonValidEtaMPt = imuon;
			}
		}
		TRootMuon *MPtMuon_oppositeCharge;
		double PtMuon_oppositeCharge = 0.0;
		bool isThereOppositeCharge = false;
		for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
			TRootMuon *MPtMuon_oppositeChargeCandidate;
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
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )" << " CUT at level I because of bad muons (charge)" << endl;
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(iphoton);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[iphoton];
				miniTree_allphotons->Fill();
			}
			continue;
		}
		isAfterCut1c = 1;
		nAfterCut1c++;

		TRootMuon *leadingMuon;
		TRootMuon *subleadingMuon;
		leadingMuon = (TRootMuon*) MPtMuon;
		subleadingMuon	= (TRootMuon*) MPtMuon_oppositeCharge;
//		subleadingMuon	= (TRootMuon*) SecondMPtMuon;
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


		// CUT 1d: two muons with correct eta with opposite charge AND pT>10 GeV
		if(!( ((PtMuon>10.0) && (PtMuon_oppositeCharge>10.0)) && ((PtMuon>15.0) || (PtMuon_oppositeCharge>15.0)) )){
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )" << " CUT at level I because of bad muons (ptmu1= " << PtMuon << " GeV; ptmu2= " << PtMuon_oppositeCharge << " GeV)" << endl;
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(iphoton);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[iphoton];
				miniTree_allphotons->Fill();
			}
			continue;
		}
		isAfterCut1d = 1;
		nAfterCut1d++;

		// CUT 1e: dimuon invariant mass >= 20 GeV
		if(!( mumuInvMass >= 20.0 )){
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )" << " CUT at level I because of m(mumu)= " << mumuInvMass << " GeV" << endl;
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(iphoton);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[iphoton];
				miniTree_allphotons->Fill();
			}
			continue;
		}
		isAfterCut1e = 1;
		nAfterCut1e++;

		// CUT 2a: nb of photons > 0
		if(!( NbPhotonsNoSpike>0 )){
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )" << " CUT at level II because "<<	NbPhotonsNoSpike	<< " photon" << endl;
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(iphoton);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[iphoton];
				miniTree_allphotons->Fill();
			}
			continue;
		}
		isAfterCut2a = 1;
		nAfterCut2a++;

		// CUT 2b: one photon with |eta| < 2.5 and pT>10GeV AND no spike
		unsigned int NbPhotonsValidEta = 0;
		vector<int> photonsValidEta;
		photonsValidEta.clear();
		TRootPhoton *photonValidEtaCandidate;
		for(int iphoton=0 ; iphoton<NbPhotonsNoSpike ; iphoton++){
			photonValidEtaCandidate = (TRootPhoton*) photons->At(photonsNoSpike[iphoton]);
			cerr << "\t\tINFO: Photon " << photonsNoSpike[iphoton] << "\tPt= " << photonValidEtaCandidate->Pt() << "\tEta= " << photonValidEtaCandidate->Eta() << endl;
			if( (photonValidEtaCandidate->Pt()>10.0) && (fabs(photonValidEtaCandidate->Eta())<2.5) ){
//			if( (photonValidEtaCandidate->Pt()>0.0) && (fabs(photonValidEtaCandidate->Eta())<2.5) ){ // FIXME
				photonsValidEta.push_back(photonsNoSpike[iphoton]);
			}
		}
		NbPhotonsValidEta = photonsValidEta.size();
		if(!( NbPhotonsValidEta>0 )){
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )" << " CUT at level II because of bad photon" << endl;
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotonsValidEta ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[photonsValidEta[iphoton]];
				miniTree_allphotons->Fill();
			}
			continue;
		}
		isAfterCut2b = 1;
		nAfterCut2b++;

		// GET most energetic photon
		TRootPhoton *MPtPhoton;
		MPtPhoton = (TRootPhoton*) photons->At(photonsValidEta[0]);
		double PtPhoton = MPtPhoton->Pt();
		for(int iphoton=0 ; iphoton<NbPhotonsValidEta ; iphoton++){
			TRootPhoton *MPtPhotonCandidate;
			MPtPhotonCandidate = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
			if(MPtPhotonCandidate->Pt() > PtPhoton){
				MPtPhoton = MPtPhotonCandidate;
				PtPhoton = MPtPhoton->Pt();
			}
		}
		// FILL THE MINITREE
		Photon_Eta = MPtPhoton->Eta();
		Photon_Phi = MPtPhoton->Phi();
		if( MPtPhoton->isEBPho() ){ Photon_isEB=1; } else { Photon_isEB=0; }
		if( MPtPhoton->isEEPho() ){ Photon_isEE=1; } else { Photon_isEE=0; }
		if( MPtPhoton->isEEPho() && MPtPhoton->Eta()<0 ){ Photon_isEEM=1; } else { Photon_isEEM=0; }
		if( MPtPhoton->isEEPho() && MPtPhoton->Eta()>0 ){ Photon_isEEP=1; } else { Photon_isEEP=0; }
		Photon_hasPixelSeed = MPtPhoton->hasPixelSeed();
		Photon_isAlsoElectron = MPtPhoton->isAlsoElectron();
		Photon_Nclusters = MPtPhoton->nbClusters();
//		cout << "MPtPhoton->superCluster()=" << MPtPhoton->superCluster() << endl; // FIXME
//		Photon_nBasicClusters = MPtPhoton->superCluster()->nBasicClusters();
		Photon_isTightPhoton = MPtPhoton->isTightPhoton();
		Photon_isLoosePhoton = MPtPhoton->isLoosePhoton();
		Photon_convNTracks = MPtPhoton->convNTracks();
		Photon_E = MPtPhoton->Energy();
		Photon_Et = MPtPhoton->Et();
		Photon_E2x2 = MPtPhoton->e2x2();
		Photon_E3x3 = MPtPhoton->e3x3();
		Photon_E5x5 = MPtPhoton->e5x5();
		Photon_Emax = MPtPhoton->eMax();
		Photon_E2nd = MPtPhoton->e2nd();
		Photon_r19 = MPtPhoton->r19();
		Photon_r9 = MPtPhoton->r9();
//FIXME		Photon_cross = 1-((MPtPhoton->superCluster()->s4())/(MPtPhoton->superCluster()->eMax()));		
		Photon_caloConeSize = MPtPhoton->caloConeSize();
		Photon_PreshEnergy = MPtPhoton->preshowerEnergy();
		Photon_HoE = MPtPhoton->hoe();
		Photon_sigmaEtaEta = MPtPhoton->sigmaEtaEta();
    Photon_sigmaIetaIeta = MPtPhoton->sigmaIetaIeta();
		Photon_covEtaEta = MPtPhoton->covEtaEta();
		Photon_covPhiPhi = MPtPhoton->covPhiPhi();
		Photon_covEtaPhi = MPtPhoton->covEtaPhi();
//FIXME		Photon_etaWidth = MPtPhoton->superCluster()->etaWidth();
//FIXME		Photon_phiWidth = MPtPhoton->superCluster()->phiWidth();
		Photon_dR03isoEcalRecHit = MPtPhoton->dR03IsolationEcalRecHit();
		Photon_dR03isoHcalRecHit = MPtPhoton->dR03IsolationHcalRecHit();
		Photon_dR03isoSolidTrkCone = MPtPhoton->dR03IsolationSolidTrkCone();
		Photon_dR03isoHollowTrkCone = MPtPhoton->dR03IsolationHollowTrkCone();
		Photon_dR03isoNTracksSolidCone = MPtPhoton->dR03IsolationNTracksSolidCone();
		Photon_dR03isoNTracksHollowCone = MPtPhoton->dR03IsolationNTracksHollowCone();
		Photon_dR04isoEcalRecHit = MPtPhoton->dR04IsolationEcalRecHit();
		Photon_dR04isoHcalRecHit = MPtPhoton->dR04IsolationHcalRecHit();
		Photon_dR04isoSolidTrkCone = MPtPhoton->dR04IsolationSolidTrkCone();
		Photon_dR04isoHollowTrkCone = MPtPhoton->dR04IsolationHollowTrkCone();
		Photon_dR04isoNTracksSolidCone = MPtPhoton->dR04IsolationNTracksSolidCone();
		Photon_dR04isoNTracksHollowCone = MPtPhoton->dR04IsolationNTracksHollowCone();
//FIXME		Photon_seedTime = MPtPhoton->superCluster()->hitAt(MPtPhoton->superCluster()->nRecHits()-1)->time();
//FIXME		Photon_seedFlag = MPtPhoton->superCluster()->hitAt(MPtPhoton->superCluster()->nRecHits()-1)->recoFlag();


		// ********************************************************************
		// *** Compute mumugamma invariant mass ***
		// ********************************************************************
		TLorentzVector mumugamma;
		mumugamma = (*leadingMuon) + (*subleadingMuon) + (*MPtPhoton);
		double mumugammaInvMass = mumugamma.M();
		mumugamma.Clear();
		cerr << "\t\tINFO: mumugamma invariant mass : Mmumugamma = " << mumugammaInvMass << endl;
		Mmumugamma = mumugammaInvMass;

		double phiPhoton = MPtPhoton->Phi();
		double etaPhoton = MPtPhoton->Eta();
		double phiMuon = MPtMuon->Phi();
		double etaMuon = MPtMuon->Eta();
		double phiMuon_oppositeCharge = MPtMuon_oppositeCharge->Phi();
		double etaMuon_oppositeCharge = MPtMuon_oppositeCharge->Eta();

		double deltaRPM	= DeltaR(etaPhoton, phiPhoton, etaMuon, phiMuon);
		double deltaRPAM = DeltaR(etaPhoton, phiPhoton, etaMuon_oppositeCharge, phiMuon_oppositeCharge);

		double deltaRmin;
		TRootMuon *farMuon;
		TRootMuon *nearMuon;
		TRootMuon *minusMuon;
		TRootMuon *plusMuon;

		if(deltaRPM < deltaRPAM){
			deltaRmin = deltaRPM;
			farMuon	= (TRootMuon*) MPtMuon_oppositeCharge;
			nearMuon = (TRootMuon*) MPtMuon;
		} else {
			deltaRmin = deltaRPAM;
			farMuon	= (TRootMuon*) MPtMuon;
			nearMuon = (TRootMuon*) MPtMuon_oppositeCharge;
		}
		if( MPtMuon->charge()>0 ){
			plusMuon	= (TRootMuon*) MPtMuon;
			minusMuon = (TRootMuon*) MPtMuon_oppositeCharge;
		} else {
			minusMuon = (TRootMuon*) MPtMuon;
			plusMuon	= (TRootMuon*) MPtMuon_oppositeCharge;
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
	
		// CUT 2c: DeltaR(photon, close muon) >= 0.05
		if(!( deltaRmin>=0.00 )){
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )"	<< " CUT at level II for Photons (deltar= " << deltaRmin << " )" << endl;
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotonsValidEta ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[photonsValidEta[iphoton]];
				miniTree_allphotons->Fill();
			}
				continue;
		}
		isAfterCut2c = 1;
		nAfterCut2c++;


		// CUT 3: 40GeV <= dimuon invariant mass <= 80GeV
		if(!( (mumuInvMass>=40.0)&&(mumuInvMass<=80.0) )){
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )"	<< " CUT at level III for Drell-Yan: mumuInvMass= " << mumuInvMass << " GeV" << endl;
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotonsValidEta ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[photonsValidEta[iphoton]];
				miniTree_allphotons->Fill();
			}
				continue;
		}
		isAfterCut3 = 1;
		nAfterCut3++;

		// CUT 4: photon_Et >= 10 GeV && DeltaR(photon, close muon)<=0.8
		if(!( (MPtPhoton->Et()>=10.0)&&(deltaRmin<=0.8) )){
			if( !(MPtPhoton->Et()>=10.0) ){
				cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )"	<< " CUT at level IV for gamma momentum: MPtPhoton->Et()= " << MPtPhoton->Et() << " GeV" << endl;
			} else if(!(deltaRmin<=0.8)) {
				cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )"	<< " CUT at level IV for large deltar: deltaRmin= " << deltaRmin << endl;
			}
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotonsValidEta ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[photonsValidEta[iphoton]];
				miniTree_allphotons->Fill();
			}
				continue;
		}
		isAfterCut4 = 1;
		nAfterCut4++;

		// CUT 5: 87.2GeV <= mumugamma invariant mass <= 95.2GeV *** *** *** 70GeV <= mumugamma invariant mass <= 110GeV
		bool cutMuMuGammaWindow = false;
		if(signal){
			cutMuMuGammaWindow = (mumugammaInvMass >=87.2) && (mumugammaInvMass <=95.2);} // in case of signal
		else {
			cutMuMuGammaWindow = (mumugammaInvMass >=70.0) && (mumugammaInvMass <=110.0);} // in case of background
		if(!( cutMuMuGammaWindow )){
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )"	<< " CUT at level V for Z Mass Window: mumugammaInvMass= " << mumugammaInvMass << " GeV" << endl;
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotonsValidEta ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[photonsValidEta[iphoton]];
				miniTree_allphotons->Fill();
			}
				continue;
		}
		isAfterCut5 = 1;
		nAfterCut5++;
	
		// CUT 6: farMuon->isoR03_emEt() <= 1.0
		if(!( farMuon->isoR03_emEt()<=1.0 )) {
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )"	<< " CUT at level VI for large emEt: farMuon->isoR03_emEt()= " << farMuon->isoR03_emEt() << " GeV" << endl;
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotonsValidEta ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[photonsValidEta[iphoton]];
				miniTree_allphotons->Fill();
			}
				continue;
		}
		isAfterCut6 = 1;
		nAfterCut6++;

		// CUT 7: farMuon->Pt() >= 30.0
		if(!( farMuon->Pt()>=30.0 )) {
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )"	<< " CUT at level VII for soft far muon: farMuon->Pt()= " << farMuon->Pt() << " GeV" << endl;
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotonsValidEta ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[photonsValidEta[iphoton]];
				miniTree_allphotons->Fill();
			}
				continue;
		}
		isAfterCut7 = 1;
		nAfterCut7++;

		// CUT 8: nearMuon->isoR03_hadEt() < 1.0
		if(!( nearMuon->isoR03_hadEt()<1.0 )){
			cerr << "\tCUT: event " << ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )"	<< " CUT at level VIII for large hadEt: nearMuon->isoR03_hadEt()= " << nearMuon->isoR03_hadEt() << " GeV" << endl;
			miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotonsValidEta ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[photonsValidEta[iphoton]];
				miniTree_allphotons->Fill();
			}
				continue;
		}
		isAfterCut8 = 1;
		nAfterCut8++;
		isAfterCut9 = 1;
		nAfterCut9++;
		isAfterCut10 = 1;
		nAfterCut10++;
		isSelected = 1;
		nSelected++;
		cerr << "OK: Surviving veto event: "<< ievt << " ( " << iRunID << " , " << iLumiID << " , " << iEventID << " )"  << endl;
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



		miniTree->Fill();
			for(int imuon=0 ; imuon<NbMuonsValidEta ; imuon++){
				TRootMuon *mymuon;
				mymuon = (TRootMuon*) muons->At(muonsValidEta[imuon]);
				Pt_allMuons = mymuon->Pt();
				Eta_allMuons = mymuon->Eta();
				Phi_allMuons = mymuon->Phi();
				Charge_allMuons = mymuon->charge();
				miniTree_allmuons->Fill();
			}
			for(int iphoton=0 ; iphoton<NbPhotonsValidEta ; iphoton++){
				TRootPhoton *myphoton;
				myphoton = (TRootPhoton*) photons->At(photonsValidEta[iphoton]);
				Pt_allPhotons = myphoton->Pt();
				Eta_allPhotons = myphoton->Eta();
				Phi_allPhotons = myphoton->Phi();
				isEBorEE_allPhotons = 1;
				if( myphoton->isEBPho()==1 ){ isEB_allPhotons=1; } else { isEB_allPhotons=0; }
				if( myphoton->isEEPho()==1 ){ isEE_allPhotons=1; } else { isEE_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()<0) ){ isEEM_allPhotons=1; } else { isEEM_allPhotons=0; }
				if( (myphoton->isEEPho()==1) && (myphoton->Eta()>0) ){ isEEP_allPhotons=1; } else { isEEP_allPhotons=0; }
				Cross_allPhotons = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));
				isNotCommissionned = photonIsNotCommissioned[photonsValidEta[iphoton]];
				miniTree_allphotons->Fill();
			}
			outputEventTree->Fill();
	} // fin boucle sur evts

	cout << endl << "**************************************************************************" << endl;
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
	cout << "nAfterCut1a=" << "\t\t" << nAfterCut1a << "\t\t" << (double)nAfterCut1a/(double)nBeforeAllCuts*100.0 << "\t\t" << (double)nAfterCut1a/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut1b=" << "\t\t" << nAfterCut1b << "\t\t" << (double)nAfterCut1b/(double)nAfterCut1a*100.0 << "\t\t" << (double)nAfterCut1b/(double)nBeforeAllCuts*100.0 << endl;
	cout << "nAfterCut1c=" << "\t\t" << nAfterCut1c << "\t\t" << (double)nAfterCut1c/(double)nAfterCut1b*100.0 << "\t\t" << (double)nAfterCut1c/(double)nBeforeAllCuts*100.0 << endl;
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

	outputEventTree->AutoSave();
	
	OutputRootFile->cd();
	OutputRootFile->Write();
	OutputRootFile->Close();

	OutputRootFile->Clear();
	inputEventTree->Clear();

	return 0;
}
