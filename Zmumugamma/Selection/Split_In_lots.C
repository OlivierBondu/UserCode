{
#pragma optimize 0

	TFile *input = new TFile("miniTree_FSR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_ALL.root");
	TTree *wholetree = (TTree*)input->Get("miniTree");

	wholetree->SetBranchStatus("*",1);

	TFile *newfile = new TFile("miniminiTree_36.15pb-1_TEMP.root","recreate");
	newfile->cd();

	TTree *newtree = wholetree->CopyTree("isAfterCut8");
	newfile->cd();
 //newtree->Write();
	newfile->Write("Tree");
	newfile->Close();

	delete wholetree;
	input->Close();

// use the first output as input
	int nEvent = 219;
	int nInit = 0;

	TFile *newinput = new TFile("miniminiTree_36.15pb-1_TEMP.root");
	TTree *newwholetree = (TTree*)newinput->Get("miniTree");
	for(int ilot = 0; ilot < 34; ilot++){
		newwholetree->SetBranchStatus("*",1);
	
		nInit = ilot * 219;
/*
		if( ilot != 0){
		} else {
		}
*/
		nEvent = (ilot + 1 ) * 219;
	
		stringstream ss[2];
		string snInit, snEvent;
		ss[0] << nInit;
		ss[0] >> snInit;
		ss[1] << nEvent;
		ss[1] >> snEvent;
		selection = "Entry$ >= " + snInit + " && Entry$ < " + snEvent;
		cout << "nInit=" << nInit << " nEvent=" << nEvent << "\t" << "Number of events total: " << nEvent - nInit << endl;
	
		TFile *newnewfile = new TFile(Form("miniminiTree_36.15pb-1_%ith_FSR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia.root", ilot),"recreate");
		newnewfile->cd();
		TTree *newnewtree = newwholetree->CopyTree(selection.c_str(), "", nEvent, nInit);
		cout << Form("miniminiTree_36.15pb-1_%ith_FSR_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia.root", ilot) << " created" << endl;
		newnewfile->cd();
	 //newtree->Write();
		newnewfile->Write("Tree");
		newnewfile->Close();
	}
	delete newwholetree;
	newinput->Close();

}
