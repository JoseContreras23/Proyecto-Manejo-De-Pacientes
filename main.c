#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "list.h"
#include <stdbool.h>


//Estucturas De Datos
typedef struct{
  char* dia;
  char* mes;
  char* anno;
}Fecha;

typedef struct {
  char* nombre;
  int edad;
  char* sexo;
  char* rut;
  char* sangre;
  char* prevMedica;
  char* comuna;
  char* diagnostico;
  int sala;
  Fecha *fecha;
}Ficha;

//FUNCIONES CSV
const char* get_csv_field (char * tmp, int i);
char * _strdup (const char *s);

//FUNCIONES DEL PROGRAMA
void poblarMapas(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna, Ficha * persona);
void ingresoManual(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre,Map* prevMedica, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* alta);
Ficha *crearPaciente(char *nombre, int edad, char *sexo, char *rut, char *sangre, char *prevMedica, char *comuna, char *diagnostico, int sala, int dia, int mes, int anno);
//FUNCIONES MENU
void MostrarMenu(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaPrev,Map* alta);
void subMenuGrupal(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaPrev,Map *alta);
void subMenuIndividual(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaPrev,Map *alta);

void CargarArchivo(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaPrev,Map* alta);
void darAlta(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaPrev,Map* alta);

//FUNCIONES DE FUNCION 5
Fecha* separarFecha(char* prefecha);


//FUNCIONES HASH Y EQUAL
long long stringHash(const void * key);
int stringEqual(const void * key1, const void * key2);

long long stringHash(const void * key) {
    long long hash = 5381;

    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}




int main(void){
    //Creamos los mapas a usar
    Map *mapaNombre = createMap(stringHash,stringEqual);
    Map *mapaRut = createMap(stringHash,stringEqual); //PROBLEMA
    Map *mapaSexo = createMap(stringHash,stringEqual); //PROBLEMATICO
    Map *mapaSangre = createMap(stringHash,stringEqual);
    Map *mapaMes = createMap(stringHash,stringEqual); //PROBLEMA
    Map *mapaAno = createMap(stringHash,stringEqual); //PROBLEMA
    Map* mapaPrev = createMap(stringHash,stringEqual);
    Map *mapaComuna = createMap(stringHash,stringEqual);
    Map *alta = createMap(stringHash,stringEqual); //MAPA PARA GUARDAR A LAS PERSONAS QUE FUERON DADAS DE ALTA POST ELIMINACION
    //Mostramos el menu principal desde alli modificamos las estructuras y llamamos a las funciones
    MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaPrev,alta);
    return 0;

}
//MENUS
void MostrarMenu(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    int key = 0;
    printf("|*********************************************|\n");
    printf("|---------------------------------------------|\n");
    printf("| 1) INGRESAR PACIENTE MANUALMENTE}           |\n");
    printf("|---------------------------------------------|\n");
    printf("| 2) BUSQUEDA INDIVIDUAL                      |\n");
    printf("|---------------------------------------------|\n");
    printf("| 3) BUSQUEDA GRUPAL                          |\n");
    printf("|---------------------------------------------|\n");
    printf("| 4) DAR DE ALTA                              |\n");
    printf("|---------------------------------------------|\n");
    printf("| 5) IMPORTAR ARCHIVO PACIENTES               |\n");
    printf("|---------------------------------------------|\n");
    printf("| 6) SALIR                                    |\n");
    printf("|---------------------------------------------|\n");
    printf("***********************************************\n");
    printf("\n");
    while(key != 6){
        printf("Ingrese Opcion (NO INGRESE LETRAS PORFAVOR)\n");
        scanf(" %d",&key);
        switch(key){
            case 1:
            //LLAMAMOS LA FUNCION DE INGRESO MANUAL
            ingresoManual(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaPrev,mapaMes,mapaAno, mapaComuna,alta);
            break;

            case 2:
            //SUBMENU BUSQUEDA INDIVIDUAL
            subMenuIndividual(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaPrev,alta);

            break;

            case 3:
            //SUBMENU BUSQUEDA GRUPAL
            subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaPrev,alta);
            break;

            case 4:
            //FUNCION DAR DE ALTA
            darAlta(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaPrev,alta);
            break;

            case 5:
            //FUNCION IMPORTAR LISTA PACIENTES
            CargarArchivo(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaPrev,alta);
            break;

            case 6:
            //SALIR DEL PROGRAMA
            printf("SALIENDO DEL PROGRAMA\n");
            return exit(0);
            break;

            default:
            //OPCION NO VALIDA
            printf("Opcion Invalida, Intente Denuevo\n(NO INGRESE LETRAS PORFAVOR\n)");
            fflush(stdin);
            break;
        }
    }
}

