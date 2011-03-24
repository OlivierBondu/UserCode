{
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
#include <iomanip>
#include <sstream>
#include <TLatex.h>
#include <THStack.h>
#include <TLegendEntry.h>
#include <TMinuit.h>
#include <TPaveStats.h>


gROOT->Reset();

#include "CMSStyle.C"

#pragma optimize 0
using namespace std;

gROOT->ProcessLine(".x setTDRStyle.C");
CMSstyle();
gStyle->SetOptTitle(0);
gStyle->SetOptStat(1000000001);

TTree *MC_scale = new TTree ("scale", "Information for each injected scale measurement");

//MC_scale->ReadFile("mc.raw", "Gnumber/I:estimatorName/C:category/C:Nevents/I:chi2/F:constant/F:deltaConstant/F:estimator/F:deltaEstimator/F:deltaEstimator_estimator/F:sigma/F:deltaSigma/F:deltaSigma_sigma/F");
//MC_scale->ReadFile("mc.raw2", "Gnumber/I:estimatorName/I:category/C:Nevents/I:chi2/F:constant/F:deltaConstant/F:estimator/F:deltaEstimator/F:deltaEstimator_estimator/F:sigma/F:deltaSigma/F:deltaSigma_sigma/F");
//MC_scale->ReadFile("mc.raw3", "Gnumber/I:estimatorName/I:category/I:Nevents/I:chi2/F:constant/F:deltaConstant/F:estimator/F:deltaEstimator/F:deltaEstimator_estimator/F:sigma/F:deltaSigma/F:deltaSigma_sigma/F");
MC_scale->ReadFile("mc_k_scale.RAW", "k_inj/F:k_meas/F:k_meas_err/F:category/I");

TCanvas c1;
TH2F *h2_scale_temp = new TH2F();
//TH2F *h2_scale_temp_EB = new TH2F();
//TH2F *h2_scale_temp_EE = new TH2F();
//TH2F *h2_scale_error_temp = new TH2F();
////TH2F *h2_scale_error_temp_EB = new TH2F();
MC_scale->Draw("k_meas:k_inj>>h2_scale_temp(200,0.94,1.06,200,0.94,1.06)", "category==0");
//MC_scale->Draw("k_meas:k_inj>>h2_scale_temp_EB(200,0.94,1.06,200,0.94,1.06)", "category==1");
//MC_scale->Draw("k_meas:k_inj>>h2_scale_temp_EE(200,0.94,1.06,200,0.94,1.06)", "category==2");
//gPad->Update();
//h2_scale_temp->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale_temp->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h2_scale_temp->Draw();
//h2_scale_temp->Draw("sames");
//h2_scale_temp_EB->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale_temp_EB->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h2_scale_temp_EE->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale_temp_EE->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//gPad->Update();
//MC_scale->Draw("k_meas_err:k_inj>>h2_scale_error_temp(200,0.0012,0.0015,200,0.94,1.06)", "category==0");
////MC_scale->Draw("k_meas_err:k_inj>>h2_scale_error_temp_EB(200,0.0012,0.0015,200,0.94,1.06)", "category==1");



TH2F *h2_scale = (TH2F*)gDirectory->Get("h2_scale_temp");
//TH2F *h2_scale_EB = (TH2F*)gDirectory->Get("h2_scale_temp_EB");
//TH2F *h2_scale_EE = (TH2F*)gDirectory->Get("h2_scale_temp_EE");
//h2_scale->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h2_scale_EB->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale_EB->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h2_scale_EE->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale_EE->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//TH2F *h2_scale_error = (TH2F*)gDirectory->Get("h2_scale_error_temp");
////TH2F *h2_scale_error_EB = (TH2F*)gDirectory->Get("h2_scale_error_temp_EB");
//h2_scale->Sumw2();
//h2_scale_EB->Sumw2();
//h2_scale_EE->Sumw2();
//h2_scale_error->Sumw2();
////h2_scale_error_EB->Sumw2();
//h2_scale->Draw();


//h2_scale->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h2_scale_EB->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale_EB->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h2_scale_EE->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale_EE->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");


//TCanvas c2;
//h2_scale_error->Draw();


//TCanvas c3;
TProfile* h2_scale_profile = (TProfile*)h2_scale->ProfileX();
//TProfile* h2_scale_profile_EB = (TProfile*)h2_scale_EB->ProfileX();
//TProfile* h2_scale_profile_EE = (TProfile*)h2_scale_EE->ProfileX();
//TProfile* h2_scale_error_profile = (TProfile*)h2_scale_error->ProfileX();


//h2_scale_profile->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale_profile->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h2_scale_profile_EB->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale_profile_EB->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h2_scale_profile_EE->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale_profile_EE->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//gPad->Update();
//cout << "h2_scale_error_profile->GetNbinsX()= " << h2_scale_error_profile->GetNbinsX() << endl;

//Double_t error[h2_scale_error_profile->GetNbinsX() + 1];
//for(int i = 0 ;  i < h2_scale_error_profile->GetNbinsX() ; i++){
//	h2_scale_profile->GetXaxis()->SetBinLabel(i+1, label[i]);
//	cout << "h2_scale_error_profile->GetBinContent(i+1)= " << h2_scale_error_profile->GetBinContent(i+1) << endl;
////	error[i+1] = h2_scale_error_profile->GetBinContent(i+1);
//	h2_scale_profile->SetBinError(i+1, i+1);
//	h2_scale_profile->SetBinError(i+1, h2_scale_error_profile->GetBinContent(i+1));
//}
//h2_scale_profile->SetError(error);
//h2_scale_profile->Draw();

//TCanvas c4;
TH1D *h1_scale = h2_scale_profile->ProjectionX();
//TH1D *h1_scale_EB = h2_scale_profile_EB->ProjectionX();
//TH1D *h1_scale_EE = h2_scale_profile_EE->ProjectionX();
/*
h1_scale->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
h1_scale->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
h1_scale->Draw();
*/
//h1_scale_EB->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h1_scale_EB->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h1_scale_EE->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h1_scale_EE->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//cout << "h1_scale->GetNbinsX()= " << h1_scale->GetNbinsX() << endl;
//h1_scale->SetError(error);
//for(int i=0 ; i < h1_scale->GetNbinsX(); i++)
//{
////	h1_scale->SetBinError(i+1,error[i+1]);
//}

//gPad->Clear();

//// EE
//gPad->Update();
//h1_scale_EE->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h1_scale_EE->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");

//h1_scale_EE->SetMarkerColor(kBlue);
//h1_scale_EE->SetMaximum(1.06);
//h1_scale_EE->SetMinimum(0.94);
//h1_scale_EE->SetName("EE");
//h1_scale_EE->Draw("E1sames");
//TF1* f_EE = new TF1("f_EE", "pol1",  h1_scale_EE->GetXaxis()->GetXmin(), h1_scale_EE->GetXaxis()->GetXmax());
//f_EE->SetLineWidth(1);
//f_EE->SetLineColor(kBlue);
//f_EE->SetParameter(1,1);
//f_EE->SetParameter(0,0);
//h1_scale_EE->Fit("f_EE", "RB+", "sames");
//h1_scale_EE->Draw("E1sames");
//gPad->Update();

//TPaveStats* statsh1_scale_EE = (TPaveStats*) h1_scale_EE->GetListOfFunctions()->FindObject("stats");
//statsh1_scale_EE->SetName("statsh1_scale_EE");
//statsh1_scale_EE->SetShadowColor(0);
//statsh1_scale_EE->SetLineColor(kBlue);
//statsh1_scale_EE->SetTextColor(kBlue);
//statsh1_scale_EE->SetX1NDC(0.68);
//statsh1_scale_EE->SetX2NDC(0.93);
//statsh1_scale_EE->SetY1NDC(0.20);
//statsh1_scale_EE->SetY2NDC(0.33);
//statsh1_scale_EE->Draw("sames");
//gPad->Update();

//// EB
//h1_scale_EB->SetMarkerColor(kGreen+3);
//h1_scale_EB->SetMaximum(1.06);
//h1_scale_EB->SetMinimum(0.94);
//h1_scale_EB->SetName("EB");
//h1_scale_EB->Draw("E1sames");
//TF1* f_EB = new TF1("f_EB", "pol1",  h1_scale_EB->GetXaxis()->GetXmin(), h1_scale_EB->GetXaxis()->GetXmax());
//f_EB->SetLineWidth(1);
//f_EB->SetLineColor(kGreen+3);
//f_EB->SetParameter(1,1);
//f_EB->SetParameter(0,0);
//h1_scale_EB->Fit("f_EB", "RB+", "sames");
//h1_scale_EB->Draw("E1sames");

//gPad->Update();
//TPaveStats* statsh1_scale_EB = (TPaveStats*) h1_scale_EB->GetListOfFunctions()->FindObject("stats");
//statsh1_scale_EB->SetShadowColor(0);
//statsh1_scale_EB->SetName("statsh1_scale_EB");
//statsh1_scale_EB->SetLineColor(kGreen+3);
//statsh1_scale_EB->SetTextColor(kGreen+3);
//statsh1_scale_EB->SetX1NDC(0.68);
//statsh1_scale_EB->SetX2NDC(0.93);
//statsh1_scale_EB->SetY1NDC(0.34);
//statsh1_scale_EB->SetY2NDC(0.47);
//statsh1_scale_EB->Draw("sames");

//gPad->Update();

////// EB +EE 
//h1_scale->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h1_scale->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
h1_scale->SetMaximum(1.06);
h1_scale->SetMinimum(0.94);
//h1_scale->Draw("E1sames");
//h1_scale->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h1_scale->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");


TF1* f = new TF1("f", "pol1",  h1_scale->GetXaxis()->GetXmin(), h1_scale->GetXaxis()->GetXmax());
f->SetLineWidth(1);
f->SetParameter(1,1);
f->SetParameter(0,0);
h1_scale->Fit("f", "RB+", "sames");
h1_scale->SetName("EB+EE");
h1_scale->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
h1_scale->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h1_scale->Draw("E1sames");
h1_scale->Draw("E1");


gPad->Update();
TPaveStats* statsh1_scale = (TPaveStats*) h1_scale->GetListOfFunctions()->FindObject("stats");
statsh1_scale->SetShadowColor(0);
statsh1_scale->SetName("statsh1_scale");
statsh1_scale->SetX1NDC(0.68);
statsh1_scale->SetX2NDC(0.93);
statsh1_scale->SetY1NDC(0.48);
statsh1_scale->SetY2NDC(0.61);
statsh1_scale->Draw("sames");

//h1_scale->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h1_scale->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h1_scale->Draw("E1sames");

/*
   TIter next(gDirectory->GetList());
   TObject *obj;
   while ((obj=next())) {
      if (obj->InheritsFrom("TH1")) {
         TH1 *h = (TH1*)obj;
         h->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
         h->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
      }
   }
   TIter next(gDirectory->GetList());
   TObject *obj;
   while ((obj=next())) {
      if (obj->InheritsFrom("TProfile")) {
         TH1 *h = (TH1*)obj;
         h->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
         h->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
      }
   }

   TIter next(gDirectory->GetList());
   TObject *obj;
   while ((obj=next())) {
      if (obj->InheritsFrom("TH2F")) {
         TH1 *h = (TH1*)obj;
         h->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
         h->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
      }
   }


   TIter next(gDirectory->GetList());
   TObject *obj;
   while ((obj=next())) {
      if (obj->InheritsFrom("TH1D")) {
         TH1 *h = (TH1*)obj;
         h->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
         h->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
      }
   }
*/
/*
c1->Modified();
gPad->Modified();
gPad->Update();
h2_scale_temp->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
h2_scale_temp->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h2_scale_temp_EB->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale_temp_EB->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
//h2_scale_temp_EE->GetYaxis()->SetTitle("(E_{measured}/E_{muons})_{measured}");
//h2_scale_temp_EE->GetXaxis()->SetTitle("(E_{measured}/E_{muons})_{injected}");
gPad->Update();
*/

//c1->Print("kmeasVSkinj.eps");
//c1->Print("kmeasVSkinj.pdf");
//c1->Print("kmeasVSkinj.gif");
//c1->Print("kmeasVSkinj.C");


//TProfile* h2_scale_profile_temp = new TProfile(h2_scale->ProfileX());
//h2_scale->ProfileX()->Draw();
//h2_scale->ProjectionY()->Draw();
//h2_scale->

}
