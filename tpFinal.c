#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h> //Librería oficial de C necesaria para utilizar la estructura FILE y sus respectivas funciones, entre otras utilidades.
#include <conio.h> //Libreria oficial para utilizar la funcion getch
#include "estructuraUsuario.h"
#include "funcionesGenerales.h"
#include "estructuraLibros.h"
#include "estructuraComentarios.h"
#include <stddef.h>

int opcionesMenuLogueo();
void menuLogueo();
int opcionesMenuAdmin(usuario arregloUsuarios[], int usuarioLogueado);
void menuAdmins(usuario arregloUsuarios[], int usuarioLogueado, usuario SESSION);
int opcionesMenuUsuario(usuario arregloUsuarios[], int usuarioLogueado);
void menuUsuarios(usuario arregloUsuarios[], int usuarioLogueado, usuario SESSION);
usuario cargarVariablesDeSession(usuario SESSION, usuario u);
// void libroUsuarios(int opcion, usuario SESSION);
// void libroAdmins(int opcion, usuario SESSION);
// void accionLibro(int opcion, usuario SESSION, stLibro miLibro);

usuario SESSION; /*VARIABLES DE SESIÓN. En esta variable vamos a almacenar los valores de los campos del usuario que se logueo para, luego, poder utilizarlos a lo largo del programa.
                     Necesitaremos, por ejemplo, recuperar el id del usuario para que cada comentario se corresponda con el usuario.*/

int main()
{


/* ----------------------------      ZONA TESTEOS     -------------------------------- */







/* ------------------------------------------------------------------------------------ */




    menuLogueo();

  //  mostrarUsuario(SESSION);  ///Función para controlar los datos almacenados en SESSION
}

