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
void LL_Jan()
{
	CMSstyle();

// Prepare output file
	ofstream* errfile = new ofstream("Likelihood.txt");
	TProfile *LL_k_EB = new TProfile("LL_k_EB", "LL_k_EB", 101, 0.95, 1.05);
	TProfile *LL_s_EB = new TProfile("LL_s_EB", "LL_s_EB", 101, -6, 6);
	TProfile *LL_mmg_EB = new TProfile("LL_mmg_EB", "LL_mmg_EB", 101, -6, 6);
	TProfile *LL_k_EE = new TProfile("LL_k_EE", "LL_k_EE", 101, 0.95, 1.05);
	TProfile *LL_s_EE = new TProfile("LL_s_EE", "LL_s_EE", 101, -6, 6);
	TProfile *LL_mmg_EE = new TProfile("LL_mmg_EE", "LL_mmg_EE", 101, -6, 6);
//	TH2F *th2 = new TH2F("th2", "th2", 101, 0.95, 1.05, 100, -235, -223);

// Setup data observables
	RooRealVar mmgData("mmgData", "mmgData", 60, 120);
	RooRealVar kData("kData","kData",-9,9);
  RooRealVar ikData("ikData","ikData",-9,9);
  RooRealVar sData("sData","sData",-9,9);
  RooRealVar etaData("etaData", "etaData", -3, 3);

// Read data
//  RooDataSet *data = RooDataSet::read("Selected_DATA_eta_k.txt", RooArgList(etaData, mmgData, kData, ikData, sData));
  RooDataSet *data = RooDataSet::read("hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG/Selected_DATA_eta_k.txt", RooArgList(etaData, mmgData, kData, ikData, sData));
// Create data subsets
  RooDataSet *EBdata = data->reduce("etaData<1.4442&&etaData>-1.4442");
  RooDataSet *mmgEBdata = data->reduce(mmgData, "etaData<1.4442&&etaData>-1.4442");
  RooDataSet *kEBdata = data->reduce(kData, "etaData<1.4442&&etaData>-1.4442");
  RooDataSet *iEBdata = data->reduce(ikData, "etaData<1.4442&&etaData>-1.4442");
  RooDataSet *sEBdata = data->reduce(sData, "etaData<1.4442&&etaData>-1.4442");

  RooDataSet *EEdata = data->reduce("etaData>1.566||etaData<1.566");
  RooDataSet *mmgEEdata = data->reduce(mmgData, "etaData>1.566||etaData<-1.566");
  RooDataSet *kEEdata = data->reduce(kData, "etaData>1.566||etaData<-1.566");
  RooDataSet *iEEdata = data->reduce(ikData, "etaData>1.566||etaData<-1.566");
  RooDataSet *sEEdata = data->reduce(sData, "etaData>1.566||etaData<-1.566");


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
	{
		TH1F *mmg_MC_EB_hist = new TH1F("h_EB_mmg", "h_EB_mmg", 20, 87.2, 95.2);
		TH1F *k_MC_EB_hist = new TH1F("h_EB_k", "h_EB_k", 20, 0.95, 1.05);
		TH1F *s_MC_EB_hist = new TH1F("h_EB_s", "h_EB_s", 20, -5.0, 5.0);
		TH1F *mmg_MC_EE_hist = new TH1F("h_EE_mmg", "h_EE_mmg", 20, 87.2, 95.2);
		TH1F *k_MC_EE_hist = new TH1F("h_EE_k", "h_EE_k", 20, 0.95, 1.05);
		TH1F *s_MC_EE_hist = new TH1F("h_EE_s", "h_EE_s", 20, -5.0, 5.0);
		sprintf(x,"%4.3f",alpha);
		s_alpha = (alpha - 1) * 100;


// Setup Monte-Carlo observables
		RooRealVar mmgMC("mmgMC", "mmgMC", 60, 120);
		RooRealVar kMC("kMC","kMC",-9,9);
		RooRealVar ikMC("ikMC","ikMC",-9,9);
		RooRealVar sMC("sMC","sMC",-9,9);
		RooRealVar etaMC("etaMC", "etaMC", -3, 3);
// Read mc file
//		RooDataSet *mc = RooDataSet::read(Form("MC/Selected_MC_%s_eta_k.txt", x), RooArgList(etaMC, mmgMC, kMC, ikMC, sMC));
		RooDataSet *mc = RooDataSet::read(Form("hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG/Selected_MC_%s_eta_k.txt", x), RooArgList(etaMC, mmgMC, kMC, ikMC, sMC));

		RooDataSet *EBmc = mc->reduce("etaMC<1.4442&&etaMC>-1.4442");
		RooDataSet *mmgEBmc = mc->reduce(mmgMC, "etaMC<1.4442&&etaMC>-1.4442");
		RooDataSet *kEBmc = mc->reduce(kMC, "etaMC<1.4442&&etaMC>-1.4442");
		RooDataSet *sEBmc = mc->reduce(sMC, "etaMC<1.4442&&etaMC>-1.4442");

		RooDataSet *EEmc = mc->reduce("etaMC>1.566||etaMC<-1.566");
		RooDataSet *mmgEEmc = mc->reduce(mmgMC, "etaMC>1.566||etaMC<-1.566");
		RooDataSet *kEEmc = mc->reduce(kMC, "etaMC>1.566||etaMC<-1.566");
		RooDataSet *sEEmc = mc->reduce(sMC, "etaMC>1.566||etaMC<-1.566");

// Create PDF
		RooKeysPdf *pdfmmgEBMC = new RooKeysPdf("pdfmmgEBMC", "pdfmmgEBMC", mmgMC,*mmgEBmc);
		RooKeysPdf *pdfkEBMC = new RooKeysPdf("pdfkEBMC", "pdfkEBMC", kMC,*kEBmc);
		RooKeysPdf *pdfsEBMC = new RooKeysPdf("pdfsEBMC", "pdfsEBMC", sMC,*sEBmc);

// Alternative PDF : RooHistPdf
//		mmgMC.setBins(20);
//		RooDataHist * mmgEBmcHist = mmgEBmc->binnedClone();
//		RooHistPdf *pdfmmgEBMC = new RooHistPdf("pdfmmgEBMC", "pdfmmgEBMC",mmgMC, *mmgEBmcHist);

// Jan's approach
		double likelihood_EB_mmg = 0.0;
		double likelihood_EB_k = 0.0;
		double likelihood_EB_s = 0.0;
		double likelihood_EE_mmg = 0.0;
		double likelihood_EE_k = 0.0;
		double likelihood_EE_s = 0.0;
		double sum_EB_mmg = 0.0;
		double sum_EB_k = 0.0;
		double sum_EB_s = 0.0;
		double sum_EE_mmg = 0.0;
		double sum_EE_k = 0.0;
		double sum_EE_s = 0.0;
// Create MC Histogram
		mmgEBmc->fillHistogram(mmg_MC_EB_hist, RooArgList(mmgMC));
		kEBmc->fillHistogram(k_MC_EB_hist, RooArgList(kMC));
		sEBmc->fillHistogram(s_MC_EB_hist, RooArgList(sMC));
		mmgEEmc->fillHistogram(mmg_MC_EE_hist, RooArgList(mmgMC));
		kEEmc->fillHistogram(k_MC_EE_hist, RooArgList(kMC));
		sEEmc->fillHistogram(s_MC_EE_hist, RooArgList(sMC));
// Fit MC histogram
		mmg_MC_EB_hist->Fit("gaus", "Q0");
		k_MC_EB_hist->Fit("gaus", "Q0");
		s_MC_EB_hist->Fit("gaus", "Q0");
		mmg_MC_EE_hist->Fit("gaus", "Q0");
		k_MC_EE_hist->Fit("gaus", "Q0");
		s_MC_EE_hist->Fit("gaus", "Q0");
		TF1* fit_mmg_EB = mmg_MC_EB_hist->GetFunction("gaus");
		TF1* fit_k_EB = k_MC_EB_hist->GetFunction("gaus");
		TF1* fit_s_EB = s_MC_EB_hist->GetFunction("gaus");
		TF1* fit_mmg_EE = mmg_MC_EE_hist->GetFunction("gaus");
		TF1* fit_k_EE = k_MC_EE_hist->GetFunction("gaus");
		TF1* fit_s_EE = s_MC_EE_hist->GetFunction("gaus");
// Loop over data points
		int dataEntries_mmg_EB = mmgEBdata->numEntries();
		int dataEntries_k_EB = kEBdata->numEntries();
		int dataEntries_s_EB = sEBdata->numEntries();
		int dataEntries_mmg_EE = mmgEEdata->numEntries();
		int dataEntries_k_EE = kEEdata->numEntries();
		int dataEntries_s_EE = sEEdata->numEntries();

		for(int idata = 0 ; idata < dataEntries_mmg_EB ; idata++ )
		{
			RooArgSet* temp = mmgEBdata->get(idata);
			likelihood_EB_mmg = mmg_MC_EB_hist->Interpolate(temp->getRealValue("mmgData"));
			if (likelihood_EB_mmg <= 0.0) likelihood_EB_mmg = fit_mmg_EB->Eval(temp->getRealValue("mmgData"));
			sum_EB_mmg -= log(likelihood_EB_mmg);
		}
		for(int idata = 0 ; idata < dataEntries_k_EB ; idata++ )
		{
			RooArgSet* temp = kEBdata->get(idata);
			likelihood_EB_k = k_MC_EB_hist->Interpolate(temp->getRealValue("kData"));
			if (likelihood_EB_k <= 0.0) likelihood_EB_k = fit_k_EB->Eval(temp->getRealValue("kData"));
			sum_EB_k -= log(likelihood_EB_k);
		}
		for(int idata = 0 ; idata < dataEntries_s_EB ; idata++ )
		{
			RooArgSet* temp = sEBdata->get(idata);
			likelihood_EB_s = s_MC_EB_hist->Interpolate(temp->getRealValue("sData"));
			if (likelihood_EB_s <= 0.0) likelihood_EB_s = fit_s_EB->Eval(temp->getRealValue("sData"));
			sum_EB_s -= log(likelihood_EB_s);
		}

		for(int idata = 0 ; idata < dataEntries_mmg_EE ; idata++ )
		{
			RooArgSet* temp = mmgEEdata->get(idata);
			likelihood_EE_mmg = mmg_MC_EE_hist->Interpolate(temp->getRealValue("mmgData"));
			if (likelihood_EE_mmg <= 0.0) likelihood_EE_mmg = fit_mmg_EE->Eval(temp->getRealValue("mmgData"));
			sum_EE_mmg -= log(likelihood_EE_mmg);
		}
		for(int idata = 0 ; idata < dataEntries_k_EE ; idata++ )
		{
			RooArgSet* temp = kEEdata->get(idata);
			likelihood_EE_k = k_MC_EE_hist->Interpolate(temp->getRealValue("kData"));
			if (likelihood_EE_k <= 0.0) likelihood_EE_k = fit_k_EE->Eval(temp->getRealValue("kData"));
			sum_EE_k -= log(likelihood_EE_k);
		}
		for(int idata = 0 ; idata < dataEntries_s_EE ; idata++ )
		{
			RooArgSet* temp = sEEdata->get(idata);
			likelihood_EE_s = s_MC_EE_hist->Interpolate(temp->getRealValue("sData"));
			if (likelihood_EE_s <= 0.0) likelihood_EE_s = fit_s_EE->Eval(temp->getRealValue("sData"));
			sum_EE_s -= log(likelihood_EE_s);
		}
// Draw PDF with MC
/*
		TCanvas *cMC = new TCanvas("MC", "MC");
		RooPlot* kMCframe = kMC.frame();
		kEBmc->plotOn(kMCframe);
		pdfkEBMC->plotOn(kMCframe);
		kMCframe->Draw();
		cMC->Draw();
		cMC->Print(Form("k_%s.gif", x));

		RooPlot* mmgMCframe = mmgMC.frame();
		mmgEBmc->plotOn(mmgMCframe);
		pdfmmgEBMC->plotOn(mmgMCframe);
		mmgMCframe->Draw();
		cMC->Draw();
		cMC->Print(Form("mmg_%s.gif", x));
*/

// Fit MC to data (ie compute probability of data given the MC pdf)
/*
		RooFitResult* fit = pdfkEBMC->fitTo(*kEBdata, Save(kTRUE));
		*errfile << x << "\t" << fit->minNll() << endl;
*/

// Create NLL of MC to data
/*
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
*/
//		cout << s_alpha << "\t" << -(mmgEBnll->getVal()) << endl;
//		cout << s_alpha << "\t" << sum_mmg << endl;
//		LL_mmg->Fill(s_alpha, -(mmgEBnll->getVal()));
		LL_mmg_EB->Fill(s_alpha, sum_EB_mmg);
//		cout << alpha << "\t" << -(kEBnll->getVal()) << endl;
//		cout << alpha << "\t" << sum_k << endl;
//		LL_k->Fill(alpha, -(kEBnll->getVal()));
		LL_k_EB->Fill(alpha, sum_EB_k);
//		cout << s_alpha << "\t" << -(sEBnll->getVal()) << endl;
//		cout << s_alpha << "\t" << sum_s << endl;
//		LL_s->Fill(s_alpha, -(sEBnll->getVal()));
		LL_s_EB->Fill(s_alpha, sum_EB_s);
//		th2->Fill(alpha, (sEBnll->getVal()));
		LL_mmg_EE->Fill(s_alpha, sum_EE_mmg);
		LL_k_EE->Fill(alpha, sum_EE_k);
		LL_s_EE->Fill(s_alpha, sum_EE_s);


		mmg_MC_EB_hist->Delete();
		k_MC_EB_hist->Delete();
		s_MC_EB_hist->Delete();
		mmg_MC_EE_hist->Delete();
		k_MC_EE_hist->Delete();
		s_MC_EE_hist->Delete();


	} // end of loop over ikin

// Draw nll
	TCanvas *cLL_k_EB = new TCanvas("cLL_k_EB", "cLL_k_EB");
	LL_k_EB->Draw("E1");
	TF1 *p2kfit_EB = new TF1("p2kfit_EB","pol2", 0.95, 1.05);
	LL_k_EB->Fit(p2kfit_EB, "Rw");
	double p0_k_EB, p1_k_EB, p2_k_EB;
	double p0err_k_EB, p1err_k_EB, p2err_k_EB;
	p0_k_EB = p2kfit_EB->GetParameter(0);
	p0err_k_EB = p2kfit_EB->GetParError(0);
	p1_k_EB = p2kfit_EB->GetParameter(1);
	p1err_k_EB = p2kfit_EB->GetParError(1);
	p2_k_EB = p2kfit_EB->GetParameter(2);
	p2err_k_EB = p2kfit_EB->GetParError(2);
	cout <<
	"p0=\t" << p0_k_EB << "\t\\pm\t" << p0err_k_EB << "\t" << endl << 
	"p1=\t" << p1_k_EB << "\t\\pm\t" << p1err_k_EB << "\t" << endl <<
	"p2=\t" << p2_k_EB << "\t\\pm\t" << p2err_k_EB << "\t" << 
	endl;
	
	cout << endl;
	cout << "scale=\t" << (double)(- p1_k_EB) / (double)(2 * p2_k_EB) << endl;
	if(p2_k_EB >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * p2_k_EB) ) << endl;
