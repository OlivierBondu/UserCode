#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
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
#include <sstream>
#include <iostream>
#include <fstream>
#include "CMSStyle.C"
gROOT->Reset();

using namespace RooFit ;
void LL()
{
	CMSstyle();

// Prepare output file
	ofstream* errfile = new ofstream("Likelihood.txt");
	TProfile *LL = new TProfile("LL", "LL", 101, 0.95, 1.05);
	TProfile *LL_s = new TProfile("LL_s", "LL_s", 101, -6, 6);
	TProfile *LL_mmg = new TProfile("LL_mmg", "LL_mmg", 101, -6, 6);
//	TH2F *th2 = new TH2F("th2", "th2", 101, 0.95, 1.05, 100, -235, -223);

// Setup data observables
	RooRealVar mmgData("mmgData", "mmgData", 70, 110);
	RooRealVar kData("kData","kData",0,2);
  RooRealVar ikData("ikData","ikData",0,2);
  RooRealVar sData("sData","sData",-2,2);
  RooRealVar etaData("etaData", "etaData", -3, 3);

// Read data

	TFile *file_Data = new TFile("/sps/cms/obondu/CMSSW_4_2_3_patch2/src/Zmumugamma/Selection/miniTree_v5_DYToMuMu_M-20_TuneZ2_7TeV-pythia6_v3.root");
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


	RooDataSet *data = new RooDataSet("Data", "Data", tree_Data, *ntplVars);

// Create data subsets
/*
  RooDataSet *EBdata = data->reduce("Photon_isEB && isLooseMMG");
  RooDataSet *mmgEBdata = data->reduce(Mmumugamma, "Photon_isEB && isLooseMMG");
	RooDataSet *kEBdata = data->reduce(mmg_k, "Photon_isEB && isLooseMMG");
	RooDataSet *ikEBdata = data->reduce(mmg_ik, "Photon_isEB && isLooseMMG");
	RooDataSet *sEBdata = data->reduce(mmg_s, "Photon_isEB && isLooseMMG");
*/
 RooDataSet *EBdata = data->reduce("Photon_isEB && isTightMMG");
  RooDataSet *mmgEBdata = data->reduce(Mmumugamma, "Photon_isEB && isTightMMG");
	RooDataSet *kEBdata = data->reduce(mmg_k, "Photon_isEB && isTightMMG");
	RooDataSet *ikEBdata = data->reduce(mmg_ik, "Photon_isEB && isTightMMG");
	RooDataSet *sEBdata = data->reduce(mmg_s, "Photon_isEB && isTightMMG");

// Set data observables as constants
/*
	mmgData.setConstant();
	kData.setConstant();
	ikData.setConstant();
	sData.setConstant();
	etaData.setConstant();
*/

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
	for(double alpha = 0.950 ; alpha <= 1.050 ; alpha += 0.001)
//	for(double alpha = 0.950 ; alpha <= 0.971 ; alpha += 0.001)
	{
		sprintf(x,"%4.3f",alpha);
		s_alpha = (alpha - 1) * 100;

// Setup Monte-Carlo observables
		RooRealVar mmgMC("mmgMC", "mmgMC", 70, 110);
		RooRealVar kMC("kMC","kMC",0,2);
		RooRealVar ikMC("ikMC","ikMC",0,2);
		RooRealVar sMC("sMC","sMC",-2,2);
		RooRealVar etaMC("etaMC", "etaMC", -3, 3);
// Read mc file
/// /sps/cms/obondu/temp/test_batch/miniTree_ALL_0.997.root

  TFile *file_MC = new TFile(Form("/sps/cms/obondu/temp/test_batch/miniTree_ALL_%s.root", x));
  TTree *tree_MC = (TTree*)file_MC->Get("miniTree");

	RooDataSet *mc = new RooDataSet("MC", "MC", tree_MC, *ntplVars);

// Create data subsets

  RooDataSet *EBmc = mc->reduce("Photon_isEB && isTightMMG");
  RooDataSet *mmgEBmc = mc->reduce(Mmumugamma, "Photon_isEB && isTightMMG");
	RooDataSet *kEBmc = mc->reduce(mmg_k, "Photon_isEB && isTightMMG");
	RooDataSet *ikEBmc = mc->reduce(mmg_ik, "Photon_isEB && isTightMMG");
	RooDataSet *sEBmc = mc->reduce(mmg_s, "Photon_isEB && isTightMMG");
/*
  RooDataSet *EBmc = mc->reduce("Photon_isEB && isLooseMMG");
  RooDataSet *mmgEBmc = mc->reduce(Mmumugamma, "Photon_isEB && isLooseMMG");
	RooDataSet *kEBmc = mc->reduce(mmg_k, "Photon_isEB && isLooseMMG");
	RooDataSet *ikEBmc = mc->reduce(mmg_ik, "Photon_isEB && isLooseMMG");
	RooDataSet *sEBmc = mc->reduce(mmg_s, "Photon_isEB && isLooseMMG");
*/

// Create PDF
	RooKeysPdf *pdfmmgEBMC = new RooKeysPdf("pdfmmgEBMC", "pdfmmgEBMC", Mmumugamma, *mmgEBmc);
	RooKeysPdf *pdfkEBMC = new RooKeysPdf("pdfkEBMC", "pdfkEBMC", mmg_k, *kEBmc);
	RooKeysPdf *pdfsEBMC = new RooKeysPdf("pdfsEBMC", "pdfsEBMC", mmg_s, *sEBmc);
	
//		RooKeysPdf *pdfmmgEBMC = new RooKeysPdf("pdfmmgEBMC", "pdfmmgEBMC", mmgMC,*mmgEBmc);
//		RooKeysPdf *pdfkEBMC = new RooKeysPdf("pdfkEBMC", "pdfkEBMC", kMC,*kEBmc);
//		RooKeysPdf *pdfsEBMC = new RooKeysPdf("pdfsEBMC", "pdfsEBMC", sMC,*sEBmc);

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
/*
		RooFitResult* fit = pdfkEBMC->fitTo(*kEBdata, Save(kTRUE));
		*errfile << x << "\t" << fit->minNll() << endl;
*/

		//Double_t mmgEBnll = pdfmmgEBMC->chi2FitTo(*mmgEBdata).minNll();
//		RooAbsReal* mmgEBnll = pdfmmgEBMC->createChi2(*mmgEBdata);

//		Double_t kEBnll = pdfkEBMC->fitTo(*kEBdata, Save())->minNll();
//    RooAbsReal* kEBnll = pdfkEBMC->fitTo(*kEBdata)->minNll();
//		RooFitResult* k_result = new RooFitResult();
//		k_result = (RooFitResult*)pdfkEBMC->fitTo(*kEBdata);
//		RooFitResult* k_result = (RooFitResult*)pdfkEBMC->fitTo(*kEBdata, Save(), Range(0.98, 1.02));
//		RooFitResult* s_result = (RooFitResult*)pdfsEBMC->fitTo(*sEBdata, Save(), Range(-0.02, 0.02));
		RooFitResult* k_result = (RooFitResult*)pdfkEBMC->fitTo(*kEBdata, Save());
		RooFitResult* s_result = (RooFitResult*)pdfsEBMC->fitTo(*sEBdata, Save());
//		k_result->Print();
//    cout << "k_result->minNll()" << k_result->minNll() << endl;
//    RooAbsReal* sEBnll = pdfsEBMC->fitTo(*sEBdata)->minNll();

		cout << s_alpha << "\t" << s_result->minNll() << endl;
		LL_s->Fill(s_alpha, s_result->minNll());
		cout << alpha << "\t" << k_result->minNll() << endl;
		LL->Fill(alpha, k_result->minNll());
/*
		cout << s_alpha << "\t" << -(mmgEBnll->getVal()) << endl;
		LL_mmg->Fill(s_alpha, -(mmgEBnll->getVal()));
		cout << alpha << "\t" << -(kEBnll->getVal()) << endl;
		LL->Fill(alpha, -(kEBnll->getVal()));
		cout << s_alpha << "\t" << -(sEBnll->getVal()) << endl;
		LL_s->Fill(s_alpha, -(sEBnll->getVal()));
*/
/*
// Create NLL of MC to data
		RooAbsReal* mmgEBnll = pdfmmgEBMC->createNLL(*mmgEBdata);
		RooAbsReal* kEBnll = pdfkEBMC->createNLL(*kEBdata);
		RooAbsReal* sEBnll = pdfsEBMC->createNLL(*sEBdata);
		RooMinuit(*mmgEBnll).migrad();
		RooMinuit(*kEBnll).migrad();
		RooMinuit(*sEBnll).migrad();
		*errfile << x << 
		"\t" << mmgEBnll->getVal() << 
		"\t" << kEBnll->getVal() << 
		"\t" << sEBnll->getVal() << 
		endl;
		cout << s_alpha << "\t" << -(mmgEBnll->getVal()) << endl;
		LL_mmg->Fill(s_alpha, -(mmgEBnll->getVal()));
		cout << alpha << "\t" << -(kEBnll->getVal()) << endl;
		LL->Fill(alpha, -(kEBnll->getVal()));
		cout << s_alpha << "\t" << -(sEBnll->getVal()) << endl;
		LL_s->Fill(s_alpha, -(sEBnll->getVal()));
//		th2->Fill(alpha, (sEBnll->getVal()));
*/


	} // end of loop over ikin

// Draw nll

	TCanvas *cLL = new TCanvas("cLL", "cLL");
	LL->Draw("E1");
	TF1 *p2kfit = new TF1("p2kfit","pol2", 0.98, 1.02);
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
	"p0=\t" << p0 << "\t\\pm\t" << p0err << "\t" << endl << 
	"p1=\t" << p1 << "\t\\pm\t" << p1err << "\t" << endl <<
	"p2=\t" << p2 << "\t\\pm\t" << p2err << "\t" << 
	endl;
	
	cout << endl;
	cout << "scale=\t" << (double)(- p1) / (double)(2 * p2) << endl;
	if(p2 >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * p2) ) << endl;
