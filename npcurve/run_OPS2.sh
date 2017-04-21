#! /bin/tcsh -f

set OPE = "S2"
make draws_OP${OPE} || exit
rm -f dat/tmp_OP${OPE}_*.dat


foreach LEP( 0 1 10 )
foreach PAR( m3p00 m2p00 m1p00 1p00 0p00 2p00 3p00 4p00 5p00 )
  echo -n $PAR | sed 's|p|.|' | sed 's|m|-|' >> dat/tmp_OP${OPE}_lep${LEP}.dat
  grep HIGEEEE ../nominal_fit/nominal_log_fit/20160317/OP${OPE}/*/*.log | grep "\/$PAR" | grep "lep${LEP}lep" | awk '{print " "$4" "$5}' >> dat/tmp_OP${OPE}_lep${LEP}.dat
end
end

./draws_OP${OPE}
