CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

merge_cut:merge_cut.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

merge_cut_hadtag:merge_cut_hadtag.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

merge_cut_single:merge_cut_single.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

merge_cut_ctrl_ddoublestr:merge_cut_ctrl_ddoublestr.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

through_cut:through_cut.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_weight:cal_weight.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

bcs_gmc:bcs_gmc.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

bcs_sigmc:bcs_sigmc.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

bcs_gmc_rnd:bcs_gmc_rnd.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

bcs_sigmc_rnd:bcs_sigmc_rnd.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

bcs_gmc_vtx:bcs_gmc_vtx.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

bcs_sigmc_vtx:bcs_sigmc_vtx.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@

through_cut.o               : draws_.h through_cut.cpp                   $(other)
merge_cut.o                 : draws_.h merge_cut.cpp                     $(other)
merge_cut_hadtag.o          : draws_.h merge_cut_hadtag.cpp              $(other)
merge_cut_single.o          : draws_.h merge_cut_single.cpp              $(other)
merge_cut_ctrl_ddoublestr.o : draws_.h merge_cut_ctrl_ddoublestr.cpp     $(other)
cal_weight.o                : draws_.h cal_weight.cpp                    $(other)
bcs_gmc.o                   : draws_.h bcs_gmc.h   bcs_gmc.cpp           $(other)
bcs_sigmc.o                 : draws_.h bcs_sigmc.h bcs_sigmc.cpp         $(other)
bcs_gmc_rnd.o               : draws_.h bcs_gmc_rnd.h   bcs_gmc_rnd.cpp   $(other)
bcs_sigmc_rnd.o             : draws_.h bcs_sigmc_rnd.h bcs_sigmc_rnd.cpp $(other)
bcs_gmc_vtx.o               : draws_.h bcs_gmc_vtx.h   bcs_gmc_vtx.cpp   $(other)
bcs_sigmc_vtx.o             : draws_.h bcs_sigmc_vtx.h bcs_sigmc_vtx.cpp $(other)

.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
