#! /bin/tcsh -f

set OPE = "V2"
make draws_OP${OPE} || exit
rm -f dat/tmp_OP${OPE}_*.dat


foreach LEP( 0 1 10 )
foreach PAR( m0p50 0p00 0p50 1p00 1p50 1p88 2p00 2p50 )
  echo -n $PAR | sed 's|p|.|' | sed 's|m|-|' >> dat/tmp_OP${OPE}_lep${LEP}.dat
  grep HIGEEEE ../nominal_fit/nominal_log_fit/20160317/OP${OPE}/*/*.log | grep "\/$PAR" | grep "lep${LEP}lep" | awk '{print " "$4" "$5}' >> dat/tmp_OP${OPE}_lep${LEP}.dat
end
end

./draws_OP${OPE}
