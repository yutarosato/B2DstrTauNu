CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

eecl:eecl.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

nb:nb.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

draws_leg:draws_leg.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

fit_deltam_2d:fit_deltam_2d.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

2dfit:2dfit.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

2dfit_paper:2dfit_paper.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

2dfit_stat:2dfit_stat.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

convolution_rdstr:convolution_rdstr.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

convolution_nsig:convolution_nsig.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

makepdf:makepdf.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

makepdf_syst:makepdf_syst.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

ensemble_test:ensemble_test.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

toymc_test:toymc_test.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

ck_sideband:ck_sideband.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

syststudy:syststudy.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
eecl.o                 : draws_.h draws_fit_.h draws_roofit_.h eecl.cpp                  $(other)
nb.o                   : draws_.h draws_fit_.h draws_roofit_.h nb.cpp                    $(other)
draws_leg.o            : draws_.h draws_fit_.h draws_roofit_.h draws_leg.cpp             $(other)
fit_deltam_2d.o        : draws_.h draws_fit_.h draws_roofit_.h fit_deltam_2d.cpp         $(other)
2dfit.o                : draws_.h draws_fit_.h draws_roofit_.h 2dfit.cpp                 $(other)
2dfit_paper.o          : draws_.h draws_fit_.h draws_roofit_.h 2dfit_paper.cpp           $(other)
2dfit_stat.o           : draws_.h draws_fit_.h draws_roofit_.h 2dfit_stat.cpp            $(other)
convolution_rdstr.o    : draws_.h draws_fit_.h draws_roofit_.h convolution_rdstr.cpp     $(other)
convolution_nsig.o     : draws_.h draws_fit_.h draws_roofit_.h convolution_nsig.cpp      $(other)
makepdf.o              : draws_.h draws_fit_.h draws_roofit_.h makepdf.cpp               $(other)
makepdf_syst.o         : draws_.h draws_fit_.h draws_roofit_.h makepdf_syst.cpp          $(other)
ensemble_test.o        : draws_.h draws_fit_.h                 ensemble_test.cpp         $(other)
toymc_test.o           : draws_.h draws_fit_.h                 toymc_test.cpp            $(other)
ck_sideband.o          : draws_.h draws_fit_.h                 ck_sideband.cpp           $(other)
syststudy.o            : draws_.h draws_fit_.h                 syststudy.cpp             $(other)

.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
