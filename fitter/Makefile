CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

makepdf:makepdf.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

makepdf_syst:makepdf_syst.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

nbprime:nbprime.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

eecl:eecl.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

nb:nb.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

2dfit:2dfit.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

fit_deltam_2d:fit_deltam_2d.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

deltam_sideband_dist:deltam_sideband_dist.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

toymc_test:toymc_test.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

ensemble_test:ensemble_test.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

syststudy:syststudy.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

dstst_component:dstst_component.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cnt_signal:cnt_signal.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cnt_npmc_sig:cnt_npmc_sig.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cnt_multiplicity:cnt_multiplicity.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

test:test.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
makepdf.o              : draws_.h draws_fit_.h draws_roofit_.h makepdf.cpp               $(other)
makepdf_syst.o         : draws_.h draws_fit_.h draws_roofit_.h makepdf_syst.cpp          $(other)
nbprime.o              : draws_.h draws_fit_.h draws_roofit_.h nbprime.cpp               $(other)
eecl.o                 : draws_.h draws_fit_.h draws_roofit_.h eecl.cpp                  $(other)
nb.o                   : draws_.h draws_fit_.h draws_roofit_.h nb.cpp                    $(other)
2dfit.o                : draws_.h draws_fit_.h draws_roofit_.h 2dfit.cpp                 $(other)
fit_deltam_2d.o        : draws_.h draws_fit_.h draws_roofit_.h fit_deltam_2d.cpp         $(other)
deltam_sideband_dist.o : draws_.h draws_fit_.h draws_roofit_.h deltam_sideband_dist.cpp  $(other)
toymc_test.o           : draws_.h draws_fit_.h                 toymc_test.cpp            $(other)
ensemble_test.o        : draws_.h draws_fit_.h                 ensemble_test.cpp         $(other)
syststudy.o            : draws_.h draws_fit_.h                 syststudy.cpp             $(other)
dstst_component.o      : draws_.h draws_fit_.h                 dstst_component.cpp       $(other)
cnt_signal.o           : draws_.h draws_fit_.h                 cnt_signal.cpp            $(other)
cnt_npmc_sig.o         : draws_.h draws_fit_.h                 cnt_npmc_sig.cpp          $(other)
cnt_multiplicity.o     : draws_.h draws_fit_.h                 cnt_multiplicity.cpp      $(other)
test.o                 : draws_.h draws_fit_.h                 test.cpp                  $(other)

.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
