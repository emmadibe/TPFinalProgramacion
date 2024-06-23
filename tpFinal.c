#include "funcionesGenerales.h"

#define AR_USUARIOS "usuario.bid"
#define AR_LIBROS "libros.bid"
#define AR_COMENTARIOS "comentarios.bid"


int opcionesMenuLogueo();
void menuLogueo(char archivoUsuarios[], char archivoLibros[], char archivoComentarios[]);
usuario guardaVariablesDeSession(usuario SESSION, usuario u);

int opcionesMenuAdmin();
void menuAdmins(usuario arregloUsuarios[], int usuarioLogueado, usuario SESSION, char archivoUsuarios[], char archivoLibros[], char archivoComentarios[]);
int opcionSubMenuUsuariosAdmin();
void subMenuUsuariosAdmin(usuario SESSION, char archivoUsuarios[]);
int opcionSubMenuLibrosAdmin();
void subMenuLibrosAdmin(usuario SESSION, char archivoLibros[], char archivoUsuarios[], char archivoComentarios[]);
int opcionSubMenuComentariosAdmin();
void subMenuComentariosAdmin(usuario SESSION, char archivoComentarios[],char archivoLibros[], char archivoUsuarios[]);

int opcionesMenuUsuario();
void menuUsuarios(usuario arregloUsuarios[], int usuarioLogueado, usuario SESSION, char archivoUsuarios[], char archivoLibros[], char archivoComentarios[]);
int opcionSubMenuLibrosUsuario();
void subMenuLibrosUsuario(usuario SESSION, char archivoLibros[], char archivoUsuarios[], char archivoComentarios[]);
int opcionSubMenuComentariosUsuario();
void subMenuComentariosUsuario(usuario SESSION, char archivoComentarios[],char archivoLibros[], char archivoUsuarios[]);

/**
*VARIABLE DE SESSION. En esta variable vamos a almacenar los valores de los campos del usuario que se logueo
*para, luego, poder utilizarlos a lo largo del programa.
*Necesitaremos, por ejemplo, recuperar el id del usuario para que cada comentario se corresponda con el usuario.
*/

usuario SESSION;

int main()
{

    menuLogueo(AR_USUARIOS,AR_LIBROS,AR_COMENTARIOS);

    // mostrarUnUsuario(SESSION);  //Función para controlar los datos almacenados en SESSION
}

/// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------///
///         ZONA DE LOGUEO Y REGISTRO DE USUARIOS
/// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------///

int opcionesMenuLogueo()
{
    /*Función para imprimir por pantalla el primer menu y retornar la elección del usuario*/

    int eleccion;

    system("color 75");
    printf("----------------------------------------------\n");
    printf("                  BIENVENIDO!\n");
    printf("----------------------------------------------\n");
    printf("\n 1-  Crear usuario nuevo");
    printf("\n 2-  Iniciar sesion");
    printf("\n 0-  Cerrar programa");

    printf("\n\n Ingresa una opcion:  ");
    fflush(stdin);
    scanf("%d", &eleccion);
    printf("\n");

    return eleccion;
}

void menuLogueo(char archivoUsuarios[], char archivoLibros[], char archivoComentarios[])
{
    /*Función que administra la creación de usuarios, logueos y cierres de sesión,
    *además lleva al usuario a los menus de arministrador o de usuarios clientes según sea su rol*/

    int crearNuevoUsuario = 0;

    usuario a[100];
    int validosUsuario = 0;

    char email[50];
    char pass[50];

    int posUsuarioLogueado = -3;

    validosUsuario = archivoToArregloUsuario(archivoUsuarios, a, validosUsuario, 100);   /// se está pasando el archivo al arreglo dos veces (ver linea 116)

    int opcionMenu;

    do
    {
        opcionMenu = opcionesMenuLogueo();
        system("cls");

        switch(opcionMenu)
        {
        case 1:

            puts("CREAR UN NUEVO USUARIO\n");

            crearNuevoUsuario = crearUsuario(archivoUsuarios);

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

            validosUsuario = archivoToArregloUsuario(archivoUsuarios, a, validosUsuario, 100);

            do
            {
                printf("INGRESE SU EMAIL: \n");
                fflush(stdin);
                gets(email);

                printf("INGRESE SU PASS: \n");
                fflush(stdin);
                gets(pass);

                posUsuarioLogueado = buscarUsuario(a, validosUsuario, email, pass);

                if(posUsuarioLogueado == -2)
                {
                    puts("USUARIO INCORRECTO!\n");
                }
                else if (posUsuarioLogueado == -1)
                {
                    puts("ALGUNO DE LOS DATOS INGRESADOS NO SON CORRECTOS!\n");
                }
                else if (posUsuarioLogueado == 33)
                {

                    puts("Su cuenta ha sido deshabilitada.\n");

                }
                else
                {
                    system("cls");
                    printf("HOLA DE NUEVO, %s!\n", a[posUsuarioLogueado].nombre ); //Es que la función logueo, de encontrar una coincidencia, me retorna la posicion del usuario.

                    SESSION = guardaVariablesDeSession(SESSION, a[posUsuarioLogueado]);

                    if(a[posUsuarioLogueado].rol == 2 ) //Solo los admins (rol == 2) deben poder ver, editar y eliminar usuarios.
                    {
                        menuAdmins(a, posUsuarioLogueado, SESSION, archivoUsuarios, archivoLibros, archivoComentarios);
                    }
                    else
                    {
                        menuUsuarios(a, posUsuarioLogueado, SESSION, archivoUsuarios, archivoLibros, archivoComentarios);
                    }
                }
            }
            while(posUsuarioLogueado == -1 || posUsuarioLogueado == -2);

            break;
        case 0:
            break;
        default:
            system("color 74");
            printf("\nOPCION INVALIDA\n");
        }
        puts("\n\n");
        system("PAUSE");
        system("cls");
        system("color 75");
    }
    while(opcionMenu != 0);
}