//FUNCION 2
void subMenuIndividual(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    int key3 = 0;
    printf("|*********************************************|\n");
    printf("|    MENU DE BUSQUEDA INDIVIDUAL              |\n");
    printf("|---------------------------------------------|\n");
    printf("| 1) BUSCAR PACIENTE POR NOMBRE               |\n");
    printf("|---------------------------------------------|\n");
    printf("| 2) BUSCAR PACIENTE POR RUT                  |\n");
    printf("|---------------------------------------------|\n");
    printf("| 3) VOLVER AL MENU ANTERIOR                  |\n");
    printf("|---------------------------------------------|\n");
    printf("|*********************************************|\n");
    printf("\n");
    do{
        printf("PORFAVOR INGRESE LA OPCION DESEADA\n");
        scanf(" %d",&key3);
        fflush(stdin);
        switch(key3){
            case 1:
            //FUNCION BUSCAR POR NOMBRE
            break;

            case 2:
            //FUNCION BUSCAR POR RUT
            break;

            case 3:
            return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaPrev,alta);
            break;

            default:
            printf("OPCION INGRESADA NO VALIDA INGRESE NUEVAMENTE PORFAVOR\n");
            fflush(stdin);
            break;
        }
    }while(key3!=3);
}


//Funcion 3
void subMenuGrupal(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    int key2 = 0;
    printf("|*********************************************|\n");
    printf("|    MENU DE BUSQUEDA MULTIPLE O GRUPAL       |\n");
    printf("|---------------------------------------------|\n");
    printf("| 1) BUSCAR PACIENTES POR SEXO                |\n");
    printf("|---------------------------------------------|\n");
    printf("| 2) BUSCAR PACIENTES POR TIPO DE SANGRE      |\n");
    printf("|---------------------------------------------|\n");
    printf("| 3) BUSCAR PACIENTES POR MES DE INGRESO       |\n");
    printf("|---------------------------------------------|\n");
    printf("| 4) BUSCAR PACIENTES POR ANNO DE INGRESO     |\n");
    printf("|---------------------------------------------|\n");
    printf("| 5) BUSCAR PACIENTES POR COMUNA              |\n");
    printf("|---------------------------------------------|\n");
    printf("| 6) BUSCAR PACIENTES POR PREVISION MEDICA    |\n");
    printf("|---------------------------------------------|\n");
    printf("| 7) BUSCAR PACIENTES POR SALA                |\n");
    printf("|---------------------------------------------|\n");
    printf("| 8) VOLVER AL MENU ANTERIOR                  |\n");
    printf("|---------------------------------------------|\n");
    printf("|*********************************************|\n");
    printf("\n");
    do{
        printf("PORFAVOR INGRESE LA OPCION DESEADA\n");
        scanf(" %d",&key2);
        fflush(stdin);
        switch(key2){
            case 1:
            //FUNCION BUSQUEDA SEXO
            break;

            case 2:
            //FUNCION BUSQUEDA TIPO DE SANGRE
            break;

            case 3:
            //FUNCION BUSQUEDA MES DE INGRESO
            break;

            case 4:
            //FUNCION BUSQUEDA ANNO DE INGRESO
            break;

            case 5:
            //FUNCION BUSQUEDA COMUNA
            break;

            case 6:
            //FUNCION BUSQUEDA PREV MEDICA
            break;

            case 7:
            //FUNCION BUSQUEDA GRUPAL POR SALA
            break;

            case 8:
            return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaPrev,alta);
            break;

            default:
            printf("OPCION INGRESADA NO VALIDA INGRESE NUEVAMENTE PORFAVOR\n");
            fflush(stdin);
            break;
        }
    }while(key2!=7);
}



