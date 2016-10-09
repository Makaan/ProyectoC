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

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

int es_digito(char caracter){
    int toreturn=0;
    switch(caracter){
        case '0'...'9': toreturn=1;
    }
    return toreturn;
}

int caracter_valido(char caracter){
    int toreturn=0;
    switch(caracter){
        case '+': toreturn=1;
        case '-': toreturn=1;
        case '*': toreturn=1;
        case '/': toreturn=1;
        case ')': toreturn=1;
        case '(': toreturn=1;
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
    char* cadena=malloc(CADENA_MAX);
    printf(">>>EN OBTENER_CADENA EL CARACTER ES: %c\n", caracter);
    if (caracter=='+') cadena="+";
    if (caracter=='+') cadena="-";
    if (caracter=='+') cadena="*";
    if (caracter=='+') cadena="/";
    if (caracter=='+') cadena=")";
    if (caracter=='+') cadena="(";
    return cadena;
}

int suma(lista_t lista){
    int resultado=0;
    int i;
    int cant=lista_cantidad(lista);
    if (cant<2) exit(OPND_INSUF);
    for (i=0;i<cant;i++){
        resultado=resultado+lista_obtener(lista,i);
    }
    lista_destruir(lista);
    return resultado;
}

int producto(lista_t lista){
    int resultado=0;
    int i;
    int cant=lista_cantidad(lista);
    if (cant<2) exit(OPND_INSUF);
    for (i=0;i<cant;i++){
        resultado=resultado*lista_obtener(lista,i);
    }
    lista_destruir(lista);
    return resultado;
}

int resta(lista_t lista){
    int resultado=0;
    int i;
    int cant=lista_cantidad(lista);
    if (cant<2) exit(OPND_INSUF);
    if (cant>2) exit(OPND_DEMAS);

    resultado=lista_obtener(lista,1)-lista_obtener(lista,0);
    lista_destruir(lista);
    return resultado;
}

int division(lista_t lista){
    int resultado=0;
    int i;
    int cant=lista_cantidad(lista);
    if (cant<2) exit(OPND_INSUF);
    if (cant>2) exit(OPND_DEMAS);

    resultado=lista_obtener(lista,1)/lista_obtener(lista,0);
    lista_destruir(lista);
    return resultado;
}




void apilar_cadena(char* cadena){

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
                //Si se introduce un numero no entreo (con coma o punto) sale con error
                if ( (*(cadena+i)=='.')||(*(cadena+i)==',') )
                    exit (OPND_INV);
                //Apilo el numero
                apilar(&mipila,num);
            }
            else{
                 //Apilo el caracter valido que no es numero
                 if (caracter_valido(*(cadena+i))){
                    char c=(*(cadena+i));
                    printf("> Caracter es %c\n",c);
                    printf("> &Caracter es %s\n",&c);
                    apilar(&mipila,&c);
                    i++;
                 }else
                    exit (OPRD_INV);

            }
            printf("\n>Tope: %s\n", tope(mipila) );
        }
        else{
            //Aumento i cuando el caracter es un espacio
            i++;
        }
    }
    if(cont_parentesis!=0) exit(EXP_MALF);

    printf("********Comienzo**a**evaluar*******\n\n");
    char* caracter=malloc(CADENA_MAX);

    while (!pila_vacia(mipila)){
        printf("\n>Tope: -%s-\n", tope(mipila) );
        caracter=desapilar(&mipila);
        printf(">>Desapile caracter: -%s-\n",caracter);
    }


    if (caracter==")"){

        while(!pila_vacia(mipila)){

            caracter=desapilar(&mipila);

            lista_t milista=lista_crear();

            while ( (caracter!="(") && (caracter!=")") && (caracter!="+") &&(caracter!="*")&&(caracter!="-")&&(caracter!="/")){

                int num=atoi(caracter);
                lista_adjuntar(milista,num);
                caracter=desapilar(&mipila);
            }
            int resultado=0;
            switch (*caracter){
                case '+': resultado=suma(milista);
                case '*': resultado=producto(milista);
                case '/': resultado=division(milista);
                case '-': resultado=resta(milista);
            }
            char* res_cadena;
            printf("\nResultado: %d\n",resultado);
            itoa(resultado,&res_cadena);
            apilar(&mipila,res_cadena);

        }

    }



}


int main(int argc, char** argv){
    char *cadena = malloc (CADENA_MAX);
    fgets (cadena, CADENA_MAX, stdin);

    printf("Cadena leida: %s\n",cadena);
    printf("------------------------------ \n");
    printf("-------Empiezo-a-apilar------- \n");
    printf("------------------------------ \n");

    apilar_cadena(cadena);
    return 0;
}
