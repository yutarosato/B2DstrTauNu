#!/bin/csh -f

set infile = $1
set TAG    = $2
set outdir = $3
######################################################################################################
set fl_mode = '0'
set type    = 'nor'

mkdir -p $outdir
( ~/dstrtaunu/ana/NB/nb_expert ${infile} ${outdir} ${fl_mode} ${TAG} ${type} >> log/log_expert.log ) >>& error.log
