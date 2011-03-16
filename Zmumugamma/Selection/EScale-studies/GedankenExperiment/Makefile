# Makefile

plotMC: plotMC_TDR_miniTree.o DrawMC.o
	g++ `root-config --libs --cflags` plotMC_TDR_miniTree.o DrawMC.o -o plotMC
plotMC_TDR_miniTree.o: plotMC_TDR_miniTree.C DrawMC.h
	g++ `root-config --libs --cflags` -c plotMC_TDR_miniTree.C
DrawMC.o: DrawMC.C DrawMC.h
	g++ `root-config --libs --cflags` -c DrawMC.C

