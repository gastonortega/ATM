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
            printf("\nUltimo leido:%s", userExistente.nombreUsuario);
            printf("\nIngresado:%s", nuevoUser.nombreUsuario);
            printf("\nPassword guardado:%s", nuevoUser.passwordUsuario);
            printf("\nJerrarquia %d", nuevoUser.jerarquia);
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
    printf("Archivo cerrado");
}
