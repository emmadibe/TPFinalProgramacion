#include "estructuraUsuario.h"
#include "funcionesGenerales.h"

int crearUsuario(char archivo[])
{

    char pass2[30];

    int longCadena = 0;

    int compararCadenas = 0;

    int verificaEmail;

    usuario u; //Declaramos una variable de tipo usuario.

    FILE *archi; //Declaramos un puntero a la estructura FILE.

    archi = fopen(archivo, "ab");

    if(archi == NULL){

        return -1; //Retorno -1 si hubo un error al abrir/crear el archivo.

    } 

    u.id = cantElementosArchivo("usuario.bid", sizeof(usuario)) + 1;

    puts("----------------\n");

    do{

        printf("Ingrese nombre y apellido entre 6 y 30 caracteres: \n");
        fflush(stdin);
        gets(u.nombre);

        longCadena = strlen(u.nombre);

    }while(longCadena < 6 || longCadena > 30);

    do{

        printf("Ingrese una edad del 1 al 100: \n");
        scanf("%d", &u.edad);

    }while(u.edad < 1 || u.edad > 100 );

    do{

        printf("Ingrese su email: \n");
        fflush(stdin);
        gets(u.email);

        verificaEmail = comprobarEmail(u.email);

        printf("%d", verificaEmail);

        if(verificaEmail != 0){

            puts("UN EMAIL DEBE TENER UN ARROBA!\n");

        }

    }while(verificaEmail != 0);

    do{

        do{

            printf("Ingrese password: \n");
            gets(u.pass);
            longCadena = strlen(u.pass);

        }while(longCadena < 5); //obligo al usuario a ingresar ua contraseña de, como minimo, 5 caracteres.

        printf("Confirmar pass: \n");
        gets(pass2);

        compararCadenas = strcmp(u.pass, pass2);

    }while(compararCadenas != 0);

    do{

        printf("Inrgese su genero: f, m o x\n");
        u.genero = getch();

    }while(u.genero != 'f' && u.genero != 'm' && u.genero != 'x');

    do{

        printf("Si usted conoce la key para ser administrador, escribala; sino, presione 1.\n");
        scanf("%d", &u.rol);

        if(u.rol == 4815){

            u.rol = 2;

        }

    }while(u.rol != 2 && u.rol != 1);

    puts("-----------------------\n");

    fwrite(&u, sizeof(usuario), 1, archi);

    fclose(archi); //Cierro el archivo. Fundamental para que los datos escritos en el buffer se guarden en el archivo ubicado en memoria secundaria.

    return 0;

}

void verUsuarios (char archivo[])
{

    FILE *archi;
    usuario u;
    archi = fopen(archivo, "rb");
    int i = 0;
    if(archi != NULL){

        while(fread(&u, sizeof(usuario), 1, archi) > 0){

            printf("Registro N %d\n", i);
            puts("-----------\n");
            printf("ID: %d\n", u.id);
            printf("Nombre y apellido: %s\n", u.nombre);
            printf("Edad: %d\n", u.edad);
            printf("Genero: %c\n", u.genero);
            printf("Rol: %d\n", u.rol);
            puts("---------------\n");

        }

    }

}

int comprobarEmail(char email[])
{

    char caracter;

    int i = 0;

    int flag = 1;

    while(email[i] != '\0' && flag == 1){

        if (email[i] == 64){ //64 es el @ en ASCII.

            flag = 0;

        }

        i++;

    }

    return flag;

}


//ArchivoToArray.
//La función archivoToArregloUsuario tiene como objetivo leer los datos de un arhivo binario y almacenarlos en un array llamado a a partir de la posición v.
int archivoToArregloUsuario(char nombrearchivo[], usuario a[], int v, int dim)//Parámetros: nombre del archivo, un array de tipo usuario, válidos y la dimensión del array. 
{

    int cant = cantElementosArchivo(nombrearchivo, sizeof(usuario)); //Obtengo la cantidad de elementos que tiene mi archivo.
    int total = v + cant; //Calculo el total de elementos que tendrá mi array sumando válidos (elementos que ya tiene) más cant(que indica la cantidad de elementos que debe agregarsele).

    FILE * archi = fopen(nombrearchivo,"rb");

    if( archi && total <= dim) //Verifico, por un lado, que el archivo se haya abierto correctamente (si no existe, la función fopen en modo rb retorna NUll); por otro, que el total no supere a la dimensión del array. Si me paso de la dimensión se rompe todo.
    {
        while(fread(&a[v],sizeof(usuario),1,archi) > 0) //En esta línea de código paso los datos del archivo al array. Lo que hace es leer el archivo y almacenar cada uno de sus elementos en el array llamado a desde la posición v (o sea, desde válidos).
        {
            v++; //Como siempre, debo incrementar válidos en uno. Pues, con cada elemento nuevo en el array debo aumentar válidos en uno
        }
        fclose(archi); //Cierro el archivo porque terminé de trabajar.
    }

    return v; //Retorno el nuevo valor de válidos del array.

}

//Imprimo array de usuarios:
void imprimirArrayUsuario(usuario a[], int v)
{

    int i = 0;

    while(i < v){

        puts("----------------------------\n");

        printf("Registro N %d\n", i);

        printf("ID: %d\n", a[i].id);
        printf("Nombre: %s\n", a[i].nombre);
        printf("Email: %s\n", a[i].email);
        printf("Edad: %d\n", a[i].edad);
        printf("Rol: %d\n", a[i].rol);
        printf("Contrasenia: %s\n", a[i].pass);
        printf("Genero: %c\n", a[i].genero);

        puts("----------------------------\n");

        i++;

    }

}

int buscarUsuario(usuario a[], int v, char email[], char pass[])
{

    int i = 0;

    int control = -2;

    while(i < v){

        if(strcmpi(a[i].email, email) == 0){

            if(strcmpi(a[i].pass, pass) == 0){

                control = i; //Retorno la posición del usuario. Así, me será muy sencillo acceder a todos sus datos.

            }else{

                control = -1;

            }

        }

        i++;

    }

    return control;

}