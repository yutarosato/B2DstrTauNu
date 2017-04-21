#ifndef CAL_SIGNIF_SIGREGION_DELTAM_H
#define CAL_SIGNIF_SIGREGION_DELTAM_H

#include "draws_.h"

Double_t cal_signif ( TChain* chain, Double_t mass_L, Double_t mass_H, Double_t mass_L_slow, Double_t mass_H_slow, Bool_t fl_error=false );
Double_t cal_signifE( TChain* chain, Double_t mass_L, Double_t mass_H, Double_t mass_L_slow, Double_t mass_H_slow );

Int_t main( Int_t argc, Char_t** argv );

#endif
