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

void DrawDataMCplot_NormEntries_Fast(TTree *Data_eventTree, TTree *MC_eventTree, string var, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFlow, TCanvas *c1){

	// Get Histo_Data from eventTree
	TH1F *Histo_Data_temp = new TH1F();
	string variable_Data = var + ">>Histo_Data_temp" + limits;
	Data_eventTree->Draw(variable_Data.c_str(), cut.c_str());
	TH1F *Histo_Data = (TH1F*)gDirectory->Get("Histo_Data_temp"); 
	c1->Clear();

	// Get Histo_MC from eventTree
	TH1F *Histo_MC_temp = new TH1F();
	string variable_MC = var + ">>Histo_MC_temp" + limits;
	MC_eventTree->Draw(variable_MC.c_str(), cut.c_str());
	TH1F *Histo_MC = (TH1F*)gDirectory->Get("Histo_MC_temp");
	c1->Clear();

	// TODO: implement drawUnderOverFlow

	// Get the number of entries for further normalization
	double a = Histo_Data->GetEntries();
	double b = Histo_MC->GetEntries();

	// Normalize
	Histo_Data->Sumw2(); // In order to have the correct error bars on data after renormalization
	// // Normalize MC and Data to 1
	//Histo_Data->Scale((double)((double)1.0/(double)a));
	//Histo_MC->Scale((double)((double)1.0/(double)b));
	// // Normalize MC to Data number of entries
	Histo_MC->Scale((double)((double)a/(double)b));

	// Get the maxs and the mins to further correct the Y-axis
	double dataMax = Histo_Data->GetMaximumStored();
	double dataMin = Histo_Data->GetMinimumStored();
	double mcMax = Histo_MC->GetMaximumStored();
	double mcMin = Histo_MC->GetMinimumStored();
	double YMax = max(dataMax, mcMax);
	double YMin = max(dataMin, mcMin);	

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
	Histo_Data->SetMaximum(YMax);
	Histo_Data->SetMinimum(YMin);
	Histo_Data->Draw("E1");

	// // Second: draw MC on the same canvas
	Histo_MC->SetLineColor(kBlack);
	Histo_MC->SetFillColor(kYellow);
	Histo_MC->Draw("same");

	// // Third: re-draw Data so that data appears in front of MC
	Histo_Data->Draw("E1same");

	// // Fourth: redraw axis so that axis appears in front of everything
	gPad->RedrawAxis();

	// // Fifth: draw legend
	TLegend *legend = new TLegend(0.7, 0.83, 0.99, 0.994, "");
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
//	cout<<"\tDEBUG:\tEntering main()"<<endl;
	//gStyle->SetOptStat(0);
	gROOT->ProcessLine(".x setTDRStyle.C");
	string Data = "miniTree_eventTree_DATA.root"; 
	string MC = "miniTree_eventTree_DATA.root"; 
	
	TFile *Data_File = new TFile(Data.c_str());
	TFile *MC_File = new TFile(MC.c_str());
	TTree* Data_eventTree = (TTree*) Data_File->Get("miniTree");
	TTree* MC_eventTree = (TTree*) MC_File->Get("miniTree");

	TCanvas *c1 = new TCanvas("Default", "Default");

	vector<string> set_of_cuts;
	vector<string> name;
	set_of_cuts.push_back("isAfterCut2c");
	name.push_back("isAfterCut2c");

	for(int i=0; i<set_of_cuts.size() ; i++){ // loop over different set of cuts
	// ____________________________________________
	// Muon variables
	// ____________________________________________
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "NbMuons", "(10,0,10)", set_of_cuts[i], name[i], "# of muons", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_Pt", "(50,0,100)", set_of_cuts[i], name[i], "p_{T} #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_Eta", "(10,-2.5,2.5)", set_of_cuts[i], name[i], "#eta #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_Eta", "(10,-2.5,2.5)", set_of_cuts[i], name[i], "#eta #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_Eta", "(10,-2.5,2.5)", set_of_cuts[i], name[i], "#eta #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_Eta", "(10,-2.5,2.5)", set_of_cuts[i], name[i], "#eta #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_Eta", "(10,-2.5,2.5)", set_of_cuts[i], name[i], "#eta #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_Eta", "(10,-2.5,2.5)", set_of_cuts[i], name[i], "#eta #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_Charge", "(2,-1,1)", set_of_cuts[i], name[i], "charge #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_Charge", "(2,-1,1)", set_of_cuts[i], name[i], "charge #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_Charge", "(2,-1,1)", set_of_cuts[i], name[i], "charge #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_Charge", "(2,-1,1)", set_of_cuts[i], name[i], "charge #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_isoR03_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .3} #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_isoR03_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .3} #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_isoR03_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .3} #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_isoR03_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .3} #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_isoR03_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .3} #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_isoR03_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .3} #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_isoR05_emEt", "(20,-2,5)", set_of_cuts[i], name[i], "emEt iso_{#Delta R = .5} #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_isoR05_hadEt", "(20,-2,5)", set_of_cuts[i], name[i], "hadEt iso_{#Delta R = .5} #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_isoR05_hoEt", "(20,-2,5)", set_of_cuts[i], name[i], "hoEt iso_{#Delta R = .5} #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_isoR05_nJets", "(6,-1,5)", set_of_cuts[i], name[i], "nJets iso_{#Delta R = .5} #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_isoR05_nTracks", "(30,0,30)", set_of_cuts[i], name[i], "nTracks iso_{#Delta R = .5} #mu_{low}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonM_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu^{-}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonP_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu^{+}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonF_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu_{near}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonN_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu_{far}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonH_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu_{high}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "MuonL_isoR05_sumPt", "(20,-1,20)", set_of_cuts[i], name[i], "sumPt iso_{#Delta R = .5} #mu_{low}", false, false, c1);

	// ____________________________________________
	// Photon variables
	// ___________________________________________

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "NbPhotons", "(10,0,10)", set_of_cuts[i], name[i], "# of photons", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Eta", "(10,-2.5,2.5)", set_of_cuts[i], name[i], "#eta of photon", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Phi", "(10,-3.15,3.15)", set_of_cuts[i], name[i], "#phi of photon", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isEB", "(2,0,1)", set_of_cuts[i], name[i], "photon is in barrel", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isEE", "(2,0,1)", set_of_cuts[i], name[i], "photon is in endcap", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isEEP", "(2,0,1)", set_of_cuts[i], name[i], "photon is in endcap plus", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isEEM", "(2,0,1)", set_of_cuts[i], name[i], "photon is in endcap minus", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Multiplicity", "(15,0,15)", set_of_cuts[i], name[i], "Photon Multiplicity", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_hasPixelSeed", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon hasPixelSeed", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isAlsoElectron", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isAlsoElectron", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Nclusters", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon Nclusters", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_nBasicClusters", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon nBasicClusters", false, false, c1);
//		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_nXtals", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon nXtals", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isTightPhoton", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isTightPhoton", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isLoosePhoton", "(3, 0, 3)", set_of_cuts[i], name[i], "Photon isLoosePhoton", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_E", "(100, 0, 800)", set_of_cuts[i], name[i], "Photon Energy", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Et", "(100, 0, 800)", set_of_cuts[i], name[i], "Photon Et", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_E2x2", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E2x2", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_E3x3", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E3x3", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_E5x5", "(50, 0, 800)", set_of_cuts[i], name[i], "Photon E5x5", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_Emax", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon Emax", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_E2nd", "(100, 0, 100)", set_of_cuts[i], name[i], "Photon E2nd", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_r19", "(100, 0, 2)", set_of_cuts[i], name[i], "Photon r19", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_r9", "(100, 0, 2)", set_of_cuts[i], name[i], "r9", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_cross", "(50, 0, 1.1)", set_of_cuts[i], name[i], "Photon cross", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_caloConeSize", "(30, 0, 0.5)", set_of_cuts[i], name[i], "Photon caloConeSize", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_PreshEnergy", "(40, 0, 10)", set_of_cuts[i], name[i], "Photon Preshower Energy", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_HoE", "(30, 0, 0.55)", set_of_cuts[i], name[i], "Photon HoE", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_covIetaIeta", "(30, 0, 0.02)", set_of_cuts[i], name[i], "Photon covIetaIeta", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_covIphiIphi", "(30, 0, 0.025)", set_of_cuts[i], name[i], "Photon covIphiIphi", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_convNTracks", "(5, -1, 4)", set_of_cuts[i], name[i], "Photon convNTracks", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_etaWidth", "(20, 0, 0.2)", set_of_cuts[i], name[i], "Photon Eta Width", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_phiWidth", "(20, 0, 0.2)", set_of_cuts[i], name[i], "Photon Phi Width", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoEcalRecHit", "(70, -2, 20)", set_of_cuts[i], name[i], "Photon isoEcalRecHit", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoHcalRecHit", "(100, -1, 10)", set_of_cuts[i], name[i], "Photon isoHcalRecHit", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoSolidTrkCone", "(100, -1, 20)", set_of_cuts[i], name[i], "Photon isoSolidTrkCone", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoHollowTrkCone", "(100, -1, 20)", set_of_cuts[i], name[i], "Photon isoHollowTrkCone", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoNTracksSolidCone", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon isoNTracksSolidCone", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_isoNTracksHollowCone", "(20, 0, 20)", set_of_cuts[i], name[i], "Photon isoNTracksHollowCone", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_seedTime", "(50,-50,50)", set_of_cuts[i], name[i], "Photon seed Time", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Photon_seedFlag", "(50,0,50)", set_of_cuts[i], name[i], "Photon seed Flag", false, false, c1);

	// ____________________________________________
	// mugamma / mumu / mumugamma information
	// ____________________________________________

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Mmumu", "(100,0,2500)", set_of_cuts[i], name[i], "M_{#mu#mu}", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "Mmumugamma", "(100,0,2500)", set_of_cuts[i], name[i], "M_{#mu#mu#gamma}", false, false, c1);

		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "deltaRNear", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{near})", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "deltaRFar", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{far})", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "deltaRPlus", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{plus})", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "deltaRMinus", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{minus})", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "deltaRHigh", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{high})", false, false, c1);
		DrawDataMCplot_NormEntries_Fast(Data_eventTree, MC_eventTree, "deltaRLow", "(100,0,10)", set_of_cuts[i], name[i], "#Delta R(#gamma, #mu_{low})", false, false, c1);

	} // end of loop over set of cuts



	return 0;	
}

