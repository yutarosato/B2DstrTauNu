#!/bin/csh -f

(./est_weight ${1} ${2} ${3} > log/est_weight_${1}.log ) >>& error.log
