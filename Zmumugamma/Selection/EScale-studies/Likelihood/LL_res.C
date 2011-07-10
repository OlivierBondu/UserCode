#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooKeysPdf.h"
#include "RooFitResult.h"
#include "TStyle.h"
#include "TLatex.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooAddPdf.h"
#include "RooMinuit.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "RooFormulaVar.h"
#include "TFile.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "TROOT.h"
#include "CMSStyle.C"
#include "TSystem.h"

//gROOT->Reset();

// g++ LL.C -lRooFit -lRooFitCore `root-config --libs --cflags` -o plaf.exe

//#pragma optimize 0;
using namespace RooFit ;
int main()
{
	gROOT->ProcessLine(".x setTDRStyle.C");
	CMSstyle();

// Prepare output file
	ofstream* errfile = new ofstream("Likelihood.txt");
	TProfile *LL = new TProfile("LL", "LL", 201, 0.0, 10.05);
	TProfile *LL_s = new TProfile("LL_s", "LL_s", 201, 0.0, 10.05);
	TProfile *LL_mmg = new TProfile("LL_mmg", "LL_mmg", 201, 0.0, 10.05);

// Setup data observables
	RooRealVar mmgData("mmgData", "mmgData", 70, 110);
	RooRealVar kData("kData","kData",0,2);
  RooRealVar ikData("ikData","ikData",0,2);
  RooRealVar sData("sData","sData",-2,2);
  RooRealVar etaData("etaData", "etaData", -3, 3);

// Read data

//	TFile *file_Data = new TFile("/sps/cms/obondu/CMSSW_4_2_3_patch2/src/Zmumugamma/Selection/miniTree_v5_DYToMuMu_M-20_TuneZ2_7TeV-pythia6_v3.root");
	TFile *file_Data = new TFile("/sps/cms/obondu/CMSSW_4_2_3_patch2/src/Zmumugamma/Selection/miniTree_v7_Run2011A_ALL.root");
	TTree *tree_Data = (TTree*)file_Data->Get("miniTree");
  RooRealVar Mmumugamma("Mmumugamma", "m_{#mu#mu#gamma}", 0.0, 300.0, "GeV");
  RooRealVar Photon_isEB("Photon_isEB", "Photon_isEB", 0, 1);
//  RooRealVar mmg_k("mmg_k", "k", 0.0, 8.0, "");
  RooRealVar mmg_k("mmg_k", "k", -1.0, 3.0, "");
//  RooRealVar mmg_ik("mmg_ik", "ik", -5.0, 6.0, "");
  RooRealVar mmg_ik("mmg_ik", "ik", -1.0, 3.0, "");
//  RooRealVar mmg_s("mmg_s", "s = E_{reco} / E_{kin.} - 1", -5.0, 5.0, "");
  RooRealVar mmg_s("mmg_s", "s = E_{reco} / E_{kin.} - 1", -2.0, 2.0, "");
  RooRealVar Photon_r9("Photon_r9", "Photon_r9", -2.0, 2.0);
  RooRealVar isVeryLooseMMG("isVeryLooseMMG", "isVeryLooseMMG", -2.0, 2.0);
  RooRealVar isLooseMMG("isLooseMMG", "isLooseMMG", -2.0, 2.0);
  RooRealVar isTightMMG("isTightMMG", "isTightMMG", -2.0, 2.0);
  RooRealVar isAfterFSRCut1("isAfterFSRCut1", "isAfterFSRCut1", -2.0, 2.0);
  RooRealVar isAfterFSRCut2("isAfterFSRCut2", "isAfterFSRCut2", -2.0, 2.0);
  RooRealVar isAfterFSRCut3("isAfterFSRCut3", "isAfterFSRCut3", -2.0, 2.0);
  RooRealVar isAfterFSRCut4("isAfterFSRCut4", "isAfterFSRCut4", -2.0, 2.0);
  RooRealVar nGenVertices("nGenVertices", "nGenVertices", -0.5, 50.5);
	RooRealVar weight_pileUp("weight_pileUp", "weight_pileUp", 0.0, 10000000);
	RooRealVar weight_Xsection("weight_Xsection", "weight_Xsection", 0.0, 10000000);
	RooArgSet *ntplVars = new RooArgSet();
	ntplVars->add(Mmumugamma);
	ntplVars->add(Photon_isEB);
	ntplVars->add(mmg_k);
	ntplVars->add(mmg_ik);
	ntplVars->add(mmg_s);
	ntplVars->add(Photon_r9);
	ntplVars->add(isVeryLooseMMG);
	ntplVars->add(isLooseMMG);
	ntplVars->add(isTightMMG);
	ntplVars->add(isAfterFSRCut1);
	ntplVars->add(isAfterFSRCut2);
	ntplVars->add(isAfterFSRCut3);
	ntplVars->add(isAfterFSRCut4);
	ntplVars->add(nGenVertices);
	ntplVars->add(weight_pileUp);
  ntplVars->add(weight_Xsection);

	RooFormulaVar weight = RooFormulaVar("weight", "weight_pileUp * weight_Xsection", RooArgList(weight_pileUp, weight_Xsection));

	RooDataSet *data = new RooDataSet("Data", "Data", tree_Data, *ntplVars);

  vector<string> set_of_cuts;
  vector<string> name;
  vector<string> display;
/*
  set_of_cuts.push_back("Photon_isEB == 1 && isLooseMMG && Photon_r9 > 0.94");
  display.push_back("EB, loose m_{#mu#mu#gamma}, r9 > .94");
//  display.push_back("ECAL Barrel");
  name.push_back("EB_loose-highR9");

  set_of_cuts.push_back("Photon_isEB == 1 && isLooseMMG && Photon_r9 < 0.94");
  display.push_back("EB, loose m_{#mu#mu#gamma}, r9 < .94");
//  display.push_back("ECAL Barrel");
  name.push_back("EB_loose-lowR9");

  set_of_cuts.push_back("Photon_isEB == 0 && isLooseMMG && Photon_r9 > 0.95");
  display.push_back("EE, loose m_{#mu#mu#gamma}, r9 > .95");
//  display.push_back("ECAL Endcaps");
  name.push_back("EE_loose-highR9");

  set_of_cuts.push_back("Photon_isEB == 0 && isLooseMMG && Photon_r9 < 0.95");
  display.push_back("EE, loose m_{#mu#mu#gamma}, r9 < .95");
//  display.push_back("ECAL Endcaps");
  name.push_back("EE_loose-lowR9");
*/


  set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && Photon_r9 > 0.94");
  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 > .94");
//  display.push_back("ECAL Barrel");
  name.push_back("EB_tight-highR9");
/*
  set_of_cuts.push_back("Photon_isEB == 1 && isTightMMG && Photon_r9 < 0.94");
  display.push_back("EB, tight m_{#mu#mu#gamma}, r9 < .94");
//  display.push_back("ECAL Barrel");
  name.push_back("EB_tight-lowR9");
*//*
  set_of_cuts.push_back("Photon_isEB == 0 && isTightMMG && Photon_r9 > 0.95");
  display.push_back("EE, tight m_{#mu#mu#gamma}, r9 > .95");
//  display.push_back("ECAL Endcaps");
  name.push_back("EE_tight-highR9");
*//*
  set_of_cuts.push_back("Photon_isEB == 0 && isTightMMG && Photon_r9 < 0.95");
  display.push_back("EE, tight m_{#mu#mu#gamma}, r9 < .95");
//  display.push_back("ECAL Endcaps");
  name.push_back("EE_tight-lowR9");
*/

for(int i=0; i<set_of_cuts.size() ; i++){
	
	double maxLL_mmg, maxLL_k, maxLL_s;
	double minLL_mmg, minLL_k, minLL_s;
	maxLL_mmg = maxLL_k = maxLL_s = -99999999.9;
	minLL_mmg = minLL_k = minLL_s = 99999999.9;
	
	// Create data subsets

	 RooDataSet *EBdata = (RooDataSet*)data->reduce(set_of_cuts[i].c_str());
	  RooDataSet *mmgEBdata = (RooDataSet*)data->reduce(Mmumugamma, set_of_cuts[i].c_str());
		RooDataSet *kEBdata = (RooDataSet*)data->reduce(mmg_k, set_of_cuts[i].c_str());
		RooDataSet *ikEBdata = (RooDataSet*)data->reduce(mmg_ik, set_of_cuts[i].c_str());
		RooDataSet *sEBdata = (RooDataSet*)data->reduce(mmg_s, set_of_cuts[i].c_str());
	
	// Draw Data
	/*
	    TCanvas *cData = new TCanvas("Data", "Data");
	    RooPlot* kDataframe = kData.frame();
	    kEBdata->plotOn(kDataframe);
	    kDataframe->Draw();
	    cData->Draw();
	*/
		
		char x[50];
		double s_alpha;
		for(double alpha = 0.050 ; alpha <= 10.000 ; alpha += 0.050)
//		for(double alpha = 0.050 ; alpha <= 10.000 ; alpha += 1.0)
		{
			sprintf(x,"%4.3f",alpha);
			s_alpha = (alpha - 1) * 100;

	// Read mc file
	  TFile *file_MC = new TFile(Form("/sps/cms/obondu/temp/test_batch/miniTree_res_%s.root", x));
	  TTree *tree_MC = (TTree*)file_MC->Get("miniTree");
	
//		RooDataSet *mc = new RooDataSet("MC", "MC", tree_MC, *ntplVars);
//		RooDataSet *mc = new RooDataSet("MC", "MC", tree_MC, *ntplVars, "", "weight");
		RooDataSet *mc = new RooDataSet("MC", "MC", tree_MC, *ntplVars, "", "weight_pileUp");
	
	// Create data subsets
	
	  RooDataSet *EBmc = (RooDataSet*)mc->reduce(set_of_cuts[i].c_str());
	  RooDataSet *mmgEBmc = (RooDataSet*)mc->reduce(Mmumugamma, set_of_cuts[i].c_str());
		RooDataSet *kEBmc = (RooDataSet*)mc->reduce(mmg_k, set_of_cuts[i].c_str());
		RooDataSet *ikEBmc = (RooDataSet*)mc->reduce(mmg_ik, set_of_cuts[i].c_str());
		RooDataSet *sEBmc = (RooDataSet*)mc->reduce(mmg_s, set_of_cuts[i].c_str());

	// Create PDF
		RooKeysPdf *pdfmmgEBMC = new RooKeysPdf("pdfmmgEBMC", "pdfmmgEBMC", Mmumugamma, *mmgEBmc);
//		cout << endl << endl << pdfmmgEBMC->getNorm() << endl << endl;
		RooKeysPdf *pdfkEBMC = new RooKeysPdf("pdfkEBMC", "pdfkEBMC", mmg_k, *kEBmc);
		RooKeysPdf *pdfsEBMC = new RooKeysPdf("pdfsEBMC", "pdfsEBMC", mmg_s, *sEBmc);
		
	// Draw PDF with MC
	/*
			TCanvas *cMC = new TCanvas("MC", "MC");
			RooPlot* kMCframe = mmg_k.frame();
			kEBmc->plotOn(kMCframe);
			pdfkEBMC->plotOn(kMCframe);
			kMCframe->Draw();
			cMC->Draw();
	*/
	
	// Fit MC to data (ie compute probability of data given the MC pdf)
			RooFitResult* mmg_result = (RooFitResult*)pdfmmgEBMC->fitTo(*mmgEBmc, Save());
			RooFitResult* k_result = (RooFitResult*)pdfkEBMC->fitTo(*kEBdata, Save());
			RooFitResult* s_result = (RooFitResult*)pdfsEBMC->fitTo(*sEBdata, Save());

			maxLL_mmg = max(maxLL_mmg, mmg_result->minNll());
			maxLL_k = max(maxLL_k, k_result->minNll());
			maxLL_s = max(maxLL_s, s_result->minNll());

			minLL_mmg = min(minLL_mmg, mmg_result->minNll());
			minLL_k = min(minLL_k, k_result->minNll());
			minLL_s = min(minLL_s, s_result->minNll());

			cout << alpha << "\t" << mmg_result->minNll() << endl;
			LL_mmg->Fill(alpha, mmg_result->minNll());	
			cout << alpha << "\t" << s_result->minNll() << endl;
			LL_s->Fill(alpha, s_result->minNll());
			cout << alpha << "\t" << k_result->minNll() << endl;
			LL->Fill(alpha, k_result->minNll());

		} // end of loop over ikin
	
	// Draw nll
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	string title;

  double Range_mmg_lin = ((double)(maxLL_mmg - minLL_mmg)) / ((double)(1.0));
  double YMin_mmg_lin = - 0.1*Range_mmg_lin + minLL_mmg;
  double YMax_mmg_lin = 0.2*Range_mmg_lin + maxLL_mmg;

  double Range_k_lin = ((double)(maxLL_k - minLL_k)) / ((double)(1.0));
  double YMin_k_lin = - 0.1*Range_k_lin + minLL_k;
  double YMax_k_lin = 0.2*Range_k_lin + maxLL_k;

  double Range_s_lin = ((double)(maxLL_s - minLL_s)) / ((double)(1.0));
  double YMin_s_lin = - 0.1*Range_s_lin + minLL_s;
  double YMax_s_lin = 0.2*Range_s_lin + maxLL_s;

// Compute Likelihood

// likelihood on k
		
		title  = "LL_res_k_" + name[i];
		TCanvas *cLL = new TCanvas(title.c_str(), title.c_str());
//		LL->Draw("E1");
		TF1 *p2kfit = new TF1("p2kfit","pol2", 0.00, 10.05);
		p2kfit->SetLineColor(kRed);
		p2kfit->SetLineWidth(1);
		LL->Fit(p2kfit, "Rw");
		double p0, p1, p2;
		double p0err, p1err, p2err;
		p0 = p2kfit->GetParameter(0);
		p0err = p2kfit->GetParError(0);
		p1 = p2kfit->GetParameter(1);
		p1err = p2kfit->GetParError(1);
		p2 = p2kfit->GetParameter(2);
		p2err = p2kfit->GetParError(2);
		cout <<
		"p0=\t" << p0 << "\t+-\t" << p0err << "\t" << endl << 
		"p1=\t" << p1 << "\t+-\t" << p1err << "\t" << endl <<
		"p2=\t" << p2 << "\t+-\t" << p2err << "\t" << 
		endl;
		gPad->Update();
		LL->GetXaxis()->SetTitle("injected resolution");
		LL->GetYaxis()->SetTitle("-#Delta log L for k");
  	LL->SetLineColor(kWhite);
  	LL->SetMarkerColor(kBlack);
  	LL->SetMarkerSize(0.7);
  	LL->SetMarkerStyle(20);
  	LL->SetMaximum(YMax_k_lin);
  	LL->SetMinimum(YMin_k_lin);

	  TLatex latexLabel;
	  latexLabel.SetNDC();
  	latexLabel.SetTextSize(0.03);
  	latexLabel.DrawLatex(0.13, 0.96, "CMS Preliminary 2011");
  	latexLabel.DrawLatex(0.42, 0.96, "#sqrt{s} = 7 TeV");
		latexLabel.SetTextSize(0.05);
		latexLabel.DrawLatex(0.65, 0.88, display[i].c_str());
//		latexLabel.SetTextSize(0.03);
		double position = 0.92;
		position -= 0.04;
		latexLabel.DrawLatex(0.20, position, "Fit: parabola");
		position -= 0.04;
/*
		latexLabel.DrawLatex(0.20, position, Form("p0= %f #pm %f", p0, p0err));
		position -= 0.04;
		latexLabel.DrawLatex(0.20, position, Form("p1= %f #pm %f", p1, p1err));
		position -= 0.04;
		latexLabel.DrawLatex(0.20, position, Form("p2= %f #pm %f", p2, p2err));
		position -= 0.04;
*/
		latexLabel.DrawLatex(0.20, position, Form("resolution= %f", (double)(- p1) / (double)(2 * p2)));
		position -= 0.04;
		latexLabel.DrawLatex(0.20, position, Form("sigma= %f", (double)(1.0) / (double)( sqrt(2 * fabs(p2)))));
		gPad->Update();
		
		cout << endl;
		cout << "resolution=\t" << (double)(- p1) / (double)(2 * p2) << endl;
		if(p2 >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * fabs(p2)) ) << endl;
	//	th2->Draw();
		LL->Draw("Psame");
//		cLL->Draw();
		cLL->Print(Form("gif/%s.gif", title.c_str()));
		cLL->Print(Form("eps/%s.eps", title.c_str()));
		cLL->Print(Form("png/%s.png", title.c_str()));
		cLL->Print(Form("C/%s.C", title.c_str()));
		system(Form("convert eps/%s.eps pdf/%s.pdf", title.c_str(), title.c_str()));


	// likelihood on s
		title  = "LL_res_s_" + name[i];
		TCanvas *cLL_s = new TCanvas(title.c_str(), title.c_str());
		LL_s->Draw("E1");
		p2kfit = new TF1("p2kfit","pol2", 0.0, 10.05);
    p2kfit->SetLineColor(kRed);
    p2kfit->SetLineWidth(1);
		LL_s->Fit(p2kfit, "Rw");
		p0 = p2kfit->GetParameter(0);
		p0err = p2kfit->GetParError(0);
		p1 = p2kfit->GetParameter(1);
		p1err = p2kfit->GetParError(1);
		p2 = p2kfit->GetParameter(2);
		p2err = p2kfit->GetParError(2);
		cout <<
		"p0=\t" << p0 << "\t+-\t" << p0err << "\t" << endl << 
		"p1=\t" << p1 << "\t+-\t" << p1err << "\t" << endl <<
		"p2=\t" << p2 << "\t+-\t" << p2err << "\t" << 
		endl;
		gPad->Update();
		LL_s->GetXaxis()->SetTitle("injected resolution");
		LL_s->GetYaxis()->SetTitle("-#Delta log L for s");
  	LL_s->SetLineColor(kWhite);
  	LL_s->SetMarkerColor(kBlack);
  	LL_s->SetMarkerSize(0.7);
  	LL_s->SetMarkerStyle(20);
  	LL_s->SetMaximum(YMax_s_lin);
  	LL_s->SetMinimum(YMin_s_lin);

	  latexLabel.SetNDC();
  	latexLabel.SetTextSize(0.03);
  	latexLabel.DrawLatex(0.13, 0.96, "CMS Preliminary 2011");
  	latexLabel.DrawLatex(0.42, 0.96, "#sqrt{s} = 7 TeV");
		latexLabel.SetTextSize(0.05);
		latexLabel.DrawLatex(0.65, 0.88, display[i].c_str());
//		latexLabel.SetTextSize(0.03);
		position = 0.92;
		position -= 0.04;
		latexLabel.DrawLatex(0.20, position, "Fit: parabola");
		position -= 0.04;
/*
		latexLabel.DrawLatex(0.20, position, Form("p0= %f #pm %f", p0, p0err));
		position -= 0.04;
		latexLabel.DrawLatex(0.20, position, Form("p1= %f #pm %f", p1, p1err));
		position -= 0.04;
		latexLabel.DrawLatex(0.20, position, Form("p2= %f #pm %f", p2, p2err));
		position -= 0.04;
*/
		latexLabel.DrawLatex(0.20, position, Form("resolution= %f", (double)(- p1) / (double)(2 * p2)));
		position -= 0.04;
		latexLabel.DrawLatex(0.20, position, Form("sigma= %f", (double)(1.0) / (double)( sqrt(2 * fabs(p2)))));
		gPad->Update();
		
		cout << endl;
		cout << "resolution=\t" << (double)(- p1) / (double)(2 * p2) << endl;
		if(p2 >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * fabs(p2)) ) << endl;
	//	th2->Draw();
		LL_s->Draw("Psame");
