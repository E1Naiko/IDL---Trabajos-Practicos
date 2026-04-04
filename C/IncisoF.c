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
    int divisor = 1; /*variable para guardar el divisor de la parte fraccionaria */

    printf("Ingrese un numero (+/-eee.ffff): ");

    /* lee de la entrada estandar stdin (el teclado), lee como máximo 49 caracteres y guarda en input, lo dejo en vez del scanf porque es más facil validar el tamaño y además evita crasheos*/
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

    /* a medida que lee digitos, los va metiendo en la parte entera (añade digito a digito multiplicando por 10) (resta el '0' porque son caracteres)*/
    while (isdigit(input[i]) && i<sizeof(input)) {
        entera = entera * 10 + (input[i] - '0');
        i++;
    }

    /* cuando lee el punto, empieza a completar la parte fraccionaria con el mismo proceso de arriba */
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

    /*convierte la parte entera a punto flotante multiplicando por la escala (2^8)*/
    int resultado = entera * ESCALA;

    /*realiza el mismo proceso con la parte fraccionaria (para mejorar precisión realiza un redondeo sumando el divisor/2 al numero antes de hacer la división, ya que si lo haces directo algunos números no se representan bien)*/
    if (divisor > 1) {
        int num = fraccion * ESCALA;


        if (signo > 0)
            num += divisor / 2;
        else
            num -= divisor / 2;

        /*se suma la parte fraccionaria al resultado (para convertirla de entero a decimales se divide por el divisor)*/
        resultado += num / divisor;
    }
    /*multiplica por +-1 para darle signo al numero*/
    resultado *= signo;

    /*chequeo*/
    printf("%d\n", resultado);

    /*valida el rango (los numeros ahí equivalen a -128 y 127 en decimal respectivamente)*/
    if (resultado < -32768 || resultado > 32767) {
        printf("Error: fuera de rango\n");
        return 1;
    }

    /*imprime el resultado (se debe usar unsigned int ya que si no se pisan los signos - y el número se imprime incorrectamente)*/
    printf("Resultado Q(7,8): 0x%04X\n",(uint16_t) resultado);

    return 0;
}

