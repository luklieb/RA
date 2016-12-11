#!/bin/bash


OUTFILE=data_parameter.txt
cd /home/hpc/rzku/iwi3003h/RA/ex06
module load intel64/16.0up03

rm -f $OUTFILE

echo "starting"

for bx in $(seq 100 100 1000)
do
	for by in $(seq 4 100 1004)
	do
		make clean
		make BX=$bx BY=$by
		perf=$(./main 1000 0)
		echo "$perf" >> $OUTFILE
	done
done
#TMP=`mktemp`
#uniq $OUTFILE >> $TMP
#mv $TMP $OUTFILE 
