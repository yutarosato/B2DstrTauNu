#! /bin/tcsh -f

make tag_eff || exit

rm -f tmp_e_*.dat tmp_m_*.dat

foreach LOG(`ls log/cosdl1_*10.log`)
  grep -h HOGEEE $LOG | tr '\n' ' '  >> tmp_e_total.dat
  grep -h Status $LOG | awk -F "=" '{print $2" "$3}' | sed 's|HESSE ||' | awk '{sum += $1+$2} END{print sum}' >> tmp_e_total.dat
end

foreach LOG(`ls log/cosdl1_*1.log`)
  grep -h HOGEMU $LOG | tr '\n' ' ' >> tmp_m_total.dat
  grep -h Status $LOG | awk -F "=" '{print $2" "$3}' | sed 's|HESSE ||' | awk '{sum = $1+$2} END{print sum}' >> tmp_m_total.dat
end

grep -h    "HOGEEE 0" tmp_e_total.dat > tmp_e_success.dat
grep -h -v "HOGEEE 0" tmp_e_total.dat > tmp_e_false.dat
grep -h    "HOGEMU 0" tmp_m_total.dat > tmp_m_success.dat
grep -h -v "HOGEMU 0" tmp_m_total.dat > tmp_m_false.dat
cat tmp_e_success.dat
cat tmp_e_false.dat
cat tmp_m_success.dat
cat tmp_m_false.dat
wc -l tmp_{e,m}_*.dat

psmerge -otag_eff.ps pic/cosdl1_*.ps && ps2pdf tag_eff.ps pic/tag_eff_mode.pdf && rm -f tag_eff.ps

./tag_eff
