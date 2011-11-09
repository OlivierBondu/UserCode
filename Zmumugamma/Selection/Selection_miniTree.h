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

#include "corrections.h"


using namespace std;


double weight_DYToMuMu(int nGenVertices, string lumi_set, string pu_set)
{
	if( lumi_set == "Nov03" )
	{
		if( pu_set == "PU_S6" )
		{
			double weight[36] = {0, 0, 0.00419895, 0.0501903, 0.324344, 1.41023, 2.43948, 2.504, 2.10814, 1.75313, 1.61091, 1.40119, 1.25931, 1.14953, 0.970073, 0.672993, 0.356685, 0.14207, 0.0472661, 0.014344, 0.00481347, 0.001252, 8.89355e-05, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Nov03 2011 ; PU_S6
			return weight[nGenVertices];
		}

		if( pu_set == "PU_S4" )
		{
	    double weight[36] = {0, 0, 0.00126977, 0.0230463, 0.203327, 1.07616, 2.08245, 2.28388, 1.99976, 1.68898, 1.58258, 1.41129, 1.32724, 1.30215, 1.19746, 0.942886, 0.575914, 0.271399, 0.107312, 0.0405825, 0.0169426, 0.00561874, 0.000500778, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Nov03 2011 ; PU_S4
			return weight[nGenVertices];
		}
	}
	double weight[36] = {0.0};
	return weight[nGenVertices];
}

double weight_TTJets(int nGenVertices)
{
	double weight[51] = {
0, 0, 0.130953, 0.478315, 0.814199, 1.11549, 1.36463, 1.4534, 1.47222, 1.38149, 1.30462, 1.19369, 1.08147, 1.00757, 0.93383, 0.83356, 0.748923, 0.691019, 0.699203, 0.586132, 0.499935, 0.442856, 0.377828, 0.310338, 0.176515, 0.201486, 0.292975, 0.0715264, 0.0572582, 0.0292919, 0.061007, 0.0248481, 0, 0, 0.00147735, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0// May10_Promptv4_Aug05_Promptv6 2.15 fb-1
};
	return weight[nGenVertices];
}
double weight_WJetsToLNu(int nGenVertices)
{
	double weight[51] = {
0, 0, 0.207242, 0.445507, 0.859512, 1.07573, 1.26513, 1.46919, 1.21893, 1.2368, 0.996704, 0.898286, 1.02384, 1.10968, 1.15656, 1.41378, 1.19411, 1.00502, 0.973797, 1.64394, 0, 0.947574, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0// May10_Promptv4_Aug05_Promptv6 2.15 fb-1
};
  return weight[nGenVertices];
}
double  weight_QCDMu(int nGenVertices)
{
  double weight[51] = {
0, 0, 0.216306, 0.484129, 0.782602, 1.0295, 1.30368, 1.31239, 1.26043, 1.10026, 1.07655, 1.03941, 1.0667, 1.00138, 1.15552, 0.968367, 1.46147, 1.95245, 3.40521, 1.9162, 2.08934, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 // May10_Promptv4_Aug05_Promptv6 2.15 fb-1
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

int photonIsInCrack(double sc_abs_eta, double sc_abs_phi)
{
	double phiCrackSize = (double)(21.5) / (double) (1290.0);
	double phiCrackPosition = (double)(TMath::Pi()) / (double)(9.0);
	double phiOffset = -(double)(10.0 * TMath::Pi()) / (double)(180.0);
	bool isInEtaCrack = (sc_abs_eta < 0.018 ||
		(sc_abs_eta >0.423 && sc_abs_eta <0.461) ||
		(sc_abs_eta >0.770 && sc_abs_eta <0.806) ||
		(sc_abs_eta >1.127 && sc_abs_eta <1.163) ||
		(sc_abs_eta >1.460 && sc_abs_eta <1.558));
	bool isInPhiCrack = (	(sc_abs_phi + phiOffset) < phiCrackSize ||
		( (1.0*phiCrackPosition - phiCrackSize) < (sc_abs_phi + phiOffset) && (sc_abs_phi + phiOffset) < (1.0*phiCrackPosition + phiCrackSize) ) ||
		( (2.0*phiCrackPosition - phiCrackSize) < (sc_abs_phi + phiOffset) && (sc_abs_phi + phiOffset) < (2.0*phiCrackPosition + phiCrackSize) ) ||
		( (3.0*phiCrackPosition - phiCrackSize) < (sc_abs_phi + phiOffset) && (sc_abs_phi + phiOffset) < (3.0*phiCrackPosition + phiCrackSize) ) ||
		( (4.0*phiCrackPosition - phiCrackSize) < (sc_abs_phi + phiOffset) && (sc_abs_phi + phiOffset) < (4.0*phiCrackPosition + phiCrackSize) ) ||
		( (5.0*phiCrackPosition - phiCrackSize) < (sc_abs_phi + phiOffset) && (sc_abs_phi + phiOffset) < (5.0*phiCrackPosition + phiCrackSize) ) ||
		( (6.0*phiCrackPosition - phiCrackSize) < (sc_abs_phi + phiOffset) && (sc_abs_phi + phiOffset) < (6.0*phiCrackPosition + phiCrackSize) ) ||
		( (7.0*phiCrackPosition - phiCrackSize) < (sc_abs_phi + phiOffset) && (sc_abs_phi + phiOffset) < (7.0*phiCrackPosition + phiCrackSize) ) ||
		( (8.0*phiCrackPosition - phiCrackSize) < (sc_abs_phi + phiOffset) && (sc_abs_phi + phiOffset) < (8.0*phiCrackPosition + phiCrackSize) ) ||
		( (9.0*phiCrackPosition - phiCrackSize) < (sc_abs_phi + phiOffset) ) );
//	isInPhiCrack = false;
	if (isInEtaCrack) return 1;
	if (isInPhiCrack) return 2;
	return 0;
}

double fEta(vector<double> param, double eta) 
{
  double ieta = fabs(eta)*(5/0.087);
  double p0 = param[0];  // should be 40.2198
  double p1 = param[1];  // should be -3.03103e-6
  double feta = 1; 

  if ( ieta < p0 || fabs(eta) > 1.4442) feta = 1.0; 
  else feta = (double)1.0/(double)(1.0 + p1*(ieta-p0)*(ieta-p0));

  return feta;
}

double BremCor(vector<double> param, double brem)
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

  //Make No Corrections if brem is invalid! 
	//cout<<endl<<setprecision( 10 )<<"brem in function= "<<brem<<endl;
  if ( brem == 0 ) return 1.0;

		//double bremLowThr  = 0.9;
		double bremLowThr  = param[0];
		//double bremHighThr = 6.5;
		double bremHighThr = param[1];

		if ( brem < bremLowThr  ) brem = bremLowThr;
		if ( brem > bremHighThr ) brem = bremHighThr;
   		p0 = param[2];
   		p1 = param[3];
   		p2 = param[4];
   		p3 = param[5];
   		p4 = param[6];

  double threshold = p4;

  double y = p0*threshold*threshold + p1*threshold + p2;
  double yprime = 2*p0*threshold + p1;
  double a = p3;
  double b = yprime - 2*a*threshold;
  double c = y - a*threshold*threshold - b*threshold;

  double bremCorrection = 1.0;
  if ( brem < threshold ) bremCorrection = p0*brem*brem + p1*brem + p2;
  else bremCorrection = a*brem*brem + b*brem + c;

  return (double)(1.0) / (double)(bremCorrection);
}

double EtEtaCor(vector<double> param, double et, double eta, bool isEB) 
{ 
  
  double etEtaCorrection = 0.0; 

	if( isEB )
	{
		double p0 = param[0] + (double)(param[1]) / (double)(et + param[2]) + (double)(param[3])/(double)(et*et);
		double p1 = param[4] + (double)(param[5])/(double)(et + param[6]) + (double)(param[7])/(double)(et*et);
		etEtaCorrection = p0 +  p1 * atan(param[8]*(param[9]-fabs(eta))) + param[10] * fabs(eta);
	} else {
		double p0 = param[0] + (double)(param[1])/(double)(sqrt(et));
		double p1 = param[2] + (double)(param[3])/(double)(sqrt(et));
		double p2 = param[4] + (double)(param[5])/(double)(sqrt(et));
		double p3 = param[6] + (double)(param[7])/(double)(sqrt(et));
		etEtaCorrection = p0 + p1*fabs(eta) + p2*eta*eta + p3/fabs(eta);
  }
		if ( etEtaCorrection < 0.5 ) etEtaCorrection = 0.5;
  		if ( etEtaCorrection > 1.5 ) etEtaCorrection = 1.5;
  //End Caps
   
  return (double)(1.0)/(double)(etEtaCorrection);
}

double photonManualCorrectionFactor(TRootPhoton *myphoton, string correctionSet)
{
	int verbositybis = 0;
	int photonIsInCrack_ = photonIsInCrack(    fabs(myphoton->superCluster()->Eta()), fabs(myphoton->superCluster()->Phi())   );
	if( photonIsInCrack_ > 0 )
	{
		if( verbositybis > 0) cout << "Photon is in crack : " << ((photonIsInCrack_ == 1) ? "Eta" : "Phi") << endl;
//		return 1.0; // IF COMMENTED, BE SURE CRACK CORRECTIONS ARE TURNED ON BELOW
	}
	vector<double> param_Ceta;
	vector<double> param_fbrem;
	vector<double> param_feteta;
	parameters_Ceta(param_Ceta, correctionSet);
	parameters_fbrem(param_fbrem, correctionSet, myphoton->isEBPho());
	parameters_feteta(param_feteta, correctionSet, myphoton->isEBPho());
	double f_eta = fEta(param_Ceta, myphoton->superCluster()->Eta());
	double brem = (double)(myphoton->superCluster()->phiWidth()) / (double)(myphoton->superCluster()->etaWidth());
	double f_brem = BremCor(param_fbrem, brem);
	double sc_e = (myphoton->isEBPho()==1) ? (f_eta * myphoton->superCluster()->rawEnergy()) : (myphoton->superCluster()->rawEnergy() + myphoton->preshowerEnergy());
	double sc_e_noCrack = (myphoton->isEBPho()==1) ? (f_eta * myphoton->superCluster()->rawEnergy()) : (myphoton->superCluster()->rawEnergy() + myphoton->preshowerEnergy());
	double f_crack = myphoton->superCluster()->crackCorrectionEtaPhi();
	double sc_et = sc_e * (sin(myphoton->superCluster()->Theta()));
  double sc_et_noCrack = sc_e_noCrack * (sin(myphoton->superCluster()->Theta()));
	double f_et_eta = EtEtaCor(param_feteta, f_brem * sc_et, myphoton->superCluster()->Eta(), myphoton->isEBPho());
  double f_et_eta_noCrack = EtEtaCor(param_feteta, f_brem * sc_et_noCrack, myphoton->superCluster()->Eta(), myphoton->isEBPho());

	if( (myphoton->isEBPho()) && (myphoton->r9()<0.94) )
	{
    if( verbositybis > 1) cout << "###\tmyphoton->superCluster()->crackCorrectionEta()= " << myphoton->superCluster()->crackCorrectionEta() << endl;
    if( verbositybis > 1) cout << "###\tmyphoton->superCluster()->crackCorrectionPhi()= " << myphoton->superCluster()->crackCorrectionPhi() << endl;
    if( verbositybis > 1) cout << "###\tmyphoton->superCluster()->crackCorrectionEtaPhi()= " << myphoton->superCluster()->crackCorrectionEtaPhi() << endl;
		if( verbositybis > 1) cout << "f_et_eta * f_brem * f_eta * myphoton->superCluster()->rawEnergy()= " << f_et_eta * f_brem * f_eta * myphoton->superCluster()->rawEnergy() << endl;
    if( verbositybis > 1) cout << "###\tf_et_eta_noCrack * f_brem * f_eta * sc_e_noCrack * f_crack= " << f_et_eta_noCrack * f_brem * f_eta * sc_e_noCrack * f_crack << endl;
// WITH CRACK CORRECTIONS
    return (double)(f_et_eta_noCrack * f_brem * sc_e_noCrack * f_crack) / (double)(myphoton->Energy());
// WITHOUT CRACK CORRECTIONS
//		return (double)(f_et_eta * f_brem * f_eta * myphoton->superCluster()->rawEnergy()) / (double)(myphoton->Energy());
	}
	if( (myphoton->isEBPho()) && (myphoton->r9()>0.94) )
	{
		if( verbositybis > 1) cout << "f_eta * myphoton->e5x5()= " << f_eta * myphoton->e5x5() << endl;
		return (double)(f_eta * myphoton->e5x5()) / (double)(myphoton->Energy());
	}
	if( (myphoton->isEEPho()) && (myphoton->r9()<0.95) )
	{
		if( verbositybis > 1) cout << "f_et_eta * f_brem * (myphoton->superCluster()->rawEnergy() + myphoton->preshowerEnergy())= " << f_et_eta * f_brem * (myphoton->superCluster()->rawEnergy() + myphoton->preshowerEnergy()) << endl;
		return (double)(f_et_eta * f_brem * (myphoton->superCluster()->rawEnergy() + myphoton->preshowerEnergy())) / (double)(myphoton->Energy());
	}
	if( (myphoton->isEEPho()) && (myphoton->r9()>0.95) )
	{
		if( verbositybis > 1) cout << "(myphoton->e5x5() + myphoton->preshowerEnergy())= " << (myphoton->e5x5() + myphoton->preshowerEnergy()) <<  endl;
		return (double)(myphoton->e5x5() + myphoton->preshowerEnergy()) / (double)(myphoton->Energy());
	}

}



void findConversionMCtruth(TRootPhoton *myPhoton, TClonesArray *theMCphotons, int &Photon_MCisConverted, float &Photon_MCconvEoverP, float &Photon_MCconvMass, float &Photon_MCconvCotanTheta, float &Photon_MCconvVertexX, float &Photon_MCconvVertexY, float &Photon_MCconvVertexZ)
{
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



double PtMuonsConefunction(TRootMuon *mymuon, TRootPhoton *myphoton, double deltaR)
{
        double PtMuonsCone = 0;
    
        double dzCut = 0.0;
        TRootTrack trackbis = (TRootTrack)mymuon->innerTrack();
        dzCut = trackbis.vz() - myphoton->vz();
        double etLow_ = 0.0;
        double lip_ = 0.2;
        double drb_ = 0.1;
        if(dzCut < lip_ && mymuon->innerTrack().Et() > 0 && fabs(mymuon->dB()) < drb_)
        {
                double dr = DeltaR(mymuon->innerTrack().Eta(), mymuon->innerTrack().Phi(), myphoton->Eta(), myphoton->Phi());
                double deta = mymuon->innerTrack().Eta() - myphoton->Eta();
                if(fabs(myphoton->Eta()) < 1.479)
                {
                        double extRadius_ = deltaR;
                        double intRadiusBarrel_ = 0.04;
                        double stripBarrel_ = 0.015;
                        if(fabs(dr) < extRadius_ && fabs(dr) >= intRadiusBarrel_ && fabs(deta) >= stripBarrel_)    
                        {
                            PtMuonsCone = mymuon->innerTrack().Pt();
                            //cout<<"mymuon->innerTrack().Pt() = "<<mymuon->innerTrack().Pt()<<endl;
                        }
                }
                else
                {
                        double extRadius_ = deltaR;
                        double intRadiusBarrel_ = 0.04;
                        double stripBarrel_ = 0.015;
                        if(fabs(dr) < extRadius_ && fabs(dr) >= intRadiusBarrel_ && fabs(deta) >= stripBarrel_)
                        {
                            PtMuonsCone = mymuon->innerTrack().Pt();
                            //cout<<"mymuon->innerTrack().Pt() = "<<mymuon->innerTrack().Pt()<<endl;
                        }
                }

        }

        return PtMuonsCone;
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
	extern Float_t Photon_Ecorr_o_Ereco;
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
	extern Float_t Photon_ratioS4_corrected;
	extern Float_t Photon_SC_rawE_x_fEta, Photon_SC_rawE_x_fEta_x_fBrem, Photon_SC_rawE_x_fEta_x_fBrem_AF, Photon_SC_rawE_x_fEta_x_fBrem_L, Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta, Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta, Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta;
	extern Float_t Photon_secondMomentMaj, Photon_secondMomentMin, Photon_secondMomentAlpha;
	extern Float_t Photon_etaLAT, Photon_phiLAT, Photon_LAT, Photon_Zernike20, Photon_Zernike42, Photon_ESratio;


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



//int FillMMG(TRootPhoton* myphoton, TRootMuon* mymuon1, TRootMuon* mymuon2, double EScale, bool doMC, bool doPhotonConversionMC, TClonesArray* mcParticles, TClonesArray* mcPhotons, TMVA::Reader* reader){
int FillMMG(TRootPhoton* myphoton, TRootMuon* mymuon1, TRootMuon* mymuon2, double EScale, bool doMC, bool doPhotonConversionMC, TClonesArray* mcParticles, TMVA::Reader* reader){

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

/*
      if (doPhotonConversionMC)
      {
				findConversionMCtruth(myphoton, mcPhotons, Photon_MCisConverted, Photon_MCconvEoverP, Photon_MCconvMass, Photon_MCconvCotanTheta, Photon_MCconvVertexX, Photon_MCconvVertexY, Photon_MCconvVertexZ);
      }
*/


 
      Photon_E = EScale*(myphoton->Energy());
			Photon_Ecorr_o_Ereco = EScale;
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
			if(Photon_isEB) Photon_ratioS4_corrected = 1.008 * Photon_ratioS4;
			if(Photon_isEE) Photon_ratioS4_corrected = 1.008074 * Photon_ratioS4;
			Photon_lamdbaDivCov = 0.0;
			if (Photon_covEtaEta != 0) Photon_lamdbaDivCov = (Photon_covEtaEta+Photon_covPhiPhi-sqrt((Photon_covEtaEta-Photon_covPhiPhi)*(Photon_covEtaEta-Photon_covPhiPhi)+4*Photon_covEtaPhi*Photon_covEtaPhi))/Photon_covEtaEta;
//			Photon_SC_rawE_x_fEta = Photon_SC_rawE * fEta(Photon_SC_Eta);
			
//			Photon_SC_rawE_x_fEta_x_fBrem = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), 0);
//			Photon_SC_rawE_x_fEta_x_fBrem_AF = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), 1);
//			Photon_SC_rawE_x_fEta_x_fBrem_L = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), 2);
/*
			Photon_SC_rawE_x_fEta_x_fBrem = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11");
			Photon_SC_rawE_x_fEta_x_fBrem_AF = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), "Anne-Fleur");
			Photon_SC_rawE_x_fEta_x_fBrem_L = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), "Louis");

			float etraw_fEta_fBrem = Photon_SC_rawE_x_fEta_x_fBrem/cosh(Photon_SC_Eta);
			float etraw_fEta_fBrem_AF = Photon_SC_rawE_x_fEta_x_fBrem_AF/cosh(Photon_SC_Eta);
			float etraw_fEta_fBrem_L = Photon_SC_rawE_x_fEta_x_fBrem_L/cosh(Photon_SC_Eta);
*/
//			Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), 0) * EtEtaCor(etraw_fEta_fBrem, abs(Photon_SC_Eta), myphoton->isEEPho(), 0);
//			Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), 0) * EtEtaCor(etraw_fEta_fBrem_AF, abs(Photon_SC_Eta), myphoton->isEEPho(), 1);
//			Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), 0) * EtEtaCor(etraw_fEta_fBrem_L, abs(Photon_SC_Eta), myphoton->isEEPho(), 1);
/*
			Photon_SC_rawE_x_fEta_x_fBrem_x_fEtEta = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11") * EtEtaCor(etraw_fEta_fBrem, abs(Photon_SC_Eta), myphoton->isEEPho(), "START42_V11");
			Photon_SC_rawE_x_fEta_x_fBrem_AF_x_fEtEta = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11") * EtEtaCor(etraw_fEta_fBrem_AF, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur");
			Photon_SC_rawE_x_fEta_x_fBrem_L_x_fEtEta = Photon_SC_rawE * fEta(Photon_SC_Eta) * BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11") * EtEtaCor(etraw_fEta_fBrem_L, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur");
*/

			Photon_secondMomentMaj = myphoton->secondMomentMaj();
			Photon_secondMomentMin = myphoton->secondMomentMin();
			Photon_secondMomentAlpha = myphoton->secondMomentAlpha();

			Photon_etaLAT = myphoton->etaLAT();
			Photon_phiLAT = myphoton->phiLAT();
			Photon_LAT = myphoton->lat();
			Photon_Zernike20 = myphoton->zernike20();
			Photon_Zernike42 = myphoton->zernike42();
			Photon_ESratio = myphoton->superCluster()->esRatio();
	

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

/*
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
*/


    TLorentzVector mumugamma;
    TLorentzVector mumuSC;
    TLorentzVector mumu5x5;
    TLorentzVector mumuSC_raw;
/*    TLorentzVector mumuSC_raw_fEta;
	
    TLorentzVector mumuSC_raw_fEta_fBrem, mumuSC_raw_fEta_fBrem_AF, mumuSC_raw_fEta_fBrem_L, mumuSC_raw_fEta_fBrem_fEtEta, mumuSC_raw_fEta_fBrem_AF_fEtEta, mumuSC_raw_fEta_fBrem_L_fEtEta;
*/

    TLorentzVector *PhotonEScale = new TLorentzVector( EScale*(myphoton->Px()), EScale*(myphoton->Py()), EScale*(myphoton->Pz()), EScale*(myphoton->Energy()));
    TLorentzVector *PhotonSC = new TLorentzVector( EScale*Px_SC, EScale*Py_SC, EScale*Pz_SC, EScale*(myphoton->superCluster()->Mag()) );
    TLorentzVector *Photon5x5 = new TLorentzVector(EScale*Px_5x5 , EScale*Py_5x5, EScale*Pz_5x5, EScale*(myphoton->e5x5()));
    TLorentzVector *PhotonSC_raw = new TLorentzVector(EScale*Px_SCraw , EScale*Py_SCraw, EScale*Pz_SCraw, EScale*(myphoton->superCluster()->rawEnergy()));
/*
    TLorentzVector *PhotonSC_raw_fEta = new TLorentzVector(EScale*Px_SCraw_fEta , EScale*Py_SCraw_fEta, EScale*Pz_SCraw_fEta, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta)));

    TLorentzVector *PhotonSC_raw_fEta_fBrem = new TLorentzVector(EScale*Px_SCraw_fEta_fBrem, EScale*Py_SCraw_fEta_fBrem, EScale*Pz_SCraw_fEta_fBrem, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta))*(BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11")));

    TLorentzVector *PhotonSC_raw_fEta_fBrem_AF = new TLorentzVector(EScale*Px_SCraw_fEta_fBrem_AF, EScale*Py_SCraw_fEta_fBrem_AF, EScale*Pz_SCraw_fEta_fBrem_AF, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta))*(BremCor(Photon_SC_brem, myphoton->isEEPho(), "Anne-Fleur")));

    TLorentzVector *PhotonSC_raw_fEta_fBrem_L = new TLorentzVector(EScale*Px_SCraw_fEta_fBrem_L, EScale*Py_SCraw_fEta_fBrem_L, EScale*Pz_SCraw_fEta_fBrem_L, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta))*(BremCor(Photon_SC_brem, myphoton->isEEPho(), "Louis")));

    
    TLorentzVector *PhotonSC_raw_fEta_fBrem_fEtEta = new TLorentzVector(EScale*Px_SCraw_fEta_fBrem_fEtEta, EScale*Py_SCraw_fEta_fBrem_fEtEta, EScale*Pz_SCraw_fEta_fBrem_fEtEta, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta))*(BremCor(Photon_SC_brem, myphoton->isEEPho(), "START42_V11"))*(EtEtaCor(etraw_fEta_fBrem, abs(Photon_SC_Eta), myphoton->isEEPho(), "START42_V11")));

    TLorentzVector *PhotonSC_raw_fEta_fBrem_AF_fEtEta = new TLorentzVector(EScale*Px_SCraw_fEta_fBrem_AF_fEtEta, EScale*Py_SCraw_fEta_fBrem_AF_fEtEta, EScale*Pz_SCraw_fEta_fBrem_AF_fEtEta, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta))*(BremCor(Photon_SC_brem, myphoton->isEEPho(), "Anne-Fleur"))*(EtEtaCor(etraw_fEta_fBrem_AF, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur")));

    TLorentzVector *PhotonSC_raw_fEta_fBrem_L_fEtEta = new TLorentzVector(EScale*Px_SCraw_fEta_fBrem_L_fEtEta, EScale*Py_SCraw_fEta_fBrem_L_fEtEta, EScale*Pz_SCraw_fEta_fBrem_L_fEtEta, EScale*(myphoton->superCluster()->rawEnergy())*(fEta(Photon_SC_Eta))*(BremCor(Photon_SC_brem, myphoton->isEEPho(), "Louis"))*(EtEtaCor(etraw_fEta_fBrem_L, abs(Photon_SC_Eta), myphoton->isEEPho(), "Anne-Fleur")));
*/



//    mumugamma = (*leadingMuon) + (*subleadingMuon) + (*myphoton);
    mumugamma = (*leadingMuon) + (*subleadingMuon) + (*PhotonEScale);
    mumuSC = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC);
    mumu5x5 = (*leadingMuon) + (*subleadingMuon) + (*Photon5x5);
    mumuSC_raw = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw);
/*
    mumuSC_raw_fEta = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta);

    mumuSC_raw_fEta_fBrem = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta_fBrem);
    mumuSC_raw_fEta_fBrem_AF = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta_fBrem_AF);
    mumuSC_raw_fEta_fBrem_L = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta_fBrem_L);
    mumuSC_raw_fEta_fBrem_fEtEta = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta_fBrem_fEtEta);
    mumuSC_raw_fEta_fBrem_AF_fEtEta = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta_fBrem_AF_fEtEta);
    mumuSC_raw_fEta_fBrem_L_fEtEta = (*leadingMuon) + (*subleadingMuon) + (*PhotonSC_raw_fEta_fBrem_L_fEtEta);
*/
    double mumugammaInvMass = mumugamma.M();
    double mumuSCInvMass = mumuSC.M();
    double mumu5x5InvMass = mumu5x5.M();
    double mumuSC_rawInvMass = mumuSC_raw.M();
/*
    double mumuSC_rawInvMass_fEta = mumuSC_raw_fEta.M();
    
    double mumuSC_rawInvMass_fEta_fBrem = mumuSC_raw_fEta_fBrem.M();
    double mumuSC_rawInvMass_fEta_fBrem_AF = mumuSC_raw_fEta_fBrem_AF.M();
    double mumuSC_rawInvMass_fEta_fBrem_L = mumuSC_raw_fEta_fBrem_L.M();
    double mumuSC_rawInvMass_fEta_fBrem_fEtEta = mumuSC_raw_fEta_fBrem_fEtEta.M();
    double mumuSC_rawInvMass_fEta_fBrem_AF_fEtEta = mumuSC_raw_fEta_fBrem_AF_fEtEta.M();
    double mumuSC_rawInvMass_fEta_fBrem_L_fEtEta = mumuSC_raw_fEta_fBrem_L_fEtEta.M();
*/
    Mmumugamma = mumugammaInvMass;
//		if( ((Mmumugamma>97.2) && (Mmumugamma<110.0)) || ((Mmumugamma>70.0) && (Mmumugamma<87.2)) ) cout << "isVeryLooseMMG:isLooseMMG:isTightMMG " << isVeryLooseMMG << isLooseMMG << isTightMMG << "\t\t\tMmumugamma= " << Mmumugamma << endl;
//		cout << "ievt= " << iEvent << "\t\tVL:L:T:M " << isVeryLooseMMG << isLooseMMG << isTightMMG << isMultipleCandidate << "\t\t\tMmumugamma= " << Mmumugamma << endl;
//		cout << "ievt= " << iEvent << "\t\t" << isMMGCandidate << isAfterFSRCut1 << isAfterFSRCut2 << isAfterFSRCut3 << isAfterFSRCut4 << isVeryLooseMMG << isLooseMMG << isTightMMG << isMultipleCandidate << "\t\t\tMmumugamma= " << Mmumugamma << endl;
    Mmumugamma_SC = mumuSCInvMass;
    Mmumugamma_5x5 = mumu5x5InvMass;
    Mmumugamma_SCraw = mumuSC_rawInvMass;
/*
    Mmumugamma_SCraw_fEta = mumuSC_rawInvMass_fEta;
   
    Mmumugamma_SCraw_fEta_fBrem = mumuSC_rawInvMass_fEta_fBrem;
    Mmumugamma_SCraw_fEta_fBrem_AF = mumuSC_rawInvMass_fEta_fBrem_AF;
    Mmumugamma_SCraw_fEta_fBrem_L = mumuSC_rawInvMass_fEta_fBrem_L;
    Mmumugamma_SCraw_fEta_fBrem_fEtEta = mumuSC_rawInvMass_fEta_fBrem_fEtEta;
    Mmumugamma_SCraw_fEta_fBrem_AF_fEtEta = mumuSC_rawInvMass_fEta_fBrem_AF_fEtEta;
    Mmumugamma_SCraw_fEta_fBrem_L_fEtEta = mumuSC_rawInvMass_fEta_fBrem_L_fEtEta;
*/
    mumugamma.Clear();
    mumuSC.Clear();
    mumu5x5.Clear();
    mumuSC_raw.Clear();
    PhotonEScale->Clear();
    PhotonSC->Clear();
    Photon5x5->Clear();
    PhotonSC_raw->Clear();
//    PhotonSC_raw_fEta->Clear();

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

