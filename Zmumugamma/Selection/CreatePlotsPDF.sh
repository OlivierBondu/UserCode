#!/bin/bash

CMSSW_release="CMSSW_3_5_8_patch3"

syntax="Syntax is: ${0}"
#if [[ -z ${1} ]]
#then
#				echo ${syntax}
#				exit 1
#fi
#SelectionVersion=${1}

plots_dir="PlotDataMC7TeV_TEST"
if [[ -d ${plots_dir}/pdf ]]
then
	echo "${plots_dir}/pdf exists"
else
	echo "creating ${plots_dir}/pdf"
	mkdir ${plots_dir}/pdf
fi

cd ${plots_dir}

echo "convert gif into pdf"
pwd
for file in `'ls' *gif`
do
	basename=`echo ${file} | cut -d . -f -1`
	if [[ -e ${basename}.pdf ]]
	then
		echo "No conversion needed for ${basename}.pdf"
	else
		echo "converting ${basename}"
		convert ${file} ${basename}.pdf
	fi
done

cd pdf

echo "
\documentclass{beamer}

\usepackage[english]{babel}
\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{amssymb}
\usepackage{graphicx}
\usepackage{colortbl}
\usepackage{wasysym}
\usepackage[abs]{overpic}
\usetheme{CambridgeUS} % +++
%\usepackage{hyperref}
\definecolor{MyColor}{RGB}{43,153,43}
\setbeamercolor{structure}{fg=MyColor}
\setbeamercolor{titlelike}{fg=MyColor}
\setbeamercolor{palette primary}{fg=MyColor}
\setbeamercolor{palette secondary}{fg=MyColor}
\setbeamercolor{palette tertiary}{bg=MyColor}
\setcounter{tocdepth}{1}

\title{Update on \$Z^0\rightarrow \mu\mu \gamma\$ FSR Selection Status}
\author{C.~B\^aty, \underline{O.~Bondu}, S.~Gascon-Shotkin, M.~Lethuillier}
\institute{IPN Lyon}

\begin{document}


\begin{frame}
\titlepage
\end{frame}

\begin{frame}
\tableofcontents
\end{frame}
" > presentation.tex

#echo "
#\section{${currentCut} Numbers}
#" >> presentation.tex

for currentCut in `echo "Before After1a After1b After1c After1d After1e After2a"`
do
	
	echo "
	\subsection{${currentCut} Muons}
	" >> presentation.tex
	
	echo "\begin{frame}
	\includegraphics[width=.3\textwidth]{../DataMC_NbMuons_${currentCut}_log.pdf}" >>presentation.tex
	for variable in `echo "Eta Phi"`
	do
		echo "\includegraphics[width=.3\textwidth]{../DataMC_${variable}_allMuons_${currentCut}.pdf}" >>presentation.tex
	done
		echo "\\\\
    " >>presentation.tex
	echo "\includegraphics[width=.3\textwidth]{../DataMC_Pt_allMuons_${currentCut}.pdf}
	\includegraphics[width=.3\textwidth]{../DataMC_Charge_allMuons_${currentCut}.pdf}
	\includegraphics[width=.3\textwidth]{../DataMC_Mmumu_${currentCut}_log.pdf}
\end{frame}
	">>presentation.tex
done

for currentCut in `echo "Before After1a After1b After1c After1d"`
do
	
	echo "
	\subsection{${currentCut} Photons}
	" >> presentation.tex
	
	echo "\begin{frame}
	\includegraphics[width=.3\textwidth]{../DataMC_NbPhotons_${currentCut}_log.pdf}" >>presentation.tex
	for variable in `echo "Eta Phi"`
	do
		echo "\includegraphics[width=.3\textwidth]{../DataMC_${variable}_allPhotons_${currentCut}.pdf}" >>presentation.tex
	done
		echo "\\\\
    " >>presentation.tex
	echo "\includegraphics[width=.3\textwidth]{../DataMC_Pt_allPhotons_${currentCut}.pdf}
	\includegraphics[width=.3\textwidth]{../DataMC_Pt_allPhotons_${currentCut}_log.pdf}
\end{frame}
	">>presentation.tex
done

#
#	echo "
#	\section{${currentCut} Photon}
#	" >> presentation.tex
#	echo "\subsection{Overview}
#	\begin{frame}
#	" >>presentation.tex
#	echo "\includegraphics[width=.3\textwidth]{../DataMC_NbPhotons_${currentCut}.pdf}" >>presentation.tex
#	for variable in `echo "Eta Phi"`
#	do
#		echo "\includegraphics[width=.3\textwidth]{../DataMC_${variable}_allPhotons_${currentCut}.pdf}" >>presentation.tex
#	done
#		echo "\\\\
#		" >>presentation.tex
#	for variable in `echo "Pt isEB isEE"`
#	do
#		echo "\includegraphics[width=.3\textwidth]{../DataMC_${variable}_allPhotons_${currentCut}.pdf}" >>presentation.tex
#	done
#	echo "\end{frame}
#	">>presentation.tex
	

echo "

\end{document}
" >> presentation.tex


echo "Creating the pdf with pdflatex"
pdflatex presentation.tex
pdflatex presentation.tex
pdflatex presentation.tex