usuario guardaVariablesDeSession(usuario SESSION, usuario u)
{
    strcpy(SESSION.nombre, u.nombre);
    strcpy(SESSION.email, u.email);
    strcpy(SESSION.pass, u.pass);
    strcpy(SESSION.fechaNacimiento, u.fechaNacimiento);
    strcpy(SESSION.dni, u.dni);
    strcpy(SESSION.domicilio.pais, u.domicilio.pais);
    strcpy(SESSION.domicilio.localidad, u.domicilio.localidad);
    strcpy(SESSION.domicilio.calle, u.domicilio.calle);
    strcpy(SESSION.domicilio.ciudad, u.domicilio.ciudad);
    SESSION.genero = u.genero; //Es un char, no un string.
    SESSION.edad = u.edad;
    SESSION.rol = u.rol;
    SESSION.id = u.id;
    SESSION.domicilio.cp = u.domicilio.cp;
    SESSION.domicilio.altura = u.domicilio.altura;

    return SESSION;
}

/// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------///
///         ZONA DE USUARIOS ADMINISTRADORES
/// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------///

int opcionesMenuAdmin()
{
    /*Función para imprimir por pantalla el menu principal del usuario administrador y retornar la elección del mismo*/

    int eleccion;

    system("color 75");
    printf("----------------------------------------------\n");
    printf("        MENU PRINCIPAL ADMINISTRADORES \n");
    printf("----------------------------------------------\n");
    printf("\n 1-  Ir a SECCION COMENTARIOS");
    printf("\n 2-  Ir a SECCION LIBROS");
    printf("\n 3-  Ir a SECCION USUARIOS");
    printf("\n 4-  Ver mi perfil");
    printf("\n 5-  Editar mi perfil");
    printf("\n 0-  Cerrar sesion");

    printf("\n\n Ingresa una opcion:  ");
    fflush(stdin);
    scanf("%d", &eleccion);
    printf("\n");

    return eleccion;
}

void menuAdmins(usuario arregloUsuarios[], int usuarioLogueado, usuario SESSION, char archivoUsuarios[], char archivoLibros[], char archivoComentarios[])
{
    /*Función de administración del menu principal de administradores*/

    int opcionMenu = -1;

    do
    {
        opcionMenu = opcionesMenuAdmin();
        system("cls");

        switch(opcionMenu)
        {
        case 1: //Ir a SECCION COMENTARIOS

            subMenuComentariosAdmin(SESSION, archivoComentarios, archivoLibros, archivoUsuarios);

            break;
        case 2: //Ir a SECCION LIBROS

            subMenuLibrosAdmin(SESSION, archivoLibros, archivoUsuarios, archivoComentarios);

            break;
        case 3: //Ir a SECCION USUARIOS  (subMenu exclusivo de administradores)

            subMenuUsuariosAdmin(SESSION, archivoUsuarios);

            break;
        case 4: //ver mi perfil

            puts("MI PERFIL:\n");
            imprimirUnRegistro(SESSION);

            break;
        case 5: //editar mi perfil

            editarUsuario(archivoUsuarios, SESSION.id);

            break;
        case 0:
            break;

        default:
            system("color 74");
            printf("\nOPCION INVALIDA\n");
        }
        puts("\n\n");
        system("PAUSE");
        system("cls");
        system("color 75");

    }
    while(opcionMenu != 0);
}

