#!/bin/csh -f

set treename = "h15" # double
#foreach TYPE( uds charm mixed charged DssMC DssMC2 )
#foreach TYPE( uds charm mixed charged )
#foreach TYPE( DssMC )
#foreach TYPE( 0p0 0p5 )
foreach TYPE( 0p0 )
  set  indir = "~/dstrtaunu/modules/dstrtaunu/hbk/${TYPE}/*.root"
  set outdir = "~/dstrtaunu/modules/dstrtaunu/hbk/${TYPE}_weight"
  foreach FILE($indir)
    echo "./exe_cal_weight.sh ${treename} ${FILE} ${outdir}" >> tmp.list
  end
end




#set treename = "h17" # single
#foreach TYPE( uds charm mixed charged )
#  set  indir = "~/dstrtaunu/modules/dstrtaunu/hbk_single/store/hbk20/${TYPE}/gMC_*"
#  set outdir = "~/dstrtaunu/modules/dstrtaunu/hbk_single/${TYPE}_weight"
#  foreach FILE($indir)
#    echo "./exe_cal_weight.sh ${treename} ${FILE} ${outdir}" >> tmp.list
#  end
#end
