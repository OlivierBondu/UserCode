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

#pragma optimize 0

using namespace std;

void DrawDataMCplot_NormEntries_Fast(TTree *Data_miniTree, TTree *MC_miniTree, string var, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1){

	// Get Histo_Data from eventTree
	TH1F *Histo_Data_temp = new TH1F();
	string variable_Data = var + ">>Histo_Data_temp" + limits;
	Data_miniTree->Draw(variable_Data.c_str(), cut.c_str());
	TH1F *Histo_Data = (TH1F*)gDirectory->Get("Histo_Data_temp"); 
	c1->Clear();

	// Get Histo_MC from eventTree
	TH1F *Histo_MC_temp = new TH1F();
	string variable_MC = var + ">>Histo_MC_temp" + limits;
	MC_miniTree->Draw(variable_MC.c_str(), cut.c_str());
	TH1F *Histo_MC = (TH1F*)gDirectory->Get("Histo_MC_temp");
	c1->Clear();

	// TODO: implement drawUnderOverFsubleading

	// Get the number of entries for further normalization
	double a = Histo_Data->Integral();
	double b = Histo_MC->Integral();
	if( (a==0.0) || (b==0.0) ){
		cout << "no entries to plots" <<endl;
		return; 
	}	

	// Normalize
	Histo_Data->Sumw2(); // In order to have the correct error bars on data after renormalization
	// // Normalize MC and Data to 1
	//Histo_Data->Scale((double)((double)1.0/(double)a));
	//Histo_MC->Scale((double)((double)1.0/(double)b));
	// // Normalize MC to Data number of entries
	Histo_MC->Scale((double)((double)a/(double)b));

	// Get the maxs and the mins to further correct the Y-axis
	double dataMax = Histo_Data->GetMaximum();
	double mcMax = Histo_MC->GetMaximum();
	double YMax = max(dataMax, mcMax);
	double dataMin = YMax;
	double mcMin = YMax;
	// Gets the actual minimum for each histogram, and not the unfilled bin if any
	for( int ibin=1 ; ibin<Histo_Data->GetNbinsX() ; ibin++ ){
		if( ((Histo_Data->GetBinContent(ibin))!=0) && ((Histo_Data->GetBinContent(ibin))<dataMin) ){
			dataMin = Histo_Data->GetBinContent(ibin);
		}
	}
	for( int ibin=1 ; ibin<Histo_MC->GetNbinsX() ; ibin++ ){
		if( ((Histo_MC->GetBinContent(ibin))!=0) && ((Histo_MC->GetBinContent(ibin))<mcMin) ){
			mcMin = Histo_MC->GetBinContent(ibin);
		}
	}
	double YMin = min(dataMin, mcMin);	
	double YMax_lin = YMax + (YMax)*.2;
	double YMin_lin = YMin - (YMin)*.2;
	double YMax_log = YMax * 1.5;
	double YMin_log = (double) YMin / (double) 1.5;

	// Setup the histo and canvas names and title
	string data_name = "Data_" + var + "_" + name;
	string mc_name = "MC_" + var + "_" + name;
	string canvas_name = "DataMC_" + var + "_" + name;
	Histo_Data->SetName(data_name.c_str());
	Histo_MC->SetName(mc_name.c_str());
	c1->SetName(canvas_name.c_str());
	c1->SetTitle(canvas_name.c_str());

	// Draw the comparison plots
	// // First: draw the data to get correct Y-axis scale
	Histo_Data->GetXaxis()->SetTitle(Title.c_str());
	Histo_Data->SetLineColor(kBlack);
	Histo_Data->SetMarkerColor(kBlack);
	Histo_Data->SetMarkerSize(0.7);
	Histo_Data->SetMarkerStyle(20);
	Histo_Data->SetMaximum(YMax_lin);
	Histo_Data->SetMinimum(YMin_lin);
	Histo_Data->Draw("E1");

	// // Second: draw MC on the same canvas
	Histo_MC->SetLineColor(kBlack);
//	Histo_MC->SetFillColor(kOrange-3);
//	Histo_MC->SetFillColor(kRed);
//	Histo_MC->SetFillColor(kBlue);
	Histo_MC->SetFillColor(kAzure+2);
	Histo_MC->SetFillStyle(3001);
	Histo_MC->SetMaximum(YMax_lin);
	Histo_MC->SetMinimum(YMin_lin);
	Histo_MC->Draw("same");

	// // Third: re-draw Data so that data appears in front of MC
	Histo_Data->Draw("E1same");

	// // Fourth: redraw axis so that axis appears in front of everything
	gPad->RedrawAxis();

	// // Fifth: draw legend
	TLegend *legend = new TLegend(0.90, 0.83, 0.99, 0.994, "");
	legend->SetTextSize(0.025);
	legend->SetFillColor(kWhite);
	legend->SetLineColor(kWhite);
	legend->SetShadowColor(kWhite);
	legend->AddEntry(Histo_Data->GetName(), "Data", "lp");
	legend->AddEntry(Histo_MC->GetName(), "MC", "f");
	legend->Draw();

	// // Sixth: update canvas
	c1->Update();
	c1->Draw();

	// Print the canvas
	string PicName="PlotDataMC7TeV_TEST/DataMC_" + var + "_" + name + ".gif";
	c1->Print(PicName.c_str());
	if (inlog==true) {
		string PicName_log="PlotDataMC7TeV_TEST/DataMC_" + var + "_" + name + "_log.gif";
		c1->cd(1);
		c1->SetLogy(1);
		Histo_Data->SetMaximum(YMax_log);
		Histo_Data->SetMinimum(YMin_log);
		c1->Update();
		c1->Draw();
		c1->Print(PicName_log.c_str());
		c1->SetLogy(0);
		c1->Update();
	} 

	// Clean the memory
	c1->Clear();
	legend->Clear();
	Histo_Data_temp->Delete();
	Histo_MC_temp->Delete();
	Histo_Data->Delete();
	Histo_MC->Delete();

}
	
