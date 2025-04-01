#include <stdio.h>
#include <stdlib.h>

typedef struct producto{
    int numero;
    char nombre[20];
    int cantActual;
    int cantMin;
    int cantMax;
    float precio;
} Producto;

//Lee la fecha desde teclado
void leerProducto(Producto *p) {
    printf("Ingrese el numero: ");
    scanf("%d", &p->numero);
    if (p->numero != 0) {
        printf("Ingrese el nombre: ");
        scanf(" %s", p->nombre);
        printf("Ingrese la cantidad actual: ");
        scanf("%d", &p->cantActual);
        printf("Ingrese la cantidad minima: ");
        scanf("%d", &p->cantMin);
        printf("Ingrese la cantidad maxima: ");
        scanf("%d", &p->cantMax);
        printf("Ingrese el precio: ");
        scanf("%f", &p->precio);
    }
}

//Crea el arcivo con los productos
void crearArchivo(char nomArch[15]){
    FILE *arch;
    arch = fopen(nomArch, "wb");
    Producto prod;
    if (arch != NULL){
        leerProducto(&prod);
        while (prod.numero != 0){
            fwrite(&prod, sizeof(Producto), 1, arch);
            leerProducto(&prod);
        }
    }else   
        printf("Error al crear el archivo\n");
    fclose(arch);
}

//Da un alta de un producto
int altaProducto(char nomArch[15]){
    FILE *arch;
    arch = fopen(nomArch, "ab");
    Producto prod;
    int ok = 0;
    if (arch != NULL){
        leerProducto(&prod);
        fwrite(&prod, sizeof(Producto), 1, arch);
        ok = 1;
    }
    fclose(arch);
    return ok;
}

//Modifica la info de un producto con determinado codigo
int modificarProd(char nomArch[15], int codProd){
    FILE *arch;
    arch = fopen(nomArch, "rb+");
    Producto prod;
    int ok = 0;
    if (arch != NULL){
        while (fread(&prod, sizeof(Producto), 1, arch)){
            fread(&prod, sizeof(Producto), 1, arch);
            if (prod.numero == codProd){
                leerProducto(&prod);
                fseek(arch, -sizeof(Persona), SEEK_CUR);    // Mueve el puntero al inicio del registro
                fwrite(&p, sizeof(Persona), 1, arch);   // Escribe los nuevos datos
                ok = 1;
            }
        }
    }
    fclose(arch);
    return ok;
}

//Elimina logicamente un producto con un determinado codigo
int eliminarProdLog(char nomArch[15], int codProd){
    FILE *arch;
    arch = fopen(nomArch, "rb+");
    Producto prod;
    int ok = 0;
    if (arch != NULL){
        while (fread(&prod, sizeof(Producto), 1, arch)){
            if (prod.numero == codProd){
                prod.numero = 0;    //Marco el codigo de producto para saber que esta eliminado
                fseek(arch, -sizeof(Persona), SEEK_CUR);    // Mueve el puntero al inicio del registro
                fwrite(&p, sizeof(Persona), 1, arch);   // Escribe los nuevos datos
                ok = 1;
            }
        }
    }
    fclose(arch);
    return ok;
}

//Crea otro archivo copiando todo los pructos que siguen sin darse de baja
void eliminarProdFis(char nomArch[15]){
    FILE *arch;
    FILE *arch2;
    arch = fopen(nomArch, "rb");
    char nombreArchivo;
    printf("Ingrese el nombre del archivo nuevo: ");
    scanf(" %s", nombreArchivo);
    arch2 = fopen(nombreArchivo, "wb");
    Producto prod;
    int cont = 0;
    if ((arch != NULL) && (arch2 != NULL)){
        while (fread(&prod, sizeof(Producto), 1, arch)){
            if (prod.numero != 0){
                fwrite(&prod, sizeof(Producto), 1, arch2);
            }else
                cont++;
        }
        printf("Se genero otro archivo con %d productos dados de baja (Ya no existen)\n", cont);
    }
    fclose(arch);
    fclose(arch2);
}

int main(int argc, char const *argv[]){
    int codProd;
    char nomArch[15];
    int opciones;
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", &nomArch);

    crearArchivo(nomArch);
    printf("        MENU        \n");
    printf("a) Dar de alta un producto\n");
    printf("b) Modificar un producto\n");
    printf("c) Eliminar un producto logicamente\n");
    printf("d) Eliminar un producto fisicamente\n");
    printf("x) Para salir\n");
    scanf(" %c", &opciones);

    while(opciones != 'x'){
        switch (opciones){
        case 'a':{
            if (altaProducto(nomArch)){
                printf("Se dio de alta el producto con exito\n");
            }else
                printf("No se logro dar de alta el producto\n");
            break;
        }

        case 'b':{
            printf("Ingresa el codigo de producto que quieres modificar:");
            scanf("%d", &codProd);
            if (modificarProd(nomArch, codProd)){
                printf("Se modifico con exito el producto con codigo %d\n", codProd);
            }else
                printf("Erro al modificar el producto\n");
            break;
        }

        case 'c':{
            printf("Ingresa el codigo de producto que quieres eliminar:");
            scanf("%d", &codProd);
            if (eliminarProdLog(nomArch, codProd)){
                printf("Se elimino con exito el producto con codigo %d\n", codProd);
            }else
                printf("Erro al eliminar el producto\n");
            break;
        }

        case 'd':{
            eliminarProdFis(nomArch);
        }

        case 'x':
            break;
        }
        printf(" Opcion: ");
        scanf(" %c", &opciones);
    }
    return 0;
}
