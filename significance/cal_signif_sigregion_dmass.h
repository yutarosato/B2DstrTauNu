#ifndef CAL_SIGNIF_SIGREGION_DMASS_H
#define CAL_SIGNIF_SIGREGION_DMASS_H

#include "draws_.h"

Double_t cal_signif ( TChain* chain, Double_t mass_D0L, Double_t mass_D0H, Double_t mass_D0L_pi0, Double_t mass_D0H_pi0, Bool_t fl_error=false );
Double_t cal_signifE( TChain* chain, Double_t mass_L, Double_t mass_H, Double_t mass_L_slow, Double_t mass_H_slow );

Int_t main( Int_t argc, Char_t** argv );

#endif
