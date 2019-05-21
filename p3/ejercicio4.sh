#!/bin/bash

echo `who|awk '{print $1}'|sort|uniq`
echo -en "¿Qué carácter quieres contar?\t"
if ! read -n1 -t5 c;then
	c="a"
fi	# 5 segundos o se asigna "a"

echo

count=$(
for x in `find`; do
    echo `basename $x`
done | grep $c -o | wc -l
)
case "$count" in
	1) p="vez";;
	*) p="veces";;
esac

echo "El carácter '$c' aparece $count $p en nombres de ficheros o directorios"
