typedef struct celda {
	//PREGUNTAR
	int elementos[4];
	struct celda* proxima_celda;
} celda_t;

typedef struct lista_eficiente {
	unsigned int cantidad_elementos;
	celda_t* primera_celda;
} *lista_t;

