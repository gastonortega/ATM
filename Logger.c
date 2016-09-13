#include "Logger.h"




/*
char c[3]= Referido al sistema ADM,CAJ,USER.
char d[100] = detalle accion.

*/
void Logueo(char **a,char b ,char c , char d)
{
   FILE *Arch;
   time_t t;
    struct tm *tiempo;
    t=time(NULL);
    tiempo=localtime(&t);
    Arch = fopen(*(a+c), "r+");
    if (archivo==NULL) {
        printf("\nNo se encontro el archivo de registro. Se creara uno.");
        Arch = fopen(*(a+c), "w+");
        if (archivo == NULL) printf("\nNo se pudo crear el archivo");
            else printf("\nArchivo creado exitosamente.");
    }
    fseek(Arch, 0, SEEK_END);
    fprintf(archivo,"\nFecha %02d/%02d/%02d Hora %02d:%02d %s %s",
    tiempo->tm_mday,tiempo->tm_mon+1,tiempo->tm_year+1900,tiempo->tm_hour,tiempo->tm_min,c,d);
    fclose(Arch);

}
int contarPaths(void) {
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
