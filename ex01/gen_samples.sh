#!/bin/bash

START=$((1))
STOP=$((128*1024))
SAMPLES=64
bla=1

OUTFILE=input_sizes.txt
cd /home/hpc/rzku/iwi3003h/RA/ex01
module load intel64/16.0up03
make clean
make

rm -f $OUTFILE

y=`echo "e(l($STOP/$START)/$SAMPLES)" | bc -l`
for j in 1 2 3 4 8
do
	echo "\" $j -fach unrolled:\"" >> $OUTFILE
	for i in `seq 0 $SAMPLES`
	do
		kb=`echo "$START*$y^$i" | bc -l | xargs printf "%f\n"`
		bla=$(./main $kb $j)
		echo "$kb, $bla"  >> $OUTFILE
	done
	echo " " >> $OUTFILE
	echo "\n" >> $OUTFILE
	done

TMP=`mktemp`
uniq $OUTFILE >> $TMP
mv $TMP $OUTFILE 
