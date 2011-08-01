#include "TMVA/Reader.h"
#include "TMVA/Tools.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TBranch.h"
#include "TChain.h"
#include "TFile.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TString.h"
#include "TBits.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TTimeStamp.h"
#include "TSystem.h"
#include "TProof.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <utility>

//#pragma optimize 0

#include "interface/TRootBardak.h"
#include "interface/TRootBeamSpot.h"
#include "interface/TRootCluster.h"
#include "interface/TRootDummyEvent.h"
#include "interface/TRootEcalRecHit.h"
#include "interface/TRootElectron.h"
#include "interface/TRootEvent.h"
#include "interface/TRootJet.h"
#include "interface/TRootMCParticle.h"
#include "interface/TRootMCPhoton.h"
#include "interface/TRootMET.h"
#include "interface/TRootMuon.h"
#include "interface/TRootParticle.h"
#include "interface/TRootPhoton.h"
#include "interface/TRootRun.h"
#include "interface/TRootSignalEvent.h"
#include "interface/TRootSuperCluster.h"
#include "interface/TRootTopTop.h"
#include "interface/TRootTrack.h"
#include "interface/TRootVertex.h"


using namespace std;

double weight_DYToMuMu(int nGenVertices)
{
	double weight[51] = {
//0, 0.192859, 0.37571, 0.98006, 1.47381, 2.13772, 1.97435, 1.75482, 1.61272, 1.30487, 0.858989, 0.593953, 0.406, 0.271559, 0.200834, 0.123192, 0.101752, 0.0724765, 0.0505275, 0.0609286, 0.0265446, 0.0178984, 0.0603881, 0, 0.00990419, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
0, 0.115446, 0.515513, 1.02729, 1.65565, 2.07852, 2.20219, 2.04419, 1.71476, 1.31424, 0.953279, 0.653809, 0.435285, 0.280843, 0.174236, 0.107087, 0.0646172, 0.0383951, 0.0221918, 0.0132036, 0.00758329, 0.00439256, 0.00246895, 0.00144276, 0.000825138, 0.000477362, 0.000267711, 0.000149803, 9.07888e-05, 4.86278e-05, 2.65074e-05, 1.6692e-05, 9.69296e-06, 6.1014e-06, 3.17422e-06, 1.73845e-06, 1.01719e-06, 4.02585e-07, 3.57171e-07, 2.42991e-07, 4.82115e-08, 8.47143e-08, 2.44069e-08, 3.45819e-09, 1.92746e-09, 5.2817e-10, 0, 0, 0, 0, 0
};
	return weight[nGenVertices];
}

