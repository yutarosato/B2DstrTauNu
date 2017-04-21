#!/bin/csh -f

(./fit_dmass_deltam_morecalib ${1} ${2} ${3} ${4} ${5} ${6} ${7} ${8} ${9} ${10} > log/dmass_deltam_morecalib_${1}_${2}.log ) >>& error.log
