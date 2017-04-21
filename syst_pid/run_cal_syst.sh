#! /bin/tcsh -f

make || exit

bsub -q e  ./exe_syst_lep.sh
#bsub -q e  ./exe_syst_kpi.sh
#bsub -q sx ./exe_syst_ks.sh
#bsub -q sx ./exe_syst_pi0.sh


