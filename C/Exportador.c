#include <stdio.h>
#include <string.h>
#include "Exportador.h"

int exportador(int mi, int md, int bi, int bd, int dataXi[], int dataXd[], int dataYi[], int dataYd[], int size)
{
    FILE *datasheet;

    printf("\nExportar datos a .txt\n");

    datasheet = fopen("datos.txt", "w");

    if (datasheet == NULL) {
        printf("Error al crear el archivo\n");
        return 0;
    }

    // Escribir datos
    fprintf(datasheet, "%i.%i;%i.%i;", mi, md, bi, bd);

    for (int i = 0; i < size; i++) {
        fprintf(datasheet, "%i.%i;%i.i", dataXi[i], dataXd[i], dataYi[i], dataXd[i]);
    }

    fclose(datasheet);

    printf("\nArchivo exportado correctamente\n");

    return 1;
}
