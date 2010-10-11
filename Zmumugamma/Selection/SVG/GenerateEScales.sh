#!/bin/bash
# script to generate automatically  EScale points/iterations
# Written by O.Bondu (October 2010)

file="Selection_miniTree_hadEt-noDeltaRmin-singleTightedPtMu-plus10EScale.C"
for scale in `seq -w 0.95 0.005 1.05`
do
	echo "EScale: ${scale}"
	sed -e "/Double_t EScale/s/= .*$/= ${scale};/g" ${file} > ${file/plus10/${scale}}
done

exit 0
