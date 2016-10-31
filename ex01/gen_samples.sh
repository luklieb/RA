#!/bin/bash

START=$((16*1023))
STOP=$((16*1021*1027))
SAMPLES=60

OUTFILE=input_sizes.txt

rm -f $OUTFILE

y=`echo "e(l($STOP/$START)/$SAMPLES)" | bc -l`
cd /Users/lukas/Documents/Universitaet/Studium/WS\ 16-17/Rechnerarchitektur/Rechnerübung/ex01
for i in `seq 0 $SAMPLES`
do
	kb=`echo "$START*$y^$i" | bc -l | xargs printf "%d\n"`
	bla=$(./main $kb)
	echo "$kb, $bla"  >> $OUTFILE
done

TMP=`mktemp`
uniq $OUTFILE >> $TMP
mv $TMP $OUTFILE
