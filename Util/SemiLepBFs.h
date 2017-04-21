// Scale factors for MC branching fractions
// lclass = class of semileptonic decay
// mom_lund = pdg code of the lepton mother

#include "const.h"

float SemiLepBFs(int lclass, int mom_lund);
Int_t cal_lclass         ( Int_t semi, Int_t gm_ddst, Int_t lund ); // 1(D*), 2(D), 3-6(D**) [3(D1), 4(D2), 5(D1'), 6(D*0)]
Int_t cal_lclass_for_syst( Int_t semi, Int_t gm_ddst, Int_t lund ); //              3-8(D**) [3(D1), 4(D2), 5(D1'), 6(D*0), 7(D(2S)), 8(D*(2S))]
