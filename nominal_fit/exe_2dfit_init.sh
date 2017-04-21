#!/bin/csh -f
# $5 : fl_par_dt
# $6 : weight_table
(./2dfit ${1} ${2} ${3} ${4} ${5} ${6} > log/2dfit_${1}_${2}_${3}_${4}_${5}.log ) >>& error.log
