#!/bin/bash

./bcs_sigmc_rnd $1 $2 << EOF 1>>  log/log_bcs_rnd_sigmc.log 2>> error.log
EOF
