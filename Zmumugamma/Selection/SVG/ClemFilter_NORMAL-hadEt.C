// Macro for applying Clement Baty's cuts to the root output file of TotoAnalyzer
// V 021v05, modified for CMSSW_3_5_8_patch3 (January 2010)
{
// The events passing the cuts are put in the output file OUTPUT.root
// Macro by O.Bondu on the skeleton Filter.C from M.Lethuillier in UserCode/IpnTreeProducer for CMSSW 2_2_9

// ********************************************************************
// *** Initialization ***
// ********************************************************************
	gROOT->Reset();
	#include <vector>
	#include <iomanip>
	const double M_PI = 3.14159265358979323846;
	int verbosity = 0;

	cout<<"Loading librairies"<<endl;
	gSystem->Load("libPhysics.so");
	gSystem->Load("libEG.so");
	gSystem->Load("/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/src/libToto.so");
	gStyle->SetOptStat(111111);

// ********************************************************************
// *** Global IN parameters ***
// ********************************************************************
	bool signal = ISSIGNAL; //signal=true=signal || signal=false=background
  bool stew = ISSTEW; //if the background source is stew, we need to run csa07id 62/63 in order to emulate triggers previous to TotoAnalyzer
  bool zjet_veto = IS_ZJETS_VETO; // true if the background sample is Z+Jets

	unsigned int BEGIN=BEGINFILENUMBER;
	unsigned int END=ENDFILENUMBER; // Parameters of each input files 
  char* part="SAMPLEPART";

// ********************************************************************
// *** Setting IN parameters and reading IN files ***
// ********************************************************************
	bool doHLT = true, doMC = true, doSignalMuMuGamma = true, doSignalTopTop = false, doPhotonConversionMC = true, doTrack = true, doJet = true, doMuon = true, doElectron = true, doPhoton = true, doCluster = true, doPhotonIsolation = true, doPhotonConversion = true, doMET = true;

	// Get input file, trees and branches
	cout<<"Reading ROOT input files"<<endl;
	TChain *inputEventTree = new TChain("eventTree");
	for (int i = BEGIN ; i <= END ; i++) { // FOR LOCAL FILES GENERIC OUTPUTFILE_partie_X_sample_Y.root 
		inputEventTree->Add(Form("/sps/cms/obondu/CMSSW_3_5_8_patch3/src/Zmumugamma/RecoSamples/%s/Toto_%s_%i.root", part, part, i));
    cout << "Adding OUTPUTFILE_partie_" << part << "_sample_" << i << ".root" << endl;
  }
	cout<<"Using "<<inputEventTree->GetNtrees()<<" files"<<endl;
	unsigned int NbEvents = (int)inputEventTree->GetEntries();
	if( verbosity > 1) {cerr<<"NbEvents: "<<NbEvents<<endl;}

	TBranch* event_br = (TBranch *) inputEventTree->GetBranch("Event");
	TRootEvent* INrootEvent = 0;
	event_br->SetAddress(&INrootEvent);
		
	if(doMC){
		TBranch* mcParticles_br = 0;
		TClonesArray* INmcParticles = new TClonesArray("TRootMCParticle", 0);
		inputEventTree->SetBranchAddress("MCParticles", &INmcParticles, &mcParticles_br);
		inputEventTree->SetBranchStatus("MCParticles", 1);}
	if(doSignalMuMuGamma){
		TBranch* mcSignalMuMuGamma_br = 0;
		TRootSignalEvent* INmcMuMuGammaEvent = 0;
		inputEventTree->SetBranchAddress("MuMuGamma", &INmcMuMuGammaEvent, &mcSignalMuMuGamma_br);
		inputEventTree->SetBranchStatus("MuMuGamma", 1);}
	if(doSignalTopTop){
		TBranch* mcTopTopEvent_br = 0;
		TRootSignalEvent* INmcTopTopEvent = 0;
		inputEventTree->SetBranchAddress("rootMCTopTop", &INmcTopTopEvent, &mcTopTopEvent_br);
		inputEventTree->SetBranchStatus("rootMCTopTop", 1);}
	if(doPhotonConversionMC){
		TBranch* mcPhotons_br = 0;
		TClonesArray* INmcPhotons = new TClonesArray("TRootMCPhoton", 0);
		inputEventTree->SetBranchAddress("MCPhotons", &INmcPhotons, &mcPhotons_br);
		inputEventTree->SetBranchStatus("MCPhotons", 1);}
	if(doTrack){
		TBranch* tracks_br = 0;
		TClonesArray* INtracks = new TClonesArray("TRootTrack", 0);
		inputEventTree->SetBranchAddress("Tracks", &INtracks, &tracks_br);		
    inputEventTree->SetBranchStatus("Tracks", 1);}
	if(doJet){
		TBranch* jets_br = 0;
		TClonesArray* INjets = new TClonesArray("TRootJet", 0);
		inputEventTree->SetBranchAddress("Jets", &INjets, &jets_br);
		inputEventTree->SetBranchStatus("Jets", 1);}
	if(doMuon){
		TBranch* muons_br = 0;
		TClonesArray* INmuons = new TClonesArray("TRootMuon", 0);
		inputEventTree->SetBranchAddress("Muons", &INmuons, &muons_br);
    inputEventTree->SetBranchStatus("Muons", 1);}
	if(doElectron){
		TBranch* electrons_br = 0;
		TClonesArray* INelectrons = new TClonesArray("TRootElectron", 0);
		inputEventTree->SetBranchAddress("Electrons", &INelectrons, &electrons_br);
    inputEventTree->SetBranchStatus("Electrons", 1);}
	if(doPhoton){
		TBranch* photons_br = 0;
		TClonesArray* INphotons = new TClonesArray("TRootPhoton", 0);
		inputEventTree->SetBranchAddress("Photons", &INphotons, &photons_br);		
    inputEventTree->SetBranchStatus("Photons", 1);}
	if(doCluster){
		TBranch* clusters_br = 0;
		TClonesArray* INclusters = new TClonesArray("TRootCluster", 0);
		inputEventTree->SetBranchAddress("BasicClusters", &INclusters, &clusters_br);
    inputEventTree->SetBranchStatus("BasicClusters", 1);
		TBranch* superClusters_br = 0;
		TClonesArray* INsuperClusters = new TClonesArray("TRootSuperCluster", 0);
		inputEventTree->SetBranchAddress("SuperClusters", &INsuperClusters, &superClusters_br);
    inputEventTree->SetBranchStatus("SuperClusters", 1);}
	if(doPhotonConversion){
		TBranch* conversions_br = 0;
		TClonesArray* INconversionTracks = new TClonesArray("TRootTrack", 0);
		inputEventTree->SetBranchAddress("ConversionTracks", &INconversionTracks, &conversions_br);
    inputEventTree->SetBranchStatus("ConversionTracks", 1);}
	if(doMET){
		TBranch* met_br = 0;
		TClonesArray* INmet = new TClonesArray("TRootMET", 0);
		inputEventTree->SetBranchAddress("MET", &INmet, &met_br);
    inputEventTree->SetBranchStatus("MET", 1);}

	// ********************************************************************
	// *** Preparing OUT files
	// ********************************************************************
	// Create output file and copy trees headers
	TFile *outputFile = new TFile("OUTPUT.root","recreate");
	TTree *outputEventTree = inputEventTree->CloneTree(0);

	unsigned int nSelected=0, NbEventsAfterCSA07ID = 0, NbEventsAfterZJETVETO = 0, NbEventsAfterC1a = 0, NbEventsAfterC1b = 0, NbEventsAfterC1c = 0, NbEventsAfterC1d = 0, NbEventsAfterC1e = 0, NbEventsAfterC2a = 0, NbEventsAfterC2b = 0, NbEventsAfterC2c = 0, NbEventsAfterC3 = 0, NbEventsAfterC4 = 0, NbEventsAfterC5 = 0, NbEventsAfterC6 = 0, NbEventsAfterC7 = 0, NbEventsAfterC8 = 0, NbEventsAfterC9 = 0, NbEventsAfterC10 = 0;

	// ********************************************************************
	// *** Preparing histograms
	// ********************************************************************

	// ********************************************************************
	// *** Applying selection cuts 
	// ********************************************************************
  cout<<"Applying cuts"<<endl;
  if(stew){ cout<<"INPUT is stew, so we use csa07id"<<endl; }
  if(zjet_veto){ cout<<"INPUT is Z+Jets, so we use zjet veto"<<endl; }

	for(unsigned int ievt=0; ievt<NbEvents; ievt++){// Loop over all events
    if( verbosity > 1) {cerr<<"Event #"<<ievt<<endl;}
    int nprint = (int)((double)NbEvents/(double)100.0);
    if( (ievt % nprint)==0 ){ cout<< ievt <<" events done over "<<NbEvents<<" ( "<<ceil((double)ievt/(double)NbEvents*100)<<" \% )"<<endl; }

    if( verbosity > 1) {cerr<<"Getting entry"<<endl;}
		inputEventTree->GetEvent(ievt);
    if( verbosity > 1) {cerr<<"\tentry fetched!"<<endl;}

		// ********************************************************************
    // *** cut 0.a : CSA07ID *** (for STEW only)
    // ********************************************************************
		if( verbosity > 1) { cerr<<"CSA07ID"<<endl;}
    if(stew){
      if( (INrootEvent->csa07id() != 62) && (INrootEvent->csa07id() != 63) ){
        cerr<<"CSA07ID is not 62/63 ( "<< INrootEvent->csa07id() << ") aborting event " << ievt << endl;
        continue;
      } else {
        NbEventsAfterCSA07ID++;
      }
    }// end of if stew

		// ********************************************************************
		// *** cut 0.b : Z+Jets veto *** (for ZJets events)
		// ********************************************************************
    if( zjet_veto ){
      bool MCphotons_from_muons = false;
      for( int iMCparticle = 0 ; iMCparticle < INmcParticles->GetEntries() ; iMCparticle++ ){
        TRootMCParticle *mcParticleCandidate = (TRootMCParticle *)INmcParticles->At(iMCparticle);
        if( (mcParticleCandidate->status()==1) && (mcParticleCandidate->type() == 22) ){ // if the particle is a true MC photon
          if( abs(mcParticleCandidate->motherType()) == 13 ){// if the true MC photon origins from a muon
            MCphotons_from_muons = true;
          }
        }
      }// end of loop over MC particles
      if( MCphotons_from_muons ){
        cerr<<"SAFE: photon(s) coming from muon, aborting event " << ievt << endl;
        continue;
      } else {
        NbEventsAfterZJETVETO++;
      }
    }// end of if Z+Jets veto

    int NbPhotons = INphotons->GetEntries();
    int NbMuonstot = INmuons->GetEntries();
		// ********************************************************************
    // *** cut 1 ***
    // ********************************************************************

    // ** subcut 1.a : selection of events with at least 2 muons
    // ********************************************************************
    if( verbosity > 1) {cerr<<"subcut 1.a"<<endl;}
    if( NbMuonstot > 1){
      NbEventsAfterC1a++;

			if( verbosity > 3 ){cerr<<"\tFetchin' muons with valid eta ...";}
      vector<int> almostValidMuons;
      almostValidMuons.clear();
      TRootMuon *almostValidMuonCandidate = new TRootMuon();
      for(int imuon=0 ; imuon<NbMuonstot ; imuon++){
        TRootMuon *almostValidMuonCandidate = (TRootMuon*) INmuons->At(imuon);
        if( fabs(almostValidMuonCandidate->Eta())<2.5 ){
          almostValidMuons.push_back(imuon);
        }
      }
			if( verbosity > 3 ){cerr<<"  done"<<endl;}
//			delete almostValidMuonCandidate;
      unsigned int NbAlmostValidMuons = almostValidMuons.size();

      // ** subcut 1.b : selection of almostvalid muons : cut on eta
      // ********************************************************************
      if( verbosity > 1) {cerr<<"subcut 1.b"<<endl;}
      if(NbAlmostValidMuons > 1){
        NbEventsAfterC1b++;
			
				if( verbosity > 2 ){cerr<<"Number of valid eta muons : "<<NbAlmostValidMuons<<endl;}	
				if( verbosity > 3 ){cerr<<"\tFetchin' validEta muon with max pT ..."<<endl;}
				if( verbosity > 4 ){cerr<<"\t\tInit stuff"<<endl;}  
        TRootMuon *MPtMuon = (TRootMuon*) INmuons->At(almostValidMuons[0]);
        double PtMuon = MPtMuon->Pt();
				if( verbosity > 4 ){cerr<<"\t\tActual Max Pt :"<<PtMuon<<endl;}
        int ialmostValidMPtMuon = 0;
				if( verbosity > 4 ){cerr<<"\t\tStart Loop"<<endl;}
				TRootMuon *MPtMuonCandidate;
				MPtMuonCandidate = new TRootMuon();
        for(int imuon=1 ; imuon<NbAlmostValidMuons ; imuon++){
					if( verbosity > 5 ){cerr<<"\t\t\tIteration \# "<<imuon<<endl;}
	        if( verbosity > 4 ){cerr<<"\t\t\tActual Max Pt :"<<PtMuon<<endl;}
					MPtMuonCandidate = new TRootMuon();
//          TRootMuon *MPtMuonCandidate = new TRootMuon();
//          TRootMuon *MPtMuonCandidate = (TRootMuon*) INmuons->At(almostValidMuons[imuon]);
          MPtMuonCandidate = (TRootMuon*) INmuons->At(almostValidMuons[imuon]);
	        if( verbosity > 4 ){cerr<<"\t\t\tCandidate for new max Pt :"<<MPtMuonCandidate->Pt()<<endl;}
          if(MPtMuonCandidate->Pt() > PtMuon){
						if( verbosity > 5 ){cerr<<"\t\t\tNew Max Pt Muon"<<endl;}
            MPtMuon = MPtMuonCandidate;
            PtMuon = MPtMuon->Pt();
            ialmostValidMPtMuon = imuon;
          }
        }
				if( verbosity > 4 ){cerr<<"\t\tDelete stuff"<<endl;} 
//				delete MPtMuonCandidate;
				if( verbosity > 4 ){cerr<<"\t\tEnd Loop"<<endl;}
        if( verbosity > 3 ){cerr<<"  done"<<endl;}
				if( verbosity > 3 ){cerr<<"\tFetchin' validEta antimuon with max pT ...";}
				TRootMuon *MPtMuon_oppositeCharge = new TRootMuon();
        double PtMuon_oppositeCharge = 0.0;
        bool isThereOppositeCharge = false;
        for(int imuon=0 ; imuon<NbAlmostValidMuons ; imuon++){
          TRootMuon *MPtMuon_oppositeChargeCandidate = new TRootMuon();
          TRootMuon *MPtMuon_oppositeChargeCandidate = (TRootMuon*) INmuons->At(almostValidMuons[imuon]);
          if( imuon != ialmostValidMPtMuon ){
            if( (MPtMuon_oppositeChargeCandidate->charge())*(MPtMuon->charge()) < 0.0 ){
              if(MPtMuon_oppositeChargeCandidate->Pt() > PtMuon_oppositeCharge){
                MPtMuon_oppositeCharge = MPtMuon_oppositeChargeCandidate;
                PtMuon_oppositeCharge = MPtMuon_oppositeCharge->Pt();
                isThereOppositeCharge = true;
              }
            }
          }
//					delete MPtMuon_oppositeChargeCandidate;
        }// end of loop over almost valid muons
				if( verbosity > 3 ){cerr<<"  done"<<endl;}


        // ** subcut 1.c : check on opposite charge of muon criterium
        // ********************************************************************
        if( verbosity > 1) {cerr<<"subcut 1.c"<<endl;}
        if( isThereOppositeCharge ){
          NbEventsAfterC1c++;

        // ** subcut 1.d : selection on pt : valid muons selection (since the two muons selected have opposite charge, passing cut on eta and are the highest pt per charge, we can make them pass the selection immediately
        // ********************************************************************
				if( verbosity > 1) {cerr<<"subcut 1.d"<<endl;}
        if( (PtMuon > 10.0) && (PtMuon_oppositeCharge > 10.0) ){
          NbEventsAfterC1d++;

          // ** subcut 1.e : cut on mumu invariant mass
          // ********************************************************************
					if( verbosity > 1) {cerr<<"subcut 1.e"<<endl;}
          TRootParticle *mumu = new TRootParticle();
          *mumu = (*MPtMuon) + (*MPtMuon_oppositeCharge);
          double mumuInvMass = mumu->M();
//					delete mumu;
          if( mumuInvMass >= 20.0 ){
            NbEventsAfterC1e++;

            // ********************************************************************
            // *** cut 2 ***
            // ********************************************************************
					if( verbosity > 1) {cerr<<"cut 2"<<endl;}

            // ** subcut 2.a : We need at least one photon
            // ********************************************************************
						if( verbosity > 1) {cerr<<"subcut 2.a"<<endl;}
            if(NbPhotons > 0){
              NbEventsAfterC2a++;
              unsigned int NbValidPhotons = 0;
              // Make a list of valid photons
              vector<int> validPhotons;
              validPhotons.clear();
              TRootPhoton *validPhotonCandidate = new TRootPhoton();
              for(int iphoton=0 ; iphoton<NbPhotons ; iphoton++){
                TRootPhoton *validPhotonCandidate = (TRootPhoton*) INphotons->At(iphoton);
                if( (validPhotonCandidate->Pt()>10.0) && (fabs(validPhotonCandidate->Eta())<2.5) ){
                  validPhotons.push_back(iphoton);
                }
              }// end of loop over photons
//							delete validPhotonCandidate;
              NbValidPhotons = validPhotons.size();

              // ** subcut 2.b : We need at least one valid photon
              // ********************************************************************
							if( verbosity > 1) {cerr<<"subcut 2.b"<<endl;}
              if(NbValidPhotons > 0){
                NbEventsAfterC2b++;
								if( verbosity > 1) {cerr<<"Nb of Photons (valid)"<<NbPhotons<<" ( "<<NbValidPhotons<<" )"<<endl;}
      // MPtPhoton : Most Pt Photon
      // PtPhoton : Pt of the most energetic Photon
                TRootPhoton *MPtPhoton = new TRootPhoton();
                TRootPhoton *MPtPhoton = (TRootPhoton*) INphotons->At(validPhotons[0]);
                double PtPhoton = MPtPhoton->Pt();
                // Get the photon with the highest pt WITHIN those valid :
                for(int iphoton=0 ; iphoton<NbValidPhotons ; iphoton++){
                  TRootPhoton *MPtPhotonCandidate = new TRootPhoton();
                  TRootPhoton *MPtPhotonCandidate = (TRootPhoton*) INphotons->At(validPhotons[iphoton]);
                  if(MPtPhotonCandidate->Pt() > PtPhoton){
                    MPtPhoton = MPtPhotonCandidate;
                    PtPhoton = MPtPhoton->Pt();
                  }
//									delete MPtPhotonCandidate;
                }// End of getting the highest pt Photon

                // ********************************************************************
                // *** Compute mumugamma invariant mass ***
                // ********************************************************************
								TRootParticle *mumugamma = new TRootParticle();  
                *mumugamma = (*MPtMuon) + (*MPtMuon_oppositeCharge) + (*MPtPhoton);
                double mumugammaInvMass = mumugamma->M();
//								delete mumugamma;

                double phiPhoton = MPtPhoton->Phi();
                double etaPhoton = MPtPhoton->Eta();
                double phiMuon = MPtMuon->Phi();
                double etaMuon = MPtMuon->Eta();
                double phiMuon_oppositeCharge = MPtMuon_oppositeCharge->Phi();
                double etaMuon_oppositeCharge = MPtMuon_oppositeCharge->Eta();

                double dphiPM = fabs(phiPhoton - phiMuon);
                while (dphiPM > M_PI) dphiPM -= 2*M_PI;
                while (dphiPM <= -M_PI) dphiPM += 2*M_PI;
                double dphiPAM = fabs(phiPhoton - phiMuon_oppositeCharge);
                while (dphiPAM > M_PI) dphiPAM -= 2*M_PI;
                while (dphiPAM <= -M_PI) dphiPAM += 2*M_PI;

                double detaPM = fabs(etaPhoton - etaMuon);
                double detaPAM = fabs(etaPhoton - etaMuon_oppositeCharge);

                double deltaRPM = sqrt(detaPM*detaPM + dphiPM*dphiPM);
                double deltaRPAM = sqrt(detaPAM*detaPAM + dphiPAM*dphiPAM);

                double deltaRmin;
                TRootMuon *farMuon;
                TRootMuon *nearMuon;
                if(deltaRPM < deltaRPAM){
                  deltaRmin = deltaRPM;
                  farMuon = (TRootMuon*) MPtMuon_oppositeCharge;
                  nearMuon = (TRootMuon*) MPtMuon;
                } else {
                  deltaRmin = deltaRPAM; 
                  farMuon = (TRootMuon*) MPtMuon;
                  nearMuon = (TRootMuon*) MPtMuon_oppositeCharge;
                }

                // ** subcut 2.c : We need a photon distant enough from both muons
                // ********************************************************************
                if( (deltaRmin>=0.05) ){
                  NbEventsAfterC2c++;

                  // ********************************************************************
                  // *** cut 3 ***
                  // ********************************************************************
                  if( MPtPhoton->Pt() > 1.0){// *** cut 3 (should be always true) ***
                    NbEventsAfterC3++;

                    // ********************************************************************
                    // *** cut 4 ***
                    // ********************************************************************
                    if( (mumuInvMass>=40.0) && (mumuInvMass<=80.0) ){// *** cut 4 : Drell-Yan Cut ***
                      NbEventsAfterC4++;

 											// ********************************************************************
                      // *** cut 5 ***
 				              // ********************************************************************
                      if( (MPtPhoton->Et()>=12.0) && (deltaRmin<=0.8) ){// *** cut 5 ***
 				                NbEventsAfterC5++;

												// ********************************************************************
                        // *** cut 6/7 *** (6 in case of signal, 7 in case of background)
                        // ********************************************************************
                        bool cut67;
                        if(signal){		cut67 = (mumugammaInvMass >=87.2) && (mumugammaInvMass <=95.2);} // in case of signal
                        else {				cut67 = (mumugammaInvMass >=70.0) && (mumugammaInvMass <=110.0);} // in case of background
                        if(cut67){// *** cut 6.0 OR 7.0 ***
                          if(signal){
                            NbEventsAfterC6++;
                          } else {
                            NbEventsAfterC7++;
                          }

                          // ********************************************************************
                          // *** cut 8 *** 
                          // ********************************************************************
                          if(farMuon->isoR03_emEt() <= 1.0) {
                            NbEventsAfterC8++;

                            // ********************************************************************
                            // *** cut 9 *** 
                            // ********************************************************************
                            if(farMuon->Pt() >= 30.0) {
                              NbEventsAfterC9++;

															// ********************************************************************
				                      // *** cut 10 ***
        				              // ********************************************************************
				                      if( nearMuon->isoR03_hadEt() < 1.0 ){// *** cut 5 ***
        				                NbEventsAfterC10++;

																outputEventTree->Fill();
														    nSelected++;
																cerr << "OK: Surviving veto event: "<< ievt << endl;
															}// end of cut 5
															else { cerr << "\tCUT: event " << ievt  << " CUT at level X for large hadEt" << endl; }

                            }//end of cut 9
                            else { cerr << "\tCUT: event " << ievt  << " CUT at level IX for large hadEt " << endl; }

                          }//end of cut 8
                          else { cerr << "\tCUT: event " << ievt  << " CUT at level VIII for large sumPT " << endl; }

                        }// end of cut 6 OR 7
                        else {
                          if(signal){
                            cerr << "\tCUT: event " << ievt  << " CUT at level VI for Z Mass Window " << endl;
                          } else {
                            cerr << "\tCUT: event " << ievt  << " CUT at level VII for Z Mass Window " << endl;
                          }
                        }// end of cerr for cut 6-7

											}// end of cut 5
                      else { cerr << "\tCUT: event " << ievt  << " CUT at level V for gamma momentum" << endl; }

                    }// end of cut 4
                    else { cerr << "\tCUT: event " << ievt  << " CUT at level IV for Drell-Yan " << endl; }

                  }// end of cut 3
                  else { cerr << "\tCUT: event " << ievt  << " CUT at level III" << endl; }

                }//deltaRmin (2.c)
                else { cerr << "\tCUT: event " << ievt  << " CUT at level II for Photons (deltar)" << endl; }
							
							if( verbosity > 3 ){ cerr<<"Deleting stuff used for cuts II.B ...";}
//							delete MPtPhoton;
//							delete farMuon;
//							delete nearMuon;
							if( verbosity > 3 ){ cerr<<"   done"<<endl;}
              }//NbValidPhotons (2.b)
              else { cerr << "\tCUT: event " << ievt << " CUT at level II because of bad gamma" << endl; }

            }// end of cut 2.a (NbPhotons)
            else { cerr << "\tCUT: event " << ievt << " CUT at level II because "<<  NbPhotons  << " gamma" << endl; }

          }// mumuInvMass (1.e)
          else { cerr << "\tCUT: event " << ievt << " CUT at level I because of m(mumu)" << endl; }

        }// cut on muon pt (1.d)
        else { cerr << "\tCUT: event " << ievt << " CUT at level I because of bad muons (pt)" << endl; }

      }// opposite charge (1.c)
      else { cerr << "\tCUT: event " << ievt << " CUT at level I because of bad muons (charge)" << endl; }
		
		if( verbosity > 3 ){ cerr<<"Deleting stuff used for cuts I.B ...";}
//		delete MPtMuon;
//		delete MPtMuon_oppositeCharge;
		if( verbosity > 3 ){ cerr<<"   done"<<endl;}
    }// cut on muon eta (1.b)
    else { cerr << "\tCUT: event " << ievt << " CUT at level I because of bad muons (eta)" << endl; }
 
  }// at least 2 muons (end of cut 1) (1.a) 
  else { cerr << "\tCUT: event " << ievt << " CUT at level I because "<< NbMuonstot  << " muons only" << endl; }
    

	} // end of loop over events

	cout << nSelected << " selected events out of " << NbEvents << endl;
	cout<<"Writing surviving events in OUTPUT.root"<<endl;
	outputEventTree->AutoSave();
  outputFile.Write();
  outputFile.Close();
	delete outputFile;
	delete inputEventTree;
  
  cout<<"Writing (raw) results in RESULTS.txt"<<endl;
  cout<<endl;
  
  ofstream of("RESULTS.txt");
  of<<"CUT\#\t\t # of EVENTS"<<endl;
  of<<0<<"\t\t"<<NbEvents<<endl;
  of<<"CSA07"<<"\t\t"<<NbEventsAfterCSA07ID<<endl;
  of<<"ZJET"<<"\t\t"<<NbEventsAfterZJETVETO<<endl;
  of<<"1.a"<<"\t\t"<<NbEventsAfterC1a<<endl;
  of<<"1.b"<<"\t\t"<<NbEventsAfterC1b<<endl;
  of<<"1.c"<<"\t\t"<<NbEventsAfterC1c<<endl;
  of<<"1.d"<<"\t\t"<<NbEventsAfterC1d<<endl;
  of<<"1.e"<<"\t\t"<<NbEventsAfterC1e<<endl;
  of<<"2.a"<<"\t\t"<<NbEventsAfterC2a<<endl;
  of<<"2.b"<<"\t\t"<<NbEventsAfterC2b<<endl;
  of<<"2.c"<<"\t\t"<<NbEventsAfterC2c<<endl;
  of<<3<<"\t\t"<<NbEventsAfterC3<<endl;
  of<<4<<"\t\t"<<NbEventsAfterC4<<endl;
  of<<5<<"\t\t"<<NbEventsAfterC5<<endl;
  of<<6<<"\t\t"<<NbEventsAfterC6<<endl;
  of<<7<<"\t\t"<<NbEventsAfterC7<<endl;
  of<<8<<"\t\t"<<NbEventsAfterC8<<endl;
  of<<9<<"\t\t"<<NbEventsAfterC9<<endl;
	of<<10<<"\t\t"<<NbEventsAfterC10<<endl;
  of.close();


// ********************************************************************
// *** Compute selection efficiencies
// ********************************************************************
  cout<<endl<<endl;
  cout<<setprecision(4);
  cout<<"Number of events total :\t"<<NbEvents<<"\t( "<<(double)NbEvents/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after CSA07ID :\t"<<NbEventsAfterCSA07ID<<endl;
  cout<<"Number of events after Z+Jets veto :\t"<<NbEventsAfterZJETVETO<<endl;
  cout<<"Number of events after cut 1.a :\t"<<NbEventsAfterC1a<<"\t( "<<(double)NbEventsAfterC1a/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 1.b :\t"<<NbEventsAfterC1b<<"\t( "<<(double)NbEventsAfterC1b/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 1.c :\t"<<NbEventsAfterC1c<<"\t( "<<(double)NbEventsAfterC1c/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 1.d :\t"<<NbEventsAfterC1d<<"\t( "<<(double)NbEventsAfterC1d/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 1.e :\t"<<NbEventsAfterC1e<<"\t( "<<(double)NbEventsAfterC1e/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 2.a :\t"<<NbEventsAfterC2a<<"\t( "<<(double)NbEventsAfterC2a/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 2.b :\t"<<NbEventsAfterC2b<<"\t( "<<(double)NbEventsAfterC2b/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 2.c :\t"<<NbEventsAfterC2c<<"\t( "<<(double)NbEventsAfterC2c/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 3 :\t"<<NbEventsAfterC3<<"\t( "<<(double)NbEventsAfterC3/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 4 :\t"<<NbEventsAfterC4<<"\t( "<<(double)NbEventsAfterC4/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 5 :\t"<<NbEventsAfterC5<<"\t( "<<(double)NbEventsAfterC5/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 6 :\t"<<NbEventsAfterC6<<"\t( "<<(double)NbEventsAfterC6/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 7 :\t"<<NbEventsAfterC7<<"\t( "<<(double)NbEventsAfterC7/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 8 :\t"<<NbEventsAfterC8<<"\t( "<<(double)NbEventsAfterC8/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 9 :\t"<<NbEventsAfterC9<<"\t( "<<(double)NbEventsAfterC9/(double)NbEvents*100.0<<" % )"<<endl;
  cout<<"Number of events after cut 10 :\t"<<NbEventsAfterC10<<"\t( "<<(double)NbEventsAfterC10/(double)NbEvents*100.0<<" % )"<<endl;
  
  cout<<endl;
}
