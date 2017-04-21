#! /bin/tcsh -f

make 2dfit     || exit
make syststudy || exit

#set STREAMNO = 2
set STREAMNO = -999
set NEXP     = 100
set LEP      = 0
#set LEP      = 10
#set LEP      = 1


rm -f tmp.list
######################################
## systematics from MC statictics   ## comment on <for syststudy : MC statistics>                                           & systpdf_no = 0-9.
## systematics from decay modelling ## comment on <for syststudy : decay modelling...> & set pdf_dir_syst to be "pdf_syst1" & systpdf_no = 2or3
## systematics from calib factor    ## comment on <for syststudy : decay modelling...> & set pdf_dir_syst to be "pdf_syst1" & systpdf_no = 5-9
######################################
#foreach TAGCNT (`seq 0 1 499`)
#foreach TAGCNT (`seq 0 1 199`)
#foreach TAGCNT (`seq 0 1 99`)
#  echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP $TAGCNT" >> tmp.list
#end

####################################
## systematics from D**/DD or nor ## comment on <for syststudy : decay modelling...> & set pdf_dir_syst to be "pdf_syst0" & systpdf_no = 2-4
####################################
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP  0" >> tmp.list
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP  3" >> tmp.list # D1
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP -3" >> tmp.list # D1
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP  4" >> tmp.list # D2
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP -4" >> tmp.list # D2
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP  5" >> tmp.list # D1'
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP -5" >> tmp.list # D1'
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP  6" >> tmp.list # D*0
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP -6" >> tmp.list # D*0
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP  7" >> tmp.list # D(2S)
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP -7" >> tmp.list # D(2S)
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP  8" >> tmp.list # D*(2S)
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP -8" >> tmp.list # D*(2S)

#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP  11" >> tmp.list # Ds D* & Ds -> tau nu
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP -11" >> tmp.list # Ds D* & Ds -> tau nu
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP  12" >> tmp.list # Ds*D* & Ds -> tau nu
#echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP -12" >> tmp.list # Ds*D* & Ds -> tau nu

echo "./exe_2dfit.sh $NEXP $STREAMNO $LEP 1" >> tmp.list # for normalization PDF shape (modeling)


bundle e 10 tmp.list
wait_job
rm -f tmp.list
#exit


#grep -h HIGEEEE log/2dfit_*.log > log/syststudy.dat
#exit
#./syststudy
