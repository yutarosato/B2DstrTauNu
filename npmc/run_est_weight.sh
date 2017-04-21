#! /bin/tcsh -f

make est_weight         || exit
make est_weight_combine || exit

################################
# change L.26-27 in draws_np_.h
################################
set NTOT  = 20736 # 12^4
set NPERJ =   144 # 12^2
#set NTOT  = 4096 # 8^4
#set NPERJ =   64 # 8^2
################################
      
set INDEX=0
set CNT=0
while(1)
echo -n "${INDEX} ${CNT} (${NPERJ}) -> "
#bsub -q sx ./exe_est_weight.sh ${INDEX} ${CNT} ${NPERJ}
@ INDEX += 1
@ CNT   += ${NPERJ}
if( ${CNT} >= ${NTOT} ) then
    break;
endif
end

wait_job
./est_weight_combine ${INDEX}