//int plotDataMC_TDR_miniTree()
int main()
{
	gROOT->ProcessLine(".x setTDRStyle.C");
	string Data = "miniTree_eventTree_DATA_MinimumBias_Commissioning10-May6thPDSkim_GOODCOLL-v1_RAW-RECO.root"; 
	string MC = "miniTree_eventTree_MC_MinBias_TuneD6T_7TeV-pythia6_Spring10-START3X_V26B-v1_GEN-SIM-RECO.root"; 
	
	TFile *Data_File = new TFile(Data.c_str());
	TFile *MC_File = new TFile(MC.c_str());
	TTree* Data_miniTree = (TTree*) Data_File->Get("miniTree");
	TTree* MC_miniTree = (TTree*) MC_File->Get("miniTree");
	TTree* Data_miniTree_allmuons = (TTree*) Data_File->Get("miniTree_allmuons");
	TTree* MC_miniTree_allmuons = (TTree*) MC_File->Get("miniTree_allmuons");
	TTree* Data_miniTree_allphotons = (TTree*) Data_File->Get("miniTree_allphotons");
	TTree* MC_miniTree_allphotons = (TTree*) MC_File->Get("miniTree_allphotons");

	TCanvas *c1 = new TCanvas("Default", "Default");

// NOTES:
// NO PHOTON/MUON INFORMATION IS FILLED IN BEFORE 2B
	vector<string> set_of_cuts;
	vector<string> name;
	set_of_cuts.push_back("isBeforeAllCuts");
	name.push_back("Before");
	set_of_cuts.push_back("isAfterCut1a");
	name.push_back("After1a");
	set_of_cuts.push_back("isAfterCut1b");
	name.push_back("After1b");
	set_of_cuts.push_back("isAfterCut1c");
	name.push_back("After1c");
	set_of_cuts.push_back("isAfterCut1d");
	name.push_back("After1d");
	set_of_cuts.push_back("isAfterCut1e");
	name.push_back("After1e");
	set_of_cuts.push_back("isAfterCut2a");
	name.push_back("After2a");
	set_of_cuts.push_back("isAfterCut2b");
	name.push_back("After2b");
/*	set_of_cuts.push_back("isAfterCut2c");
	name.push_back("After2c");
	set_of_cuts.push_back("isAfterCut3");
  name.push_back("After3");
	set_of_cuts.push_back("isAfterCut4");
  name.push_back("After4");
	set_of_cuts.push_back("isAfterCut5");
  name.push_back("After5");
	set_of_cuts.push_back("isAfterCut6");
  name.push_back("After6");
	set_of_cuts.push_back("isAfterCut7");
  name.push_back("After7");
	set_of_cuts.push_back("isAfterCut8");
  name.push_back("After8");
	set_of_cuts.push_back("isSelected");
  name.push_back("SELECTED");
	set_of_cuts.push_back("isSelected && Mmumugamma < 95.2 && Mmumugamma > 87.2");
  name.push_back("SELECTED_restrained_masswindow");
*/

	for(int i=0; i<set_of_cuts.size() ; i++){
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "NbMuons", "(10,0,10)", set_of_cuts[i], name[i], "# of muons", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "NbPhotons", "(10,0,10)", set_of_cuts[i], name[i], "# of photons", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allmuons, MC_miniTree_allmuons, "Pt_allMuons", "(100,0,100)", set_of_cuts[i], name[i], "p_{T_{#mu}}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allmuons, MC_miniTree_allmuons, "Phi_allMuons", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi_{#mu}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allmuons, MC_miniTree_allmuons, "Eta_allMuons", "(50,-3.0,3.0)", set_of_cuts[i], name[i], "#eta_{#mu}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allmuons, MC_miniTree_allmuons, "Charge_allMuons", "(20,-2,2)", set_of_cuts[i], name[i], "Charge_{#mu}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allphotons, MC_miniTree_allphotons, "Pt_allPhotons", "(100,0,100)", set_of_cuts[i], name[i], "p_{T_{#gamma}}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allphotons, MC_miniTree_allphotons, "Phi_allPhotons", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi_{#gamma}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allphotons, MC_miniTree_allphotons, "Eta_allPhotons", "(50,-3.0,3.0)", set_of_cuts[i], name[i], "#eta_{#gamma}", true, false, c1);
//FIXME		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allphotons, MC_miniTree_allphotons, "Cross_allPhotons", "(50,-1.0,1.5)", set_of_cuts[i], name[i], "cross_{#gamma}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allphotons, MC_miniTree_allphotons, "isEB_allPhotons", "(20,-1,2)", set_of_cuts[i], name[i], "#gamma isEB", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allphotons, MC_miniTree_allphotons, "isEE_allPhotons", "(20,-1,2)", set_of_cuts[i], name[i], "#gamma isEE", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allphotons, MC_miniTree_allphotons, "isEEM_allPhotons", "(20,-1,2)", set_of_cuts[i], name[i], "#gamma isEEM", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allphotons, MC_miniTree_allphotons, "isEEP_allPhotons", "(20,-1,2)", set_of_cuts[i], name[i], "#gamma isEEP", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{subleading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{subleading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{subleading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{subleading}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_Charge", "(20,-2,2)", set_of_cuts[i], name[i], "charge #mu_{near}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Mmumu", "(100,0,300)", set_of_cuts[i], name[i], "M_{#mu#mu}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Mmumugamma", "(100,70,110)", set_of_cuts[i], name[i], "M_{#mu#mu#gamma}", true, false, c1);
	

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "deltaRNear", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{near})", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "deltaRFar", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{far})", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "deltaRPlus", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{plus})", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "deltaRMinus", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{minus})", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "deltaRLeading", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{leading})", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "deltaRSubleading", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{subleading})", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_Eta", "(50,-3,3)", set_of_cuts[i], name[i], "#eta of photon", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_Phi", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi of photon", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isEB", "(10,-1,2)", set_of_cuts[i], name[i], "photon is in barrel", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isEE", "(10,-1,2)", set_of_cuts[i], name[i], "photon is in endcap", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isEEP", "(10,-1,2)", set_of_cuts[i], name[i], "photon is in endcap plus", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isEEM", "(10,-1,2)", set_of_cuts[i], name[i], "photon is in endcap minus", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_E", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon Energy", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_Et", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon Et", true, false, c1);

	}
