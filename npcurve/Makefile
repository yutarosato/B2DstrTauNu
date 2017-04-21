dCXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

draws_2hdmII:draws_2hdmII.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

draws_R2LQ:draws_R2LQ.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

draws_S1LQ:draws_S1LQ.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

draws_OPS1:draws_OPS1.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

draws_OPS2:draws_OPS2.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

draws_OPV1:draws_OPV1.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

draws_OPV2:draws_OPV2.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

draws_OPT:draws_OPT.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
draws_2hdmII.o     : draws_.h draws_npcurve_.h draws_2hdmII.cpp $(other)
draws_R2LQ.o       : draws_.h draws_npcurve_.h draws_R2LQ.cpp   $(other)
draws_S1LQ.o       : draws_.h draws_npcurve_.h draws_S1LQ.cpp   $(other)
draws_OPS1.o       : draws_.h draws_npcurve_.h draws_OPS1.cpp   $(other)
draws_OPS2.o       : draws_.h draws_npcurve_.h draws_OPS2.cpp   $(other)
draws_OPV1.o       : draws_.h draws_npcurve_.h draws_OPV1.cpp   $(other)
draws_OPV2.o       : draws_.h draws_npcurve_.h draws_OPV2.cpp   $(other)
draws_OPT.o        : draws_.h draws_npcurve_.h draws_OPT.cpp    $(other)


.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
