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
/**
Funcion que retorna si el caracter pasado por parametro es un digito de '0' a '9'
Retorna 1 si caracter es un digito, 0 en caso contrario.
**/
int es_digito(char caracter){
    int toreturn=0;
    switch(caracter){
        case '0'...'9': toreturn=1;
    }
    return toreturn;
}

/**
Funcion que retorna si el caracter pasado por parametro es un caracter que no
es un digito y es valido para una expresion.
Retorna 1 si caracter es un caracter, no digito, valido, 0 en caso contrario.
**/
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

/**
Funcion que retorna un string equivalente al caracter pasado por parametro
Retorna una string equivalente al caracter caracter.
**/
char* obtener_cadena(char caracter){
    //Reservo espacio para la string que voy a retornar.
    char* cadena=malloc(CADENA_MAX);
    if (caracter=='+') cadena="+";
    if (caracter=='-') cadena="-";
    if (caracter=='*') cadena="*";
    if (caracter=='/') cadena="/";
    if (caracter==')') cadena=")";
    if (caracter=='(') cadena="(";
    return cadena;
}

/**
Funcion que suma los elementos de la lista pasada por parametro.
Retorna la suma de todos los elementos de la lista lista.
Si la cantidad de elementos de la lista es menor a 2, el programa sale con error OPND_INSUF.
**/
int suma(lista_t lista){
    int resultado=0;
    int i;
    int cant=lista_cantidad(lista);
    //Si la cantidad de elementos de la lista es menor a 2
    //los operandos son insuficientes y salgo con el error correspondiente
    if (cant<2) exit(OPND_INSUF);

    for (i=0;i<cant;i++){
        resultado=resultado+lista_obtener(lista,i);
    }
    //Destruyo la lista luego calcular el resultado
    lista_destruir(&lista);
    return resultado;
}

/**
Funcion que multiplica los elementos de la lista pasada por parametro.
Retorna el producto de todos los elementos de la lista lista.
Si la cantidad de elementos de la lista es menor a 2, el programa sale con error OPND_INSUF.
**/
int producto(lista_t lista){
    int resultado=1;
    int i;
    int cant=lista_cantidad(lista);
    //Si la cantidad de elementos de la lista es menor a 2
    //los operandos son insuficientes y salgo con el error correspondiente
    if (cant<2) exit(OPND_INSUF);
    for (i=0;i<cant;i++){
        resultado=resultado*lista_obtener(lista,i);
    }
    //Destruyo la lista luego calcular el resultado
    lista_destruir(&lista);
    return resultado;
}

/**
Funcion que resta los elementos de la lista pasada por parametro.
Retorna la resta de los primeros dos elementos de la lista.
Si la cantidad de elementos de la lista es menor a 2, el programa sale con error OPND_INSUF.
Si la cantidad de elementos de la lista es mayor a 2, el programa sale con error OPND_DEMAS.
**/
int resta(lista_t lista){
    int resultado=0;
    int cant=lista_cantidad(lista);

    //Si la cantidad de elementos de la lista es menor a 2
    //los operandos son insuficientes y salgo con el error correspondiente
    if (cant<2) exit(OPND_INSUF);
    //Si la cantidad de elementos de la lista es mayor a 2
    //los operandos son demasiados y salgo con el error correspondiente
    if (cant>2) exit(OPND_DEMAS);

    resultado=lista_obtener(lista,0)-lista_obtener(lista,1);
    //Destruyo la lista luego calcular el resultado
    lista_destruir(&lista);
    return resultado;
}

/**
Funcion que divide los elementos de la lista pasada por parametro.
Retorna la division de los primeros dos elementos de la lista.
Si la cantidad de elementos de la lista es menor a 2, el programa sale con error OPND_INSUF.
Si la cantidad de elementos de la lista es mayor a 2, el programa sale con error OPND_DEMAS.
**/
int division(lista_t lista){
    int resultado=0;
    int cant=lista_cantidad(lista);

    //Si la cantidad de elementos de la lista es menor a 2
    //los operandos son insuficientes y salgo con el error correspondiente
    if (cant<2) exit(OPND_INSUF);
    //Si la cantidad de elementos de la lista es mayor a 2
    //los operandos son demasiados y salgo con el error correspondiente
    if (cant>2) exit(OPND_DEMAS);

    resultado=lista_obtener(lista,0)/lista_obtener(lista,1);
    //Destruyo la lista luego calcular el resultado
    lista_destruir(&lista);
    return resultado;
}

