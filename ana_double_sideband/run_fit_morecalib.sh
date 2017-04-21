#! /bin/tcsh -f

make fit_dmass_deltam_morecalib || exit

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
  
#set FILE = "calib.dat"
set FILE = "tmp.dat"
#set FILE = ""

echo "[FL_CALIB] D(sig,sig)=${FL_CALIB_D_SS}, D(sig,bkg)=${FL_CALIB_D_SB}, D(bkg,bkg)=${FL_CALIB_D_BB}, D*(sig,sig)=${FL_CALIB_DSTR_SS}, D*(sig,bkg)=${FL_CALIB_DSTR_SB}, D*(bkg,bkg)=${FL_CALIB_DSTR_BB}"
  
#######################################################################################################################

#foreach LEP ( -999 1 10 )
foreach LEP ( -999 )
#foreach LEP ( 10 )
  # D0
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh  101 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh  301 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh 1101 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh 1210 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh  210 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh 1200 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh 1010 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh   12 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh    2 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh  200 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
# D+
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh  201 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh 1110 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh  310 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh  110 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh  102 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
# Total D
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh  411 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
  bsub -q s ./exe_fit_dmass_deltam_morecalib.sh  421 $LEP $FILE ${FL_CALIB_D_SS} ${FL_CALIB_D_SB} ${FL_CALIB_D_BB} ${FL_CALIB_DSTR_SS} ${FL_CALIB_DSTR_SB} ${FL_CALIB_DSTR_BB}
end
