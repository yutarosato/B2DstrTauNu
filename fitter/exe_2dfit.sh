#!/bin/csh -f

(./2dfit ${1} ${2} ${3} ${4} > log/2dfit_${1}_${2}_${3}_${4}.log ) >>& error.log
