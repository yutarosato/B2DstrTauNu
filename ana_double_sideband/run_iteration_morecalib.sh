#! /bin/tcsh -f

make fit_dmass_deltam_morecalib || exit

#rm -f tmp.dat
#./run_fit_morecalib.sh

################################
#foreach iter (`seq 15`)
#  echo "D([sig,sig]) : ${iter}"
#  ~/script/wait_job
#  ./run_tag_eff_morecalib.sh 1
#end
#exit

################################
#foreach iter (`seq 15`)
#  echo "D([sig,sig],[bkg,bkg]) : ${iter}"
#  ~/script/wait_job
#  ./run_tag_eff_morecalib.sh 1 0 1
#end
#exit

################################
#foreach iter (`seq 20`)
#  echo "D([sig,sig],[sig,bkg],[bkg,bkg]) : ${iter}"
#  ~/script/wait_job
#  ./run_tag_eff_morecalib.sh 1 1 1
#end
#exit

################################
foreach iter (`seq 20`)
  echo "D([sig,sig],[sig,bkg],[bkg,bkg]) D*([sig,sig]): ${iter}"
  ~/script/wait_job
  ./run_tag_eff_morecalib.sh 0 0 0 1
end
exit
