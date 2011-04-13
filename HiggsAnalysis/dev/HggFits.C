// Compillation:  .L runfits.C+
// Running:       .L runfits_C.so  
//                runfits()



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
#include "CMSStyle.C"
gROOT->Reset();

// RooStats headers
//#include "RooStats/HLFactory.h"

void HggFits(){

	CMSstyle();
  using namespace RooFit;

  TFile* file_GGFusion = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105_new/DiphotonTree_MC_PowhegHgg120GluonFusion_noNNcut.root");
  TFile* file_VBF = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105_new/DiphotonTree_MC_PowhegHgg110BVF_noNNcut.root");
  TFile* file_AssocProd = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105_new/DiphotonTree_MC_PythiaHgg120WHZHTTH_noNNcut.root");
  
  TTree* Tree_GGFusion = (TTree*) file_GGFusion->Get("Tree");
  TTree* Tree_VBF = (TTree*) file_VBF->Get("Tree");
  TTree* Tree_AssocProd = (TTree*) file_AssocProd->Get("Tree");

  //RooRealVar weightGGFusion("weightGGFusion","weightGGFusion", 1.56 * 0.0244 / 109992.0);
  //RooRealVar weightVBF("weightVBF","weightVBF", 0.00290 / 109842.0);
  //RooRealVar weightAssocProd("weightAssocProd","weightAssocProd", 0.00242 / 110000.0);
  
  RooRealVar dipho_costhetastar("dipho_costhetastar","cos(#theta^{*})",0,1,"");
  RooRealVar dipho_qt("dipho_qt","p_{T,#gamma#gamma}",0,200,"GeV");
  RooRealVar phoNNmin_MLPoutputClusterShapeEnv("phoNNmin_MLPoutputClusterShapeEnv","NNoutput_{min}",-1.2,1.2);
  RooRealVar dipho_highestpt_mgg("dipho_highestpt_mgg","M_{#gamma#gamma}",100,140,"GeV");
  RooCategory dipho_cat4("dipho_cat4","dipho_cat4");
  dipho_cat4.defineType("cat4_0",0);
  dipho_cat4.defineType("cat4_1",1);
  dipho_cat4.defineType("cat4_2",2);
  dipho_cat4.defineType("cat4_3",3);
  RooRealVar dipho_Xsection("dipho_Xsection","dipho_Xsection",1,0,10000000,"");
  RooArgSet ntplVars(dipho_highestpt_mgg, dipho_qt, dipho_costhetastar, phoNNmin_MLPoutputClusterShapeEnv, dipho_cat4, dipho_Xsection);


  RooDataSet Data("Data","Data",Tree_GGFusion,ntplVars,"","dipho_Xsection");
  RooDataSet Data_VBF("Data_VBF","Data_VBF",Tree_VBF,ntplVars,"","dipho_Xsection");
  RooDataSet Data_AssocProd("Data_AssocProd","Data_AssocProd",Tree_AssocProd,ntplVars,"","dipho_Xsection");

  Data.append(Data_VBF);
  Data.append(Data_AssocProd);

  /*
  //RooRealVar* WeightGGFusion = (RooRealVar*) Data.addColumn(weightGGFusion);
  //Data.setWeightVar(weightGGFusion);
  //RooDataSet Data_weighted("Data_weighted","Data_weighted",Data,ntplVars,WeightVar("weightGGFusion"));

  return;

//Data.add(ntplVars, 1.56 * 0.0244 / 109992.0);
  RooDataSet Data_VBF("Data_VBF","Data_VBF",Tree_VBF,ntplVars);
  Data_VBF.add(ntplVars, 0.00290 / 109842.0);
  RooDataSet Data_AssocProd("Data_AssocProd","Data_AssocProd",Tree_AssocProd,ntplVars);
  Data_AssocProd.add(ntplVars, 0.00242 / 110000.0);

  Data.append(Data_VBF);
  Data.append(Data_AssocProd);
  */


  RooDataSet* Data_cat0 = Data.reduce("dipho_cat4==0");
  RooDataSet* Data_cat1 = Data.reduce("dipho_cat4==1");
  RooDataSet* Data_cat2 = Data.reduce("dipho_cat4==2");
  RooDataSet* Data_cat3 = Data.reduce("dipho_cat4==3");


/*
  
  //FITS  + PLOT cat0
  RooRealVar frac_cat0("frac_cat0","frac_cat0",0.5,0,1);
  
  RooRealVar mu_cat0("mu_cat0","mu_cat0",120,100,140);
  RooRealVar sigmagauss_cat0("sigmagauss_cat0","sigmagauss_cat0",2,0,10);
  RooGaussian Gauss_cat0("Gauss_cat0","Gauss_cat0",dipho_highestpt_mgg,mu_cat0,sigmagauss_cat0);

//  RooRealVar m0_cat0("m0_cat0","m0_cat0",120,100,140);  
  RooRealVar sigma_cat0("sigma_cat0","sigma_cat0",0,10);
  RooRealVar alpha_cat0("alpha_cat0","alpha_cat0",0,10);
  RooRealVar n_cat0("n_cat0","n_cat0",0,10);
//  RooCBShape CrystalBall_cat0("CrystalBall_cat0","CrystalBall_cat0", dipho_highestpt_mgg, m0_cat0, sigma_cat0, alpha_cat0, n_cat0);
  RooCBShape CrystalBall_cat0("CrystalBall_cat0","CrystalBall_cat0", dipho_highestpt_mgg, mu_cat0, sigma_cat0, alpha_cat0, n_cat0);

  RooAddPdf model_cat0("model_cat0","model_cat0",RooArgList(Gauss_cat0,CrystalBall_cat0),frac_cat0);
  
  TCanvas* Canvas0 = new TCanvas("Canvas0","Canvas0");
  model_cat0.fitTo(*Data_cat0);
  RooArgSet* params0 = model_cat0.getVariables();
  params0->Print("v");
  RooPlot* frame = dipho_highestpt_mgg.frame(Title("#gamma#gamma Invariant mass, cat0"));
  Data_cat0->plotOn(frame,Binning(40));
  //Gauss.plotOn(frame);
  //CrystalBall.plotOn(frame);
  model_cat0.plotOn(frame);
  model_cat0.plotOn(frame,Components("CrystalBall_cat0"),LineStyle(kDashed),LineColor(kRed));
  model_cat0.plotOn(frame,Components("Gauss_cat0"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();
  

  //FIT + PLOT cat1
  RooRealVar frac_cat1("frac_cat1","frac_cat1",0.5,0,1);
  
  RooRealVar mu_cat1("mu_cat1","mu_cat1",120,100,140);
  RooRealVar sigmagauss_cat1("sigmagauss_cat1","sigmagauss_cat1",2,0,10);
  RooGaussian Gauss_cat1("Gauss_cat1","Gauss_cat1",dipho_highestpt_mgg,mu_cat1,sigmagauss_cat1);

//  RooRealVar m0_cat1("m0_cat1","m0_cat1",120,100,140);  
  RooRealVar sigma_cat1("sigma_cat1","sigma_cat1",0,10);
  RooRealVar alpha_cat1("alpha_cat1","alpha_cat1",0,10);
  RooRealVar n_cat1("n_cat1","n_cat1",0,10);
//  RooCBShape CrystalBall_cat1("CrystalBall_cat1","CrystalBall_cat1", dipho_highestpt_mgg, m0_cat1, sigma_cat1, alpha_cat1, n_cat1);
  RooCBShape CrystalBall_cat1("CrystalBall_cat1","CrystalBall_cat1", dipho_highestpt_mgg, mu_cat1, sigma_cat1, alpha_cat1, n_cat1);

  RooAddPdf model_cat1("model_cat1","model_cat1",RooArgList(Gauss_cat1,CrystalBall_cat1),frac_cat1);

  TCanvas* Canvas1 = new TCanvas("Canvas1","Canvas1");
  model_cat1.fitTo(*Data_cat1);
  RooArgSet* params1 = model_cat1.getVariables() ;
  params1->Print("v");
  RooPlot* frame = dipho_highestpt_mgg.frame(Title("#gamma#gamma Invariant mass, cat1"));
  Data_cat1->plotOn(frame,Binning(40));
  //Gauss.plotOn(frame);
  //CrystalBall.plotOn(frame);
  model_cat1.plotOn(frame);
  model_cat1.plotOn(frame,Components("CrystalBall_cat1"),LineStyle(kDashed),LineColor(kRed));
  model_cat1.plotOn(frame,Components("Gauss_cat1"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();

  
  //FIT + PLOT cat2
  RooRealVar frac_cat2("frac_cat2","frac_cat2",0.5,0,1);
  
  RooRealVar mu_cat2("mu_cat2","mu_cat2",120,100,140);
  RooRealVar sigmagauss_cat2("sigmagauss_cat2","sigmagauss_cat2",2,0,10);
  RooGaussian Gauss_cat2("Gauss_cat2","Gauss_cat2",dipho_highestpt_mgg,mu_cat2,sigmagauss_cat2);

//  RooRealVar m0_cat2("m0_cat2","m0_cat2",120,100,140);  
  RooRealVar sigma_cat2("sigma_cat2","sigma_cat2",0,10);
  RooRealVar alpha_cat2("alpha_cat2","alpha_cat2",0,10);
  RooRealVar n_cat2("n_cat2","n_cat2",0,10);
//  RooCBShape CrystalBall_cat2("CrystalBall_cat2","CrystalBall_cat2", dipho_highestpt_mgg, m0_cat2, sigma_cat2, alpha_cat2, n_cat2);
  RooCBShape CrystalBall_cat2("CrystalBall_cat2","CrystalBall_cat2", dipho_highestpt_mgg, mu_cat2, sigma_cat2, alpha_cat2, n_cat2);

  RooAddPdf model_cat2("model_cat2","model_cat2",RooArgList(Gauss_cat2,CrystalBall_cat2),frac_cat2);

  TCanvas* Canvas2 = new TCanvas("Canvas2","Canvas2");
  model_cat2.fitTo(*Data_cat2);
  RooArgSet* params2 = model_cat2.getVariables() ;
  params2->Print("v");
  RooPlot* frame = dipho_highestpt_mgg.frame(Title("#gamma#gamma Invariant mass, cat2"));
  Data_cat2->plotOn(frame,Binning(40));
  //Gauss.plotOn(frame);
  //CrystalBall.plotOn(frame);
  model_cat2.plotOn(frame);
  model_cat2.plotOn(frame,Components("CrystalBall_cat2"),LineStyle(kDashed),LineColor(kRed));
  model_cat2.plotOn(frame,Components("Gauss_cat2"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();


  //FIT + PLOT cat3
  RooRealVar frac_cat3("frac_cat3","frac_cat3",0.5,0,1);
  
  RooRealVar mu_cat3("mu_cat3","mu_cat3",120,100,140);
  RooRealVar sigmagauss_cat3("sigmagauss_cat3","sigmagauss_cat3",2,0,10);
  RooGaussian Gauss_cat3("Gauss_cat3","Gauss_cat3",dipho_highestpt_mgg,mu_cat3,sigmagauss_cat3);

//  RooRealVar m0_cat3("m0_cat3","m0_cat3",120,100,140);  
  RooRealVar sigma_cat3("sigma_cat3","sigma_cat3",0,10);
  RooRealVar alpha_cat3("alpha_cat3","alpha_cat3",0,10);
  RooRealVar n_cat3("n_cat3","n_cat3",0,10);
//  RooCBShape CrystalBall_cat3("CrystalBall_cat3","CrystalBall_cat3", dipho_highestpt_mgg, m0_cat3, sigma_cat3, alpha_cat3, n_cat3);
  RooCBShape CrystalBall_cat3("CrystalBall_cat3","CrystalBall_cat3", dipho_highestpt_mgg, mu_cat3, sigma_cat3, alpha_cat3, n_cat3);

  RooAddPdf model_cat3("model_cat3","model_cat3",RooArgList(Gauss_cat3,CrystalBall_cat3),frac_cat3);

  TCanvas* Canvas3 = new TCanvas("Canvas3","Canvas3");
  model_cat3.fitTo(*Data_cat3);
  RooArgSet* params3 = model_cat3.getVariables() ;
  params3->Print("v");
  RooPlot* frame = dipho_highestpt_mgg.frame(Title("#gamma#gamma Invariant mass, cat3"));
  Data_cat3->plotOn(frame,Binning(40));
  //Gauss.plotOn(frame);
  //CrystalBall.plotOn(frame);
  model_cat3.plotOn(frame);
  model_cat3.plotOn(frame,Components("CrystalBall_cat3"),LineStyle(kDashed),LineColor(kRed));
  model_cat3.plotOn(frame,Components("Gauss_cat3"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();
 

//  return;


  
    //QT
  //LANDAU
  RooRealVar meanLandau("meanLandau","meanLandau",10,0,50);
  RooRealVar sigmaLandau("sigmaLandau","sigmaLandau",5,0,50);
  RooLandau Landau("Landau","Landau",dipho_qt,meanLandau,sigmaLandau);

  //BIFURCATED GAUSSIAN
  RooRealVar meanBfG("meanBfG","meanBfG",15,0,50);
  RooRealVar sigmaLBfG("sigmaLBfG","sigmaLBfG",5,0,50);
  RooRealVar sigmaRBfG("sigmaRBfG","sigmaRBfG",10,0,50);  
  RooBifurGauss BifurGauss("BifurGauss","BifurGauss",dipho_qt,meanBfG,sigmaLBfG,sigmaRBfG);

  //COMPOSITION LANDAU BIFURCATED GAUSSIAN
  RooRealVar qTfrac("qTfrac","qTfrac",0.5,0,1);
  RooAddPdf qTmodel("qTmodel","qTmodel",RooArgList(Landau,BifurGauss),qTfrac);
  
  //FIT + PLOT qT
  TCanvas* Canvas4 = new TCanvas("Canvas4","Canvas4");
//  qTmodel.fitTo(Data, SumW2Error(kFALSE));
	qTmodel.fitTo(Data);
  RooArgSet* params4 = qTmodel.getVariables();
  params4->Print("v");
  RooPlot* frame = dipho_qt.frame(Title("#gamma#gamma transverse momentum"));
  Data.plotOn(frame,Binning(50));
  qTmodel.plotOn(frame);
  qTmodel.plotOn(frame,Components("Landau"),LineStyle(kDashed),LineColor(kRed));
  qTmodel.plotOn(frame,Components("BifurGauss"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();
  
//  return;
  

  
    //COSTHETASTAR
  //GAUSSIAN + GAUSSIAN + POLYN

//  RooRealVar mu1("mu1","mu1",0.3,-0.5,1.5);
//  RooRealVar sigma1("sigma1","sigma1",0.1,0,5);
//  RooRealVar mu1("mu1","mu1",0.3,0.25,0.4);
//  RooRealVar sigma1("sigma1","sigma1",0.05,0,2);
//  RooGaussian Gauss1("Gauss1","Gauss1",dipho_costhetastar,mu1,sigma1);

//  RooRealVar mu2("mu2","mu2",0.8,0.5,0.9);
//  RooRealVar sigma2("sigma2","sigma2",0.05,0,5);
//  RooRealVar mu2("mu2","mu2",0.8,0.5,1);
//  RooRealVar sigma2("sigma2","sigma2",0.05,0,2);
//  RooGaussian Gauss2("Gauss2","Gauss2",dipho_costhetastar,mu2,sigma2);

//  RooRealVar mu3("mu3","mu3",0.5,0,1);
//  RooRealVar sigma3("sigma3","sigma3",0.2,0,10);
//  RooGaussian Gauss3("Gauss3","Gauss3",dipho_costhetastar,mu3,sigma3);  

  RooRealVar a("a","a",0,-10,10);
  RooRealVar b("b","b",-1,-10,10);  
//  RooRealVar a("a","a",-1,-50,50);
//  RooRealVar b("b","b",10,-50,50);  
//  RooRealVar c("c","c",-10,-50,50);  
//  RooRealVar d("d","d",0,-50,50);    
  //RooPolynomial Pol1("Pol1","Pol1",dipho_costhetastar,RooArgList(a,b,c,d));
  RooPolynomial Pol1("Pol1","Pol1",dipho_costhetastar,RooArgList(a,b));
//  RooPolynomial Pol3("Pol3","Pol3",dipho_costhetastar,RooArgList(a,b,c,d));


  //BIFURCATED GAUSSIAN
  RooRealVar meanBfG2("meanBfG2","meanBfG2",0.8,0.5,1);
  RooRealVar sigmaLBfG2("sigmaLBfG2","sigmaLBfG2",6,0,20);
  RooRealVar sigmaRBfG2("sigmaRBfG2","sigmaRBfG2",0.1,0,1);  
  RooBifurGauss BifurGauss2("BifurGauss2","BifurGauss2",dipho_costhetastar,meanBfG2,sigmaLBfG2,sigmaRBfG2);

 
//  RooRealVar fracfloat("fracfloat","fracfloat",0.4,0,1);
  RooRealVar fracfloat2("fracfloat2","fracfloat2",0.3,0,1);  
//  RooRealVar fracfloat("fracfloat","fracfloat",0.999,0.999,1);
//  RooRealVar fracfloat2("fracfloat2","fracfloat2",0.5,0,0.1);  

//  RooAddPdf DoubleGauss("DoubleGauss","DoubleGauss",RooArgList(Gauss1,Gauss2),fracfloat);
  //RooAddPdf TripleGauss("TripleGauss","TripleGauss",RooArgList(DoubleGauss,Gauss3),frac);  

//  RooAddPdf CosthetastarModel("CosthetastarModel","CosthetastarModel",RooArgList(DoubleGauss,BifurGauss2),fracfloat2);
  RooAddPdf CosthetastarModel("CosthetastarModel","CosthetastarModel",RooArgList(Pol1,BifurGauss2),fracfloat2);
//  RooAddPdf CosthetastarModel("CosthetastarModel","CosthetastarModel",RooArgList(DoubleGauss,Pol1),fracfloat2);
//  RooAddPdf CosthetastarModel("CosthetastarModel","CosthetastarModel",RooArgList(DoubleGauss,Pol2),fracfloat2);
//  RooAddPdf CosthetastarModel("CosthetastarModel","CosthetastarModel",RooArgList(Gauss2,Pol3),fracfloat2);

  //FIT + PLOT costhetastar
  TCanvas* Canvas5 = new TCanvas("Canvas5","Canvas5");
  CosthetastarModel.fitTo(Data, SumW2Error(kFALSE));
  RooArgSet* params5 = CosthetastarModel.getVariables() ;
  params5->Print("v");
  RooPlot* frame = dipho_costhetastar.frame(Title("#gamma#gamma angular distribution cos(#theta^{*})"));
  Data.plotOn(frame,Binning(25));
  CosthetastarModel.plotOn(frame);
//  CosthetastarModel.plotOn(frame,Components("Gauss1"),LineStyle(kDashed),LineColor(kCyan));
//  CosthetastarModel.plotOn(frame,Components("Gauss2"),LineStyle(kDashed),LineColor(kMagenta));  
  //CosthetastarModel.plotOn(frame,Components("Gauss3"),LineStyle(kDashed),LineColor(kBlack));  
//  CosthetastarModel.plotOn(frame,Components("DoubleGauss"),LineStyle(kDashed),LineColor(kOrange));
  //CosthetastarModel.plotOn(frame,Components("TripleGauss"),LineStyle(kDashed),LineColor(kRed));
  CosthetastarModel.plotOn(frame,Components("Pol1"),LineStyle(kDashed),LineColor(kOrange));
  CosthetastarModel.plotOn(frame,Components("BifurGauss2"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();
  
//  return;
  

  //NN OUTPUT
  //KERNEL + tests...
*/
  /*
  RooFormulaVar arccosNN("arccosNN","acos(@0)",phoNNmin_MLPoutputClusterShapeEnv);
  
  TCanvas* Canvas6 = new TCanvas("Canvas6","Canvas6");
  RooPlot* frame = phoNNmin_MLPoutputClusterShapeEnv.frame();
  Data.plotOn(frame,Binning(50));
  

  return;
  */

//  RooKeysPdf NNsumgauss("NNsumgauss","NNsumgauss", phoNNmin_MLPoutputClusterShapeEnv, Data);
/*
  
  RooRealVar NNmeanLandau("NNmeanLandau","NNmeanLandau",0,-1.1,-0.9);
  RooRealVar NNsigmaLandau("NNsigmaLandau","NNsigmaLandau",0.1,0,10);
  RooLandau NNLandau("NNLandau","NNLandau",phoNNmin_MLPoutputClusterShapeEnv,NNmeanLandau,NNsigmaLandau);
  NNmeanLandau.setRange(-1.1,-0.9);

  
  RooRealVar NNmu("NNmu","NNmu",-1,-1.1,-0.9);
  RooRealVar NNsigma("NNsigma","NNsigma",0.1,0,10);
  RooGaussian NNGauss("NNGauss","NNGauss",phoNNmin_MLPoutputClusterShapeEnv,NNmu,NNsigma);
  
  RooRealVar a("a","a",0,-1000,1000);
  RooRealVar b("b","b",-1,-1000,1000);  
  RooRealVar c("c","c",0,-100,100);  
  RooRealVar d("d","d",0,-100,100);  
  RooRealVar e("e","e",0,-100,100);  
  RooRealVar f("f","f",0,-100,100);    
  RooPolynomial Pol("Pol","Pol",phoNNmin_MLPoutputClusterShapeEnv,RooArgList(a,b,c,d,e,f));

  RooRealVar NNexpParam("NNexpParam","NNexpParam",0,-100,100);
  RooExponential NNexp("NNexp", "NNexp", phoNNmin_MLPoutputClusterShapeEnv, NNexpParam);
  //NNexp.SetRange(-1,1);

  RooRealVar beta_a("beta_a","beta_a",5,0,10) ;
  RooRealVar beta_b("beta_b","beta_b",2,0,10) ;
  RooAbsPdf* beta = bindPdf("beta",ROOT::Math::beta_pdf,phoNNmin_MLPoutputClusterShapeEnv,beta_a,beta_b) ;
*/

  RooRealVar NNmeanBfG_NN1("NNmeanBfG_NN1","NNmeanBfG_NN1",0.8,0.7,1.0);
	RooRealVar NNsigmaLBfG_NN1("NNsigmaLBfG_NN1","NNsigmaLBfG_NN1",0,0,0.3);
  RooRealVar NNsigmaRBfG_NN1("NNsigmaRBfG_NN1","NNsigmaRBfG_NN1",0.01,0,0.10);  
  RooBifurGauss NNBifurGauss_NN1("NNBifurGauss_NN1","NNBifurGauss_NN1",phoNNmin_MLPoutputClusterShapeEnv,NNmeanBfG_NN1,NNsigmaLBfG_NN1,NNsigmaRBfG_NN1);


  RooRealVar NNmeanBfG_NN2("NNmeanBfG_NN2","NNmeanBfG_NN2",0.3,0,0.6);
  RooRealVar NNsigmaLBfG_NN2("NNsigmaLBfG_NN2","NNsigmaLBfG_NN2",0.6,0,5);
  RooRealVar NNsigmaRBfG_NN2("NNsigmaRBfG_NN2","NNsigmaRBfG_NN2",0.07,0,1.5);  
  RooBifurGauss NNBifurGauss_NN2("NNBifurGauss_NN2","NNBifurGauss_NN2",phoNNmin_MLPoutputClusterShapeEnv,NNmeanBfG_NN2,NNsigmaLBfG_NN2,NNsigmaRBfG_NN2);

  RooRealVar NNmeanBfG_NN3("NNmeanBfG_NN3","NNmeanBfG_NN3",-0.95,-1.0,-0.90);
  RooRealVar NNsigmaLBfG_NN3("NNsigmaLBfG_NN3","NNsigmaLBfG_NN3",0.01,0,0.02);
  RooRealVar NNsigmaRBfG_NN3("NNsigmaRBfG_NN3","NNsigmaRBfG_NN3",0.01,0,0.02);  
  RooBifurGauss NNBifurGauss_NN3("NNBifurGauss_NN3","NNBifurGauss_NN3",phoNNmin_MLPoutputClusterShapeEnv,NNmeanBfG_NN3,NNsigmaLBfG_NN3,NNsigmaRBfG_NN3);

  RooRealVar mu_NN1("mu_NN1","mu_NN1",0.9,0.7,1.1);
  RooRealVar sigma_NN1("sigma_NN1","sigma_NN1",0.1,0,5);
  RooGaussian Gauss_NN1("Gauss_NN1","Gauss_NN1",phoNNmin_MLPoutputClusterShapeEnv,mu_NN1,sigma_NN1);

  RooRealVar mu_NN2("mu_NN2","mu_NN2",-0.9,-1.0,-0.85);
  RooRealVar sigma_NN2("sigma_NN2","sigma_NN2",0.02,0,15);
  RooGaussian Gauss_NN2("Gauss_NN2","Gauss_NN2",phoNNmin_MLPoutputClusterShapeEnv,mu_NN2,sigma_NN2);

//LANDAU
  RooRealVar meanLandau_NN("meanLandau_NN","meanLandau_NN",0,-1.1,1.1);
  RooRealVar sigmaLandau_NN("sigmaLandau_NN","sigmaLandau_NN",5,0,10);
  RooLandau Landau_NN("Landau_NN","Landau_NN",phoNNmin_MLPoutputClusterShapeEnv,meanLandau_NN,sigmaLandau_NN);

// CRYSTALBALL
  RooRealVar m0_NN("m0_NN","m0_NN",0.9,0.7,1.0);  
  RooRealVar sigma_NN("sigma_NN","sigma_NN", 0.1 ,0,5);
  RooRealVar alpha_NN("alpha_NN","alpha_NN", 0.1 ,0,5);
  RooRealVar n_NN("n_NN","n_NN", 0.1 ,0,20);
  RooCBShape CrystalBall_NN("CrystalBall_NN","CrystalBall_NN", phoNNmin_MLPoutputClusterShapeEnv, m0_NN, sigma_NN, alpha_NN, n_NN);

 
//  RooRealVar NNfrac("NNfrac","NNfrac",0.5,0,1);
//  RooRealVar NNfrac2("NNfrac2","NNfrac2",0.9,0.7,1);
  RooRealVar NNfrac("NNfrac","NNfrac",0.5,0,1);
  RooRealVar NNfrac2("NNfrac2","NNfrac2",0.9,0.8,1);
//  RooAddPdf DoubleBfGauss("DoubleBfGauss","DoubleBfGauss",RooArgList(NNBifurGauss_NN1, NNBifurGauss_NN2),NNfrac);
//  RooAddPdf BfGaussGauss("BfGaussGauss","BfGaussGauss",RooArgList(Gauss_NN1, NNBifurGauss_NN2),NNfrac);
//  RooAddPdf LandauGauss("LandauGauss","LandauGauss",RooArgList(Gauss_NN1, Landau_NN),NNfrac);
//  RooAddPdf CrystalBallGauss("CrystalBallGauss","CrystalBallGauss",RooArgList(Gauss_NN1, CrystalBall_NN),NNfrac);
  RooAddPdf CrystalBallBfGauss("CrystalBallBfGauss","CrystalBallBfGauss",RooArgList(NNBifurGauss_NN2, CrystalBall_NN),NNfrac);

//  RooAddPdf NNModel("NNModel","NNModel",RooArgList(NNBifurGauss_NN1, NNBifurGauss_NN2),NNfrac2);
//  RooAddPdf NNModel("NNModel","NNModel",RooArgList(DoubleBfGauss, NNBifurGauss_NN3),NNfrac2);
//  RooAddPdf NNModel("NNModel","NNModel",RooArgList(BfGaussGauss, Gauss_NN2),NNfrac2);
//  RooAddPdf NNModel("NNModel","NNModel",RooArgList(LandauGauss, Gauss_NN2),NNfrac2);
//  RooAddPdf NNModel("NNModel","NNModel",RooArgList(CrystalBallGauss, Gauss_NN2),NNfrac2);
//  RooAddPdf NNModel("NNModel","NNModel",RooArgList(CrystalBallBfGauss, Gauss_NN2),NNfrac2);
  RooAddPdf NNModel("NNModel","NNModel",RooArgList(CrystalBallBfGauss, NNBifurGauss_NN3),NNfrac2);

  //RooRealVar NNfrac("NNfrac","NNfrac",0.5,0,1);
  //RooAddPdf NNmodel("NNmodel","NNmodel",RooArgList(NNsumgauss,NNLandau),NNfrac);
 
//  NNsumgauss.fitTo(Data);
  NNModel.fitTo(Data, SumW2Error(kFALSE));
  //NNmodel.fitTo(Data, Range(-0.9,0.82));
  RooArgSet* params6 = NNModel.getVariables();
 // RooArgSet* params6 = NNsumgauss.getVariables();
  params6->Print("v");

  TCanvas* Canvas6 = new TCanvas("Canvas6","Canvas6");
  RooPlot* frame = phoNNmin_MLPoutputClusterShapeEnv.frame(Title("#gamma/#pi^{0} Neural network output min"));
  Data.plotOn(frame,Binning(100));
  
  //NNsumgauss.plotOn(frame);
  NNModel.plotOn(frame);
//  NNModel.plotOn(frame, Components("NNBifurGauss_NN1"),LineStyle(kDashed),LineColor(kRed));
//  NNModel.plotOn(frame, Components("Gauss_NN1"),LineStyle(kDashed),LineColor(kRed));
//  NNModel.plotOn(frame, Components("NNBifurGauss_NN2"),LineStyle(kDashed),LineColor(kGreen));
  NNModel.plotOn(frame, Components("NNBifurGauss_NN2"),LineStyle(kDashed),LineColor(kRed));
  NNModel.plotOn(frame, Components("CrystalBall_NN"),LineStyle(kDashed),LineColor(kGreen));
//  NNModel.plotOn(frame, Components("Landau_NN"),LineStyle(kDashed),LineColor(kGreen));
//  NNModel.plotOn(frame, Components("DoubleBfGauss"),LineStyle(kDashed),LineColor(kOrange));
  NNModel.plotOn(frame, Components("NNBifurGauss_NN3"),LineStyle(kDashed),LineColor(kCyan));
//  NNModel.plotOn(frame, Components("Gauss_NN2"),LineStyle(kDashed),LineColor(kCyan));
  //NNmodel.plotOn(frame, Components("NNsumgauss"),LineStyle(kDashed),LineColor(kRed));
  //NNmodel.plotOn(frame,Components("NNLandau"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();
  

  return;
}
