#!/bin/tcsh
set input = $1:r
ps2pdf -dEPSCrop -dPDFSETTINGS=/prepress $input.eps $input.pdf
pdf2ps $input.pdf {$input}.eps
rm $input.pdf
