set terminal pngcairo font "Arial, 18"
set output "results.png"

set key left top
set xlabel "Number of Doubles"
set ylabel "Time (ns)"

plot \
"results.dat" u 1:2 w linespoints lw 3 t "MMap",\
"results.dat" u 1:3 w linespoints lw 3 t "Std::C++"
