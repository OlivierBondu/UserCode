# Makefile


plotDataMC_TEST: plotDataMC_TDR_miniTree.o DrawDataMC.o
#	g++ -lProof -lProofPlayer `root-config --libs --cflags` plotDataMC_TDR_miniTree.o DrawDataMC.o -o PLOT.exe
	g++ `root-config --libs --cflags` plotDataMC_TDR_miniTree.o DrawDataMC.o -o PLOT.exe
plotDataMC_TDR_miniTree.o: plotDataMC_TDR_miniTree.C DrawDataMC.h
#	g++ -lProof -lProofPlayer `root-config --libs --cflags` -c plotDataMC_TDR_miniTree.C
	g++ `root-config --libs --cflags` -c plotDataMC_TDR_miniTree.C
DrawDataMC.o: DrawDataMC.C DrawDataMC.h CMSStyle.C
	g++ `root-config --libs --cflags` -c DrawDataMC.C

MyDict.cxx: DrawDataMC.h
	rootcint -f $@ -c `root-config --libs --cflags` -p $^
libMyLib.so: MyDict.cxx plotDataMC_TDR_miniTree.C DrawDataMC.C CMSStyle.C
#libMyLib.so: mydict.C plotDataMC_TDR_miniTree.C DrawDataMC.C CMSStyle.C
	g++ -shared -o$@ `root-config --ldflags` -I$(ROOTSYS)/include $^

#MyDict.cxx: $(HEADERS) Linkdef.h
#	rootcint -f $@ -c $(CXXFLAGS) -p $^
#libMyLib.so: MyDict.cxx $(SOURCES)
#	g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include $^


clean:
	rm DrawDataMC.o plotDataMC_TDR_miniTree.o DrawDataMC_h.d DrawDataMC_h.so 