//	th2->Draw();
	cLL_k_EB->Draw();
	cLL_k_EB->Print("LL_k_EB.gif");


	TCanvas *cLL_s_EB = new TCanvas("cLL_s_EB", "cLL_s_EB");
	LL_s_EB->Draw("E1");
	TF1 *p2sfit_EB = new TF1("p2sfit_EB","pol2", -5.0, -5.0);
	LL_s_EB->Fit(p2sfit_EB, "Rw");
	double p0_s_EB, p1_s_EB, p2_s_EB;
	double p0err_s_EB, p1err_s_EB, p2err_s_EB;
	p0_s_EB = p2sfit_EB->GetParameter(0);
	p0err_s_EB = p2sfit_EB->GetParError(0);
	p1_s_EB = p2sfit_EB->GetParameter(1);
	p1err_s_EB = p2sfit_EB->GetParError(1);
	p2_s_EB = p2sfit_EB->GetParameter(2);
	p2err_s_EB = p2sfit_EB->GetParError(2);
	cout <<
	"p0=\t" << p0_s_EB << "\t\\pm\t" << p0err_s_EB << "\t" << endl << 
	"p1=\t" << p1_s_EB << "\t\\pm\t" << p1err_s_EB << "\t" << endl <<
	"p2=\t" << p2_s_EB << "\t\\pm\t" << p2err_s_EB << "\t" << 
	endl;
	
	cout << endl;
	if(p2_s_EB >= 0.0) cout << "scale=\t" << (double)(- p1_s_EB) / (double)(2 * p2_s_EB) << endl;
	if(p2_s_EB >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * p2_s_EB) ) << endl;
