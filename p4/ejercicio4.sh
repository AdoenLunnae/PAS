#!/bin/bash
if [ "$#" -ne 1 ];then
	echo "Uso: $0 <fichero>"
	exit 1
fi

if [ ! -f $1 ]; then
	echo "$1 no es un fichero válido"
	echo "Uso: $0 <fichero>"
	exit 1
fi

while read -r line;do 
	if  ret=$(ping -c 1 -W "$2" $line); then
		echo $ret | sed -n -r 's/.+[0-9]+ bytes from ([0-9\.]+): icmp_seq=[0-9]+ ttl=[0-9]+ time=([0-9\.]+) ms.+\b/La IP \1 respondió en \2 milisegundos/p'
	else
		echo "La IP $line no respondió tras $2 segundos"
	fi 


done < $1 | sort -k7,7dr -k6,6g
