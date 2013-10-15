cd /home/dk0r/git/musical-phys/2D_wave-equation/csv/pngs/
rm -f *.png
rm -f *.gif

cd /home/dk0r/git/musical-phys/2D_wave-equation/csv/

for file in *.csv
do
 
gnuplot << EOF
 
# Your GNUplot script with $file instead of the filename
#set terminal pngcairo  transparent enhanced font "arial,10" fontscale 1.0 size 500, 350 
#set terminal pngcairo background rgb "FCFCFC" enhanced font "arial,14" fontscale 1.0 size 1920, 1080 
set terminal pngcairo background rgb "FCFCFC" enhanced font "arial,14" fontscale 1.0 size 1000, 1000 
set datafile separator ','

set border 4095 front linetype -1 linewidth 1.000
set view map
set samples 100, 100
set isosamples 100, 100
unset surface
set style data pm3d
set style function pm3d
set ticslevel 0

set xrange [ 0 : 256 ] noreverse nowriteback
set yrange [ 0 : 256 ] noreverse nowriteback
set zrange [ -0.008 : 0.008 ] noreverse nowriteback
set cbrange [-0.0005:0.0005]

set title "x=$file"
set xlabel "x" 
set ylabel "y" 

set pm3d implicit at b

set output "/home/dk0r/git/musical-phys/2D_wave-equation/csv/pngs/$file.png"
splot "$file";

 
EOF

done

cd /home/dk0r/git/musical-phys/2D_wave-equation/csv/pngs/
#ffmpeg -r 10 -i *.png -s:v 1280x720 -c:v libx264 \ -profile:v high -crf 23 -pix_fmt yuv420p -r 30 daimler_man.mp4
#ffmpeg -r 20 -f image2 -i psi%d.csv.png -y -s 320x240 -aspect 4:3 0_psi.mp4
#ffmpeg -r 20 -f image2 -i "psi%03d.csv.png" -y -s 1920x1080 -aspect 16:9 0-psi_movie.mp4
#ffmpeg -r 20 -f image2 -i psi%*.csv.png -pattern_type glob -y -s 1920x1080 -aspect 16:9 0psi_movie.mp4
ffmpeg -r 20 -f image2 -i psi%*.csv.png -pattern_type glob -y -s 1000x1000 -aspect 1:1 0psi_movie.mp4
#convert   -delay 8   -loop 0   psi*.png   animatedpsi.gif