double weight_TTJets(int nGenVertices)
{
	double weight[51] = {
//0, 0, 0.333378, 0.723157, 1.19322, 1.49033, 1.58834, 1.44156, 1.2383, 0.980278, 0.764237, 0.616463, 0.502961, 0.415539, 0.340722, 0.312991, 0.247561, 0.235585, 0.22141, 0.235256, 0.247388, 0.283565, 0.460907, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
0, 0, 0.243413, 0.821845, 1.27575, 1.57447, 1.71148, 1.59537, 1.3914, 1.10501, 0.86792, 0.649448, 0.473748, 0.350538, 0.255107, 0.177246, 0.123198, 0.0876263, 0.0682639, 0.0440952, 0.0290569, 0.0199671, 0.013285, 0.00856315, 0.00384906, 0.00349844, 0.00408291, 0.000806618, 0.000526854, 0.000221726, 0.000382953, 0.000130345, 0, 0, 4.71268e-06, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
	return weight[nGenVertices];
}
double weight_WJetsToLNu(int nGenVertices)
{
	double weight[51] = {
//0, 0, 0.330484, 0.67655, 1.23639, 1.44633, 1.56369, 1.63896, 1.20385, 1.06055, 0.727991, 0.54883, 0.514699, 0.452454, 0.377948, 0.366865, 0.244431, 0.161619, 0.1228, 0.162598, 0, 0.05807, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
0, 0, 0.38522, 0.765474, 1.34675, 1.51834, 1.58669, 1.61271, 1.15202, 0.989275, 0.663074, 0.488727, 0.448501, 0.386062, 0.315953, 0.300622, 0.196432, 0.127445, 0.0950729, 0.123675, 0, 0.0427233, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
  return weight[nGenVertices];
}
double  weight_QCDMu(int nGenVertices)
{
  double weight[51] = {
//0, 0, 0.344937, 0.735201, 1.12576, 1.38418, 1.61134, 1.46404, 1.24484, 0.943461, 0.786307, 0.635055, 0.536248, 0.4083, 0.377607, 0.251284, 0.299158, 0.313975, 0.429412, 0.189526, 0.162392, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
0, 0, 0.402067, 0.831834, 1.22624, 1.4531, 1.63504, 1.44059, 1.19124, 0.880055, 0.71619, 0.565509, 0.467278, 0.348386, 0.315668, 0.205911, 0.240412, 0.247585, 0.332455, 0.144157, 0.121435, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
  return weight[nGenVertices];
}

int factorial(int number) {
	int temp;

	if(number <= 1) return 1;

	temp = number * factorial(number - 1);
	return temp;
}


double DeltaR( double eta1, double phi1, double eta2, double phi2)
{
	double DeltaEta = fabs( eta1-eta2 );
	double DeltaPhi = fabs( phi1-phi2 );
	// Returning DeltaPhi in the correct range (0, 2pi)
	while (DeltaPhi >	 TMath::Pi()) DeltaPhi -= 2*TMath::Pi();
	while (DeltaPhi <= -TMath::Pi()) DeltaPhi += 2*TMath::Pi();
	return sqrt(DeltaEta*DeltaEta + DeltaPhi*DeltaPhi);
}

void doGenInfo(TRootParticle* myparticle, TClonesArray* mcParticles, float* particule_trueE, float* particule_truePx, float* particule_truePy, float* particule_truePz, float* particule_trueEta, float* particule_truePhi, int particle_pdgId = 0)
{
  TRootMCParticle* mygenparticle;
  int NbMCpartInCone=0;
  double bestPtdiff=500.0;
  int igpsl=-1;
  for (int igp=0; igp<mcParticles->GetEntriesFast(); igp++) {
    mygenparticle = (TRootMCParticle*) mcParticles->At(igp);
    //cout<<endl<<"deltaR = "<<DeltaR(mygenparticle->Eta(), mygenparticle->Phi(), myparticle->Eta(), myparticle->Phi())<<endl;
    //cout<<"mygenparticle->Mag() = "<<mygenparticle->Mag()<<endl;
    if (DeltaR(mygenparticle->Eta(), mygenparticle->Phi(), myparticle->Eta(), myparticle->Phi())<0.3){
      if ( (mygenparticle->status()==1) && ( (particle_pdgId==0)?true:((mygenparticle->type())==particle_pdgId) ) ){
        //HistoMCpartStatus1InConeId->Fill(mygenparticle->type());
        NbMCpartInCone++;
        if (fabs( (mygenparticle->Pt()) - (myparticle->Pt()) )<bestPtdiff){
          bestPtdiff=fabs(mygenparticle->Pt()-myparticle->Pt());
          igpsl=igp;
        }
      }
    }
  }
  if (igpsl!=-1){
    mygenparticle = (TRootMCParticle*) mcParticles->At(igpsl);
    *particule_trueE = mygenparticle->Energy();
    *particule_truePx = mygenparticle->Px();
    *particule_truePy = mygenparticle->Py();
    *particule_truePz = mygenparticle->Pz();
    *particule_truePhi = mygenparticle->Phi();
    *particule_trueEta = mygenparticle->Eta();

  }
  return;
}


double fEta(double eta) 
{
  double ieta = fabs(eta)*(5/0.087);
  double p0 = 40.2198;  // should be 40.2198
  double p1 = -3.03103e-6;  // should be -3.03103e-6
  double feta = 1; 

  if ( ieta < p0 || fabs(eta) > 1.4442) feta = 1.0; 
  else feta = 1.0/(1.0 + p1*(ieta-p0)*(ieta-p0));

  return feta;
}

//double BremCor(double brem, int EndCaps, int New) 
double BremCor(double brem, int EndCaps, string correctionSet) 
{
  // brem == phiWidth/etaWidth of the SuperCluster 
  // e  == energy of the SuperCluster 
  // first parabola (for br > threshold) 
  // p0 + p1*x + p2*x^2 
  // second parabola (for br <= threshold) 
  // ax^2 + bx + c, make y and y' the same in threshold 
  // y = p0 + p1*threshold + p2*threshold^2  
  // yprime = p1 + 2*p2*threshold 
  // a = p3 
  // b = yprime - 2*a*threshold 
  // c = y - a*threshold^2 - b*threshold 
  double p0 = 0;
  double p1 = 0;
  double p2 = 0;
  double p3 = 0;
  double p4 = 0;
/*
  int offset;
  if ( EndCaps == 0 ) offset = 0; //Barrel
  else if ( EndCaps == 1 ) offset = 20; //End caps
  else {
    // not supported, produce no correction
    return 1.0;
  }
*/
  //Make No Corrections if brem is invalid! 
	//cout<<endl<<setprecision( 10 )<<"brem in function= "<<brem<<endl;
  if ( brem == 0 ) return 1.0;

	if(EndCaps == 1) //End caps
	{
		//double bremLowThr  = 0.9;
		double bremLowThr  = 0.8999999762;
		//double bremHighThr = 6.5;
		double bremHighThr = 6.5000000000;
//  if(New == 2) 
		if( correctionSet == "Louis" ) 
		{
			bremLowThr  = 0.8;
			bremHighThr = 4.5;
		}
		if ( brem < bremLowThr  ) brem = bremLowThr;
		if ( brem > bremHighThr ) brem = bremHighThr;
//  if(New == 0)
  	if( correctionSet == "START42_V11" )
  	{
  		// Parameters provided in cfg file
  		//p0 = -0.12139999866485595703125;
   		//p0 = -0.07945;
   		p0 = -0.0794499964;
  		//p1 = 0.2362000048160552978515625;
   		//p1 = 0.1298;
   		p1 = 0.1298000067;
  		//p2 = 0.884700000286102294921875;
   		//p2 = 0.9147;
   		p2 = 0.9146999717;
  		//p3 = -0.00193000002764165401458740234375;
   		//p3 = -0.001565;
   		p3 = -0.0015650000;
  		//p4 = 1.05700004100799560546875;
   		//p4 = 0.9;
   		p4 = 0.8999999762;
 		}
//  if(New == 1)
		if( correctionSet == "Anne-Fleur" )
  	{
    	// Parameters provided in cfg file
      p0 = -0.07667;
      p1 = 0.1407;
      p2 = 0.9157;
      p3 = 0.00251;
      p4 = 1.117;
  	}
//  if(New == 2)//mes corrections
		if( correctionSet == "Louis" )
  	{
      p0 = -0.004003;
      p1 = 0.003938;
      p2 = 0.9638;
      p3 = -0.07402;
      p4 = 30.52;
  	}
	}

if(EndCaps == 0) //Barrel
 {
  //double bremLowThr  = 1.1;
  double bremLowThr  = 1.1000000238;
  //double bremHighThr = 8.0;
  double bremHighThr = 8.0000000000;
//  if(New == 2)
	if( correctionSet == "Louis" )
  {
        bremLowThr  = 0.7;
        bremHighThr = 4.9;
  }
  if ( brem < bremLowThr  ) brem = bremLowThr;
  if ( brem > bremHighThr ) brem = bremHighThr;

//  if(New == 0)
	if( correctionSet == "START42_V11" )
  {
	// Parameters provided in cfg file
  	//p0 = -0.051849998533725738525390625;
  	//p0 = -0.05289;
  	p0 = -0.0528899990;
  	//p1 = 0.135399997234344482421875;
  	//p1 = 0.1374;  
  	p1 = 0.1374000013;  
  	//p2 = 0.91649997234344482421875;
  	//p2 = 0.9141;
  	p2 = 0.9140999913;
  	//p3 = -0.000562599976547062397003173828125;
  	//p3 = -0.000669;
  	p3 = -0.0006690000;
  	//p4 = 1.3849999904632568359375;
  	//p4 = 1.38;
  	p4 = 1.3799999952;
  }

//  if(New == 1)
	if( correctionSet == "Anne-Fleur" )
  {
        // Parameters provided in cfg file
        p0 = -0.002362;
        p1 = 0.004314;
        p2 = 1.001;
        p3 = 0.0003413;
        p4 = 3.124;
  }

//  if(New == 2)//mes corrections
	if( correctionSet == "Louis" )
  {
        p0 = -0.001492;
        p1 = 0.0001637;
        p2 = 1.003;
        p3 = -0.03081;
        p4 = 136.7;
  }

 }

  double threshold = p4;

  double y = p0*threshold*threshold + p1*threshold + p2;
  double yprime = 2*p0*threshold + p1;
  double a = p3;
  double b = yprime - 2*a*threshold;
  double c = y - a*threshold*threshold - b*threshold;

  double bremCorrection = 1.0;
  if ( brem < threshold ) bremCorrection = p0*brem*brem + p1*brem + p2;
  else bremCorrection = a*brem*brem + b*brem + c;

  return 1.0 / bremCorrection;
}

//double EtEtaCor(double et, double eta, int EndCaps, int New) 
double EtEtaCor(double et, double eta, int EndCaps, string correctionSet) 
{ 
  
  double etEtaCorrection = 0.; 
  if(EndCaps != 0 && EndCaps != 1) return 1.0; 

  // Barrel 
  if ( EndCaps == 0 ) 
  { 
    /*double p0 = (params_->params())[ 9 + offset]  + (params_->params())[10 + offset]/ (et + (params_->params())[11 + offset]) + (params_->params())[12 + offset]/(et*et);  
    double p1 = (params_->params())[13 + offset]  + (params_->params())[14 + offset]/ (et + (params_->params())[15 + offset]) + (params_->params())[16 + offset]/(et*et);  
 
    etEtaCorrection = p0 +  p1 * atan((params_->params())[17 + offset]*((params_->params())[18 + offset]-fabs(eta))) + (params_->params())[19 + offset] * fabs(eta); 
 */
//	if(New == 0)
		if( correctionSet == "START42_V11" )
  	{

		//double p0 = 1.00199997425079345703125 -0.742399990558624267578125/ (et + 0) + 0/(et*et);
		//double p0 = 1.000 -0.698 / (et + 0) + 0/(et*et);
		double p0 = 1.0000000000 -0.6980000138 / (et + 0.0000000000) + 0.0000000000/(et*et);
		//double p1 = 0  + 0.555800020694732666015625/ (et + 2.375) + 0.18690000474452972412109375/(et*et);
		//double p1 = 0  + 0.6605/ (et + 8.825) + 0.841/(et*et);
		double p1 = 0.0000000000  + 0.6604999900/ (et + 8.8249998093) + 0.8410000205/(et*et);
		//etEtaCorrection = p0 +  p1 * atan(7.599999904632568359375*(1.08099997043609619140625-fabs(eta))) -0.00181000004522502422332763671875 * fabs(eta);
		//etEtaCorrection = p0 +  p1 * atan(7.6*(1.081-fabs(eta))) -0.00181 * fabs(eta);
		etEtaCorrection = p0 +  p1 * atan(7.5999999046*(1.0809999704-fabs(eta))) -0.0018100000 * fabs(eta);
		//cout<<endl<<endl<<endl<<"p0 = "<<p0<<endl<<"p1 = "<<p1<<endl;
		//cout<<"fCorr = "<<etEtaCorrection;
		if ( etEtaCorrection < 0.5 ) etEtaCorrection = 0.5;
  		if ( etEtaCorrection > 1.5 ) etEtaCorrection = 1.5;
	}

//	if(New == 1)
	if( correctionSet == "Anne-Fleur" )
        {
                double p0 = 0.9963 -0.1158/ (et + -4.189);
                double p1 = 0.9009/ (et + 39.67) + 1.253/(et*et);
                etEtaCorrection = p0 +  p1 * atan(7.6*(1.081-fabs(eta))) -0.00181 * fabs(eta);
        }
 } 
  
  //End Caps
  if ( EndCaps == 1 ) 
  {
   /* 
    double p0 = (params_->params())[ 9 + offset] + (params_->params())[10 + offset]/sqrt(et); 
    double p1 = (params_->params())[11 + offset] + (params_->params())[12 + offset]/sqrt(et); 
    double p2 = (params_->params())[13 + offset] + (params_->params())[14 + offset]/sqrt(et); 
    double p3 = (params_->params())[15 + offset] + (params_->params())[16 + offset]/sqrt(et); 
  
    etEtaCorrection = p0 + p1*fabs(eta) + p2*eta*eta + p3/fabs(eta); 
*/
//	if(New == 0)
	if( correctionSet == "START42_V11" )
        {
		//double p0 = 2.2130000591278076171875 -17.29000091552734375/sqrt(et);
		//double p0 = -3.516 -2.362/sqrt(et);	
		double p0 = -3.5160000324 -2.3619999886/sqrt(et);	
		//double p1 = -0.59899997711181640625 + 8.87399959564208984375/sqrt(et);
		//double p1 = 2.151 + 1.572/sqrt(et);
		double p1 = 2.1510000229 + 1.5720000267/sqrt(et);
		//double p2 = 0.0963200032711029052734375 -1.4570000171661376953125/sqrt(et); 
    //double p2 = -0.336 -0.2807/sqrt(et);
    double p2 = -0.3359999955 -0.2806999981/sqrt(et);
		//double p3 = -0.758400022983551025390625 + 10.28999996185302734375/sqrt(et); 
		//double p3 = 3.2 + 0/sqrt(et); 	
		double p3 = 3.2000000477 + 0.0000000000/sqrt(et); 	
		//etEtaCorrection = p0 + p1*fabs(eta) + p2*eta*eta + p3/fabs(eta);
		etEtaCorrection = p0 + p1*fabs(eta) + p2*eta*eta + p3/fabs(eta);
		//cout<<endl<<endl<<endl<<"p0 = "<<p0<<endl<<"p1 = "<<p1<<endl<<"p2 = "<<p2<<endl<<"p3 = "<<p3<<endl;
        	//cout<<"fCorr = "<<etEtaCorrection; 
		if ( etEtaCorrection < 0.5 ) etEtaCorrection = 0.5;
  		if ( etEtaCorrection > 1.5 ) etEtaCorrection = 1.5;
	}

//	if(New == 1)
	if( correctionSet == "Anne-Fleur" )
        {
                double p0 = -1.513 -0.4142/sqrt(et);
                double p1 = 1.239 + 0.2625/sqrt(et);
                double p2 = -0.2016 -0.02905/sqrt(et);
                double p3 = 1.7 + 0.0/sqrt(et);
				if ( fabs(eta) < 1.6 ) eta = 1.6;
        if ( fabs(eta) > 2.6 ) eta = 2.6;
				etEtaCorrection = p0 + p1*fabs(eta) + p2*eta*eta + p3/fabs(eta);
		
    		if ( 1./etEtaCorrection > 1.2 ) return et/1.2;
    		if ( 1./etEtaCorrection < 0.5 ) return et/0.5;
        }
 } 
 
  // cap the correction at 50%
  //if ( etEtaCorrection < 0.5 ) etEtaCorrection = 0.5;  
  //if ( etEtaCorrection > 1.5 ) etEtaCorrection = 1.5;   
 
  //std::cout << "ECEC fEtEta " << et/etEtaCorrection << std::endl;
  //return et/etEtaCorrection; 
  return 1.0/etEtaCorrection;
}

double photonManualCorrectionFactor(TRootPhoton *myphoton, string correctionSet)
{
//	cout << "myphoton->superCluster()->Eta()= " << myphoton->superCluster()->Eta() << endl;
	double f_eta = fEta(myphoton->superCluster()->Eta());
//	cout << "f_eta= " << f_eta << endl;

	double brem = (double)(myphoton->superCluster()->phiWidth()) / (double)(myphoton->superCluster()->etaWidth());
//	cout << "brem= " << brem << endl;
//	cout << "myphoton->isEEPho()= " << myphoton->isEEPho() << endl;
	double f_brem = BremCor(brem, myphoton->isEEPho(), correctionSet);
//	cout << "f_brem= " << f_brem << endl;

//	cout << "myphoton->superCluster()->rawEnergy()= " << myphoton->superCluster()->rawEnergy() << endl;
//	cout << "myphoton->preshowerEnergy()= " << myphoton->preshowerEnergy() << endl;
	double sc_e = (myphoton->isEBPho()==1) ? (f_eta * myphoton->superCluster()->rawEnergy()) : (myphoton->superCluster()->rawEnergy() + myphoton->preshowerEnergy());
//	cout << "sc_e= " << sc_e << endl;
	double sc_et = sc_e * (sin(myphoton->superCluster()->Theta()));
//	cout << "sc_et= " << sc_et << endl;
	double f_et_eta = EtEtaCor(f_brem * sc_et, myphoton->superCluster()->Eta(), myphoton->isEEPho(), correctionSet);
//	cout << "f_et_eta= " <<  f_et_eta << endl;

//	cout << "myphoton->Energy()= " << myphoton->Energy() << endl;
	if( (myphoton->isEBPho()) && (myphoton->r9()<0.94) )
	{
		cout << "f_et_eta * f_brem * f_eta * myphoton->superCluster()->rawEnergy()= " << f_et_eta * f_brem * f_eta * myphoton->superCluster()->rawEnergy() << endl;
		return (double)(f_et_eta * f_brem * f_eta * myphoton->superCluster()->rawEnergy()) / (double)(myphoton->Energy());
	}
	if( (myphoton->isEBPho()) && (myphoton->r9()>0.94) )
	{
		cout << "f_eta * myphoton->e5x5()= " << f_eta * myphoton->e5x5() << endl;
		return (double)(f_eta * myphoton->e5x5()) / (double)(myphoton->Energy());
	}
	if( (myphoton->isEEPho()) && (myphoton->r9()<0.95) )
	{
//		cout << "f_et_eta * (myphoton->superCluster()->rawEnergy() + myphoton->preshowerEnergy())= " << f_et_eta * (myphoton->superCluster()->rawEnergy() + myphoton->preshowerEnergy()) << endl;
//		return (double)(f_et_eta * (myphoton->superCluster()->rawEnergy() + myphoton->preshowerEnergy())) / (double)(myphoton->Energy());
		cout << "f_et_eta * f_brem * (myphoton->superCluster()->rawEnergy() + myphoton->preshowerEnergy())= " << f_et_eta * f_brem * (myphoton->superCluster()->rawEnergy() + myphoton->preshowerEnergy()) << endl;
		return (double)(f_et_eta * f_brem * (myphoton->superCluster()->rawEnergy() + myphoton->preshowerEnergy())) / (double)(myphoton->Energy());
	}
	if( (myphoton->isEEPho()) && (myphoton->r9()>0.94) )
	{
		cout << "myphoton->e5x5()= " << endl;
		return (double)(myphoton->e5x5()) / (double)(myphoton->Energy());
	}
}



void findConversionMCtruth(TRootPhoton *myPhoton, TClonesArray *theMCphotons, int &Photon_MCisConverted, float &Photon_MCconvEoverP, float &Photon_MCconvMass, float &Photon_MCconvCotanTheta, float &Photon_MCconvVertexX, float &Photon_MCconvVertexY, float &Photon_MCconvVertexZ){
float dr = 0;
int theIteMin = -1000;
float theDiff;
float theMinDiff = 100000;
for (unsigned int i =0 ; i < theMCphotons->GetEntriesFast() ; i++){
	TRootMCPhoton *theMCphoton = (TRootMCPhoton*) theMCphotons->At(i);
	//dr = DeltaR(myPhoton->Phi(),theMCphoton->Phi(),myPhoton->Eta(),theMCphoton->Eta());
	dr = DeltaR(myPhoton->Eta(),myPhoton->Phi(),theMCphoton->Eta(),theMCphoton->Phi());
	cout<<endl<<"dr = "<<dr<<endl;
	if (dr < 0.3){
		theDiff = fabs(theMCphoton->Pt()-myPhoton->Pt());
		if (theDiff < theMinDiff){
			theMinDiff = theDiff;
			theIteMin = i;	
		}
	}
}
if (theIteMin == -1000){
	Photon_MCisConverted = 0;
	Photon_MCconvEoverP = -10000;
	Photon_MCconvMass = -10000;
	Photon_MCconvCotanTheta = -10000;
	Photon_MCconvVertexX = -10000;
	Photon_MCconvVertexY = -10000;
	Photon_MCconvVertexZ = -10000;
}
else {
	TRootMCPhoton *theMCphoton = (TRootMCPhoton*) theMCphotons->At(theIteMin);
	Photon_MCisConverted = 1;
	Photon_MCconvEoverP = theMCphoton->convEoverP();
	Photon_MCconvMass = theMCphoton->convMass();
	Photon_MCconvCotanTheta = theMCphoton->convDeltaCotanTheta();
	Photon_MCconvVertexX = theMCphoton->conv_vx();
	Photon_MCconvVertexY = theMCphoton->conv_vy();
	Photon_MCconvVertexZ = theMCphoton->conv_vz();

}
}




int main(int argc, char *argv[]);


  // ____________________________________________
  // Event information
  // ____________________________________________
  extern Int_t iEvent, iEventID, iLumiID, iRunID;
  extern Int_t isSignalApplied, isStewApplied, isZJetsApplied;

  extern Int_t isBeforeAllCuts, isAfterCutPthatFilter, isAfterCutZJETVETO;
  extern Int_t isVeryLooseMMG, isLooseMMG, isMM, isTightMMG, isMMGCandidate;
  extern Int_t isAfterFSRCut1, isAfterFSRCut2, isAfterFSRCut3;
  extern Int_t isAfterFSRCut4, isMultipleCandidate, isAfterCut5, isAfterCut6, isAfterCut7, isAfterCut8, isAfterCut9, isAfterCut10;
  extern Int_t isSelected;

  extern Int_t isNotCommissionned;
  
  extern Int_t Muon_eventPassHLT_Mu11;
  extern Int_t nVertices;
  extern Int_t nGenVertices;
  extern Float_t weight_pileUp, weight_Xsection;

  // ____________________________________________
  // Muon variables 
  // ____________________________________________
  extern Int_t NbMuons;
  
  extern Float_t Pt_allMuons, Eta_allMuons, Phi_allMuons, Charge_allMuons;
// (M minus charge, P plus charge), (F far, N near), (L leading, S subleading)
  extern Float_t MuonM_Pt, MuonP_Pt, MuonN_Pt, MuonF_Pt, MuonL_Pt, MuonS_Pt;
  extern Float_t MuonM_Eta, MuonP_Eta, MuonN_Eta, MuonF_Eta, MuonL_Eta, MuonS_Eta;
  extern Float_t MuonM_Phi, MuonP_Phi, MuonN_Phi, MuonF_Phi, MuonL_Phi, MuonS_Phi;
  extern Int_t MuonF_Charge, MuonN_Charge, MuonL_Charge, MuonS_Charge;

  extern Float_t MuonM_isoR03_emEt, MuonP_isoR03_emEt, MuonN_isoR03_emEt, MuonF_isoR03_emEt, MuonL_isoR03_emEt, MuonS_isoR03_emEt; 
  extern Float_t MuonM_isoR03_hadEt, MuonP_isoR03_hadEt, MuonN_isoR03_hadEt, MuonF_isoR03_hadEt, MuonL_isoR03_hadEt, MuonS_isoR03_hadEt;
  extern Float_t MuonM_isoR03_hoEt, MuonP_isoR03_hoEt, MuonN_isoR03_hoEt, MuonF_isoR03_hoEt, MuonL_isoR03_hoEt, MuonS_isoR03_hoEt;   
  extern Float_t MuonM_isoR03_nJets, MuonP_isoR03_nJets, MuonN_isoR03_nJets, MuonF_isoR03_nJets, MuonL_isoR03_nJets, MuonS_isoR03_nJets;
  extern Float_t MuonM_isoR03_nTracks, MuonP_isoR03_nTracks, MuonN_isoR03_nTracks, MuonF_isoR03_nTracks, MuonL_isoR03_nTracks, MuonS_isoR03_nTracks;
  extern Float_t MuonM_isoR03_sumPt, MuonP_isoR03_sumPt, MuonN_isoR03_sumPt, MuonF_isoR03_sumPt, MuonL_isoR03_sumPt, MuonS_isoR03_sumPt;
    
  extern Float_t MuonM_isoR05_emEt, MuonP_isoR05_emEt, MuonN_isoR05_emEt, MuonF_isoR05_emEt, MuonL_isoR05_emEt, MuonS_isoR05_emEt;
  extern Float_t MuonM_isoR05_hadEt, MuonP_isoR05_hadEt, MuonN_isoR05_hadEt, MuonF_isoR05_hadEt, MuonL_isoR05_hadEt, MuonS_isoR05_hadEt;
  extern Float_t MuonM_isoR05_hoEt, MuonP_isoR05_hoEt, MuonN_isoR05_hoEt, MuonF_isoR05_hoEt, MuonL_isoR05_hoEt, MuonS_isoR05_hoEt;
  extern Float_t MuonM_isoR05_nJets, MuonP_isoR05_nJets, MuonN_isoR05_nJets, MuonF_isoR05_nJets, MuonL_isoR05_nJets, MuonS_isoR05_nJets;
  extern Float_t MuonM_isoR05_nTracks, MuonP_isoR05_nTracks, MuonN_isoR05_nTracks, MuonF_isoR05_nTracks, MuonL_isoR05_nTracks, MuonS_isoR05_nTracks;
  extern Float_t MuonM_isoR05_sumPt, MuonP_isoR05_sumPt, MuonN_isoR05_sumPt, MuonF_isoR05_sumPt, MuonL_isoR05_sumPt, MuonS_isoR05_sumPt;

  // ____________________________________________
  // Photon variables
  // ___________________________________________
  extern Int_t NbPhotons;
  extern Float_t Pt_allPhotons, Eta_allPhotons, Phi_allPhotons, Cross_allPhotons;
  extern Int_t isEBorEE_allPhotons, isEB_allPhotons, isEE_allPhotons, isEEP_allPhotons, isEEM_allPhotons;
  extern Float_t Photon_Eta, Photon_Phi;
  extern Int_t Photon_isEBorEE, Photon_isEB, Photon_isEE, Photon_isEEP, Photon_isEEM;

  extern Int_t Photon_hasPixelSeed, Photon_isAlsoElectron, Photon_Nclusters, Photon_nBasicClusters, Photon_nXtals;
  extern Int_t Photon_isTightPhoton, Photon_isLoosePhoton;
  extern Int_t Photon_convNTracks, Photon_isConverted;
  extern Float_t Photon_convEoverP, Photon_convMass, Photon_convCotanTheta, Photon_convLikely, Photon_convVertexX, Photon_convVertexY, Photon_convVertexZ;
  extern Float_t Photon_E, Photon_Et, Photon_E2x2, Photon_E3x3, Photon_E5x5, Photon_Emax, Photon_E2nd;
  extern Float_t Photon_r19, Photon_r9, Photon_cross;
  extern Float_t Photon_caloConeSize, Photon_PreshEnergy, Photon_HoE;
  extern Float_t Photon_sigmaEtaEta, Photon_sigmaIetaIeta;
  extern Float_t Photon_covEtaEta, Photon_covPhiPhi, Photon_covEtaPhi;
  extern Float_t Photon_etaWidth, Photon_phiWidth;
  extern Float_t Photon_dR03isoEcalRecHit, Photon_dR03isoHcalRecHit, Photon_dR03isoSolidTrkCone, Photon_dR03isoHollowTrkCone, Photon_dR03isoNTracksSolidCone, Photon_dR03isoNTracksHollowCone;
  extern Float_t Photon_dR04isoEcalRecHit, Photon_dR04isoHcalRecHit, Photon_dR04isoSolidTrkCone, Photon_dR04isoHollowTrkCone, Photon_dR04isoNTracksSolidCone, Photon_dR04isoNTracksHollowCone;
  extern Float_t Photon_seedTime, Photon_seedFlag;
  extern Int_t Photon_seedPosition1, Photon_seedPosition2;
  extern Float_t Photon_SC_Eta, Photon_SC_Phi, Photon_SC_brem;
  extern Float_t Photon_SC_E, Photon_SC_Et, Photon_SC_rawE, Photon_SC_rawEt;
	extern Float_t Photon_lambdaRatio, Photon_ratioSeed, Photon_ratioS4, Photon_lamdbaDivCov;
	extern Float_t Photon_SC_rawE_x_fEta, Photon_SC_rawE_x_fEta_x_fBrem, Photon_SC_rawE_x_fEta_x_fBrem_AF, Photon_SC_rawE_x_fEta_x_fBrem_L, Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta, Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta, Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta;
	extern Float_t Photon_secondMomentMaj, Photon_secondMomentMin, Photon_secondMomentAlpha;


  // ____________________________________________
  // mugamma / mumu / mumugamma information
  // ____________________________________________

  extern Float_t Mmumu, Mmumugamma, Mmumugamma_5x5, Mmumugamma_SC, Mmumugamma_SCraw, Mmumugamma_SCraw_fEta, Mmumugamma_SCraw_fEta_fBrem, Mmumugamma_SCraw_fEta_fBrem_AF, Mmumugamma_SCraw_fEta_fBrem_L, Mmumugamma_SCraw_fEta_fBrem_fEtEta, Mmumugamma_SCraw_fEta_fBrem_AF_fEtEta, Mmumugamma_SCraw_fEta_fBrem_L_fEtEta;
  extern Float_t Ptmumu;
  extern Float_t deltaRNear, deltaRFar, deltaRMinus, deltaRPlus, deltaRLeading, deltaRSubleading;
  extern Float_t mmg_k, mmg_ik, mmg_s, mmg_logk, mmg_logik, mmg_logs;
  extern Float_t mmg_k_5x5, mmg_ik_5x5, mmg_s_5x5, mmg_logk_5x5, mmg_logik_5x5, mmg_logs_5x5;
  extern Float_t mmg_k_SC, mmg_ik_SC, mmg_s_SC, mmg_logk_SC, mmg_logik_SC, mmg_logs_SC;
  extern Float_t mmg_k_SCraw, mmg_ik_SCraw, mmg_s_SCraw, mmg_logk_SCraw, mmg_logik_SCraw, mmg_logs_SCraw;
  extern Float_t mmg_k_SCraw_fEta, mmg_ik_SCraw_fEta, mmg_s_SCraw_fEta, mmg_logk_SCraw_fEta, mmg_logik_SCraw_fEta, mmg_logs_SCraw_fEta;
  extern Float_t mmg_ik_SCraw_fEta_fBrem, mmg_ik_SCraw_fEta_fBrem_AF, mmg_ik_SCraw_fEta_fBrem_L, mmg_ik_SCraw_fEta_fBrem_fEtEta, mmg_ik_SCraw_fEta_fBrem_AF_fEtEta, mmg_ik_SCraw_fEta_fBrem_L_fEtEta;

  // ____________________________________________
	// Neural Network variables
  // ____________________________________________
	extern Float_t Photon_NNshapeOutput;

  // ____________________________________________
  // MC Truth
  // ___________________________________________

  extern Float_t Photon_MC_E, Photon_MC_Px, Photon_MC_Py, Photon_MC_Pz, Photon_MC_Phi, Photon_MC_Eta;
  extern Int_t Photon_MCisConverted;
  extern Float_t Photon_MCconvEoverP, Photon_MCconvMass, Photon_MCconvCotanTheta, Photon_MCconvVertexX, Photon_MCconvVertexY, Photon_MCconvVertexZ;
  extern Float_t MuonM_MC_E, MuonM_MC_Px, MuonM_MC_Py, MuonM_MC_Pz, MuonM_MC_Phi, MuonM_MC_Eta;
  extern Float_t MuonP_MC_E, MuonP_MC_Px, MuonP_MC_Py, MuonP_MC_Pz, MuonP_MC_Phi, MuonP_MC_Eta;
  extern Float_t MuonN_MC_E, MuonN_MC_Px, MuonN_MC_Py, MuonN_MC_Pz, MuonN_MC_Phi, MuonN_MC_Eta;
  extern Float_t MuonF_MC_E, MuonF_MC_Px, MuonF_MC_Py, MuonF_MC_Pz, MuonF_MC_Phi, MuonF_MC_Eta;
  extern Float_t MuonL_MC_E, MuonL_MC_Px, MuonL_MC_Py, MuonL_MC_Pz, MuonL_MC_Phi, MuonL_MC_Eta;
  extern Float_t MuonS_MC_E, MuonS_MC_Px, MuonS_MC_Py, MuonS_MC_Pz, MuonS_MC_Phi, MuonS_MC_Eta;
  extern Float_t Photon_SC_rawE_x_fEta_o_MC_E, Photon_E_o_MC_E, Photon_SC_rawE_x_fEta_x_fBrem_o_MC_E, Photon_SC_rawE_x_fEta_x_fBrem_AF_o_MC_E, Photon_SC_rawE_x_fEta_x_fBrem_L_o_MC_E, Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta_o_MC_E, Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta_o_MC_E, Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta_o_MC_E;

  extern Float_t Mmumu_Photon_MC, Mmumugamma_Photon_MC, mmg_k_Photon_MC, mmg_ik_Photon_MC, mmg_s_Photon_MC, mmg_logk_Photon_MC, mmg_logik_Photon_MC, mmg_logs_Photon_MC;
  extern Float_t Mmumu_Muons_MC, Mmumugamma_Muons_MC, mmg_k_Muons_MC, mmg_ik_Muons_MC, mmg_s_Muons_MC, mmg_logk_Muons_MC, mmg_logik_Muons_MC, mmg_logs_Muons_MC;
  extern Float_t Mmumu_MMG_MC, Mmumugamma_MMG_MC, mmg_k_MMG_MC, mmg_ik_MMG_MC, mmg_s_MMG_MC, mmg_logk_MMG_MC, mmg_logik_MMG_MC, mmg_logs_MMG_MC;



//int FillMMG(TRootPhoton* myphoton, TRootMuon* mymuon1, TRootMuon* mymuon2, double EScale, bool doMC, TClonesArray* mcParticles);



int FillMMG(TRootPhoton* myphoton, TRootMuon* mymuon1, TRootMuon* mymuon2, double EScale, bool doMC, bool doPhotonConversionMC, TClonesArray* mcParticles, TClonesArray* mcPhotons, TMVA::Reader* reader){

      // Fill photon stuff
      Photon_Eta = myphoton->Eta();
      Photon_Phi = myphoton->Phi();
      if( myphoton->isEBPho() ){ Photon_isEB=1; } else { Photon_isEB=0; }
      if( myphoton->isEEPho() ){ Photon_isEE=1; } else { Photon_isEE=0; }
      if( myphoton->isEEPho() && myphoton->Eta()<0 ){ Photon_isEEM=1; } else { Photon_isEEM=0; }
      if( myphoton->isEEPho() && myphoton->Eta()>0 ){ Photon_isEEP=1; } else { Photon_isEEP=0; }
      Photon_hasPixelSeed = myphoton->hasPixelSeed();
      Photon_isAlsoElectron = myphoton->isAlsoElectron();
      Photon_Nclusters = myphoton->nbClusters();
  //    cout << "myphoton->superCluster()=" << myphoton->superCluster() << endl; // FIXME
      Photon_nBasicClusters = myphoton->superCluster()->nBasicClusters();
      Photon_isTightPhoton = myphoton->isTightPhoton();
      Photon_isLoosePhoton = myphoton->isLoosePhoton();

      Photon_isConverted = 0;
      if (myphoton->convNTracks() > 0 ) Photon_isConverted = 1;	
      Photon_convNTracks = myphoton->convNTracks();
      Photon_convEoverP = myphoton->convEoverP();
      Photon_convMass = myphoton->convMass();
      Photon_convCotanTheta = myphoton->convCotanTheta();
      Photon_convLikely = myphoton->convLikely();
      Photon_convVertexX = myphoton->convVertex().x();
      Photon_convVertexY = myphoton->convVertex().y();
      Photon_convVertexZ = myphoton->convVertex().z();

      if (doPhotonConversionMC)
      {
		findConversionMCtruth(myphoton, mcPhotons, Photon_MCisConverted, Photon_MCconvEoverP, Photon_MCconvMass, Photon_MCconvCotanTheta, Photon_MCconvVertexX, Photon_MCconvVertexY, Photon_MCconvVertexZ);
      }



 
      Photon_E = EScale*(myphoton->Energy());
      Photon_Et = EScale*(myphoton->Et());
      Photon_E2x2 = EScale*(myphoton->e2x2());
      Photon_E3x3 = EScale*(myphoton->e3x3());
      Photon_E5x5 = EScale*(myphoton->e5x5());
      Photon_Emax = EScale*(myphoton->eMax());
      Photon_E2nd = EScale*(myphoton->e2nd());
      Photon_r19 = myphoton->r19();
      Photon_r9 = myphoton->r9();
  //FIXME   Photon_cross = 1-((myphoton->superCluster()->s4())/(myphoton->superCluster()->eMax()));   
      Photon_caloConeSize = myphoton->caloConeSize();
      Photon_PreshEnergy = myphoton->preshowerEnergy();
      Photon_HoE = myphoton->hoe();
      Photon_sigmaEtaEta = myphoton->sigmaEtaEta();
      Photon_sigmaIetaIeta = myphoton->sigmaIetaIeta();
      Photon_covEtaEta = myphoton->covEtaEta();
      Photon_covPhiPhi = myphoton->covPhiPhi();
      Photon_covEtaPhi = myphoton->covEtaPhi();
      Photon_etaWidth = myphoton->superCluster()->etaWidth();
      Photon_phiWidth = myphoton->superCluster()->phiWidth();
      Photon_dR03isoEcalRecHit = myphoton->dR03IsolationEcalRecHit();
      Photon_dR03isoHcalRecHit = myphoton->dR03IsolationHcalRecHit();
      Photon_dR03isoSolidTrkCone = myphoton->dR03IsolationSolidTrkCone();
      Photon_dR03isoHollowTrkCone = myphoton->dR03IsolationHollowTrkCone();
      Photon_dR03isoNTracksSolidCone = myphoton->dR03IsolationNTracksSolidCone();
      Photon_dR03isoNTracksHollowCone = myphoton->dR03IsolationNTracksHollowCone();
      Photon_dR04isoEcalRecHit = myphoton->dR04IsolationEcalRecHit();
      Photon_dR04isoHcalRecHit = myphoton->dR04IsolationHcalRecHit();
      Photon_dR04isoSolidTrkCone = myphoton->dR04IsolationSolidTrkCone();
      Photon_dR04isoHollowTrkCone = myphoton->dR04IsolationHollowTrkCone();
      Photon_dR04isoNTracksSolidCone = myphoton->dR04IsolationNTracksSolidCone();
      Photon_dR04isoNTracksHollowCone = myphoton->dR04IsolationNTracksHollowCone();
      Photon_seedTime = myphoton->superCluster()->seedTime();
      Photon_seedFlag = myphoton->superCluster()->seedRecoFlag();
      Photon_seedPosition1 = myphoton->superCluster()->seedPosition1();
      Photon_seedPosition2 = myphoton->superCluster()->seedPosition2();
      Photon_SC_Eta = myphoton->superCluster()->Eta();
      Photon_SC_Phi = myphoton->superCluster()->Phi();
      Photon_SC_brem = (double)(Photon_phiWidth) / (double)(Photon_etaWidth);
      Photon_SC_E = myphoton->superCluster()->Mag();
      Photon_SC_Et = Photon_SC_E * (sin(myphoton->superCluster()->Theta()));
      Photon_SC_rawE = myphoton->superCluster()->rawEnergy();
      Photon_SC_rawEt = Photon_SC_rawE * (sin(myphoton->superCluster()->Theta()));
			Photon_lambdaRatio = 0.0;
	    if ((Photon_covEtaEta+Photon_covPhiPhi+sqrt((Photon_covEtaEta-Photon_covPhiPhi)*(Photon_covEtaEta-Photon_covPhiPhi)+4*Photon_covEtaPhi*Photon_covEtaPhi))!=0) Photon_lambdaRatio = (Photon_covEtaEta+Photon_covPhiPhi-sqrt((Photon_covEtaEta-Photon_covPhiPhi)*(Photon_covEtaEta-Photon_covPhiPhi)+4*Photon_covEtaPhi*Photon_covEtaPhi))/(Photon_covEtaEta+Photon_covPhiPhi+sqrt((Photon_covEtaEta-Photon_covPhiPhi)*(Photon_covEtaEta-Photon_covPhiPhi)+4*Photon_covEtaPhi*Photon_covEtaPhi));
			Photon_ratioSeed = 0.0;
			if (Photon_SC_rawE != 0) Photon_ratioSeed = Photon_Emax/Photon_SC_rawE; 
			Photon_ratioS4 = 0.0;
			if (Photon_E5x5 != 0)  Photon_ratioS4 = Photon_E2x2/Photon_E5x5;
			Photon_lamdbaDivCov = 0.0;
			if (Photon_covEtaEta != 0) Photon_lamdbaDivCov = (Photon_covEtaEta+Photon_covPhiPhi-sqrt((Photon_covEtaEta-Photon_covPhiPhi)*(Photon_covEtaEta-Photon_covPhiPhi)+4*Photon_covEtaPhi*Photon_covEtaPhi))/Photon_covEtaEta;
			Photon_SC_rawE_x_fEta = Photon_SC_rawE * fEta(Photon_SC_Eta);
			
//			Photon_SC_rawE_x_fEta_x_fBrem = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), 0);
//			Photon_SC_rawE_x_fEta_x_fBrem_AF = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), 1);
//			Photon_SC_rawE_x_fEta_x_fBrem_L = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), 2);
			Photon_SC_rawE_x_fEta_x_fBrem = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11");
			Photon_SC_rawE_x_fEta_x_fBrem_AF = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), "Anne-Fleur");
			Photon_SC_rawE_x_fEta_x_fBrem_L = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), "Louis");

			float etraw_fEta_fBrem = Photon_SC_rawE_x_fEta_x_fBrem/cosh(Photon_SC_Eta);
			float etraw_fEta_fBrem_AF = Photon_SC_rawE_x_fEta_x_fBrem_AF/cosh(Photon_SC_Eta);
			float etraw_fEta_fBrem_L = Photon_SC_rawE_x_fEta_x_fBrem_L/cosh(Photon_SC_Eta);

