#include "ABMCajero.h"
/*retornos AltaUsuarioCliente
   return 9 = MEMORIA INSUFICIENTE
   return 8 = ARCHIVO INACCESIBLE
   return 7 = USUARIO EXISTENTE PREGUNTAR POR CAMBIO DE CATEGORIA.
   return 0 = USUARIO AGREGADO EXITOSAMENTE
*/
int AltaUsuarioCliente(char **a, int b){
    FILE *Arch;
    RegUser Temp;
    char *User;
    char *Password;
    int Cuenta;
    User = (char*)calloc(sizeof(char),10);
    Password = (char*)calloc(sizeof(char),10);
    if(User==NULL || Password==NULL)
    {
        printf("\n No hay memoria disponible.");
        getch();
        return(9);
    }
    fflush(stdin);
    printf("\n Ingrese Usuario");
    gets(User);
    fflush(stdin);
    printf("\n Ingrese Contraseña");
    gets(Password);
    fflush(stdin);
    Arch = fopen(*(a+b),"rb+");
    if(Arch==NULL)
    {
        printf("\n No se puede leer archivo Usuarios.");
        getch();
        return(8);
    }
    else
    {
      fread(&Temp.nombreUsuario,sizeof(RegUser),1,Arch);
      while(!feof(Arch) && (strcmp(Temp.nombreUsuario,User)!=0))
      {
        fread(&Temp.nombreUsuario,sizeof(RegUser),1,Arch);
      }
        if(strcmp(Temp.nombreUsuario,User)==0)
        {
            printf("\nUsuario Existente.");
            getch();
            return(7);
        }
        else{
             printf("\n Ingrese Numero de cuenta:");
             scanf('%d',Cuenta);
            strcpy(Temp.nombreUsuario,User);
            strcpy(Temp.passwordUsuario,Password);
            Temp.jerarquia = 2;
            Temp.Cuenta = Cuenta;
            fseek(archivo, 0, SEEK_END);
            fseek(archivo, 0, SEEK_CUR);
            fwrite(&Temp,sizeof(RegUser),1,Arch);

        }
    }
 fclose(Arch);
 free(User);
 free(Password);
 return(0);
}