/*
	set_of_cuts.clear();
	name.clear();
	set_of_cuts.push_back("isBeforeAllCuts && isEB_allPhotons");
	name.push_back("BeforeEB");
	set_of_cuts.push_back("isAfterCut1a && isEB_allPhotons");
	name.push_back("After1aEB");
	set_of_cuts.push_back("isAfterCut1b && isEB_allPhotons");
	name.push_back("After1bEB");
	set_of_cuts.push_back("isAfterCut1c && isEB_allPhotons");
	name.push_back("After1cEB");
	set_of_cuts.push_back("isAfterCut1d && isEB_allPhotons");
	name.push_back("After1dEB");
	set_of_cuts.push_back("isAfterCut1e && isEB_allPhotons");
	name.push_back("After1eEB");
	set_of_cuts.push_back("isAfterCut2a && isEB_allPhotons");
	name.push_back("After2aEB");
	set_of_cuts.push_back("isAfterCut2b && isEB_allPhotons");
	name.push_back("After2bEB");
	set_of_cuts.push_back("isAfterCut2c && isEB_allPhotons");
	name.push_back("After2cEB");
	set_of_cuts.push_back("isBeforeAllCuts && isEE_allPhotons");
	name.push_back("BeforeEE");
	set_of_cuts.push_back("isAfterCut1a && isEE_allPhotons");
	name.push_back("After1aEE");
	set_of_cuts.push_back("isAfterCut1b && isEE_allPhotons");
	name.push_back("After1bEE");
	set_of_cuts.push_back("isAfterCut1c && isEE_allPhotons");
	name.push_back("After1cEE");
	set_of_cuts.push_back("isAfterCut1d && isEE_allPhotons");
	name.push_back("After1dEE");
	set_of_cuts.push_back("isAfterCut1e && isEE_allPhotons");
	name.push_back("After1eEE");
	set_of_cuts.push_back("isAfterCut2a && isEE_allPhotons");
	name.push_back("After2aEE");
	set_of_cuts.push_back("isAfterCut2b && isEE_allPhotons");
	name.push_back("After2bEE");
	set_of_cuts.push_back("isAfterCut2c && isEE_allPhotons");
	name.push_back("After2cEE");
	set_of_cuts.push_back("isBeforeAllCuts && isEEM_allPhotons");
	name.push_back("BeforeEEM");
	set_of_cuts.push_back("isAfterCut1a && isEEM_allPhotons");
	name.push_back("After1aEEM");
	set_of_cuts.push_back("isAfterCut1b && isEEM_allPhotons");
	name.push_back("After1bEEM");
	set_of_cuts.push_back("isAfterCut1c && isEEM_allPhotons");
	name.push_back("After1cEEM");
	set_of_cuts.push_back("isAfterCut1d && isEEM_allPhotons");
	name.push_back("After1dEEM");
	set_of_cuts.push_back("isAfterCut1e && isEEM_allPhotons");
	name.push_back("After1eEEM");
	set_of_cuts.push_back("isAfterCut2a && isEEM_allPhotons");
	name.push_back("After2aEEM");
	set_of_cuts.push_back("isAfterCut2b && isEEM_allPhotons");
	name.push_back("After2bEEM");
	set_of_cuts.push_back("isAfterCut2c && isEEM_allPhotons");
	name.push_back("After2cEEM");
	set_of_cuts.push_back("isBeforeAllCuts && isEEP_allPhotons");
	name.push_back("BeforeEEP");
	set_of_cuts.push_back("isAfterCut1a && isEEP_allPhotons");
	name.push_back("After1aEEP");
	set_of_cuts.push_back("isAfterCut1b && isEEP_allPhotons");
	name.push_back("After1bEEP");
	set_of_cuts.push_back("isAfterCut1c && isEEP_allPhotons");
	name.push_back("After1cEEP");
	set_of_cuts.push_back("isAfterCut1d && isEEP_allPhotons");
	name.push_back("After1dEEP");
	set_of_cuts.push_back("isAfterCut1e && isEEP_allPhotons");
	name.push_back("After1eEEP");
	set_of_cuts.push_back("isAfterCut2a && isEEP_allPhotons");
	name.push_back("After2aEEP");
	set_of_cuts.push_back("isAfterCut2b && isEEP_allPhotons");
	name.push_back("After2bEEP");
	set_of_cuts.push_back("isAfterCut2c && isEEP_allPhotons");
	name.push_back("After2cEEP");

	for(int i=0; i<set_of_cuts.size() ; i++){
		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allphotons, MC_miniTree_allphotons, "Pt_allPhotons", "(100,0,100)", set_of_cuts[i], name[i], "p_{T_{#gamma}}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allphotons, MC_miniTree_allphotons, "Phi_allPhotons", "(50,-3.15,3.15)", set_of_cuts[i], name[i], "#phi_{#gamma}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree_allphotons, MC_miniTree_allphotons, "Eta_allPhotons", "(50,-3.0,3.0)", set_of_cuts[i], name[i], "#eta_{#gamma}", true, false, c1);
	}
*/

