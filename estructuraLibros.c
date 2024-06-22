#include "estructuraLibros.h"


stLibro cargaUnNuevoLibro(char tituloNuevoLibro[], char archivoLibros[])
{
    stLibro libro; // Variable para cargar en nuevo libro

    char aux[100];
    char categoria[50];

    /* Uso la funcion de contar la cantidad de elementos del archivo para asignarle
    * al libro el siguinte ID disponible y le sumo uno para que no exista el ID 0 */
    libro.idLibro = buscaMayorIDLibro(archivoLibros) + 1;

    strcpy(libro.titulo, tituloNuevoLibro);

    printf("\nIngrese la editorial del libro: ");
    fflush(stdin);
    gets(aux);
    strcpy(libro.editorial, aux);

    printf("\nIngrese el autor del libro: ");
    fflush(stdin);
    gets(aux);
    strcpy(libro.autor, aux);

    printf("\nSeleccione la categoria del libro: ");
    eligeCategoriaLibro(categoria);
    strcpy(libro.categoria, categoria);

    libro.eliminado = 0;

    printf("\nTU LIBRO ES: \n");

    muestraUnLibroAdmin(libro);

    return libro;
}

int buscaMayorIDLibro(char archivoLibros[])
{
    stLibro arregloLibros[500];
    int val = 0;
    int mayorId = -1;

    val = archivoToArrayLibros(archivoLibros,arregloLibros,val,500);

    for(int i=0; i<val; i++)
    {
        if(arregloLibros[i].idLibro>mayorId)
        {
            mayorId = arregloLibros[i].idLibro;
        }
    }

    return mayorId;
}


void eligeCategoriaLibro(char categoria[])
{
    int eleccion;

    char op1[] = "Novelas/Ciencia Ficcion";
    char op2[] = "Historicos/Biograficos";
    char op3[] = "Educativos/Academicos";
    char op4[] = "Desarrollo personal/Autoayuda";
    char op5[] = "Infantiles";
    char op6[] = "Ciencia y tecnologia";
    char op7[] = "Cocina y gastronomia";


    printf("\n 1-  %s", op1);
    printf("\n 2-  %s", op2);
    printf("\n 3-  %s", op3);
    printf("\n 4-  %s", op4);
    printf("\n 5-  %s", op5);
    printf("\n 6-  %s", op6);
    printf("\n 7-  %s", op7);

    do
    {
        printf("\n\n Ingresa una opcion:  ");
        scanf("%d", &eleccion);

        switch(eleccion)
        {
        case 1:
            strcpy(categoria, op1);
            break;
        case 2:
            strcpy(categoria, op2);
            break;
        case 3:
            strcpy(categoria, op3);
            break;
        case 4:
            strcpy(categoria, op4);
            break;
        case 5:
            strcpy(categoria, op5);
            break;
        case 6:
            strcpy(categoria, op6);
            break;
        case 7:
            strcpy(categoria, op7);
            break;
        default:
            puts("Opcion incorrecta. Intente nuevamente: ");
            break;
        }
    }
    while(eleccion > 7 && eleccion < 1);
}

void cargaLibrosAlArchivo(char archivoLibros[])
{
    stLibro nuevoLibro;
    int option = 0;
    int flag = -1;
    char tituloNuevoLibro[100];

    do
    {
        system("cls");
        puts("CARGANDO NUEVO LIBRO\n");
        printf("\nIngrese el titulo del libro: ");
        fflush(stdin);
        gets(tituloNuevoLibro);

        flag = existeLibro(tituloNuevoLibro,archivoLibros);
        if(flag == 0)  //Valida que el libro nuevo todavia no exista en el archivo
        {
            FILE *archi = fopen(archivoLibros, "ab");
            if(archi)
            {
                nuevoLibro = cargaUnNuevoLibro(tituloNuevoLibro, archivoLibros);
                fwrite(&nuevoLibro, sizeof(stLibro), 1, archi);
                fclose(archi);
            }
            else
            {
                printf("No se pudo abrir el archivo.");
            }
        }
        else if(flag == 1)  //Si el titulo ya existe en el archivo, suspende la carga
        {
            puts("El libro ya existe en nustros archivos!");
        }
        printf("Si desea cargar otro libro presione 1, sino presione cualquier otra tecla\n");
        scanf("%d", &option);
        system("cls");
    }
    while(option == 1);
}

