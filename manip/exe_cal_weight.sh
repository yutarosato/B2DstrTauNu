#!/bin/bash

./cal_weight $1 $2 $3 << EOF 1>>  log/log_cal_weight_$1.log 2>> error.log
EOF
