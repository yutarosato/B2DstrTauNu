#!/bin/csh -f

(cd ~/dstrtaunu/ana/NB; make)
set TAG = "test13"

foreach TYPE( uds charm mixed charged rd )
  set  indir = "~/dstrtaunu/modules/skim_dstrtaunu/hbk/hbk20/${TYPE}_weight/*.root"
  set outdir = "~/dstrtaunu/modules/skim_dstrtaunu/hbk/hbk20/${TYPE}_weight_nb"
  foreach FILE ($indir)
    echo "./exe_nb.sh ${FILE} ${TAG} $outdir" >> tmp.list
  end
end

