#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h> 

int crearUsuario(char archivo[]);

typedef struct estructuraUsuario
{

    char nombre[30];

    int edad;

    int rol; // 2: adm;  1: usuario. La clave para ser anmi es la de LOST: 4815162342.

    int pass;

    char genero; //f, m, x.

}usuario;

int main()
{

    int pruebita = 0;

    pruebita = crearUsuario("pruebita.bid");

}

int crearUsuario(char archivo[])
{

    usuario u; //Declaramos una variable de tipo usuario.

    FILE *archi; //Declaramos un puntero a la estructura FILE.

    archi = fopen(archivo, "ab");

    int pass2 = 0;

    if(archi == NULL){

        return -1; //Retorno -1 si hubo un error al abrir/crear el archivo.

    } 

    puts("----------------\n");

    do{

        printf("Ingrese nombre y apellido entre 6 y 30 caracteres: \n");
        fflush(stdin);
        gets(u.nombre);

    }while(u.nombre < 6 && u.nombre > 30);

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

        if(u.rol == 4815162342){

            u.rol = 2;

        }

    }while(u.rol != 4815162342 || u.rol != 1);

    puts("-----------------------\n");

    fwrite(&u, sizeof(usuario), 1, archi);

    fclose(archi); //Cierro el archivo. Fundamental para que los datos escritos en el buffer se guarden en el archivo ubicado en memoria secundaria.

}