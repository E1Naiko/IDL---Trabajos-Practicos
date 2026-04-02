#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#define ESCALA 256
#define MAX_INT 127
#define MIN_INT -128

/*f. Escriba un programa en lenguaje de programación C que permita el ingreso de un valor expresado en notación decimal ±eee.ffff y lo convierta a representación en punto fijo de 16 bits Q(7,8).
El programa debe validar la entrada y determinar si el número ingresado está dentro del rango representable. La salida debe expresarse en Hexadecimal (0xHHHH)*/

int IncisoF() {
    char input[50]; /* el número se almacena como un array de caracteres */
    int signo = 1; /*valor para representar el signo */
    int entera = 0; /* variable para representar la parte entera del número */
    int fraccion = 0; /* variable para representar la parte fraccionaria del número */
    int divisor = 1;

    printf("Ingrese un numero (±eee.ffff): ");

    /* no se que verga hace */
    if (!fgets(input, sizeof(input), stdin)) {
        printf("Error de entrada\n");
        return 1;
    }

    int i = 0;


    /* valida el primer caracter como signo, si es negativo cambia la variable signo, si es positivo sigue de largo en el array */
    if (input[i] == '-') {
        signo = -1;
        i++;
    } else if (input[i] == '+') {
        i++;
    }

    /* si lee algo que no es un digito, corta */
    if (!isdigit(input[i])) {
        printf("Formato invalido\n");
        return 1;
    }

    /* a medida que lee digitos, los va metiendo en la parte entera (añade digito a digito multiplicando por 10) (resta el '0' debido a que son caracteres)*/
    while (isdigit(input[i]) && i<sizeof(input)) {
        entera = entera * 10 + (input[i] - '0');
        i++;
    }

    /* cuando lee el punto, comienza a completar la parte fraccionaria con el mismo proceso de arriba */
    if (input[i] == '.') {
        i++;
        if (!isdigit(input[i])) {
            printf("Formato invalido\n");
            return 1;
        }

        while (isdigit(input[i]) && i<sizeof(input)) {
            fraccion = fraccion * 10 + (input[i] - '0');
            divisor *= 10;
            i++;
        }
    }


    int32_t resultado = entera * ESCALA;

    if (divisor > 1) {
        resultado += (fraccion * ESCALA) / divisor;
    }

    resultado *= signo;
    printf("%d\n", resultado);


    if (resultado < -32768 || resultado > 32767) {
        printf("Error: fuera de rango\n");
        return 1;
    }

    printf("Resultado Q(7,8): 0x%04X\n", resultado);

    return 0;
}