//	th2->Draw();
	cLL_s_EB->Draw();
	cLL_s_EB->Print("LL_s_EB.gif");


	TCanvas *cLL_mmg_EB = new TCanvas("cLL_mmg_EB", "cLL_mmg_EB");
	LL_mmg_EB->Draw("E1");
	TF1 *p2mmgfit_EB = new TF1("p2mmgfit_EB","pol2", -5.0, -5.0);
	LL_mmg_EB->Fit(p2mmgfit_EB, "Rw");
	double p0_mmg_EB, p1_mmg_EB, p2_mmg_EB;
	double p0err_mmg_EB, p1err_mmg_EB, p2err_mmg_EB;
	p0_mmg_EB = p2mmgfit_EB->GetParameter(0);
	p0err_mmg_EB = p2mmgfit_EB->GetParError(0);
	p1_mmg_EB = p2mmgfit_EB->GetParameter(1);
	p1err_mmg_EB = p2mmgfit_EB->GetParError(1);
	p2_mmg_EB = p2mmgfit_EB->GetParameter(2);
	p2err_mmg_EB = p2mmgfit_EB->GetParError(2);
	cout <<
	"p0=\t" << p0_mmg_EB << "\t\\pm\t" << p0err_mmg_EB << "\t" << endl << 
	"p1=\t" << p1_mmg_EB << "\t\\pm\t" << p1err_mmg_EB << "\t" << endl <<
	"p2=\t" << p2_mmg_EB << "\t\\pm\t" << p2err_mmg_EB << "\t" << 
	endl;
	
	cout << endl;
	cout << "scale=\t" << (double)(- p1_mmg_EB) / (double)(2 * p2_mmg_EB) << endl;
	if(p2_mmg_EB >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * p2_mmg_EB) ) << endl;
	if(p2_mmg_EB <= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(-2 * p2_mmg_EB) ) << endl;