int opcionSubMenuUsuariosAdmin()
{
    int opcion = -1;

    system("color 75");
    printf("----------------------------------------------\n");
    printf("        SECCION USUARIOS ADMINISTRADOR  \n");
    printf("----------------------------------------------\n");
    printf("\n 1-  Ver lista de usuarios registrados.");
    printf("\n 2-  Editar usuarios.");
    printf("\n 3-  Eliminar un usuario."); //Lo borra al usuario del todo, incluido el archivo.
    printf("\n 4-  Inhabilitar un usuario."); //Solo cambia el valor de eliminado de 0 a 1.
    printf("\n 0-  Volver al menu anterior.");

    printf("\n\n Ingresa una opcion:  ");
    fflush(stdin);
    scanf("%d", &opcion);
    printf("\n");

    return opcion;
}

void subMenuUsuariosAdmin(usuario SESSION, char archivoUsuarios[])
{
    int opcion = -1;

    int validosUsuarios = 0;
    usuario u[50];

    int id = 0;

    do
    {
        opcion = opcionSubMenuUsuariosAdmin();

        switch (opcion)
        {
        case 1:
            puts("Ver lista de usuarios registrados.");

            validosUsuarios = 0; //Reinicio el válidos para que no haya repetición de usuarios.
            validosUsuarios = archivoToArregloUsuario(archivoUsuarios, u, validosUsuarios, 50);
            imprimirArrayUsuario(u, validosUsuarios);


            break;

        case 2:
            puts("Editar usuarios.");

            puts("Escribir el id del usuario que deseas editar");

            scanf("%d", &id);

            editarUsuario(AR_USUARIOS, id);

            break;

        case 3: //Lo borra al usuario del todo, incluido el archivo.
            puts("Eliminar un usuario.");

            eliminarUsuario(archivoUsuarios, SESSION);
            break;

        case 4: //Quitar el valor de eliminado de 0 y ponerle 1.

            puts("inhabilitar un usuario.\n");

            puts("Ingresar el id del usuario que desea inhabilitar.\n");

            scanf("%d", &id);

            inhabilitarUsuario(AR_USUARIOS, id);

            break;

        case 0:
            break;

        default:
            system("color 74");
            printf("\nOPCION INVALIDA\n");
        }
        puts("\n\n");
        system("PAUSE");
        system("cls");
        system("color 75");
    }
    while(opcion != 0);
}

int opcionSubMenuLibrosAdmin()
{
    int opcion = -1;

    system("color 75");
    printf("----------------------------------------------\n");
    printf("        SECCION LIBROS ADMINISTRADOR  \n");
    printf("----------------------------------------------\n");
    printf("\n 1-  Ver lista de libros guardados.");
    printf("\n 2-  Ver libros de una categoria.");
    printf("\n 3-  Ver libros de un autor.");
    printf("\n 4-  Agregar un libro nuevo.");
    printf("\n 5-  Buscar un libro por titulo y modificarlo.");
    printf("\n 6-  Ver tus libros favoritos.");
    printf("\n 7-  Agregar un libro a tus favoritos.");
    printf("\n 8-  Quitar un libro a tus favoritos.");
    printf("\n 9-  Ver una recomendacion aleatoria.");
    printf("\n10-  Inhabilitar/Habilitar un libro y sus comentarios.");
    printf("\n11-  Elimina definitivamente un libro y sus comentarios.");
    printf("\n 0-  Volver al menu anterior.");

    printf("\n\n Ingresa una opcion:  ");
    fflush(stdin);
    scanf("%d", &opcion);
    puts("\n");

    return opcion;
}

