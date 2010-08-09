#!/bin/bash
# Small script to run samples on batch
# Written by Olivier Bondu (March 2010)

./runThisSplittedOnBatch.sh partI hadEt
./runThisSplittedOnBatch.sh partII hadEt
./runThisSplittedOnBatch.sh partIII hadEt
./runThisSplittedOnBatch.sh partIV hadEt
./runThisSplittedOnBatch.sh partV hadEt

./runThisSplittedOnBatch.sh PhotonJet_Pt15 hadEt
./runThisSplittedOnBatch.sh PhotonJet_Pt30 hadEt
./runThisSplittedOnBatch.sh PhotonJet_Pt80 hadEt
./runThisSplittedOnBatch.sh PhotonJet_Pt170 hadEt
./runThisSplittedOnBatch.sh PhotonJet_Pt300 hadEt

./runThisSplittedOnBatch.sh QCD_Pt15 hadEt
./runThisSplittedOnBatch.sh QCD_Pt30 hadEt
./runThisSplittedOnBatch.sh QCD_Pt80 hadEt
./runThisSplittedOnBatch.sh QCD_Pt170 hadEt
./runThisSplittedOnBatch.sh QCD_Pt300 hadEt
./runThisSplittedOnBatch.sh QCD_Pt470 hadEt

exit 0
