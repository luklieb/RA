#!/bin/bash

START=$((16*1023))
STOP=$((16*1021*1027))
SAMPLES=60

OUTFILE=input_sizes.txt

rm -f $OUTFILE

y=`echo "e(l($STOP/$START)/$SAMPLES)" | bc -l`

for i in `seq 0 $SAMPLES`
do
    kb=`echo "$START*$y^$i" | bc -l | xargs printf "%d\n"`
    echo $kb >> $OUTFILE
done

TMP=`mktemp`
uniq $OUTFILE >> $TMP
mv $TMP $OUTFILE
