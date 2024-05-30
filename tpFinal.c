#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h> //Librería oficial de C necesaria apra utilizar la estructura FILE y sus respectivas funciones, entre otras utilidades.
#include <conio.h> //Libreria oficial para utilizar la funcion getch
#include "estructuraUsuario.h"
#include "funcionesGenerales.h"
#include "estructuraLibros.h"


int opcionesMenuLogueo();
void menuLogueo();
int opcionesMenuAdmin(usuario arregloUsuarios[], int usuarioLogueado);
void menuAdmins(usuario arregloUsuarios[], int usuarioLogueado);
int opcionesMenuUsuario(usuario arregloUsuarios[], int usuarioLogueado);
void menuUsuarios(usuario arregloUsuarios[], int usuarioLogueado);


int main()
{

/* ----------------------------      ZONA TESTEOS     -------------------------------- */
//
//    stLibro listalibros[100];
//    int vlistalibros = 0;

    cargaLibroArchivo("listaLibros.bid");


//    vlistalibros = cargaArregloLibros(listalibros, vlistalibros, 100);
//    muestraArregloLibrosAdmin(listalibros, vlistalibros);







/* ------------------------------------------------------------------------------------ */



  //  menuLogueo();

}

int opcionesMenuLogueo()
{
    int eleccion;

    system("color 75");
    printf("----------------------------------------------\n");
    printf("          BIENVENIDO A BOOKNOOK!\n");
    printf("----------------------------------------------\n");
    printf("\n 1-  Crear usuario nuevo");
    printf("\n 2-  Iniciar sesion");
    printf("\n 3-  No quiero estar aqui, adios!");

    printf("\n\n Ingresa una opcion:  ");
    scanf("%d", &eleccion);

    return eleccion;
}

void menuLogueo()
{
    int crearNuevoUsuario = 0;

    usuario a[100];
    int validosUsuario = 0;

    char email[50];
    char pass[50];

    int logueo = -198;

    validosUsuario = archivoToArregloUsuario("usuario.bid", a, validosUsuario, 100);

    char control;
    int opcionMenu;

    do
    {
        opcionMenu = opcionesMenuLogueo();
        system("cls");

        switch(opcionMenu)
        {
        case 1:

            puts("CREAR UN NUEVO USUARIO\n");

            crearNuevoUsuario = crearUsuario("usuario.bid");

            if(crearNuevoUsuario == 0)
            {
                printf("Usuario creado correctamente!\n");
            }
            else
            {
                printf("Error.\n");
            }

            break;
        case 2:

            puts("LOGUEARTE\n");

            validosUsuario = archivoToArregloUsuario("usuario.bid", a, validosUsuario, 100);

            do
            {
                printf("INGRESE SU EMAIL: \n");
                fflush(stdin);
                gets(email);

                printf("INGRESE SU PASS: \n");
                fflush(stdin);
                gets(pass);

                logueo = buscarUsuario(a, validosUsuario, email, pass);

                if(logueo == -2)
                {
                    puts("USUARIO INCORRECTO!\n");
                }
                else if (logueo == -1)
                {
                    puts("ALGUNO DE LOS DATOS INGRESADOS NO SON CORRECTOS!\n");
                }
                else
                {
                    printf("HOLA DE NUEVO, %s!\n", a[logueo].nombre ); //Es que la función logueo, de encontrar una coincidencia, me retorna la posicion del usuario.

                    if(a[logueo].rol == 2 ) //Solo los admins (rol == 2) deben poder ver, editar y eliminar usuarios.
                    {
                        menuAdmins(a, logueo);
                    }
                    else
                    {
                        menuUsuarios(a, logueo);
                    }
                }

            }while(logueo == -1 || logueo == -2);

            break;
        case 3:      // opción del usuario arrepentido

            printf("Ya te vas? Volve pronto!\n\n");

            break;
        default:
            system("color 74");
            printf("\nOPCION INVALIDA\n");
        }

        printf("\n");
        system("PAUSE");
        system("cls");

        system("color 75");
        printf("\nQuieres continuar? Presione ESC para cerrar el programa o cualquier tecla para volver al menu de logueo\n");
        fflush(stdin);
        control = getch();
        system("cls");

    }
    while(control != 27);
}

