ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)

# set the compiler options
CXX           = gcc
CXXFLAGS      = -g -Wall -Wextra -O2
                                   #-g compile with debug information
                                   #-O optimize (-O2 is higher grade of optimalization)
                                   #-Wall and -Wextra show warnings for everything

# set the linker options
LD            = gcc
LDFLAGS       = -O2

#######################
CXXFLAGS   = $(ROOTCFLAGS)
LIBS       = $(ROOTLIBS) -L$(NEUROBAYES)/lib -lNeuroBayesTeacherCPP
INC        = -I$(NEUROBAYES)/include

default : nb_training nb_expert

all: util nb_training nb_expert
other = $(shell ls ../Util/*.cpp | sed "s/\.cpp/.o/g")

util:
	cd ../Util; make

src/nb_manip.o: src/nb_manip.cpp
	@$(CXX) $(INC) $(CXXFLAGS) -c src/nb_manip.cpp -o src/nb_manip.o

src/nb_training.o: src/nb_training.cpp
	@$(CXX) $(INC) $(CXXFLAGS) -c src/nb_training.cpp -o src/nb_training.o

nb_training: src/nb_training.o src/nb_manip.o $(other)
	@$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

src/nb_expert.o: src/nb_expert.cpp
	@$(CXX) $(INC) $(CXXFLAGS) -c src/nb_expert.cpp -o src/nb_expert.o

nb_expert: src/nb_expert.o src/nb_manip.o $(other)
	@$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf src/*.o nb_expert nb_training
