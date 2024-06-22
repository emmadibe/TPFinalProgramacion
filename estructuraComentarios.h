#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h>
#include <stddef.h>


typedef struct {
    int idComentario;  /// único, autoincremental
    int idLibro;
    int idUsuario;
    char tituloComentario[100];
    char descripcion[500];
    int puntaje; /// de 0 a 5 "estrellas"
    char fechaComentario[20]; /// o se puede hacer con dia, mes, anio.
    int eliminado; /// 0 si está activo - 1 si está eliminado
}stComentario;

void archivoToArrayComentario(char nombreArchivo[], stComentario c[], int * v, int d);
int buscarComentarioIdLibro(int idLibro, stComentario c[], int v);

///agregadas 21 de junio, NO APARECEN EN EL MAIN POR SI QUERES HACER MODIFICACIONES:
void arrayToArchivoComentarios(stComentario c[], int v, char archivoComentarios[]);
void ModificarComentarios(stComentario c[],int v);
int buscaComentarioPosicionIdEnArreglo(stComentario c[], int v, int idAux);
void eliminarComentario(stComentario c[] , int pos, int idAux);


stComentario cargaUnComentario(int idUsuario, int idLibro, char archivoComentarios[]);
void cargaComentariosAlArchivo(int idUsuario, int idLibro, char archivoComentarios[]);
void intercambioComentariosArreglo(stComentario *a, stComentario *b);
