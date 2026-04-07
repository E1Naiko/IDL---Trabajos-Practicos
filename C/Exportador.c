#include <stdio.h>
#include <string.h>
int exportador(int mi, int md, int bi, int bd,
               int dataXi[], int dataXd[],
               int dataYi[], int dataYd[],
               int size)
{
    FILE *datasheet;
    char nombre[50];
    char nombreCompleto[60];

    printf("\nExportar datos a .txt\n");
    printf("\nIngrese un nombre para el archivo:\n");

    scanf("%49s", nombre);

    sprintf(nombreCompleto, "%s.txt", nombre);

    datasheet = fopen(nombreCompleto, "w");

    if (datasheet == NULL) {
        printf("Error al crear el archivo\n");
        return 0;
    }

    // m y b
    fprintf(datasheet, "%i.%i;%i.%i\n", mi, md, bi, bd);

    // datos
    for (int i = 0; i < size; i++) {
        fprintf(datasheet, "%i.%i;%i.%i\n",
                dataXi[i], dataXd[i],
                dataYi[i], dataYd[i]);
    }

    fclose(datasheet);

    printf("\nArchivo exportado correctamente\n");

    return 1;
}