//			Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), 0) * EtEtaCor(etraw_fEta_fBrem, abs(Photon_SC_Eta), myphoton->isEEPho(), 0);
//			Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), 0) * EtEtaCor(etraw_fEta_fBrem_AF, abs(Photon_SC_Eta), myphoton->isEEPho(), 1);
//			Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), 0) * EtEtaCor(etraw_fEta_fBrem_L, abs(Photon_SC_Eta), myphoton->isEEPho(), 1);
			Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11") * EtEtaCor(etraw_fEta_fBrem, abs(Photon_SC_Eta), myphoton->isEEPho(), "START42_V11");
			Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11") * EtEtaCor(etraw_fEta_fBrem_AF, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur");
			Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11") * EtEtaCor(etraw_fEta_fBrem_L, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur");


			Photon_secondMomentMaj = myphoton->secondMomentMaj();
			Photon_secondMomentMin = myphoton->secondMomentMin();
			Photon_secondMomentAlpha = myphoton->secondMomentAlpha();



// Read NN output from weight file
			Photon_NNshapeOutput = reader->EvaluateMVA("MLP method");

      // Fill muons stuff
      TRootMuon *leadingMuon;
      TRootMuon *subleadingMuon;
      if( (mymuon1->Pt()) > (mymuon2->Pt()) )      {
        leadingMuon = mymuon1;
        subleadingMuon = mymuon2;
      } else {
        leadingMuon = mymuon2;
        subleadingMuon = mymuon1;
      }
      MuonL_Pt = leadingMuon->Pt();
      MuonL_Eta = leadingMuon->Eta();
      MuonL_Phi = leadingMuon->Phi();
      MuonL_Charge = leadingMuon->charge();
      MuonL_isoR03_emEt = leadingMuon->isoR03_emEt();
      MuonL_isoR03_hadEt = leadingMuon->isoR03_hadEt();
      MuonL_isoR03_hoEt = leadingMuon->isoR03_hoEt();
      MuonL_isoR03_nJets = leadingMuon->isoR03_nJets();
      MuonL_isoR03_nTracks = leadingMuon->isoR03_nTracks();
      MuonL_isoR03_sumPt = leadingMuon->isoR03_sumPt();
      MuonL_isoR05_emEt = leadingMuon->isoR05_emEt();
      MuonL_isoR05_hadEt = leadingMuon->isoR05_hadEt();
      MuonL_isoR05_hoEt = leadingMuon->isoR05_hoEt();
      MuonL_isoR05_nJets = leadingMuon->isoR05_nJets();
      MuonL_isoR05_nTracks = leadingMuon->isoR05_nTracks();
      MuonL_isoR05_sumPt = leadingMuon->isoR05_sumPt();
      MuonS_Pt = subleadingMuon->Pt();
      MuonS_Eta = subleadingMuon->Eta();
      MuonS_Phi = subleadingMuon->Phi();
      MuonS_Charge = subleadingMuon->charge();
      MuonS_isoR03_emEt = subleadingMuon->isoR03_emEt();
      MuonS_isoR03_hadEt = subleadingMuon->isoR03_hadEt();
      MuonS_isoR03_hoEt = subleadingMuon->isoR03_hoEt();
      MuonS_isoR03_nJets = subleadingMuon->isoR03_nJets();
      MuonS_isoR03_nTracks = subleadingMuon->isoR03_nTracks();
      MuonS_isoR03_sumPt = subleadingMuon->isoR03_sumPt();
      MuonS_isoR05_emEt = subleadingMuon->isoR05_emEt();
      MuonS_isoR05_hadEt = subleadingMuon->isoR05_hadEt();
      MuonS_isoR05_hoEt = subleadingMuon->isoR05_hoEt();
      MuonS_isoR05_nJets = subleadingMuon->isoR05_nJets();
      MuonS_isoR05_nTracks = subleadingMuon->isoR05_nTracks();
      MuonS_isoR05_sumPt = subleadingMuon->isoR05_sumPt();

      TLorentzVector mumu;
      mumu = (*leadingMuon) + (*subleadingMuon);
      Ptmumu = mumu.Pt();
      double mumuInvMass = mumu.M();
