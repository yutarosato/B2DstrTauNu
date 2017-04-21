#! /bin/tcsh -f

make makepdf || exit

mkdir -p pdf;

foreach LEP( 0 1 10 )
foreach PAR( 0p0 )
#  bsub -q e ./exe_makepdf.sh 0 $PAR $LEP # other
#  bsub -q e ./exe_makepdf.sh 1 $PAR $LEP # sig
#  bsub -q e ./exe_makepdf.sh 2 $PAR $LEP # nor
  bsub -q e ./exe_makepdf.sh 3 $PAR $LEP # dstst
#  bsub -q e ./exe_makepdf.sh 4 $PAR $LEP # doubled
#  bsub -q e ./exe_makepdf.sh 5 $PAR $LEP # fake_other
#  bsub -q e ./exe_makepdf.sh 6 $PAR $LEP # fake_sig
#  bsub -q e ./exe_makepdf.sh 7 $PAR $LEP # fake_nor
  bsub -q e ./exe_makepdf.sh 8 $PAR $LEP # fake_dstst
#  bsub -q e ./exe_makepdf.sh 9 $PAR $LEP # fake_doubled
end
end
exit


foreach LEP( 0 1 10 )
#foreach PAR( 0p1 0p2 0p3 0p4 0p5 0p6 0p7 0p8 0p9 1p0 ) # should change L.8 (weight_table) in makepdf.cpp
#foreach PAR( R2_0p000 R2_m0p150 R2_m0p100 R2_m0p040 R2_0p090 R2_0p180 R2_0p260 R2_0p340 R2_0p400 )
#foreach PAR( S1_0p000 S1_m0p150 S1_m0p100 S1_m0p040 S1_0p090 S1_0p180 S1_0p260 S1_0p340 S1_0p400 )
#foreach PAR( R2_m0p030 R2_0p360 )
#foreach PAR( S1_m0p030 S1_0p360 )
#foreach PAR( OP_V1_m2p10 )
#foreach PAR( OP_V2_1p88 )
#foreach PAR( OP_S1_1p05 )
#foreach PAR( OP_S1_0p00 OP_S1_m5p00 OP_S1_m4p00 OP_S1_m3p00 OP_S1_m2p00 OP_S1_m1p00 OP_S1_1p00  OP_S1_1p05 OP_S1_2p00 OP_S1_3p00 )
#foreach PAR( OP_S2_0p00 OP_S2_m3p00 OP_S2_m2p00 OP_S2_m1p00 OP_S2_1p00  OP_S2_2p00  OP_S2_3p00  OP_S2_4p00 OP_S2_5p00            )
#foreach PAR( OP_V1_0p00 OP_V1_m2p50 OP_V1_m2p10 OP_V1_m2p00 OP_V1_m1p50 OP_V1_m1p00 OP_V1_m0p50 OP_V1_0p50                       )
#foreach PAR( OP_V2_0p00 OP_V2_m0p50 OP_V2_0p50  OP_V2_1p00  OP_V2_1p50  OP_V2_1p88  OP_V2_2p00  OP_V2_2p50                       )
#foreach PAR( OP_T_0p00  OP_T_m0p15  OP_T_m0p07  OP_T_0p07   OP_T_0p15   OP_T_0p22   OP_T_0p30   OP_T_0p37  OP_T_0p45             )
  foreach PAR( OP_T_0p36 )
  bsub -q e ./exe_makepdf.sh 1 $PAR $LEP # sig
end
end
exit


wait_job
#exit

psmerge -omakepdf.ps pdf/makepdf_*.ps && ps2pdf makepdf.ps pdf/makepdf.pdf && rm -f makepdf.ps
