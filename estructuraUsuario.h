#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include "estructuraDomicilio.h"

typedef struct
{

    int id; //Debe ser autoincremental.s

    char nombre[30];

    char email[100];

    int edad;

    int rol; // 2: adm;  1: usuario. La clave para ser anmi es 4815.

    char pass[30];

    char genero; //f, m, x.

    char fechaNacimiento[30];

    char dni[10];

    stDomicilio domicilio;

    char username[20];  /// agrege las variables que le faltaban a la estructura (18-6-24)

    int librosFavoritos[50];
    int validosFavoritos;

    int eliminado; // 0 si esta activo, -1 si esta eliminado

}usuario;

int crearUsuario(char archivo[]);
void verUsuarios (char archivo[]);
int comprobarEmail(char email[]);
int archivoToArregloUsuario(char nombrearchivo[], usuario a[], int v, int dim);
void imprimirArrayUsuario(usuario a[], int v);
int buscarUsuario(usuario a[], int v, char email[], char pass[]);
int existeEmail(char email[]);
int tienePuntoCom(char email[]);
void mostrarUnUsuario(usuario u);
usuario editarUsuario(char nombreArchivo[], int idUsuario);
void arrayToArchivo(char nombreArchivo[], usuario u[], int v);
int buscarPosUsuarioPorId(int idUsuarioBuscado, usuario arregloUsuarios[], int v);
void eliminarUsuario(char nombreArchivo[], usuario admin);
int enroqueArray(usuario u[], int v, int posicion);
void imprimirUnRegistro(usuario u);
void inhabilitarUsuario(char nombreArchivo[], int id);
int corroborarPass(char pass[]);
int buscarUltimoId(char nombreArchivo[]);
usuario buscarUnUsuarioPorId(int idUsuarioBuscado, usuario arregloUsuarios[], int v);
int buscarMayorId(char nombreArchivo[]);
int buscarUsuarioPorId(int idUsuario, usuario u[], int v);
int cantElementosArchivo(char nombreArchivo[], int tamanio);
