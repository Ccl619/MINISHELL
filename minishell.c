#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<sys/wait.h>

void reemplazarCaracter(char cadena[], char caracter,char reemplazar) {
    if (cadena == NULL) {
        return;
    }
    int longitud = strlen(cadena);
    for (int i=0;i<longitud;i++) {
        if (cadena[i] == caracter) {
            cadena[i]=reemplazar;
        }
    }
}

int main(){
  char cadena[100];
  char *argumentos[100];
  char *comando;
  pid_t pid;
  int estado;

 while(1) {
     printf("-$");
     
     if(fgets(cadena,100,stdin)==NULL) {
         printf("Error. Comando no encontrado\n");
         continue;
     }

     reemplazarCaracter(cadena,'\n','\0');

     if (strcmp(cadena, "Salir") == 0 || strcmp(cadena, "salir") == 0) {
         printf("Programa finalizado :D\n");
         break;
     }

    int i=0;
    comando=strtok(cadena, " ");//divide en subcadenas la cadena original dado un caracter delimitador
    while (comando!=NULL && i < 99) {
        argumentos[i]=comando;
        i++;
        comando=strtok(NULL," ");//se le tiene que pasar null para que siga dividiendo la cadena
    }
     argumentos[i]='\0'; //agrega el caracter nulo para marcar cada subcadena
     pid = fork();

     if (pid < 0) {
         printf("Error al crear el proceso\n");
         exit(1);
     }

     if (pid == 0) {
         if (execvp(argumentos[0], argumentos) == -1) {
             printf("Error al ejecutar el comando\n");
         }
         exit(1);
     } else {
         wait(&estado);//el proceso padre espera y recoje el estado de salida de uno de sus hijos
     }
 }
    return 0;
}
