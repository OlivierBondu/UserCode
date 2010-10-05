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
#include <TF2.h>
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
#include <THStack.h>
#include <TLegendEntry.h>
#include <TMinuit.h>
#include <TPaveStats.h>

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


using namespace std;

double fonction_affine(double *x, double *par){
	return x[0]*par[0] - x[1]*par[1];
}

void DrawDataMCplot(TTree *Data_miniTree, TTree *QCD_Pt15_miniTree, TTree *QCD_Pt30_miniTree, TTree *QCD_Pt80_miniTree, TTree *QCD_Pt170_miniTree, TTree *QCD_Pt300_miniTree, TTree *QCD_Pt470_miniTree, TTree *PhotonJet_Pt15_miniTree, TTree *PhotonJet_Pt30_miniTree, TTree *PhotonJet_Pt80_miniTree, TTree *PhotonJet_Pt170_miniTree, TTree *PhotonJet_Pt300_miniTree, TTree *TTbarJets_Tauola_miniTree, TTree *WJets_7TeV_miniTree, TTree *ZJets_7TeV_miniTree, TTree *QCD_Mu_Pt20to30_miniTree, TTree *QCD_Mu_Pt30to50_miniTree, TTree *QCD_Mu_Pt50to80_miniTree, TTree *QCD_Mu_Pt80to120_miniTree, TTree *QCD_Mu_Pt120to170_miniTree, TTree *QCD_Mu_Pt170toInf_miniTree, TTree *InclusiveMu15_miniTree, TTree *FSR_ZmumuJet_Pt0to15_miniTree, TTree *FSR_ZmumuJet_Pt15to20_miniTree, TTree *FSR_ZmumuJet_Pt20to30_miniTree, TTree *FSR_ZmumuJet_Pt30to50_miniTree, TTree *FSR_ZmumuJet_Pt50to80_miniTree, TTree *FSR_ZmumuJet_Pt80to120_miniTree, TTree *FSR_ZmumuJet_Pt120to170_miniTree, TTree *FSR_ZmumuJet_Pt170to230_miniTree, TTree *FSR_ZmumuJet_Pt230to300_miniTree, TTree *FSR_ZmumuJet_Pt300toInf_miniTree, TTree *ISR_ZmumuJet_Pt0to15_miniTree, TTree *ISR_ZmumuJet_Pt15to20_miniTree, TTree *ISR_ZmumuJet_Pt20to30_miniTree, TTree *ISR_ZmumuJet_Pt30to50_miniTree, TTree *ISR_ZmumuJet_Pt50to80_miniTree, TTree *ISR_ZmumuJet_Pt80to120_miniTree, TTree *ISR_ZmumuJet_Pt120to170_miniTree, TTree *ISR_ZmumuJet_Pt170to230_miniTree, TTree *ISR_ZmumuJet_Pt230to300_miniTree, TTree *ISR_ZmumuJet_Pt300toInf_miniTree, string var, string pic, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1, bool doFit){

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

  // Get Histo_FSR_ZmumuJet_Pt0to15 from eventTree
  TH1F *Histo_FSR_ZmumuJet_Pt0to15_temp = new TH1F();
  string variable_FSR_ZmumuJet_Pt0to15 = var + ">>Histo_FSR_ZmumuJet_Pt0to15_temp" + limits;
  FSR_ZmumuJet_Pt0to15_miniTree->Draw(variable_FSR_ZmumuJet_Pt0to15.c_str(), cut.c_str());
  TH1F *Histo_FSR_ZmumuJet_Pt0to15 = (TH1F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt0to15_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt15to20 from eventTree
  TH1F *Histo_FSR_ZmumuJet_Pt15to20_temp = new TH1F();
  string variable_FSR_ZmumuJet_Pt15to20 = var + ">>Histo_FSR_ZmumuJet_Pt15to20_temp" + limits;
  FSR_ZmumuJet_Pt15to20_miniTree->Draw(variable_FSR_ZmumuJet_Pt15to20.c_str(), cut.c_str());
  TH1F *Histo_FSR_ZmumuJet_Pt15to20 = (TH1F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt15to20_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt20to30 from eventTree
  TH1F *Histo_FSR_ZmumuJet_Pt20to30_temp = new TH1F();
  string variable_FSR_ZmumuJet_Pt20to30 = var + ">>Histo_FSR_ZmumuJet_Pt20to30_temp" + limits;
  FSR_ZmumuJet_Pt20to30_miniTree->Draw(variable_FSR_ZmumuJet_Pt20to30.c_str(), cut.c_str());
  TH1F *Histo_FSR_ZmumuJet_Pt20to30 = (TH1F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt20to30_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt30to50 from eventTree
  TH1F *Histo_FSR_ZmumuJet_Pt30to50_temp = new TH1F();
  string variable_FSR_ZmumuJet_Pt30to50 = var + ">>Histo_FSR_ZmumuJet_Pt30to50_temp" + limits;
  FSR_ZmumuJet_Pt30to50_miniTree->Draw(variable_FSR_ZmumuJet_Pt30to50.c_str(), cut.c_str());
  TH1F *Histo_FSR_ZmumuJet_Pt30to50 = (TH1F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt30to50_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt50to80 from eventTree
  TH1F *Histo_FSR_ZmumuJet_Pt50to80_temp = new TH1F();
  string variable_FSR_ZmumuJet_Pt50to80 = var + ">>Histo_FSR_ZmumuJet_Pt50to80_temp" + limits;
  FSR_ZmumuJet_Pt50to80_miniTree->Draw(variable_FSR_ZmumuJet_Pt50to80.c_str(), cut.c_str());
  TH1F *Histo_FSR_ZmumuJet_Pt50to80 = (TH1F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt50to80_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt80to120 from eventTree
  TH1F *Histo_FSR_ZmumuJet_Pt80to120_temp = new TH1F();
  string variable_FSR_ZmumuJet_Pt80to120 = var + ">>Histo_FSR_ZmumuJet_Pt80to120_temp" + limits;
  FSR_ZmumuJet_Pt80to120_miniTree->Draw(variable_FSR_ZmumuJet_Pt80to120.c_str(), cut.c_str());
  TH1F *Histo_FSR_ZmumuJet_Pt80to120 = (TH1F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt80to120_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt120to170 from eventTree
  TH1F *Histo_FSR_ZmumuJet_Pt120to170_temp = new TH1F();
  string variable_FSR_ZmumuJet_Pt120to170 = var + ">>Histo_FSR_ZmumuJet_Pt120to170_temp" + limits;
  FSR_ZmumuJet_Pt120to170_miniTree->Draw(variable_FSR_ZmumuJet_Pt120to170.c_str(), cut.c_str());
  TH1F *Histo_FSR_ZmumuJet_Pt120to170 = (TH1F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt120to170_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt170to230 from eventTree
  TH1F *Histo_FSR_ZmumuJet_Pt170to230_temp = new TH1F();
  string variable_FSR_ZmumuJet_Pt170to230 = var + ">>Histo_FSR_ZmumuJet_Pt170to230_temp" + limits;
  FSR_ZmumuJet_Pt170to230_miniTree->Draw(variable_FSR_ZmumuJet_Pt170to230.c_str(), cut.c_str());
  TH1F *Histo_FSR_ZmumuJet_Pt170to230 = (TH1F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt170to230_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt230to300 from eventTree
  TH1F *Histo_FSR_ZmumuJet_Pt230to300_temp = new TH1F();
  string variable_FSR_ZmumuJet_Pt230to300 = var + ">>Histo_FSR_ZmumuJet_Pt230to300_temp" + limits;
  FSR_ZmumuJet_Pt230to300_miniTree->Draw(variable_FSR_ZmumuJet_Pt230to300.c_str(), cut.c_str());
  TH1F *Histo_FSR_ZmumuJet_Pt230to300 = (TH1F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt230to300_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt300toInf from eventTree
  TH1F *Histo_FSR_ZmumuJet_Pt300toInf_temp = new TH1F();
  string variable_FSR_ZmumuJet_Pt300toInf = var + ">>Histo_FSR_ZmumuJet_Pt300toInf_temp" + limits;
  FSR_ZmumuJet_Pt300toInf_miniTree->Draw(variable_FSR_ZmumuJet_Pt300toInf.c_str(), cut.c_str());
  TH1F *Histo_FSR_ZmumuJet_Pt300toInf = (TH1F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt300toInf_temp");
  c1->Clear();


  // Get Histo_ISR_ZmumuJet_Pt0to15 from eventTree
  TH1F *Histo_ISR_ZmumuJet_Pt0to15_temp = new TH1F();
  string variable_ISR_ZmumuJet_Pt0to15 = var + ">>Histo_ISR_ZmumuJet_Pt0to15_temp" + limits;
  ISR_ZmumuJet_Pt0to15_miniTree->Draw(variable_ISR_ZmumuJet_Pt0to15.c_str(), cut.c_str());
  TH1F *Histo_ISR_ZmumuJet_Pt0to15 = (TH1F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt0to15_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt15to20 from eventTree
  TH1F *Histo_ISR_ZmumuJet_Pt15to20_temp = new TH1F();
  string variable_ISR_ZmumuJet_Pt15to20 = var + ">>Histo_ISR_ZmumuJet_Pt15to20_temp" + limits;
  ISR_ZmumuJet_Pt15to20_miniTree->Draw(variable_ISR_ZmumuJet_Pt15to20.c_str(), cut.c_str());
  TH1F *Histo_ISR_ZmumuJet_Pt15to20 = (TH1F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt15to20_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt20to30 from eventTree
  TH1F *Histo_ISR_ZmumuJet_Pt20to30_temp = new TH1F();
  string variable_ISR_ZmumuJet_Pt20to30 = var + ">>Histo_ISR_ZmumuJet_Pt20to30_temp" + limits;
  ISR_ZmumuJet_Pt20to30_miniTree->Draw(variable_ISR_ZmumuJet_Pt20to30.c_str(), cut.c_str());
  TH1F *Histo_ISR_ZmumuJet_Pt20to30 = (TH1F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt20to30_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt30to50 from eventTree
  TH1F *Histo_ISR_ZmumuJet_Pt30to50_temp = new TH1F();
  string variable_ISR_ZmumuJet_Pt30to50 = var + ">>Histo_ISR_ZmumuJet_Pt30to50_temp" + limits;
  ISR_ZmumuJet_Pt30to50_miniTree->Draw(variable_ISR_ZmumuJet_Pt30to50.c_str(), cut.c_str());
  TH1F *Histo_ISR_ZmumuJet_Pt30to50 = (TH1F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt30to50_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt50to80 from eventTree
  TH1F *Histo_ISR_ZmumuJet_Pt50to80_temp = new TH1F();
  string variable_ISR_ZmumuJet_Pt50to80 = var + ">>Histo_ISR_ZmumuJet_Pt50to80_temp" + limits;
  ISR_ZmumuJet_Pt50to80_miniTree->Draw(variable_ISR_ZmumuJet_Pt50to80.c_str(), cut.c_str());
  TH1F *Histo_ISR_ZmumuJet_Pt50to80 = (TH1F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt50to80_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt80to120 from eventTree
  TH1F *Histo_ISR_ZmumuJet_Pt80to120_temp = new TH1F();
  string variable_ISR_ZmumuJet_Pt80to120 = var + ">>Histo_ISR_ZmumuJet_Pt80to120_temp" + limits;
  ISR_ZmumuJet_Pt80to120_miniTree->Draw(variable_ISR_ZmumuJet_Pt80to120.c_str(), cut.c_str());
  TH1F *Histo_ISR_ZmumuJet_Pt80to120 = (TH1F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt80to120_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt120to170 from eventTree
  TH1F *Histo_ISR_ZmumuJet_Pt120to170_temp = new TH1F();
  string variable_ISR_ZmumuJet_Pt120to170 = var + ">>Histo_ISR_ZmumuJet_Pt120to170_temp" + limits;
  ISR_ZmumuJet_Pt120to170_miniTree->Draw(variable_ISR_ZmumuJet_Pt120to170.c_str(), cut.c_str());
  TH1F *Histo_ISR_ZmumuJet_Pt120to170 = (TH1F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt120to170_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt170to230 from eventTree
  TH1F *Histo_ISR_ZmumuJet_Pt170to230_temp = new TH1F();
  string variable_ISR_ZmumuJet_Pt170to230 = var + ">>Histo_ISR_ZmumuJet_Pt170to230_temp" + limits;
  ISR_ZmumuJet_Pt170to230_miniTree->Draw(variable_ISR_ZmumuJet_Pt170to230.c_str(), cut.c_str());
  TH1F *Histo_ISR_ZmumuJet_Pt170to230 = (TH1F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt170to230_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt230to300 from eventTree
  TH1F *Histo_ISR_ZmumuJet_Pt230to300_temp = new TH1F();
  string variable_ISR_ZmumuJet_Pt230to300 = var + ">>Histo_ISR_ZmumuJet_Pt230to300_temp" + limits;
  ISR_ZmumuJet_Pt230to300_miniTree->Draw(variable_ISR_ZmumuJet_Pt230to300.c_str(), cut.c_str());
  TH1F *Histo_ISR_ZmumuJet_Pt230to300 = (TH1F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt230to300_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt300toInf from eventTree
  TH1F *Histo_ISR_ZmumuJet_Pt300toInf_temp = new TH1F();
  string variable_ISR_ZmumuJet_Pt300toInf = var + ">>Histo_ISR_ZmumuJet_Pt300toInf_temp" + limits;
  ISR_ZmumuJet_Pt300toInf_miniTree->Draw(variable_ISR_ZmumuJet_Pt300toInf.c_str(), cut.c_str());
  TH1F *Histo_ISR_ZmumuJet_Pt300toInf = (TH1F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt300toInf_temp");
  c1->Clear();


  // TODO: implement drawUnderOverFsubleading

  // Get the number of entries for further normalization
  double a = Histo_Data->Integral();
/*
  double b_PhotonJet_Pt15 = Histo_PhotonJet_Pt15->Integral();
  if( (a==0.0) || (b_PhotonJet_Pt15==0.0) ){
    cout << "no entries to plots" <<endl;
    return; 
  }*/
  // Normalize
  Histo_Data->Sumw2(); // In order to have the correct error bars on data after renormalization
  // // Normalize MC and Data to 1
  //Histo_Data->Scale((double)((double)1.0/(double)a));
  //Histo_MC->Scale((double)((double)1.0/(double)b));
  // // Normalize MC to Data number of entries
  double integratedLuminosity = 2859492.190e-06;

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
  double XSectionFSR_ZmumuJet_Pt0to15 = 4.434e+03;
  double XSectionFSR_ZmumuJet_Pt15to20 = 1.454e+02;
  double XSectionFSR_ZmumuJet_Pt20to30 = 1.318e+02;
  double XSectionFSR_ZmumuJet_Pt30to50 = 8.438e+01;
  double XSectionFSR_ZmumuJet_Pt50to80 = 3.235e+01;
  double XSectionFSR_ZmumuJet_Pt80to120 = 9.981e+00;
  double XSectionFSR_ZmumuJet_Pt120to170 = 2.760e+00;
  double XSectionFSR_ZmumuJet_Pt170to230 = 7.241e-01;
  double XSectionFSR_ZmumuJet_Pt230to300 = 1.946e-01;
  double XSectionFSR_ZmumuJet_Pt300toInf = 7.627e-02;
  double XSectionISR_ZmumuJet_Pt0to15 = 4.434e+03;
  double XSectionISR_ZmumuJet_Pt15to20 = 1.454e+02;
  double XSectionISR_ZmumuJet_Pt20to30 = 1.318e+02;
  double XSectionISR_ZmumuJet_Pt30to50 = 8.438e+01;
  double XSectionISR_ZmumuJet_Pt50to80 = 3.235e+01;
  double XSectionISR_ZmumuJet_Pt80to120 = 9.981e+00;
  double XSectionISR_ZmumuJet_Pt120to170 = 2.760e+00;
  double XSectionISR_ZmumuJet_Pt170to230 = 7.241e-01;
  double XSectionISR_ZmumuJet_Pt230to300 = 1.946e-01;
  double XSectionISR_ZmumuJet_Pt300toInf = 7.627e-02;

  double InitialNumberQCD_Pt15 = 6116800;
  double InitialNumberQCD_Pt30 = 5093840;
  double InitialNumberQCD_Pt80 = 3229000;
  double InitialNumberQCD_Pt170 = 3122500;
  double InitialNumberQCD_Pt300 = 3269645;
  double InitialNumberQCD_Pt470 = 2083653;
  double InitialNumberPhotonJet_Pt15 = 1221770;
  double InitialNumberPhotonJet_Pt30 = 1025300;
  double InitialNumberPhotonJet_Pt80 = 1287711;
  double InitialNumberPhotonJet_Pt170 = 1209600;
  double InitialNumberPhotonJet_Pt300 = 1033240;
  double InitialNumberTTbarJets_Tauola = 1463572;
  double InitialNumberWJets_7TeV = 10218854;
  double InitialNumberZJets_7TeV = 1047008;
  double InitialNumberQCD_Mu_Pt20to30 = 10985188;
  double InitialNumberQCD_Mu_Pt30to50 = 6931182;
  double InitialNumberQCD_Mu_Pt50to80 = 2542308;
  double InitialNumberQCD_Mu_Pt80to120 = 523053;
  double InitialNumberQCD_Mu_Pt120to170 = 316630;
  double InitialNumberQCD_Mu_Pt170toInf = 262036;
  double InitialNumberInclusiveMu15 = 5120334;
  double InitialNumberFSR_ZmumuJet_Pt0to15 = 235420;
  double InitialNumberFSR_ZmumuJet_Pt15to20 = 222730;
  double InitialNumberFSR_ZmumuJet_Pt20to30 = 164190;
  double InitialNumberFSR_ZmumuJet_Pt30to50 = 163920;
  double InitialNumberFSR_ZmumuJet_Pt50to80 = 106016;
  double InitialNumberFSR_ZmumuJet_Pt80to120 = 107759;
  double InitialNumberFSR_ZmumuJet_Pt120to170 = 177408;
  double InitialNumberFSR_ZmumuJet_Pt170to230 = 178400;
  double InitialNumberFSR_ZmumuJet_Pt230to300 = 176485;
  double InitialNumberFSR_ZmumuJet_Pt300toInf = 109316;
  double InitialNumberISR_ZmumuJet_Pt0to15 = 235420;
  double InitialNumberISR_ZmumuJet_Pt15to20 = 222730;
  double InitialNumberISR_ZmumuJet_Pt20to30 = 164190;
  double InitialNumberISR_ZmumuJet_Pt30to50 = 163920;
  double InitialNumberISR_ZmumuJet_Pt50to80 = 106016;
  double InitialNumberISR_ZmumuJet_Pt80to120 = 107759;
  double InitialNumberISR_ZmumuJet_Pt120to170 = 177408;
  double InitialNumberISR_ZmumuJet_Pt170to230 = 178400;
  double InitialNumberISR_ZmumuJet_Pt230to300 = 176485;
  double InitialNumberISR_ZmumuJet_Pt300toInf = 109316;

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
  Histo_FSR_ZmumuJet_Pt0to15->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt0to15) / (double)(InitialNumberFSR_ZmumuJet_Pt0to15)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt15to20->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt15to20) / (double)(InitialNumberFSR_ZmumuJet_Pt15to20)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt20to30->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt20to30) / (double)(InitialNumberFSR_ZmumuJet_Pt20to30)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt30to50->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt30to50) / (double)(InitialNumberFSR_ZmumuJet_Pt30to50)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt50to80->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt50to80) / (double)(InitialNumberFSR_ZmumuJet_Pt50to80)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt80to120->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt80to120) / (double)(InitialNumberFSR_ZmumuJet_Pt80to120)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt120to170->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt120to170) / (double)(InitialNumberFSR_ZmumuJet_Pt120to170)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt170to230->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt170to230) / (double)(InitialNumberFSR_ZmumuJet_Pt170to230)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt230to300->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt230to300) / (double)(InitialNumberFSR_ZmumuJet_Pt230to300)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt300toInf->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt300toInf) / (double)(InitialNumberFSR_ZmumuJet_Pt300toInf)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt0to15->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt0to15) / (double)(InitialNumberISR_ZmumuJet_Pt0to15)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt15to20->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt15to20) / (double)(InitialNumberISR_ZmumuJet_Pt15to20)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt20to30->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt20to30) / (double)(InitialNumberISR_ZmumuJet_Pt20to30)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt30to50->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt30to50) / (double)(InitialNumberISR_ZmumuJet_Pt30to50)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt50to80->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt50to80) / (double)(InitialNumberISR_ZmumuJet_Pt50to80)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt80to120->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt80to120) / (double)(InitialNumberISR_ZmumuJet_Pt80to120)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt120to170->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt120to170) / (double)(InitialNumberISR_ZmumuJet_Pt120to170)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt170to230->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt170to230) / (double)(InitialNumberISR_ZmumuJet_Pt170to230)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt230to300->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt230to300) / (double)(InitialNumberISR_ZmumuJet_Pt230to300)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt300toInf->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt300toInf) / (double)(InitialNumberISR_ZmumuJet_Pt300toInf)) * (double)integratedLuminosity));

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

  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt15to20);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt20to30);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt30to50);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt50to80);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt80to120);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt120to170);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt170to230);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt230to300);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt300toInf);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt15to20);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt20to30);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt30to50);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt50to80);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt80to120);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt120to170);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt170to230);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt230to300);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt300toInf);

