#! /bin/tcsh -f

make kinematic || exit

#bsub -q s ./kinematic 0p0       "../npmc/new_table/2hdmII/dstrtaunu_dpi_lep_12_all/est_weight.root"
#bsub -q s ./kinematic 0p7       "../npmc/new_table/2hdmII/dstrtaunu_dpi_lep_12_all/est_weight.root"
#bsub -q s ./kinematic 1p0       "../npmc/new_table/2hdmII/dstrtaunu_dpi_lep_12_all/est_weight.root"

#bsub -q s ./kinematic R2_m0p150 "../npmc/new_table/R2LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"
#bsub -q s ./kinematic R2_m0p040 "../npmc/new_table/R2LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"
#bsub -q s ./kinematic R2_m0p030 "../npmc/new_table/R2LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"
#bsub -q s ./kinematic R2_0p340 "../npmc/new_table/R2LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"
#bsub -q s ./kinematic R2_0p360 "../npmc/new_table/R2LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"
#bsub -q s ./kinematic R2_0p400 "../npmc/new_table/R2LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"

#bsub -q s ./kinematic S1_m0p150 "../npmc/new_table/S1LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"
#bsub -q s ./kinematic S1_m0p040 "../npmc/new_table/S1LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"
#bsub -q s ./kinematic S1_0p260 "../npmc/new_table/S1LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"
#bsub -q s ./kinematic S1_0p400 "../npmc/new_table/S1LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"

#bsub -q s ./kinematic OP_V1_m2p10 "../npmc/new_table/OPV1/dstrtaunu_dpi_lep_12_all/est_weight.root"
#bsub -q s ./kinematic OP_V2_1p88  "../npmc/new_table/OPV2/dstrtaunu_dpi_lep_12_all/est_weight.root"
#bsub -q s ./kinematic OP_S1_1p05  "../npmc/new_table/OPS1/dstrtaunu_dpi_lep_12_all/est_weight.root"

bsub -q s ./kinematic OP_T_0p36  "../npmc/new_table/OPT/dstrtaunu_dpi_lep_12_all/est_weight.root"
