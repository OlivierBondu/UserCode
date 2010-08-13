#!/bin/bash
# script to relink data processed elsewhere in this directory
# Written by Olivier Bondu (July 2010)

MCrelease="CMSSW_3_6_2"
syntax="Syntax ${0} {sample}"

if [[ -z ${1} ]]
then
	echo ${syntax}
	exit 1
fi

sample=${1}
if [[ ! -e ${sample} ]]
then
  mkdir ${sample}
fi

for file in `'ls' /sps/cms/obondu/${MCrelease}/src/UserCode/IpnTreeProducer/test/${sample} | grep root`
do
	ln -s /sps/cms/obondu/${MCrelease}/src/UserCode/IpnTreeProducer/test/${sample}/${file} ./${sample}/${file}
done

exit 0
