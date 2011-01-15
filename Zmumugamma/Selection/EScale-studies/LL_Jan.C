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
  RooDataSet *data = RooDataSet::read("Selected_DATA_eta_k.txt", RooArgList(etaData, mmgData, kData, ikData, sData));
// Create data subsets
  RooDataSet *EBdata = data->reduce("etaData<1.4442&&etaData>-1.4442");
  RooDataSet *mmgEBdata = data->reduce(mmgData, "etaData<1.4442&&etaData>-1.4442");
  RooDataSet *kEBdata = data->reduce(kData, "etaData<1.4442&&etaData>-1.4442");
  RooDataSet *iEBdata = data->reduce(ikData, "etaData<1.4442&&etaData>-1.4442");
  RooDataSet *sEBdata = data->reduce(sData, "etaData<1.4442&&etaData>-1.4442");


// Set data observables as constants
	mmgData.setConstant();
	kData.setConstant();
	ikData.setConstant();
	sData.setConstant();
	etaData.setConstant();


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
		TH1F *mmg_MC_hist = new TH1F("h_mmg", "h_mmg", 20, 87.2, 95.2);
		TH1F *k_MC_hist = new TH1F("h_k", "h_k", 20, 0.95, 1.05);
		TH1F *s_MC_hist = new TH1F("h_s", "h_s", 20, -5.0, 5.0);
		sprintf(x,"%4.3f",alpha);
		s_alpha = (alpha - 1) * 100;


// Setup Monte-Carlo observables
		RooRealVar mmgMC("mmgMC", "mmgMC", 70, 110);
		RooRealVar kMC("kMC","kMC",0,2);
		RooRealVar ikMC("ikMC","ikMC",0,2);
		RooRealVar sMC("sMC","sMC",-2,2);
		RooRealVar etaMC("etaMC", "etaMC", -3, 3);
// Read mc file
		RooDataSet *mc = RooDataSet::read(Form("MC/Selected_MC_%s_eta_k.txt", x), RooArgList(etaMC, mmgMC, kMC, ikMC, sMC));
		RooDataSet *EBmc = mc->reduce("etaMC<1.4442&&etaMC>-1.4442");
		RooDataSet *mmgEBmc = mc->reduce(mmgMC, "etaMC<1.4442&&etaMC>-1.4442");
		RooDataSet *kEBmc = mc->reduce(kMC, "etaMC<1.4442&&etaMC>-1.4442");
		RooDataSet *sEBmc = mc->reduce(sMC, "etaMC<1.4442&&etaMC>-1.4442");

// Create PDF
		RooKeysPdf *pdfmmgEBMC = new RooKeysPdf("pdfmmgEBMC", "pdfmmgEBMC", mmgMC,*mmgEBmc);
		RooKeysPdf *pdfkEBMC = new RooKeysPdf("pdfkEBMC", "pdfkEBMC", kMC,*kEBmc);
		RooKeysPdf *pdfsEBMC = new RooKeysPdf("pdfsEBMC", "pdfsEBMC", sMC,*sEBmc);

// Alternative PDF : RooHistPdf
//		mmgMC.setBins(20);
//		RooDataHist * mmgEBmcHist = mmgEBmc->binnedClone();
//		RooHistPdf *pdfmmgEBMC = new RooHistPdf("pdfmmgEBMC", "pdfmmgEBMC",mmgMC, *mmgEBmcHist);

// Jan's approach
		double likelihood_mmg = 0.0;
		double likelihood_k = 0.0;
		double likelihood_s = 0.0;
		double sum_mmg = 0.0;
		double sum_k = 0.0;
		double sum_s = 0.0;
// Create MC Histogram
		mmgEBmc->fillHistogram(mmg_MC_hist, RooArgList(mmgMC));
		kEBmc->fillHistogram(k_MC_hist, RooArgList(kMC));
		sEBmc->fillHistogram(s_MC_hist, RooArgList(sMC));
