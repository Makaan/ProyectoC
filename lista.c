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
		//Recorro hasta llegar al elemento anterior.
		for(int i=0;i<pos-1;i++){
			celda_actual=celda_actual->proxima_celda;
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
	//Salgo con error si la posicion no existe.
	if(pos>=lista->cantidad_elementos) {
		exit(LST_POS_INV);
	}
	//Si el que hay que eliminar es el primero lo elimino y actualizo el puntero a la primera posicion
	if(pos==0) {
		//Si hay mas de un elemento ajusto el puntero al primer elemento de la lista y libero el espacio.
		if(lista->primera_celda!=NULL) {
			celda_t* celda_aux=lista->primera_celda;
			lista->primera_celda=lista->primera_celda->proxima_celda;
			free(celda_aux);
		}
		//Si no solo libero el espacio y pongo al primer elemento como nulo.
		else {
		free(lista->primera_celda);
		lista->primera_celda=NULL;
		}
	}
	//Si el elemento a eliminar no es el primero recorro la lista hasta encontrar el elemento anterior a este.
	else {
		celda_t* celda_actual=lista->primera_celda;
		
		for(int i=0;i<pos-1;i++) {
			celda_actual=celda_actual->proxima_celda;
		}
		//Cambio los punteros correspondientes para no romper la lista y libero el espacio de la celda a eliminar.
		celda_t* celda_aux=celda_actual->proxima_celda->proxima_celda;
		free(celda_actual->proxima_celda);
		celda_actual->proxima_celda=celda_aux;
	}
	//Decremento la cantidad de elementos de la lista.
	lista->cantidad_elementos--;
	
	//retorno exito.
	return 1;
}