// ttbar
	Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_TTbarJets_Tauola);
// *** stacked
	Histo_PhotonJet_Pt15->Add(Histo_ISR_ZmumuJet_Pt0to15);
// *** stacked
	Histo_WJets_7TeV->Add(Histo_PhotonJet_Pt15);
// *** stacked
	Histo_QCD_Pt15->Add(Histo_WJets_7TeV);
	Histo_QCD_Mu_Pt20to30->Add(Histo_WJets_7TeV);
	Histo_InclusiveMu15->Add(Histo_WJets_7TeV);
// *** stacked
//	Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_QCD_Pt15);
	Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_QCD_Mu_Pt20to30);
//	Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_InclusiveMu15);
// *** stacked
	Histo_ZJets_7TeV->Add(Histo_QCD_Pt15);
	Histo_ZJets_7TeV->Add(Histo_QCD_Mu_Pt20to30);
	Histo_ZJets_7TeV->Add(Histo_InclusiveMu15);


	// Total MC histo for comupting min/max
//	TH1F *Histo_allMC = new TH1F(*Histo_QCD_Mu_Pt20to30);
//	Histo_allMC->Add(Histo_QCD_Pt15);
//	Histo_allMC->Add(Histo_InclusiveMu15);
//	Histo_allMC->Add(Histo_FSR_ZmumuJet_Pt0to15);
//	Histo_allMC->Add(Histo_ZJets_7TeV);
//	Histo_allMC->Add(Histo_WJets_7TeV);
//	Histo_allMC->Add(Histo_TTbarJets_Tauola);
//	Histo_allMC->Add(Histo_PhotonJet_Pt15);


  // Get the maxs and the mins to further correct the Y-axis
  double dataMax = Histo_Data->GetMaximum();
  double YMax = dataMax;
/*  double PhotonJet_Pt15Max = Histo_PhotonJet_Pt15->GetMaximum();
  YMax = max(YMax, PhotonJet_Pt15Max);
  double QCD_Pt15Max = Histo_QCD_Pt15->GetMaximum();
  YMax = max(YMax, QCD_Pt15Max);
  double TTbarJets_TauolaMax = Histo_TTbarJets_Tauola->GetMaximum();
  YMax = max(YMax, TTbarJets_TauolaMax);
  double WJets_7TeVMax = Histo_WJets_7TeV->GetMaximum();
  YMax = max(YMax, WJets_7TeVMax);
  double QCD_Mu_Pt20to30Max = Histo_QCD_Mu_Pt20to30->GetMaximum();
  YMax = max(YMax, QCD_Mu_Pt20to30Max);
  double InclusiveMu15Max = Histo_InclusiveMu15->GetMaximum();
  YMax = max(YMax, InclusiveMu15Max);
*/

//  double ZJets_7TeVMax = Histo_ZJets_7TeV->GetMaximum();
//  YMax = max(YMax, ZJets_7TeVMax);
  double FSR_ZmumuJet_Pt0to15Max = Histo_FSR_ZmumuJet_Pt0to15->GetMaximum();
  YMax = max(YMax, FSR_ZmumuJet_Pt0to15Max);

//	double allMCMax = Histo_allMC->GetMaximum();
//	YMax = max(YMax, allMCMax);

  double dataMin = YMax;
  double PhotonJet_Pt15Min = YMax;
//  double QCD_Pt15Min = YMax;
  double TTbarJets_TauolaMin = YMax;
  double WJets_7TeVMin = YMax;
  double ZJets_7TeVMin = YMax;
  double QCD_Mu_Pt20to30Min = YMax;
//  double InclusiveMu15Min = YMax;
  double ISR_ZmumuJet_Pt0to15Min = YMax;
  double FSR_ZmumuJet_Pt0to15Min = YMax;

	double allMCMin = YMax;

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
/*  for( int ibin=1 ; ibin<Histo_QCD_Pt15->GetNbinsX() ; ibin++ ){
    if( ((Histo_QCD_Pt15->GetBinContent(ibin))!=0) && ((Histo_QCD_Pt15->GetBinContent(ibin))<QCD_Pt15Min) ){
      QCD_Pt15Min = Histo_QCD_Pt15->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, QCD_Pt15Min);*/
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
//  YMin = min(YMin, ZJets_7TeVMin);
  for( int ibin=1 ; ibin<Histo_QCD_Mu_Pt20to30->GetNbinsX() ; ibin++ ){
    if( ((Histo_QCD_Mu_Pt20to30->GetBinContent(ibin))!=0) && ((Histo_QCD_Mu_Pt20to30->GetBinContent(ibin))<QCD_Mu_Pt20to30Min) ){
      QCD_Mu_Pt20to30Min = Histo_QCD_Mu_Pt20to30->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, QCD_Mu_Pt20to30Min);
/*  for( int ibin=1 ; ibin<Histo_InclusiveMu15->GetNbinsX() ; ibin++ ){
    if( ((Histo_InclusiveMu15->GetBinContent(ibin))!=0) && ((Histo_InclusiveMu15->GetBinContent(ibin))<InclusiveMu15Min) ){
      InclusiveMu15Min = Histo_InclusiveMu15->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, InclusiveMu15Min);*/
  for( int ibin=1 ; ibin<Histo_FSR_ZmumuJet_Pt0to15->GetNbinsX() ; ibin++ ){
    if( ((Histo_FSR_ZmumuJet_Pt0to15->GetBinContent(ibin))!=0) && ((Histo_FSR_ZmumuJet_Pt0to15->GetBinContent(ibin))<FSR_ZmumuJet_Pt0to15Min) ){
      FSR_ZmumuJet_Pt0to15Min = Histo_FSR_ZmumuJet_Pt0to15->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, FSR_ZmumuJet_Pt0to15Min);
  for( int ibin=1 ; ibin<Histo_ISR_ZmumuJet_Pt0to15->GetNbinsX() ; ibin++ ){
    if( ((Histo_ISR_ZmumuJet_Pt0to15->GetBinContent(ibin))!=0) && ((Histo_ISR_ZmumuJet_Pt0to15->GetBinContent(ibin))<ISR_ZmumuJet_Pt0to15Min) ){
      ISR_ZmumuJet_Pt0to15Min = Histo_ISR_ZmumuJet_Pt0to15->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, ISR_ZmumuJet_Pt0to15Min);

/*	for( int ibin=1 ; ibin<Histo_allMC->GetNbinsX() ; ibin++ ){
    if( ((Histo_allMC->GetBinContent(ibin))!=0) && ((Histo_allMC->GetBinContent(ibin))<allMCMin) ){
      allMCMin = Histo_allMC->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, allMCMin);
*/


//  cout << "YMax= "<< YMax << "\t\tYMin= " << YMin << endl;
  double YMin_lin = (double)YMin / (double)10.0;
//  double Range_lin = ((double)(YMax - YMin_lin)) / ((double)(0.8));
  double Range_lin = ((double)(YMax - YMin_lin)) / ((double)(1.0));
  double YMax_lin = 0.2*Range_lin + YMax;
/*
  double Range_lin = ((double)(YMax - YMin)) / ((double)(0.77));
  double YMax_lin = 0.2*Range_lin + YMax;
  double YMin_lin = max(YMin - 0.03*Range_lin, (double)YMin / (double)10.0);
*/
  double Range_log = ((double)(log10(YMax) - log10(YMin))) / ((double)(0.77));
//  cout << "Range_lin= " << Range_lin << "\t\tRange_log= " << Range_log << endl;
  double YMax_log = pow(10.0, 0.2*Range_log + log10(YMax));
  double YMin_log = pow(10.0, log10(YMin) - 0.03*Range_log);
//  cout << "YMin_lin= " << YMin_lin << "\t\tYMax_lin= " << YMax_lin << endl;
//  cout << "YMin_log= " << YMin_log << "\t\tYMax_log= " << YMax_log << endl;


  // Setup the histo and canvas names and title
  string data_name = "Data_" + pic + "_" + name;
  string mc_name = "MC_" + pic + "_" + name;
  string canvas_name = "DataMC_" + pic + "_" + name;
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
//	// Template empty histo
//	TH1F *Histo_template = new TH1F("Histo_template", "Histo_template", Histo_Data->GetNbinsX(), Histo_Data->GetXaxis()->GetXmin(),  Histo_Data->GetXaxis()->GetXmax());
//	Histo_template->SetAxisRange(Histo_Data->GetXaxis()->GetXmin(),  Histo_Data->GetXaxis()->GetXmax(), "X");
//	Histo_template->SetAxisRange(YMin_lin, YMax_lin,"Y");
//	Histo_template->SetMaximum(YMax_lin);
//	Histo_template->SetMinimum(YMin_lin);
//	Histo_template->Draw();
//	c1->Update();
//	c1->Draw();

  TLegend *legend = new TLegend(0.65, 0.80, 0.90, 0.93, "");
	if( doFit ){
/*
		legend->SetX1(0.47);
		legend->SetX2(0.65);
*/
		legend->SetX1(0.15);
		legend->SetX2(0.40);
		legend->SetY1(0.65);
		legend->SetY2(0.78);

	}
	legend->SetTextSize(0.025);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kWhite);
  legend->SetShadowColor(kWhite);

  // // First: draw the data to get correct Y-axis scale
	gPad->Update();
  Histo_Data->GetXaxis()->SetTitle(Title.c_str());
  Histo_Data->GetYaxis()->SetTitle(YaxisTitle.c_str());
  Histo_Data->SetLineColor(kBlack);
  Histo_Data->SetMarkerColor(kBlack);
  Histo_Data->SetMarkerSize(0.7);
  Histo_Data->SetMarkerStyle(20);
  Histo_Data->SetMaximum(YMax_lin);
  Histo_Data->SetMinimum(YMin_lin);
//  Histo_Data->GetYaxis()->SetRangeUser(YMin_lin, YMax_lin);
//  Histo_Data->Draw("E1sames");
  Histo_Data->Draw("E1");
  legend->AddEntry(Histo_Data->GetName(), "Data", "lp");

  // // Second: draw MC on the same canvas
  Histo_QCD_Pt15->SetLineColor(kBlack);
  Histo_QCD_Pt15->SetFillColor(kGreen+3);
  Histo_QCD_Pt15->SetFillStyle(3001);
  Histo_QCD_Pt15->SetMaximum(YMax_lin);
  Histo_QCD_Pt15->SetMinimum(YMin_lin);
//  Histo_QCD_Pt15->Draw("same");
//  legend->AddEntry(Histo_QCD_Pt15->GetName(), "QCD", "f");

  Histo_QCD_Mu_Pt20to30->SetLineColor(kBlack);
  Histo_QCD_Mu_Pt20to30->SetFillColor(kGreen);
  Histo_QCD_Mu_Pt20to30->SetFillStyle(3001);
  Histo_QCD_Mu_Pt20to30->SetMaximum(YMax_lin);
  Histo_QCD_Mu_Pt20to30->SetMinimum(YMin_lin);
//  Histo_QCD_Mu_Pt20to30->Draw("same");

  Histo_InclusiveMu15->SetLineColor(kBlack);
  Histo_InclusiveMu15->SetFillColor(kGreen-6);
  Histo_InclusiveMu15->SetFillStyle(3001);
  Histo_InclusiveMu15->SetMaximum(YMax_lin);
  Histo_InclusiveMu15->SetMinimum(YMin_lin);
//  Histo_InclusiveMu15->Draw("same");  
//  legend->AddEntry(Histo_InclusiveMu15->GetName(), "InclusiveMu15", "f");

  Histo_WJets_7TeV->SetLineColor(kBlack);
  Histo_WJets_7TeV->SetFillColor(kMagenta+3);
  Histo_WJets_7TeV->SetFillStyle(3001);
  Histo_WJets_7TeV->SetMaximum(YMax_lin);
  Histo_WJets_7TeV->SetMinimum(YMin_lin);

  Histo_TTbarJets_Tauola->SetLineColor(kBlack);
  Histo_TTbarJets_Tauola->SetFillColor(kBlue);
  Histo_TTbarJets_Tauola->SetFillStyle(3001);
  Histo_TTbarJets_Tauola->SetMaximum(YMax_lin);
  Histo_TTbarJets_Tauola->SetMinimum(YMin_lin);

  Histo_PhotonJet_Pt15->SetLineColor(kBlack);
  Histo_PhotonJet_Pt15->SetFillColor(kMagenta);
  Histo_PhotonJet_Pt15->SetFillStyle(3001);
  Histo_PhotonJet_Pt15->SetMaximum(YMax_lin);
  Histo_PhotonJet_Pt15->SetMinimum(YMin_lin);

  Histo_FSR_ZmumuJet_Pt0to15->SetLineColor(kBlack);
  Histo_FSR_ZmumuJet_Pt0to15->SetFillColor(kRed);
  Histo_FSR_ZmumuJet_Pt0to15->SetFillStyle(3001);
  Histo_FSR_ZmumuJet_Pt0to15->SetMaximum(YMax_lin);
  Histo_FSR_ZmumuJet_Pt0to15->SetMinimum(YMin_lin);
  Histo_FSR_ZmumuJet_Pt0to15->GetXaxis()->SetTitle(Title.c_str());
  Histo_FSR_ZmumuJet_Pt0to15->GetYaxis()->SetTitle(YaxisTitle.c_str());

	Histo_ISR_ZmumuJet_Pt0to15->SetLineColor(kBlack);
  Histo_ISR_ZmumuJet_Pt0to15->SetFillColor(kOrange);
  Histo_ISR_ZmumuJet_Pt0to15->SetFillStyle(3001);
  Histo_ISR_ZmumuJet_Pt0to15->SetMaximum(YMax_lin);
  Histo_ISR_ZmumuJet_Pt0to15->SetMinimum(YMin_lin);

  Histo_ZJets_7TeV->SetLineColor(kBlack);
  Histo_ZJets_7TeV->SetFillColor(kOrange);
  Histo_ZJets_7TeV->SetFillStyle(3001);
  Histo_ZJets_7TeV->SetMaximum(YMax_lin);
  Histo_ZJets_7TeV->SetMinimum(YMin_lin);

  Histo_FSR_ZmumuJet_Pt0to15->Draw("same");
//  Histo_ZJets_7TeV->Draw("same");
	Histo_QCD_Mu_Pt20to30->Draw("same");
  Histo_WJets_7TeV->Draw("same");
  Histo_PhotonJet_Pt15->Draw("same");
  Histo_ISR_ZmumuJet_Pt0to15->Draw("same");
  Histo_TTbarJets_Tauola->Draw("same");
  legend->AddEntry(Histo_TTbarJets_Tauola->GetName(), "TTbarJets", "f");
  legend->AddEntry(Histo_ISR_ZmumuJet_Pt0to15->GetName(), "ZmumuJet (no FSR)", "f");
  legend->AddEntry(Histo_PhotonJet_Pt15->GetName(), "PhotonJet", "f");
  legend->AddEntry(Histo_WJets_7TeV->GetName(), "WJets", "f");
  legend->AddEntry(Histo_QCD_Mu_Pt20to30->GetName(), "QCD Mu", "f");
//  legend->AddEntry(Histo_ZJets_7TeV->GetName(), "ZJets madgraph", "f");
  legend->AddEntry(Histo_FSR_ZmumuJet_Pt0to15->GetName(), "ZmumuJet FSR", "f");

  // // Third: re-draw Data so that data appears in front of MC
  Histo_Data->Draw("E1same");

if( doFit ){
	Histo_Data->SetName("DATA");
	Histo_FSR_ZmumuJet_Pt0to15->SetName("MC");
	gStyle->SetOptStat(2201);
	string fitOpts = "MQ+";

	TF1* f_Data = new TF1("f_Data", "gaus");
	TF1* f_MC = new TF1("f_MC", "gaus");
	f_Data->SetLineColor(kBlue);
	f_MC->SetLineColor(kGreen+2);
	f_Data->SetLineWidth(2);
	f_MC->SetLineWidth(2);
	Histo_Data->Fit("f_Data", fitOpts.c_str());
	Histo_FSR_ZmumuJet_Pt0to15->Fit("f_MC", fitOpts.c_str());

	Histo_FSR_ZmumuJet_Pt0to15->SetMaximum(YMax_lin);
	Histo_FSR_ZmumuJet_Pt0to15->SetMinimum(YMin_lin);	
	Histo_QCD_Mu_Pt20to30->SetMaximum(YMax_lin);
	Histo_QCD_Mu_Pt20to30->SetMinimum(YMin_lin);	
	Histo_WJets_7TeV->SetMaximum(YMax_lin);
	Histo_WJets_7TeV->SetMinimum(YMin_lin);	
	Histo_PhotonJet_Pt15->SetMaximum(YMax_lin);
	Histo_PhotonJet_Pt15->SetMinimum(YMin_lin);	
	Histo_ISR_ZmumuJet_Pt0to15->SetMaximum(YMax_lin);
	Histo_ISR_ZmumuJet_Pt0to15->SetMinimum(YMin_lin);	
	Histo_TTbarJets_Tauola->SetMaximum(YMax_lin);
	Histo_TTbarJets_Tauola->SetMinimum(YMin_lin);	
	Histo_Data->SetMaximum(YMax_lin);
	Histo_Data->SetMinimum(YMin_lin);	
  Histo_FSR_ZmumuJet_Pt0to15->Draw("sames");
	//  Histo_ZJets_7TeV->Draw("sames");
  Histo_QCD_Mu_Pt20to30->Draw("sames");
  Histo_WJets_7TeV->Draw("sames");
  Histo_PhotonJet_Pt15->Draw("sames");
  Histo_ISR_ZmumuJet_Pt0to15->Draw("sames");
  Histo_TTbarJets_Tauola->Draw("sames");
  Histo_Data->GetXaxis()->SetTitle(Title.c_str());
  Histo_Data->GetYaxis()->SetTitle(YaxisTitle.c_str());
  Histo_Data->Draw("E1sames");
//	Histo_Data->SetMaximum(YMax_lin);
//	Histo_Data->SetMinimum(YMin_lin);	
//	c1->Update();	

/*
	TPaveStats* statsHisto_MC = (TPaveStats*) Histo_ZJets_7TeV->GetListOfFunctions()->FindObject("stats");
  statsHisto_ZJets_7TeV->SetLineColor(kWhite);
  statsHisto_ZJets_7TeV->SetTextColor(kWhite);
	statsHisto_ZJets_7TeV->Draw();
*/

	gPad->Update();
 	TPaveStats* statsHisto_QCD_Mu_Pt20to30 = (TPaveStats*) Histo_QCD_Mu_Pt20to30->GetListOfFunctions()->FindObject("stats");
  statsHisto_QCD_Mu_Pt20to30->SetLineColor(kWhite);
  statsHisto_QCD_Mu_Pt20to30->SetTextColor(kWhite);
	statsHisto_QCD_Mu_Pt20to30->Draw();
 
	gPad->Update();
 	TPaveStats* statsHisto_WJets_7TeV = (TPaveStats*) Histo_WJets_7TeV->GetListOfFunctions()->FindObject("stats");
  statsHisto_WJets_7TeV->SetLineColor(kWhite);
  statsHisto_WJets_7TeV->SetTextColor(kWhite);
	statsHisto_WJets_7TeV->Draw();
  
	gPad->Update();
	TPaveStats* statsHisto_PhotonJet_Pt15 = (TPaveStats*) Histo_PhotonJet_Pt15->GetListOfFunctions()->FindObject("stats");
  statsHisto_PhotonJet_Pt15->SetLineColor(kWhite);
  statsHisto_PhotonJet_Pt15->SetTextColor(kWhite);
	statsHisto_PhotonJet_Pt15->Draw();
  
	gPad->Update();
	TPaveStats* statsHisto_ISR_ZmumuJet_Pt0to15 = (TPaveStats*) Histo_ISR_ZmumuJet_Pt0to15->GetListOfFunctions()->FindObject("stats");
  statsHisto_ISR_ZmumuJet_Pt0to15->SetLineColor(kWhite);
  statsHisto_ISR_ZmumuJet_Pt0to15->SetTextColor(kWhite);
	statsHisto_ISR_ZmumuJet_Pt0to15->Draw();
  
	gPad->Update();
	TPaveStats* statsHisto_TTbarJets_Tauola = (TPaveStats*) Histo_TTbarJets_Tauola->GetListOfFunctions()->FindObject("stats");
  statsHisto_TTbarJets_Tauola->SetLineColor(kWhite);
  statsHisto_TTbarJets_Tauola->SetTextColor(kWhite);
	statsHisto_TTbarJets_Tauola->Draw();
 

	gPad->Update();
	TPaveStats* statsHisto_Data = (TPaveStats*) Histo_Data->GetListOfFunctions()->FindObject("stats");
	statsHisto_Data->SetLineColor(kBlue);
	statsHisto_Data->SetTextColor(kBlue);
	statsHisto_Data->SetTextSize(0.020);
	statsHisto_Data->SetX1NDC(0.68);
	statsHisto_Data->SetX2NDC(0.93);
	statsHisto_Data->SetY1NDC(0.80);
	statsHisto_Data->SetY2NDC(0.93);
	statsHisto_Data->Draw();


	gPad->Update();
	TPaveStats* statsHisto_FSR_ZmumuJet_Pt0to15 = (TPaveStats*) Histo_FSR_ZmumuJet_Pt0to15->GetListOfFunctions()->FindObject("stats");
	statsHisto_FSR_ZmumuJet_Pt0to15->SetLineColor(kGreen+2);
	statsHisto_FSR_ZmumuJet_Pt0to15->SetTextColor(kGreen+2);
	statsHisto_FSR_ZmumuJet_Pt0to15->SetTextSize(0.020);
	statsHisto_FSR_ZmumuJet_Pt0to15->SetX1NDC(0.68);
	statsHisto_FSR_ZmumuJet_Pt0to15->SetX2NDC(0.93);
	statsHisto_FSR_ZmumuJet_Pt0to15->SetY1NDC(0.67);
	statsHisto_FSR_ZmumuJet_Pt0to15->SetY2NDC(0.80);
	statsHisto_FSR_ZmumuJet_Pt0to15->Draw();

//	c1->Update();	

}
  // // Fourth: redraw axis so that axis appears in front of everything
  gPad->RedrawAxis();

  // // Fifth: draw legend
  legend->Draw();
	c1->Update();

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
  string PicName="gif/DataMC_" + pic + "_" + name + ".gif";
  c1->Print(PicName.c_str());
  PicName="eps/DataMC_" + pic + "_" + name + ".eps";
  c1->Print(PicName.c_str());
  string convert = "convert eps/DataMC_" + pic + "_" + name + ".eps" + " pdf/DataMC_" + pic + "_" + name + ".pdf";
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
    Histo_ISR_ZmumuJet_Pt0to15->SetMaximum(YMax_log);
    Histo_ISR_ZmumuJet_Pt0to15->SetMinimum(YMin_log);
    Histo_ISR_ZmumuJet_Pt0to15->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
    Histo_FSR_ZmumuJet_Pt0to15->SetMaximum(YMax_log);
    Histo_FSR_ZmumuJet_Pt0to15->SetMinimum(YMin_log);
    Histo_FSR_ZmumuJet_Pt0to15->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
    c1->SetLogy(1);
    c1->Update();
    c1->Draw();
    string PicName_log="gif/DataMC_" + pic + "_" + name + "_log.gif";
    c1->Print(PicName_log.c_str());
    PicName="eps/DataMC_" + pic + "_" + name + "_log.eps";
    c1->Print(PicName.c_str());
    string convert = "convert eps/DataMC_" + pic + "_" + name + "_log.eps" + " pdf/DataMC_" + pic + "_" + name + "_log.pdf";
    system(convert.c_str());
    c1->SetLogy(0);
    c1->Update();
  }

  // Clean the memory
  c1->Clear();
  legend->Clear();
//	Histo_template->Delete();
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
  Histo_ISR_ZmumuJet_Pt0to15_temp->Delete();
  Histo_ISR_ZmumuJet_Pt0to15->Delete();
  Histo_ISR_ZmumuJet_Pt15to20_temp->Delete();
  Histo_ISR_ZmumuJet_Pt15to20->Delete();
  Histo_ISR_ZmumuJet_Pt20to30_temp->Delete();
  Histo_ISR_ZmumuJet_Pt20to30->Delete();
  Histo_ISR_ZmumuJet_Pt30to50_temp->Delete();
  Histo_ISR_ZmumuJet_Pt30to50->Delete();
  Histo_ISR_ZmumuJet_Pt50to80_temp->Delete();
  Histo_ISR_ZmumuJet_Pt50to80->Delete();
  Histo_ISR_ZmumuJet_Pt80to120_temp->Delete();
  Histo_ISR_ZmumuJet_Pt80to120->Delete();
  Histo_ISR_ZmumuJet_Pt120to170_temp->Delete();
  Histo_ISR_ZmumuJet_Pt120to170->Delete();
  Histo_ISR_ZmumuJet_Pt170to230_temp->Delete();
  Histo_ISR_ZmumuJet_Pt170to230->Delete();
  Histo_ISR_ZmumuJet_Pt230to300_temp->Delete();
  Histo_ISR_ZmumuJet_Pt230to300->Delete();
  Histo_ISR_ZmumuJet_Pt300toInf_temp->Delete();
  Histo_ISR_ZmumuJet_Pt300toInf->Delete();
  Histo_FSR_ZmumuJet_Pt0to15_temp->Delete();
  Histo_FSR_ZmumuJet_Pt0to15->Delete();
  Histo_FSR_ZmumuJet_Pt15to20_temp->Delete();
  Histo_FSR_ZmumuJet_Pt15to20->Delete();
  Histo_FSR_ZmumuJet_Pt20to30_temp->Delete();
  Histo_FSR_ZmumuJet_Pt20to30->Delete();
  Histo_FSR_ZmumuJet_Pt30to50_temp->Delete();
  Histo_FSR_ZmumuJet_Pt30to50->Delete();
  Histo_FSR_ZmumuJet_Pt50to80_temp->Delete();
  Histo_FSR_ZmumuJet_Pt50to80->Delete();
  Histo_FSR_ZmumuJet_Pt80to120_temp->Delete();
  Histo_FSR_ZmumuJet_Pt80to120->Delete();
  Histo_FSR_ZmumuJet_Pt120to170_temp->Delete();
  Histo_FSR_ZmumuJet_Pt120to170->Delete();
  Histo_FSR_ZmumuJet_Pt170to230_temp->Delete();
  Histo_FSR_ZmumuJet_Pt170to230->Delete();
  Histo_FSR_ZmumuJet_Pt230to300_temp->Delete();
  Histo_FSR_ZmumuJet_Pt230to300->Delete();
  Histo_FSR_ZmumuJet_Pt300toInf_temp->Delete();
  Histo_FSR_ZmumuJet_Pt300toInf->Delete();

}