//	th2->Draw();
	cLL_mmg_EB->Draw();
	cLL_mmg_EB->Print("LL_mmg_EB.gif");

	TCanvas *cLL_k_EE = new TCanvas("cLL_k_EE", "cLL_k_EE");
	LL_k_EE->Draw("E1");
	TF1 *p2kfit_EE = new TF1("p2kfit_EE","pol2", 0.95, 1.05);
	LL_k_EE->Fit(p2kfit_EE, "Rw");
	double p0_k_EE, p1_k_EE, p2_k_EE;
	double p0err_k_EE, p1err_k_EE, p2err_k_EE;
	p0_k_EE = p2kfit_EE->GetParameter(0);
	p0err_k_EE = p2kfit_EE->GetParError(0);
	p1_k_EE = p2kfit_EE->GetParameter(1);
	p1err_k_EE = p2kfit_EE->GetParError(1);
	p2_k_EE = p2kfit_EE->GetParameter(2);
	p2err_k_EE = p2kfit_EE->GetParError(2);
	cout <<
	"p0=\t" << p0_k_EE << "\t\\pm\t" << p0err_k_EE << "\t" << endl << 
	"p1=\t" << p1_k_EE << "\t\\pm\t" << p1err_k_EE << "\t" << endl <<
	"p2=\t" << p2_k_EE << "\t\\pm\t" << p2err_k_EE << "\t" << 
	endl;
	
	cout << endl;
	cout << "scale=\t" << (double)(- p1_k_EE) / (double)(2 * p2_k_EE) << endl;
	if(p2_k_EE >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * p2_k_EE) ) << endl;