//Funcion 1
void ingresoManual(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre,Map* mapaPrev, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* alta){
    system("@cls||clear");
    //PREGUNTAMOS E INGRESAMOS LOS DATOS QUE NOS PIDEN
    char nombre[50];
    printf("PORFAVOR INGRESE LOS DATOS SEGUN SE PIDEN\n");
    fflush(stdin);
    printf("NOMBRE: \n");
    fflush(stdin);
    scanf("%[^\n]s",&nombre);

    char rut[12];
    printf("RUT: \n");
    fflush(stdin);
    scanf("%[^\n]s",&rut);

    char sexo[3];
    printf("SEXO:(M O F) \n");
    fflush(stdin);
    scanf("%[^\n]s",&sexo);

    char edad[3];
    printf("EDAD: \n");
    fflush(stdin);
    scanf("%[^\n]s",&edad);

    char diagnostico[50];
    printf("DIAGNOSTICO O CONDICION: \n");
    fflush(stdin);
    scanf("%[^\n]s",&diagnostico);

    char comuna[20];
    printf("COMUNA DE RESIDENCIA: \n");
    fflush(stdin);
    scanf("%[^\n]s",&comuna);

    char sangre[4];
    printf("TIPO DE SANGRE: \n");
    fflush(stdin);
    scanf("%[^\n]s",&sangre);


    char prevMedica[20];
    printf("PREVISION MEDICA : \n");
    fflush(stdin);
    scanf("%[^\n]s",&prevMedica);

    char dia[3];
    printf("DIA DE INGRESO(EN NUMERO XX):\n");
    fflush(stdin);
    scanf("%[^\n]s",&dia);

    char mes[3];
    printf("MES DE INGRESO(EN NUMERO XX):\n");
    fflush(stdin);
    scanf("%[^\n]s",&mes);

    char anno[5];
    printf("ANNO DE INGRESO(EN NUMERO XXXX):\n");
    fflush(stdin);
    scanf("%[^\n]s",&anno);

    //Ingresamos las variables al tipo ficha
    Ficha* nuevo = (Ficha*) malloc (sizeof(Ficha));
    nuevo->nombre = nombre;
    nuevo->rut = rut;
    nuevo->sexo = sexo;
    nuevo->edad = edad;
    nuevo->diagnostico = diagnostico;
    nuevo->comuna = comuna;
    nuevo->sangre = sangre;
    nuevo->prevMedica = prevMedica;
    printf("PARAMETROS INGRESADOS CORRETCTAMENTE\n");
    Fecha* Nfecha =(Fecha*) malloc(sizeof(Fecha));
    Nfecha->mes = mes;
    Nfecha->dia = dia;
    Nfecha->anno = anno;
    nuevo->fecha = Nfecha;
    printf("FECHA INGRESADA CORRECTAMENTE\n");
    //PROCEDEMOS A INGRESARLO A LA BASE DE DATOS
    //REVISAMOS SI LA EL MAPA ESTA VACIO
    if(firstMap(mapaNombre) == NULL){
        //CREAMOS UNA LISTA VACIA E INSERTAMOS AL PACIENTE AHI
        list* lista = list_create_empty();
        list_push_front(lista,nuevo);
        //INSERTAMOS A LA LISTA AL LOS MAPAS GRUPALES
        insertMap(mapaAno,nuevo->fecha->anno,lista);
        insertMap(mapaMes,nuevo->fecha->mes,lista);
        insertMap(mapaComuna,nuevo->comuna,lista);
        insertMap(mapaPrev,nuevo->prevMedica,lista);
        insertMap(mapaSangre,nuevo->sangre,lista);
        insertMap(mapaSexo,nuevo->sexo,lista);
    }
    //SINO AÑADIMOS EL TIPO FICHA NUEVO A CADA LISTA DE CADA MAPA GRUPAL
    else{
        //MAPA ANNO
        list* aux = searchMap(mapaAno,nuevo->fecha->anno); //INGRESAMOS A LA LISTA DEL MAPA
        list_push_front(aux,nuevo);
        //MAPA MES
        aux = searchMap(mapaMes,nuevo->fecha->mes); //INGRESAMOS A LA LISTA DEL MAPA
        list_push_front(aux,nuevo);
        //MAPA COMUNA
        aux = searchMap(mapaComuna,nuevo->comuna); //INGRESAMOS A LA LISTA DEL MAPA
        list_push_front(aux,nuevo);
        //MAPA PREVISION M
        aux = searchMap(mapaPrev,nuevo->prevMedica); //INGRESAMOS A LA LISTA DEL MAPA
        list_push_front(aux,nuevo);
        //MAPA SANGRE
        aux = searchMap(mapaSangre,nuevo->sangre); //INGRESAMOS A LA LISTA DEL MAPA
        list_push_front(aux,nuevo);
        //MAPA SEXO
        aux = searchMap(mapaSexo,nuevo->sexo); //INGRESAMOS A LA LISTA DEL MAPA
        list_push_front(aux,nuevo);
    }
    //LUEGO SE INSERTA EL TIPO FICHA EN LOS MAPAS INDIVIDUALES
    insertMap(mapaNombre,nuevo->nombre,nuevo);
    insertMap(mapaRut,nuevo->rut,nuevo);
    printf("PERSONA INGRESADA SATISFACTORIAMENTE AL SISTEMA\n");
    getch();
    return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaPrev,alta);
}






