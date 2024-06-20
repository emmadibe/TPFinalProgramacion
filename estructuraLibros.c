#include "estructuraLibros.h"


stLibro cargaUnNuevoLibro(char tituloNuevoLibro[], char archivoLibros[])
{
    stLibro libro; // Variable para cargar en nuevo libro

    char aux[100];
    char categoria[50];

    /* Uso la funcion de contar la cantidad de elementos del archivo para asignarle
    * al libro el siguinte ID disponible y le sumo uno para que no exista el ID 0 */
    libro.idLibro = (cantElementosArchivo(archivoLibros, sizeof(stLibro)) + 1);

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
    char option = 0;
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
        printf("Desea cargar otro libro? Presiones ESC para terminar\n");
        fflush(stdin);
        option = getch();
        system("cls");
    }
    while(option != 27);
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
    printf("ID Libro ............... %d", libro.idLibro);
    printf("\nAutor ................ %s", libro.autor);
    printf("\nEditorial ............ %s", libro.editorial);
    printf("\nCategoria ............ %s", libro.categoria);
    printf("\nValoracion promedio .. %.2f", libro.valoracion);
    printf("\n-----------------------------------------------\n");
}

void muestraUnLibroUsuario(stLibro libro)
{
    printf("\n-----------------------------------------------\n");
    printf("Titulo: %s", libro.titulo);
    printf("\n-----------------------------------------------\n");
    printf("\nAutor ................ %s", libro.autor);
    printf("\nEditorial ............ %s", libro.editorial);
    printf("\nCategoria ............ %s", libro.categoria);
    printf("\nValoracion promedio .. %.2f", libro.valoracion);
    printf("\n-----------------------------------------------\n");
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
        printf("POSENARREGLO %d", posEnArreglo);
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

void muestraLibrosFavoritosDeUsuario(usuario usuarioConsulta, stLibro arregloLibros[], int val)
{
    stLibro libroAux;

    puts("Tus libros favoritos son:");
    for(int i = 0; i<usuarioConsulta.validosFavoritos; i++)
    {
        libroAux = buscarLibroPorId(usuarioConsulta.librosFavoritos[i],arregloLibros,val);
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
        puts("Indica el titulo del libro que deseas agregar a tu lista de favoritos: ");
        fflush(stdin);
        gets(tituloAux);
        idLibroAux = buscarIdLibroConTitulo(tituloAux, archivoLibros);

        if(idLibroAux == -1)
        {
            puts("No pudimos encontrar el libro que buscas");
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
                puts("Tu lista de favoritos esta llena, elimina otro libro e intenta nuevamente");
            }
        }
        puts("Si quieres agregar otro libro presiona 1, para terminar presiona cualquier otra tecla");
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
                intercambioVariables(&usuarioAux.librosFavoritos[posLibroFav], &usuarioAux.librosFavoritos[i]); //muevo el idLibro al final del array y disminuyo los validos.
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