//	th2->Draw();
	cLL_k_EE->Draw();
	cLL_k_EE->Print("LL_k_EE.gif");


	TCanvas *cLL_s_EE = new TCanvas("cLL_s_EE", "cLL_s_EE");
	LL_s_EE->Draw("E1");
	TF1 *p2sfit_EE = new TF1("p2sfit_EE","pol2", -5.0, -5.0);
	LL_s_EE->Fit(p2sfit_EE, "Rw");
	double p0_s_EE, p1_s_EE, p2_s_EE;
	double p0err_s_EE, p1err_s_EE, p2err_s_EE;
	p0_s_EE = p2sfit_EE->GetParameter(0);
	p0err_s_EE = p2sfit_EE->GetParError(0);
	p1_s_EE = p2sfit_EE->GetParameter(1);
	p1err_s_EE = p2sfit_EE->GetParError(1);
	p2_s_EE = p2sfit_EE->GetParameter(2);
	p2err_s_EE = p2sfit_EE->GetParError(2);
	cout <<
	"p0=\t" << p0_s_EE << "\t\\pm\t" << p0err_s_EE << "\t" << endl << 
	"p1=\t" << p1_s_EE << "\t\\pm\t" << p1err_s_EE << "\t" << endl <<
	"p2=\t" << p2_s_EE << "\t\\pm\t" << p2err_s_EE << "\t" << 
	endl;
	
	cout << endl;
	if(p2_s_EE >= 0.0) cout << "scale=\t" << (double)(- p1_s_EE) / (double)(2 * p2_s_EE) << endl;
	if(p2_s_EE >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * p2_s_EE) ) << endl;
