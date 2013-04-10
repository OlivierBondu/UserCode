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
all: Selection_miniTree.o corrections.o rochcor_v4_new.o EnergyScaleCorrection_class.o
	$(CC) Selection_miniTree.o corrections.o rochcor_v4_new.o EnergyScaleCorrection_class.o -o Selection_miniTree.exe $(CFLAGS)
 
Selection_miniTree.o: Selection_miniTree.C corrections.h rochcor_v4_new.h
	$(CC) -c Selection_miniTree.C -o Selection_miniTree.o $(CFLAGS)

corrections.o : corrections.C
	$(CC) -c corrections.C -o corrections.o $(CFLAGS)

rochcor_v4_new.o : rochcor_v4_new.C
	$(CC) -c rochcor_v4_new.C -o rochcor_v4_new.o $(CFLAGS)

EnergyScaleCorrection_class.o : EnergyScaleCorrection_class.cc
	$(CC) -c EnergyScaleCorrection_class.cc -o EnergyScaleCorrection_class.o $(CFLAGS)
 
# clean
clean:
	rm -rf *.bak rm -rf *.o
 
# mrproper
mrproper: clean
	rm -rf Programme


