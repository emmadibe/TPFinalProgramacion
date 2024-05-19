#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h> //Librería oficial de C necesaria apra utilizar la estructura FILE y sus respectivas funciones, entre otras utilidades.

int main()
{

    int menu = 0;

    do{

        do{

            if(menu > 2 || menu < 0){

                puts("DEBES INGRESAR UN VALOR ENTRE 0 y 2!\n"); //El cartel solo salta si menu vale más que 2 0 menor a 0. O sea, si el usuario se equivocó.

            }

            puts("BIENVENIDO!\n ELEGIR LA OPCION: \n 1)Crear un usuario.\n 2)Iniciar sesión.\n 0) Salir.\n");

            scanf("%d", &menu);

        }while(menu < 0 || menu > 2);

        switch (menu)
        {
        case 1:
            
            puts("CREAR UN USUARIO\n");

            break;
        
        case 2:

            puts("LOGUEARTE\n");

            break;

        case 0:

            puts("ADIOS!\n");

            return 0;

                break;

        default:

            return 0;

            break;
        }   

    }while(menu != 0);

}


