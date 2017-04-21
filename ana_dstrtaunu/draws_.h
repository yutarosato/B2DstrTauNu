#ifndef DRAWS_H
#define DRAWS_H

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <math.h>

#include "../Util/Style.h"
#include "../Util/Object.h"
#include "../Util/Category.h"
#include "../Util/Canvas.h"
#include "../Util/makeCut.h"
#include "../Util/Print.h"
#include "../Util/FitFunc.h"
#include "../Util/Residual.h"
#include "../Util/SemiLepBFs.h"
#include "../Util/SemiLepWeights2D.h"
#include "../Util/SemiLepD2StarWeights2D.h"
#include "../Util/SemiLepDs2StarWeights2D.h"

#include <TROOT.h>
#include <TStyle.h>
#include <TTree.h>
#include <TChain.h>
#include <TText.h>
#include <THStack.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TPaveStats.h>
#include <TString.h>
#include <TF1.h>
#include <TFile.h>
#include <TPie.h>
#include <TArrow.h>
#include <TMarker.h>
#include <TMath.h>
#include <Math/DistFunc.h>
#include <TRandom.h>
#include <TMultiGraph.h>
#include <TComplex.h>


const Int_t col_fil[30] = {4,9,3,2,15,12,1,16,5,13,6,11,7,8,10,14, 17,18,19,20,21,22,23,24,25,26,27,28,29,30};

const Char_t* ctgry_BB[2] = {"B0B0", "B+B-"};
const Char_t* ctgry_DD[3] = {"D D ", "D*D ", "D*D*"};
const Char_t* ctgry_12[2] = {"1st D", "2nd D"};

const Int_t nd_dec = 15;
//                                   [       2-body D0 decay          ][                  3-body D0 decay             ][    4-body D0 decay   ][2-body D+][          3-body D+ decay       ][4-body D+]
const Char_t* d_dec_name  [nd_dec] = { "K#pi", "2K", "2#pi", "Ks#pi^{0}", "K#pi#pi^{0}", "Ks2#pi", "2#pi#pi^{0}", "Ks2K", "K3#pi", "Ks2#pi#pi^{0}", "Ks#pi", "K2#pi", "Ks#pi#pi^{0}", "2K#pi","Ks3#pi" };
const Int_t   d_dec       [nd_dec] = {    101,    2,    200,        1010,          1101,      210,          1200,     12,     301,            1210,     110,     201,           1110,     102,    310  };
const Int_t   d_dec_pi0   [nd_dec] = {      0,    0,      0,           1,             1,        0,             1,      0,       0,               1,       0,       0,              1,       0,      0  };
const Int_t   d_dec_pi    [nd_dec] = {      1,    0,      2,           0,             1,        2,             2,      0,       3,               2,       1,       2,              1,       1,      3  };
const Int_t   d_dec_Ks    [nd_dec] = {      0,    0,      0,           1,             0,        1,             0,      1,       0,               1,       1,       0,              1,       0,      1  };
const Int_t   d_dec_K     [nd_dec] = {      1,    2,      0,           0,             1,        0,             0,      2,       1,               0,       0,       1,              0,       2,      0  };
const Int_t   d_dec_chg   [nd_dec] = {      0,    0,      0,           0,             0,        0,             0,      0,       0,               0,       1,       1,              1,       1,      1  }; // 0(D0),    1(D+)

Int_t dec_index( Int_t dec ){
  for( Int_t i=0; i<nd_dec; i++ ){
    if( d_dec[i]==dec ) return i;
  }
  //if( dec==411 ) return 11; // total D+
  if( dec==411 ) return 10; // total D+ @201507016
  if( dec==421 ) return  1; // total D0 @201507016
  std::cerr << "[WARNING] Wrong fl_dec : " << dec << std::endl;
  return -999;
}

#endif
