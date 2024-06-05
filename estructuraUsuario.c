#include "estructuraUsuario.h"
#include "funcionesGenerales.h"

void editarusuario(char nombreArchivo[]) //La idea es pasar todo el archivo, todos los usuarios, a un array y editar al usuario DESDE el array, Luego, sobreescribo el archivo con los datos del array. Para ello, debo abrir el archivo en modo wb.
{
    int verificaEmail;
    int compararCadenas;
    char pass2[55];
    int longCadena;
    int v = 0, d = 222, posicion = 0, edad = 0;
    char sexo;

    char email[55];

    char pass[55];

    usuario u[222];

    v = archivoToArregloUsuario(nombreArchivo, u, v, d);

    printf("Debes ingresar tus datos actuales, primero, para poder editar tu perfil:\n");

    printf("Email: \n");
    fflush(stdin);
    gets(email);

    printf("password: \n");
    fflush(stdin);
    gets(pass);

    posicion = buscarUsuario(u, v, email, pass); //Ya tengo la posición del usuario en el array.

    do
    {

        printf("\nIngrese nombre y apellido entre 6 y 30 caracteres: \n");
        fflush(stdin);
        gets(u[posicion].nombre);

        longCadena = strlen(u[posicion].nombre);

    }while(longCadena < 6 || longCadena > 30);

        do
    {

        printf("\nIngrese su email: \n");
        fflush(stdin);
        gets(u[posicion].email);

        verificaEmail = comprobarEmail(u[posicion].email);

        //printf("%d", verificaEmail);  //Control de funcion

        if(verificaEmail == 1)
        {

            puts("UN EMAIL DEBE TENER UN ARROBA Y TERMINAR EN .COM!\n");

        }
        else if(verificaEmail == -9)
        {

            puts("EL EMAIL YA EXISTEª ELIJA OTRO.\n");

        }

    }while(verificaEmail != 0);


    do
    {

        do
        {

            printf("\nIngrese password: \n");
            gets(u[posicion].pass);
            longCadena = strlen(u[posicion].pass);

        }
        while(longCadena < 5);  //obligo al usuario a ingresar ua contraseña de, como minimo, 5 caracteres.

        printf("\nConfirmar pass: \n");
        gets(pass2);

        compararCadenas = strcmp(u[posicion].pass, pass2);

    }while(compararCadenas != 0);

        do
    {

        printf("\nIngrese una edad del 1 al 100: \n");
        scanf("%d", &u[posicion].edad);

    }while(u[posicion].edad < 1 || u[posicion].edad > 100 );

    do
    {

        printf("\nIngrese su genero: f, m o x\n");
        u[posicion].genero = getche();

    }while(u[posicion].genero != 'f' && u[posicion].genero != 'm' && u[posicion].genero != 'x');

    arrayToArchivo(nombreArchivo, u, v);

}

void arrayToArchivo(char nombreArchivo[], usuario u[], int v)
{

    FILE *archi = fopen(nombreArchivo, "wb");

    if(archi)
    {

        fwrite(u, sizeof(usuario), v, archi);
        
        fclose(archi);

    }

}