//FUNCIONES DE USO MULTIPLE
Ficha *crearPaciente(char *nombre, int edad, char *sexo, char *rut, char *sangre, char *prevMedica, char *comuna, char *diagnostico, int sala, int dia, int mes, int anno){
  Ficha *f = malloc(sizeof(Ficha));
  f->nombre = nombre;
  f->edad = edad;
  f->sexo = sexo;
  f->rut = rut;
  f->sangre = sangre;
  f->prevMedica = prevMedica;
  f->comuna = comuna;
  f->diagnostico = diagnostico;
  f->sala = sala;
  f->fecha->dia = dia;
  f->fecha->mes = mes;
  f->fecha->anno = anno;
  return f;
}




//FUNCIONES INGRESO
void CargarArchivo(Map* mapaNombre,Map* mapaRut,Map* mapaSexo,Map* mapaSangre,Map* mapaMes,Map* mapaAno,Map* mapaComuna,Map* mapaPrev,Map* alta){
    system("@cls||clear");
    FILE *fp = fopen("pacientes.csv","r");
    char linea[1024];
    if (fp == NULL){
        printf("ARCHIVO NO ENCONTRADO\n");
    }
    else{
        //CONTAMOS LAS LINEAS DEL ARCHIVO
        printf("ARCHIVO ENCONTRADO\n");
        while(fgets(linea,1024,(FILE*)fp)!= NULL){
            Ficha *ficha =  malloc (sizeof(Ficha)); //Se crea el tipo ficha
            printf("FICHA CREADA\n");
            //Ingresamos los datos que corresponden en orden al tipo ficha usando la funcion get_csv_field
            ficha->nombre = (char*)get_csv_field(linea,1);
            ficha->edad = atoi(get_csv_field(linea,2));
            ficha->sexo = (char*)get_csv_field(linea,3);
            ficha->rut = (char*)get_csv_field(linea,4);
            ficha->sangre = (char*)get_csv_field(linea,5);
            ficha->prevMedica = (char*)get_csv_field(linea,6);
            ficha->comuna = (char*)get_csv_field(linea,7);
            ficha->diagnostico = (char*)get_csv_field(linea,8);
            ficha->sala = atoi(get_csv_field(linea,9));
            char* prefecha = get_csv_field(linea,10);
            ficha->fecha = separarFecha(prefecha);
            //Saltamos el tipo null leido desde archivo
            if(ficha->sexo != NULL){
                //Luego poblamos los mapas por cada paciente leido desde el archivo
                printf("|*********************************|\n");
                printf("|INFORMACION DE PACIENTE INGRESADA|\n");
                printf("|NOMBRE: %s           |\n",ficha->nombre);
                printf("|EDAD: %d                         |\n",ficha->edad);
                printf("|SEXO: %s                          |\n",ficha->sexo);
                printf("|RUT: %s                |\n",ficha->rut);
                printf("|TIPO DE SANGRE: %s               |\n",ficha->sangre);
                printf("|PREVISION MEDICA: %s      |\n",ficha->prevMedica);
                printf("|COMUNA : %s            |\n",ficha->comuna);
                printf("|DIAGNOSTICO: %s       |\n",ficha->diagnostico);
                printf("|MES  : %s                         |\n",ficha->fecha->mes);
                printf("|ANNO: %s                       |\n",ficha->fecha->anno);
                printf("|DIA: %s                          |\n",ficha->fecha->dia);
                printf("|*********************************|\n");
                //VEMOS SI EXISTEN LAS LISTAS EN LOS MAPAS(GRUPALES)
                if(firstMap(mapaNombre) == NULL){
                    //CREAMOS UNA LISTA VACIA E INSERTAMOS AL PACIENTE AHI
                    list* lista = list_create_empty();
                    list_push_front(lista,ficha);
                    //INSERTAMOS A LA LISTA AL LOS MAPAS GRUPALES
                    insertMap(mapaAno,ficha->fecha->anno,lista);
                    insertMap(mapaMes,ficha->fecha->mes,lista);
                    insertMap(mapaComuna,ficha->comuna,lista);
                    insertMap(mapaPrev,ficha->prevMedica,lista);
                    insertMap(mapaSangre,ficha->sangre,lista);
                    insertMap(mapaSexo,ficha->sexo,lista);
                    printf("INSERTADO A LAS LISTAS CORRECTAMENTE\n");
                }
                    //SINO AÑADIMOS EL TIPO FICHA NUEVO A CADA LISTA DE CADA MAPA GRUPAL
                else{
                    //MAPA ANNO
                    list* aux = searchMap(mapaAno,ficha->fecha->anno); //INGRESAMOS A LA LISTA DEL MAPA
                    list_push_front(aux,ficha);
                    //MAPA MES
                    aux = searchMap(mapaMes,ficha->fecha->mes);
                    list_push_front(aux,ficha);
                    //MAPA COMUNA
                    aux = searchMap(mapaComuna,ficha->comuna);
                    list_push_front(aux,ficha);
                    //MAPA PREVISION M
                    aux = searchMap(mapaPrev,ficha->prevMedica);
                    list_push_front(aux,ficha);
                    //MAPA SANGRE
                    aux = searchMap(mapaSangre,ficha->sangre);
                    list_push_front(aux,ficha);
                    //MAPA SEXO
                    aux = searchMap(mapaSexo,ficha->sexo);
                    list_push_front(aux,ficha);
                    printf("INSERTADO A LAS LISTAS CORRECTAMENTE\n");
                }
                //FINALMENTE INGRESAMOS LAS FICHAS A LOS MAPAS INDIVIDUALES
                insertMap(mapaNombre,ficha->nombre,ficha);
                insertMap(mapaRut,ficha->rut,ficha);
            }
        }
    getch();
    }
    fclose(fp);
    return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaPrev,alta);
}

