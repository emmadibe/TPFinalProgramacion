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
int buscarPosComentarioIdLibro(int idLibro, stComentario c[], int v);

///agregadas 21 de junio, NO APARECEN EN EL MAIN POR SI QUERES HACER MODIFICACIONES:
void arrayToArchivoComentarios(stComentario c[], int v, char archivoComentarios[]);
int buscaComentarioPosicionPorIdComent(stComentario c[], int v, int idAux);


stComentario cargaUnComentario(int idUsuario, int idLibro, char archivoComentarios[]);
void intercambioComentariosArreglo(stComentario *a, stComentario *b);
int archivoToArrayComenSegunIdLibro(char archivoComentarios[], stComentario arregloComent[], int v, int dim, int idLibro);
int archivoToArrayComenSegunIdUsuario(char archivoComentarios[], stComentario arregloComent[], int v, int dim, int idUsuario);
int buscaMayorIDComentario(char archivoComentario[]);
int cantElementosArchivo(char nombreArchivo[], int tamanioEstructura);
int usuarioYaComentoLibro(int idLibro, int idUsuario, char archivoComentarios[]);
int sumaPuntuacionesRecursivoCondicion(stComentario arregloComent[],int val, int i, int idLibro);
int cantPuntuacionesRecursivoCondicion(stComentario arregloComent[],int val, int i, int idLibro);
float promedioPuntuacion(stComentario arregloComent[], int val, int idLibro);
void subMenuModificaComentario(stComentario c[], int pos);