void DrawDataMCplot_TH1I(TTree *Data_miniTree, TTree *QCD_Pt15_miniTree, TTree *QCD_Pt30_miniTree, TTree *QCD_Pt80_miniTree, TTree *QCD_Pt170_miniTree, TTree *QCD_Pt300_miniTree, TTree *QCD_Pt470_miniTree, TTree *PhotonJet_Pt15_miniTree, TTree *PhotonJet_Pt30_miniTree, TTree *PhotonJet_Pt80_miniTree, TTree *PhotonJet_Pt170_miniTree, TTree *PhotonJet_Pt300_miniTree, TTree *TTbarJets_Tauola_miniTree, TTree *WJets_7TeV_miniTree, TTree *ZJets_7TeV_miniTree, TTree *QCD_Mu_Pt20to30_miniTree, TTree *QCD_Mu_Pt30to50_miniTree, TTree *QCD_Mu_Pt50to80_miniTree, TTree *QCD_Mu_Pt80to120_miniTree, TTree *QCD_Mu_Pt120to170_miniTree, TTree *QCD_Mu_Pt170toInf_miniTree, TTree *InclusiveMu15_miniTree, TTree *FSR_ZmumuJet_Pt0to15_miniTree, TTree *FSR_ZmumuJet_Pt15to20_miniTree, TTree *FSR_ZmumuJet_Pt20to30_miniTree, TTree *FSR_ZmumuJet_Pt30to50_miniTree, TTree *FSR_ZmumuJet_Pt50to80_miniTree, TTree *FSR_ZmumuJet_Pt80to120_miniTree, TTree *FSR_ZmumuJet_Pt120to170_miniTree, TTree *FSR_ZmumuJet_Pt170to230_miniTree, TTree *FSR_ZmumuJet_Pt230to300_miniTree, TTree *FSR_ZmumuJet_Pt300toInf_miniTree, TTree *ISR_ZmumuJet_Pt0to15_miniTree, TTree *ISR_ZmumuJet_Pt15to20_miniTree, TTree *ISR_ZmumuJet_Pt20to30_miniTree, TTree *ISR_ZmumuJet_Pt30to50_miniTree, TTree *ISR_ZmumuJet_Pt50to80_miniTree, TTree *ISR_ZmumuJet_Pt80to120_miniTree, TTree *ISR_ZmumuJet_Pt120to170_miniTree, TTree *ISR_ZmumuJet_Pt170to230_miniTree, TTree *ISR_ZmumuJet_Pt230to300_miniTree, TTree *ISR_ZmumuJet_Pt300toInf_miniTree, string var, string pic, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1, bool doFit){

  // Get Histo_Data from eventTree
  TH1I *Histo_Data_temp = new TH1I();
  string variable_Data = var + ">>Histo_Data_temp" + limits;
  Data_miniTree->Draw(variable_Data.c_str(), cut.c_str());
  TH1I *Histo_Data = (TH1I*)gDirectory->Get("Histo_Data_temp");
  c1->Clear();

  // Get Histo_PhotonJet_Pt15 from eventTree
  TH1I *Histo_PhotonJet_Pt15_temp = new TH1I();
  string variable_PhotonJet_Pt15 = var + ">>Histo_PhotonJet_Pt15_temp" + limits;
  PhotonJet_Pt15_miniTree->Draw(variable_PhotonJet_Pt15.c_str(), cut.c_str());
  TH1I *Histo_PhotonJet_Pt15 = (TH1I*)gDirectory->Get("Histo_PhotonJet_Pt15_temp");
  c1->Clear();

  // Get Histo_PhotonJet_Pt30 from eventTree
  TH1I *Histo_PhotonJet_Pt30_temp = new TH1I();
  string variable_PhotonJet_Pt30 = var + ">>Histo_PhotonJet_Pt30_temp" + limits;
  PhotonJet_Pt30_miniTree->Draw(variable_PhotonJet_Pt30.c_str(), cut.c_str());
  TH1I *Histo_PhotonJet_Pt30 = (TH1I*)gDirectory->Get("Histo_PhotonJet_Pt30_temp");
  c1->Clear();

  // Get Histo_PhotonJet_Pt80 from eventTree
  TH1I *Histo_PhotonJet_Pt80_temp = new TH1I();
  string variable_PhotonJet_Pt80 = var + ">>Histo_PhotonJet_Pt80_temp" + limits;
  PhotonJet_Pt80_miniTree->Draw(variable_PhotonJet_Pt80.c_str(), cut.c_str());
  TH1I *Histo_PhotonJet_Pt80 = (TH1I*)gDirectory->Get("Histo_PhotonJet_Pt80_temp");
  c1->Clear();

  // Get Histo_PhotonJet_Pt170 from eventTree
  TH1I *Histo_PhotonJet_Pt170_temp = new TH1I();
  string variable_PhotonJet_Pt170 = var + ">>Histo_PhotonJet_Pt170_temp" + limits;
  PhotonJet_Pt170_miniTree->Draw(variable_PhotonJet_Pt170.c_str(), cut.c_str());
  TH1I *Histo_PhotonJet_Pt170 = (TH1I*)gDirectory->Get("Histo_PhotonJet_Pt170_temp");
  c1->Clear();

  // Get Histo_PhotonJet_Pt300 from eventTree
  TH1I *Histo_PhotonJet_Pt300_temp = new TH1I();
  string variable_PhotonJet_Pt300 = var + ">>Histo_PhotonJet_Pt300_temp" + limits;
  PhotonJet_Pt300_miniTree->Draw(variable_PhotonJet_Pt300.c_str(), cut.c_str());
  TH1I *Histo_PhotonJet_Pt300 = (TH1I*)gDirectory->Get("Histo_PhotonJet_Pt300_temp");
  c1->Clear();

  // Get Histo_QCD_Pt15 from eventTree
  TH1I *Histo_QCD_Pt15_temp = new TH1I();
  string variable_QCD_Pt15 = var + ">>Histo_QCD_Pt15_temp" + limits;
  QCD_Pt15_miniTree->Draw(variable_QCD_Pt15.c_str(), cut.c_str());
  TH1I *Histo_QCD_Pt15 = (TH1I*)gDirectory->Get("Histo_QCD_Pt15_temp");
  c1->Clear();

  // Get Histo_QCD_Pt30 from eventTree
  TH1I *Histo_QCD_Pt30_temp = new TH1I();
  string variable_QCD_Pt30 = var + ">>Histo_QCD_Pt30_temp" + limits;
  QCD_Pt30_miniTree->Draw(variable_QCD_Pt30.c_str(), cut.c_str());
  TH1I *Histo_QCD_Pt30 = (TH1I*)gDirectory->Get("Histo_QCD_Pt30_temp");

  // Get Histo_QCD_Pt80 from eventTree
  TH1I *Histo_QCD_Pt80_temp = new TH1I();
  string variable_QCD_Pt80 = var + ">>Histo_QCD_Pt80_temp" + limits;
  QCD_Pt80_miniTree->Draw(variable_QCD_Pt80.c_str(), cut.c_str());
  TH1I *Histo_QCD_Pt80 = (TH1I*)gDirectory->Get("Histo_QCD_Pt80_temp");
  c1->Clear();

  // Get Histo_QCD_Pt170 from eventTree
  TH1I *Histo_QCD_Pt170_temp = new TH1I();
  string variable_QCD_Pt170 = var + ">>Histo_QCD_Pt170_temp" + limits;
  QCD_Pt170_miniTree->Draw(variable_QCD_Pt170.c_str(), cut.c_str());
  TH1I *Histo_QCD_Pt170 = (TH1I*)gDirectory->Get("Histo_QCD_Pt170_temp");
  c1->Clear();

  // Get Histo_QCD_Pt300 from eventTree
  TH1I *Histo_QCD_Pt300_temp = new TH1I();
  string variable_QCD_Pt300 = var + ">>Histo_QCD_Pt300_temp" + limits;
  QCD_Pt300_miniTree->Draw(variable_QCD_Pt300.c_str(), cut.c_str());
  TH1I *Histo_QCD_Pt300 = (TH1I*)gDirectory->Get("Histo_QCD_Pt300_temp");
  c1->Clear();

  // Get Histo_QCD_Pt470 from eventTree
  TH1I *Histo_QCD_Pt470_temp = new TH1I();
  string variable_QCD_Pt470 = var + ">>Histo_QCD_Pt470_temp" + limits;
  QCD_Pt470_miniTree->Draw(variable_QCD_Pt470.c_str(), cut.c_str());
  TH1I *Histo_QCD_Pt470 = (TH1I*)gDirectory->Get("Histo_QCD_Pt470_temp");
  c1->Clear();

  // Get Histo_TTbarJets_Tauola from eventTree
  TH1I *Histo_TTbarJets_Tauola_temp = new TH1I();
  string variable_TTbarJets_Tauola = var + ">>Histo_TTbarJets_Tauola_temp" + limits;
  TTbarJets_Tauola_miniTree->Draw(variable_TTbarJets_Tauola.c_str(), cut.c_str());
  TH1I *Histo_TTbarJets_Tauola = (TH1I*)gDirectory->Get("Histo_TTbarJets_Tauola_temp");
  c1->Clear();

  // Get Histo_WJets_7TeV from eventTree
  TH1I *Histo_WJets_7TeV_temp = new TH1I();
  string variable_WJets_7TeV = var + ">>Histo_WJets_7TeV_temp" + limits;
  WJets_7TeV_miniTree->Draw(variable_WJets_7TeV.c_str(), cut.c_str());
  TH1I *Histo_WJets_7TeV = (TH1I*)gDirectory->Get("Histo_WJets_7TeV_temp");
  c1->Clear();

  // Get Histo_ZJets_7TeV from eventTree
  TH1I *Histo_ZJets_7TeV_temp = new TH1I();
  string variable_ZJets_7TeV = var + ">>Histo_ZJets_7TeV_temp" + limits;
  ZJets_7TeV_miniTree->Draw(variable_ZJets_7TeV.c_str(), cut.c_str());
  TH1I *Histo_ZJets_7TeV = (TH1I*)gDirectory->Get("Histo_ZJets_7TeV_temp");
  c1->Clear();

  // Get Histo_QCD_Mu_Pt20to30 from eventTree
  TH1I *Histo_QCD_Mu_Pt20to30_temp = new TH1I();
  string variable_QCD_Mu_Pt20to30 = var + ">>Histo_QCD_Mu_Pt20to30_temp" + limits;
  QCD_Mu_Pt20to30_miniTree->Draw(variable_QCD_Mu_Pt20to30.c_str(), cut.c_str());
  TH1I *Histo_QCD_Mu_Pt20to30 = (TH1I*)gDirectory->Get("Histo_QCD_Mu_Pt20to30_temp");
  c1->Clear();

  // Get Histo_QCD_Mu_Pt30to50 from eventTree
  TH1I *Histo_QCD_Mu_Pt30to50_temp = new TH1I();
  string variable_QCD_Mu_Pt30to50 = var + ">>Histo_QCD_Mu_Pt30to50_temp" + limits;
  QCD_Mu_Pt30to50_miniTree->Draw(variable_QCD_Mu_Pt30to50.c_str(), cut.c_str());
  TH1I *Histo_QCD_Mu_Pt30to50 = (TH1I*)gDirectory->Get("Histo_QCD_Mu_Pt30to50_temp");
  c1->Clear();

  // Get Histo_QCD_Mu_Pt50to80 from eventTree
  TH1I *Histo_QCD_Mu_Pt50to80_temp = new TH1I();
  string variable_QCD_Mu_Pt50to80 = var + ">>Histo_QCD_Mu_Pt50to80_temp" + limits;
  QCD_Mu_Pt50to80_miniTree->Draw(variable_QCD_Mu_Pt50to80.c_str(), cut.c_str());
  TH1I *Histo_QCD_Mu_Pt50to80 = (TH1I*)gDirectory->Get("Histo_QCD_Mu_Pt50to80_temp");
  c1->Clear();

  // Get Histo_QCD_Mu_Pt80to120 from eventTree
  TH1I *Histo_QCD_Mu_Pt80to120_temp = new TH1I();
  string variable_QCD_Mu_Pt80to120 = var + ">>Histo_QCD_Mu_Pt80to120_temp" + limits;
  QCD_Mu_Pt80to120_miniTree->Draw(variable_QCD_Mu_Pt80to120.c_str(), cut.c_str());
  TH1I *Histo_QCD_Mu_Pt80to120 = (TH1I*)gDirectory->Get("Histo_QCD_Mu_Pt80to120_temp");
  c1->Clear();

  // Get Histo_QCD_Mu_Pt120to170 from eventTree
  TH1I *Histo_QCD_Mu_Pt120to170_temp = new TH1I();
  string variable_QCD_Mu_Pt120to170 = var + ">>Histo_QCD_Mu_Pt120to170_temp" + limits;
  QCD_Mu_Pt120to170_miniTree->Draw(variable_QCD_Mu_Pt120to170.c_str(), cut.c_str());
  TH1I *Histo_QCD_Mu_Pt120to170 = (TH1I*)gDirectory->Get("Histo_QCD_Mu_Pt120to170_temp");
  c1->Clear();

  // Get Histo_QCD_Mu_Pt170toInf from eventTree
  TH1I *Histo_QCD_Mu_Pt170toInf_temp = new TH1I();
  string variable_QCD_Mu_Pt170toInf = var + ">>Histo_QCD_Mu_Pt170toInf_temp" + limits;
  QCD_Mu_Pt170toInf_miniTree->Draw(variable_QCD_Mu_Pt170toInf.c_str(), cut.c_str());
  TH1I *Histo_QCD_Mu_Pt170toInf = (TH1I*)gDirectory->Get("Histo_QCD_Mu_Pt170toInf_temp");
  c1->Clear();

  // Get Histo_InclusiveMu15 from eventTree
  TH1I *Histo_InclusiveMu15_temp = new TH1I();
  string variable_InclusiveMu15 = var + ">>Histo_InclusiveMu15_temp" + limits;
  InclusiveMu15_miniTree->Draw(variable_InclusiveMu15.c_str(), cut.c_str());
  TH1I *Histo_InclusiveMu15 = (TH1I*)gDirectory->Get("Histo_InclusiveMu15_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt0to15 from eventTree
  TH1I *Histo_FSR_ZmumuJet_Pt0to15_temp = new TH1I();
  string variable_FSR_ZmumuJet_Pt0to15 = var + ">>Histo_FSR_ZmumuJet_Pt0to15_temp" + limits;
  FSR_ZmumuJet_Pt0to15_miniTree->Draw(variable_FSR_ZmumuJet_Pt0to15.c_str(), cut.c_str());
  TH1I *Histo_FSR_ZmumuJet_Pt0to15 = (TH1I*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt0to15_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt15to20 from eventTree
  TH1I *Histo_FSR_ZmumuJet_Pt15to20_temp = new TH1I();
  string variable_FSR_ZmumuJet_Pt15to20 = var + ">>Histo_FSR_ZmumuJet_Pt15to20_temp" + limits;
  FSR_ZmumuJet_Pt15to20_miniTree->Draw(variable_FSR_ZmumuJet_Pt15to20.c_str(), cut.c_str());
  TH1I *Histo_FSR_ZmumuJet_Pt15to20 = (TH1I*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt15to20_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt20to30 from eventTree
  TH1I *Histo_FSR_ZmumuJet_Pt20to30_temp = new TH1I();
  string variable_FSR_ZmumuJet_Pt20to30 = var + ">>Histo_FSR_ZmumuJet_Pt20to30_temp" + limits;
  FSR_ZmumuJet_Pt20to30_miniTree->Draw(variable_FSR_ZmumuJet_Pt20to30.c_str(), cut.c_str());
  TH1I *Histo_FSR_ZmumuJet_Pt20to30 = (TH1I*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt20to30_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt30to50 from eventTree
  TH1I *Histo_FSR_ZmumuJet_Pt30to50_temp = new TH1I();
  string variable_FSR_ZmumuJet_Pt30to50 = var + ">>Histo_FSR_ZmumuJet_Pt30to50_temp" + limits;
  FSR_ZmumuJet_Pt30to50_miniTree->Draw(variable_FSR_ZmumuJet_Pt30to50.c_str(), cut.c_str());
  TH1I *Histo_FSR_ZmumuJet_Pt30to50 = (TH1I*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt30to50_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt50to80 from eventTree
  TH1I *Histo_FSR_ZmumuJet_Pt50to80_temp = new TH1I();
  string variable_FSR_ZmumuJet_Pt50to80 = var + ">>Histo_FSR_ZmumuJet_Pt50to80_temp" + limits;
  FSR_ZmumuJet_Pt50to80_miniTree->Draw(variable_FSR_ZmumuJet_Pt50to80.c_str(), cut.c_str());
  TH1I *Histo_FSR_ZmumuJet_Pt50to80 = (TH1I*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt50to80_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt80to120 from eventTree
  TH1I *Histo_FSR_ZmumuJet_Pt80to120_temp = new TH1I();
  string variable_FSR_ZmumuJet_Pt80to120 = var + ">>Histo_FSR_ZmumuJet_Pt80to120_temp" + limits;
  FSR_ZmumuJet_Pt80to120_miniTree->Draw(variable_FSR_ZmumuJet_Pt80to120.c_str(), cut.c_str());
  TH1I *Histo_FSR_ZmumuJet_Pt80to120 = (TH1I*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt80to120_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt120to170 from eventTree
  TH1I *Histo_FSR_ZmumuJet_Pt120to170_temp = new TH1I();
  string variable_FSR_ZmumuJet_Pt120to170 = var + ">>Histo_FSR_ZmumuJet_Pt120to170_temp" + limits;
  FSR_ZmumuJet_Pt120to170_miniTree->Draw(variable_FSR_ZmumuJet_Pt120to170.c_str(), cut.c_str());
  TH1I *Histo_FSR_ZmumuJet_Pt120to170 = (TH1I*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt120to170_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt170to230 from eventTree
  TH1I *Histo_FSR_ZmumuJet_Pt170to230_temp = new TH1I();
  string variable_FSR_ZmumuJet_Pt170to230 = var + ">>Histo_FSR_ZmumuJet_Pt170to230_temp" + limits;
  FSR_ZmumuJet_Pt170to230_miniTree->Draw(variable_FSR_ZmumuJet_Pt170to230.c_str(), cut.c_str());
  TH1I *Histo_FSR_ZmumuJet_Pt170to230 = (TH1I*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt170to230_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt230to300 from eventTree
  TH1I *Histo_FSR_ZmumuJet_Pt230to300_temp = new TH1I();
  string variable_FSR_ZmumuJet_Pt230to300 = var + ">>Histo_FSR_ZmumuJet_Pt230to300_temp" + limits;
  FSR_ZmumuJet_Pt230to300_miniTree->Draw(variable_FSR_ZmumuJet_Pt230to300.c_str(), cut.c_str());
  TH1I *Histo_FSR_ZmumuJet_Pt230to300 = (TH1I*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt230to300_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt300toInf from eventTree
  TH1I *Histo_FSR_ZmumuJet_Pt300toInf_temp = new TH1I();
  string variable_FSR_ZmumuJet_Pt300toInf = var + ">>Histo_FSR_ZmumuJet_Pt300toInf_temp" + limits;
  FSR_ZmumuJet_Pt300toInf_miniTree->Draw(variable_FSR_ZmumuJet_Pt300toInf.c_str(), cut.c_str());
  TH1I *Histo_FSR_ZmumuJet_Pt300toInf = (TH1I*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt300toInf_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt0to15 from eventTree
  TH1I *Histo_ISR_ZmumuJet_Pt0to15_temp = new TH1I();
  string variable_ISR_ZmumuJet_Pt0to15 = var + ">>Histo_ISR_ZmumuJet_Pt0to15_temp" + limits;
  ISR_ZmumuJet_Pt0to15_miniTree->Draw(variable_ISR_ZmumuJet_Pt0to15.c_str(), cut.c_str());
  TH1I *Histo_ISR_ZmumuJet_Pt0to15 = (TH1I*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt0to15_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt15to20 from eventTree
  TH1I *Histo_ISR_ZmumuJet_Pt15to20_temp = new TH1I();
  string variable_ISR_ZmumuJet_Pt15to20 = var + ">>Histo_ISR_ZmumuJet_Pt15to20_temp" + limits;
  ISR_ZmumuJet_Pt15to20_miniTree->Draw(variable_ISR_ZmumuJet_Pt15to20.c_str(), cut.c_str());
  TH1I *Histo_ISR_ZmumuJet_Pt15to20 = (TH1I*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt15to20_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt20to30 from eventTree
  TH1I *Histo_ISR_ZmumuJet_Pt20to30_temp = new TH1I();
  string variable_ISR_ZmumuJet_Pt20to30 = var + ">>Histo_ISR_ZmumuJet_Pt20to30_temp" + limits;
  ISR_ZmumuJet_Pt20to30_miniTree->Draw(variable_ISR_ZmumuJet_Pt20to30.c_str(), cut.c_str());
  TH1I *Histo_ISR_ZmumuJet_Pt20to30 = (TH1I*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt20to30_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt30to50 from eventTree
  TH1I *Histo_ISR_ZmumuJet_Pt30to50_temp = new TH1I();
  string variable_ISR_ZmumuJet_Pt30to50 = var + ">>Histo_ISR_ZmumuJet_Pt30to50_temp" + limits;
  ISR_ZmumuJet_Pt30to50_miniTree->Draw(variable_ISR_ZmumuJet_Pt30to50.c_str(), cut.c_str());
  TH1I *Histo_ISR_ZmumuJet_Pt30to50 = (TH1I*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt30to50_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt50to80 from eventTree
  TH1I *Histo_ISR_ZmumuJet_Pt50to80_temp = new TH1I();
  string variable_ISR_ZmumuJet_Pt50to80 = var + ">>Histo_ISR_ZmumuJet_Pt50to80_temp" + limits;
  ISR_ZmumuJet_Pt50to80_miniTree->Draw(variable_ISR_ZmumuJet_Pt50to80.c_str(), cut.c_str());
  TH1I *Histo_ISR_ZmumuJet_Pt50to80 = (TH1I*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt50to80_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt80to120 from eventTree
  TH1I *Histo_ISR_ZmumuJet_Pt80to120_temp = new TH1I();
  string variable_ISR_ZmumuJet_Pt80to120 = var + ">>Histo_ISR_ZmumuJet_Pt80to120_temp" + limits;
  ISR_ZmumuJet_Pt80to120_miniTree->Draw(variable_ISR_ZmumuJet_Pt80to120.c_str(), cut.c_str());
  TH1I *Histo_ISR_ZmumuJet_Pt80to120 = (TH1I*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt80to120_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt120to170 from eventTree
  TH1I *Histo_ISR_ZmumuJet_Pt120to170_temp = new TH1I();
  string variable_ISR_ZmumuJet_Pt120to170 = var + ">>Histo_ISR_ZmumuJet_Pt120to170_temp" + limits;
  ISR_ZmumuJet_Pt120to170_miniTree->Draw(variable_ISR_ZmumuJet_Pt120to170.c_str(), cut.c_str());
  TH1I *Histo_ISR_ZmumuJet_Pt120to170 = (TH1I*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt120to170_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt170to230 from eventTree
  TH1I *Histo_ISR_ZmumuJet_Pt170to230_temp = new TH1I();
  string variable_ISR_ZmumuJet_Pt170to230 = var + ">>Histo_ISR_ZmumuJet_Pt170to230_temp" + limits;
  ISR_ZmumuJet_Pt170to230_miniTree->Draw(variable_ISR_ZmumuJet_Pt170to230.c_str(), cut.c_str());
  TH1I *Histo_ISR_ZmumuJet_Pt170to230 = (TH1I*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt170to230_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt230to300 from eventTree
  TH1I *Histo_ISR_ZmumuJet_Pt230to300_temp = new TH1I();
  string variable_ISR_ZmumuJet_Pt230to300 = var + ">>Histo_ISR_ZmumuJet_Pt230to300_temp" + limits;
  ISR_ZmumuJet_Pt230to300_miniTree->Draw(variable_ISR_ZmumuJet_Pt230to300.c_str(), cut.c_str());
  TH1I *Histo_ISR_ZmumuJet_Pt230to300 = (TH1I*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt230to300_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt300toInf from eventTree
  TH1I *Histo_ISR_ZmumuJet_Pt300toInf_temp = new TH1I();
  string variable_ISR_ZmumuJet_Pt300toInf = var + ">>Histo_ISR_ZmumuJet_Pt300toInf_temp" + limits;
  ISR_ZmumuJet_Pt300toInf_miniTree->Draw(variable_ISR_ZmumuJet_Pt300toInf.c_str(), cut.c_str());
  TH1I *Histo_ISR_ZmumuJet_Pt300toInf = (TH1I*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt300toInf_temp");
  c1->Clear();

  // TODO: implement drawUnderOverFsubleading

  // Get the number of entries for further normalization
  double a = Histo_Data->Integral();
/*
  double b_PhotonJet_Pt15 = Histo_PhotonJet_Pt15->Integral();
  if( (a==0.0) || (b_PhotonJet_Pt15==0.0) ){
    cout << "no entries to plots" <<endl;
    return; 
  }*/
  // Normalize
  Histo_Data->Sumw2(); // In order to have the correct error bars on data after renormalization
  // // Normalize MC and Data to 1
  //Histo_Data->Scale((double)((double)1.0/(double)a));
  //Histo_MC->Scale((double)((double)1.0/(double)b));
  // // Normalize MC to Data number of entries
  double integratedLuminosity = 2859492.190e-06;

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
  double XSectionFSR_ZmumuJet_Pt0to15 = 4.434e+03;
  double XSectionFSR_ZmumuJet_Pt15to20 = 1.454e+02;
  double XSectionFSR_ZmumuJet_Pt20to30 = 1.318e+02;
  double XSectionFSR_ZmumuJet_Pt30to50 = 8.438e+01;
  double XSectionFSR_ZmumuJet_Pt50to80 = 3.235e+01;
  double XSectionFSR_ZmumuJet_Pt80to120 = 9.981e+00;
  double XSectionFSR_ZmumuJet_Pt120to170 = 2.760e+00;
  double XSectionFSR_ZmumuJet_Pt170to230 = 7.241e-01;
  double XSectionFSR_ZmumuJet_Pt230to300 = 1.946e-01;
  double XSectionFSR_ZmumuJet_Pt300toInf = 7.627e-02;
  double XSectionISR_ZmumuJet_Pt0to15 = 4.434e+03;
  double XSectionISR_ZmumuJet_Pt15to20 = 1.454e+02;
  double XSectionISR_ZmumuJet_Pt20to30 = 1.318e+02;
  double XSectionISR_ZmumuJet_Pt30to50 = 8.438e+01;
  double XSectionISR_ZmumuJet_Pt50to80 = 3.235e+01;
  double XSectionISR_ZmumuJet_Pt80to120 = 9.981e+00;
  double XSectionISR_ZmumuJet_Pt120to170 = 2.760e+00;
  double XSectionISR_ZmumuJet_Pt170to230 = 7.241e-01;
  double XSectionISR_ZmumuJet_Pt230to300 = 1.946e-01;
  double XSectionISR_ZmumuJet_Pt300toInf = 7.627e-02;

  double InitialNumberQCD_Pt15 = 6116800;
  double InitialNumberQCD_Pt30 = 5093840;
  double InitialNumberQCD_Pt80 = 3229000;
  double InitialNumberQCD_Pt170 = 3122500;
  double InitialNumberQCD_Pt300 = 3269645;
  double InitialNumberQCD_Pt470 = 2083653;
  double InitialNumberPhotonJet_Pt15 = 1221770;
  double InitialNumberPhotonJet_Pt30 = 1025300;
  double InitialNumberPhotonJet_Pt80 = 1287711;
  double InitialNumberPhotonJet_Pt170 = 1209600;
  double InitialNumberPhotonJet_Pt300 = 1033240;
  double InitialNumberTTbarJets_Tauola = 1463572;
  double InitialNumberWJets_7TeV = 10218854;
  double InitialNumberZJets_7TeV = 1047008;
  double InitialNumberQCD_Mu_Pt20to30 = 10985188;
  double InitialNumberQCD_Mu_Pt30to50 = 6931182;
  double InitialNumberQCD_Mu_Pt50to80 = 2542308;
  double InitialNumberQCD_Mu_Pt80to120 = 523053;
  double InitialNumberQCD_Mu_Pt120to170 = 316630;
  double InitialNumberQCD_Mu_Pt170toInf = 262036;
  double InitialNumberInclusiveMu15 = 5120334;
  double InitialNumberFSR_ZmumuJet_Pt0to15 = 235420;
  double InitialNumberFSR_ZmumuJet_Pt15to20 = 222730;
  double InitialNumberFSR_ZmumuJet_Pt20to30 = 164190;
  double InitialNumberFSR_ZmumuJet_Pt30to50 = 163920;
  double InitialNumberFSR_ZmumuJet_Pt50to80 = 106016;
  double InitialNumberFSR_ZmumuJet_Pt80to120 = 107759;
  double InitialNumberFSR_ZmumuJet_Pt120to170 = 177408;
  double InitialNumberFSR_ZmumuJet_Pt170to230 = 178400;
  double InitialNumberFSR_ZmumuJet_Pt230to300 = 176485;
  double InitialNumberFSR_ZmumuJet_Pt300toInf = 109316;
  double InitialNumberISR_ZmumuJet_Pt0to15 = 235420;
  double InitialNumberISR_ZmumuJet_Pt15to20 = 222730;
  double InitialNumberISR_ZmumuJet_Pt20to30 = 164190;
  double InitialNumberISR_ZmumuJet_Pt30to50 = 163920;
  double InitialNumberISR_ZmumuJet_Pt50to80 = 106016;
  double InitialNumberISR_ZmumuJet_Pt80to120 = 107759;
  double InitialNumberISR_ZmumuJet_Pt120to170 = 177408;
  double InitialNumberISR_ZmumuJet_Pt170to230 = 178400;
  double InitialNumberISR_ZmumuJet_Pt230to300 = 176485;
  double InitialNumberISR_ZmumuJet_Pt300toInf = 109316;

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
  Histo_FSR_ZmumuJet_Pt0to15->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt0to15) / (double)(InitialNumberFSR_ZmumuJet_Pt0to15)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt15to20->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt15to20) / (double)(InitialNumberFSR_ZmumuJet_Pt15to20)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt20to30->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt20to30) / (double)(InitialNumberFSR_ZmumuJet_Pt20to30)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt30to50->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt30to50) / (double)(InitialNumberFSR_ZmumuJet_Pt30to50)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt50to80->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt50to80) / (double)(InitialNumberFSR_ZmumuJet_Pt50to80)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt80to120->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt80to120) / (double)(InitialNumberFSR_ZmumuJet_Pt80to120)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt120to170->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt120to170) / (double)(InitialNumberFSR_ZmumuJet_Pt120to170)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt170to230->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt170to230) / (double)(InitialNumberFSR_ZmumuJet_Pt170to230)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt230to300->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt230to300) / (double)(InitialNumberFSR_ZmumuJet_Pt230to300)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt300toInf->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt300toInf) / (double)(InitialNumberFSR_ZmumuJet_Pt300toInf)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt0to15->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt0to15) / (double)(InitialNumberISR_ZmumuJet_Pt0to15)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt15to20->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt15to20) / (double)(InitialNumberISR_ZmumuJet_Pt15to20)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt20to30->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt20to30) / (double)(InitialNumberISR_ZmumuJet_Pt20to30)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt30to50->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt30to50) / (double)(InitialNumberISR_ZmumuJet_Pt30to50)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt50to80->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt50to80) / (double)(InitialNumberISR_ZmumuJet_Pt50to80)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt80to120->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt80to120) / (double)(InitialNumberISR_ZmumuJet_Pt80to120)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt120to170->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt120to170) / (double)(InitialNumberISR_ZmumuJet_Pt120to170)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt170to230->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt170to230) / (double)(InitialNumberISR_ZmumuJet_Pt170to230)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt230to300->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt230to300) / (double)(InitialNumberISR_ZmumuJet_Pt230to300)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt300toInf->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt300toInf) / (double)(InitialNumberISR_ZmumuJet_Pt300toInf)) * (double)integratedLuminosity));

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

  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt15to20);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt20to30);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt30to50);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt50to80);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt80to120);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt120to170);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt170to230);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt230to300);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt300toInf);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt15to20);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt20to30);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt30to50);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt50to80);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt80to120);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt120to170);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt170to230);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt230to300);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt300toInf);

