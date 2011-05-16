
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
//#pragma optimize 0

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


using namespace std;

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

void doGenInfo(TRootParticle* myparticle, TClonesArray* mcParticles, float* particule_trueE, float* particule_truePx, float* particule_truePy, float* particule_truePz, float* particule_trueEta, float* particule_truePhi, int particle_pdgId = 0)
{
  TRootMCParticle* mygenparticle;
  int NbMCpartInCone=0;
  double bestPtdiff=500.0;
  int igpsl=-1;
  for (int igp=0; igp<mcParticles->GetEntriesFast(); igp++) {
    mygenparticle = (TRootMCParticle*) mcParticles->At(igp);
    //cout<<endl<<"deltaR = "<<DeltaR(mygenparticle->Eta(), mygenparticle->Phi(), myparticle->Eta(), myparticle->Phi())<<endl;
    //cout<<"mygenparticle->Mag() = "<<mygenparticle->Mag()<<endl;
    if (DeltaR(mygenparticle->Eta(), mygenparticle->Phi(), myparticle->Eta(), myparticle->Phi())<0.3){
      if ( (mygenparticle->status()==1) && ( (particle_pdgId==0)?true:((mygenparticle->type())==particle_pdgId) ) ){
        //HistoMCpartStatus1InConeId->Fill(mygenparticle->type());
        NbMCpartInCone++;
        if (fabs( (mygenparticle->Pt()) - (myparticle->Pt()) )<bestPtdiff){
          bestPtdiff=fabs(mygenparticle->Pt()-myparticle->Pt());
          igpsl=igp;
        }
      }
    }
  }
  if (igpsl!=-1){
    mygenparticle = (TRootMCParticle*) mcParticles->At(igpsl);
    *particule_trueE = mygenparticle->Energy();
    *particule_truePx = mygenparticle->Px();
    *particule_truePy = mygenparticle->Py();
    *particule_truePz = mygenparticle->Pz();
    *particule_truePhi = mygenparticle->Phi();
    *particule_trueEta = mygenparticle->Eta();

  }
  return;
}

float fEta(float eta) 
{

  
  float ieta = fabs(eta)*(5/0.087);
  float p0 = 40.2198;  // should be 40.2198
  float p1 = -3.03103e-6;  // should be -3.03103e-6
  float feta = 1; 

  if ( ieta < p0 || fabs(eta) > 1.4442) feta = 1.0; 
  else feta = 1.0/(1.0 + p1*(ieta-p0)*(ieta-p0));

  //correctedEnergy = energy/(1.0 + p1*(ieta-p0)*(ieta-p0));
  return feta;

}

int main(int argc, char *argv[]);

  // ____________________________________________
  // Event information
  // ____________________________________________
  extern Int_t iEvent, iEventID, iLumiID, iRunID;
  extern Int_t isSignalApplied, isStewApplied, isZJetsApplied;

  extern Int_t isBeforeAllCuts, isAfterCutPthatFilter, isAfterCutZJETVETO;
  extern Int_t isLooseMMG, isTightMMG, isMM, isAfterCut1d, isAfterCut1e;
  extern Int_t isAfterCut2a, isAfterCut2b, isAfterCut2c;
  extern Int_t isAfterCut3, isAfterCut4, isAfterCut5, isAfterCut6, isAfterCut7, isAfterCut8, isAfterCut9, isAfterCut10;
  extern Int_t isSelected;

  extern Int_t isNotCommissionned;
  
  extern Int_t Muon_eventPassHLT_Mu11;
  extern Int_t nVertices;

  // ____________________________________________
  // Muon variables 
  // ____________________________________________
  extern Int_t NbMuons;
  
  extern Float_t Pt_allMuons, Eta_allMuons, Phi_allMuons, Charge_allMuons;
