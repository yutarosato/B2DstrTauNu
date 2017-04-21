#!/bin/csh -f

(./makepdf_syst ${1} ${2} ${3} > log/makepdf_${1}_${2}_lep_${3}.log ) >>& error.log
