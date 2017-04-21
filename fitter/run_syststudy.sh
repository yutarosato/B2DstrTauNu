#! /bin/tcsh -f

make 2dfit     || exit
make syststudy || exit

set STREAMNO = 2
set NEXP     = 100

rm -f tmp.list
#foreach TAGCNT (`seq 0 1 499`)
#foreach TAGCNT (`seq 0 1 99`)
#  echo "./exe_2dfit.sh $NEXP $STREAMNO $TAGCNT" >> tmp.list
#end

echo "./exe_2dfit.sh $NEXP $STREAMNO 0  0" >> tmp.list
echo "./exe_2dfit.sh $NEXP $STREAMNO 0  3" >> tmp.list
echo "./exe_2dfit.sh $NEXP $STREAMNO 0 -3" >> tmp.list
echo "./exe_2dfit.sh $NEXP $STREAMNO 0  4" >> tmp.list
echo "./exe_2dfit.sh $NEXP $STREAMNO 0 -4" >> tmp.list
echo "./exe_2dfit.sh $NEXP $STREAMNO 0  5" >> tmp.list
echo "./exe_2dfit.sh $NEXP $STREAMNO 0 -5" >> tmp.list
echo "./exe_2dfit.sh $NEXP $STREAMNO 0  6" >> tmp.list
echo "./exe_2dfit.sh $NEXP $STREAMNO 0 -6" >> tmp.list
echo "./exe_2dfit.sh $NEXP $STREAMNO 0  7" >> tmp.list
echo "./exe_2dfit.sh $NEXP $STREAMNO 0 -7" >> tmp.list
echo "./exe_2dfit.sh $NEXP $STREAMNO 0  8" >> tmp.list
echo "./exe_2dfit.sh $NEXP $STREAMNO 0 -8" >> tmp.list

#echo "./exe_2dfit.sh $NEXP $STREAMNO 0  11" >> tmp.list
#echo "./exe_2dfit.sh $NEXP $STREAMNO 0 -11" >> tmp.list
#echo "./exe_2dfit.sh $NEXP $STREAMNO 0  12" >> tmp.list
#echo "./exe_2dfit.sh $NEXP $STREAMNO 0 -12" >> tmp.list

#echo "./exe_2dfit.sh $NEXP $STREAMNO 0 1" >> tmp.list # for normalization PDF shape (modeling)


bundle e 15 tmp.list
wait_job
rm -f tmp.list
#exit


grep -h HIGEEEE log/2dfit_*.log > log/syststudy.dat
#exit
./syststudy
