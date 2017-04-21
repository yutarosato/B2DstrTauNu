#!/bin/csh -f

(./makepdf_syst ${1} ${2} ${3} ${4} ${5} > log/makepdf_${1}_${2}_${3}_${4}_lep_${5}.log ) >>& error.log
