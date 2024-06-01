#include "estructuraLibros.h"
#include "funcionesGenerales.h"


stLibro cargaUnNuevoLibro(char tituloNuevoLibro[])
{
    stLibro libro;
    char aux[100];
    float valoracion;
    char categoria[50];

    libro.idLibro = cantElementosArchivoLibro("listaLibros.bid");

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

    char op1[] = "Ciencia Ficcion";
    char op2[] = "Misterio y suspenso";
    char op3[] = "Policial";
    char op4[] = "Romance";
    char op5[] = "Juvenil";
    char op6[] = "Infantil";
    char op7[] = "Cocina y gastronomia";
    char op8[] = "Academico";
    char op9[] = "Ciencia y tecnologia";
    char op10[] = "Salud y bienestar";

    printf("\n 1-  %s", op1);
    printf("\n 2-  %s", op2);
    printf("\n 3-  %s", op3);
    printf("\n 4-  %s", op4);
    printf("\n 5-  %s", op5);
    printf("\n 6-  %s", op6);
    printf("\n 7-  %s", op7);
    printf("\n 8-  %s", op8);
    printf("\n 9-  %s", op9);
    printf("\n 10-  %s", op10);

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
    case 8:
        strcpy(categoria, op8);
        break;
    case 9:
        strcpy(categoria, op9);
        break;
    case 10:
        strcpy(categoria, op10);
        break;
    }
}

/*
int cargaArregloLibros(stLibro libros[], int vLibros, int dimLibros)
{
    char control = 's';
    stLibro nuevoLibro;
    while(vLibros < dimLibros && control != 27)
    {
        libros[vLibros] = cargaUnNuevoLibro(nuevoLibro);
        vLibros++;
        //printf("Libros cargados: %d", vAlumnos);  ///Control funcion de carga
        printf("Desea agregar otro libro? Presiones ESC para terminar\n");
        fflush(stdin);
        control = getch();
        system("cls");
    }
    return vLibros;
}
*/

void muestraUnLibroAdmin(stLibro libro)
{
    printf("\n-----------------------------------------------\n");
    printf("\nTitulo: %s", libro.titulo);
    printf("\n-----------------------------------------------\n");
    printf("\nIdLibro ..... %d", libro.idLibro);
    printf("\nAutor ....... %s", libro.autor);
    printf("\nEditorial ... %s", libro.editorial);
    printf("\nCategoria ... %s", libro.categoria);
    printf("\nValoracion .. %.2f", libro.valoracion);
    printf("\n-----------------------------------------------\n");
}

void muestraArregloLibrosAdmin(stLibro arregloLibros[], int vLibros)
{
    int i = 0;
    printf("Libros cargados: \n");
    while(i < vLibros)
    {
        muestraUnLibroAdmin(arregloLibros[i]);
        i++;
    }
    printf("\n");
}

void cargaLibroArchivo(char nombreArchivo[])
{
    stLibro nuevoLibro;
    char option = 0;
    char tituloNuevoLibro[100];

    FILE *archi = fopen(nombreArchivo, "ab");

    if(archi != NULL)
    {
        do{
            printf("\nIngrese el titulo del libro: ");
            fflush(stdin);
            gets(tituloNuevoLibro);

            if(yaExisteLibro(tituloNuevoLibro)== 0)  //Valida que el libro nuevo todavia no exista en el archivo
            {
                nuevoLibro = cargaUnNuevoLibro(tituloNuevoLibro);
                fwrite(&nuevoLibro, sizeof(stLibro), 1, archi);  //fwrite devuelve la cantidad de elemetos que fueron escritos
                fclose(archi); //Debo cerrar aquí el archivo para que se guarden los cambios. Sino, si el usuario quiere agregar otro libro, no podrá actualizarse el id.
            }
            else if(yaExisteLibro(tituloNuevoLibro)== 1)  //Si el titulo ya existe en el archivo, suspende la carga
            {
                puts("El libro ya existe en nustros archivos!");
            }

            printf("�Desea cargar otro libro? Presiones ESC para terminar\n");
            fflush(stdin);
            option = getch();
            system("cls");

        }while (option != 27);

    }
    else
    {
        printf("No se pudo abrir el archivo.");
    }
}

