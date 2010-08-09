#!/bin/bash
# Small script to run CreateFoldersForSelectedAndAnalysis.sh for all selections in one shot
# Written by Olivier Bondu (March 2010)

for selection in `echo "hadEt"`
do
	./CreateFoldersForSelectedAndAnalysis.sh ${selection}
done

exit 0
