#! /bin/tcsh -f

make cal_deltam_reso || exit
psmerge -odeltam_reso.ps pic/dm1_*.ps && ps2pdf deltam_reso.ps pic/deltam_reso.pdf && rm -f deltam_reso.ps

rm -f tmp_dstr_{1,2}.dat
foreach LOG(`ls log/dm1_*.log`)
  grep -h HOGE1 $LOG >> tmp_dstr_1.dat
  grep -h HOGE2 $LOG >> tmp_dstr_2.dat
end

cat tmp_dstr_?.dat

./cal_deltam_reso
