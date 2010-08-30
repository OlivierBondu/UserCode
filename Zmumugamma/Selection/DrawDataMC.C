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

void DrawDataMCplot(TTree *Data_miniTree, TTree *QCD_Pt15_miniTree, TTree *QCD_Pt30_miniTree, TTree *QCD_Pt80_miniTree, TTree *QCD_Pt170_miniTree, TTree *QCD_Pt300_miniTree, TTree *QCD_Pt470_miniTree, TTree *PhotonJet_Pt15_miniTree, TTree *PhotonJet_Pt30_miniTree, TTree *PhotonJet_Pt80_miniTree, TTree *PhotonJet_Pt170_miniTree, TTree *PhotonJet_Pt300_miniTree, TTree *TTbarJets_Tauola_miniTree, TTree *WJets_7TeV_miniTree, TTree *ZJets_7TeV_miniTree, TTree *QCD_Mu_Pt20to30_miniTree, TTree *QCD_Mu_Pt30to50_miniTree, TTree *QCD_Mu_Pt50to80_miniTree, TTree *QCD_Mu_Pt80to120_miniTree, TTree *QCD_Mu_Pt120to170_miniTree, TTree *QCD_Mu_Pt170toInf_miniTree, TTree *InclusiveMu15_miniTree, TTree *ZmumuJet_Pt0to15_miniTree, TTree *ZmumuJet_Pt15to20_miniTree, TTree *ZmumuJet_Pt20to30_miniTree, TTree *ZmumuJet_Pt30to50_miniTree, TTree *ZmumuJet_Pt50to80_miniTree, TTree *ZmumuJet_Pt80to120_miniTree, TTree *ZmumuJet_Pt120to170_miniTree, TTree *ZmumuJet_Pt170to230_miniTree, TTree *ZmumuJet_Pt230to300_miniTree, TTree *ZmumuJet_Pt300toInf_miniTree, string var, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1){

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

  // Get Histo_ZmumuJet_Pt0to15 from eventTree
  TH1F *Histo_ZmumuJet_Pt0to15_temp = new TH1F();
  string variable_ZmumuJet_Pt0to15 = var + ">>Histo_ZmumuJet_Pt0to15_temp" + limits;
  ZmumuJet_Pt0to15_miniTree->Draw(variable_ZmumuJet_Pt0to15.c_str(), cut.c_str());
  TH1F *Histo_ZmumuJet_Pt0to15 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt0to15_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt15to20 from eventTree
  TH1F *Histo_ZmumuJet_Pt15to20_temp = new TH1F();
  string variable_ZmumuJet_Pt15to20 = var + ">>Histo_ZmumuJet_Pt15to20_temp" + limits;
  ZmumuJet_Pt15to20_miniTree->Draw(variable_ZmumuJet_Pt15to20.c_str(), cut.c_str());
  TH1F *Histo_ZmumuJet_Pt15to20 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt15to20_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt20to30 from eventTree
  TH1F *Histo_ZmumuJet_Pt20to30_temp = new TH1F();
  string variable_ZmumuJet_Pt20to30 = var + ">>Histo_ZmumuJet_Pt20to30_temp" + limits;
  ZmumuJet_Pt20to30_miniTree->Draw(variable_ZmumuJet_Pt20to30.c_str(), cut.c_str());
  TH1F *Histo_ZmumuJet_Pt20to30 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt20to30_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt30to50 from eventTree
  TH1F *Histo_ZmumuJet_Pt30to50_temp = new TH1F();
  string variable_ZmumuJet_Pt30to50 = var + ">>Histo_ZmumuJet_Pt30to50_temp" + limits;
  ZmumuJet_Pt30to50_miniTree->Draw(variable_ZmumuJet_Pt30to50.c_str(), cut.c_str());
  TH1F *Histo_ZmumuJet_Pt30to50 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt30to50_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt50to80 from eventTree
  TH1F *Histo_ZmumuJet_Pt50to80_temp = new TH1F();
  string variable_ZmumuJet_Pt50to80 = var + ">>Histo_ZmumuJet_Pt50to80_temp" + limits;
  ZmumuJet_Pt50to80_miniTree->Draw(variable_ZmumuJet_Pt50to80.c_str(), cut.c_str());
  TH1F *Histo_ZmumuJet_Pt50to80 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt50to80_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt80to120 from eventTree
  TH1F *Histo_ZmumuJet_Pt80to120_temp = new TH1F();
  string variable_ZmumuJet_Pt80to120 = var + ">>Histo_ZmumuJet_Pt80to120_temp" + limits;
  ZmumuJet_Pt80to120_miniTree->Draw(variable_ZmumuJet_Pt80to120.c_str(), cut.c_str());
  TH1F *Histo_ZmumuJet_Pt80to120 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt80to120_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt120to170 from eventTree
  TH1F *Histo_ZmumuJet_Pt120to170_temp = new TH1F();
  string variable_ZmumuJet_Pt120to170 = var + ">>Histo_ZmumuJet_Pt120to170_temp" + limits;
  ZmumuJet_Pt120to170_miniTree->Draw(variable_ZmumuJet_Pt120to170.c_str(), cut.c_str());
  TH1F *Histo_ZmumuJet_Pt120to170 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt120to170_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt170to230 from eventTree
  TH1F *Histo_ZmumuJet_Pt170to230_temp = new TH1F();
  string variable_ZmumuJet_Pt170to230 = var + ">>Histo_ZmumuJet_Pt170to230_temp" + limits;
  ZmumuJet_Pt170to230_miniTree->Draw(variable_ZmumuJet_Pt170to230.c_str(), cut.c_str());
  TH1F *Histo_ZmumuJet_Pt170to230 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt170to230_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt230to300 from eventTree
  TH1F *Histo_ZmumuJet_Pt230to300_temp = new TH1F();
  string variable_ZmumuJet_Pt230to300 = var + ">>Histo_ZmumuJet_Pt230to300_temp" + limits;
  ZmumuJet_Pt230to300_miniTree->Draw(variable_ZmumuJet_Pt230to300.c_str(), cut.c_str());
  TH1F *Histo_ZmumuJet_Pt230to300 = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt230to300_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt300toInf from eventTree
  TH1F *Histo_ZmumuJet_Pt300toInf_temp = new TH1F();
  string variable_ZmumuJet_Pt300toInf = var + ">>Histo_ZmumuJet_Pt300toInf_temp" + limits;
  ZmumuJet_Pt300toInf_miniTree->Draw(variable_ZmumuJet_Pt300toInf.c_str(), cut.c_str());
  TH1F *Histo_ZmumuJet_Pt300toInf = (TH1F*)gDirectory->Get("Histo_ZmumuJet_Pt300toInf_temp");
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
  double integratedLuminosity = 1092.64e-03;

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
  double XSectionZmumuJet_Pt0to15 = 4.434e+03;
  double XSectionZmumuJet_Pt15to20 = 1.454e+02;
  double XSectionZmumuJet_Pt20to30 = 1.318e+02;
  double XSectionZmumuJet_Pt30to50 = 8.438e+01;
  double XSectionZmumuJet_Pt50to80 = 3.235e+01;
  double XSectionZmumuJet_Pt80to120 = 9.981e+00;
  double XSectionZmumuJet_Pt120to170 = 2.760e+00;
  double XSectionZmumuJet_Pt170to230 = 7.241e-01;
  double XSectionZmumuJet_Pt230to300 = 1.946e-01;
  double XSectionZmumuJet_Pt300toInf = 7.627e-02;

  double InitialNumberQCD_Pt15 = 6196800;
  double InitialNumberQCD_Pt30 = 5093840;
  double InitialNumberQCD_Pt80 = 3229000;
  double InitialNumberQCD_Pt170 = 3162500;
  double InitialNumberQCD_Pt300 = 3269645;
  double InitialNumberQCD_Pt470 = 2093653;
  double InitialNumberPhotonJet_Pt15 = 1221770;
  double InitialNumberPhotonJet_Pt30 = 1025300;
  double InitialNumberPhotonJet_Pt80 = 1287711;
  double InitialNumberPhotonJet_Pt170 = 1209600;
  double InitialNumberPhotonJet_Pt300 = 1033240;
  double InitialNumberTTbarJets_Tauola = 1463572;
  double InitialNumberWJets_7TeV = 10218854;
  double InitialNumberZJets_7TeV = 1047008;
  double InitialNumberQCD_Mu_Pt20to30 = 11035188;
  double InitialNumberQCD_Mu_Pt30to50 = 6951182;
  double InitialNumberQCD_Mu_Pt50to80 = 2542308;
  double InitialNumberQCD_Mu_Pt80to120 = 523053;
  double InitialNumberQCD_Mu_Pt120to170 = 316630;
  double InitialNumberQCD_Mu_Pt170toInf = 262036;
  double InitialNumberInclusiveMu15 = 5120334;
  double InitialNumberZmumuJet_Pt0to15 = 235420;
  double InitialNumberZmumuJet_Pt15to20 = 222730;
  double InitialNumberZmumuJet_Pt20to30 = 164190;
  double InitialNumberZmumuJet_Pt30to50 = 163920;
  double InitialNumberZmumuJet_Pt50to80 = 106016;
  double InitialNumberZmumuJet_Pt80to120 = 107759;
  double InitialNumberZmumuJet_Pt120to170 = 177408;
  double InitialNumberZmumuJet_Pt170to230 = 178400;
  double InitialNumberZmumuJet_Pt230to300 = 176485;
  double InitialNumberZmumuJet_Pt300toInf = 109316;

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
  Histo_ZmumuJet_Pt0to15->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt0to15) / (double)(InitialNumberZmumuJet_Pt0to15)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt15to20->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt15to20) / (double)(InitialNumberZmumuJet_Pt15to20)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt20to30->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt20to30) / (double)(InitialNumberZmumuJet_Pt20to30)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt30to50->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt30to50) / (double)(InitialNumberZmumuJet_Pt30to50)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt50to80->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt50to80) / (double)(InitialNumberZmumuJet_Pt50to80)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt80to120->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt80to120) / (double)(InitialNumberZmumuJet_Pt80to120)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt120to170->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt120to170) / (double)(InitialNumberZmumuJet_Pt120to170)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt170to230->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt170to230) / (double)(InitialNumberZmumuJet_Pt170to230)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt230to300->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt230to300) / (double)(InitialNumberZmumuJet_Pt230to300)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt300toInf->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt300toInf) / (double)(InitialNumberZmumuJet_Pt300toInf)) * (double)integratedLuminosity));

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

  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt15to20);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt20to30);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt30to50);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt50to80);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt80to120);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt120to170);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt170to230);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt230to300);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt300toInf);


  // Get the maxs and the mins to further correct the Y-axis
  double dataMax = Histo_Data->GetMaximum();
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
  double ZmumuJet_Pt0to15Max = Histo_ZmumuJet_Pt0to15->GetMaximum();
  YMax = max(YMax, ZmumuJet_Pt0to15Max);

  double dataMin = YMax;
  double PhotonJet_Pt15Min = YMax;
  double QCD_Pt15Min = YMax;
  double TTbarJets_TauolaMin = YMax;
  double WJets_7TeVMin = YMax;
  double ZJets_7TeVMin = YMax;
  double QCD_Mu_Pt20to30Min = YMax;
  double InclusiveMu15Min = YMax;
  double ZmumuJet_Pt0to15Min = YMax;
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
  for( int ibin=1 ; ibin<Histo_ZmumuJet_Pt0to15->GetNbinsX() ; ibin++ ){
    if( ((Histo_ZmumuJet_Pt0to15->GetBinContent(ibin))!=0) && ((Histo_ZmumuJet_Pt0to15->GetBinContent(ibin))<ZmumuJet_Pt0to15Min) ){
      ZmumuJet_Pt0to15Min = Histo_ZmumuJet_Pt0to15->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, ZmumuJet_Pt0to15Min);

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
  string data_name = "Data_" + var + "_" + name;
  string mc_name = "MC_" + var + "_" + name;
  string canvas_name = "DataMC_" + var + "_" + name;
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

  TLegend *legend = new TLegend(0.75, 0.80, 0.90, 0.93, "");
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
//  Histo_Data->GetYaxis()->SetRangeUser(YMin_lin, YMax_lin);
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
  Histo_QCD_Mu_Pt20to30->Draw("same");
  legend->AddEntry(Histo_QCD_Mu_Pt20to30->GetName(), "QCD Mu", "f");

  Histo_InclusiveMu15->SetLineColor(kBlack);
  Histo_InclusiveMu15->SetFillColor(kGreen-6);
  Histo_InclusiveMu15->SetFillStyle(3001);
  Histo_InclusiveMu15->SetMaximum(YMax_lin);
  Histo_InclusiveMu15->SetMinimum(YMin_lin);
//  Histo_InclusiveMu15->Draw("same");  
//  legend->AddEntry(Histo_InclusiveMu15->GetName(), "InclusiveMu15", "f");

  Histo_ZmumuJet_Pt0to15->SetLineColor(kBlack);
  Histo_ZmumuJet_Pt0to15->SetFillColor(kRed);
  Histo_ZmumuJet_Pt0to15->SetFillStyle(3001);
  Histo_ZmumuJet_Pt0to15->SetMaximum(YMax_lin);
  Histo_ZmumuJet_Pt0to15->SetMinimum(YMin_lin);
  Histo_ZmumuJet_Pt0to15->Draw("same");
  legend->AddEntry(Histo_ZmumuJet_Pt0to15->GetName(), "ZmumuJet", "f");

  Histo_ZJets_7TeV->SetLineColor(kBlack);
  Histo_ZJets_7TeV->SetFillColor(kOrange);
  Histo_ZJets_7TeV->SetFillStyle(3001);
  Histo_ZJets_7TeV->SetMaximum(YMax_lin);
  Histo_ZJets_7TeV->SetMinimum(YMin_lin);
  Histo_ZJets_7TeV->Draw("same");
  legend->AddEntry(Histo_ZJets_7TeV->GetName(), "ZJets", "f");

  Histo_WJets_7TeV->SetLineColor(kBlack);
  Histo_WJets_7TeV->SetFillColor(kMagenta+3);
  Histo_WJets_7TeV->SetFillStyle(3001);
  Histo_WJets_7TeV->SetMaximum(YMax_lin);
  Histo_WJets_7TeV->SetMinimum(YMin_lin);
  Histo_WJets_7TeV->Draw("same");
  legend->AddEntry(Histo_WJets_7TeV->GetName(), "WJets", "f");

  Histo_TTbarJets_Tauola->SetLineColor(kBlack);
  Histo_TTbarJets_Tauola->SetFillColor(kBlue);
  Histo_TTbarJets_Tauola->SetFillStyle(3001);
  Histo_TTbarJets_Tauola->SetMaximum(YMax_lin);
  Histo_TTbarJets_Tauola->SetMinimum(YMin_lin);
  Histo_TTbarJets_Tauola->Draw("same");
  legend->AddEntry(Histo_TTbarJets_Tauola->GetName(), "TTbarJets", "f");

  Histo_PhotonJet_Pt15->SetLineColor(kBlack);
  Histo_PhotonJet_Pt15->SetFillColor(kMagenta);
  Histo_PhotonJet_Pt15->SetFillStyle(3001);
  Histo_PhotonJet_Pt15->SetMaximum(YMax_lin);
  Histo_PhotonJet_Pt15->SetMinimum(YMin_lin);
  Histo_PhotonJet_Pt15->Draw("same");
  legend->AddEntry(Histo_PhotonJet_Pt15->GetName(), "PhotonJet", "f");

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
  string PicName="Plots_TEST/gif/DataMC_" + var + "_" + name + ".gif";
  c1->Print(PicName.c_str());
  PicName="Plots_TEST/eps/DataMC_" + var + "_" + name + ".eps";
  c1->Print(PicName.c_str());
  string convert = "convert Plots_TEST/eps/DataMC_" + var + "_" + name + ".eps" + " Plots_TEST/pdf/DataMC_" + var + "_" + name + ".pdf";
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
    Histo_ZmumuJet_Pt0to15->SetMaximum(YMax_log);
    Histo_ZmumuJet_Pt0to15->SetMinimum(YMin_log);
    Histo_ZmumuJet_Pt0to15->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
    c1->SetLogy(1);
    c1->Update();
    c1->Draw();
    string PicName_log="Plots_TEST/gif/DataMC_" + var + "_" + name + "_log.gif";
    c1->Print(PicName_log.c_str());
    PicName="Plots_TEST/eps/DataMC_" + var + "_" + name + "_log.eps";
    c1->Print(PicName.c_str());
    string convert = "convert Plots_TEST/eps/DataMC_" + var + "_" + name + "_log.eps" + " Plots_TEST/pdf/DataMC_" + var + "_" + name + "_log.pdf";
    system(convert.c_str());
    c1->SetLogy(0);
    c1->Update();
  }

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
  Histo_ZmumuJet_Pt0to15_temp->Delete();
  Histo_ZmumuJet_Pt0to15->Delete();
  Histo_ZmumuJet_Pt15to20_temp->Delete();
  Histo_ZmumuJet_Pt15to20->Delete();
  Histo_ZmumuJet_Pt20to30_temp->Delete();
  Histo_ZmumuJet_Pt20to30->Delete();
  Histo_ZmumuJet_Pt30to50_temp->Delete();
  Histo_ZmumuJet_Pt30to50->Delete();
  Histo_ZmumuJet_Pt50to80_temp->Delete();
  Histo_ZmumuJet_Pt50to80->Delete();
  Histo_ZmumuJet_Pt80to120_temp->Delete();
  Histo_ZmumuJet_Pt80to120->Delete();
  Histo_ZmumuJet_Pt120to170_temp->Delete();
  Histo_ZmumuJet_Pt120to170->Delete();
  Histo_ZmumuJet_Pt170to230_temp->Delete();
  Histo_ZmumuJet_Pt170to230->Delete();
  Histo_ZmumuJet_Pt230to300_temp->Delete();
  Histo_ZmumuJet_Pt230to300->Delete();
  Histo_ZmumuJet_Pt300toInf_temp->Delete();
  Histo_ZmumuJet_Pt300toInf->Delete();

}

