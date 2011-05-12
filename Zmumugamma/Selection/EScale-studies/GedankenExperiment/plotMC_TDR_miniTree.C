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
#include "CMSStyle.C"

#include "DrawMC.h"


#pragma optimize 0

using namespace std;
	
//int plotMC_TDR_miniTree()
int main(int argc, char *argv[])
{
	string iteration = argv[1];
	string selection = "tight";
	gROOT->ProcessLine(".x setTDRStyle.C");
	CMSstyle();
//	string FSR_DYToMuMu_powheg = "../../Selected/" + selection + "/FSR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia/miniminiTree_36.15pb-1_" + iteration + "th_FSR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia.root";
//	string FSR_DYToMuMu_powheg = "../../Selected/" + selection + "/DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia/miniminiTree_36.15pb-1_" + iteration + "th_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia.root";
//	string FSR_DYToMuMu_powheg = "../../Selected/" + selection + "/miniTree_DATA_ALL.root";

//	string FSR_DYToMuMu_powheg = "../miniTree_FSR_DYToMuMu.root";
//	string FSR_DYToMuMu_powheg = "../miniminiTree_35.91pb-1_" + iteration + "th_FSR_DYToMuMu.root";
	string FSR_DYToMuMu_powheg = "../../miniTree_Run2010_ALL_v3.root";
	
	TFile *FSR_DYToMuMu_powheg_File = new TFile(FSR_DYToMuMu_powheg.c_str());
	TTree* FSR_DYToMuMu_powheg_miniTree = (TTree*) FSR_DYToMuMu_powheg_File->Get("miniTree");

	TCanvas *c1 = new TCanvas("Default", "Default");

// NOTES:
// NO PHOTON/MUON INFORMATION IS FILLED IN BEFORE 2B
	vector<string> set_of_cuts;
	vector<string> name;


// *** all EB + all EE
//	set_of_cuts.push_back("isSelected");
//  name.push_back("EBEE");

// *** all EB
  set_of_cuts.push_back("isSelected && Photon_isEB");
  name.push_back("EB");

// *** all EE
  set_of_cuts.push_back("isSelected && Photon_isEE");
  name.push_back("EE");
/*
// *** EB+
	set_of_cuts.push_back("isSelected && Photon_isEB && Photon_SC_Eta>0");
	name.push_back("EBP");

// *** EB-
	set_of_cuts.push_back("isSelected && Photon_isEB && Photon_SC_Eta<0");
	name.push_back("EBM");

// *** EB reference region ( (abs(iEta) > 5) && (abs(iEta) < 21) && (iPhi%20 > 5) && (iPhi%20 < 16) ) with iEta=1...85
	set_of_cuts.push_back("isSelected && Photon_isEB && ( (abs(Photon_seedPosition1) > 5) && (abs(Photon_seedPosition1) < 21) && (Photon_seedPosition2%20 > 5) && (Photon_seedPosition2%20 < 16) ) && abs(Photon_seedPosition1) > 1 && abs(Photon_seedPosition1) < 85");
	name.push_back("EBref");

// *** EB+ reference region 
	set_of_cuts.push_back("isSelected && Photon_isEB && ( (abs(Photon_seedPosition1) > 5) && (abs(Photon_seedPosition1) < 21) && (Photon_seedPosition2%20 > 5) && (Photon_seedPosition2%20 < 16) ) && abs(Photon_seedPosition1) > 1 && abs(Photon_seedPosition1) < 85 && Photon_SC_Eta>0");
	name.push_back("EBPref");

// *** EB- reference region 
	set_of_cuts.push_back("isSelected && Photon_isEB && ( (abs(Photon_seedPosition1) > 5) && (abs(Photon_seedPosition1) < 21) && (Photon_seedPosition2%20 > 5) && (Photon_seedPosition2%20 < 16) ) && abs(Photon_seedPosition1) > 1 && abs(Photon_seedPosition1) < 85 && Photon_SC_Eta<0");
	name.push_back("EBMref");

// *** EE+
	set_of_cuts.push_back("isSelected && Photon_isEE && Photon_SC_Eta>0");
	name.push_back("EEP");

// *** EE-
	set_of_cuts.push_back("isSelected && Photon_isEE && Photon_SC_Eta<0");
	name.push_back("EEM");

// *** EB |eta| < 0.5
	set_of_cuts.push_back("isSelected && Photon_isEB && abs(Photon_SC_Eta) < 0.5");
	name.push_back("EB_eta_LT_05");

// *** EB 0.5 < |eta| < 1.0
	set_of_cuts.push_back("isSelected && Photon_isEB && 0.5 < abs(Photon_SC_Eta) && abs(Photon_SC_Eta) < 1.0");
	name.push_back("EB_05_LT_eta_LT_10");

// *** EB 1.0 < |eta| < 1.44
	set_of_cuts.push_back("isSelected && Photon_isEB && 1.0 < abs(Photon_SC_Eta) && abs(Photon_SC_Eta) < 1.44");
	name.push_back("EB_10_LT_eta_LT_144");

// *** EE+ ES region
	set_of_cuts.push_back("isSelected && Photon_isEE && Photon_SC_Eta>0 && 1.7 < abs(Photon_SC_Eta) && abs(Photon_SC_Eta) < 2.5");
  name.push_back("EEP_ES");

// *** EE- ES region
	set_of_cuts.push_back("isSelected && Photon_isEE && Photon_SC_Eta<0 && 1.7 < abs(Photon_SC_Eta) && abs(Photon_SC_Eta) < 2.5");
  name.push_back("EEM_ES");

// *** all EB and unconverted
	set_of_cuts.push_back("isSelected && Photon_isEB && Photon_r9 > 0.94");
	name.push_back("EB_unconv");

// *** all EB and converted
	set_of_cuts.push_back("isSelected && Photon_isEB && Photon_r9 < 0.94");
	name.push_back("EB_conv");

// *** all EE and unconverted
	set_of_cuts.push_back("isSelected && Photon_isEE && Photon_r9 > 0.95");
	name.push_back("EE_unconv");

// *** all EE and converted
	set_of_cuts.push_back("isSelected && Photon_isEE && Photon_r9 < 0.95");
	name.push_back("EE_conv");

// *** ntracks conversions
// *** all EB and unconverted
  set_of_cuts.push_back("isSelected && Photon_isEB && Photon_convNTracks < 1");
  name.push_back("EB_unconv_ntracks");

// *** all EB and converted
  set_of_cuts.push_back("isSelected && Photon_isEB && Photon_convNTracks >= 1");
  name.push_back("EB_conv_ntracks");

// *** all EE and unconverted
  set_of_cuts.push_back("isSelected && Photon_isEE && Photon_convNTracks < 1");
  name.push_back("EE_unconv_ntracks");

// *** all EE and converted
  set_of_cuts.push_back("isSelected && Photon_isEE && Photon_convNTracks >= 1");
  name.push_back("EE_conv_ntracks");
*/

	for(int i=0; i<set_of_cuts.size() ; i++)
	{

string temptitle;
/*
	temptitle = iteration + "th_Photon_k";
	DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "(91.1876**2 - Mmumu**2 ) / (Mmumugamma**2 - Mmumu**2)", temptitle, "(40, 0.0 , 2.0)", set_of_cuts[i], name[i], "k = E_{true} / E_{reco}", true, false, c1, true);

	temptitle = iteration + "th_Photon_ik";
	DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "(Mmumugamma**2 - Mmumu**2) / (91.1876**2 - Mmumu**2 )", temptitle, "(40, 0.0 , 2.0)", set_of_cuts[i], name[i], "x = 1 / k = E_{reco} / E_{true}", true, false, c1, true);

	temptitle = iteration + "th_Photon_s";
	DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "(Mmumugamma**2 - Mmumu**2) / (91.1876**2 - Mmumu**2 ) -1", temptitle, "(40, 0.0 , 2.0)", set_of_cuts[i], name[i], "x = 1 / k = E_{reco} / E_{true}", true, false, c1, true);
*/
/*
  temptitle = iteration + "th_Photon_k";
  DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "mmg_k", temptitle, "(40, 0.0 , 2.0)", set_of_cuts[i], name[i], "k = E_{kin} / E_{reco}", true, false, c1, true);
*/
//  temptitle = iteration + "th_Photon_ik";
//  DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "mmg_ik", temptitle, "(20, 0.0 , 2.0)", set_of_cuts[i], name[i], "1 / k = E_{reco} / E_{kin}", true, false, c1, true);

  temptitle = iteration + "th_Photon_s";
  DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "mmg_s", temptitle, "(40, -1.0 , 1.0)", set_of_cuts[i], name[i], "s = E_{reco} / E_{kin.} -1", true, false, c1, true);

/*
// *****
  temptitle = iteration + "th_Photon_k_5x5";
  DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "mmg_k_5x5", temptitle, "(20, 0.0 , 2.0)", set_of_cuts[i], name[i], "k_{5x5} = E_{kin} / E_{reco}_{5x5}", true, false, c1, true);

//  temptitle = iteration + "th_Photon_ik_5x5";
//  DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "mmg_ik_5x5", temptitle, "(20, 0.0 , 2.0)", set_of_cuts[i], name[i], "1 / k_{5x5} = E_{reco}_{5x5} / E_{kin}", true, false, c1, true);

  temptitle = iteration + "th_Photon_s_5x5";
  DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "mmg_s_5x5", temptitle, "(20, -1.0 , 1.0)", set_of_cuts[i], name[i], "s_{5x5} = E_{reco}_{5x5} / E_{kin} -1", true, false, c1, true);

// *****
  temptitle = iteration + "th_Photon_k_SC";
  DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "mmg_k_SC", temptitle, "(20, 0.0 , 2.0)", set_of_cuts[i], name[i], "k_{SC} = E_{kin} / E_{reco}_{SC}", true, false, c1, true);

//  temptitle = iteration + "th_Photon_ik_SC";
//  DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "mmg_ik_SC", temptitle, "(20, 0.0 , 2.0)", set_of_cuts[i], name[i], "1 / k_{SC} = E_{reco}_{SC} / E_{kin}", true, false, c1, true);

  temptitle = iteration + "th_Photon_s_SC";
  DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "mmg_s_SC", temptitle, "(20, -1.0 , 1.0)", set_of_cuts[i], name[i], "s_{SC} = E_{reco}_{SC} / E_{kin} -1", true, false, c1, true);
*/
// *****
/*
  temptitle = iteration + "th_Photon_k_SCraw";
  DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "mmg_k_SCraw", temptitle, "(40, 0.0 , 2.0)", set_of_cuts[i], name[i], "k_{SCraw} = E_{kin} / E_{reco}_{SCraw}", true, false, c1, true);

//  temptitle = iteration + "th_Photon_ik_SCraw";
//  DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "mmg_ik_SCraw", temptitle, "(20, 0.0 , 2.0)", set_of_cuts[i], name[i], "1 / k_{SCraw} = E_{reco}_{SCraw} / E_{kin}", true, false, c1, true);

  temptitle = iteration + "th_Photon_s_SCraw";
  DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "mmg_s_SCraw", temptitle, "(40, -1.0 , 1.0)", set_of_cuts[i], name[i], "s_{SCraw} = E_{reco}_{SCraw} / E_{kin} -1", true, false, c1, true);
*/


//temptitle = iteration + "th_Photon_k_extended2";
//	DrawMCplot(FSR_DYToMuMu_powheg_miniTree, "(91.1876**2 - Mmumu**2 ) / (Mmumugamma**2 - Mmumu**2)", temptitle, "(20, 0.0 , 2.0)", set_of_cuts[i], name[i], "k = E_{true} / E_{reco}", true, false, c1, true);

	}
	return 0;	
}

