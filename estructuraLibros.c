#include "estructuraLibros.h"
#include "funcionesGenerales.h"

stLibro cargaUnNuevoLibro()
{
    stLibro libro;
    char aux[100];

    char categoria[50];

    libro.idLibro = cantElementosArchivo("libro.bid", sizeof(libro)) + 1;

    printf("\nIngrese el titulo del libro: ");
    fflush(stdin);
    gets(aux);
    //Hacer función que chequee que no esté repetido el titulo
    strcpy(libro.titulo, aux);

    printf("\nIngrese la editorial del libro: ");
    fflush(stdin);
    gets(aux);
    strcpy(libro.editorial, aux);

    printf("\nIngrese el autor del libro: ");
    fflush(stdin);
    gets(aux);
    strcpy(libro.autor, aux);

    printf("\nSeleccione la categoría del libro: ");
    eligeCategoriaLibro(categoria);
    strcpy(libro.categoria, categoria);

    libro.eliminado = 0;

    printf("TU LIBRO ES: \n");

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

int cargaArregloLibros(stLibro libros[], int vLibros, int dimLibros)
{
    char control = 's';
    stLibro nuevoLibro;
    while(vLibros < dimLibros && control != 27)
    {
        libros[vLibros] = cargaUnNuevoLibro(nuevoLibro);
        vLibros++;
        //printf("Libros cargados: %d", vAlumnos);  ///Control función de carga
        printf("Desea agregar otro libro? Presiones ESC para terminar\n");
        fflush(stdin);
        control = getch();
        system("cls");
    }
    return vLibros;
}

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

    FILE *archi = fopen(nombreArchivo, "ab");

    if(archi != NULL)
    {
        do{
            nuevoLibro = cargaUnNuevoLibro();
            fwrite(&nuevoLibro, sizeof(stLibro), 1, archi);  //fwrite devuelve la cantidad de elemetos que fueron escritos

            printf("¿Desea cargar otro libro? Presiones ESC para terminar\n");
            fflush(stdin);
            option = getch();
            system("cls");

        }while (option != 27);

        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo.");
    }
}

int archivoToArregloLibro(char nombrearchivo[], stLibro a[], int val, int dim)
{
    int cant = cantElementosArchivo("libro.bid", sizeof(stLibro));
    int total = val + cant;

    FILE * archi = fopen(nombrearchivo,"rb");

    if( archi && total <= dim)
    {
        while(fread(&a[val],sizeof(stLibro),1,archi) > 0)
        {
            val++;
        }
        fclose(archi);
    }
    return val;
}












