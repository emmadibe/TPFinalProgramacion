#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h>

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

stComentario cargarComentarioNuevo(int idUsuario, int idLibro);
void archivoToArrayComentario(char nombreArchivo[], stComentario c[], int * v, int d);
int buscarComentario(int idLibro, stComentario c[], int v);
void imprimirUnComentarioDelArrayComentario(stComentario c[], int posicion, char tituloLibro[50]);
