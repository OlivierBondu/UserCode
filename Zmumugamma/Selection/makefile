# définition des cibles particulières
.PHONY: clean, mrproper
 
# désactivation des règles implicites
.SUFFIXES:
 
# définition des variables
CC = g++
#CFLAGS = -W -Wall -v -L`pwd` -lRooFitCore -lRooFit `root-config --libs --cflags`
#CFLAGS = -L`pwd` -lRooFitCore -lRooFit `root-config --libs --cflags` 
CFLAGS = -L${ROOTSYS}lib -lTMVA -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMLP -lTreePlayer -lMinuit -pthread -lm -ldl -rdynamic -pthread -m64 -I${ROOTSYS}include -L`pwd` -lToto `root-config --libs --cflags` 
  
# all
all: Selection_miniTree.o Muons_miniTree.o corrections.o rochcor2012v2.o
	$(CC) Selection_miniTree.o corrections.o rochcor2012v2.o -o Selection_miniTree.exe $(CFLAGS)
	$(CC) Muons_miniTree.o corrections.o rochcor2012v2.o -o Muons_miniTree.exe $(CFLAGS) 

Selection_miniTree.o: Selection_miniTree.C corrections.h rochcor2012v2.h
	$(CC) -c Selection_miniTree.C -o Selection_miniTree.o $(CFLAGS)

Muons_miniTree.o: Muons_miniTree.C corrections.h rochcor2012v2.h
	$(CC) -c Muons_miniTree.C -o Muons_miniTree.o $(CFLAGS)

corrections.o : corrections.C
	$(CC) -c corrections.C -o corrections.o $(CFLAGS)

rochcor2012v2.o : rochcor2012v2.C
	$(CC) -c rochcor2012v2.C -o rochcor2012v2.o $(CFLAGS)
 
# clean
clean:
	rm -rf *.bak rm -rf *.o
 
# mrproper
mrproper: clean
	rm -rf Programme