//		cLL_s->Draw();
		cLL_s->Print(Form("gif/%s.gif", title.c_str()));
		cLL_s->Print(Form("eps/%s.eps", title.c_str()));
		cLL_s->Print(Form("png/%s.png", title.c_str()));
		cLL_s->Print(Form("C/%s.C", title.c_str()));
		system(Form("convert eps/%s.eps pdf/%s.pdf", title.c_str(), title.c_str()));


	// likelihood on mmg
		title  = "LL_res_mmg_" + name[i];
		TCanvas *cLL_mmg = new TCanvas(title.c_str(), title.c_str());
		LL_mmg->Draw("E1");
		p2kfit = new TF1("p2kfit","pol2", 0.0, 10.05);
    p2kfit->SetLineColor(kRed);
    p2kfit->SetLineWidth(1);
		LL_mmg->Fit(p2kfit, "Rw");
		p0 = p2kfit->GetParameter(0);
		p0err = p2kfit->GetParError(0);
		p1 = p2kfit->GetParameter(1);
		p1err = p2kfit->GetParError(1);
		p2 = p2kfit->GetParameter(2);
		p2err = p2kfit->GetParError(2);
		cout <<
		"p0=\t" << p0 << "\t+-\t" << p0err << "\t" << endl << 
		"p1=\t" << p1 << "\t+-\t" << p1err << "\t" << endl <<
		"p2=\t" << p2 << "\t+-\t" << p2err << "\t" << 
		endl;
		gPad->Update();
		LL_mmg->GetXaxis()->SetTitle("injected resolution");
		LL_mmg->GetYaxis()->SetTitle("-#Delta log L for mmg");
  	LL_mmg->SetLineColor(kWhite);
  	LL_mmg->SetMarkerColor(kBlack);
  	LL_mmg->SetMarkerSize(0.7);
  	LL_mmg->SetMarkerStyle(20);
  	LL_mmg->SetMaximum(YMax_mmg_lin);
  	LL_mmg->SetMinimum(YMin_mmg_lin);

	  latexLabel.SetNDC();
  	latexLabel.SetTextSize(0.03);
  	latexLabel.DrawLatex(0.13, 0.96, "CMS Preliminary 2011");
  	latexLabel.DrawLatex(0.42, 0.96, "#sqrt{s} = 7 TeV");
		latexLabel.SetTextSize(0.05);
		latexLabel.DrawLatex(0.65, 0.88, display[i].c_str());
