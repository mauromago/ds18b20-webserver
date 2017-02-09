#! /bin/bash
lettura=$( wget -nv -O - 192.168.1.212)
lettura=$(echo $lettura | sed 's/temp/ -temp/g;s/A/Umid%/g')
lettura=$(echo $lettura | sed 's/<\/html>//g;s/<br \/>//g')
data=$( date)
data=$(echo $data | sed 's/CET//g;s/,//;')
lettura="$data-$lettura"
lettura=$(echo $lettura | sed 's/\r//g;s/-<!DOCTYPE HTML> <html>//g;s/,//g')
echo $lettura >> /your/logfile/here.txt
echo $lettura
# awk '{print ($8 - $11)}' $lettura
echo "---"
a=$( echo $lettura | awk '{print ($8)}')
echo $a
b=$( echo $lettura | awk '{print ($11)}')
echo $b
curl "http://www.your.server.here/put.php?v4=$a&v5=$b"
