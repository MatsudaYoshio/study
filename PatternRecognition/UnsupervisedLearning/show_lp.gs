unset key
set term postscript eps enhanced
set output 'lp_data.eps'
plot "lp_data.txt" using 1:2 w lp
set term x11