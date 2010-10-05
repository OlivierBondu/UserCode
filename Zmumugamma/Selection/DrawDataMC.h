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

#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootBardak.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootBeamSpot.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootCluster.h"
#include "/sps/cms/obondu/CMSSW_3_6_1_patch4/src/UserCode/IpnTreeProducer/interface/TRootDummyEvent.h"
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


#pragma optimize 0

using namespace std;

void DrawDataMCplot(TTree *Data_miniTree, TTree *QCD_Pt15_miniTree, TTree *QCD_Pt30_miniTree, TTree *QCD_Pt80_miniTree, TTree *QCD_Pt170_miniTree, TTree *QCD_Pt300_miniTree, TTree *QCD_Pt470_miniTree, TTree *PhotonJet_Pt15_miniTree, TTree *PhotonJet_Pt30_miniTree, TTree *PhotonJet_Pt80_miniTree, TTree *PhotonJet_Pt170_miniTree, TTree *PhotonJet_Pt300_miniTree, TTree *TTbarJets_Tauola_miniTree, TTree *WJets_7TeV_miniTree, TTree *ZJets_7TeV_miniTree, TTree *QCD_Mu_Pt20to30_miniTree, TTree *QCD_Mu_Pt30to50_miniTree, TTree *QCD_Mu_Pt50to80_miniTree, TTree *QCD_Mu_Pt80to120_miniTree, TTree *QCD_Mu_Pt120to170_miniTree, TTree *QCD_Mu_Pt170toInf_miniTree, TTree *InclusiveMu15_miniTree, TTree *FSR_ZmumuJet_Pt0to15_miniTree, TTree *FSR_ZmumuJet_Pt15to20_miniTree, TTree *FSR_ZmumuJet_Pt20to30_miniTree, TTree *FSR_ZmumuJet_Pt30to50_miniTree, TTree *FSR_ZmumuJet_Pt50to80_miniTree, TTree *FSR_ZmumuJet_Pt80to120_miniTree, TTree *FSR_ZmumuJet_Pt120to170_miniTree, TTree *FSR_ZmumuJet_Pt170to230_miniTree, TTree *FSR_ZmumuJet_Pt230to300_miniTree, TTree *FSR_ZmumuJet_Pt300toInf_miniTree, TTree *ISR_ZmumuJet_Pt0to15_miniTree, TTree *ISR_ZmumuJet_Pt15to20_miniTree, TTree *ISR_ZmumuJet_Pt20to30_miniTree, TTree *ISR_ZmumuJet_Pt30to50_miniTree, TTree *ISR_ZmumuJet_Pt50to80_miniTree, TTree *ISR_ZmumuJet_Pt80to120_miniTree, TTree *ISR_ZmumuJet_Pt120to170_miniTree, TTree *ISR_ZmumuJet_Pt170to230_miniTree, TTree *ISR_ZmumuJet_Pt230to300_miniTree, TTree *ISR_ZmumuJet_Pt300toInf_miniTree, string var, string pic, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1, bool doFit = false);