//	for(int i=0; i<set_of_cuts.size() ; i++){ // loop over different set of cuts
	// ____________________________________________
	// Muon variables
	// ____________________________________________
/*

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu^{+}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_Eta", "(10,-3,3)", set_of_cuts[i], name[i], "#eta #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_Eta", "(10,-3,3)", set_of_cuts[i], name[i], "#eta #mu^{+}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{near}", true, false, c1);


		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu_{subleading}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu_{subleading}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu_{subleading}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu_{subleading}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu_{subleading}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu_{subleading}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu_{subleading}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu_{subleading}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu_{subleading}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu_{subleading}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu_{subleading}", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonM_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu^{-}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonP_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu^{+}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonF_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu_{near}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonN_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu_{far}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonL_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu_{leading}", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "MuonS_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu_{subleading}", true, false, c1);

	// ____________________________________________
	// Photon variables
	// ___________________________________________

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_hasPixelSeed", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon hasPixelSeed", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isAlsoElectron", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isAlsoElectron", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_Nclusters", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon Nclusters", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_nBasicClusters", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon nBasicClusters", true, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_nXtals", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon nXtals", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isTightPhoton", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isTightPhoton", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isLoosePhoton", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isLoosePhoton", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_E2x2", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E2x2", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_E3x3", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E3x3", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_E5x5", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E5x5", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_Emax", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon Emax", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_E2nd", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon E2nd", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_r19", "(100, 0, 2)", set_of_cuts[i], name[i], "Photon r19", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_r9", "(100, 0, 2)", set_of_cuts[i], name[i], "r9", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_cross", "(50, 0, 1.1)", set_of_cuts[i], name[i], "Photon cross", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_caloConeSize", "(30, 0, 0.5)", set_of_cuts[i], name[i], "Photon caloConeSize", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_PreshEnergy", "(40, 0, 10)", set_of_cuts[i], name[i], "Photon Preshower Energy", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_HoE", "(30, 0, 0.55)", set_of_cuts[i], name[i], "Photon HoE", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_covIetaIeta", "(30, 0, 0.02)", set_of_cuts[i], name[i], "Photon covIetaIeta", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_covIphiIphi", "(30, 0, 0.025)", set_of_cuts[i], name[i], "Photon covIphiIphi", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_convNTracks", "(5, -1, 4)", set_of_cuts[i], name[i], "Photon convNTracks", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_etaWidth", "(20, 0, 0.2)", set_of_cuts[i], name[i], "Photon Eta Width", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_phiWidth", "(20, 0, 0.2)", set_of_cuts[i], name[i], "Photon Phi Width", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isoEcalRecHit", "(70, -2, 20)", set_of_cuts[i], name[i], "Photon isoEcalRecHit", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isoHcalRecHit", "(100, -1, 10)", set_of_cuts[i], name[i], "Photon isoHcalRecHit", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isoSolidTrkCone", "(100, -1, 20)", set_of_cuts[i], name[i], "Photon isoSolidTrkCone", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isoHolsubleadingTrkCone", "(100, -1, 20)", set_of_cuts[i], name[i], "Photon isoHolsubleadingTrkCone", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isoNTracksSolidCone", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon isoNTracksSolidCone", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_isoNTracksHolsubleadingCone", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon isoNTracksHolsubleadingCone", true, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_seedTime", "(50,-50,50)", set_of_cuts[i], name[i], "Photon seed Time", true, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_miniTree, MC_miniTree, "Photon_seedFlag", "(50,0,50)", set_of_cuts[i], name[i], "Photon seed Flag", true, false, c1);

	// ____________________________________________
	// mugamma / mumu / mumugamma information
	// ____________________________________________

*/
//	} // end of loop over set of cuts



	return 0;	
}

