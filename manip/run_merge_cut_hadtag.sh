#!/bin/csh -f

set indir  = "~/dstrtaunu/modules/dstrtaunu/hbk_hadtag/"
set outdir = "~/dstrtaunu/modules/dstrtaunu/hbk_hadtag/merge_noremcut/"

set list_exp = `awk '{print $1}' ~/script/nBB2.txt`


# for RD
foreach exp ($list_exp)
  echo "./exe_merge_cut_hadtag.sh   $indir $outdir $exp 0 rd" >> tmp.list
end

set list_stream = "0 1 2 3 4 5" # 0 1 2 3 4 5 6 7 8 9
set list_type = "uds charm mixed charged" # uds charm mixed charged rd

# for gMC
if(1) then
foreach exp ($list_exp)
  foreach stream ($list_stream)
     foreach type ($list_type)
        echo "./exe_merge_cut_hadtag.sh $indir $outdir $exp $stream $type" >> tmp.list
     end
   end
end
endif

