#include <stdio.h>
#include "lista.h"

int main() {
	lista_t lista=lista_crear();
	for(int i=0;i<=10;i++) {
		lista_insertar(lista,i,i);
	}
	for(int i=0;i<=10;i++) {
		int x=lista_obtener(lista,i);
		printf("%d\n",x);
	}
	printf("cantidad: %d\n",lista_cantidad(lista));
	printf("---\n");
	lista_eliminar(lista,0);
	printf("elimino la pos 3\n");
	for(int i=0;i<lista_cantidad(lista);i++) {
		int x=lista_obtener(lista,i);
		printf("%d\n",x);
	}
	printf("cantidad: %d\n",lista_cantidad(lista));
	printf("---\n");
	lista_eliminar(lista,9);
	printf("elimino la pos 9\n");
	for(int i=0;i<lista_cantidad(lista);i++) {
		int x=lista_obtener(lista,i);
		printf("%d\n",x);
	}
	/**
	printf("cantidad: %d\n",lista_cantidad(lista));
	printf("---\n");
	for(int i=0;i<=10;i++) {
		lista_insertar(lista,i,i);
	}
	for(int i=0;i<=10;i++) {
		int x=lista_obtener(lista,i);
		printf("%d\n",x);
	}
	**/
	lista_destruir(&lista);
	printf("cantidad: %d\n",lista_cantidad(lista));
	printf("---\n");
}