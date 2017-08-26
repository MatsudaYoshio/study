unset key
plot "data.txt" using 1:2 w lp
replot "data.txt" using 1:3 w lp
set term postscript eps enhanced
set output 'glaph.eps'
replot "data.txt" using 1:4 w lp
set term x11