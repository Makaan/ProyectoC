#include <stdio.h>
#include "pila.h"
#include "pila.c"
int main(){
   pila_t mipila=pila_crear();
   char* aux;
   printf("Vacia: %d\n",pila_vacia(mipila));
   int i; int j;
   for(i=1;i<=5;i++){
      scanf("%s",aux);
      if (apilar(&mipila,aux)){
          printf("%d Apilando: %s\n",i,aux);
          printf("Tope: %s\n",tope(mipila));
      }
   }

   for(j=1;j<=6;j++){
      printf("Desapilando: %s\n",desapilar(&mipila));
   }
   printf("---------------------------\n");
   //printf("Tope: %s\n",tope(mipila));
   //printf("Vacia: %d\n",pila_vacia(mipila));

   return 0;
}

