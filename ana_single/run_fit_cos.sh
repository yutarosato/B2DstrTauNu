#! /bin/tcsh -f

make || exit


bsub -q s ./exe_fit_cos.sh 1200 1
bsub -q s ./exe_fit_cos.sh 1200 10

foreach LEP ( 1 10 )
  # D0
  #bsub -q sx ./exe_fit_cos.sh  101 $LEP
  #bsub -q sx ./exe_fit_cos.sh  301 $LEP
  #bsub -q sx ./exe_fit_cos.sh 1101 $LEP
  #bsub -q sx ./exe_fit_cos.sh 1210 $LEP
  #bsub -q sx ./exe_fit_cos.sh  210 $LEP
  #bsub -q sx ./exe_fit_cos.sh 1200 $LEP
  #bsub -q sx ./exe_fit_cos.sh 1010 $LEP
  #bsub -q sx ./exe_fit_cos.sh   12 $LEP
  #bsub -q sx ./exe_fit_cos.sh    2 $LEP
  #bsub -q sx ./exe_fit_cos.sh  200 $LEP
# D+
  #bsub -q sx ./exe_fit_cos.sh  201 $LEP
  #bsub -q sx ./exe_fit_cos.sh 1110 $LEP
  #bsub -q sx ./exe_fit_cos.sh  310 $LEP
  #bsub -q sx ./exe_fit_cos.sh  110 $LEP
  #bsub -q sx ./exe_fit_cos.sh  102 $LEP
end
