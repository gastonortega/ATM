#include "ABMUsuario.h"
#include "Logger.h"
#define PATH_TRANSFERENCIAS 4
#define PATH_CAJADEAHORRO   5
typedef struct{
char NombreUsuario[10];
int CuentaOrigen;
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

int AltaUsuarioCliente(char **, int);
int Consulta_Archivo_CajaAhorro(char **, int);
int Consulta_Archivo_Transferenci(char **, int);
