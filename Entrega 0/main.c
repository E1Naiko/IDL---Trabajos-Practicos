#include <stdio.h>
#include "Grupo03f.c"
#include "Grupo03g.c"
#include "Grupo03h.c"

/* ATENCION PARA USAR ESTE MAIN HAY QUE RENOMBRAR EL ARCHIVO A main.c, LE CAMBIAMOS EL NOMBRE PARA RESPETAR LOS TERMINOS DE ENTREGA */
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
          if (Grupo03f())
            printf("\nERROR INCISO F");
        break;
        case 2:
            if (Grupo03g())
                printf("\nERROR INCISO G");
            break;
        case 3:
            if (Grupo03h())
                printf("\nERROR INCISO H");
            break;
        default:
          printf("\nError valor no valido.");
      }
    
      printf("\n\n-----------------");
    } while (act != 0);
    return 0;
}
