#!/bin/bash

START=$((16))
STOP=$((16*1024))
SAMPLES=64
bla=1

OUTFILE=data_performance.txt
cd /home/hpc/rzku/iwi3003h/RA/ex06
module load intel64/16.0up03
make clean
make BX=600 BY=500

rm -f $OUTFILE

echo "starting"

y=`echo "e(l($STOP/$START)/$SAMPLES)" | bc -l`
echo "\"$j blocked\"" >> $OUTFILE
for i in `seq 0 $SAMPLES`
do
	mb=`echo "$START*$y^$i" | bc -l | xargs printf "%f\n"`
	echo "program"
	bla=$(./main $mb 1)
	echo "program end"
	echo "$bla"  >> $OUTFILE
done
#TMP=`mktemp`
#uniq $OUTFILE >> $TMP
#mv $TMP $OUTFILE 
