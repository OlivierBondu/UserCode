#./bin/bash
# Small script to run samples on batch
# Written by Olivier Bondu (March 2010)

./runThisSplittedOnBatch_DTM_PROD.sh DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia hadEt-noDeltaRmin-relaxedMuEta_EScale

dtm-prod-enable -p DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia
dtm-start -p DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia -i BQS -b "-l platform=LINUX,u_sps_cmsf"

exit 0

dtm-cancel -p DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia -i BQS -a

