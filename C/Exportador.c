#include <stdio.h>
#include <string.h>

int exportador(int m, int b, int dataX[], int dataY[], int size)
{
    FILE *datasheet;
    char nombre[50];
    char nombreCompleto[60];

    printf("\nExportar datos a .txt\n");
    printf("\nIngrese un nombre para el archivo:\n");

    scanf("%49s", nombre);  // evita overflow

    // Agregar extensión .csv
    sprintf(nombreCompleto, "%s.csv", nombre);

    datasheet = fopen(nombreCompleto, "w");

    if (datasheet == NULL) {
        printf("Error al crear el archivo\n");
        return 0;
    }

    // Escribir datos
    fprintf(datasheet, "%i;%i;", m, b);

    for (int i = 0; i < size; i++) {
        fprintf(datasheet, "%i;%i;", dataX[i], dataY[i]);
    }

    fclose(datasheet);

    printf("\nArchivo exportado correctamente\n");

    return 1;
}