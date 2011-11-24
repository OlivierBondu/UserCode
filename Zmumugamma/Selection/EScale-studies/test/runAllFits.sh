#./bin/bash
# Small script to run samples on batch
# Written by Olivier Bondu (March 2010)

source ~/load_ROOT.sh

DATE=`date +%F`

for lumi in `echo "2011"`
#for lumi in `echo "2011A 2011B 2011"`
#for lumi in `echo "2011A"`
do
  low[1]=38
  high[1]=82
  #
  low[2]=36
  high[2]=84
  #
  low[3]=38
  high[3]=84
  #
  low[4]=38
  high[4]=86
  #
  low[5]=38
  high[5]=88
  #
  low[6]=38
  high[6]=78
   #
  low[7]=40
  high[7]=80
  #
  low[8]=42
  high[8]=82
  #
  low[9]=36
  high[9]=76
  #
  low[10]=44
  high[10]=84
#	for idx in `seq 7 7`
	for idx in `seq 1 10`
	do
		low=${low[${idx}]}
		high=${high[${idx}]}
		NAME=`echo "S6_${lumi}_${low}_${high}"`
		echo "NAME= ${NAME}"
		LOC_REP=`echo "${DATE}-Plots_${NAME}"`
		if [[ -d "${LOC_REP}" ]]
		then
			rm -r ${LOC_REP}
		fi
#		mkdir ${LOC_REP}
#		for img in `echo "C png gif pdf eps"`
#		do
#	  	mkdir ${LOC_REP}/${img}
#		done
		time root -l -b -q "Scale_Data.C(\"${lumi}\", ${low}, ${high})" &> fits_${NAME}.eo
#		root -l -b -q "Scale_Data.C(\"${lumi}\", ${low}, ${high})"
		movePlots.sh ${LOC_REP}
#		sed -e "s/NAME/${NAME}/g" -e "s/LUMI/${lumi}/g" batch_GE_plotter_template.sh > batch_GE_plotter_${NAME}.sh
#		qsub batch_GE_plotter_${NAME}.sh ${lumi} ${LOC_REP} ${low} ${high}
#		mv batch_GE_plotter_${NAME}.sh stored_batch/
	done
done

return 0;

