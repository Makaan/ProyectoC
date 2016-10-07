#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "pila.h"
#include "lista.c"
#include "pila.c"

#define CADENA_MAX 512

const int EXP_MALF=2;
const int OPND_DEMAS=5;
const int OPND_INSUF=6;
const int OPND_INV=7;
const int OPRD_INV=8;

int es_digito(char caracter){
    int toreturn=0;
    switch(caracter){
        case '0'...'9': toreturn=1;
    }
    return toreturn;
}

int operador_valido(char caracter){
    int toreturn=0;
    switch(caracter){
        case '+': toreturn=1;
        case '-': toreturn=1;
        case '*': toreturn=1;
        case '/': toreturn=1;
    }
    return toreturn;
}

/*
char* eliminar_espacios(char* cadena)
{
   char* toreturn=malloc(CADENA_MAX);
   int largo=strlen(cadena);
   int i=0;
   int j=0;

   while(i<largo-1){


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
*/

char* obtener_cadena(char caracter){
    return &caracter;
}

pila_t apilar_cadena(char* cadena){

    pila_t mipila=pila_crear();

    char* num=malloc(CADENA_MAX);
    int largo=strlen(cadena);
    int i=0;
    int j;
    int cont_parentesis=0;
    while(i<largo-1){
        if(*(cadena+i)=='(') {
            cont_parentesis++;
        }
        if(*(cadena+i)==')') {
            cont_parentesis--;
        }

        //Si no es espacio...
        if (*(cadena+i)!=' '){

            //Si es un digito...
            if ( es_digito(*(cadena+i)) ){
                //Debo hacer malloc para evitar que los numeros queden con los ultimos digitos del numero anterior calculado
                char* num=malloc(CADENA_MAX);
                j=0;
                //Mientras sea digito lo guardo en una string aux
                while(es_digito(*(cadena+i))){
                    *(num+j)=*(cadena+i);
                    j++;
                    i++;
                }
                //Apilo el numero
                apilar(&mipila,num);
            }
            else{
                 //Apilo el caracter que no es numero
                 apilar(&mipila, obtener_cadena(*(cadena+i)));
                 i++;
            }
            printf(">Tope: %s\n", tope(mipila) );
        }
        else{
            //Aumento i cuando el caracter es un espacio
            i++;
        }
    }
    if(cont_parentesis!=0)
        exit(EXP_MALF);
    return mipila;
}


int main(int argc, char** argv){
    char *cadena = malloc (CADENA_MAX);
    fgets (cadena, CADENA_MAX, stdin);

    printf("Cadena leida: %s\n",cadena);
    printf("------------------------------ \n");
    printf("-------Empiezo-a-apilar------- \n");
    printf("------------------------------ \n");
    pila_t mipila=apilar_cadena(cadena);

    printf("------------------------------ \n");
    printf("------Empiezo-a-desapilar----- \n");
    printf("------------------------------ \n");
    while(!pila_vacia(mipila)){
        printf(">Desapilo: %s\n",desapilar(&mipila));
    }

    return 0;
}
