#! /bin/tcsh -f

make cal_dmass_reso || exit
psmerge -odmass_reso.ps pic/d1_m_*.ps && ps2pdf dmass_reso.ps pic/dmass_reso.pdf && rm -f dmass_reso.ps

rm -f tmp_d_{1,2}.dat
foreach LOG(`ls log/d1_m_*.log`)
  grep -h HOGE1 $LOG >> tmp_d_1.dat
  grep -h HOGE2 $LOG >> tmp_d_2.dat
end

cat tmp_d_?.dat

./cal_dmass_reso
