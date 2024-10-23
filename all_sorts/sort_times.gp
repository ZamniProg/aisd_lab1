set title "Sort Times"
set xlabel "Run Number"
set ylabel "Time (seconds)"
plot "sort_results.txt" using 1:3 with linespoints title "Sort Time"
