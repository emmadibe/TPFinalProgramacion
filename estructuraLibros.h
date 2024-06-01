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


stLibro cargaUnNuevoLibro();
void eligeCategoriaLibro(char categoria[]);
int cargaArregloLibros(stLibro libros[], int vLibros, int dimLibros);

void muestraUnLibroAdmin(stLibro libro);
void muestraArregloLibrosAdmin(stLibro arregloLibros[], int vLibros);
void cargaLibroArchivo(char nombreArchivo[]);
int archivoToArrayLibros(char nombreArchivo[], stLibro l[], int v, int dim);
void imprimirArrayLibros(stLibro l[], int v);
int cantElementosArchivoLibroAdm(char nombreArchivo[]);
int buscarIdibro(char nombreLibro[]);
stLibro buscarLibroPorId(int idLibro, stLibro a[], int v);



