#!/bin/bash
# macro to convert raw dump into xml file for excel import
# written by O. Bondu (thanks to H. Brun) February 2011

sed -i -e "s/DATAth_/datath_/g" data.out
cat data.out | grep -v CHI2 | grep -v DATA | sed -e 's/\\pm//g' | sed -s 's/th_Photon_/\t/g' > data.raw
echo "<fullDATAxml>" > full_DATA.xml
cat data.raw | awk '{print "<"$3"><GedankenNumber>"$1"</GedankenNumber><NumberEvents>"$4"</NumberEvents><Chi2Ndf>"$5"</Chi2Ndf><Constant>"$6"</Constant><deltaConstant>"$7"</deltaConstant><"$2">"$8"</"$2"><delta"$2">"$9"</delta"$2"><delta"$2"_"$2">"$10"</delta"$2"_"$2"><Sigma>"$11"</Sigma><deltaSigma>"$12"</deltaSigma><deltaSigma_Sigma>"$13"</deltaSigma_Sigma></"$3">"}' >> full_DATA.xml
echo "</fullDATAxml>" >> full_DATA.xml
for estimator in `echo "k ik s k_5x5 ik_5x5 s_5x5 k_SC ik_SC s_SC k_SCraw ik_SCraw s_SCraw"`
do
	echo "<${estimator}XML>" > ${estimator}_DATA.xml
grep "<${estimator}>" full_DATA.xml >> ${estimator}_DATA.xml
	echo "</${estimator}XML>" >> ${estimator}_DATA.xml
done


exit 0
cat MC.out | grep -v CHI2 | grep -v MC | sed -e 's/\\pm//g' | sed -s 's/th_Photon_/\t/g' > MC.raw
echo "<fullMCxml>" > full_MC.xml

#cat dump3 | awk '{print "<GedankenNumber>"$1"</GedankenNumber><EstimatorName>"$2"</EstimatorName><region>"$3"</region><NumberEvents>"$4"</NumberEvents><Chi2Ndf>"$5"</Chi2Ndf><Constant>"$6"</Constant><deltaConstant>"$7"</deltaConstant><Estimator>"$8"</Estimator><deltaEstimator>"$9"</deltaEstimator><deltaEstimator_Estimator>"$10"</deltaEstimator_Estimator><Sigma>"$11"</Sigma><deltaSigma>"$12"</deltaSigma><deltaSigma_Sigma>"$13"</deltaSigma_Sigma>"}' >> full_MC.xml
#cat dump3 | awk '{print "<"$3"><GedankenNumber>"$1"</GedankenNumber><EstimatorName>"$2"</EstimatorName><NumberEvents>"$4"</NumberEvents><Chi2Ndf>"$5"</Chi2Ndf><Constant>"$6"</Constant><deltaConstant>"$7"</deltaConstant><Estimator>"$8"</Estimator><deltaEstimator>"$9"</deltaEstimator><deltaEstimator_Estimator>"$10"</deltaEstimator_Estimator><Sigma>"$11"</Sigma><deltaSigma>"$12"</deltaSigma><deltaSigma_Sigma>"$13"</deltaSigma_Sigma></"$3">"}' >> full_MC.xml
cat MC.raw | awk '{print "<"$3"><GedankenNumber>"$1"</GedankenNumber><NumberEvents>"$4"</NumberEvents><Chi2Ndf>"$5"</Chi2Ndf><Constant>"$6"</Constant><deltaConstant>"$7"</deltaConstant><"$2">"$8"</"$2"><delta"$2">"$9"</delta"$2"><delta"$2"_"$2">"$10"</delta"$2"_"$2"><Sigma>"$11"</Sigma><deltaSigma>"$12"</deltaSigma><deltaSigma_Sigma>"$13"</deltaSigma_Sigma></"$3">"}' >> full_MC.xml

echo "</fullMCxml>" >> full_MC.xml

for estimator in `echo "k ik s k_5x5 ik_5x5 s_5x5 k_SC ik_SC s_SC k_SCraw ik_SCraw s_SCraw"`
do
	echo "<${estimator}XML>" > ${estimator}_MC.xml
#	grep "<EstimatorName>${estimator}</EstimatorName>" full_MC.xml >> ${estimator}_MC.xml
	grep "<${estimator}>" full_MC.xml >> ${estimator}_MC.xml
	echo "</${estimator}XML>" >> ${estimator}_MC.xml
done

exit 0
