#include <stdio.h>
#include <ctype.h>
#include <string.h>

// IMPORTANTE
// - HAY QUE USAR Q(16,15) YA QUE ES LO QUE ELIGIO EL YUYO EN EL INCISO C. (ya lo deje en el programa pero por las dudas aclaro
#define A 16
#define B 15
// 2^16-2^(-15) = 65535.99996948242
#define RANGO_ENTERO 65535
#define RANGO_DECIMAL 99996948242
#define DEFINICION 000030517578125
#define ERROR 999

struct NumerosQ
{
    int signo; /* valor para representar el signo */
    int entera; /* variable para representar la parte entera del número */
    int fraccion; /* variable para representar la parte fraccionaria del número */
    int divisor; /* variable para guardar el divisor de la parte fraccionaria */
};

int IncisoH(){

    /*
     h. Escriba un programa que permita el ingreso de los valores de m, b y x en forma decimal y muestre su
     representación en punto fijo en formato hexadecimal validando la entrada como en los puntos anteriores.
     Luego realizando todas las operaciones en punto fijo con las representaciones adoptadas calcule el valor de
     la ordenada y y lo muestre en punto fijo en forma hexadecimal y en decimal.
    */




    return 0;
}

NumerosQ leerNumeros(){ // Lee un numero en punto fijo desde terminal y lo devuelve en una estructura, en caso de error el signo resultante es ERROR
    struct NumerosQ num;
    
    num.signo = 1;
    num.entera = 0;
    num.fraccion = 0;
    num.divisor = 1;

    printf("Ingrese un numero (+/-eee.ffff): ");

    /* lee de la entrada estandar stdin (el teclado), lee como máximo 49 caracteres y guarda en input, lo dejo en vez del scanf porque es más facil validar el tamaño y además evita crasheos*/
    if (!fgets(input, sizeof(input), stdin)) {
        printf("Error de entrada\n");
        num.signo = ERROR;
        return num;
    }

    int i = 0;


    /* valida el primer caracter como signo, si es negativo cambia la variable signo, si es positivo sigue de largo en el array */
    if (input[i] == '-') {
        num.signo = -1;
        i++;
    } else if (input[i] == '+') {
        i++;
    }

    /* si lee algo que no es un digito, corta */
    if (!isdigit(input[i])) {
        printf("Formato invalido\n");
        num.signo = ERROR;
        return num;
    }

    /* a medida que lee digitos, los va metiendo en la parte entera (añade digito a digito multiplicando por 10) (resta el '0' porque son caracteres) */
    while (isdigit(input[i]) && i<sizeof(input)) {
        num.entera = num.entera * 10 + (input[i] - '0');
        i++;
    }

    /* cuando lee el punto, empieza a completar la parte fraccionaria con el mismo proceso de arriba */
    if (input[i] == '.') {
        i++;
        if (!isdigit(input[i])) {
            printf("Formato invalido\n");
            num.signo = ERROR;
            return num;
        }

        while (isdigit(input[i]) && i<sizeof(input)) {
            num.fraccion = num.fraccion * 10 + (input[i] - '0');
            num.divisor *= 10;
            i++;
        }
    }

    return num;
}
