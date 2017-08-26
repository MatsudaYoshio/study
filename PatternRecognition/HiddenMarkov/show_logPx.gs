unset key
set term postscript eps enhanced
set output 'data_logPx.eps'
plot [1:150] "data_logPx.txt" using 1:2 w lp
set term x11