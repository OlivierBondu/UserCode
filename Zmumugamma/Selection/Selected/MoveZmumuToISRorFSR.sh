#!/bin/bash
# move ZmumuFolders and files to ISR and FSR
# Written by O. Bondu (October 2010)

syntax="${0} {ISR/FSR}"

if [[ -z ${1} ]]
then
	echo "ERROR, syntax is: ${syntax}"
	exit 2
fi

IorF=${1}
if [[ "${IorF}" == "FSR" ]]
then
	notIorF="ISR"
else
	notIorF="FSR"
fi

for folder in `'ls'  -l | grep drw | awk '{print $9}' | grep Zmumu | grep -v ${notIorF}`
do
	mv ${folder} ${folder/Zmumu/${IorF}_Zmumu}
	for file in `'ls' ${folder/Zmumu/${IorF}_Zmumu}`
	do
		mv ${folder/Zmumu/${IorF}_Zmumu}/${file} ${folder/Zmumu/${IorF}_Zmumu}/${file/Zmumu/${IorF}_Zmumu}
	done
done

exit 0
