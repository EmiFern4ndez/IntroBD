#include <stdio.h>
#include <stdlib.h>

typedef struct socio{
    int num;
    int dni;
    char apeynom[40];
    char domicilo[20];
    char nacimiento[10];
    char asociacion[10];
}Socio;

typedef struct lista{
    Socio dato;
    struct lista *sig;
} *Lista;

void leerSocio(Socio *s){
    printf("Ingrese el numero:");
    scanf("%d", &s->num);
    printf("Ingrese el dni:");
    scanf("%d", &s->dni);
    printf("Ingrese el Apellido y Nombre:");
    scanf("%s", s->apeynom);
    printf("Ingrese el Domicilio:");
    scanf("%s", s->domicilo);
    printf("Ingrese el nacimiento:");
    scanf("%s", s->nacimiento);
    printf("Ingrese el Apellido y Nombre:");
    scanf("%s", s->apeynom);
    printf("Ingrese el Apellido y Nombre:");
    scanf("%s", s->asociacion);
}

int existe(char nomArch[20], int num){
    FILE *arch;
    arch = fopen(nomArch, "rb");
    int ok = 0;
    Socio socio;
    while (fread(&socio, sizeof(Socio), 1, arch) && ok != 1){
        if (socio.num != num){
            ok++;
            fclose(nomArch);
        }
    }
    fclose(nomArch);
    return ok;
}

void alta(char nomArch[20], Socio s){
    FILE *arch;
    arch = fopen(nomArch, "ab");
    if (arch != NULL){
        Socio s;
        if (!existe(nomArch, s.num)){
            fwrite(&s, sizeof(Socio), 1, arch);
        }else
            printf("El socio ya existe\n");
    }else   
        printf("Error al crear el archivo\n");
    fclose(arch);
}

void baja(char nomArch[20], int num){
    FILE *arch;
    arch = fopen(nomArch, "ab");
    Socio socio;
    int ok = 0;
    if (existe(nomArch, num)){
        while (fread(&socio, sizeof(Socio), 1, arch)){
            if (socio.num == num){
                socio.num = 0;
                fseek(arch, -sizeof(Socio), SEEK_CUR); // Retrocede al inicio del registro
                fwrite(&socio, sizeof(Socio), 1, arch);
                fclose(nomArch);
            }
        }
    }else
        fclose(nomArch);
}

void generarLista(char nomArch[20]){
    Lista l = NULL;
    FILE *arch;
    Socio s;
    arch = fopen(nomArch, "rb");
    while (fread(&s, sizeof(Socio), 1, arch)){
        agregarAdelante(&l, s);
    }
    fclose(nomArch);
}

Lista crearNodo(int num){
    Lista nue = (Lista)malloc(sizeof(struct lista));
    nue ->dato = num;
    nue ->sig = NULL;
    return nue;
}

void agregarAdelante (Lista *l, int num){
    Lista nue = malloc(sizeof(Lista));
    nue->dato = num;                                
    nue->sig = *l;
    *l = nue;
}

int main(int argc, char const *argv[]){
    char nomArch[20];
    char opcion;
    printf("Ingrese el nombre del archivo:");
    scanf("%s", nomArch);
    Socio s;
    int numSocio;
    printf("        MENU        \n");
    printf("a) Dar de alta un socio\n");
    printf("b) Dar de baja un socio\n");
    printf("c) Buscar socio\n");
    printf("d) Listar socio\n");
    printf("x) Salir\n");
    while(opcion != 'x'){
        switch (opcion){
        case 'a':{
            leerSocio(&s);
            alta(nomArch, s);
        }

        case 'b':{
            printf("Ingrese el numero del socio que quieres eliminar:");
            scanf("%d", &numSocio);
            baja(nomArch, numSocio);
            break;
        }

        case 'c':{
            printf("Ingrese el numero del socio que quieres buscar:");
            scanf("%d", &numSocio);
            if (existe(nomArch, numSocio)){
                printf("Existe el socio con numero: %d\n", numSocio);
            }else
                printf("No existe el socio\n");
            break;
        }

        case 'd':{
            generarLista(nomArch);
        }

        case 'x':
            break;
        }
        printf(" Opcion: ");
        scanf(" %c", &opcion);
    }
    return 0;

}
