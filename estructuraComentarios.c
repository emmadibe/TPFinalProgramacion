#include "estructuraComentarios.h"



void archivoToArrayComentario(char nombreArchivo[], stComentario c[], int  *v, int d)
{
    int cant = cantElementosArchivo(nombreArchivo, sizeof(stComentario));
    int total = cant + *v;

    FILE *archi = fopen(nombreArchivo, "rb");

    if(archi && total <= d)
    {
        while(fread(&c[*v], sizeof(stComentario), 1, archi) > 0)
        {
            *v = *v + 1;
        }
        fclose(archi);
    }
}

int buscarPosComentarioIdLibro(int idLibro, stComentario c[], int v)
{
    int i = 0;
    int posicion = -1;
    char flag = 't';

    while(i < v && flag == 't')
    {
        if(c[i].idLibro == idLibro)
        {
            posicion = i;
            flag = 'f';
        }
        i++;
    }
    return posicion;
}

void arrayToArchivoComentarios(stComentario c[], int v, char archivoComentarios[])
{
    FILE * archi = fopen(archivoComentarios,"wb");

    if(archi)
    {
        fwrite(c,sizeof(stComentario),v,archi);
        fclose(archi);
    }
}

void subMenuModificaComentario(stComentario c[], int pos)
{
    int option2 = 0;

    do
    {
        printf("Cual campo queres modificar?\n");
        printf("1. Modificar Titulo del comentario\n");
        printf("2. Modificar Descripcion\n");
        printf("3. Modificar Puntaje\n");
        printf("0. Salir de EDITAR COMENTARIO\n");

        scanf("%d",&option2);

        switch(option2)
        {
        case 1:
            printf("Ingrese el nuevo titulo\n");
            fflush(stdin);
            gets(c[pos].tituloComentario);
            printf("Se modifico correctamente \n");
            break;
        case 2:
            printf("Ingrese la nueva descripcion \n");
            fflush(stdin);
            gets(c[pos].descripcion);
            printf("Se modifico correctamente\n");
            break;
        case 3:

            do
            {
                printf("Ingrese nuevo puntaje del 0 al 5 al libro.\n");
                fflush(stdin);
                scanf("%d", &c[pos].puntaje);
            }
            while(c[pos].puntaje < 0 || c[pos].puntaje > 5);

            printf("Se modifico correctamente\n");
            break;
        case 0:
            break;
        default:
            printf("No existe esa opción. Quiere volver a intentar? Presione 1.\n");
            scanf("%d", &option2);
        }
        system("cls");
    }
    while (option2 == 1);
}


