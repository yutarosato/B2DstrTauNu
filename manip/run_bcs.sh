#!/bin/csh -f

set tag = "_bcs_vtx2"
set indir = "~/dstrtaunu/modules/dstrtaunu/hbk/"

#foreach TYPE ( DssMC )
#foreach TYPE ( 0p0 0p5 )
foreach TYPE ( 0p0 )
   set outdir = "${indir}/${TYPE}_weight_nb_cut${tag}"
   foreach FILE ( `\ls ${indir}/${TYPE}"_weight_nb_cut/"*.root` )
     echo "./exe_bcs_sigmc_vtx.sh ${FILE} ${outdir}" >> tmp.list
   end
end
exit

set list_exp_bkg = `awk '{print $1}' ~/script/nBB2.txt`
set outdir = "${indir}/merge_cut${tag}"
foreach EXP ($list_exp_bkg)
foreach STREAM (0 1 2 3 4 5)
   echo "./exe_bcs_gmc_vtx.sh $EXP $STREAM uds     ${indir}/merge_cut ${outdir}" >> tmp.list
   echo "./exe_bcs_gmc_vtx.sh $EXP $STREAM charm   ${indir}/merge_cut ${outdir}" >> tmp.list
end
foreach STREAM (0 1 2 3 4 5 6 7 8 9)
   echo "./exe_bcs_gmc_vtx.sh $EXP $STREAM mixed   ${indir}/merge_cut ${outdir}" >> tmp.list
   echo "./exe_bcs_gmc_vtx.sh $EXP $STREAM charged ${indir}/merge_cut ${outdir}" >> tmp.list
end
end
#exit


foreach f(`\ls ${indir}"/merge_cut/RD_"*".root"`)
  echo "./exe_bcs_sigmc_vtx.sh $f ${outdir}" >> tmp.list
end
