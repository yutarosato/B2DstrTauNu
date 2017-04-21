#!/bin/bash

./bcs_sigmc $1 $2 << EOF 1>>  log/log_bcs_sigmc.log 2>> error.log
EOF
