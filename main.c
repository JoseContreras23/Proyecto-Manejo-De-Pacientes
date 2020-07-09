#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"
#include "list.h"

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
  char* sala;
  Fecha *fecha;
}Ficha;

//FUNCIONES DEL PROGRAMA
void ingresoManual(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);

//FUNCIONES MENU
void MostrarMenu(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);
void subMenuGrupal(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);
void subMenuIndividual(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);

//FUNCIONES SUB MENU INDIVIDUAL(FUNCION 2)
void buscarNombre(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);
void buscarRut(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);

//FUNCIONES SUBMENU GRUPAL (FUNCION 3)
void buscarSexo(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);
void buscarSangre(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);
void buscarMes(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);
void buscarAno(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);
void buscarComuna(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);
void buscarPrev(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);
void buscarSala(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);
//FUNCION 4
void darAlta(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);

//FUNCION 5
void CargarArchivo(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta);
Fecha* separarFecha(char* prefecha);

//FUNCION 6
void exportarArchivo(Map* mapaNombre,Map* mapaRut,Map* mapaSexo,Map* mapaSangre,Map* mapaMes,Map* mapaAno,Map* mapaComuna,Map* mapaSala,Map* mapaPrev,Map* alta);

//FUNCIONES DE UTILIDAD
void insertarMapaGrupal(Map* mapaSexo,Map* mapaSangre,Map* mapaMes,Map* mapaAno,Map* mapaComuna,Map* mapaSala,Map* mapaPrev,Ficha *ficha);
//void poblarMapas(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna, Ficha * persona);
const char* get_csv_field (char * tmp, int i);
char * _strdup (const char *s);
long long stringHash(const void * key);
int stringEqual(const void * key1, const void * key2);






int main(void){
    //Creamos los mapas a usar
    Map *mapaNombre = createMap(stringHash,stringEqual);
    Map *mapaRut = createMap(stringHash,stringEqual);
    Map *mapaSexo = createMap(stringHash,stringEqual);
    Map *mapaSangre = createMap(stringHash,stringEqual);
    Map *mapaMes = createMap(stringHash,stringEqual);
    Map *mapaAno = createMap(stringHash,stringEqual);
    Map* mapaPrev = createMap(stringHash,stringEqual);
    Map *mapaComuna = createMap(stringHash,stringEqual);
    Map *alta = createMap(stringHash,stringEqual); //MAPA PARA GUARDAR A LAS PERSONAS QUE FUERON DADAS DE ALTA POST ELIMINACION
    Map *mapaSala = createMap(stringHash,stringEqual);
    MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
    return 0;
}


