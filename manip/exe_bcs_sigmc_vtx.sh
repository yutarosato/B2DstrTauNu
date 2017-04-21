#!/bin/bash

./bcs_sigmc_vtx $1 $2 << EOF 1>>  log/log_bcs_vtx_sigmc.log 2>> error.log
EOF
