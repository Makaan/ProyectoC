#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "lista.h"
#include "pila.h"
#include "evaluar.c"

int main(){

    char* cadena;

    cadena="((+3 5 6 7 1))";
    printf("%s\n",cadena);
    apilar_cadena(cadena);




    return 0;
}