int archivoToArrayLibros(char nombreArchivo[], stLibro libros[], int v, int dim)
{
    int cant = cantElementosArchivo(nombreArchivo, sizeof(stLibro));
    int total = cant + v;
    stLibro aux;

    FILE *archi = fopen(nombreArchivo, "rb");

    if(archi && total <= dim)
    {
        while(fread(&aux, sizeof(stLibro), 1, archi) > 0)
        {
            libros[v] = aux;
            v++;
        }
        fclose(archi);
    }
    return v;
}

int existeLibro(char nombreLibro[], char archivoLibros[])
{
    stLibro arrayLibro[150];
    int validos = 0, i = 0;
    int flag = 0; // en un primcipio, suponemos que el libro no existe en el archivo

    validos = archivoToArrayLibros(archivoLibros, arrayLibro, validos, 200);

    while(i < validos && flag == 0)
    {
        if(strcmpi(nombreLibro, arrayLibro[i].titulo) == 0)  // comprueba, libro por libro, si el titulo ya está guardado en el archivo (no diferencia entre mayusculas y minusculas
        {
            flag = 1; // El libro ya existe en el archivo
        }
        i++;
    }
    return flag;
}

void muestraUnLibroAdmin(stLibro libro)
{
    printf("\n-----------------------------------------------\n");
    printf("Titulo: %s", libro.titulo);
    printf("\n-----------------------------------------------\n");
    printf("ID Libro ............. %d", libro.idLibro);
    printf("\nAutor ................ %s", libro.autor);
    printf("\nEditorial ............ %s", libro.editorial);
    printf("\nCategoria ............ %s", libro.categoria);
    printf("\nValoracion promedio .. %.2f/5", libro.valoracion);
    if(libro.eliminado == 1)
    {
        printf("\nEstado................ DESHABILITADO");
    }
    else if(libro.eliminado == 0)
    {
        printf("\nEstado................ HABILITADO");
    }
    printf("\n-----------------------------------------------\n");
}

void muestraUnLibroUsuario(stLibro libro)
{
    if(libro.eliminado == 0)
    {
        printf("\n-----------------------------------------------\n");
        printf("Titulo: %s", libro.titulo);
        printf("\n-----------------------------------------------\n");
        printf("Autor ................ %s", libro.autor);
        printf("\nEditorial ............ %s", libro.editorial);
        printf("\nCategoria ............ %s", libro.categoria);
        printf("\nValoracion promedio .. %.2f/5", libro.valoracion);
        printf("\n-----------------------------------------------\n");
    }
}

void muestraArchivoLibrosAdmins(char archivoLibros[])
{
    FILE * archi = fopen(archivoLibros, "rb");
    stLibro aux;

    if(archi)
    {
        while(fread(&aux, sizeof(stLibro), 1, archi)>0)
        {
            muestraUnLibroAdmin(aux);
        }
        fclose(archi);
    }
}

void muestraArchivoLibrosUsuario(char archivoLibros[])
{
    FILE * archi = fopen(archivoLibros, "rb");
    stLibro aux;

    if(archi)
    {
        while(fread(&aux, sizeof(stLibro), 1, archi)>0)
        {
            muestraUnLibroUsuario(aux);
        }
        fclose(archi);
    }
}

void muestraArregloLibrosAdmin(stLibro arregloLibros[], int vLibros)
{
    int i = 0;

    while(i < vLibros)
    {
        muestraUnLibroAdmin(arregloLibros[i]);
        i++;
    }
    printf("\n");
}

