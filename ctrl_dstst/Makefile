CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

fit_deltam_2d:fit_deltam_2d.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

dstst_diff_study:dstst_diff_study.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

cnt_dstst:cnt_dstst.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

2dfit:2dfit.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

2dfit_paper:2dfit_paper.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

makepdf:makepdf.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

ensemble_test:ensemble_test.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

toymc_test:toymc_test.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

ck_sideband:ck_sideband.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
fit_deltam_2d.o        : draws_.h draws_fit_.h draws_roofit_.h fit_deltam_2d.cpp    $(other)
dstst_diff_study.o     : draws_.h draws_fit_.h draws_roofit_.h dstst_diff_study.cpp $(other)
cnt_dstst.o            : draws_.h draws_fit_.h                 cnt_dstst.cpp        $(other)
2dfit.o                : draws_.h draws_fit_.h draws_roofit_.h 2dfit.cpp            $(other)
2dfit_paper.o          : draws_.h draws_fit_.h draws_roofit_.h 2dfit_paper.cpp      $(other)
makepdf.o              : draws_.h draws_fit_.h draws_roofit_.h makepdf.cpp          $(other)
ensemble_test.o        : draws_.h draws_fit_.h                 ensemble_test.cpp    $(other)
toymc_test.o           : draws_.h draws_fit_.h                 toymc_test.cpp       $(other)
ck_sideband.o          : draws_.h draws_fit_.h                 ck_sideband.cpp      $(other)

.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