//FUNCION DAR DE ALTA
void darAlta(Map* mapaNombre,Map* mapaRut,Map* mapaSexo,Map* mapaSangre,Map* mapaMes,Map* mapaAno,Map* mapaComuna,Map* mapaPrev,Map* alta){
    system("@cls||clear");
    char nombre[50];
    char rut[12];
    //Pedimos el rut y nombre de la persona que se desea dar de alta
    printf("PORFAVOR INGRESE EL NOMBRE DE LA PERSONA\n");
    fflush(stdin);
    scanf("%[^\n]s",&nombre);
    printf("PORVAFOR INGRESE EL RUT DE LA PERSONA(FORMATO XXXXXXXX-X)\n");
    fflush(stdin);
    scanf("%[^\n]s",&rut);
    //CREAMOS UN AUX PARA GUARDAR LA FICHA DE LA PERSONA DADA DE ALTA
    Ficha* aux = searchMap(mapaNombre,nombre);
    //SI LA PERSONA NO ESTA
    if(aux == NULL){
        printf("LA PERSONA NO SE ENCUENTRA EN LA BASE DE DATOS PRESIONE ENTER PORFAVOR\n");
        getch();
        return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaPrev,alta);
    }
    //Si se encuentra la persona
    else{
        //GUARDAMOS AUX EN EL MAPA DE ALTA
        insertMap(alta,aux->nombre,aux);
        //Lo eliminamos de los mapas individuales directamente
        eraseKeyMap(mapaNombre,aux->nombre);
        eraseKeyMap(mapaRut,aux->rut);
        printf("PERSONA DADA DE ALTA SATISFACTORIAMENTE\n");
        getch();
        return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaPrev,alta);
    }
}


void poblarMapas(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna, Ficha * persona){
    insertMap(mapaNombre, persona->nombre, persona);
    insertMap(mapaRut, persona->rut, persona);
    insertMap(mapaSexo, persona->sexo, persona);
    insertMap(mapaSangre, persona->sangre, persona);
    insertMap(mapaMes, persona->fecha->mes, persona);
    insertMap(mapaAno,persona->fecha->anno, persona);
    insertMap(mapaComuna, persona->comuna, persona);
}


Fecha* separarFecha(char* prefecha){ //
    Fecha *fecha =  malloc (sizeof(Fecha));
    //La separamos
    const char s[2] = "/";
    char* token;
    token = strtok(prefecha,s);
    //Guardamos los datos en el orden dia, mes, fecha
    fecha->dia = token;
    token = strtok(NULL,s);
    fecha->mes = token;
    token = strtok(NULL,s);
    fecha->anno = token;
    return fecha;
}



char * _strdup (const char *s) { //
    size_t len = strlen (s) + 1;
    void *new = malloc (len);

    if (new == NULL)
    	return NULL;

    return (char *) memcpy (new, s, len);
}

const char *get_csv_field (char * tmp, int i) { //
    //se crea una copia del string tmp
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}




