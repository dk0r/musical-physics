for file in $(echo *.csv); do
    gnuplot <<EOF
    set terminal post color
    set output "/home/dk0r/git/musical-phys/2D_wave-equation/csv/pngs/${file}.eps"
    set datafile separator ','  #csv file
   
set view map
set size ratio .9

set object 1 rect from graph 0, graph 0 to graph 1, graph 1 back
set object 1 rect fc rgb "black" fillstyle solid 1.0

splot "$file" using 1:2:3 with points pointtype 5 pointsize 1 palette linewidth 30

    
EOF
done