// (M minus charge, P plus charge), (F far, N near), (L leading, S subleading)
  extern Float_t MuonM_Pt, MuonP_Pt, MuonN_Pt, MuonF_Pt, MuonL_Pt, MuonS_Pt;
  extern Float_t MuonM_Eta, MuonP_Eta, MuonN_Eta, MuonF_Eta, MuonL_Eta, MuonS_Eta;
  extern Float_t MuonM_Phi, MuonP_Phi, MuonN_Phi, MuonF_Phi, MuonL_Phi, MuonS_Phi;
  extern Int_t MuonF_Charge, MuonN_Charge, MuonL_Charge, MuonS_Charge;

  extern Float_t MuonM_isoR03_emEt, MuonP_isoR03_emEt, MuonN_isoR03_emEt, MuonF_isoR03_emEt, MuonL_isoR03_emEt, MuonS_isoR03_emEt; 
  extern Float_t MuonM_isoR03_hadEt, MuonP_isoR03_hadEt, MuonN_isoR03_hadEt, MuonF_isoR03_hadEt, MuonL_isoR03_hadEt, MuonS_isoR03_hadEt;
  extern Float_t MuonM_isoR03_hoEt, MuonP_isoR03_hoEt, MuonN_isoR03_hoEt, MuonF_isoR03_hoEt, MuonL_isoR03_hoEt, MuonS_isoR03_hoEt;   
  extern Float_t MuonM_isoR03_nJets, MuonP_isoR03_nJets, MuonN_isoR03_nJets, MuonF_isoR03_nJets, MuonL_isoR03_nJets, MuonS_isoR03_nJets;
  extern Float_t MuonM_isoR03_nTracks, MuonP_isoR03_nTracks, MuonN_isoR03_nTracks, MuonF_isoR03_nTracks, MuonL_isoR03_nTracks, MuonS_isoR03_nTracks;
  extern Float_t MuonM_isoR03_sumPt, MuonP_isoR03_sumPt, MuonN_isoR03_sumPt, MuonF_isoR03_sumPt, MuonL_isoR03_sumPt, MuonS_isoR03_sumPt;
    
  extern Float_t MuonM_isoR05_emEt, MuonP_isoR05_emEt, MuonN_isoR05_emEt, MuonF_isoR05_emEt, MuonL_isoR05_emEt, MuonS_isoR05_emEt;
  extern Float_t MuonM_isoR05_hadEt, MuonP_isoR05_hadEt, MuonN_isoR05_hadEt, MuonF_isoR05_hadEt, MuonL_isoR05_hadEt, MuonS_isoR05_hadEt;
  extern Float_t MuonM_isoR05_hoEt, MuonP_isoR05_hoEt, MuonN_isoR05_hoEt, MuonF_isoR05_hoEt, MuonL_isoR05_hoEt, MuonS_isoR05_hoEt;
  extern Float_t MuonM_isoR05_nJets, MuonP_isoR05_nJets, MuonN_isoR05_nJets, MuonF_isoR05_nJets, MuonL_isoR05_nJets, MuonS_isoR05_nJets;
  extern Float_t MuonM_isoR05_nTracks, MuonP_isoR05_nTracks, MuonN_isoR05_nTracks, MuonF_isoR05_nTracks, MuonL_isoR05_nTracks, MuonS_isoR05_nTracks;
  extern Float_t MuonM_isoR05_sumPt, MuonP_isoR05_sumPt, MuonN_isoR05_sumPt, MuonF_isoR05_sumPt, MuonL_isoR05_sumPt, MuonS_isoR05_sumPt;

  // ____________________________________________
  // Photon variables
  // ___________________________________________
  extern Int_t NbPhotons;
  extern Float_t Pt_allPhotons, Eta_allPhotons, Phi_allPhotons, Cross_allPhotons;
  extern Int_t isEBorEE_allPhotons, isEB_allPhotons, isEE_allPhotons, isEEP_allPhotons, isEEM_allPhotons;
  extern Float_t Photon_Eta, Photon_Phi;
  extern Int_t Photon_isEBorEE, Photon_isEB, Photon_isEE, Photon_isEEP, Photon_isEEM;

  extern Int_t Photon_hasPixelSeed, Photon_isAlsoElectron, Photon_Nclusters, Photon_nBasicClusters, Photon_nXtals;
  extern Int_t Photon_isTightPhoton, Photon_isLoosePhoton;
  extern Int_t Photon_convNTracks;
  extern Float_t Photon_E, Photon_Et, Photon_E2x2, Photon_E3x3, Photon_E5x5, Photon_Emax, Photon_E2nd;
  extern Float_t Photon_r19, Photon_r9, Photon_cross;
  extern Float_t Photon_caloConeSize, Photon_PreshEnergy, Photon_HoE;
  extern Float_t Photon_sigmaEtaEta, Photon_sigmaIetaIeta;
  extern Float_t Photon_covEtaEta, Photon_covPhiPhi, Photon_covEtaPhi;
  extern Float_t Photon_etaWidth, Photon_phiWidth;
  extern Float_t Photon_dR03isoEcalRecHit, Photon_dR03isoHcalRecHit, Photon_dR03isoSolidTrkCone, Photon_dR03isoHollowTrkCone, Photon_dR03isoNTracksSolidCone, Photon_dR03isoNTracksHollowCone;
  extern Float_t Photon_dR04isoEcalRecHit, Photon_dR04isoHcalRecHit, Photon_dR04isoSolidTrkCone, Photon_dR04isoHollowTrkCone, Photon_dR04isoNTracksSolidCone, Photon_dR04isoNTracksHollowCone;
  extern Float_t Photon_seedTime, Photon_seedFlag;
  extern Int_t Photon_seedPosition1, Photon_seedPosition2;
  extern Float_t Photon_SC_Eta, Photon_SC_Phi, Photon_SC_brem;
  extern Float_t Photon_SC_E, Photon_SC_Et, Photon_SC_rawE, Photon_SC_rawEt;

  // ____________________________________________
  // mugamma / mumu / mumugamma information
  // ____________________________________________

  extern Float_t Mmumu, Mmumugamma, Mmumugamma_5x5, Mmumugamma_SC, Mmumugamma_SCraw, Mmumugamma_SCraw_fEta;
  extern Float_t Ptmumu;
  extern Float_t deltaRNear, deltaRFar, deltaRMinus, deltaRPlus, deltaRLeading, deltaRSubleading;
  extern Float_t mmg_k, mmg_ik, mmg_s, mmg_logk, mmg_logik, mmg_logs;
  extern Float_t mmg_k_5x5, mmg_ik_5x5, mmg_s_5x5, mmg_logk_5x5, mmg_logik_5x5, mmg_logs_5x5;
  extern Float_t mmg_k_SC, mmg_ik_SC, mmg_s_SC, mmg_logk_SC, mmg_logik_SC, mmg_logs_SC;
  extern Float_t mmg_k_SCraw, mmg_ik_SCraw, mmg_s_SCraw, mmg_logk_SCraw, mmg_logik_SCraw, mmg_logs_SCraw;
  extern Float_t mmg_k_SCraw_fEta, mmg_ik_SCraw_fEta, mmg_s_SCraw_fEta, mmg_logk_SCraw_fEta, mmg_logik_SCraw_fEta, mmg_logs_SCraw_fEta;

  // ____________________________________________
  // MC Truth
  // ___________________________________________

  extern Float_t Photon_MC_E, Photon_MC_Px, Photon_MC_Py, Photon_MC_Pz, Photon_MC_Phi, Photon_MC_Eta;
  extern Float_t MuonM_MC_E, MuonM_MC_Px, MuonM_MC_Py, MuonM_MC_Pz, MuonM_MC_Phi, MuonM_MC_Eta;
  extern Float_t MuonP_MC_E, MuonP_MC_Px, MuonP_MC_Py, MuonP_MC_Pz, MuonP_MC_Phi, MuonP_MC_Eta;
  extern Float_t MuonN_MC_E, MuonN_MC_Px, MuonN_MC_Py, MuonN_MC_Pz, MuonN_MC_Phi, MuonN_MC_Eta;
  extern Float_t MuonF_MC_E, MuonF_MC_Px, MuonF_MC_Py, MuonF_MC_Pz, MuonF_MC_Phi, MuonF_MC_Eta;
  extern Float_t MuonL_MC_E, MuonL_MC_Px, MuonL_MC_Py, MuonL_MC_Pz, MuonL_MC_Phi, MuonL_MC_Eta;
  extern Float_t MuonS_MC_E, MuonS_MC_Px, MuonS_MC_Py, MuonS_MC_Pz, MuonS_MC_Phi, MuonS_MC_Eta;

  extern Float_t Mmumu_Photon_MC, Mmumugamma_Photon_MC, mmg_k_Photon_MC, mmg_ik_Photon_MC, mmg_s_Photon_MC, mmg_logk_Photon_MC, mmg_logik_Photon_MC, mmg_logs_Photon_MC;
  extern Float_t Mmumu_Muons_MC, Mmumugamma_Muons_MC, mmg_k_Muons_MC, mmg_ik_Muons_MC, mmg_s_Muons_MC, mmg_logk_Muons_MC, mmg_logik_Muons_MC, mmg_logs_Muons_MC;
  extern Float_t Mmumu_MMG_MC, Mmumugamma_MMG_MC, mmg_k_MMG_MC, mmg_ik_MMG_MC, mmg_s_MMG_MC, mmg_logk_MMG_MC, mmg_logik_MMG_MC, mmg_logs_MMG_MC;