exit 0


	echo "\subsection{Energy}
	\begin{frame}
	" >>presentation.tex
	for variable in `echo "E Emax Et"`
	do
		echo "\includegraphics[width=.3\textwidth]{../DataMC_Photon_${variable}_${currentCut}.pdf}" >>presentation.tex
	done
		echo "\\\\
		" >>presentation.tex
	for variable in `echo "E2x2 E3x3 E5x5"`
	do
		echo "\includegraphics[width=.3\textwidth]{../DataMC_Photon_${variable}_${currentCut}.pdf}" >>presentation.tex
	done
	echo "\end{frame}
	">>presentation.tex
	
	
	
	
	echo "
	\section{${currentCut} \$\mu\mu\gamma\$}
	" >> presentation.tex
	
	echo "
\begin{frame}
\includegraphics[height=.5\textheight]{../DataMC_Mmumu_${currentCut}.pdf}
\includegraphics[height=.5\textheight]{../DataMC_Mmumugamma_${currentCut}.pdf}
\end{frame}
">> presentation.tex

echo "\begin{frame}
\includegraphics[width=.3\textwidth]{../DataMC_deltaRFar_${currentCut}.pdf}
\includegraphics[width=.3\textwidth]{../DataMC_deltaRHigh_${currentCut}.pdf}
\includegraphics[width=.3\textwidth]{../DataMC_deltaRPlus_${currentCut}.pdf}
\\\\
\includegraphics[width=.3\textwidth]{../DataMC_deltaRNear_${currentCut}.pdf}
\includegraphics[width=.3\textwidth]{../DataMC_deltaRLow_${currentCut}.pdf}
\includegraphics[width=.3\textwidth]{../DataMC_deltaRMinus_${currentCut}.pdf}
\end{frame}
">> presentation.tex

done

echo "

\end{document}
" >> presentation.tex

echo "Creating the pdf with pdflatex"
pdflatex presentation.tex
pdflatex presentation.tex
pdflatex presentation.tex

exit 0
































		for muon in `echo "MuonF MuonL MuonP"`
		do
			echo "\includegraphics[width=.3\textwidth]{../DataMC_${muon}_${variable}_${currentCut}.pdf}" >>presentation.tex
		done
		echo "\\\\
		" >>presentation.tex
		for muon in `echo "MuonN MuonS MuonM"`
		do
			echo "\includegraphics[width=.3\textwidth]{../DataMC_${muon}_${variable}_${currentCut}.pdf}" >>presentation.tex
		done
	echo "\end{frame}
	">>presentation.tex	
	done
	for variable in `echo "Charge"`
	do
		echo "\subsection{${variable}}
	\begin{frame}
	" >>presentation.tex
		for muon in `echo "MuonF MuonL"`
		do
			echo "\includegraphics[height=.5\textheight]{../DataMC_${muon}_${variable}_${currentCut}.pdf}" >>presentation.tex
		done
		echo "\\\\
		" >>presentation.tex
		for muon in `echo "MuonN MuonS"`
		do
			echo "\includegraphics[height=.5\textheight]{../DataMC_${muon}_${variable}_${currentCut}.pdf}" >>presentation.tex
		done
	echo "\end{frame}
	">>presentation.tex
	done
	
	
	echo "\subsection{Isolation in \$\Delta R = .3\$ cone}
	" >>presentation.tex
	currentIso="isoR03"
	for variable in `echo "emEt hadEt hoEt nJets nTracks sumPt"`
	do
		echo "\subsubsection{${variable}}
	\begin{frame}
	" >>presentation.tex
		for muon in `echo "MuonF MuonL MuonP"`
		do
			echo "\includegraphics[width=.3\textwidth]{../DataMC_${muon}_${currentIso}_${variable}_${currentCut}.pdf}" >>presentation.tex
		done
	 	echo "\\\\
		" >>presentation.tex
	for muon in `echo "MuonN MuonS MuonM"`
		do
			echo "\includegraphics[width=.3\textwidth]{../DataMC_${muon}_${currentIso}_${variable}_${currentCut}.pdf}" >>presentation.tex
		done
	echo "\end{frame}
	">>presentation.tex
	done
	echo "\subsection{Isolation in \$\Delta R = .5\$ cone}
	" >>presentation.tex
	currentIso="isoR05"
	for variable in `echo "emEt hadEt hoEt nJets nTracks sumPt"`
	do
		echo "\subsubsection{${variable}}
	\begin{frame}
	" >>presentation.tex
		for muon in `echo "MuonF MuonL MuonP"`
		do
			echo "\includegraphics[width=.3\textwidth]{../DataMC_${muon}_${currentIso}_${variable}_${currentCut}.pdf}" >>presentation.tex
		done
		echo "\\\\
		" >>presentation.tex
	for muon in `echo "MuonN MuonS MuonM"`
		do
			echo "\includegraphics[width=.3\textwidth]{../DataMC_${muon}_${currentIso}_${variable}_${currentCut}.pdf}" >>presentation.tex
		done
	echo "\end{frame}
	">>presentation.tex
	done
	
	
	
	
	
	
