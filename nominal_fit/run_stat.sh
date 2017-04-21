#! /bin/tcsh -f

make convolution_rdstr || exit
make convolution_nsig  || exit

foreach LEP (0)
  grep -h STATSIGNIFICANCE 20160126_stat/rdstr_stat/*/*_${LEP}_.log | tee tmp_stat_rdstr_lep${LEP}.dat
end
./convolution_rdstr

#foreach LEP (0)
#  grep -h STATSIGNIFICANCE 20160126_stat/nsig_stat/*/*_${LEP}_.log | tee tmp_stat_nsig_lep${LEP}.dat
#end
#./convolution_nsig
