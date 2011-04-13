void CreateXSectionTreeFriends()
{
//TFile *parent = new TFile("DiphotonTree_MC_PythiaQCD40filtered_Test_noNNcut.root"); // QCD40
//TFile *parent = new TFile("DiphotonTree_MC_PythiaGjet20filtered_noNNcut.root"); // GammaJet
//TFile *parent = new TFile("DiphotonTree_MC_MadgraphDiphotonJets_noNNcut.root"); // Born
TFile *parent = new TFile("diphoton_DiPhoJets.root"); // Born
//TFile *parent = new TFile("DiphotonTree_MC_PythiaBox10to25_noNNcut.root"); // PythiaBox10to25
//TFile *parent = new TFile("DiphotonTree_MC_PythiaBox25to250_noNNcut.root"); // PythiaBox25to250
//TFile *parent = new TFile("DiphotonTree_MC_PythiaBox250toInf_noNNcut.root"); // PythiaBox250toInf
//TTree *parentTree = (TTree*) parent->Get("Tree");
TTree *parentTree = (TTree*) parent->Get("diPhotons");
//TFile *friend = new TFile("DiphotonTree_MC_PythiaQCD40filtered_Test_noNNcut_friend.root", "recreate"); // QCD40
//TFile *friend = new TFile("DiphotonTree_MC_PythiaGjet20filtered_noNNcut_friend.root", "recreate"); // GammaJet
//TFile *friend = new TFile("DiphotonTree_MC_MadgraphDiphotonJets_noNNcut_friend.root", "recreate"); // Born
TFile *friend = new TFile("diphoton_DiPhoJets_friend.root", "recreate"); // Born
//TFile *friend = new TFile("DiphotonTree_MC_PythiaBox10to25_noNNcut_friend.root", "recreate"); // PythiaBox10to25
//TFile *friend = new TFile("DiphotonTree_MC_PythiaBox25to250_noNNcut_friend.root", "recreate"); // PythiaBox25to250
//TFile *friend = new TFile("DiphotonTree_MC_PythiaBox250toInf_noNNcut_friend.root", "recreate"); // PythiaBox250toInf
Float_t dipho_Xsection;
TTree *friendTree = new TTree("friendTree", "friend Tree containing diphoton X section of the process");
friendTree->Branch("dipho_Xsection", &dipho_Xsection, "dipho_Xsection/F");
//dipho_Xsection = ((double)40392.0 / (double)20479315.0) * 36.134; // QCD40
//dipho_Xsection = ((double)493.44 / (double)1177569.0) * 36.134; // GammaJet
dipho_Xsection = ((double)134.0 / (double)1070060.0) * 36.134; // Born
//dipho_Xsection = ((double)358.2 / (double)792675.0) * 36.134; // PythiaBox10to25
//dipho_Xsection = ((double)12.37 / (double)768815.0) * 36.134; // PythiaBox25to250
//dipho_Xsection = ((double)0.0002 / (double)790685.0) * 36.134; // PythiaBox250toInf
cout << "parentTree->GetEntries()= " << parentTree->GetEntries() << "\t\tdipho_Xsection= " << dipho_Xsection << endl;
for (int i=0; i < parentTree->GetEntries(); i++){friendTree->Fill();}
friend->cd();
friend->Write();
friend->Close();

return;
}