void muestraArregloLibrosUsuario(stLibro arregloLibros[], int vLibros)
{
    int i = 0;

    while(i < vLibros)
    {
        muestraUnLibroUsuario(arregloLibros[i]);
        i++;
    }
    printf("\n");
}


int buscarIdLibroConTitulo(char tituloLibro[], char archivoLibros[])
{
    stLibro arrayLibro[200];
    int validos = 0, i = 0;
    char flag = 1;
    int id = -1; //Por si  no lo encuentra, debe retornar un valor no validos como id. El id no puede ser negativo.

    validos = archivoToArrayLibros(archivoLibros, arrayLibro, validos, 200);

    while(i < validos && flag == 1)
    {
        if(strcmpi(tituloLibro, arrayLibro[i].titulo) == 0)
        {
            flag = 0;
            id = arrayLibro[i].idLibro;
        }
        i++;
    }
    return id; // si no encuentra el libro, retorna -1
}

stLibro buscarLibroPorId(int idLibroBuscado, stLibro arregloLibros[], int v)
{
    int i = 0;
    stLibro libroEncontrado;
    char flag = 1;

    while(i < v && flag == 1)
    {
        if(arregloLibros[i].idLibro == idLibroBuscado)
        {
            libroEncontrado = arregloLibros[i];
            flag = 0;
        }
        i++;
    }
    return libroEncontrado;
}

int archivoToArrayLibrosSegunCategoria(char archivoLibros[], stLibro arregloLibros[], int v, int dim, char categoria[])
{
    stLibro aux;
    FILE * archi = fopen(archivoLibros, "rb");
    int i = 0;

    if(archi)
    {
        while( v < dim && fread(&aux, sizeof(stLibro), 1, archi) > 0)
        {
            if(strcmpi(categoria, aux.categoria) == 0)
            {
                arregloLibros[i] = aux;
                i++;
            }
        }
        fclose(archi);
    }
    return i; //retorna los validos
}

int archivoToArrayLibrosSegunAutor(char archivoLibros[], stLibro arregloLibros[], int v, int dim, char autorBuscado[])
{
    stLibro aux;
    FILE * archi = fopen(archivoLibros, "rb");
    int i = v;

    if(archi)
    {
        while( i < dim && fread(&aux, sizeof(stLibro), 1, archi) > 0)
        {
            if(strcmpi(autorBuscado, aux.autor) == 0)
            {
                arregloLibros[i] = aux;
                i++;
            }
        }
        fclose(archi);
    }
    return i; //retorna los validos
}
void modificaDatosLibro(stLibro arregloLibros[], int val)
{
    char tituloBuscado[100];
    int flag = 0;
    int opcion1 = -1;
    int posEnArreglo = -1;

    do
    {
        puts("Ingrese el titulo del libro que desea modificar:");
        fflush(stdin);
        gets(tituloBuscado);

        posEnArreglo = buscaLibroPosicionEnArregloTitulo(arregloLibros,val,tituloBuscado);
        if(posEnArreglo >= 0)
        {
            subMenuModificaArregloDatosLibro(arregloLibros,posEnArreglo);
            flag = 1;
            opcion1 = 0;
        }
        else
        {
            puts("\nNo existe ningun libro en nuestro archivo con ese titulo.");
            puts("\nIngrese 1 para volver a intentar o 0 para salir.");
            scanf("%d", &opcion1);
        }
    }
    while(flag == 0 && opcion1 != 0);
}

