#!/bin/bash

mkdir -p $2
./merge_cut_single $1 $2 << EOF 1>>  log/log_merge_cut_single.log 2>> error.log
EOF
