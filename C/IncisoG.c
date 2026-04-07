#include <stdio.h>
#include <stdint.h>
#include <ctype.h>/*No es necesario para esta implementacion*/
/* Codigo deseado -> 0xA200 -> -94 */
int esHex(char c);/*No se usa en esta implementacion*/
int hexToInt(char c);/*No se usa en esta implementacion*/

/*  g. Escriba otro programa que dado un número expresado
    en punto fijo de 16 bits Q(7,8) exprese el valor decimal
    equivalente eee.ffff. La entrada debe ser un numero
    hexadecimal expresado en la forma 0xHHHH que debe ser
    validada.
*/

int IncisoG(){
    uint16_t valor = 0;
    printf("Ingrese un numero en formato 0xHHHH: "); 
    
    /* Leer directamente hexadecimal */
    if (scanf("%hx", &valor) != 1) {
        printf("Formato invalido\n");
        return 1;
    }
    
    /*Mostrar el valor entero sin signo para verificar la conversión*/
    printf("Valor entero sin signo: %u\n", valor); 
    
    /* Interpretar como int16_t (complemento a 2)*/
    int16_t valor16 = (int16_t)valor; 
    
    /*Mostrar el valor entero con signo para verificar la interpretación*/
    printf("Valor entero con signo: %d\n", valor16); 
    
    /* Separar partes

    Formato Q(7,8):
   - 16 bits totales
   - 1 bit de signo
   - 7 bits parte entera
   - 8 bits parte fraccionaria
   - Valor real = numero / 256 
   */
    
    int signo = 1; /*Valor para representar el signo, se asume positivo por defecto*/
    int32_t abs_val = valor16; /*Convertir a valor absoluto para facilitar el cálculo de la parte entera y fraccionaria*/
    
    if (valor16 < 0) { 
        signo = -1;
        abs_val = -valor16; /*Si el número es negativo, se cambia el signo y se obtiene el valor absoluto "cambiado"*/
    }
    
    int entero = abs_val / 256; /*La parte entera se obtiene dividiendo el valor absoluto por 256,
    ya que en formato Q(7,8) la parte entera ocupa 7 bits y la parte fraccionaria ocupa 8 bits, lo que equivale a dividir por 2^8 = 256
    Basicamente la inversa de hacer resultado = entero * escala del conversor de decimal a hexa */

    int resto = abs_val % 256;/*La parte fraccionaria se obtiene como el residuo de la división por 256*/

    /* Se multiplica por 10000 para trabajar con enteros y simular 4 decimales.
    Es decir:
    fraccion = (resto / 256) ≈ decimal
    (resto * 10000) / 256 -> convierte a entero con 4 cifras decimales
    Ej: 0.5 -> 5000 -> se imprime como 0.5000 */
    int fraccion = (resto * 10000) /256; 


    /* Mostrar signo negativo*/
    if (signo < 0) {
        entero = -entero; /*Si el número es negativo, se muestra el signo y se convierte la parte entera a negativa para que se imprima correctamente*/
    }

    printf("valor en formato Q(7,8): %d.%04d\n", entero, fraccion); /* Mostrar el valor en formato Q(7,8)*/

    return 0;
}

/*Verificamos si es un carácter hexadecimal. No se usa en esta implementacion.*/
int esHex(char c){
    return isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

/*Convierte un carácter hexadecimal a su valor entero. No se usa para esta implementacion.*/
int hexToInt(char c){
    if (isdigit(c)){
        return c - '0'; /*Si es un dígito, restamos '0' para obtener su valor numérico*/
    }
    if (c >= 'A' && c <= 'F'){
        return 10 + (c - 'A');/*Si es una letra mayúscula, restamos 'A' y sumamos 10 para obtener su valor numérico*/
    } 
    if (c >= 'a' && c <= 'f') {
        return 10 + (c - 'a');/*Si es una letra minúscula, restamos 'a' y sumamos 10 para obtener su valor numérico*/
    }
    return 0;
}
