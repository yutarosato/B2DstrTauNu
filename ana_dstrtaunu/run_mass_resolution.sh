#!/bin/csh -f

#foreach MODE (101 1010 2 200 1101 210 1200 12 1210 301) #D0
foreach MODE (110 1110 201 102 310) #D+
#foreach MODE (101 1010 2 200 1101 210 1200 12 1210 301  110 1110 201 102 310) #D
   bsub -q s ./mass_resolution $MODE
end
