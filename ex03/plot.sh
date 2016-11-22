set title 'Hit Rate vs Array Size'
set xlabel "Array Size [Byte]"
set ylabel "Cache Hit Rate [%]"
set yrange [0:105]
plot "data.txt" using 1:2 with lines title 'cacheSim', "data.txt" using 1:3 with lines title 'likwid'

pause(-1)