//		latexLabel.SetTextSize(0.03);
		position = 0.92;
		position -= 0.04;
		latexLabel.DrawLatex(0.20, position, "Fit: parabola");
		position -= 0.04;
/*
		latexLabel.DrawLatex(0.20, position, Form("p0= %f #pm %f", p0, p0err));
		position -= 0.04;
		latexLabel.DrawLatex(0.20, position, Form("p1= %f #pm %f", p1, p1err));
		position -= 0.04;
		latexLabel.DrawLatex(0.20, position, Form("p2= %f #pm %f", p2, p2err));
		position -= 0.04;
*/
		latexLabel.DrawLatex(0.20, position, Form("resolution= %f", (double)(- p1) / (double)(2 * p2)));
		position -= 0.04;
		latexLabel.DrawLatex(0.20, position, Form("sigma= %f", (double)(1.0) / (double)( sqrt(2 * fabs(p2)))));
		gPad->Update();
		
		cout << endl;
		cout << "resolution=\t" << (double)(- p1) / (double)(-2 * p2) << endl;
		if(p2 >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * fabs(p2)) ) << endl;
	//	th2->Draw();
		LL_s->Draw("Psame");
//		cLL_s->Draw();
		cLL_mmg->Print(Form("gif/%s.gif", title.c_str()));
		cLL_mmg->Print(Form("png/%s.png", title.c_str()));
		cLL_mmg->Print(Form("eps/%s.eps", title.c_str()));
		cLL_mmg->Print(Form("C/%s.C", title.c_str()));
		system(Form("convert eps/%s.eps	pdf/%s.pdf", title.c_str(), title.c_str()));
