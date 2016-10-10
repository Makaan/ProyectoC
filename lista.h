#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

//Estructura celda que modela un componente de la lista que almacena hasta cuatro elementos.
typedef struct celda {
	int elementos[4];
	struct celda* proxima_celda;
} celda_t;

//Cabecera de la estructura lista, posee una referencia a la primera celda y la cantidad de elementos de la lista.
typedef struct lista_eficiente {
	unsigned int cantidad_elementos;
	celda_t* primera_celda;
} *lista_t;

//Retorna una nueva lista vacia
lista_t lista_crear();

//Inserto un elemento en una posición pasada como parametro
//Si la posicion es mayor a la cantidad de elementos, finaliza la ejecucion con error LST_POS_INV
//Si la posicion es igual a la cantidad de elementos, inserto al final.
int lista_insertar(lista_t lista, unsigned int pos, int elem);

//Elimina un elemento de la lista segun la posicion pasada como parametro
//Si la posicion pasada es mayor que la cantidad de elementos, finaliza la ejecucion con error LST_POS_INV
int lista_eliminar(lista_t lista, unsigned int pos);

//Retorna la cantidad de elementos de la lista.
//Si la lista no esta inicializada finaliza la ejecucion con error LST_NO_INI
int lista_cantidad(lista_t lista);

//Retorna el elemento en la posicion pasada como parametro
//Si la posicion es mayor a la cantidad de elementos de la lista finaliza la ejecucion con error LST_POS_INV 
int lista_obtener(lista_t lista, unsigned int pos);

//Agrego un elemento al final de la lista
//Si la lista no esta inicializada finaliza la ejecucion con error LST_NO_INI
int lista_adjuntar(lista_t lista, int elem);

//Libero todo el espacio ocupado por la lista, incluyendo las celdas.
int lista_destruir(lista_t* lista);

#endif // LISTA_H_INCLUDED