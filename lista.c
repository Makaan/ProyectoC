#include <stdio.h>
#include <stdlib.h>

const int LST_NO_INI=3;
const int LST_POS_INV=4;



//Retorna una nueva lista vacia.
lista_t lista_crear() {
	//Asigno la cantidad de memoria necesaria.
  lista_t lista=(lista_t) malloc(sizeof(struct lista_eficiente));

  //Creo la lista.
	lista->cantidad_elementos=0;
	lista->primera_celda=malloc(sizeof(celda_t));

  return lista;
}

//Inserta un elemento en la lista en la posicion pasada como parametro, si la posicion es igual
//a la cantida de elementos de la lista, se inserta al final.
int lista_insertar(lista_t lista, unsigned int pos, int elem) {
	//Si la posicion es mayor que la cantidad de elementos retorna falso.
	if(pos>lista->cantidad_elementos)
		return 0;
	
	int posCelda=pos/4;
	celda_t* celda_actual=lista->primera_celda;
	for(int i=0;i<posCelda;i++) {
		if((celda_actual->proxima_celda)==NULL) {
			celda_t* nuevaCelda=(celda_t*)malloc(sizeof(celda_t));
			celda_actual->proxima_celda=nuevaCelda;
		}
		celda_actual=celda_actual->proxima_celda;
	}
	int posArreglo=pos%4;
	celda_actual->elementos[posArreglo]=elem;
	lista->cantidad_elementos++;
	
	return 1;
}

//Elimina de la lista el elemento en la posicion pasada como parametro
int lista_eliminar(lista_t lista, unsigned int pos) {
	//Salgo con error si la posicion no existe.
	if(pos>=lista->cantidad_elementos) {
		exit(LST_POS_INV);
	}
	int posCelda=pos/4;
	celda_t* celda_actual=lista->primera_celda;
	for(int i=0;i<posCelda;i++) {
		celda_actual=celda_actual->proxima_celda;
	}
	int posArreglo=pos%4;
	while(pos<lista->cantidad_elementos) {
		for(;posArreglo<4 && (pos<lista->cantidad_elementos);posArreglo++) {
			celda_actual->elementos[posArreglo]=celda_actual->elementos[posArreglo+1];
			pos++;
		}
		if(pos<lista->cantidad_elementos) {
			celda_actual->elementos[3]=celda_actual->proxima_celda->elementos[0];
			celda_actual=celda_actual->proxima_celda;
			posArreglo=0;
		}
	}
	lista->cantidad_elementos--;
	return 1;
	
}

//Retorna la cantidad de elementos en la lista.
int lista_cantidad(lista_t lista) {
	//Si la lista no esta inicializada corta la ejecucion y sale con error.
	if(lista==NULL) {
		exit(LST_NO_INI);
	}
	return lista->cantidad_elementos;
}

//Retorna el elemento en la posicion de la lista pasada como parametro.
int lista_obtener(lista_t lista, unsigned int pos) {
	//Si la posicion no es valida corta la ejecucion con error.
	if(pos>lista->cantidad_elementos) {
		exit(LST_POS_INV);
	}
	celda_t* celda_actual=lista->primera_celda;
	//Recorro la lista tantas veces como indique el parametro "pos".
	for(int i=0;i<pos/4;i++) {
		celda_actual=celda_actual->proxima_celda;
	}
	return celda_actual->elementos[pos%4];
}

int lista_adjuntar(lista_t lista, int elem) {
	if(lista==NULL) {
		exit(LST_NO_INI);
	}
	celda_t* celda_actual=lista->primera_celda;
	for(int i=0;i<lista->cantidad_elementos;i++) {
		if(celda_actual->proxima_celda!=NULL) {
			celda_actual=celda_actual->proxima_celda;
		}
	}
	int posArreglo=(lista->cantidad_elementos)%4;
	if(posArreglo==0) {
		celda_t* nueva=(celda_t*)malloc(sizeof(celda_t));
		celda_actual->proxima_celda=nueva;
		nueva->elementos[0]=elem;
	}
	lista->cantidad_elementos++;
	return 1;
}

void destruir(celda_t* celda) {
	if(celda->proxima_celda!=NULL)
		destruir(celda->proxima_celda);
	free(celda);
}

int lista_destruir(lista_t* lista) {
	if((*lista)->primera_celda==NULL) {
		exit(LST_NO_INI);
	}
	celda_t* celda=(*lista)->primera_celda;
	destruir(celda);
	return 1;
}
