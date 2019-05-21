#include <stdio.h>
#include <stdlib.h> //exit, rand, srand
#include <unistd.h> //pipe, close, fork, usleep, read, write, getpid, getppid
#include <sys/wait.h> //wait
#include <errno.h> //Control de errores
#include <string.h> //strerror
#include <time.h> //Para la semilla del generador de aleatorios
#include <math.h>

int esPrimo(int x){
  int i = 2;
  int ret = 1;
  for(i; (i < pow(x, 0.5)) && (ret!= 0); i++){
    if( (x%i) == 0){
      ret = 0;
    }
  }
  return ret;
}
int checkPrimos(int a, int b){
  if(!esPrimo(a) || !esPrimo(b)){
    return 0;
  }
  else if(abs(a-b) == 2){
    return 1;
  }
  return 2;
}


int main() 
{
pid_t flag;
int status,pipe2;
int a, b;
int fildes[2];
int fildes2[2];
const int BSIZE = 100;
char buf[BSIZE];
char strfather[32]; 
ssize_t nbytes;


status = pipe(fildes);
pipe2 = pipe(fildes2);
if (status == -1 ) 
{
	perror("Error en pipe"); 
	exit(EXIT_FAILURE);
}

switch (fork()) 
{
	case -1: // Ocurrió un error al hacer fork()
		perror("No se ha podido crear el proceso hijo...");
		exit(EXIT_FAILURE);

	case 0: // El hijo lee desde la tubería, no necesitamos escribir.
		if (close(fildes[1]) == -1) 
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
	
		// Leer usando READ
		nbytes = read(fildes[0], buf, BSIZE);
		if (nbytes == -1)
		{
			perror("Error en read"); 
			exit(EXIT_FAILURE);
		}
		else if (nbytes == 0) //read() no ha leido nada -> Se ha llegado a EOF -> El padre ha cerrado la tuberia
			printf("[HIJO]: Detecto que mi padre ha cerrado la tuberia...\n"); 
		else
			a = atoi(strtok(buf, ";"));
			b = atoi(strtok(NULL, ";"));
			switch (checkPrimos(a, b))
      {
        case 0:
          write(fildes2[1], "no primos", 17);
          break;
        case 1:
          write(fildes2[1], "gemelos", 17);
          break;
        case 2:
          write(fildes2[1], "primos", 17);
          break;
      }
    close(fildes2[1]);
		if (close(fildes[0]) == -1) //Se termina de leer -> Cerramos filfes[0]
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
		else
			printf("[HIJO]: Tuberia cerrada.\n"); 

		exit(EXIT_SUCCESS);

	
	default: // El padre escribe en la tubería
		// No se necesita leer
		printf("Primer Numero:  ");
		scanf("%d", &a);
		printf("Segundo Numero:  ");
		scanf("%d", &b);
		sprintf(strfather, "%d;%d", a, b);
		if (close(fildes[0]) == -1) 
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}

		// Escribimos datos en la tubería
		if ( write(fildes[1], strfather, 32) == -1)
		{
			perror("Error en write"); 
			exit(EXIT_FAILURE);
		}
    nbytes = read(fildes2[0], buf, BSIZE);
		if (nbytes == -1)
		{
			perror("Error en read"); 
			exit(EXIT_FAILURE);
		}
    else{
      printf("[PADRE]: Los numeros son %s\n", buf);
    }
    close(fildes2[1]);
		// El hijo verá FEOF (por hacer close)
		if (close(fildes[1]) == -1) 
		{
			perror("Error en close"); 
			exit(EXIT_FAILURE);
		}
		else
			printf("[PADRE]: Tuberia cerrada.\n"); 
			
		while ( (flag=wait(&status)) > 0 ) 
		{
			if (WIFEXITED(status)) 
			{
				printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
			} else if (WIFSIGNALED(status)) {  //Para seniales como las de finalizar o matar
				printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
			} else if (WIFSTOPPED(status)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
				printf("Proceso Padre, Hijo con PID %ld parado al recibir la señal %d\n", (long int)flag,WSTOPSIG(status));
			} else if (WIFCONTINUED(status)){ //Para cuando se reanuda un proceso parado. Al usar wait() en vez de waitpid() no nos sirve.
				printf("Proceso Padre, Hijo con PID %ld reanudado\n",(long int) flag);		  
			}	
		}
		if (flag==(pid_t)-1 && errno==ECHILD)
		{
			printf("Proceso Padre, valor de errno = %d, definido como %s, no hay más hijos que esperar!\n", errno, strerror(errno));
		}
		else
		{
			printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
			exit(EXIT_FAILURE);
		}
		
		exit(EXIT_SUCCESS);	
	}//switch		 
}
