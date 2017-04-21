CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

comparison:comparison.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

comparison_for_prd:comparison_for_prd.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cnt_multiplicity:cnt_multiplicity.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
comparison.o         : draws_.h draws_had_.h comparison.cpp         $(other)
comparison_for_prd.o : draws_.h draws_had_.h comparison_for_prd.cpp $(other)
cnt_multiplicity.o   : draws_.h draws_had_.h cnt_multiplicity.cpp   $(other)

.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
