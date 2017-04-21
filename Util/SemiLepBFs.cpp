#include "SemiLepBFs.h"
#include <cmath>


// BF weights
// using PDG for, D and D*
// using PRD 61 014016 for the rest

float SemiLepBFs(int lclass, int mom_lund) {
    // FROM PDG:
    if (lclass == 2) {
        if (abs(mom_lund) == 521) return 0.98; // D0
        else return 1.03; // D+
    } else if (lclass == 1) {
        if (abs(mom_lund) == 521) return 0.98; // D*0
        else return 0.92; // D*+
    }
    // FROM PRD 61 014016
    /*
    else if (lclass == 3) return 0.85; // D1
    else if (lclass == 4) return 1.64; // D2
    else if (lclass == 5) return 0.12; // D1'
    else if (lclass == 6) return 0.17; // D*0
    */
    // FROM PRD 87 034033
    else if (lclass == 7) return 1.0; // Ds
    else if (lclass == 9) return 1.08; // Ds*
    // FROM PRD 61 014016
    /*
    else if (lclass == 8) return 0.9; // Ds0*
    else if (lclass == 10) return 2.1; // Ds1(2536)
    else if (lclass == 11) return 0.27; // Ds1'(2460)
    else if (lclass == 12) return 0.96; // Ds2*
    */
    return 1.00;
}


// Old BF weights

/*
float SemiLepBFs(int lclass, int mom_lund) {
    if (lclass == 2) {
        if (abs(mom_lund) == 521) return 0.96; // D0
        else return 1.02; // D+
    } else if (lclass == 1) {
        if (abs(mom_lund) == 521) return 0.98; // D*0
        else return 0.92; // D*+
    } else if (lclass == 3) return 1.00; // D1
    else if (lclass == 4) return 1.34; // D2
    else if (lclass == 5) return 1.30; // D1'
    else if (lclass == 6) return 0.62; // D*0
    return 1.00;
}
*/

Int_t cal_lclass( Int_t semi, Int_t gm_ddst, Int_t lund ){
  Int_t lclass = 0;
  if( semi==1 || semi==2 ){
    if     ( gm_ddst==1 ) lclass = 2; // D
    else if( gm_ddst==2 ) lclass = 1; // D*
    else if( gm_ddst==3 && ( abs(lund)==10411 || abs(lund)==10421 ) ) lclass = 6; // D** (D*0)
    else if( gm_ddst==3 && ( abs(lund)==20413 || abs(lund)==20423 ) ) lclass = 5; // D** (D1')
    else if( gm_ddst==3 && ( abs(lund)==10413 || abs(lund)==10423 ) ) lclass = 3; // D** (D1 )
    else if( gm_ddst==3 && ( abs(lund)==  415 || abs(lund)==  425 ) ) lclass = 4; // D** (D2 )
  }
  return lclass;
}


Int_t cal_lclass_for_syst( Int_t semi, Int_t gm_ddst, Int_t lund ){
  Int_t lclass = 0;
  if( semi==1 || semi==2 ){
    if     ( gm_ddst==3 && ( abs(lund)==10411 || abs(lund)==10421 ) ) lclass = 6; // D** (D*0)
    else if( gm_ddst==3 && ( abs(lund)==20413 || abs(lund)==20423 ) ) lclass = 5; // D** (D1')
    else if( gm_ddst==3 && ( abs(lund)==10413 || abs(lund)==10423 ) ) lclass = 3; // D** (D1 )
    else if( gm_ddst==3 && ( abs(lund)==  415 || abs(lund)==  425 ) ) lclass = 4; // D** (D2 )
    else if( gm_ddst==3 && ( abs(lund)==100411|| abs(lund)==100421) ) lclass = 7; // D** (D(2S))
    else if( gm_ddst==3 && ( abs(lund)==100413|| abs(lund)==100423) ) lclass = 8; // D** (D*(2S))
  }
  return lclass;
}
