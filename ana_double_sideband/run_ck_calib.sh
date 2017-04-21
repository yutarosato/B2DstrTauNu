#! /bin/tcsh -f

set DIR = "hz_000100_20"

set CNT=0

foreach DIR( ${DIR} ${DIR} )
  echo ${DIR}
  @ CNT += 1
  foreach DATA( mc dt )
  foreach DMESON( d dstr )
  foreach COMP( s1s2 s1b2 b1s2 b1b2 )
    set FILE = dat/tmp_${DMESON}_${DATA}_${COMP}_${CNT}.dat
    rm -f ${FILE}
    echo ${FILE}
    foreach MODE( 101 2 200 1010 1101 210 1200 12 301 1210 110 201 1110 102 310 )
       echo -n "${MODE} " >> ${FILE}; grep -A 5 "FinalValue" ${DIR}/*_${MODE}_*.log | grep "${COMP},${DMESON},${DATA}" | sed -e 's|\s\+| |g'| awk '{print $3" "$5}' >> ${FILE}
    end
  end
  end
  end
end

make ck_calib
./ck_calib
#######################################################################################################################
