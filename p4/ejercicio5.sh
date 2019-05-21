cat /proc/cpuinfo | sed -r -n '1,/^[ \t]*$/p' | sed -r -n '
	s/model name[ \t]+: +(.+)/ Modelo: \1/p;
	s/cpu MHz[ \t]+: ([0-9\.]+)/ Megahercios: \1/p;
	s/cpu cores [ \t]+: ([0-9]+)/ Número máximo de hilos/ 	
	'

