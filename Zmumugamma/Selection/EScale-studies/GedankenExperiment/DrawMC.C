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
#include <TF2.h>
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
#include <THStack.h>
#include <TLegendEntry.h>
#include <TMinuit.h>
#include <TPaveStats.h>

#include "DrawMC.h"


using namespace std;

void DrawMCplot(TTree *FSR_DYToMuMu_powheg_miniTree, string var, string pic, string limits, string cut, string name, string Title, bool inlog, bool drawUnderOverFsubleading, TCanvas *c1, bool doFit){

	bool doData = true;

  // Get Histo_FSR_DYToMuMu_powheg from eventTree
  TH1F *Histo_FSR_DYToMuMu_powheg_temp = new TH1F();
  string variable_FSR_DYToMuMu_powheg = var + ">>Histo_FSR_DYToMuMu_powheg_temp" + limits;
  FSR_DYToMuMu_powheg_miniTree->Draw(variable_FSR_DYToMuMu_powheg.c_str(), cut.c_str());
  TH1F *Histo_FSR_DYToMuMu_powheg = (TH1F*)gDirectory->Get("Histo_FSR_DYToMuMu_powheg_temp");
  c1->Clear();
  // TODO: implement drawUnderOverFsubleading

  // Get the number of entries for further normalization
/*
  double b_PhotonJet_Pt15 = Histo_PhotonJet_Pt15->Integral();
  if( (a==0.0) || (b_PhotonJet_Pt15==0.0) ){
    cout << "no entries to plots" <<endl;
    return; 
  }*/
  // Normalize
  // // Normalize MC and Data to 1
  //Histo_Data->Scale((double)((double)1.0/(double)a));
  //Histo_MC->Scale((double)((double)1.0/(double)b));
  // // Normalize MC to Data number of entries
	double integratedLuminosity;
  if(doData) integratedLuminosity = 35.91246801;
	else integratedLuminosity = (1958953.0) / (1614.0);

  double XSectionFSR_DYToMuMu_powheg = 1614.0;

  double InitialNumberFSR_DYToMuMu_powheg = 1998931;

  // Adding histograms for binned samples

  // Get the maxs and the mins to further correct the Y-axis
  double YMax;
  double FSR_DYToMuMu_powhegMax = Histo_FSR_DYToMuMu_powheg->GetMaximum();
  YMax = FSR_DYToMuMu_powhegMax;

//	double allMCMax = Histo_allMC->GetMaximum();
//	YMax = max(YMax, allMCMax);

  double FSR_DYToMuMu_powhegMin = YMax;

  double YMin = YMax;

  // Gets the actual minimum for each histogram, and not the unfilled bin if any
  for( int ibin=1 ; ibin<Histo_FSR_DYToMuMu_powheg->GetNbinsX() ; ibin++ ){
    if( ((Histo_FSR_DYToMuMu_powheg->GetBinContent(ibin))!=0) && ((Histo_FSR_DYToMuMu_powheg->GetBinContent(ibin))<FSR_DYToMuMu_powhegMin) ){
      FSR_DYToMuMu_powhegMin = Histo_FSR_DYToMuMu_powheg->GetBinContent(ibin);
    }
  }
  YMin = min(YMin, FSR_DYToMuMu_powhegMin);
  
//  cout << "YMax= "<< YMax << "\t\tYMin= " << YMin << endl;
  double YMin_lin = (double)YMin / (double)10.0;
//  double Range_lin = ((double)(YMax - YMin_lin)) / ((double)(0.8));
  double Range_lin = ((double)(YMax - YMin_lin)) / ((double)(1.0));
  double YMax_lin = 0.2*Range_lin + YMax;
/*
  double Range_lin = ((double)(YMax - YMin)) / ((double)(0.77));
  double YMax_lin = 0.2*Range_lin + YMax;
  double YMin_lin = max(YMin - 0.03*Range_lin, (double)YMin / (double)10.0);
*/
  double Range_log = ((double)(log10(YMax) - log10(YMin))) / ((double)(0.77));
//  cout << "Range_lin= " << Range_lin << "\t\tRange_log= " << Range_log << endl;
  double YMax_log = pow(10.0, 0.2*Range_log + log10(YMax));
  double YMin_log = pow(10.0, log10(YMin) - 0.03*Range_log);
//  cout << "YMin_lin= " << YMin_lin << "\t\tYMax_lin= " << YMax_lin << endl;
//  cout << "YMin_log= " << YMin_log << "\t\tYMax_log= " << YMax_log << endl;


  // Setup the histo and canvas names and title
	string mc_name;
	string canvas_name;
	if( !doData){
	  mc_name = "MC_" + pic + "_" + name;
	  canvas_name = "MC_" + pic + "_" + name;
	} else {
		mc_name = "DATA_" + pic + "_" + name;
    canvas_name = "DATA_" + pic + "_" + name;
	}

  std::ostringstream binWidthOSS;
  binWidthOSS << (double)Histo_FSR_DYToMuMu_powheg->GetBinWidth(1);
  string binWidth = binWidthOSS.str();
  string YaxisTitle = "";
  if((Title.rfind("(") < Title.size()) && (Title.rfind(")") < Title.size())){
    string unit = Title.substr(Title.rfind("(")+1, Title.size()-Title.rfind("(")-2);
    YaxisTitle = "Events / ( " + binWidth + " " + unit + " )";
  } else {
    YaxisTitle = "Events / ( " + binWidth + " )";
  }
  Histo_FSR_DYToMuMu_powheg->SetName(mc_name.c_str());
  c1->SetName(canvas_name.c_str());
  c1->SetTitle(canvas_name.c_str());

  // Draw the comparison plots
  TLegend *legend = new TLegend(0.65, 0.80, 0.90, 0.93, "");
	if( doFit ){
/*
		legend->SetX1(0.47);
		legend->SetX2(0.65);
*/
		legend->SetX1(0.15);
		legend->SetX2(0.40);
		legend->SetY1(0.65);
		legend->SetY2(0.78);

	}
	legend->SetTextSize(0.025);
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kWhite);
  legend->SetShadowColor(kWhite);

  // // First: draw the data to get correct Y-axis scale
	gPad->Update();
  Histo_FSR_DYToMuMu_powheg->GetXaxis()->SetTitle(Title.c_str());
  Histo_FSR_DYToMuMu_powheg->GetYaxis()->SetTitle(YaxisTitle.c_str());
  Histo_FSR_DYToMuMu_powheg->SetLineColor(kBlack);
	if(!doData){
	  Histo_FSR_DYToMuMu_powheg->SetFillColor(kRed);
		Histo_FSR_DYToMuMu_powheg->SetFillStyle(3001);
	} else {
	  Histo_FSR_DYToMuMu_powheg->SetMarkerColor(kBlack);
	  Histo_FSR_DYToMuMu_powheg->SetMarkerSize(0.7);
	  Histo_FSR_DYToMuMu_powheg->SetMarkerStyle(20);
	}
  Histo_FSR_DYToMuMu_powheg->SetMaximum(YMax_lin);
  Histo_FSR_DYToMuMu_powheg->SetMinimum(YMin_lin);

	if(!doData){
	gStyle->SetOptTitle(0);
	  Histo_FSR_DYToMuMu_powheg->Draw();
  	legend->AddEntry(Histo_FSR_DYToMuMu_powheg->GetName(), "MC Z#mu#muJet FSR", "f");
	} else {
	gStyle->SetOptTitle(0);
	  Histo_FSR_DYToMuMu_powheg->Draw("E1");
//  	legend->AddEntry(Histo_FSR_DYToMuMu_powheg->GetName(), "DATA", "lp");
	}
