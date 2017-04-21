CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

NB_LIBS = -L$(NEUROBAYES)/lib -lNeuroBayesTeacherCPP
NB_INC  = -I$(NEUROBAYES)/include

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

plot_dist_gen:plot_dist_gen.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

plot_dist_fit_var:plot_dist_fit_var.o $(other)
	$(CXX) $(NB_LIBS) $(ROOTLIBS) -o $@ $^

est_weight:est_weight.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

est_weight_combine:est_weight_combine.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

reweight:reweight.o $(other)
	$(CXX) $(NB_LIBS) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(NB_INC) $(ROOTFLAGS) -c $< -o $@
plot_dist_gen.o         : draws_.h plot_dist_gen.cpp                    $(other)
plot_dist_fit_var.o     : draws_.h plot_dist_fit_var.cpp                $(other)
est_weight.o            : draws_.h est_weight.cpp         draws_np_.h   $(other)
est_weight_combine.o    : draws_.h est_weight_combine.cpp draws_np_.h   $(other)
reweight.o              : draws_.h reweight.cpp           draws_np_.h   $(other)


.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