int FillMMG(TRootPhoton* myphoton, TRootMuon* mymuon1, TRootMuon* mymuon2, double EScale, bool doMC, TClonesArray* mcParticles){

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
      if( (mymuon1->Pt()) > (mymuon2->Pt()) )      {
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
      Ptmumu = mumu.Pt();
      double mumuInvMass = mumu.M();
//      cerr << "\t\tINFO: Dimuon invariant mass : Mmumu = " << mumuInvMass << endl;
////      mumu.Clear();
      Mmumu = mumuInvMass;

    // ********************************************************************
    // *** Compute mumugamma invariant mass ***
    // ********************************************************************
    // Re-compute modified photon momentum so as to keep m_photon = 0
    Double_t Px_SC, Px_5x5, Px_SCraw, Px_SCraw_fEta;
    Double_t Py_SC, Py_5x5, Py_SCraw, Py_SCraw_fEta;
    Double_t Pz_SC, Pz_5x5, Pz_SCraw, Pz_SCraw_fEta;
    Px_SC = Px_5x5 = Px_SCraw = Px_SCraw_fEta = 0.0;
    Py_SC = Py_5x5 = Py_SCraw = Py_SCraw_fEta = 0.0;
    Pz_SC = Pz_5x5 = Pz_SCraw = Pz_SCraw_fEta = 0.0;

    Px_SC = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->Mag());
    Py_SC = (myphoton->Py()) / (myphoton->Energy()) * (myphoton->superCluster()->Mag());
    Pz_SC = (myphoton->Pz()) / (myphoton->Energy()) * (myphoton->superCluster()->Mag());

    Px_5x5 = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->e5x5());
    Py_5x5 = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->e5x5());
    Pz_5x5 = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->e5x5());

    Px_SCraw = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy());
    Py_SCraw = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy());
    Pz_SCraw = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy());

    Px_SCraw_fEta = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta));
    Py_SCraw_fEta = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta));
    Pz_SCraw_fEta = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta));

    TLorentzVector mumugamma;
    TLorentzVector mumuSC;
    TLorentzVector mumu5x5;
    TLorentzVector mumuSC_raw;
    TLorentzVector mumuSC_raw_fEta;

    TLorentzVector *PhotonEScale = new TLorentzVector( EScale*(myphoton->Px()), EScale*(myphoton->Py()), EScale*(myphoton->Pz()), EScale*(myphoton->Energy()));
    TLorentzVector *PhotonSC = new TLorentzVector( EScale*Px_SC, EScale*Py_SC, EScale*Pz_SC, EScale*(myphoton->superCluster()->Mag()) );
    TLorentzVector *Photon5x5 = new TLorentzVector(EScale*Px_5x5 , EScale*Py_5x5, EScale*Pz_5x5, EScale*(myphoton->e5x5()));
    TLorentzVector *PhotonSC_raw = new TLorentzVector(EScale*Px_SCraw , EScale*Py_SCraw, EScale*Pz_SCraw, EScale*(myphoton->superCluster()->rawEnergy()));
    TLorentzVector *PhotonSC_raw_fEta = new TLorentzVector(EScale*Px_SCraw_fEta , EScale*Py_SCraw_fEta, EScale*Pz_SCraw_fEta, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta)));