void DrawDataMCplot_TH1I(TTree *Data_miniTree, TTree *QCD_Pt15_miniTree, TTree *QCD_Pt30_miniTree, TTree *QCD_Pt80_miniTree, TTree *QCD_Pt170_miniTree, TTree *QCD_Pt300_miniTree, TTree *QCD_Pt470_miniTree, TTree *PhotonJet_Pt15_miniTree, TTree *PhotonJet_Pt30_miniTree, TTree *PhotonJet_Pt80_miniTree, TTree *PhotonJet_Pt170_miniTree, TTree *PhotonJet_Pt300_miniTree, TTree *TTbarJets_Tauola_miniTree, TTree *WJets_7TeV_miniTree, TTree *ZJets_7TeV_miniTree, TTree *QCD_Mu_Pt20to30_miniTree, TTree *QCD_Mu_Pt30to50_miniTree, TTree *QCD_Mu_Pt50to80_miniTree, TTree *QCD_Mu_Pt80to120_miniTree, TTree *QCD_Mu_Pt120to170_miniTree, TTree *QCD_Mu_Pt170toInf_miniTree, TTree *InclusiveMu15_miniTree, TTree *ZmumuJet_Pt0to15_miniTree, TTree *ZmumuJet_Pt15to20_miniTree, TTree *ZmumuJet_Pt20to30_miniTree, TTree *ZmumuJet_Pt30to50_miniTree, TTree *ZmumuJet_Pt50to80_miniTree, TTree *ZmumuJet_Pt80to120_miniTree, TTree *ZmumuJet_Pt120to170_miniTree, TTree *ZmumuJet_Pt170to230_miniTree, TTree *ZmumuJet_Pt230to300_miniTree, TTree *ZmumuJet_Pt300toInf_miniTree, string var, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1){

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

  // Get Histo_ZmumuJet_Pt0to15 from eventTree
  TH1I *Histo_ZmumuJet_Pt0to15_temp = new TH1I();
  string variable_ZmumuJet_Pt0to15 = var + ">>Histo_ZmumuJet_Pt0to15_temp" + limits;
  ZmumuJet_Pt0to15_miniTree->Draw(variable_ZmumuJet_Pt0to15.c_str(), cut.c_str());
  TH1I *Histo_ZmumuJet_Pt0to15 = (TH1I*)gDirectory->Get("Histo_ZmumuJet_Pt0to15_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt15to20 from eventTree
  TH1I *Histo_ZmumuJet_Pt15to20_temp = new TH1I();
  string variable_ZmumuJet_Pt15to20 = var + ">>Histo_ZmumuJet_Pt15to20_temp" + limits;
  ZmumuJet_Pt15to20_miniTree->Draw(variable_ZmumuJet_Pt15to20.c_str(), cut.c_str());
  TH1I *Histo_ZmumuJet_Pt15to20 = (TH1I*)gDirectory->Get("Histo_ZmumuJet_Pt15to20_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt20to30 from eventTree
  TH1I *Histo_ZmumuJet_Pt20to30_temp = new TH1I();
  string variable_ZmumuJet_Pt20to30 = var + ">>Histo_ZmumuJet_Pt20to30_temp" + limits;
  ZmumuJet_Pt20to30_miniTree->Draw(variable_ZmumuJet_Pt20to30.c_str(), cut.c_str());
  TH1I *Histo_ZmumuJet_Pt20to30 = (TH1I*)gDirectory->Get("Histo_ZmumuJet_Pt20to30_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt30to50 from eventTree
  TH1I *Histo_ZmumuJet_Pt30to50_temp = new TH1I();
  string variable_ZmumuJet_Pt30to50 = var + ">>Histo_ZmumuJet_Pt30to50_temp" + limits;
  ZmumuJet_Pt30to50_miniTree->Draw(variable_ZmumuJet_Pt30to50.c_str(), cut.c_str());
  TH1I *Histo_ZmumuJet_Pt30to50 = (TH1I*)gDirectory->Get("Histo_ZmumuJet_Pt30to50_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt50to80 from eventTree
  TH1I *Histo_ZmumuJet_Pt50to80_temp = new TH1I();
  string variable_ZmumuJet_Pt50to80 = var + ">>Histo_ZmumuJet_Pt50to80_temp" + limits;
  ZmumuJet_Pt50to80_miniTree->Draw(variable_ZmumuJet_Pt50to80.c_str(), cut.c_str());
  TH1I *Histo_ZmumuJet_Pt50to80 = (TH1I*)gDirectory->Get("Histo_ZmumuJet_Pt50to80_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt80to120 from eventTree
  TH1I *Histo_ZmumuJet_Pt80to120_temp = new TH1I();
  string variable_ZmumuJet_Pt80to120 = var + ">>Histo_ZmumuJet_Pt80to120_temp" + limits;
  ZmumuJet_Pt80to120_miniTree->Draw(variable_ZmumuJet_Pt80to120.c_str(), cut.c_str());
  TH1I *Histo_ZmumuJet_Pt80to120 = (TH1I*)gDirectory->Get("Histo_ZmumuJet_Pt80to120_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt120to170 from eventTree
  TH1I *Histo_ZmumuJet_Pt120to170_temp = new TH1I();
  string variable_ZmumuJet_Pt120to170 = var + ">>Histo_ZmumuJet_Pt120to170_temp" + limits;
  ZmumuJet_Pt120to170_miniTree->Draw(variable_ZmumuJet_Pt120to170.c_str(), cut.c_str());
  TH1I *Histo_ZmumuJet_Pt120to170 = (TH1I*)gDirectory->Get("Histo_ZmumuJet_Pt120to170_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt170to230 from eventTree
  TH1I *Histo_ZmumuJet_Pt170to230_temp = new TH1I();
  string variable_ZmumuJet_Pt170to230 = var + ">>Histo_ZmumuJet_Pt170to230_temp" + limits;
  ZmumuJet_Pt170to230_miniTree->Draw(variable_ZmumuJet_Pt170to230.c_str(), cut.c_str());
  TH1I *Histo_ZmumuJet_Pt170to230 = (TH1I*)gDirectory->Get("Histo_ZmumuJet_Pt170to230_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt230to300 from eventTree
  TH1I *Histo_ZmumuJet_Pt230to300_temp = new TH1I();
  string variable_ZmumuJet_Pt230to300 = var + ">>Histo_ZmumuJet_Pt230to300_temp" + limits;
  ZmumuJet_Pt230to300_miniTree->Draw(variable_ZmumuJet_Pt230to300.c_str(), cut.c_str());
  TH1I *Histo_ZmumuJet_Pt230to300 = (TH1I*)gDirectory->Get("Histo_ZmumuJet_Pt230to300_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt300toInf from eventTree
  TH1I *Histo_ZmumuJet_Pt300toInf_temp = new TH1I();
  string variable_ZmumuJet_Pt300toInf = var + ">>Histo_ZmumuJet_Pt300toInf_temp" + limits;
  ZmumuJet_Pt300toInf_miniTree->Draw(variable_ZmumuJet_Pt300toInf.c_str(), cut.c_str());
  TH1I *Histo_ZmumuJet_Pt300toInf = (TH1I*)gDirectory->Get("Histo_ZmumuJet_Pt300toInf_temp");
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
  double integratedLuminosity = 1092.64e-03;

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
  double XSectionZmumuJet_Pt0to15 = 4.434e+03;
  double XSectionZmumuJet_Pt15to20 = 1.454e+02;
  double XSectionZmumuJet_Pt20to30 = 1.318e+02;
  double XSectionZmumuJet_Pt30to50 = 8.438e+01;
  double XSectionZmumuJet_Pt50to80 = 3.235e+01;
  double XSectionZmumuJet_Pt80to120 = 9.981e+00;
  double XSectionZmumuJet_Pt120to170 = 2.760e+00;
  double XSectionZmumuJet_Pt170to230 = 7.241e-01;
  double XSectionZmumuJet_Pt230to300 = 1.946e-01;
  double XSectionZmumuJet_Pt300toInf = 7.627e-02;

  double InitialNumberQCD_Pt15 = 6196800;
  double InitialNumberQCD_Pt30 = 5093840;
  double InitialNumberQCD_Pt80 = 3229000;
  double InitialNumberQCD_Pt170 = 3162500;
  double InitialNumberQCD_Pt300 = 3269645;
  double InitialNumberQCD_Pt470 = 2093653;
  double InitialNumberPhotonJet_Pt15 = 1221770;
  double InitialNumberPhotonJet_Pt30 = 1025300;
  double InitialNumberPhotonJet_Pt80 = 1287711;
  double InitialNumberPhotonJet_Pt170 = 1209600;
  double InitialNumberPhotonJet_Pt300 = 1033240;
  double InitialNumberTTbarJets_Tauola = 1463572;
  double InitialNumberWJets_7TeV = 10218854;
  double InitialNumberZJets_7TeV = 1047008;
  double InitialNumberQCD_Mu_Pt20to30 = 11035188;
  double InitialNumberQCD_Mu_Pt30to50 = 6951182;
  double InitialNumberQCD_Mu_Pt50to80 = 2542308;
  double InitialNumberQCD_Mu_Pt80to120 = 523053;
  double InitialNumberQCD_Mu_Pt120to170 = 316630;
  double InitialNumberQCD_Mu_Pt170toInf = 262036;
  double InitialNumberInclusiveMu15 = 5120334;
  double InitialNumberZmumuJet_Pt0to15 = 235420;
  double InitialNumberZmumuJet_Pt15to20 = 222730;
  double InitialNumberZmumuJet_Pt20to30 = 164190;
  double InitialNumberZmumuJet_Pt30to50 = 163920;
  double InitialNumberZmumuJet_Pt50to80 = 106016;
  double InitialNumberZmumuJet_Pt80to120 = 107759;
  double InitialNumberZmumuJet_Pt120to170 = 177408;
  double InitialNumberZmumuJet_Pt170to230 = 178400;
  double InitialNumberZmumuJet_Pt230to300 = 176485;
  double InitialNumberZmumuJet_Pt300toInf = 109316;

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
  Histo_ZmumuJet_Pt0to15->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt0to15) / (double)(InitialNumberZmumuJet_Pt0to15)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt15to20->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt15to20) / (double)(InitialNumberZmumuJet_Pt15to20)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt20to30->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt20to30) / (double)(InitialNumberZmumuJet_Pt20to30)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt30to50->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt30to50) / (double)(InitialNumberZmumuJet_Pt30to50)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt50to80->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt50to80) / (double)(InitialNumberZmumuJet_Pt50to80)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt80to120->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt80to120) / (double)(InitialNumberZmumuJet_Pt80to120)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt120to170->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt120to170) / (double)(InitialNumberZmumuJet_Pt120to170)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt170to230->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt170to230) / (double)(InitialNumberZmumuJet_Pt170to230)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt230to300->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt230to300) / (double)(InitialNumberZmumuJet_Pt230to300)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt300toInf->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt300toInf) / (double)(InitialNumberZmumuJet_Pt300toInf)) * (double)integratedLuminosity));

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

  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt15to20);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt20to30);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt30to50);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt50to80);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt80to120);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt120to170);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt170to230);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt230to300);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt300toInf);


  // Get the maxs and the mins to further correct the Y-axis
  double dataMax = Histo_Data->GetMaximum();
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
  double ZmumuJet_Pt0to15Max = Histo_ZmumuJet_Pt0to15->GetMaximum();
  YMax = max(YMax, ZmumuJet_Pt0to15Max);

  double dataMin = YMax;
  double PhotonJet_Pt15Min = YMax;
  double QCD_Pt15Min = YMax;
  double TTbarJets_TauolaMin = YMax;
  double WJets_7TeVMin = YMax;
  double ZJets_7TeVMin = YMax;
  double QCD_Mu_Pt20to30Min = YMax;
  double InclusiveMu15Min = YMax;
  double ZmumuJet_Pt0to15Min = YMax;
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
  for( int ibin=1 ; ibin<Histo_ZmumuJet_Pt0to15->GetNbinsX() ; ibin++ ){
    if( ((Histo_ZmumuJet_Pt0to15->GetBinContent(ibin))!=0) && ((Histo_ZmumuJet_Pt0to15->GetBinContent(ibin))<ZmumuJet_Pt0to15Min) ){
      ZmumuJet_Pt0to15Min = Histo_ZmumuJet_Pt0to15->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, ZmumuJet_Pt0to15Min);

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
  string data_name = "Data_" + var + "_" + name;
  string mc_name = "MC_" + var + "_" + name;
  string canvas_name = "DataMC_" + var + "_" + name;
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

  TLegend *legend = new TLegend(0.75, 0.80, 0.90, 0.93, "");
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
//  Histo_Data->GetYaxis()->SetRangeUser(YMin_lin, YMax_lin);
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
  Histo_QCD_Mu_Pt20to30->Draw("same");
  legend->AddEntry(Histo_QCD_Mu_Pt20to30->GetName(), "QCD Mu", "f");

  Histo_InclusiveMu15->SetLineColor(kBlack);
  Histo_InclusiveMu15->SetFillColor(kGreen-6);
  Histo_InclusiveMu15->SetFillStyle(3001);
  Histo_InclusiveMu15->SetMaximum(YMax_lin);
  Histo_InclusiveMu15->SetMinimum(YMin_lin);
//  Histo_InclusiveMu15->Draw("same");  
//  legend->AddEntry(Histo_InclusiveMu15->GetName(), "InclusiveMu15", "f");

  Histo_ZmumuJet_Pt0to15->SetLineColor(kBlack);
  Histo_ZmumuJet_Pt0to15->SetFillColor(kRed);
  Histo_ZmumuJet_Pt0to15->SetFillStyle(3001);
  Histo_ZmumuJet_Pt0to15->SetMaximum(YMax_lin);
  Histo_ZmumuJet_Pt0to15->SetMinimum(YMin_lin);
  Histo_ZmumuJet_Pt0to15->Draw("same");
  legend->AddEntry(Histo_ZmumuJet_Pt0to15->GetName(), "ZmumuJet", "f");

  Histo_ZJets_7TeV->SetLineColor(kBlack);
  Histo_ZJets_7TeV->SetFillColor(kOrange);
  Histo_ZJets_7TeV->SetFillStyle(3001);
  Histo_ZJets_7TeV->SetMaximum(YMax_lin);
  Histo_ZJets_7TeV->SetMinimum(YMin_lin);
  Histo_ZJets_7TeV->Draw("same");
  legend->AddEntry(Histo_ZJets_7TeV->GetName(), "ZJets", "f");

  Histo_WJets_7TeV->SetLineColor(kBlack);
  Histo_WJets_7TeV->SetFillColor(kMagenta+3);
  Histo_WJets_7TeV->SetFillStyle(3001);
  Histo_WJets_7TeV->SetMaximum(YMax_lin);
  Histo_WJets_7TeV->SetMinimum(YMin_lin);
  Histo_WJets_7TeV->Draw("same");
  legend->AddEntry(Histo_WJets_7TeV->GetName(), "WJets", "f");

  Histo_TTbarJets_Tauola->SetLineColor(kBlack);
  Histo_TTbarJets_Tauola->SetFillColor(kBlue);
  Histo_TTbarJets_Tauola->SetFillStyle(3001);
  Histo_TTbarJets_Tauola->SetMaximum(YMax_lin);
  Histo_TTbarJets_Tauola->SetMinimum(YMin_lin);
  Histo_TTbarJets_Tauola->Draw("same");
  legend->AddEntry(Histo_TTbarJets_Tauola->GetName(), "TTbarJets", "f");

  Histo_PhotonJet_Pt15->SetLineColor(kBlack);
  Histo_PhotonJet_Pt15->SetFillColor(kMagenta);
  Histo_PhotonJet_Pt15->SetFillStyle(3001);
  Histo_PhotonJet_Pt15->SetMaximum(YMax_lin);
  Histo_PhotonJet_Pt15->SetMinimum(YMin_lin);
  Histo_PhotonJet_Pt15->Draw("same");
  legend->AddEntry(Histo_PhotonJet_Pt15->GetName(), "PhotonJet", "f");

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
  string PicName="Plots_TEST/gif/DataMC_" + var + "_" + name + ".gif";
  c1->Print(PicName.c_str());
  PicName="Plots_TEST/eps/DataMC_" + var + "_" + name + ".eps";
  c1->Print(PicName.c_str());
  string convert = "convert Plots_TEST/eps/DataMC_" + var + "_" + name + ".eps" + " Plots_TEST/pdf/DataMC_" + var + "_" + name + ".pdf";
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
    Histo_ZmumuJet_Pt0to15->SetMaximum(YMax_log);
    Histo_ZmumuJet_Pt0to15->SetMinimum(YMin_log);
    Histo_ZmumuJet_Pt0to15->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
    c1->SetLogy(1);
    c1->Update();
    c1->Draw();
    string PicName_log="Plots_TEST/gif/DataMC_" + var + "_" + name + "_log.gif";
    c1->Print(PicName_log.c_str());
    PicName="Plots_TEST/eps/DataMC_" + var + "_" + name + "_log.eps";
    c1->Print(PicName.c_str());
    string convert = "convert Plots_TEST/eps/DataMC_" + var + "_" + name + "_log.eps" + " Plots_TEST/pdf/DataMC_" + var + "_" + name + "_log.pdf";
    system(convert.c_str());
    c1->SetLogy(0);
    c1->Update();
  }

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
  Histo_ZmumuJet_Pt0to15_temp->Delete();
  Histo_ZmumuJet_Pt0to15->Delete();
  Histo_ZmumuJet_Pt15to20_temp->Delete();
  Histo_ZmumuJet_Pt15to20->Delete();
  Histo_ZmumuJet_Pt20to30_temp->Delete();
  Histo_ZmumuJet_Pt20to30->Delete();
  Histo_ZmumuJet_Pt30to50_temp->Delete();
  Histo_ZmumuJet_Pt30to50->Delete();
  Histo_ZmumuJet_Pt50to80_temp->Delete();
  Histo_ZmumuJet_Pt50to80->Delete();
  Histo_ZmumuJet_Pt80to120_temp->Delete();
  Histo_ZmumuJet_Pt80to120->Delete();
  Histo_ZmumuJet_Pt120to170_temp->Delete();
  Histo_ZmumuJet_Pt120to170->Delete();
  Histo_ZmumuJet_Pt170to230_temp->Delete();
  Histo_ZmumuJet_Pt170to230->Delete();
  Histo_ZmumuJet_Pt230to300_temp->Delete();
  Histo_ZmumuJet_Pt230to300->Delete();
  Histo_ZmumuJet_Pt300toInf_temp->Delete();
  Histo_ZmumuJet_Pt300toInf->Delete();

}


