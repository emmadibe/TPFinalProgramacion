#include "estructuraComentarios.h"


void archivoToArrayComentario(char nombreArchivo[], stComentario c[], int  *v, int d)
{
    int cant = cantElementosArchivo(nombreArchivo, sizeof(stComentario));
    int total = cant + *v;

    FILE *archi = fopen(nombreArchivo, "rb");

    if(archi && total <= d)
    {
        while(fread(&c[*v], sizeof(stComentario), 1, archi) > 0)
        {
            *v = *v + 1;
        }
        fclose(archi);
    }
}

int buscarComentarioIdLibro(int idLibro, stComentario c[], int v)
{
    int i = 0;
    int posicion = -1;
    char flag = 't';

    while(i < v && flag == 't')
    {
        if(c[i].idLibro == idLibro)
        {
            posicion = i;
            flag = 'f';
        }
        i++;
    }
    return posicion;
}

void arrayToArchivoComentarios(stComentario c[], int v, char archivoComentarios[])
{
    FILE * archi = fopen(archivoComentarios,"wb");

    if(archi)
    {
        fwrite(c,sizeof(stComentario),v,archi);
        fclose(archi);
    }
}

///modificar y eliminar comentarios:


void ModificarComentarios(stComentario c[],int v)
{
    int idAux;
    int option2;
    int pos = -1;

    printf("Que comentario queres modificar?\n");
    scanf("%d",&idAux);

    ///o sino mostrar libros y seleccionar pero mayor costo?

    pos = buscaComentarioPosicionIdEnArreglo(c,v,idAux);

    if(pos > -1)
    {
        do
        {
            printf("EDITAR COMENTARIO (marque opcion)\n");
            printf("1. Modificar Titulo del comentario\n");
            printf("2. Modificar Descripcion\n");
            printf("3. Modificar Puntaje");
            printf("4. Eliminar comentario");
            printf("5. Salir de EDITAR COMENTARIO");


            scanf("%d",&option2);

            switch(option2)
            {

            case 1:
                printf("Ingrese el nuevo titulo\n");
                fflush(stdin);
                gets(c[pos].tituloComentario);
                printf("Se modifico correctamente \n");
                break;

            case 2:
                printf("Ingrese la nueva descripcion \n");
                fflush(stdin);
                gets(c[pos].descripcion);
                printf("Se modifico correctamente\n");
                break;

            case 3:
                printf("Ingrese nuevo puntaje \n");
                scanf("%d", &c[pos].puntaje);
                printf("Se modifico correctamente\n");
                break;

            case 4:
                eliminarComentario(c,pos,idAux);
                printf("El comentario se ha eliminado correctamente\n");
                break;

            }

        }
        while(option2 != 5);

    }
    else
    {

        printf("\n No existe comentario con ese id");
    }
}

int buscaComentarioPosicionIdEnArreglo(stComentario c[], int v, int idBuscado)
{
    int pos = -1;
    int i = 0;

    while(i < v && pos == -1 )
    {
        if(c[i].idComentario == idBuscado)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}

void eliminarComentario(stComentario c[], int pos, int idAux)
{
    strcpy (c[pos].descripcion, " ");
    strcpy (c[pos].puntaje, " ");
    strcpy (c[pos].tituloComentario, " ");
    strcpy (c[pos].fechaComentario, " ");
    ///int eliminado; /// 0 si está activo - 1 si está eliminado

}

stComentario cargaUnComentario(int idUsuario, int idLibro, char archivoComentarios[])
{
    stComentario nuevoComentario;
    int puntaje = -1;

    //OBTENGO LA FECHA ACTUAL :
    time_t tiempo_actual;
    struct tm* tiempo_local;
    char fecha_actual[80];

    // Obtener el tiempo actual
    tiempo_actual = time(NULL);
    tiempo_local = localtime(&tiempo_actual);

    // Formatear la fecha actual como una cadena
    strftime(fecha_actual, 80, "%d/%m/%Y", tiempo_local);

    nuevoComentario.idUsuario = idUsuario;
    nuevoComentario.idLibro = idLibro;
    nuevoComentario.idComentario = buscaMayorIDComentario(archivoComentarios) + 1;

    printf("Titulo del comentario: \n");
    fflush(stdin);
    gets(nuevoComentario.tituloComentario);

    printf("Comente, en un maximo de 500 caracteres, que le parecio el libro: \n");
    fflush(stdin);
    gets(nuevoComentario.descripcion);

    do
    {

        printf("Ponele un puntaje del 0 al 5 al libro.\n");

        scanf("%d", &puntaje);

    }
    while(puntaje < 0 || puntaje > 5);

    nuevoComentario.puntaje = puntaje;

    strcpy(nuevoComentario.fechaComentario, fecha_actual);

    return nuevoComentario;
}

int buscaMayorIDComentario(char archivoComentario[])
{
    stComentario arregloComentarios[500];
    int val = 0;
    int mayorId = -1;

    archivoToArrayComentario(archivoComentario,arregloComentarios,&val,500);

    for(int i=0; i<val; i++)
    {
        if(arregloComentarios[i].idComentario > mayorId)
        {
            mayorId = arregloComentarios[i].idComentario;
        }
    }

    return mayorId;
}

void cargaComentariosAlArchivo(int idUsuario, int idLibro, char archivoComentarios[])
{
    stComentario comentario;

    FILE *archi = fopen(archivoComentarios, "ab");

    if(archi)
    {
        comentario = cargaUnComentario(idUsuario,idLibro,archivoComentarios);
        fwrite(&comentario, sizeof(stComentario), 1, archi);
        fclose(archi); //Debo cerrar el archivo para guardar los cambios

    }
}



void intercambioComentariosArreglo(stComentario *a, stComentario *b)
{
    stComentario comenAux = *a;

    *a = *b;
    *b = comenAux;
}


/*
int archivoToArrayComenSegunIdLibro(char archivoComentarios[], stComentario arregloComent[], int v, int dim, int idLibro)
{
    stComentario aux;
    FILE * archi = fopen(archivoComentarios, "rb");
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
}*/
