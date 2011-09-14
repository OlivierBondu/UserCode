#!/bin/bash
# Script to extract information from the output of all fits
# Written by Olivier Bondu (August 2011)

syntax="$0 {outputPrefix}"
if [[ -z $1 ]]
then
	echo ${syntax}
	return 1
fi

outputPrefix="${1}"

if [[ -e ${outputPrefix}_latex.out ]]
then
	echo "ERROR: file already exists"
	return 2;
fi
rm ${outputPrefix}_latex.out ${outputPrefix}_latex2.out


grep -A 10 'begin{tabular}{ccc}'  VGamma_875pb-1_v3.out > dump_${outputPrefix}.txt
#grep -A 10 'begin{tabular}{ccc}'  VGamma_875pb-1_v3.out | grep tight > dump_${outputPrefix}.txt

for estimator in `echo "s f"`
do
	if [[ "${estimator}" == "f" ]]
	then
		var="))"
	elif [[ "${estimator}" == "s" ]]
	then
		var="s"
	fi
	for data in `echo "DATA MC"`
	do
echo "#################################################"
echo "### Processing ${estimator} ${data} ###"
echo "#################################################"
		for EBEE in `echo "EB EE"`
		do
			for r9 in `echo "lowR9 highR9 inclusiveR9"`
			do
				if [[ "${EBEE}" == "EB" ]]
				then
					if [[ "${r9}" == "lowR9" ]]
					then
						grab_r9="< .94"
					elif [[ "${r9}" == "highR9" ]]
          then
            grab_r9="> .94"
					elif [[ "${r9}" == "inclusiveR9" ]]
					then
						grab_r9="gamma}\\$, \\$ \\$"
					fi
				elif [[ "${EBEE}" == "EE" ]]
				then
					if [[ "${r9}" == "lowR9" ]]
          then
            grab_r9="< .95"
          elif [[ "${r9}" == "highR9" ]]
          then
            grab_r9="> .95"
          elif [[ "${r9}" == "inclusiveR9" ]]
          then
            grab_r9="gamma}\\$, \\$ \\$"
          fi
				fi
#				for pt in `echo "10.0 15.0 20.0 30.0 inclusive_pt"`
#				for pt in `echo "10.0 11.0 12.0 13.0 14.0"`
				for pt in `echo "10.0 12.0 15.0 20.0 25.0 30.0 inclusivept"`
				do
					if [[ "${pt}" == "inclusivept" ]]
					then
#						grab_pt=", \\$ \\$, \\$ \\$"
						grab_pt="inclusive p_"
#inclusive p_{T}
					else
#						sup=`echo "${pt} + 1.0" | bc -ql`
#						grab_pt=`echo "${pt} < p_{T} < ${sup}"`
						grab_pt=`echo "${pt} < "`
					fi
					for run in `echo "inclusive_run"`
					do
						echo -e "### ${estimator}\t${EBEE}\t${r9}\t${pt}\t${run} ###"
						if [[ "${run}" == "inclusive_run" ]]
						then
							grab_run=", \\$ \\\$[[:space:]]*&[[:space:]]*\\\$${estimator}\\$"
						else
							grab_run=`echo "${run} < run"`
						fi
						if [[ "${estimator}" == "s" ]]
						then
#							cat dump_${outputPrefix}.txt | grep "${EBEE}" | grep "${grab_r9}" | grep "${grab_pt}" | grep "${grab_run}"
							cat dump_${outputPrefix}.txt | grep -B 1 -A 8 "${EBEE}" | grep -B 1 -A 8 "${grab_r9}" | grep -B 1 -A 8 "${grab_pt}" | grep -B 1 -A 8 "${grab_run}" | grep -B 1 -A 8 "${estimator}\\$" | grep -v "data 	\&" | grep -v "mc 	&" | grep -v " data - mc 	&" >> ${outputPrefix}_latex.out
						else
							cat dump_${outputPrefix}.txt | grep -B 1 -A 8 "${EBEE}" | grep -B 1 -A 8 "${grab_r9}" | grep -B 1 -A 8 "${grab_pt}" | grep -B 1 -A 8 "${grab_run}" | grep -B 1 -A 8 "${estimator}\\$" | grep -v "data (" | grep -v "mc (" | grep -v " data - mc  &" >> ${outputPrefix}_latex.out
						fi
					done
					#end of run
				done
				# end of pt
				echo -e "\n\n%%%%%%%%\n\n"  >> ${outputPrefix}_latex.out
