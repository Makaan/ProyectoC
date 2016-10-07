#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "pila.h"

int main(){
    char* cadena;
    scanf("%s", cadena);
    printf("Cadena con espacios: %s\n",cadena);
    eliminar_espacios(cadena);
    printf("Cadena sin espacios: %s\n",cadena);
    return 0;
}

void eliminar_espacios(char* cadena)
{
  char* cad = cadena;
  char* aux = cadena;
  int i=0;
  while(*(aux+i)!=0){
    printf("Char de aux: %c",*(aux+i));
    i++;
  }
}
