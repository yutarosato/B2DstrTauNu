#! /bin/tcsh -f

make draws_R2LQ || exit
rm -f dat/tmp_R2LQ_*.dat

foreach LEP( 0 1 10 )
foreach PAR( m0p150 m0p100 m0p040 0p000 0p090 0p180 0p260 0p340 0p400 )
  echo -n $PAR | sed 's|p|.|' | sed 's|m|-|' >> dat/tmp_R2LQ_lep${LEP}.dat
  grep HIGEEEE ../nominal_fit/nominal_log_fit/20160222_npcurve/R2LQ/*/*.log | grep "\/$PAR" | grep "lep${LEP}lep" | awk '{print " "$4" "$5}' >> dat/tmp_R2LQ_lep${LEP}.dat
end
end

./draws_R2LQ
