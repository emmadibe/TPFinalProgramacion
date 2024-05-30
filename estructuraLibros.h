#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>


typedef struct{

    int idLibro; /// único, autoincremental
    char titulo[100];
    char editorial[50];
    char autor[50];
    char categoria[50];
    float valoracion;
    int eliminado; /// 0 si está activo - 1 si está eliminado

}stLibro;


stLibro cargaUnNuevoLibro();
void eligeCategoriaLibro(char categoria[]);
int cargaArregloLibros(stLibro libros[], int vLibros, int dimLibros);

void muestraUnLibroAdmin(stLibro libro);
void muestraArregloLibrosAdmin(stLibro arregloLibros[], int vLibros);
void cargaLibroArchivo(char nombreArchivo[]);




