#include "estructuraUsuario.h"
#include "estructuraLibros.h"
#include "estructuraComentarios.h"

int cantElementosArchivo(char nombreArchivo[], int tamanio);
int buscaPosicionEnArregloEntero(int arreglo[], int val, int entero);
void intercambioVariablesInt(int *a, int *b);
int posRandomArray(int validos);
void muestraLibrosFavoritosDeUsuario(int idUsuario, char archivoUsuarios[], char archivoLibros[]);
void muestraLibroComentAleatorio(char archivoLibros[],char archivoComentarios[]);
void subMenuAgregaFavsDeUser(int posUsuario, usuario arregloUsuarios[], char archivoLibros[]);
void subMenuEliminaFavsDeUser(int posUsuario, usuario arregloUsuarios[], char archivoLibros[]);
void subMenuEliminaLibrosAdmin(char archivoLibros[], char archivoUsuarios[], char archivoComentarios[]);
void subMenuEliminaLibroDeFavs(int idLibroEliminado,char archivoUsuarios[]);
void subMenuEliminaComentariosIdLibro(int idLibroEliminado, char archivoComentarios[]);
void subMenuDeshabHabLibrosAdmin(char archivoLibros[], char archivoUsuarios[], char archivoComentarios[]);
void subMenuDeshabHabComentarios(int idLibro, char archivoComentarios[], int accion);
void imprimirUnComentarioAdmin(stComentario c, stLibro arregloLibros[], int valLibros, usuario arregloUsuarios[], int valUsuarios);
void imprimirUnComentarioUsuario(stComentario c, stLibro arregloLibros[], int valLibros, usuario arregloUsuarios[], int valUsuarios);
void imprimirArregloComentariosAdmin(stComentario arregloComents[], int valComents, stLibro arregloLibros[], int valLibros, usuario arregloUsuarios[], int valUsuarios);
void imprimirArregloComentariosUser(stComentario arregloComents[], int valComents, stLibro arregloLibros[], int valLibros, usuario arregloUsuarios[], int valUsuarios);
