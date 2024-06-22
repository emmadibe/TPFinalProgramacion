#include "funcionesGenerales.h"

int cantElementosArchivo(char nombreArchivo[], int tamanioEstructura)
{

    FILE * archi = fopen(nombreArchivo,"rb"); //Abro el archivo que paso por parámetro en modo lectura binaria (rb).
    int cant = 0;

    if(archi) //Compruebo que el archivo se haya abierto correctamente.
    {
        fseek(archi, 0, SEEK_END); //Desplazo el indicador de posesión al final del archivo (EOF).
        cant = ftell(archi)/tamanioEstructura; //En esta línea de código obtengo la cantidad de elementos que tengo en el archivo.
        fclose(archi); //Cierro el archivo.
    }
    return cant;
}

int buscaPosicionEnArregloEntero(int arreglo[], int val, int entero)
{
    int pos = -1;
    int i = 0;

    while(i < val && pos == -1 )
    {
        if(entero == arreglo[i])
        {
            pos = i;
        }
        i++;
    }
    return pos;
}

void intercambioVariablesInt(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int posRandomArray(int validos)
{
    srand(time(NULL));
    int pos = 0;

    pos = rand()%validos - 1;

    return pos;
}

void muestraLibrosFavoritosDeUsuario(int idUsuario, char archivoUsuarios[], char archivoLibros[])
{
    stLibro libroAux;
    usuario usuarioAux;

    stLibro arregloLibros[500];
    int valArregloLibros = 0;

    usuario arregloUsuarios[500];
    int valArregloUsuarios = 0;

    valArregloLibros = archivoToArrayLibros(archivoLibros,arregloLibros,valArregloLibros,500);
    valArregloUsuarios = archivoToArregloUsuario(archivoUsuarios, arregloUsuarios,valArregloUsuarios,500);

    usuarioAux = buscarUnUsuarioPorId(idUsuario,arregloUsuarios,valArregloUsuarios);

    printf("%s, tus libros favoritos son:\n\n", usuarioAux.nombre);
    for(int i = 0; i<usuarioAux.validosFavoritos; i++)
    {
        libroAux = buscarLibroPorId(usuarioAux.librosFavoritos[i],arregloLibros,valArregloLibros);
        printf("%d. %s\n", i+1, libroAux.titulo);
    }
}

void muestraLibroComentAleatorio(char archivoLibros[],char archivoComentarios[])
{
    stLibro arregloLibros[500];
    int validosLibros = 0;
    int posLibro = -1;

    //stComentario arregloComentarios[500];
    //int valComentarios = 0;

    validosLibros = archivoToArrayLibros(archivoLibros,arregloLibros,validosLibros,500);
    posLibro = posRandomArray(validosLibros);

    muestraUnLibroUsuario(arregloLibros[posLibro]);
    /// funcion de muestra de los comentarios del libro
}

void subMenuAgregaFavsDeUser(int posUsuario, usuario arregloUsuarios[], char archivoLibros[])
{
    int idLibroAux = -1;
    char tituloAux[100];
    int control = 0;
    usuario usuarioAux = arregloUsuarios[posUsuario];
    int i = usuarioAux.validosFavoritos; //bajo los validos del arreglo de favoritos del usuario a una variable contador

    do
    {
        puts("\nIndica el titulo del libro que deseas agregar a tu lista de favoritos: \n");
        fflush(stdin);
        gets(tituloAux);
        idLibroAux = buscarIdLibroConTitulo(tituloAux, archivoLibros);

        if(idLibroAux == -1)
        {
            puts("\nNo pudimos encontrar el libro que buscas\n");
        }
        else if(idLibroAux >= 0)
        {
            if(i<50)
            {
                usuarioAux.librosFavoritos[i] = idLibroAux; //copio el id del libro al final del arreglo de la estructura
                i++;
            }
            else
            {
                puts("\nTu lista de favoritos esta llena, elimina otro libro e intenta nuevamente\n");
            }
        }
        puts("\nSi quieres agregar otro libro presiona 1, para terminar presiona cualquier otra tecla\n");
        scanf("%d", &control);
        system("cls");
    }
    while(control == 1);

    usuarioAux.validosFavoritos = i; //almaceno los nuevos validos en la estructura
    arregloUsuarios[posUsuario] = usuarioAux; // sobreescribo el usuario con la nueva lista de favoritos y los validos
}

void subMenuEliminaFavsDeUser(int posUsuario, usuario arregloUsuarios[], char archivoLibros[])
{
    int idLibroAux = -1;
    char tituloAux[100];
    int control = 0;
    usuario usuarioAux = arregloUsuarios[posUsuario];
    int i = usuarioAux.validosFavoritos; //bajo los validos del arreglo de favoritos del usuario a una variable contador
    int posLibroFav = -1;

    do
    {
        puts("Indica el titulo del libro que deseas eliminar de tu lista de favoritos: ");
        fflush(stdin);
        gets(tituloAux);
        idLibroAux = buscarIdLibroConTitulo(tituloAux, archivoLibros); // primero: busco el id del libro

        posLibroFav = buscaPosicionEnArregloEntero(usuarioAux.librosFavoritos, usuarioAux.validosFavoritos, idLibroAux);    // segundo: verifico que la id se encuentre en la lista de favoritos

        if(posLibroFav == -1)
        {
            puts("No pudimos encontrar el libro que buscas en tu lista de favoritos");
        }
        else if(posLibroFav >= 0)
        {
            if(i>0)
            {
                intercambioVariablesInt(&usuarioAux.librosFavoritos[posLibroFav], &usuarioAux.librosFavoritos[i-1]); //muevo el idLibro al final del array y disminuyo los validos.
                i--;
            }
            else
            {
                puts("Tu lista de favoritos ya esta vacia");
            }
        }
        puts("Si quieres eliminar otro libro presiona 1, para terminar presiona cualquier otra tecla");
        scanf("%d", &control);
        system("cls");
    }
    while(control == 1);

    usuarioAux.validosFavoritos = i; //almaceno los nuevos validos en la estructura
    arregloUsuarios[posUsuario] = usuarioAux; // sobreescribo el usuario con la nueva lista de favoritos y los validos
}

void subMenuEliminaLibrosAdmin(char archivoLibros[], char archivoUsuarios[], char archivoComentarios[])
{
    stLibro arregloLibros[500];
    int valArregloLibros = 0;

    char tituloAux[100];
    int posLibroArreglo = -1;
    stLibro libroEliminar;

    int control = 0;

    // 1ro: paso archivosa arreglo para trabajar en buffer
    valArregloLibros = archivoToArrayLibros(archivoLibros, arregloLibros, valArregloLibros, 500);

    do
    {
        puts("Indica el titulo del libro que deseas eliminar del archivo: ");
        fflush(stdin);
        gets(tituloAux);

        // 2do: busco posición del libro en el arreglo
        posLibroArreglo = buscaLibroPosicionEnArregloTitulo(arregloLibros, valArregloLibros, tituloAux);

        if(posLibroArreglo == -1)
        {
            puts("No pudimos encontrar el libro que buscas eliminar, intenta nuevamente");
        }
        else if(posLibroArreglo >= 0)
        {
            libroEliminar = arregloLibros[posLibroArreglo]; // guardo los datos del libro que se va a eliminar

            puts("LIBRO:");
            muestraUnLibroAdmin(libroEliminar);

            if(valArregloLibros>0)
            {
                intercambioLibrosArreglo(&arregloLibros[posLibroArreglo],&arregloLibros[valArregloLibros-1]); //muevo el idLibro al final del array y disminuyo los validos.
                valArregloLibros--;

                //Elimino los cometarios del libro y elimino el libro de las listas de favoritos

                subMenuEliminaComentariosIdLibro(libroEliminar.idLibro,archivoComentarios);
                subMenuEliminaLibroDeFavs(libroEliminar.idLibro,archivoUsuarios);

                puts("\nLibro eliminado correctamente.\n");
            }
            else
            {
                puts("No existen libros en el archivo.");
            }
            arregloToArchivoLibros(arregloLibros, valArregloLibros, archivoLibros); // sobreescrivo el archivo con los cambios
        }
        puts("Si quieres eliminar otro libro presiona 1, para terminar presiona cualquier otra tecla");
        scanf("%d", &control);
        system("cls");
    }
    while(control == 1);
}

void subMenuEliminaLibroDeFavs(int idLibroEliminado,char archivoUsuarios[])
{
    usuario arregloUsuarios[500];
    int valArregloUsuarios = 0;
    usuario aux;
    int posIdLibro = -1;

    valArregloUsuarios = archivoToArregloUsuario(archivoUsuarios,arregloUsuarios,valArregloUsuarios,500);

    for(int i = 0; i<valArregloUsuarios; i++)
    {
        aux = arregloUsuarios[i];

        posIdLibro = existeIdArreglo(idLibroEliminado, aux.librosFavoritos, aux.validosFavoritos);

        if(posIdLibro > -1)
        {
            intercambioVariablesInt(&aux.librosFavoritos[posIdLibro],&aux.librosFavoritos[aux.validosFavoritos-1]);
            aux.validosFavoritos--;

            arregloUsuarios[i] = aux;
        }
    }

    arrayToArchivo(archivoUsuarios, arregloUsuarios, valArregloUsuarios);
}

void subMenuEliminaComentariosIdLibro(int idLibroEliminado, char archivoComentarios[])
{
    stComentario arregloComentarios[500];
    int valArregloComentarios = 0;

    archivoToArrayComentario(archivoComentarios, arregloComentarios, &valArregloComentarios, 500);

    for(int i = 0; i<valArregloComentarios; i++)
    {
        if(idLibroEliminado == arregloComentarios[i].idLibro)
        {
            intercambioComentariosArreglo(&arregloComentarios[i], &arregloComentarios[valArregloComentarios-1]);
            valArregloComentarios--;
        }
    }

    arrayToArchivoComentarios(arregloComentarios, valArregloComentarios, archivoComentarios);
}

void subMenuDeshabHabLibrosAdmin(char archivoLibros[], char archivoUsuarios[], char archivoComentarios[])
{
    stLibro arregloLibros[500];
    int valArregloLibros = 0;

    char tituloAux[100];
    int posLibroArreglo = -1;

    int control = 0;
    int accion = -1;

    // 1ro: paso archivo a arreglo para trabajar en buffer
    valArregloLibros = archivoToArrayLibros(archivoLibros, arregloLibros, valArregloLibros, 500);

    do
    {
        puts("Indica el titulo del libro que deseas habilitar o deshabilitar del archivo: ");
        fflush(stdin);
        gets(tituloAux);

        // 2do: busco posición del libro en el arreglo
        posLibroArreglo = buscaLibroPosicionEnArregloTitulo(arregloLibros, valArregloLibros, tituloAux);

        if(posLibroArreglo == -1)
        {
            puts("No pudimos encontrar el libro, intenta nuevamente");
        }
        else if(posLibroArreglo >= 0)
        {
            puts("LIBRO:");
            muestraUnLibroAdmin(arregloLibros[posLibroArreglo]);

            do
            {
                puts("\nPresiona 0 para habilitar el libro, o presiona 1 para deshabilitarlo.");
                scanf("%d", &accion);

                if(accion == 1)
                {
                    arregloLibros[posLibroArreglo].eliminado = 1; // se desabilita el libro
                    subMenuEliminaLibroDeFavs(arregloLibros[posLibroArreglo].idLibro, archivoUsuarios);
                    subMenuDeshabHabComentarios(arregloLibros[posLibroArreglo].idLibro, archivoComentarios, accion);
                }
                else if(accion == 0)
                {
                    arregloLibros[posLibroArreglo].eliminado = 0; // se habilita el libro
                    subMenuDeshabHabComentarios(arregloLibros[posLibroArreglo].idLibro, archivoComentarios, accion);
                }
                else
                {
                    puts("OPCION INCORRECTA: intente nuevamente.");
                }
            }
            while(accion != 1 && accion != 0);

            arregloToArchivoLibros(arregloLibros, valArregloLibros, archivoLibros); // sobreescrivo el archivo con los cambios
        }
        puts("Si quieres habilitar/deshabilitar otro libro presiona 1, para terminar presiona cualquier otra tecla");
        scanf("%d", &control);
        system("cls");
    }
    while(control == 1);
}

void subMenuDeshabHabComentarios(int idLibro, char archivoComentarios[], int accion)
{
    stComentario arregloComentarios[500];
    int valArregloComentarios = 0;

    archivoToArrayComentario(archivoComentarios, arregloComentarios, &valArregloComentarios, 500);

    for(int i = 0; i<valArregloComentarios; i++)
    {
        if(idLibro == arregloComentarios[i].idLibro)
        {
            arregloComentarios[i].eliminado = accion;
        }
    }

    arrayToArchivoComentarios(arregloComentarios, valArregloComentarios, archivoComentarios);
}

void imprimirUnComentarioAdmin(stComentario c, stLibro arregloLibros[], int valLibros, usuario arregloUsuarios[], int valUsuarios)
{
    stLibro libroAux;
    usuario usuarioAux;

    libroAux = buscarLibroPorId(c.idLibro,arregloLibros,valLibros);
    usuarioAux = buscarUnUsuarioPorId(c.idUsuario,arregloUsuarios,valUsuarios);

    puts("------------------------------------------------");
    printf("Comentario del libro: %s\n",libroAux.titulo);
    puts("------------------------------------------------");
    printf("Usuario: %s\n", usuarioAux.username);
    printf("Titulo del comentario: %sn\n", c.tituloComentario);
    printf("Comentario: \n\n%s\n\n", c.descripcion);
    printf("Puntaje del usuario: %d\n", c.puntaje);
    printf("Fecha: %s\n", c.fechaComentario);
    printf("Fecha: %s\n", c.fechaComentario);
    if(c.eliminado == 1)
    {
        printf("\nEstado:DESHABILITADO");
    }
    else if(c.eliminado == 0)
    {
        printf("\nEstado:HABILITADO");
    }
    puts("-------------------------------------\n");
}


void imprimirUnComentarioUsuario(stComentario c, stLibro arregloLibros[], int valLibros, usuario arregloUsuarios[], int valUsuarios)
{
    stLibro libroAux;
    usuario usuarioAux;

    libroAux = buscarLibroPorId(c.idLibro,arregloLibros,valLibros);
    usuarioAux = buscarUnUsuarioPorId(c.idUsuario,arregloUsuarios,valUsuarios);
    if(c.eliminado == 0)
    {
        puts("------------------------------------------------");
        printf("Comentario del libro: %s\n",libroAux.titulo);
        puts("------------------------------------------------");
        printf("Usuario: %s\n", usuarioAux.username);
        printf("Titulo del comentario: %sn\n", c.tituloComentario);
        printf("Comentario: \n\n%s\n\n", c.descripcion);
        printf("Puntaje del usuario: %d\n", c.puntaje);
        printf("Fecha: %s\n", c.fechaComentario);
        printf("Fecha: %s\n", c.fechaComentario);
        puts("-------------------------------------\n");
    }
}

void imprimirArregloComentariosAdmin(stComentario arregloComents[], int valComents, stLibro arregloLibros[], int valLibros, usuario arregloUsuarios[], int valUsuarios)
{
    int i = 0;

    while(i < valComents)
    {
        imprimirUnComentarioAdmin(arregloComents[i],arregloLibros,valLibros,arregloUsuarios,valUsuarios);
        i++;
    }
    printf("\n");
}

void imprimirArregloComentariosUser(stComentario arregloComents[], int valComents, stLibro arregloLibros[], int valLibros, usuario arregloUsuarios[], int valUsuarios)
{
    int i = 0;

    while(i < valComents)
    {
        imprimirUnComentarioUsuario(arregloComents[i],arregloLibros,valLibros,arregloUsuarios,valUsuarios);
        i++;
    }
    printf("\n");
}

/*          INCOMPLETA

void subMenuAgregaComentNuevo(usuario sesion, char archivoComent[], char archivoLibros[])
{
    char tituloAux[100];
    int idLibroAux = -1;

    puts("Indica el titulo del lubro que deseas comentar: ");
    fflush(stdin);
    gets(tituloAux);

    idLibroAux = buscarIdLibroConTitulo(tituloAux, archivoLibros);
    if(idLibroAux == -1)
    {
        puts("No conocemos ese libro. Puedes ir a la seccion libros y agregarlo.");
    }
    else if(idLibroAux > -1)
    {

    }





}

*/