void DrawDataMCplot_TH2F(TTree *Data_miniTree, TTree *QCD_Pt15_miniTree, TTree *QCD_Pt30_miniTree, TTree *QCD_Pt80_miniTree, TTree *QCD_Pt170_miniTree, TTree *QCD_Pt300_miniTree, TTree *QCD_Pt470_miniTree, TTree *PhotonJet_Pt15_miniTree, TTree *PhotonJet_Pt30_miniTree, TTree *PhotonJet_Pt80_miniTree, TTree *PhotonJet_Pt170_miniTree, TTree *PhotonJet_Pt300_miniTree, TTree *TTbarJets_Tauola_miniTree, TTree *WJets_7TeV_miniTree, TTree *ZJets_7TeV_miniTree, TTree *QCD_Mu_Pt20to30_miniTree, TTree *QCD_Mu_Pt30to50_miniTree, TTree *QCD_Mu_Pt50to80_miniTree, TTree *QCD_Mu_Pt80to120_miniTree, TTree *QCD_Mu_Pt120to170_miniTree, TTree *QCD_Mu_Pt170toInf_miniTree, TTree *InclusiveMu15_miniTree, TTree *ZmumuJet_Pt0to15_miniTree, TTree *ZmumuJet_Pt15to20_miniTree, TTree *ZmumuJet_Pt20to30_miniTree, TTree *ZmumuJet_Pt30to50_miniTree, TTree *ZmumuJet_Pt50to80_miniTree, TTree *ZmumuJet_Pt80to120_miniTree, TTree *ZmumuJet_Pt120to170_miniTree, TTree *ZmumuJet_Pt170to230_miniTree, TTree *ZmumuJet_Pt230to300_miniTree, TTree *ZmumuJet_Pt300toInf_miniTree, string var1, string var2, string limits, string cut, string name, string Title_var1, string Title_var2, bool inlog_var1, bool inlog_var2, TCanvas *c1){

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

  // Get Histo_ZmumuJet_Pt0to15 from eventTree
  TH2F *Histo_ZmumuJet_Pt0to15_temp = new TH2F();
  string variable_ZmumuJet_Pt0to15 = var2 + ":" + var1 + ">>Histo_ZmumuJet_Pt0to15_temp" + limits;
  ZmumuJet_Pt0to15_miniTree->Draw(variable_ZmumuJet_Pt0to15.c_str(), cut.c_str());
  TH2F *Histo_ZmumuJet_Pt0to15 = (TH2F*)gDirectory->Get("Histo_ZmumuJet_Pt0to15_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt15to20 from eventTree
  TH2F *Histo_ZmumuJet_Pt15to20_temp = new TH2F();
  string variable_ZmumuJet_Pt15to20 = var2 + ":" + var1 + ">>Histo_ZmumuJet_Pt15to20_temp" + limits;
  ZmumuJet_Pt15to20_miniTree->Draw(variable_ZmumuJet_Pt15to20.c_str(), cut.c_str());
  TH2F *Histo_ZmumuJet_Pt15to20 = (TH2F*)gDirectory->Get("Histo_ZmumuJet_Pt15to20_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt20to30 from eventTree
  TH2F *Histo_ZmumuJet_Pt20to30_temp = new TH2F();
  string variable_ZmumuJet_Pt20to30 = var2 + ":" + var1 + ">>Histo_ZmumuJet_Pt20to30_temp" + limits;
  ZmumuJet_Pt20to30_miniTree->Draw(variable_ZmumuJet_Pt20to30.c_str(), cut.c_str());
  TH2F *Histo_ZmumuJet_Pt20to30 = (TH2F*)gDirectory->Get("Histo_ZmumuJet_Pt20to30_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt30to50 from eventTree
  TH2F *Histo_ZmumuJet_Pt30to50_temp = new TH2F();
  string variable_ZmumuJet_Pt30to50 = var2 + ":" + var1 + ">>Histo_ZmumuJet_Pt30to50_temp" + limits;
  ZmumuJet_Pt30to50_miniTree->Draw(variable_ZmumuJet_Pt30to50.c_str(), cut.c_str());
  TH2F *Histo_ZmumuJet_Pt30to50 = (TH2F*)gDirectory->Get("Histo_ZmumuJet_Pt30to50_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt50to80 from eventTree
  TH2F *Histo_ZmumuJet_Pt50to80_temp = new TH2F();
  string variable_ZmumuJet_Pt50to80 = var2 + ":" + var1 + ">>Histo_ZmumuJet_Pt50to80_temp" + limits;
  ZmumuJet_Pt50to80_miniTree->Draw(variable_ZmumuJet_Pt50to80.c_str(), cut.c_str());
  TH2F *Histo_ZmumuJet_Pt50to80 = (TH2F*)gDirectory->Get("Histo_ZmumuJet_Pt50to80_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt80to120 from eventTree
  TH2F *Histo_ZmumuJet_Pt80to120_temp = new TH2F();
  string variable_ZmumuJet_Pt80to120 = var2 + ":" + var1 + ">>Histo_ZmumuJet_Pt80to120_temp" + limits;
  ZmumuJet_Pt80to120_miniTree->Draw(variable_ZmumuJet_Pt80to120.c_str(), cut.c_str());
  TH2F *Histo_ZmumuJet_Pt80to120 = (TH2F*)gDirectory->Get("Histo_ZmumuJet_Pt80to120_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt120to170 from eventTree
  TH2F *Histo_ZmumuJet_Pt120to170_temp = new TH2F();
  string variable_ZmumuJet_Pt120to170 = var2 + ":" + var1 + ">>Histo_ZmumuJet_Pt120to170_temp" + limits;
  ZmumuJet_Pt120to170_miniTree->Draw(variable_ZmumuJet_Pt120to170.c_str(), cut.c_str());
  TH2F *Histo_ZmumuJet_Pt120to170 = (TH2F*)gDirectory->Get("Histo_ZmumuJet_Pt120to170_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt170to230 from eventTree
  TH2F *Histo_ZmumuJet_Pt170to230_temp = new TH2F();
  string variable_ZmumuJet_Pt170to230 = var2 + ":" + var1 + ">>Histo_ZmumuJet_Pt170to230_temp" + limits;
  ZmumuJet_Pt170to230_miniTree->Draw(variable_ZmumuJet_Pt170to230.c_str(), cut.c_str());
  TH2F *Histo_ZmumuJet_Pt170to230 = (TH2F*)gDirectory->Get("Histo_ZmumuJet_Pt170to230_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt230to300 from eventTree
  TH2F *Histo_ZmumuJet_Pt230to300_temp = new TH2F();
  string variable_ZmumuJet_Pt230to300 = var2 + ":" + var1 + ">>Histo_ZmumuJet_Pt230to300_temp" + limits;
  ZmumuJet_Pt230to300_miniTree->Draw(variable_ZmumuJet_Pt230to300.c_str(), cut.c_str());
  TH2F *Histo_ZmumuJet_Pt230to300 = (TH2F*)gDirectory->Get("Histo_ZmumuJet_Pt230to300_temp");
  c1->Clear();

  // Get Histo_ZmumuJet_Pt300toInf from eventTree
  TH2F *Histo_ZmumuJet_Pt300toInf_temp = new TH2F();
  string variable_ZmumuJet_Pt300toInf = var2 + ":" + var1 + ">>Histo_ZmumuJet_Pt300toInf_temp" + limits;
  ZmumuJet_Pt300toInf_miniTree->Draw(variable_ZmumuJet_Pt300toInf.c_str(), cut.c_str());
  TH2F *Histo_ZmumuJet_Pt300toInf = (TH2F*)gDirectory->Get("Histo_ZmumuJet_Pt300toInf_temp");
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
  double integratedLuminosity = 1092.64e-03;

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
  double XSectionZmumuJet_Pt0to15 = 4.434e+03;
  double XSectionZmumuJet_Pt15to20 = 1.454e+02;
  double XSectionZmumuJet_Pt20to30 = 1.318e+02;
  double XSectionZmumuJet_Pt30to50 = 8.438e+01;
  double XSectionZmumuJet_Pt50to80 = 3.235e+01;
  double XSectionZmumuJet_Pt80to120 = 9.981e+00;
  double XSectionZmumuJet_Pt120to170 = 2.760e+00;
  double XSectionZmumuJet_Pt170to230 = 7.241e-01;
  double XSectionZmumuJet_Pt230to300 = 1.946e-01;
  double XSectionZmumuJet_Pt300toInf = 7.627e-02;

  double InitialNumberQCD_Pt15 = 6196800;
  double InitialNumberQCD_Pt30 = 5093840;
  double InitialNumberQCD_Pt80 = 3229000;
  double InitialNumberQCD_Pt170 = 3162500;
  double InitialNumberQCD_Pt300 = 3269645;
  double InitialNumberQCD_Pt470 = 2093653;
  double InitialNumberPhotonJet_Pt15 = 1221770;
  double InitialNumberPhotonJet_Pt30 = 1025300;
  double InitialNumberPhotonJet_Pt80 = 1287711;
  double InitialNumberPhotonJet_Pt170 = 1209600;
  double InitialNumberPhotonJet_Pt300 = 1033240;
  double InitialNumberTTbarJets_Tauola = 1463572;
  double InitialNumberWJets_7TeV = 10218854;
  double InitialNumberZJets_7TeV = 1047008;
  double InitialNumberQCD_Mu_Pt20to30 = 11035188;
  double InitialNumberQCD_Mu_Pt30to50 = 6951182;
  double InitialNumberQCD_Mu_Pt50to80 = 2542308;
  double InitialNumberQCD_Mu_Pt80to120 = 523053;
  double InitialNumberQCD_Mu_Pt120to170 = 316630;
  double InitialNumberQCD_Mu_Pt170toInf = 262036;
  double InitialNumberInclusiveMu15 = 5120334;
  double InitialNumberZmumuJet_Pt0to15 = 235420;
  double InitialNumberZmumuJet_Pt15to20 = 222730;
  double InitialNumberZmumuJet_Pt20to30 = 164190;
  double InitialNumberZmumuJet_Pt30to50 = 163920;
  double InitialNumberZmumuJet_Pt50to80 = 106016;
  double InitialNumberZmumuJet_Pt80to120 = 107759;
  double InitialNumberZmumuJet_Pt120to170 = 177408;
  double InitialNumberZmumuJet_Pt170to230 = 178400;
  double InitialNumberZmumuJet_Pt230to300 = 176485;
  double InitialNumberZmumuJet_Pt300toInf = 109316;

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
  Histo_ZmumuJet_Pt0to15->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt0to15) / (double)(InitialNumberZmumuJet_Pt0to15)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt15to20->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt15to20) / (double)(InitialNumberZmumuJet_Pt15to20)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt20to30->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt20to30) / (double)(InitialNumberZmumuJet_Pt20to30)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt30to50->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt30to50) / (double)(InitialNumberZmumuJet_Pt30to50)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt50to80->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt50to80) / (double)(InitialNumberZmumuJet_Pt50to80)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt80to120->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt80to120) / (double)(InitialNumberZmumuJet_Pt80to120)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt120to170->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt120to170) / (double)(InitialNumberZmumuJet_Pt120to170)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt170to230->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt170to230) / (double)(InitialNumberZmumuJet_Pt170to230)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt230to300->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt230to300) / (double)(InitialNumberZmumuJet_Pt230to300)) * (double)integratedLuminosity));
  Histo_ZmumuJet_Pt300toInf->Scale((double)(  (double)((double)(XSectionZmumuJet_Pt300toInf) / (double)(InitialNumberZmumuJet_Pt300toInf)) * (double)integratedLuminosity));

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

  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt15to20);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt20to30);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt30to50);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt50to80);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt80to120);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt120to170);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt170to230);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt230to300);
  Histo_ZmumuJet_Pt0to15->Add(Histo_ZmumuJet_Pt300toInf);


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
  double ZmumuJet_Pt0to15Max = Histo_ZmumuJet_Pt0to15->GetMaximum();
  YMax = max(YMax, ZmumuJet_Pt0to15Max);

  double dataMin = YMax;
  double PhotonJet_Pt15Min = YMax;
  double QCD_Pt15Min = YMax;
  double TTbarJets_TauolaMin = YMax;
  double WJets_7TeVMin = YMax;
  double ZJets_7TeVMin = YMax;
  double QCD_Mu_Pt20to30Min = YMax;
  double InclusiveMu15Min = YMax;
  double ZmumuJet_Pt0to15Min = YMax;
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
  for( int ibin=1 ; ibin<Histo_ZmumuJet_Pt0to15->GetNbinsX() ; ibin++ ){
    if( ((Histo_ZmumuJet_Pt0to15->GetBinContent(ibin))!=0) && ((Histo_ZmumuJet_Pt0to15->GetBinContent(ibin))<ZmumuJet_Pt0to15Min) ){
      ZmumuJet_Pt0to15Min = Histo_ZmumuJet_Pt0to15->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, ZmumuJet_Pt0to15Min);

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
  string data_name = "Data_" + var1 + "_VS_" + var2 + "_" + name;
  string mc_name = "MC_" + var1 + "_VS_" + var2 + "_" + name;
  string canvas_name = "DataMC_" + var1 + "_VS_" + var2 + "_" + name;
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
  legend->SetTextSize(0.025);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kWhite);
  legend->SetShadowColor(kWhite);

  // // First: draw the data to get correct Y-axis scale
  Histo_Data->GetXaxis()->SetTitle(Title_var1.c_str());
  Histo_Data->GetYaxis()->SetTitle(Title_var2.c_str());
  Histo_Data->SetLineColor(kBlack);
  Histo_Data->SetMarkerColor(kBlack);
