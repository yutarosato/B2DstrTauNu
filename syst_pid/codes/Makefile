CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`

all: $(shell ls *.cpp | sed "s/\.cpp/\.o/g")

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
lid_syst_09.o       : lid_syst_09.h      lid_syst_09.cpp
kid_eff_09.o        : kid_eff_09.h       kid_eff_09.cpp
Ks_eff.o            : Ks_eff.h           Ks_eff.cpp
pi0_eff.o           : pi0_eff.h          pi0_eff.cpp

.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
