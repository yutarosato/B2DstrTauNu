CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`
ROOTLIBS_ROOFIT = `root-config --libs`
ROOTLIBS_ROOFIT += -lRooFit -lRooFitCore -lMinuit 

all: util $(shell ls *.cpp | sed "s/\.cpp//g")
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

cnt_gen:cnt_gen.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cnt_signal:cnt_signal.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

plot:plot.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

plot_sum_cos:plot_sum_cos.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

plot_combine:plot_combine.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

plot_var_event:plot_var_event.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

plot_var_event_gmc:plot_var_event_gmc.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

plot_var_single:plot_var_single.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

plot_var_2d:plot_var_2d.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

cal_eff:cal_eff.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

plot_true_dist:plot_true_dist.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

correlation_var_1d:correlation_var_1d.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

correlation_var_2d:correlation_var_2d.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

estimate_bremsstrahlung_recovery:estimate_bremsstrahlung_recovery.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

mass_resolution:mass_resolution.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

eecl_origin_ratio:eecl_origin_ratio.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

check_strange_nbpeak:check_strange_nbpeak.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

scan_significance:scan_significance.o $(other)
	$(CXX) $(ROOTLIBS) -o $@ $^

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
cnt_gen.o         : draws_.h cnt_gen.cpp         $(other)
cnt_signal.o      : draws_.h cnt_signal.cpp      $(other)
plot.o            : draws_.h plot.cpp            $(other)
plot_sum_cos.o    : draws_.h plot_sum_cos.cpp    $(other)
plot_combine.o    : draws_.h plot_combine.cpp    $(other)
plot_var_single.o : draws_.h plot_var_single.cpp $(other)
plot_var_2d.o     : draws_.h plot_var_2d.cpp     $(other)
plot_var_event.o  : draws_.h plot_var_event.cpp  $(other)
plot_var_event_gmc.o : draws_.h plot_var_event_gmc.cpp  $(other)
cal_eff.o         : draws_.h cal_eff.cpp         $(other)
plot_true_dist.o  : draws_.h plot_true_dist.cpp  $(other)
correlation_var_1d.o : draws_.h correlation_var_1d.cpp $(other)
correlation_var_2d.o : draws_.h correlation_var_2d.cpp $(other)
estimate_bremsstrahlung_recovery.o : draws_.h estimate_bremsstrahlung_recovery.cpp $(other)
mass_resolution.o    : draws_.h mass_resolution.cpp    $(other)
eecl_origin_ratio.o  : draws_.h eecl_origin_ratio.cpp  $(other)
check_strange_nbpeak.o  : draws_.h check_strange_nbpeak.cpp  $(other)
scan_significance.o  : draws_.h scan_significance.h scan_significance.cpp  $(other)


.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
distclean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g") $(shell ls ../Util/*.cpp | sed "s/\.cpp/\.o/g")
