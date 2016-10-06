#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

typedef struct pila {
   char* elemento;
   struct pila* proximo_elemento;
} *pila_t;

/**Retorna una pila nueva vacía**/
pila_t  pila_crear();

/**Retorna el string que se encuentra en el tope de la pila. Si la
pila se enceuntra vacia, aborta su ejecucion con exit status PIL_VACIA**/
char* tope(pila_t pila);

/**Elimina el string que se encuentra en el tope de la pila y lo retorna. Si la
pila se encuentra vacia, aborta su ejecucion con exit status PIL_VACIA**/
char* desapilar(pila_t* pila);

/**Inserta el string str en el tope de la pila. Retorna verdadero si la insercion fue exitosa,
falso en caso contrario. Si la pila no se encuentra inicializada, finaliza la ejecucion con
exit status PIL_NO_INI**/
int apilar(pila_t* pila, char* str);

/**Retorna verdadero si la pila esta vacia, falso en caso contrario. Si la pila
no se encuentra inicializada, finaliza la ejecucion con exit status PIL_NO_INI**/
int pila_vacia(pila_t pila);

#endif // PILA_H_INCLUDED