int crearUsuario(char archivo[])
{

    char pass2[30];

    int longCadena = 0;

    int compararCadenas = 0;

    int verificaEmail;

    int dia = 0, mes = 0, anio = 0;

    char diaStr[20];
    char mesStr[20];
    char anioStr[20];

    usuario u; //Declaramos una variable de tipo usuario.

    FILE *archi; //Declaramos un puntero a la estructura FILE.

    archi = fopen(archivo, "ab");

    if(archi == NULL)
    {

        return -1; //Retorno -1 si hubo un error al abrir/crear el archivo.

    }

    u.id = cantElementosArchivo("usuario.bid", sizeof(usuario)) + 1;

    puts("----------------\n");

    do
    {

        printf("\nIngrese nombre y apellido entre 6 y 30 caracteres: \n");
        fflush(stdin);
        gets(u.nombre);

        longCadena = strlen(u.nombre);

    }
    while(longCadena < 6 || longCadena > 30);

    do
    {

        printf("\nIngrese una edad del 1 al 100: \n");
        scanf("%d", &u.edad);

    }
    while(u.edad < 1 || u.edad > 100 );

    do
    {

        printf("\nIngrese su email: \n");
        fflush(stdin);
        gets(u.email);

        verificaEmail = comprobarEmail(u.email);

        //printf("%d", verificaEmail);  //Control de funcion

        if(verificaEmail == 1)
        {

            puts("UN EMAIL DEBE TENER UN ARROBA Y TERMINAR EN .COM!\n");

        }
        else if(verificaEmail == -9)
        {

            puts("EL EMAIL YA EXISTEª ELIJA OTRO.\n");

        }

    }
    while(verificaEmail != 0);

    do
    {

        do
        {

            printf("\nIngrese password: \n");
            gets(u.pass);
            longCadena = strlen(u.pass);

        }
        while(longCadena < 5);  //obligo al usuario a ingresar ua contraseña de, como minimo, 5 caracteres.

        printf("\nConfirmar pass: \n");
        gets(pass2);

        compararCadenas = strcmp(u.pass, pass2);

    }
    while(compararCadenas != 0);

    do
    {

        printf("\nIngrese su genero: f, m o x\n");
        u.genero = getche();

    }
    while(u.genero != 'f' && u.genero != 'm' && u.genero != 'x');

    do
    {

        printf("\nIngresar el dia de nacimiento.\n");
        scanf("%d", &dia);

    }
    while( dia < 1 || dia > 31);

    do
    {

        printf("\nIngrese mes de nacimiento\n");
        scanf("%d", &mes);

    }
    while( mes < 1 || mes > 12);

    do
    {

        printf("\nIngrese el anio de nacimiento\n");
        scanf("%d", &anio);

    }
    while(anio < 1940 || anio > 2024);

    //Ahora convertiremos las fechas de int a string con la función itoa():
    sprintf(diaStr, "%d", dia); //Paso de int a str.
    sprintf(mesStr, "%d", mes);
    sprintf(anioStr, "%d", anio);

    sprintf(u.fechaNacimiento, "%s %s %s %s %s", diaStr, "|", mesStr, "|", anioStr); // COn la función sprintf puedo agregar varios string a un string. Por eso, me sirve esta función y no strcpy().

    do
    {

        printf("\nSi usted conoce la key para ser administrador, escribala; sino, presione 1.\n");
        scanf("%d", &u.rol);

        if(u.rol == 4815)
        {

            u.rol = 2;

        }

    }
    while(u.rol != 2 && u.rol != 1);

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
    if(archi != NULL)
    {

        while(fread(&u, sizeof(usuario), 1, archi) > 0)
        {

            printf("Registro N %d\n", i);
            puts("-----------\n");
            printf("ID: %d\n", u.id);
            printf("Nombre y apellido: %s\n", u.nombre);
            printf("Edad: %d\n", u.edad);
            printf("Genero: %c\n", u.genero);
            printf("Fecha de nacimiento: %s\n", u.fechaNacimiento);
            printf("Rol: %d\n", u.rol);
            puts("---------------\n");

        }

    }

}

int comprobarEmail(char email[])
{

    int i = 0;

    int flag = 1;

    while(email[i] != '\0' && flag == 1)
    {

        if (email[i] == 64)  //Compruebo que el mail tenga un arroba. 64 es el @ en ASCII.
        {

            if(tienePuntoCom(email) == 0)  //Ya comprobado que haya un arroba, compruebo que tenga ".com".
            {

                if(existeEmail(email) == 0)  //Solo falta comprobar que el email no exista.
                {

                    flag = 0; //Y, así, si el email ingresado pasa los tres test, flag valdrá 0.

                }
                else
                {

                    flag = -9;

                }

            }

        }

        i++;

    }

    return flag;

}

int existeEmail(char email[])
{

    usuario a[100];

    int i = 0;

    int control = 0;

    int v = archivoToArregloUsuario("usuario.bid", a, 0, 100);

    while(i < v && control == 0)  //Si control deja de valer 0, no tiene sentido seguir recorriendo el bucle; pues, ya sé que el mail existe.
    {

        if(strcmpi(a[i].email, email) == 0)
        {

            control = 1;

        }

        i++;

    }

    return control;

}

int tienePuntoCom(char email[])
{

    int longitud = strlen(email);

    int i = 0;

    int j = longitud - 4;

    char aux[10];

    while(j <= longitud)
    {

        aux[i] = email[j];

        i++;
        j++;

    }

    return strcmpi(aux, ".com");

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

    while(i < v)
    {

        puts("----------------------------\n");

        printf("Registro N %d\n", i);

        printf("ID: %d\n", a[i].id);
        printf("Nombre: %s\n", a[i].nombre);
        printf("Email: %s\n", a[i].email);
        printf("Edad: %d\n", a[i].edad);
        printf("Rol: %d\n", a[i].rol);
        printf("Contrasenia: %s\n", a[i].pass);
        printf("Genero: %c\n", a[i].genero);
        printf("Fecha de nacimiento: %s\n", a[i].fechaNacimiento);

        puts("----------------------------\n");

        i++;

    }

}

int buscarUsuario(usuario a[], int v, char email[], char pass[])
{

    int i = 0;

    int control = -2;

    while(i < v)
    {

        if(strcmpi(a[i].email, email) == 0)
        {

            if(strcmpi(a[i].pass, pass) == 0)
            {

                control = i; //Retorno la posición del usuario. Así, me será muy sencillo acceder a todos sus datos.

            }
            else
            {

                control = -1;

            }

        }

        i++;

    }

    return control;

}

void mostrarUsuario(usuario u)  ///Función para controlar los datos almacenados en SESSION
{
    puts("-----------\n");
    printf("ID: %d\n", u.id);
    printf("Nombre y apellido: %s\n", u.nombre);
    printf("Email: %s\n", u.email);
    printf("Edad: %d\n", u.edad);
    printf("Genero: %c\n", u.genero);
    printf("Fecha de nacimiento: %s\n", u.fechaNacimiento);
    printf("Rol: %d\n", u.rol);
    puts("---------------\n");
}
