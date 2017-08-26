unset key
plot x
replot "data_classify.txt" using 1:2 every ::0::101 w p pt 2
set term postscript eps enhanced
set output 'data_classify.eps'
replot "data_classify.txt" using 1:2 every ::100::201 w p pt 4
set term x11