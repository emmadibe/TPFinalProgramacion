#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h>
#include <stddef.h>
//Contar cantidad de elemento en el archivo
//La función cantElementosArchivo cuenta la cantidad de elementos en un archivo binario.

int cantElementosArchivo(char nombreArchivo[], int tamanioEstructura)
{

    FILE * archi = fopen(nombreArchivo,"rb"); //Abro el archivo que paso por parámetro en modo lectura binaria (rb).
    int cant = 0;

    if(archi) //Compruebo que el archivo se haya abierto correctamente.
    {
        fseek(archi, 0, SEEK_END); //Desplazo el indicador de posesión al final del archivo (EOF).
        cant = ftell(archi)/tamanioEstructura; //En esta línea de código obtengo la cantidad de elementos que tengo en el archivo.
        fclose(archi); //Cierro el archivo.
    }
    return cant;
}

int buscaPosicionEnArregloEntero(int arreglo[], int val, int entero)
{
    int pos = -1;
    int i = 0;

    while(i < val && pos == -1 )
    {
        if(entero == arreglo[i])
        {
            pos = i;
        }
        i++;
    }
    return pos;
}

void intercambioVariablesInt(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

