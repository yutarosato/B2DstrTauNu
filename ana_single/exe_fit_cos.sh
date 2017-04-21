#!/bin/csh -f

(./fit_cos ${1} ${2} > log/cosdl1_${1}_${2}.log ) >>& error.log
