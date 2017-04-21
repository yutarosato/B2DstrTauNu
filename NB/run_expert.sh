#!/bin/csh -f

make nb_expert || exit

set tag     = "test13"

#foreach type (uds charm mixed charged rd rd2 DssMC DssMC2)
#foreach type (0p0 0p5)
foreach type (0p0)

set indir  = "../../modules/dstrtaunu/hbk/${type}_weight/*.root"
set outdir = "../../modules/dstrtaunu/hbk/${type}_weight_nb"
  
set count=0

foreach f($indir)
     @ count++
end
 echo $count "files exists"

echo "execute expert(y/n) ?"
#set kakunin = $<
set kakunin = 'y'
@ count=0

if( $kakunin == 'y') then
  foreach f ($indir)
    @ count++
    echo "./exe_nb_expert.sh $f $tag $outdir" >> tmp.list
   end
else
    echo 'canceled'
endif

end
