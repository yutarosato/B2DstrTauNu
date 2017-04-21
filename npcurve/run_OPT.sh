#! /bin/tcsh -f

set OPE = "T"
make draws_OP${OPE} || exit
rm -f dat/tmp_OP${OPE}_*.dat


foreach LEP( 0 1 10 )
foreach PAR( m0p15 m0p07 0p00 0p07 0p15 0p22 0p30 0p37 0p45 )
  echo -n $PAR | sed 's|p|.|' | sed 's|m|-|' >> dat/tmp_OP${OPE}_lep${LEP}.dat
  grep HIGEEEE ../nominal_fit/nominal_log_fit/20160317/OP${OPE}/*/*.log | grep "\/$PAR" | grep "lep${LEP}lep" | awk '{print " "$4" "$5}' >> dat/tmp_OP${OPE}_lep${LEP}.dat
end
end

./draws_OP${OPE}