void subMenuLibrosAdmin(usuario SESSION, char archivoLibros[], char archivoUsuarios[], char archivoComentarios[])
{
    int opcion = -1;

    char categoriaElegida[50];
    stLibro librosCategBuscada[200];
    int valLibrosCategBuscada = 0;

    char autorBuscado[50];
    stLibro librosDelAutor[200];
    int valLibrosDelAutor = 0;

    stLibro libreriaCompleta[300];
    int valLibreriaCompleta = 0;

    usuario arregloDeUsuarios[300];
    int valArregloUsario = 0;
    int posUsuario = -1;
    int idSession = SESSION.id;

    do
    {
        opcion = opcionSubMenuLibrosAdmin();

        switch (opcion)
        {
        case 1:
            puts("\nVer lista de libros guardados\n");
            muestraArchivoLibrosAdmins(archivoLibros);

            break;
        case 2:
            puts("\n\nVer libros de una categoria\n");
            puts("\n Que categoria quieres ver?");
            eligeCategoriaLibro(categoriaElegida);

            valLibrosCategBuscada = archivoToArrayLibrosSegunCategoria(archivoLibros, librosCategBuscada, valLibrosCategBuscada, 200, categoriaElegida);

            if( valLibrosCategBuscada == 0)
            {
                puts("No se encontraron libros de esa categoria en nuestros archivos.");
            }
            else
            {
                muestraArregloLibrosAdmin(librosCategBuscada, valLibrosCategBuscada);
            }

            break;
        case 3:
            puts("\n\nVer libros de un autor\n");
            puts("\n Ingresa el nombre del autor del cual quieres ver los libros: ");
            fflush(stdin);
            gets(autorBuscado);

            valLibrosDelAutor = archivoToArrayLibrosSegunAutor(archivoLibros, librosDelAutor, valLibrosDelAutor, 200, autorBuscado);

            if( valLibrosDelAutor == 0)
            {
                puts("\nNo se encontraron libros de ese autor en nuestros archivos\n");
            }
            else
            {
                muestraArregloLibrosAdmin(librosDelAutor, valLibrosDelAutor);
            }

            break;
        case 4:
            puts("\nAgregar un libro nuevo\n");
            cargaLibrosAlArchivo(archivoLibros);

            break;

        case 5:
            puts("\nBuscar un libro por titulo y modificarlo\n");
            valLibreriaCompleta = 0; // reinicio validos para escribir el arreglo desde el inicio
            valLibreriaCompleta = archivoToArrayLibros(archivoLibros,libreriaCompleta,valLibreriaCompleta,300);

            if (valLibreriaCompleta > 0)
            {
                /* funcion de control para evitar sobreescribir el archivo vacio
                si hubo algun error al pasar los datos del archivo al array*/

                modificaDatosLibro(libreriaCompleta,valLibreriaCompleta);
                arregloToArchivoLibros(libreriaCompleta, valLibreriaCompleta, archivoLibros);
            }
            else
            {
                puts("\n ERROR: El archivo está vacio o no funcionó la transferencia de datos al buffer\n");
            }

            break;
        case 6:
            puts("\nVer tus libros favoritos\n\n");

            muestraLibrosFavoritosDeUsuario(SESSION.id, archivoUsuarios, archivoLibros);

            break;
        case 7:
            puts("\nAgregar libros a tus favoritos\n");
            valArregloUsario = 0; // reinicio validos para escribir el arreglo desde el inicio
            valArregloUsario = archivoToArregloUsuario(archivoUsuarios, arregloDeUsuarios, valArregloUsario, 300);

            if (valArregloUsario > 0)
            {
                /* funcion de control para evitar sobreescribir el archivo vacio
                * si hubo algun error al pasar los datos del archivo al array */

                posUsuario = buscarPosUsuarioPorId(idSession, arregloDeUsuarios, valArregloUsario); /// creo que no está funcionando esta funcion

                if(posUsuario == -1)
                {
                    puts("\nERROR: No se pudo recuperar la informacion del usuario\n");
                }
                else
                {
                    subMenuAgregaFavsDeUser(posUsuario,arregloDeUsuarios,archivoLibros);
                    arrayToArchivo(archivoUsuarios,arregloDeUsuarios,valArregloUsario); //sobreescribo el archivo con las modificaciones
                }
            }
            else
            {
                puts("\n ERROR: El archivo está vacio o no funcionó la transferencia de datos al buffer");
            }

            break;
        case 8:
            puts("\nQuitar libros de tus favoritos\n");
            valArregloUsario = 0; // reinicio validos para escribir el arreglo desde el inicio
            valArregloUsario = archivoToArregloUsuario(archivoUsuarios, arregloDeUsuarios, valArregloUsario, 300);

            if (valArregloUsario > 0)
            {
                /* funcion de control para evitar sobreescribir el archivo vacio
                * si hubo algun error al pasar los datos del archivo al array */

                posUsuario = buscarPosUsuarioPorId(idSession, arregloDeUsuarios, valArregloUsario); /// creo que no está funcionando esta funcion

                if(posUsuario == -1)
                {
                    puts("ERROR: No se pudo recuperar la informacion del usuario\n");
                }
                else
                {
                    subMenuEliminaFavsDeUser(posUsuario,arregloDeUsuarios,archivoLibros);
                    arrayToArchivo(archivoUsuarios,arregloDeUsuarios,valArregloUsario); //sobreescribo el archivo con las modificaciones
                }
            }
            break;
        case 9:
            puts("\nVer una recomendacion aleatoria\n");

            muestraLibroComentAleatorio(archivoLibros,archivoComentarios,archivoUsuarios);

            break;
        case 10:
            puts("\nInhabilitar/Habilitar libros y sus comentarios\n");

            subMenuDeshabHabLibrosAdmin(archivoLibros,archivoUsuarios,archivoComentarios);

            break;
        case 11:
            puts("\nElimina definitivamente libros y sus comentarios\n");

            subMenuEliminaLibrosAdmin(archivoLibros, archivoUsuarios, archivoComentarios);

            break;
        case 0:
            break;
        default:
            system("color 74");
            printf("\nOPCION INVALIDA\n");
        }
        puts("\n\n");
        system("PAUSE");
        system("cls");
        system("color 75");
    }
    while(opcion != 0);
}

