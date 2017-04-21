#!/bin/csh -f

#make

#bsub -q s ./correlation_var_1d  4 # Mmiss ^2
#bsub -q s ./correlation_var_1d  5 # Mmiss*^2
#bsub -q s ./correlation_var_1d  6 # Evis
#bsub -q s ./correlation_var_1d  7 # Evis*
#bsub -q s ./correlation_var_1d  8 # cosdlh
#bsub -q s ./correlation_var_1d  9 # cosdll
#bsub -q s ./correlation_var_1d 10 # rm_bdir
#bsub -q s ./correlation_var_1d 12 # eecl

#
#bsub -q s ./correlation_var_2d  11 9
#bsub -q s ./correlation_var_2d  11 12
# eecl
#bsub -q s ./correlation_var_2d  12 4
#bsub -q s ./correlation_var_2d  12 5
#bsub -q s ./correlation_var_2d  12 6
#bsub -q s ./correlation_var_2d  12 7
#bsub -q s ./correlation_var_2d  12 8
#bsub -q s ./correlation_var_2d  12 9
#bsub -q s ./correlation_var_2d  12 10

# cosdll
#bsub -q s ./correlation_var_2d  9 4
#bsub -q s ./correlation_var_2d  9 5
#bsub -q s ./correlation_var_2d  9 6
#bsub -q s ./correlation_var_2d  9 7
#bsub -q s ./correlation_var_2d  9 8
#bsub -q s ./correlation_var_2d  9 10
#bsub -q s ./correlation_var_2d  9 12

# rm_bdir
#bsub -q s ./correlation_var_2d  10 4
#bsub -q s ./correlation_var_2d  10 5
#bsub -q s ./correlation_var_2d  10 6
#bsub -q s ./correlation_var_2d  10 7
#bsub -q s ./correlation_var_2d  10 8
#bsub -q s ./correlation_var_2d  10 9
#bsub -q s ./correlation_var_2d  10 12

# evis-mmiss^2
#bsub -q s ./correlation_var_2d  4 6
#bsub -q s ./correlation_var_2d  5 7
