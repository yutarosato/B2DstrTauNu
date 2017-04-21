CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

fit_dmass_reso:fit_dmass_reso.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

fit_deltam_reso:fit_deltam_reso.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

bn_deltam_reso:bn_deltam_reso.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

fit_cos:fit_cos.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

tag_eff:tag_eff.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_dmass_reso:cal_dmass_reso.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_deltam_reso:cal_deltam_reso.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cnt_signal:cnt_signal.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
fit_dmass_reso.o  : draws_.h draws_single.h fit_dmass_reso.cpp          $(other)
fit_deltam_reso.o : draws_.h draws_single.h fit_deltam_reso.cpp         $(other)
bn_deltam_reso.o  : draws_.h draws_single.h bn_deltam_reso.cpp          $(other)
fit_cos.o         : draws_.h draws_single.h fit_cos.cpp draws_roofit_.h $(other)
tag_eff.o         : draws_.h draws_single.h tag_eff.cpp                 $(other)
cal_dmass_reso.o  : draws_.h draws_single.h cal_dmass_reso.cpp          $(other)
cal_deltam_reso.o : draws_.h draws_single.h cal_deltam_reso.cpp         $(other)
cnt_signal.o      : draws_.h draws_single.h cnt_signal.cpp              $(other)


.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
