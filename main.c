#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LOGIN 3 //Maxima cantidad de intentos de inicio de sesion
#define PATH_LOGIN 0 //Indice del archivo login.dat
#define PATH_LOG 1
#define PATH_HISTORICO 2
#define PATH_TEMPORAL 3

typedef struct {
    char nombreUsuario[10];
    char passwordUsuario[10];
    int jerarquia;
} RegUser; //Estructura para leer de login.dat y ademas almacenar la sesion

int contarPaths(); //Devuelve la cantidad de paths en el archivo path.txt
void almacenarPaths(char**); //Almacena en un vector de punteros los paths
void registroAccion(char**, int, char*);

void main() {
    int cantidadPath = 0;
    char **paths;
    int opcion;
    FILE *archRegistro;
    RegUser userLogueado;
    cantidadPath = contarPaths();
    printf("Se encontraron %d paths.\n", (cantidadPath+1));
    paths = (char**)malloc(cantidadPath*sizeof(char*));
    almacenarPaths(paths);
    listarUsuarios(paths, PATH_LOGIN);
    logueoPlataforma(paths, PATH_LOGIN);
    printf("\nIngrese la opcion");
    scanf("%d", &opcion);
    switch(opcion) {
        case 1:
        altaUsuarioPlataforma(paths, PATH_LOGIN);
        break;
        case 2:
        bajaUsuarioPlataforma(paths, PATH_LOGIN, PATH_HISTORICO, PATH_TEMPORAL);
        break;
    }
}

int contarPaths() {
    FILE *archivo;
    int contador = 0;
    char lineaPath[80];
    archivo = fopen("path.txt", "r");
    if (archivo==NULL) {
        printf("\nNo se pudo abrir el archivo de Paths.");
        exit(1);
    }
    fgets(lineaPath, 80, archivo); //Se almacena en lineaPath la linea leida
    while(!feof(archivo)) {
        contador++;
        fgets(lineaPath, 80, archivo);
    } //Mientras no sea el fin del archivo, se lee linea por linea y se va aumentando el contador.
    fclose(archivo);
    return (contador-1); //Devuelve contador-1 porque el indice debe empezar en 0
}

void almacenarPaths(char **dpPaths) {
    FILE *archivo;
    char pathTemp[80] = "\0"; //El "\0" esta medio al pedo
    char *pathPath;
    char *modo;
    int lenCadena = 0;
    int contador = 0;
    archivo = fopen("path.txt", "r");
    fgets(pathTemp, 80, archivo); //Almaceno en pathTemp la linea leida
    while(!feof(archivo)) {
        printf("Se guardo el path: %s", pathTemp);
        lenCadena = strlen(pathTemp); //guardo en lenCadena la longitud en caracteres de la linea leida
        *(dpPaths+contador) = (char*)malloc(sizeof(char)*lenCadena);
        /*
        En el vector de punteros, en la posicion de contador (que va a ir incrementando) aloco memoria para una cadena del largo que
        la que acaba de leer en el archivo.
        */
        pathTemp[lenCadena-1]='\0';
        /*
        Como el fgets me toma el carater nueva linea "\n" debo volver un espacio atras y reemplazarlo por el caracter terminal "\0"
        de lo contrario, el fopen no me va a abrir el archivo porque toma \n como parte de la ruta.
        */

        strcpy(*(dpPaths+contador), pathTemp); //guardo en el vector, en la posicion contador, el path
        contador++;//aumento el contador
        fgets(pathTemp, 80, archivo); //vuevo a leer
    }
    fclose(archivo);
}

void registroAccion(char **a, int c, char *b) {
    FILE *archivo;
    time_t t;
    struct tm *tiempo;
    t=time(NULL);
    tiempo=localtime(&t);
    archivo = fopen(*(a+c), "r+");
    if (archivo==NULL) {
        printf("\nNo se encontro el archivo de registro. Se creara uno.");
        archivo = fopen(*(a+c), "w+");
        if (archivo == NULL) printf("\nNo se pudo crear el archivo");
            else printf("\nArchivo creado exitosamente.");
    }
    fseek(archivo, 0, SEEK_END);
    fprintf(archivo,"\nFecha %02d/%02d/%02d Hora %02d:%02d %s",
    tiempo->tm_mday,tiempo->tm_mon+1,tiempo->tm_year+1900,tiempo->tm_hour,tiempo->tm_min,b);
    fclose(archivo);
}
