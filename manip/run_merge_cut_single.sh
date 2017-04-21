#!/bin/csh -f

#set indir  = "~/dstrtaunu/modules/dstrtaunu/hbk_single/rd/*.root"
#set outdir = "~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut_loose_D_Dstr_rd/"

#set indir  = "~/dstrtaunu/modules/dstrtaunu/hbk_single/uds_weight/*.root"
#set outdir = "~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut_loose_D_Dstr_uds/"

set indir  = "~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut_FitRange_charged/*.root"
set outdir = "~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut_charged/"

foreach FILE ( ${indir} )
  echo "./exe_merge_cut_single.sh  $FILE $outdir" >> tmp.list
end
exit

set TAG = "FitRange"
foreach TYPE( rd uds charm mixed charged )
  #set indir  = "~/dstrtaunu/modules/dstrtaunu/hbk_single/${TYPE}_weight/*.root"
  #set outdir = "~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut_${TAG}_${TYPE}"
  set indir  = "~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut_${TAG}_${TYPE}/*.root"
  set outdir = "tmp/${TAG}_${TYPE}"
  foreach FILE($indir)
    echo "./exe_merge_cut_single.sh ${FILE} ${outdir}" >> tmp.list
  end
end
