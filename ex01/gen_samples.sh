#!/bin/bash

START=$((128*1024))
STOP=$((128*1024*1024))
SAMPLES=60

OUTFILE=input_sizes.txt

rm -f $OUTFILE

y=`echo "e(l($STOP/$START)/$SAMPLES)" | bc -l`
#cd /Users/lukas/Documents/Universitaet/Studium/WS\ 16-17/Rechnerarchitektur/Rechnerübung/ex01
for j in 2 3 4 8
do
	echo "# $(j)-fach unrolled: "
	for i in `seq 0 $SAMPLES`
	do
		kb=`echo "$START*$y^$i" | bc -l | xargs printf "%d\n"`
		bla=$(./main $kb $j)
		echo "$kb, $bla"  >> $OUTFILE
	done
	echo " "
	done

TMP=`mktemp`
uniq $OUTFILE >> $TMP
mv $TMP $OUTFILE 
