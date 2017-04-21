#!/bin/csh -f

(./fit_dmass_reso ${1} ${2} ${3} > log/d1_m_${1}_${2}_${3}.log ) >>& error.log
