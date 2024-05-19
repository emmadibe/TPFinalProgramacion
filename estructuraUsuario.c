#include "estructuraUsuario.h"

int crearUsuario(char archivo[])
{

    int pass2 = 0;

    usuario u; //Declaramos una variable de tipo usuario.

    FILE *archi; //Declaramos un puntero a la estructura FILE.

    archi = fopen(archivo, "ab");

    if(archi == NULL){

        return -1; //Retorno -1 si hubo un error al abrir/crear el archivo.

    } 

    puts("----------------\n");

    do{

        printf("Ingrese nombre y apellido entre 6 y 30 caracteres: \n");
        fflush(stdin);
        gets(u.nombre);

    }while(strlen(u.nombre) < 6 && strlen(u.nombre) > 30);

    do{

        printf("Ingrese una edad del 1 al 100: \n");
        scanf("%d", &u.edad);

    }while(u.edad < 1 && u.edad > 100 );

    do{

        printf("Ingrese password: \n");
        scanf("%d", &u.pass);
        printf("Confirmar pass: \n");
        scanf("%d", &pass2);

    }while(u.pass != pass2);

    do{

        printf("Si usted conoce la key para ser administrador, escribala; sino, presione 1.\n");
        scanf("%d", &u.rol);

        if(u.rol == 4815){

            u.rol = 2;

        }

    }while(u.rol != 2 || u.rol != 1);

    puts("-----------------------\n");

    fwrite(&u, sizeof(usuario), 1, archi);

    fclose(archi); //Cierro el archivo. Fundamental para que los datos escritos en el buffer se guarden en el archivo ubicado en memoria secundaria.

    return 0;

}