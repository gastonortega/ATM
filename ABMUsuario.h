#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LOGIN 3 //Maxima cantidad de intentos de inicio de sesion
#define PATH_LOGIN 0 //Indice del archivo login.dat
#define PATH_LOG 1
<<<<<<< HEAD
#define PATH_HISTORICO 2
#define PATH_TEMPORAL 3
=======
#define M_READ_TEXTO 0 //eesto se  va a borrar
#define M_WRITE_TEXTO 1 //eesto se  va a borrar
#define M_READ_BINARIO 2 //eesto se  va a borrar
#define M_WRITE_BINARIO 3 //eesto se  va a borrar
>>>>>>> origin/master

void logueoPlataforma(char**, int);
void altaUsuarioPlataforma(char**, int);
void listarUsuarios(char **, int);
void bajaUsuarioPlataforma(char**, int, int, int);
void modificarJerarquia(char**, int);

typedef struct {
    char nombreUsuario[10];
    char passwordUsuario[10];
    int jerarquia;
} RegUser;