//  Histo_Data->SetMarkerSize(0.7);
//  Histo_Data->SetMarkerStyle(20);
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
  Histo_QCD_Mu_Pt20to30->Draw("SCATsame");
  legend->AddEntry(Histo_QCD_Mu_Pt20to30->GetName(), "QCD Mu", "f");

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
  Histo_TTbarJets_Tauola->Draw("SCATsame");
  legend->AddEntry(Histo_TTbarJets_Tauola->GetName(), "TTbarJets", "f");

  Histo_ZmumuJet_Pt0to15->SetLineColor(kBlack);
  Histo_ZmumuJet_Pt0to15->SetFillColor(kRed);
	Histo_ZmumuJet_Pt0to15->SetMarkerColor(kRed);
  Histo_ZmumuJet_Pt0to15->SetFillStyle(3001);
  Histo_ZmumuJet_Pt0to15->Draw("SCATsame");
  legend->AddEntry(Histo_ZmumuJet_Pt0to15->GetName(), "ZmumuJet", "f");

  Histo_ZJets_7TeV->SetLineColor(kBlack);
  Histo_ZJets_7TeV->SetFillColor(kOrange);
	Histo_ZJets_7TeV->SetMarkerColor(kOrange);
  Histo_ZJets_7TeV->SetFillStyle(3001);
  Histo_ZJets_7TeV->Draw("SCATsame");
  legend->AddEntry(Histo_ZJets_7TeV->GetName(), "ZJets", "f");

  Histo_WJets_7TeV->SetLineColor(kBlack);
  Histo_WJets_7TeV->SetFillColor(kMagenta+3);
	Histo_WJets_7TeV->SetMarkerColor(kMagenta+3);
  Histo_WJets_7TeV->SetFillStyle(3001);
  Histo_WJets_7TeV->Draw("SCATsame");
  legend->AddEntry(Histo_WJets_7TeV->GetName(), "WJets", "f");

  Histo_PhotonJet_Pt15->SetLineColor(kBlack);
  Histo_PhotonJet_Pt15->SetFillColor(kMagenta);
	Histo_PhotonJet_Pt15->SetMarkerColor(kMagenta);
  Histo_PhotonJet_Pt15->SetFillStyle(3001);
  Histo_PhotonJet_Pt15->Draw("SCATsame");
  legend->AddEntry(Histo_PhotonJet_Pt15->GetName(), "PhotonJet", "f");

  // // Third: re-draw Data so that data appears in front of MC
  Histo_Data->Draw("SCATsame");

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
  string PicName="Plots_TEST/gif/DataMC_" + var1 + "_VS_" + var2 + "_" + name + ".gif";
  c1->Print(PicName.c_str());
  PicName="Plots_TEST/eps/DataMC_" + var1 + "_VS_" + var2 + "_" + name + ".eps";
  c1->Print(PicName.c_str());
  string convert = "convert Plots_TEST/eps/DataMC_" + var1 + "_VS_" + var2 + "_" + name + ".eps" + " Plots_TEST/pdf/DataMC_" + var1 + "_VS_" + var2 + "_" + name + ".pdf";
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
    Histo_ZmumuJet_Pt0to15->SetMaximum(YMax_log);
    Histo_ZmumuJet_Pt0to15->SetMinimum(YMin_log);
    Histo_ZmumuJet_Pt0to15->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
    c1->SetLogy(1);
    c1->Update();
    c1->Draw();
    string PicName_log="Plots_TEST/gif/DataMC_" + var + "_" + name + "_log.gif";
    c1->Print(PicName_log.c_str());
    PicName="Plots_TEST/eps/DataMC_" + var + "_" + name + "_log.eps";
    c1->Print(PicName.c_str());
    string convert = "convert Plots_TEST/eps/DataMC_" + var + "_" + name + "_log.eps" + " Plots_TEST/pdf/DataMC_" + var + "_" + name + "_log.pdf";
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
  Histo_ZmumuJet_Pt0to15_temp->Delete();
  Histo_ZmumuJet_Pt0to15->Delete();
  Histo_ZmumuJet_Pt15to20_temp->Delete();
  Histo_ZmumuJet_Pt15to20->Delete();
  Histo_ZmumuJet_Pt20to30_temp->Delete();
  Histo_ZmumuJet_Pt20to30->Delete();
  Histo_ZmumuJet_Pt30to50_temp->Delete();
  Histo_ZmumuJet_Pt30to50->Delete();
  Histo_ZmumuJet_Pt50to80_temp->Delete();
  Histo_ZmumuJet_Pt50to80->Delete();
  Histo_ZmumuJet_Pt80to120_temp->Delete();
  Histo_ZmumuJet_Pt80to120->Delete();
  Histo_ZmumuJet_Pt120to170_temp->Delete();
  Histo_ZmumuJet_Pt120to170->Delete();
  Histo_ZmumuJet_Pt170to230_temp->Delete();
  Histo_ZmumuJet_Pt170to230->Delete();
  Histo_ZmumuJet_Pt230to300_temp->Delete();
  Histo_ZmumuJet_Pt230to300->Delete();
  Histo_ZmumuJet_Pt300toInf_temp->Delete();
  Histo_ZmumuJet_Pt300toInf->Delete();

}

