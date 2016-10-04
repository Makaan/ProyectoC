#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

const int LST_POS_INV=4;

//Retorna una nueva lista vacia.
lista_t lista_crear() {
	//Asigno la cantidad de memoria necesaria.
  lista_t lista=(lista_t) malloc(sizeof(lista_t));

  //Creo la lista.
	lista->cantidad_elementos=0;
	lista->primera_celda=NULL;

  return lista;
}

//Inserta un elemento en la lista en la posicion pasada como parametro, si la posicion es igual
//a la cantida de elementos de la lista, se inserta al final.
int lista_insertar(lista_t lista, unsigned int pos, int elem) {
	//Si la posicion es mayor que la cantidad de elementos retorna falso.
	if(pos>lista->cantidad_elementos)
		return 0;
	
	//Si la posicion es el primer elemento lo agrego al principio.
	if(pos==0) {
		//Si ya hay primer elemento solo lo reemplazo.
		if(lista->primera_celda!=NULL) {
			lista->primera_celda->elementos[0]=elem;
		}
		//Si no creo uno nuevo.
		else {
			celda_t *celda=(celda_t *) malloc(sizeof(celda_t));
			celda->elementos[0]=elem;
			celda->proxima_celda=NULL;
			lista->primera_celda->proxima_celda=celda;
		}
	}
	//Si la posicion no es la primera busco donde insertar.
	else {
		//Creo un puntero para recorrer la lista.
		celda_t* celda_actual=lista->primera_celda->proxima_celda;
		int i=0;
		//Recorro hasta llegar al elemento anterior.
		while(i<pos) {
			celda_actual=celda_actual->proxima_celda;
			i++;
		}
		//Si estoy al final de la lista agrego un nuevo elemento.
		if(celda_actual->proxima_celda==NULL) {
			celda_t* celda=(celda_t *) malloc(sizeof(celda_t));
			celda->elementos[0]=elem;
			celda_actual->proxima_celda=celda;
			lista->cantidad_elementos++;
		}
		//Si no estoy al final solo reemplazo el elemtno en la proxima celda.
		else {
			celda_actual->proxima_celda->elementos[0]=elem;
		}
	}
	//Retorno exito.
	return 1;
}

int lista_eliminar(lista_t lista, unsigned int pos) {
	if(pos>lista->cantidad_elementos) {
		exit(LST_POS_INV);
	}
	if(pos==0) {
		free(lista->primera_celda);
		lista->primera_celda=NULL;
	}
	celda_t* celda_actual=lista->primera_celda;
	
	for(int i=0;i<pos;)
}