#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include "estructuraUsuario.h"
#include "estructuraComentarios.h"
#include "funcionesGenerales.h"

typedef struct{

    int idLibro; /// unico, autoincremental
    char titulo[100];
    char editorial[50];
    char autor[50];
    char categoria[50];
    float valoracion;
    int eliminado; /// 0 si esta activo - 1 si esta eliminado

}stLibro;


stLibro cargaUnNuevoLibro(char tituloNuevoLibro[], char archivoLibros[]);
void eligeCategoriaLibro(char categoria[]);
int existeLibro(char nombreLibro[], char archivoLibros[]);
void cargaLibrosAlArchivo(char archivoLibros[]);
int existeIdArreglo(int id, int arregloId[], int val);
int posRandomArray(int validos);

void muestraUnLibroAdmin(stLibro libro);
void muestraArchivoLibrosAdmins(char archivoLibros[]);
void muestraArregloLibrosAdmin(stLibro arregloLibros[], int vLibros);
void muestraLibrosFavoritosDeUsuario(int idUsuario, char archivoUsuarios[], char archivoLibros[]);
void mostrarLibroComentAleatorio(char archivoLibros[],char archivoComentarios[]);
void muestraArchivoLibrosUsuario(char archivoLibros[]);
void muestraArregloLibrosUsuario(stLibro arregloLibros[], int vLibros);

int archivoToArrayLibros(char nombreArchivo[], stLibro libros[], int v, int dim);
int archivoToArrayLibrosSegunCategoria(char archivoLibros[], stLibro arregloLibros[], int v, int dim, char categoria[]);
int archivoToArrayLibrosSegunAutor(char archivoLibros[], stLibro arregloLibros[], int v, int dim, char autorBuscado[]);
void arregloToArchivoLibros(stLibro arregloLibros[], int v, char archivoLibros[]);
void intercambioLibrosArreglo(stLibro *a, stLibro *b);
void intercambioComentariosArreglo(stComentario *a, stComentario *b);

int buscarIdLibroConTitulo(char tituloLibro[], char archivoLibros[]);
stLibro buscarLibroPorId(int idLibroBuscado, stLibro arregloLibros[], int v);
int buscaLibroConTituloEnArreglo(stLibro arregloLibros[], int val);
int buscaLibroPosicionEnArregloTitulo(stLibro arreglo[], int val, char titulo[]);

void subMenuModificaArregloDatosLibro(stLibro arrayLibros[], int posEnArreglo);
void modificaDatosLibro(stLibro arregloLibros[], int val);
void subMenuAgregaFavsDeUser(int posUsuario, usuario arregloUsuarios[], char archivoLibros[]);
void subMenuEliminaFavsDeUser(int posUsuario, usuario arregloUsuarios[], char archivoLibros[]);
void subMenuEliminaLibrosAdmin(char archivoLibros[], char archivoUsuarios[], char archivoComentarios[]);
void subMenuEliminaLibroDeFavs(int idLibroEliminado,char archivoUsuarios[]);
void subMenuEliminaComentariosIdLibro(int idLibroEliminado, char archivoComentarios[]);
void subMenuDeshabHabLibrosAdmin(char archivoLibros[], char archivoUsuarios[], char archivoComentarios[]);
void subMenuDeshabHabComentarios(int idLibro, char archivoComentarios[], int accion);