// ttbar
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_TTbarJets_Tauola);
// *** stacked
  Histo_PhotonJet_Pt15->Add(Histo_ISR_ZmumuJet_Pt0to15);
// *** stacked
  Histo_WJets_7TeV->Add(Histo_PhotonJet_Pt15);
// *** stacked
  Histo_QCD_Pt15->Add(Histo_WJets_7TeV);
  Histo_QCD_Mu_Pt20to30->Add(Histo_WJets_7TeV);
  Histo_InclusiveMu15->Add(Histo_WJets_7TeV);
// *** stacked
//  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_QCD_Pt15);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_QCD_Mu_Pt20to30);
//  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_InclusiveMu15);
// *** stacked
  Histo_ZJets_7TeV->Add(Histo_QCD_Pt15);
  Histo_ZJets_7TeV->Add(Histo_QCD_Mu_Pt20to30);
  Histo_ZJets_7TeV->Add(Histo_InclusiveMu15);


	// Total MC histo for comupting min/max
//  TH1I *Histo_allMC = new TH1I(*Histo_QCD_Mu_Pt20to30);
//  Histo_allMC->Add(Histo_QCD_Pt15);
//  Histo_allMC->Add(Histo_InclusiveMu15);
//  Histo_allMC->Add(Histo_FSR_ZmumuJet_Pt0to15);
//  Histo_allMC->Add(Histo_ZJets_7TeV);
//  Histo_allMC->Add(Histo_WJets_7TeV);
//  Histo_allMC->Add(Histo_TTbarJets_Tauola);
//  Histo_allMC->Add(Histo_PhotonJet_Pt15);

  // Get the maxs and the mins to further correct the Y-axis
  double dataMax = Histo_Data->GetMaximum();
  double YMax = dataMax;
