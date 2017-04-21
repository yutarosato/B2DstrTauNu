#ifndef DRAWS_SYST_H
#define DRAWS_SYST_H

#include "codes/kid_eff_06.h"
#include "codes/lid_syst_09.h"
#include "codes/Ks_eff.h"
#include "codes/pi0_eff.h"

const Int_t nsvd   = 2;
const Int_t nlep   = 3;

Double_t lumi_tot   = 140.909 +159.856 +187.850 +216.877;
Double_t lumi_svd1  = 140.909;
Double_t lumi_svd2  = (159.856 +187.850 +216.877);
Double_t lumi_ee[2] = {140.909, 159.856 +187.850 +216.877}; // svd1, svd2
Double_t lumi_mm[4] = {140.909, 159.856, 187.850, 216.877}; // svd1, e31-39&45a, e41-49 except 45a, e51-65

#endif
