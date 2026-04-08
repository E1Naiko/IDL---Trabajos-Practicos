#include <stdio.h>
#include "IncisoF.c"
#include "IncisoG.c"
#include "IncisoH.c"

int main() {

    printf("Programa iniciado correctamente.\n");
    int act;
    do {
        printf("\n Operaciones disponibles:");
        printf("\n -  1: IncisoF.");
        printf("\n -  2: IncisoG.");
        printf("\n -  3: IncisoH.");
        printf("\n -  0: Salir.");
        printf("\nIngrese una opcion:");

        scanf("%d", &act);
        getchar();

        switch (act) {
        case 0:
          break;
        case 1:
          if (IncisoF())
            printf("\nERROR INCISO F");
        break;
        case 2:
            if (IncisoG())
                printf("\nERROR INCISO G");
            break;
        case 3:
            if (IncisoH())
                printf("\nERROR INCISO H");
            break;
        default:
          printf("\nError valor no valido.");
      }
    
      printf("\n\n-----------------");
    } while (act != 0);
    return 0;
}
