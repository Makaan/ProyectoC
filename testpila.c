#include <stdio.h>
#include "pila.h"
#include "pila.c"
int main(){
   pila_t mipila=pila_crear();
   char* aux;
   printf("Vacia? %d\n",pila_vacia(mipila));
   int i; int j;

   apilar(&mipila,"1");
   printf("Tope: %s\n",tope(mipila));
   apilar(&mipila,"2");
   printf("Tope: %s\n",tope(mipila));
   apilar(&mipila,"3");
   printf("Tope: %s\n",tope(mipila));
   apilar(&mipila,"4");
   printf("Tope: %s\n",tope(mipila));
   apilar(&mipila,"5");
   printf("Tope: %s\n",tope(mipila));

   printf("---------------------------\n");
   printf("---------------------------\n");
   for(j=1;j<=10;j++){
      aux=desapilar(&mipila);
      printf("Desapilo: %s\n",aux);
   }
   printf("---------------------------\n");
   printf("Vacia? %d\n",pila_vacia(mipila));
   return 0;
}