//MENU PRINCIPAL
void MostrarMenu(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    int key = 0;
    printf("|*********************************************|\n");
    printf("|---------------------------------------------|\n");
    printf("| 1) INGRESAR PACIENTE MANUALMENTE            |\n");
    printf("|---------------------------------------------|\n");
    printf("| 2) BUSQUEDA INDIVIDUAL                      |\n");
    printf("|---------------------------------------------|\n");
    printf("| 3) BUSQUEDA GRUPAL                          |\n");
    printf("|---------------------------------------------|\n");
    printf("| 4) DAR DE ALTA                              |\n");
    printf("|---------------------------------------------|\n");
    printf("| 5) IMPORTAR ARCHIVO PACIENTES               |\n");
    printf("|---------------------------------------------|\n");
    printf("| 6) EXPORTAR ARCHIVO PACIENTES               |\n");
    printf("|---------------------------------------------|\n");
    printf("| 7) SALIR                                    |\n");
    printf("|---------------------------------------------|\n");
    printf("***********************************************\n");
    printf("\n");
    while(key != 6){
        printf("Ingrese Opcion (NO INGRESE LETRAS PORFAVOR)\n");
        scanf(" %d",&key);
        switch(key){
            case 1:
            //LLAMAMOS LA FUNCION DE INGRESO MANUAL
            ingresoManual(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 2:
            //SUBMENU BUSQUEDA INDIVIDUAL
            subMenuIndividual(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);

            break;

            case 3:
            //SUBMENU BUSQUEDA GRUPAL
            subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 4:
            //FUNCION DAR DE ALTA
            darAlta(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 5:
            //FUNCION IMPORTAR LISTA PACIENTES
            CargarArchivo(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 6:
            //FUNCION EXPORTAR LISTA DE PACIENTES
            exportarArchivo(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 7:
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


//FUNCION INGRESAR PACIENTE(1) LISTO
void ingresoManual(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    //PREGUNTAMOS E INGRESAMOS LOS DATOS QUE NOS PIDEN
    char nombre[50];
    printf("PORFAVOR INGRESE LOS DATOS SEGUN SE PIDEN\n");
    fflush(stdin);
    printf("NOMBRE: \n");
    fflush(stdin);
    scanf("%[^\n]s",nombre);

    char rut[12];
    printf("RUT: \n");
    fflush(stdin);
    scanf("%[^\n]s",rut);

    char sexo[3];
    printf("SEXO:(M O F) \n");
    fflush(stdin);
    scanf("%[^\n]s",sexo);

    char sala[4];
    printf("SALA: \n");
    fflush(stdin);
    scanf("%[^\n]s",sala);

    char edad[3];
    printf("EDAD: \n");
    fflush(stdin);
    scanf("%[^\n]s",edad);

    char diagnostico[50];
    printf("DIAGNOSTICO O CONDICION: \n");
    fflush(stdin);
    scanf("%[^\n]s",diagnostico);

    char comuna[20];
    printf("COMUNA DE RESIDENCIA: \n");
    fflush(stdin);
    scanf("%[^\n]s",comuna);

    char sangre[4];
    printf("TIPO DE SANGRE: \n");
    fflush(stdin);
    scanf("%[^\n]s",sangre);


    char prevMedica[20];
    printf("PREVISION MEDICA : \n");
    fflush(stdin);
    scanf("%[^\n]s",prevMedica);

    char dia[3];
    printf("DIA DE INGRESO(EN NUMERO XX):\n");
    fflush(stdin);
    scanf("%[^\n]s",dia);

    char mes[3];
    printf("MES DE INGRESO(EN NUMERO XX):\n");
    fflush(stdin);
    scanf("%[^\n]s",mes);

    char anno[5];
    printf("ANNO DE INGRESO(EN NUMERO XXXX):\n");
    fflush(stdin);
    scanf("%[^\n]s",anno);

    //Ingresamos las variables al tipo ficha
    Ficha* nuevo = (Ficha*) malloc (sizeof(Ficha));
    nuevo->nombre = nombre;
    nuevo->rut = rut;
    nuevo->sala = sala;
    nuevo->sexo = sexo;
    nuevo->edad = atoi(edad);
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
    //SINO USAMOS LA FUNCION PARA AÑADIRLO A LOS MAPAS GRUPALES
    else{
        insertarMapaGrupal(mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,nuevo);
    }
    //LUEGO SE INSERTA EL TIPO FICHA EN LOS MAPAS INDIVIDUALES
    insertMap(mapaNombre,nuevo->nombre,nuevo);
    insertMap(mapaRut,nuevo->rut,nuevo);
    printf("PERSONA INGRESADA SATISFACTORIAMENTE AL SISTEMA\n");
    getch();
    return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaSala,mapaComuna,mapaPrev,alta);
}


//SUBMENU I  (FUNCION 2) LISTO
void subMenuIndividual(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
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
            buscarNombre(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 2:
            //FUNCION BUSCAR POR RUT
            buscarRut(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 3:
            //VOLVER AL MENU ANTERIOR
            return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            default:
            printf("OPCION INGRESADA NO VALIDA INGRESE NUEVAMENTE PORFAVOR\n");
            fflush(stdin);
            break;
        }
    }while(key3!=3);
}

//SUBFUNCION 1(2) LISTO
void buscarNombre(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    printf("PORFAVOR ESCRIBA EL NOMBRE DE LA PERSONA(NOMBRE PRIMER APELLIDO)\n");
    fflush(stdin);
    char nombre[50];
    scanf(" %[^\n]s",nombre);
    //Buscamos usando searchMap
    Ficha* aux = searchMap(mapaNombre,nombre);
    if(aux == NULL){
        if(!searchMap(alta,nombre)){
            printf("404 PERSONA NO ENCONTRADA O INGRESADA\nPRESIONE ENTER PARA VOLVER AL MENU ANTERIOR\n");
            fflush(stdin);
            getch();
            return subMenuIndividual(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
        }
        else{
            printf("LA PERSONA QUE BUSCA FUE RECIENTEMENTE DADA DE ALTA\n");
            fflush(stdin);
            getch();
            return subMenuIndividual(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
        }
    }
    //Imprmimimos su data
    printf("|-----------------------------------------------------------------------|\n");
    printf("| NOMBRE : %s                                                           |\n",aux->nombre);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| RUT : %s                                                              |\n",aux->rut);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| SEXO : %s                                                             |\n",aux->sexo);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| SALA : %s                                                             |\n",aux->sala);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| COMUNA: %s                                                            |\n",aux->comuna);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| PREVISION MEDICA : %s                                                 |\n",aux->prevMedica);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| TIPO DE SANGRE: %s                                                    |\n",aux->sangre);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| FECHA DE INGRESO: %s/%s/%s                                            |\n",aux->fecha->dia,aux->fecha->mes,aux->fecha->anno);
    printf("|-----------------------------------------------------------------------|\n");
    printf("\n");
    printf("PRESIONE ENTER PARA VOLVER AL MENU PRINCIPAL\n");
    getch();
    return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
}

//SUBFUNCION 2(2) LISTO
void buscarRut(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    printf("PORFAVOR INGRESE EL RUT DE LA PERSONA QUE ESTA BUSCANDO (FORMATO XXXXXXXX-X)\n");
    char rut[10];
    fflush(stdin);
    scanf(" %s",rut);
    //Buscamos la persona
    Ficha* aux = searchMap(mapaRut,rut);
    if(aux == NULL){
        printf("404 PERSONA NO ENCONTRADA O DADA DE ALTA \nPRESIONE ENTER PARA VOLVER AL MENU ANTERIOR\n");
        fflush(stdin);
        getch();
        return subMenuIndividual(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
    }
    //Imprmimimos su data
    system("@cls||clear");
    printf("PACIENTE ENCONTRADO \n");
    printf("|-----------------------------------------------------------------------|\n");
    printf("| NOMBRE : %s                                                           |\n",aux->nombre);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| RUT : %s                                                              |\n",aux->rut);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| SEXO : %s                                                             |\n",aux->sexo);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| SALA : %s                                                             |\n",aux->sala);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| COMUNA: %s                                                            |\n",aux->comuna);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| PREVISION MEDICA : %s                                                 |\n",aux->prevMedica);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| TIPO DE SANGRE: %s                                                    |\n",aux->sangre);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| FECHA DE INGRESO: %s/%s/%s                                            |\n",aux->fecha->dia,aux->fecha->mes,aux->fecha->anno);
    printf("|-----------------------------------------------------------------------|\n");
    printf("\n");
    printf("PRESIONE ENTER PARA VOLVER AL MENU PRINCIPAL\n");
    getch();
    return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
}


//SUBMENU G (FUNCION 3) //LISTO
void subMenuGrupal(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    int key2 = 0;
    printf("|*********************************************|\n");
    printf("|    MENU DE BUSQUEDA MULTIPLE O GRUPAL       |\n");
    printf("|---------------------------------------------|\n");
    printf("| 1) MOSTRAR PACIENTES POR SEXO               |\n");
    printf("|---------------------------------------------|\n");
    printf("| 2) MOSTRAR PACIENTES POR TIPO DE SANGRE     |\n");
    printf("|---------------------------------------------|\n");
    printf("| 3) MOSTRAR PACIENTES POR MES DE INGRESO     |\n");
    printf("|---------------------------------------------|\n");
    printf("| 4) MOSTRAR PACIENTES POR ANNO DE INGRESO    |\n");
    printf("|---------------------------------------------|\n");
    printf("| 5) MOSTRAR PACIENTES POR COMUNA             |\n");
    printf("|---------------------------------------------|\n");
    printf("| 6) MOSTRAR PACIENTES POR PREVISION MEDICA   |\n");
    printf("|---------------------------------------------|\n");
    printf("| 7) MOSTRAR PACIENTES POR SALA               |\n");
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
            buscarSexo(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 2:
            //FUNCION BUSQUEDA TIPO DE SANGRE
            buscarSangre(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 3:
            //FUNCION BUSQUEDA MES DE INGRESO
            buscarMes(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 4:
            //FUNCION BUSQUEDA ANNO DE INGRESO
            buscarAno(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 5:
            //FUNCION BUSQUEDA COMUNA
            buscarComuna(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 6:
            //FUNCION BUSQUEDA PREV MEDICA
            buscarPrev(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 7:
            //FUNCION BUSQUEDA GRUPAL POR SALA
            buscarSala(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            case 8:
            return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
            break;

            default:
            printf("OPCION INGRESADA NO VALIDA INGRESE NUEVAMENTE PORFAVOR\n");
            fflush(stdin);
            break;
        }
    }while(key2!=7);
}

//SUBFUNCION 1(3) //LISTO
void buscarSexo(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    char resp[2];
    printf("QUE SEXO DESEA BUSCAR? (M O F)\n");
    fflush(stdin);
    scanf(" %s",resp);
    //Accedemos a la lista de la respuesta
    list* aux = searchMap(mapaSexo,resp);
    //SI LA LISTA NO EXISTE
    if(aux == NULL){
        printf("NO SE HAN INGRESADO PACIENTES DE SEXO TIPO %s",resp);
        fflush(stdin);
        getch();
        return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
    }
    //Accedemos a la primera ficha de la lista
    Ficha* auxF = list_first(aux);
    do{
        //VEMOS SI LA RESPUESTA Y SU SEXO SON EL MISMO
        if(strcmp(resp,auxF->sexo)== 0){
            //VEMOS SI EL PACIENTE ESTA EN LA LISTA ALTA
            if(searchMap(alta,auxF->nombre)){
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s | SALA: %s | COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : SI |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
            else{
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s |SALA : %s| COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : NO |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
        }
        //Avanzamos en la lista al siguiente
        auxF = list_next(aux);
        fflush(stdin);
    }while(auxF);
    printf("CARGA COMPLETADA PRESIONE ENTER PARA VOLVER AL MENU ANTERIOR\n");
    fflush(stdin);
    getch();
    return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
}

//Subfuncion 2(3) //LISTO
void buscarSangre(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    char resp[4];
    printf("INGRESE EL TIPO DE SANGRE DESEA BUSCAR\n");
    fflush(stdin);
    scanf(" %s",resp);
    //Accedemos a la lista de la respuesta
    list* aux = searchMap(mapaSangre,resp);
    //SI LA LISTA NO EXISTE
    if(aux == NULL){
        printf("NO SE HAN INGRESADO PACIENTES DE SEXO TIPO %s",resp);
        fflush(stdin);
        getch();
        return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
    }
    //Accedemos a la primera ficha de la lista
    Ficha* auxF = list_first(aux);
    do{
        //VEMOS SI LA RESPUESTA Y SU SEXO SON EL MISMO
        if(strcmp(resp,auxF->sangre)== 0){
            //VEMOS SI EL PACIENTE ESTA EN LA LISTA ALTA
            if(searchMap(alta,auxF->nombre)){
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s | SALA: %s | COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : SI |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
            else{
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s |SALA : %s| COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : NO |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
        }
        //Avanzamos en la lista al siguiente
        auxF = list_next(aux);
        fflush(stdin);
    }while(auxF);
    printf("CARGA COMPLETADA PRESIONE ENTER PARA VOLVER AL MENU ANTERIOR\n");
    fflush(stdin);
    getch();
    return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
}

//SUBFUNCION 3(3) //LISTO
void buscarMes(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    char resp[3];
    printf("INGRESE INGRESE EL MES(NUMERO) QUE DESEA BUSCAR(FORMATO: XX)\n");
    fflush(stdin);
    scanf(" %s",resp);
    //Accedemos a la lista de la respuesta
    list* aux = searchMap(mapaMes,resp);
    //SI LA LISTA NO EXISTE
    if(aux == NULL){
        printf("NO SE HAN INGRESADO PACIENTES EN EL MES %s",resp);
        fflush(stdin);
        getch();
        return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
    }
    //Accedemos a la primera ficha de la lista
    Ficha* auxF = list_first(aux);
    do{
        //VEMOS SI LA RESPUESTA Y SU SEXO SON EL MISMO
        if(strcmp(resp,auxF->fecha->mes)== 0){
            //VEMOS SI EL PACIENTE ESTA EN LA LISTA ALTA
            if(searchMap(alta,auxF->nombre)){
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s | SALA: %s | COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : SI |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
            else{
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s |SALA : %s| COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : NO |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
        }
        //Avanzamos en la lista al siguiente
        auxF = list_next(aux);
        fflush(stdin);
    }while(auxF);
    printf("CARGA COMPLETADA PRESIONE ENTER PARA VOLVER AL MENU ANTERIOR\n");
    fflush(stdin);
    getch();
    return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
}

//SUBFUNCION 4(3) //LISTO
void buscarAno(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    char resp[5];
    printf("INGRESE EL ANNO QUE DESEA BUSCAR(FORMATO: XXXX)\n");
    fflush(stdin);
    scanf(" %s",resp);
    //Accedemos a la lista de la respuesta
    list* aux = searchMap(mapaAno,resp);
    //SI LA LISTA NO EXISTE
    if(aux == NULL){
        printf("NO SE HAN INGRESADO PACIENTES EN EL ANNO %s",resp);
        fflush(stdin);
        getch();
        return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
    }
    //Accedemos a la primera ficha de la lista
    Ficha* auxF = list_first(aux);
    do{
        //VEMOS SI LA RESPUESTA Y SU AÑO SON EL MISMO
        if(strcmp(resp,auxF->fecha->anno)== 0){
            //VEMOS SI EL PACIENTE ESTA EN LA LISTA ALTA
            if(searchMap(alta,auxF->nombre)){
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s | SALA: %s | COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : SI |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
            else{
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s |SALA : %s| COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : NO |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
        }
        //Avanzamos en la lista al siguiente
        auxF = list_next(aux);
        fflush(stdin);
    }while(auxF);
    printf("CARGA COMPLETADA PRESIONE ENTER PARA VOLVER AL MENU ANTERIOR\n");
    fflush(stdin);
    getch();
    return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
}

//SUBFUNCION 5(3) //LISTO
void buscarComuna(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    char resp[20];
    printf("INGRESE LA COMUNA QUE DESEA BUSCAR\n");
    fflush(stdin);
    scanf(" %[^\n]s",resp);
    //Accedemos a la lista de la respuesta
    list* aux = searchMap(mapaComuna,resp);
    //SI LA LISTA NO EXISTE
    if(aux == NULL){
        printf("NO SE HAN INGRESADO PACIENTES DE LA COMUNA DE %s",resp);
        fflush(stdin);
        getch();
        return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
    }
    //Accedemos a la primera ficha de la lista
    Ficha* auxF = list_first(aux);
    do{
        //VEMOS SI LA RESPUESTA Y SU AÑO SON EL MISMO
        if(strcmp(resp,auxF->comuna)== 0){
            //VEMOS SI EL PACIENTE ESTA EN LA LISTA ALTA
            if(searchMap(alta,auxF->nombre)){
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s | SALA: %s | COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : SI |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
            else{
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s |SALA : %s| COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : NO |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
        }
        //Avanzamos en la lista al siguiente
        auxF = list_next(aux);
        fflush(stdin);
    }while(auxF);
    printf("CARGA COMPLETADA PRESIONE ENTER PARA VOLVER AL MENU ANTERIOR\n");
    fflush(stdin);
    getch();
    return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
}

//SUBFUNCION 6(3) //LISTO
void buscarPrev(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    char resp[20];
    printf("INGRESE LA PREVISION MEDICA QUE DESEA BUSCAR\n");
    fflush(stdin);
    scanf(" %[^\n]s",resp);
    //Accedemos a la lista de la respuesta
    list* aux = searchMap(mapaPrev,resp);
    //SI LA LISTA NO EXISTE
    if(aux == NULL){
        printf("NO SE HAN INGRESADO PACIENTES DE LA COMUNA DE %s",resp);
        fflush(stdin);
        getch();
        return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
    }
    //Accedemos a la primera ficha de la lista
    Ficha* auxF = list_first(aux);
    do{
        //VEMOS SI LA RESPUESTA Y SU AÑO SON EL MISMO
        if(strcmp(resp,auxF->prevMedica)== 0){
            //VEMOS SI EL PACIENTE ESTA EN LA LISTA ALTA
            if(searchMap(alta,auxF->nombre)){
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s | SALA: %s | COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : SI |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
            else{
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s |SALA : %s| COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : NO |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
        }
        //Avanzamos en la lista al siguiente
        auxF = list_next(aux);
        fflush(stdin);
    }while(auxF);
    printf("CARGA COMPLETADA PRESIONE ENTER PARA VOLVER AL MENU ANTERIOR\n");
    fflush(stdin);
    getch();
    return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
}

//SUBFUNCION 7(3) //LISTO
void buscarSala(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    char resp[3];
    printf("INGRESE EL NUMERO SALA QUE DESEA BUSCAR\n");
    fflush(stdin);
    scanf(" %s",resp);
    //Accedemos a la lista de la respuesta
    list* aux = searchMap(mapaSala,resp);
    //SI LA LISTA NO EXISTE
    if(aux == NULL){
        printf("NO SE HAN INGRESADO PACIENTES EN LA SALA %s",resp);
        fflush(stdin);
        getch();
        return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
    }
    //Accedemos a la primera ficha de la lista
    Ficha* auxF = list_first(aux);
    do{
        //VEMOS SI LA RESPUESTA Y SU AÑO SON EL MISMO
        if(strcmp(resp,auxF->sala)== 0){
            //VEMOS SI EL PACIENTE ESTA EN LA LISTA ALTA
            if(searchMap(alta,auxF->nombre)){
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s | SALA: %s | COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : SI |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
            else{
                //Imprimimos la data de forma ordenada
                printf("| NOMBRE : %s | RUT:  %s  | SEXO: %s |SALA : %s| COMUNA; %s \n| PREVICION M : %s | T.SANGRE: %s | MES DE I: %s | ANNO DE I: %s | DAD@ DE ALTA? : NO |\n",auxF->nombre,auxF->rut,auxF->sexo,auxF->sala,auxF->comuna,auxF->prevMedica,auxF->sangre,auxF->fecha->mes,auxF->fecha->anno);
                printf("\n");
                fflush(stdin);
            }
        }
        //Avanzamos en la lista al siguiente
        auxF = list_next(aux);
        fflush(stdin);
    }while(auxF);
    printf("CARGA COMPLETADA PRESIONE ENTER PARA VOLVER AL MENU ANTERIOR\n");
    fflush(stdin);
    getch();
    return subMenuGrupal(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
}

//FUNCION DAR DE ALTA(4) //LISTO
void darAlta(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    char nombre[50];
    char rut[12];
    //Pedimos el rut y nombre de la persona que se desea dar de alta
    printf("PORFAVOR INGRESE EL NOMBRE DE LA PERSONA\n");
    fflush(stdin);
    scanf("%[^\n]s",nombre);
    printf("PORVAFOR INGRESE EL RUT DE LA PERSONA(FORMATO XXXXXXXX-X)\n");
    fflush(stdin);
    scanf("%[^\n]s",rut);
    //CREAMOS UN AUX PARA GUARDAR LA FICHA DE LA PERSONA DADA DE ALTA
    Ficha* aux = searchMap(mapaNombre,nombre);
    //SI LA PERSONA NO ESTA
    if(aux == NULL){
        printf("LA PERSONA NO SE ENCUENTRA EN LA BASE DE DATOS PRESIONE ENTER PORFAVOR\n");
        getch();
        return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
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
        return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
    }
}



//FUNCION CARGAR ARCHIVO(5) //LISTO
void CargarArchivo(Map *mapaNombre, Map *mapaRut, Map *mapaSexo, Map *mapaSangre, Map *mapaMes, Map *mapaAno, Map *mapaComuna,Map* mapaSala,Map* mapaPrev,Map *alta){
    system("@cls||clear");
    FILE *fp = fopen("pacientes.csv","r");
    char linea[1024];
    if (fp == NULL){
        printf("ARCHIVO NO ENCONTRADO\n PRESIONE ENTER PARA VOLER AL MENU PRINCIPAL\n");
        getch();
        return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
    }
    else{
        //CONTAMOS LAS LINEAS DEL ARCHIVO
        printf("ARCHIVO ENCONTRADO\n");
        while(fgets(linea,1024,(FILE*)fp)!= NULL){
            Ficha *ficha =  malloc (sizeof(Ficha)); //Se crea el tipo ficha
            //Ingresamos los datos que corresponden en orden al tipo ficha usando la funcion get_csv_field
            ficha->nombre = (char*)get_csv_field(linea,1);
            ficha->edad = atoi(get_csv_field(linea,2));
            ficha->sexo = (char*)get_csv_field(linea,3);
            ficha->rut = (char*)get_csv_field(linea,4);
            ficha->sangre = (char*)get_csv_field(linea,5);
            ficha->prevMedica = (char*)get_csv_field(linea,6);
            ficha->comuna = (char*)get_csv_field(linea,7);
            ficha->diagnostico = (char*)get_csv_field(linea,8);
            ficha->sala = (char*)get_csv_field(linea,9);
            char* prefecha =(char*)get_csv_field(linea,10);
            ficha->fecha = separarFecha(prefecha);
            if(ficha->edad != NULL){
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
                printf("|SALA : %s                         |\n",ficha->sala);
                printf("|MES  : %s                         |\n",ficha->fecha->mes);
                printf("|ANNO: %s                       |\n",ficha->fecha->anno);
                printf("|DIA: %s                          |\n",ficha->fecha->dia);
                printf("|*********************************|\n");
                printf("PRESIONE ENTER PARA CONTINUAR\n");
                fflush(stdin);
                getch();
                //FUNCION PARA POBLAR MAPAS GRUPALES
                insertarMapaGrupal(mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,ficha);
                //FINALMENTE INGRESAMOS LAS FICHAS A LOS MAPAS INDIVIDUALES
                insertMap(mapaNombre,ficha->nombre,ficha);
                insertMap(mapaRut,ficha->rut,ficha);
            }
        }
    }
    fclose(fp);
    return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
}


//FUNCION EXPORTAR ARCHIVO(6) //LISTO
void exportarArchivo(Map* mapaNombre,Map* mapaRut,Map* mapaSexo,Map* mapaSangre,Map* mapaMes,Map* mapaAno,Map* mapaComuna,Map* mapaSala,Map* mapaPrev,Map* alta){
    system("@cls||clear");
    //PEDIMOS QUE INGRESEN EL NOMBRE QUE DESEA DEL ARCHIVO A GUARDAR
    char nombreA[30];
    printf("PORFAVOR NOMBRE EL ARCHIVO A EXPORTAR (USE _ EN VEZ DE ESPACIOS Y SIN .CSV y MAX 25 CAR) \n[EVITE USAR EL NOMBRE PACIENTES]\n");
    fflush(stdin);
    scanf(" %[^\n]s",nombreA);
    //Le añadimos el .csv concatenandolo
    strcat(nombreA,".csv");
    //Creamos el puntero File y el archivo a escribir
    FILE* fw = fopen(nombreA,"w");
    //Ingresamos al la primera ficha mapa nombres para escribir la data de los pacientes hasta que ya no queden
    Ficha* aux = firstMap(mapaNombre);
    //SI NO HAY DATOS EN EL MAPA
    if(aux == NULL){
        fclose(fw);
        printf("NO SE HAN INGRESADO PERSONAS LA BASE DE DATOS DEL PROGRAMA\n PRESIONE ENTER PARA VOLVER AL MENU PRINCIPAL\n");
        fflush(stdin);
        getch();
        return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
    }
    //INGRESAMOS LA PRIMERA LINEA DE LOS PARAMETROS
    fprintf(fw,"NOMBRE,EDAD,SEXO,RUT,TIPO SANGRE,PREV MEDICA,COMUNA,DIAGNOSTICO,SALA,FECHA\n");
    fflush(fw);
    //DESPUES INGRESAMOS LOS DATOS QUE CORRESPONDEN
    do{
        fprintf(fw,"%s,%d,%s,%s,%s,%s,%s,%s,%s,%s/%s/%s\n",aux->nombre,aux->edad,aux->sexo,aux->rut,aux->sangre,aux->prevMedica,aux->comuna,aux->diagnostico,aux->sala,aux->fecha->dia,aux->fecha->mes,aux->fecha->anno);
        printf("VMO BIEN\n");
        aux = nextMap(mapaNombre);
    }while(aux);
    //Cerramos el archivo
    fclose(fw);
    return MostrarMenu(mapaNombre,mapaRut,mapaSexo,mapaSangre,mapaMes,mapaAno,mapaComuna,mapaSala,mapaPrev,alta);
}


//FUNCIONES DE USO MULTIPLE Y UTILIDADES //LISTO
Fecha* separarFecha(char* prefecha){
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

//INSERTAR PACIENTE EN MAPAS GRUPALES(FUNCIONES 1 Y 5) LISTO
void insertarMapaGrupal(Map* mapaSexo,Map* mapaSangre,Map* mapaMes,Map* mapaAno,Map* mapaComuna,Map* mapaSala,Map* mapaPrev,Ficha *ficha){
    //SI LOS MAPAS YA TIENEN SU LISTA INGRESAMOS TODO PASO A PASO
    //MAPA SALA
    if(searchMap(mapaSala,ficha->sala)){
        list* aux = searchMap(mapaSala,ficha->sala); //INGRESAMOS A LA LISTA DEL MAPA
        list_push_front(aux,ficha); //INSERTAMOS LA FICHA A LA LISTA
    }
    else{
        list* aux = list_create_empty();   //CREAMOS UNA LISTA VACIA
        list_push_front(aux,ficha); //INGRESAMOS LA FICHA A LA LISTA
        insertMap(mapaSala,ficha->sala,aux); //INSERTAMOS LA LISTA EN EL LUGAR DEL MAPA CON CLAVE EL AÑO
    }
    //MAPA ANNO
    //SI EL ANNO ESTA EN EL MAPA
    if(searchMap(mapaAno,ficha->fecha->anno)){
        list* aux = searchMap(mapaAno,ficha->fecha->anno); //INGRESAMOS A LA LISTA DEL MAPA
        list_push_front(aux,ficha); //INSERTAMOS LA FICHA A LA LISTA
    }
    else{
        list* aux = list_create_empty();   //CREAMOS UNA LISTA VACIA
        list_push_front(aux,ficha); //INGRESAMOS LA FICHA A LA LISTA
        insertMap(mapaAno,ficha->fecha->anno,aux); //INSERTAMOS LA LISTA EN EL LUGAR DEL MAPA CON CLAVE EL AÑO
    }
    //MAPA MES
    if(searchMap(mapaMes,ficha->fecha->mes))
    {
        list* aux = searchMap(mapaMes,ficha->fecha->mes);
        list_push_front(aux,ficha);
    }
    else
    {
        list* aux = list_create_empty();
        list_push_front(aux,ficha);
        insertMap(mapaMes,ficha->fecha->mes,aux); //INSERTAMOS LA LISTA EN EL LUGAR DEL MAPA
    }
    //MAPA COMUNA
    if(searchMap(mapaComuna,ficha->comuna))
    {
        list* aux = searchMap(mapaComuna,ficha->comuna); //INGRESAMOS A LA LISTA DEL MAPA
        list_push_front(aux,ficha);
    }
    if(!searchMap(mapaComuna,ficha->comuna))
    {
        list* aux = list_create_empty();
        list_push_front(aux,ficha);
        insertMap(mapaComuna,ficha->comuna,aux); //INSERTAMOS LA LISTA EN EL LUGAR DEL MAPA
    }
    //MAPA PREVISION M
    if(searchMap(mapaPrev,ficha->prevMedica))
    {
        list* aux = searchMap(mapaPrev,ficha->prevMedica); //INGRESAMOS A LA LISTA DEL MAPA
        list_push_front(aux,ficha);
    }
    if(!searchMap(mapaPrev,ficha->prevMedica))
    {
        //Creamos la lista y la insertamos
        list* aux = list_create_empty();
        list_push_front(aux,ficha);
        insertMap(mapaPrev,ficha->prevMedica,aux);
    }
    //MAPA SANGRE
    if(searchMap(mapaSangre,ficha->sangre))
    {
        list* aux = searchMap(mapaSangre,ficha->sangre); //INGRESAMOS A LA LISTA DEL MAPA
        list_push_front(aux,ficha);
    }
    if(!searchMap(mapaSangre,ficha->sangre))
    {
        list* aux = list_create_empty();
        list_push_front(aux,ficha);
        insertMap(mapaSangre,ficha->sangre,aux); //INSERTAMOS LA LISTA EN EL LUGAR DEL MAPA
    }
    //MAPA SEXO
    if(searchMap(mapaSexo,ficha->sexo)){
        list* aux = searchMap(mapaSexo,ficha->sexo); //INGRESAMOS A LA LISTA DEL MAPA
        list_push_front(aux,ficha);
    }
    if(!searchMap(mapaSexo,ficha->sexo)){
        list* aux = list_create_empty();
        list_push_front(aux,ficha);
        insertMap(mapaSexo,ficha->sexo,aux); //INSERTAMOS LA LISTA EN EL LUGAR DEL MAPA
    }
}


//FUNCIONES DE MULTIPLE USO Y UTILIDADES
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




