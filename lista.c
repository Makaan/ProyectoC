//Lista.c
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

const int LST_NO_INI=3;
const int LST_POS_INV=4;



//Retorna una nueva lista vacia.
lista_t lista_crear() {
	//Asigno la cantidad de memoria necesaria.
  lista_t lista=(lista_t) malloc(sizeof(struct lista_eficiente));

  //Creo la lista.
	lista->cantidad_elementos=0;
	lista->primera_celda=NULL;

  return lista;
}

//Inserto un elemento en una posicion pasada como parametro
//Si la posicion es mayor a la cantidad de elementos, finaliza la ejecucion con error LST_POS_INV
//Si la posicion es igual a la cantidad de elementos, inserto al final.
int lista_insertar(lista_t lista, unsigned int pos, int elem) {
	//Si la posicion es mayor que la cantidad de elementos salgo con error de posicion invalida.
	if(pos>lista->cantidad_elementos)
		exit(LST_POS_INV);

	//Obtengo la celda donde debo insertar.
	int posCelda=pos/4;
	if(lista->primera_celda==NULL) {
        lista->primera_celda=(celda_t*) malloc(sizeof(celda_t));
	}
	celda_t* celda_actual=lista->primera_celda;

	//Recorro hasta encontrar la celda donde agregar.
	int i;
	for(i=0;i<posCelda;i++) {
		//Si esa celda no existe la creo.
		if((celda_actual->proxima_celda)==NULL) {
			celda_t* nuevaCelda=(celda_t*)malloc(sizeof(celda_t));
			nuevaCelda->proxima_celda=NULL;
			celda_actual->proxima_celda=nuevaCelda;

		}
		celda_actual=celda_actual->proxima_celda;
	}

	int posArreglo=pos%4;
	if(pos==(lista->cantidad_elementos))
		lista->cantidad_elementos++;

	celda_actual->elementos[posArreglo]=elem;

    printf("lista_insertar\n");
	return 0;
}

//Elimina un elemento de la lista segun la posicion pasada como parametro
//Si la posicion pasada es mayor que la cantidad de elementos, finaliza la ejecucion con error LST_POS_INV
int lista_eliminar(lista_t lista, unsigned int pos) {
	//Salgo con error si la posicion no existe.
	if(pos>=lista->cantidad_elementos) {
		exit(LST_POS_INV);
	}
	//Obtengo la celda donde voy a eliminar
	int posCelda=pos/4;
	celda_t* celda_actual=lista->primera_celda;
	int i;
	//Recorro hasta llegar a esa celda
	for(i=0;i<posCelda;i++) {
		celda_actual=celda_actual->proxima_celda;
	}
	//Obtengo la posicion del arreglo de esa celda donde eliminar.
	int posArreglo=pos%4;
	printf("arreglo %d elem %d\n",posArreglo,(celda_actual->elementos[posArreglo]));
	//Acomodo todos los elementos restantes del arreglo para cerrar el espacio creado por elemento eliminado.
	while(pos<lista->cantidad_elementos) {
		//Muevo cada elemento i+1 al i en el arreglo de la celda.
		for(;posArreglo<4 && (pos<lista->cantidad_elementos);posArreglo++) {
			celda_actual->elementos[posArreglo]=celda_actual->elementos[posArreglo+1];
			pos++;
		}
		//Cuando termino con el arreglo de esa celda me muevo a la celda siguiente1
		if(pos<lista->cantidad_elementos) {
			celda_actual->elementos[3]=celda_actual->proxima_celda->elementos[0];
			celda_actual=celda_actual->proxima_celda;
			posArreglo=0;
		}
	}
	lista->cantidad_elementos--;
	return 0;

}

//Retorna la cantidad de elementos de la lista.
//Si la lista no esta inicializada finaliza la ejecucion con error LST_NO_INI
int lista_cantidad(lista_t lista) {
	//Si la lista no esta inicializada corta la ejecucion y sale con error.
	if(lista==NULL) {
		exit(LST_NO_INI);
	}
	return lista->cantidad_elementos;
}

//Retorna el elemento en la posicion pasada como parametro
//Si la posicion es mayor a la cantidad de elementos de la lista finaliza la ejecucion con error LST_POS_INV
int lista_obtener(lista_t lista, unsigned int pos) {

	//Si la lista no esta inicializada salgo con error.
	if(lista==NULL){
		exit(LST_NO_INI);
	}
	//Si la posicion no es valida corta la ejecucion con error.
	if(pos>(lista->cantidad_elementos-1)) {
		exit(LST_POS_INV);
	}
	celda_t* celda_actual=lista->primera_celda;
	//Recorro la lista tantas veces como indique el parametro "pos".
	int i;
	for(i=0;i<pos/4;i++) {
		celda_actual=celda_actual->proxima_celda;
	}
	return celda_actual->elementos[pos%4];
}

int lista_adjuntar(lista_t lista, int elem) {
	//Uso el metodo lista_insertar con la cantidad de elementos de la lista como posicion
	int to_return=lista_insertar(lista,(lista->cantidad_elementos),elem);
	printf("lista %u size %d elem %d\n",lista,lista_cantidad(lista),elem );
	return to_return;
}

//Metodo recursivo que recorre todas las celdas y les hace free cuando vuelve de la recursion
void destruir(celda_t* celda) {
	//Si hay mas celdas llamo recursivamente
	printf("Destruir. Celda: %u %u %d\n",celda,(celda->proxima_celda),(celda->proxima_celda!=NULL));
	if((celda->proxima_celda)!=NULL){
    printf("llamo recursivamente\n");   
		destruir(celda->proxima_celda);
    }
    printf("x\n");
	free(celda);
}

//Agrego un elemento al final de la lista
//Si la lista no esta inicializada finaliza la ejecucion con error LST_NO_INI
int lista_destruir(lista_t* lista) {
	if((*lista)->primera_celda==NULL) {
		exit(LST_NO_INI);
	}
	//Obtengo la primera celda.
	celda_t* celda=(*lista)->primera_celda;
	//Lamo recursivamente para liberar el espacio de las celdas.
	printf("Antes de destruir en lista\n");
	destruir(celda);
	printf("Despues de destruir en lista\n");
	free(*lista);

	return 0;
}
