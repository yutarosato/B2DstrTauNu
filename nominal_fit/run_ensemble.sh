#! /bin/tcsh -f

make 2dfit         || exit
make 2dfit_paper   || exit
make 2dfit_stat    || exit
make ensemble_test || exit

set NEXP = 100

foreach LEP (0 1 10)
#foreach LEP (0)
#foreach STREAMNO (`seq 0 1 9`)
#foreach STREAMNO (0)
foreach STREAMNO (-999) # Data
  bsub -q s ./exe_2dfit.sh $NEXP $STREAMNO $LEP
  #bsub -q s ./exe_2dfit_stat.sh $NEXP $STREAMNO $LEP
end
end

wait_job
exit


foreach LEP (0 1 10)
  psmerge -o2dfit_fit_lep${LEP}.ps  pic/2dfit_*lep${LEP}_*fit.ps  && ps2pdf 2dfit_fit_lep${LEP}.ps  pic/2dfit_fit_lep${LEP}.pdf  && rm -f 2dfit_fit_lep${LEP}.ps
  grep -h HIGEEEE log/2dfit_*.log | grep lep${LEP}lep > log/ensemble_lep${LEP}.dat
#  #./ensemble_test $LEP
end

./ensemble_test 0
#./ensemble_test 1
#./ensemble_test 10