//	th2->Draw();
	cLL->Draw();
	cLL->Print("LL.gif");


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
	"p0=\t" << p0_s << "\t\\pm\t" << p0err_s << "\t" << endl << 
	"p1=\t" << p1_s << "\t\\pm\t" << p1err_s << "\t" << endl <<
	"p2=\t" << p2_s << "\t\\pm\t" << p2err_s << "\t" << 
	endl;
	
	cout << endl;
	if(p2_s >= 0.0) cout << "scale=\t" << (double)(- p1_s) / (double)(2 * p2_s) << endl;
	if(p2_s >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * p2_s) ) << endl;
	if(p2_s <= 0.0) cout << "scale=\t" << (double)(- p1_s) / (double)(- 2 * p2_s) << endl;
	if(p2_s <= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(- 2 * p2_s) ) << endl;
//	th2->Draw();
	cLL_s->Draw();
	cLL_s->Print("LL_s.gif");

/*
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
	"p0=\t" << p0_mmg << "\t\\pm\t" << p0err_mmg << "\t" << endl << 
	"p1=\t" << p1_mmg << "\t\\pm\t" << p1err_mmg << "\t" << endl <<
	"p2=\t" << p2_mmg << "\t\\pm\t" << p2err_mmg << "\t" << 
	endl;
	
	cout << endl;
	if(p2_mmg >= 0.0) cout << "scale=\t" << (double)(- p1_mmg) / (double)(2 * p2_mmg) << endl;
	if(p2_mmg >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * p2_mmg) ) << endl;
//	th2->Draw();
	cLL_mmg->Draw();
	cLL_mmg->Print("LL_mmg.gif");
*/
}

