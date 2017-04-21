#! /bin/tcsh -f

make 2dfit         || exit

set NEXP = 100

foreach LEP (0 1 10)
#foreach LEP (0)
foreach STREAMNO (0)

#  set WEIGHT = "../npmc/new_table/2hdmII/dstrtaunu_dpi_lep_12_all/est_weight.root"
#  foreach PARAM (0p0 0p1 0p2 0p3 0p4 0p5 0p6 0p7 0p8 0p9 1p0)
#    bsub -q s ./exe_2dfit_init.sh $NEXP $STREAMNO $LEP 0 $PARAM $WEIGHT
#  end

#  set WEIGHT = "../npmc/new_table/R2LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"
#  foreach PARAM (R2_m0p150 R2_m0p100 R2_m0p040 R2_0p000 R2_0p090 R2_0p180 R2_0p260 R2_0p340 R2_0p400)
#  foreach PARAM (R2_m0p030 R2_0p360)
#  foreach PARAM (R2_m0p150 R2_m0p100 R2_m0p040 R2_0p000 R2_0p090 R2_0p180 R2_0p260 R2_0p340 R2_0p400 R2_m0p030 R2_0p360)
#    bsub -q s ./exe_2dfit_init.sh $NEXP $STREAMNO $LEP 0 $PARAM $WEIGHT
#  end

#  set WEIGHT = "../npmc/new_table/S1LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"
#  foreach PARAM (S1_m0p150 S1_m0p100 S1_m0p040 S1_0p000 S1_0p090 S1_0p180 S1_0p260 S1_0p340 S1_0p400)
#  foreach PARAM (S1_m0p030 S1_0p360)
#  foreach PARAM (S1_m0p150 S1_m0p100 S1_m0p040 S1_0p000 S1_0p090 S1_0p180 S1_0p260 S1_0p340 S1_0p400 S1_m0p030 S1_0p360)
#    bsub -q s ./exe_2dfit_init.sh $NEXP $STREAMNO $LEP 0 $PARAM $WEIGHT
#  end



#  set WEIGHT = "../npmc/new_table/OPS1/dstrtaunu_dpi_lep_12_all/est_weight.root"
#  foreach PARAM (OP_S1_0p00 OP_S1_m5p00 OP_S1_m4p00 OP_S1_m3p00 OP_S1_m2p00 OP_S1_m1p00 OP_S1_1p00 OP_S1_1p05 OP_S1_2p00 OP_S1_3p00)
#    bsub -q s ./exe_2dfit_init.sh $NEXP $STREAMNO $LEP 0 $PARAM $WEIGHT
#  end

#  set WEIGHT = "../npmc/new_table/OPS2/dstrtaunu_dpi_lep_12_all/est_weight.root"
#  foreach PARAM (OP_S2_0p00 OP_S2_m3p00 OP_S2_m2p00 OP_S2_m1p00 OP_S2_1p00 OP_S2_2p00 OP_S2_3p00 OP_S2_4p00 OP_S2_5p00)
#    bsub -q s ./exe_2dfit_init.sh $NEXP $STREAMNO $LEP 0 $PARAM $WEIGHT
#  end

#  set WEIGHT = "../npmc/new_table/OPV1/dstrtaunu_dpi_lep_12_all/est_weight.root"
#  foreach PARAM (OP_V1_0p00 OP_V1_m2p50 OP_V1_m2p10 OP_V1_m2p00 OP_V1_m1p50 OP_V1_m1p00 OP_V1_m0p50 OP_V1_0p50)
#    bsub -q s ./exe_2dfit_init.sh $NEXP $STREAMNO $LEP 0 $PARAM $WEIGHT
#  end


#  set WEIGHT = "../npmc/new_table/OPV2/dstrtaunu_dpi_lep_12_all/est_weight.root"
#  foreach PARAM (OP_V2_0p00 OP_V2_m0p50 OP_V2_0p50 OP_V2_1p00 OP_V2_1p50 OP_V2_1p88 OP_V2_2p00 OP_V2_2p50)
#    bsub -q s ./exe_2dfit_init.sh $NEXP $STREAMNO $LEP 0 $PARAM $WEIGHT
#  end

#  set WEIGHT = "../npmc/new_table/OPT/dstrtaunu_dpi_lep_12_all/est_weight.root"
#  foreach PARAM (OP_T_0p00 OP_T_m0p15 OP_T_m0p07 OP_T_0p07 OP_T_0p15 OP_T_0p22 OP_T_0p30 OP_T_0p37 OP_T_0p45)
#  foreach PARAM (OP_T_0p36)
#    bsub -q s ./exe_2dfit_init.sh $NEXP $STREAMNO $LEP 0 $PARAM $WEIGHT
#  end







      

#  set WEIGHT = "../npmc/new_table/OPV1/dstrtaunu_dpi_lep_12_all/est_weight.root"
#  foreach PARAM (OP_V1_m2p10)
#    bsub -q s ./exe_2dfit_init.sh $NEXP $STREAMNO $LEP 0 $PARAM $WEIGHT
#  end

#  set WEIGHT = "../npmc/new_table/OPV2/dstrtaunu_dpi_lep_12_all/est_weight.root"
#  foreach PARAM (OP_V2_1p88)
#    bsub -q s ./exe_2dfit_init.sh $NEXP $STREAMNO $LEP 0 $PARAM $WEIGHT
#  end

#  set WEIGHT = "../npmc/new_table/OPS1/dstrtaunu_dpi_lep_12_all/est_weight.root"
#  foreach PARAM (OP_S1_1p05)
#    bsub -q s ./exe_2dfit_init.sh $NEXP $STREAMNO $LEP 0 $PARAM $WEIGHT
#  end

end
end

#wait_job
#exit



foreach OPE( S1 S2 V1 V2 T)
foreach LEP( 0 1 10 )
foreach FILE( `ls log/2dfit_100_0_${LEP}_0_OP_${OPE}_*`)
  if(${LEP} == 1) then
    echo -n "Double_t init_m[npdf] = { "
  else if(${LEP} == 10) then
    echo -n "Double_t init_e[npdf] = { "
  else
    echo -n "Double_t init_l[npdf] = { "
  endif
  grep -A 10 'INITIAL VALUE' $FILE | awk '{if(NR!=1) printf $4", ";}END{printf "};//"}'
  echo -n "veto D(*)(2S) // sigMC(40 streams) // npmc("
  echo $FILE | cut -d "_" -f7-8 | cut -d "." -f1 | sed 's|$|)|'
#  exit
end
end
end
