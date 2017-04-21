#! /bin/tcsh -f

make makepdf || exit

mkdir -p pdf_syst0;
mkdir -p pdf_syst1;

# 0(other)
# 1(sig)
# 2(nor)
# 3(D**)
# 4(Double DD)
# 5(fake-D(*):other)
# 6(fake-D(*):sig)
# 7(fake-D(*):nor)
# 8(fake-D(*):D**)
# 9(fake-D(*):DD)

rm -f tmp.list
foreach TAGCNT (`seq 0 1 199`)
foreach LEP( 0 1 10 )
  echo "./exe_makepdf_syst.sh 2 0p0 1 $TAGCNT $LEP" >> tmp.list # semileptonic decay modelling (nor)
  echo "./exe_makepdf_syst.sh 3 0p0 1 $TAGCNT $LEP" >> tmp.list # semileptonic decay modelling (D**)

  echo "./exe_makepdf_syst.sh 5 0p0 1 $TAGCNT $LEP" >> tmp.list # calibration factor : fake-D(*)[other]
  echo "./exe_makepdf_syst.sh 6 0p0 1 $TAGCNT $LEP" >> tmp.list # calibration factor : fake-D(*)[sig]
  echo "./exe_makepdf_syst.sh 7 0p0 1 $TAGCNT $LEP" >> tmp.list # calibration factor : fake-D(*)[nor]
  echo "./exe_makepdf_syst.sh 8 0p0 1 $TAGCNT $LEP" >> tmp.list # calibration factor : fake-D(*)[D**]
  echo "./exe_makepdf_syst.sh 9 0p0 1 $TAGCNT $LEP" >> tmp.list # calibration factor : fake-D(*)[DD]
end
end


#foreach LEP( 0 1 10 )
  #echo "./exe_makepdf_syst.sh 3  0p0 0  0 $LEP" >> tmp.list # D** composition (nominal)
  #echo "./exe_makepdf_syst.sh 3  0p0 0  3 $LEP" >> tmp.list # D** composition (+D1)
  #echo "./exe_makepdf_syst.sh 3  0p0 0 -3 $LEP" >> tmp.list # D** composition (-D1)
  #echo "./exe_makepdf_syst.sh 3  0p0 0  4 $LEP" >> tmp.list # D** composition (+D2)
  #echo "./exe_makepdf_syst.sh 3  0p0 0 -4 $LEP" >> tmp.list # D** composition (-D2)
  #echo "./exe_makepdf_syst.sh 3  0p0 0  5 $LEP" >> tmp.list # D** composition (+D1')
  #echo "./exe_makepdf_syst.sh 3  0p0 0 -5 $LEP" >> tmp.list # D** composition (-D1')
  #echo "./exe_makepdf_syst.sh 3  0p0 0  6 $LEP" >> tmp.list # D** composition (+D*0)
  #echo "./exe_makepdf_syst.sh 3  0p0 0 -6 $LEP" >> tmp.list # D** composition (-D*0)
  #echo "./exe_makepdf_syst.sh 3  0p0 0  7 $LEP" >> tmp.list # D** composition (+D(2S))
  #echo "./exe_makepdf_syst.sh 3  0p0 0 -7 $LEP" >> tmp.list # D** composition (-D(2S))
  #echo "./exe_makepdf_syst.sh 3  0p0 0  8 $LEP" >> tmp.list # D** composition (+D*(2S))
  #echo "./exe_makepdf_syst.sh 3  0p0 0 -8 $LEP" >> tmp.list # D** composition (-D*(2S))

  #echo "./exe_makepdf_syst.sh 4  0p0 0   0 $LEP" >> tmp.list # DD (nominal)
  #echo "./exe_makepdf_syst.sh 4  0p0 0  11 $LEP" >> tmp.list # DD (Ds -> tau nu)
  #echo "./exe_makepdf_syst.sh 4  0p0 0 -11 $LEP" >> tmp.list # DD (Ds -> tau nu)
  #echo "./exe_makepdf_syst.sh 4  0p0 0  12 $LEP" >> tmp.list # DD (Ds* -> Ds -> tau nu)
  #echo "./exe_makepdf_syst.sh 4  0p0 0 -12 $LEP" >> tmp.list # DD (Ds* -> Ds -> tau nu)

  #echo "./exe_makepdf_syst.sh 2 0p0 0  1 $LEP" >> tmp.list # norm (cos resolution)
#end

#bundle e 1 tmp.list
bundle s 30 tmp.list
wait_job
rm -f tmp.list
