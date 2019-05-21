#!/bin/bash
#arg1: carpeta arg2:umbral1(10000) arg3:umbral2(100000)
#pequeños/umbral1/medianos/umbral2/grandes

if [ "$#" -lt 1 ] || [ ! -d $1 ];then
	echo "Uso $0 <directory> [umbral1] [umbral2]"
	exit 1
fi

if [ "$#" -eq 1 ];then   #Si no recibimos ningun umbral asignamos [10000, 100000]
	umbral1=10000
	umbral2=100000 
elif [ "$#" -eq 2 ];then
	if [ $2 -lt 100000 ];then   #Si recibimos uno menor que 100000 asignamos [x, 100000]
		umbral1=$2
		umbral2=100000
	else
		umbral1=10000    #Si recibimos uno mayor que 100000 asignamos [10000, x]
		umbral2=$2
	fi
else
	if [ $2 -lt $3 ];then  #Si recibimos los dos asignamos [menor, mayor]
		umbral1=$2
		umbral2=$3
	else
		umbral1=$3
		umbral2=$2 
	fi  
fi

if [ -d "grandes" ] || [ -d "pequenos" ] || [ -d "medianos" ];then
	echo "Los directorios destino ya existen. Borrando..."
	rm -rf "grandes" "pequenos" "medianos"
fi

	mkdir grandes

	mkdir pequenos

	mkdir medianos

echo "Copiando los archivos..."

for x in `find $1 -size -"$umbral1"c -type f`;do
    cp $x pequenos
done

for x in `find $1 -size +"$umbral1"c -type f -a -size -"$umbral2"c -type f`;do
    cp $x medianos
done

for x in `find $1 -size +"$umbral2"c -type f`;do
    cp $x grandes
done
