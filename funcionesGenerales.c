#include <stdlib.h>
#include <time.h> //Librería oficial de C que tiene la función random.
#include <string.h>
#include <stdio.h> 

//Contar cantidad de elemento en el archivo
//La función cantElementosArchivo cuenta la cantidad de elementos en un archivo binario.

int cantElementosArchivo(char nombreArchivo[], size_t tamanioEstructura) 
{

    FILE * archi = fopen(nombreArchivo,"rb"); //Abro el archivo que paso por parámetro en modo lectura binaria (rb).
    int cant = 0; 

    if(archi) //Compruebo que el archivo se haya abierto correctamente. Acordate que, en modo rb, si no existe el archivo retorna NULL. 
    {
        fseek(archi, 0, SEEK_END); //Desplazo el indicador de posesión al final del archivo (EOF).
        cant = ftell(archi)/tamanioEstructura; //En esta línea de código obtengo la cantidad de elementos que tengo en el archivo. La función ftell() me retorna la posición actual del indicador de posisión MEDIDO EN BYTES. Al estar en el final del archivo, me va a terminar retornando la cantidad de bytes que ocupa mi archivo. Si eso lo divido por el tamanio de la estructura, obtengo la cantidad de elementos.
        //Obviamente, el tamanio de la estructura la obtendré en el main usando la función sizeof() y pasándole como parámetro el identificador de la estructura. Por ejemplo: sizeof(usuario).
        fclose(archi);//Cierro el archivo. 
    }

    

    return cant;

}

