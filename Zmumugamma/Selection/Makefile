# Makefile

plotDataMC_TEST: plotDataMC_TDR_miniTree.o DrawDataMC.o
	g++ `root-config --libs --cflags` plotDataMC_TDR_miniTree.o DrawDataMC.o -o PLOT.exe
plotDataMC_TDR_miniTree.o: plotDataMC_TDR_miniTree.C DrawDataMC.h
	g++ `root-config --libs --cflags` -c plotDataMC_TDR_miniTree.C
DrawDataMC.o: DrawDataMC.C DrawDataMC.h CMSStyle.C
	g++ `root-config --libs --cflags` -c DrawDataMC.C

