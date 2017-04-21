#!/bin/csh -f

set NAME       = `basename $1`
set TAG        = $2
set outbasedir = $3
######################################################################################################
set fl_mode_out = '0'
set type_out    = 'nor'

mkdir -p $outbasedir
( ./nb_expert $1 ${outbasedir} ${fl_mode_out} ${TAG} ${type_out} >> log_expert.log ) >>& error.log
exit
######################################################################################################
######################################################################################################
set fl_mode_out = '0'
set type_out    = 'nor'
set outdir_out  = "${outbasedir}/hbk_mode${fl_mode_out}_${TAG}_${type_out}/"

mkdir -p $outdir_out
( ./nb_expert $1 ${outdir_out} ${fl_mode_out} ${TAG} ${type_out} >> log_expert.log ) >>& error.log
######################################################################################################
set fl_mode_in  = ${fl_mode_out}
set type_in     = ${type_out}
set outdir_in   = ${outdir_out}

set fl_mode_out = '0'
set type_out    = 'tot'
set outdir_out  = "${outbasedir}/hbk_mode${fl_mode_out}_${TAG}_${type_out}/"

mkdir -p $outdir_out
(./nb_expert  "${outdir_in}${NAME}" ${outdir_out} ${fl_mode_out} ${TAG} ${type_out} >> log_expert.log ) >>& error.log

if( $? == 0 ) rm -f "${outdir_in}${NAME}"
#exit
######################################################################################################
set fl_mode_in  = ${fl_mode_out}
set type_in     = ${type_out}
set outdir_in   = ${outdir_out}

set fl_mode_out = '0'
set type_out    = 'qq' # {qq,bb,tot}
set outdir_out  = "${outbasedir}/hbk_mode${fl_mode_out}_${TAG}_${type_out}/"

mkdir -p $outdir_out
(./nb_expert  "${outdir_in}${NAME}" ${outdir_out} ${fl_mode_out} ${TAG} ${type_out} >> log_expert.log ) >>& error.log

if( $? == 0 ) rm -f "${outdir_in}${NAME}"
######################################################################################################
set fl_mode_in  = ${fl_mode_out}
set type_in     = ${type_out}
set outdir_in   = ${outdir_out}

set fl_mode_out = '0'
set type_out    = 'bb' # {qq,bb,tot}
set outdir_out  = "${outbasedir}/hbk_mode${fl_mode_out}_${TAG}_${type_out}/"

mkdir -p $outdir_out
(./nb_expert  "${outdir_in}${NAME}" ${outdir_out} ${fl_mode_out} ${TAG} ${type_out} >> log_expert.log ) >>& error.log

if( $? == 0 ) rm -f "${outdir_in}${NAME}"
######################################################################################################
