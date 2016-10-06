#include <stdio.h>
#include "pila.h"
#include "pila.c"
int main(){
   pila_t mipila=pila_crear();
   char* aux;
   printf("Vacia: %d\n",pila_vacia(mipila));
   for(int i=1;i<=10;i++){
      scanf("%s",aux);
      if (apilar(&mipila,aux)){
          printf("%d Apilando: %s\n",i,aux);
          printf("Tope: %s\n",tope(mipila));
      }
   for(i=1;i<=10;i++){
      printf("Desapilando: &d\n",desapilar(mipila));
   }

   }
   printf("---------------------------\n");
   printf("Tope: %s\n",tope(mipila));
   printf("Vacia: %d\n",pila_vacia(mipila));

   return 0;
}