int buscaComentarioPosicionPorIdComent(stComentario c[], int v, int idBuscado)
{
    int pos = -1;
    int i = 0;

    while(i < v && pos == -1 )
    {
        if(c[i].idComentario == idBuscado)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}

stComentario cargaUnComentario(int idUsuario, int idLibro, char archivoComentarios[])
{
    stComentario nuevoComentario;
    int puntaje = -1;

    //OBTENGO LA FECHA ACTUAL :
    time_t tiempo_actual;
    struct tm* tiempo_local;
    char fecha_actual[80];

    // Obtener el tiempo actual
    tiempo_actual = time(NULL);
    tiempo_local = localtime(&tiempo_actual);

    // Formatear la fecha actual como una cadena
    strftime(fecha_actual, 80, "%d/%m/%Y", tiempo_local);

    nuevoComentario.idUsuario = idUsuario;
    nuevoComentario.idLibro = idLibro;
    nuevoComentario.idComentario = buscaMayorIDComentario(archivoComentarios) + 1;

    printf("Titulo del comentario: \n");
    fflush(stdin);
    gets(nuevoComentario.tituloComentario);

    printf("Comente, en un maximo de 500 caracteres, que le parecio el libro: \n");
    fflush(stdin);
    gets(nuevoComentario.descripcion);

    do
    {

        printf("Ponele un puntaje del 0 al 5 al libro.\n");
        fflush(stdin);
        scanf("%d", &puntaje);

    }
    while(puntaje < 0 || puntaje > 5);

    nuevoComentario.puntaje = puntaje;

    strcpy(nuevoComentario.fechaComentario, fecha_actual);

    return nuevoComentario;
}

int buscaMayorIDComentario(char archivoComentario[])
{
    stComentario arregloComentarios[500];
    int val = 0;
    int mayorId = -1;

    archivoToArrayComentario(archivoComentario,arregloComentarios,&val,500);

    for(int i=0; i<val; i++)
    {
        if(arregloComentarios[i].idComentario > mayorId)
        {
            mayorId = arregloComentarios[i].idComentario;
        }
    }

    return mayorId;
}


void intercambioComentariosArreglo(stComentario *a, stComentario *b)
{
    stComentario comenAux = *a;

    *a = *b;
    *b = comenAux;
}

int archivoToArrayComenSegunIdLibro(char archivoComentarios[], stComentario arregloComent[], int v, int dim, int idLibro)
{
    stComentario aux;
    FILE * archi = fopen(archivoComentarios, "rb");
    int i = v;

    if(archi)
    {
        while( i < dim && fread(&aux, sizeof(stComentario), 1, archi) > 0)
        {
            if(aux.idLibro == idLibro)
            {
                arregloComent[i] = aux;
                i++;
            }
        }
        fclose(archi);
    }

    return i; //retorna los validos
}

int archivoToArrayComenSegunIdUsuario(char archivoComentarios[], stComentario arregloComent[], int v, int dim, int idUsuario)
{
    stComentario aux;
    FILE * archi = fopen(archivoComentarios, "rb");
    int i = v;

    if(archi)
    {
        while( i < dim && fread(&aux, sizeof(stComentario), 1, archi) > 0)
        {
            if(aux.idUsuario == idUsuario)
            {
                arregloComent[i] = aux;
                i++;
            }
        }
        fclose(archi);
    }

    return i; //retorna los validos
}

int usuarioYaComentoLibro(int idLibro, int idUsuario, char archivoComentarios[])
{
    stComentario arrayComents[500];
    int validos = 0, i = 0;
    int flag = 0; // en un primcipio, suponemos que el comentario no existe en el archivo

    validos = archivoToArrayComenSegunIdLibro(archivoComentarios,arrayComents,validos,500,idLibro);

    while(i < validos && flag == 0)
    {
        if(idUsuario == arrayComents[i].idUsuario)  // comprueba, libro por libro, si el titulo ya está guardado en el archivo (no diferencia entre mayusculas y minusculas
        {
            flag = 1; // El libro ya existe en el archivo
        }
        i++;
    }
    return flag; // 1: el usuario ya comento, 0: el usuario todavia no comento
}

int sumaPuntuacionesRecursivoCondicion(stComentario arregloComent[],int val, int i, int idLibro)
{
    int sumatoria;

    if(i == val)
    {
        sumatoria = 0;
    }
    else
    {
        if(arregloComent[i].idLibro == idLibro)
        {
            sumatoria = (arregloComent[i].puntaje) + (sumaPuntuacionesRecursivoCondicion(arregloComent,val,i+1,idLibro));
        }
        else
        {
            sumatoria = sumaPuntuacionesRecursivoCondicion(arregloComent,val,i+1,idLibro);
        }
    }
    return sumatoria;
}

int cantPuntuacionesRecursivoCondicion(stComentario arregloComent[],int val, int i, int idLibro)
{
    int cant;

    if(i == val)
    {
        cant = 0;
    }
    else
    {
        if(arregloComent[i].idLibro == idLibro)
        {
            cant = 1 + cantPuntuacionesRecursivoCondicion(arregloComent,val,i+1,idLibro);
        }
        else
        {
            cant = cantPuntuacionesRecursivoCondicion(arregloComent,val,i+1,idLibro);
        }
    }
    return cant;
}

float promedioPuntuacion(stComentario arregloComent[], int val, int idLibro)
{
    return (float) sumaPuntuacionesRecursivoCondicion(arregloComent,val,0,idLibro)/cantPuntuacionesRecursivoCondicion(arregloComent,val,0,idLibro);
}







//
/////eliminar comentario:
//void eliminarComentario(char archivoComentarios[])
//{
//
//        int v = 0;
//        int dimension = 300;
//        int idComenEliminar = 0;
//        int pos;
//
//        v = archivoToArrayComentario(archivoComentarios, c, &v, dimension);
//
//        printf("Ingresar el id del comentario que desea eliminar: \n");
//        scanf("%d", &idComenEliminar);
//
//        pos = buscaComentarioPosicionPorIdComent(c,v,idcomenEliminar);
//
//        if(pos == -1)
//        {
//
//            printf("No existe un comentario con ese id\n");
//
//        }else{
//
//
//            v = eliminarC(c, v, pos);
//
//            arrayToArchivoComentarios(c, v, archivoComentarios); //Guardo el array en el archivo de comentarios
//
//            printf("Comentario eliminado correctamente\n");
//
//            }
//
//        }
//
//
//
//int eliminarC(stComentario c[] , int v, int pos)
//{
//
//    c[pos].idComentario, c[v - 1].idComentario;
//    c[pos].idLibro,  c[v - 1].idLibro;
//    c[pos].idUsuario,  c[v - 1].idUsuario;
//    strcpy(c[pos].tituloComentario,  c[v - 1].tituloComentario);
//    strcpy(c[pos].descripcion =  c[v - 1].descripcion);
//    c[pos].puntaje =  c[v - 1].puntaje;
//    strcpy(c[pos].fechaComentario =  c[v - 1].fechaComentario);
//    c[pos].eliminado =  c[v - 1].eliminado;
//
//
//    return v - 1; //un comentario menos
//
//}
//



