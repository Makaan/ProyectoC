#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

//Retorna una nueva lista vacia.
lista_t lista_crear() {
	//Asigno la cantidad de memoria necesaria.
  lista_t lista=(lista_t) malloc(sizeof(tLista));

  //Creo la lista.
	lista->cantidad_elementos=0;
	lista->primer_celda=null;

  return lista;
}

int lista_insertar(lista_t lista, unsigned int pos, int elem) {
	if(pos>lista->cantidad_elementos)
		return false;

	if(pos==0) {
		celda_t *celda=(celda_t *) malloc(sizeof(celda_t));
		celda->elementos[0]=elem;
		celda->proxima_celda=lista->primera_celda->proxima_celda;
		lista->primera_celda->proxima_celda=celda;
	}
	else {
		celda_t *celda_actual=lista.primer_celda->proxima_celda;
		int i=0;
		while(i<pos) {
			celda_actual=celda_actual->proxima_celda;
			if(celda_actual==NULL) {
				exit(LST_POS_INV);
			}
			i++;
		}
		if(celda_actual->proxima_celda==NULL) {
			celda_t *celda=(celda_t *) malloc(sizeof(celda_t));
			celda->elementos[0]=elem;
			celda_actual->proxima_celda=celda;
		}
		else {
			celda_actual->proxima_celda->elemento[0]=elem;
		}
	}
}