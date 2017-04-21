#! /bin/tcsh -f

make makepdf || exit

foreach LEP( 0 1 10 )
foreach PAR( 0p0 )
  bsub -q e ./exe_makepdf.sh 0 $PAR $LEP # other
  bsub -q e ./exe_makepdf.sh 1 $PAR $LEP # sig
  bsub -q e ./exe_makepdf.sh 2 $PAR $LEP # nor
  bsub -q e ./exe_makepdf.sh 3 $PAR $LEP # dstst
  bsub -q e ./exe_makepdf.sh 4 $PAR $LEP # doubled
  bsub -q e ./exe_makepdf.sh 5 $PAR $LEP # fake_other
  bsub -q e ./exe_makepdf.sh 6 $PAR $LEP # fake_sig
  bsub -q e ./exe_makepdf.sh 7 $PAR $LEP # fake_nor
  bsub -q e ./exe_makepdf.sh 8 $PAR $LEP # fake_dstst
  bsub -q e ./exe_makepdf.sh 9 $PAR $LEP # fake_doubled

end
end
#exit

wait_job
#exit

psmerge -omakepdf.ps pic/makepdf_*.ps && ps2pdf makepdf.ps pic/makepdf.pdf && rm -f makepdf.ps
