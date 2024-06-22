#include "estructuraComentarios.h"
#include "funcionesGenerales.h"
#include <stddef.h>



stComentario cargarComentarioNuevo(int idUsuario, int idLibro, char archivoComentarios[])
{

    stComentario comentario;
    char descripcion[500];
    char titulo[20];
    comentario.idComentario = cantElementosArchivo(archivoComentarios, sizeof(stComentario));
    int puntaje = 0;

    /////////////////////////////////////////////OBTENGO LA FECHA ACTUAL :
    time_t tiempo_actual;
    struct tm* tiempo_local;
    char fecha_actual[80];

    // Obtener el tiempo actual
    tiempo_actual = time(NULL);
    tiempo_local = localtime(&tiempo_actual);

    // Formatear la fecha actual como una cadena
    strftime(fecha_actual, 80, "%d/%m/%Y", tiempo_local);

    ///////////////////////////////////////FIN DE OBTENER LA FECHA ACTUAL

    FILE * archi = fopen(archivoComentarios, "ab");

    if(archi)
    {

        comentario.idUsuario = idUsuario;
        comentario.idLibro = idLibro;
        comentario.idComentario = cantElementosArchivo(archivoComentarios, sizeof(stComentario));

        printf("Titulo del comentario: \n");
        fflush(stdin);
        gets(titulo);

        strcpy(comentario.tituloComentario, titulo);
        printf("Comente, en un maximo de 500 chars, que le parecio el libro.\n");
        fflush(stdin);
        gets(descripcion);

        strcpy(comentario.descripcion, descripcion);

        do{

            printf("Ponele un puntaje del 0 al 5 al libro.\n");

            scanf("%d", &puntaje);

        }while(puntaje < 0 || puntaje > 5);

            comentario.puntaje = puntaje;

        strcpy(comentario.fechaComentario, fecha_actual); //Copio el contenido de fecha_actual en el campo fechaComentario.

        fwrite(&comentario, sizeof(stComentario), 1, archi);
        fclose(archi); //Debo cerrar el archivo para guardar los cambios

    }

    return comentario;
}

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

void imprimirUnComentarioDelArrayComentario(stComentario c[], int posicion, char tituloLibro[50])
{

    puts("-------------------------------------\n");

    printf("Comentario del libro %s\n", tituloLibro);

    printf("Titulo del comentario: %s\n", c[posicion].tituloComentario);
    printf("Descripcion: %s\n", c[posicion].descripcion);
    printf ("Puntaje: %d\n", c[posicion].puntaje);
    printf ("Fecha: %s\n", c[posicion].fechaComentario);
    ///como hacer para que aparezca el usuario que realizo el comentario?
    ///esta bien poner lo siguiente?
    printf ("Usuario %d\n", c[posicion].idUsuario);

    puts("-------------------------------------\n");


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

int buscaComentarioPosicionIdEnArreglo(stComentario c[], int v, int idAux)
{

    int pos = -1;
    int i = 0;

    while(i < v && pos == -1 )
    {
        if(c[i].idComentario == idAux)
        {
            pos = i;
        }
        i++;
    }


    return pos;
}

void eliminarComentario(stComentario c[] , int pos, int idAux)
{
    strcpy (c[pos].descripcion, " ");
    strcpy (c[pos].puntaje, " ");
    strcpy (c[pos].tituloComentario, " ");
    strcpy (c[pos].fechaComentario, " ");
    ///int eliminado; /// 0 si está activo - 1 si está eliminado

}

