#! /bin/bash
lettura=$( wget -nv -O - 192.168.1.211)
lettura=$(echo $lettura | sed 's/temp/ -temp/g;s/A/mandata/g;s/B/ritorno/g;s/C/esterno/g')
lettura=$(echo $lettura | sed 's/<\/html>//g;s/<br \/>//g')
data=$( date)
data=$(echo $data | sed 's/CET//g;s/,//;')
lettura="$data-$lettura"
lettura=$(echo $lettura | sed 's/\r//g;s/-<!DOesternoTYPE HTML> <html>//g;')
echo $lettura >> /your/logfile/here.txt
echo $lettura
echo 'differenza'
w=$( echo $lettura | awk '{print ($8 - $11)}')
echo $w
# awk '{print ($8 - $11)}' $lettura
echo "---"
a=$( echo $lettura | awk '{print ($8)}')
echo $a
b=$( echo $lettura | awk '{print ($11)}')
echo $b
c=$( echo $lettura | awk '{print ($14)}')
echo $c
curl "http://www.your.server.here/put.php?v1=$a&v2=$b&v3=$c"
