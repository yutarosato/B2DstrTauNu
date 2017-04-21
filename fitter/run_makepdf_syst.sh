#! /bin/tcsh -f

make makepdf || exit

# 0(fake-D(*))
# 1(sig)
# 2(nor)
# 3(Double DD)
# 4(other)
# 5(D**)

rm -f tmp.list
#foreach TAGCNT (`seq 0 1 99`)
  #echo "./exe_makepdf_syst.sh 0 $TAGCNT" >> tmp.list
  #echo "./exe_makepdf_syst.sh 2 $TAGCNT" >> tmp.list
  #echo "./exe_makepdf_syst.sh 5 $TAGCNT" >> tmp.list
#end

#echo "./exe_makepdf_syst.sh 5  0" >> tmp.list
#echo "./exe_makepdf_syst.sh 5  3" >> tmp.list
#echo "./exe_makepdf_syst.sh 5 -3" >> tmp.list
#echo "./exe_makepdf_syst.sh 5  4" >> tmp.list
#echo "./exe_makepdf_syst.sh 5 -4" >> tmp.list
#echo "./exe_makepdf_syst.sh 5  5" >> tmp.list
#echo "./exe_makepdf_syst.sh 5 -5" >> tmp.list
#echo "./exe_makepdf_syst.sh 5  6" >> tmp.list
#echo "./exe_makepdf_syst.sh 5 -6" >> tmp.list
#echo "./exe_makepdf_syst.sh 5  7" >> tmp.list
#echo "./exe_makepdf_syst.sh 5 -7" >> tmp.list
#echo "./exe_makepdf_syst.sh 5  8" >> tmp.list
#echo "./exe_makepdf_syst.sh 5 -8" >> tmp.list

#echo "./exe_makepdf_syst.sh 3  11" >> tmp.list
#echo "./exe_makepdf_syst.sh 3 -11" >> tmp.list
#echo "./exe_makepdf_syst.sh 3  12" >> tmp.list
#echo "./exe_makepdf_syst.sh 3 -12" >> tmp.list
#echo "./exe_makepdf_syst.sh 3   0" >> tmp.list

echo "./exe_makepdf_syst.sh 2  1" >> tmp.list

bundle e 1 tmp.list
wait_job
rm -f tmp.list
