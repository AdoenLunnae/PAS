#!/bin/bash

if [ "$#" -eq 0 ];then
	echo "Usage: $1 [archivos a copiar]+"
	exit 1
fi
date=`date +%s`
name="copia-$USER-$date.tar.gz"

if [ ! -d "$HOME/Copia" ];then
	mkdir ~/Copia
fi

for x in `find ~/Copia -mindepth 1`; do
    creation=`stat $x -c %Y`
    time=$[$date - $creation]
    if [ "$time" -ge 200 ]; then
	echo "Borrando `realpath $x` de $time segundos de antigüedad"
        rm -f $x
    fi
done
tar -czf $name $*
echo "Copia de seguridad creada correctamente"
mv $name ~/Copia