//      cerr << "\t\tINFO: Dimuon invariant mass : Mmumu = " << mumuInvMass << endl;
      mumu.Clear();
      Mmumu = mumuInvMass;

    // ********************************************************************
    // *** Compute mumugamma invariant mass ***
    // ********************************************************************
    // Re-compute modified photon momentum so as to keep m_photon = 0
    Double_t Px_SC, Px_5x5, Px_SCraw, Px_SCraw_fEta;
    Double_t Py_SC, Py_5x5, Py_SCraw, Py_SCraw_fEta;
    Double_t Pz_SC, Pz_5x5, Pz_SCraw, Pz_SCraw_fEta;
	
    Double_t Px_SCraw_fEta_fBrem, Px_SCraw_fEta_fBrem_AF, Px_SCraw_fEta_fBrem_L, Px_SCraw_fEta_fBrem_fEtEta, Px_SCraw_fEta_fBrem_AF_fEtEta, Px_SCraw_fEta_fBrem_L_fEtEta;
    Double_t Py_SCraw_fEta_fBrem, Py_SCraw_fEta_fBrem_AF, Py_SCraw_fEta_fBrem_L, Py_SCraw_fEta_fBrem_fEtEta, Py_SCraw_fEta_fBrem_AF_fEtEta, Py_SCraw_fEta_fBrem_L_fEtEta;
    Double_t Pz_SCraw_fEta_fBrem, Pz_SCraw_fEta_fBrem_AF, Pz_SCraw_fEta_fBrem_L, Pz_SCraw_fEta_fBrem_fEtEta, Pz_SCraw_fEta_fBrem_AF_fEtEta, Pz_SCraw_fEta_fBrem_L_fEtEta;



    Px_SC = Px_5x5 = Px_SCraw = Px_SCraw_fEta = 0.0;
    Py_SC = Py_5x5 = Py_SCraw = Py_SCraw_fEta = 0.0;
    Pz_SC = Pz_5x5 = Pz_SCraw = Pz_SCraw_fEta = 0.0;

    Px_SC = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->Mag());
    Py_SC = (myphoton->Py()) / (myphoton->Energy()) * (myphoton->superCluster()->Mag());
    Pz_SC = (myphoton->Pz()) / (myphoton->Energy()) * (myphoton->superCluster()->Mag());

    Px_5x5 = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->e5x5());
    Py_5x5 = (myphoton->Py()) / (myphoton->Energy()) * (myphoton->e5x5());
    Pz_5x5 = (myphoton->Pz()) / (myphoton->Energy()) * (myphoton->e5x5());

    Px_SCraw = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy());
    Py_SCraw = (myphoton->Py()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy());
    Pz_SCraw = (myphoton->Pz()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy());

    Px_SCraw_fEta = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta));
    Py_SCraw_fEta = (myphoton->Py()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta));
    Pz_SCraw_fEta = (myphoton->Pz()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta));


    Px_SCraw_fEta_fBrem = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11"));
    Px_SCraw_fEta_fBrem_AF = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "Anne-Fleur"));
    Px_SCraw_fEta_fBrem_L = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "Louis"));

    Py_SCraw_fEta_fBrem = (myphoton->Py()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11"));
    Py_SCraw_fEta_fBrem_AF = (myphoton->Py()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "Anne-Fleur"));
    Py_SCraw_fEta_fBrem_L = (myphoton->Py()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "Louis"));

    Pz_SCraw_fEta_fBrem = (myphoton->Pz()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11"));
    Pz_SCraw_fEta_fBrem_AF = (myphoton->Pz()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "Anne-Fleur"));
    Pz_SCraw_fEta_fBrem_L = (myphoton->Pz()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "Louis"));


    Px_SCraw_fEta_fBrem_fEtEta = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11")) * (EtEtaCor(etraw_fEta_fBrem, abs(Photon_SC_Eta), myphoton->isEEPho(), "START42_V11"));
    Px_SCraw_fEta_fBrem_AF_fEtEta  = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "Anne-Fleur")) * (EtEtaCor(etraw_fEta_fBrem_AF, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur"));
    Px_SCraw_fEta_fBrem_L_fEtEta  = (myphoton->Px()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "Louis")) * (EtEtaCor(etraw_fEta_fBrem_L, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur"));

    Py_SCraw_fEta_fBrem_fEtEta = (myphoton->Py()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11")) * (EtEtaCor(etraw_fEta_fBrem, abs(Photon_SC_Eta), myphoton->isEEPho(), "START42_V11"));
    Py_SCraw_fEta_fBrem_AF_fEtEta  = (myphoton->Py()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "Anne-Fleur")) * (EtEtaCor(etraw_fEta_fBrem_AF, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur"));
    Py_SCraw_fEta_fBrem_L_fEtEta  = (myphoton->Py()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "Louis")) * (EtEtaCor(etraw_fEta_fBrem_L, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur"));

    Pz_SCraw_fEta_fBrem_fEtEta = (myphoton->Pz()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11")) * (EtEtaCor(etraw_fEta_fBrem, abs(Photon_SC_Eta), myphoton->isEEPho(), "START42_V11"));
    Pz_SCraw_fEta_fBrem_AF_fEtEta  = (myphoton->Pz()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "Anne-Fleur")) * (EtEtaCor(etraw_fEta_fBrem_AF, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur"));
    Pz_SCraw_fEta_fBrem_L_fEtEta  = (myphoton->Pz()) / (myphoton->Energy()) * (myphoton->superCluster()->rawEnergy()) * (fEta(Photon_SC_Eta)) * (BremCor(Photon_SC_brem, myphoton->isEEPho(), "Louis")) * (EtEtaCor(etraw_fEta_fBrem_L, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur"));



    TLorentzVector mumugamma;
    TLorentzVector mumuSC;
    TLorentzVector mumu5x5;
    TLorentzVector mumuSC_raw;
    TLorentzVector mumuSC_raw_fEta;
	
    TLorentzVector mumuSC_raw_fEta_fBrem, mumuSC_raw_fEta_fBrem_AF, mumuSC_raw_fEta_fBrem_L, mumuSC_raw_fEta_fBrem_fEtEta, mumuSC_raw_fEta_fBrem_AF_fEtEta, mumuSC_raw_fEta_fBrem_L_fEtEta;


    TLorentzVector *PhotonEScale = new TLorentzVector( EScale*(myphoton->Px()), EScale*(myphoton->Py()), EScale*(myphoton->Pz()), EScale*(myphoton->Energy()));
    TLorentzVector *PhotonSC = new TLorentzVector( EScale*Px_SC, EScale*Py_SC, EScale*Pz_SC, EScale*(myphoton->superCluster()->Mag()) );
    TLorentzVector *Photon5x5 = new TLorentzVector(EScale*Px_5x5 , EScale*Py_5x5, EScale*Pz_5x5, EScale*(myphoton->e5x5()));
    TLorentzVector *PhotonSC_raw = new TLorentzVector(EScale*Px_SCraw , EScale*Py_SCraw, EScale*Pz_SCraw, EScale*(myphoton->superCluster()->rawEnergy()));
    TLorentzVector *PhotonSC_raw_fEta = new TLorentzVector(EScale*Px_SCraw_fEta , EScale*Py_SCraw_fEta, EScale*Pz_SCraw_fEta, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta)));

    TLorentzVector *PhotonSC_raw_fEta_fBrem = new TLorentzVector(EScale*Px_SCraw_fEta_fBrem, EScale*Py_SCraw_fEta_fBrem, EScale*Pz_SCraw_fEta_fBrem, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta))*(BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11")));

    TLorentzVector *PhotonSC_raw_fEta_fBrem_AF = new TLorentzVector(EScale*Px_SCraw_fEta_fBrem_AF, EScale*Py_SCraw_fEta_fBrem_AF, EScale*Pz_SCraw_fEta_fBrem_AF, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta))*(BremCor(Photon_SC_brem, myphoton->isEEPho(), "Anne-Fleur")));

    TLorentzVector *PhotonSC_raw_fEta_fBrem_L = new TLorentzVector(EScale*Px_SCraw_fEta_fBrem_L, EScale*Py_SCraw_fEta_fBrem_L, EScale*Pz_SCraw_fEta_fBrem_L, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta))*(BremCor(Photon_SC_brem, myphoton->isEEPho(), "Louis")));

    
    TLorentzVector *PhotonSC_raw_fEta_fBrem_fEtEta = new TLorentzVector(EScale*Px_SCraw_fEta_fBrem_fEtEta, EScale*Py_SCraw_fEta_fBrem_fEtEta, EScale*Pz_SCraw_fEta_fBrem_fEtEta, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta))*(BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11"))*(EtEtaCor(etraw_fEta_fBrem, abs(Photon_SC_Eta), myphoton->isEEPho(), "START42_V11")));

    TLorentzVector *PhotonSC_raw_fEta_fBrem_AF_fEtEta = new TLorentzVector(EScale*Px_SCraw_fEta_fBrem_AF_fEtEta, EScale*Py_SCraw_fEta_fBrem_AF_fEtEta, EScale*Pz_SCraw_fEta_fBrem_AF_fEtEta, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta))*(BremCor(Photon_SC_brem, myphoton->isEEPho(), "Anne-Fleur"))*(EtEtaCor(etraw_fEta_fBrem_AF, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur")));

    TLorentzVector *PhotonSC_raw_fEta_fBrem_L_fEtEta = new TLorentzVector(EScale*Px_SCraw_fEta_fBrem_L_fEtEta, EScale*Py_SCraw_fEta_fBrem_L_fEtEta, EScale*Pz_SCraw_fEta_fBrem_L_fEtEta, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta))*(BremCor(Photon_SC_brem, myphoton->isEEPho(), "Louis"))*(EtEtaCor(etraw_fEta_fBrem_L, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur")));




//    mumugamma = (*leadingMuon) + (*subleadingMuon) + (*myphoton);
    mumugamma = (*leadingMuon) + (*subleadingMuon) + (*PhotonEScale);
    mumuSC = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC);
    mumu5x5 = (*leadingMuon) + (*subleadingMuon) + (*Photon5x5);
    mumuSC_raw = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw);
    mumuSC_raw_fEta = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta);

    mumuSC_raw_fEta_fBrem = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta_fBrem);
    mumuSC_raw_fEta_fBrem_AF = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta_fBrem_AF);
    mumuSC_raw_fEta_fBrem_L = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta_fBrem_L);
    mumuSC_raw_fEta_fBrem_fEtEta = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta_fBrem_fEtEta);
    mumuSC_raw_fEta_fBrem_AF_fEtEta = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta_fBrem_AF_fEtEta);
    mumuSC_raw_fEta_fBrem_L_fEtEta = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta_fBrem_L_fEtEta);

    double mumugammaInvMass = mumugamma.M();
    double mumuSCInvMass = mumuSC.M();
    double mumu5x5InvMass = mumu5x5.M();
    double mumuSC_rawInvMass = mumuSC_raw.M();
    double mumuSC_rawInvMass_fEta = mumuSC_raw_fEta.M();
    
    double mumuSC_rawInvMass_fEta_fBrem = mumuSC_raw_fEta_fBrem.M();
    double mumuSC_rawInvMass_fEta_fBrem_AF = mumuSC_raw_fEta_fBrem_AF.M();
    double mumuSC_rawInvMass_fEta_fBrem_L = mumuSC_raw_fEta_fBrem_L.M();
    double mumuSC_rawInvMass_fEta_fBrem_fEtEta = mumuSC_raw_fEta_fBrem_fEtEta.M();
    double mumuSC_rawInvMass_fEta_fBrem_AF_fEtEta = mumuSC_raw_fEta_fBrem_AF_fEtEta.M();
    double mumuSC_rawInvMass_fEta_fBrem_L_fEtEta = mumuSC_raw_fEta_fBrem_L_fEtEta.M();

    Mmumugamma = mumugammaInvMass;
