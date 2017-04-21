#! /bin/tcsh -f

make || exit
# TOTAL
bsub -q e ./exe_fit_dmass_reso.sh  421  30000 1
bsub -q e ./exe_fit_dmass_reso.sh  411  30000 1

# D0
bsub -q e ./exe_fit_dmass_reso.sh  101    30 1
bsub -q e ./exe_fit_dmass_reso.sh  301    30 1
bsub -q e ./exe_fit_dmass_reso.sh 1101 30000 2
bsub -q e ./exe_fit_dmass_reso.sh 1210 30000 1
bsub -q e ./exe_fit_dmass_reso.sh  210    30 1
bsub -q e ./exe_fit_dmass_reso.sh 1200 30000 1
bsub -q e ./exe_fit_dmass_reso.sh 1010 30000 1
bsub -q e ./exe_fit_dmass_reso.sh   12    30 1
bsub -q e ./exe_fit_dmass_reso.sh    2    30 1
bsub -q e ./exe_fit_dmass_reso.sh  200    30 1

# D+
bsub -q e ./exe_fit_dmass_reso.sh  201 30000 1
bsub -q e ./exe_fit_dmass_reso.sh 1110 30000 1
bsub -q e ./exe_fit_dmass_reso.sh  310 30000 1
bsub -q e ./exe_fit_dmass_reso.sh  110 30000 1
bsub -q e ./exe_fit_dmass_reso.sh  102 30000 1

