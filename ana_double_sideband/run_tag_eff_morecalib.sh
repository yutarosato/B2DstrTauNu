#! /bin/tcsh -f

set FL_CALIB_D_SS    = 0
set FL_CALIB_D_SB    = 0
set FL_CALIB_D_BB    = 0
set FL_CALIB_DSTR_SS = 0
set FL_CALIB_DSTR_SB = 0
set FL_CALIB_DSTR_BB = 0

if( $#argv > 0 )then
  set FL_CALIB_D_SS = $1
endif
if( $#argv > 1 )then
  set FL_CALIB_D_SB = $2
endif
if( $#argv > 2 )then
  set FL_CALIB_D_BB = $3
endif
if( $#argv > 3 )then
  set FL_CALIB_DSTR_SS = $4
endif
if( $#argv > 4 )then
  set FL_CALIB_DSTR_SB = $5
endif
if( $#argv > 5 )then
  set FL_CALIB_DSTR_BB = $6
endif

#######################################################################################################################
psmerge -odmass_deltam.ps pic/dmass_deltam_*.ps && ps2pdf dmass_deltam.ps pic/dmass_deltam.pdf && rm -f dmass_deltam.ps
echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
grep STATUS log/dmass_deltam_*.log | grep -v INITIATE | grep -v OK | grep -v CONVERGED
echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
grep -A 4 "STATUS=CONVERGED" log/dmass_deltam_*.log | grep -v "CONVERGED" | grep -v "SIZE" | grep -v "STEP" | grep -A 2 "per cent"
#grep -A 2 "STATUS=CONVERGED" log/dmass_deltam_*.log | grep "ERROR MATRIX" | grep -v "ACCURATE"

grep -h HOGEEE log/dmass_deltam_*.log  > tmp.dat
grep -h HUGEEE log/dmass_deltam_*.log >> tmp.dat
echo "*" >> tmp.dat

grep -h HOGEEE log/dmass_deltam_*.log  > tmp2.dat
echo "*" >> tmp2.dat

set INDEX=1
while ( $INDEX < 100 )
    set DIR = "hz_"`printf %d%d%d%d%d%d ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}`"_"`printf %02d ${INDEX}`  
  if( !(-d $DIR) ) then
      mkdir $DIR
      echo "--> copy to ${DIR}"
      mv log/*     ${DIR}/.
      mv pic/*     ${DIR}/.
      cp tmp.dat   ${DIR}/.
      cp tmp2.dat  ${DIR}/.
      ./run_fit_morecalib.sh ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
      exit
    endif
  @ INDEX += 1
end