int opcionesMenuAdmin(usuario arregloUsuarios[], int usuarioLogueado)
{
    int eleccion;

    system("color 75");
    printf("----------------------------------------------\n");
    printf("        MENU PRINCIPAL ADMINISTRADORES \n");
    printf("----------------------------------------------\n");
    printf("\n 1-  Ir a SECCION LIBROS");
    printf("\n 2-  Ir a SECCION COMENTARIOS");
    printf("\n 3-  Editar mi perfil");
    printf("\n 4-  Ver lista de usuarios");
    printf("\n 5-  Editar usuarios");
    printf("\n 6-  Eliminar un usuario");
    printf("\n 7-  Cerrar sesion");

    printf("\n\n Ingresa una opcion:  ");
    scanf("%d", &eleccion);

    return eleccion;
}

void menuAdmins(usuario arregloUsuarios[], int usuarioLogueado)
{
    char control;
    int opcionMenu;
    int validosUsuarios = 0;
    usuario u[50];

    do
    {
        opcionMenu = opcionesMenuAdmin(arregloUsuarios, usuarioLogueado);
        system("cls");

        switch(opcionMenu)
        {
        case 1: //Ir a SECCION LIBROS

            break;
        case 2: //Ir a SECCION COMENTARIOS

            break;
        case 3: //Editar mi perfil

            break;
        case 4: //Ver lista de usuarios

            validosUsuarios = archivoToArregloUsuario("usuario.bid", u, validosUsuarios, 50);
            imprimirArrayUsuario(u, validosUsuarios);

            break;
        case 5: //Editar usuarios

            break;
        case 6: //Eliminar un usuario

            break;
        case 7: //Cierre de sesion

            printf("Hasta luego admin!");

            break;

        default:
            system("color 74");
            printf("\nOPCION INVALIDA\n");
        }

        printf("\n");
        system("PAUSE");
        system("cls");

        system("color 75");
        printf("\nQuieres continuar? Presione ESC para confirmar el cierre de sesion o cualquier tecla para volver al menu de administrador\n");
        fflush(stdin);
        control = getch();
        system("cls");
    }
    while(control != 27);
}

int opcionesMenuUsuario(usuario arregloUsuarios[], int usuarioLogueado)
{
    int eleccion;

    system("color 75");
    printf("----------------------------------------------\n");
    printf("              MENU PRINCIPAL  \n");
    printf("----------------------------------------------\n");
    printf("\n 1-  Ir a SECCION LIBROS");
    printf("\n 2-  Ir a SECCION COMENTARIOS");
    printf("\n 3-  Editar mi perfil");
    printf("\n 4-  Cerrar sesion");

    printf("\n\n Ingresa una opcion:  ");
    scanf("%d", &eleccion);

    return eleccion;
}

void menuUsuarios(usuario arregloUsuarios[], int usuarioLogueado)
{
    char control;
    int opcionMenu;

    do
    {
        opcionMenu = opcionesMenuUsuario(arregloUsuarios, usuarioLogueado);
        system("cls");

        switch(opcionMenu)
        {
        case 1: //Ir a SECCION LIBROS

            break;
        case 2: //Ir a SECCION COMENTARIOS

            break;
        case 3: //Editar mi perfil

            break;
        case 4: //Cierre de sesion

            printf("Hasta luego!");

            break;

        default:
            system("color 74");
            printf("\nOPCION INVALIDA\n");
        }

        printf("\n");
        system("PAUSE");
        system("cls");

        system("color 75");
        printf("\nQuieres continuar? Presione ESC para confirmar el cierre de sesion o cualquier tecla para volver al menu de administrador\n");
        fflush(stdin);
        control = getch();
        system("cls");
    }
    while(control != 27);
}


