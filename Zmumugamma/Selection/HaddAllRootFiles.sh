#!/bin/bash
# script to hadd all root files into big ones
# Written by O. Bondu (August 2010)

syntax="Syntax: ${0} {cutVersion}"
if [[ -z ${1} ]]
then
  echo ${syntax}
  exit 1
fi

cutVersion=${1}

for sample in `'ls' Selected/${cutVersion}`
do
	echo "Processing ${cutVersion} ${sample}"
	summedRootFile=`'ls' Selected/${cutVersion}/${sample} | grep _0.root | sed -e "s/_0/_ALL/g"`
	if [[ -e Selected/${cutVersion}/${sample}/${summedRootFile} ]]
	then
		echo "Removing Selected/${cutVersion}/${sample}/${summedRootFile}"
		rm Selected/${cutVersion}/${sample}/${summedRootFile}
	fi
	fileList=""
	for file in `'ls' Selected/${cutVersion}/${sample} | grep root`
	do
		fileList=`echo "${fileList} Selected/${cutVersion}/${sample}/${file}"`
	done
	hadd Selected/${cutVersion}/${sample}/${summedRootFile} ${fileList}
done

for data in `'ls' Selected/${cutVersion} | grep part`
do
	summedRootFile="miniTree_DATA_ALL.root"
	if [[ -e Selected/${cutVersion}/${summedRootFile} ]]
	then
		echo "Removing Selected/${cutVersion}/${summedRootFile}"
    rm Selected/${cutVersion}/${summedRootFile}
	fi
	fileList=""
  for file in `'ls' Selected/${cutVersion}/${data} | grep root`
  do
    fileList=`echo "${fileList} Selected/${cutVersion}/${data}/${file}"`
  done
  hadd Selected/${cutVersion}/${summedRootFile} ${fileList}
done


exit 0