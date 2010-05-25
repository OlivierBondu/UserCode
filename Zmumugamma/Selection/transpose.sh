#!/bin/bash
# Small script to transpose line data to column data and vice versa
# From http://stackoverflow.com/questions/1729824/transpose-a-file-in-bash (May 2010)

if [[ -z ${1} ]]
then
	echo "ERROR: syntax is ${0} {filename}"
	exit 1
fi
file=${1}

awk '
{ 
    for (i=1; i<=NF; i++)  {
        a[NR,i] = $i
    }
}
NF>p { p = NF }
END {    
    for(j=1; j<=p; j++) {
        str=a[1,j]
        for(i=2; i<=NR; i++){
            str=str" "a[i,j];
        }
        print str
    }
}' ${file}

exit 0
