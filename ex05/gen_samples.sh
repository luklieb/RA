#!/bin/bash

START=$((16))
STOP=$((16*1024))
SAMPLES=64
bla=1

OUTFILE=data.txt
cd /home/hpc/rzku/iwi3003h/RA/ex05
module load intel64/16.0up03
make clean
make

#rm -f $OUTFILE

echo "starting"

y=`echo "e(l($STOP/$START)/$SAMPLES)" | bc -l`
for j in 4000 6000 8000 12000
do
	echo "\"$j blocked\"" >> $OUTFILE
	for i in `seq 0 $SAMPLES`
	do
		kb=`echo "$START*$y^$i" | bc -l | xargs printf "%f\n"`
		echo "program"
		bla=$(./main $kb $j)
		echo "program end"
		echo "$bla"  >> $OUTFILE
	done
	echo " " >> $OUTFILE
	echo " " >> $OUTFILE
	echo " " >> $OUTFILE
	echo " " >> $OUTFILE
done
#TMP=`mktemp`
#uniq $OUTFILE >> $TMP
#mv $TMP $OUTFILE 