int opcionSubMenuComentariosAdmin()
{
    int opcion = -1;

    system("color 75");
    printf("------------------------------------------------------\n");
    printf("   SECCION COMENTARIOS Y VALORACIONES ADMINISTRADOR  \n");
    printf("------------------------------------------------------\n");
    printf("\n 1-  Comentar y puntuar un libro");
    printf("\n 2-  Ver todos tus comentarios y puntuaciones");
    printf("\n 3-  Modificar tus comentarios y puntuaciones");
    printf("\n 4-  Eliminar tus comentarios y puntuaciones");
    printf("\n 5-  Ver comentarios y puntuaciones de un libro. Busca por titulo");
    printf("\n 6-  Ver todos los comentarios y puntuaciones.");
    printf("\n 7-  Habilitar/Deshabilitar comentarios y puntuaciones. No modifica las puntuaciones de los libros.");
    printf("\n 8-  Eliminar comentarios y puntuaciones de otros usuarios.");
    printf("\n 0-  Volver al menu anterior.");

    printf("\n\n Ingresa una opcion:  ");
    fflush(stdin);
    scanf("%d", &opcion);
    printf("\n");

    return opcion;
}

void subMenuComentariosAdmin(usuario SESSION, char archivoComentarios[],char archivoLibros[], char archivoUsuarios[])
{
    int opcion = -1;

    stComentario arregloComentarios[500];
    int validosComentarios = 0;

    stLibro arregloLibros[500];
    int valLibros = 0;


    do
    {
        opcion = opcionSubMenuComentariosAdmin();

        switch (opcion)
        {
        case 1:
            puts("\nComentar y puntuar un libro\n\n");

            subMenuAgregaComentNuevo(SESSION,archivoComentarios,archivoLibros);

            break;
        case 2:
            puts("\nVer todos tus comentarios y puntuaciones\n\n");

            validosComentarios = 0; // reinicio validos para escribir el arreglo desde el inicio
            validosComentarios = archivoToArrayComenSegunIdUsuario(archivoComentarios,arregloComentarios,validosComentarios,500,SESSION.id);
            subMenuImprimeComentariosAdministradores(arregloComentarios,validosComentarios,archivoLibros,archivoUsuarios);

            break;
        case 3:
            puts("\nModificar tus comentarios y puntuaciones\n\n");

            validosComentarios = 0; // reinicio validos para escribir el arreglo desde el inicio
            valLibros = 0; // reinicio validos para escribir el arreglo desde el inicio
            archivoToArrayComentario(archivoComentarios,arregloComentarios,&validosComentarios,500);
            valLibros = archivoToArrayLibros(archivoLibros,arregloLibros,valLibros,500);

            if (validosComentarios > 0)
            {
                /* funcion de control para evitar sobreescribir el archivo vacio
                si hubo algun error al pasar los datos del archivo al array*/

                modificaComentarioLibro(arregloLibros,valLibros,arregloComentarios,validosComentarios,archivoLibros,archivoComentarios,SESSION.id);
                arrayToArchivoComentarios(arregloComentarios,validosComentarios,archivoComentarios);
            }
            else
            {
                puts("\n ERROR: El archivo está vacio o no funcionó la transferencia de datos al buffer\n");
            }
            break;
        case 4:
            puts("\nEliminar tus comentarios y puntuaciones\n\n");

            subMenuEliminaComentarioPropio(archivoLibros,archivoComentarios,SESSION.id);

            break;
        case 5:
            puts("\nVer comentarios y puntuaciones de un libro. Busca por titulo\n\n");

            subMenuImprimeComentariosDeUnLibro(archivoLibros, archivoComentarios, archivoUsuarios);

            break;
        case 6:
            puts("\nVer todos los comentarios y puntuaciones\n\n");

            validosComentarios = 0; // reinicio validos para escribir el arreglo desde el inicio
            archivoToArrayComentario(archivoComentarios,arregloComentarios,&validosComentarios,500);
            subMenuImprimeComentariosAdministradores(arregloComentarios,validosComentarios,archivoLibros,archivoUsuarios);

            break;
        case 7:
            puts("\nHabilitar/Deshabilitar comentarios y puntuaciones\n\n");



            break;
        case 8:
            puts("\nEliminar comentarios y puntuaciones de otros usuarios\n\n");



            break;
        case 0:
            break;
        default:
            system("color 74");
            printf("\nOPCION INVALIDA\n");
        }
        puts("\n\n");
        system("PAUSE");
        system("cls");
        system("color 75");
    }
    while(opcion != 0);
}

/// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------///
///         ZONA DE USUARIOS CLIENTES
/// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------///

int opcionesMenuUsuario()
{
    int eleccion;

    system("color 75");
    printf("----------------------------------------------\n");
    printf("              MENU PRINCIPAL  \n");
    printf("----------------------------------------------\n");
    printf("\n 1-  Ir a SECCION COMENTARIOS");
    printf("\n 2-  Ir a SECCION LIBROS");
    printf("\n 3-  Ver mi perfil");
    printf("\n 4-  Editar mi perfil");
    printf("\n 0-  Cerrar sesion");

    printf("\n\n Ingresa una opcion:  ");
    fflush(stdin);
    scanf("%d", &eleccion);
    printf("\n");

    return eleccion;
}

void menuUsuarios(usuario arregloUsuarios[], int usuarioLogueado, usuario SESSION, char archivoUsuarios[], char archivoLibros[], char archivoComentarios[])
{
    /*Función de administración del menu principal de usuarios clientes*/

    int opcionMenu = -1;

    do
    {
        opcionMenu = opcionesMenuUsuario();
        system("cls");

        switch(opcionMenu)
        {
        case 1: //Ir a SECCION COMENTARIOS
            subMenuComentariosUsuario(SESSION,archivoComentarios,archivoLibros,archivoUsuarios);

            break;
        case 2: //Ir a SECCION LIBROS

            subMenuLibrosUsuario(SESSION,archivoLibros,archivoUsuarios,archivoComentarios);
            break;
        case 3: //ver mi perfil

            puts("MI PERFIL:\n");
            imprimirUnRegistro(SESSION);

            break;
        case 4: //editar mi perfil

            editarUsuario(archivoUsuarios, SESSION.id);

            break;
        case 0:
            break;

        default:
            system("color 74");
            printf("\nOPCION INVALIDA\n");
        }
        puts("\n\n");
        system("PAUSE");
        system("cls");
        system("color 75");

    }
    while(opcionMenu != 0);
}

int opcionSubMenuLibrosUsuario()
{
    int opcion = -1;

    system("color 75");
    printf("----------------------------------------------\n");
    printf("                SECCION LIBROS   \n");
    printf("----------------------------------------------\n");
    printf("\n 1-  Ver lista de libros guardados.");
    printf("\n 2-  Ver libros de una categoria.");
    printf("\n 3-  Ver libros de un autor.");
    printf("\n 4-  Agregar un libro nuevo.");
    printf("\n 5-  Buscar un libro por titulo y modificarlo.");
    printf("\n 6-  Ver tus libros favoritos.");
    printf("\n 7-  Agregar un libro a tus favoritos.");
    printf("\n 8-  Quitar un libro a tus favoritos.");
    printf("\n 9-  Ver una recomendacion aleatoria.");
    printf("\n 0-  Volver al menu anterior.");

    printf("\n\n Ingresa una opcion:  ");
    fflush(stdin);
    scanf("%d", &opcion);
    puts("\n");

    return opcion;
}

