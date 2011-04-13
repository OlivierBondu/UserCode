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

//#pragma optimize 0

// RooStats headers
//#include "RooStats/HLFactory.h"

void BkgdFits(){

	CMSstyle();
  using namespace RooFit;

	TChain *Tree_Born = new TChain("Tree");
	Tree_Born->Add("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_MadgraphDiphotonJets_noNNcut.root");

//  TFile* file_QCD = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_PythiaQCD40filtered_Test_noNNcut.root");
//  TFile* file_GammaJet = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_PythiaGjet20filtered_noNNcut.root");
//  TFile* file_Born = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/a.root");
//  TFile* file_Born = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_MadgraphDiphotonJets_noNNcut.root");
//  TFile* file_Born = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/diphoton_DiPhoJets.root");
//  TFile* file_Born = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_MadgraphDiphotonJets_noNNcut_friend.root");
//  TFile* file_Box10to25 = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_PythiaBox10to25_noNNcut.root");
//  TFile* file_Box25to250 = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_PythiaBox25to250_noNNcut.root");
//  TFile* file_Box250toInf = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_PythiaBox250toInf_noNNcut.root");
  
//  TTree* Tree_QCD = (TTree*) file_QCD->Get("Tree");
//  TTree* Tree_GammaJet = (TTree*) file_GammaJet->Get("Tree");
//  TTree* Tree_Born = (TTree*) file_Born->("Tree");
//  TTree* Tree_Born = (TTree*) file_Born->("diPhotons");
//	cout << "Tree_Born->GetEntries()= " << Tree_Born->GetEntries() << endl;
//  TTree* Tree_Born = (TTree*) file_Born->("friendTree");
//  TTree* Tree_Box10to25 = (TTree*) file_Box10to25->Get("Tree");
//  TTree* Tree_Box25to250 = (TTree*) file_Box25to250->Get("Tree");
//  TTree* Tree_Box250toInf = (TTree*) file_Box250toInf->Get("Tree");

//	Tree_QCD->AddFriend("friendTree","DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_PythiaQCD40filtered_Test_noNNcut_friend.root");
//	Tree_GammaJet->AddFriend("friendTree","DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_PythiaGjet20filtered_noNNcut_friend.root");
// BUG TO BE UNDERSTOOD ??????
//	TFile* file_Born_friend = new TFile("DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_MadgraphDiphotonJets_noNNcut.root");
//	TTree* Tree_Born_friend = (TTree*) file_Born_friend->("friendTree");
//	cout << "\t\tTree_Born_friend->GetEntries()= " << Tree_Born_friend->GetEntries() << endl;
//	Tree_Born->AddFriend(Tree_Born_friend);
//	Tree_Born->AddFriend("Tree","DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_MadgraphDiphotonJets_noNNcut.root");
//	Tree_Born->AddFriend("friendTree","DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/diphoton_DiPhoJets_friend.root"); 
	Tree_Born->AddFriend("friendTree","DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_MadgraphDiphotonJets_noNNcut_friend.root"); 
//	Tree_Born->AddFriend("friendTree","DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/a_friend.root"); 
//	Tree_Box10to25->AddFriend("friendTree","DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_PythiaBox10to25_noNNcut_friend.root");
//	cout << "Tree_Box10to25->GetEntries()= " << Tree_Box10to25->GetEntries() << endl;
//	Tree_Box25to250->AddFriend("friendTree","DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_PythiaBox25to250_noNNcut_friend.root");
//	Tree_Box250toInf->AddFriend("friendTree","DiphotonFiltered_mgg90_pt30_20_EGM006Loose_sig0105/DiphotonTree_MC_PythiaBox250toInf_noNNcut_friend.root");

  RooRealVar dipho_costhetastar("dipho_costhetastar","cos(#theta^{*})",0.0,1.0,"");
  RooRealVar dipho_qt("dipho_qt","p_{T,#gamma#gamma}",0,140,"GeV");
  RooRealVar phoNNmin_MLPoutputClusterShapeEnv("phoNNmin_MLPoutputClusterShapeEnv","NNoutput_{min}",-1.2,1.2);
  RooRealVar dipho_highestpt_mgg("dipho_highestpt_mgg","M_{#gamma#gamma}",90,200,"GeV");
  RooCategory dipho_cat4("dipho_cat4","dipho_cat4");
  dipho_cat4.defineType("cat4_0",0);
  dipho_cat4.defineType("cat4_1",1);
  dipho_cat4.defineType("cat4_2",2);
  dipho_cat4.defineType("cat4_3",3);
	RooRealVar dipho_Xsection("dipho_Xsection","dipho_Xsection", -1.0, 10000000000000,"");
//	RooRealVar dipho_Xsection("dipho_Xsection","dipho_Xsection", 1.0);
  RooArgSet ntplVars(dipho_highestpt_mgg, dipho_qt, dipho_costhetastar, phoNNmin_MLPoutputClusterShapeEnv, dipho_cat4, dipho_Xsection);


//  RooDataSet Data("Data","Data",Tree_QCD,ntplVars,"","dipho_Xsection");
//  RooDataSet Data("Data","Data",Tree_GammaJet,ntplVars,"","dipho_Xsection");
  RooDataSet Data("Data","Data",Tree_Born,ntplVars,"","dipho_Xsection");
//  RooDataSet Data("Data","Data",Tree_Box10to25,ntplVars,"","dipho_Xsection");
//  RooDataSet Data_Box10to25("Data_Box10to25","Data_Box10to25",Tree_Box10to25,ntplVars,"","dipho_Xsection");
//  RooDataSet Data_Box25to250("Data_Box25to250","Data_Box25to250",Tree_Box25to250,ntplVars,"","dipho_Xsection");
//  RooDataSet Data_Box250toInf("Data_Box250toInf","Data_Box250toInf",Tree_Box250toInf,ntplVars,"","dipho_Xsection");


//	Data.append(Data_Box25to250);
//	Data.append(Data_Box250toInf);

 /*
 Data.add(ntplVars, 1.15 * (28977825.0/21056664.0) * 40392 / 20479315.0);
  RooDataSet Data_GammaJet("Data_GammaJet","Data_GammaJet",Tree_GammaJet,ntplVars);
  Data_GammaJet.add(ntplVars, 493.44 / 1177569.0);
  RooDataSet Data_Born("Data_Born","Data_Born",Tree_Born,ntplVars);
  Data_Born.add(ntplVars, 0.00242 / 110000.0);

  Data.append(Data_GammaJet);
  Data.append(Data_Born);
*/
  RooDataSet* Data_cat0 = Data.reduce("dipho_cat4==0");
  RooDataSet* Data_cat1 = Data.reduce("dipho_cat4==1");
  RooDataSet* Data_cat2 = Data.reduce("dipho_cat4==2");
  RooDataSet* Data_cat3 = Data.reduce("dipho_cat4==3");




  //FITS 
//  RooRealVar frac("frac","frac",0.5,0,1);

 
	// Exponential
	RooRealVar mgg_c("cat0_c", "cat0_c", -0.05, -0.1, 0);
	RooExponential mgg_exp("cat0_exp", "cat0_exp", dipho_highestpt_mgg, mgg_c);

  //Gaussienne
//  RooRealVar mu("mu","mu",120,100,140);
//  RooRealVar sigmagauss("sigmagauss","sigmagauss",2,0,10);
//  RooGaussian Gauss("Gauss","Gauss",dipho_highestpt_mgg,mu,sigmagauss);

  //Crystal Ball
//  RooRealVar m0("m0","m0",120,100,140);  
//  RooRealVar sigma("sigma","sigma",0,10);
//  RooRealVar alpha("alpha","alpha",0,10);
//  RooRealVar n("n","n",0,10);
//  RooCBShape CrystalBall("CrystalBall","CrystalBall", dipho_highestpt_mgg, m0, sigma, alpha, n);

  //Convolution Gaussienne + CB
  //RooNumConvPdf model("model","model",dipho_highestpt_mgg,Gauss,CrystalBall) ;
//  RooAddPdf model("model","model",RooArgList(Gauss,CrystalBall),frac);
 
 
  //FIT + PLOT cat0
  TCanvas* Canvas0 = new TCanvas("Canvas0_Born","Canvas0_Born");
	mgg_exp.fitTo(*Data_cat0);
	RooArgSet* params0 = mgg_exp.getVariables();
//  model.fitTo(*Data_cat0);
//  RooArgSet* params0 = model.getVariables();
  params0->Print("v");
  RooPlot* frame = dipho_highestpt_mgg.frame(Title("#gamma#gamma Invariant mass, cat0"));
  Data_cat0->plotOn(frame,Binning(40));
 //Gauss.plotOn(frame);
  //CrystalBall.plotOn(frame);
	mgg_exp.plotOn(frame);
//  model.plotOn(frame);
//  model.plotOn(frame,Components("CrystalBall"),LineStyle(kDashed),LineColor(kRed));
//  model.plotOn(frame,Components("Gauss"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();

  //FIT + PLOT cat1
  TCanvas* Canvas1 = new TCanvas("Canvas1_Born","Canvas1_Born");
	mgg_exp.fitTo(*Data_cat1);
	RooArgSet* params1 = mgg_exp.getVariables();
//  model.fitTo(*Data_cat1);
//  RooArgSet* params1 = model.getVariables() ;
  params1->Print("v");
  RooPlot* frame = dipho_highestpt_mgg.frame(Title("#gamma#gamma Invariant mass, cat1"));
  Data_cat1->plotOn(frame,Binning(40));
	mgg_exp.plotOn(frame);
  //Gauss.plotOn(frame);
  //CrystalBall.plotOn(frame);
//  model.plotOn(frame);
//  model.plotOn(frame,Components("CrystalBall"),LineStyle(kDashed),LineColor(kRed));
//  model.plotOn(frame,Components("Gauss"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();


  //FIT + PLOT cat2
  TCanvas* Canvas2 = new TCanvas("Canvas2_Born","Canvas2_Born");
	mgg_exp.fitTo(*Data_cat2);
	RooArgSet* params2 = mgg_exp.getVariables();
//  model.fitTo(*Data_cat2);
//  RooArgSet* params2 = model.getVariables() ;
  params2->Print("v");
  RooPlot* frame = dipho_highestpt_mgg.frame(Title("#gamma#gamma Invariant mass, cat2"));
  Data_cat2->plotOn(frame,Binning(40));
	mgg_exp.plotOn(frame);
  //Gauss.plotOn(frame);
  //CrystalBall.plotOn(frame);
//  model.plotOn(frame);
//  model.plotOn(frame,Components("CrystalBall"),LineStyle(kDashed),LineColor(kRed));
//  model.plotOn(frame,Components("Gauss"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();


  //FIT + PLOT cat3
  TCanvas* Canvas3 = new TCanvas("Canvas3_Born","Canvas3_Born");
	mgg_exp.fitTo(*Data_cat3);
	RooArgSet* params3 = mgg_exp.getVariables();
//  model.fitTo(*Data_cat3);
//  RooArgSet* params3 = model.getVariables() ;
  params3->Print("v");
  RooPlot* frame = dipho_highestpt_mgg.frame(Title("#gamma#gamma Invariant mass, cat3"));
  Data_cat3->plotOn(frame,Binning(40));
	mgg_exp.plotOn(frame);
  //Gauss.plotOn(frame);
  //CrystalBall.plotOn(frame);
//  model.plotOn(frame);
//  model.plotOn(frame,Components("CrystalBall"),LineStyle(kDashed),LineColor(kRed));
//  model.plotOn(frame,Components("Gauss"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();
  
//  return;


  
    //QT
  //LANDAU
  //RooLandau(const char* name, const char* title, RooAbsReal& _x, RooAbsReal& _mean, RooAbsReal& _sigma)
  RooRealVar meanLandau("meanLandau","meanLandau",4,0,100);
  RooRealVar sigmaLandau("sigmaLandau","sigmaLandau",1,0,100);
  RooLandau Landau("Landau","Landau",dipho_qt,meanLandau,sigmaLandau);

  //BIFURCATED GAUSSIAN
  //RooBifurGauss(const char* name, const char* title, RooAbsReal& _x, RooAbsReal& _mean, RooAbsReal& _sigmaL, RooAbsReal& _sigmaR)
  RooRealVar meanBfG("meanBfG","meanBfG",10,0,100);
  RooRealVar sigmaLBfG("sigmaLBfG","sigmaLBfG",4,0,100);
  RooRealVar sigmaRBfG("sigmaRBfG","sigmaRBfG",4,0,100);  
  RooBifurGauss BifurGauss("BifurGauss","BifurGauss",dipho_qt,meanBfG,sigmaLBfG,sigmaRBfG);

  //COMPOSITION LANDAU BIFURCATED GAUSSIAN
  RooRealVar qTfrac("qTfrac","qTfrac",0.5,0,1);
  RooAddPdf qTmodel("qTmodel","qTmodel",RooArgList(Landau,BifurGauss),qTfrac);
  
  //FIT + PLOT qT
  TCanvas* Canvas4 = new TCanvas("Canvas4_Born","Canvas4_Born");
  qTmodel.fitTo(Data, SumW2Error(kTRUE));
  RooArgSet* params4 = qTmodel.getVariables();
  params4->Print("v");
  RooPlot* frame = dipho_qt.frame(Title("#gamma#gamma transverse momentum"));
  Data.plotOn(frame,Binning(50));
  qTmodel.plotOn(frame);
  qTmodel.plotOn(frame,Components("Landau"),LineStyle(kDashed),LineColor(kRed));
  qTmodel.plotOn(frame,Components("BifurGauss"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();
  
//return;
 

    //COSTHETASTAR
  //GAUSSIAN + GAUSSIAN + POLYN
  RooRealVar mu1("mu1","mu1",0.5,0,1);
  RooRealVar sigma1("sigma1","sigma1",0.2,0,10);
  RooGaussian Gauss1("Gauss1","Gauss1",dipho_costhetastar,mu1,sigma1);

  RooRealVar mu2("mu2","mu2",0.5,0,1);
  RooRealVar sigma2("sigma2","sigma2",0.2,0,10);
  RooGaussian Gauss2("Gauss2","Gauss2",dipho_costhetastar,mu2,sigma2);

  RooRealVar mu3("mu3","mu3",0.5,0,1);
  RooRealVar sigma3("sigma3","sigma3",0.2,0,10);
  RooGaussian Gauss3("Gauss3","Gauss3",dipho_costhetastar,mu3,sigma3);  

  RooRealVar a("a","a",0,-1000,1000);
  RooRealVar b("b","b",-1,-1000,1000);  
  RooRealVar c("c","c",0,-100,100);  
  RooRealVar d("d","d",0,-100,100);    
  //RooPolynomial Pol1("Pol1","Pol1",dipho_costhetastar,RooArgList(a,b,c,d));
  RooPolynomial Pol1("Pol1","Pol1",dipho_costhetastar,RooArgList(a,b));
  
  RooRealVar fracfloat("fracfloat","fracfloat",0.3,0,1);
  RooRealVar fracfloat2("fracfloat2","fracfloat2",0.3,0,1);  

  RooAddPdf DoubleGauss("DoubleGauss","DoubleGauss",RooArgList(Gauss1,Gauss2),fracfloat);
  //RooAddPdf TripleGauss("TripleGauss","TripleGauss",RooArgList(DoubleGauss,Gauss3),frac);  

  RooAddPdf CosthetastarModel("CosthetastarModel","CosthetastarModel",RooArgList(DoubleGauss,Pol1),fracfloat2);

  //FIT + PLOT costhetastar
  TCanvas* Canvas5 = new TCanvas("Canvas5_Born","Canvas5_Born");
  CosthetastarModel.fitTo(Data);
  RooArgSet* params5 = CosthetastarModel.getVariables() ;
  params5->Print("v");
  RooPlot* frame = dipho_costhetastar.frame(Title("#gamma#gamma angular distribution cos(#theta^{*})"));
  Data.plotOn(frame,Binning(25));
  CosthetastarModel.plotOn(frame);
  CosthetastarModel.plotOn(frame,Components("Gauss1"),LineStyle(kDashed),LineColor(kCyan));
  CosthetastarModel.plotOn(frame,Components("Gauss2"),LineStyle(kDashed),LineColor(kMagenta));  
  //CosthetastarModel.plotOn(frame,Components("Gauss3"),LineStyle(kDashed),LineColor(kBlack));  
//  CosthetastarModel.plotOn(frame,Components("DoubleGauss"),LineStyle(kDashed),LineColor(kOrange));
  //CosthetastarModel.plotOn(frame,Components("TripleGauss"),LineStyle(kDashed),LineColor(kRed));
  CosthetastarModel.plotOn(frame,Components("Pol1"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();
  
//return;



  //NN OUTPUT
  //KERNEL + tests...

 /* 
  RooFormulaVar arccosNN("arccosNN","acos(@0)",phoNNmin_MLPoutputClusterShapeEnv);
  
  TCanvas* Canvas6 = new TCanvas("Canvas6_Born","Canvas6_Born");
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


  RooRealVar NNmeanBfG("NNmeanBfG","NNmeanBfG",0.9,0.7,1.0);
  RooRealVar NNsigmaLBfG("NNsigmaLBfG","NNsigmaLBfG",0.4,0,5);
  RooRealVar NNsigmaRBfG("NNsigmaRBfG","NNsigmaRBfG",0.4,0,5);  
  RooBifurGauss NNBifurGauss("NNBifurGauss","NNBifurGauss",phoNNmin_MLPoutputClusterShapeEnv,NNmeanBfG,NNsigmaLBfG,NNsigmaRBfG);
 
*/
	// BIFURCATED GAUSSIAN
  RooRealVar NNmeanBfG_NN1("NNmeanBfG_NN1","NNmeanBfG_NN1",0.9, 0.7, 1.0);// GJets
  RooRealVar NNsigmaLBfG_NN1("NNsigmaLBfG_NN1","NNsigmaLBfG_NN1",0.4,0,5); // GJets
  RooRealVar NNsigmaRBfG_NN1("NNsigmaRBfG_NN1","NNsigmaRBfG_NN1",0.4,0,5); // GJets
  RooBifurGauss NNBifurGauss_NN1("NNBifurGauss_NN1","NNBifurGauss_NN1",phoNNmin_MLPoutputClusterShapeEnv,NNmeanBfG_NN1,NNsigmaLBfG_NN1,NNsigmaRBfG_NN1); // GJets
 
// CRYSTALBALL
  RooRealVar m0_NN("m0_NN","m0_NN",0.9,0.7,1.0); // BOX QCD
  RooRealVar sigma_NN("sigma_NN","sigma_NN", 0.1 ,0,5); // BOX QCD
  RooRealVar alpha_NN("alpha_NN","alpha_NN", 0.1 ,0,5); // BOX QCD
  RooRealVar n_NN("n_NN","n_NN", 0.1 ,0,20); // BOX
//  RooRealVar n_NN("n_NN","n_NN", 0.1 ,0,50); // QCD
//  RooRealVar n_NN("n_NN","n_NN", 9.1 ,0,100); // QCD
  RooCBShape CrystalBall_NN("CrystalBall_NN","CrystalBall_NN", phoNNmin_MLPoutputClusterShapeEnv, m0_NN, sigma_NN, alpha_NN, n_NN);
//	CrystalBall_NN.fitTo(Data, SumW2Error(kFALSE), Range(0.8, 1.0));

//  RooRealVar NNmeanBfG_NN2("NNmeanBfG_NN2","NNmeanBfG_NN2",0.3,0,0.6); // FOR BOX
  RooRealVar NNmeanBfG_NN2("NNmeanBfG_NN2","NNmeanBfG_NN2",0.3,0,0.8); // BORN
//  RooRealVar NNmeanBfG_NN2("NNmeanBfG_NN2","NNmeanBfG_NN2",-0.8,-1.0,-0.7);// QCD
//  RooRealVar NNmeanBfG_NN2("NNmeanBfG_NN2","NNmeanBfG_NN2",-0.8,-0.9,-0.7);// GJets
  RooRealVar NNsigmaLBfG_NN2("NNsigmaLBfG_NN2","NNsigmaLBfG_NN2",0.6,0.025,5); // BOX QCD
//  RooRealVar NNsigmaLBfG_NN2("NNsigmaLBfG_NN2","NNsigmaLBfG_NN2",0.6,0.005,5); // GJets
  RooRealVar NNsigmaRBfG_NN2("NNsigmaRBfG_NN2","NNsigmaRBfG_NN2",0.07,0,1.5); // BOX QCD GJets
  RooBifurGauss NNBifurGauss_NN2("NNBifurGauss_NN2","NNBifurGauss_NN2",phoNNmin_MLPoutputClusterShapeEnv,NNmeanBfG_NN2,NNsigmaLBfG_NN2,NNsigmaRBfG_NN2);

  RooRealVar NNmeanBfG_NN3("NNmeanBfG_NN3","NNmeanBfG_NN3",-0.95,-1.0,-0.85); // BOX QCD GJets
  RooRealVar NNsigmaLBfG_NN3("NNsigmaLBfG_NN3","NNsigmaLBfG_NN3",0.01,0,0.02); // BOX
  RooRealVar NNsigmaRBfG_NN3("NNsigmaRBfG_NN3","NNsigmaRBfG_NN3",0.01,0,0.02); // BOX
//  RooRealVar NNsigmaRBfG_NN3("NNsigmaRBfG_NN3","NNsigmaRBfG_NN3",0.01,0,0.10); //QCD
//  RooRealVar NNsigmaRBfG_NN3("NNsigmaRBfG_NN3","NNsigmaRBfG_NN3",0.01,0,0.20); //QCD
//  RooRealVar NNsigmaLBfG_NN3("NNsigmaLBfG_NN3","NNsigmaLBfG_NN3",0.01,0,0.05); // GJets
//  RooRealVar NNsigmaRBfG_NN3("NNsigmaRBfG_NN3","NNsigmaRBfG_NN3",0.01,0,0.50); //GJets
  RooBifurGauss NNBifurGauss_NN3("NNBifurGauss_NN3","NNBifurGauss_NN3",phoNNmin_MLPoutputClusterShapeEnv,NNmeanBfG_NN3,NNsigmaLBfG_NN3,NNsigmaRBfG_NN3);
	NNBifurGauss_NN3.fitTo(Data, SumW2Error(kFALSE), Range(-1.1, -0.8)); // FOR BOX GJets

  RooRealVar NNfrac("NNfrac","NNfrac",0.5,0,1); // BOX QCD GJets
  RooRealVar NNfrac2("NNfrac2","NNfrac2",0.90,0.75,1.00); // GJets
//  RooRealVar NNfrac2("NNfrac2","NNfrac2",0.50,0.0,1.00); // BOX QCD
  RooAddPdf CrystalBallBfGauss("CrystalBallBfGauss","CrystalBallBfGauss",RooArgList(NNBifurGauss_NN2, CrystalBall_NN),NNfrac); // BOX QCD
  RooAddPdf DoubleBfGauss("DoubleBfGauss","DoubleBfGauss",RooArgList(NNBifurGauss_NN2, NNBifurGauss_NN1),NNfrac); // GJets
  RooAddPdf NNModel("NNModel","NNModel",RooArgList(CrystalBallBfGauss, NNBifurGauss_NN3),NNfrac2); // QCD BOX
//  RooAddPdf NNModel("NNModel","NNModel",RooArgList(DoubleBfGauss, NNBifurGauss_NN3),NNfrac2); // GJets
  NNModel.fitTo(Data, SumW2Error(kFALSE));
  RooArgSet* params6 = NNModel.getVariables();
  params6->Print("v");



  //RooRealVar NNfrac("NNfrac","NNfrac",0.5,0,1);
  //RooAddPdf NNmodel("NNmodel","NNmodel",RooArgList(NNsumgauss,NNLandau),NNfrac);
 
//  NNsumgauss.fitTo(Data);
  //NNmodel.fitTo(Data);
  //NNmodel.fitTo(Data, Range(-0.9,0.82));
  //RooArgSet* params6 = NNmodel.getVariables();
//  RooArgSet* params6 = NNsumgauss.getVariables();
//  params6->Print("v");

  TCanvas* Canvas6 = new TCanvas("Canvas6_Born","Canvas6_Born");
  RooPlot* frame = phoNNmin_MLPoutputClusterShapeEnv.frame(Title("#gamma/#pi^{0} Neural network output min"));
  Data.plotOn(frame,Binning(100)); // BOX
//  Data.plotOn(frame,Binning(50)); // QCD GJets
  
//  NNsumgauss.plotOn(frame);
  NNModel.plotOn(frame);
//  NNModel.plotOn(frame, Components("NNBifurGauss_NN1"),LineStyle(kDashed),LineColor(kGreen)); // GJets
  NNModel.plotOn(frame, Components("NNBifurGauss_NN2"),LineStyle(kDashed),LineColor(kRed)); // BOX QCD GJets
  NNModel.plotOn(frame, Components("CrystalBall_NN"),LineStyle(kDashed),LineColor(kGreen)); // BOX QCD
  NNModel.plotOn(frame, Components("NNBifurGauss_NN3"),LineStyle(kDashed),LineColor(kCyan)); // BOX QCD GJets

  //NNmodel.plotOn(frame, Components("NNsumgauss"),LineStyle(kDashed),LineColor(kRed));
  //NNmodel.plotOn(frame,Components("NNLandau"),LineStyle(kDashed),LineColor(kGreen));
  frame->Draw();
  

  return;
}
