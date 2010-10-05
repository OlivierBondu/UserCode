#!/bin/bash
# Small script to run all GetRawSelectionCutsNumbers.sh in one shot
# Written by Olivier Bondu (March 2010)

#for selection in `echo "hadEt noMuIso-hadEt sumPt noMuIso-sumPt"`
#for selection in `echo "hadEt-lowDeltaRmin hadEt-noDeltaRmin-relaxedMuEta hadEt-noDeltaRmin-relaxedpT hadEt-noDeltaRmin-tightedPtMu"`
#for selection in `echo "hadEt-lowDeltaRmin"`
#for selection in `echo "hadEt-noDeltaRmin-relaxedMuEta"`
#for selection in `echo "hadEt-noDeltaRmin-relaxedpT"`
#for selection in `echo "hadEt-noDeltaRmin-tightedPtMu"`
for selection in `echo "hadEt-noDeltaRmin-relaxedpT-looseWindow"`
do
	./GetRawSelectionCutsNumbers.sh ${selection}
	./ConvertRawNumbersIntoNumbers.sh ${selection}
	./SumNumbersBySample.sh ${selection}
	./GetSelectionNumbers.sh ${selection}
	echo "HaddAllRootFiles.sh ${selection}"
	eval `./HaddAllRootFiles.sh ${selection}`
	cd LaTeXTables/
	eval `pdflatex SelectionCutsNumbersEfficiencies_${selection}.tex`
done

exit 0
