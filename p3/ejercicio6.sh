#!/bin/bash
#arg1: directorio

function listar_archivos
{
    echo "<ul>" >> $name
    for x in `find $1 -maxdepth 1 -mindepth 1`;do  # -mindepth 1 para que no se liste a si mismo indefinidamente.
        if [ -d $x ]; then
            echo "<li><strong>$(realpath $x)</strong></li>" >> $name
            listar_archivos $x $name
        else
            echo "<li>$(realpath $x)</li>" >> $name
        fi
    done
    echo "</ul>" >> $name                        
}

if [ "$#" -ne 1 ] || [ ! -d $1 ];then
	echo "Uso: $0 <directorio>"
	exit 1
fi

name=$(basename $1)".html"
echo "<html>" > $name
echo "<head>" >> $name
echo "<title>Listado del directorio $1</title>" >> $name
echo "</head>" >> $name
echo "<body>" >> $name
echo "Generando el listado en el fichero $name"
listar_archivos $1 $name 
echo "</body>" >> $name
echo "</html>" >> $name
