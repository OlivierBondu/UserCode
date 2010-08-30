#!/bin/bash
# Small script to run samples on batch
# Written by Olivier Bondu (March 2010)

#./runThisSplittedOnBatch.sh InclusiveMu15 hadEt
#./runThisSplittedOnBatch.sh InclusiveMu15 noMuIso-hadEt
#./runThisSplittedOnBatch.sh InclusiveMu15 sumPt
#./runThisSplittedOnBatch.sh InclusiveMu15 noMuIso-sumPt

#./runThisSplittedOnBatch.sh PhotonJet_Pt15 hadEt
#./runThisSplittedOnBatch.sh PhotonJet_Pt15 noMuIso-hadEt
#./runThisSplittedOnBatch.sh PhotonJet_Pt15 sumPt
#./runThisSplittedOnBatch.sh PhotonJet_Pt15 noMuIso-sumPt

#./runThisSplittedOnBatch.sh PhotonJet_Pt170 hadEt
#./runThisSplittedOnBatch.sh PhotonJet_Pt170 noMuIso-hadEt
#./runThisSplittedOnBatch.sh PhotonJet_Pt170 sumPt
#./runThisSplittedOnBatch.sh PhotonJet_Pt170 noMuIso-sumPt

#./runThisSplittedOnBatch.sh PhotonJet_Pt30 hadEt
#./runThisSplittedOnBatch.sh PhotonJet_Pt30 noMuIso-hadEt
#./runThisSplittedOnBatch.sh PhotonJet_Pt30 sumPt
#./runThisSplittedOnBatch.sh PhotonJet_Pt30 noMuIso-sumPt

#./runThisSplittedOnBatch.sh PhotonJet_Pt300 hadEt
#./runThisSplittedOnBatch.sh PhotonJet_Pt300 noMuIso-hadEt
#./runThisSplittedOnBatch.sh PhotonJet_Pt300 sumPt
#./runThisSplittedOnBatch.sh PhotonJet_Pt300 noMuIso-sumPt

#./runThisSplittedOnBatch.sh PhotonJet_Pt80 hadEt
#./runThisSplittedOnBatch.sh PhotonJet_Pt80 noMuIso-hadEt
#./runThisSplittedOnBatch.sh PhotonJet_Pt80 sumPt
#./runThisSplittedOnBatch.sh PhotonJet_Pt80 noMuIso-sumPt

#./runThisSplittedOnBatch.sh QCD_Mu_Pt120to170 hadEt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt120to170 noMuIso-hadEt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt120to170 sumPt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt120to170 noMuIso-sumPt

#./runThisSplittedOnBatch.sh QCD_Mu_Pt170toInf hadEt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt170toInf noMuIso-hadEt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt170toInf sumPt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt170toInf noMuIso-sumPt

#./runThisSplittedOnBatch.sh QCD_Mu_Pt20to30 hadEt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt20to30 noMuIso-hadEt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt20to30 sumPt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt20to30 noMuIso-sumPt

#./runThisSplittedOnBatch.sh QCD_Mu_Pt30to50 hadEt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt30to50 noMuIso-hadEt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt30to50 sumPt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt30to50 noMuIso-sumPt

#./runThisSplittedOnBatch.sh QCD_Mu_Pt50to80 hadEt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt50to80 noMuIso-hadEt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt50to80 sumPt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt50to80 noMuIso-sumPt

#./runThisSplittedOnBatch.sh QCD_Mu_Pt80to120 hadEt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt80to120 noMuIso-hadEt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt80to120 sumPt
#./runThisSplittedOnBatch.sh QCD_Mu_Pt80to120 noMuIso-sumPt

#./runThisSplittedOnBatch.sh QCD_Pt15 hadEt
#./runThisSplittedOnBatch.sh QCD_Pt15 noMuIso-hadEt
#./runThisSplittedOnBatch.sh QCD_Pt15 sumPt
#./runThisSplittedOnBatch.sh QCD_Pt15 noMuIso-sumPt

#./runThisSplittedOnBatch.sh QCD_Pt170 hadEt
#./runThisSplittedOnBatch.sh QCD_Pt170 noMuIso-hadEt
#./runThisSplittedOnBatch.sh QCD_Pt170 sumPt
#./runThisSplittedOnBatch.sh QCD_Pt170 noMuIso-sumPt

#./runThisSplittedOnBatch.sh QCD_Pt30 hadEt
#./runThisSplittedOnBatch.sh QCD_Pt30 noMuIso-hadEt
#./runThisSplittedOnBatch.sh QCD_Pt30 sumPt
#./runThisSplittedOnBatch.sh QCD_Pt30 noMuIso-sumPt

#./runThisSplittedOnBatch.sh QCD_Pt300 hadEt
#./runThisSplittedOnBatch.sh QCD_Pt300 noMuIso-hadEt
#./runThisSplittedOnBatch.sh QCD_Pt300 sumPt
#./runThisSplittedOnBatch.sh QCD_Pt300 noMuIso-sumPt

#./runThisSplittedOnBatch.sh QCD_Pt470 hadEt
#./runThisSplittedOnBatch.sh QCD_Pt470 noMuIso-hadEt
#./runThisSplittedOnBatch.sh QCD_Pt470 sumPt
#./runThisSplittedOnBatch.sh QCD_Pt470 noMuIso-sumPt

