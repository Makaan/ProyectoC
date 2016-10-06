#include "lista.c"

typedef struct lista_eficiente {
	unsigned int cantidad_elementos;
	celda_t* primera_celda;
} *lista_t;

typedef struct celda {
	int elementos[4];
	struct celda* proxima_celda;
} celda_t;

lista_t lista_crear();

int lista_insertar(lista_t lista, unsigned int pos, int elem);##

int lista_eliminar(lista_t lista, unsigned int pos);

int lista_cantidad(lista_t lista);

int lista_obtener(lista_t lista, unsigned int pos);

int lista_adjuntar(lista_t lista, int elem);

int lista_destruir(lista_t* lista);