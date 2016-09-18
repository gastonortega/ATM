
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include "ABMUsuario.h"
#define PATH_TRANSFERENCIAS 4
#define PATH_CAJADEAHORRO   5
typedef struct{
int CuentaArch;
int  Alias;
int  FechaTransf;
int  Saldo;
int  Monto;
}CajaAhorro;

typedef struct{
char NombreUsuario[10];
int Fecha;
int CuentaDestino;
int Alias;
int Activo;
}Transferencias;

int Deposito_Archivo_CajaAhorro(char **, int , int);
int Ingreso_Archivo_Transferenci(char **, int, int);
int AltaUsuarioCliente(char **, int);
int Consulta_Archivo_CajaAhorro(char **, int);
int Consulta_Archivo_Transferenci(char **, int);

