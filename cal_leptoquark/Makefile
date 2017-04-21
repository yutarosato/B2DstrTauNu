dCXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

cal_cs2:cal_cs2.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_full:cal_full.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

draws_leptoquark:draws_leptoquark.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
cal_cs2.o   : draws_.h draws_leptoquark.h cal_cs2.cpp  $(other)
cal_full.o  : draws_.h draws_leptoquark.h cal_full.cpp $(other)
draws_leptoquark.o  : draws_.h draws_leptoquark.h draws_leptoquark.cpp $(other)

.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
