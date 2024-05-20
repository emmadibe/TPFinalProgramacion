#include "estructuraUsuario.h"

int crearUsuario(char archivo[])
{

    char pass2[30];

    int longCadena = 0;

    int compararCadenas = 0;

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

        longCadena = strlen(u.nombre);

    }while(longCadena < 6 || longCadena > 30);

    do{

        printf("Ingrese una edad del 1 al 100: \n");
        scanf("%d", &u.edad);

    }while(u.edad < 1 || u.edad > 100 );

    do{

        do{

            printf("Ingrese password: \n");
            gets(u.pass);
            longCadena = strlen(u.pass);

        }while(longCadena < 5); //obligo al usuario a ingresar ua contraseña de, como minimo, 5 caracteres.

        printf("Confirmar pass: \n");
        gets(pass2);

        compararCadenas = strcmp(u.pass, pass2);

    }while(compararCadenas != 0);

    do{

        printf("Inrgese su genero: f, m o x\n");
        u.genero = getch();

    }while(u.genero != 'f' && u.genero != 'm' && u.genero != 'x');

    do{

        printf("Si usted conoce la key para ser administrador, escribala; sino, presione 1.\n");
        scanf("%d", &u.rol);

        if(u.rol == 4815){

            u.rol = 2;

        }

    }while(u.rol != 2 && u.rol != 1);

    puts("-----------------------\n");

    fwrite(&u, sizeof(usuario), 1, archi);

    fclose(archi); //Cierro el archivo. Fundamental para que los datos escritos en el buffer se guarden en el archivo ubicado en memoria secundaria.

    return 0;

}

void verUsuarios (char archivo[])
{

    FILE *archi;
    usuario u;
    archi = fopen(archivo, "rb");
    int i = 0;
    if(archi != NULL){

        while(fread(&u, sizeof(usuario), 1, archi) > 0){

            printf("Registro N %d\n", i);
            puts("-----------\n");
            printf("Nombre y apellido: %s\n", u.nombre);
            printf("Edad: %d\n", u.edad);
            printf("Genero: %c\n", u.genero);
            printf("Rol: %d\n", u.rol);
            puts("---------------\n");

        }

    }

}