int buscarIdibro(char nombreLibro[])
{
    stLibro arrayLibro[50];
    int validos = 0, i = 0;
    char flag = 't';
    int id = -1; //Por si  no lo encuentra, debe retornar un valor no validos como id. El id no puede ser negativo.

    validos = archivoToArrayLibros("listaLibros.bid", arrayLibro, validos, 50);

    while(i < validos && flag == 't')
    {
        if(strcmpi(nombreLibro, arrayLibro[i].titulo) == 0)
        {
            flag = 'f';
            id = arrayLibro[i].idLibro;
        }
        i++;
    }
    return id;
}

stLibro buscarLibroPorId(int idLibro, stLibro a[], int v)
{
    int i = 0;
    stLibro librito;
    char flag = 't';
    while(i < v && flag == 't')
    {
        if(a[i].idLibro == idLibro)
        {
            librito = a[i];
            flag = 'f';
        }
        i++;
    }
    return librito;
}

void imprimirArrayLibrosAdm(stLibro l[], int v)
{
    int i = 0;

    while(i < v)
    {
        printf("----------------------\n");
        printf("ID: %d\n", l[i].idLibro);
        printf("Titulo: %s\n", l[i].titulo);
        printf("Autor: %s\n", l[i].autor);
        printf("Editorial: %s\n", l[i].editorial);
        printf("Categoria: %s\n", l[i].categoria);
        printf("Valoracion: %.2f\n", l[i].valoracion);
        printf("--------------------------\n");

        i++;
    }
}

int archivoToArrayLibros(char nombreArchivo[], stLibro l[], int v, int dim)
{

    int cant = cantElementosArchivo(nombreArchivo, sizeof(stLibro));
    int total = cant + v;

    FILE * archi = fopen(nombreArchivo, "rb");

    if(archi && total <= dim)
    {
        while(fread(&l[v], sizeof(stLibro), 1, archi) > 0)
        {
            v++;
        }
        fclose(archi);
    }
    return v;
}

int cantElementosArchivoLibro(char nombreArchivo[])
{
    FILE * archi = fopen(nombreArchivo,"rb"); //Abro el archivo que paso por parámetro en modo lectura binaria (rb).
    int cant = 0;

    if(archi) //Compruebo que el archivo se haya abierto correctamente. Acordate que, en modo rb, si no existe el archivo retorna NULL.
    {
        fseek(archi, 0, SEEK_END); //Desplazo el indicador de posesión al final del archivo (EOF).
        long int tamano = ftell(archi);

        cant = tamano/sizeof(stLibro);
        /*En esta línea de código obtengo la cantidad de elementos que tengo en el archivo. //La función ftell() me retorna la posición actual del indicador de posisión MEDIDO EN BYTES.
        Al estar en el final del archivo, me va a terminar retornando la cantidad de bytes que ocupa mi archivo. Si eso lo divido por el tamanio de la estructura, obtengo la cantidad de elementos.
        Obviamente, el tamanio de la estructura la obtendré en el main usando la función sizeof() y pasándole como parámetro el identificador de la estructura. Por ejemplo: sizeof(usuario).*/

        fclose(archi);//Cierro el archivo.
    }
    return cant;
}

int yaExisteLibro(char nombreLibro[])
{
    stLibro arrayLibro[150];
    int validos = 0, i = 0;
    int flag = 0;

    validos = archivoToArrayLibros("listaLibros.bid", arrayLibro, validos, 150);

    while(i < validos && flag == 0)
    {
        if(strcmpi(nombreLibro, arrayLibro[i].titulo) == 0)
        {
            flag = 1;
        }
        i++;
    }
    return flag;
}