//    mumugamma = (*leadingMuon) + (*subleadingMuon) + (*myphoton);
    mumugamma = (*leadingMuon) + (*subleadingMuon) + (*PhotonEScale);
    mumuSC = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC);
    mumu5x5 = (*leadingMuon) + (*subleadingMuon) + (*Photon5x5);
    mumuSC_raw = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw);
    mumuSC_raw_fEta = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta);
    double mumugammaInvMass = mumugamma.M();
    double mumuSCInvMass = mumuSC.M();
    double mumu5x5InvMass = mumu5x5.M();
    double mumuSC_rawInvMass = mumuSC_raw.M();
    double mumuSC_rawInvMass_fEta = mumuSC_raw_fEta.M();
    Mmumugamma = mumugammaInvMass;
    Mmumugamma_SC = mumuSCInvMass;
    Mmumugamma_5x5 = mumu5x5InvMass;
    Mmumugamma_SCraw = mumuSC_rawInvMass;
    Mmumugamma_SCraw_fEta = mumuSC_rawInvMass_fEta;
////    mumugamma.Clear();
////    mumuSC.Clear();
////    mumu5x5.Clear();
////    mumuSC_raw.Clear();
//    PhotonEScale->Clear();
//    PhotonSC->Clear();
//    Photon5x5->Clear();
//    PhotonSC_raw->Clear();
//    PhotonSC_raw_fEta->Clear();

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

    mmg_k_SCraw_fEta = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma_SCraw_fEta,2) - pow(Mmumu,2));
    mmg_ik_SCraw_fEta = (double)(pow(Mmumugamma_SCraw_fEta,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s_SCraw_fEta = mmg_ik_SCraw_fEta - 1.0;
    mmg_logk_SCraw_fEta = log(mmg_k_SCraw_fEta);
    mmg_logik_SCraw_fEta = log(mmg_ik_SCraw_fEta);
    mmg_logs_SCraw_fEta = log(mmg_s_SCraw_fEta);


//    cerr << "\t\tINFO: mumugamma invariant mass : Mmumugamma = " << mumugammaInvMass << endl;

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

    if( doMC )
    { // Compute Stuff, with MC truth information
      doGenInfo( (TRootParticle*) myphoton, mcParticles, &Photon_MC_E, &Photon_MC_Px, &Photon_MC_Py, &Photon_MC_Pz, &Photon_MC_Phi, &Photon_MC_Eta, 22 );
      doGenInfo( (TRootParticle*) minusMuon, mcParticles, &MuonM_MC_E, &MuonM_MC_Px, &MuonM_MC_Py, &MuonM_MC_Pz, &MuonM_MC_Phi, &MuonM_MC_Eta, 13 );
      doGenInfo( (TRootParticle*) plusMuon, mcParticles, &MuonP_MC_E, &MuonP_MC_Px, &MuonP_MC_Py, &MuonP_MC_Pz, &MuonP_MC_Phi, &MuonP_MC_Eta, -13 );
      doGenInfo( (TRootParticle*) nearMuon, mcParticles, &MuonN_MC_E, &MuonN_MC_Px, &MuonN_MC_Py, &MuonN_MC_Pz, &MuonN_MC_Phi, &MuonN_MC_Eta, (-1)*(nearMuon->charge())*13 );
      doGenInfo( (TRootParticle*) farMuon, mcParticles, &MuonF_MC_E, &MuonF_MC_Px, &MuonF_MC_Py, &MuonF_MC_Pz, &MuonF_MC_Phi, &MuonF_MC_Eta, (-1)*(farMuon->charge())*13 );
      doGenInfo( (TRootParticle*) leadingMuon, mcParticles, &MuonL_MC_E, &MuonL_MC_Px, &MuonL_MC_Py, &MuonL_MC_Pz, &MuonL_MC_Phi, &MuonL_MC_Eta, (-1)*(leadingMuon->charge())*13 );
      doGenInfo( (TRootParticle*) subleadingMuon, mcParticles, &MuonS_MC_E, &MuonS_MC_Px, &MuonS_MC_Py, &MuonS_MC_Pz, &MuonS_MC_Phi, &MuonS_MC_Eta, (-1)*(subleadingMuon->charge())*13 );

      TLorentzVector mumu_Photon_MC;
      TLorentzVector mumugamma_Photon_MC;
      TLorentzVector mumu_Muons_MC;
      TLorentzVector mumugamma_Muons_MC;
      TLorentzVector mumu_MMG_MC;
      TLorentzVector mumugamma_MMG_MC;

      TLorentzVector *PhotonMC = new TLorentzVector( Photon_MC_Px, Photon_MC_Py, Photon_MC_Pz, Photon_MC_E);
      TLorentzVector *MuonLMC = new TLorentzVector( MuonL_MC_Px, MuonL_MC_Py, MuonL_MC_Pz, MuonL_MC_E);
      TLorentzVector *MuonSMC = new TLorentzVector( MuonS_MC_Px, MuonS_MC_Py, MuonS_MC_Pz, MuonS_MC_E);

      TLorentzVector *PhotonEScale = new TLorentzVector( EScale*(myphoton->Px()), EScale*(myphoton->Py()), EScale*(myphoton->Pz()), EScale*(myphoton->Energy()));
      TLorentzVector *PhotonSC = new TLorentzVector( myphoton->Px(), myphoton->Py(), myphoton->Pz(), EScale*(myphoton->superCluster()->Mag()));
      TLorentzVector *Photon5x5 = new TLorentzVector( myphoton->Px(), myphoton->Py(), myphoton->Pz(), EScale*(myphoton->e5x5()));
      TLorentzVector *PhotonSC_raw = new TLorentzVector( myphoton->Px(), myphoton->Py(), myphoton->Pz(), EScale*(myphoton->superCluster()->rawEnergy()));

      mumu_Photon_MC = (*leadingMuon) + (*subleadingMuon);
      mumugamma_Photon_MC = (*leadingMuon) + (*subleadingMuon) + (*PhotonMC);
      mumu_Muons_MC = (*MuonLMC) + (*MuonSMC);
      mumugamma_Muons_MC = (*MuonLMC) + (*MuonSMC) + (*PhotonEScale);
      mumu_MMG_MC = (*MuonLMC) + (*MuonSMC);
      mumugamma_MMG_MC = (*MuonLMC) + (*MuonSMC) + (*PhotonMC);
      Mmumu_Photon_MC = mumu_Photon_MC.M();
      Mmumugamma_Photon_MC = mumugamma_Photon_MC.M();
      Mmumu_Muons_MC = mumu_Muons_MC.M();
      Mmumugamma_Muons_MC = mumugamma_Muons_MC.M();
      Mmumu_MMG_MC = mumu_MMG_MC.M();
      Mmumugamma_MMG_MC = mumugamma_MMG_MC.M();

      mmg_k_Photon_MC = (double)(pow(91.1876,2) - pow(Mmumu_Photon_MC,2) ) / (double)(pow(Mmumugamma_Photon_MC,2) - pow(Mmumu_Photon_MC,2));
      mmg_ik_Photon_MC = (double)(pow(Mmumugamma_Photon_MC,2) - pow(Mmumu_Photon_MC,2)) / (double)(pow(91.1876,2) - pow(Mmumu_Photon_MC,2) );
      mmg_s_Photon_MC = mmg_ik_Photon_MC -1.0;
      mmg_logk_Photon_MC = log(mmg_k_Photon_MC);
      mmg_logik_Photon_MC = log(mmg_ik_Photon_MC);
      mmg_logs_Photon_MC = log(mmg_s_Photon_MC);

      mmg_k_Muons_MC = (double)(pow(91.1876,2) - pow(Mmumu_Muons_MC,2) ) / (double)(pow(Mmumugamma_Muons_MC,2) - pow(Mmumu_Muons_MC,2));
      mmg_ik_Muons_MC = (double)(pow(Mmumugamma_Muons_MC,2) - pow(Mmumu_Muons_MC,2)) / (double)(pow(91.1876,2) - pow(Mmumu_Muons_MC,2) );
      mmg_s_Muons_MC = mmg_ik_Muons_MC -1.0;
      mmg_logk_Muons_MC = log(mmg_k_Muons_MC);
      mmg_logik_Muons_MC = log(mmg_ik_Muons_MC);
      mmg_logs_Muons_MC = log(mmg_s_Muons_MC);

      mmg_k_MMG_MC = (double)(pow(91.1876,2) - pow(Mmumu_MMG_MC,2) ) / (double)(pow(Mmumugamma_MMG_MC,2) - pow(Mmumu_MMG_MC,2));
      mmg_ik_MMG_MC = (double)(pow(Mmumugamma_MMG_MC,2) - pow(Mmumu_MMG_MC,2)) / (double)(pow(91.1876,2) - pow(Mmumu_MMG_MC,2) );
      mmg_s_MMG_MC = mmg_ik_MMG_MC -1.0;
      mmg_logk_MMG_MC = log(mmg_k_MMG_MC);
      mmg_logik_MMG_MC = log(mmg_ik_MMG_MC);
      mmg_logs_MMG_MC = log(mmg_s_MMG_MC);

//      Mmumu_Photon_MC = Mmumugamma_Photon_MC = mmg_k_Photon_MC = mmg_ik_Photon_MC = mmg_s_Photon_MC = mmg_logk_Photon_MC = mmg_logik_Photon_MC = mmg_logs_Photon_MC = -99.0;
//      Mmumu_Muons_MC = Mmumugamma_Muons_MC = mmg_k_Muons_MC = mmg_ik_Muons_MC = mmg_s_Muons_MC = mmg_logk_Muons_MC = mmg_logik_Muons_MC = mmg_logs_Muons_MC = -99.0;
//      Mmumu_MMG_MC = Mmumugamma_MMG_MC = mmg_k_MMG_MC = mmg_ik_MMG_MC = mmg_s_MMG_MC = mmg_logk_MMG_MC = mmg_logik_MMG_MC = mmg_logs_MMG_MC = -99.0;
//    PhotonMC->Clear();
//    MuonLMC->Clear();
//    MuonSMC->Clear();
//    PhotonEScale->Clear();
//    PhotonSC->Clear();
//    Photon5x5->Clear();
//    PhotonSC_raw->Clear();
    }// end doMC


////    myphoton->Clear();
////    mymuon1->Clear();
////    mymuon2->Clear();
////    farMuon->Clear();
////    nearMuon->Clear();
////    minusMuon->Clear();
////    plusMuon->Clear();
////    PhotonSC->Clear();
////    Photon5x5->Clear();
////    PhotonSC_raw->Clear();
////    leadingMuon->Clear();
////    subleadingMuon->Clear();


return 0;
}


