unset key
plot "data_Bij.txt" using 1:2 w lp
replot "data_Bij.txt" using 1:3 w lp
set term postscript eps enhanced
set output 'data_Bij.eps'
replot "data_Bij.txt" using 1:4 w lp
set term x11