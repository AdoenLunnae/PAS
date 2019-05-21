#!/bin/bash

if [ $# -ne 1 ] || [ ! -d $1 ]; then
    echo "Uso $0 <directorio>"
    exit 1
fi

countc=`find $1 -name *.c|wc -l`
counth=`find $1 -name *.h|wc -l`
echo "Hay $countc ficheros con extensión .c y $counth ficheros con extensión .h"

for x in `find $1 -name *.c -type f -or -name *.h -type f`; do
    echo "El fichero $x tiene `wc -l < $x` lineas y `wc -m < $x` caracteres"
done | sort -nr -k 8