//  legend->AddEntry(Histo_FSR_DYToMuMu_powheg->GetName(), "Data", "lp");

	double f_min, f_max;
	f_min = (Histo_FSR_DYToMuMu_powheg->GetMean()) - 4*(Histo_FSR_DYToMuMu_powheg->GetRMS());
	f_max = (Histo_FSR_DYToMuMu_powheg->GetMean()) + 4*(Histo_FSR_DYToMuMu_powheg->GetRMS());
	TF1* f_MC = new TF1("f_MC", "gaus(0)", f_min, f_max);

if( doFit ){
	if(!doData){
		Histo_FSR_DYToMuMu_powheg->SetName("MC");
	} else {
		Histo_FSR_DYToMuMu_powheg->SetName("DATA");
	}
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	string fitOpts = "MQ+";

//	TF1* f_Data = new TF1("f_Data", "gaus");
//	TF1* f_MC = new TF1("f_MC", "gaus");
//	double f_min, f_max;
//	f_min = (Histo_FSR_DYToMuMu_powheg->GetMean()) - 4*(Histo_FSR_DYToMuMu_powheg->GetRMS());
//	f_max = (Histo_FSR_DYToMuMu_powheg->GetMean()) + 4*(Histo_FSR_DYToMuMu_powheg->GetRMS());
//	TF1* f_MC = new TF1("f_MC", "TMath::Gaus(x, [1], [2])", f_min, f_max);
//	TF1* f_MC = new TF1("f_MC", "gaus(0)", f_min, f_max);
	cout
	<< "Histo_FSR_DYToMuMu_powheg->GetMean()= " << Histo_FSR_DYToMuMu_powheg->GetMean() << endl
	<< "Histo_FSR_DYToMuMu_powheg->GetRMS()= " << Histo_FSR_DYToMuMu_powheg->GetRMS() << endl
	<< "f_min= " << f_min << endl
	<< "f_max= " << f_max << endl
	<< endl;
	f_MC->SetParameter(1, Histo_FSR_DYToMuMu_powheg->GetMean());
	f_MC->SetParameter(2, Histo_FSR_DYToMuMu_powheg->GetRMS());
	if(!doData){
		f_MC->SetLineColor(kGreen+2);
	} else {
		f_MC->SetLineColor(kBlue);
	}
//	f_Data->SetLineWidth(2);
	f_MC->SetLineWidth(2);
//	Histo_Data->Fit("f_Data", fitOpts.c_str());
	double epsilon = 100;
	Histo_FSR_DYToMuMu_powheg->Fit("f_MC", fitOpts.c_str());
	cout << "\tvar"
	<< "\tcut"
	<< "\tevts"
	<< "\tCHI2/NDF"
	<< "\tconstant\terror"
	<< "\tmean\terror"
	<< "\tdeltamean/mean"
	<< "\tsigma\terror"
	<< "\tdeltasigma/sigma"
	<< endl;
	if(!doData){
		cout << "MC:" << endl;
	} else {
		cout << "DATA:" << endl;
	}
	cout << "\t" << pic
	<< "\t" << name
	<< "\t" << Histo_FSR_DYToMuMu_powheg->GetEntries()
	<< "\t" << ((double)f_MC->GetChisquare()/(double)f_MC->GetNDF())
	<< "\t" << f_MC->GetParameter(0) << " \\pm " << f_MC->GetParError(0)
	<< "\t" << f_MC->GetParameter(1) << " \\pm " << f_MC->GetParError(1)
	<< "\t" << (double)(f_MC->GetParError(1))/(double)(f_MC->GetParameter(1))
	<< "\t" << f_MC->GetParameter(2) << " \\pm " << f_MC->GetParError(2)
	<< "\t" << (double)(f_MC->GetParError(2))/(double)(f_MC->GetParameter(2))
	<< endl;
	double sigma = f_MC->GetParameter(2);
	while( epsilon > 0.001 )
	{
	f_min = (f_MC->GetParameter(1)) - 4 * (f_MC->GetParameter(2));
	f_max = (f_MC->GetParameter(1)) + 4 * (f_MC->GetParameter(2));
	cout
	<< "f_min= " << f_min << endl
	<< "f_max= " << f_max << endl;
	f_MC->SetRange(f_min, f_max);
	Histo_FSR_DYToMuMu_powheg->Fit("f_MC", fitOpts.c_str());
	cout << "\tvar"
	<< "\tcut"
	<< "\tevts"
	<< "\tCHI2/NDF"
	<< "\tconstant\terror"
	<< "\tmean\terror"
	<< "\tdeltamean/mean"
	<< "\tsigma\terror"
	<< "\tdeltasigma/sigma"
	<< endl;
	if(!doData){
		cout << "MC:" << endl;
	} else {
		cout << "DATA:" << endl;
	}
	cout << "\t" << pic
	<< "\t" << name
	<< "\t" << Histo_FSR_DYToMuMu_powheg->GetEntries()
	<< "\t" << ((double)f_MC->GetChisquare()/(double)f_MC->GetNDF())
	<< "\t" << f_MC->GetParameter(0) << " \\pm " << f_MC->GetParError(0)
	<< "\t" << f_MC->GetParameter(1) << " \\pm " << f_MC->GetParError(1)
	<< "\t" << (double)(f_MC->GetParError(1))/(double)(f_MC->GetParameter(1))
	<< "\t" << f_MC->GetParameter(2) << " \\pm " << f_MC->GetParError(2)
	<< "\t" << (double)(f_MC->GetParError(2))/(double)(f_MC->GetParameter(2))
	<< endl;
	epsilon = fabs(sigma - (f_MC->GetParameter(2)));
	cout << "epsilon= " << epsilon << endl;
	sigma = f_MC->GetParameter(2);
	}	

	Histo_FSR_DYToMuMu_powheg->SetMaximum(YMax_lin);
	Histo_FSR_DYToMuMu_powheg->SetMinimum(YMin_lin);	
  if(!doData){
	gStyle->SetOptTitle(0);
		Histo_FSR_DYToMuMu_powheg->Draw("sames");
	} else {
//	gStyle->SetOptTitle(0);
	  Histo_FSR_DYToMuMu_powheg->Draw("E1");
//	  Histo_FSR_DYToMuMu_powheg->Draw("E1sames");
	}

	gPad->Update();

/*	TPaveStats* statsHisto_FSR_DYToMuMu_powheg = (TPaveStats*) Histo_FSR_DYToMuMu_powheg->GetListOfFunctions()->FindObject("stats");
	if(!doData){
		statsHisto_FSR_DYToMuMu_powheg->SetLineColor(kGreen+2);
		statsHisto_FSR_DYToMuMu_powheg->SetTextColor(kGreen+2);
	} else {
		statsHisto_FSR_DYToMuMu_powheg->SetLineColor(kWhite);
//		statsHisto_FSR_DYToMuMu_powheg->SetLineColor(kBlue);
//		statsHisto_FSR_DYToMuMu_powheg->SetTextColor(kBlue);
	}
	statsHisto_FSR_DYToMuMu_powheg->SetTextSize(0.020);
	statsHisto_FSR_DYToMuMu_powheg->SetX1NDC(0.68);
	statsHisto_FSR_DYToMuMu_powheg->SetX2NDC(0.93);
	statsHisto_FSR_DYToMuMu_powheg->SetY1NDC(0.67);
	statsHisto_FSR_DYToMuMu_powheg->SetY2NDC(0.80);
	statsHisto_FSR_DYToMuMu_powheg->Draw();

//	c1->Update();	
*/
}
  // // Fourth: redraw axis so that axis appears in front of everything
  gPad->RedrawAxis();

  // // Fifth: draw legend
