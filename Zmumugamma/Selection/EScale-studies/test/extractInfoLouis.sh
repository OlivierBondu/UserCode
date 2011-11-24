#!/bin/bash
# Small script to extract info of MC truth in Louis' files
# Written by Olivier Bondu (November 2011)

# CB & BG: 
LouisDir="/sps/cms/sgandurr/CMSSW_4_2_3_patch2/src/UserCode/IpnTreeProducer/ComparaisonFitsErecoOverEtrueJan/Olivier/2011/Fits"
#fit="CB"
fit="BFG"

# fits RECO: Olivier2

for eta in `echo "EB EE"`
do
	if [[ "${eta}" == "EB" ]]; then eta_disp=0; fi
	if [[ "${eta}" == "EE" ]]; then eta_disp=1; fi
	for r9 in `echo "inf sup"`
	do
		if [[ "${r9}" == "inf" ]]; then r9_disp=0; fi
		if [[ "${r9}" == "sup" ]]; then r9_disp=1; fi
		tempdir=`echo "${LouisDir}/ErecoOverEtrue${fit}r9${r9}${eta}"`
		for pT in  `echo "10 12 15 20 25 30"`
		do
			if [[ "${pT}" == "10" ]]; then pT_disp=0; fi
			if [[ "${pT}" == "12" ]]; then pT_disp=1; fi
			if [[ "${pT}" == "15" ]]; then pT_disp=2; fi
			if [[ "${pT}" == "20" ]]; then pT_disp=3; fi
			if [[ "${pT}" == "25" ]]; then pT_disp=4; fi
			if [[ "${pT}" == "30" ]]; then pT_disp=5; fi
			line=`cat -n ${tempdir}/MinPt.txt | grep "${pT}" | awk '{print $1}'`
			mean=`head -n ${line} ${tempdir}/MeanTab.txt | tail -n 1`
			meanerror=`head -n ${line} ${tempdir}/MeanErrorTab.txt | tail -n 1`
#			meanerror=`head -n ${line} ${tempdir}/SigmaEffTab.txt | tail -n 1`
#			meanerror=`echo "${meanerror} * 100.0" | bc -ql`
			echo -e "${eta_disp}\t${r9_disp}\t${pT_disp}\t5\t${mean}\t${meanerror}"
		done
	done
done 

return 0;
