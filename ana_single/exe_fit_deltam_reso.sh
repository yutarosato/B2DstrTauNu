#!/bin/csh -f

(./fit_deltam_reso ${1} ${2} ${3} > log/dm1_${1}_${2}_${3}.log ) >>& error.log
