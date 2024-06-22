#include "estructuraDomicilio.h"

stDomicilio cargarDomicilio()
{

    stDomicilio d;

    printf("Agregar calle:\n");
    fflush(stdin);
    gets(d.calle);
    puts("\n");

    printf("Altura\n");
    scanf("%d", &d.altura);
    puts("\n");

    printf("Ciudad:\n");
    fflush(stdin);
    gets(d.ciudad);
    puts("\n");

    printf("Localidad:\n");
    fflush(stdin);
    gets(d.localidad);
    puts("\n");

    printf("Pais:\n");
    fflush(stdin);
    gets(d.pais);
    puts("\n");

    printf("Codigo Postal:\n");
    scanf("%d", &d.cp);

    return d;
}
