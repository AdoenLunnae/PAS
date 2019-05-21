#!/bin/bash
function separar
{
	echo
	echo "****************************************************************************************************************"
	echo "================================================================================================================"
	echo "****************************************************************************************************************"
	echo
	echo $1
	return
}

separar "1) Lineas con las duraciones"
egrep --colour  "^[0-9]+hr " $1
separar "2) Lineas con los paises"
egrep --colour  "\-.+\-" $1
separar "3) Solo los paises"
egrep --colour -o  "\-.+\-" $1
separar "4) Contar peliculas de 2016 y 2017"
echo "$(egrep --colour -c  '[0-9]+/[0-9]+/2016' $1) peliculas de 2016 y $(egrep -c  '[0-9]+/[0-9]+/2017' $1) peliculas de 2017"
separar "5) Archivo sin lineas en blanco"
egrep -v  "^$" $1
separar "6) Lineas que empiezen por 'E'"
egrep --colour  "^ *E" $1
separar "7) Lineas con d,l o t, una vocal, y la misma letra"
egrep --colour  "(d[aeiou]d)|(l[aeiou]l)|(t[aeiou]t)" $1
separar "8) Lineas con 8 o mas aes"
egrep --colour  "(.*a.*){8,}" $1
separar "9) Lineas que acaban en '...' y no empiezan por espacio"
egrep --colour  "^[^ ].*\.{3}$" $1
separar "10) Mostrar vocales con tilde entre comillas"
cat $1 | sed -r 's/([áéíóúÁÉÍÓÚ])/"\1"/g' 
