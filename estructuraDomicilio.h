#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h>

typedef struct
{
    char calle[50];
    int altura;
    int cp;
    char ciudad[100];
    char localidad[50]; ///provincia
    char pais[100];

} stDomicilio;

stDomicilio cargarDomicilio();
