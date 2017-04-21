CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

scan_1d:scan_1d.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_signif_sigregion_pi0mass:cal_signif_sigregion_pi0mass.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_signif_sigregion_dmass:cal_signif_sigregion_dmass.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_signif_sigregion_deltam:cal_signif_sigregion_deltam.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
scan_1d.o                         : draws_.h scan_1d.h                      scan_1d.cpp                      $(other)
cal_signif_sigregion_pi0mass.o    : draws_.h cal_signif_sigregion_pi0mass.h cal_signif_sigregion_pi0mass.cpp $(other)
cal_signif_sigregion_dmass.o      : draws_.h cal_signif_sigregion_dmass.h   cal_signif_sigregion_dmass.cpp   $(other)
cal_signif_sigregion_deltam.o     : draws_.h cal_signif_sigregion_deltam.h  cal_signif_sigregion_deltam.cpp  $(other)

.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
