CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

all: pid util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g") $(shell ls codes/*.cpp | sed "s/\.cpp/.o/g")

pid:
	cd codes; make

util:
	cd ../Util; make

cal_pid_syst_kpi:cal_pid_syst_kpi.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_pid_syst_ks:cal_pid_syst_ks.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_pid_syst_pi0:cal_pid_syst_pi0.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_pid_syst_lep:cal_pid_syst_lep.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_pid_syst_lep_double:cal_pid_syst_lep_double.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_pid_syst_lep_double_ratio:cal_pid_syst_lep_double_ratio.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
cal_pid_syst_kpi.o                : draws_.h draws_syst.h cal_pid_syst_kpi.cpp               $(other)
cal_pid_syst_ks.o                 : draws_.h draws_syst.h cal_pid_syst_ks.cpp                $(other)
cal_pid_syst_pi0.o                : draws_.h draws_syst.h cal_pid_syst_pi0.cpp               $(other)
cal_pid_syst_lep.o                : draws_.h draws_syst.h cal_pid_syst_lep.cpp               $(other)
cal_pid_syst_lep_double.o         : draws_.h draws_syst.h cal_pid_syst_lep_double.cpp        $(other)
cal_pid_syst_lep_double_ratio.o   : draws_.h draws_syst.h cal_pid_syst_lep_double_ratio.cpp  $(other)


.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls codes/*.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
