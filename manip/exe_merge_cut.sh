#!/bin/bash

./merge_cut $1 $2 $3 $4 $5 << EOF 1>>  log/log_merge_cut_${5}_s0${4}.log 2>> error.log
EOF