void subMenuLibrosUsuario(usuario SESSION, char archivoLibros[], char archivoUsuarios[], char archivoComentarios[])
{
    int opcion = -1;

    char categoriaElegida[50];
    stLibro librosCategBuscada[200];
    int valLibrosCategBuscada = 0;

    char autorBuscado[50];
    stLibro librosDelAutor[200];
    int valLibrosDelAutor = 0;

    stLibro libreriaCompleta[300];
    int valLibreriaCompleta = 0;

    usuario arregloDeUsuarios[300];
    int valArregloUsario = 0;
    int posUsuario = -1;
    int idSession = SESSION.id;

    do
    {
        opcion = opcionSubMenuLibrosUsuario();

        switch (opcion)
        {
        case 1:
            puts("\nVer lista de libros guardados\n");
            muestraArchivoLibrosUsuario(archivoLibros);

            break;
        case 2:
            puts("\n\nVer libros de una categoria\n");
            puts("\n Que categoria quieres ver?");
            eligeCategoriaLibro(categoriaElegida);

            valLibrosCategBuscada = archivoToArrayLibrosSegunCategoria(archivoLibros, librosCategBuscada, valLibrosCategBuscada, 200, categoriaElegida);

            if( valLibrosCategBuscada == 0)
            {
                puts("No se encontraron libros de esa categoria en nuestros archivos.");
            }
            else
            {
                muestraArregloLibrosUsuario(librosCategBuscada, valLibrosCategBuscada);
            }

            break;
        case 3:
            puts("\n\nVer libros de un autor\n");
            puts("\n Ingresa el nombre del autor del cual quieres ver los libros: ");
            fflush(stdin);
            gets(autorBuscado);

            valLibrosDelAutor = archivoToArrayLibrosSegunAutor(archivoLibros, librosDelAutor, valLibrosDelAutor, 200, autorBuscado);

            if( valLibrosDelAutor == 0)
            {
                puts("\nNo se encontraron libros de ese autor en nuestros archivos\n");
            }
            else
            {
                muestraArregloLibrosUsuario(librosDelAutor, valLibrosDelAutor);
            }

            break;
        case 4:
            puts("\nAgregar un libro nuevo\n");
            cargaLibrosAlArchivo(archivoLibros);

            break;

        case 5:
            puts("\nBuscar un libro por titulo y modificarlo\n");
            valLibreriaCompleta = 0; // reinicio validos para escribir el arreglo desde el inicio
            valLibreriaCompleta = archivoToArrayLibros(archivoLibros,libreriaCompleta,valLibreriaCompleta,300);

            if (valLibreriaCompleta > 0)
            {
                /* funcion de control para evitar sobreescribir el archivo vacio
                si hubo algun error al pasar los datos del archivo al array*/

                modificaDatosLibro(libreriaCompleta,valLibreriaCompleta);
                arregloToArchivoLibros(libreriaCompleta, valLibreriaCompleta, archivoLibros);
            }
            else
            {
                puts("\n ERROR: El archivo está vacio o no funcionó la transferencia de datos al buffer\n");
            }

            break;
        case 6:
            puts("\nVer tus libros favoritos\n\n");

            muestraLibrosFavoritosDeUsuario(SESSION.id, archivoUsuarios, archivoLibros);

            break;
        case 7:
            puts("\nAgregar libros a tus favoritos\n");
            valArregloUsario = 0; // reinicio validos para escribir el arreglo desde el inicio
            valArregloUsario = archivoToArregloUsuario(archivoUsuarios, arregloDeUsuarios, valArregloUsario, 300);

            if (valArregloUsario > 0)
            {
                /* funcion de control para evitar sobreescribir el archivo vacio
                * si hubo algun error al pasar los datos del archivo al array */

                posUsuario = buscarPosUsuarioPorId(idSession, arregloDeUsuarios, valArregloUsario);

                if(posUsuario == -1)
                {
                    puts("\nERROR: No se pudo recuperar la informacion del usuario\n");
                }
                else
                {
                    subMenuAgregaFavsDeUser(posUsuario,arregloDeUsuarios,archivoLibros);
                    arrayToArchivo(archivoUsuarios,arregloDeUsuarios,valArregloUsario); //sobreescribo el archivo con las modificaciones
                }
            }
            else
            {
                puts("\n ERROR: El archivo está vacio o no funcionó la transferencia de datos al buffer");
            }

            break;
        case 8:
            puts("\nQuitar libros de tus favoritos\n");
            valArregloUsario = 0; // reinicio validos para escribir el arreglo desde el inicio
            valArregloUsario = archivoToArregloUsuario(archivoUsuarios, arregloDeUsuarios, valArregloUsario, 300);

            if (valArregloUsario > 0)
            {
                /* funcion de control para evitar sobreescribir el archivo vacio
                * si hubo algun error al pasar los datos del archivo al array */

                posUsuario = buscarPosUsuarioPorId(idSession, arregloDeUsuarios, valArregloUsario);

                if(posUsuario == -1)
                {
                    puts("ERROR: No se pudo recuperar la informacion del usuario\n");
                }
                else
                {
                    subMenuEliminaFavsDeUser(posUsuario,arregloDeUsuarios,archivoLibros);
                    arrayToArchivo(archivoUsuarios,arregloDeUsuarios,valArregloUsario); //sobreescribo el archivo con las modificaciones
                }
            }
            break;
        case 9:
            puts("\nVer una recomendacion aleatoria\n");

            muestraLibroComentAleatorio(archivoLibros,archivoComentarios,archivoUsuarios);

            break;
        case 0:
            break;
        default:
            system("color 74");
            printf("\nOPCION INVALIDA\n");
        }
        puts("\n\n");
        system("PAUSE");
        system("cls");
        system("color 75");
    }
    while(opcion != 0);
}

