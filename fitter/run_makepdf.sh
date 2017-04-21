#! /bin/tcsh -f

make makepdf || exit

foreach LEP( 0 1 10 )
foreach PAR( 0p0 )
  bsub -q e ./exe_makepdf.sh 0 $PAR $LEP # faked
  bsub -q e ./exe_makepdf.sh 1 $PAR $LEP # sig
  bsub -q e ./exe_makepdf.sh 2 $PAR $LEP # nor
  bsub -q e ./exe_makepdf.sh 3 $PAR $LEP # doubled
  bsub -q e ./exe_makepdf.sh 4 $PAR $LEP # other
  bsub -q e ./exe_makepdf.sh 5 $PAR $LEP # dstst
end
end
#exit


foreach LEP( 0 1 10 )
foreach PAR( 0p1 0p2 0p3 0p4 0p5 0p6 0p7 0p8 0p9 1p0 )
  bsub -q e ./exe_makepdf.sh 1 $PAR $LEP # sig
end
end
#exit


wait_job
#exit

psmerge -omakepdf.ps pic/makepdf_*.ps && ps2pdf makepdf.ps pic/makepdf.pdf && rm -f makepdf.ps
