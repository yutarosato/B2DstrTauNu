#! /bin/tcsh -f

make draws_2hdmII || exit
rm -f dat/tmp_2hdmII_*.dat

foreach LEP( 0 1 10 )
foreach PAR( 0p0 0p1 0p2 0p3 0p4 0p5 0p6 0p7 0p8 0p9 1p0 )
  echo -n $PAR | sed 's|p|.|' >> dat/tmp_2hdmII_lep${LEP}.dat
  grep HIGEEEE ../nominal_fit/nominal_log_fit/20160222_npcurve/2hdmII/*/*.log | grep $PAR | grep "lep${LEP}lep" | awk '{print " "$4" "$5}' >> dat/tmp_2hdmII_lep${LEP}.dat
end
end

./draws_2hdmII
