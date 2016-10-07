#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "pila.h"
#include "lista.c"
#include "pila.c"

#define CADENA_MAX 512

int es_numero(char caracter){
    int toreturn=0;
    switch(caracter){
        case '0'...'9': toreturn=1;
    }
    return toreturn;
}

int caracter_valido(char caracter){
    int toreturn=0;
    switch(caracter){
        case '0'...'9': toreturn=1;
        case '+': toreturn=1;
        case '-': toreturn=1;
        case '*': toreturn=1;
        case '/': toreturn=1;
        case '(': toreturn=1;
        case ')': toreturn=1;
    }
    return toreturn;
}

char* eliminar_espacios(char* cadena)
{
   char* toreturn=malloc(CADENA_MAX);
   int largo=strlen(cadena);
   int i=0;
   int j=0;
   while(i<largo){
        if (*(cadena+i)!=' ') {
            *(toreturn+j)=*(cadena+i);
            if ( !caracter_valido( *(cadena+i+1) ) ){
                *(toreturn+j+1)=' ';
                j++;
            }
            j++;
        }
        i++;
   }
   return toreturn;
}

void apilar_cadena(char* cadena){
    printf("\nCadena que voy a apilar: %s\n",cadena);

    pila_t mipila=pila_crear();

    char car;
    char* num=malloc(CADENA_MAX);
    int largo=strlen(cadena)-1;
    int i=0;
    int j;
    while(i<largo){
        if ( es_numero(*(cadena+i)) ){
            j=0;
            while(es_numero(*(cadena+i))){
                *(num+j)=*(cadena+i);
                j++;
                i++;
                printf(">char=%c | >j=%d | >i=%d",*(num+j),j,i);
            }
            printf("Num: %s\n",num);
            apilar(&mipila,num);
            printf("Tope: %s\n",mipila);
        }
        apilar(&mipila,*(cadena+i));
        printf("Tope: %s\n",mipila);
        i++;
    }
}


int main(int argc, char** argv){
    char *cadena = malloc (CADENA_MAX);
    fgets (cadena, CADENA_MAX, stdin);

    printf("Cadena leida: %s\n",cadena);
    cadena=eliminar_espacios(cadena);
    printf("Cadena sin espacios: %s\n",cadena);
    apilar_cadena(cadena);

    return 0;
}
