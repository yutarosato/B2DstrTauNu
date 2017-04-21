#ifndef Residual_H
#define Residual_H

#include "const.h"

TGraphErrors* Residual( TH1D* hist1, TH1D* hist2, const Char_t* axisname, const Char_t* memo = "dt-mc",     Double_t chi_range = 6.0 ); // hist1 - hist2
TGraphErrors* Residual( TH1D* hist,  TF1* func,   const Char_t* axisname, const Char_t* memo = "hist-func", Double_t chi_range = 6.0 ); // hist  - func
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TPad* makePadU(               const Char_t* name, const Char_t* title, Double_t margin=0.3, Bool_t fl_gridy=true, Bool_t fl_gridx=true );
TPad* makePadD(               const Char_t* name, const Char_t* title, Double_t margin=0.7, Bool_t fl_gridy=true, Bool_t fl_gridx=true );
TPad* makePad ( Bool_t fl_ud, const Char_t* name, const Char_t* title, Double_t margin=0.5, Bool_t fl_gridy=true, Bool_t fl_gridx=true );

#endif
