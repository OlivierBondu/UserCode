// ROOT headers
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"

// RooFit headers
#include "RooAbsPdf.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooHistPdf.h"
#include "RooMsgService.h"
#include "RooNLLVar.h"
#include "RooPlot.h"
#include "RooRandom.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "RooFFTConvPdf.h"
#include "CMSStyle.C"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <TLatex.h>

//gROOT->Reset();

/*
double weight_DYToMuMu(int nGenVertices)
{
	double weight[51] = {
0, 0.192859, 0.37571, 0.98006, 1.47381, 2.13772, 1.97435, 1.75482, 1.61272, 1.30487, 0.858989, 0.593953, 0.406, 0.271559, 0.200834, 0.123192, 0.101752, 0.0724765, 0.0505275, 0.0609286, 0.0265446, 0.0178984, 0.0603881, 0, 0.00990419, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
	return weight[nGenVertices];
}
*/

void Scale_Data(){
//	gStyle->SetOptTitle(0);
	gROOT->ProcessLine(".x setTDRStyle.C");
	CMSstyle();
	using namespace RooFit;

	TFile* file_Data = new TFile("../../miniTree_v7_Run2011A_ALL.root");
	TFile* file_MC = new TFile("../../miniTree_v7_DYToMuMu_M-20_TuneZ2_7TeV-pythia6_v3.root");
	TTree* Tree_Data = (TTree*) file_Data->Get("miniTree");
	TTree* Tree_MC = (TTree*) file_MC->Get("miniTree");

	RooRealVar Photon_isEB("Photon_isEB", "Photon_isEB", 0, 1);
 
	RooRealVar Mmumu("Mmumu", "Mmumu", 40, 80, "GeV");
	RooRealVar Mmumugamma("Mmumugamma", "m_{#mu#mu#gamma}", 60, 120, "GeV");

	RooRealVar mmg_k("mmg_k", "k", 0.0, 2.0, ""); 
	RooRealVar mmg_ik("mmg_ik", "mmg_ik", -500, 500, "");
	RooRealVar mmg_s("mmg_s", "s = E_{reco} / E_{kin.} - 1", -1.0, 1.0, "");
	RooRealVar mmg_logk("mmg_logk", "mmg_logk", -500, 500, ""); 
	RooRealVar mmg_logik("mmg_logik", "mmg_logik", -500, 500, "");
	RooRealVar mmg_logs("mmg_logs", "mmg_logs", -500, 500, "");
	RooRealVar Photon_r9("Photon_r9", "Photon_r9", -2.0, 2.0);
	RooRealVar isVeryLooseMMG("isVeryLooseMMG", "isVeryLooseMMG", -2.0, 2.0);
	RooRealVar isLooseMMG("isLooseMMG", "isLooseMMG", -2.0, 2.0);
	RooRealVar isTightMMG("isTightMMG", "isTightMMG", -2.0, 2.0);
	RooRealVar isAfterFSRCut1("isAfterFSRCut1", "isAfterFSRCut1", -2.0, 2.0);
	RooRealVar isAfterFSRCut2("isAfterFSRCut2", "isAfterFSRCut2", -2.0, 2.0);
	RooRealVar isAfterFSRCut3("isAfterFSRCut3", "isAfterFSRCut3", -2.0, 2.0);
	RooRealVar isAfterFSRCut4("isAfterFSRCut4", "isAfterFSRCut4", -2.0, 2.0);
	RooRealVar isMultipleCandidate("isMultipleCandidate", "isMultipleCandidate", -2.0, 2.0);
	RooRealVar nGenVerticess("nGenVertices", "nGenVertices", -0.5, 50.5);
  RooRealVar weight_pileUp("weight_pileUp", "weight_pileUp", 0.0, 10000000);
  RooRealVar weight_Xsection("weight_Xsection", "weight_Xsection", 0.0, 10000000);

	

	RooArgSet *ntplVars = new RooArgSet(Photon_isEB, Mmumu, Mmumugamma, mmg_k, mmg_ik, mmg_s, mmg_logk, mmg_logik, mmg_logs);
ntplVars->add(Photon_r9);
ntplVars->add(isVeryLooseMMG);
ntplVars->add(isLooseMMG);
ntplVars->add(isTightMMG);
ntplVars->add(isAfterFSRCut1);
ntplVars->add(isAfterFSRCut2);
ntplVars->add(isAfterFSRCut3);
ntplVars->add(isAfterFSRCut4);
ntplVars->add(isMultipleCandidate);
ntplVars->add(nGenVerticess);
ntplVars->add(weight_pileUp);
ntplVars->add(weight_Xsection);

//	RooArgSet ntplVars(Mmumu, Mmumugamma, Mmumugamma_5x5, Mmumugamma_SC, Mmumugamma_SCraw, mmg_k, mmg_ik, mmg_s, mmg_logk, mmg_logik, mmg_logs, mmg_k_5x5, mmg_ik_5x5, mmg_s_5x5, mmg_logk_5x5, mmg_logik_5x5, mmg_logs_5x5, mmg_k_SC, mmg_ik_SC, mmg_s_SC, mmg_logk_SC, mmg_logik_SC, mmg_logs_SC, mmg_k_SCraw, mmg_ik_SCraw, mmg_s_SCraw, mmg_logk_SCraw, mmg_logik_SCraw, mmg_logs_SCraw);
//	RooMCSet *MC = new RooMCSet("MC", "MC", Tree_MC, *ntplVars);

	vector<string> set_of_cuts;
  vector<string> name;
	vector<string> display;
	vector<string> display_latex;
	vector<double> mc_alpha;
	vector<double> mc_alpha_err;
	vector<double> mc_m0;
	vector<double> mc_m0_err;
	vector<double> mc_n;
	vector<double> mc_n_err;
	vector<double> mc_sigma;
	vector<double> mc_sigma_err;

	vector<double> data_alpha;
	vector<double> data_alpha_err;
	vector<double> data_m0;
	vector<double> data_m0_err;
	vector<double> data_n;
	vector<double> data_n_err;
	vector<double> data_sigma;
	vector<double> data_sigma_err;

/*
  set_of_cuts.push_back("Photon_isEB == 1");
  display.push_back("EB, loose m_{#mu#mu#gamma}");
	name.push_back("EB_loose");


  set_of_cuts.push_back("Photon_isEB == 0");
  display.push_back("EE, loose m_{#mu#mu#gamma}");
	name.push_back("EE_loose");
*/
/*
	set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0");
  display.push_back("EB, tight m_{#mu#mu#gamma}");
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight");

  set_of_cuts.push_back("Photon_isEB == 0 && isTightMMG && isMultipleCandidate == 0");
  display.push_back("EE, tight m_{#mu#mu#gamma}");
//  display.push_back("ECAL Endcaps");
	name.push_back("EE_tight");
*/

	set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.94");
  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 > .94");
  display_latex.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 > .94$");
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight-highR9");

	set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 < 0.94");
  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 < .94");
  display_latex.push_back("EB, tight $m_{\\mu\\mu\\gamma}$, $r9 < .94$");
//  display.push_back("ECAL Barrel");
	name.push_back("EB_tight-lowR9");

  set_of_cuts.push_back("Photon_isEB == 0 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 > 0.95");
  display.push_back("EE, tight m_{#mu#mu#gamma}, r9 > .95");
  display_latex.push_back("EE, tight $m_{\\mu\\mu\\gamma}$, $r9 > .95$");
//  display.push_back("ECAL Endcaps");
	name.push_back("EE_tight-highR9");

  set_of_cuts.push_back("Photon_isEB == 0 && isTightMMG && isMultipleCandidate == 0 && Photon_r9 < 0.95");
  display.push_back("EE, tight m_{#mu#mu#gamma}, r9 < .95");
  display_latex.push_back("EE, tight $m_{\\mu\\mu\\gamma}$, $r9 < .95$");
//  display.push_back("ECAL Endcaps");
	name.push_back("EE_tight-lowR9");


//return;

for(int idata=0; idata < 2; idata++){
	RooDataSet *Data = new RooDataSet();
	bool isData;
	if(idata ==0)
	{
		Data = new RooDataSet("Data", "Data", Tree_Data, *ntplVars);
		isData = true;
	} else {
		Data = new RooDataSet("MC", "MC", Tree_MC, *ntplVars, "", "weight_pileUp");
		isData = false;
	}

const int size = set_of_cuts.size();
	RooDataSet* Data_subset[size];


for(int i=0; i<set_of_cuts.size() ; i++){

  Data_subset[i] = (RooDataSet*)Data->reduce(set_of_cuts[i].c_str());

/*	
// ***************************************************************
// ***** Mmumugamma fit
// ***************************************************************


	// BREIT-WIGNER
	RooRealVar mmg_BW_mean("mmg_BW_mean", "BW m_{0}",  91.188, 85.0, 95.0,"GeV");
	RooRealVar mmg_BW_width("mmg_BW_width", "BW #Gamma", 2.45, 2.0,3.0,"GeV");
	mmg_BW_mean.setConstant();
	mmg_BW_width.setConstant();
	RooBreitWigner mmg_BW("mmg_BW", "mmg_BW", Mmumugamma, mmg_BW_mean, mmg_BW_width);


	// CRYSTALBALL
  RooRealVar mmg_CB_m0("mmg_CB_m0", "CB #Delta m_{0}", 0.0, -10.0, 10.0, "GeV");  
  RooRealVar mmg_CB_sigma("mmg_CB_sigma", "CB #sigma", 1.45, 0.01, 5.0, "GeV");
  RooRealVar mmg_CB_alpha("mmg_CB_alpha", "CB #alpha", 0.98, 0.01, 10.0);
  RooRealVar mmg_CB_n("mmg_CB_n", "CB n", 3.8, 0.5, 50.0);
  RooCBShape mmg_CrystalBall("mmg_CrystalBall","mmg_CrystalBall", Mmumugamma, mmg_CB_m0, mmg_CB_sigma, mmg_CB_alpha, mmg_CB_n);

	// CONVOLUTION
	RooFFTConvPdf mmg_BWxCB("mmg_BWxCB", "mmg_BWxCB", Mmumugamma, mmg_BW, mmg_CrystalBall);

	mmg_BWxCB.fitTo(*Data_subset[i]);
	RooArgSet* mmg_BWxCB_param = mmg_BWxCB.getVariables();
	mmg_BWxCB_param->Print("v");

	TCanvas* mmg_BWxCB_canvas = new TCanvas("mmg_BWxCB_canvas", "mmg_BWxCB_canvas");
	RooPlot* mmg_BWxCB_frame = Mmumugamma.frame(Title("m_{#mu#mu#gamma} fitted with Z^{0} Breit-Wigner convoluted with  a Crystal Ball"));
//	RooPlot* mmg_BWxCB_frame = Mmumugamma.frame(Title(" "));
	Data_subset[i]->plotOn(mmg_BWxCB_frame, Name("data"));
	mmg_BWxCB.plotOn(mmg_BWxCB_frame, Name("model"));
//	mmg_BWxCB.paramOn(mmg_BWxCB_frame, Format("NEU", AutoPrecision(2)), Parameters(RooArgSet(mmg_BW_mean, mmg_BW_width, mmg_CB_m0, mmg_CB_sigma, mmg_CB_alpha, mmg_CB_n)), ShowConstants(kTRUE));
	mmg_BWxCB_frame->Draw();


	Double_t mmg_BWxCB_chi2_ndf = mmg_BWxCB_frame->chiSquare("model", "data", 4);
	cout << "mmg_BWxCB_chi2_ndf= " << mmg_BWxCB_chi2_ndf << endl;

	TLatex latexLabel;
	latexLabel.SetTextSize(0.06);
	latexLabel.SetNDC();
	latexLabel.DrawLatex(0.20, 0.88, "CMS Preliminary 2011");
	latexLabel.DrawLatex(0.20, 0.82, "#sqrt{s} = 7 TeV");
	latexLabel.DrawLatex(0.70, 0.88, isData ? "DATA" : "MC");
	latexLabel.DrawLatex(0.70, 0.82, display[i].c_str());
	latexLabel.SetTextSize(0.03);

	TIterator *it = (TIterator*) mmg_BWxCB_param->createIterator();	
//	cout << mmg_BWxCB_param->getRealValue("BW #Gamma") << endl;
//	mmg_BWxCB_param->printValue(cout);
//	it->Next()->Print();
//	mmg_BW_width.Print();
//	cout << "mmg_BW_width.GetName()= " << mmg_BW_width.GetName() << "\tmmg_BW_width.getVal()= " << mmg_BW_width.getVal() << endl;
	RooRealVar* obj = new RooRealVar();
	double position = 0.82;
	gStyle->SetOptTitle(0);
	position -= 0.04;
	latexLabel.DrawLatex(0.20, position, "Fit: BW #otimes CB");
	while(( (RooRealVar*)obj = it->Next()) != 0)
	{
		if( ! strcmp(((char*)obj->GetName()), "Mmumugamma") ) continue;
//		cout << "obj->getTitle()= " << obj->getTitle() << endl; // char*
//		cout << "obj->GetName()= " << obj->GetName() << endl; // char*
//		cout << "obj->getVal()= " << obj->getVal() << endl; // Double_t
//		cout << "obj->getError()= " << obj->getError() << endl; // Double_t
//		cout << "obj->getUnit()= " << obj->getUnit() << endl; // Text_t
//		cout << endl;
		position -= 0.04;
//		double plaf = (double)obj->getVal();
//		cout << "plaf= " << plaf << endl;
		std::ostringstream valueStream;
		if( (double)obj->getError() != 0.0 )
		{
			valueStream << setprecision (3) << fixed << (double)obj->getVal() << " +- " << (double)obj->getError();
		} else {
			 valueStream << setprecision (3) << fixed << (double)obj->getVal();
		}
		string valueString = valueStream.str();
		latexLabel.DrawLatex(0.20, position, Form("%s = %s %s", obj->GetTitle(), valueString.c_str(), (char*)obj->getUnit()));
//		latexLabel.DrawLatex(0.18, position, Form("%s = %d \pm %d (%s)", obj->GetTitle(), (double)obj->getVal(), (double)obj->getError(), (char*)obj->getUnit()));
	}
//	cout << "it->Next()->GetName()= " << it->Next()->GetName() << "\tit->Next()->getVal()= " << it->Next()->getVal() << endl;

	position -= 0.04;
	std::ostringstream valueStream;
	valueStream << setprecision (4) << fixed << (double)mmg_BWxCB_chi2_ndf;
	string valueString = valueStream.str();
	latexLabel.DrawLatex(0.20, position, Form("#chi^{2} / ndf = %s", valueString.c_str()));

//	Data_subset[i]->Clear();
	mmg_BWxCB_canvas->Print(Form("gif/mmg_BWxCB_%s.gif", name[i].c_str()));
	mmg_BWxCB_canvas->Print(Form("eps/mmg_BWxCB_%s.eps", name[i].c_str()));
	mmg_BWxCB_canvas->Print(Form("png/mmg_BWxCB_%s.png", name[i].c_str()));
	mmg_BWxCB_canvas->Print(Form("C/mmg_BWxCB_%s.C", name[i].c_str()));
	system(Form("convert eps/mmg_BWxCB_%s.eps pdf/mmg_BWxCB_%s.pdf", name[i].c_str(), name[i].c_str()));

*/
// ***************************************************************
// ***** k fit
// ***************************************************************
/*
  // CRYSTALBALL
  RooRealVar mmg_k_CB_m0("mmg_k_CB_m0", "CB #Delta m_{0}", 1.0, -5.0, 5.0, "GeV");  
  RooRealVar mmg_k_CB_sigma("mmg_k_CB_sigma", "CB #sigma", 0.45, 0.01, 0.5, "GeV");
  RooRealVar mmg_k_CB_alpha("mmg_k_CB_alpha", "CB #alpha", -1.0, -10.01, 10.0);
  RooRealVar mmg_k_CB_n("mmg_k_CB_n", "CB n", 2.0, 0.5, 500.0);
//  RooCBShape mmg_k_CrystalBall("mmg_k_CrystalBall","mmg_k_CrystalBall", mmg_k, mmg_k_CB_m0, mmg_k_CB_sigma, mmg_k_CB_alpha, mmg_k_CB_n);
  RooCBShape model("mmg_k_CrystalBall","mmg_k_CrystalBall", mmg_k, mmg_k_CB_m0, mmg_k_CB_sigma, mmg_k_CB_alpha, mmg_k_CB_n);

	// BREIT-WIGNER
	RooRealVar mmg_k_BW_mean("mmg_k_BW_mean", "BW m_{0}", 0.0 , -2.0, 2.0 ,"GeV");
	RooRealVar mmg_k_BW_width("mmg_k_BW_width", "BW #Gamma", 1.0, 0.0, 5.0,"GeV");
	RooBreitWigner mmg_k_BW("mmg_k_BW", "mmg_k_BW", mmg_k, mmg_k_BW_mean, mmg_k_BW_width);


  // CONVOLUTION
//  RooFFTConvPdf model("mmg_k_BWxCB", "mmg_k_BWxCB", mmg_k, mmg_k_BW, mmg_k_CrystalBall);


	model.fitTo(*Data_subset[i]);
  RooArgSet* mmg_k_BWxCB_param = model.getVariables();
  mmg_k_BWxCB_param->Print("v");

	TCanvas *mmg_k_BWxCB_canvas = new TCanvas("mmg_k_BWxCB_canvas", "mmg_k_BWxCB_canvas");
	RooPlot* mmg_k_frame = mmg_k.frame(Title("k"));
	Data_subset[i]->plotOn(mmg_k_frame, Name("data"));
	model.plotOn(mmg_k_frame, Name("model"));
	mmg_k_frame->Draw();

//	Double_t mmg_k_BWxCB_chi2_ndf = mmg_k_frame->chiSquare("model", "data", 6);
	Double_t mmg_k_BWxCB_chi2_ndf = mmg_k_frame->chiSquare("model", "data", 4);
	cout << "mmg_k_BWxCB_chi2_ndf= " << mmg_k_BWxCB_chi2_ndf << endl;	
	TLatex latexLabel;
	latexLabel.SetTextSize(0.06);
	latexLabel.SetNDC();
	latexLabel.DrawLatex(0.20, 0.88, "CMS Preliminary 2011");
	latexLabel.DrawLatex(0.20, 0.82, "#sqrt{s} = 7 TeV");
	latexLabel.DrawLatex(0.70, 0.88, isData ? "DATA" : "MC");
	latexLabel.DrawLatex(0.70, 0.82, display[i].c_str());
	latexLabel.SetTextSize(0.03);

	TIterator *it = (TIterator*) mmg_k_BWxCB_param->createIterator();	
//	cout << mmg_k_BWxCB_param->getRealValue("BW #Gamma") << endl;
//	mmg_k_BWxCB_param->printValue(cout);
//	it->Next()->Print();
//	mmg_BW_width.Print();
//	cout << "mmg_BW_width.GetName()= " << mmg_BW_width.GetName() << "\tmmg_BW_width.getVal()= " << mmg_BW_width.getVal() << endl;
	RooRealVar* obj = new RooRealVar();
	double position = 0.82;
	gStyle->SetOptTitle(0);
	position -= 0.04;
//	latexLabel.DrawLatex(0.20, position, "Fit: BW #otimes CB");
	latexLabel.DrawLatex(0.20, position, "Fit: Crystal-Ball");
	while(( (RooRealVar*)obj = it->Next()) != 0)
	{
		if( ! strcmp(((char*)obj->GetName()), "mmg_k") ) continue;
//		cout << "obj->getTitle()= " << obj->getTitle() << endl; // char*
//		cout << "obj->GetName()= " << obj->GetName() << endl; // char*
//		cout << "obj->getVal()= " << obj->getVal() << endl; // Double_t
//		cout << "obj->getError()= " << obj->getError() << endl; // Double_t
//		cout << "obj->getUnit()= " << obj->getUnit() << endl; // Text_t
//		cout << endl;
		position -= 0.04;
//		double plaf = (double)obj->getVal();
//		cout << "plaf= " << plaf << endl;
		std::ostringstream valueStream;
		if( (double)obj->getError() != 0.0 )
		{
			valueStream << setprecision (3) << fixed << (double)obj->getVal() << " +- " << (double)obj->getError();
		} else {
			 valueStream << setprecision (3) << fixed << (double)obj->getVal();
		}
		string valueString = valueStream.str();
		latexLabel.DrawLatex(0.20, position, Form("%s = %s %s", obj->GetTitle(), valueString.c_str(), (char*)obj->getUnit()));
//		latexLabel.DrawLatex(0.18, position, Form("%s = %d \pm %d (%s)", obj->GetTitle(), (double)obj->getVal(), (double)obj->getError(), (char*)obj->getUnit()));
	}
//	cout << "it->Next()->GetName()= " << it->Next()->GetName() << "\tit->Next()->getVal()= " << it->Next()->getVal() << endl;

	position -= 0.04;
	std::ostringstream valueStream;
	valueStream << setprecision (4) << fixed << (double)mmg_k_BWxCB_chi2_ndf;
	string valueString = valueStream.str();
	latexLabel.DrawLatex(0.20, position, Form("#chi^{2} / ndf = %s", valueString.c_str()));
*/
//	Data_subset[i]->Clear();
/*
	mmg_k_BWxCB_canvas->Print(Form("gif/mmg_k_BWxCB_%s.gif", name[i].c_str()));
	mmg_k_BWxCB_canvas->Print(Form("eps/mmg_k_BWxCB_%s.eps", name[i].c_str()));
	mmg_k_BWxCB_canvas->Print(Form("png/mmg_k_BWxCB_%s.png", name[i].c_str()));
	mmg_k_BWxCB_canvas->Print(Form("C/mmg_k_BWxCB_%s.C", name[i].c_str()));
	system(Form("convert eps/mmg_k_BWxCB_%s.eps pdf/mmg_k_BWxCB_%s.pdf", name[i].c_str(), name[i].c_str()));
*/
/*
	mmg_k_BWxCB_canvas->Print(Form("gif/mmg_k_CB_%s_%s.gif", isData?"DATA":"MC", name[i].c_str()));
	mmg_k_BWxCB_canvas->Print(Form("eps/mmg_k_CB_%s_%s.eps", isData?"DATA":"MC", name[i].c_str()));
	mmg_k_BWxCB_canvas->Print(Form("png/mmg_k_CB_%s_%s.png", isData?"DATA":"MC", name[i].c_str()));
	mmg_k_BWxCB_canvas->Print(Form("C/mmg_k_CB_%s_%s.C", isData?"DATA":"MC", name[i].c_str()));
	system(Form("convert eps/mmg_k_CB_%s_%s.eps pdf/mmg_k_CB_%s_%s.pdf", isData?"DATA":"MC", name[i].c_str(), isData?"DATA":"MC", name[i].c_str()));
*/

// ***************************************************************
// ***** s fit
// ***************************************************************
  // CRYSTALBALL
  RooRealVar mmg_s_CB_m0("mmg_s_CB_m0", "CB #Delta m_{0}", 1.0, -5.0, 5.0, "GeV");  
  RooRealVar mmg_s_CB_sigma("mmg_s_CB_sigma", "CB #sigma", 0.45, 0.0, 0.5, "GeV");
  RooRealVar mmg_s_CB_alpha("mmg_s_CB_alpha", "CB #alpha", 1.0, 0.0, 10.0);
  RooRealVar mmg_s_CB_n("mmg_s_CB_n", "CB n", 2.0, 0.5, 20.0);
//  RooCBShape mmg_s_CrystalBall("mmg_s_CrystalBall","mmg_s_CrystalBall", mmg_s, mmg_s_CB_m0, mmg_s_CB_sigma, mmg_s_CB_alpha, mmg_s_CB_n);
  RooCBShape model("mmg_s_CrystalBall","mmg_s_CrystalBall", mmg_s, mmg_s_CB_m0, mmg_s_CB_sigma, mmg_s_CB_alpha, mmg_s_CB_n);

	// BREIT-WIGNER
	RooRealVar mmg_s_BW_mean("mmg_s_BW_mean", "BW m_{0}", 0.0 , -2.0, 2.0 ,"GeV");
	RooRealVar mmg_s_BW_width("mmg_s_BW_width", "BW #Gamma", 1.0, 0.0, 5.0,"GeV");
	RooBreitWigner mmg_s_BW("mmg_s_BW", "mmg_s_BW", mmg_s, mmg_s_BW_mean, mmg_s_BW_width);


  // CONVOLUTION
//  RooFFTConvPdf model("mmg_s_BWxCB", "mmg_s_BWxCB", mmg_s, mmg_s_BW, mmg_s_CrystalBall);


//	model.fitTo(*Data_subset[i], Range(-0.2, 0.2));
	model.fitTo(*Data_subset[i]);
  RooArgSet* mmg_s_BWxCB_param = model.getVariables();
  mmg_s_BWxCB_param->Print("v");

	if(isData)
	{
		data_alpha.push_back(mmg_s_CB_alpha.getVal());
		data_alpha_err.push_back(mmg_s_CB_alpha.getError());
		data_m0.push_back(mmg_s_CB_m0.getVal());
		data_m0_err.push_back(mmg_s_CB_m0.getError());
		data_sigma.push_back(mmg_s_CB_sigma.getVal());
		data_sigma_err.push_back(mmg_s_CB_sigma.getError());
		data_n.push_back(mmg_s_CB_n.getVal());
		data_n_err.push_back(mmg_s_CB_n.getError());
	} else {
		mc_alpha.push_back(mmg_s_CB_alpha.getVal());
		mc_alpha_err.push_back(mmg_s_CB_alpha.getError());
		mc_m0.push_back(mmg_s_CB_m0.getVal());
		mc_m0_err.push_back(mmg_s_CB_m0.getError());
		mc_sigma.push_back(mmg_s_CB_sigma.getVal());
		mc_sigma_err.push_back(mmg_s_CB_sigma.getError());
		mc_n.push_back(mmg_s_CB_n.getVal());
		mc_n_err.push_back(mmg_s_CB_n.getError());
	}





	TCanvas *mmg_s_BWxCB_canvas = new TCanvas("mmg_s_BWxCB_canvas", "mmg_s_BWxCB_canvas");
	RooPlot* mmg_s_frame = mmg_s.frame(Title("k"));
	Data_subset[i]->plotOn(mmg_s_frame, Name("data"));
	model.plotOn(mmg_s_frame, Name("model"));
	mmg_s_frame->Draw();

//	Double_t mmg_s_BWxCB_chi2_ndf = mmg_s_frame->chiSquare("model", "data", 6);
	Double_t mmg_s_BWxCB_chi2_ndf = mmg_s_frame->chiSquare("model", "data", 4);
	cout << "mmg_s_BWxCB_chi2_ndf= " << mmg_s_BWxCB_chi2_ndf << endl;	
	TLatex latexLabel;
	latexLabel.SetNDC();
	latexLabel.SetTextSize(0.03);
	latexLabel.DrawLatex(0.13, 0.96, "CMS Preliminary 2011");
	latexLabel.DrawLatex(0.42, 0.96, "#sqrt{s} = 7 TeV");
	latexLabel.DrawLatex(0.57, 0.96, isData ? "DATA" : "Simulation");
	latexLabel.SetTextSize(0.05);
//	latexLabel.DrawLatex(0.20, 0.88, "CMS Preliminary 2011");
//	latexLabel.DrawLatex(0.20, 0.82, "#sqrt{s} = 7 TeV");
//	latexLabel.DrawLatex(0.65, 0.88, isData ? "DATA" : "Simulation");
	latexLabel.DrawLatex(0.65, 0.88, display[i].c_str());
	latexLabel.SetTextSize(0.03);

	TIterator *it = (TIterator*) mmg_s_BWxCB_param->createIterator();	
//	cout << mmg_s_BWxCB_param->getRealValue("BW #Gamma") << endl;
//	mmg_s_BWxCB_param->printValue(cout);
//	it->Next()->Print();
//	mmg_BW_width.Print();
//	cout << "mmg_BW_width.GetName()= " << mmg_BW_width.GetName() << "\tmmg_BW_width.getVal()= " << mmg_BW_width.getVal() << endl;
	RooRealVar* obj = new RooRealVar();
	double position = 0.92;
	gStyle->SetOptTitle(0);
	position -= 0.04;
//	latexLabel.DrawLatex(0.20, position, "Fit: BW #otimes CB");
	latexLabel.DrawLatex(0.20, position, "Fit: Crystal-Ball");
	while(( (RooRealVar*)obj = it->Next()) != 0)
	{
		if( ! strcmp(((char*)obj->GetName()), "mmg_s") ) continue;
//		cout << "obj->getTitle()= " << obj->getTitle() << endl; // char*
//		cout << "obj->GetName()= " << obj->GetName() << endl; // char*
//		cout << "obj->getVal()= " << obj->getVal() << endl; // Double_t
//		cout << "obj->getError()= " << obj->getError() << endl; // Double_t
//		cout << "obj->getUnit()= " << obj->getUnit() << endl; // Text_t
//		cout << endl;
		position -= 0.04;
//		double plaf = (double)obj->getVal();
//		cout << "plaf= " << plaf << endl;
		std::ostringstream valueStream;
		if( (double)obj->getError() != 0.0 )
		{
			valueStream << setprecision (3) << fixed << (double)obj->getVal() << " +- " << (double)obj->getError();
		} else {
			 valueStream << setprecision (3) << fixed << (double)obj->getVal();
		}
		string valueString = valueStream.str();
		latexLabel.DrawLatex(0.20, position, Form("%s = %s %s", obj->GetTitle(), valueString.c_str(), (char*)obj->getUnit()));
//		latexLabel.DrawLatex(0.18, position, Form("%s = %d \pm %d (%s)", obj->GetTitle(), (double)obj->getVal(), (double)obj->getError(), (char*)obj->getUnit()));
	}
//	cout << "it->Next()->GetName()= " << it->Next()->GetName() << "\tit->Next()->getVal()= " << it->Next()->getVal() << endl;

	position -= 0.04;
	std::ostringstream valueStream;
	valueStream << setprecision (4) << fixed << (double)mmg_s_BWxCB_chi2_ndf;
	string valueString = valueStream.str();
	latexLabel.DrawLatex(0.20, position, Form("#chi^{2} / ndf = %s", valueString.c_str()));

//	Data_subset[i]->Clear();
/*
	mmg_s_BWxCB_canvas->Print(Form("gif/mmg_s_BWxCB_%s.gif", name[i].c_str()));
	mmg_s_BWxCB_canvas->Print(Form("eps/mmg_s_BWxCB_%s.eps", name[i].c_str()));
	mmg_s_BWxCB_canvas->Print(Form("png/mmg_s_BWxCB_%s.png", name[i].c_str()));
	mmg_s_BWxCB_canvas->Print(Form("C/mmg_s_BWxCB_%s.C", name[i].c_str()));
	system(Form("convert eps/mmg_s_BWxCB_%s.eps pdf/mmg_s_BWxCB_%s.pdf", name[i].c_str(), name[i].c_str()));
*/
	mmg_s_BWxCB_canvas->Print(Form("gif/mmg_s_CB_%s_%s.gif", isData?"DATA":"MC", name[i].c_str()));
	mmg_s_BWxCB_canvas->Print(Form("eps/mmg_s_CB_%s_%s.eps", isData?"DATA":"MC", name[i].c_str()));
	mmg_s_BWxCB_canvas->Print(Form("png/mmg_s_CB_%s_%s.png", isData?"DATA":"MC", name[i].c_str()));
	mmg_s_BWxCB_canvas->Print(Form("C/mmg_s_CB_%s_%s.C", isData?"DATA":"MC", name[i].c_str()));
	system(Form("convert eps/mmg_s_CB_%s_%s.eps pdf/mmg_s_CB_%s_%s.pdf", isData?"DATA":"MC", name[i].c_str(), isData?"DATA":"MC", name[i].c_str()));

} // end of loop over categories
}// end of loop over data / mc

// TWIKI TABLES
cout << "|\t *DATA* \t|\t *m0* \t|\t *sigma* \t|\t *alpha* \t|\t *n* \t|" << endl; 

for(int i=0; i < data_alpha.size(); i++)
{
	cout << "|\t" << name[i] << "\t"
	<< "|\t" << data_m0[i] << " +- " << data_m0_err[i] << "\t"
	<< "|\t" << data_sigma[i] << " +- " << data_sigma_err[i] << "\t"
	<< "|\t" << data_alpha[i] << " +- " << data_alpha_err[i] << "\t"
	<< "|\t" << data_n[i] << " +- " << data_n_err[i] << "\t|" << endl;
}

cout << "|\t *MC* \t|\t *m0* \t|\t *sigma* \t|\t *alpha* \t|\t *n* \t|" << endl; 

for(int i=0; i < mc_alpha.size(); i++)
{
	cout << "|\t" << name[i] << "\t"
	<< "|\t" << mc_m0[i] << " +- " << mc_m0_err[i] << "\t"
	<< "|\t" << mc_sigma[i] << " +- " << mc_sigma_err[i] << "\t"
	<< "|\t" << mc_alpha[i] << " +- " << mc_alpha_err[i] << "\t"
	<< "|\t" << mc_n[i] << " +- " << mc_n_err[i] << "\t|" << endl;
}

cout << endl << endl;
for(int i=0; i < mc_alpha.size(); i++)
{
	cout << "|\t *" << name[i] << "* \t|\t *m0* \t|\t *sigma* \t|\t *alpha* \t|\t *n* \t|" << endl;
  cout << "|\t" << " data " << "\t"
  << "|\t" << data_m0[i] << " +- " << data_m0_err[i] << "\t"
  << "|\t" << data_sigma[i] << " +- " << data_sigma_err[i] << "\t"
  << "|\t" << data_alpha[i] << " +- " << data_alpha_err[i] << "\t"
  << "|\t" << data_n[i] << " +- " << data_n_err[i] << "\t|"
	<< endl;
  cout << "|\t" << " mc " << "\t"
  << "|\t" << mc_m0[i] << " +- " << mc_m0_err[i] << "\t"
  << "|\t" << mc_sigma[i] << " +- " << mc_sigma_err[i] << "\t"
  << "|\t" << mc_alpha[i] << " +- " << mc_alpha_err[i] << "\t"
  << "|\t" << mc_n[i] << " +- " << mc_n_err[i] << "\t|"
	<< endl;
	cout << "|\t" << " data - mc " << "\t"
	<< "|\t" << setprecision (8) << fixed << data_m0[i] - mc_m0[i] << " +- " << sqrt( data_m0_err[i]*data_m0_err[i] + mc_m0_err[i]*mc_m0_err[i]) << "\t"
	<< "|\t" << setprecision (8) << fixed << data_sigma[i] - mc_sigma[i] << " +- " << sqrt( data_sigma_err[i]*data_sigma_err[i] + mc_sigma_err[i]*mc_sigma_err[i]) << "\t"
	<< "| | |"
//	<< "|\t" << setprecision (8) << fixed << data_alpha[i] - mc_alpha[i] << " +- " << sqrt( data_alpha_err[i]*data_alpha_err[i] + mc_alpha_err[i]*mc_alpha_err[i]) << "\t"
//	<< "|\t" << setprecision (8) << fixed << data_n[i] - mc_n[i] << " +- " << sqrt( data_n_err[i]*data_n_err[i] + mc_n_err[i]*mc_n_err[i]) << "\t|"
	<< endl;
	cout << "|\t" << " data - mc (%)" << "\t"
	<< "|\t" << setprecision (5) << fixed << (data_m0[i] - mc_m0[i])*100.0 << " +- " << 100.0 * sqrt( data_m0_err[i]*data_m0_err[i] + mc_m0_err[i]*mc_m0_err[i]) << "\t"
	<< "|\t" << setprecision (5) << fixed << (data_sigma[i] - mc_sigma[i])*100.0 << " +- " << 100.0 * sqrt( data_sigma_err[i]*data_sigma_err[i] + mc_sigma_err[i]*mc_sigma_err[i]) << "\t"
	<< "| | |"
//	<< "|\t" << setprecision (5) << fixed << (data_alpha[i] - mc_alpha[i])*100.0 << " +- " << 100.0 * sqrt( data_alpha_err[i]*data_alpha_err[i] + mc_alpha_err[i]*mc_alpha_err[i]) << "\t"
//	<< "|\t" << setprecision (5) << fixed << (data_n[i] - mc_n[i])*100.0 << " +- " << 100.0 * sqrt( data_n_err[i]*data_n_err[i] + mc_n_err[i]*mc_n_err[i]) << "\t|"
	<< endl;
}
cout << endl << endl;
cout << endl << endl;

// LATEX TABLES
cout << "\\begin{tabular}{ccccc}" << endl;
cout << "DATA \t&\t $m_0$ \t&\t $\\sigma$ \t&\t $\\alpha$ \t&\t $n$ \t\\\\" << endl; 
cout << "\\hline" << endl;
for(int i=0; i < data_alpha.size(); i++)
{
	cout << "\t" << display_latex[i] << "\t"
	<< "&\t$" << data_m0[i] << " \\pm " << data_m0_err[i] << "$\t"
	<< "&\t$" << data_sigma[i] << " \\pm " << data_sigma_err[i] << "$\t"
	<< "&\t$" << data_alpha[i] << " \\pm " << data_alpha_err[i] << "$\t"
	<< "&\t$" << data_n[i] << " \\pm " << data_n_err[i] << "$\t\\\\" << endl;
}
cout << "\\end{tabular}" << endl;
cout << "\\begin{tabular}{ccccc}" << endl;
cout << "MC \t&\t $m_0$ \t&\t $\\sigma$ \t&\t $\\alpha$ \t&\t $n$ \t\\\\" << endl; 
cout << "\\hline" << endl;

for(int i=0; i < mc_alpha.size(); i++)
{
	cout << "\t" << display_latex[i] << "\t"
	<< "&\t$" << mc_m0[i] << " \\pm " << mc_m0_err[i] << "$\t"
	<< "&\t$" << mc_sigma[i] << " \\pm " << mc_sigma_err[i] << "$\t"
	<< "&\t$" << mc_alpha[i] << " \\pm " << mc_alpha_err[i] << "$\t"
	<< "&\t$" << mc_n[i] << " \\pm " << mc_n_err[i] << "$\t\\\\" << endl;
}
cout << "\\end{tabular}" << endl;

cout << endl << endl;
for(int i=0; i < mc_alpha.size(); i++)
{
	cout << "\\begin{tabular}{ccc}" << endl;
	cout << display_latex[i] << "\t&\t $m_0$ \t&\t $\\sigma$ \\\\" << endl;
	cout << "\\hline" << endl;
  cout << "data " << "\t"
  << "&\t$" << data_m0[i] << " \\pm " << data_m0_err[i] << "$\t"
  << "&\t$" << data_sigma[i] << " \\pm " << data_sigma_err[i] << "$\t\\\\"
//  << "&\t$" << data_alpha[i] << " \\pm " << data_alpha_err[i] << "$\t"
//  << "&\t$" << data_n[i] << " \\pm " << data_n_err[i] << "$\t\\\\"
	<< endl;
  cout << "mc " << "\t"
  << "&\t$" << mc_m0[i] << " \\pm " << mc_m0_err[i] << "$\t"
  << "&\t$" << mc_sigma[i] << " \\pm " << mc_sigma_err[i] << "$\t\\\\"
//  << "&\t$" << mc_alpha[i] << " \\pm " << mc_alpha_err[i] << "$\t"
//  << "&\t$" << mc_n[i] << " \\pm " << mc_n_err[i] << "$\t\\\\"
	<< endl;
	cout << " data - mc " << "\t"
	<< "&\t$" << setprecision (5) << fixed << data_m0[i] - mc_m0[i] << " \\pm " << sqrt( data_m0_err[i]*data_m0_err[i] + mc_m0_err[i]*mc_m0_err[i]) << "$\t"
	<< "&\t$" << setprecision (5) << fixed << data_sigma[i] - mc_sigma[i] << " \\pm " << sqrt( data_sigma_err[i]*data_sigma_err[i] + mc_sigma_err[i]*mc_sigma_err[i]) << "$\t"
	<< " \\\\"
//	<< "&\t" << setprecision (8) << fixed << data_alpha[i] - mc_alpha[i] << " \\pm " << sqrt( data_alpha_err[i]*data_alpha_err[i] + mc_alpha_err[i]*mc_alpha_err[i]) << "\t"
//	<< "&\t" << setprecision (8) << fixed << data_n[i] - mc_n[i] << " \\pm " << sqrt( data_n_err[i]*data_n_err[i] + mc_n_err[i]*mc_n_err[i]) << "\t&"
	<< endl;
	cout << " data - mc (\\%)" << "\t"
	<< "&\t$" << setprecision (4) << fixed << (data_m0[i] - mc_m0[i])*100.0 << " \\pm " << 100.0 * sqrt( data_m0_err[i]*data_m0_err[i] + mc_m0_err[i]*mc_m0_err[i]) << "$\t"
	<< "&\t$" << setprecision (4) << fixed << (data_sigma[i] - mc_sigma[i])*100.0 << " \\pm " << 100.0 * sqrt( data_sigma_err[i]*data_sigma_err[i] + mc_sigma_err[i]*mc_sigma_err[i]) << "$\t"
	<< " \\\\"
//	<< "&\t" << setprecision (5) << fixed << (data_alpha[i] - mc_alpha[i])*100.0 << " \\pm " << 100.0 * sqrt( data_alpha_err[i]*data_alpha_err[i] + mc_alpha_err[i]*mc_alpha_err[i]) << "\t"
//	<< "&\t" << setprecision (5) << fixed << (data_n[i] - mc_n[i])*100.0 << " \\pm " << 100.0 * sqrt( data_n_err[i]*data_n_err[i] + mc_n_err[i]*mc_n_err[i]) << "\t&"
	<< endl;
	cout << "\\end{tabular}" << endl;
}


return;
}
