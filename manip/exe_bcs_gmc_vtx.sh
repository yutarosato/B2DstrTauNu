#!/bin/bash

./bcs_gmc_vtx $1 $2 $3 $4 $5 << EOF 1>>  log/log_bcs_gmc_vtx_$3_s0$2.log 2>> error.log
EOF
