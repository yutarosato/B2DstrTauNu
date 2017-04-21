CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

fit_dmass_deltam_morecalib:fit_dmass_deltam_morecalib.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

tag_eff_morecalib:tag_eff_morecalib.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

ck_calib:ck_calib.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

comparison_dt_mc:comparison_dt_mc.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@

fit_dmass_deltam_morecalib.o : draws_.h fit_dmass_deltam_morecalib.cpp draws_roofit_.h $(other)
tag_eff_morecalib.o          : draws_.h tag_eff_morecalib.cpp  tag_eff.h               $(other)
ck_calib.o                   : draws_.h ck_calib.cpp           tag_eff.h               $(other)
comparison_dt_mc.o           : draws_.h comparison_dt_mc.cpp                           $(other)


.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
