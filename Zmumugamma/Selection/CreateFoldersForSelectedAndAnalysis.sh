#!/bin/bash
# Small script to create folder architecture in Analysis (ClemAnalysis) and in Selected (ClemFilter)
# Written for CMSSW 336 by Olivier Bondu (February 2010)

syntax="Syntax is: ${0} {Selection Version}"
if [[ -z ${1} ]]
then
				echo ${syntax}
				exit 1
fi
SelectionVersion=${1}

for Case in `echo "Analysis Selected"`
do
	for folder in `'ls' -l  /sps/cms/obondu/CMSSW_3_5_7/src/Zmumugamma/RecoSamples | egrep "^d" | awk '{print $9}' | grep -v crab`
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
			mkdir ${Case}/${SelectionVersion}/${folder}
			echo "Folder ${Case}/${SelectionVersion}/${folder} CREATED"
		fi
	done
done