//		if( ((Mmumugamma>97.2) && (Mmumugamma<110.0)) || ((Mmumugamma>70.0) && (Mmumugamma<87.2)) ) cout << "isVeryLooseMMG:isLooseMMG:isTightMMG " << isVeryLooseMMG << isLooseMMG << isTightMMG << "\t\t\tMmumugamma= " << Mmumugamma << endl;
//		cout << "ievt= " << iEvent << "\t\tVL:L:T:M " << isVeryLooseMMG << isLooseMMG << isTightMMG << isMultipleCandidate << "\t\t\tMmumugamma= " << Mmumugamma << endl;
//		cout << "ievt= " << iEvent << "\t\t" << isMMGCandidate << isAfterFSRCut1 << isAfterFSRCut2 << isAfterFSRCut3 << isAfterFSRCut4 << isVeryLooseMMG << isLooseMMG << isTightMMG << isMultipleCandidate << "\t\t\tMmumugamma= " << Mmumugamma << endl;
    Mmumugamma_SC = mumuSCInvMass;
    Mmumugamma_5x5 = mumu5x5InvMass;
    Mmumugamma_SCraw = mumuSC_rawInvMass;
    Mmumugamma_SCraw_fEta = mumuSC_rawInvMass_fEta;
   
    Mmumugamma_SCraw_fEta_fBrem = mumuSC_rawInvMass_fEta_fBrem;
    Mmumugamma_SCraw_fEta_fBrem_AF = mumuSC_rawInvMass_fEta_fBrem_AF;
    Mmumugamma_SCraw_fEta_fBrem_L = mumuSC_rawInvMass_fEta_fBrem_L;
    Mmumugamma_SCraw_fEta_fBrem_fEtEta = mumuSC_rawInvMass_fEta_fBrem_fEtEta;
    Mmumugamma_SCraw_fEta_fBrem_AF_fEtEta = mumuSC_rawInvMass_fEta_fBrem_AF_fEtEta;
    Mmumugamma_SCraw_fEta_fBrem_L_fEtEta = mumuSC_rawInvMass_fEta_fBrem_L_fEtEta;

    mumugamma.Clear();
    mumuSC.Clear();
    mumu5x5.Clear();
    mumuSC_raw.Clear();
    PhotonEScale->Clear();
    PhotonSC->Clear();
    Photon5x5->Clear();
    PhotonSC_raw->Clear();
    PhotonSC_raw_fEta->Clear();

    mmg_k = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma,2) - pow(Mmumu,2));
    mmg_ik = (double)(pow(Mmumugamma,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s = mmg_ik - 1.0;
    mmg_logk = log(mmg_k);
    mmg_logik = log(mmg_ik);
    mmg_logs = log(mmg_s);

    mmg_k_5x5 = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma_5x5,2) - pow(Mmumu,2));
    mmg_ik_5x5 = (double)(pow(Mmumugamma_5x5,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s_5x5 = mmg_ik_5x5 - 1.0;
    mmg_logk_5x5 = log(mmg_k_5x5);
    mmg_logik_5x5 = log(mmg_ik_5x5);
    mmg_logs_5x5 = log(mmg_s_5x5);

    mmg_k_SC = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma_SC,2) - pow(Mmumu,2));
    mmg_ik_SC = (double)(pow(Mmumugamma_SC,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s_SC = mmg_ik_SC - 1.0;
    mmg_logk_SC = log(mmg_k_SC);
    mmg_logik_SC = log(mmg_ik_SC);
    mmg_logs_SC = log(mmg_s_SC);

    mmg_k_SCraw = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma_SCraw,2) - pow(Mmumu,2));
    mmg_ik_SCraw = (double)(pow(Mmumugamma_SCraw,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s_SCraw = mmg_ik_SCraw - 1.0;
    mmg_logk_SCraw = log(mmg_k_SCraw);
    mmg_logik_SCraw = log(mmg_ik_SCraw);
    mmg_logs_SCraw = log(mmg_s_SCraw);

    mmg_k_SCraw_fEta = (double)(pow(91.1876,2) - pow(Mmumu,2) ) / (double)(pow(Mmumugamma_SCraw_fEta,2) - pow(Mmumu,2));
    mmg_ik_SCraw_fEta = (double)(pow(Mmumugamma_SCraw_fEta,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_s_SCraw_fEta = mmg_ik_SCraw_fEta - 1.0;
    mmg_logk_SCraw_fEta = log(mmg_k_SCraw_fEta);
    mmg_logik_SCraw_fEta = log(mmg_ik_SCraw_fEta);
    mmg_logs_SCraw_fEta = log(mmg_s_SCraw_fEta);


    mmg_ik_SCraw_fEta_fBrem = (double)(pow(Mmumugamma_SCraw_fEta_fBrem,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_ik_SCraw_fEta_fBrem_AF = (double)(pow(Mmumugamma_SCraw_fEta_fBrem_AF,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_ik_SCraw_fEta_fBrem_L = (double)(pow(Mmumugamma_SCraw_fEta_fBrem_L,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_ik_SCraw_fEta_fBrem_fEtEta = (double)(pow(Mmumugamma_SCraw_fEta_fBrem_fEtEta,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_ik_SCraw_fEta_fBrem_AF_fEtEta = (double)(pow(Mmumugamma_SCraw_fEta_fBrem_AF_fEtEta,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );
    mmg_ik_SCraw_fEta_fBrem_L_fEtEta = (double)(pow(Mmumugamma_SCraw_fEta_fBrem_L_fEtEta,2) - pow(Mmumu,2)) / (double)(pow(91.1876,2) - pow(Mmumu,2) );


//    cerr << "\t\tINFO: mumugamma invariant mass : Mmumugamma = " << mumugammaInvMass << endl;

    double phiPhoton = myphoton->Phi();
    double etaPhoton = myphoton->Eta();
    double phiMuon = mymuon1->Phi();
    double etaMuon = mymuon1->Eta();
    double phiMuon_oppositeCharge = mymuon2->Phi();
    double etaMuon_oppositeCharge = mymuon2->Eta();
    double deltaRPM = DeltaR(etaPhoton, phiPhoton, etaMuon, phiMuon);
    double deltaRPAM = DeltaR(etaPhoton, phiPhoton, etaMuon_oppositeCharge, phiMuon_oppositeCharge);

    double deltaRmin;
    TRootMuon *farMuon;
    TRootMuon *nearMuon;
    TRootMuon *minusMuon;
    TRootMuon *plusMuon;

    if(deltaRPM < deltaRPAM){
      deltaRmin = deltaRPM;
      farMuon = (TRootMuon*) mymuon2;
      nearMuon = (TRootMuon*) mymuon1;
    } else {
      deltaRmin = deltaRPAM;
      farMuon = (TRootMuon*) mymuon1;
      nearMuon = (TRootMuon*) mymuon2;
    }
    if( mymuon1->charge()>0 ){
      plusMuon  = (TRootMuon*) mymuon1;
      minusMuon = (TRootMuon*) mymuon2;
    } else {
      minusMuon = (TRootMuon*) mymuon1;
      plusMuon  = (TRootMuon*) mymuon2;
    }

    // FILLING MINITREE INFORMATION
    MuonM_Pt = minusMuon->Pt();
    MuonM_Eta = minusMuon->Eta();
    MuonM_Phi = minusMuon->Phi();
    MuonM_isoR03_emEt = minusMuon->isoR03_emEt();
    MuonM_isoR03_hadEt = minusMuon->isoR03_hadEt();
    MuonM_isoR03_hoEt = minusMuon->isoR03_hoEt();
    MuonM_isoR03_nJets = minusMuon->isoR03_nJets();
    MuonM_isoR03_nTracks = minusMuon->isoR03_nTracks();
    MuonM_isoR03_sumPt = minusMuon->isoR03_sumPt();
    MuonM_isoR05_emEt = minusMuon->isoR05_emEt();
    MuonM_isoR05_hadEt = minusMuon->isoR05_hadEt();
    MuonM_isoR05_hoEt = minusMuon->isoR05_hoEt();
    MuonM_isoR05_nJets = minusMuon->isoR05_nJets();
    MuonM_isoR05_nTracks = minusMuon->isoR05_nTracks();
    MuonM_isoR05_sumPt = minusMuon->isoR05_sumPt();
    MuonP_Pt = plusMuon->Pt();
    MuonP_Eta = plusMuon->Eta();
    MuonP_Phi = plusMuon->Phi();
    MuonP_isoR03_emEt = plusMuon->isoR03_emEt();
    MuonP_isoR03_hadEt = plusMuon->isoR03_hadEt();
    MuonP_isoR03_hoEt = plusMuon->isoR03_hoEt();
    MuonP_isoR03_nJets = plusMuon->isoR03_nJets();
    MuonP_isoR03_nTracks = plusMuon->isoR03_nTracks();
    MuonP_isoR03_sumPt = plusMuon->isoR03_sumPt();
    MuonP_isoR05_emEt = plusMuon->isoR05_emEt();
    MuonP_isoR05_hadEt = plusMuon->isoR05_hadEt();
    MuonP_isoR05_hoEt = plusMuon->isoR05_hoEt();
    MuonP_isoR05_nJets = plusMuon->isoR05_nJets();
    MuonP_isoR05_nTracks = plusMuon->isoR05_nTracks();
    MuonP_isoR05_sumPt = plusMuon->isoR05_sumPt();
    MuonF_Pt = farMuon->Pt();
    MuonF_Eta = farMuon->Eta();
    MuonF_Phi = farMuon->Phi();
    MuonF_Charge = farMuon->charge();
    MuonF_isoR03_emEt = farMuon->isoR03_emEt();
    MuonF_isoR03_hadEt = farMuon->isoR03_hadEt();
    MuonF_isoR03_hoEt = farMuon->isoR03_hoEt();
    MuonF_isoR03_nJets = farMuon->isoR03_nJets();
    MuonF_isoR03_nTracks = farMuon->isoR03_nTracks();
    MuonF_isoR03_sumPt = farMuon->isoR03_sumPt();
    MuonF_isoR05_emEt = farMuon->isoR05_emEt();
    MuonF_isoR05_hadEt = farMuon->isoR05_hadEt();
    MuonF_isoR05_hoEt = farMuon->isoR05_hoEt();
    MuonF_isoR05_nJets = farMuon->isoR05_nJets();
    MuonF_isoR05_nTracks = farMuon->isoR05_nTracks();
    MuonF_isoR05_sumPt = farMuon->isoR05_sumPt();
    MuonN_Pt = nearMuon->Pt();
    MuonN_Eta = nearMuon->Eta();
    MuonN_Phi = nearMuon->Phi();
    MuonN_Charge = nearMuon->charge();
    MuonN_isoR03_emEt = nearMuon->isoR03_emEt();
    MuonN_isoR03_hadEt = nearMuon->isoR03_hadEt();
    MuonN_isoR03_hoEt = nearMuon->isoR03_hoEt();
    MuonN_isoR03_nJets = nearMuon->isoR03_nJets();
    MuonN_isoR03_nTracks = nearMuon->isoR03_nTracks();
    MuonN_isoR03_sumPt = nearMuon->isoR03_sumPt();
    MuonN_isoR05_emEt = nearMuon->isoR05_emEt();
    MuonN_isoR05_hadEt = nearMuon->isoR05_hadEt();
    MuonN_isoR05_hoEt = nearMuon->isoR05_hoEt();
    MuonN_isoR05_nJets = nearMuon->isoR05_nJets();
    MuonN_isoR05_nTracks = nearMuon->isoR05_nTracks();
    MuonN_isoR05_sumPt = nearMuon->isoR05_sumPt();

    deltaRNear = DeltaR(etaPhoton, phiPhoton, nearMuon->Eta(), nearMuon->Phi());
    deltaRFar = DeltaR(etaPhoton, phiPhoton, farMuon->Eta(), farMuon->Phi());
    deltaRMinus = DeltaR(etaPhoton, phiPhoton, minusMuon->Eta(), minusMuon->Phi());
    deltaRPlus = DeltaR(etaPhoton, phiPhoton, plusMuon->Eta(), plusMuon->Phi());
    deltaRLeading = DeltaR(etaPhoton, phiPhoton, leadingMuon->Eta(), leadingMuon->Phi());
    deltaRSubleading = DeltaR(etaPhoton, phiPhoton, subleadingMuon->Eta(), subleadingMuon->Phi());

    if( doMC )
    { 
	//cout<<endl<<"doMC dans le if = "<<doMC<<endl; 
	// Compute Stuff, with MC truth information
      doGenInfo( (TRootParticle*) myphoton, mcParticles, &Photon_MC_E, &Photon_MC_Px, &Photon_MC_Py, &Photon_MC_Pz, &Photon_MC_Phi, &Photon_MC_Eta, 22 );
      doGenInfo( (TRootParticle*) minusMuon, mcParticles, &MuonM_MC_E, &MuonM_MC_Px, &MuonM_MC_Py, &MuonM_MC_Pz, &MuonM_MC_Phi, &MuonM_MC_Eta, 13 );
      doGenInfo( (TRootParticle*) plusMuon, mcParticles, &MuonP_MC_E, &MuonP_MC_Px, &MuonP_MC_Py, &MuonP_MC_Pz, &MuonP_MC_Phi, &MuonP_MC_Eta, -13 );
      doGenInfo( (TRootParticle*) nearMuon, mcParticles, &MuonN_MC_E, &MuonN_MC_Px, &MuonN_MC_Py, &MuonN_MC_Pz, &MuonN_MC_Phi, &MuonN_MC_Eta, (-1)*(nearMuon->charge())*13 );
      doGenInfo( (TRootParticle*) farMuon, mcParticles, &MuonF_MC_E, &MuonF_MC_Px, &MuonF_MC_Py, &MuonF_MC_Pz, &MuonF_MC_Phi, &MuonF_MC_Eta, (-1)*(farMuon->charge())*13 );
      doGenInfo( (TRootParticle*) leadingMuon, mcParticles, &MuonL_MC_E, &MuonL_MC_Px, &MuonL_MC_Py, &MuonL_MC_Pz, &MuonL_MC_Phi, &MuonL_MC_Eta, (-1)*(leadingMuon->charge())*13 );
      doGenInfo( (TRootParticle*) subleadingMuon, mcParticles, &MuonS_MC_E, &MuonS_MC_Px, &MuonS_MC_Py, &MuonS_MC_Pz, &MuonS_MC_Phi, &MuonS_MC_Eta, (-1)*(subleadingMuon->charge())*13 );

			if(Photon_MC_E != 0.0) Photon_SC_rawE_x_fEta_o_MC_E = (double)(Photon_SC_rawE_x_fEta) / (double)(Photon_MC_E);
			if(Photon_MC_E != 0.0) Photon_E_o_MC_E = (double)(Photon_E) / (double)(Photon_MC_E);
			
			if(Photon_MC_E != 0.0) Photon_SC_rawE_x_fEta_x_fBrem_o_MC_E  = (double)(Photon_SC_rawE_x_fEta_x_fBrem) / (double)(Photon_MC_E);
			if(Photon_MC_E != 0.0) Photon_SC_rawE_x_fEta_x_fBrem_AF_o_MC_E  = (double)(Photon_SC_rawE_x_fEta_x_fBrem_AF) / (double)(Photon_MC_E);
			if(Photon_MC_E != 0.0) Photon_SC_rawE_x_fEta_x_fBrem_L_o_MC_E  = (double)(Photon_SC_rawE_x_fEta_x_fBrem_L) / (double)(Photon_MC_E);

			if(Photon_MC_E != 0.0) Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta_o_MC_E  = (double)(Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta) / (double)(Photon_MC_E);
			if(Photon_MC_E != 0.0) Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta_o_MC_E  = (double)(Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta) / (double)(Photon_MC_E);
			if(Photon_MC_E != 0.0) Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta_o_MC_E  = (double)(Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta) / (double)(Photon_MC_E);

	//cout<<endl<<"Photon_E_o_MC_E = "<<Photon_E_o_MC_E<<endl;

      TLorentzVector mumu_Photon_MC;
      TLorentzVector mumugamma_Photon_MC;
      TLorentzVector mumu_Muons_MC;
      TLorentzVector mumugamma_Muons_MC;
      TLorentzVector mumu_MMG_MC;
      TLorentzVector mumugamma_MMG_MC;

      TLorentzVector *PhotonMC = new TLorentzVector( Photon_MC_Px, Photon_MC_Py, Photon_MC_Pz, Photon_MC_E);
      TLorentzVector *MuonLMC = new TLorentzVector( MuonL_MC_Px, MuonL_MC_Py, MuonL_MC_Pz, MuonL_MC_E);
      TLorentzVector *MuonSMC = new TLorentzVector( MuonS_MC_Px, MuonS_MC_Py, MuonS_MC_Pz, MuonS_MC_E);

      TLorentzVector *PhotonEScale = new TLorentzVector( EScale*(myphoton->Px()), EScale*(myphoton->Py()), EScale*(myphoton->Pz()), EScale*(myphoton->Energy()));
      TLorentzVector *PhotonSC = new TLorentzVector( myphoton->Px(), myphoton->Py(), myphoton->Pz(), EScale*(myphoton->superCluster()->Mag()));
      TLorentzVector *Photon5x5 = new TLorentzVector( myphoton->Px(), myphoton->Py(), myphoton->Pz(), EScale*(myphoton->e5x5()));
      TLorentzVector *PhotonSC_raw = new TLorentzVector( myphoton->Px(), myphoton->Py(), myphoton->Pz(), EScale*(myphoton->superCluster()->rawEnergy()));

      mumu_Photon_MC = (*leadingMuon) + (*subleadingMuon);
      mumugamma_Photon_MC = (*leadingMuon) + (*subleadingMuon) + (*PhotonMC);
      mumu_Muons_MC = (*MuonLMC) + (*MuonSMC);
      mumugamma_Muons_MC = (*MuonLMC) + (*MuonSMC) + (*PhotonEScale);
      mumu_MMG_MC = (*MuonLMC) + (*MuonSMC);
      mumugamma_MMG_MC = (*MuonLMC) + (*MuonSMC) + (*PhotonMC);
      Mmumu_Photon_MC = mumu_Photon_MC.M();
      Mmumugamma_Photon_MC = mumugamma_Photon_MC.M();
      Mmumu_Muons_MC = mumu_Muons_MC.M();
      Mmumugamma_Muons_MC = mumugamma_Muons_MC.M();
      Mmumu_MMG_MC = mumu_MMG_MC.M();
      Mmumugamma_MMG_MC = mumugamma_MMG_MC.M();

      mmg_k_Photon_MC = (double)(pow(91.1876,2) - pow(Mmumu_Photon_MC,2) ) / (double)(pow(Mmumugamma_Photon_MC,2) - pow(Mmumu_Photon_MC,2));
      mmg_ik_Photon_MC = (double)(pow(Mmumugamma_Photon_MC,2) - pow(Mmumu_Photon_MC,2)) / (double)(pow(91.1876,2) - pow(Mmumu_Photon_MC,2) );
      mmg_s_Photon_MC = mmg_ik_Photon_MC -1.0;
      mmg_logk_Photon_MC = log(mmg_k_Photon_MC);
      mmg_logik_Photon_MC = log(mmg_ik_Photon_MC);
      mmg_logs_Photon_MC = log(mmg_s_Photon_MC);

      mmg_k_Muons_MC = (double)(pow(91.1876,2) - pow(Mmumu_Muons_MC,2) ) / (double)(pow(Mmumugamma_Muons_MC,2) - pow(Mmumu_Muons_MC,2));
      mmg_ik_Muons_MC = (double)(pow(Mmumugamma_Muons_MC,2) - pow(Mmumu_Muons_MC,2)) / (double)(pow(91.1876,2) - pow(Mmumu_Muons_MC,2) );
      mmg_s_Muons_MC = mmg_ik_Muons_MC -1.0;
      mmg_logk_Muons_MC = log(mmg_k_Muons_MC);
      mmg_logik_Muons_MC = log(mmg_ik_Muons_MC);
      mmg_logs_Muons_MC = log(mmg_s_Muons_MC);

      mmg_k_MMG_MC = (double)(pow(91.1876,2) - pow(Mmumu_MMG_MC,2) ) / (double)(pow(Mmumugamma_MMG_MC,2) - pow(Mmumu_MMG_MC,2));
      mmg_ik_MMG_MC = (double)(pow(Mmumugamma_MMG_MC,2) - pow(Mmumu_MMG_MC,2)) / (double)(pow(91.1876,2) - pow(Mmumu_MMG_MC,2) );
      mmg_s_MMG_MC = mmg_ik_MMG_MC -1.0;
      mmg_logk_MMG_MC = log(mmg_k_MMG_MC);
      mmg_logik_MMG_MC = log(mmg_ik_MMG_MC);
      mmg_logs_MMG_MC = log(mmg_s_MMG_MC);

//      Mmumu_Photon_MC = Mmumugamma_Photon_MC = mmg_k_Photon_MC = mmg_ik_Photon_MC = mmg_s_Photon_MC = mmg_logk_Photon_MC = mmg_logik_Photon_MC = mmg_logs_Photon_MC = -99.0;
//      Mmumu_Muons_MC = Mmumugamma_Muons_MC = mmg_k_Muons_MC = mmg_ik_Muons_MC = mmg_s_Muons_MC = mmg_logk_Muons_MC = mmg_logik_Muons_MC = mmg_logs_Muons_MC = -99.0;
//      Mmumu_MMG_MC = Mmumugamma_MMG_MC = mmg_k_MMG_MC = mmg_ik_MMG_MC = mmg_s_MMG_MC = mmg_logk_MMG_MC = mmg_logik_MMG_MC = mmg_logs_MMG_MC = -99.0;
    PhotonMC->Clear();
    MuonLMC->Clear();
    MuonSMC->Clear();
    PhotonEScale->Clear();
    PhotonSC->Clear();
    Photon5x5->Clear();
    PhotonSC_raw->Clear();
    }// end doMC


//    myphoton->Clear();
////    mymuon1->Clear();
////    mymuon2->Clear();
////    farMuon->Clear();
////    nearMuon->Clear();
////    minusMuon->Clear();
////    plusMuon->Clear();
////    PhotonSC->Clear();
////    Photon5x5->Clear();
////    PhotonSC_raw->Clear();
////    leadingMuon->Clear();
////    subleadingMuon->Clear();


return 0;
}