int opcionesMenuLogueo()
{
    int eleccion;

    system("color 75");
    printf("----------------------------------------------\n");
    printf("          BIENVENIDO A BOOKLIFE!\n");
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

                    SESSION = cargarVariablesDeSession(SESSION, a[logueo]);

                    if(a[logueo].rol == 2 ) //Solo los admins (rol == 2) deben poder ver, editar y eliminar usuarios.
                    {
                        menuAdmins(a, logueo, SESSION);
                    }
                    else
                    {
                        menuUsuarios(a, logueo, SESSION);
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

void menuAdmins(usuario arregloUsuarios[], int usuarioLogueado, usuario SESSION)
{
    char control;
    int opcionMenu;
    int opcionLibros = 0;
    int validosUsuarios = 0;
    usuario u[50];

    do
    {
        opcionMenu = opcionesMenuAdmin(arregloUsuarios, usuarioLogueado);
        system("cls");

        switch(opcionMenu)
        {
        case 1: //Ir a SECCION LIBROS

            opcionLibros =  opcionLibrosAdmins();
            libroAdmins(opcionLibros, SESSION);

            break;
        case 2: //Ir a SECCION COMENTARIOS

            break;
        case 3: //Editar mi perfil

            editarusuario("usuario.bid");            

            break;
        case 4: //Ver lista de usuarios

            validosUsuarios = 0; //Reinicio el válidos para que o haya repetición de usuarios.

            validosUsuarios = archivoToArregloUsuario("usuario.bid", u, validosUsuarios, 50);
            imprimirArrayUsuario(u, validosUsuarios);

            break;
        case 5: //Editar usuarios

            break;

        case 6: //Eliminar un usuario

            eliminarUsuario("usuario.bid", SESSION);

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

void menuUsuarios(usuario arregloUsuarios[], int usuarioLogueado, usuario SESSION)
{
    char control;
    int opcionMenu;

    do
    {
        int opcionLibros = 0;
        opcionMenu = opcionesMenuUsuario(arregloUsuarios, usuarioLogueado);
        system("cls");

        switch(opcionMenu)
        {
        case 1: //Ir a SECCION LIBROS

            opcionLibros = opcionLibrosUsuarios();

            libroUsuarios(opcionLibros, SESSION);

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

int opcionLibrosUsuarios()
{

    int opcion = 0;

    do{

        printf("Bienvenido a la seccion de libros. \n");
        printf("Marque 1) Ver lista de libros.\n 2) Entrar a un libro.\n 3) Agregar un libro.\n 0) Regresar.\n");

    }while(opcion < 0 || opcion > 3);

    return opcion;

}

void libroUsuarios(int opcion, usuario SESSION)
{
    stLibro l[30];

    int validos = 0;

    int dim = 30;

    switch (opcion)
    {
    case 1:

        printf("LISTA DE LIBROS: \n");

        validos = archivoToArrayLibros("listaLibros.bid", l, validos, dim);

        imprimirArrayLibrosAdm(l, validos);

        break;

    case 2:

        break;

    case 3:

        cargaLibroArchivo("listaLibros.bid");

        break;

    default:
        break;
    }

}

int opcionLibrosAdmins()
{

    int opcion = 0;

    do{

        printf("Bienvenido a la seccion de libros. \n");
        printf("Marque 1) Ver lista de libros.\n 2) Entrar a un libro.\n 3) Agregar un libro.\n 0) Regresar.\n");

        scanf("%d", &opcion);

    }while(opcion < 0 || opcion > 3);

    return opcion;

}

void libroAdmins(int opcion, usuario SESSION)
{

    stLibro l[30];

    stLibro miLibro;

    int validos = 0;
    char nombreLibro[60];
    int dim = 30;
    int idLibro;

    int opcionEntrarAlLibro;

    switch (opcion)
    {
    case 1:
        printf("LISTA DE LIBROS: \n");

        validos = archivoToArrayLibros("listaLibros.bid", l, validos, dim);

        imprimirArrayLibrosAdm(l, validos);

        break;

    case 2:

        printf("Escribir el nombre del libro al cual deseas ingresar.\n");
        fflush(stdin);
        gets(nombreLibro);
        idLibro = buscarIdibro(nombreLibro);

        if(idLibro >= 0){

            validos = 0;
            validos = archivoToArrayLibros("listaLibros.bid", l, validos, dim);

            miLibro = buscarLibroPorId(idLibro, l, validos);

            puts("-----------------------\n");
            printf("ID del libro :  %d\n", idLibro);
            printf("Titulo:  %s\n", miLibro.titulo);
            printf("Autor :  %s\n", miLibro.autor);
            printf("Editorial :  %s\n", miLibro.editorial);
            printf("Categoria :  %s\n", miLibro.categoria);
            printf("Puntaje :  %f\n", miLibro.valoracion);
            puts("-----------------------\n");

            opcionEntrarAlLibro = opcionesMenuEntrarALibro();

            accionLibro(opcionEntrarAlLibro, SESSION, miLibro);

        }else{

            printf("No existe el libro.\n");

        }

        break;

    case 3:

        cargaLibroArchivo("listaLibros.bid");

        break;

    default:
        break;
    }

}

void accionLibro(int opcion, usuario SESSION, stLibro miLibro)
{

    int v = 0, d= 55;

    stComentario comentario;

    stComentario arrayComentario[55];

    int posicion = 0;

    switch (opcion)
    {
    case 3:

        printf("Hola %s.\n Entraste al libro %s.\n", SESSION.nombre, miLibro.titulo);

        comentario = cargarComentarioNuevo(SESSION.id, miLibro.idLibro);

        printf("Tu comentario del libro es el siguiente:\n");
        puts("---------------------------------------------\n");
        printf("%s\n", comentario.tituloComentario);
        printf("%s\n", comentario.descripcion);
        printf("Puntaje: %d.\n", comentario.puntaje);
        puts("---------------------------------------------\n");

        break;

    case 4:

        archivoToArrayComentario("listaComentarios.bid", arrayComentario, &v, d);

        posicion = buscarComentario(miLibro.idLibro, arrayComentario, v);

        if (posicion != -1){ //buscarComentario retorna -1 si no encontró una estructura con el valor de idLibro que le pasamos por parametro.

            imprimirUnComentarioDelArrayComentario(arrayComentario, posicion, miLibro.titulo);

        }else{

            printf("El libro %s todavia no posee comentarios.\n", miLibro.titulo);

        }

        printf("La posicion es: %d\n", posicion);
        printf("El id es: %d\n", miLibro.idLibro);

    default:
        break;
    }

}

int opcionesMenuEntrarALibro()
{

    int opcion;

    do{

        puts("Que desea hacer con el libro?\n");
        printf("1) Eliminar el comentario.\n 2) Editar el comentario.\n 3) Agregarle un comentario.\n 4) Ver comentario\n 0) Nada.\n");
        scanf("%d", &opcion);

    }while(opcion <= 0 || opcion > 4);

    return opcion;

}

usuario cargarVariablesDeSession(usuario SESSION, usuario u)
{

    strcpy(SESSION.nombre, u.nombre);
    strcpy(SESSION.email, u.email);
    strcpy(SESSION.pass, u.pass);
    strcpy(SESSION.fechaNacimiento, u.fechaNacimiento);
    SESSION.genero = u.genero; //Es un char, no un string.
    sprintf(SESSION.id, "%d", u.id);
    sprintf(SESSION.rol, "%d", u.rol);

    return SESSION;
}
