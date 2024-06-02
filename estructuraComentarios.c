#include "estructuraComentarios.h"
#include "funcionesGenerales.h"
#include <stddef.h>
stComentario cargarComentarioNuevo(int idUsuario, int idLibro)
{

    stComentario comentario;
    char descripcion[500];
    char titulo[20];
    comentario.idComentario = cantElementosArchivo("listaComentarios.bid", sizeof(stComentario));
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

    FILE * archi = fopen("listaComentarios.bid", "ab");

    if(archi)
    {

        comentario.idUsuario = idUsuario;
        comentario.idLibro = idLibro;
        comentario.idComentario = cantElementosArchivo("listaComentarios.bid", sizeof(stComentario));

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

void archivoToArrayComentario(char nombreArchivo[])
{

    FILE *archi = fopen(nombreArchivo, "rb");

    if(archi)
    {

        
    }

}