#./runThisSplittedOnBatch.sh QCD_Pt80 hadEt
#./runThisSplittedOnBatch.sh QCD_Pt80 noMuIso-hadEt
#./runThisSplittedOnBatch.sh QCD_Pt80 sumPt
#./runThisSplittedOnBatch.sh QCD_Pt80 noMuIso-sumPt

#./runThisSplittedOnBatch.sh TTbarJets_Tauola-madgraph hadEt
#./runThisSplittedOnBatch.sh TTbarJets_Tauola-madgraph noMuIso-hadEt
#./runThisSplittedOnBatch.sh TTbarJets_Tauola-madgraph sumPt
#./runThisSplittedOnBatch.sh TTbarJets_Tauola-madgraph noMuIso-sumPt

#./runThisSplittedOnBatch.sh WJets_7TeV-madgraph-tauola hadEt
#./runThisSplittedOnBatch.sh WJets_7TeV-madgraph-tauola noMuIso-hadEt
#./runThisSplittedOnBatch.sh WJets_7TeV-madgraph-tauola sumPt
#./runThisSplittedOnBatch.sh WJets_7TeV-madgraph-tauola noMuIso-sumPt

#./runThisSplittedOnBatch.sh ZJets_7TeV-madgraph-tauola hadEt
#./runThisSplittedOnBatch.sh ZJets_7TeV-madgraph-tauola noMuIso-hadEt
#./runThisSplittedOnBatch.sh ZJets_7TeV-madgraph-tauola sumPt
#./runThisSplittedOnBatch.sh ZJets_7TeV-madgraph-tauola noMuIso-sumPt

#./runThisSplittedOnBatch.sh ZmumuJet_Pt0to15 hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt0to15 noMuIso-hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt0to15 sumPt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt0to15 noMuIso-sumPt

#./runThisSplittedOnBatch.sh ZmumuJet_Pt120to170 hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt120to170 noMuIso-hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt120to170 sumPt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt120to170 noMuIso-sumPt

#./runThisSplittedOnBatch.sh ZmumuJet_Pt15to20 hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt15to20 noMuIso-hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt15to20 sumPt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt15to20 noMuIso-sumPt

#./runThisSplittedOnBatch.sh ZmumuJet_Pt170to230 hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt170to230 noMuIso-hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt170to230 sumPt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt170to230 noMuIso-sumPt

#./runThisSplittedOnBatch.sh ZmumuJet_Pt20to30 hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt20to30 noMuIso-hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt20to30 sumPt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt20to30 noMuIso-sumPt

#./runThisSplittedOnBatch.sh ZmumuJet_Pt230to300 hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt230to300 noMuIso-hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt230to300 sumPt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt230to300 noMuIso-sumPt

#./runThisSplittedOnBatch.sh ZmumuJet_Pt300toInf hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt300toInf noMuIso-hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt300toInf sumPt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt300toInf noMuIso-sumPt

#./runThisSplittedOnBatch.sh ZmumuJet_Pt30to50 hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt30to50 noMuIso-hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt30to50 sumPt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt30to50 noMuIso-sumPt

#./runThisSplittedOnBatch.sh ZmumuJet_Pt50to80 hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt50to80 noMuIso-hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt50to80 sumPt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt50to80 noMuIso-sumPt

#./runThisSplittedOnBatch.sh ZmumuJet_Pt80to120 hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt80to120 noMuIso-hadEt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt80to120 sumPt
#./runThisSplittedOnBatch.sh ZmumuJet_Pt80to120 noMuIso-sumPt

#./runThisSplittedOnBatch.sh partI hadEt
#./runThisSplittedOnBatch.sh partI noMuIso-hadEt
#./runThisSplittedOnBatch.sh partI sumPt
#./runThisSplittedOnBatch.sh partI noMuIso-sumPt

#./runThisSplittedOnBatch.sh partII hadEt
#./runThisSplittedOnBatch.sh partII noMuIso-hadEt
#./runThisSplittedOnBatch.sh partII sumPt
#./runThisSplittedOnBatch.sh partII noMuIso-sumPt

#./runThisSplittedOnBatch.sh partIII hadEt
#./runThisSplittedOnBatch.sh partIII noMuIso-hadEt
#./runThisSplittedOnBatch.sh partIII sumPt
#./runThisSplittedOnBatch.sh partIII noMuIso-sumPt

#./runThisSplittedOnBatch.sh partIV hadEt
#./runThisSplittedOnBatch.sh partIV noMuIso-hadEt
#./runThisSplittedOnBatch.sh partIV sumPt
#./runThisSplittedOnBatch.sh partIV noMuIso-sumPt

#./runThisSplittedOnBatch.sh partV hadEt
#./runThisSplittedOnBatch.sh partV noMuIso-hadEt
#./runThisSplittedOnBatch.sh partV sumPt
#./runThisSplittedOnBatch.sh partV noMuIso-sumPt

#./runThisSplittedOnBatch.sh partVI hadEt
#./runThisSplittedOnBatch.sh partVI noMuIso-hadEt
#./runThisSplittedOnBatch.sh partVI sumPt
#./runThisSplittedOnBatch.sh partVI noMuIso-sumPt

./runThisSplittedOnBatch.sh partVII hadEt
./runThisSplittedOnBatch.sh partVII noMuIso-hadEt
./runThisSplittedOnBatch.sh partVII sumPt
./runThisSplittedOnBatch.sh partVII noMuIso-sumPt

exit 0
