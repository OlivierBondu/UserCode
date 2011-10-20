{
	TChain *plaf = new TChain("miniTree");
//	plaf->Add("selection_v5/miniTree_v5_Run2011A-PromptReco-v4_June17_ALL.root");
//	plaf->Add("miniTree_v7_Run2011A_ALL.root");
//	plaf->Add("miniTree_v9_Run2011A-PromptReco-v4_July6.root");
//	plaf->Add("miniTree_v___TEMP____Run2011A-PromptReco-v4_July6_ALL.root");
//	plaf->Add("miniTree_v11_Run2011A_July6_ALL.root");
//	plaf->Add("miniTree_v11_Run2011A-May10ReReco.root");
//	plaf->Add("miniTree_v11_Run2011A-PromptReco-v4_July6.root");
//	plaf->Add("miniTree_v12_Run2011A-ZMu-05Jul2011ReReco-ECAL-v1.root");
//	plaf->Add("miniTree_v12_Run2011A-ZMu-05Jul2011ReReco-ECAL-v1.root");
//	plaf->Add("miniTree_v13_Run2011A-ZMu-05Jul2011ReReco-ECAL-v1.root");
//	plaf->Add("miniTree_v13_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_v2.root");
//	plaf->Add("miniTree_v13_Run2011A-May10ReReco_PromptReco-v4_June17.root");
//	plaf->Add("miniTree_v14_VGamma_DYToMuMu.root");
	plaf->Add("miniTree_v16_DATA_875pb-1.root");
	plaf->SetScanField(0);
	plaf->Scan("iRunID:iLumiID:iEventID", "isTightMMG && isMultipleCandidate == 0", "colsize=50");
//	plaf->Scan("iRunID:iLumiID:iEventID:Photon_Et", "isTightMMG && Photon_isEB", "colsize=50");
	return 0;
/*
	vector<string> selection;
	vector<string> name;

	selection.push_back("isLooseMMG");
	selection.push_back("isTightMMG");

	selection.push_back("isLooseMMG && Photon_isEB");
	selection.push_back("isLooseMMG && Photon_isEE");
	selection.push_back("isTightMMG && Photon_isEB");
	selection.push_back("isTightMMG && Photon_isEE");

	selection.push_back("isLooseMMG && Photon_isEB && Photon_r9 > 0.94");
	selection.push_back("isLooseMMG && Photon_isEB && Photon_r9 < 0.94");
	selection.push_back("isLooseMMG && Photon_isEE && Photon_r9 > 0.95");
	selection.push_back("isLooseMMG && Photon_isEE && Photon_r9 < 0.95");

	selection.push_back("isTightMMG && Photon_isEB && Photon_r9 > 0.94");
	selection.push_back("isTightMMG && Photon_isEB && Photon_r9 < 0.94");
	selection.push_back("isTightMMG && Photon_isEE && Photon_r9 > 0.95");
	selection.push_back("isTightMMG && Photon_isEE && Photon_r9 < 0.95");

for( int ipt = 0 ; ipt < 4 ; ipt++ )
{
	string ptcut = "";
	if( ipt == 0 ) ptcut = "&& 10.0 < Photon_Et && Photon_Et < 15.0";
	if( ipt == 1 ) ptcut = "&& 15.0 < Photon_Et && Photon_Et < 20.0";
	if( ipt == 2 ) ptcut = "&& 20.0 < Photon_Et && Photon_Et < 30.0";
	if( ipt == 3 ) ptcut = "&& 30.0 < Photon_Et";
	selection.push_back(Form("isLooseMMG && Photon_isEB && Photon_r9 > 0.94 %s", ptcut.c_str()));
	selection.push_back(Form("isLooseMMG && Photon_isEB && Photon_r9 < 0.94 %s", ptcut.c_str()));
	selection.push_back(Form("isLooseMMG && Photon_isEE && Photon_r9 > 0.95 %s", ptcut.c_str()));
	selection.push_back(Form("isLooseMMG && Photon_isEE && Photon_r9 < 0.95 %s", ptcut.c_str()));

	selection.push_back(Form("isTightMMG && Photon_isEB && Photon_r9 > 0.94 %s", ptcut.c_str()));
	selection.push_back(Form("isTightMMG && Photon_isEB && Photon_r9 < 0.94 %s", ptcut.c_str()));
	selection.push_back(Form("isTightMMG && Photon_isEE && Photon_r9 > 0.95 %s", ptcut.c_str()));
	selection.push_back(Form("isTightMMG && Photon_isEE && Photon_r9 < 0.95 %s", ptcut.c_str()));
}
	for(int i = 0; i < selection.size() ; i++)
	{	
		cout << selection[i] << "= " << plaf->GetEntries(selection[i].c_str()) << endl;
	}

*/
}
