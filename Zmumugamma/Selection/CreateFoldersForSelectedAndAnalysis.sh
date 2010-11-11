#!/bin/bash
# Small script to create folder architecture in Analysis (ClemAnalysis) and in Selected (ClemFilter)
# Written for CMSSW 336 by Olivier Bondu (February 2010)

# Adapted for miniTree only (August 2010)

CMSSW_release="CMSSW_3_8_5_patch3"

syntax="Syntax is: ${0} {Selection Version}"
if [[ -z ${1} ]]
then
				echo ${syntax}
				exit 1
fi
SelectionVersion=${1}

if [[ ! -d Selected ]]
then
	echo "Folder Selected CREATED"
	mkdir Selected
fi


for Case in `echo "Selected"`
do
	for folder in `'ls' -l  /sps/cms/obondu/${CMSSW_release}/src/Zmumugamma/RecoSamples | egrep "^d" | awk '{print $9}' | grep -v crab | grep -v CVS`
	do
		if [[ -d ${Case}/${SelectionVersion} ]]
		then
			if [[ -d ${Case}/${SelectionVersion}/${folder} ]]
			then
				continue
			else
				mkdir ${Case}/${SelectionVersion}/${folder}
				echo "Folder ${Case}/${SelectionVersion}/${folder} CREATED"
			fi
		else
			mkdir ${Case}/${SelectionVersion}
			echo "Folder ${Case}/${SelectionVersion} CREATED"
			mkdir ${Case}/${SelectionVersion}/${folder}
			echo "Folder ${Case}/${SelectionVersion}/${folder} CREATED"
		fi
	done
done

