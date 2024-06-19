#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>


typedef struct{

    int idLibro; /// �nico, autoincremental
    char titulo[100];
    char editorial[50];
    char autor[50];
    char categoria[50];
    float valoracion;
    int eliminado; /// 0 si est� activo - 1 si est� eliminado

}stLibro;


stLibro cargaUnNuevoLibro(char tituloNuevoLibro[], char archivoLibros[]);
void eligeCategoriaLibro(char categoria[]);
int existeLibro(char nombreLibro[], char archivoLibros[]);
void cargaLibrosAlArchivo(char archivoLibros[]);


void muestraUnLibroAdmin(stLibro libro);
void muestraArchivoLibrosAdmins(char archivoLibros[]);
void muestraArregloLibrosAdmin(stLibro arregloLibros[], int vLibros);


int archivoToArrayLibros(char nombreArchivo[], stLibro libros[], int v, int dim);
int archivoToArrayLibrosSegunCategoria(char archivoLibros[], stLibro arregloLibros[], int v, int dim, char categoria[]);
int archivoToArrayLibrosSegunAutor(char archivoLibros[], stLibro arregloLibros[], int v, int dim, char autorBuscado[]);


int buscarIdLibroConTitulo(char tituloLibro[], char archivoLibros[]);
stLibro buscarLibroPorId(int idLibroBuscado, stLibro arregloLibros[], int v);
int buscaLibroConTituloEnArreglo(stLibro arregloLibros[], int val);

