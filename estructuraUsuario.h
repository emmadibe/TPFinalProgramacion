#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h> 



typedef struct 
{

    char nombre[30];

    int edad;

    int rol; // 2: adm;  1: usuario. La clave para ser anmi es 4815.

    char pass[30];

    char genero; //f, m, x.

}usuario;

int crearUsuario(char archivo[]);
void verUsuarios (char archivo[]);