//	th2->Draw();
	cLL_s_EE->Draw();
	cLL_s_EE->Print("LL_s_EE.gif");


	TCanvas *cLL_mmg_EE = new TCanvas("cLL_mmg_EE", "cLL_mmg_EE");
	LL_mmg_EE->Draw("E1");
	TF1 *p2mmgfit_EE = new TF1("p2mmgfit_EE","pol2", -5.0, -5.0);
	LL_mmg_EE->Fit(p2mmgfit_EE, "Rw");
	double p0_mmg_EE, p1_mmg_EE, p2_mmg_EE;
	double p0err_mmg_EE, p1err_mmg_EE, p2err_mmg_EE;
	p0_mmg_EE = p2mmgfit_EE->GetParameter(0);
	p0err_mmg_EE = p2mmgfit_EE->GetParError(0);
	p1_mmg_EE = p2mmgfit_EE->GetParameter(1);
	p1err_mmg_EE = p2mmgfit_EE->GetParError(1);
	p2_mmg_EE = p2mmgfit_EE->GetParameter(2);
	p2err_mmg_EE = p2mmgfit_EE->GetParError(2);
	cout <<
	"p0=\t" << p0_mmg_EE << "\t\\pm\t" << p0err_mmg_EE << "\t" << endl << 
	"p1=\t" << p1_mmg_EE << "\t\\pm\t" << p1err_mmg_EE << "\t" << endl <<
	"p2=\t" << p2_mmg_EE << "\t\\pm\t" << p2err_mmg_EE << "\t" << 
	endl;
	
	cout << endl;
	cout << "scale=\t" << (double)(- p1_mmg_EE) / (double)(2 * p2_mmg_EE) << endl;
	if(p2_mmg_EE >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * p2_mmg_EE) ) << endl;
	if(p2_mmg_EE <= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(-2 * p2_mmg_EE) ) << endl;
//	th2->Draw();
	cLL_mmg_EE->Draw();
	cLL_mmg_EE->Print("LL_mmg_EE.gif");

}