void DrawDataMCplot_TH1I(TTree *Data_miniTree, TTree *QCD_Pt15_miniTree, TTree *QCD_Pt30_miniTree, TTree *QCD_Pt80_miniTree, TTree *QCD_Pt170_miniTree, TTree *QCD_Pt300_miniTree, TTree *QCD_Pt470_miniTree, TTree *PhotonJet_Pt15_miniTree, TTree *PhotonJet_Pt30_miniTree, TTree *PhotonJet_Pt80_miniTree, TTree *PhotonJet_Pt170_miniTree, TTree *PhotonJet_Pt300_miniTree, TTree *TTbarJets_Tauola_miniTree, TTree *WJets_7TeV_miniTree, TTree *ZJets_7TeV_miniTree, TTree *QCD_Mu_Pt20to30_miniTree, TTree *QCD_Mu_Pt30to50_miniTree, TTree *QCD_Mu_Pt50to80_miniTree, TTree *QCD_Mu_Pt80to120_miniTree, TTree *QCD_Mu_Pt120to170_miniTree, TTree *QCD_Mu_Pt170toInf_miniTree, TTree *InclusiveMu15_miniTree, TTree *FSR_ZmumuJet_Pt0to15_miniTree, TTree *FSR_ZmumuJet_Pt15to20_miniTree, TTree *FSR_ZmumuJet_Pt20to30_miniTree, TTree *FSR_ZmumuJet_Pt30to50_miniTree, TTree *FSR_ZmumuJet_Pt50to80_miniTree, TTree *FSR_ZmumuJet_Pt80to120_miniTree, TTree *FSR_ZmumuJet_Pt120to170_miniTree, TTree *FSR_ZmumuJet_Pt170to230_miniTree, TTree *FSR_ZmumuJet_Pt230to300_miniTree, TTree *FSR_ZmumuJet_Pt300toInf_miniTree, TTree *ISR_ZmumuJet_Pt0to15_miniTree, TTree *ISR_ZmumuJet_Pt15to20_miniTree, TTree *ISR_ZmumuJet_Pt20to30_miniTree, TTree *ISR_ZmumuJet_Pt30to50_miniTree, TTree *ISR_ZmumuJet_Pt50to80_miniTree, TTree *ISR_ZmumuJet_Pt80to120_miniTree, TTree *ISR_ZmumuJet_Pt120to170_miniTree, TTree *ISR_ZmumuJet_Pt170to230_miniTree, TTree *ISR_ZmumuJet_Pt230to300_miniTree, TTree *ISR_ZmumuJet_Pt300toInf_miniTree, string var, string pic, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1, bool doFit = false);

void DrawDataMCplot_TH2F(TTree *Data_miniTree, TTree *QCD_Pt15_miniTree, TTree *QCD_Pt30_miniTree, TTree *QCD_Pt80_miniTree, TTree *QCD_Pt170_miniTree, TTree *QCD_Pt300_miniTree, TTree *QCD_Pt470_miniTree, TTree *PhotonJet_Pt15_miniTree, TTree *PhotonJet_Pt30_miniTree, TTree *PhotonJet_Pt80_miniTree, TTree *PhotonJet_Pt170_miniTree, TTree *PhotonJet_Pt300_miniTree, TTree *TTbarJets_Tauola_miniTree, TTree *WJets_7TeV_miniTree, TTree *ZJets_7TeV_miniTree, TTree *QCD_Mu_Pt20to30_miniTree, TTree *QCD_Mu_Pt30to50_miniTree, TTree *QCD_Mu_Pt50to80_miniTree, TTree *QCD_Mu_Pt80to120_miniTree, TTree *QCD_Mu_Pt120to170_miniTree, TTree *QCD_Mu_Pt170toInf_miniTree, TTree *InclusiveMu15_miniTree, TTree *FSR_ZmumuJet_Pt0to15_miniTree, TTree *FSR_ZmumuJet_Pt15to20_miniTree, TTree *FSR_ZmumuJet_Pt20to30_miniTree, TTree *FSR_ZmumuJet_Pt30to50_miniTree, TTree *FSR_ZmumuJet_Pt50to80_miniTree, TTree *FSR_ZmumuJet_Pt80to120_miniTree, TTree *FSR_ZmumuJet_Pt120to170_miniTree, TTree *FSR_ZmumuJet_Pt170to230_miniTree, TTree *FSR_ZmumuJet_Pt230to300_miniTree, TTree *FSR_ZmumuJet_Pt300toInf_miniTree, TTree *ISR_ZmumuJet_Pt0to15_miniTree, TTree *ISR_ZmumuJet_Pt15to20_miniTree, TTree *ISR_ZmumuJet_Pt20to30_miniTree, TTree *ISR_ZmumuJet_Pt30to50_miniTree, TTree *ISR_ZmumuJet_Pt50to80_miniTree, TTree *ISR_ZmumuJet_Pt80to120_miniTree, TTree *ISR_ZmumuJet_Pt120to170_miniTree, TTree *ISR_ZmumuJet_Pt170to230_miniTree, TTree *ISR_ZmumuJet_Pt230to300_miniTree, TTree *ISR_ZmumuJet_Pt300toInf_miniTree, string var1, string var2, string limits, string cut, string name, string Title_var1, string Title_var2, string pic, bool inlog_var1, bool inlog_var2, TCanvas *c1, bool doFit = false);

