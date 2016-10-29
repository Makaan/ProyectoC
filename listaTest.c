#include <stdio.h>
#include <stdlib.h>
#include "lista.c"
#include "lista.h"

int main() {
    lista_t lista=lista_crear();
    
    for(int i=0;i<100;i++) {
	printf("size %d\n",lista_cantidad(lista));
	lista_insertar(lista,i,i);
    }
    printf("------------------------\n");
    lista_eliminar(lista,3);
    lista_eliminar(lista,4);
}