//  legend->Draw();
	c1->Update();

  TLatex latexLabel;
  latexLabel.SetNDC();
  std::ostringstream intLumiString;
  intLumiString << setprecision (2) << fixed << integratedLuminosity;
  string intLumiText = "DATA #int L dt= " + intLumiString.str() + " pb^{-1}";
  latexLabel.SetTextSize(0.05);
	latexLabel.DrawLatex(0.65, 0.88, name == "EB" ? "ECAL Barrel" : "ECAL Endcaps");
	latexLabel.SetTextSize(0.03);
	latexLabel.DrawLatex(0.13, 0.96, "CMS Preliminary 2010");
	latexLabel.DrawLatex(0.42, 0.96, "#sqrt{s} = 7 TeV");
	latexLabel.DrawLatex(0.57, 0.96, intLumiText.c_str());
//  latexLabel.DrawLatex(0.18, 0.90, "CMS Preliminary 2010");
//  latexLabel.DrawLatex(0.18, 0.86, "#sqrt{s} = 7 TeV");
//  latexLabel.DrawLatex(0.16, 0.82, intLumiText.c_str());
	double position = 0.92;
	position -= 0.04;
	string text;
	std::ostringstream valueStream[4];
	
// = "Entries: " + Histo_FSR_DYToMuMu_powheg->GetEntries();
	
	latexLabel.DrawLatex(0.20, position, Form("Entries: %i", (int)Histo_FSR_DYToMuMu_powheg->GetEntries()));
	position -= 0.04;
	latexLabel.DrawLatex(0.20, position, "Fit: Gaussian, binned");
	position -= 0.04;
	valueStream[0] << setprecision (3) << "Constant = " << (double)f_MC->GetParameter(0) << " +- " << (double)f_MC->GetParError(0);
	text=valueStream[0].str();
	latexLabel.DrawLatex(0.20, position, text.c_str());
	position -= 0.04;
	valueStream[1] << setprecision (3) << "Mean = " << (double)f_MC->GetParameter(1) << " +- " << (double)f_MC->GetParError(1);
	text=valueStream[1].str();
  latexLabel.DrawLatex(0.20, position, text.c_str());	
	position -= 0.04;
	valueStream[2] << setprecision (3) << "#sigma = " << (double)f_MC->GetParameter(2) << " +- " << (double)f_MC->GetParError(2);
  text=valueStream[2].str();
  latexLabel.DrawLatex(0.20, position, text.c_str());
	position -= 0.04;
	valueStream[3] << setprecision (4) << "#chi^{2} / ndf = " << (double)((double)f_MC->GetChisquare()/(double)f_MC->GetNDF());
	text=valueStream[3].str();
  latexLabel.DrawLatex(0.20, position, text.c_str());

  // // Sixth: update canvas
  c1->Update();
  c1->Draw();

  // Print the canvas
  string PicName;
	if(!doData){
	  PicName="gif/MC_" + pic + "_" + name + ".gif";
	} else {
	  PicName="gif/Data_" + pic + "_" + name + ".gif";
	}
  c1->Print(PicName.c_str());
	if(!doData){
	  PicName="png/MC_" + pic + "_" + name + ".png";
	} else {
	  PicName="png/Data_" + pic + "_" + name + ".png";
	}
  c1->Print(PicName.c_str());
	if(!doData){
	  PicName="C/MC_" + pic + "_" + name + ".C";
	} else {
	  PicName="C/Data_" + pic + "_" + name + ".C";
	}
  c1->Print(PicName.c_str());
	if(!doData){
  	PicName="eps/MC_" + pic + "_" + name + ".eps";
	} else {
  	PicName="eps/DATA_" + pic + "_" + name + ".eps";
	}
  c1->Print(PicName.c_str());
  string convert;
  if(!doData){
		convert = "convert eps/MC_" + pic + "_" + name + ".eps" + " pdf/MC_" + pic + "_" + name + ".pdf";
	} else {
		convert = "convert eps/DATA_" + pic + "_" + name + ".eps" + " pdf/DATA_" + pic + "_" + name + ".pdf";
	}
  system(convert.c_str());
  if (inlog==true) {
    c1->cd(1);
    Histo_FSR_DYToMuMu_powheg->SetMaximum(YMax_log);
    Histo_FSR_DYToMuMu_powheg->SetMinimum(YMin_log);
    Histo_FSR_DYToMuMu_powheg->GetYaxis()->SetRangeUser(YMin_log, YMax_log);
    c1->SetLogy(1);
    c1->Update();
    c1->Draw();
		string PicName_log;
	  if(!doData){
  	  PicName_log="gif/MC_" + pic + "_" + name + "_log.gif";
		} else {
  	  PicName_log="gif/DATA_" + pic + "_" + name + "_log.gif";
		}
    c1->Print(PicName_log.c_str());
	  if(!doData){
  	  PicName_log="C/MC_" + pic + "_" + name + "_log.C";
		} else {
  	  PicName_log="C/DATA_" + pic + "_" + name + "_log.C";
		}
    c1->Print(PicName_log.c_str());
	  if(!doData){
  	  PicName_log="png/MC_" + pic + "_" + name + "_log.png";
		} else {
  	  PicName_log="png/DATA_" + pic + "_" + name + "_log.png";
		}
    c1->Print(PicName_log.c_str());
	  if(!doData){
  	  PicName="eps/MC_" + pic + "_" + name + "_log.eps";
		} else {
  	  PicName="eps/DATA_" + pic + "_" + name + "_log.eps";
		}
    c1->Print(PicName.c_str());
		string convert;
	  if(!doData){
  	  convert = "convert eps/MC_" + pic + "_" + name + "_log.eps" + " pdf/MC_" + pic + "_" + name + "_log.pdf";
		} else {
  	  convert = "convert eps/DATA_" + pic + "_" + name + "_log.eps" + " pdf/DATA_" + pic + "_" + name + "_log.pdf";
		}
    system(convert.c_str());
    c1->SetLogy(0);
    c1->Update();
  }

  // Clean the memory
  c1->Clear();
  legend->Clear();
//	Histo_template->Delete();
  Histo_FSR_DYToMuMu_powheg_temp->Delete();
  Histo_FSR_DYToMuMu_powheg->Delete();
}