/*  double PhotonJet_Pt15Max = Histo_PhotonJet_Pt15->GetMaximum();
  YMax = max(YMax, PhotonJet_Pt15Max);
  double QCD_Pt15Max = Histo_QCD_Pt15->GetMaximum();
  YMax = max(YMax, QCD_Pt15Max);
  double TTbarJets_TauolaMax = Histo_TTbarJets_Tauola->GetMaximum();
  YMax = max(YMax, TTbarJets_TauolaMax);
  double WJets_7TeVMax = Histo_WJets_7TeV->GetMaximum();
  YMax = max(YMax, WJets_7TeVMax);
  double QCD_Mu_Pt20to30Max = Histo_QCD_Mu_Pt20to30->GetMaximum();
  YMax = max(YMax, QCD_Mu_Pt20to30Max);
  double InclusiveMu15Max = Histo_InclusiveMu15->GetMaximum();
  YMax = max(YMax, InclusiveMu15Max);
*/
//  double ZJets_7TeVMax = Histo_ZJets_7TeV->GetMaximum();
//  YMax = max(YMax, ZJets_7TeVMax);
  double FSR_ZmumuJet_Pt0to15Max = Histo_FSR_ZmumuJet_Pt0to15->GetMaximum();
  YMax = max(YMax, FSR_ZmumuJet_Pt0to15Max);
/*
	double allMCMax = Histo_allMC->GetMaximum();
  YMax = max(YMax, allMCMax);
*/
  double dataMin = YMax;
  double PhotonJet_Pt15Min = YMax;
//  double QCD_Pt15Min = YMax;
  double TTbarJets_TauolaMin = YMax;
  double WJets_7TeVMin = YMax;
  double ZJets_7TeVMin = YMax;
  double QCD_Mu_Pt20to30Min = YMax;
