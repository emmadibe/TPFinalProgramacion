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

    return d;
}
