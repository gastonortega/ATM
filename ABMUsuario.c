#include "ABMUsuario.h"

void logueoPlataforma(char **a, int b) {
    FILE *archivo;
    int logueado = 0;
    int cantidadLogueo = 0;
    int i;
    RegUser userTemporal;
    char *nombreTemporal;
    char *passwordTemporal;
    char c;
    int contador = 0;
    nombreTemporal = (char*)calloc(sizeof(char),10);
    passwordTemporal = (char*)calloc(sizeof(char),10);
    if (archivo==NULL) {
        printf("\nNo se pudo acceder al archivo de usuarios.");
    } else {
        do {
        printf("\nIntento %d de %d", cantidadLogueo+1, MAX_LOGIN);
        contador = 0;
        do {
        fflush(stdin);
        printf("\nIngrese su nombre de usuario: ");
        gets(nombreTemporal);
        } while (strlen(nombreTemporal)>9);
        printf("Ingrese su password: ");
        c = getch();
        while (c != '\r') {
            if (c == '\b') {
                if (contador > 0) {
                    contador--;
                    printf("\b \b");
                }
            }
            else {
                if (contador<10) {
                *(passwordTemporal+contador) = c;
                printf("*");
                contador++;
                }
            }
            c = getch();
        }
        archivo = fopen(*(a+b), "rb+");
        printf("\nNombre ingresado: %s", nombreTemporal);
        printf("\nPassword ingreso: %s", passwordTemporal);
        fseek(archivo, 0, SEEK_SET);
        fread(&userTemporal, sizeof(RegUser), 1, archivo);
        printf("user leido: %s", userTemporal.nombreUsuario);
            printf("%d",(strcmp(userTemporal.nombreUsuario, nombreTemporal)));
        printf("feof: %d", !(feof(archivo)));
        while(!(feof(archivo))&&(strcmp(userTemporal.nombreUsuario, nombreTemporal)!=0)) {
            printf("\n Login User leido: %s", userTemporal.nombreUsuario);
            printf("\n Passowrd User leido: %s", userTemporal.passwordUsuario);
            fread(&userTemporal, sizeof(RegUser),1,archivo);
        }
        if (!strcmp(userTemporal.nombreUsuario, nombreTemporal)) {
            if (!strcmp(userTemporal.passwordUsuario, passwordTemporal)) {
                printf("\n\n¡Bienvenido al sistema!");
                logueado = 1;
            }
        } else {
            if (strlen(passwordTemporal)==strlen(userTemporal.passwordUsuario)) printf("\nLONGITUDES IGUALES");
        }
        cantidadLogueo++;
        } while ((cantidadLogueo>=0&&cantidadLogueo<3)&&logueado==0);
        if (cantidadLogueo==3) {
            printf("\n\nHa alcanzado el limite de intentos de logueo.");
        }
    }
    fclose(archivo);
}

void altaUsuarioPlataforma(char **a, int b) {
    FILE *archivo;
    RegUser nuevoUser;
    RegUser userExistente;
    char *nombre;
    char *password;
    nombre = (char*)calloc(sizeof(char), 10);
    password = (char*)calloc(sizeof(char),10);
    fflush(stdin);
    printf("\nIngrese el nombre de usuario a crear [max 9 car.]: ");
    gets(nombre);
    fflush(stdin);
    printf("\nIngrese el password de este usuario [max 9 car.]: ");
    gets(password);
    printf("\nIngrese la jerarquia del usuario: ");
    scanf("%d", &nuevoUser.jerarquia);
    archivo = fopen(*(a+b), "rb+");
    if (archivo == NULL) {
        printf("\nNo se pudo leer el archivo de usuarios.");
    } else {
        fread(&userExistente, sizeof(RegUser), 1, archivo);
        while(!feof(archivo)&&!strcmp(nombre, userExistente.nombreUsuario)) {
            fread(&userExistente, sizeof(RegUser), 1, archivo);
        }
        if (strcmp(userExistente.nombreUsuario, nombre)==0) {
            printf("\nEste usuario ya existe en el sistema.");
        } else {
            strcpy(nuevoUser.nombreUsuario, nombre);
            strcpy(nuevoUser.passwordUsuario, password);
            userExistente.nombreUsuario[strlen(userExistente.nombreUsuario)] = '\0';
            userExistente.passwordUsuario[strlen(userExistente.passwordUsuario)] = '\0';
            fseek(archivo, 0, SEEK_END);
            fseek(archivo, 0, SEEK_CUR);
            fwrite(&nuevoUser, sizeof(RegUser),1,archivo);
            printf("\nUsuario agregado correctamente!");
            fclose(archivo);
        }
    }
    fclose(archivo);

}

void listarUsuarios(char **a, int b) {
    FILE *archivo;
    RegUser usuario;
    archivo = fopen(*(a+b), "rb");
    fseek(archivo, 0, SEEK_SET);
    fread(&usuario, sizeof(RegUser), 1, archivo);
    while(!feof(archivo)) {
        printf("\nUsuario: %s. Largo: %d", usuario.nombreUsuario, strlen(usuario.nombreUsuario));
        printf("\nPassword: %s. Largo %d", usuario.passwordUsuario, strlen(usuario.nombreUsuario));
        printf("\nJerarquia: %d", usuario.jerarquia);
        fread(&usuario, sizeof(RegUser), 1, archivo);
    }
    fclose(archivo);
}

void bajaUsuarioPlataforma(char **a, int b , int c, int d) {
    /*
    int b = login original
    int c = login historico
    int d = login temporal
    */
    FILE *archivoViejo;
    FILE *archivoNuevo;
    FILE *archivoHistorico;
    RegUser temporal;
    char *usuario;
    usuario = (char*)calloc(sizeof(char), 10);
    archivoViejo = fopen(*(a+b), "rb+");
    archivoNuevo = fopen(*(a+d), "wb");
    archivoHistorico = fopen(*(a+c), "rb+");
    fseek(archivoViejo, 0, SEEK_SET);
    fseek(archivoHistorico, 0, SEEK_SET);
    fseek(archivoNuevo, 0, SEEK_END);
    fflush(stdin);
    printf("\nIngrese el usuario que desea eliminar: ");
    gets(usuario);
    fread(&temporal, sizeof(RegUser), 1, archivoViejo);
    while(!feof(archivoViejo)) {
        if (strcmp(temporal.nombreUsuario, usuario)!=0) {
            fwrite(&temporal, sizeof(RegUser), 1, archivoNuevo);
        } else {
            fwrite(&temporal, sizeof(RegUser), 1, archivoHistorico);
        }
        fread(&temporal, sizeof(RegUser), 1, archivoViejo);
    }
    fclose(archivoViejo);
    fclose(archivoNuevo);
    fclose(archivoHistorico);
    remove(*(a+b));
    rename(*(a+d), *(a+b));
}