int buscaLibroPosicionEnArregloTitulo(stLibro arreglo[], int val, char titulo[])
{
    int pos = -1;
    int i = 0;

    while(i < val && pos == -1 )
    {
        if(strcmpi(titulo, arreglo[i].titulo) == 0)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}


void subMenuModificaArregloDatosLibro(stLibro arrayLibros[], int posEnArreglo)
{
    int option = 0;
    int option2 = 0;

    do
    {
        puts("El libro que estas por modificar es:");
        muestraUnLibroUsuario(arrayLibros[posEnArreglo]);
        puts("\n");

        printf("Cual campo queres modificar?\n");
        printf("1. Titulo\n");
        printf("2. Editorial \n");
        printf("3. Autor\n");
        printf("4. Categoria\n");

        scanf("%d",&option);

        switch(option)
        {
        case 1:
            puts("Ingrese el nuevo titulo:\n");
            fflush(stdin);
            gets(arrayLibros[posEnArreglo].titulo);
            puts("Se modifico correctamente.\n");
            system("PAUSE");
            option2 = 0;
            break;
        case 2:
            puts("Ingrese la nueva editorial:\n");
            fflush(stdin);
            gets(arrayLibros[posEnArreglo].editorial);
            puts("Se modifico correctamente\n");
            system("PAUSE");
            option2 = 0;
            break;
        case 3:
            puts("Ingrese el nuevo autor: ");
            fflush(stdin);
            gets(arrayLibros[posEnArreglo].autor);
            puts("Se modifico correctamente\n");
            system("PAUSE");
            option2 = 0;
            break;
        case 4:
            puts("Selecione la nueva categoria del libro: ");
            eligeCategoriaLibro(arrayLibros[posEnArreglo].categoria);
            puts("Se modifico correctamente\n");
            system("PAUSE");
            option2 = 0;
            break;
        default:
            printf("No existe esa opción. Quiere volver a intentar? Presione 1.\n");
            scanf("%d", &option2);
        }
        system("cls");
    }
    while (option2 == 1);
}

void arregloToArchivoLibros(stLibro arregloLibros[], int v, char archivoLibros[])
{
    FILE * archi = fopen(archivoLibros,"wb");

    if(archi)
    {
        fwrite(arregloLibros,sizeof(stLibro),v,archi);
        fclose(archi);
    }
}

void muestraLibrosFavoritosDeUsuario(int idUsuario, char archivoUsuarios[], char archivoLibros[])
{
    stLibro libroAux;
    usuario usuarioAux;

    stLibro arregloLibros[500];
    int valArregloLibros = 0;

    usuario arregloUsuarios[500];
    int valArregloUsuarios = 0;
    int posUsuarioAux = -1;

    valArregloLibros = archivoToArrayLibros(archivoLibros,arregloLibros,valArregloLibros,500);
    valArregloUsuarios = archivoToArregloUsuario(archivoUsuarios, arregloUsuarios,valArregloUsuarios,500);

    posUsuarioAux = buscarUsuarioPorId(idUsuario, arregloUsuarios,valArregloUsuarios);
    usuarioAux = arregloUsuarios[posUsuarioAux];

    printf("%s, tus libros favoritos son:\n\n", usuarioAux.nombre);
    for(int i = 0; i<usuarioAux.validosFavoritos; i++)
    {
        libroAux = buscarLibroPorId(usuarioAux.librosFavoritos[i],arregloLibros,valArregloLibros);
        printf("%d. %s\n", i+1, libroAux.titulo);
    }
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

void intercambioLibrosArreglo(stLibro *a, stLibro *b)
{
    stLibro libroAux = *a;

    *a = *b;
    *b = libroAux;
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

void intercambioComentariosArreglo(stComentario *a, stComentario *b)
{
    stComentario comenAux = *a;

    *a = *b;
    *b = comenAux;
}

int existeIdArreglo(int id, int arregloId[], int val)
{
    int posicion = -1;
    int i = 0;

    while(i<val && posicion == -1)
    {
        if(id == arregloId[i])
        {
            posicion = i;
        }
        else
        {
            i++;
        }
    }
    return posicion;
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

void mostrarLibroComentAleatorio(char archivoLibros[],char archivoComentarios[])
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

int posRandomArray(int validos)
{
    srand(time(NULL));
    int pos = 0;

    pos = rand()%validos - 1;

    return pos;
}





