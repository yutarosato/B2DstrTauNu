#! /bin/tcsh -f

make || exit

# TOTAL
bsub -q s ./exe_fit_deltam_reso.sh  421  40000 81
bsub -q s ./exe_fit_deltam_reso.sh  411  40000 81

# D0
bsub -q s ./exe_fit_deltam_reso.sh  101 40000 81
bsub -q s ./exe_fit_deltam_reso.sh  301 40000 81
bsub -q s ./exe_fit_deltam_reso.sh 1101 40000 81
bsub -q s ./exe_fit_deltam_reso.sh 1210 40000 81
bsub -q s ./exe_fit_deltam_reso.sh  210 40000 81
bsub -q s ./exe_fit_deltam_reso.sh 1200 40000 81
bsub -q s ./exe_fit_deltam_reso.sh 1010 40000 81
bsub -q s ./exe_fit_deltam_reso.sh   12 40000 81
bsub -q s ./exe_fit_deltam_reso.sh    2 40000 81
bsub -q s ./exe_fit_deltam_reso.sh  200 40000 81

# D+
bsub -q s ./exe_fit_deltam_reso.sh  201 40000 81 # NOT CONVERGED DUE TO LESS SIGNAL
bsub -q s ./exe_fit_deltam_reso.sh 1110 40000 81
bsub -q s ./exe_fit_deltam_reso.sh  310 40000 81
bsub -q s ./exe_fit_deltam_reso.sh  110 40000 81
bsub -q s ./exe_fit_deltam_reso.sh  102 40000 81


exit
psmerge -odeltam_reso.ps pic/dm1_*.ps && ps2pdf deltam_reso.ps pic/deltam_reso.pdf && rm -f deltam_reso.ps
