#!/bin/csh -f

(./makepdf ${1} ${2} ${3} > log/makepdf_${1}_lep_${2}_${3}.log ) >>& error.log
