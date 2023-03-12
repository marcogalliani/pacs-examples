#!/bin/bash
# A script that launches gnuplot on the file result.dat
#
# you can also launch gnuplot and type the command at the gnuplot prompt
#

gnuplot<<EOF
plot [0:1] "result.dat" u 2:3 w lp lw 2 title "uh", log(1-x**2/2) title "exact solution"
pause -1
EOF