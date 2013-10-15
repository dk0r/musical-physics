cd /home/dk0r/git/musical-phys/2D_wave-equation/csv/pngs/
#ffmpeg -r 10 -i *.png -s:v 1280x720 -c:v libx264 \ -profile:v high -crf 23 -pix_fmt yuv420p -r 30 daimler_man.mp4
#ffmpeg -r 20 -f image2 -i psi%d.csv.png -y -s 320x240 -aspect 4:3 0_psi.mp4
#ffmpeg -r 20 -f image2 -i "psi%03d.csv.png" -y -s 1920x1080 -aspect 16:9 0-psi_movie.mp4
#ffmpeg -r 20 -f image2 -i psi%*.csv.png -pattern_type glob -y -s 1920x1080 -aspect 16:9 0psi_movie.mp4
ffmpeg -r 20 -f image2 -i psi%*.csv.png -pattern_type glob -y -s 500x500 -aspect 1:1 0psi_movie.mp4
