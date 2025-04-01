#include <stdio.h>
#include <stdlib.h>

typedef struct fecha {
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct persona {
    Fecha nacimiento;
    int dni;
    char nombre[15];
    char apellido[15];
} Persona;


//Lee la fecha desde teclado
void leerFecha(Fecha *fech){
    printf("Dia: ");
    scanf("%d", &fech->dia);
    printf("Mes: ");
    scanf("%d", &fech->mes);
    printf("Anio: ");
    scanf("%d", &fech->anio);
}

//Lee la persona desde teclado
void leerPersona(Persona *perso){
    printf("Ingrese dni: ");
    scanf("%d", &perso->dni);
    if (perso->dni != 0){
        leerFecha(&perso->nacimiento);
        printf("Ingrese nombre: ");
        scanf("%s", &perso->nombre);
        printf("Ingrese apellido: ");
        scanf("%s", &perso->apellido);
    }
}

//Crea el archivo
void crearArcivo(char nomArch[15]){
    Persona p;
    FILE *arch;
    arch = fopen(nomArch, "wb");      //Crea la variable del archivo y lo abre en forma de escritura
    if (arch == NULL) {
        perror("Error al abrir el archivo\n");
    }else{
        leerPersona(&p);        //Lee la persona
        while (p.dni != 0){
            fwrite(&p, sizeof(Persona), 1, arch);       //Lo guarda en el buffer
            leerPersona(&p);
        }
    }
    printf("Cerrando archivo...\n");
    fclose(arch);
}

//Verifica si cumple anios en un mes en concreto
int cumple (Fecha fecha, int mes){
    return fecha.mes == mes;
}

//Muestra la fecha de una persona
void mostrarFecha(Fecha fecha){
    printf("Dia: %d\n Mes %d\n Anio: %d\n", fecha.dia, fecha.mes, fecha.anio);
}

//Muestra los datos de la persona que cumple con la condicion
void mostrarPersona(Persona p){
    mostrarFecha(p.nacimiento);
    printf("Dni: %d\n Nombre %s\n Apellido: %s\n", p.dni, p.nombre, p.apellido);
}

//Recorre el archivo abierto en modo lectura y muestra info segun la condicion
void reportar(char nomArch[15]){
    FILE *arch;
    Persona p;
    int mes;
    arch = fopen(nomArch, "rb");        //Se abre el archivo en modo lectura
    printf("Ingrese el mes para verificar la BD\n");
    scanf("%d", &mes);
    while (fread(&p, sizeof(Persona), 1, arch)){        //Mientras no llegue al final del archivo
        if ((cumple(p.nacimiento, mes)) && (p.nacimiento.dia != -1)){
            mostrarPersona(p);
        }
    fclose(arch);
    }
}

void listar(char nomArch[15]){
    FILE *arch;
    Persona p;
    arch = fopen(nomArch, "rb");
    while(fread(&p, sizeof(Persona), 1, arch)){
        mostrarPersona(p);
    }
    fclose(arch);
}

int main(int argc, char const *argv[]){
    /* Menu */
    char opciones;
    char nomArch[15];
    printf("        MENU        \n");
    printf("a) Crear archivo y cargarlo\n");
    printf("b) Reportar en pantalla los datos de personas que cumplan años en un determinado mes o que no posean fecha de nacimiento\n");
    printf("c) Listar personas\n");
    printf("x) Para salir\n");
    scanf(" %c", &opciones);

    while(opciones != 'x'){
        switch (opciones){
        case 'a':{
            printf("Ingrese el nombre del archivo: ");
            scanf("%s", &nomArch);
            crearArcivo(nomArch);
            break;
        }
        
        case 'b':{
            reportar(nomArch);
            break;
        }

        case 'c':{
            listar(nomArch);
            break;
        }

        case 'x':
            break;
        }
        printf(" Opcion: ");
        scanf(" %c", &opciones);
    }
    return 0;
}
