#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
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


//Codigo obtenido de: http://stackoverflow.com/a/9660930"
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
    }
    lista_destruir(&lista);
    return resultado;
}

int resta(lista_t lista){
    int resultado=0;
    int cant=lista_cantidad(lista);
    if (cant<2) exit(OPND_INSUF);
    if (cant>2) exit(OPND_DEMAS);

    resultado=lista_obtener(lista,0)-lista_obtener(lista,1);
    lista_destruir(&lista);
    return resultado;
}

int division(lista_t lista){
    int resultado=0;
    int cant=lista_cantidad(lista);
    if (cant<2) exit(OPND_INSUF);
    if (cant>2) exit(OPND_DEMAS);

    resultado=lista_obtener(lista,0)/lista_obtener(lista,1);
    lista_destruir(&lista);
    return resultado;
}

int desapilar_y_evaluar(pila_t pila){

    //printf("Entro a desapilar y evaluar\n");

    char* caracter=malloc(CADENA_MAX);
    char* caracter_aux=malloc(CADENA_MAX);

    int resultado=0;

    pila_t pila_aux=pila_crear();

    while(!pila_vacia(pila)){

        //printf("Entro a While\n");
        caracter=desapilar(&pila);
        if ((caracter!="+") &&(caracter!="*")&&(caracter!="-")&&(caracter!="/")){
            //printf("Antes de apilar en pila_aux|Caracter=%s\n",caracter);
            if (caracter=="(") {
                //printf("Entre al if '('\n");
                caracter_aux=desapilar(&pila_aux);
                //printf("En if '(' caracter_aux=%s\n",caracter_aux);
                if (tope(pila_aux)==")"){
                    //printf("En if '(' tope(pila_aux)=%s\n",tope(pila_aux));
                    desapilar(&pila_aux);
                    apilar(&pila_aux,caracter_aux);
                }
                else{
                    exit(OPRD_INV);
                }
            }
            else{
                apilar(&pila_aux,caracter);
            }
        }
        else{
            //printf("\nCaracter=%s | Caracter_aux=%s\n\n",caracter,caracter_aux);
            if (tope(pila_aux)==")") exit(OPND_INSUF);
            lista_t milista=lista_crear();
            while(tope(pila_aux)!=")"){

                caracter_aux=desapilar(&pila_aux);
                int num=atoi(caracter_aux);
                lista_adjuntar(milista,num);
                //printf("\n>En while listar| Caracter=%s | Caracter_aux=%s\n\n",caracter,caracter_aux);
            }

            //printf("Antes de desapilar pila_aux|Caracter_aux=%s\n",caracter_aux);
            desapilar(&pila_aux);

            if (caracter=="+") resultado=suma(milista);
            if (caracter=="*") resultado=producto(milista);
            if (caracter=="/") resultado=division(milista);
            if (caracter=="-") resultado=resta(milista);

            char* resultado_aux=malloc(CADENA_MAX);
            resultado_aux=itoa(resultado,resultado_aux);
            //printf("En else | Despues de itoa | Resultado_aux=%s\n",resultado_aux);

            apilar(&pila_aux,resultado_aux);
            desapilar(&pila);
        }

    }
    //printf(">Tope(pila_aux) al final=%s\n",tope(pila_aux));
    int toreturn=atoi(tope(pila_aux));
    return toreturn;
}

void apilar_cadena(char* cadena){

    pila_t mipila=pila_crear();

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
        }
        else{
            //Aumento i cuando el caracter es un espacio
            i++;
        }
    }
    if(cont_parentesis!=0) exit(EXP_MALF);

    int resultado;
    resultado=desapilar_y_evaluar(mipila);
    printf("%d\n",resultado);
}

void mostrar_ayuda(){
    printf("El programa evalúa expresiones aritméticas por entrada estándar interpretadas en preorden.\n");
    printf("Las expresiones aritméticas son suma, resta, división y multiplicación.\n\n");
    printf("Las expresiones aritméticas utilizan la siguiente sintaxis:\n");
    printf("(<operador> <operando1> <operando2> ... <operandoN>)\n");
    printf("Donde un <operandoI> puede ser de la forma:\n");
    printf("(<operando>)\n");
    printf("Con <operando> un número entero, que va a ser procesado como <operando> sin importar\n");
    printf("la cantidad de parentesis que lo rodea, siempre y cuando los parentesis esten bien formados.\n\n");
    printf("Todas las operaciones deben recibir al menos dos operandos para poder ser evaluadas.\n");
    printf("Las operaciones suma y multiplicación pueden recibir más de dos operandos.\n\n");
    printf("Un caso especial de expresion a evaluar es:\n");
    printf("(<operando>)\n");
    printf("Donde <operando> es un número entero, y es el mismo resultado de la expresión.\n\n");
    printf("El parámetro -h muestra esta ayuda.\n");
}

int main(int argc, char** argv){
    int argumento;
    while ((argumento = getopt (argc, argv, "h")) != -1){
        switch (argumento){
            case 'h':{
                mostrar_ayuda();
                exit(0);
            }
            default: {
                printf("Argumentos incorrectos\n");
                mostrar_ayuda();
                exit(0);
            }
        }
    }
    char *cadena = malloc (CADENA_MAX);
    printf("Ingrese la expresión\n");
    fgets (cadena, CADENA_MAX, stdin);
    apilar_cadena(cadena);
    printf("\nFin del programa\n");
    return 0;
}
