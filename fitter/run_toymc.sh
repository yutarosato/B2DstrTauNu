#! /bin/tcsh -f

make 2dfit      || exit
make toymc_test || exit

set ITERATION = 500

foreach NEXP (`seq 10 10 200`)
  #bsub -q s ./exe_2dfit.sh $NEXP -1 $ITERATION
  bsub -q s ./exe_2dfit.sh $NEXP -1 0 $ITERATION
end


wait_job
#exit

psmerge -o2dfit_fit.ps  pic/2dfit_*_fit.ps  && ps2pdf 2dfit_fit.ps  pic/2dfit_fit.pdf  && rm -f 2dfit_fit.ps
psmerge -o2dfit_toy.ps  pic/2dfit_*_toy.ps  && ps2pdf 2dfit_toy.ps  pic/2dfit_toy.pdf  && rm -f 2dfit_toy.ps
psmerge -o2dfit_toy2.ps pic/2dfit_*_toy2.ps && ps2pdf 2dfit_toy2.ps pic/2dfit_toy2.pdf && rm -f 2dfit_toy2.ps

foreach CTGRY (sig nor faked dstst doubled other)
  grep -h HOGEEEE log/2dfit_*.log | grep $CTGRY > log/toymctest_${CTGRY}.dat
end
  grep -h HUGEEEE log/2dfit_*.log > log/toymctest_sensitivity.dat

./toymc_test
