#!/bin/bash

CMSSW_release="CMSSW_3_5_8_patch3"

syntax="Syntax is: ${0}"
#if [[ -z ${1} ]]
#then
#        echo ${syntax}
#        exit 1
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

currentCut="isAfterCut2c"

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
\usepackage{hyperref}
\definecolor{MyColor}{RGB}{43,153,43}
\setbeamercolor{structure}{fg=MyColor}
\setbeamercolor{titlelike}{fg=MyColor}
\setbeamercolor{palette primary}{fg=MyColor}
\setbeamercolor{palette secondary}{fg=MyColor}
\setbeamercolor{palette tertiary}{bg=MyColor}
\setcounter{tocdepth}{2}

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

echo "
\section{Numbers}
" >> presentation.tex

echo "
\section{Muons}
" >> presentation.tex

echo "\begin{frame}
\includegraphics[width=.5\textwidth]{../DataMC_NbMuons_${currentCut}.pdf}
\end{frame}
">>presentation.tex

for variable in `echo "Eta Phi Pt"`
do
	echo "\subsection{${variable}}
\begin{frame}
" >>presentation.tex
	for muon in `echo "MuonF MuonH MuonP"`
	do
		echo "\includegraphics[width=.3\textwidth]{../DataMC_${muon}_${variable}_${currentCut}.pdf}" >>presentation.tex
	done
	echo "\\\\
	" >>presentation.tex
	for muon in `echo "MuonN MuonL MuonM"`
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
  for muon in `echo "MuonF MuonH"`
  do
    echo "\includegraphics[height=.5\textheight]{../DataMC_${muon}_${variable}_${currentCut}.pdf}" >>presentation.tex
  done
  echo "\\\\
  " >>presentation.tex
  for muon in `echo "MuonN MuonL"`
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
	for muon in `echo "MuonF MuonH MuonP"`
  do
		echo "\includegraphics[width=.3\textwidth]{../DataMC_${muon}_${currentIso}_${variable}_${currentCut}.pdf}" >>presentation.tex
  done
 	echo "\\\\
  " >>presentation.tex
for muon in `echo "MuonN MuonL MuonM"`
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
  for muon in `echo "MuonF MuonH MuonP"`
  do
    echo "\includegraphics[width=.3\textwidth]{../DataMC_${muon}_${currentIso}_${variable}_${currentCut}.pdf}" >>presentation.tex
  done
  echo "\\\\
  " >>presentation.tex
for muon in `echo "MuonN MuonL MuonM"`
  do
    echo "\includegraphics[width=.3\textwidth]{../DataMC_${muon}_${currentIso}_${variable}_${currentCut}.pdf}" >>presentation.tex
  done
echo "\end{frame}
">>presentation.tex
done






echo "
\section{Photon}
" >> presentation.tex
echo "\subsection{Overview}
\begin{frame}
" >>presentation.tex
echo "\includegraphics[width=.3\textwidth]{../DataMC_NbPhotons_${currentCut}.pdf}" >>presentation.tex
for variable in `echo "E Eta"`
do
	echo "\includegraphics[width=.3\textwidth]{../DataMC_Photon_${variable}_${currentCut}.pdf}" >>presentation.tex
done
  echo "\\\\
  " >>presentation.tex
for variable in `echo "Phi isEB isEE"`
do
  echo "\includegraphics[width=.3\textwidth]{../DataMC_Photon_${variable}_${currentCut}.pdf}" >>presentation.tex
done
echo "\end{frame}
">>presentation.tex

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
\section{\$\mu\mu\gamma\$}
" >> presentation.tex


echo "

\end{document}
" >> presentation.tex

echo "Creating the pdf with pdflatex"
pdflatex presentation.tex
pdflatex presentation.tex
pdflatex presentation.tex

exit 0
