#include "estructuraLibros.h"
#include "funcionesGenerales.h"


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
    char op6[] = "Ciencia y tecnología";
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

    FILE *archi = fopen(archivoLibros, "ab");

    if(archi != NULL)
    {
        do
        {
            printf("\nIngrese el titulo del libro: ");
            fflush(stdin);
            gets(tituloNuevoLibro);

            flag = existeLibro(tituloNuevoLibro,archivoLibros);
            if(flag == 0)  //Valida que el libro nuevo todavia no exista en el archivo
            {
                nuevoLibro = cargaUnNuevoLibro(tituloNuevoLibro, archivoLibros);
                fwrite(&nuevoLibro, sizeof(stLibro), 1, archi);
                fclose(archi); //Debo cerrar aquí el archivo para que se guarden los cambios. Sino, si el usuario quiere agregar otro libro, no podrá actualizarse el id.
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
        while (option != 27);

        fclose(archi); //Vuelvo a cerrar el archivo porque si el libro ya existia dejaba el archivo abierto
    }
    else
    {
        printf("No se pudo abrir el archivo.");
    }
}

int archivoToArrayLibros(char nombreArchivo[], stLibro libros[], int v, int dim)
{

    int cant = cantElementosArchivo(nombreArchivo, sizeof(stLibro));
    int total = cant + v;

    FILE * archi = fopen(nombreArchivo, "rb");

    if(archi && total <= dim)
    {
        while(fread(&libros[v], sizeof(stLibro), 1, archi) > 0)
        {
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
    return id;
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
    int i = v;

    if(archi)
    {
        while( i < dim && fread(&aux, sizeof(stLibro), 1, archi) > 0)
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