#				for pt in `echo "inclusive_pt"`
#				do
#					if [[ "${pt}" == "inclusive_pt" ]]
#					then
#						grab_pt=" "
#					else
#						grab_pt=`echo "${pt} < "`
#					fi
#					for run in `echo "160431 165071 165971 166503 166862 inclusive_run"`
#					do
#						echo -e "${estimator}\t${EBEE}\t${r9}\t${pt}\t${run}"
#						if [[ "${run}" == "inclusive_run" ]]
#						then
#							grab_run=", \\$ \\$"
#						else
#							grab_run=`echo "${run} < run"`
#						fi
#						if [[ "${estimator}" == "s" ]]
#						then
#							cat dump_${outputPrefix}.txt | grep -B 1 -A 8 "${EBEE}" | grep -B 1 -A 8 "${grab_r9}" | grep -B 1 -A 8 "${grab_pt}" | grep -B 1 -A 8 "${grab_run}" | grep -B 1 -A 8 "${estimator}\\$" | grep -v "data 	\&" | grep -v "mc 	&" | grep -v " data - mc 	&" >> ${outputPrefix}_latex2.out
#						else
#							cat dump_${outputPrefix}.txt | grep -B 1 -A 8 "${EBEE}" | grep -B 1 -A 8 "${grab_r9}" | grep -B 1 -A 8 "${grab_pt}" | grep -B 1 -A 8 "${grab_run}" | grep -B 1 -A 8 "${estimator}\\$" | grep -v "data (" | grep -v "mc (" | grep -v " data - mc  &" >> ${outputPrefix}_latex2.out
#						fi
#					done
#					#end of run
#				done
#				# end of pt
			done
			# end of r9
		done
		# end of eb/ee
	done	
	# end of data/mc
done
# end of estimator


#return 3



for estimator in `echo "s f"`
do
	if [[ "${estimator}" == "f" ]]
	then
		grab_estimator="\\\$"
	elif [[ "${estimator}" == "s" ]]
	then
		var="s"
	fi
	for data in `echo "DATA MC"`
	do
echo "#################################################"
echo "### Processing ${estimator} ${data} ###"
echo "#################################################"
		for EBEE in `echo "EB EE"`
		do
			for r9 in `echo "lowR9 highR9 inclusiveR9"`
			do
				if [[ "${EBEE}" == "EB" ]]
				then
					if [[ "${r9}" == "lowR9" ]]
					then
						grab_r9="< .94"
					elif [[ "${r9}" == "highR9" ]]
          then
            grab_r9="> .94"
					elif [[ "${r9}" == "inclusiveR9" ]]
					then
						grab_r9="gamma}\\$, \\$ \\\$, \\$ \\$"
					fi
				elif [[ "${EBEE}" == "EE" ]]
				then
					if [[ "${r9}" == "lowR9" ]]
          then
            grab_r9="< .95"
          elif [[ "${r9}" == "highR9" ]]
          then
            grab_r9="> .95"
          elif [[ "${r9}" == "inclusiveR9" ]]
          then
            grab_r9="gamma}\\$, \\$ \\\$, \\$ \\$"
          fi
				fi
				for pt in `echo "inclusivept"`
				do
					if [[ "${pt}" == "inclusivept" ]]
					then
						grab_pt="inclusive p_"
					else
						grab_pt=`echo "${pt} < "`
					fi
					for run in `echo "163869 165970 166502 166861 166967 inclusive_run"`
