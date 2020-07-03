#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include <stdbool.h>


//Estucturas De Datos
typedef struct{
  int dia;
  int mes;
  int anno;
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
  bool alta;
}Ficha;

//FUNCIONES CSV
const char* get_csv_field (char * tmp, int i);
char * _strdup (const char *s);

//FUNCIONES DEL PROGRAMA
void poblarMapas(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna, Ficha * persona);
void ingresoManual(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna);
Ficha *crearPaciente(char *nombre, int edad, char *sexo, char *rut, char *sangre, char *prevMedica, char *comuna, char *diagnostico, int sala, int dia, int mes, int anno);
int MostrarMenu(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna);
void CargarArchivo(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna);

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




void main(){
    //Creamos los mapas a usar
    Map *mapaNombre = createMap(stringHash,stringEqual);
    Map *mapaRut = createMap(stringHash,stringEqual); //PROBLEMA
    Map *mapaSexo = createMap(stringHash,stringEqual); //PROBLEMATICO
    Map *mapaSangre = createMap(stringHash,stringEqual);
    Map *mapaMes = createMap(stringHash,stringEqual); //PROBLEMA
    Map *mapaAno = createMap(stringHash,stringEqual); //PROBLEMA
    Map *mapaComuna = createMap(stringHash,stringEqual);
    //Mostramos el menu principal desde alli modificamos las estructuras y llamamos a las funciones
    MostrarMenu(mapaNombre,mapaRut,mapaSexo, mapaSangre,mapaMes,mapaAno,mapaComuna);

}

int MostrarMenu(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna){
    system("@cls||clear");
    int key = 0;
    printf("***********************************************\n");
    printf("|---------------------------------------------|\n");
    printf("| 1) INGRESAR PACIENTE MANUALMENTE}            |\n");
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
    printf("Ingrese Opcion\n");
    while(key != 6){
        scanf("%d",&key);
        switch(key){
            case 1:
            //LLAMAMOS AL SUBMENU DE INGRESO DE DATOS
            //ingresoManual(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna);
            break;

            case 2:
            //SUBMENU BUSQUEDA INDIVIDUAL
            break;

            case 3:
            //SUBMENU BUSQUEDA GRUPAL
            break;

            case 4:
            //FUNCION DAR DE ALTA
            break;

            case 5:
            //FUNCION IMPORTAR LISTA PACIENTES
            CargarArchivo(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna);
            break;

            case 6:
            //SALIR DEL PROGRAMA
            printf("SALIENDO DEL PROGRAMA\n");
            return 1;
            break;

            default:
            //OPCION NO VALIDA
            printf("Opcion Invalida, Intente Denuevo\n");
            key = 0;
            break;
        }
    }
}


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
void CargarArchivo(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna){
    FILE *fp = fopen("pacientes.csv","r");
    char linea[1024];
    if (fp == NULL){
        printf("ARCHIVO NO ENCONTRADO\n");
        return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna);
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
            char* prefecha =  (char*)get_csv_field(linea,10);
            ficha->fecha = separarFecha(prefecha);
            ficha->alta = false;
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
                printf("|MES  : %d                         |\n",ficha->fecha->mes);
                printf("|ANNO: %d                       |\n",ficha->fecha->anno);
                printf("|DIA: %d                          |\n",ficha->fecha->dia);
                printf("|*********************************|\n");
                insertMap(mapaNombre,ficha->nombre,ficha);
                insertMap(mapaSangre, ficha->sangre, ficha);
                insertMap(mapaComuna, ficha->comuna, ficha);
                insertMap(mapaRut,ficha->rut,ficha);
                Ficha* imprimir = searchMap(mapaNombre,ficha->nombre);
                printf(" %s Si funciona\n",imprimir->nombre);
                printf("INGRESADOS AL MAPA CORRECTAMENTE\n");
                //PROBLEMAS AL INGRESAR A ESTOS 2 MAPAS
                //insertMap(mapaAno,ficha->fecha->anno,ficha);
                //insertMap(mapaMes,ficha->fecha->mes,ficha);
            }
        }
    getch();
    }
    fclose(fp);
    return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna);
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
    fecha->dia = atoi(token);
    token = strtok(NULL,s);
    fecha->mes = atoi(token);
    token = strtok(NULL,s);
    fecha->anno = atoi(token);
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




