#!/bin/bash
#PBS -lnodes=1:ppn=40:f2.2:ddr1600:likwid,walltime=0:30:00
#PBS -N cacheSim
cd /home/hpc/rzku/iwi3003h/RA/ex03
module load likwid
make clean
make
perfAll=0
perfHit=0
simRate=0
perfRate=0

echo '#size simRate perfRate' > data.txt
#echo '#size perfAll perfHit perfRate simRate' > debug.txt

for i in `seq 20 40`;
do
	size=$((i*1024))
	likwid-perfctr -C 1 -g MEM_UOPS_RETIRED_LOADS:PMC1,MEM_LOAD_UOPS_RETIRED_L1_HIT:PMC2 -m ./cacheSim 32768 64 8 64 $size > out.tmp
	perfAll=$(grep PMC1 out.tmp | grep -oP 'PMC1  |   \s*\K\d*')
	perfHit=$(grep PMC2 out.tmp | grep -oP 'PMC2  |   \s*\K\d*')
	simRate=$(grep -oP '(?<=cacheSim: )[0-9.]+' out.tmp)
	perfRate=$(echo 'scale=4;'$perfHit*100/$perfAll | bc)
	echo $size $simRate $perfRate >> data.txt
	#echo $size $perfAll $perfHit $perfRate $simRate >> debug.txt
	#cp out.tmp out$i.tmp
done

#rm out.tmp
