CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

nbout:nbout.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

eecl:eecl.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

eecl_peak:eecl_peak.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

eecl_norm_shape:eecl_norm_shape.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

ck_correlation:ck_correlation.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

compare_dststlnumc:compare_dststlnumc.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

1d:1d.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^

2d:2d.o $(other)
	$(CXX) $(ROOTLIBS_ROOFIT) -o $@ $^


.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
nbout.o              : draws_.h draws_roofit_.h nbout.cpp              $(other)
eecl.o               : draws_.h draws_roofit_.h eecl.cpp               $(other)
eecl_peak.o          : draws_.h draws_roofit_.h eecl_peak.cpp          $(other)
eecl_norm_shape.o    : draws_.h draws_roofit_.h eecl_norm_shape.cpp    $(other)
ck_correlation.o     : draws_.h draws_roofit_.h ck_correlation.cpp     $(other)
compare_dststlnumc.o : draws_.h                 compare_dststlnumc.cpp $(other)
1d.o                 : draws_.h draws_roofit_.h 1d.cpp                 $(other)
2d.o                 : draws_.h draws_roofit_.h 2d.cpp                 $(other)

.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
