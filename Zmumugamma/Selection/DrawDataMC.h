#ifndef _DRAWDATAMC
#define _DRAWDATAMC
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


/*
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootBardak.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootBeamSpot.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootCluster.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootDummyEvent.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootEcalRecHit.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootElectron.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootEvent.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootJet.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootMCParticle.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootMCPhoton.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootMET.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootMuon.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootParticle.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootPhoton.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootRun.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootSignalEvent.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootSuperCluster.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootTopTop.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootTrack.h"
#include "/sps/cms/obondu/CMSSW_4_1_2/src/UserCode/IpnTreeProducer/interface/TRootVertex.h"
*/

#pragma optimize 0

using namespace std;

void DrawDataMCplot(TTree *Data_miniTree, TTree *FSR_DYToMuMu_miniTree, TTree *nonFSR_DYToMuMu_miniTree, TTree *QCDMu_miniTree, TTree* TTJets_miniTree, TTree *WJetsToLNu_miniTree, string var, string pic, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1, bool doFit = false);
//void DrawDataMCplot(TTree *Data_miniTree, TTree *FSR_DYToMuMu_miniTree, TTree *nonFSR_DYToMuMu_miniTree, TTree *TTJets_miniTree, TTree *WJetsToLNu_miniTree, string var, string pic, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1, bool doFit = false);

//void DrawDataMCplot_TH1I(TTree *Data_miniTree, TTree *FSR_DYToMuMu_miniTree, TTree *nonFSR_DYToMuMu_miniTree, TTree *TTJets_miniTree, TTree *WJetsToLNu_miniTree, string var, string pic, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1, bool doFit = false);

//void DrawDataMCplot_TH2F(TTree *Data_miniTree, TTree *FSR_DYToMuMu_miniTree, TTree *nonFSR_DYToMuMu_miniTree, TTree *TTJets_miniTree, TTree *WJetsToLNu_miniTree, string var1, string var2, string limits, string cut, string name, string Title_var1, string Title_var2, string pic, bool inlog_var1, bool inlog_var2, TCanvas *c1, bool doFit = false);

double weight_DYToMuMu(int nGenVertices)
{
	double weight[51] = {
//0, 0.192859, 0.37571, 0.98006, 1.47381, 2.13772, 1.97435, 1.75482, 1.61272, 1.30487, 0.858989, 0.593953, 0.406, 0.271559, 0.200834, 0.123192, 0.101752, 0.0724765, 0.0505275, 0.0609286, 0.0265446, 0.0178984, 0.0603881, 0, 0.00990419, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
0, 0.115446, 0.515513, 1.02729, 1.65565, 2.07852, 2.20219, 2.04419, 1.71476, 1.31424, 0.953279, 0.653809, 0.435285, 0.280843, 0.174236, 0.107087, 0.0646172, 0.0383951, 0.0221918, 0.0132036, 0.00758329, 0.00439256, 0.00246895, 0.00144276, 0.000825138, 0.000477362, 0.000267711, 0.000149803, 9.07888e-05, 4.86278e-05, 2.65074e-05, 1.6692e-05, 9.69296e-06, 6.1014e-06, 3.17422e-06, 1.73845e-06, 1.01719e-06, 4.02585e-07, 3.57171e-07, 2.42991e-07, 4.82115e-08, 8.47143e-08, 2.44069e-08, 3.45819e-09, 1.92746e-09, 5.2817e-10, 0, 0, 0, 0, 0
};
	return weight[nGenVertices];
}

double weight_TTJets(int nGenVertices)
{
	double weight[51] = {
//0, 0, 0.333378, 0.723157, 1.19322, 1.49033, 1.58834, 1.44156, 1.2383, 0.980278, 0.764237, 0.616463, 0.502961, 0.415539, 0.340722, 0.312991, 0.247561, 0.235585, 0.22141, 0.235256, 0.247388, 0.283565, 0.460907, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
0, 0, 0.243413, 0.821845, 1.27575, 1.57447, 1.71148, 1.59537, 1.3914, 1.10501, 0.86792, 0.649448, 0.473748, 0.350538, 0.255107, 0.177246, 0.123198, 0.0876263, 0.0682639, 0.0440952, 0.0290569, 0.0199671, 0.013285, 0.00856315, 0.00384906, 0.00349844, 0.00408291, 0.000806618, 0.000526854, 0.000221726, 0.000382953, 0.000130345, 0, 0, 4.71268e-06, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
	return weight[nGenVertices];
}
double weight_WJetsToLNu(int nGenVertices)
{
	double weight[51] = {
//0, 0, 0.330484, 0.67655, 1.23639, 1.44633, 1.56369, 1.63896, 1.20385, 1.06055, 0.727991, 0.54883, 0.514699, 0.452454, 0.377948, 0.366865, 0.244431, 0.161619, 0.1228, 0.162598, 0, 0.05807, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
0, 0, 0.38522, 0.765474, 1.34675, 1.51834, 1.58669, 1.61271, 1.15202, 0.989275, 0.663074, 0.488727, 0.448501, 0.386062, 0.315953, 0.300622, 0.196432, 0.127445, 0.0950729, 0.123675, 0, 0.0427233, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
  return weight[nGenVertices];
}
double  weight_QCDMu(int nGenVertices)
{
  double weight[51] = {
//0, 0, 0.344937, 0.735201, 1.12576, 1.38418, 1.61134, 1.46404, 1.24484, 0.943461, 0.786307, 0.635055, 0.536248, 0.4083, 0.377607, 0.251284, 0.299158, 0.313975, 0.429412, 0.189526, 0.162392, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
0, 0, 0.402067, 0.831834, 1.22624, 1.4531, 1.63504, 1.44059, 1.19124, 0.880055, 0.71619, 0.565509, 0.467278, 0.348386, 0.315668, 0.205911, 0.240412, 0.247585, 0.332455, 0.144157, 0.121435, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
  return weight[nGenVertices];
}

#endif
