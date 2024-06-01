#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h>



typedef struct
{

    int id; //Debe ser autoincremental.s

    char nombre[30];

    char email[30];

    int edad;

    int rol; // 2: adm;  1: usuario. La clave para ser anmi es 4815.

    char pass[30];

    char genero; //f, m, x.

    char fechaNacimiento[30];

}usuario;

int crearUsuario(char archivo[]);
void verUsuarios (char archivo[]);
int comprobarEmail(char email[]);
int archivoToArregloUsuario(char nombrearchivo[], usuario a[], int v, int dim);
void imprimirArrayUsuario(usuario a[], int v);
int buscarUsuario(usuario a[], int v, char email[], char pass[]);
int existeEmail(char email[]);
int tienePuntoCom(char email[]);
void mostrarUsuario(usuario u);  ///Función para controlar los datos almacenados en SESSION
