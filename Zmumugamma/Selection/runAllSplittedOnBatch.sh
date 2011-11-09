#./bin/bash
# Small script to run samples on batch
# Written by Olivier Bondu (March 2010)

for zgamma in `seq 1 2`
do
#	for lumi in `echo "May10 Promptv4 July05 Aug05 Oct03 2011A 2011B 2011"`
#	for lumi in `echo "2011A 2011B 2011"`
	do
#		for low in `echo "38 40 42"`
		for low in `echo "40"`
		do
			high=`echo "${low} + 40" | bc -ql`
			if [[ "${zgamma}" == "1" ]]
			then
				zg_disp="FSR"
			fi
			if [[ "${zgamma}" == "2" ]]
			then
				zg_disp="nonFSR"
			fi
			name=`echo "v06_${zg_disp}_DY_S6_${lumi}_${low}"`
			sed -e "s/NAME/${name}/g" batch_GE_selection_template.sh > batch_GE_selection_${name}.sh
			qsub batch_GE_selection_${name}.sh Reduc_v03_DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia_PU_S6_v2 ${name} ${zgamma} ${lumi} PU_S6 ${low} ${high} 
#			qdel ${name}
		done
	done
done





return 0;




#./runThisSplittedOnBatch.sh G_Pt_0to15_TuneZ2_7TeV_pythia6 hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh Run2010A_partII hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh Run2010B hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G_Pt_15to30_TuneZ2_7TeV_pythia6 hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh TTJets_TuneZ2_7TeV-madgraph-tauola hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh WJetsToLNu_TuneZ2_7TeV-madgraph-tauola hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G2Jets_Pt-120to180_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G2Jets_Pt-180to240_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G2Jets_Pt-20to60_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G2Jets_Pt-240to300_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G2Jets_Pt-300to5000_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G2Jets_Pt-60to120_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G3Jets_Pt-120to180_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G3Jets_Pt-180to240_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G3Jets_Pt-20to60_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G3Jets_Pt-240to300_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G3Jets_Pt-300to5000_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G3Jets_Pt-60to120_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G4Jets_Pt-120to180_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G4Jets_Pt-180to240_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G4Jets_Pt-20to60_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G4Jets_Pt-240to300_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G4Jets_Pt-300to5000_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh G4Jets_Pt-60to120_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta
#./runThisSplittedOnBatch.sh QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6 hadEt-noDeltaRmin-relaxedMuEta

#./runThisSplittedOnBatch.sh Run2010A_partII hadEt-noDeltaRmin-relaxedMuEta-v2
#./runThisSplittedOnBatch.sh Run2010B hadEt-noDeltaRmin-relaxedMuEta-v2
#./runThisSplittedOnBatch.sh DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia hadEt-noDeltaRmin-relaxedMuEta-v2

#./runThisSplittedOnBatch.sh DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G2Jets_Pt-120to180_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G2Jets_Pt-180to240_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G2Jets_Pt-20to60_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G2Jets_Pt-240to300_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G2Jets_Pt-300to5000_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G2Jets_Pt-60to120_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G3Jets_Pt-120to180_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G3Jets_Pt-180to240_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G3Jets_Pt-20to60_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G3Jets_Pt-240to300_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G3Jets_Pt-300to5000_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G3Jets_Pt-60to120_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G4Jets_Pt-120to180_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G4Jets_Pt-180to240_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G4Jets_Pt-20to60_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G4Jets_Pt-240to300_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G4Jets_Pt-300to5000_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G4Jets_Pt-60to120_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G_Pt_0to15_TuneZ2_7TeV_pythia6 hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh G_Pt_15to30_TuneZ2_7TeV_pythia6 hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6 hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh Run2010A_partII hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh Run2010B hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh TTJets_TuneZ2_7TeV-madgraph-tauola hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG
#./runThisSplittedOnBatch.sh WJetsToLNu_TuneZ2_7TeV-madgraph-tauola hadEt-noDeltaRmin-relaxedMuEta-relaxedMMG



#./runThisSplittedOnBatch.sh DYToMuMu_M-20_CT10_TuneZ2_7TeV-powheg-pythia hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G2Jets_Pt-120to180_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G2Jets_Pt-180to240_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G2Jets_Pt-20to60_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G2Jets_Pt-240to300_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G2Jets_Pt-300to5000_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G2Jets_Pt-60to120_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G3Jets_Pt-120to180_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G3Jets_Pt-180to240_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G3Jets_Pt-20to60_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G3Jets_Pt-240to300_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G3Jets_Pt-300to5000_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G3Jets_Pt-60to120_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G4Jets_Pt-120to180_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G4Jets_Pt-180to240_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G4Jets_Pt-20to60_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G4Jets_Pt-240to300_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G4Jets_Pt-300to5000_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G4Jets_Pt-60to120_TuneZ2_7TeV-alpgen hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G_Pt_0to15_TuneZ2_7TeV_pythia6 hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh G_Pt_15to30_TuneZ2_7TeV_pythia6 hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6 hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh Run2010A_partII hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh Run2010B hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh TTJets_TuneZ2_7TeV-madgraph-tauola hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2
#./runThisSplittedOnBatch.sh WJetsToLNu_TuneZ2_7TeV-madgraph-tauola hadEt-noDeltaRmin-relaxedMuEta-relaxedMMGv2

#exit 0
