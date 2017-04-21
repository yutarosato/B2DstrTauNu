#!/bin/csh -f

###################################################
# [NOTE] must modify treename in src/nb_expert.cpp
###################################################

make nb_expert || exit

set tag = "test13"

foreach PAR ( 0p0 0p1 0p2 0p3 0p4 0p5 0p6 0p7 0p8 0p9 1p0 )
    set indir  = "../../modules/np_dstrtaunu_gen/hbk/${PAR}_double/*.root"
    set outdir = "../../modules/np_dstrtaunu_gen/hbk/${PAR}_double_nb/"
  foreach f ($indir)
    echo "./exe_nb_expert.sh $f $tag $outdir" >> tmp.list
  end
end

