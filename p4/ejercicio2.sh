cat $1 | grep -v -E "^[=]*$" | sed -r 
'
	/^ .+$/d;
	s/^\((.+)\) -.+-$/|->Fecha de estreno : \1/g;
	s/^Dirigida por (.+)$/|->Director: \1/g;
	s/^Reparto: (.+)/|->Reparto: \1/g;
	s/^([0-9]*hr [0-9]+min)$/|->Duración: \1/g;
	s/^([^|].+)/Título: \1/g
'
