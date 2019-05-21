#!/bin/bash

re='^[0-9]+$'
if [ "$#" -eq 1 ];then
	umbral=0
else
	umbral=$2
fi
 
if [ ! -d $1 ] ||  [[ ! $umbral =~ $re ]]; then
    echo "Uso: $0 <directorio> [umbral]"
    exit 1
fi

echo "Nombre, LongUsuario, FechaMod, FechaAcceso, Tamaño, Bloques, Permisos, Ejecutable"

for x in `find $1 -size +"$umbral"c -type f -o -size "$umbral"c -type f`; do
    longusuario=`stat -c %u $x|wc -m`-1
    ejecutable=0
	
	if [ -x $x ];then
		ejecutable=1
	fi
	
    echo "$(basename $x);$longusuario;$(stat -c '%y;%X;%s;%b;%A' $x);$ejecutable"
done | sort -k 5 -n -t ";"
