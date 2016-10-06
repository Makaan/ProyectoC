#include <stdio.h>
#include "pila.h"

const int PIL_NO_INI = 9;
const int PIL_VACIA = 10;

/**Retorna una pila nueva vacía**/
pila_t  pila_crear(){
   return NULL;
}

/**Retorna el string que se encuentra en el tope de la pila. Si la
pila se enceuntra vacia, aborta su ejecucion con exit status PIL_VACIA**/
char* tope(pila_t pila){
   if (!pila_vacia(pila))
      return pila->elemento;
   else exit(PIL_VACIA);
}

/**Elimina el string que se encuentra en el tope de la pila y lo retorna. Si la
pila se encuentra vacia, aborta su ejecucion con exit status PIL_VACIA**/
char* desapilar(pila_t* pila){
   char* aux; pila_t tofree;
   if (pila_vacia(*pila)) {
      exit(PIL_VACIA);
   }
   else{
         aux=(*pila)->elemento;
         if ((*pila)->proximo_elemento!=NULL){
            tofree=(*pila);
            (*pila)=(*pila)->proximo_elemento;
            free(tofree);
         }
         (*pila)->elemento=NULL;
         return aux;
    }
}

/**Inserta el string str en el tope de la pila. Retorna verdadero si la insercion fue exitosa,
falso en caso contrario. Si la pila no se encuentra inicializada, finaliza la ejecucion con
exit status PIL_NO_INI**/
int apilar(pila_t* pila, char* str){
   if(pila==NULL) {
      exit(PIL_NO_INI);
   }
   int toreturn=0;
   printf("antes 1 if\n");
   if (str!=NULL){
      printf("antes 2 if\n");
      pila_t nueva=(pila_t)malloc(sizeof(pila_t));
      nueva->elemento=str;
      nueva->proximo_elemento=(*pila);
      printf("antes asignacion\n");
      (*pila)=nueva;
      toreturn=1;
    }
   return toreturn;
}

/**Retorna verdadero si la pila esta vacia, falso en caso contrario. Si la pila
no se encuentra inicializada, finaliza la ejecucion con exit status PIL_NO_INI**/
int pila_vacia(pila_t pila){
   if (pila!=NULL)
      return 1;
   else
      return 0;
}
