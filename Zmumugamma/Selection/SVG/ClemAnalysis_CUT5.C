/*
From ClemAnalysis by Clement Baty
Modified by Olivier Bondu (October 2009)
*/
// Global File for doing all analysis
#include <vector>
// Main code
void ClemAnalysis(char* filename="TotoAna.root") {
	
// INIT

	// Parameters for files
	bool FILEisCHAIN=true; // Single [false] or multiple files [true]
		unsigned int BEGIN=DEBUT,END=FIN; // Parameters of each input files 
		char* part="PART"; // 0-3 
	/*
	 Type of file : 

		0: SIGNAL MORGAN 

		// SERIE UN
		1: BACKGROUND BB2MuMu
		2: BACKGROUND BB3JETS
		3: BACKGROUND STEW

		// SERIE DEUX
		BB1: BACKGROUND BB1JETS
		BB2: BACKGROUND BB2JETS
		BB3: BACKGROUND BB3JETS
		BB4: BACKGROUND BB4JETS
		BB5: BACKGROUND BB5JETS

		// SERIE TROIS
		PHX-20: BACKGROUND PHOTON X JETS range 20-60
		PHX-60: BACKGROUND PHOTON X JETS range 60-120
		PHX-120: BACKGROUND PHOTON X JETS range 120-180
		PHX-180: BACKGROUND PHOTON X JETS range 180-240
		PHX-240: BACKGROUND PHOTON X JETS range 240-300
		PHX-300: BACKGROUND PHOTON X JETS range 300-7000
	*/ 
	
	// Global parameters
	bool SIGNAL=false; 		// TRUE == SIGNAL ; FALSE == BACKGROUND
	bool NEED_CSA07_ID=false; 	// This choose between CSA07 ID number use or not (false by default, true for stew)
	bool NEED_ZJETS_VETO=false;	// This choose between ZJETS VETO or not (false by default, true for Z+JETS samples) 

	// Load external libraries for handle the rootchain format
	gSystem->Load("libPhysics.so");
        gSystem->Load("libEG.so");
        gSystem->Load("/sps/cms/obondu/CMSSW_3_5_8_patch3/src/UserCode/IpnTreeProducer/src/libToto.so");

	// General options for graphs and histos
	gStyle->SetOptStat(1);
	gStyle->SetOptStat(1111111);	

// PART 0 : Global Declarations	
	if(FILEisCHAIN) {
		// TChain chain("eventTree", "mychain");
		TChain *chain = new TChain("eventTree");
		cout << "Adding " << END-BEGIN+1 << " files : " << flush; 

/*
		for(int i = BEGIN ;  i <= END ; i++) { // FOR HPSS FILE
			chain->Add(Form("%s_%s/RECODIR/Toto_%s_%i.root",filename, part, part, i));
			cout << "." << flush;
		}
*/

		for (int i = BEGIN ; i <= END ; i++) { // FOR LOCAL FILES GENERIC RECODIR/Toto_X_Y.root 
			chain->Add(Form("RECODIR/Toto_%s_%d.root", part, i));
			cout << "Adding RECODIR/Toto_" << part << "_" << i << ".root" << endl;
		}

		cout << " DONE" << endl;
	} 
	else {

		filename="newfile.root";
		chain->Add(Form("%s", filename)); cout << "Add file : " << filename << endl; 
	}

	TFile* outputfile = new TFile(Form("EXPORTDIR/SelectionAnalysis_%s.root", part), "recreate");

// PART 1 : Settings branchs

	TRootEvent* event = NULL;
	chain->SetBranchAddress("Event",&event);
	    	    
	TClonesArray* jets = new TClonesArray("TRootJet", NULL);
	chain->SetBranchAddress("Jets",&jets);
        	
	TClonesArray* muons = new TClonesArray("TRootMuon", NULL);
	chain->SetBranchAddress("Muons",&muons);
	TRootMuon *mymuon, mymuonbis;
	    
	TClonesArray* electrons = new TClonesArray("TRootElectron", NULL);
	chain->SetBranchAddress("Electrons",&electrons);
    
	TClonesArray* correctedPhotons = new TClonesArray("TRootPhoton", NULL);
	chain->SetBranchAddress("Photons", &correctedPhotons);
	TRootPhoton *mycorrectedphoton;

	TClonesArray* mcparticles = new TClonesArray("TRootMCParticle", NULL);
	chain->SetBranchAddress("MCParticles",&mcparticles);
        
	unsigned int NbEvents = (int)chain->GetEntries();
// Part 2 : needed vars
	double deltar;
	double var_deltar[2];
	double deltaeta, deltaphi;
	const unsigned int NB_CUTS=10;

// Part 3 : Plots to make
	// !!!!!!!

	// N-1 PLOTS : NEW
	// PLOTS CUT 1
	TH1D * THESE_NB_MUONS[NB_CUTS+1];
	TH1D * THESE_PT_MUON[NB_CUTS+1];
	TH1D * THESE_ETA_MUON[NB_CUTS+1]; 
	TH1D * THESE_MASSE_MUON[NB_CUTS+1];
	// PLOTS CUT 2
	TH1D * THESE_NB_GAMMA[NB_CUTS+1];
	TH1D * THESE_PT_GAMMA[NB_CUTS+1];		// ALSO FOR CUT 3 AND 5
	TH1D * THESE_ETA_GAMMA[NB_CUTS+1];
	TH1D * THESE_DR_MUMUGAMMA[NB_CUTS+1];		// ALSO FOR CUT 5 
	// PLOTS CUT 4
	TH1D * THESE_MASSE_DIMUON[NB_CUTS+1];
	// PLOTS CUT 6 and 7
	TH1D * THESE_MASSE_MUMUGAMMA[NB_CUTS+1];	
	// PLOTS CUT 8
	TH1D * THESE_ISOEMET_DR03[NB_CUTS+1];
	// PLOTS CUT 9
	TH1D * THESE_PT_MUON_FAR[NB_CUTS+1];
	// INITIALISATION
	for (int nbcuts=0 ; nbcuts < NB_CUTS+1 ; nbcuts++) {
		THESE_NB_MUONS[nbcuts] =  new TH1D(Form("THESE_muons_numbers_%i", nbcuts), Form("# Muons at cut %i", nbcuts), 25, 0, 25);
		THESE_PT_MUON[nbcuts] =  new TH1D(Form("THESE_muons_pt_%i", nbcuts), Form("Pt muon at cut %i", nbcuts), 100, 0, 100);
		THESE_ETA_MUON[nbcuts] =  new TH1D(Form("THESE_muons_eta_%i", nbcuts), Form("Muons \eta at cut %i", nbcuts), 100, -5, 5);
		THESE_MASSE_MUON[nbcuts] =  new TH1D(Form("THESE_muons_masse_%i", nbcuts), Form("muons mass at cut %i", nbcuts), 200, 0, 200);
		THESE_MASSE_DIMUON[nbcuts] =  new TH1D(Form("THESE_dimuons_masse_%i", nbcuts), Form("Dimuons mass at cut %i", nbcuts), 300, 0, 300);
		THESE_NB_GAMMA[nbcuts] =  new TH1D(Form("THESE_gamma_numbers_%i", nbcuts), Form("# \gamma at cut %i", nbcuts), 25, 0, 25);
		THESE_PT_GAMMA[nbcuts] =  new TH1D(Form("THESE_gamma_pt_%i", nbcuts), Form("Pt \gamma at cut %i", nbcuts), 200, 0, 200);
		THESE_ETA_GAMMA[nbcuts] =  new TH1D(Form("THESE_gamma_eta_%i", nbcuts), Form("\gamma \eta at cut %i", nbcuts), 100, -5, 5);
		THESE_DR_MUMUGAMMA[nbcuts] =  new TH1D(Form("THESE_mumugamma_dr_%i", nbcuts), Form("DR (\mu_1, \mu_2 , \gamma) at cut %i", nbcuts), 100, 0, 5);
		THESE_MASSE_MUMUGAMMA[nbcuts] =  new TH1D(Form("THESE_mumugamma_masse_%i", nbcuts), Form("MuMuGamma Mass at cut %i", nbcuts), 250, 0, 250);
		THESE_ISOEMET_DR03[nbcuts] =  new TH1D(Form("THESE_isoemet_dr03_%i", nbcuts), Form("ISOEMET_{\Delta R = 0.3} at cut %i", nbcuts), 100, 0, 10);
		THESE_PT_MUON_FAR[nbcuts] =  new TH1D(Form("THESE_far_muon_pt_%i", nbcuts), Form("Pt Muon Far at cut %i", nbcuts), 100, 0, 100);
	}

	// !!!!!!

	// GLOBAL mumugamma plots
	TH1D* Reco_mumugamma_invariant_mass[NB_CUTS+1];
	TH1D* plots_deltar_near[NB_CUTS+1];
	TH1D* plots_deltar_far[NB_CUTS+1];
	for (int nbcuts=0 ; nbcuts < NB_CUTS+1 ; nbcuts++) {
		Reco_mumugamma_invariant_mass[nbcuts] = new TH1D(Form("Reco_Invariant_Mass_%i", nbcuts), Form("InvariantMass after cut %i", nbcuts), 250, 0, 250);
		plots_deltar_near[nbcuts] = new TH1D(Form("deltar_near_%i", nbcuts), Form("Deltar NEAR shape after cut %i", nbcuts), 250, 0, 25);
		plots_deltar_far[nbcuts] = new TH1D(Form("deltar_far_%i", nbcuts), Form("Deltar FAR shape after cut %i", nbcuts), 250, 0, 25);
	}  		
	TH1D* Final_Reco_mumugamma_invariant_mass = new TH1D("Final_Reco_Invariant_Mass", "Masse Invariante Finale", 250, 0, 250);

	// FAR AND NEAR mu && gamma
	// ONLY ONE MUONS
	TH1D* ptmuon_far[NB_CUTS+1];
	TH1D* ptmuon_high[NB_CUTS+1];
	TH1D* ptgamma_valid[NB_CUTS+1];
	for (int nbcuts=0 ; nbcuts < NB_CUTS+1 ; nbcuts++) {
		// Muon PT
		ptmuon_far[nbcuts] = new TH1D(Form("Muon_PT_far_%i", nbcuts), Form("Muon PT (far cut %i)", nbcuts), 100, 0, 100);	
		ptmuon_high[nbcuts] = new TH1D(Form("Muon_PT_high_%i", nbcuts), Form("Muon PT (high cut %i)", nbcuts), 100, 0, 100);	
		// Photons PT
		ptgamma_valid[nbcuts] = new TH1D(Form("Gamma_PT_valid_%i", nbcuts), Form("Gamma PT (valid cut %i)", nbcuts), 100, 0, 100);	
	}
	// DR = 0.3 FAR && NEAR
	TH1D* ISO_extrems_vars_dr03_emEt_near[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr03_emEt_far[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr03_hadEt_near[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr03_hadEt_far[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr03_hoEt_near[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr03_hoEt_far[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr03_njets_near[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr03_njets_far[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr03_ntracks_near[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr03_ntracks_far[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr03_sumpt_near[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr03_sumpt_far[NB_CUTS+1];

	for (int nbcuts=0 ; nbcuts < NB_CUTS+1 ; nbcuts++) {
	ISO_extrems_vars_dr03_emEt_near[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr03_emEt_near_%i", nbcuts), Form("ISO dr03 emEt (near cut %i)", nbcuts), 50, 0, 50);
	ISO_extrems_vars_dr03_emEt_far[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr03_emEt_far_%i", nbcuts), Form("ISO dr03 emEt (far cut %i)", nbcuts), 50, 0, 50);
	ISO_extrems_vars_dr03_hadEt_near[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr03_hadEt_near_%i", nbcuts), Form("ISO dr03 hadEt (near cut %i)", nbcuts), 20, 0, 20);
	ISO_extrems_vars_dr03_hadEt_far[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr03_hadEt_far_%i", nbcuts), Form("ISO dr03 hadEt (far cut %i)", nbcuts), 20, 0, 20);
	ISO_extrems_vars_dr03_hoEt_near[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr03_hoEt_near_%i", nbcuts), Form("ISO dr03 hoEt (near cut %i)", nbcuts), 100, 0, 2);
	ISO_extrems_vars_dr03_hoEt_far[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr03_hoEt_far_%i", nbcuts), Form("ISO dr03 hoEt (far cut %i)", nbcuts), 100, 0, 2);
	ISO_extrems_vars_dr03_njets_near[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr03_njets_near_%i", nbcuts), Form("ISO dr03 njets (near cut %i)", nbcuts), 10, 0, 5);
	ISO_extrems_vars_dr03_njets_far[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr03_njets_far_%i", nbcuts), Form("ISO dr03 njets (far cut %i)", nbcuts), 10, 0, 5);
	ISO_extrems_vars_dr03_ntracks_near[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr03_ntracks_near_%i", nbcuts), Form("ISO dr03 ntracks (near cut %i)", nbcuts), 25, 0, 25);
	ISO_extrems_vars_dr03_ntracks_far[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr03_ntracks_far_%i", nbcuts), Form("ISO dr03 ntracks (far cut %i)", nbcuts), 25, 0, 25);
	ISO_extrems_vars_dr03_sumpt_near[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr03_sumpt_near_%i", nbcuts), Form("ISO dr03 sumpt (near cut %i)", nbcuts), 100, 0, 100);
	ISO_extrems_vars_dr03_sumpt_far[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr03_sumpt_far_%i", nbcuts), Form("ISO dr03 sumpt (far cut %i)", nbcuts), 100, 0, 100);
	}

	// DR = 0.5
	TH1D* ISO_extrems_vars_dr05_emEt_near[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr05_emEt_far[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr05_hadEt_near[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr05_hadEt_far[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr05_hoEt_near[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr05_hoEt_far[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr05_njets_near[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr05_njets_far[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr05_ntracks_near[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr05_ntracks_far[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr05_sumpt_near[NB_CUTS+1];
	TH1D* ISO_extrems_vars_dr05_sumpt_far[NB_CUTS+1];
	for (int nbcuts=0 ; nbcuts < NB_CUTS+1 ; nbcuts++) {
	ISO_extrems_vars_dr05_emEt_near[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr05_emEt_near_%i", nbcuts), Form("ISO dr05 emEt (near cut %i)", nbcuts), 50, 0, 50);
	ISO_extrems_vars_dr05_emEt_far[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr05_emEt_far_%i", nbcuts), Form("ISO dr05 emEt (far cut %i)", nbcuts), 50, 0, 50);
	ISO_extrems_vars_dr05_hadEt_near[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr05_hadEt_near_%i", nbcuts), Form("ISO dr05 hadEt (near cut %i)", nbcuts), 20, 0, 20);
	ISO_extrems_vars_dr05_hadEt_far[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr05_hadEt_far_%i", nbcuts), Form("ISO dr05 hadEt (far cut %i)", nbcuts), 20, 0, 20);
	ISO_extrems_vars_dr05_hoEt_near[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr05_hoEt_near_%i", nbcuts), Form("ISO dr05 hoEt (near cut %i)", nbcuts), 100, 0, 2);
	ISO_extrems_vars_dr05_hoEt_far[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr05_hoEt_far_%i", nbcuts), Form("ISO dr05 hoEt (far cut %i)", nbcuts), 100, 0, 2);
	ISO_extrems_vars_dr05_njets_near[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr05_njets_near_%i", nbcuts), Form("ISO dr05 njets (near cut %i)", nbcuts), 10, 0, 5);
	ISO_extrems_vars_dr05_njets_far[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr05_njets_far_%i", nbcuts), Form("ISO dr05 njets (far cut %i)", nbcuts), 10, 0, 5);
	ISO_extrems_vars_dr05_ntracks_near[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr05_ntracks_near_%i", nbcuts), Form("ISO dr05 ntracks (near cut %i)", nbcuts), 25, 0, 25);
	ISO_extrems_vars_dr05_ntracks_far[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr05_ntracks_far_%i", nbcuts), Form("ISO dr05 ntracks (far cut %i)", nbcuts), 25, 0, 25);
	ISO_extrems_vars_dr05_sumpt_near[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr05_sumpt_near_%i", nbcuts), Form("ISO dr05 sumpt (near cut %i)", nbcuts), 100, 0, 100);
	ISO_extrems_vars_dr05_sumpt_far[nbcuts] = new TH1D(Form("ISO_extrems_vars_dr05_sumpt_far_%i", nbcuts), Form("ISO dr05 sumpt (far cut %i)", nbcuts), 100, 0, 100);
	}
	// ISOLATION PLOTS 
	const unsigned int NB_PLOTS=10;
	TH1D* ISO_dr03_emEt[NB_PLOTS+1]; // DR=0.3
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {	 
		ISO_dr03_emEt[nbplots] = new TH1D(Form("ISO_dr03_emEt_%i", nbplots), Form("ISOLATION dR 03 ECAL-ET %i", nbplots), 50, 0, 50);
	}
	TH1D* ISO_dr03_hadEt[NB_PLOTS+1];
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {	 
		ISO_dr03_hadEt[nbplots]  = new TH1D(Form("ISO_dr03_hadEt_%i", nbplots), Form("ISOLATION dR 03 HCAL-ET %i", nbplots), 20, 0, 20);
	}
	TH1D* ISO_dr03_hoEt[NB_PLOTS+1];
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {	 
		ISO_dr03_hoEt[nbplots] = new TH1D(Form("ISO_dr03_hoEt_%i", nbplots), Form("ISOLATION dR 03 FULL_HCAL-ET %i", nbplots), 100, 0, 2);
	}
	TH1D* ISO_dr03_njets[NB_PLOTS+1]; 
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {	 
		ISO_dr03_njets[nbplots] = new TH1D(Form("ISO_dr03_njets_%i", nbplots), Form("ISOLATION dR 03 NJETS %i", nbplots), 10, 0, 5);
	}
	TH1D* ISO_dr03_ntracks[NB_PLOTS+1];
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {	 
		ISO_dr03_ntracks[nbplots] = new TH1D(Form("ISO_dr03_ntracks_%i", nbplots), Form("ISOLATION dR 03 NTRACKS %i", nbplots), 25, 0, 25);
	}
	TH1D* ISO_dr03_sumpt[NB_PLOTS+1];
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {	 
		ISO_dr03_sumpt[nbplots] = new TH1D(Form("ISO_dr03_sumpt_%i", nbplots), Form("ISOLATION dR 03 SUMPT %i", nbplots), 100, 0, 100);
	}

	TH1D* ISO_dr05_emEt[NB_PLOTS+1]; // DR=0.5
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {	 
		ISO_dr05_emEt[nbplots] = new TH1D(Form("ISO_dr05_emEt_%i", nbplots), Form("ISOLATION dR 05 ECAL-ET %i", nbplots), 50, 0, 50);
	}
	TH1D* ISO_dr05_hadEt[NB_PLOTS+1];
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {	 
		ISO_dr05_hadEt[nbplots]  = new TH1D(Form("ISO_dr05_hadEt_%i", nbplots), Form("ISOLATION dR 05 HCAL-ET %i", nbplots), 20, 0, 20);
	}
	TH1D* ISO_dr05_hoEt[NB_PLOTS+1];
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {	 
		ISO_dr05_hoEt[nbplots] = new TH1D(Form("ISO_dr05_hoEt_%i", nbplots), Form("ISOLATION dR 05 FULL_HCAL-ET %i", nbplots), 100, 0, 2);
	}
	TH1D* ISO_dr05_njets[NB_PLOTS+1]; 
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {	 
		ISO_dr05_njets[nbplots] = new TH1D(Form("ISO_dr05_njets_%i", nbplots), Form("ISOLATION dR 05 NJETS %i", nbplots), 10, 0, 5);
	}
	TH1D* ISO_dr05_ntracks[NB_PLOTS+1];
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {	 
		ISO_dr05_ntracks[nbplots] = new TH1D(Form("ISO_dr05_ntracks_%i", nbplots), Form("ISOLATION dR 05 NTRACKS %i", nbplots), 25, 0, 25);
	}
	TH1D* ISO_dr05_sumpt[NB_PLOTS+1];
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {	 
		ISO_dr05_sumpt[nbplots] = new TH1D(Form("ISO_dr05_sumpt_%i", nbplots), Form("ISOLATION dR 05 SUMPT %i", nbplots), 100, 0, 100);
	}

	// GRAPHS 2D ISOvsDR(mu,gamma)
	const unsigned int NB_2D_PLOTS=2;
	TH2D* ISOdr03emEt_deltar[NB_2D_PLOTS]; // DR = 0.3
	for (int nbplots=0 ; nbplots < NB_2D_PLOTS ; nbplots++) {
                ISOdr03emEt_deltar[nbplots] = new TH2D(Form("ISOdr03emEt_vs_deltar_%i", nbplots), Form("ISO emET (0.3) vs Delta R %i", nbplots), 50, 0, 5, 50, 0, 50);
        }
	TH2D* ISOdr03hadEt_deltar[NB_2D_PLOTS];
	for (int nbplots=0 ; nbplots < NB_2D_PLOTS ; nbplots++) {
                ISOdr03hadEt_deltar[nbplots] = new TH2D(Form("ISOdr03hadEt_vs_deltar_%i", nbplots), Form("ISO hadET (0.3) vs Delta R %i", nbplots), 50, 0, 5, 20, 0, 20);
        }
	TH2D* ISOdr03hoEt_deltar[NB_2D_PLOTS];
	for (int nbplots=0 ; nbplots < NB_2D_PLOTS ; nbplots++) {
                ISOdr03hoEt_deltar[nbplots] = new TH2D(Form("ISOdr03hoEt_vs_deltar_%i", nbplots), Form("ISO hoET (0.3) vs Delta R %i", nbplots), 50, 0, 5, 100, 0, 2);
        }
	TH2D* ISOdr03njets_deltar[NB_2D_PLOTS];
	for (int nbplots=0 ; nbplots < NB_2D_PLOTS ; nbplots++) {
                ISOdr03njets_deltar[nbplots] = new TH2D(Form("ISOdr03njets_vs_deltar_%i", nbplots), Form("ISO njets (0.3) vs Delta R %i", nbplots), 50, 0, 5, 10, 0, 5);
        }
	TH2D* ISOdr03ntracks_deltar[NB_2D_PLOTS];
	for (int nbplots=0 ; nbplots < NB_2D_PLOTS ; nbplots++) {
                ISOdr03ntracks_deltar[nbplots] = new TH2D(Form("ISOdr03ntracks_vs_deltar_%i", nbplots), Form("ISO ntracks (0.3) vs Delta R %i", nbplots), 50, 0, 50, 25, 0, 25);
        }
	TH2D* ISOdr03sumpt_deltar[NB_2D_PLOTS];
	for (int nbplots=0 ; nbplots < NB_2D_PLOTS ; nbplots++) {
                ISOdr03sumpt_deltar[nbplots] = new TH2D(Form("ISOdr03sumpt_vs_deltar_%i", nbplots), Form("ISO sumpt (0.3) vs Delta R %i", nbplots), 50, 0, 5, 100, 0, 100);
        }

	TH2D* dr03_hadEt_sumpt[NB_CUTS+1], *dr03_hadEt_ntracks[NB_CUTS+1], *dr03_sumpt_ntracks[NB_CUTS+1]; // CORRELATIONS
	for (int nbplots=0 ; nbplots < NB_CUTS+1 ; nbplots++) {
		dr03_hadEt_sumpt[nbplots] = new TH2D(Form("03_hadEt_vs_sumpt_%i", nbplots), Form("hadET vs sumpt DR03 cut %i", nbplots), 50, 0, 50, 100, 0, 100);
		dr03_hadEt_ntracks[nbplots] = new TH2D(Form("03_hadEt_vs_ntracks_%i", nbplots), Form("hadET vs ntracks DR03 cut %i", nbplots), 50, 0, 50, 25, 0, 25);
                dr03_sumpt_ntracks[nbplots] = new TH2D(Form("03_sumpt_vs_ntracks_%i", nbplots), Form("sumpt vs ntracks DR03 cut %i", nbplots), 100, 0, 100, 50, 0, 50);
        }

	TH2D* ISOdr05emEt_deltar[NB_2D_PLOTS]; // DR = 0.5
	for (int nbplots=0 ; nbplots < NB_2D_PLOTS ; nbplots++) {
                ISOdr05emEt_deltar[nbplots] = new TH2D(Form("ISOdr05emEt_vs_deltar_%i", nbplots), Form("ISO emET (0.5) vs Delta R %i", nbplots), 50, 0, 5, 50, 0, 50);
        }
	TH2D* ISOdr05hadEt_deltar[NB_2D_PLOTS];
	for (int nbplots=0 ; nbplots < NB_2D_PLOTS ; nbplots++) {
                ISOdr05hadEt_deltar[nbplots] = new TH2D(Form("ISOdr05hadEt_vs_deltar_%i", nbplots), Form("ISO hadET (0.5) vs Delta R %i", nbplots), 50, 0, 5, 20, 0, 20);
        }
	TH2D* ISOdr05hoEt_deltar[NB_2D_PLOTS];
	for (int nbplots=0 ; nbplots < NB_2D_PLOTS ; nbplots++) {
                ISOdr05hoEt_deltar[nbplots] = new TH2D(Form("ISOdr05hoEt_vs_deltar_%i", nbplots), Form("ISO hoET (0.5) vs Delta R %i", nbplots), 50, 0, 5, 100, 0, 2);
        }
	TH2D* ISOdr05njets_deltar[NB_2D_PLOTS];
	for (int nbplots=0 ; nbplots < NB_2D_PLOTS ; nbplots++) {
                ISOdr05njets_deltar[nbplots] = new TH2D(Form("ISOdr05njets_vs_deltar_%i", nbplots), Form("ISO njets (0.5) vs Delta R %i", nbplots), 50, 0, 5, 10, 0, 5);
        }
	TH2D* ISOdr05ntracks_deltar[NB_2D_PLOTS];
	for (int nbplots=0 ; nbplots < NB_2D_PLOTS ; nbplots++) {
                ISOdr05ntracks_deltar[nbplots] = new TH2D(Form("ISOdr05ntracks_vs_deltar_%i", nbplots), Form("ISO ntracks (0.5) vs Delta R %i", nbplots), 50, 0, 5, 25, 0, 25);
        }
	TH2D* ISOdr05sumpt_deltar[NB_2D_PLOTS];
	for (int nbplots=0 ; nbplots < NB_2D_PLOTS ; nbplots++) {
                ISOdr05sumpt_deltar[nbplots] = new TH2D(Form("ISOdr05sumpt_vs_deltar_%i", nbplots), Form("ISO sumpt (0.5) vs Delta R %i", nbplots), 50, 0, 5, 100, 0, 100);
        }

	TH2D* dr05_hadEt_sumpt[NB_CUTS+1], *dr05_hadEt_ntracks[NB_CUTS+1], *dr05_sumpt_ntracks[NB_CUTS+1]; // CORRELATIONS
	for (int nbplots=0 ; nbplots < NB_CUTS+1 ; nbplots++) {
		dr05_hadEt_sumpt[nbplots] = new TH2D(Form("05_hadEt_vs_sumpt_%i", nbplots), Form("hadET vs sumpt DR05 cut %i", nbplots), 50, 0, 50, 100, 0, 100);
		dr05_hadEt_ntracks[nbplots] = new TH2D(Form("05_hadEt_vs_ntracks_%i", nbplots), Form("hadET vs ntracks DR05 cut %i", nbplots), 50, 0, 50, 25, 0, 25);
		dr05_sumpt_ntracks[nbplots] = new TH2D(Form("05_sumpt_vs_ntracks_%i", nbplots), Form("sumpt vs ntracks DR05 cut %i", nbplots), 100, 0, 100, 50, 0, 50);
	}

	// Graphs 2D ISOvsISO
	TH2D* ISO_had_vs_ISO_ntracks_dr03[NB_PLOTS+1];
	TH2D* ISO_had_vs_ISO_ntracks_dr05[NB_PLOTS+1];
	for (int nbplots=0 ; nbplots < NB_PLOTS+1 ; nbplots++) {
                ISO_had_vs_ISO_ntracks_dr03[nbplots] = new TH2D(Form("ISO_had_vs_ISO_ntracks_dr03_%i", nbplots), Form("ISO_had vs ISO_ntracks dr03 %i", nbplots), 50, 0, 5, 100, 0, 20);
                ISO_had_vs_ISO_ntracks_dr05[nbplots] = new TH2D(Form("ISO_had_vs_ISO_ntracks_dr05_%i", nbplots), Form("ISO_had vs ISO_ntracks dr05 %i", nbplots), 50, 0, 5, 100, 0, 20);
        }

// Part 4 : Fonctions boolennes

	if (SIGNAL) { cout << "Running " << NbEvents  << " Signal events " << flush; }
	else { cout << "Running " << NbEvents  << " background events " << flush; }

	if (NEED_CSA07_ID || NEED_ZJETS_VETO) {
		if (NEED_ZJETS_VETO) {cout << "USING ZJETS VETO tool to avoid double counting " << flush;}
		if (NEED_CSA07_ID) {cout << "USING CSA07 ID tool for select correct vars " << flush;}
	}
	else {cout << "No specific configuration needed " << flush;}

//NbEvents=100;

	double max=-1;
	int pourcent =(NbEvents / 100)+1;	
	int mypourcent=0;
	for(unsigned int ievt=0; ievt<NbEvents; ievt++)	{
		// Compteur 
		if(ievt % pourcent == 0) {
			mypourcent++;
			cout << mypourcent << " % ... " << flush;
		}


		bool CUT0=false, CUT1=false, CUT2=false, CUT3=false, CUT4=false, CUT5=false, CUT6=false, CUT7=false, CUT8=false, CUT9=false, CUT10=false; 

		chain->GetEntry(ievt, 1); 

		if (NEED_CSA07_ID) {
			if (event->csa07id() != 62 && event->csa07id() != 63) {
				cerr << "CSA07ID is not 62/63 ( "<< event->csa07id() << ") aborting event " << ievt << endl;
				continue;
			}
		}	

		if(NEED_ZJETS_VETO) {
			bool photons_from_muon =  false;
			for(int MCpart = 0 ; MCpart < mcparticles->GetEntries() ; MCpart++) {
				TRootMCParticle *mcparticle = (TRootMCParticle *) mcparticles->At(MCpart);		
				if(mcparticle->status() == 1 && mcparticle->type() == 22) { // TRUE MCPhotons  only
					if(abs(mcparticle->motherType()) == 13) { // Check if origin is muon
						photons_from_muon=true;
					}
				} 
			}
			if (photons_from_muon) {
				cerr << "SAFE: photon(s) coming from muon, aborting event " << ievt << endl;
                                continue;
			}
		}
		unsigned int valid_muons[2]; valid_muons[0]=110; valid_muons[1]=120; 
		unsigned int valid_gamma=101;

		vector<int> candidates_muons;	
		candidates_muons.clear();

		// STEP 0
		if (muons->GetEntries() > 1 ) { // CHECK MUONS 
			
			// ETA CUT
			for (int nb_muons = 0 ; nb_muons < muons->GetEntries() ; nb_muons++ ) {
				mymuon = (TRootMuon*) muons->At(nb_muons);
				if(fabs(mymuon->Eta()) < 2.5) candidates_muons.push_back(nb_muons);
			}
			if(candidates_muons.size() < 2) {
				cerr << "\tCUT: event " << ievt << " CUT at level I because of bad muons (eta)" << endl;
				CUT1=true; // PLOTS WITHOUT TWO OPPOSITE MUONS
			}

			// CHARGE 
			max=-1;
			for(int nb_muons = 0 ; nb_muons < candidates_muons.size() ; nb_muons++ ) { 	// SELECT FIRST HIGHEST PT MUONS
				mymuon = (TRootMuon*) muons->At(candidates_muons[nb_muons]);
				if (mymuon->Pt() > max) {
					valid_muons[0]=candidates_muons[nb_muons];
                                        max = mymuon->Pt();
				}
			}
			max=-1;
			for (int nb_muons = 0 ; nb_muons < candidates_muons.size() ; nb_muons++ ) { 	// SELECT SECOND HIGHEST PT MUONS

				if(candidates_muons[nb_muons] == valid_muons[0]) continue; // Do not select first one
				mymuon = (TRootMuon*) muons->At(valid_muons[0]);
				mymuonbis = (TRootMuon*) muons->At(candidates_muons[nb_muons]);
				
				if( (mymuon->charge() * mymuonbis.charge()) < 0) { 	
					if (mymuonbis.Pt() > max) {
						valid_muons[1]=candidates_muons[nb_muons];
						max = mymuonbis.Pt();
					}
				}
			}

			if(valid_muons[1]==120 && !CUT1) {
				cerr << "\tCUT: event " << ievt << " CUT at level I because of bad muons (charge)" << endl;
                                CUT1=true; // PLOTS WITHOUT TWO ETA VALID MUONS
				valid_muons[0]==0; valid_muons[1]==1;
			}

			// PT CUT
			if (!CUT1) {
				mymuon = (TRootMuon*) muons->At(valid_muons[0]);
				mymuonbis = (TRootMuon*) muons->At(valid_muons[1]);

				if(mymuon->Pt() < 10 || mymuonbis.Pt() < 10) {
					cerr << "\tCUT: event " << ievt << " CUT at level I because of bad muons (pt)" << endl;
					CUT1=true; // PLOTS WITHOUT TWO ETA VALID MUONS
				}

				TRootParticle* mumu = new TRootParticle();
				*mumu = *((TRootMuon*) muons->At(valid_muons[0])) + *((TRootMuon*) muons->At(valid_muons[1]));
			}

			if(!CUT1) {
				if(mumu->M() < 20) {
					cerr << "\tCUT: event " << ievt << " CUT at level I because of m(mumu)" << endl;
					CUT1=true; // PLOTS WITHOUT TWO ETA VALID MUONS
				} 
			}

		} else { // NOT ENOUGHT MUONS
			cerr << "\tCUT: event " << ievt << " CUT at level I because "<<  muons->GetEntries()  << " muons only" << endl;
                        CUT1=true; // PLOTS WITHOUT TWO MUONS
		}

		if(correctedPhotons->GetEntries() > 0) { // CHECK GAMMA
			max=-1;
			for (int nb_photons=0 ; nb_photons < correctedPhotons->GetEntries() ; nb_photons++) {
				mycorrectedphoton = (TRootPhoton*) correctedPhotons->At(nb_photons);
				if (mycorrectedphoton->Pt() > max && mycorrectedphoton->Pt() > 10 && fabs(mycorrectedphoton->Eta()) < 2.5 ) {
					valid_gamma = nb_photons;
					max = mycorrectedphoton->Pt();
				}
			}

			if (valid_gamma == 101) {
				valid_gamma=0; // ALLOW CREATION of MUMUGAMMA
				if(!CUT1 && !CUT2) cerr << "\tCUT: event " << ievt << " CUT at level II because of bad gamma" << endl; CUT2=true;
			}

			TRootParticle* mumugamma = new TRootParticle();

			if(!CUT1) {
				if(correctedPhotons->GetEntries() > 0) { 
					*mumugamma = *((TRootPhoton*) correctedPhotons->At(valid_gamma)) 
					+ *((TRootMuon*) muons->At(valid_muons[0])) 
					+ *((TRootMuon*) muons->At(valid_muons[1]));
				} 

				// Calcul de deltar
				mycorrectedphoton = (TRootPhoton*) correctedPhotons->At(valid_gamma);
				// deltar1
				mymuon = (TRootMuon*) muons->At(valid_muons[0]);
				deltaeta = fabs(mycorrectedphoton->Eta() - mymuon->Eta());
				deltaphi = fabs(mycorrectedphoton->Phi() - mymuon->Phi()); if(deltaphi > TMath::Pi()) deltaphi = TMath::TwoPi()-deltaphi;
				var_deltar[0] = sqrt(deltaeta*deltaeta+deltaphi*deltaphi);

				// deltar2
				mymuon = (TRootMuon*) muons->At(valid_muons[1]);
				deltaeta = fabs(mycorrectedphoton->Eta() - mymuon->Eta());
				deltaphi = fabs(mycorrectedphoton->Phi() - mymuon->Phi()); if(deltaphi > TMath::Pi()) deltaphi = TMath::TwoPi()-deltaphi;
				var_deltar[1] = sqrt(deltaeta*deltaeta+deltaphi*deltaphi);

				// deltar (inf des deux deltar1 / deltar2)
				deltar = var_deltar[0]<var_deltar[1]?var_deltar[0]:var_deltar[1];

				// Check if the corrected photon satisfy ALPGEN signal preselection CUTs
				mycorrectedphoton = (TRootPhoton*) correctedPhotons->At(valid_gamma); // Choix du plus haut PT

				if( deltar < 0.05 && !CUT2 && !CUT1) {
					cerr << "\tCUT: event " << ievt  << " CUT at level II for correctedPhotons (deltar)" << endl;
					CUT2=true;
				}
			} 
		} else { // NO GAMMA
			if(!CUT1) {
				cerr << "\tCUT: event " << ievt << " CUT at level II because "<<  correctedPhotons->GetEntries()  << " gamma" << endl;
				CUT2=true; // PLOTS WITHOUT GAMMA
			}
		}

		// PLOTS for EXTREMS muons if possible !
		unsigned int deltar_muon[2]; // deltar_muon[0/1] == minimal/maximal deltar muon gamma value 
		TRootMuon *tempomuon, *tempomuon2;

		if(!CUT1 && correctedPhotons->GetEntries() > 0) {
			if (var_deltar[1] > var_deltar[0]) { 
				deltar_muon[1]=valid_muons[1]; deltar_muon[0]=valid_muons[0];
			} else {
				deltar_muon[1]=valid_muons[0]; deltar_muon[0]=valid_muons[1];
			} 

			double mydeltar[2]; // deltar 0 = NEAR, 1 = FAR
			mydeltar[0] = var_deltar[0]<var_deltar[1]?var_deltar[0]:var_deltar[1]; 	// NEAR
			mydeltar[1] = var_deltar[1]<var_deltar[0]?var_deltar[0]:var_deltar[1];	 // FAR

		} else CUT0=true; // ALLOW NO CREATION OF EXTREMS PLOTS

		// PLOTS AT LEVEL 0

		// BEGIN N-1 PLOTS
		THESE_NB_MUONS[0]->Fill(muons->GetEntries());
		if(muons->GetEntries() > 1) {
			if(!CUT1) {
				for(int these_muons ; these_muons < muons->GetEntries() ; these_muons++ ) { 
					mymuon = (TRootMuon*) muons->At(these_muons);		
					THESE_PT_MUON[0]->Fill(mymuon->Pt());
					THESE_ETA_MUON[0]->Fill(mymuon->Eta());
					THESE_MASSE_MUON[0]->Fill(mymuon->M());
				}
			}
		}
		// END N-1 PLOTS

		if(correctedPhotons->GetEntries() > 0 && !CUT1 && !CUT0) {

			mycorrectedphoton = (TRootPhoton*) correctedPhotons->At(valid_gamma); // Choix du plus haut PT
			Reco_mumugamma_invariant_mass[0]->Fill(mumugamma->M());
			ptgamma_valid[0]->Fill(mycorrectedphoton->Pt());
			if(!CUT1 && correctedPhotons->GetEntries() > 0) {
				plots_deltar_near[0]->Fill(mydeltar[0]);
				plots_deltar_far[0]->Fill(mydeltar[1]);
			}
		} 

		if(!CUT1) {
			// FILL ISO PLOTS FOR EACH MUONS
			for(int nbofmuons=0 ; nbofmuons < 2 ; nbofmuons++) {	
				mymuon = (TRootMuon*) muons->At(valid_muons[nbofmuons]);
				// DR=0.3
				ISO_dr03_emEt[0]->Fill(mymuon->isoR03_emEt());
				ISO_dr03_hadEt[0]->Fill(mymuon->isoR03_hadEt());
				ISO_dr03_hoEt[0]->Fill(mymuon->isoR03_hoEt());
				ISO_dr03_njets[0]->Fill(mymuon->isoR03_nJets());
				ISO_dr03_ntracks[0]->Fill(mymuon->isoR03_nTracks());
				ISO_dr03_sumpt[0]->Fill(mymuon->isoR03_sumPt()); 
				// DR=0.5
				ISO_dr05_emEt[0]->Fill(mymuon->isoR05_emEt());
				ISO_dr05_hadEt[0]->Fill(mymuon->isoR05_hadEt());
				ISO_dr05_hoEt[0]->Fill(mymuon->isoR05_hoEt());
				ISO_dr05_njets[0]->Fill(mymuon->isoR05_nJets());
				ISO_dr05_ntracks[0]->Fill(mymuon->isoR05_nTracks());
				ISO_dr05_sumpt[0]->Fill(mymuon->isoR03_sumPt()); 
				// Comparaison DR=0.3 / DR=0.5
				ISO_had_vs_ISO_ntracks_dr03[0]->Fill(mymuon->isoR03_nTracks(), mymuon->isoR03_hadEt());
				ISO_had_vs_ISO_ntracks_dr05[0]->Fill(mymuon->isoR05_nTracks(), mymuon->isoR05_hadEt());
			}
		}

		if (!CUT0) { // IF POSSIBLE DRAW EXTREMS PLOTS with  0 = near && 1 =far

			tempomuon = (TRootMuon*) muons->At(deltar_muon[0]); tempomuon2 = (TRootMuon*) muons->At(deltar_muon[1]);

			// DR=0.3 && DR=0.5 NEAR
			ISO_extrems_vars_dr03_emEt_near[0]->Fill(tempomuon->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_near[0]->Fill(tempomuon->isoR05_emEt());
			ISO_extrems_vars_dr03_hadEt_near[0]->Fill(tempomuon->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_near[0]->Fill(tempomuon->isoR05_hadEt());
			ISO_extrems_vars_dr03_hoEt_near[0]->Fill(tempomuon->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_near[0]->Fill(tempomuon->isoR05_hoEt());
			ISO_extrems_vars_dr03_njets_near[0]->Fill(tempomuon->isoR03_nJets()); ISO_extrems_vars_dr05_njets_near[0]->Fill(tempomuon->isoR05_nJets());
			ISO_extrems_vars_dr03_ntracks_near[0]->Fill(tempomuon->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_near[0]->Fill(tempomuon->isoR05_nTracks());
			ISO_extrems_vars_dr03_sumpt_near[0]->Fill(tempomuon->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_near[0]->Fill(tempomuon->isoR05_sumPt()); 
			// DR=0.3 && DR=0.5 FAR
			ISO_extrems_vars_dr03_emEt_far[0]->Fill(tempomuon2->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_far[0]->Fill(tempomuon2->isoR05_emEt());
			ISO_extrems_vars_dr03_hadEt_far[0]->Fill(tempomuon2->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_far[0]->Fill(tempomuon2->isoR05_hadEt());
			ISO_extrems_vars_dr03_hoEt_far[0]->Fill(tempomuon2->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_far[0]->Fill(tempomuon2->isoR05_hoEt());
			ISO_extrems_vars_dr03_njets_far[0]->Fill(tempomuon2->isoR03_nJets()); ISO_extrems_vars_dr05_njets_far[0]->Fill(tempomuon2->isoR05_nJets());
			ISO_extrems_vars_dr03_ntracks_far[0]->Fill(tempomuon2->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_far[0]->Fill(tempomuon2->isoR05_nTracks());
			ISO_extrems_vars_dr03_sumpt_far[0]->Fill(tempomuon2->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_far[0]->Fill(tempomuon2->isoR05_sumPt()); 
			// CORRELATIONS PLOTS for DELTAR = 03 && 05 with muon far
			// DELTAR 0.3
			dr03_hadEt_sumpt[0]->Fill(tempomuon2->isoR03_sumPt() , tempomuon2->isoR03_hadEt()); 
			dr03_hadEt_ntracks[0]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_hadEt());
			dr03_sumpt_ntracks[0]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_sumPt());
			// DELTAR 0.5
			dr05_hadEt_sumpt[0]->Fill(tempomuon2->isoR05_sumPt() , tempomuon2->isoR05_hadEt()); 
			dr05_hadEt_ntracks[0]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_hadEt());
			dr05_sumpt_ntracks[0]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_sumPt());
			// FILL 2D ISOvsDR PLOTS 
			// For DR = 0.3 && DR = 0.5 NEAR && FAR
			for(int i=0 ; i < 2 ; i++ ) {  
				mymuon = (TRootMuon*) muons->At(deltar_muon[i]); 
				ISOdr03emEt_deltar[0]->Fill(mydeltar[i], mymuon->isoR03_emEt());			
				ISOdr03hadEt_deltar[0]->Fill(mydeltar[i], mymuon->isoR03_hadEt());			
				ISOdr03hoEt_deltar[0]->Fill(mydeltar[i], mymuon->isoR03_hoEt());			
				ISOdr03njets_deltar[0]->Fill(mydeltar[i], mymuon->isoR03_nJets());			
				ISOdr03ntracks_deltar[0]->Fill(mydeltar[i], mymuon->isoR03_nTracks());			
				ISOdr03sumpt_deltar[0]->Fill(mydeltar[i], mymuon->isoR03_sumPt());			
				ISOdr05emEt_deltar[0]->Fill(mydeltar[i], mymuon->isoR05_emEt());			
				ISOdr05hadEt_deltar[0]->Fill(mydeltar[i], mymuon->isoR05_hadEt());			
				ISOdr05hoEt_deltar[0]->Fill(mydeltar[i], mymuon->isoR05_hoEt());			
				ISOdr05njets_deltar[0]->Fill(mydeltar[i], mymuon->isoR05_nJets());			
				ISOdr05ntracks_deltar[0]->Fill(mydeltar[i], mymuon->isoR05_nTracks());			
				ISOdr05sumpt_deltar[0]->Fill(mydeltar[i], mymuon->isoR05_sumPt());			
			}
			// OTHERS
			ptmuon_far[0]->Fill(tempomuon2->Pt());
			if(tempomuon->Pt() > tempomuon2->Pt()) {
				ptmuon_high[0]->Fill(tempomuon->Pt());
			} else {
				ptmuon_high[0]->Fill(tempomuon2->Pt());
			} 
		} 

		// STEP I
		if(CUT1) continue;
		// PLOTS AT LEVEL 1 

		// BEGIN N-1 PLOTS
		if(valid_gamma != 101) {
			mycorrectedphoton = (TRootPhoton*) correctedPhotons->At(valid_gamma);
			THESE_NB_GAMMA[1]->Fill(correctedPhotons->GetEntries());
			THESE_PT_GAMMA[1]->Fill(mycorrectedphoton->Pt());
			THESE_ETA_GAMMA[1]->Fill(mycorrectedphoton->Eta());
			THESE_DR_MUMUGAMMA[1]->Fill(deltar);
		}
		// END N-1 PLOTS


		if(correctedPhotons->GetEntries() > 0  && !CUT1) {
			Reco_mumugamma_invariant_mass[1]->Fill(mumugamma->M());
		} 

		if(!CUT1 && correctedPhotons->GetEntries() > 0) {
			plots_deltar_near[1]->Fill(mydeltar[0]);
			plots_deltar_far[1]->Fill(mydeltar[1]);
		}
		// FILL ISO PLOTS FOR EACH MUONS
		for(int nbofmuons=0 ; nbofmuons < 2 ; nbofmuons++) {	
			mymuon = (TRootMuon*) muons->At(valid_muons[nbofmuons]);
			// DR=0.3
			ISO_dr03_emEt[1]->Fill(mymuon->isoR03_emEt());
			ISO_dr03_hadEt[1]->Fill(mymuon->isoR03_hadEt());
			ISO_dr03_hoEt[1]->Fill(mymuon->isoR03_hoEt());
			ISO_dr03_njets[1]->Fill(mymuon->isoR03_nJets());
			ISO_dr03_ntracks[1]->Fill(mymuon->isoR03_nTracks());
			ISO_dr03_sumpt[1]->Fill(mymuon->isoR03_sumPt()); 
			// DR=0.5
			ISO_dr05_emEt[1]->Fill(mymuon->isoR05_emEt());
			ISO_dr05_hadEt[1]->Fill(mymuon->isoR05_hadEt());
			ISO_dr05_hoEt[1]->Fill(mymuon->isoR05_hoEt());
			ISO_dr05_njets[1]->Fill(mymuon->isoR05_nJets());
			ISO_dr05_ntracks[1]->Fill(mymuon->isoR05_nTracks());
			ISO_dr05_sumpt[1]->Fill(mymuon->isoR03_sumPt()); 
			// Comparaison DR=0.3 / DR=0.5
			ISO_had_vs_ISO_ntracks_dr03[1]->Fill(mymuon->isoR03_nTracks(), mymuon->isoR03_hadEt());
			ISO_had_vs_ISO_ntracks_dr05[1]->Fill(mymuon->isoR05_nTracks(), mymuon->isoR05_hadEt());
		}
		// FILL the EXTREMS PLOTS 0 = near && 1 =far
		if(!CUT0) {
		tempomuon = (TRootMuon*) muons->At(deltar_muon[0]); tempomuon2 = (TRootMuon*) muons->At(deltar_muon[1]);
		// DR=0.3 && DR=0.5 NEAR
		ISO_extrems_vars_dr03_emEt_near[1]->Fill(tempomuon->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_near[1]->Fill(tempomuon->isoR05_emEt());
		ISO_extrems_vars_dr03_hadEt_near[1]->Fill(tempomuon->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_near[1]->Fill(tempomuon->isoR05_hadEt());
		ISO_extrems_vars_dr03_hoEt_near[1]->Fill(tempomuon->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_near[1]->Fill(tempomuon->isoR05_hoEt());
		ISO_extrems_vars_dr03_njets_near[1]->Fill(tempomuon->isoR03_nJets()); ISO_extrems_vars_dr05_njets_near[1]->Fill(tempomuon->isoR05_nJets());
		ISO_extrems_vars_dr03_ntracks_near[1]->Fill(tempomuon->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_near[1]->Fill(tempomuon->isoR05_nTracks());
		ISO_extrems_vars_dr03_sumpt_near[1]->Fill(tempomuon->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_near[1]->Fill(tempomuon->isoR05_sumPt()); 
		// DR=0.3 && DR=0.5 FAR
		ISO_extrems_vars_dr03_emEt_far[1]->Fill(tempomuon2->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_far[1]->Fill(tempomuon2->isoR05_emEt());
		ISO_extrems_vars_dr03_hadEt_far[1]->Fill(tempomuon2->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_far[1]->Fill(tempomuon2->isoR05_hadEt());
		ISO_extrems_vars_dr03_hoEt_far[1]->Fill(tempomuon2->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_far[1]->Fill(tempomuon2->isoR05_hoEt());
		ISO_extrems_vars_dr03_njets_far[1]->Fill(tempomuon2->isoR03_nJets()); ISO_extrems_vars_dr05_njets_far[1]->Fill(tempomuon2->isoR05_nJets());
		ISO_extrems_vars_dr03_ntracks_far[1]->Fill(tempomuon2->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_far[1]->Fill(tempomuon2->isoR05_nTracks());
		ISO_extrems_vars_dr03_sumpt_far[1]->Fill(tempomuon2->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_far[1]->Fill(tempomuon2->isoR05_sumPt()); 
		// CORRELATIONS PLOTS for DELTAR = 03 && 05 with muon far
		// DELTAR 0.3
		dr03_hadEt_sumpt[1]->Fill(tempomuon2->isoR03_sumPt() , tempomuon2->isoR03_hadEt()); 
		dr03_hadEt_ntracks[1]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_hadEt());
		dr03_sumpt_ntracks[1]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_sumPt());
		// DELTAR 0.5
		dr05_hadEt_sumpt[1]->Fill(tempomuon2->isoR05_sumPt() , tempomuon2->isoR05_hadEt()); 
		dr05_hadEt_ntracks[1]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_hadEt());
		dr05_sumpt_ntracks[1]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_sumPt());
		// OTHERS
		ptmuon_far[1]->Fill(tempomuon2->Pt());
		if(tempomuon->Pt() > tempomuon2->Pt()) {
			ptmuon_high[1]->Fill(tempomuon->Pt());
		} else {
			ptmuon_high[1]->Fill(tempomuon2->Pt());
		} 
		ptgamma_valid[1]->Fill(mycorrectedphoton->Pt());
		} 

		// STEP II
		if(CUT2) continue;	
		// PLOTS AT LEVEL 2
		// BEGIN N-1 PLOTS
			mycorrectedphoton = (TRootPhoton*) correctedPhotons->At(valid_gamma);
			THESE_PT_GAMMA[2]->Fill(mycorrectedphoton->Pt());
		// END N-1 PLOTS

		Reco_mumugamma_invariant_mass[2]->Fill(mumugamma->M());
		plots_deltar_near[2]->Fill(mydeltar[0]);
		plots_deltar_far[2]->Fill(mydeltar[1]);
		// FILL ISO PLOTS FOR EACH MUONS
		for(int nbofmuons=0 ; nbofmuons < 2 ; nbofmuons++) {	
			mymuon = (TRootMuon*) muons->At(valid_muons[nbofmuons]);
			// DR=0.3
			ISO_dr03_emEt[2]->Fill(mymuon->isoR03_emEt());
			ISO_dr03_hadEt[2]->Fill(mymuon->isoR03_hadEt());
			ISO_dr03_hoEt[2]->Fill(mymuon->isoR03_hoEt());
			ISO_dr03_njets[2]->Fill(mymuon->isoR03_nJets());
			ISO_dr03_ntracks[2]->Fill(mymuon->isoR03_nTracks());
			ISO_dr03_sumpt[2]->Fill(mymuon->isoR03_sumPt()); 
			// DR=0.5
			ISO_dr05_emEt[2]->Fill(mymuon->isoR05_emEt());
			ISO_dr05_hadEt[2]->Fill(mymuon->isoR05_hadEt());
			ISO_dr05_hoEt[2]->Fill(mymuon->isoR05_hoEt());
			ISO_dr05_njets[2]->Fill(mymuon->isoR05_nJets());
			ISO_dr05_ntracks[2]->Fill(mymuon->isoR05_nTracks());
			ISO_dr05_sumpt[2]->Fill(mymuon->isoR03_sumPt()); 
			// Comparaison DR=0.3 / DR=0.5
			ISO_had_vs_ISO_ntracks_dr03[2]->Fill(mymuon->isoR03_nTracks(), mymuon->isoR03_hadEt());
			ISO_had_vs_ISO_ntracks_dr05[2]->Fill(mymuon->isoR05_nTracks(), mymuon->isoR05_hadEt());
		}
		// FILL the EXTREMS PLOTS 0 = near && 1 =far
		tempomuon = (TRootMuon*) muons->At(deltar_muon[0]); tempomuon2 = (TRootMuon*) muons->At(deltar_muon[1]);
		// DR=0.3 && DR=0.5 NEAR
		ISO_extrems_vars_dr03_emEt_near[2]->Fill(tempomuon->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_near[2]->Fill(tempomuon->isoR05_emEt());
		ISO_extrems_vars_dr03_hadEt_near[2]->Fill(tempomuon->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_near[2]->Fill(tempomuon->isoR05_hadEt());
		ISO_extrems_vars_dr03_hoEt_near[2]->Fill(tempomuon->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_near[2]->Fill(tempomuon->isoR05_hoEt());
		ISO_extrems_vars_dr03_njets_near[2]->Fill(tempomuon->isoR03_nJets()); ISO_extrems_vars_dr05_njets_near[2]->Fill(tempomuon->isoR05_nJets());
		ISO_extrems_vars_dr03_ntracks_near[2]->Fill(tempomuon->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_near[2]->Fill(tempomuon->isoR05_nTracks());
		ISO_extrems_vars_dr03_sumpt_near[2]->Fill(tempomuon->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_near[1]->Fill(tempomuon->isoR05_sumPt()); 
		// DR=0.3 && DR=0.5 FAR
		ISO_extrems_vars_dr03_emEt_far[2]->Fill(tempomuon2->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_far[2]->Fill(tempomuon2->isoR05_emEt());
		ISO_extrems_vars_dr03_hadEt_far[2]->Fill(tempomuon2->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_far[2]->Fill(tempomuon2->isoR05_hadEt());
		ISO_extrems_vars_dr03_hoEt_far[2]->Fill(tempomuon2->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_far[2]->Fill(tempomuon2->isoR05_hoEt());
		ISO_extrems_vars_dr03_njets_far[2]->Fill(tempomuon2->isoR03_nJets()); ISO_extrems_vars_dr05_njets_far[2]->Fill(tempomuon2->isoR05_nJets());
		ISO_extrems_vars_dr03_ntracks_far[2]->Fill(tempomuon2->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_far[2]->Fill(tempomuon2->isoR05_nTracks());
		ISO_extrems_vars_dr03_sumpt_far[2]->Fill(tempomuon2->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_far[2]->Fill(tempomuon2->isoR05_sumPt()); 
		// CORRELATIONS PLOTS for DELTAR = 03 && 05 with muon far
		// DELTAR 0.3
		dr03_hadEt_sumpt[2]->Fill(tempomuon2->isoR03_sumPt() , tempomuon2->isoR03_hadEt()); 
		dr03_hadEt_ntracks[2]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_hadEt());
		dr03_sumpt_ntracks[2]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_sumPt());
		// DELTAR 0.5
		dr05_hadEt_sumpt[2]->Fill(tempomuon2->isoR05_sumPt() , tempomuon2->isoR05_hadEt()); 
		dr05_hadEt_ntracks[2]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_hadEt());
		dr05_sumpt_ntracks[2]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_sumPt());
		// OTHERS
		ptmuon_far[2]->Fill(tempomuon2->Pt());
		if(tempomuon->Pt() > tempomuon2->Pt()) {
			ptmuon_high[2]->Fill(tempomuon->Pt());
		} else {
			ptmuon_high[2]->Fill(tempomuon2->Pt());
		} 
		ptgamma_valid[2]->Fill(mycorrectedphoton->Pt());

		// STEP III
		mycorrectedphoton = (TRootPhoton*) correctedPhotons->At(valid_gamma);
		if (mycorrectedphoton->Pt() < 1) {
			cerr << "\tCUT: event " << ievt  << " CUT at level III for strange event " << endl;
			CUT3=true;
		}
		if (CUT3) continue;
		// PLOTS AT LEVEL 3 
		
		// BEGIN N-1 PLOTS 
			THESE_MASSE_DIMUON[3]->Fill(mumu->M());	
		// END N-1 PLOTS 

		plots_deltar_near[3]->Fill(mydeltar[0]);
		plots_deltar_far[3]->Fill(mydeltar[1]);
		if (!CUT3) {
			Reco_mumugamma_invariant_mass[3]->Fill(mumugamma->M());
			// FILL ISO PLOTS FOR EACH MUONS
			for(int nbofmuons=0 ; nbofmuons < 2 ; nbofmuons++) {	
				mymuon = (TRootMuon*) muons->At(valid_muons[nbofmuons]);
				// DR=0.3
				ISO_dr03_emEt[3]->Fill(mymuon->isoR03_emEt());
				ISO_dr03_hadEt[3]->Fill(mymuon->isoR03_hadEt());
				ISO_dr03_hoEt[3]->Fill(mymuon->isoR03_hoEt());
				ISO_dr03_njets[3]->Fill(mymuon->isoR03_nJets());
				ISO_dr03_ntracks[3]->Fill(mymuon->isoR03_nTracks());
				ISO_dr03_sumpt[3]->Fill(mymuon->isoR03_sumPt()); 
				// DR=0.5
				ISO_dr05_emEt[3]->Fill(mymuon->isoR05_emEt());
				ISO_dr05_hadEt[3]->Fill(mymuon->isoR05_hadEt());
				ISO_dr05_hoEt[3]->Fill(mymuon->isoR05_hoEt());
				ISO_dr05_njets[3]->Fill(mymuon->isoR05_nJets());
				ISO_dr05_ntracks[3]->Fill(mymuon->isoR05_nTracks());
				ISO_dr05_sumpt[3]->Fill(mymuon->isoR03_sumPt()); 
				// Comparaison DR=0.3 / DR=0.5
				ISO_had_vs_ISO_ntracks_dr03[3]->Fill(mymuon->isoR03_nTracks(), mymuon->isoR03_hadEt());
				ISO_had_vs_ISO_ntracks_dr05[3]->Fill(mymuon->isoR05_nTracks(), mymuon->isoR05_hadEt());
			}
			// FILL the EXTREMS PLOTS 0 = near && 1 =far
			tempomuon = (TRootMuon*) muons->At(deltar_muon[0]);
			tempomuon2 = (TRootMuon*) muons->At(deltar_muon[1]);
			if (tempomuon && tempomuon2) {
				// DR=0.3 && DR=0.5 NEAR
				ISO_extrems_vars_dr03_emEt_near[3]->Fill(tempomuon->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_near[3]->Fill(tempomuon->isoR05_emEt());
				ISO_extrems_vars_dr03_hadEt_near[3]->Fill(tempomuon->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_near[3]->Fill(tempomuon->isoR05_hadEt());
				ISO_extrems_vars_dr03_hoEt_near[3]->Fill(tempomuon->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_near[3]->Fill(tempomuon->isoR05_hoEt());
				ISO_extrems_vars_dr03_njets_near[3]->Fill(tempomuon->isoR03_nJets()); ISO_extrems_vars_dr05_njets_near[3]->Fill(tempomuon->isoR05_nJets());
				ISO_extrems_vars_dr03_ntracks_near[3]->Fill(tempomuon->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_near[3]->Fill(tempomuon->isoR05_nTracks());
				ISO_extrems_vars_dr03_sumpt_near[3]->Fill(tempomuon->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_near[3]->Fill(tempomuon->isoR05_sumPt()); 
				// DR=0.3 && DR=0.5 FAR
				ISO_extrems_vars_dr03_emEt_far[3]->Fill(tempomuon2->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_far[3]->Fill(tempomuon2->isoR05_emEt());
				ISO_extrems_vars_dr03_hadEt_far[3]->Fill(tempomuon2->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_far[3]->Fill(tempomuon2->isoR05_hadEt());
				ISO_extrems_vars_dr03_hoEt_far[3]->Fill(tempomuon2->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_far[3]->Fill(tempomuon2->isoR05_hoEt());
				ISO_extrems_vars_dr03_njets_far[3]->Fill(tempomuon2->isoR03_nJets()); ISO_extrems_vars_dr05_njets_far[3]->Fill(tempomuon2->isoR05_nJets());
				ISO_extrems_vars_dr03_ntracks_far[3]->Fill(tempomuon2->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_far[3]->Fill(tempomuon2->isoR05_nTracks());
				ISO_extrems_vars_dr03_sumpt_far[3]->Fill(tempomuon2->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_far[3]->Fill(tempomuon2->isoR05_sumPt()); 
				// CORRELATIONS PLOTS for DELTAR = 03 && 05 with muon far
				// DELTAR 0.3
				dr03_hadEt_sumpt[3]->Fill(tempomuon2->isoR03_sumPt() , tempomuon2->isoR03_hadEt()); 
				dr03_hadEt_ntracks[3]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_hadEt());
				dr03_sumpt_ntracks[3]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_sumPt());
				// DELTAR 0.5
				dr05_hadEt_sumpt[3]->Fill(tempomuon2->isoR05_sumPt() , tempomuon2->isoR05_hadEt()); 
				dr05_hadEt_ntracks[3]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_hadEt());
				dr05_sumpt_ntracks[3]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_sumPt());
				// OTHERS
				ptmuon_far[3]->Fill(tempomuon2->Pt());
				if(tempomuon->Pt() > tempomuon2->Pt()) {
					ptmuon_high[3]->Fill(tempomuon->Pt());
				} else {
					ptmuon_high[3]->Fill(tempomuon2->Pt());
				} 
				ptgamma_valid[3]->Fill(mycorrectedphoton->Pt());
			}
		}
		// STEP IV


		if (mumu->M() < 40 || mumu->M() > 80) { 
			cerr << "\tCUT: event " << ievt  << " CUT at level IV for Drell-Yan " << endl;
			CUT4=true;
		}
		if (CUT4) continue; 
		// PLOTS AT LEVEL 4 

		// BEGIN N-1 PLOTS 
			mycorrectedphoton = (TRootPhoton*) correctedPhotons->At(valid_gamma);
			THESE_PT_GAMMA[4]->Fill(mycorrectedphoton->Pt());	
			THESE_DR_MUMUGAMMA[4]->Fill(deltar);
		// END N-1 PLOTS 

		if (!CUT4) {
			Reco_mumugamma_invariant_mass[4]->Fill(mumugamma->M());
			plots_deltar_near[4]->Fill(mydeltar[0]);
			plots_deltar_far[4]->Fill(mydeltar[1]);
			// FILL ISO PLOTS FOR EACH MUONS
			for(int nbofmuons=0 ; nbofmuons < 2 ; nbofmuons++) {	
				mymuon = (TRootMuon*) muons->At(valid_muons[nbofmuons]);
				// DR=0.3
				ISO_dr03_emEt[4]->Fill(mymuon->isoR03_emEt());
				ISO_dr03_hadEt[4]->Fill(mymuon->isoR03_hadEt());
				ISO_dr03_hoEt[4]->Fill(mymuon->isoR03_hoEt());
				ISO_dr03_njets[4]->Fill(mymuon->isoR03_nJets());
				ISO_dr03_ntracks[4]->Fill(mymuon->isoR03_nTracks());
				ISO_dr03_sumpt[4]->Fill(mymuon->isoR03_sumPt()); 
				// DR=0.5
				ISO_dr05_emEt[4]->Fill(mymuon->isoR05_emEt());
				ISO_dr05_hadEt[4]->Fill(mymuon->isoR05_hadEt());
				ISO_dr05_hoEt[4]->Fill(mymuon->isoR05_hoEt());
				ISO_dr05_njets[4]->Fill(mymuon->isoR05_nJets());
				ISO_dr05_ntracks[4]->Fill(mymuon->isoR05_nTracks());
				ISO_dr05_sumpt[4]->Fill(mymuon->isoR03_sumPt()); 
				// Comparaison DR=0.3 / DR=0.5
				ISO_had_vs_ISO_ntracks_dr03[4]->Fill(mymuon->isoR03_nTracks(), mymuon->isoR03_hadEt());
				ISO_had_vs_ISO_ntracks_dr05[4]->Fill(mymuon->isoR05_nTracks(), mymuon->isoR05_hadEt());
			}
			// FILL the EXTREMS PLOTS 0 = near && 1 =far
			tempomuon = (TRootMuon*) muons->At(deltar_muon[0]); tempomuon2 = (TRootMuon*) muons->At(deltar_muon[1]);
			if (tempomuon && tempomuon2) {
				// DR=0.3 && DR=0.5 NEAR
				ISO_extrems_vars_dr03_emEt_near[4]->Fill(tempomuon->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_near[4]->Fill(tempomuon->isoR05_emEt());
				ISO_extrems_vars_dr03_hadEt_near[4]->Fill(tempomuon->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_near[4]->Fill(tempomuon->isoR05_hadEt());
				ISO_extrems_vars_dr03_hoEt_near[4]->Fill(tempomuon->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_near[4]->Fill(tempomuon->isoR05_hoEt());
				ISO_extrems_vars_dr03_njets_near[4]->Fill(tempomuon->isoR03_nJets()); ISO_extrems_vars_dr05_njets_near[4]->Fill(tempomuon->isoR05_nJets());
				ISO_extrems_vars_dr03_ntracks_near[4]->Fill(tempomuon->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_near[4]->Fill(tempomuon->isoR05_nTracks());
				ISO_extrems_vars_dr03_sumpt_near[4]->Fill(tempomuon->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_near[4]->Fill(tempomuon->isoR05_sumPt()); 
				// DR=0.3 && DR=0.5 FAR
				ISO_extrems_vars_dr03_emEt_far[4]->Fill(tempomuon2->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_far[4]->Fill(tempomuon2->isoR05_emEt());
				ISO_extrems_vars_dr03_hadEt_far[4]->Fill(tempomuon2->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_far[4]->Fill(tempomuon2->isoR05_hadEt());
				ISO_extrems_vars_dr03_hoEt_far[4]->Fill(tempomuon2->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_far[4]->Fill(tempomuon2->isoR05_hoEt());
				ISO_extrems_vars_dr03_njets_far[4]->Fill(tempomuon2->isoR03_nJets()); ISO_extrems_vars_dr05_njets_far[4]->Fill(tempomuon2->isoR05_nJets());
				ISO_extrems_vars_dr03_ntracks_far[4]->Fill(tempomuon2->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_far[4]->Fill(tempomuon2->isoR05_nTracks());
				ISO_extrems_vars_dr03_sumpt_far[4]->Fill(tempomuon2->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_far[4]->Fill(tempomuon2->isoR05_sumPt()); 
				// CORRELATIONS PLOTS for DELTAR = 03 && 05 with muon far
				// DELTAR 0.3
				dr03_hadEt_sumpt[4]->Fill(tempomuon2->isoR03_sumPt() , tempomuon2->isoR03_hadEt()); 
				dr03_hadEt_ntracks[4]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_hadEt());
				dr03_sumpt_ntracks[4]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_sumPt());
				// DELTAR 0.5
				dr05_hadEt_sumpt[4]->Fill(tempomuon2->isoR05_sumPt() , tempomuon2->isoR05_hadEt()); 
				dr05_hadEt_ntracks[4]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_hadEt());
				dr05_sumpt_ntracks[4]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_sumPt());
				// OTHERS
				ptmuon_far[4]->Fill(tempomuon2->Pt());
				if(tempomuon->Pt() > tempomuon2->Pt()) {
					ptmuon_high[4]->Fill(tempomuon->Pt());
				} else {
					ptmuon_high[4]->Fill(tempomuon2->Pt());
				} 
				ptgamma_valid[4]->Fill(mycorrectedphoton->Pt());
			}
		}
		// CUT V		
		mycorrectedphoton = (TRootPhoton*) correctedPhotons->At(valid_gamma);
		if (mycorrectedphoton->Pt() < 12) {
			cerr << "\tCUT: event " << ievt  << " CUT at level V for gamma momentum" << endl;
			CUT5=true;
		} 
		// PLOTS AT LEVEL 5 
		if (CUT5) continue; 
		// BEGIN N-1 PLOTS 
			THESE_MASSE_MUMUGAMMA[5]->Fill(mumugamma->M());	
		// END N-1 PLOTS 

		if (!CUT5) {
			Reco_mumugamma_invariant_mass[5]->Fill(mumugamma->M());
			plots_deltar_near[5]->Fill(mydeltar[0]);
			plots_deltar_far[5]->Fill(mydeltar[1]);
			// FILL ISO PLOTS FOR EACH MUONS
			for(int nbofmuons=0 ; nbofmuons < 2 ; nbofmuons++) {	
				mymuon = (TRootMuon*) muons->At(valid_muons[nbofmuons]);
				// DR=0.3
				ISO_dr03_emEt[5]->Fill(mymuon->isoR03_emEt());
				ISO_dr03_hadEt[5]->Fill(mymuon->isoR03_hadEt());
				ISO_dr03_hoEt[5]->Fill(mymuon->isoR03_hoEt());
				ISO_dr03_njets[5]->Fill(mymuon->isoR03_nJets());
				ISO_dr03_ntracks[5]->Fill(mymuon->isoR03_nTracks());
				ISO_dr03_sumpt[5]->Fill(mymuon->isoR03_sumPt()); 
				// DR=0.5
				ISO_dr05_emEt[5]->Fill(mymuon->isoR05_emEt());
				ISO_dr05_hadEt[5]->Fill(mymuon->isoR05_hadEt());
				ISO_dr05_hoEt[5]->Fill(mymuon->isoR05_hoEt());
				ISO_dr05_njets[5]->Fill(mymuon->isoR05_nJets());
				ISO_dr05_ntracks[5]->Fill(mymuon->isoR05_nTracks());
				ISO_dr05_sumpt[5]->Fill(mymuon->isoR03_sumPt()); 
				// Comparaison DR=0.3 / DR=0.5
				ISO_had_vs_ISO_ntracks_dr03[5]->Fill(mymuon->isoR03_nTracks(), mymuon->isoR03_hadEt());
				ISO_had_vs_ISO_ntracks_dr05[5]->Fill(mymuon->isoR05_nTracks(), mymuon->isoR05_hadEt());
			}
			// FILL the EXTREMS PLOTS 0 = near && 1 =far
			tempomuon = (TRootMuon*) muons->At(deltar_muon[0]);
			tempomuon2 = (TRootMuon*) muons->At(deltar_muon[1]);
			if (tempomuon && tempomuon2) {
				// DR=0.3 && DR=0.5 NEAR
				ISO_extrems_vars_dr03_emEt_near[5]->Fill(tempomuon->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_near[5]->Fill(tempomuon->isoR05_emEt());
				ISO_extrems_vars_dr03_hadEt_near[5]->Fill(tempomuon->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_near[5]->Fill(tempomuon->isoR05_hadEt());
				ISO_extrems_vars_dr03_hoEt_near[5]->Fill(tempomuon->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_near[5]->Fill(tempomuon->isoR05_hoEt());
				ISO_extrems_vars_dr03_njets_near[5]->Fill(tempomuon->isoR03_nJets()); ISO_extrems_vars_dr05_njets_near[5]->Fill(tempomuon->isoR05_nJets());
				ISO_extrems_vars_dr03_ntracks_near[5]->Fill(tempomuon->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_near[5]->Fill(tempomuon->isoR05_nTracks());
				ISO_extrems_vars_dr03_sumpt_near[5]->Fill(tempomuon->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_near[5]->Fill(tempomuon->isoR05_sumPt()); 
				// DR=0.3 && DR=0.5 FAR
				ISO_extrems_vars_dr03_emEt_far[5]->Fill(tempomuon2->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_far[5]->Fill(tempomuon2->isoR05_emEt());
				ISO_extrems_vars_dr03_hadEt_far[5]->Fill(tempomuon2->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_far[5]->Fill(tempomuon2->isoR05_hadEt());
				ISO_extrems_vars_dr03_hoEt_far[5]->Fill(tempomuon2->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_far[5]->Fill(tempomuon2->isoR05_hoEt());
				ISO_extrems_vars_dr03_njets_far[5]->Fill(tempomuon2->isoR03_nJets()); ISO_extrems_vars_dr05_njets_far[5]->Fill(tempomuon2->isoR05_nJets());
				ISO_extrems_vars_dr03_ntracks_far[5]->Fill(tempomuon2->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_far[5]->Fill(tempomuon2->isoR05_nTracks());
				ISO_extrems_vars_dr03_sumpt_far[5]->Fill(tempomuon2->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_far[5]->Fill(tempomuon2->isoR05_sumPt()); 
				// CORRELATIONS PLOTS for DELTAR = 03 && 05 with muon far
				// DELTAR 0.3
				dr03_hadEt_sumpt[5]->Fill(tempomuon2->isoR03_sumPt() , tempomuon2->isoR03_hadEt()); 
				dr03_hadEt_ntracks[5]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_hadEt());
				dr03_sumpt_ntracks[5]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_sumPt());
				// DELTAR 0.5
				dr05_hadEt_sumpt[5]->Fill(tempomuon2->isoR05_sumPt() , tempomuon2->isoR05_hadEt()); 
				dr05_hadEt_ntracks[5]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_hadEt());
				dr05_sumpt_ntracks[5]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_sumPt());
				// OTHERS
				ptmuon_far[5]->Fill(tempomuon2->Pt());
				if(tempomuon->Pt() > tempomuon2->Pt()) {
					ptmuon_high[5]->Fill(tempomuon->Pt());
				} else {
					ptmuon_high[5]->Fill(tempomuon2->Pt());
				} 
				ptgamma_valid[5]->Fill(mycorrectedphoton->Pt());
			}
		}

		// STEP VI && VII
		if (CUT5) continue;
		if (SIGNAL) { // FOR SIGNAL
			if (mumugamma->M() < 87.2 || mumugamma->M() > 95.2) {
				cerr << "\tCUT: event " << ievt  << " CUT at level VI for Z Mass Window " << endl;
				CUT6=true;
			}	
			// PLOTS AT LEVEL 6 
			if (!CUT6) {
				Reco_mumugamma_invariant_mass[6]->Fill(mumugamma->M());
				plots_deltar_near[6]->Fill(mydeltar[0]);
				plots_deltar_far[6]->Fill(mydeltar[1]);
				// FILL ISO PLOTS FOR EACH MUONS
				for(int nbofmuons=0 ; nbofmuons < 2 ; nbofmuons++) {	
					mymuon = (TRootMuon*) muons->At(valid_muons[nbofmuons]);
					// DR=0.3
					ISO_dr03_emEt[6]->Fill(mymuon->isoR03_emEt());
					ISO_dr03_hadEt[6]->Fill(mymuon->isoR03_hadEt());
					ISO_dr03_hoEt[6]->Fill(mymuon->isoR03_hoEt());
					ISO_dr03_njets[6]->Fill(mymuon->isoR03_nJets());
					ISO_dr03_ntracks[6]->Fill(mymuon->isoR03_nTracks());
					ISO_dr03_sumpt[6]->Fill(mymuon->isoR03_sumPt()); 
					// DR=0.5
					ISO_dr05_emEt[6]->Fill(mymuon->isoR05_emEt());
					ISO_dr05_hadEt[6]->Fill(mymuon->isoR05_hadEt());
					ISO_dr05_hoEt[6]->Fill(mymuon->isoR05_hoEt());
					ISO_dr05_njets[6]->Fill(mymuon->isoR05_nJets());
					ISO_dr05_ntracks[6]->Fill(mymuon->isoR05_nTracks());
					ISO_dr05_sumpt[6]->Fill(mymuon->isoR03_sumPt()); 
					// Comparaison DR=0.3 / DR=0.5
					ISO_had_vs_ISO_ntracks_dr03[6]->Fill(mymuon->isoR03_nTracks(), mymuon->isoR03_hadEt());
					ISO_had_vs_ISO_ntracks_dr05[6]->Fill(mymuon->isoR05_nTracks(), mymuon->isoR05_hadEt());
				}
				// FILL the EXTREMS PLOTS 0 = near && 1 =far
				tempomuon = (TRootMuon*) muons->At(deltar_muon[0]);
				tempomuon2 = (TRootMuon*) muons->At(deltar_muon[1]);
				if (tempomuon && tempomuon2) {
				// DR=0.3 && DR=0.5 NEAR
				ISO_extrems_vars_dr03_emEt_near[6]->Fill(tempomuon->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_near[6]->Fill(tempomuon->isoR05_emEt());
				ISO_extrems_vars_dr03_hadEt_near[6]->Fill(tempomuon->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_near[6]->Fill(tempomuon->isoR05_hadEt());
				ISO_extrems_vars_dr03_hoEt_near[6]->Fill(tempomuon->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_near[6]->Fill(tempomuon->isoR05_hoEt());
				ISO_extrems_vars_dr03_njets_near[6]->Fill(tempomuon->isoR03_nJets()); ISO_extrems_vars_dr05_njets_near[6]->Fill(tempomuon->isoR05_nJets());
				ISO_extrems_vars_dr03_ntracks_near[6]->Fill(tempomuon->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_near[6]->Fill(tempomuon->isoR05_nTracks());
				ISO_extrems_vars_dr03_sumpt_near[6]->Fill(tempomuon->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_near[6]->Fill(tempomuon->isoR05_sumPt()); 
				// DR=0.3 && DR=0.5 FAR
				ISO_extrems_vars_dr03_emEt_far[6]->Fill(tempomuon2->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_far[6]->Fill(tempomuon2->isoR05_emEt());
				ISO_extrems_vars_dr03_hadEt_far[6]->Fill(tempomuon2->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_far[6]->Fill(tempomuon2->isoR05_hadEt());
				ISO_extrems_vars_dr03_hoEt_far[6]->Fill(tempomuon2->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_far[6]->Fill(tempomuon2->isoR05_hoEt());
				ISO_extrems_vars_dr03_njets_far[6]->Fill(tempomuon2->isoR03_nJets()); ISO_extrems_vars_dr05_njets_far[6]->Fill(tempomuon2->isoR05_nJets());
				ISO_extrems_vars_dr03_ntracks_far[6]->Fill(tempomuon2->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_far[6]->Fill(tempomuon2->isoR05_nTracks());
				ISO_extrems_vars_dr03_sumpt_far[6]->Fill(tempomuon2->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_far[6]->Fill(tempomuon2->isoR05_sumPt()); 
				// CORRELATIONS PLOTS for DELTAR = 03 && 05 with muon far
				// DELTAR 0.3
				dr03_hadEt_sumpt[6]->Fill(tempomuon2->isoR03_sumPt() , tempomuon2->isoR03_hadEt()); 
				dr03_hadEt_ntracks[6]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_hadEt());
				dr03_sumpt_ntracks[6]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_sumPt());
				// DELTAR 0.5
				dr05_hadEt_sumpt[6]->Fill(tempomuon2->isoR05_sumPt() , tempomuon2->isoR05_hadEt()); 
				dr05_hadEt_ntracks[6]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_hadEt());
				dr05_sumpt_ntracks[6]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_sumPt());
				// OTHERS
				ptmuon_far[6]->Fill(tempomuon2->Pt());
				if(tempomuon->Pt() > tempomuon2->Pt()) {
					ptmuon_high[6]->Fill(tempomuon->Pt());
				} else {
					ptmuon_high[6]->Fill(tempomuon2->Pt());
				} 
				ptgamma_valid[6]->Fill(mycorrectedphoton->Pt());
				}
			}
		} else { // FOR BACKGROUND
			if (mumugamma->M() < 70 || mumugamma->M() > 110) {
				cerr << "\tCUT: event " << ievt  << " CUT at level VII for Z Mass Window " << endl;
				CUT7=true;
			}	
			// PLOTS AT LEVEL 7 
			if (!CUT7) {
				Reco_mumugamma_invariant_mass[7]->Fill(mumugamma->M(), 0.2);
				plots_deltar_near[7]->Fill(mydeltar[0]);
				plots_deltar_far[7]->Fill(mydeltar[1]);
				// FILL ISO PLOTS FOR EACH MUONS
				for(int nbofmuons=0 ; nbofmuons < 2 ; nbofmuons++) {	
					mymuon = (TRootMuon*) muons->At(valid_muons[nbofmuons]);
					// DR=0.3
					ISO_dr03_emEt[7]->Fill(mymuon->isoR03_emEt(), 0.2);
					ISO_dr03_hadEt[7]->Fill(mymuon->isoR03_hadEt(), 0.2);
					ISO_dr03_hoEt[7]->Fill(mymuon->isoR03_hoEt(), 0.2);
					ISO_dr03_njets[7]->Fill(mymuon->isoR03_nJets(), 0.2);
					ISO_dr03_ntracks[7]->Fill(mymuon->isoR03_nTracks(), 0.2);
					ISO_dr03_sumpt[7]->Fill(mymuon->isoR03_sumPt(), 0.2); 
					// DR=0.5
					ISO_dr05_emEt[7]->Fill(mymuon->isoR05_emEt(), 0.2);
					ISO_dr05_hadEt[7]->Fill(mymuon->isoR05_hadEt(), 0.2);
					ISO_dr05_hoEt[7]->Fill(mymuon->isoR05_hoEt(), 0.2);
					ISO_dr05_njets[7]->Fill(mymuon->isoR05_nJets(), 0.2);
					ISO_dr05_ntracks[7]->Fill(mymuon->isoR05_nTracks(), 0.2);
					ISO_dr05_sumpt[7]->Fill(mymuon->isoR03_sumPt(), 0.2); 
					// Comparaison DR=0.3 / DR=0.5
					ISO_had_vs_ISO_ntracks_dr03[7]->Fill(mymuon->isoR03_nTracks(), mymuon->isoR03_hadEt(), 0.2);
					ISO_had_vs_ISO_ntracks_dr05[7]->Fill(mymuon->isoR05_nTracks(), mymuon->isoR05_hadEt(), 0.2);
				}
				// FILL the EXTREMS PLOTS 0 = near && 1 =far
				tempomuon = (TRootMuon*) muons->At(deltar_muon[0]);
				tempomuon2 = (TRootMuon*) muons->At(deltar_muon[1]);
				if (tempomuon && tempomuon2) {
					// DR=0.3 && DR=0.5 NEAR
					ISO_extrems_vars_dr03_emEt_near[7]->Fill(tempomuon->isoR03_emEt(), 0.2); ISO_extrems_vars_dr05_emEt_near[7]->Fill(tempomuon->isoR05_emEt(), 0.2);
					ISO_extrems_vars_dr03_hadEt_near[7]->Fill(tempomuon->isoR03_hadEt(), 0.2);ISO_extrems_vars_dr05_hadEt_near[7]->Fill(tempomuon->isoR05_hadEt(), 0.2);
					ISO_extrems_vars_dr03_hoEt_near[7]->Fill(tempomuon->isoR03_hoEt(), 0.2); ISO_extrems_vars_dr05_hoEt_near[7]->Fill(tempomuon->isoR05_hoEt(), 0.2);
					ISO_extrems_vars_dr03_njets_near[7]->Fill(tempomuon->isoR03_nJets(), 0.2); ISO_extrems_vars_dr05_njets_near[7]->Fill(tempomuon->isoR05_nJets(), 0.2);
					ISO_extrems_vars_dr03_ntracks_near[7]->Fill(tempomuon->isoR03_nTracks(), 0.2); ISO_extrems_vars_dr05_ntracks_near[7]->Fill(tempomuon->isoR05_nTracks(), 0.2);
					ISO_extrems_vars_dr03_sumpt_near[7]->Fill(tempomuon->isoR03_sumPt(), 0.2); ISO_extrems_vars_dr05_sumpt_near[7]->Fill(tempomuon->isoR05_sumPt(), 0.2); 
					// DR=0.3 && DR=0.5 FAR
					ISO_extrems_vars_dr03_emEt_far[7]->Fill(tempomuon2->isoR03_emEt(), 0.2); ISO_extrems_vars_dr05_emEt_far[7]->Fill(tempomuon2->isoR05_emEt(), 0.2);
					ISO_extrems_vars_dr03_hadEt_far[7]->Fill(tempomuon2->isoR03_hadEt(), 0.2);ISO_extrems_vars_dr05_hadEt_far[7]->Fill(tempomuon2->isoR05_hadEt(), 0.2);
					ISO_extrems_vars_dr03_hoEt_far[7]->Fill(tempomuon2->isoR03_hoEt(), 0.2); ISO_extrems_vars_dr05_hoEt_far[7]->Fill(tempomuon2->isoR05_hoEt(), 0.2);
					ISO_extrems_vars_dr03_njets_far[7]->Fill(tempomuon2->isoR03_nJets(), 0.2); ISO_extrems_vars_dr05_njets_far[7]->Fill(tempomuon2->isoR05_nJets(), 0.2);
					ISO_extrems_vars_dr03_ntracks_far[7]->Fill(tempomuon2->isoR03_nTracks(), 0.2); ISO_extrems_vars_dr05_ntracks_far[7]->Fill(tempomuon2->isoR05_nTracks(), 0.2);
					ISO_extrems_vars_dr03_sumpt_far[7]->Fill(tempomuon2->isoR03_sumPt(), 0.2); ISO_extrems_vars_dr05_sumpt_far[7]->Fill(tempomuon2->isoR05_sumPt(), 0.2); 
					// CORRELATIONS PLOTS for DELTAR = 03 && 05 with muon far
					// DELTAR 0.3
					dr03_hadEt_sumpt[7]->Fill(tempomuon2->isoR03_sumPt() , tempomuon2->isoR03_hadEt(), 0.2); 
					dr03_hadEt_ntracks[7]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_hadEt(), 0.2);
					dr03_sumpt_ntracks[7]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_sumPt(), 0.2);
					// DELTAR 0.5
					dr05_hadEt_sumpt[7]->Fill(tempomuon2->isoR05_sumPt() , tempomuon2->isoR05_hadEt(), 0.2); 
					dr05_hadEt_ntracks[7]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_hadEt(), 0.2);
					dr05_sumpt_ntracks[7]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_sumPt(), 0.2);
					// OTHERS
					ptmuon_far[7]->Fill(tempomuon2->Pt(), 0.2);
					if(tempomuon->Pt() > tempomuon2->Pt()) {
						ptmuon_high[7]->Fill(tempomuon->Pt(), 0.2);
					} else {
						ptmuon_high[7]->Fill(tempomuon2->Pt(), 0.2);
					} 
					ptgamma_valid[7]->Fill(mycorrectedphoton->Pt(), 0.2);
				}
			}
		}
		// BEGIN N-1 PLOTS	
			if(SIGNAL) {
				THESE_ISOEMET_DR03[6]->Fill(tempomuon2->isoR03_emEt());
			} else {
				THESE_ISOEMET_DR03[7]->Fill(tempomuon2->isoR03_emEt(), 0.2);
			}
		// END N-1 PLOTS	

		if(SIGNAL) float myscale = 1 ; else float myscale = 0.2 ; // ALLOW scaling for background and NOT for signal.

		// ADDITIONAL STEP : CUTTING SURVIVING EVENTS CUT 8 (BB2MUMU Killer I)
		// STEP VIII
		if(CUT6 || CUT7) continue;
		//DEFINE CUT	
		if(tempomuon2->isoR03_emEt() > 1) {
			cerr << "\tCUT: event " << ievt  << " CUT at level VIII for large emEt " << endl;
			CUT8=true;
		}
		if(CUT8) continue;
		if(!CUT8) { // PLOTS RESULTINGS GRAPHS
			Reco_mumugamma_invariant_mass[8]->Fill(mumugamma->M(), myscale);
			plots_deltar_near[8]->Fill(mydeltar[0]);
			plots_deltar_far[8]->Fill(mydeltar[1]);
			// FILL ISO PLOTS FOR EACH MUONS
			for(int nbofmuons=0 ; nbofmuons < 2 ; nbofmuons++) {	
				mymuon = (TRootMuon*) muons->At(valid_muons[nbofmuons]);
				// DR=0.3
				ISO_dr03_emEt[8]->Fill(mymuon->isoR03_emEt(), myscale);
				ISO_dr03_hadEt[8]->Fill(mymuon->isoR03_hadEt(), myscale);
				ISO_dr03_hoEt[8]->Fill(mymuon->isoR03_hoEt(), myscale);
				ISO_dr03_njets[8]->Fill(mymuon->isoR03_nJets(), myscale);
				ISO_dr03_ntracks[8]->Fill(mymuon->isoR03_nTracks(), myscale);
				ISO_dr03_sumpt[8]->Fill(mymuon->isoR03_sumPt(), myscale); 
				// DR=0.5
				ISO_dr05_emEt[8]->Fill(mymuon->isoR05_emEt(), myscale);
				ISO_dr05_hadEt[8]->Fill(mymuon->isoR05_hadEt(), myscale);
				ISO_dr05_hoEt[8]->Fill(mymuon->isoR05_hoEt(), myscale);
				ISO_dr05_njets[8]->Fill(mymuon->isoR05_nJets(), myscale);
				ISO_dr05_ntracks[8]->Fill(mymuon->isoR05_nTracks(), myscale);
				ISO_dr05_sumpt[8]->Fill(mymuon->isoR03_sumPt(), myscale); 
				// Comparaison DR=0.3 / DR=0.5
				ISO_had_vs_ISO_ntracks_dr03[8]->Fill(mymuon->isoR03_nTracks(), mymuon->isoR03_hadEt(), myscale);
				ISO_had_vs_ISO_ntracks_dr05[8]->Fill(mymuon->isoR05_nTracks(), mymuon->isoR05_hadEt(), myscale);
			}
			// FILL the EXTREMS PLOTS 0 = near && 1 =far
			tempomuon = (TRootMuon*) muons->At(deltar_muon[0]);
			tempomuon2 = (TRootMuon*) muons->At(deltar_muon[1]);

			if (tempomuon && tempomuon2) {
				// DR=0.3 && DR=0.5 NEAR
				ISO_extrems_vars_dr03_emEt_near[8]->Fill(tempomuon->isoR03_emEt(), myscale); ISO_extrems_vars_dr05_emEt_near[8]->Fill(tempomuon->isoR05_emEt(), myscale);
				ISO_extrems_vars_dr03_hadEt_near[8]->Fill(tempomuon->isoR03_hadEt(), myscale);ISO_extrems_vars_dr05_hadEt_near[8]->Fill(tempomuon->isoR05_hadEt(), myscale);
				ISO_extrems_vars_dr03_hoEt_near[8]->Fill(tempomuon->isoR03_hoEt(), myscale); ISO_extrems_vars_dr05_hoEt_near[8]->Fill(tempomuon->isoR05_hoEt(), myscale);
				ISO_extrems_vars_dr03_njets_near[8]->Fill(tempomuon->isoR03_nJets(), myscale); ISO_extrems_vars_dr05_njets_near[8]->Fill(tempomuon->isoR05_nJets(), myscale);
				ISO_extrems_vars_dr03_ntracks_near[8]->Fill(tempomuon->isoR03_nTracks(), myscale); ISO_extrems_vars_dr05_ntracks_near[8]->Fill(tempomuon->isoR05_nTracks(), myscale);
				ISO_extrems_vars_dr03_sumpt_near[8]->Fill(tempomuon->isoR03_sumPt(), myscale); ISO_extrems_vars_dr05_sumpt_near[8]->Fill(tempomuon->isoR05_sumPt(), myscale); 
				// DR=0.3 && DR=0.5 FAR
				ISO_extrems_vars_dr03_emEt_far[8]->Fill(tempomuon2->isoR03_emEt(), myscale); ISO_extrems_vars_dr05_emEt_far[8]->Fill(tempomuon2->isoR05_emEt(), myscale);
				ISO_extrems_vars_dr03_hadEt_far[8]->Fill(tempomuon2->isoR03_hadEt(), myscale);ISO_extrems_vars_dr05_hadEt_far[8]->Fill(tempomuon2->isoR05_hadEt(), myscale);
				ISO_extrems_vars_dr03_hoEt_far[8]->Fill(tempomuon2->isoR03_hoEt(), myscale); ISO_extrems_vars_dr05_hoEt_far[8]->Fill(tempomuon2->isoR05_hoEt(), myscale);
				ISO_extrems_vars_dr03_njets_far[8]->Fill(tempomuon2->isoR03_nJets(), myscale); ISO_extrems_vars_dr05_njets_far[8]->Fill(tempomuon2->isoR05_nJets(), myscale);
				ISO_extrems_vars_dr03_ntracks_far[8]->Fill(tempomuon2->isoR03_nTracks(), myscale); ISO_extrems_vars_dr05_ntracks_far[8]->Fill(tempomuon2->isoR05_nTracks(), myscale);
				ISO_extrems_vars_dr03_sumpt_far[8]->Fill(tempomuon2->isoR03_sumPt(), myscale); ISO_extrems_vars_dr05_sumpt_far[8]->Fill(tempomuon2->isoR05_sumPt(), myscale); 
				// CORRELATIONS PLOTS for DELTAR = 03 && 05 with muon far
				// DELTAR 0.3
				dr03_hadEt_sumpt[8]->Fill(tempomuon2->isoR03_sumPt() , tempomuon2->isoR03_hadEt(), myscale); 
				dr03_hadEt_ntracks[8]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_hadEt(), myscale);
				dr03_sumpt_ntracks[8]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_sumPt(), myscale);
				// DELTAR 0.5
				dr05_hadEt_sumpt[8]->Fill(tempomuon2->isoR05_sumPt() , tempomuon2->isoR05_hadEt(), myscale); 
				dr05_hadEt_ntracks[8]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_hadEt(), myscale);
				dr05_sumpt_ntracks[8]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_sumPt(), myscale);
				// OTHERS
				ptmuon_far[8]->Fill(tempomuon2->Pt(), myscale);
				if(tempomuon->Pt() > tempomuon2->Pt()) {
					ptmuon_high[8]->Fill(tempomuon->Pt(), myscale);
				} else {
					ptmuon_high[8]->Fill(tempomuon2->Pt(), myscale);
				} 
				ptgamma_valid[8]->Fill(mycorrectedphoton->Pt(), myscale);
			}
		
		}

		// BEGIN N-1 CUT
			THESE_PT_MUON_FAR[8]->Fill(tempomuon2->Pt());
		// END N-1 CUT

		// CUT IX : OTHER CUT

		// ADDITIONAL STEP : CUTTING SURVIVING EVENTS CUT 9 (BB2MUMU Killer II)
		//DEFINE CUT	
		if(tempomuon2->Pt() < 30) {
			cerr << "\tCUT: event " << ievt  << " CUT at level IX for keeping only Muon far with high PT" << endl;
			CUT9=true;
		}

		if(CUT9) continue;
		if(!CUT9) { // PLOTS RESULTINGS GRAPHS
			Reco_mumugamma_invariant_mass[9]->Fill(mumugamma->M(), myscale);
			plots_deltar_near[9]->Fill(mydeltar[0]);
			plots_deltar_far[9]->Fill(mydeltar[1]);
			// FILL ISO PLOTS FOR EACH MUONS
			for(int nbofmuons=0 ; nbofmuons < 2 ; nbofmuons++) {	
				mymuon = (TRootMuon*) muons->At(valid_muons[nbofmuons]);
				// DR=0.3
				ISO_dr03_emEt[9]->Fill(mymuon->isoR03_emEt(), myscale);
				ISO_dr03_hadEt[9]->Fill(mymuon->isoR03_hadEt(), myscale);
				ISO_dr03_hoEt[9]->Fill(mymuon->isoR03_hoEt(), myscale);
				ISO_dr03_njets[9]->Fill(mymuon->isoR03_nJets(), myscale);
				ISO_dr03_ntracks[9]->Fill(mymuon->isoR03_nTracks(), myscale);
				ISO_dr03_sumpt[9]->Fill(mymuon->isoR03_sumPt(), myscale); 
				// DR=0.5
				ISO_dr05_emEt[9]->Fill(mymuon->isoR05_emEt(), myscale);
				ISO_dr05_hadEt[9]->Fill(mymuon->isoR05_hadEt(), myscale);
				ISO_dr05_hoEt[9]->Fill(mymuon->isoR05_hoEt(), myscale);
				ISO_dr05_njets[9]->Fill(mymuon->isoR05_nJets(), myscale);
				ISO_dr05_ntracks[9]->Fill(mymuon->isoR05_nTracks(), myscale);
				ISO_dr05_sumpt[9]->Fill(mymuon->isoR03_sumPt(), myscale); 
				// Comparaison DR=0.3 / DR=0.5
				ISO_had_vs_ISO_ntracks_dr03[9]->Fill(mymuon->isoR03_nTracks(), mymuon->isoR03_hadEt(), myscale);
				ISO_had_vs_ISO_ntracks_dr05[9]->Fill(mymuon->isoR05_nTracks(), mymuon->isoR05_hadEt(), myscale);
			}
			// FILL the EXTREMS PLOTS 0 = near && 1 =far
			tempomuon = (TRootMuon*) muons->At(deltar_muon[0]);
			tempomuon2 = (TRootMuon*) muons->At(deltar_muon[1]);

			if (tempomuon && tempomuon2) {
				// DR=0.3 && DR=0.5 NEAR
				ISO_extrems_vars_dr03_emEt_near[9]->Fill(tempomuon->isoR03_emEt(), myscale); ISO_extrems_vars_dr05_emEt_near[9]->Fill(tempomuon->isoR05_emEt(), myscale);
				ISO_extrems_vars_dr03_hadEt_near[9]->Fill(tempomuon->isoR03_hadEt(), myscale);ISO_extrems_vars_dr05_hadEt_near[9]->Fill(tempomuon->isoR05_hadEt(), myscale);
				ISO_extrems_vars_dr03_hoEt_near[9]->Fill(tempomuon->isoR03_hoEt(), myscale); ISO_extrems_vars_dr05_hoEt_near[9]->Fill(tempomuon->isoR05_hoEt(), myscale);
				ISO_extrems_vars_dr03_njets_near[9]->Fill(tempomuon->isoR03_nJets(), myscale); ISO_extrems_vars_dr05_njets_near[9]->Fill(tempomuon->isoR05_nJets(), myscale);
				ISO_extrems_vars_dr03_ntracks_near[9]->Fill(tempomuon->isoR03_nTracks(), myscale); ISO_extrems_vars_dr05_ntracks_near[9]->Fill(tempomuon->isoR05_nTracks(), myscale);
				ISO_extrems_vars_dr03_sumpt_near[9]->Fill(tempomuon->isoR03_sumPt(), myscale); ISO_extrems_vars_dr05_sumpt_near[9]->Fill(tempomuon->isoR05_sumPt(), myscale); 
				// DR=0.3 && DR=0.5 FAR
				ISO_extrems_vars_dr03_emEt_far[9]->Fill(tempomuon2->isoR03_emEt(), myscale); ISO_extrems_vars_dr05_emEt_far[9]->Fill(tempomuon2->isoR05_emEt(), myscale);
				ISO_extrems_vars_dr03_hadEt_far[9]->Fill(tempomuon2->isoR03_hadEt(), myscale);ISO_extrems_vars_dr05_hadEt_far[9]->Fill(tempomuon2->isoR05_hadEt(), myscale);
				ISO_extrems_vars_dr03_hoEt_far[9]->Fill(tempomuon2->isoR03_hoEt(), myscale); ISO_extrems_vars_dr05_hoEt_far[9]->Fill(tempomuon2->isoR05_hoEt(), myscale);
				ISO_extrems_vars_dr03_njets_far[9]->Fill(tempomuon2->isoR03_nJets(), myscale); ISO_extrems_vars_dr05_njets_far[9]->Fill(tempomuon2->isoR05_nJets(), myscale);
				ISO_extrems_vars_dr03_ntracks_far[9]->Fill(tempomuon2->isoR03_nTracks(), myscale); ISO_extrems_vars_dr05_ntracks_far[9]->Fill(tempomuon2->isoR05_nTracks(), myscale);
				ISO_extrems_vars_dr03_sumpt_far[9]->Fill(tempomuon2->isoR03_sumPt(), myscale); ISO_extrems_vars_dr05_sumpt_far[9]->Fill(tempomuon2->isoR05_sumPt(), myscale); 
				// CORRELATIONS PLOTS for DELTAR = 03 && 05 with muon far
				// DELTAR 0.3
				dr03_hadEt_sumpt[9]->Fill(tempomuon2->isoR03_sumPt() , tempomuon2->isoR03_hadEt(), myscale); 
				dr03_hadEt_ntracks[9]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_hadEt(), myscale);
				dr03_sumpt_ntracks[9]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_sumPt(), myscale);
				// DELTAR 0.5
				dr05_hadEt_sumpt[9]->Fill(tempomuon2->isoR05_sumPt() , tempomuon2->isoR05_hadEt(), myscale); 
				dr05_hadEt_ntracks[9]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_hadEt(), myscale);
				dr05_sumpt_ntracks[9]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_sumPt(), myscale);
				// OTHERS
				ptmuon_far[9]->Fill(tempomuon2->Pt(), myscale);
				if(tempomuon->Pt() > tempomuon2->Pt()) {
					ptmuon_high[9]->Fill(tempomuon->Pt(), myscale);
				} else {
					ptmuon_high[9]->Fill(tempomuon2->Pt(), myscale);
				} 
				ptgamma_valid[9]->Fill(mycorrectedphoton->Pt(), myscale);
			}
		
		}
		// IF SUCCES IN ALL CUTS

		// STEP X
		mycorrectedphoton = (TRootPhoton*) correctedPhotons->At(valid_gamma);
		if (deltar > 0.8) {
			cerr << "\tCUT: event " << ievt  << " CUT at level X for gamma/mu correlation" << endl;
			CUT10=true;
		} 
		// PLOTS AT LEVEL 10
		if (CUT10) continue; 
		// BEGIN N-1 PLOTS 
			THESE_MASSE_MUMUGAMMA[10]->Fill(mumugamma->M());	
		// END N-1 PLOTS 

		if (!CUT10) {
			Reco_mumugamma_invariant_mass[10]->Fill(mumugamma->M());
			plots_deltar_near[10]->Fill(mydeltar[0]);
			plots_deltar_far[10]->Fill(mydeltar[1]);
			// FILL ISO PLOTS FOR EACH MUONS
			for(int nbofmuons=0 ; nbofmuons < 2 ; nbofmuons++) {	
				mymuon = (TRootMuon*) muons->At(valid_muons[nbofmuons]);
				// DR=0.3
				ISO_dr03_emEt[10]->Fill(mymuon->isoR03_emEt());
				ISO_dr03_hadEt[10]->Fill(mymuon->isoR03_hadEt());
				ISO_dr03_hoEt[10]->Fill(mymuon->isoR03_hoEt());
				ISO_dr03_njets[10]->Fill(mymuon->isoR03_nJets());
				ISO_dr03_ntracks[10]->Fill(mymuon->isoR03_nTracks());
				ISO_dr03_sumpt[10]->Fill(mymuon->isoR03_sumPt()); 
				// DR=0.5
				ISO_dr05_emEt[10]->Fill(mymuon->isoR05_emEt());
				ISO_dr05_hadEt[10]->Fill(mymuon->isoR05_hadEt());
				ISO_dr05_hoEt[10]->Fill(mymuon->isoR05_hoEt());
				ISO_dr05_njets[10]->Fill(mymuon->isoR05_nJets());
				ISO_dr05_ntracks[10]->Fill(mymuon->isoR05_nTracks());
				ISO_dr05_sumpt[10]->Fill(mymuon->isoR03_sumPt()); 
				// Comparaison DR=0.3 / DR=0.5
				ISO_had_vs_ISO_ntracks_dr03[10]->Fill(mymuon->isoR03_nTracks(), mymuon->isoR03_hadEt());
				ISO_had_vs_ISO_ntracks_dr05[10]->Fill(mymuon->isoR05_nTracks(), mymuon->isoR05_hadEt());
			}
			// FILL the EXTREMS PLOTS 0 = near && 1 =far
			tempomuon = (TRootMuon*) muons->At(deltar_muon[0]);
			tempomuon2 = (TRootMuon*) muons->At(deltar_muon[1]);
			if (tempomuon && tempomuon2) {
				// DR=0.3 && DR=0.5 NEAR
				ISO_extrems_vars_dr03_emEt_near[10]->Fill(tempomuon->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_near[10]->Fill(tempomuon->isoR05_emEt());
				ISO_extrems_vars_dr03_hadEt_near[10]->Fill(tempomuon->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_near[10]->Fill(tempomuon->isoR05_hadEt());
				ISO_extrems_vars_dr03_hoEt_near[10]->Fill(tempomuon->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_near[10]->Fill(tempomuon->isoR05_hoEt());
				ISO_extrems_vars_dr03_njets_near[10]->Fill(tempomuon->isoR03_nJets()); ISO_extrems_vars_dr05_njets_near[10]->Fill(tempomuon->isoR05_nJets());
				ISO_extrems_vars_dr03_ntracks_near[10]->Fill(tempomuon->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_near[10]->Fill(tempomuon->isoR05_nTracks());
				ISO_extrems_vars_dr03_sumpt_near[10]->Fill(tempomuon->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_near[10]->Fill(tempomuon->isoR05_sumPt()); 
				// DR=0.3 && DR=0.5 FAR
				ISO_extrems_vars_dr03_emEt_far[10]->Fill(tempomuon2->isoR03_emEt()); ISO_extrems_vars_dr05_emEt_far[10]->Fill(tempomuon2->isoR05_emEt());
				ISO_extrems_vars_dr03_hadEt_far[10]->Fill(tempomuon2->isoR03_hadEt());ISO_extrems_vars_dr05_hadEt_far[10]->Fill(tempomuon2->isoR05_hadEt());
				ISO_extrems_vars_dr03_hoEt_far[10]->Fill(tempomuon2->isoR03_hoEt()); ISO_extrems_vars_dr05_hoEt_far[10]->Fill(tempomuon2->isoR05_hoEt());
				ISO_extrems_vars_dr03_njets_far[10]->Fill(tempomuon2->isoR03_nJets()); ISO_extrems_vars_dr05_njets_far[10]->Fill(tempomuon2->isoR05_nJets());
				ISO_extrems_vars_dr03_ntracks_far[10]->Fill(tempomuon2->isoR03_nTracks()); ISO_extrems_vars_dr05_ntracks_far[10]->Fill(tempomuon2->isoR05_nTracks());
				ISO_extrems_vars_dr03_sumpt_far[10]->Fill(tempomuon2->isoR03_sumPt()); ISO_extrems_vars_dr05_sumpt_far[10]->Fill(tempomuon2->isoR05_sumPt()); 
				// CORRELATIONS PLOTS for DELTAR = 03 && 05 with muon far
				// DELTAR 0.3
				dr03_hadEt_sumpt[10]->Fill(tempomuon2->isoR03_sumPt() , tempomuon2->isoR03_hadEt()); 
				dr03_hadEt_ntracks[10]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_hadEt());
				dr03_sumpt_ntracks[10]->Fill(tempomuon2->isoR03_nTracks() , tempomuon2->isoR03_sumPt());
				// DELTAR 0.5
				dr05_hadEt_sumpt[10]->Fill(tempomuon2->isoR05_sumPt() , tempomuon2->isoR05_hadEt()); 
				dr05_hadEt_ntracks[10]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_hadEt());
				dr05_sumpt_ntracks[10]->Fill(tempomuon2->isoR05_nTracks() , tempomuon2->isoR05_sumPt());
				// OTHERS
				ptmuon_far[10]->Fill(tempomuon2->Pt());
				if(tempomuon->Pt() > tempomuon2->Pt()) {
					ptmuon_high[10]->Fill(tempomuon->Pt());
				} else {
					ptmuon_high[10]->Fill(tempomuon2->Pt());
				} 
				ptgamma_valid[10]->Fill(mycorrectedphoton->Pt());
			}
		}
 
		cerr << "OK: Surviving veto event: "<< ievt << endl;
		// PLOTS AFTER ALL CUTS  
		Final_Reco_mumugamma_invariant_mass->Fill(mumugamma->M(), myscale);

		// FILL ISO PLOTS FOR EACH MUONS
		for(int nbofmuons=0 ; nbofmuons < 2 ; nbofmuons++) {	
			mymuon = (TRootMuon*) muons->At(valid_muons[nbofmuons]);
			// DR=0.3
			ISO_dr03_emEt[10]->Fill(mymuon->isoR03_emEt(), myscale);
			ISO_dr03_hadEt[10]->Fill(mymuon->isoR03_hadEt(), myscale);
			ISO_dr03_hoEt[10]->Fill(mymuon->isoR03_hoEt(), myscale);
			ISO_dr03_njets[10]->Fill(mymuon->isoR03_nJets(), myscale);
			ISO_dr03_ntracks[10]->Fill(mymuon->isoR03_nTracks(), myscale);
			ISO_dr03_sumpt[10]->Fill(mymuon->isoR03_sumPt(), myscale); 
			// DR=0.5
			ISO_dr05_emEt[10]->Fill(mymuon->isoR05_emEt(), myscale);
			ISO_dr05_hadEt[10]->Fill(mymuon->isoR05_hadEt(), myscale);
			ISO_dr05_hoEt[10]->Fill(mymuon->isoR05_hoEt(), myscale);
			ISO_dr05_njets[10]->Fill(mymuon->isoR05_nJets(), myscale);
			ISO_dr05_ntracks[10]->Fill(mymuon->isoR05_nTracks(), myscale);
			ISO_dr05_sumpt[10]->Fill(mymuon->isoR03_sumPt(), myscale); 
			// Comparaison DR=0.3 / DR=0.5
			ISO_had_vs_ISO_ntracks_dr03[10]->Fill(mymuon->isoR03_nTracks(), mymuon->isoR03_hadEt(), myscale);
			ISO_had_vs_ISO_ntracks_dr05[10]->Fill(mymuon->isoR05_nTracks(), mymuon->isoR05_hadEt(), myscale);
		}
		for(int i=0 ; i < 2 ; i++ ) {  
			mymuon = (TRootMuon*) muons->At(deltar_muon[i]); 
			ISOdr03emEt_deltar[1]->Fill(mydeltar[i], mymuon->isoR03_emEt(), myscale);			
			ISOdr03hadEt_deltar[1]->Fill(mydeltar[i], mymuon->isoR03_hadEt(), myscale);			
			ISOdr03hoEt_deltar[1]->Fill(mydeltar[i], mymuon->isoR03_hoEt(), myscale);			
			ISOdr03njets_deltar[1]->Fill(mydeltar[i], mymuon->isoR03_nJets(), myscale);			
			ISOdr03ntracks_deltar[1]->Fill(mydeltar[i], mymuon->isoR03_nTracks(), myscale);			
			ISOdr03sumpt_deltar[1]->Fill(mydeltar[i], mymuon->isoR03_sumPt(), myscale);			
			ISOdr05emEt_deltar[1]->Fill(mydeltar[i], mymuon->isoR05_emEt(), myscale);			
			ISOdr05hadEt_deltar[1]->Fill(mydeltar[i], mymuon->isoR05_hadEt(), myscale);			
			ISOdr05hoEt_deltar[1]->Fill(mydeltar[i], mymuon->isoR05_hoEt(), myscale);			
			ISOdr05njets_deltar[1]->Fill(mydeltar[i], mymuon->isoR05_nJets(), myscale);			
			ISOdr05ntracks_deltar[1]->Fill(mydeltar[i], mymuon->isoR05_nTracks(), myscale);			
			ISOdr05sumpt_deltar[1]->Fill(mydeltar[i], mymuon->isoR05_sumPt(), myscale);			
		}
		
	} // fin boucle sur evts

	cout << "end" << endl;
	cout << "WARNING: NO PLOTS DRAWN, USE Plots.C to create them !" << endl;

	// Closing rootfile
	outputfile->Write();
	outputfile->Close();	
}

