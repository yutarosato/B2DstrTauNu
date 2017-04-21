#!/bin/csh -f

#set tag = "_cut"
set tag = "_nocoscut"
#set tag = "_noremcut"
#set tag = "_nodmcut"
#set tag = "_nomddmcut"
#set tag = "_noremcut_nodmcut"

#foreach TYPE ( DssMC )
#foreach TYPE ( 0p0 0p5 )
foreach TYPE ( 0p0 )
   set indir  = "~/dstrtaunu/modules/dstrtaunu/hbk/${TYPE}_weight_nb"
   set outdir = ${indir}${tag}"/"
   foreach FILE ( `\ls ${indir}/*.root` )
     echo "./exe_through_cut.sh  $FILE $outdir" >> tmp.list.sig
   end
end