#166503_lt_run_lt_166861/3\t/g" -e "s/166862_lt_run_lt_166967/4\t/g" -e "s/inclusive_
					do
						echo -e "### ${estimator}\t${EBEE}\t${r9}\t${pt}\t${run} ###"
						if [[ "${run}" == "inclusive_run" ]]
						then
							grab_run=", \\$ \\\$, \\$ \\\$[[:space:]]*&[[:space:]]*\\\$${estimator}\\$"
						else
#							grab_run=`echo "run < ${run}\\\$[[:space:]]*&[[:space:]]*\\\$${estimator}\\$"`
							grab_run=`echo "run < ${run}"`
						fi
						if [[ "${estimator}" == "s" ]]
						then
#							cat dump_${outputPrefix}.txt | grep "${EBEE}" | grep "${grab_r9}" | grep "${grab_pt}" | grep "${grab_run}" | grep "\\\$${estimator}\\\$"
							cat dump_${outputPrefix}.txt | grep -B 1 -A 8 "${EBEE}" | grep -B 1 -A 8 "${grab_r9}" | grep -B 1 -A 8 "${grab_pt}" | grep -B 1 -A 8 "${grab_run}" | grep -B 1 -A 8 "${estimator}\\$" | grep -v "data 	\&" | grep -v "mc 	&" | grep -v " data - mc 	&" >> ${outputPrefix}_latex2.out
						else
							cat dump_${outputPrefix}.txt | grep -B 1 -A 8 "${EBEE}" | grep -B 1 -A 8 "${grab_r9}" | grep -B 1 -A 8 "${grab_pt}" | grep -B 1 -A 8 "${grab_run}" | grep -B 1 -A 8 "${estimator}\\$" | grep -v "data (" | grep -v "mc (" | grep -v " data - mc  &" >> ${outputPrefix}_latex2.out
						fi
					done
					#end of run
				done
				# end of pt
				echo -e "\n\n%%%%%%%%\n\n"  >> ${outputPrefix}_latex2.out
#				for pt in `echo "inclusive_pt"`
#				do
#					if [[ "${pt}" == "inclusive_pt" ]]
#					then
#						grab_pt=" "
#					else
#						grab_pt=`echo "${pt} < "`
#					fi
#					for run in `echo "160431 165071 165971 166503 166862 inclusive_run"`
#					do
#						echo -e "${estimator}\t${EBEE}\t${r9}\t${pt}\t${run}"
#						if [[ "${run}" == "inclusive_run" ]]
#						then
#							grab_run=", \\$ \\$"
#						else
#							grab_run=`echo "${run} < run"`
#						fi
#						if [[ "${estimator}" == "s" ]]
#						then
#							cat dump_${outputPrefix}.txt | grep -B 1 -A 8 "${EBEE}" | grep -B 1 -A 8 "${grab_r9}" | grep -B 1 -A 8 "${grab_pt}" | grep -B 1 -A 8 "${grab_run}" | grep -B 1 -A 8 "${estimator}\\$" | grep -v "data 	\&" | grep -v "mc 	&" | grep -v " data - mc 	&" >> ${outputPrefix}_latex2.out
#						else
#							cat dump_${outputPrefix}.txt | grep -B 1 -A 8 "${EBEE}" | grep -B 1 -A 8 "${grab_r9}" | grep -B 1 -A 8 "${grab_pt}" | grep -B 1 -A 8 "${grab_run}" | grep -B 1 -A 8 "${estimator}\\$" | grep -v "data (" | grep -v "mc (" | grep -v " data - mc  &" >> ${outputPrefix}_latex2.out
#						fi
#					done
#					#end of run
#				done
#				# end of pt
			done
			# end of r9
		done
		# end of eb/ee
	done	
	# end of data/mc
done
# end of estimator












return 0