// Fit MC histogram
		mmg_MC_hist->Fit("gaus", "Q0");
		k_MC_hist->Fit("gaus", "Q0");
		s_MC_hist->Fit("gaus", "Q0");
		TF1* fit_mmg = mmg_MC_hist->GetFunction("gaus");
		TF1* fit_k = k_MC_hist->GetFunction("gaus");
		TF1* fit_s = s_MC_hist->GetFunction("gaus");
// Loop over data points
		int dataEntries_mmg = mmgEBdata->numEntries();
		int dataEntries_k = kEBdata->numEntries();
		int dataEntries_s = sEBdata->numEntries();
		for(int idata = 0 ; idata < dataEntries_mmg ; idata++ )
		{
			RooArgSet* temp = mmgEBdata->get(idata);
			likelihood_mmg = mmg_MC_hist->Interpolate(temp->getRealValue("mmgData"));
			if (likelihood_mmg <= 0.0) likelihood_mmg = fit_mmg.Eval(temp->getRealValue("mmgData"));
			sum_mmg -= log(likelihood_mmg);
		}
		for(int idata = 0 ; idata < dataEntries_k ; idata++ )
		{
			RooArgSet* temp = kEBdata->get(idata);
			likelihood_k = k_MC_hist->Interpolate(temp->getRealValue("kData"));
			if (likelihood_k <= 0.0) likelihood_k = fit_k.Eval(temp->getRealValue("kData"));
			sum_k -= log(likelihood_k);
		}
		for(int idata = 0 ; idata < dataEntries_s ; idata++ )
		{
			RooArgSet* temp = sEBdata->get(idata);
			likelihood_s = s_MC_hist->Interpolate(temp->getRealValue("sData"));
			if (likelihood_s <= 0.0) likelihood_s = fit_s.Eval(temp->getRealValue("sData"));
			sum_s -= log(likelihood_s);
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
		cout << s_alpha << "\t" << sum_mmg << endl;
//		LL_mmg->Fill(s_alpha, -(mmgEBnll->getVal()));
		LL_mmg->Fill(s_alpha, sum_mmg);
//		cout << alpha << "\t" << -(kEBnll->getVal()) << endl;
		cout << alpha << "\t" << sum_k << endl;
//		LL->Fill(alpha, -(kEBnll->getVal()));
		LL->Fill(alpha, sum_k);
//		cout << s_alpha << "\t" << -(sEBnll->getVal()) << endl;
		cout << s_alpha << "\t" << sum_s << endl;
//		LL_s->Fill(s_alpha, -(sEBnll->getVal()));
		LL_s->Fill(s_alpha, sum_s);
//		th2->Fill(alpha, (sEBnll->getVal()));

	} // end of loop over ikin

// Draw nll
	TCanvas *cLL = new TCanvas("cLL", "cLL");
	LL->Draw("E1");
	TF1 *p2kfit = new TF1("p2kfit","pol2", 0.95, 1.05);
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
	TF1 *p2sfit = new TF1("p2sfit","pol2", -5.0, -5.0);
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
//	th2->Draw();
	cLL_s->Draw();
	cLL_s->Print("LL_s.gif");


	TCanvas *cLL_mmg = new TCanvas("cLL_mmg", "cLL_mmg");
	LL_mmg->Draw("E1");
	TF1 *p2mmgfit = new TF1("p2mmgfit","pol2", -5.0, -5.0);
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
	cout << "scale=\t" << (double)(- p1_mmg) / (double)(2 * p2_mmg) << endl;
	if(p2_mmg >= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(2 * p2_mmg) ) << endl;
	if(p2_mmg <= 0.0)	cout << "sigma=\t" << (double)(1.0) / (double)( sqrt(-2 * p2_mmg) ) << endl;
//	th2->Draw();
	cLL_mmg->Draw();
	cLL_mmg->Print("LL_mmg.gif");

}

