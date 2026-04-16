#include <stdio.h>
#include <stdint.h>

#define B 15
#define DECIMALES 100000

// convierte fracción Q a decimal (5 decimales)
int qFracToDecimal(int fracQ) {
    return (fracQ * DECIMALES) >> B;
}

// imprime un número en formato decimal desde Q
void printQ(FILE *f, int32_t valorQ) {
    int signo = (valorQ < 0) ? -1 : 1;

    int64_t absVal = (valorQ < 0) ? -(int64_t)valorQ : valorQ;

    int ent = (int)(absVal >> B);
    int fracQ = (int)(absVal & ((1 << B) - 1));
    int frac = qFracToDecimal(fracQ);

    if (signo < 0)
        fprintf(f, "-%d.%05d", ent, frac);
    else
        fprintf(f, "%d.%05d", ent, frac);
}

int exportador(int mQ, int bQ,
               int dataXQ[], int dataYQ[],
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

    // =========================
    // m y b
    // =========================
    printQ(datasheet, mQ);
    fprintf(datasheet, ";");
    printQ(datasheet, bQ);
    fprintf(datasheet, "\n");

    // =========================
    // datos
    // =========================
    for (int i = 0; i < size; i++) {
        printQ(datasheet, dataXQ[i]);
        fprintf(datasheet, ";");
        printQ(datasheet, dataYQ[i]);
        fprintf(datasheet, "\n");
    }

    fclose(datasheet);

    printf("\nArchivo exportado correctamente\n");

    return 1;
}