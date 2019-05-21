/*
Ejemplo extraído y adaptado del estándar POSIX y glibc.
Enlace a la página de documentación de la implemencación de getopt de glibc:
http://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Options.html
http://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <pwd.h>
#include <grp.h>

char* parseGroup(char* line){
	char* name;
	int id;
	char *ret = malloc(64 * sizeof(char));
	name = strtok(line, ":");
	strtok(NULL, ":");
	id = atoi(strtok(NULL, ":"));
	sprintf(ret, "Name: %s, GID: %d", name, id);
	return ret;
}

void printhelp(){
	msg = 
	"Usage: ejercicio1 [opcion] <parametros>\n-u, --username";
}


int main (int argc, char **argv)
{
	int c;
	int uflag=0, iflag=0, gflag=0, dflag=0, aflag=0, sflag=0, bflag = 0, hflag = 0;
	char* uvalue = NULL;
	char* ivalue = NULL;
	char* gvalue = NULL;
	char* dvalue = NULL;
	char* avalue = NULL;
	struct passwd *pw;
  struct group *gr;

	/* Estructura a utilizar por getoptlong */
	static struct option long_options[] =
	{
		/* Opciones que no van a actuar sobre un flag */
		/* "opcion", recibe o no un argumento, 0,
		   identificador de la opción */	
		{"username", 	required_argument, 	0, 'u'},
		{"userid", 		required_argument, 	0, 'i'},
		{"groupname", required_argument, 	0, 'g'},
		{"groupid", 	required_argument, 	0, 'd'},
		{"allinfo", 	required_argument, 	0, 'a'},
		{"allgroups", no_argument, 				0, 's'},
		{"bactive", 	no_argument, 				0, 'b'},
		{"help", 			no_argument, 				0, 'h'},
		/* Necesario para indicar el final de las opciones */
		{0, 0, 0, 0}
	};

	/* Estas variables servirán para almacenar el resultado de procesar la línea de comandos */
	char *pattern;

	/* getopt_long guardará el índice de la opción en esta variable. */
	int option_index = 0;
	
	/* Deshabilitar la impresión de errores por defecto */
	/* opterr=0; */
	while ((c = getopt_long(argc, argv, "u:i:g:d:a:sbh", long_options, &option_index))!=-1)
	{
		/* El usuario ha terminado de introducir opciones */
		if (c == -1)
			break;
		switch (c)
		{
			case 'u':
				uflag = 1;
				uvalue = optarg;
				break;
			case 'i':
				iflag = 1;
				ivalue = optarg;
				break;
			case 'g':
				gflag = 1;
				gvalue = optarg;
				break;
			case 'd':
				dflag = 1;
				dvalue = optarg;
				break;
			case 'a':
				aflag = 1;
				avalue = optarg;
				break;
			case 's':
				sflag = 1;
				break;
			case 'b':
				bflag = 1;
				break;
			case 'h':
				hflag = 1;
				break;
			case '?':
				hflag = 1;
				/* getopt_long ya imprime su mensaje de error, no es necesario hacer nada */
				/* Si queremos imprimir nuestros propios errores, debemos poner opterr=0,
				 y hacer algo como lo que se expone a continuacion. Pruebe a hacer sus propios errores.
				if (optopt == 'c')
					fprintf (stderr, "La opción %c requiere un argumento.\n", optopt);*/
				break;

			default:
				abort ();
		}
		//printf("optind: %d, optarg: %s, optopt: %c\n", optind, optarg, optopt);
	}

	/* Imprimir el resto de argumentos de la línea de comandos que no son opciones con "-" */
	
	//printf ("uflag=%d, iflag=%d, gflag=%d, dflag=%d, aflag=%d, sflag=%d, bflag = %d, hflag = %d\n", uflag, iflag, gflag, dflag, aflag, sflag, bflag, hflag);
	//printf("uvalue=%s, ivalue=%d, gvalue=%s, dvalue=%s, avalue=%s\n", uvalue, ivalue, gvalue, dvalue, avalue);


// struct passwd
// {
//   char *pw_name;		/* Username.  */
//   char *pw_passwd;		/* Hashed passphrase, if shadow database
//                                    not in use (see shadow.h).  */
//   __uid_t pw_uid;		/* User ID.  */
//   __gid_t pw_gid;		/* Group ID.  */
//   char *pw_gecos;		/* Real name.  */
//   char *pw_dir;			/* Home directory.  */
//   char *pw_shell;		/* Shell program.  */
// };

// struct group
// {
//   char *gr_name;		/* Group name.	*/
//   char *gr_passwd;		/* Password.	*/
//   __gid_t gr_gid;		/* Group ID.	*/
//   char **gr_mem;		/* Member list.	*/
// };
	if(uflag){
		if((pw = getpwnam(uvalue)) != NULL){
			printf("Username: %s, UID: %d, GID: %d, Name: %s, Home: %s, Shell: %s\n", 
			pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_gecos, pw->pw_dir, pw->pw_shell);
		}
		else{
			fprintf(stderr, "Username doesn't exist\n");	
			return(1);
		}
	}else if(iflag){
		if((pw = getpwuid(atoi(ivalue))) != NULL){
			printf("Username: %s, UID: %d, Main GID: %d, Name: %s, Home: %s, Shell: %s\n", 
			pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_gecos, pw->pw_dir, pw->pw_shell);
		}
		else{
			fprintf(stderr, "User ID doesn't exist\n");	
			return(1);
		}
	}else if(gflag){
		if((gr = getgrnam(gvalue)) != NULL){
			printf("Name: %s, GID: %d\n", gr->gr_name, gr->gr_gid);
		}
		else{
			fprintf(stderr, "Group doesn't exist\n");
		}
	}else if(dflag){
		if((gr = getgrgid(atoi(dvalue))) != NULL){
			printf("Name: %s, GID: %d\n", gr->gr_name, gr->gr_gid);
		}
		else{
			fprintf(stderr, "Group doesn't exist\n");
		}
	}else if(aflag){
		if((pw = getpwnam(avalue)) != NULL){
			gr = getgrgid(pw->pw_gid);
			printf("Username: %s, UID: %d, Main GID: %d, Name: %s, Home: %s, Shell: %s\n", 
			pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_gecos, pw->pw_dir, pw->pw_shell);
			printf("Name: %s, GID: %d\n", gr->gr_name, gr->gr_gid);
		}
		else{
			fprintf(stderr, "Usern doesn't exist");
		}
	}else if(sflag){
		FILE* grfile; 
		char* line = NULL;
		size_t n = 0;
		if((grfile = fopen("/etc/group", "r")) == NULL){
			fprintf(stderr, "Couldn't open group file");
			exit(1);
		}
		getline(&line, &n, grfile);
		while(!feof(grfile)){
			printf("%s\n", parseGroup(line));
			getline(&line, &n, grfile);
		}
		free(line);
		fclose(grfile);
	}else if(bflag){
		char* uname = getenv("USER");
		if((pw = getpwnam(uname)) != NULL){
			gr = getgrgid(pw->pw_gid);
			printf("Name: %s, GID: %d\n", gr->gr_name, gr->gr_gid);
		}
	}else if(hflag){
		printhelp();
	}

	return(0);
}

