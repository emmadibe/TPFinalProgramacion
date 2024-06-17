#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h>
#include "estructuraDomicilio.h"

stDomicilio cargarDomicilio()
{

    stDomicilio d;

    printf("Agregar calle:\n");
    fflush(stdin);
    gets(d.calle);

    printf("Altura\n");
    scanf("%d", &d.altura);

    printf("Ciudad:\n");
    fflush(stdin);
    gets(d.ciudad);

    printf("Localidad:\n");
    fflush(stdin);
    gets(d.localidad);

    printf("Pais:\n");
    fflush(stdin);
    gets(d.pais);

    printf("Codigo Postal:\n");
    scanf("%d", &d.cp);


}