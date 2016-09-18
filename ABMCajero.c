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
    int Cuentaori;
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
            strcpy(Temp.nombreUsuario,User);
            strcpy(Temp.passwordUsuario,Password);
            Temp.jerarquia = 2;
            fseek(Arch, 0, SEEK_END);
            fseek(Arch, 0, SEEK_CUR);
            fwrite(&Temp,sizeof(RegUser),1,Arch);

            return(7);
        }

             printf("\n Ingrese Numero de cuenta:");
             scanf('%d',Cuentaori);
            strcpy(Temp.nombreUsuario,User);
            strcpy(Temp.passwordUsuario,Password);
            Temp.jerarquia = 2;
            Temp.cuenta = Cuentaori;
            fseek(Arch, 0, SEEK_END);
            fseek(Arch, 0, SEEK_CUR);
            fwrite(&Temp,sizeof(RegUser),1,Arch);





    }
 fclose(Arch);
 free(User);
 free(Password);
 return(0);
}
/*
RETORNOS INGRESO ARCH CAJA DE AHORRRO
RETURN 9 = ARCHIVO CAJA DE AHORRO  INACCESIBLE

*/
int Deposito_Archivo_CajaAhorro(char ** a, int b, int cue)
{
    FILE *ArchCaja;
    int monto=0;
    CajaAhorro CajaTemp;
    ArchCaja = fopen(*(a+b),"rb+");
    if(ArchCaja==NULL)
    {
             ArchCaja = fopen(*(a+b),"wb+");
             if(ArchCaja==NULL)
             {
                 printf("\n no se puede abrir archivo caja de ahorro");
                 getch();
                 return(9);
             }

    }
    printf("\n Ingrese monto  a depositar: ");
    scanf("%.2f");
    fseek(ArchCaja,0,SEEK_SET);
    fread(&CajaTemp.CuentaArch,sizeof(CajaAhorro),1,ArchCaja);

  //despues sacar
  return 0;
}
