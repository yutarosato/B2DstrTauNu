CXX = g++

ROOTFLAGS = `root-config --cflags`
ROOTLIBS  = `root-config --libs`

all: $(shell ls *.cpp | sed "s/\.cpp/\.o/g")

.cpp.o:
	$(CXX) $(ROOTFLAGS) -c $< -o $@
Style.o       : const.h  Style.h      Style.cpp
Category.o    : const.h  Category.h   Category.cpp
Object.o      : const.h  Object.h     Object.cpp
Canvas.o      : const.h  Canvas.h     Canvas.cpp
makeCut.o     : const.h  makeCut.h    makeCut.cpp
Print.o       : const.h  Print.h      Print.cpp
FitFunc.o     : const.h  FitFunc.h    FitFunc.cpp
Residual.o    : const.h  Residual.h   Residual.cpp

SemiLepBFs.o                 : const.h  SemiLepBFs.h               SemiLepBFs.cpp
SemiLepWeights2Ds.o          : const.h  SemiLepWeights2Ds.h        SemiLepWeights2Ds.cpp
SemiLepD2StarWeights2Ds.o    : const.h  SemiLepD2StarWeights2Ds.h  SemiLepD2StarWeights2Ds.cpp
SemiLepDs2StarWeights2Ds.o   : const.h  SemiLepDs2StarWeights2Ds.h SemiLepDs2StarWeights2Ds.cpp



.PHONY: clean
clean:
	rm $(shell ls *.cpp | sed "s/\.cpp/\.o/g")
