#ifndef BCS_SIGMC_RND_H
#define BCS_SIGMC_RND_H

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
Double_t calc_bcs( Float_t d1_m,    Float_t d2_m,    Float_t dm1,        Float_t dm2,
		   Float_t d1_lund, Float_t d2_lund, Float_t dstr1_lund, Float_t dstr2_lund );

#endif
