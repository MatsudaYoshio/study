unset key
plot "param_data.txt" using 1:2 w lp
replot "param_data.txt" using 1:3 w lp
set term postscript eps enhanced
set output 'param_data.eps'
replot "param_data.txt" using 1:4 w lp
set term x11