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
    if (caracter=='+') cadena="+";
    if (caracter=='-') cadena="-";
    if (caracter=='*') cadena="*";
    if (caracter=='/') cadena="/";
    if (caracter==')') cadena=")";
    if (caracter=='(') cadena="(";
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
    lista_destruir(&lista);

    return resultado;
}

int producto(lista_t lista){
    int resultado=1;
    int i;
    int cant=lista_cantidad(lista);
    if (cant<2) exit(OPND_INSUF);
    for (i=0;i<cant;i++){
        resultado=resultado*lista_obtener(lista,i);
        printf("Producto> RES=%d Lista(i)=%d\n",resultado,lista_obtener(lista,i));
    }
    lista_destruir(&lista);
    return resultado;
}

int resta(lista_t lista){
    int resultado=0;
    int i;
    int cant=lista_cantidad(lista);
    if (cant<2) exit(OPND_INSUF);
    if (cant>2) exit(OPND_DEMAS);

    resultado=lista_obtener(lista,0)-lista_obtener(lista,1);
    lista_destruir(&lista);
    return resultado;
}

int division(lista_t lista){
    int resultado=0;
    int i;
    int cant=lista_cantidad(lista);
    if (cant<2) exit(OPND_INSUF);
    if (cant>2) exit(OPND_DEMAS);

    resultado=lista_obtener(lista,0)/lista_obtener(lista,1);
    lista_destruir(&lista);
    return resultado;
}

int desapilar_y_evaluar(pila_t pila){

    char* caracter=malloc(CADENA_MAX);
    char* caracter_aux=malloc(CADENA_MAX);

    int resultado=0;

    pila_t pila_aux=pila_crear();

    while(!pila_vacia(pila)){
        printf(">tope pila=%s\n",tope(pila));

        caracter=desapilar(&pila);
        if ((caracter!="+") &&(caracter!="*")&&(caracter!="-")&&(caracter!="/")){
            printf("Apilo caracter: %s\n",caracter);
            apilar(&pila_aux,caracter);
        }
        else{
            if (tope(pila_aux)==")") exit(OPND_INSUF);
            lista_t milista=lista_crear();
            while(tope(pila_aux)!=")"){
                caracter_aux=desapilar(&pila_aux);
                int num=atoi(caracter_aux);
                lista_adjuntar(milista,num);
            }
            desapilar(&pila_aux);
            if (caracter=="+") resultado=suma(milista);
            if (caracter=="*") resultado=producto(milista);
            if (caracter=="/") resultado=division(milista);
            if (caracter=="-") resultado=resta(milista);

            char* res_cadena=itoa(resultado,res_cadena);
            printf("Resultado parcial: %d\n",resultado);
            apilar(&pila_aux,res_cadena);
            printf("Res_Cadena: %s\n",res_cadena);
            desapilar(&pila);
        }

    }

    printf(">tope final pila_aux=%s\n",tope(pila_aux));

    int toreturn=atoi(tope(pila_aux));
    return toreturn;
}

/*void desapilar_y_evaluar2(pila_t mipila){

    printf("********Comienzo**a**evaluar*******\n\n");

    char* caracter=malloc(CADENA_MAX);

    int resultado=0;

    caracter=desapilar(&mipila);
    printf(">Antes primer while. Desapile. Caracter=%s\n",caracter);

    if (caracter==")"){

        caracter=desapilar(&mipila);

        if (caracter==")"){
            desapilar_y_evaluar(mipila);
        }
        else{
            while ( ((!pila_vacia(mipila)) || (caracter!="(")) ) {
                printf(">Primer while. Desapile. Caracter=%s. Creo lista.\n",caracter);
                lista_t milista=lista_crear();
                while ( (caracter!="(") && (caracter!=")") && (caracter!="+") &&(caracter!="*")&&(caracter!="-")&&(caracter!="/")){
                    printf(">Seg while. Caracter=%s\n",caracter);
                    int num=atoi(caracter);
                    printf(">Seg while. Converti a Int. Num=%d \n",num);
                    lista_adjuntar(milista,num);
                    printf(">Seg while. Enliste Num=%d \n",num);
                    caracter=desapilar(&mipila);
                    printf(">Seg while. Desapile: Caracter=%s \n",caracter);
                }
                printf(">Primer while. Antes de Switch. Caracter (deberia ser operador)=%s \n",caracter);
                if (caracter=="+")resultado=suma(milista);
                if (caracter=="*") resultado=producto(milista);
                if (caracter=="/") resultado=division(milista);
                if (caracter=="-") resultado=resta(milista);
                printf(">Primer while. Despues de Switch.\n\n ||||||||||||||||||||||Resultado:%d||||||||||||||||||\n\n",resultado);
                caracter=desapilar(&mipila);
                printf(">Primer while. Despues de resultado. Desapile: Caracter[deberia ser '(']= %s \n",caracter);
                char* res_cadena=itoa(resultado,res_cadena);
                printf(">Primer while. Despues de ITOA. Res Cadena=%s \n",res_cadena);
                apilar(&mipila,res_cadena);
                printf(">Apile. Res-Cadena=%s | Cadena=%s \n",res_cadena,caracter);
                }
            }
    }

}

*/

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
                    apilar(&mipila,obtener_cadena(c));
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

    int resultado=desapilar_y_evaluar(mipila);

    printf("@@@@@@@@ RESULTADO = %d @@@@@@@@@",resultado);
}


int main(int argc, char** argv){
    char *cadena = malloc (CADENA_MAX);
    fgets (cadena, CADENA_MAX, stdin);

    printf("Cadena leida: %s\n",cadena);

    apilar_cadena(cadena);
    return 0;
}
