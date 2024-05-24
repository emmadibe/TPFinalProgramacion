#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h> //Librería oficial de C necesaria apra utilizar la estructura FILE y sus respectivas funciones, entre otras utilidades.
#include "estructuraUsuario.h"
#include "funcionesGenerales.h"

int main()
{

    int menuInicio = 0;

    int menuPrincipal = 0;

    int crearNuevoUsuario = 0;

    usuario a[100];

    int cantElementos = 0;

    int validosUsuario = 0;

    char email[50];

    char pass[50];

    int logueo = -198;

    validosUsuario = archivoToArregloUsuario("usuario.bid", a, validosUsuario, 100);

    do{

        do{

            if(menuInicio > 2 || menuInicio < 0){

                puts("DEBES INGRESAR UN VALOR ENTRE 0 y 2!\n"); //El cartel solo salta si menuInicio vale más que 2 0 menor a 0. O sea, si el usuario se equivocó.

            }

            puts("BIENVENIDO!\n ELEGIR LA OPCION: \n 1)Crear un usuario.\n 2)Iniciar sesión.\n 0) Salir.\n");

            scanf("%d", &menuInicio);

        }while(menuInicio < 0 || menuInicio > 2);

        switch (menuInicio)
        {
        case 1: //////////////////////////CREAR UN USUARIO
            
            puts("CREAR UN USUARIO\n");

            crearNuevoUsuario = crearUsuario("usuario.bid");

            if(crearNuevoUsuario == 0){

                printf("Usuario creado correctamente!\n");

            }else{

                printf("Error.\n");

            }

            break;
        
        case 2: //////////////////////LOGUEARNOS

            puts("LOGUEARTE\n");

            validosUsuario = archivoToArregloUsuario("usuario.bid", a, validosUsuario, 100);

            do{

                printf("INGRESE SU EMAIL: \n");
                fflush(stdin);
                gets(email);

                printf("INGRESE SU PASS: \n");
                fflush(stdin);
                gets(pass);

                logueo = buscarUsuario(a, validosUsuario, email, pass);

                if(logueo == -2){

                    puts("USUARIO INCORRECTO!\n");

                }else if (logueo == -1){

                    puts("ALGUNO DE LOS DATOS INGRESADOS NO SON CORRECTOS!\n");

                }else{

                    printf("LOGUEADO, %s!\n", a[logueo].nombre ); //Es que la función logueo, de encontrar una coincidencia, me retorna la posicion del usuario.


                    //////////////// ESTE ES EL MENÚ PRINCIPAL/////////////////////////////////////////////////

                    do{

                        printf("Seleccionar una opcion, %s.\n", a[logueo].nombre);
                        printf("0) Salir.\n 1) Ir a seccion LIBROS.\n 2) Ir a seccion COMENTARIOS.\n 3) Editar mi perfil.\n");
                        if(a[logueo].rol == 2){

                            printf("4) para ver lista de usuarios.\n");
                            printf("5) para editar usuarios.\n");
                            printf("6) para eliminar a un usuario.\n");

                        }

                        scanf("%d", &menuPrincipal);

                        if(menuPrincipal == 1){

                            puts("SECCION LIBROS\n");

                        }else if(menuPrincipal == 2){

                            puts("SECCION COMENTARIOS\n");

                        }else if(menuPrincipal == 3){

                            puts("EDITAR PERFIL.\n");

                        }else if(menuPrincipal == 4){

                            if(a[logueo].rol != 2 ){ //Solo los admins (rol == 2) deben poder ver, editar y eliminar usuarios.

                                puts("PROHIBIDO!\n");

                            }else{

                                printf("Claro, admin %s. Esta es la lista de usuarios!\n", a[logueo]. nombre);

                                imprimirArrayUsuario(a, validosUsuario);

                            }

                        }else if(menuPrincipal == 5){

                            if(a[logueo].rol != 2){

                                puts("PROHIBIDO!\n");

                            }else{

                                puts("EDITAR UN USUARIO\n");

                            }

                        }else if(menuPrincipal == 6){

                            if(a[logueo].rol != 2){

                                puts("PROHIBIDO!\n");

                            }else{

                                puts("ELIMINAR UN USUARIO.\n");

                            }

                        }

                        if(menuPrincipal < 0 || menuPrincipal > 6){

                            puts("DEBES INGRESAR UN VALOR ENTRE 0 Y 6!!!!\n");

                        }

                    }while( menuPrincipal != 0); //Si el usuario selecciona 0, cierra sesión, volviendo al menú de incio (DESLOGUEO).

                    ////////////////////////////////////////////////////////////////

                }

            }while(logueo == -1 || logueo == -2);

            break;

        case 0:

            puts("ADIOS!\n");

            return 0;

                break;

        default:

            return 0;

            break;
        }   

    }while(menuInicio != 0);

}


