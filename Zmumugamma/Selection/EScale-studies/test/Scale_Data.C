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

// RooStats headers
//#include "RooStats/HLFactory.h"

void Scale_Data(){
//	gStyle->SetOptTitle(0);
	CMSstyle();
	using namespace RooFit;

//	TFile* file_Data = new TFile("../../miniTree_Run2010_ALL_v2.root");
	TFile* file_Data = new TFile("../../miniTree_FSR_DYToMuMu_v2.root");
	TTree* Tree_Data = (TTree*) file_Data->Get("miniTree");

	RooRealVar Photon_isEB("Photon_isEB", "Photon_isEB", 0, 1);
 
	RooRealVar Mmumu("Mmumu", "Mmumu", 40, 80, "GeV");
	RooRealVar Mmumugamma("Mmumugamma", "m_{#mu#mu#gamma}", 60, 120, "GeV");
/*
	RooRealVar Mmumugamma_5x5("Mmumugamma_5x5", "Mmumugamma_5x5", 60, 120, "GeV");
	RooRealVar Mmumugamma_SC("Mmumugamma_SC", "Mmumugamma_SC", 60, 120, "GeV");
	RooRealVar Mmumugamma_SCraw("Mmumugamma_SCraw", "Mmumugamma_SCraw", 60, 120, "GeV");
*/
	RooRealVar mmg_k("mmg_k", "mmg_k", -500, 500, ""); 
	RooRealVar mmg_ik("mmg_ik", "mmg_ik", -500, 500, "");
	RooRealVar mmg_s("mmg_s", "mmg_s", -500, 500, "");
	RooRealVar mmg_logk("mmg_logk", "mmg_logk", -500, 500, ""); 
	RooRealVar mmg_logik("mmg_logik", "mmg_logik", -500, 500, "");
	RooRealVar mmg_logs("mmg_logs", "mmg_logs", -500, 500, "");
/*
	RooRealVar mmg_k_5x5("mmg_k_5x5", "mmg_k_5x5", -500, 500, "");
	RooRealVar mmg_ik_5x5("mmg_ik_5x5", "mmg_ik_5x5", -500, 500, "");
	RooRealVar mmg_s_5x5("mmg_s_5x5", "mmg_s_5x5", -500, 500, "");
	RooRealVar mmg_logk_5x5("mmg_logk_5x5", "mmg_logk_5x5", -500, 500, "");
	RooRealVar mmg_logik_5x5("mmg_logik_5x5", "mmg_logik_5x5", -500, 500, "");
	RooRealVar mmg_logs_5x5("mmg_logs_5x5", "mmg_logs_5x5", -500, 500, "");
	RooRealVar mmg_k_SC("mmg_k_SC", "mmg_k_SC", -500, 500, "");
	RooRealVar mmg_ik_SC("mmg_ik_SC", "mmg_ik_SC", -500, 500, "");
	RooRealVar mmg_s_SC("mmg_s_SC", "mmg_s_SC", -500, 500, "");
	RooRealVar mmg_logk_SC("mmg_logk_SC", "mmg_logk_SC", -500, 500, "");
	RooRealVar mmg_logik_SC("mmg_logik_SC", "mmg_logik_SC", -500, 500, "");
	RooRealVar mmg_logs_SC("mmg_logs_SC", "mmg_logs_SC", -500, 500, "");
	RooRealVar mmg_k_SCraw("mmg_k_SCraw", "mmg_k_SCraw", -500, 500, "");
	RooRealVar mmg_ik_SCraw("mmg_ik_SCraw", "mmg_ik_SCraw", -500, 500, "");
	RooRealVar mmg_s_SCraw("mmg_s_SCraw", "mmg_s_SCraw", -500, 500, "");
	RooRealVar mmg_logk_SCraw("mmg_logk_SCraw", "mmg_logk_SCraw", -500, 500, "");
	RooRealVar mmg_logik_SCraw("mmg_logik_SCraw", "mmg_logik_SCraw", -500, 500, "");
	RooRealVar mmg_logs_SCraw("mmg_logs_SCraw", "mmg_logs_SCraw", -500, 500, "");
*/
	
	RooArgSet *ntplVars = new RooArgSet(Photon_isEB, Mmumu, Mmumugamma, mmg_k, mmg_ik, mmg_s, mmg_logk, mmg_logik, mmg_logs);
//	RooArgSet ntplVars(Mmumu, Mmumugamma, Mmumugamma_5x5, Mmumugamma_SC, Mmumugamma_SCraw, mmg_k, mmg_ik, mmg_s, mmg_logk, mmg_logik, mmg_logs, mmg_k_5x5, mmg_ik_5x5, mmg_s_5x5, mmg_logk_5x5, mmg_logik_5x5, mmg_logs_5x5, mmg_k_SC, mmg_ik_SC, mmg_s_SC, mmg_logk_SC, mmg_logik_SC, mmg_logs_SC, mmg_k_SCraw, mmg_ik_SCraw, mmg_s_SCraw, mmg_logk_SCraw, mmg_logik_SCraw, mmg_logs_SCraw);
	RooDataSet *Data = new RooDataSet("Data", "Data", Tree_Data, *ntplVars);

	vector<string> set_of_cuts;
  vector<string> name;
	vector<string> display;

  set_of_cuts.push_back("Photon_isEB == 1");
  display.push_back("EB, loose m_{#mu#mu#gamma}");
	name.push_back("EB_loose");
  set_of_cuts.push_back("Photon_isEB == 0");
  display.push_back("EE, loose m_{#mu#mu#gamma}");
	name.push_back("EE_loose");
	set_of_cuts.push_back("Photon_isEB == 1 && Mmumugamma > 87.2 && Mmumugamma < 95.2");
  display.push_back("EB, tight m_{#mu#mu#gamma}");
	name.push_back("EB_tight");
  set_of_cuts.push_back("Photon_isEB == 0 && Mmumugamma > 87.2 && Mmumugamma < 95.2");
  display.push_back("EE, tight m_{#mu#mu#gamma}");
	name.push_back("EE_tight");

	const int size = set_of_cuts.size();
	RooDataSet* Data_subset[size];
//return;

for(int i=0; i<set_of_cuts.size() ; i++){

  Data_subset[i] = (RooDataSet*)Data->reduce(set_of_cuts[i].c_str());
	
// ***************************************************************
// ***** Mmumugamma fit
// ***************************************************************

//	RooDataSet *Data_subset[i] = Data->reduce("Photon_isEB == 1");

	// BREIT-WIGNER
	RooRealVar mmg_BW_mean("mmg_BW_mean", "BW m_{0}",  91.188, 85.0, 95.0,"GeV");
	RooRealVar mmg_BW_width("mmg_BW_width", "BW #Gamma", 2.45, 2.0,3.0,"GeV");
	mmg_BW_mean.setConstant();
	mmg_BW_width.setConstant();
	RooBreitWigner mmg_BW("mmg_BW", "mmg_BW", Mmumugamma, mmg_BW_mean, mmg_BW_width);


	// CRYSTALBALL
  RooRealVar mmg_CB_m0("mmg_CB_m0", "CB #Delta m_{0}", 0.0, -10.0, 10.0, "GeV");  
  RooRealVar mmg_CB_sigma("mmg_CB_sigma", "CB #sigma", 1.45, 0.0, 5.0, "GeV");
  RooRealVar mmg_CB_alpha("mmg_CB_alpha", "CB #alpha", 0.98, 0.0, 10.0);
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
//	cout << "mmg_BWxCB_chi2_ndf= " << mmg_BWxCB_chi2_ndf << endl;

	TLatex latexLabel;
	latexLabel.SetTextSize(0.06);
	latexLabel.SetNDC();
	latexLabel.DrawLatex(0.20, 0.88, "CMS Preliminary 2010");
	latexLabel.DrawLatex(0.20, 0.82, "#sqrt{s} = 7 TeV");
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


// ***************************************************************
// ***** k fit
// ***************************************************************


}

return;
}
