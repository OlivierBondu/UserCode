#!/bin/bash
# move ZmumuFolders and files to nonFSR and FSR
# Written by O. Bondu (October 2010)

syntax="${0} {nonFSR/FSR}"

if [[ -z ${1} ]]
then
	echo "ERROR, syntax is: ${syntax}"
	exit 2
fi

IorF=${1}
if [[ "${IorF}" == "FSR" ]]
then
	notIorF="nonFSR"
else
	notIorF="FSR"
fi

for folder in `'ls'  -l | grep drw | awk '{print $9}' | grep Zmumu | grep -v ${notIorF} | grep -v TMP`
do
	mv ${folder} ${folder/${IorF}_Zmumu/TMP${notIorF}_Zmumu}
	for file in `'ls' ${folder/${IorF}_Zmumu/TMP${notIorF}_Zmumu}`
	do
		mv ${folder/${IorF}_Zmumu/TMP${notIorF}_Zmumu}/${file} ${folder/${IorF}_Zmumu/TMP${notIorF}_Zmumu}/${file/${IorF}_Zmumu/TMP${notIorF}_Zmumu}
	done
done

for folder in `'ls'  -l | grep drw | awk '{print $9}' | grep Zmumu | grep -v ${IorF} | grep -v TMP`
do
  mv ${folder} ${folder/${notIorF}_Zmumu/${IorF}_Zmumu}
  for file in `'ls' ${folder/${notIorF}_Zmumu/${IorF}_Zmumu}`
  do
    mv ${folder/${notIorF}_Zmumu/${IorF}_Zmumu}/${file} ${folder/${notIorF}_Zmumu/${IorF}_Zmumu}/${file/${notIorF}_Zmumu/${IorF}_Zmumu}
  done
done

for folder in `'ls'  -l | grep drw | awk '{print $9}' | grep Zmumu | grep ${notIorF}| grep TMP`
do
  mv ${folder} ${folder/TMP${notIorF}_Zmumu/${notIorF}_Zmumu}
  for file in `'ls' ${folder/TMP${notIorF}_Zmumu/${notIorF}_Zmumu}`
  do
    mv ${folder/TMP${notIorF}_Zmumu/${notIorF}_Zmumu}/${file} ${folder/TMP${notIorF}_Zmumu/${notIorF}_Zmumu}/${file/TMP${notIorF}_Zmumu/${notIorF}_Zmumu}
  done
done





exit 0
