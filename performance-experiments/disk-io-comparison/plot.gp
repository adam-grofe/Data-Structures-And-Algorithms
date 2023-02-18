set terminal pngcairo font "Arial, 18"
set output "results.png"

set key left top
set xlabel "Millions of Doubles"
set ylabel "Time (s)"

plot \
"results.dat" u ($1/1E6):($2/1E9) w linespoints lw 3 t "MMap",\
"results.dat" u ($1/1E6):($3/1E9) w linespoints lw 3 t "Std::C++"