int opcionSubMenuComentariosUsuario()
{
    int opcion = -1;

    system("color 75");
    printf("------------------------------------------------------\n");
    printf("          SECCION COMENTARIOS Y VALORACIONES   \n");
    printf("------------------------------------------------------\n");
    printf("\n 1-  Comentar y puntuar un libro");
    printf("\n 2-  Ver todos tus comentarios y puntuaciones");
    printf("\n 3-  Modificar tus comentarios y puntuaciones");
    printf("\n 4-  Eliminar tus comentarios y puntuaciones");
    printf("\n 5-  Ver comentarios y puntuaciones de un libro. Busca por titulo");
    printf("\n 0-  Volver al menu anterior.");

    printf("\n\n Ingresa una opcion:  ");
    fflush(stdin);
    scanf("%d", &opcion);
    printf("\n");

    return opcion;
}

void subMenuComentariosUsuario(usuario SESSION, char archivoComentarios[],char archivoLibros[], char archivoUsuarios[])
{
    int opcion = -1;

    stComentario arregloComentarios[500];
    int validosComentarios = 0;

    stLibro arregloLibros[500];
    int valLibros = 0;


    do
    {
        opcion = opcionSubMenuComentariosUsuario();

        switch (opcion)
        {
        case 1:
            puts("\nComentar y puntuar un libro\n\n");

            subMenuAgregaComentNuevo(SESSION,archivoComentarios,archivoLibros);

            break;
        case 2:
            puts("\nVer todos tus comentarios y puntuaciones\n\n");

            validosComentarios = 0; // reinicio validos para escribir el arreglo desde el inicio
            validosComentarios = archivoToArrayComenSegunIdUsuario(archivoComentarios,arregloComentarios,validosComentarios,500,SESSION.id);
            subMenuImprimeComentariosUsuarios(arregloComentarios,validosComentarios,archivoLibros,archivoUsuarios);

            break;
        case 3:
            puts("\nModificar tus comentarios y puntuaciones\n\n");

            validosComentarios = 0; // reinicio validos para escribir el arreglo desde el inicio
            valLibros = 0; // reinicio validos para escribir el arreglo desde el inicio
            archivoToArrayComentario(archivoComentarios,arregloComentarios,&validosComentarios,500);
            valLibros = archivoToArrayLibros(archivoLibros,arregloLibros,valLibros,500);

            if (validosComentarios > 0)
            {
                /* funcion de control para evitar sobreescribir el archivo vacio
                si hubo algun error al pasar los datos del archivo al array*/

                modificaComentarioLibro(arregloLibros,valLibros,arregloComentarios,validosComentarios,archivoLibros,archivoComentarios,SESSION.id);
                arrayToArchivoComentarios(arregloComentarios,validosComentarios,archivoComentarios);
            }
            else
            {
                puts("\n ERROR: El archivo está vacio o no funcionó la transferencia de datos al buffer\n");
            }
            break;
        case 4:
            puts("\nEliminar tus comentarios y puntuaciones\n\n");

            subMenuEliminaComentarioPropio(archivoLibros,archivoComentarios,SESSION.id);

            break;
        case 5:
            puts("\nVer comentarios y puntuaciones de un libro. Busca por titulo\n\n");

            subMenuImprimeComentariosDeUnLibro(archivoLibros, archivoComentarios, archivoUsuarios);

            break;
        case 0:
            break;
        default:
            system("color 74");
            printf("\nOPCION INVALIDA\n");
        }
        puts("\n\n");
        system("PAUSE");
        system("cls");
        system("color 75");
    }
    while(opcion != 0);
}





