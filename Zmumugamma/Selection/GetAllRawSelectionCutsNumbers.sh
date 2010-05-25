#!/bin/bash
# Small script to run all GetRawSelectionCutsNumbers.sh in one shot
# Written by Olivier Bondu (March 2010)

for selection in `echo "CUT5 CUT5-hadEt CUT5-hadEt01 CUT5-sumPt CUT5-sumPt01 NORMAL-hadEt NORMAL-sumPt"`
do
	./GetRawSelectionCutsNumbers.sh ${selection}
done

exit 0

