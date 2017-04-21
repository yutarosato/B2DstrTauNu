#ifndef BCS_GMC_VTX_H
#define BCS_GMC_VTX_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <map>

#include "draws_.h"

typedef std::pair    < double, int > type_di;
typedef std::multimap< double, int >::iterator type_MMapIter;

Int_t main  ( Int_t argc, Char_t** argv );
Int_t select( std::multimap<double, int>& event );
Double_t calc_bcs( Float_t chisq1,    Float_t ndf1,    Float_t chisq2, Float_t ndf2 );

#endif