/*	
		TCanvas *cLL_s = new TCanvas("cLL_s", "cLL_s");
		LL_s->Draw("E1");
		TF1 *p2sfit = new TF1("p2sfit","pol2", -2.0, 2.0);
		LL_s->Fit(p2sfit, "Rw");
		double p0_s, p1_s, p2_s;
		double p0err_s, p1err_s, p2err_s;
		p0_s = p2sfit->GetParameter(0);
		p0err_s = p2sfit->GetParError(0);
		p1_s = p2sfit->GetParameter(1);
		p1err_s = p2sfit->GetParError(1);
		p2_s = p2sfit->GetParameter(2);
		p2err_s = p2sfit->GetParError(2);
		cout <<
		"p0=\t" << p0_s << "\t+-\t" << p0err_s << "\t" << endl << 
		"p1=\t" << p1_s << "\t+-\t" << p1err_s << "\t" << endl <<
		"p2=\t" << p2_s << "\t+-\t" << p2err_s << "\t" << 
		endl;
		
		cout << endl;
		if(p2_s >= 0.0) cout << "scale=\t" << (double)(- p1_s) / (double)(2 * p2_s) << endl;
		if(p2_s >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * p2_s) ) << endl;
		if(p2_s <= 0.0) cout << "scale=\t" << (double)(- p1_s) / (double)(- 2 * p2_s) << endl;
		if(p2_s <= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(- 2 * p2_s) ) << endl;
	//	th2->Draw();
		LL_s->Draw("E1");
		cLL_s->Draw();
		cLL_s->Print("LL_s.gif");
	
	
		TCanvas *cLL_mmg = new TCanvas("cLL_mmg", "cLL_mmg");
		LL_mmg->Draw("E1");
		TF1 *p2mmgfit = new TF1("p2mmgfit","pol2", -6.0, -6.0);
		LL_mmg->Fit(p2mmgfit, "Rw");
		double p0_mmg, p1_mmg, p2_mmg;
		double p0err_mmg, p1err_mmg, p2err_mmg;
		p0_mmg = p2mmgfit->GetParameter(0);
		p0err_mmg = p2mmgfit->GetParError(0);
		p1_mmg = p2mmgfit->GetParameter(1);
		p1err_mmg = p2mmgfit->GetParError(1);
		p2_mmg = p2mmgfit->GetParameter(2);
		p2err_mmg = p2mmgfit->GetParError(2);
		cout <<
		"p0=\t" << p0_mmg << "\t\+-\t" << p0err_mmg << "\t" << endl << 
		"p1=\t" << p1_mmg << "\t\+-\t" << p1err_mmg << "\t" << endl <<
		"p2=\t" << p2_mmg << "\t\+-\t" << p2err_mmg << "\t" << 
		endl;
		
		cout << endl;
		if(p2_mmg >= 0.0) cout << "scale=\t" << (double)(- p1_mmg) / (double)(2 * p2_mmg) << endl;
		if(p2_mmg >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * p2_mmg) ) << endl;
	//	th2->Draw();
		LL_mmg->Draw("E1");
		cLL_mmg->Draw();
		cLL_mmg->Print("LL_mmg.gif");
	*/

	}// end of loop over set of cuts

	return 0;
}// end of macro

