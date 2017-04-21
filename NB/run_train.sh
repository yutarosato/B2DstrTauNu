#!/bin/csh -f

###############################################
set indir_sig = "../../modules/dstrtaunu/hbk/store/hbk8/sig_kpi_through_cut/"
set indir_nor = "../../modules/dstrtaunu/hbk/store/hbk8/nor_kpi_through_cut/"
set indir_bkg = "../../modules/dstrtaunu/hbk/store/hbk8_merge_cut/"

#set setname_sig   = 'A-C'
#set setname_nor   = 'A-C'

#set setname_sig   = 'D-F'
#set setname_nor   = 'D-F'

set setname_sig   = 'A-H'
set setname_nor   = 'A-H'



set stream    = '2-5'

#set tag       = 'test'
#set type      = 'tot' # tot, qq, bb
#set fl_mode = '0'
set tag     = $1
set type    = $2
set fl_mode = $3
###############################################
     
echo $NEUROBAYES
echo '--- build executable ---'
make || exit
echo '--- start training ---'
./nb_training ${indir_sig} ${indir_nor} ${indir_bkg} ${setname_sig} ${setname_nor} ${stream} ${fl_mode} ${tag} ${type} | tee log/log_nb_training_mode${fl_mode}_${tag}_${type}.log
echo '--- create analysis plots ---'
( root -b -q -l $NEUROBAYES/external/analysis.C'("ahist.txt")'                        >log/log_analysis_mode${fl_mode}_${tag}_${type}.log        ) >& log/log_analysis_mode${fl_mode}_${tag}_${type}.err
( root -b -q -l $NEUROBAYES/external/analysis.C'("ahist.txt","analysis_sorted.ps",1)' >log/log_analysis_mode${fl_mode}_${tag}_${type}_sorted.log ) >& log/log_analysis_mode${fl_mode}_${tag}_${type}_sorted.err

echo '--- view results ---'
mv ahist.txt          pic/ahist_mode${fl_mode}_${tag}_${type}.txt
mv ahist.root         pic/ahist_mode${fl_mode}_${tag}_${type}.root
mv analysis.ps        pic/analysis_mode${fl_mode}_${tag}_${type}.ps
mv analysis_sorted.ps pic/analysis_mode${fl_mode}_${tag}_${type}_sorted.ps
#gv -noantialias pic/analysis_mode${fl_mode}_${tag}_${type}.ps        &
#gv -noantialias pic/analysis_mode${fl_mode}_${tag}_${type}_sorted.ps &