//  double InclusiveMu15Min = YMax;
  double FSR_ZmumuJet_Pt0to15Min = YMax;
  double ISR_ZmumuJet_Pt0to15Min = YMax;

	double allMCMin = YMax;

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
/*  for( int ibin=1 ; ibin<Histo_QCD_Pt15->GetNbinsX() ; ibin++ ){
    if( ((Histo_QCD_Pt15->GetBinContent(ibin))!=0) && ((Histo_QCD_Pt15->GetBinContent(ibin))<QCD_Pt15Min) ){
      QCD_Pt15Min = Histo_QCD_Pt15->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, QCD_Pt15Min);*/
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
//  YMin = min(YMin, ZJets_7TeVMin);
  for( int ibin=1 ; ibin<Histo_QCD_Mu_Pt20to30->GetNbinsX() ; ibin++ ){
    if( ((Histo_QCD_Mu_Pt20to30->GetBinContent(ibin))!=0) && ((Histo_QCD_Mu_Pt20to30->GetBinContent(ibin))<QCD_Mu_Pt20to30Min) ){
      QCD_Mu_Pt20to30Min = Histo_QCD_Mu_Pt20to30->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, QCD_Mu_Pt20to30Min);
/*  for( int ibin=1 ; ibin<Histo_InclusiveMu15->GetNbinsX() ; ibin++ ){
    if( ((Histo_InclusiveMu15->GetBinContent(ibin))!=0) && ((Histo_InclusiveMu15->GetBinContent(ibin))<InclusiveMu15Min) ){
      InclusiveMu15Min = Histo_InclusiveMu15->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, InclusiveMu15Min);*/
  for( int ibin=1 ; ibin<Histo_FSR_ZmumuJet_Pt0to15->GetNbinsX() ; ibin++ ){
    if( ((Histo_FSR_ZmumuJet_Pt0to15->GetBinContent(ibin))!=0) && ((Histo_FSR_ZmumuJet_Pt0to15->GetBinContent(ibin))<FSR_ZmumuJet_Pt0to15Min) ){
      FSR_ZmumuJet_Pt0to15Min = Histo_FSR_ZmumuJet_Pt0to15->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, FSR_ZmumuJet_Pt0to15Min);
  for( int ibin=1 ; ibin<Histo_ISR_ZmumuJet_Pt0to15->GetNbinsX() ; ibin++ ){
    if( ((Histo_ISR_ZmumuJet_Pt0to15->GetBinContent(ibin))!=0) && ((Histo_ISR_ZmumuJet_Pt0to15->GetBinContent(ibin))<ISR_ZmumuJet_Pt0to15Min) ){
      ISR_ZmumuJet_Pt0to15Min = Histo_ISR_ZmumuJet_Pt0to15->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, ISR_ZmumuJet_Pt0to15Min);
/*
	for( int ibin=1 ; ibin<Histo_allMC->GetNbinsX() ; ibin++ ){
    if( ((Histo_allMC->GetBinContent(ibin))!=0) && ((Histo_allMC->GetBinContent(ibin))<allMCMin) ){
      allMCMin = Histo_allMC->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, allMCMin);
*/
//  cout << "YMax= "<< YMax << "\t\tYMin= " << YMin << endl;
  double YMin_lin = (double)YMin / (double)10.0;
//  double Range_lin = ((double)(YMax - YMin_lin)) / ((double)(0.8));
  double Range_lin = ((double)(YMax - YMin_lin)) / ((double)(1.0));
  double YMax_lin = 0.2*Range_lin + YMax;
/*
  double Range_lin = ((double)(YMax - YMin)) / ((double)(0.77));
  double YMax_lin = 0.2*Range_lin + YMax;
  double YMin_lin = max(YMin - 0.03*Range_lin, (double)YMin / (double)10.0);
*/
  double Range_log = ((double)(log10(YMax) - log10(YMin))) / ((double)(0.77));
//  cout << "Range_lin= " << Range_lin << "\t\tRange_log= " << Range_log << endl;
  double YMax_log = pow(10.0, 0.2*Range_log + log10(YMax));
  double YMin_log = pow(10.0, log10(YMin) - 0.03*Range_log);
//  cout << "YMin_lin= " << YMin_lin << "\t\tYMax_lin= " << YMax_lin << endl;
//  cout << "YMin_log= " << YMin_log << "\t\tYMax_log= " << YMax_log << endl;


  // Setup the histo and canvas names and title
  string data_name = "Data_" + pic + "_" + name;
  string mc_name = "MC_" + pic + "_" + name;
  string canvas_name = "DataMC_" + pic + "_" + name;
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

  TLegend *legend = new TLegend(0.65, 0.80, 0.90, 0.93, "");
	if( doFit ){
		legend->SetX1(0.47);
		legend->SetX2(0.65);
	}
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

  // // Second: draw MC on the same canvas
  Histo_QCD_Pt15->SetLineColor(kBlack);
  Histo_QCD_Pt15->SetFillColor(kGreen+3);
  Histo_QCD_Pt15->SetFillStyle(3001);
  Histo_QCD_Pt15->SetMaximum(YMax_lin);
  Histo_QCD_Pt15->SetMinimum(YMin_lin);
//  Histo_QCD_Pt15->Draw("same");
//  legend->AddEntry(Histo_QCD_Pt15->GetName(), "QCD", "f");

  Histo_QCD_Mu_Pt20to30->SetLineColor(kBlack);
  Histo_QCD_Mu_Pt20to30->SetFillColor(kGreen);
  Histo_QCD_Mu_Pt20to30->SetFillStyle(3001);
  Histo_QCD_Mu_Pt20to30->SetMaximum(YMax_lin);
  Histo_QCD_Mu_Pt20to30->SetMinimum(YMin_lin);

  Histo_InclusiveMu15->SetLineColor(kBlack);
  Histo_InclusiveMu15->SetFillColor(kGreen-6);
  Histo_InclusiveMu15->SetFillStyle(3001);
  Histo_InclusiveMu15->SetMaximum(YMax_lin);
  Histo_InclusiveMu15->SetMinimum(YMin_lin);
//  Histo_InclusiveMu15->Draw("same");  
//  legend->AddEntry(Histo_InclusiveMu15->GetName(), "InclusiveMu15", "f");

  Histo_WJets_7TeV->SetLineColor(kBlack);
  Histo_WJets_7TeV->SetFillColor(kMagenta+3);
  Histo_WJets_7TeV->SetFillStyle(3001);
  Histo_WJets_7TeV->SetMaximum(YMax_lin);
  Histo_WJets_7TeV->SetMinimum(YMin_lin);

  Histo_TTbarJets_Tauola->SetLineColor(kBlack);
  Histo_TTbarJets_Tauola->SetFillColor(kBlue);
  Histo_TTbarJets_Tauola->SetFillStyle(3001);
  Histo_TTbarJets_Tauola->SetMaximum(YMax_lin);
  Histo_TTbarJets_Tauola->SetMinimum(YMin_lin);

  Histo_PhotonJet_Pt15->SetLineColor(kBlack);
  Histo_PhotonJet_Pt15->SetFillColor(kMagenta);
  Histo_PhotonJet_Pt15->SetFillStyle(3001);
  Histo_PhotonJet_Pt15->SetMaximum(YMax_lin);
  Histo_PhotonJet_Pt15->SetMinimum(YMin_lin);

  Histo_FSR_ZmumuJet_Pt0to15->SetLineColor(kBlack);
  Histo_FSR_ZmumuJet_Pt0to15->SetFillColor(kRed);
  Histo_FSR_ZmumuJet_Pt0to15->SetFillStyle(3001);
  Histo_FSR_ZmumuJet_Pt0to15->SetMaximum(YMax_lin);
  Histo_FSR_ZmumuJet_Pt0to15->SetMinimum(YMin_lin);

  Histo_ISR_ZmumuJet_Pt0to15->SetLineColor(kBlack);
  Histo_ISR_ZmumuJet_Pt0to15->SetFillColor(kOrange);
  Histo_ISR_ZmumuJet_Pt0to15->SetFillStyle(3001);
  Histo_ISR_ZmumuJet_Pt0to15->SetMaximum(YMax_lin);
  Histo_ISR_ZmumuJet_Pt0to15->SetMinimum(YMin_lin);

  Histo_ZJets_7TeV->SetLineColor(kBlack);
  Histo_ZJets_7TeV->SetFillColor(kOrange);
  Histo_ZJets_7TeV->SetFillStyle(3001);
  Histo_ZJets_7TeV->SetMaximum(YMax_lin);
  Histo_ZJets_7TeV->SetMinimum(YMin_lin);

  Histo_Data->Draw("E1");
  legend->AddEntry(Histo_Data->GetName(), "Data", "lp");
  Histo_FSR_ZmumuJet_Pt0to15->Draw("same");
//  Histo_ZJets_7TeV->Draw("same");
  Histo_QCD_Mu_Pt20to30->Draw("same");
  Histo_WJets_7TeV->Draw("same");
  Histo_PhotonJet_Pt15->Draw("same");
  Histo_ISR_ZmumuJet_Pt0to15->Draw("same");
  Histo_TTbarJets_Tauola->Draw("same");
  legend->AddEntry(Histo_TTbarJets_Tauola->GetName(), "TTbarJets", "f");
  legend->AddEntry(Histo_ISR_ZmumuJet_Pt0to15->GetName(), "ZmumuJet (no FSR)", "f");
  legend->AddEntry(Histo_PhotonJet_Pt15->GetName(), "PhotonJet", "f");
  legend->AddEntry(Histo_WJets_7TeV->GetName(), "WJets", "f");
  legend->AddEntry(Histo_QCD_Mu_Pt20to30->GetName(), "QCD Mu", "f");
//  legend->AddEntry(Histo_ZJets_7TeV->GetName(), "ZJets madgraph", "f");
  legend->AddEntry(Histo_FSR_ZmumuJet_Pt0to15->GetName(), "ZmumuJet FSR", "f");

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
  string PicName="gif/DataMC_" + pic + "_" + name + ".gif";
  c1->Print(PicName.c_str());
  PicName="eps/DataMC_" + pic + "_" + name + ".eps";
  c1->Print(PicName.c_str());
  string convert = "convert eps/DataMC_" + pic + "_" + name + ".eps" + " pdf/DataMC_" + pic + "_" + name + ".pdf";
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
    Histo_FSR_ZmumuJet_Pt0to15->SetMaximum(YMax_log);
    Histo_FSR_ZmumuJet_Pt0to15->SetMinimum(YMin_log);
    Histo_FSR_ZmumuJet_Pt0to15->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
    Histo_ISR_ZmumuJet_Pt0to15->SetMaximum(YMax_log);
    Histo_ISR_ZmumuJet_Pt0to15->SetMinimum(YMin_log);
    Histo_ISR_ZmumuJet_Pt0to15->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
    c1->SetLogy(1);
    c1->Update();
    c1->Draw();
    string PicName_log="gif/DataMC_" + pic + "_" + name + "_log.gif";
    c1->Print(PicName_log.c_str());
    PicName="eps/DataMC_" + pic + "_" + name + "_log.eps";
    c1->Print(PicName.c_str());
    string convert = "convert eps/DataMC_" + pic + "_" + name + "_log.eps" + " pdf/DataMC_" + pic + "_" + name + "_log.pdf";
    system(convert.c_str());
    c1->SetLogy(0);
    c1->Update();
  }

  // Clean the memory
  c1->Clear();
  legend->Delete();
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
  Histo_FSR_ZmumuJet_Pt0to15_temp->Delete();
  Histo_FSR_ZmumuJet_Pt0to15->Delete();
  Histo_FSR_ZmumuJet_Pt15to20_temp->Delete();
  Histo_FSR_ZmumuJet_Pt15to20->Delete();
  Histo_FSR_ZmumuJet_Pt20to30_temp->Delete();
  Histo_FSR_ZmumuJet_Pt20to30->Delete();
  Histo_FSR_ZmumuJet_Pt30to50_temp->Delete();
  Histo_FSR_ZmumuJet_Pt30to50->Delete();
  Histo_FSR_ZmumuJet_Pt50to80_temp->Delete();
  Histo_FSR_ZmumuJet_Pt50to80->Delete();
  Histo_FSR_ZmumuJet_Pt80to120_temp->Delete();
  Histo_FSR_ZmumuJet_Pt80to120->Delete();
  Histo_FSR_ZmumuJet_Pt120to170_temp->Delete();
  Histo_FSR_ZmumuJet_Pt120to170->Delete();
  Histo_FSR_ZmumuJet_Pt170to230_temp->Delete();
  Histo_FSR_ZmumuJet_Pt170to230->Delete();
  Histo_FSR_ZmumuJet_Pt230to300_temp->Delete();
  Histo_FSR_ZmumuJet_Pt230to300->Delete();
  Histo_FSR_ZmumuJet_Pt300toInf_temp->Delete();
  Histo_FSR_ZmumuJet_Pt300toInf->Delete();
  Histo_ISR_ZmumuJet_Pt0to15_temp->Delete();
  Histo_ISR_ZmumuJet_Pt0to15->Delete();
  Histo_ISR_ZmumuJet_Pt15to20_temp->Delete();
  Histo_ISR_ZmumuJet_Pt15to20->Delete();
  Histo_ISR_ZmumuJet_Pt20to30_temp->Delete();
  Histo_ISR_ZmumuJet_Pt20to30->Delete();
  Histo_ISR_ZmumuJet_Pt30to50_temp->Delete();
  Histo_ISR_ZmumuJet_Pt30to50->Delete();
  Histo_ISR_ZmumuJet_Pt50to80_temp->Delete();
  Histo_ISR_ZmumuJet_Pt50to80->Delete();
  Histo_ISR_ZmumuJet_Pt80to120_temp->Delete();
  Histo_ISR_ZmumuJet_Pt80to120->Delete();
  Histo_ISR_ZmumuJet_Pt120to170_temp->Delete();
  Histo_ISR_ZmumuJet_Pt120to170->Delete();
  Histo_ISR_ZmumuJet_Pt170to230_temp->Delete();
  Histo_ISR_ZmumuJet_Pt170to230->Delete();
  Histo_ISR_ZmumuJet_Pt230to300_temp->Delete();
  Histo_ISR_ZmumuJet_Pt230to300->Delete();
  Histo_ISR_ZmumuJet_Pt300toInf_temp->Delete();
  Histo_ISR_ZmumuJet_Pt300toInf->Delete();

}


void DrawDataMCplot_TH2F(TTree *Data_miniTree, TTree *QCD_Pt15_miniTree, TTree *QCD_Pt30_miniTree, TTree *QCD_Pt80_miniTree, TTree *QCD_Pt170_miniTree, TTree *QCD_Pt300_miniTree, TTree *QCD_Pt470_miniTree, TTree *PhotonJet_Pt15_miniTree, TTree *PhotonJet_Pt30_miniTree, TTree *PhotonJet_Pt80_miniTree, TTree *PhotonJet_Pt170_miniTree, TTree *PhotonJet_Pt300_miniTree, TTree *TTbarJets_Tauola_miniTree, TTree *WJets_7TeV_miniTree, TTree *ZJets_7TeV_miniTree, TTree *QCD_Mu_Pt20to30_miniTree, TTree *QCD_Mu_Pt30to50_miniTree, TTree *QCD_Mu_Pt50to80_miniTree, TTree *QCD_Mu_Pt80to120_miniTree, TTree *QCD_Mu_Pt120to170_miniTree, TTree *QCD_Mu_Pt170toInf_miniTree, TTree *InclusiveMu15_miniTree, TTree *FSR_ZmumuJet_Pt0to15_miniTree, TTree *FSR_ZmumuJet_Pt15to20_miniTree, TTree *FSR_ZmumuJet_Pt20to30_miniTree, TTree *FSR_ZmumuJet_Pt30to50_miniTree, TTree *FSR_ZmumuJet_Pt50to80_miniTree, TTree *FSR_ZmumuJet_Pt80to120_miniTree, TTree *FSR_ZmumuJet_Pt120to170_miniTree, TTree *FSR_ZmumuJet_Pt170to230_miniTree, TTree *FSR_ZmumuJet_Pt230to300_miniTree, TTree *FSR_ZmumuJet_Pt300toInf_miniTree, TTree *ISR_ZmumuJet_Pt0to15_miniTree, TTree *ISR_ZmumuJet_Pt15to20_miniTree, TTree *ISR_ZmumuJet_Pt20to30_miniTree, TTree *ISR_ZmumuJet_Pt30to50_miniTree, TTree *ISR_ZmumuJet_Pt50to80_miniTree, TTree *ISR_ZmumuJet_Pt80to120_miniTree, TTree *ISR_ZmumuJet_Pt120to170_miniTree, TTree *ISR_ZmumuJet_Pt170to230_miniTree, TTree *ISR_ZmumuJet_Pt230to300_miniTree, TTree *ISR_ZmumuJet_Pt300toInf_miniTree, string var1, string var2, string limits, string cut, string name, string Title_var1, string Title_var2, string pic, bool inlog_var1, bool inlog_var2, TCanvas *c1, bool doFit){

  // Get Histo_Data from eventTree
  TH2F *Histo_Data_temp = new TH2F();
  string variable_Data = var2 + ":" + var1 + ">>Histo_Data_temp" + limits;
  Data_miniTree->Draw(variable_Data.c_str(), cut.c_str());
  TH2F *Histo_Data = (TH2F*)gDirectory->Get("Histo_Data_temp");
  c1->Clear();

  // Get Histo_PhotonJet_Pt15 from eventTree
  TH2F *Histo_PhotonJet_Pt15_temp = new TH2F();
  string variable_PhotonJet_Pt15 = var2 + ":" + var1 + ">>Histo_PhotonJet_Pt15_temp" + limits;
  PhotonJet_Pt15_miniTree->Draw(variable_PhotonJet_Pt15.c_str(), cut.c_str());
  TH2F *Histo_PhotonJet_Pt15 = (TH2F*)gDirectory->Get("Histo_PhotonJet_Pt15_temp");
  c1->Clear();

  // Get Histo_PhotonJet_Pt30 from eventTree
  TH2F *Histo_PhotonJet_Pt30_temp = new TH2F();
  string variable_PhotonJet_Pt30 = var2 + ":" + var1 + ">>Histo_PhotonJet_Pt30_temp" + limits;
  PhotonJet_Pt30_miniTree->Draw(variable_PhotonJet_Pt30.c_str(), cut.c_str());
  TH2F *Histo_PhotonJet_Pt30 = (TH2F*)gDirectory->Get("Histo_PhotonJet_Pt30_temp");
  c1->Clear();

  // Get Histo_PhotonJet_Pt80 from eventTree
  TH2F *Histo_PhotonJet_Pt80_temp = new TH2F();
  string variable_PhotonJet_Pt80 = var2 + ":" + var1 + ">>Histo_PhotonJet_Pt80_temp" + limits;
  PhotonJet_Pt80_miniTree->Draw(variable_PhotonJet_Pt80.c_str(), cut.c_str());
  TH2F *Histo_PhotonJet_Pt80 = (TH2F*)gDirectory->Get("Histo_PhotonJet_Pt80_temp");
  c1->Clear();

  // Get Histo_PhotonJet_Pt170 from eventTree
  TH2F *Histo_PhotonJet_Pt170_temp = new TH2F();
  string variable_PhotonJet_Pt170 = var2 + ":" + var1 + ">>Histo_PhotonJet_Pt170_temp" + limits;
  PhotonJet_Pt170_miniTree->Draw(variable_PhotonJet_Pt170.c_str(), cut.c_str());
  TH2F *Histo_PhotonJet_Pt170 = (TH2F*)gDirectory->Get("Histo_PhotonJet_Pt170_temp");
  c1->Clear();

  // Get Histo_PhotonJet_Pt300 from eventTree
  TH2F *Histo_PhotonJet_Pt300_temp = new TH2F();
  string variable_PhotonJet_Pt300 = var2 + ":" + var1 + ">>Histo_PhotonJet_Pt300_temp" + limits;
  PhotonJet_Pt300_miniTree->Draw(variable_PhotonJet_Pt300.c_str(), cut.c_str());
  TH2F *Histo_PhotonJet_Pt300 = (TH2F*)gDirectory->Get("Histo_PhotonJet_Pt300_temp");
  c1->Clear();

  // Get Histo_QCD_Pt15 from eventTree
  TH2F *Histo_QCD_Pt15_temp = new TH2F();
  string variable_QCD_Pt15 = var2 + ":" + var1 + ">>Histo_QCD_Pt15_temp" + limits;
  QCD_Pt15_miniTree->Draw(variable_QCD_Pt15.c_str(), cut.c_str());
  TH2F *Histo_QCD_Pt15 = (TH2F*)gDirectory->Get("Histo_QCD_Pt15_temp");
  c1->Clear();

  // Get Histo_QCD_Pt30 from eventTree
  TH2F *Histo_QCD_Pt30_temp = new TH2F();
  string variable_QCD_Pt30 = var2 + ":" + var1 + ">>Histo_QCD_Pt30_temp" + limits;
  QCD_Pt30_miniTree->Draw(variable_QCD_Pt30.c_str(), cut.c_str());
  TH2F *Histo_QCD_Pt30 = (TH2F*)gDirectory->Get("Histo_QCD_Pt30_temp");

  // Get Histo_QCD_Pt80 from eventTree
  TH2F *Histo_QCD_Pt80_temp = new TH2F();
  string variable_QCD_Pt80 = var2 + ":" + var1 + ">>Histo_QCD_Pt80_temp" + limits;
  QCD_Pt80_miniTree->Draw(variable_QCD_Pt80.c_str(), cut.c_str());
  TH2F *Histo_QCD_Pt80 = (TH2F*)gDirectory->Get("Histo_QCD_Pt80_temp");
  c1->Clear();

  // Get Histo_QCD_Pt170 from eventTree
  TH2F *Histo_QCD_Pt170_temp = new TH2F();
  string variable_QCD_Pt170 = var2 + ":" + var1 + ">>Histo_QCD_Pt170_temp" + limits;
  QCD_Pt170_miniTree->Draw(variable_QCD_Pt170.c_str(), cut.c_str());
  TH2F *Histo_QCD_Pt170 = (TH2F*)gDirectory->Get("Histo_QCD_Pt170_temp");
  c1->Clear();

  // Get Histo_QCD_Pt300 from eventTree
  TH2F *Histo_QCD_Pt300_temp = new TH2F();
  string variable_QCD_Pt300 = var2 + ":" + var1 + ">>Histo_QCD_Pt300_temp" + limits;
  QCD_Pt300_miniTree->Draw(variable_QCD_Pt300.c_str(), cut.c_str());
  TH2F *Histo_QCD_Pt300 = (TH2F*)gDirectory->Get("Histo_QCD_Pt300_temp");
  c1->Clear();

  // Get Histo_QCD_Pt470 from eventTree
  TH2F *Histo_QCD_Pt470_temp = new TH2F();
  string variable_QCD_Pt470 = var2 + ":" + var1 + ">>Histo_QCD_Pt470_temp" + limits;
  QCD_Pt470_miniTree->Draw(variable_QCD_Pt470.c_str(), cut.c_str());
  TH2F *Histo_QCD_Pt470 = (TH2F*)gDirectory->Get("Histo_QCD_Pt470_temp");
  c1->Clear();

  // Get Histo_TTbarJets_Tauola from eventTree
  TH2F *Histo_TTbarJets_Tauola_temp = new TH2F();
  string variable_TTbarJets_Tauola = var2 + ":" + var1 + ">>Histo_TTbarJets_Tauola_temp" + limits;
  TTbarJets_Tauola_miniTree->Draw(variable_TTbarJets_Tauola.c_str(), cut.c_str());
  TH2F *Histo_TTbarJets_Tauola = (TH2F*)gDirectory->Get("Histo_TTbarJets_Tauola_temp");
  c1->Clear();

  // Get Histo_WJets_7TeV from eventTree
  TH2F *Histo_WJets_7TeV_temp = new TH2F();
  string variable_WJets_7TeV = var2 + ":" + var1 + ">>Histo_WJets_7TeV_temp" + limits;
  WJets_7TeV_miniTree->Draw(variable_WJets_7TeV.c_str(), cut.c_str());
  TH2F *Histo_WJets_7TeV = (TH2F*)gDirectory->Get("Histo_WJets_7TeV_temp");
  c1->Clear();

  // Get Histo_ZJets_7TeV from eventTree
  TH2F *Histo_ZJets_7TeV_temp = new TH2F();
  string variable_ZJets_7TeV = var2 + ":" + var1 + ">>Histo_ZJets_7TeV_temp" + limits;
  ZJets_7TeV_miniTree->Draw(variable_ZJets_7TeV.c_str(), cut.c_str());
  TH2F *Histo_ZJets_7TeV = (TH2F*)gDirectory->Get("Histo_ZJets_7TeV_temp");
  c1->Clear();

  // Get Histo_QCD_Mu_Pt20to30 from eventTree
  TH2F *Histo_QCD_Mu_Pt20to30_temp = new TH2F();
  string variable_QCD_Mu_Pt20to30 = var2 + ":" + var1 + ">>Histo_QCD_Mu_Pt20to30_temp" + limits;
  QCD_Mu_Pt20to30_miniTree->Draw(variable_QCD_Mu_Pt20to30.c_str(), cut.c_str());
  TH2F *Histo_QCD_Mu_Pt20to30 = (TH2F*)gDirectory->Get("Histo_QCD_Mu_Pt20to30_temp");
  c1->Clear();

  // Get Histo_QCD_Mu_Pt30to50 from eventTree
  TH2F *Histo_QCD_Mu_Pt30to50_temp = new TH2F();
  string variable_QCD_Mu_Pt30to50 = var2 + ":" + var1 + ">>Histo_QCD_Mu_Pt30to50_temp" + limits;
  QCD_Mu_Pt30to50_miniTree->Draw(variable_QCD_Mu_Pt30to50.c_str(), cut.c_str());
  TH2F *Histo_QCD_Mu_Pt30to50 = (TH2F*)gDirectory->Get("Histo_QCD_Mu_Pt30to50_temp");
  c1->Clear();

  // Get Histo_QCD_Mu_Pt50to80 from eventTree
  TH2F *Histo_QCD_Mu_Pt50to80_temp = new TH2F();
  string variable_QCD_Mu_Pt50to80 = var2 + ":" + var1 + ">>Histo_QCD_Mu_Pt50to80_temp" + limits;
  QCD_Mu_Pt50to80_miniTree->Draw(variable_QCD_Mu_Pt50to80.c_str(), cut.c_str());
  TH2F *Histo_QCD_Mu_Pt50to80 = (TH2F*)gDirectory->Get("Histo_QCD_Mu_Pt50to80_temp");
  c1->Clear();

  // Get Histo_QCD_Mu_Pt80to120 from eventTree
  TH2F *Histo_QCD_Mu_Pt80to120_temp = new TH2F();
  string variable_QCD_Mu_Pt80to120 = var2 + ":" + var1 + ">>Histo_QCD_Mu_Pt80to120_temp" + limits;
  QCD_Mu_Pt80to120_miniTree->Draw(variable_QCD_Mu_Pt80to120.c_str(), cut.c_str());
  TH2F *Histo_QCD_Mu_Pt80to120 = (TH2F*)gDirectory->Get("Histo_QCD_Mu_Pt80to120_temp");
  c1->Clear();

  // Get Histo_QCD_Mu_Pt120to170 from eventTree
  TH2F *Histo_QCD_Mu_Pt120to170_temp = new TH2F();
  string variable_QCD_Mu_Pt120to170 = var2 + ":" + var1 + ">>Histo_QCD_Mu_Pt120to170_temp" + limits;
  QCD_Mu_Pt120to170_miniTree->Draw(variable_QCD_Mu_Pt120to170.c_str(), cut.c_str());
  TH2F *Histo_QCD_Mu_Pt120to170 = (TH2F*)gDirectory->Get("Histo_QCD_Mu_Pt120to170_temp");
  c1->Clear();

  // Get Histo_QCD_Mu_Pt170toInf from eventTree
  TH2F *Histo_QCD_Mu_Pt170toInf_temp = new TH2F();
  string variable_QCD_Mu_Pt170toInf = var2 + ":" + var1 + ">>Histo_QCD_Mu_Pt170toInf_temp" + limits;
  QCD_Mu_Pt170toInf_miniTree->Draw(variable_QCD_Mu_Pt170toInf.c_str(), cut.c_str());
  TH2F *Histo_QCD_Mu_Pt170toInf = (TH2F*)gDirectory->Get("Histo_QCD_Mu_Pt170toInf_temp");
  c1->Clear();

  // Get Histo_InclusiveMu15 from eventTree
  TH2F *Histo_InclusiveMu15_temp = new TH2F();
  string variable_InclusiveMu15 = var2 + ":" + var1 + ">>Histo_InclusiveMu15_temp" + limits;
  InclusiveMu15_miniTree->Draw(variable_InclusiveMu15.c_str(), cut.c_str());
  TH2F *Histo_InclusiveMu15 = (TH2F*)gDirectory->Get("Histo_InclusiveMu15_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt0to15 from eventTree
  TH2F *Histo_FSR_ZmumuJet_Pt0to15_temp = new TH2F();
  string variable_FSR_ZmumuJet_Pt0to15 = var2 + ":" + var1 + ">>Histo_FSR_ZmumuJet_Pt0to15_temp" + limits;
  FSR_ZmumuJet_Pt0to15_miniTree->Draw(variable_FSR_ZmumuJet_Pt0to15.c_str(), cut.c_str());
  TH2F *Histo_FSR_ZmumuJet_Pt0to15 = (TH2F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt0to15_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt15to20 from eventTree
  TH2F *Histo_FSR_ZmumuJet_Pt15to20_temp = new TH2F();
  string variable_FSR_ZmumuJet_Pt15to20 = var2 + ":" + var1 + ">>Histo_FSR_ZmumuJet_Pt15to20_temp" + limits;
  FSR_ZmumuJet_Pt15to20_miniTree->Draw(variable_FSR_ZmumuJet_Pt15to20.c_str(), cut.c_str());
  TH2F *Histo_FSR_ZmumuJet_Pt15to20 = (TH2F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt15to20_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt20to30 from eventTree
  TH2F *Histo_FSR_ZmumuJet_Pt20to30_temp = new TH2F();
  string variable_FSR_ZmumuJet_Pt20to30 = var2 + ":" + var1 + ">>Histo_FSR_ZmumuJet_Pt20to30_temp" + limits;
  FSR_ZmumuJet_Pt20to30_miniTree->Draw(variable_FSR_ZmumuJet_Pt20to30.c_str(), cut.c_str());
  TH2F *Histo_FSR_ZmumuJet_Pt20to30 = (TH2F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt20to30_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt30to50 from eventTree
  TH2F *Histo_FSR_ZmumuJet_Pt30to50_temp = new TH2F();
  string variable_FSR_ZmumuJet_Pt30to50 = var2 + ":" + var1 + ">>Histo_FSR_ZmumuJet_Pt30to50_temp" + limits;
  FSR_ZmumuJet_Pt30to50_miniTree->Draw(variable_FSR_ZmumuJet_Pt30to50.c_str(), cut.c_str());
  TH2F *Histo_FSR_ZmumuJet_Pt30to50 = (TH2F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt30to50_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt50to80 from eventTree
  TH2F *Histo_FSR_ZmumuJet_Pt50to80_temp = new TH2F();
  string variable_FSR_ZmumuJet_Pt50to80 = var2 + ":" + var1 + ">>Histo_FSR_ZmumuJet_Pt50to80_temp" + limits;
  FSR_ZmumuJet_Pt50to80_miniTree->Draw(variable_FSR_ZmumuJet_Pt50to80.c_str(), cut.c_str());
  TH2F *Histo_FSR_ZmumuJet_Pt50to80 = (TH2F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt50to80_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt80to120 from eventTree
  TH2F *Histo_FSR_ZmumuJet_Pt80to120_temp = new TH2F();
  string variable_FSR_ZmumuJet_Pt80to120 = var2 + ":" + var1 + ">>Histo_FSR_ZmumuJet_Pt80to120_temp" + limits;
  FSR_ZmumuJet_Pt80to120_miniTree->Draw(variable_FSR_ZmumuJet_Pt80to120.c_str(), cut.c_str());
  TH2F *Histo_FSR_ZmumuJet_Pt80to120 = (TH2F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt80to120_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt120to170 from eventTree
  TH2F *Histo_FSR_ZmumuJet_Pt120to170_temp = new TH2F();
  string variable_FSR_ZmumuJet_Pt120to170 = var2 + ":" + var1 + ">>Histo_FSR_ZmumuJet_Pt120to170_temp" + limits;
  FSR_ZmumuJet_Pt120to170_miniTree->Draw(variable_FSR_ZmumuJet_Pt120to170.c_str(), cut.c_str());
  TH2F *Histo_FSR_ZmumuJet_Pt120to170 = (TH2F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt120to170_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt170to230 from eventTree
  TH2F *Histo_FSR_ZmumuJet_Pt170to230_temp = new TH2F();
  string variable_FSR_ZmumuJet_Pt170to230 = var2 + ":" + var1 + ">>Histo_FSR_ZmumuJet_Pt170to230_temp" + limits;
  FSR_ZmumuJet_Pt170to230_miniTree->Draw(variable_FSR_ZmumuJet_Pt170to230.c_str(), cut.c_str());
  TH2F *Histo_FSR_ZmumuJet_Pt170to230 = (TH2F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt170to230_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt230to300 from eventTree
  TH2F *Histo_FSR_ZmumuJet_Pt230to300_temp = new TH2F();
  string variable_FSR_ZmumuJet_Pt230to300 = var2 + ":" + var1 + ">>Histo_FSR_ZmumuJet_Pt230to300_temp" + limits;
  FSR_ZmumuJet_Pt230to300_miniTree->Draw(variable_FSR_ZmumuJet_Pt230to300.c_str(), cut.c_str());
  TH2F *Histo_FSR_ZmumuJet_Pt230to300 = (TH2F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt230to300_temp");
  c1->Clear();

  // Get Histo_FSR_ZmumuJet_Pt300toInf from eventTree
  TH2F *Histo_FSR_ZmumuJet_Pt300toInf_temp = new TH2F();
  string variable_FSR_ZmumuJet_Pt300toInf = var2 + ":" + var1 + ">>Histo_FSR_ZmumuJet_Pt300toInf_temp" + limits;
  FSR_ZmumuJet_Pt300toInf_miniTree->Draw(variable_FSR_ZmumuJet_Pt300toInf.c_str(), cut.c_str());
  TH2F *Histo_FSR_ZmumuJet_Pt300toInf = (TH2F*)gDirectory->Get("Histo_FSR_ZmumuJet_Pt300toInf_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt0to15 from eventTree
  TH2F *Histo_ISR_ZmumuJet_Pt0to15_temp = new TH2F();
  string variable_ISR_ZmumuJet_Pt0to15 = var2 + ":" + var1 + ">>Histo_ISR_ZmumuJet_Pt0to15_temp" + limits;
  ISR_ZmumuJet_Pt0to15_miniTree->Draw(variable_ISR_ZmumuJet_Pt0to15.c_str(), cut.c_str());
  TH2F *Histo_ISR_ZmumuJet_Pt0to15 = (TH2F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt0to15_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt15to20 from eventTree
  TH2F *Histo_ISR_ZmumuJet_Pt15to20_temp = new TH2F();
  string variable_ISR_ZmumuJet_Pt15to20 = var2 + ":" + var1 + ">>Histo_ISR_ZmumuJet_Pt15to20_temp" + limits;
  ISR_ZmumuJet_Pt15to20_miniTree->Draw(variable_ISR_ZmumuJet_Pt15to20.c_str(), cut.c_str());
  TH2F *Histo_ISR_ZmumuJet_Pt15to20 = (TH2F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt15to20_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt20to30 from eventTree
  TH2F *Histo_ISR_ZmumuJet_Pt20to30_temp = new TH2F();
  string variable_ISR_ZmumuJet_Pt20to30 = var2 + ":" + var1 + ">>Histo_ISR_ZmumuJet_Pt20to30_temp" + limits;
  ISR_ZmumuJet_Pt20to30_miniTree->Draw(variable_ISR_ZmumuJet_Pt20to30.c_str(), cut.c_str());
  TH2F *Histo_ISR_ZmumuJet_Pt20to30 = (TH2F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt20to30_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt30to50 from eventTree
  TH2F *Histo_ISR_ZmumuJet_Pt30to50_temp = new TH2F();
  string variable_ISR_ZmumuJet_Pt30to50 = var2 + ":" + var1 + ">>Histo_ISR_ZmumuJet_Pt30to50_temp" + limits;
  ISR_ZmumuJet_Pt30to50_miniTree->Draw(variable_ISR_ZmumuJet_Pt30to50.c_str(), cut.c_str());
  TH2F *Histo_ISR_ZmumuJet_Pt30to50 = (TH2F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt30to50_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt50to80 from eventTree
  TH2F *Histo_ISR_ZmumuJet_Pt50to80_temp = new TH2F();
  string variable_ISR_ZmumuJet_Pt50to80 = var2 + ":" + var1 + ">>Histo_ISR_ZmumuJet_Pt50to80_temp" + limits;
  ISR_ZmumuJet_Pt50to80_miniTree->Draw(variable_ISR_ZmumuJet_Pt50to80.c_str(), cut.c_str());
  TH2F *Histo_ISR_ZmumuJet_Pt50to80 = (TH2F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt50to80_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt80to120 from eventTree
  TH2F *Histo_ISR_ZmumuJet_Pt80to120_temp = new TH2F();
  string variable_ISR_ZmumuJet_Pt80to120 = var2 + ":" + var1 + ">>Histo_ISR_ZmumuJet_Pt80to120_temp" + limits;
  ISR_ZmumuJet_Pt80to120_miniTree->Draw(variable_ISR_ZmumuJet_Pt80to120.c_str(), cut.c_str());
  TH2F *Histo_ISR_ZmumuJet_Pt80to120 = (TH2F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt80to120_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt120to170 from eventTree
  TH2F *Histo_ISR_ZmumuJet_Pt120to170_temp = new TH2F();
  string variable_ISR_ZmumuJet_Pt120to170 = var2 + ":" + var1 + ">>Histo_ISR_ZmumuJet_Pt120to170_temp" + limits;
  ISR_ZmumuJet_Pt120to170_miniTree->Draw(variable_ISR_ZmumuJet_Pt120to170.c_str(), cut.c_str());
  TH2F *Histo_ISR_ZmumuJet_Pt120to170 = (TH2F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt120to170_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt170to230 from eventTree
  TH2F *Histo_ISR_ZmumuJet_Pt170to230_temp = new TH2F();
  string variable_ISR_ZmumuJet_Pt170to230 = var2 + ":" + var1 + ">>Histo_ISR_ZmumuJet_Pt170to230_temp" + limits;
  ISR_ZmumuJet_Pt170to230_miniTree->Draw(variable_ISR_ZmumuJet_Pt170to230.c_str(), cut.c_str());
  TH2F *Histo_ISR_ZmumuJet_Pt170to230 = (TH2F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt170to230_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt230to300 from eventTree
  TH2F *Histo_ISR_ZmumuJet_Pt230to300_temp = new TH2F();
  string variable_ISR_ZmumuJet_Pt230to300 = var2 + ":" + var1 + ">>Histo_ISR_ZmumuJet_Pt230to300_temp" + limits;
  ISR_ZmumuJet_Pt230to300_miniTree->Draw(variable_ISR_ZmumuJet_Pt230to300.c_str(), cut.c_str());
  TH2F *Histo_ISR_ZmumuJet_Pt230to300 = (TH2F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt230to300_temp");
  c1->Clear();

  // Get Histo_ISR_ZmumuJet_Pt300toInf from eventTree
  TH2F *Histo_ISR_ZmumuJet_Pt300toInf_temp = new TH2F();
  string variable_ISR_ZmumuJet_Pt300toInf = var2 + ":" + var1 + ">>Histo_ISR_ZmumuJet_Pt300toInf_temp" + limits;
  ISR_ZmumuJet_Pt300toInf_miniTree->Draw(variable_ISR_ZmumuJet_Pt300toInf.c_str(), cut.c_str());
  TH2F *Histo_ISR_ZmumuJet_Pt300toInf = (TH2F*)gDirectory->Get("Histo_ISR_ZmumuJet_Pt300toInf_temp");
  c1->Clear();

  // TODO: implement drawUnderOverFsubleading

  // Get the number of entries for further normalization
  double a = Histo_Data->Integral();
  // Normalize
  Histo_Data->Sumw2(); // In order to have the correct error bars on data after renormalization
  // // Normalize MC and Data to 1
  //Histo_Data->Scale((double)((double)1.0/(double)a));
  //Histo_MC->Scale((double)((double)1.0/(double)b));
  // // Normalize MC to Data number of entries
  double integratedLuminosity = 2859492.190e-06;

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
  double XSectionFSR_ZmumuJet_Pt0to15 = 4.434e+03;
  double XSectionFSR_ZmumuJet_Pt15to20 = 1.454e+02;
  double XSectionFSR_ZmumuJet_Pt20to30 = 1.318e+02;
  double XSectionFSR_ZmumuJet_Pt30to50 = 8.438e+01;
  double XSectionFSR_ZmumuJet_Pt50to80 = 3.235e+01;
  double XSectionFSR_ZmumuJet_Pt80to120 = 9.981e+00;
  double XSectionFSR_ZmumuJet_Pt120to170 = 2.760e+00;
  double XSectionFSR_ZmumuJet_Pt170to230 = 7.241e-01;
  double XSectionFSR_ZmumuJet_Pt230to300 = 1.946e-01;
  double XSectionFSR_ZmumuJet_Pt300toInf = 7.627e-02;
  double XSectionISR_ZmumuJet_Pt0to15 = 4.434e+03;
  double XSectionISR_ZmumuJet_Pt15to20 = 1.454e+02;
  double XSectionISR_ZmumuJet_Pt20to30 = 1.318e+02;
  double XSectionISR_ZmumuJet_Pt30to50 = 8.438e+01;
  double XSectionISR_ZmumuJet_Pt50to80 = 3.235e+01;
  double XSectionISR_ZmumuJet_Pt80to120 = 9.981e+00;
  double XSectionISR_ZmumuJet_Pt120to170 = 2.760e+00;
  double XSectionISR_ZmumuJet_Pt170to230 = 7.241e-01;
  double XSectionISR_ZmumuJet_Pt230to300 = 1.946e-01;
  double XSectionISR_ZmumuJet_Pt300toInf = 7.627e-02;

  double InitialNumberQCD_Pt15 = 6116800;
  double InitialNumberQCD_Pt30 = 5093840;
  double InitialNumberQCD_Pt80 = 3229000;
  double InitialNumberQCD_Pt170 = 3122500;
  double InitialNumberQCD_Pt300 = 3269645;
  double InitialNumberQCD_Pt470 = 2083653;
  double InitialNumberPhotonJet_Pt15 = 1221770;
  double InitialNumberPhotonJet_Pt30 = 1025300;
  double InitialNumberPhotonJet_Pt80 = 1287711;
  double InitialNumberPhotonJet_Pt170 = 1209600;
  double InitialNumberPhotonJet_Pt300 = 1033240;
  double InitialNumberTTbarJets_Tauola = 1463572;
  double InitialNumberWJets_7TeV = 10218854;
  double InitialNumberZJets_7TeV = 1047008;
  double InitialNumberQCD_Mu_Pt20to30 = 10985188;
  double InitialNumberQCD_Mu_Pt30to50 = 6931182;
  double InitialNumberQCD_Mu_Pt50to80 = 2542308;
  double InitialNumberQCD_Mu_Pt80to120 = 523053;
  double InitialNumberQCD_Mu_Pt120to170 = 316630;
  double InitialNumberQCD_Mu_Pt170toInf = 262036;
  double InitialNumberInclusiveMu15 = 5120334;
  double InitialNumberFSR_ZmumuJet_Pt0to15 = 235420;
  double InitialNumberFSR_ZmumuJet_Pt15to20 = 222730;
  double InitialNumberFSR_ZmumuJet_Pt20to30 = 164190;
  double InitialNumberFSR_ZmumuJet_Pt30to50 = 163920;
  double InitialNumberFSR_ZmumuJet_Pt50to80 = 106016;
  double InitialNumberFSR_ZmumuJet_Pt80to120 = 107759;
  double InitialNumberFSR_ZmumuJet_Pt120to170 = 177408;
  double InitialNumberFSR_ZmumuJet_Pt170to230 = 178400;
  double InitialNumberFSR_ZmumuJet_Pt230to300 = 176485;
  double InitialNumberFSR_ZmumuJet_Pt300toInf = 109316;
  double InitialNumberISR_ZmumuJet_Pt0to15 = 235420;
  double InitialNumberISR_ZmumuJet_Pt15to20 = 222730;
  double InitialNumberISR_ZmumuJet_Pt20to30 = 164190;
  double InitialNumberISR_ZmumuJet_Pt30to50 = 163920;
  double InitialNumberISR_ZmumuJet_Pt50to80 = 106016;
  double InitialNumberISR_ZmumuJet_Pt80to120 = 107759;
  double InitialNumberISR_ZmumuJet_Pt120to170 = 177408;
  double InitialNumberISR_ZmumuJet_Pt170to230 = 178400;
  double InitialNumberISR_ZmumuJet_Pt230to300 = 176485;
  double InitialNumberISR_ZmumuJet_Pt300toInf = 109316;
/*
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
  Histo_FSR_ZmumuJet_Pt0to15->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt0to15) / (double)(InitialNumberFSR_ZmumuJet_Pt0to15)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt15to20->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt15to20) / (double)(InitialNumberFSR_ZmumuJet_Pt15to20)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt20to30->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt20to30) / (double)(InitialNumberFSR_ZmumuJet_Pt20to30)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt30to50->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt30to50) / (double)(InitialNumberFSR_ZmumuJet_Pt30to50)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt50to80->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt50to80) / (double)(InitialNumberFSR_ZmumuJet_Pt50to80)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt80to120->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt80to120) / (double)(InitialNumberFSR_ZmumuJet_Pt80to120)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt120to170->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt120to170) / (double)(InitialNumberFSR_ZmumuJet_Pt120to170)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt170to230->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt170to230) / (double)(InitialNumberFSR_ZmumuJet_Pt170to230)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt230to300->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt230to300) / (double)(InitialNumberFSR_ZmumuJet_Pt230to300)) * (double)integratedLuminosity));
  Histo_FSR_ZmumuJet_Pt300toInf->Scale((double)(  (double)((double)(XSectionFSR_ZmumuJet_Pt300toInf) / (double)(InitialNumberFSR_ZmumuJet_Pt300toInf)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt0to15->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt0to15) / (double)(InitialNumberISR_ZmumuJet_Pt0to15)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt15to20->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt15to20) / (double)(InitialNumberISR_ZmumuJet_Pt15to20)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt20to30->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt20to30) / (double)(InitialNumberISR_ZmumuJet_Pt20to30)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt30to50->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt30to50) / (double)(InitialNumberISR_ZmumuJet_Pt30to50)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt50to80->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt50to80) / (double)(InitialNumberISR_ZmumuJet_Pt50to80)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt80to120->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt80to120) / (double)(InitialNumberISR_ZmumuJet_Pt80to120)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt120to170->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt120to170) / (double)(InitialNumberISR_ZmumuJet_Pt120to170)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt170to230->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt170to230) / (double)(InitialNumberISR_ZmumuJet_Pt170to230)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt230to300->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt230to300) / (double)(InitialNumberISR_ZmumuJet_Pt230to300)) * (double)integratedLuminosity));
  Histo_ISR_ZmumuJet_Pt300toInf->Scale((double)(  (double)((double)(XSectionISR_ZmumuJet_Pt300toInf) / (double)(InitialNumberISR_ZmumuJet_Pt300toInf)) * (double)integratedLuminosity));
*/
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

  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt15to20);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt20to30);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt30to50);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt50to80);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt80to120);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt120to170);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt170to230);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt230to300);
  Histo_FSR_ZmumuJet_Pt0to15->Add(Histo_FSR_ZmumuJet_Pt300toInf);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt15to20);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt20to30);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt30to50);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt50to80);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt80to120);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt120to170);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt170to230);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt230to300);
  Histo_ISR_ZmumuJet_Pt0to15->Add(Histo_ISR_ZmumuJet_Pt300toInf);


  // Get the maxs and the mins to further correct the Y-axis
/*  double dataMax = Histo_Data->GetMaximum();
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
  double FSR_ZmumuJet_Pt0to15Max = Histo_FSR_ZmumuJet_Pt0to15->GetMaximum();
  YMax = max(YMax, FSR_ZmumuJet_Pt0to15Max);

  double dataMin = YMax;
  double PhotonJet_Pt15Min = YMax;
  double QCD_Pt15Min = YMax;
  double TTbarJets_TauolaMin = YMax;
  double WJets_7TeVMin = YMax;
  double ZJets_7TeVMin = YMax;
  double QCD_Mu_Pt20to30Min = YMax;
  double InclusiveMu15Min = YMax;
  double FSR_ZmumuJet_Pt0to15Min = YMax;
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
  for( int ibin=1 ; ibin<Histo_FSR_ZmumuJet_Pt0to15->GetNbinsX() ; ibin++ ){
    if( ((Histo_FSR_ZmumuJet_Pt0to15->GetBinContent(ibin))!=0) && ((Histo_FSR_ZmumuJet_Pt0to15->GetBinContent(ibin))<FSR_ZmumuJet_Pt0to15Min) ){
      FSR_ZmumuJet_Pt0to15Min = Histo_FSR_ZmumuJet_Pt0to15->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, FSR_ZmumuJet_Pt0to15Min);

//  cout << "YMax= "<< YMax << "\t\tYMin= " << YMin << endl;
  double YMin_lin = (double)YMin / (double)10.0;
  double Range_lin = ((double)(YMax - YMin_lin)) / ((double)(1.0));
  double YMax_lin = 0.2*Range_lin + YMax;
  double Range_log = ((double)(log10(YMax) - log10(YMin))) / ((double)(0.77));
//  cout << "Range_lin= " << Range_lin << "\t\tRange_log= " << Range_log << endl;
  double YMax_log = pow(10.0, 0.2*Range_log + log10(YMax));
  double YMin_log = pow(10.0, log10(YMin) - 0.03*Range_log);
//  cout << "YMin_lin= " << YMin_lin << "\t\tYMax_lin= " << YMax_lin << endl;
//  cout << "YMin_log= " << YMin_log << "\t\tYMax_log= " << YMax_log << endl;
*/

  // Setup the histo and canvas names and title
  string data_name = "Data_" + pic + "_" + name;
  string mc_name = "MC_" + pic + "_" + name;
  string canvas_name = "DataMC_" + pic + "_" + name;
/*
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
*/
  Histo_Data->SetName(data_name.c_str());
  Histo_QCD_Pt15->SetName(mc_name.c_str());
  c1->SetName(canvas_name.c_str());
  c1->SetTitle(canvas_name.c_str());

  // Draw the comparison plots

  TLegend *legend = new TLegend(0.75, 0.80, 0.90, 0.93, "");
	if( doFit ){
		legend->SetX1(0.50);
		legend->SetX2(0.65);
	}
  legend->SetTextSize(0.025);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kWhite);
  legend->SetShadowColor(kWhite);

  // // First: draw the data to get correct Y-axis scale
	cout << "Title_var1.c_str = " << Title_var1.c_str() << endl;
	cout << "Title_var2.c_str = " << Title_var2.c_str() << endl;

  Histo_Data->GetXaxis()->SetTitle(Title_var1.c_str());
  Histo_Data->GetYaxis()->SetTitle(Title_var2.c_str());
  Histo_Data->SetLineColor(kBlack);
  Histo_Data->SetMarkerColor(kBlack);
//  Histo_Data->SetMarkerSize(15);
  Histo_Data->SetMarkerStyle(20);
  Histo_Data->Draw("SCAT");
  legend->AddEntry(Histo_Data->GetName(), "Data", "lp");

  // // Second: draw MC on the same canvas
  Histo_QCD_Pt15->SetLineColor(kBlack);
  Histo_QCD_Pt15->SetFillColor(kGreen+3);
	Histo_QCD_Pt15->SetMarkerColor(kGreen+3);
  Histo_QCD_Pt15->SetFillStyle(3001);
//  Histo_QCD_Pt15->Draw("SCATsame");
//  legend->AddEntry(Histo_QCD_Pt15->GetName(), "QCD", "f");

  Histo_QCD_Mu_Pt20to30->SetLineColor(kBlack);
  Histo_QCD_Mu_Pt20to30->SetFillColor(kGreen);
	Histo_QCD_Mu_Pt20to30->SetMarkerColor(kGreen);
  Histo_QCD_Mu_Pt20to30->SetFillStyle(3001);

  Histo_InclusiveMu15->SetLineColor(kBlack);
  Histo_InclusiveMu15->SetFillColor(kGreen-6);
	Histo_InclusiveMu15->SetMarkerColor(kGreen-6);
  Histo_InclusiveMu15->SetFillStyle(3001);
//  Histo_InclusiveMu15->Draw("SCATsame");  
//  legend->AddEntry(Histo_InclusiveMu15->GetName(), "InclusiveMu15", "f");

  Histo_TTbarJets_Tauola->SetLineColor(kBlack);
  Histo_TTbarJets_Tauola->SetFillColor(kBlue);
	Histo_TTbarJets_Tauola->SetMarkerColor(kBlue);
  Histo_TTbarJets_Tauola->SetFillStyle(3001);

  Histo_FSR_ZmumuJet_Pt0to15->SetLineColor(kBlack);
  Histo_FSR_ZmumuJet_Pt0to15->SetFillColor(kRed);
	Histo_FSR_ZmumuJet_Pt0to15->SetMarkerColor(kRed);
  Histo_FSR_ZmumuJet_Pt0to15->SetFillStyle(3001);

  Histo_ISR_ZmumuJet_Pt0to15->SetLineColor(kBlack);
  Histo_ISR_ZmumuJet_Pt0to15->SetFillColor(kOrange);
	Histo_ISR_ZmumuJet_Pt0to15->SetMarkerColor(kOrange);
  Histo_ISR_ZmumuJet_Pt0to15->SetFillStyle(3001);

  Histo_ZJets_7TeV->SetLineColor(kBlack);
  Histo_ZJets_7TeV->SetFillColor(kOrange);
	Histo_ZJets_7TeV->SetMarkerColor(kOrange);
  Histo_ZJets_7TeV->SetFillStyle(3001);
//  Histo_ZJets_7TeV->Draw("SCATsame");
//  legend->AddEntry(Histo_ZJets_7TeV->GetName(), "ZJets", "f");

  Histo_WJets_7TeV->SetLineColor(kBlack);
  Histo_WJets_7TeV->SetFillColor(kMagenta+3);
	Histo_WJets_7TeV->SetMarkerColor(kMagenta+3);
  Histo_WJets_7TeV->SetFillStyle(3001);

  Histo_PhotonJet_Pt15->SetLineColor(kBlack);
  Histo_PhotonJet_Pt15->SetFillColor(kMagenta);
	Histo_PhotonJet_Pt15->SetMarkerColor(kMagenta);
  Histo_PhotonJet_Pt15->SetFillStyle(3001);

  // // Third: re-draw Data so that data appears in front of MC
  Histo_TTbarJets_Tauola->Draw("SCATsame");
  Histo_ISR_ZmumuJet_Pt0to15->Draw("SCATsame");
  Histo_PhotonJet_Pt15->Draw("SCATsame");
  Histo_WJets_7TeV->Draw("SCATsame");
  Histo_QCD_Mu_Pt20to30->Draw("SCATsame");
  Histo_FSR_ZmumuJet_Pt0to15->Draw("SCATsame");
  Histo_Data->Draw("SCATsame");
  legend->AddEntry(Histo_TTbarJets_Tauola->GetName(), "TTbarJets", "f");
  legend->AddEntry(Histo_ISR_ZmumuJet_Pt0to15->GetName(), "ZmumuJet (no FSR)", "f");
  legend->AddEntry(Histo_PhotonJet_Pt15->GetName(), "PhotonJet", "f");
  legend->AddEntry(Histo_WJets_7TeV->GetName(), "WJets", "f");
  legend->AddEntry(Histo_QCD_Mu_Pt20to30->GetName(), "QCD Mu", "f");
  legend->AddEntry(Histo_FSR_ZmumuJet_Pt0to15->GetName(), "ZmumuJet (FSR)", "f");

  // // Fourth: redraw axis so that axis appears in front of everything
  gPad->RedrawAxis();
if( doFit ){
	string fitOpts = "RMQB+";
	//TMinuit *gMinuit = new TMinuit();
	//gMinuit->SetGraphicsMode(kFALSE);
	gStyle->SetOptStat(10);
//	gStyle->SetOptFit(1111);
//	cout << "max= " << Histo_Data->GetXaxis()->GetXmax() << endl;
//	cout << "min= " << Histo_Data->GetXaxis()->GetXmin() << endl;
	TF1* f = new TF1("f", "pol1",  Histo_Data->GetXaxis()->GetXmin(), Histo_Data->GetXaxis()->GetXmax());
	f->SetLineColor(kBlue);
	f->SetLineWidth(2);
//	TF2* f2 = new TF2("f2", "x-y", Histo_Data->GetXaxis()->GetXmin(), Histo_Data->GetXaxis()->GetXmax(), Histo_Data->GetYaxis()->GetXmin(), Histo_Data->GetYaxis()->GetXmax(), (Int_t)2);
//	TF2* f2 = new TF2("f2", "x[0]", 0, 100, 0, 100, 1);
//	double pars[2] = {0, 1};
//	TF2* f2 = new TF2("f2", fonction_affine, 0, 100, 0, 100, 2);
//	f2->SetParameters(pars);
//	Histo_Data->Fit("f2", fitOpts.c_str());
	f->SetParameter(1, 1); // coeff dir 1 si pas de correction
//	TProfile *prof = Histo_Data->ProfileX();
//	f->SetParameter(0, 0); // ordonnee a l'origine est 0 si correction parfaite
	f->FixParameter(0, 0); // ordonnee a l'origine est 0 si correction parfaite
//	prof->Fit("f", fitOpts.c_str());
//	prof->Fit("f", fitOpts.c_str());
//	prof->Draw();
//	f2->Draw();
//	Histo_Data->Fit("f2", fitOpts.c_str());
	//TF1* f = gROOT->GetFunction("pol1");
	//gMinuit->SetFCN(f);
	Histo_Data->Fit("f", fitOpts.c_str());
//	Histo_FSR_ZmumuJet_Pt0to15->Fit("f", fitOpts.c_str());

	Histo_WJets_7TeV->Draw("SCATsame");
	Histo_PhotonJet_Pt15->Draw("SCATsame");
	Histo_ISR_ZmumuJet_Pt0to15->Draw("SCATsame");
	Histo_TTbarJets_Tauola->Draw("SCATsame");
	Histo_QCD_Mu_Pt20to30->Draw("SCATsame");
	Histo_FSR_ZmumuJet_Pt0to15->Draw("SCATsame");
  Histo_Data->Draw("SCATsame");
  Histo_Data->GetXaxis()->SetTitle(Title_var1.c_str());
  Histo_Data->GetYaxis()->SetTitle(Title_var2.c_str());
//  gPad->RedrawAxis();
 
	TPaveStats* statsHisto_Data = (TPaveStats*) Histo_Data->GetListOfFunctions()->FindObject("stats");
//	statsHisto_Data->SetLineColor(kBlue);
//	statsHisto_Data->SetTextColor(kBlue);
	statsHisto_Data->SetTextSize(0.020);
	statsHisto_Data->SetX1NDC(0.73);
	statsHisto_Data->SetX2NDC(0.93);
	statsHisto_Data->SetY1NDC(0.20);
	statsHisto_Data->SetY2NDC(0.33);
	Histo_Data->SetName("DATA");
	statsHisto_Data->Draw();


}


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
  string PicName="gif/DataMC_" + pic + "_" + name + ".gif";
  c1->Print(PicName.c_str());
//	c1->SaveAs("plaf.C");
  PicName="eps/DataMC_" + pic + "_" + name + ".eps";
  c1->Print(PicName.c_str());
  string convert = "convert eps/DataMC_" + pic + "_" + name + ".eps" + " pdf/DataMC_" + pic + "_" + name + ".pdf";
  system(convert.c_str());
/*
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
    Histo_FSR_ZmumuJet_Pt0to15->SetMaximum(YMax_log);
    Histo_FSR_ZmumuJet_Pt0to15->SetMinimum(YMin_log);
    Histo_FSR_ZmumuJet_Pt0to15->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
    c1->SetLogy(1);
    c1->Update();
    c1->Draw();
    string PicName_log="Plots_TEST/gif/DataMC_" + pic + "_" + name + "_log.gif";
    c1->Print(PicName_log.c_str());
    PicName="Plots_TEST/eps/DataMC_" + pic + "_" + name + "_log.eps";
    c1->Print(PicName.c_str());
    string convert = "convert Plots_TEST/eps/DataMC_" + pic + "_" + name + "_log.eps" + " Plots_TEST/pdf/DataMC_" + pic + "_" + name + "_log.pdf";
    system(convert.c_str());
    c1->SetLogy(0);
    c1->Update();
  }
*/
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
  Histo_FSR_ZmumuJet_Pt0to15_temp->Delete();
  Histo_FSR_ZmumuJet_Pt0to15->Delete();
  Histo_FSR_ZmumuJet_Pt15to20_temp->Delete();
  Histo_FSR_ZmumuJet_Pt15to20->Delete();
  Histo_FSR_ZmumuJet_Pt20to30_temp->Delete();
  Histo_FSR_ZmumuJet_Pt20to30->Delete();
  Histo_FSR_ZmumuJet_Pt30to50_temp->Delete();
  Histo_FSR_ZmumuJet_Pt30to50->Delete();
  Histo_FSR_ZmumuJet_Pt50to80_temp->Delete();
  Histo_FSR_ZmumuJet_Pt50to80->Delete();
  Histo_FSR_ZmumuJet_Pt80to120_temp->Delete();
  Histo_FSR_ZmumuJet_Pt80to120->Delete();
  Histo_FSR_ZmumuJet_Pt120to170_temp->Delete();
  Histo_FSR_ZmumuJet_Pt120to170->Delete();
  Histo_FSR_ZmumuJet_Pt170to230_temp->Delete();
  Histo_FSR_ZmumuJet_Pt170to230->Delete();
  Histo_FSR_ZmumuJet_Pt230to300_temp->Delete();
  Histo_FSR_ZmumuJet_Pt230to300->Delete();
  Histo_FSR_ZmumuJet_Pt300toInf_temp->Delete();
  Histo_FSR_ZmumuJet_Pt300toInf->Delete();
  Histo_ISR_ZmumuJet_Pt0to15_temp->Delete();
  Histo_ISR_ZmumuJet_Pt0to15->Delete();
  Histo_ISR_ZmumuJet_Pt15to20_temp->Delete();
  Histo_ISR_ZmumuJet_Pt15to20->Delete();
  Histo_ISR_ZmumuJet_Pt20to30_temp->Delete();
  Histo_ISR_ZmumuJet_Pt20to30->Delete();
  Histo_ISR_ZmumuJet_Pt30to50_temp->Delete();
  Histo_ISR_ZmumuJet_Pt30to50->Delete();
  Histo_ISR_ZmumuJet_Pt50to80_temp->Delete();
  Histo_ISR_ZmumuJet_Pt50to80->Delete();
  Histo_ISR_ZmumuJet_Pt80to120_temp->Delete();
  Histo_ISR_ZmumuJet_Pt80to120->Delete();
  Histo_ISR_ZmumuJet_Pt120to170_temp->Delete();
  Histo_ISR_ZmumuJet_Pt120to170->Delete();
  Histo_ISR_ZmumuJet_Pt170to230_temp->Delete();
  Histo_ISR_ZmumuJet_Pt170to230->Delete();
  Histo_ISR_ZmumuJet_Pt230to300_temp->Delete();
  Histo_ISR_ZmumuJet_Pt230to300->Delete();
  Histo_ISR_ZmumuJet_Pt300toInf_temp->Delete();
  Histo_ISR_ZmumuJet_Pt300toInf->Delete();

}