/**
Metodo que toma una pila con los elementos de la expresion ya apilados y la evalua utilizando una pila auxiliar.
El resultado final se imprime por pantalla
**/
void desapilar_y_evaluar(pila_t pila){
    //Reservo memoria para los string que voy a utilizar
    char* caracter=malloc(CADENA_MAX);
    char* caracter_aux=malloc(CADENA_MAX);

    int resultado=0;
    //Creo la pila auxiliar
    pila_t pila_aux=pila_crear();

    while(!pila_vacia(pila)){
        caracter=desapilar(&pila);
        //Si el caracter no es un operador
        if ( (strcmp(caracter,"+")!=0)  && (strcmp(caracter,"*")!=0) && (strcmp(caracter,"-")!=0) && (strcmp(caracter,"/")!=0)){
            //Si el caracter es un '(' estoy en el caso de un entero rodeado de parantesis
            if (strcmp(caracter,"(")==0) {
                //Desapilo el entero de la pila auxiliar
                caracter_aux=desapilar(&pila_aux);
                if (strcmp(tope(pila_aux),")")==0){
                    //Desapilo el ')' de la pila auxiliar para luego apilar de nuevo el entero
                    //y asi eleminar todos los parentesis que rodean al entero
                    desapilar(&pila_aux);
                    apilar(&pila_aux,caracter_aux);
                }
                else{
                    exit(OPRD_INV);
                }
            }
            else{
                //Si no tengo un entero rodeado de parentesis lo apilo en la pila auxiliar
                apilar(&pila_aux,caracter);
            }
        }
        else{
            //Si hay un ')' en el tope de la pila auxiliar entonces la cantidad de operadores es insuficientes
            if (strcmp(tope(pila_aux),")")) exit(OPND_INSUF);
            //Creo la lista para luego insertarle los enteros a evaluar
            lista_t milista=lista_crear();
            while(strcmp(tope(pila_aux),")")!=0){
                //Mintras no haya un ')' en el tope de pila auxiliar
                //Sigo desapilando enteros y insertandolos a la lista
                caracter_aux=desapilar(&pila_aux);
                int num=atoi(caracter_aux);
                lista_adjuntar(milista,num);
            }
            //Desapilo el ')' de la pila auxiliar
            desapilar(&pila_aux);
            //Dependiendo de el operando llamo a cada funcion con la lista de enteros
            if (strcmp(caracter,"+")==0) resultado=suma(milista);
            if (strcmp(caracter,"*")==0) resultado=producto(milista);
            if (strcmp(caracter,"/")==0) resultado=division(milista);
            if (strcmp(caracter,"-")==0) resultado=resta(milista);

            //Convierto el resultado de las funciones de entero a string para luego apilarlo en la pila auxiliar
            char* resultado_aux=malloc(CADENA_MAX);
            resultado_aux=itoa(resultado,resultado_aux);
            apilar(&pila_aux,resultado_aux);

            //Desapilo el '(' de la pila original
            desapilar(&pila);

        }
    }
    //Aca el unico elemento de la pila auxiliar es el resultado final
    //Desapilo el resutado final y lo convierto a entero para mostrarlo
    int toreturn=atoi(desapilar(&pila_aux));
    //Imprimo por pantalla el resultado final
    printf("%d\n",toreturn);
}

/**
Metodo que apila solo los elementos de la expresion ingresada por pantalla a una pila.
Este metodo no apila espacios en blanco.
Si se encuentra con un caracter no valido en la expresion el programa sale con error OPRD_INV.
Si uno de los operandos es un numero no entero (es decir que tiene un '.' o una ',' entre sus digitos)
el programa sale con error OPND_INV.
Si la expresion no esta bien formada el programa sale con error EXP_MALF
**/
void apilar_cadena(char* cadena){

    //Creo la pila
    pila_t mipila=pila_crear();

    //Obtengo el largo de la cadena ingresada
    int largo=strlen(cadena);
    int i=0;
    int j;
    //Utilizo este entero para controlar que cantidad de parentesis sea correcta
    int cont_parentesis=0;

    while(i<largo-1){

        //Cuento los parentesis
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
                    //Si el operando no es un entero salgo con el error correspondiente
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
                    //Si el caracter no es valido salgo con el error correspondiente
                    exit (OPRD_INV);

            }
        }
        else{
            //Aumento i cuando el caracter es un espacio
            i++;
        }
    }
    //Si la cantidad de parentesis no es la correcta salgo con el error correspondiente
    if(cont_parentesis!=0) exit(EXP_MALF);

    //Llamo al metodo desapilar_y_evaluar para evaluar la expresion apilada
    desapilar_y_evaluar(mipila);
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
